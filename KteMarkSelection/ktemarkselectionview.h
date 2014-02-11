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

#ifndef KTEHIGHLIGHTMARKERVIEW_H
#define KTEHIGHLIGHTMARKERVIEW_H

#include <QObject>
#include <KXMLGUIClient>

namespace KTextEditor {
    class MovingRange;
};

class KteMarkSelectionView : public QObject, public KXMLGUIClient
{
    Q_OBJECT
public:
    explicit KteMarkSelectionView(const QList<QColor> colros, KTextEditor::View *view = 0);
    ~KteMarkSelectionView();
    
    void setColors( const QList<QColor> colros );
    
    static const int SEL_COLORS_COUNT = 5;
private slots:
    void createSelection();
    void removeSelection();
    void removeAllSelections();
    
private:
    void clearSelection( int colorId );
    
    KTextEditor::View *m_view;
    QList<QColor> m_colors;
    QList<KTextEditor::MovingRange *> m_ranges[SEL_COLORS_COUNT];
};

#endif
