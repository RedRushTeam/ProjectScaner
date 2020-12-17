#include "change_size.h"
#include "ui_change_size.h"

change_size::change_size(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_size)
{
    ui->setupUi(this);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout();

    vbox->setContentsMargins(50, 5, 50, 50);
    vbox->setSpacing(15);

    QFont font_for_buttons("Times new roman", 14, QFont::Bold);
    QFont font_for_label("Times new roman", 18, QFont::ExtraBold);

    QLabel *title = new QLabel("Выберете размер карты", this);
    title->setFont(font_for_buttons);
    title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    vbox->addWidget(title);

    high = new QLineEdit();
    high->setFont(font_for_label);
    high->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    high->setValidator(new QIntValidator(10, 80, this));
    high->setStyleSheet("QLineEdit {    border: 2px solid gray;    border-radius: 10px;    padding: 0 8px;    background:  rgba(255, 255, 0, 120);    selection-background-color: rgba(255, 255, 0, 120);    }");
    high->setFont(font_for_label);
    high->setText("10");
    hbox->addWidget(high);

    weight = new QLineEdit();
    weight->setFont(font_for_label);
    weight->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    weight->setValidator(new QIntValidator(10, 80, this));
    weight->setStyleSheet("QLineEdit {    border: 2px solid gray;    border-radius: 10px;    padding: 0 8px;    background:  rgba(255, 255, 0, 120);    selection-background-color: rgba(255, 255, 0, 120);    }");
    weight->setFont(font_for_label);
    weight->setText("10");
    hbox->addWidget(weight);

    vbox->addLayout(hbox);

    QPushButton *OK = new QPushButton("ОК", this);
    OK->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    OK->setCursor(QCursor(Qt::PointingHandCursor));
    OK->setFont(font_for_buttons);
    vbox->addWidget(OK);

    connect(OK, &QPushButton::clicked, this, &change_size::OK_clicked);
}

change_size::~change_size()
{
    delete ui;
}

void change_size::closeEvent(QCloseEvent *event)
{
    event->accept();
    this->parentWidget()->show();   //done
}

void change_size::OK_clicked()
{
    //OK clicked        TODO

    if(this->high->text().toInt() > 80 || (this->high->text().toInt() < 10))
        this->high->setText("10");

    if(this->weight->text().toInt() > 80 || (this->weight->text().toInt() < 10))
        this->weight->setText("10");


    //w.showMaximized();
    if(this->is_this_will_be_random_game){
        auto* randome_game_ = new randome_game(this, this->weight->text().toInt(), this->high->text().toInt());
        randome_game_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
        randome_game_->setWindowTitle("Случайная игра");
        randome_game_->showMaximized();
        randome_game_->setModal(true);
        this->close();
        randome_game_->exec();
    }

    if(this->is_this_will_be_prep_game){
        auto* prepod_game_ = new prepod_game(this, this->weight->text().toInt(), this->high->text().toInt());
        prepod_game_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
        prepod_game_->setWindowTitle("Игра с преподавателем");
        prepod_game_->showMaximized();
        prepod_game_->setModal(true);
        this->close();
        prepod_game_->exec();
    }

    if(this->is_this_will_be_god_game){
        auto* god_game_ = new nastr_game(this, this->weight->text().toInt(), this->high->text().toInt());
        god_game_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
        god_game_->setWindowTitle("Настраиваемая игра");
        god_game_->showMaximized();
        god_game_->setModal(true);
        this->close();
        god_game_->exec();
    }
}
