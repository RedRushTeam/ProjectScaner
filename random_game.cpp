#include "random_game.h"
#include "ui_random_game.h"

randome_game::randome_game(QWidget *parent, int weight, int height) :
    QDialog(parent), weight_of_map(weight), height_of_map(height),
    ui(new Ui::randome_game)
{
    ui->setupUi(this);

    QVBoxLayout* hbox = new QVBoxLayout(this);

    this->scene = new QGraphicsScene(/*0, 0, 1280, 720*/);
    this->view = new QGraphicsView(scene);
    view->show();
    this->set_scene_size();
    //this->resize(1280, 720);
    hbox->addWidget(view);

    this->generate_map();
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
    //scene->setSceneRect(this->geometry());
}

int randome_game::generate_random_int_number(int min, int max) const
{
    std::mt19937 gen(time(NULL));
    std::uniform_int_distribution<> uid(min, max);
    if(min == max)
        return min;
    return uid(gen);
}

void randome_game::generate_map()
{
    int total_size_of_map = this->weight_of_map * this->height_of_map;     //100 minimum, 6400 maximum

    int mnozitel = total_size_of_map / 100;

    //count of items generations
    int total_armchairs = this->generate_random_int_number(1, 2) * mnozitel;
    int total_ones_tables = this->generate_random_int_number(1, 2) * mnozitel;
    int one_shair_tables = this->generate_random_int_number(1, 2) * mnozitel;
    int two_chairs_tables = this->generate_random_int_number(0, 1) * mnozitel;
    int sofa_count = this->generate_random_int_number(0, 1) * mnozitel;

    //allocated memory for vec
    this->vec_of_soderzimoe.resize(this->height_of_map + 2);

    for(int i = 0; i < this->vec_of_soderzimoe.size(); ++i)
        this->vec_of_soderzimoe[i].resize(this->weight_of_map + 2);

    //generate items with map

    //downloading textures
    QPixmap* wall_H = new QPixmap();
    wall_H->load(":/new/random_game_textures/Bricks_H.jpg");


    //wall add
    //horizontal walls
    for(int i = 0; i < this->weight_of_map + 2; ++i){
        Pixmap *item_wall_H = new Pixmap(*wall_H);
        this->vec_of_soderzimoe[0][i] = neprohod_object_;
        this->vec_of_soderzimoe[this->height_of_map + 1][i] = neprohod_object_;
        item_wall_H->setOffset(-wall_H->width()/2, -wall_H->height()/2);
        item_wall_H->setPos(64. + 128 * (i), 64.);  //shit
        scene->addItem(item_wall_H);
    }


    //cycling check


}

void randome_game::set_scene_size()
{
    scene->setSceneRect(0, 0, 128 * this->weight_of_map + 2, 128 * this->height_of_map + 2);
}
