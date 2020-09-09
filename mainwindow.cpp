#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);

    vbox->setContentsMargins(50, 5, 50, 50);
    vbox->setSpacing(10);

    QFont font_for_buttons("Times new roman", 14, QFont::Bold);

    QFont font_for_label("Times new roman", 18, QFont::ExtraBold);

    QLabel *title = new QLabel("Project SCANER", this);
    title->setFont(font_for_buttons);
    title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    vbox->addWidget(title);

    QPushButton *start_with_rand = new QPushButton("Случайный режим", this);
    start_with_rand->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_with_rand->setCursor(QCursor(Qt::PointingHandCursor));
    start_with_rand->setFont(font_for_buttons);
    vbox->addWidget(start_with_rand);

    QPushButton *start_with_prep = new QPushButton("Режим с преподавателем", this);
    start_with_prep->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_with_prep->setCursor(QCursor(Qt::PointingHandCursor));
    start_with_prep->setFont(font_for_buttons);
    vbox->addWidget(start_with_prep);

    QPushButton *start_with_settings = new QPushButton("Настраиваемый режим", this);
    start_with_settings->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_with_settings->setCursor(QCursor(Qt::PointingHandCursor));
    start_with_settings->setFont(font_for_buttons);
    vbox->addWidget(start_with_settings);

    QPushButton *help_ = new QPushButton("Помощь", this);
    help_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    help_->setCursor(QCursor(Qt::PointingHandCursor));
    help_->setFont(font_for_buttons);
    vbox->addWidget(help_);

    QPushButton *about_ = new QPushButton("О программе", this);
    about_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    about_->setCursor(QCursor(Qt::PointingHandCursor));
    about_->setFont(font_for_buttons);
    vbox->addWidget(about_);

    QPushButton *exit_ = new QPushButton("Выход", this);
    exit_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    exit_->setCursor(QCursor(Qt::PointingHandCursor));
    exit_->setFont(font_for_buttons);
    vbox->addWidget(exit_);

    connect(exit_, &QPushButton::clicked, qApp, &QApplication::quit);

    this->setMinimumSize(720, 420);
}
