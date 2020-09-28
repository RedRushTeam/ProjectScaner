#ifndef RANDOM_GAME_H
#define RANDOM_GAME_H
#pragma once

#include "graphic_window.h"

enum orientation_of_hero{left_, right_, up_, down_};
enum type_of_fluctuation{no_fluct_, inactive_semiconductors_, active_semiconductors_, bluetooth_, _5g_, _4g_, _3g_, GPS_, radio_, GLONASS_};

//              kostil'
class myGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    myGraphicsView(QGraphicsScene* scene) {
        //setDragMode(QGraphicsView::ScrollHandDrag);
        this->setScene(scene);
    }

    void wheelEvent(QWheelEvent *event){
        const QGraphicsView::ViewportAnchor anchor = this->transformationAnchor();
        this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        int angle = event->angleDelta().y();
        qreal factor;

        if (angle > 0)
           factor = 1.1;
        else
           factor = 0.9;

        this->scale(factor, factor);
        this->setTransformationAnchor(anchor);
    }
};
//              kostil'//

//              kostil'
class Pixmap : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    Pixmap(const QPixmap &pix)
        : QObject(), QGraphicsPixmapItem(pix)
    {
        setCacheMode(DeviceCoordinateCache);
    }
};
//              kostil'//

//              kostil'
class Hero : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
public:
    Hero(const QPixmap &pix)
        : QObject(), QGraphicsPixmapItem(pix)
    {
        setCacheMode(DeviceCoordinateCache);
    }

    pair<int, int> coordinate;
    orientation_of_hero _orientation_of_hero = left_;
};
//              kostil'//

namespace Ui {
class randome_game;
}

class randome_game : public QDialog
{
    Q_OBJECT

public:
    explicit randome_game(QWidget *parent = nullptr, int weight = 10, int height = 10);
    ~randome_game();

    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent * event);
    int generate_random_int_number(int min, int max) const;
    void generate_map();
    void set_scene_size();
    bool check_cycle(pair<int, int> coord) const;
    void add_hero();
    void add_zakladka();
    void generate_flukt();
    void generate_graphik_perems();
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *mEvent);

    Hero* _hero;
    int height_of_map;
    int weight_of_map;
    int col_vo_popytok = 3;
    pair<int, int> _vibrannaya_kletka = make_pair(-1, -1);
    pair<int, int> _coordinate_of_zakladka;


private:
    myGraphicsView* view;
    QGraphicsScene* scene;
    Ui::randome_game *ui;

    vector<vector<type_of_item>> vec_of_soderzimoe;
    vector<vector<type_of_fluctuation>> vec_of_fluct;
    std::mt19937* gen;
};
#endif // RANDOM_GAME_H
