/*
Copyright (C) 2015  Jean-Baptiste Mardelle <jb@kdenlive.org>
This file is part of Kdenlive. See www.kdenlive.org.

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of
the License or (at your option) version 3 or any later version
accepted by the membership of KDE e.V. (or its successor approved
by the membership of KDE e.V.), which shall act as a proxy 
defined in Section 14 of version 3 of the license.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "qmlaudiothumb.h"
#include <QPainter>

QmlAudioThumb::QmlAudioThumb(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
}

void QmlAudioThumb::setImage(QImage &img)
{
    m_img = img;
    update();
}

void QmlAudioThumb::paint(QPainter *painter)
{
    painter->drawImage(boundingRect().adjusted(1, 1, -1, -1), m_img);
}
