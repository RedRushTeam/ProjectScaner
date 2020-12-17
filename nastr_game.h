#ifndef NASTR_GAME_H
#define NASTR_GAME_H

#include "prepod_game.h"

namespace Ui {
class nastr_game;
}

enum type_of_texture{empty__, white_chair_, divan_big_, simpe_divan_, pro_table_, wood_chair_128x128_, pol_128x128_, Bricks_H_, tableH_, red_square_, Bricks_V_, GG__};

class nastr_game : public randome_game
{
    Q_OBJECT

public:
    explicit nastr_game(QWidget *parent = nullptr, int weight = 10, int height = 10);

private:
    type_of_texture type_of_texture_ = empty__;
    bool is_game_started_now = false;
    bool is_las_texture_was_be_3x = false;
    bool dialog_method();

private slots:
    void white_chair_add();
    void divan_big_add();
    void simpe_divan_add();
    void pro_table_add();
    void wood_chair_128x128_add();
    void pol_128x128_add();
    void Bricks_H_add();
    void tableH_add();
    void red_square_add();
    void Bricks_V_add();
    void hero_add();

    //for menue bar
    void upload();
    void download();
    void clear_all();
    void start_game();

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

    vector<vector<type_of_texture>> vec_of_concr_texture;
};

#endif // NASTR_GAME_H
