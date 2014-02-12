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

#ifndef KTERANGEDELETERPLUGIN_H
#define KTERANGEDELETERPLUGIN_H

#include <KTextEditor/Plugin>

namespace KTextEditor
{
	class View;
}

class KteRangeDeleterView;

class KteRangeDeleterPlugin
  : public KTextEditor::Plugin
{
  public:
    // Constructor
    explicit KteRangeDeleterPlugin(QObject *parent = 0, const QVariantList &args = QVariantList());
    // Destructor
    virtual ~KteRangeDeleterPlugin();

    void addView (KTextEditor::View *view);
    void removeView (KTextEditor::View *view);
 
    void readConfig();
    void writeConfig();
 
//     void readConfig (KConfig *);
//     void writeConfig (KConfig *);
 
  private:
    QList<class KteRangeDeleterView*> m_views;
};

#endif
