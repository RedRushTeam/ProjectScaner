#ifndef RANDOM_GAME_H
#define RANDOM_GAME_H
#pragma once

#include "graphic_window.h"

enum orientation_of_hero{left_, right_, up_, down_};

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
        this->_timer = new QTimer();
        this->_timer->setTimerType(Qt::TimerType::PreciseTimer);
        this->_timer->setInterval(500);
        this->_timer->stop();

        this->_timer_obnovl = new QTimer();
        this->_timer_obnovl->setTimerType(Qt::TimerType::PreciseTimer);
        this->_timer_obnovl->setInterval(10);
        this->_timer_obnovl->stop();

        connect(_timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
        connect(_timer_obnovl, SIGNAL(timeout()), this, SLOT(slotTimerAlarm1()));
        this->mo = new QMovie();
        this->mo->setCacheMode(QMovie::CacheAll);
        this->mo->setSpeed(125);
        this->mo->setFileName(":/new/random_game_textures/new/random_game_textures/Animation.gif");
    }

    QTimer* _timer_obnovl;
    QTimer* _timer;
    QMovie* mo;
    pair<int, int> coordinate;
    orientation_of_hero _orientation_of_hero = down_;

private slots:
    void slotTimerAlarm()
    {
        //
        //qDebug() << QString("Таймер встал");
        this->_timer->setInterval(500);
        this->_timer->stop();
        this->mo->stop();
        this->_timer_obnovl->stop();
        this->mo->jumpToFrame(0);
        this->setPixmap(this->mo->currentPixmap());
    }

    void slotTimerAlarm1()
    {
        //
        this->setPixmap(this->mo->currentPixmap());
        this->update();
        this->_timer_obnovl->setInterval(10);
        this->_timer_obnovl->start();
    }
};
//              kostil'//

namespace Ui {
class randome_game;
}

class randome_game : public QDialog
{
    Q_OBJECT

public:
    randome_game(QWidget *parent = nullptr, int weight = 10, int height = 10);
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
    void add_concret_fluct_second_formanta(int start, int length, float power_of_fluct);
    void add_concret_fluct_trird_formanta(int start, int length, float power_of_fluct);
    bool is_coordinate_is_normal(pair<int, int> _coordinate) const;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QMouseEvent *mEvent);
    void keyReleaseEvent(QKeyEvent *event);
    void move_hero();
    void start_animation_and_move_hero();

    Hero* _hero;
    int height_of_map;
    int weight_of_map;
    int col_vo_popytok = 3;
    pair<int, int> _vibrannaya_kletka = make_pair(-1, -1);
    Pixmap* _pix_chaged_cell = nullptr;
    pair<int, int> _coordinate_of_zakladka;
    QTimer* _timer;
    bool is_move_possible = true;
    int start;

protected slots:
    void slotTimerAlarm();
    void slotTimerStopAnimationAlarm();
    void slotTimerChangePositionAlarm();

protected:
    QVBoxLayout* hbox;
    myGraphicsView* view;
    QGraphicsScene* scene;
    Ui::randome_game *ui;

    QTimer* _timer_stop_animation;
    QTimer* _timer_for_change_position;
    vector<vector<type_of_item>> vec_of_soderzimoe;
    vector<vector<pair<type_of_fluctuation, float>>> vec_of_fluct;
    vector<vector<Pixmap*>> vec_of_pixmaps;
    vector<pair<float, float>>* vec_of_graphik_of_second_formanta;
    vector<pair<float, float>>* vec_of_graphik_of_trird_formanta;
    std::mt19937* gen;
};
#endif // RANDOM_GAME_H
