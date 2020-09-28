#include "graphic_window.h"
#include "ui_graphic_window.h"

graphic_window::graphic_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graphic_window)
{
    ui->setupUi(this);
}

graphic_window::~graphic_window()
{
    delete ui;
}
