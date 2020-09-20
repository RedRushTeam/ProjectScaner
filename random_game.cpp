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

    //******************************************************* generate items on map ********************************************************

    //downloading textures
    QPixmap* wall_H = new QPixmap();
    wall_H->load(":/new/random_game_textures/Bricks_H.jpg");
    QPixmap* wall_V = new QPixmap();
    wall_V->load(":/new/random_game_textures/Bricks_V.jpg");
    QPixmap* floor = new QPixmap();
    floor->load(":/new/random_game_textures/228.1.jpg");
    // TODO ADD TEXTURES
    QPixmap* armchair = new QPixmap();
    armchair->load(":/new/random_game_textures/new/random_game_textures/chair 128x128.jpg");

    // TODO TROUBLES WITH PRYAM. KOMNATAMI
    //wall add
    //horizontal walls
    for(int i = 0; i < this->weight_of_map + 2; ++i){
        //verhnie
        Pixmap *item_wall_H = new Pixmap(*wall_H);
        this->vec_of_soderzimoe[0][i] = neprohod_object_;
        item_wall_H->setOffset(-wall_H->width()/2, -wall_H->height()/2);
        item_wall_H->setPos(64. + 128 * (i), 64.);
        scene->addItem(item_wall_H);

        //niznie
        Pixmap *item_wall_H_low = new Pixmap(*wall_H);                          //done
        this->vec_of_soderzimoe[this->height_of_map + 1][i] = neprohod_object_;
        item_wall_H_low->setOffset(-wall_H->width()/2, -wall_H->height()/2);
        item_wall_H_low->setPos(64. + 128 * (i), 128. * (this->weight_of_map + 2) - 64.);
        scene->addItem(item_wall_H_low);
    }

    //vertical walls
    for(int i = 0; i < this->height_of_map + 2; ++i){
        //levie
        Pixmap *item_wall_V_left = new Pixmap(*wall_V);                          //done
        this->vec_of_soderzimoe[i][0] = neprohod_object_;
        item_wall_V_left->setOffset(-wall_V->width()/2, -wall_V->height()/2);
        item_wall_V_left->setPos(64., 64. + 128 * (i));  //it's ok
        scene->addItem(item_wall_V_left);

        //pravie
        Pixmap *item_wall_V_right = new Pixmap(*wall_V);                          //done
        this->vec_of_soderzimoe[i][this->weight_of_map + 1] = neprohod_object_;
        item_wall_V_right->setOffset(-wall_V->width()/2, -wall_V->height()/2);
        item_wall_V_right->setPos(128. * (this->weight_of_map + 2) - 64., 64. + 128 * (i));
        scene->addItem(item_wall_V_right);
    }

    //floor
    for(int i = 1; i < this->height_of_map + 1; ++i)
        for(int j = 1; j < this->weight_of_map + 1; ++j){
            Pixmap *item_floor = new Pixmap(*floor);
            item_floor->setOffset(-floor->width()/2, -floor->height()/2);
            item_floor->setPos(128. * (j) + 64., 64. + 128 * (i));
            scene->addItem(item_floor);
        }

    //cycling check

    //armchairs adding                              ////////////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < total_armchairs; ++i){
        Pixmap *item_armchair = new Pixmap(*armchair);
        auto sh = this->generate_random_int_number(0, this->weight_of_map - 2);
        auto v = this->generate_random_int_number(0, this->height_of_map - 2);
        this->vec_of_soderzimoe[v + 2][sh + 2] = neprohod_object_;
        item_armchair->setOffset(-armchair->width()/2, -armchair->height()/2);
        item_armchair->setPos(128. * sh + 320., 320. + 128 * v);
        scene->addItem(item_armchair);
    }

    int blyadovka1 = 1;

}

bool randome_game::check_cycle(pair<int, int> coord) const
{
    //proverka sosedey
    if(this->vec_of_soderzimoe[coord.first][coord.second] != empty_)
        return false;
    pair<int, int> focuse = coord;
    pair<int, int> previouse_focuse = coord;
    vector<pair<int, int>> vec_of_needed_roads;
    bool end_of_finding = true;

    while(end_of_finding){
        if(this->vec_of_soderzimoe[focuse.first + 1][focuse.second] != empty_ && (previouse_focuse != make_pair(focuse.first + 1, focuse.second)))
            vec_of_needed_roads.push_back(make_pair(focuse.first + 1, focuse.second));
        if(this->vec_of_soderzimoe[focuse.first + 1][focuse.second + 1] != empty_ && (previouse_focuse != make_pair(focuse.first + 1, focuse.second + 1)))
            vec_of_needed_roads.push_back(make_pair(focuse.first + 1, focuse.second + 1));
        if(this->vec_of_soderzimoe[focuse.first][focuse.second + 1] != empty_ && (previouse_focuse != make_pair(focuse.first, focuse.second + 1)))
            vec_of_needed_roads.push_back(make_pair(focuse.first, focuse.second + 1));
        if(this->vec_of_soderzimoe[focuse.first - 1][focuse.second] != empty_ && (previouse_focuse != make_pair(focuse.first - 1, focuse.second)))
            vec_of_needed_roads.push_back(make_pair(focuse.first - 1, focuse.second));
        if(this->vec_of_soderzimoe[focuse.first - 1][focuse.second - 1] != empty_ && (previouse_focuse != make_pair(focuse.first - 1, focuse.second - 1)))
            vec_of_needed_roads.push_back(make_pair(focuse.first - 1, focuse.second - 1));
        if(this->vec_of_soderzimoe[focuse.first][focuse.second - 1] != empty_ && (previouse_focuse != make_pair(focuse.first, focuse.second - 1)))
            vec_of_needed_roads.push_back(make_pair(focuse.first, focuse.second - 1));
        if(this->vec_of_soderzimoe[focuse.first + 1][focuse.second - 1] != empty_ && (previouse_focuse != make_pair(focuse.first + 1, focuse.second - 1)))
            vec_of_needed_roads.push_back(make_pair(focuse.first + 1, focuse.second - 1));
        if(this->vec_of_soderzimoe[focuse.first - 1][focuse.second + 1] != empty_ && (previouse_focuse != make_pair(focuse.first - 1, focuse.second + 1)))
            vec_of_needed_roads.push_back(make_pair(focuse.first - 1, focuse.second + 1));

        if(vec_of_needed_roads.empty())
            return true;

        previouse_focuse = focuse;
        focuse = vec_of_needed_roads.front();

        vec_of_needed_roads.pop_back();

        if(focuse == coord)
            return false;

        //
        //  xx    <-  need to add checking this situation
        //  xx
        //
    }

    //kostil'
    return true;

}

void randome_game::set_scene_size()
{
    scene->setSceneRect(0, 0, 128 * (this->weight_of_map + 2), 128 * (this->height_of_map + 2));
}


