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

#ifndef KTEHIGHLIGHTMARKERPLUGIN_H
#define KTEHIGHLIGHTMARKERPLUGIN_H

#include <KTextEditor/Plugin>

#include "ktemarkselectionview.h"

namespace KTextEditor
{
	class View;
}

class KteMarkSelectionView;

class KteMarkSelectionPlugin: public KTextEditor::Plugin
{
  public:
    // Constructor
    explicit KteMarkSelectionPlugin(QObject *parent = 0, const QVariantList &args = QVariantList());
    // Destructor
    virtual ~KteMarkSelectionPlugin();
    
    static KteMarkSelectionPlugin *self() { return m_plugin; }
    static void saveConfig( const QList<QColor> colors );
    static QList<QColor> loadConfig();

    void addView (KTextEditor::View *view);
    void removeView (KTextEditor::View *view);
 
    void readConfig();
    void writeConfig();
    
    virtual void readConfig (KConfig *) {}
    virtual void writeConfig (KConfig *) {}
    
    void setColors( const QList<QColor> colros );
 
    static const QColor s_defaultColors[KteMarkSelectionView::SEL_COLORS_COUNT];
  private:
    static KteMarkSelectionPlugin *m_plugin;
    
    QList<class KteMarkSelectionView*> m_views;
    QList< QColor > m_colors;
};

K_PLUGIN_FACTORY_DECLARATION(KteMarkSelectionPluginFactory)

#endif
