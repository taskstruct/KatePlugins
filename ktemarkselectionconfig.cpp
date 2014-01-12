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
#include "ktemarkselectionconfig.h"
#include "ui_ktemarkselectionconfig.h"

#include <QDebug>

KteMarkSelectionConfig::KteMarkSelectionConfig(QWidget *parent, const QVariantList &args):
    KCModule(KteMarkSelectionPluginFactory::componentData(), parent, args),
    m_ui( new Ui::KteMarkSelectionConfig() )
{
    m_ui->setupUi(this);
    
    connect( m_ui->kcolorbutton1, SIGNAL(changed(QColor)), this, SLOT(onChanged()) );
    connect( m_ui->kcolorbutton2, SIGNAL(changed(QColor)), this, SLOT(onChanged()) );
    connect( m_ui->kcolorbutton3, SIGNAL(changed(QColor)), this, SLOT(onChanged()) );
    connect( m_ui->kcolorbutton4, SIGNAL(changed(QColor)), this, SLOT(onChanged()) );
    connect( m_ui->kcolorbutton5, SIGNAL(changed(QColor)), this, SLOT(onChanged()) );
}

KteMarkSelectionConfig::~KteMarkSelectionConfig()
{
    delete m_ui;
}

void KteMarkSelectionConfig::save()
{
    qDebug() << "Saving...";
    QList<QColor> cols;
    
    cols.append( m_ui->kcolorbutton1->color() );
    cols.append( m_ui->kcolorbutton2->color() );
    cols.append( m_ui->kcolorbutton3->color() );
    cols.append( m_ui->kcolorbutton4->color() );
    cols.append( m_ui->kcolorbutton5->color() );
    
    KteMarkSelectionPlugin::saveConfig(cols);
    
    KteMarkSelectionPlugin *plugin = KteMarkSelectionPlugin::self();
    
    // update views
    if( plugin )
    {
        plugin->setColors(cols);
    }
    
    emit changed(false);
}

void KteMarkSelectionConfig::load()
{
    qDebug() << "Loading...";
    QList<QColor> colors( KteMarkSelectionPlugin::loadConfig() );
    
    m_ui->kcolorbutton1->setColor(colors[0]);
    m_ui->kcolorbutton2->setColor(colors[1]);
    m_ui->kcolorbutton3->setColor(colors[2]);
    m_ui->kcolorbutton4->setColor(colors[3]);
    m_ui->kcolorbutton5->setColor(colors[4]);
    
    emit changed(false);
}

void KteMarkSelectionConfig::defaults()
{
    m_ui->kcolorbutton1->setColor(KteMarkSelectionPlugin::s_defaultColors[0]);
    m_ui->kcolorbutton2->setColor(KteMarkSelectionPlugin::s_defaultColors[1]);
    m_ui->kcolorbutton3->setColor(KteMarkSelectionPlugin::s_defaultColors[2]);
    m_ui->kcolorbutton4->setColor(KteMarkSelectionPlugin::s_defaultColors[3]);
    m_ui->kcolorbutton5->setColor(KteMarkSelectionPlugin::s_defaultColors[4]);
    
    emit changed(true);
}

void KteMarkSelectionConfig::onChanged()
{
    emit changed(true);
}
