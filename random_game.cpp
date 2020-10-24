#include "random_game.h"
#include "ui_random_game.h"

randome_game::randome_game(QWidget *parent, int weight, int height) :
    QDialog(parent), weight_of_map(weight), height_of_map(height),
    ui(new Ui::randome_game)
{
    ui->setupUi(this);

    this->gen = new std::mt19937(time(NULL));

    this->_timer = new QTimer();
    this->_timer->setTimerType(Qt::TimerType::CoarseTimer);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));

    QVBoxLayout* hbox = new QVBoxLayout(this);

    this->scene = new QGraphicsScene();
    this->view = new myGraphicsView(scene);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
    this->set_scene_size();
    //this->resize(1280, 720);
    hbox->addWidget(view);

    //allocating memory
    //3th formanta
    this->vec_of_graphik = new vector<pair<float, float>>();
    this->vec_of_graphik->resize(5550); //4islo otshetov na graphike

    this->generate_map();
    this->generate_flukt();
    //this->generate_graphik_perems();
    this->add_hero();
    this->add_zakladka();
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
    std::uniform_int_distribution<> uid(min, max);
    if(min == max)
        return min;
    return uid(*this->gen);
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

    //allocated memory for vec
    this->vec_of_pixmaps.resize(this->height_of_map + 2);
    for(int i = 0; i < this->vec_of_pixmaps.size(); ++i)
        this->vec_of_pixmaps[i].resize(this->weight_of_map + 2);

    //allocated memory for vec
    this->vec_of_fluct.resize(this->height_of_map + 2);
    for(int i = 0; i < this->vec_of_fluct.size(); ++i)
        this->vec_of_fluct[i].resize(this->weight_of_map + 2);


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
    QPixmap* tableH = new QPixmap();
    tableH->load(":/new/random_game_textures/new/random_game_textures/tableH 384x128.jpg");
    QPixmap* divanH = new QPixmap();
    divanH->load(":/new/random_game_textures/new/random_game_textures/divanH 256x128.jpg");

    // TODO TROUBLES WITH PRYAM. KOMNATAMI
    //wall add
    //horizontal walls
    for(int i = 0; i < this->weight_of_map + 2; ++i){
        //verhnie
        Pixmap *item_wall_H = new Pixmap(*wall_H);
        this->vec_of_soderzimoe[0][i] = neprohod_object_;
        this->vec_of_pixmaps[0][i] = item_wall_H;
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
        this->vec_of_pixmaps[i][0] = item_wall_V_left;
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

    //armchairs adding
    for(int i = 0; i < total_armchairs; ++i){
        Pixmap *item_armchair = new Pixmap(*armchair);
        lable_armchair:
        auto sh = this->generate_random_int_number(1, this->weight_of_map - 2);
        auto v = this->generate_random_int_number(1, this->height_of_map - 2);

        if(this->vec_of_soderzimoe[v + 1][sh + 1] == neprohod_object_)
            goto lable_armchair;

        this->vec_of_pixmaps[v + 1][sh + 1] = item_armchair;
        this->vec_of_soderzimoe[v + 1][sh + 1] = neprohod_object_;
        item_armchair->setOffset(-armchair->width()/2, -armchair->height()/2);
        item_armchair->setPos(128. * sh + 192., 192. + 128 * v);
        scene->addItem(item_armchair);
    }

    //tableH adding
    for(int i = 0; i < total_ones_tables; ++i){
        Pixmap *item_tableH = new Pixmap(*tableH);
        label_table:
        auto sh = this->generate_random_int_number(2, this->weight_of_map - 3);
        auto v = this->generate_random_int_number(1, this->height_of_map - 2);
        if((this->vec_of_soderzimoe[v + 1][sh] == neprohod_object_) || (this->vec_of_soderzimoe[v + 1][sh + 2] == neprohod_object_) || (this->vec_of_soderzimoe[v + 1][sh + 1] == neprohod_object_) )
            goto label_table;
        this->vec_of_soderzimoe[v + 1][sh] = neprohod_object_;
        this->vec_of_soderzimoe[v + 1][sh + 2] = neprohod_object_;
        this->vec_of_soderzimoe[v + 1][sh + 1] = neprohod_object_;
        this->vec_of_pixmaps[v + 1][sh] = item_tableH;
        this->vec_of_pixmaps[v + 1][sh + 2] = item_tableH;
        this->vec_of_pixmaps[v + 1][sh + 1] = item_tableH;
        item_tableH->setOffset(-tableH->width()/2, -tableH->height()/2);
        item_tableH->setPos(128. * sh + 192., 192. + 128 * v);
        scene->addItem(item_tableH);
    }
    //divanH adding
    for(int i = 0; i < sofa_count; ++i){
        Pixmap *item_divanH = new Pixmap(*divanH);
        label_divan:
        auto sh = this->generate_random_int_number(1, this->weight_of_map - 3);
        auto v = this->generate_random_int_number(1, this->height_of_map - 2);
        if((this->vec_of_soderzimoe[v + 1][sh + 1] == neprohod_object_) || (this->vec_of_soderzimoe[v + 1][sh + 2] == neprohod_object_))
            goto label_divan;
        this->vec_of_soderzimoe[v + 1][sh + 1] = neprohod_object_;
        this->vec_of_soderzimoe[v + 1][sh + 2] = neprohod_object_;
        this->vec_of_pixmaps[v + 1][sh + 1] = item_divanH;
        this->vec_of_pixmaps[v + 1][sh + 2] = item_divanH;
        item_divanH->setOffset(-divanH->width()/2, -divanH->height()/2);
        item_divanH->setPos(128. * sh + 256., 192. + 128 * v);
        scene->addItem(item_divanH);
    }

    int blyadovka1 = 1;

}

void randome_game::set_scene_size()
{
    scene->setSceneRect(0, 0, 128 * (this->weight_of_map + 2), 128 * (this->height_of_map + 2));
}

void randome_game::add_hero()
{
    //adding hero
    QPixmap* hero = new QPixmap();
    hero->load(":/new/random_game_textures/new/random_game_textures/chair 128x128.jpg");

    this->_hero = new Hero(*hero);
    this->vec_of_soderzimoe[1][1] = GG_;
    this->_hero->coordinate = make_pair(1, 1);
    _hero->setOffset(-hero->width()/2, -hero->height()/2);
    _hero->setPos(192., 192.);
    scene->addItem(_hero);
}

void randome_game::add_zakladka()
{
    lablel_add_zakl:
    int _x = this->generate_random_int_number(0, this->height_of_map + 1);
    int _y = this->generate_random_int_number(0, this->weight_of_map + 1);

    if(this->vec_of_soderzimoe[_x][_y] != neprohod_object_)
        goto lablel_add_zakl;

    this->_coordinate_of_zakladka = make_pair(_x, _y);
    //qDebug() << "zakl coord" << _x << _y;
}

void randome_game::generate_flukt()         //mabe rewrite this     //TODO CHECK GENERATION IN THE WALL
{
    int total_size_of_map = this->weight_of_map * this->height_of_map;     //100 minimum, 6400 maximum
    int mnozitel = total_size_of_map / 100;

    int total_fluct = this->generate_random_int_number(3, 5) * mnozitel;

    for(int i = 0; i < total_fluct; ++i){
        bool bez_nositelya = this->generate_random_int_number(0, 1);
        if(bez_nositelya){
            label_flukt_bez_nositelya:
            auto sh = this->generate_random_int_number(0, this->weight_of_map + 1);
            auto v = this->generate_random_int_number(0, this->height_of_map + 1);
            if(this->vec_of_fluct[v][sh].first != no_fluct_)
                goto label_flukt_bez_nositelya;
            type_of_fluctuation _type_of_fluctuation = static_cast<type_of_fluctuation>(this->generate_random_int_number(4, 9));    //magic numbers
            this->vec_of_fluct[v][sh].first = _type_of_fluctuation;
            this->vec_of_fluct[v][sh].second = this->generate_random_int_number(20, 50);
        }
        else{
            label_flukt_s_nositelem:
            auto sh = this->generate_random_int_number(0, this->weight_of_map + 1);
            auto v = this->generate_random_int_number(0, this->height_of_map + 1);
            if(this->vec_of_fluct[v][sh].first != no_fluct_ || (this->vec_of_soderzimoe[v][sh] == empty_))
                goto label_flukt_s_nositelem;
            type_of_fluctuation _type_of_fluctuation = static_cast<type_of_fluctuation>(this->generate_random_int_number(1, 3));    //magic numbers
            this->vec_of_fluct[v][sh].first = _type_of_fluctuation;
            this->vec_of_fluct[v][sh].second = this->generate_random_int_number(20, 50);
        }
    }
}

void randome_game::generate_graphik_perems()    //TODO test this code
{
    //adding shum
    for(int i = 0; i < this->vec_of_graphik->size(); ++i)
        this->vec_of_graphik->operator[](i) = make_pair(static_cast<float>(i + 450), static_cast<float>(this->generate_random_int_number(8, 15)));

    //
    auto coordinate_of_hero = this->_hero->coordinate;

    vector<pair<pair<int, int>, pair<type_of_fluctuation, float>>> vec_of_visible_fluct;


    switch (this->_hero->_orientation_of_hero) {
    case left_:
        //все ряды влево
        for(int j = 1; j <= 5; ++j)
            for(int i = coordinate_of_hero.first - j; i <= coordinate_of_hero.first + j; ++i)
                if(this->is_coordinate_is_normal(make_pair(i, coordinate_of_hero.second - j)))   //клетка допустима
                    if(this->vec_of_fluct[i][coordinate_of_hero.second - j].first != no_fluct_)  //в клетке флуктуация
                        vec_of_visible_fluct.push_back(make_pair(make_pair(i, coordinate_of_hero.second - j), this->vec_of_fluct[i][coordinate_of_hero.second - j])); //флуктуация сохранена
        break;
    case right_:
        //все ряды вправо
        for(int j = 1; j <= 5; ++j)
            for(int i = coordinate_of_hero.first - j; i <= coordinate_of_hero.first + j; ++i)
                if(this->is_coordinate_is_normal(make_pair(i, coordinate_of_hero.second + j)))   //клетка допустима
                    if(this->vec_of_fluct[i][coordinate_of_hero.second + j].first != no_fluct_)  //в клетке флуктуация
                        vec_of_visible_fluct.push_back(make_pair(make_pair(i, coordinate_of_hero.second + j), this->vec_of_fluct[i][coordinate_of_hero.second + j])); //флуктуация сохранена
        break;
    case up_:
        //все ряды вверх
        for(int j = 1; j <= 5; ++j)
            for(int i = coordinate_of_hero.second - j; i <= coordinate_of_hero.second + j; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first - j, i)))   //клетка допустима
                    if(this->vec_of_fluct[coordinate_of_hero.first - j][i].first != no_fluct_)  //в клетке флуктуация
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first - j, i), this->vec_of_fluct[coordinate_of_hero.first - j][i])); //флуктуация сохранена
        /*
        //это для up
        //на одной высоте с героем
        if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first, coordinate_of_hero.second - 1)))   //клетка допустима
            if(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second - 1].first != no_fluct_)  //в клетке флуктуация
                vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first, coordinate_of_hero.second - 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second - 1].first, this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second - 1].second * 0.5))); //флуктуация сохранена
        if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first, coordinate_of_hero.second + 1)))   //клетка допустима
            if(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].first != no_fluct_)  //в клетке флуктуация
                vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first, coordinate_of_hero.second + 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].first, this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].second * 0.5))); //флуктуация сохранена
        //на высоте +1 под героем
        if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + 1, coordinate_of_hero.second - 1)))   //клетка допустима
            if(this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second - 1].first != no_fluct_)  //в клетке флуктуация
                vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + 1, coordinate_of_hero.second - 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second - 1].first, this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].second * 0.5))); //флуктуация сохранена
        if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + 1, coordinate_of_hero.second)))   //клетка допустима
            if(this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second].first != no_fluct_)  //в клетке флуктуация
                vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first, coordinate_of_hero.second + 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].first, this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].second * 0.5))); //флуктуация сохранена
        if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + 1, coordinate_of_hero.second + 1)))   //клетка допустима
            if(this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second + 1].first != no_fluct_)  //в клетке флуктуация
                vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first, coordinate_of_hero.second + 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].first, this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].second * 0.5))); //флуктуация сохранена
        //на высоте +2 под героем
        if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + 2, coordinate_of_hero.second)))   //клетка допустима
            if(this->vec_of_fluct[coordinate_of_hero.first + 2][coordinate_of_hero.second].first != no_fluct_)  //в клетке флуктуация
                vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first, coordinate_of_hero.second + 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].first, this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].second * 0.5))); //флуктуация сохранена
        */

        break;
    case down_:
        //все ряды вниз
        for(int j = 1; j <= 5; ++j)
            for(int i = coordinate_of_hero.second - j; i <= coordinate_of_hero.second + j; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + j, i)))   //клетка допустима
                    if(this->vec_of_fluct[coordinate_of_hero.first + j][i].first != no_fluct_)  //в клетке флуктуация
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + j, i), this->vec_of_fluct[coordinate_of_hero.first + j][i])); //флуктуация сохранена
        break;
    }

    int b1 = 0;


    //на этом этапе все флуктуации сохранены

    //  todo уменьшение мощности из расстояния
    for(auto obj : vec_of_visible_fluct){
        auto pos_of_flukt_normalized = make_pair(abs(this->_hero->coordinate.first - obj.first.first), abs(this->_hero->coordinate.second - obj.first.second));
        while(pos_of_flukt_normalized.first != 0 || (pos_of_flukt_normalized.second != 0)){
            if(pos_of_flukt_normalized.first > 0 && (pos_of_flukt_normalized.second > 0)){
                pos_of_flukt_normalized = make_pair(pos_of_flukt_normalized.first - 1, pos_of_flukt_normalized.second - 1); //уменьшение мощности на 10% и понижение всех координат на единицу
                obj.second = make_pair(obj.second.first, obj.second.second * 0.9);
            }

            if(pos_of_flukt_normalized.first == 0 && (pos_of_flukt_normalized.second > 0)){
                pos_of_flukt_normalized = make_pair(pos_of_flukt_normalized.first, pos_of_flukt_normalized.second - 1); //уменьшение мощности на 10% и понижение всех координаты на единицу
                obj.second = make_pair(obj.second.first, obj.second.second * 0.9);
            }

            if(pos_of_flukt_normalized.second == 0 && (pos_of_flukt_normalized.first > 0)){
                pos_of_flukt_normalized = make_pair(pos_of_flukt_normalized.first - 1, pos_of_flukt_normalized.second); //уменьшение мощности на 10% и понижение всех координаты на единицу
                obj.second = make_pair(obj.second.first, obj.second.second * 0.9);
            }
        }
    }

    //удаление "Затухших" флуктуаций
    int counter = 0;
    while(counter < vec_of_visible_fluct.size())
        if(vec_of_visible_fluct[counter].second.second < 8)
            vec_of_fluct.erase(vec_of_fluct.begin() + counter);
        else
            ++counter;

    //вставка флуктуаций на график
    for(auto obj : vec_of_visible_fluct){
        auto type_ = obj.second.first;

        float power_of_fluct = obj.second.second;
        //enum type_of_fluctuation{no_fluct_, inactive_semiconductors_, active_semiconductors_, bluetooth_, _5g_, _4g_, _3g_, GPS_, radio_, GLONASS_};
        switch (type_) {
        case inactive_semiconductors_:
            //4800-4990
            this->add_concret_fluct(4800, 190, power_of_fluct);
        break;

        case active_semiconductors_:
            //4800-4990
            this->add_concret_fluct(4800, 190, power_of_fluct);
        break;

        case bluetooth_:
            //4800-4990
            this->add_concret_fluct(4800, 190, power_of_fluct);
        break;

        case _5g_:  //TODO НАПИСАТЬ АНАЛОГИЧНЫЙ КОД ДЛЯ ДРУГИХ ФЛУКТУАЦИЙ
            //4800-4990
            this->add_concret_fluct(4800, 190, power_of_fluct);
        break;

        case _4g_:
            //452-467
            this->add_concret_fluct(452, 15, power_of_fluct);

            //720-791
            this->add_concret_fluct(720, 71, power_of_fluct);

            //2500-2570
            this->add_concret_fluct(2500, 70, power_of_fluct);
        break;

        case _3g_:
            //1920-1980
            this->add_concret_fluct(1920, 60, power_of_fluct);

            //2500-2570
            this->add_concret_fluct(2500, 70, power_of_fluct);
        break;

        case GPS_:
            //4800-4990
            this->add_concret_fluct(4800, 190, power_of_fluct);
        break;

        case radio_:
            //4800-4990
            this->add_concret_fluct(4800, 190, power_of_fluct);
        break;

        case GLONASS_:
            //4800-4990
            this->add_concret_fluct(4800, 190, power_of_fluct);
        break;
        }

    }
}

void randome_game::add_concret_fluct(int start, int length, float power_of_fluct)
{
    for(int i = 0; i < length; ++i){
        bool is_power_wil_be_lower_than_etalon = this->generate_random_int_number(0, 1);
        float power_of_this_ots;
        if(is_power_wil_be_lower_than_etalon)
            power_of_this_ots = power_of_fluct + (this->generate_random_int_number(1, power_of_fluct * 0.1));       //shit
        else
            power_of_this_ots = power_of_fluct + (- this->generate_random_int_number(1, power_of_fluct * 0.1));
        this->vec_of_graphik->operator[](start + i) = make_pair(this->vec_of_graphik->operator[](start + i).first, power_of_this_ots);
    }
}

bool randome_game::is_coordinate_is_normal(pair<int, int> _coordinate) const
{
    if(_coordinate.first < 0 || (_coordinate.second < 0))
        return false;

    if(_coordinate.first > this->height_of_map + 1 || (_coordinate.second > this->height_of_map + 1))
        return false;

    return true;
}

void randome_game::keyPressEvent(QKeyEvent *event)              //TODO ADD diagonal move
{
    if(!this->is_move_possible)
        return;

    _list_of_pushed_buttons.push_back(event->key());        //это для двойных клавиш, но нужны ли они?

    //if(_list_of_pushed_buttons.)

    if(event->key() == Qt::Key_W || event->key() == 0x0426)
         if(this->vec_of_soderzimoe[this->_hero->coordinate.first - 1][this->_hero->coordinate.second] == empty_){
             this->vec_of_soderzimoe[this->_hero->coordinate.first - 1][this->_hero->coordinate.second] = GG_;
             this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second] = empty_;
             this->_hero->coordinate = make_pair(this->_hero->coordinate.first - 1, this->_hero->coordinate.second);
             this->_hero->setPos(this->_hero->pos().x(), this->_hero->pos().y() - 128.);
             //texture swaping
             if(this->_hero->_orientation_of_hero != orientation_of_hero::up_){
                 switch (this->_hero->_orientation_of_hero) {
                 case orientation_of_hero::right_:
                     this->_hero->setRotation(270.);
                     this->_hero->update();
                     break;
                 case orientation_of_hero::down_:
                     this->_hero->setRotation(180.);
                     this->_hero->update();
                     break;
                 case orientation_of_hero::left_:
                     this->_hero->setRotation(90.);
                     this->_hero->update();
                     break;
                 }
             }

             this->_hero->_orientation_of_hero = orientation_of_hero::up_;

             if(this->_pix_chaged_cell != nullptr){
                 this->_pix_chaged_cell->hide();
                 this->_pix_chaged_cell = nullptr;
             }

             this->is_move_possible = false;
             this->_timer->setInterval(250);
             this->_timer->start();
             //Sleep(250);
         }

    if(event->key() == Qt::Key_A || event->key() == 0x0424)
        if(this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second - 1] == empty_){
            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second - 1] = GG_;
            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second] = empty_;
            this->_hero->coordinate = make_pair(this->_hero->coordinate.first, this->_hero->coordinate.second - 1);
            this->_hero->setPos(this->_hero->pos().x() - 128., this->_hero->pos().y());
            //texture swaping
            if(this->_hero->_orientation_of_hero != orientation_of_hero::left_){
                switch (this->_hero->_orientation_of_hero) {
                case orientation_of_hero::right_:
                    this->_hero->setRotation(180.);
                    break;
                case orientation_of_hero::up_:
                    this->_hero->setRotation(270.);
                    break;
                case orientation_of_hero::down_:
                    this->_hero->setRotation(90.);
                    break;
                }
                this->_hero->_orientation_of_hero = orientation_of_hero::left_;
            }

            if(this->_pix_chaged_cell != nullptr){
                this->_pix_chaged_cell->hide();
                this->_pix_chaged_cell = nullptr;
            }

            this->is_move_possible = false;
            this->_timer->setInterval(250);
            this->_timer->start();
        }

    if(event->key() == Qt::Key_S || event->key() == 0x042b)
        if(this->vec_of_soderzimoe[this->_hero->coordinate.first + 1][this->_hero->coordinate.second] == empty_){
            this->vec_of_soderzimoe[this->_hero->coordinate.first + 1][this->_hero->coordinate.second] = GG_;
            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second] = empty_;
            this->_hero->coordinate = make_pair(this->_hero->coordinate.first + 1, this->_hero->coordinate.second);
            this->_hero->setPos(this->_hero->pos().x(), this->_hero->pos().y() + 128.);
            //texture swaping
            if(this->_hero->_orientation_of_hero != orientation_of_hero::down_){
                switch (this->_hero->_orientation_of_hero) {
                case orientation_of_hero::right_:
                    this->_hero->setRotation(90.);
                    break;
                case orientation_of_hero::up_:
                    this->_hero->setRotation(180.);
                    break;
                case orientation_of_hero::left_:
                    this->_hero->setRotation(270);
                    break;
                }
            }
            this->_hero->_orientation_of_hero = orientation_of_hero::down_;

            if(this->_pix_chaged_cell != nullptr){
                this->_pix_chaged_cell->hide();
                this->_pix_chaged_cell = nullptr;
            }

            this->is_move_possible = false;
            this->_timer->setInterval(250);
            this->_timer->start();
        }

    if(event->key() == Qt::Key_D || event->key() == 0x0412)
        if(this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second + 1] == empty_){
            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second + 1] = GG_;
            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second] = empty_;
            this->_hero->coordinate = make_pair(this->_hero->coordinate.first, this->_hero->coordinate.second + 1);
            this->_hero->setPos(this->_hero->pos().x() + 128., this->_hero->pos().y());

            //texture swaping
            if(this->_hero->_orientation_of_hero != orientation_of_hero::right_){
                switch (this->_hero->_orientation_of_hero) {
                case orientation_of_hero::down_:
                    this->_hero->setRotation(270.);      //все в обратную сторону
                    break;
                case orientation_of_hero::up_:
                    this->_hero->setRotation(90.);
                    break;
                case orientation_of_hero::left_:
                    this->_hero->setRotation(180.);
                    break;
                }
               this->_hero->_orientation_of_hero = orientation_of_hero::right_;
            }

            if(this->_pix_chaged_cell != nullptr){
                this->_pix_chaged_cell->hide();
                this->_pix_chaged_cell = nullptr;
            }

            this->is_move_possible = false;
            this->_timer->setInterval(250);
            this->_timer->start();
        }

    if(event->key() == Qt::Key_Return)
        if((this->vec_of_soderzimoe[this->_vibrannaya_kletka.first][this->_vibrannaya_kletka.second] != empty_) &&
                    (this->vec_of_soderzimoe[this->_vibrannaya_kletka.first][this->_vibrannaya_kletka.second] != GG_)){
            if(this->_coordinate_of_zakladka == _vibrannaya_kletka)
                QMessageBox::warning(this, "Поздравляю, вы нашли закладку!", "Поздравляю, вы нашли закладку!");
            else{
                this->col_vo_popytok = this->col_vo_popytok - 1;
                if(col_vo_popytok == 0){
                    QMessageBox::warning(this, "Мимо!", "Вы проиграли!");
                    return;
                }
                QMessageBox::warning(this, "Мимо!", "У вас осталось " + QString::number(this->col_vo_popytok) + " попыток!");
            }
        }

    if(event->key() == Qt::Key_G || event->key() == 0x041f){
        this->generate_graphik_perems();

        auto graphik_window = new graphic_window(&(this->vec_of_soderzimoe), &(this->vec_of_fluct), this->vec_of_graphik, this);
        graphik_window->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
        graphik_window->setWindowTitle("Просмотр графика");
        graphik_window->showMaximized();
        graphik_window->setModal(true);
        //this->close();
        graphik_window->exec();
    }
}

void randome_game::mousePressEvent(QMouseEvent *mEvent)
{
    if(this->_pix_chaged_cell != nullptr){
        this->_pix_chaged_cell->hide();
        this->_pix_chaged_cell = nullptr;
    }

    auto x = mEvent->windowPos().x();
    auto y = mEvent->windowPos().y();
    this->_vibrannaya_kletka = make_pair(this->view->mapToScene(mEvent->windowPos().x(), mEvent->windowPos().y()).x(), this->view->mapToScene(mEvent->windowPos().x(), mEvent->windowPos().y()).y());   //i dont now how it working, but it working!
    this->_vibrannaya_kletka = make_pair(floor(this->_vibrannaya_kletka.second / 128), floor(this->_vibrannaya_kletka.first / 128));

    if(this->vec_of_soderzimoe[this->_vibrannaya_kletka.first][this->_vibrannaya_kletka.second] == empty_ || (this->vec_of_soderzimoe[this->_vibrannaya_kletka.first][this->_vibrannaya_kletka.second] == GG_)){
        this->_vibrannaya_kletka = make_pair(-1, -1);
        return;
    }

    QPixmap* red_square = new QPixmap();
    red_square->load(":/new/random_game_textures/new/random_game_textures/red_square128x128.png");  //загрузка красного квадрата в png

    this->_pix_chaged_cell = new Pixmap(*red_square);
    this->_pix_chaged_cell->setOffset(-red_square->width()/2, -red_square->height()/2);
    this->_pix_chaged_cell->setPos(this->_vibrannaya_kletka.second * 128. + 64., 128. * this->_vibrannaya_kletka.first + 64.);
    scene->addItem(this->_pix_chaged_cell);

}

void randome_game::keyReleaseEvent(QKeyEvent *event)
{
    for(auto i = this->_list_of_pushed_buttons.begin(); i != this->_list_of_pushed_buttons.end(); ++i)
        if(event->key() == *i){
            this->_list_of_pushed_buttons.erase(i);
            return;
        }
}

void randome_game::slotTimerAlarm()
{
    this->is_move_possible = true;
    this->_timer->stop();
}
