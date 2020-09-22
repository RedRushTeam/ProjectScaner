#ifndef RANDOM_GAME_H
#define RANDOM_GAME_H

#include "list_of_types.h"

using namespace std;

enum type_of_item{empty_, neprohod_object_, prohod_object_};

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
    void wheelEvent(QWheelEvent *event);

    int height_of_map;
    int weight_of_map;


private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    Ui::randome_game *ui;

    vector<vector<type_of_item>> vec_of_soderzimoe;
    std::mt19937* gen;
};

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

#endif // RANDOM_GAME_H
