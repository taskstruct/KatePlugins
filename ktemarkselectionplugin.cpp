/*
 * KteMarkSelection - Plugin for Kate that allows you to highlight text chunks
 * Copyright (C) 2013  Nikolay S Nikolov nikolay.fatal.error@gmail.com
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

#include "ktemarkselectionplugin.h"
#include "ktemarkselectionview.h"
#include "ktemarkselectionconfig.h"

#include <QtGui/QColor>

#include <KTextEditor/Document>
#include <KTextEditor/View>
#include <KTextEditor/SearchInterface>
#include <KTextEditor/MovingInterface>
#include <KTextEditor/Attribute>

#include <KPluginFactory>
#include <KPluginLoader>
#include <KLocale>
#include <KAction>
#include <KActionCollection>
#include <KConfigGroup>

#include <QDebug>

K_PLUGIN_FACTORY_DEFINITION(KteMarkSelectionPluginFactory, 
                 registerPlugin<KteMarkSelectionPlugin>("ktexteditor_ktemarkselection");
                 registerPlugin<KteMarkSelectionConfig>("ktexteditor_ktemarkselection_config");
    )

K_EXPORT_PLUGIN(KteMarkSelectionPluginFactory("ktexteditor_ktemarkselection", "ktexteditor_plugins"))

//================================== KteMarkSelectionPlugin ==================================

KteMarkSelectionPlugin *KteMarkSelectionPlugin::m_plugin = 0;
const QColor KteMarkSelectionPlugin::s_defaultColors[KteMarkSelectionView::SEL_COLORS_COUNT] = { Qt::red, Qt::blue, Qt::green, Qt::cyan, Qt::lightGray };

KteMarkSelectionPlugin::KteMarkSelectionPlugin(QObject *parent, const QVariantList &args): KTextEditor::Plugin(parent)
{
    Q_UNUSED(args);
    
    m_plugin = this;
    
    readConfig();
}

KteMarkSelectionPlugin::~KteMarkSelectionPlugin()
{
    m_plugin = 0;
}

void KteMarkSelectionPlugin::addView(KTextEditor::View *view)
{
    KteMarkSelectionView *nview = new KteMarkSelectionView(m_colors, view);
    m_views.append(nview);
}

void KteMarkSelectionPlugin::removeView(KTextEditor::View *view)
{
    for (int z = 0; z < m_views.size(); z++) {
        if (m_views.at(z)->parentClient() == view) {
            KteMarkSelectionView *nview = m_views.at(z);
            m_views.removeAll(nview);
            delete nview;
        }
    }
}

void KteMarkSelectionPlugin::readConfig()
{
    m_colors = loadConfig();
}

void KteMarkSelectionPlugin::writeConfig()
{
    saveConfig( m_colors );
}

void KteMarkSelectionPlugin::setColors( const QList<QColor> colors )
{
    m_colors = colors;
    
    foreach (KteMarkSelectionView *pluginView, m_views)
    {
        pluginView->setColors(colors);
    }
}

void KteMarkSelectionPlugin::saveConfig( const QList<QColor> colors )
{
    KConfigGroup cg(KGlobal::config(), "KteMarkSelectionPlugin");
    
    cg.writeEntry( "color0", colors[0] );
    cg.writeEntry( "color1", colors[1] );
    cg.writeEntry( "color2", colors[2] );
    cg.writeEntry( "color3", colors[3] );
    cg.writeEntry( "color4", colors[4] );
}

QList<QColor> KteMarkSelectionPlugin::loadConfig()
{   
    QList<QColor> values;
    
    KConfigGroup cg(KGlobal::config(), "KteMarkSelectionPlugin");
    
    QVariant var = cg.readEntry( "color0", s_defaultColors[0] );
    values.append(var.value<QColor>());
    
    var = cg.readEntry( "color1", s_defaultColors[1] );
    values.append(var.value<QColor>());
    
    var = cg.readEntry( "color2", s_defaultColors[2] );
    values.append(var.value<QColor>());;
    
    var = cg.readEntry( "color3", s_defaultColors[3] );
    values.append(var.value<QColor>());
    
    var = cg.readEntry( "color4", s_defaultColors[4] );
    values.append(var.value<QColor>());
    
    return values;
}

//================================== KteMarkSelectionView ==================================

KteMarkSelectionView::KteMarkSelectionView(const QList<QColor> colros, KTextEditor::View *view): QObject(view), KXMLGUIClient(view),
    m_view(view),
    m_colors(colros)
{
    m_colors.reserve(SEL_COLORS_COUNT);
    
//     setObjectName("mark-selection-plugin");

    setComponentData(KteMarkSelectionPluginFactory::componentData());

    // mark actions
    KAction *action = new KAction(i18n("1st style"), this);
    actionCollection()->addAction("tools_ktemarkselection1", action);
    action->setProperty( "colorID", 0 );
    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect(action, SIGNAL(triggered()), this, SLOT(createSelection()));
    
    action = new KAction(i18n("2nd style"), this);
    actionCollection()->addAction("tools_ktemarkselection2", action);
    action->setProperty( "colorID", 1 );
    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect(action, SIGNAL(triggered()), this, SLOT(createSelection()));
    
    action = new KAction(i18n("3rd style"), this);
    actionCollection()->addAction("tools_ktemarkselection3", action);
    action->setProperty( "colorID", 2 );
    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect(action, SIGNAL(triggered()), this, SLOT(createSelection()));
    
    action = new KAction(i18n("4th style"), this);
    actionCollection()->addAction("tools_ktemarkselection4", action);
    action->setProperty( "colorID", 3 );
    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect(action, SIGNAL(triggered()), this, SLOT(createSelection()));
    
    action = new KAction(i18n("5th style"), this);
    actionCollection()->addAction("tools_ktemarkselection5", action);
    action->setProperty( "colorID", 4 );
    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect(action, SIGNAL(triggered()), this, SLOT(createSelection()));
    
    // unmark actions
    action = new KAction(i18n("1st style"), this);
    actionCollection()->addAction("tools_kteunmarkselection1", action);
    action->setProperty( "colorID", 0 );
    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect(action, SIGNAL(triggered()), this, SLOT(removeSelection()));
    
    action = new KAction(i18n("2nd style"), this);
    actionCollection()->addAction("tools_kteunmarkselection2", action);
    action->setProperty( "colorID", 1 );
    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect(action, SIGNAL(triggered()), this, SLOT(removeSelection()));
    
    action = new KAction(i18n("3rd style"), this);
    actionCollection()->addAction("tools_kteunmarkselection3", action);
    action->setProperty( "colorID", 2 );
    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect(action, SIGNAL(triggered()), this, SLOT(removeSelection()));
    
    action = new KAction(i18n("4th style"), this);
    actionCollection()->addAction("tools_kteunmarkselection4", action);
    action->setProperty( "colorID", 3 );
    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect(action, SIGNAL(triggered()), this, SLOT(removeSelection()));
    
    action = new KAction(i18n("5th style"), this);
    actionCollection()->addAction("tools_kteunmarkselection5", action);
    action->setProperty( "colorID", 4 );
    //action->setShortcut(Qt::CTRL + Qt::Key_XYZ);
    connect(action, SIGNAL(triggered()), this, SLOT(removeSelection()));

    setXMLFile("ktemarkselectionui.rc");
}

KteMarkSelectionView::~KteMarkSelectionView()
{
    for( int i = 0; i < SEL_COLORS_COUNT; ++i)
    {
        clearSelection(i);
    }
}

void KteMarkSelectionView::createSelection()
{
    //TODO: Validation
    const int colorId = sender()->property("colorID").toInt();
    
    qDebug() << "createSelection(" << colorId << ")";
    
//     static QColor s_selColors[5] = { Qt::red, Qt::blue, Qt::green, Qt::cyan, Qt::lightGray };

    QString selectionText;
    //TODO: Disable menu entry with .rc file <enable>?
    if (m_view->selection()) {
        selectionText = m_view->selectionText();
    } else {
        return;
    }

    // get search interface
    KTextEditor::SearchInterface *sIFace = qobject_cast< KTextEditor::SearchInterface * >(m_view->document());

    if (!sIFace) {
        return;
    }

    // get moving interface
    KTextEditor::MovingInterface *mIFace = qobject_cast< KTextEditor::MovingInterface * >(m_view->document());

    if (!mIFace) {
        return;
    }

    KTextEditor::Attribute::Ptr attr(new KTextEditor::Attribute());

    attr->setBackground(m_colors[colorId]);

    KTextEditor::Cursor start(0, 0);
    KTextEditor::Range searchRange;

    //TODO: Is it possible to loop only in matches? Or adding atribute moves range?
    QVector<KTextEditor::Range> matches;
    do {
        searchRange.setRange(start, m_view->document()->documentEnd());

        matches = sIFace->searchText(searchRange, selectionText, KTextEditor::Search::Regex);

        if (matches.first().isValid()) 
        {
            KTextEditor::MovingRange *mr = mIFace->newMovingRange(matches.first());
            mr->setAttribute(attr);
            mr->setView(m_view);
            mr->setZDepth(-90000.0 + colorId); // Set the z-depth to slightly worse than the selection
            mr->setAttributeOnlyForViews(true);
            m_ranges[colorId].append(mr);
            start = matches.first().end();
        }
    } 
    while (matches.first().isValid());
}

void KteMarkSelectionView::removeSelection()
{
    //TODO: Validation
    const int colorId = sender()->property("colorID").toInt();
    clearSelection(colorId);
}

void KteMarkSelectionView::setColors( const QList<QColor> colors )
{
    for( int i = 0; i < SEL_COLORS_COUNT; ++i )
    {
        if( colors[i] != m_colors[i] )
        {
            m_colors[i] = colors[i];
            
            if( !m_ranges[i].isEmpty() )
            {
                foreach( KTextEditor::MovingRange* r, m_ranges[i] )
                {
                    r->attribute()->setBackground(m_colors[i]);
                }
            }
        }
    }
}

void KteMarkSelectionView::clearSelection( int colorId )
{
    //TODO: check colorId
    qDeleteAll(m_ranges[colorId]);
    m_ranges[colorId].clear();
}

#include "ktemarkselectionview.moc"
