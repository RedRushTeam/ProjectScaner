#include "random_game.h"
#include "ui_random_game.h"

randome_game::randome_game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::randome_game)
{
    ui->setupUi(this);
}

randome_game::~randome_game()
{
    delete ui;
}
