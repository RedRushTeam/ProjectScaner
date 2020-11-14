#ifndef CHANGE_SIZE_H
#define CHANGE_SIZE_H
#pragma once

#include "random_game.h"
#include "prepod_game.h"

namespace Ui {
class change_size;
}

class change_size : public QDialog
{
    Q_OBJECT

public:
    explicit change_size(QWidget *parent = nullptr);
    ~change_size();

    bool is_this_will_be_random_game = false;
    bool is_this_will_be_prep_game = false;
    bool is_this_will_be_god_game = false;

    void closeEvent(QCloseEvent *event);

private slots:
    void OK_clicked();

private:
    Ui::change_size *ui;
    QLineEdit *high;
    QLineEdit *weight;
};

#endif // CHANGE_SIZE_H
