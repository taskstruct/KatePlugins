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

#ifndef KTERANGEDELETERVIEW_H
#define KTERANGEDELETERVIEW_H

#include <QObject>
#include <KXMLGUIClient>

class KAction;

namespace KTextEditor {
    class View;
    class MovingCursor;
};

class KteRangeDeleterView : public QObject, public KXMLGUIClient
{
	Q_OBJECT
	public:
		explicit KteRangeDeleterView(KTextEditor::View *view = 0);
		~KteRangeDeleterView();
	private slots:
		void onSetStartPos();
        void onFinish();
	private:
		KTextEditor::View *m_view;
        KTextEditor::MovingCursor* m_startPosCursor;
        KAction *m_finishAction;
};

#endif
