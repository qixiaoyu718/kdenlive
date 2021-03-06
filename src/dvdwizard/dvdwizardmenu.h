/***************************************************************************
 *   Copyright (C) 2009 by Jean-Baptiste Mardelle (jb@kdenlive.org)        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA          *
 ***************************************************************************/


#ifndef DVDWIZARDMENU_H
#define DVDWIZARDMENU_H

#include "dvdwizardvob.h"
#include "ui_dvdwizardmenu_ui.h"

#include <QWizardPage>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QDomElement>

#include <QDebug>
#include <KMessageWidget>

class DvdScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DvdScene(QObject * parent = 0);
    void setProfile(int width, int height);
    int gridSize() const;
    void setGridSize(int gridSize);
private:
    int m_width;
    int m_height;
    int m_gridSize;
protected:
    void mouseReleaseEvent( QGraphicsSceneMouseEvent * mouseEvent );
    void drawForeground(QPainter *painter, const QRectF &rect);
signals:
    void sceneChanged();
};

class DvdButtonUnderline : public QGraphicsRectItem
{

public:
    explicit DvdButtonUnderline( const QRectF & rect, QGraphicsItem * parent = 0 ) : QGraphicsRectItem(rect, parent) {}

    int type() const {
        // Enable the use of qgraphicsitem_cast with this item.
        return UserType + 2;
    }
};

class DvdButton : public QGraphicsTextItem
{
public:
    explicit DvdButton(const QString & text);
    void setTarget(int t, const QString &c);
    int target() const;
    QString command() const;
    bool backMenu() const;
    int type() const;
    void setBackMenu(bool back);
private:
    int m_target;
    QString m_command;
    bool m_backToMenu;
protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

class DvdWizardMenu : public QWizardPage
{
    Q_OBJECT

public:
    explicit DvdWizardMenu(DVDFORMAT format, QWidget * parent = 0);
    virtual ~DvdWizardMenu();
    bool createMenu() const;
    void createBackgroundImage(const QString &img1, bool letterbox);
    void createButtonImages(const QString &selected_image, const QString &highlighted_image, bool letterbox);
    void setTargets(const QStringList &list, const QStringList &targetlist);
    QMap <QString, QRect> buttonsInfo(bool letterbox = false);
    bool loopMovie() const;
    bool menuMovie() const;
    QString menuMoviePath() const;
    int menuMovieLength() const;
    void changeProfile(DVDFORMAT format);
    QDomElement toXml() const;
    void loadXml(DVDFORMAT format, const QDomElement &xml);
    void prepareUnderLines();
    void resetUnderLines();

private:
    Ui::DvdWizardMenu_UI m_view;
    DVDFORMAT m_format;
    DvdScene *m_scene;
    QGraphicsPixmapItem *m_background;
    QGraphicsRectItem *m_color;
    QGraphicsRectItem *m_safeRect;
    int m_width;
    int m_height;
    QSize m_finalSize;
    int m_movieLength;
    KMessageWidget *m_menuMessage;

private slots:
    void buildButton();
    void buildColor();
    void buildImage();
    void checkBackgroundType(int ix);
    void updatePreview();
    void buttonChanged();
    void addButton();
    void setButtonTarget(int ix);
    void deleteButton();
    void updateColor();
    void updateColor(const QColor &c);
    void updateUnderlineColor(QColor c);
    void setBackToMenu(bool backToMenu);
    void slotZoom();
    void slotUnZoom();
    void slotEnableShadows(int enable);
    void slotUseGrid(bool useGrid);
};

#endif

