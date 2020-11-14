#include "nastr_game.h"
#include "ui_nastr_game.h"

nastr_game::nastr_game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nastr_game)
{
    ui->setupUi(this);
}

nastr_game::~nastr_game()
{
    delete ui;
}
