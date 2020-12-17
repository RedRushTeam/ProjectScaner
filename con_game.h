#ifndef CON_GAME_H
#define CON_GAME_H

#include "nastr_game.h"

namespace Ui {
class con_game;
}

class con_game : public randome_game
{
    Q_OBJECT

public:
    explicit con_game(QWidget *parent = nullptr, int weight = 10, int height = 10, QString full_fname = "/");
    ~con_game();

private:
    void clear_all();
    void download();
    bool is_las_texture_was_be_3x = false;
    QString full_fname;

    vector<vector<type_of_texture>> vec_of_concr_texture;

};

#endif // CON_GAME_H
