#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    vbox = new QVBoxLayout(this);

    vbox->setContentsMargins(100, 15, 100, 200);
    vbox->setSpacing(20);

    QFont font_for_buttons("Times new roman", 18, QFont::Bold);

    QFont font_for_label("Times new roman", 24, QFont::ExtraBold);

    title = new QLabel("Project SCANER", this);
    title->setFont(font_for_buttons);
    title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    vbox->addWidget(title);

    start_with_rand = new QPushButton("Случайный режим", this);
    start_with_rand->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_with_rand->setCursor(QCursor(Qt::PointingHandCursor));
    start_with_rand->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
    start_with_rand->setFont(font_for_buttons);
    vbox->addWidget(start_with_rand);

    start_with_prep = new QPushButton("Режим с преподавателем", this);
    start_with_prep->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_with_prep->setCursor(QCursor(Qt::PointingHandCursor));
    start_with_prep->setStyleSheet("QPushButton {     background-color: rgba(0, 85, 0, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
    start_with_prep->setFont(font_for_buttons);
    vbox->addWidget(start_with_prep);

    start_with_settings = new QPushButton("Настраиваемый режим", this);
    start_with_settings->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_with_settings->setCursor(QCursor(Qt::PointingHandCursor));
    start_with_settings->setStyleSheet("QPushButton {     background-color: rgba(0, 85, 0, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
    start_with_settings->setFont(font_for_buttons);
    vbox->addWidget(start_with_settings);

    _pass = new QPushButton("Разблокировка режимов преподавателя", this);
    _pass->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    _pass->setCursor(QCursor(Qt::PointingHandCursor));
    _pass->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
    _pass->setFont(font_for_buttons);
    vbox->addWidget(_pass);

    help_ = new QPushButton("Помощь", this);
    help_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    help_->setCursor(QCursor(Qt::PointingHandCursor));
    help_->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
    help_->setFont(font_for_buttons);
    vbox->addWidget(help_);

    about_ = new QPushButton("О программе", this);
    about_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    about_->setCursor(QCursor(Qt::PointingHandCursor));
    about_->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
    about_->setFont(font_for_buttons);
    vbox->addWidget(about_);

    exit_ = new QPushButton("Выход", this);
    exit_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    exit_->setCursor(QCursor(Qt::PointingHandCursor));
    exit_->setStyleSheet("QPushButton {      background-color: rgba(0, 0, 0, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
    exit_->setFont(font_for_buttons);
    vbox->addWidget(exit_);

    connect(exit_, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(help_, &QPushButton::clicked, this, &MainWindow::open_help_window);
    connect(about_, &QPushButton::clicked, this, &MainWindow::open_about_window);
    connect(start_with_rand, &QPushButton::clicked, this, &MainWindow::open_game_window);
    connect(start_with_prep, &QPushButton::clicked, this, &MainWindow::open_prep_window);
    connect(start_with_settings, &QPushButton::clicked, this, &MainWindow::open_constr_window);
    connect(_pass, &QPushButton::clicked, this, &MainWindow::open_password_window);

    this->setMinimumSize(720, 420);
    //this->showMaximized();
}

void MainWindow::mousePressEvent(QMouseEvent *mEvent)
{
    this->view->mapToScene(mEvent->windowPos().x(), mEvent->windowPos().y()).x(), this->view->mapToScene(mEvent->windowPos().x(), mEvent->windowPos().y()).y();
}

void MainWindow::open_help_window() const
{
    help* _help_window = new help();
    _help_window->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
    _help_window->setWindowTitle("Помощь");
    _help_window->setMinimumSize(720, 420);
    _help_window->show();
}

void MainWindow::open_about_window() const
{
    auto dialog_for_about = new about();
    dialog_for_about->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    dialog_for_about->setWindowTitle("О программе");
    dialog_for_about->setMinimumSize(480, 320);
    dialog_for_about->setMaximumSize(480, 320);
    dialog_for_about->setModal(true);
    dialog_for_about->exec();
}

void MainWindow::open_password_window()
{
    if(this->is_password_true)
        return;

    auto password_dialog_ = new password_dialog();
    password_dialog_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    password_dialog_->setWindowTitle("Вход в режим с преподавателем");
    password_dialog_->setMinimumSize(480, 320);
    password_dialog_->setMaximumSize(480, 320);
    password_dialog_->setModal(true);
    password_dialog_->exec();

    if(password_dialog_->is_password_true){
        this->is_password_true = true;
        _pass->setStyleSheet("QPushButton {     background-color: rgba(0, 85, 0, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");

        start_with_prep->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
        start_with_settings->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
    }

}

void MainWindow::open_game_window()
{
    auto change_size_ = new change_size(this);
    change_size_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    change_size_->setWindowTitle("Выберете размер карты");
    change_size_->setMinimumSize(480, 320);
    change_size_->setMaximumSize(480, 320);
    change_size_->is_this_will_be_random_game = true;
    this->close();
    change_size_->setModal(true);
    change_size_->exec();
}

void MainWindow::open_prep_window()
{
    /*if(!this->is_password_true)   //TODO УБРАТЬ КОММЕНТЫ ТУТ, СЕЙЧАС ЭТО ПРОСТО ДЛЯ ОБЛЕГЧЕНИЯ ОТЛАДКИ КОДА
        return;*/

    auto change_size_ = new change_size(this);
    change_size_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    change_size_->setWindowTitle("Выберете размер карты");
    change_size_->setMinimumSize(480, 320);
    change_size_->setMaximumSize(480, 320);
    change_size_->is_this_will_be_prep_game = true;
    this->close();
    change_size_->setModal(true);
    change_size_->exec();
}

void MainWindow::open_constr_window()
{
    /*if(!this->is_password_true)
        return;*/

    auto change_size_ = new change_size();
    change_size_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    change_size_->setWindowTitle("Выберете размер карты");
    change_size_->setMinimumSize(480, 320);
    change_size_->setMaximumSize(480, 320);
    change_size_->is_this_will_be_god_game = true;
    this->close();
    change_size_->setModal(true);
    change_size_->exec();
}
