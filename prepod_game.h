#ifndef PREPOD_GAME_H
#define PREPOD_GAME_H

#include "random_game.h"

class prepod_game : public randome_game
{
public:
    prepod_game();
    explicit prepod_game(QWidget *parent = nullptr, int weight = 10, int height = 10);

private slots:
    void ok_pushed();

    // QWidget interface
protected:
    QPushButton* start_with_rand;
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
};

#endif // PREPOD_GAME_H
