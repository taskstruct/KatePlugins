/*
 * KteRangeDeleter - Plugin for Kate that allows you to easily remove large chunks of text
 * Copyright (C) 2014  Nikolay S Nikolov nikolay.fatal.error@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "kterangedeleterplugin.h"
#include "kterangedeleterview.h"

#include <KTextEditor/Document>
#include <KTextEditor/MovingInterface>
#include <KTextEditor/MovingCursor>
#include <KTextEditor/View>

#include <KPluginFactory>
#include <KPluginLoader>
#include <KLocale>
#include <KAction>
#include <KActionCollection>

#include <QDebug>

K_PLUGIN_FACTORY(KteRangeDeleterPluginFactory, registerPlugin<KteRangeDeleterPlugin>("ktexteditor_kterangedeleter");)
K_EXPORT_PLUGIN(KteRangeDeleterPluginFactory("ktexteditor_kterangedeleter", "ktexteditor_plugins"))

KteRangeDeleterPlugin::KteRangeDeleterPlugin(QObject *parent, const QVariantList &args)
: KTextEditor::Plugin(parent)
{
	Q_UNUSED(args);
}

KteRangeDeleterPlugin::~KteRangeDeleterPlugin()
{
}

void KteRangeDeleterPlugin::addView( KTextEditor::View *view )
{
    KteRangeDeleterView *nview = new KteRangeDeleterView( view );
    m_views.append( nview );
}

void KteRangeDeleterPlugin::removeView( KTextEditor::View *view )
{
    for( int z = 0; z < m_views.size(); z++ )
    {
        if( m_views.at( z )->parentClient() == view )
        {
            KteRangeDeleterView *nview = m_views.at( z );
            m_views.removeAll( nview );
            delete nview;
        }
    }
}

void KteRangeDeleterPlugin::readConfig()
{
}

void KteRangeDeleterPlugin::writeConfig()
{
}

KteRangeDeleterView::KteRangeDeleterView( KTextEditor::View *view ): QObject( view ), KXMLGUIClient( view ),
    m_view( view ),
    m_startPosCursor( 0 )
{
    setComponentData( KteRangeDeleterPluginFactory::componentData() );

    KAction *action = new KAction( KIcon("start"), i18n( "Set start position" ), this );
    actionCollection()->addAction( "tools_kterd_setstartpos", action );

    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect( action, SIGNAL( triggered() ), this, SLOT( onSetStartPos() ) );

    m_finishAction = new KAction( KIcon("edit-delete"), i18n( "Delete to here" ), this );
    actionCollection()->addAction( "tools_kterd_finish", m_finishAction );
    m_finishAction->setEnabled( false );
    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect( m_finishAction, SIGNAL( triggered() ), this, SLOT( onFinish() ) );

    setXMLFile( "kterangedeleterui.rc" );
}

KteRangeDeleterView::~KteRangeDeleterView()
{
}

void KteRangeDeleterView::onSetStartPos()
{
    KTextEditor::MovingInterface* moving = qobject_cast<KTextEditor::MovingInterface*>( m_view->document() );
    
    qDebug() << "has moving interface: " << moving;
    
    // clear old if any
    if( m_startPosCursor ) {
        delete m_startPosCursor;
    }
    
    if( moving ) {
        m_startPosCursor = moving->newMovingCursor( m_view->cursorPosition() );
        m_finishAction->setEnabled(true);
        qDebug() << "m_startPosCursor = " << m_startPosCursor;
    }
}

void KteRangeDeleterView::onFinish()
{
    KTextEditor::MovingInterface* moving = qobject_cast<KTextEditor::MovingInterface*>( m_view->document() );
    
    if( !moving ) {
        return;
    }
    
    KTextEditor::MovingCursor *endCursor = moving->newMovingCursor( m_view->cursorPosition() );
        
    if( !endCursor ) {
        return;
    }
    
    qDebug() << "endCursor = " << endCursor;
    
    m_view->document()->removeText( KTextEditor::Range( *m_startPosCursor, *endCursor ) );
    
    delete m_startPosCursor;
    delete endCursor;
    
    m_startPosCursor = 0;
    
    m_finishAction->setEnabled(false);
}

#include "kterangedeleterview.moc"
