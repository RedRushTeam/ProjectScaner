#ifndef RANDOM_GAME_H
#define RANDOM_GAME_H

#include "list_of_types.h"

namespace Ui {
class randome_game;
}

class randome_game : public QDialog
{
    Q_OBJECT

public:
    explicit randome_game(QWidget *parent = nullptr);
    ~randome_game();

    void closeEvent(QCloseEvent *event);
    void resizeEvent(QResizeEvent * event);

private:
    QGraphicsView* view;
    QGraphicsScene* scene;
    Ui::randome_game *ui;
};

#endif // RANDOM_GAME_H
