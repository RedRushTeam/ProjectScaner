#include "random_game.h"
#include "ui_random_game.h"

randome_game::randome_game(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::randome_game)
{
    ui->setupUi(this);

    QVBoxLayout* hbox = new QVBoxLayout(this);

    this->scene = new QGraphicsScene();
    this->view = new QGraphicsView(scene);

    scene->setSceneRect(this->geometry());

    hbox->addWidget(view);

    //QPointF pos(0., 0.);


    QPixmap pix("qrc:/new/random_game_textures/Bricks_H.jpg");

    //scene->addPixmap(pix);
}

randome_game::~randome_game()
{
    delete ui;
}

void randome_game::closeEvent(QCloseEvent *event)
{
    event->accept();
    this->parentWidget()->parentWidget()->show();   //done
}

void randome_game::resizeEvent(QResizeEvent *event)
{
    event->accept();
    //auto sheet = this->geometry();              //TODO ne na vse okno seychas, no po4ti
    scene->setSceneRect(this->geometry());
}
