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

#ifndef KTEMARKSELECTIONCONFIG_H
#define KTEMARKSELECTIONCONFIG_H

#include <KCModule>

namespace Ui
{
class KteMarkSelectionConfig;
}

class KteMarkSelectionConfig : public KCModule
{
    Q_OBJECT
    
public:
    explicit KteMarkSelectionConfig(QWidget *parent = 0, const QVariantList &args = QVariantList());
    virtual ~KteMarkSelectionConfig();

    virtual void save();
    virtual void load();
    virtual void defaults();    

public slots:
    void onChanged();
    
private:
    Ui::KteMarkSelectionConfig *m_ui;
};

#endif // KTEMARKSELECTIONCONFIG_H
