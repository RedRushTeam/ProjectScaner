#ifndef NASTR_GAME_H
#define NASTR_GAME_H

#include <QDialog>

namespace Ui {
class nastr_game;
}

class nastr_game : public QDialog
{
    Q_OBJECT

public:
    explicit nastr_game(QWidget *parent = nullptr);
    ~nastr_game();

private:
    Ui::nastr_game *ui;
};

#endif // NASTR_GAME_H
