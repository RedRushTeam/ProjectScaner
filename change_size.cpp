#include "change_size.h"
#include "ui_change_size.h"

change_size::change_size(QWidget *parent) : QDialog(parent)
{

    this->setStyleSheet("background-color: lightGray;");

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout();

    hbox->setAlignment(Qt::AlignHCenter);

    hbox->setSpacing(10);
    hbox->setContentsMargins(10, 10, 10, 10);
    vbox->setContentsMargins(50, 150, 50, 150);
    vbox->setSpacing(40);

    QFont font_for_buttons("Times new roman", 28, QFont::Bold);
    QFont font_for_label("Times new roman", 28, QFont::ExtraBold);

    QLabel *title = new QLabel("Выберете размер карты", this);
    title->setMaximumSize(1600, 160);
    title->setMinimumSize(800, 80);
    title->setFont(font_for_buttons);
    title->setScaledContents(true);
    QPixmap* title_pixmap = new QPixmap();
    title_pixmap->load(":/new/random_game_textures/new/random_game_textures/yakarta.png");  //загрузка красного квадрата в png
    title->setPixmap(*title_pixmap);
    //title->resize(title_pixmap->size());
    title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    vbox->addWidget(title, 0, Qt::AlignHCenter | Qt::AlignVCenter);


    high = new QLineEdit();
    high->setFont(font_for_label);
    high->setMaximumSize(380, 180);
    high->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    high->setValidator(new QIntValidator(10, 40, this));
    high->setStyleSheet("QLineEdit {    border: 2px solid gray;    border-radius: 10px;    padding: 0 8px;    background:  rgba(255, 255, 0, 120);    selection-background-color: rgba(255, 255, 0, 120);    }");
    high->setFont(font_for_label);
    //high->setAlignment(Qt::AlignLeft);
    high->setText("10");
    hbox->addWidget(high, Qt::AlignHCenter);

    weight = new QLineEdit();
    weight->setFont(font_for_label);
    weight->setMaximumSize(380, 180);
    weight->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    weight->setValidator(new QIntValidator(10, 40, this));
    weight->setStyleSheet("QLineEdit {    border: 2px solid gray;    border-radius: 10px;    padding: 0 8px;    background:  rgba(255, 255, 0, 120);    selection-background-color: rgba(255, 255, 0, 120);    }");
    weight->setFont(font_for_label);
    //weight->setAlignment(Qt::AlignLeft);
    weight->setText("10");
    hbox->addWidget(weight, Qt::AlignHCenter);

    vbox->addLayout(hbox);

    QPushButton *OK = new QPushButton("ОК", this);
    OK->setMinimumSize(500, 180);
    OK->setMaximumSize(600, 240);
    OK->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    OK->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 26px;     padding: 6px}");
    OK->setCursor(QCursor(Qt::PointingHandCursor));
    OK->setFont(font_for_buttons);
    vbox->addWidget(OK, 2, Qt::AlignHCenter);

    connect(OK, &QPushButton::clicked, this, &change_size::OK_clicked);
}

change_size::~change_size()
{
}

void change_size::closeEvent(QCloseEvent *event)
{
    event->accept();
    this->parentWidget()->show();   //done
}

void change_size::OK_clicked()
{
    //OK clicked        TODO

    if(this->high->text().toInt() > 30 || (this->high->text().toInt() < 10))
        this->high->setText("10");

    if(this->weight->text().toInt() > 30 || (this->weight->text().toInt() < 10))
        this->weight->setText("10");

    if(this->weight->text().toInt() != this->high->text().toInt()){
        QMessageBox::warning(this, "Повторите ввод!", "В текущем режиме размер карты может быть лишь квадратным!");
        return;
    }


    //w.showMaximized();
    if(this->is_this_will_be_random_game){
        auto* randome_game_ = new randome_game(this, this->weight->text().toInt(), this->high->text().toInt());
        randome_game_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
        randome_game_->setWindowTitle("Случайная игра");
        randome_game_->showFullScreen();
        //randome_game_->showMaximized();
        randome_game_->setModal(true);
        this->close();
        randome_game_->exec();
    }

    if(this->is_this_will_be_prep_game){
        auto* prepod_game_ = new prepod_game(this, this->weight->text().toInt(), this->high->text().toInt());
        prepod_game_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
        prepod_game_->setWindowTitle("Игра с преподавателем");
        //prepod_game_->showMaximized();
        prepod_game_->showFullScreen();
        prepod_game_->setModal(true);
        this->close();
        prepod_game_->exec();
    }

    if(this->is_this_will_be_god_game){
        auto* god_game_ = new nastr_game(this, this->weight->text().toInt(), this->high->text().toInt());
        god_game_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
        god_game_->setWindowTitle("Настраиваемая игра");
        god_game_->showFullScreen();
        //god_game_->showMaximized();
        god_game_->setModal(true);
        this->close();
        god_game_->exec();
    }
}

void change_size::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
        this->close();

    if(event->key() == Qt::Key_Return){
        this->OK_clicked();
    }
}
