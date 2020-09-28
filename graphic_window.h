#ifndef GRAPHIC_WINDOW_H
#define GRAPHIC_WINDOW_H
#pragma once

#include "list_of_types.h"

enum type_of_item{empty_, neprohod_object_, prohod_object_, GG_};

using namespace std;

namespace Ui {
class graphic_window;
}

class graphic_window : public QDialog
{
    Q_OBJECT

public:
    explicit graphic_window(QWidget *parent = nullptr);
    ~graphic_window();

    vector<vector<type_of_item>>* vec_of_soderzimoe;

private:
    Ui::graphic_window *ui;
};

#endif // GRAPHIC_WINDOW_H
