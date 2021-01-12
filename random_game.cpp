#include "random_game.h"
#include "ui_random_game.h"

randome_game::randome_game(QWidget *parent, int weight, int height) :
    QDialog(parent), weight_of_map(weight), height_of_map(height),
    ui(new Ui::randome_game)
{
    ui->setupUi(this);

    this->setStyleSheet("background-color: lightGray;");

    this->gen = new std::mt19937(time(NULL));

    this->_timer = new QTimer();
    this->_timer->setTimerType(Qt::TimerType::CoarseTimer);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));

    this->_timer_stop_animation = new QTimer();
    this->_timer_stop_animation->setTimerType(Qt::TimerType::PreciseTimer);
    this->_timer_stop_animation->setInterval(256);
    this->_timer_stop_animation->stop();
    connect(_timer_stop_animation, SIGNAL(timeout()), this, SLOT(slotTimerStopAnimationAlarm()));

    this->_timer_for_change_position = new QTimer();
    this->_timer_for_change_position->setTimerType(Qt::TimerType::PreciseTimer);
    this->_timer_for_change_position->setInterval(8);
    this->_timer_for_change_position->stop();
    connect(_timer_for_change_position, SIGNAL(timeout()), this, SLOT(slotTimerChangePositionAlarm()));

    this->hbox = new QVBoxLayout(this);

    this->scene = new QGraphicsScene();
    this->view = new myGraphicsView(scene);

    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();
    this->set_scene_size();
    //this->resize(1280, 720);
    hbox->addWidget(view);

    //allocating memory
    //2th formanta
    this->vec_of_graphik_of_second_formanta = new vector<pair<float, float>>();
    this->vec_of_graphik_of_second_formanta->resize(5550); //4islo otshetov na graphike

    //3th_formanta
    //this->vec_of_graphik_of_trird_formanta = new vector<pair<float, float>>();
    //this->vec_of_graphik_of_trird_formanta->resize(5550); //4islo otshetov na graphike

    this->generate_map();
    this->add_hero();
    this->add_zakladka();
    this->generate_flukt();
    //this->generate_graphik_perems();
}

randome_game::~randome_game()
{
    delete ui;
}

void randome_game::closeEvent(QCloseEvent *event)
{
    event->accept();
    //this->parentWidget()->parentWidget()->show();   //done
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
    int three_shair_tables = this->generate_random_int_number(0, 1) * mnozitel;
    int two_chairs_tables = this->generate_random_int_number(1, 2) * mnozitel;
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
    armchair->load(":/new/random_game_textures/new/random_game_textures/wood_chair_128x128.png");
    QPixmap* tableH = new QPixmap();
    tableH->load(":/new/random_game_textures/new/random_game_textures/tableH 384x128.jpg");
    QPixmap* tablePro = new QPixmap();
    tablePro->load(":/new/random_game_textures/new/random_game_textures/table_pro_128x256.png");
    QPixmap* divanH = new QPixmap();
    divanH->load(":/new/random_game_textures/new/random_game_textures/divanH 256x128.jpg");
    QPixmap* divanLarge = new QPixmap();
    divanLarge->load(":/new/random_game_textures/new/random_game_textures/divan_128x384.png");
    QPixmap* whiteChair = new QPixmap();
    whiteChair->load(":/new/random_game_textures/new/random_game_textures/white_chair_128x128.png");

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

    //two_chairs_tables adding
    for(int i = 0; i < two_chairs_tables; ++i){
        Pixmap *pro_table = new Pixmap(*tablePro);
        Pixmap *white_chair = new Pixmap(*whiteChair);
        Pixmap *armchair_ = new Pixmap(*armchair);
        lable_two_chairs_tables:
        auto sh = this->generate_random_int_number(1, this->weight_of_map - 3);
        auto v = this->generate_random_int_number(1, this->height_of_map - 2);
        if((this->vec_of_soderzimoe[v + 1][sh + 1] == neprohod_object_) || (this->vec_of_soderzimoe[v + 1][sh + 2] == neprohod_object_))
            goto lable_two_chairs_tables;
        if((this->vec_of_soderzimoe[v + 2][sh + 1] == neprohod_object_) || (this->vec_of_soderzimoe[v + 2][sh + 2] == neprohod_object_))        ////    * * *
            goto lable_two_chairs_tables;                                                                                                       ////    * * *
        if((this->vec_of_soderzimoe[v + 3][sh + 1] == neprohod_object_) || (this->vec_of_soderzimoe[v + 3][sh + 2] == neprohod_object_))        ////    * * *
            goto lable_two_chairs_tables;

        this->vec_of_soderzimoe[v + 1][sh + 1] = neprohod_object_;  //кресло сверху
        this->vec_of_soderzimoe[v + 2][sh + 1] = neprohod_object_;  //стол
        this->vec_of_soderzimoe[v + 2][sh + 2] = neprohod_object_;  //стол
        this->vec_of_soderzimoe[v + 3][sh + 1] = neprohod_object_;  //кресло снизу

        this->vec_of_pixmaps[v + 1][sh + 1] = white_chair;
        this->vec_of_pixmaps[v + 2][sh + 1] = pro_table;
        this->vec_of_pixmaps[v + 2][sh + 2] = pro_table;
        this->vec_of_pixmaps[v + 3][sh + 1] = armchair_;

        //ставим верхний стул
        white_chair->setOffset(-whiteChair->width()/2, -whiteChair->height()/2);
        white_chair->setPos(128. * sh + 192., 192. + 128 * v);
        scene->addItem(white_chair);

        //ставим нижний стул
        armchair_->setOffset(-armchair->width()/2, -armchair->height()/2);
        armchair_->setPos(128. * sh + 192., 192. + 128 * v + 256.);   //
        armchair_->setRotation(180.);
        scene->addItem(armchair_);

        //ставим стол
        pro_table->setOffset(-tablePro->width()/2, -tablePro->height()/2);
        pro_table->setPos(128. * sh + 256., 192. + 128 * v + 128.);
        scene->addItem(pro_table);
    }

    //three_shair_tables adding
    for(int i = 0; i < three_shair_tables; ++i){
        Pixmap *pro_table = new Pixmap(*tablePro);
        Pixmap *white_chair = new Pixmap(*whiteChair);
        Pixmap *armchair_ = new Pixmap(*armchair);
        Pixmap *armchair_two = new Pixmap(*armchair);
        lable_three_shair_tables:
        auto sh = this->generate_random_int_number(1, this->weight_of_map - 3);
        auto v = this->generate_random_int_number(1, this->height_of_map - 2);

        if((this->vec_of_soderzimoe[v + 1][sh + 1] == neprohod_object_) || (this->vec_of_soderzimoe[v + 1][sh + 2] == neprohod_object_))
            goto lable_three_shair_tables;
        if((this->vec_of_soderzimoe[v + 2][sh + 1] == neprohod_object_) || (this->vec_of_soderzimoe[v + 2][sh + 2] == neprohod_object_))        ////    * * *
            goto lable_three_shair_tables;                                                                                                      ////    * * *
        if((this->vec_of_soderzimoe[v + 3][sh + 1] == neprohod_object_) || (this->vec_of_soderzimoe[v + 3][sh + 2] == neprohod_object_))        ////    * * *
            goto lable_three_shair_tables;

        this->vec_of_soderzimoe[v + 1][sh + 1] = neprohod_object_;  //кресло сверху
        this->vec_of_soderzimoe[v + 2][sh + 1] = neprohod_object_;  //стол
        this->vec_of_soderzimoe[v + 2][sh + 2] = neprohod_object_;  //стол
        this->vec_of_soderzimoe[v + 3][sh + 1] = neprohod_object_;  //кресло снизу
        this->vec_of_soderzimoe[v + 3][sh + 2] = neprohod_object_;  //кресло 2 снизу

        this->vec_of_pixmaps[v + 1][sh + 1] = white_chair;
        this->vec_of_pixmaps[v + 2][sh + 1] = pro_table;
        this->vec_of_pixmaps[v + 2][sh + 2] = pro_table;
        this->vec_of_pixmaps[v + 3][sh + 1] = armchair_;
        this->vec_of_pixmaps[v + 3][sh + 2] = armchair_two;

        //ставим верхний стул
        white_chair->setOffset(-whiteChair->width()/2, -whiteChair->height()/2);
        white_chair->setPos(128. * sh + 192., 192. + 128 * v);
        scene->addItem(white_chair);

        //ставим нижний стул
        armchair_->setOffset(-armchair->width()/2, -armchair->height()/2);
        armchair_->setPos(128. * sh + 192., 192. + 128 * v + 256.);
        armchair_->setRotation(180.);
        scene->addItem(armchair_);

        //ставим второй нижний стул
        armchair_two->setOffset(-armchair->width()/2, -armchair->height()/2);
        armchair_two->setPos(128. * sh + 192. + 128., 192. + 128 * v + 256.);
        armchair_two->setRotation(180.);
        scene->addItem(armchair_two);

        //ставим стол
        pro_table->setOffset(-tablePro->width()/2, -tablePro->height()/2);
        pro_table->setPos(128. * sh + 256., 192. + 128 * v + 128.);
        scene->addItem(pro_table);
    }
}

void randome_game::set_scene_size()
{
    scene->setSceneRect(0, 0, 128 * (this->weight_of_map + 2), 128 * (this->height_of_map + 2));
}

void randome_game::add_hero()
{
    //adding hero
    QPixmap* hero = new QPixmap();
    hero->load(":/new/random_game_textures/new/random_game_textures/Animation.gif");

    this->_hero = new Hero(*hero);
    this->vec_of_soderzimoe[1][1] = GG_;
    this->_hero->coordinate = make_pair(1, 1);
    _hero->setOffset(-hero->width()/2, -hero->height()/2);
    _hero->setPos(192., 192.);
    scene->addItem(_hero);
}

void randome_game::add_zakladka()
{
    this->start = this->generate_random_int_number(0, 15) * 25 + 800;

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
    //enum type_of_fluctuation{no_fluct_, inactive_semiconductors_, active_semiconductors_, bluetooth_, _5g_, _4g_, _3g_, GPS_, radio_, GLONASS_};
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
            if(_type_of_fluctuation == active_semiconductors_)
                goto label_flukt_s_nositelem;
            this->vec_of_fluct[v][sh].first = _type_of_fluctuation;
            this->vec_of_fluct[v][sh].second = this->generate_random_int_number(20, 50);
        }
    }
    //добавление закладки в список флуктуаций
    this->vec_of_fluct[this->_coordinate_of_zakladka.first][this->_coordinate_of_zakladka.second].first = active_semiconductors_;
    this->vec_of_fluct[this->_coordinate_of_zakladka.first][this->_coordinate_of_zakladka.second].second = this->generate_random_int_number(40, 60);
}

void randome_game::generate_graphik_perems()
{
    //adding shum
    for(int i = 0; i < this->vec_of_graphik_of_second_formanta->size(); ++i)
        this->vec_of_graphik_of_second_formanta->operator[](i) = make_pair(static_cast<float>(i + 450), static_cast<float>(this->generate_random_int_number(8, 15)));

    auto coordinate_of_hero = this->_hero->coordinate;

    vector<pair<pair<int, int>, pair<type_of_fluctuation, float>>> vec_of_visible_fluct;


    // TODO rewrite this
    switch (this->_hero->_orientation_of_hero) {
    case left_:        //все ряды влево

        //единственная клетка
        if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first, coordinate_of_hero.second - 1)))   //клетка допустима
            if(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second - 1].first != no_fluct_){  //в клетке флуктуация
                float now_pwr = this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second - 1].second;
                now_pwr = now_pwr * 0.95;
                vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first, coordinate_of_hero.second - 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second - 1].first, now_pwr))); //флуктуация сохранена
            }

        //прямоугольник **
        //              **
        //              **
        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first - 1, coordinate_of_hero.second + (i - 1) - 1)))   //клетка допустима      FF
                    if(this->vec_of_fluct[coordinate_of_hero.first - 1][coordinate_of_hero.second + (i - 1) - 1].first != no_fluct_){  //в клетке флуктуация  **
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first - 1][coordinate_of_hero.second + (i - 1) - 1].second;//                   **
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first - 1, coordinate_of_hero.second + (i - 1) - 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first - 1][coordinate_of_hero.second + (i - 1) - 1].first, now_pwr))); //флуктуация сохранена
                    }

        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first, coordinate_of_hero.second + (i - 1) - 1)))   //клетка допустима      **
                    if(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + (i - 1) - 1].first != no_fluct_){  //в клетке флуктуация  FF
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + (i - 1) - 1].second;//                   **
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first, coordinate_of_hero.second + (i - 1) - 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + (i - 1) - 1].first, now_pwr))); //флуктуация сохранена
                    }

        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + 1, coordinate_of_hero.second + (i - 1) - 1)))   //клетка допустима      **
                    if(this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second + (i - 1) - 1].first != no_fluct_){  //в клетке флуктуация  **
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second + (i - 1) - 1].second;//                   FF
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + 1, coordinate_of_hero.second + (i - 1) - 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second + (i - 1) - 1].first, now_pwr))); //флуктуация сохранена
                    }

        //полоска 5х1
        for(int i = 0; i < 5; ++i)
            if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + (i - 2), coordinate_of_hero.second - 4)))   //клетка допустима
                if(this->vec_of_fluct[coordinate_of_hero.first + (i - 2)][coordinate_of_hero.second - 4].first != no_fluct_){  //в клетке флуктуация
                    float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + (i - 2)][coordinate_of_hero.second - 4].second;
                    for(int k = 0; k > 4; ++k)
                        now_pwr = now_pwr * 0.95;
                    vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + (i - 2), coordinate_of_hero.second - 4), make_pair(this->vec_of_fluct[coordinate_of_hero.first + (i - 2)][coordinate_of_hero.second - 4].first, now_pwr))); //флуктуация сохранена
                }
        break;
    case right_:
        //все ряды вправо
        //единственная клетка
        if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first, coordinate_of_hero.second + 1)))   //клетка допустима
            if(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].first != no_fluct_){  //в клетке флуктуация
                float now_pwr = this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].second;
                now_pwr = now_pwr * 0.95;
                vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first, coordinate_of_hero.second + 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + 1].first, now_pwr))); //флуктуация сохранена
            }

        //прямоугольник **
        //              **
        //              **
        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first - 1, coordinate_of_hero.second + (i + 1) + 1)))   //клетка допустима      FF
                    if(this->vec_of_fluct[coordinate_of_hero.first - 1][coordinate_of_hero.second + (i + 1) + 1].first != no_fluct_){  //в клетке флуктуация  **
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first - 1][coordinate_of_hero.second + (i + 1) + 1].second;//                   **
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first - 1, coordinate_of_hero.second + (i + 1) + 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first - 1][coordinate_of_hero.second + (i + 1) + 1].first, now_pwr))); //флуктуация сохранена
                    }

        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first, coordinate_of_hero.second + (i + 1) + 1)))   //клетка допустима      **
                    if(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + (i + 1) + 1].first != no_fluct_){  //в клетке флуктуация  FF
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + (i + 1) + 1].second;//                   **
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first, coordinate_of_hero.second + (i + 1) + 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first][coordinate_of_hero.second + (i + 1) + 1].first, now_pwr))); //флуктуация сохранена
                    }

        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + 1, coordinate_of_hero.second + (i + 1) + 1)))   //клетка допустима      **
                    if(this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second + (i + 1) + 1].first != no_fluct_){  //в клетке флуктуация  **
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second + (i + 1) + 1].second;//                   FF
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + 1, coordinate_of_hero.second + (i + 1) + 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second + (i + 1) + 1].first, now_pwr))); //флуктуация сохранена
                    }

        //полоска 5х1
        for(int i = 0; i < 5; ++i)
            if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + (i - 2), coordinate_of_hero.second + 4)))   //клетка допустима
                if(this->vec_of_fluct[coordinate_of_hero.first + (i - 2)][coordinate_of_hero.second + 4].first != no_fluct_){  //в клетке флуктуация
                    float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + (i - 2)][coordinate_of_hero.second + 4].second;
                    for(int k = 0; k > 4; ++k)
                        now_pwr = now_pwr * 0.95;
                    vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + (i - 2), coordinate_of_hero.second + 4), make_pair(this->vec_of_fluct[coordinate_of_hero.first + (i - 2)][coordinate_of_hero.second + 4].first, now_pwr))); //флуктуация сохранена
                }
        break;
    case up_:
        //все ряды вверх
        //единственная клетка
        if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first - 1, coordinate_of_hero.second)))   //клетка допустима
            if(this->vec_of_fluct[coordinate_of_hero.first - 1][coordinate_of_hero.second].first != no_fluct_){  //в клетке флуктуация
                float now_pwr = this->vec_of_fluct[coordinate_of_hero.first - 1][coordinate_of_hero.second].second;
                now_pwr = now_pwr * 0.95;
                vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first - 1, coordinate_of_hero.second), make_pair(this->vec_of_fluct[coordinate_of_hero.first - 1][coordinate_of_hero.second].first, now_pwr))); //флуктуация сохранена
            }

        //прямоугольник **
        //              **
        //              **
        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + (i - 1) - 1, coordinate_of_hero.second - 1)))   //клетка допустима      FF
                    if(this->vec_of_fluct[coordinate_of_hero.first + (i - 1) - 1][coordinate_of_hero.second - 1].first != no_fluct_){  //в клетке флуктуация  **
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + (i - 1) - 1][coordinate_of_hero.second - 1].second;//                   **
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + (i - 1) - 1, coordinate_of_hero.second - 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first + (i - 1) - 1][coordinate_of_hero.second - 1].first, now_pwr))); //флуктуация сохранена
                    }

        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + (i - 1) - 1, coordinate_of_hero.second)))   //клетка допустима      **
                    if(this->vec_of_fluct[coordinate_of_hero.first + (i - 1) - 1][coordinate_of_hero.second].first != no_fluct_){  //в клетке флуктуация  FF
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + (i - 1) - 1][coordinate_of_hero.second].second;//                   **
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + (i - 1) - 1, coordinate_of_hero.second), make_pair(this->vec_of_fluct[coordinate_of_hero.first + (i - 1) - 1][coordinate_of_hero.second].first, now_pwr))); //флуктуация сохранена
                    }

        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + (i - 1) - 1, coordinate_of_hero.second + 1)))   //клетка допустима      **
                    if(this->vec_of_fluct[coordinate_of_hero.first + (i - 1) - 1][coordinate_of_hero.second + 1].first != no_fluct_){  //в клетке флуктуация  **
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + (i - 1) - 1][coordinate_of_hero.second + 1].second;//                   FF
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + (i - 1) - 1, coordinate_of_hero.second + 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first + (i - 1) - 1][coordinate_of_hero.second + 1].first, now_pwr))); //флуктуация сохранена
                    }

        //полоска 5х1
        for(int i = 0; i < 5; ++i)
            if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first - 4, coordinate_of_hero.second + (i - 2))))   //клетка допустима
                if(this->vec_of_fluct[coordinate_of_hero.first - 4][coordinate_of_hero.second + (i - 2)].first != no_fluct_){  //в клетке флуктуация
                    float now_pwr = this->vec_of_fluct[coordinate_of_hero.first - 4][coordinate_of_hero.second + (i - 2)].second;
                    for(int k = 0; k > 4; ++k)
                        now_pwr = now_pwr * 0.95;
                    vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first - 4, coordinate_of_hero.second + (i - 2)), make_pair(this->vec_of_fluct[coordinate_of_hero.first - 4][coordinate_of_hero.second + (i - 2)].first, now_pwr))); //флуктуация сохранена
                }

        break;
    case down_:
        //все ряды вниз
        //единственная клетка
        if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + 1, coordinate_of_hero.second)))   //клетка допустима
            if(this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second].first != no_fluct_){  //в клетке флуктуация
                float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second].second;
                now_pwr = now_pwr * 0.95;
                vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + 1, coordinate_of_hero.second), make_pair(this->vec_of_fluct[coordinate_of_hero.first + 1][coordinate_of_hero.second].first, now_pwr))); //флуктуация сохранена
            }

        //прямоугольник **
        //              **
        //              **
        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + (i + 1) + 1, coordinate_of_hero.second - 1)))   //клетка допустима      FF
                    if(this->vec_of_fluct[coordinate_of_hero.first + (i + 1) + 1][coordinate_of_hero.second - 1].first != no_fluct_){  //в клетке флуктуация  **
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + (i + 1) + 1][coordinate_of_hero.second - 1].second;//                   **
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + (i + 1) + 1, coordinate_of_hero.second - 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first + (i + 1) + 1][coordinate_of_hero.second - 1].first, now_pwr))); //флуктуация сохранена
                    }

        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + (i + 1) + 1, coordinate_of_hero.second)))   //клетка допустима      **
                    if(this->vec_of_fluct[coordinate_of_hero.first + (i + 1) + 1][coordinate_of_hero.second].first != no_fluct_){  //в клетке флуктуация  FF
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + (i + 1) + 1][coordinate_of_hero.second].second;//                   **
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + (i + 1) + 1, coordinate_of_hero.second), make_pair(this->vec_of_fluct[coordinate_of_hero.first + (i + 1) + 1][coordinate_of_hero.second].first, now_pwr))); //флуктуация сохранена
                    }

        for(int i = 0; i < 2; ++i)
                if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + (i + 1) + 1, coordinate_of_hero.second + 1)))   //клетка допустима      **
                    if(this->vec_of_fluct[coordinate_of_hero.first + (i + 1) + 1][coordinate_of_hero.second + 1].first != no_fluct_){  //в клетке флуктуация  **
                        float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + (i + 1) + 1][coordinate_of_hero.second + 1].second;//                   FF
                        for(int k = i + 2; k > 0; --k)
                            now_pwr = now_pwr * 0.95;
                        vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + (i + 1) + 1, coordinate_of_hero.second + 1), make_pair(this->vec_of_fluct[coordinate_of_hero.first + (i + 1) + 1][coordinate_of_hero.second + 1].first, now_pwr))); //флуктуация сохранена
                    }

        //полоска 5х1
        for(int i = 0; i < 5; ++i)
            if(this->is_coordinate_is_normal(make_pair(coordinate_of_hero.first + 4, coordinate_of_hero.second + (i - 2))))   //клетка допустима
                if(this->vec_of_fluct[coordinate_of_hero.first + 4][coordinate_of_hero.second + (i - 2)].first != no_fluct_){  //в клетке флуктуация
                    float now_pwr = this->vec_of_fluct[coordinate_of_hero.first + 4][coordinate_of_hero.second + (i - 2)].second;
                    for(int k = 0; k > 4; ++k)
                        now_pwr = now_pwr * 0.95;
                    vec_of_visible_fluct.push_back(make_pair(make_pair(coordinate_of_hero.first + 4, coordinate_of_hero.second + (i - 2)), make_pair(this->vec_of_fluct[coordinate_of_hero.first + 4][coordinate_of_hero.second + (i - 2)].first, now_pwr))); //флуктуация сохранена
                }
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

    this->vec_of_graphik_of_trird_formanta = new vector<pair<float, float>>(*this->vec_of_graphik_of_second_formanta);

    //вставка флуктуаций на график
    for(auto obj : vec_of_visible_fluct){
        auto type_ = obj.second.first;

        float power_of_fluct = obj.second.second;
        //enum type_of_fluctuation{no_fluct_, inactive_semiconductors_, active_semiconductors_, bluetooth_, _5g_, _4g_, _3g_, GPS_, radio_, GLONASS_};
        switch (type_) {
        case inactive_semiconductors_:
            //1000-1025
            this->add_concret_fluct_second_formanta(1000, 25, power_of_fluct * 0.5);
            this->add_concret_fluct_trird_formanta(1000, 25, power_of_fluct);
        break;

        case active_semiconductors_:
            //1000-1025
            this->add_concret_fluct_second_formanta(this->start, 25, power_of_fluct);
            this->add_concret_fluct_trird_formanta(this->start, 25, power_of_fluct * 0.5);
        break;

        case bluetooth_:
            //2400-2500
            this->add_concret_fluct_second_formanta(2400, 100, power_of_fluct);
            this->add_concret_fluct_trird_formanta(2400, 100, power_of_fluct);
        break;

        case _5g_:
            //4800-4990
            this->add_concret_fluct_second_formanta(4800, 190, power_of_fluct);
            this->add_concret_fluct_trird_formanta(4800, 190, power_of_fluct);
        break;

        case _4g_:
            //452-467
            this->add_concret_fluct_second_formanta(452, 15, power_of_fluct);
            this->add_concret_fluct_trird_formanta(452, 15, power_of_fluct);

            //720-791
            this->add_concret_fluct_second_formanta(720, 71, power_of_fluct);
            this->add_concret_fluct_trird_formanta(720, 71, power_of_fluct);

            //2500-2570
            this->add_concret_fluct_second_formanta(2500, 70, power_of_fluct);
            this->add_concret_fluct_trird_formanta(2500, 70, power_of_fluct);
        break;

        case _3g_:
            //1920-1980
            this->add_concret_fluct_second_formanta(1920, 60, power_of_fluct);
            this->add_concret_fluct_trird_formanta(1920, 60, power_of_fluct);

            //2110-2170
            this->add_concret_fluct_second_formanta(2110, 60, power_of_fluct);
            this->add_concret_fluct_trird_formanta(2110, 60, power_of_fluct);
        break;

        case GPS_:
            //1176-1218
            this->add_concret_fluct_second_formanta(1176, 42, power_of_fluct);
            this->add_concret_fluct_trird_formanta(1176, 42, power_of_fluct);
        break;

        case radio_:
            //420-434
            this->add_concret_fluct_second_formanta(420, 14, power_of_fluct);
            this->add_concret_fluct_trird_formanta(420, 14, power_of_fluct);
        break;

        case GLONASS_:
            //1575-1602
            this->add_concret_fluct_second_formanta(1575, 27, power_of_fluct);
            this->add_concret_fluct_trird_formanta(1575, 27, power_of_fluct);
            //1207-1248
            this->add_concret_fluct_second_formanta(1207, 41, power_of_fluct);
            this->add_concret_fluct_trird_formanta(1207, 41, power_of_fluct);
            //1176-1202
            this->add_concret_fluct_second_formanta(1176, 26, power_of_fluct);
            this->add_concret_fluct_trird_formanta(1176, 26, power_of_fluct);
        break;
        }

    }
}

void randome_game::add_concret_fluct_second_formanta(int start, int length, float power_of_fluct)
{
    for(int i = 0; i < length; ++i){
        bool is_power_wil_be_lower_than_etalon = this->generate_random_int_number(0, 1);
        float power_of_this_ots;
        if(is_power_wil_be_lower_than_etalon)
            power_of_this_ots = power_of_fluct + (this->generate_random_int_number(1, power_of_fluct * 0.1));
        else
            power_of_this_ots = power_of_fluct + (- this->generate_random_int_number(1, power_of_fluct * 0.1));
        this->vec_of_graphik_of_second_formanta->operator[](start + i - 450) = make_pair(this->vec_of_graphik_of_second_formanta->operator[](start + i - 450).first, power_of_this_ots);
    }
}

void randome_game::add_concret_fluct_trird_formanta(int start, int length, float power_of_fluct)
{
    for(int i = 0; i < length; ++i){
        bool is_power_wil_be_lower_than_etalon = this->generate_random_int_number(0, 1);
        float power_of_this_ots;
        if(is_power_wil_be_lower_than_etalon)
            power_of_this_ots = power_of_fluct + (this->generate_random_int_number(1, power_of_fluct * 0.1));
        else
            power_of_this_ots = power_of_fluct + (- this->generate_random_int_number(1, power_of_fluct * 0.1));
        this->vec_of_graphik_of_trird_formanta->operator[](start + i - 450) = make_pair(this->vec_of_graphik_of_trird_formanta->operator[](start + i - 450).first, power_of_this_ots);
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

void randome_game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        QMessageBox::StandardButton mb = QMessageBox::question(this, "Внимание!", "Вы уверены, что хотите выйти?", QMessageBox::Yes | QMessageBox::No);

        if(mb == QMessageBox::No)
            return;
        else
            this->close();
    }

    if(!this->is_move_possible)
        return;

    if(event->key() == Qt::Key_W || event->key() == 0x0426){
         if(this->vec_of_soderzimoe[this->_hero->coordinate.first - 1][this->_hero->coordinate.second] == empty_){

             this->vec_of_soderzimoe[this->_hero->coordinate.first - 1][this->_hero->coordinate.second] = GG_;
             this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second] = empty_;
             this->_hero->coordinate = make_pair(this->_hero->coordinate.first - 1, this->_hero->coordinate.second);
             //texture swaping
             if(this->_hero->_orientation_of_hero != orientation_of_hero::up_){
                 this->_hero->setRotation(180.);
                 this->_hero->update();
             }
             this->_hero->_orientation_of_hero = orientation_of_hero::up_;

             this->start_animation_and_move_hero();
         }
         else{
             //texture swaping without move
             if(this->_hero->_orientation_of_hero != orientation_of_hero::up_){
                 this->_hero->setRotation(180.);
                 this->_hero->update();
             }
             this->_hero->_orientation_of_hero = orientation_of_hero::up_;
         }
    }

    if(event->key() == Qt::Key_A || event->key() == 0x0424){
        if(this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second - 1] == empty_){
            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second - 1] = GG_;
            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second] = empty_;
            this->_hero->coordinate = make_pair(this->_hero->coordinate.first, this->_hero->coordinate.second - 1);
            //texture swaping
            if(this->_hero->_orientation_of_hero != orientation_of_hero::left_){
                this->_hero->setRotation(90.);
                this->_hero->update();
                this->_hero->_orientation_of_hero = orientation_of_hero::left_;
            }

            this->start_animation_and_move_hero();
        }
        else{
            //texture swaping without move
            if(this->_hero->_orientation_of_hero != orientation_of_hero::left_){
                this->_hero->setRotation(90.);
                this->_hero->update();
                this->_hero->_orientation_of_hero = orientation_of_hero::left_;
            }
        }
   }

    if(event->key() == Qt::Key_S || event->key() == 0x042b){
        if(this->vec_of_soderzimoe[this->_hero->coordinate.first + 1][this->_hero->coordinate.second] == empty_){
            this->vec_of_soderzimoe[this->_hero->coordinate.first + 1][this->_hero->coordinate.second] = GG_;
            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second] = empty_;
            this->_hero->coordinate = make_pair(this->_hero->coordinate.first + 1, this->_hero->coordinate.second);
            //texture swaping
            if(this->_hero->_orientation_of_hero != orientation_of_hero::down_){
                this->_hero->setRotation(0.);
                this->_hero->update();
            }
            this->_hero->_orientation_of_hero = orientation_of_hero::down_;

            this->start_animation_and_move_hero();
        }
        else{
            //texture swaping without move
            if(this->_hero->_orientation_of_hero != orientation_of_hero::down_){
                this->_hero->setRotation(0.);
                this->_hero->update();
            }
            this->_hero->_orientation_of_hero = orientation_of_hero::down_;
        }
   }

    if(event->key() == Qt::Key_D || event->key() == 0x0412){
        if(this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second + 1] == empty_){
            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second + 1] = GG_;
            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second] = empty_;
            this->_hero->coordinate = make_pair(this->_hero->coordinate.first, this->_hero->coordinate.second + 1);
            //texture swaping
            if(this->_hero->_orientation_of_hero != orientation_of_hero::right_){
                this->_hero->setRotation(270.);
                this->_hero->update();
            }
            this->_hero->_orientation_of_hero = orientation_of_hero::right_;

            this->start_animation_and_move_hero();
        }
        else{
            //texture swaping without move
            if(this->_hero->_orientation_of_hero != orientation_of_hero::right_){
                this->_hero->setRotation(270.);
                this->_hero->update();
            }
            this->_hero->_orientation_of_hero = orientation_of_hero::right_;
        }
   }

    if(event->key() == Qt::Key_Return){
        if(this->_vibrannaya_kletka.first == -1 || (this->_vibrannaya_kletka.second == -1))
            return;


        if((this->vec_of_soderzimoe[this->_vibrannaya_kletka.first][this->_vibrannaya_kletka.second] != empty_) &&
                    (this->vec_of_soderzimoe[this->_vibrannaya_kletka.first][this->_vibrannaya_kletka.second] != GG_)){
            if(this->_coordinate_of_zakladka == _vibrannaya_kletka){
                QMessageBox::warning(this, "Поздравляю, вы нашли закладку!", "Поздравляю, вы нашли закладку!");
                this->close();
                return;
            }
            else{
                this->col_vo_popytok = this->col_vo_popytok - 1;
                if(col_vo_popytok == 0){
                    QMessageBox::warning(this, "Мимо!", "Вы проиграли, попробуйте еще раз!");
                    this->close();
                    return;
                }
                QMessageBox::warning(this, "Мимо!", "У вас осталось " + QString::number(this->col_vo_popytok) + " попыток!");
            }
        }
    }

    if(event->key() == Qt::Key_G || event->key() == 0x041f){

        this->generate_graphik_perems();

        auto graphik_window = new graphic_window(&(this->vec_of_soderzimoe), &(this->vec_of_fluct), this->vec_of_graphik_of_second_formanta, this->vec_of_graphik_of_trird_formanta, this);
        graphik_window->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
        graphik_window->setWindowTitle("Просмотр графика");
        graphik_window->showFullScreen();
    }
}

void randome_game::mousePressEvent(QMouseEvent *mEvent)
{
    if(this->_pix_chaged_cell != nullptr){
        scene->removeItem(this->_pix_chaged_cell);
        this->_pix_chaged_cell->hide();
        this->_pix_chaged_cell = nullptr;
    }

    auto temp = make_pair(this->view->mapToScene(mEvent->windowPos().x(), mEvent->windowPos().y()).x(), this->view->mapToScene(mEvent->windowPos().x(), mEvent->windowPos().y()).y());   //i dont now how it working, but it working!
    this->_vibrannaya_kletka = make_pair(floor(temp.second / 128), floor(temp.first / 128));

    if(this->_vibrannaya_kletka.first <= -1 || (this->_vibrannaya_kletka.second <= -1) || (this->_vibrannaya_kletka.first > this->weight_of_map) || (this->_vibrannaya_kletka.second > this->height_of_map))
        return;

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
/*    for(auto i = this->_list_of_pushed_buttons.begin(); i != this->_list_of_pushed_buttons.end(); ++i)
        if(event->key() == *i){
            this->_list_of_pushed_buttons.erase(i);
            return;
        }*/
}

void randome_game::move_hero()  //должен вызываться уже после установки нового направления героя!
{
    switch (this->_hero->_orientation_of_hero) {

    case up_:
        this->_hero->setPos(this->_hero->pos().x(), this->_hero->pos().y() - 4.);
        this->_hero->update();
        break;

    case down_:
        this->_hero->setPos(this->_hero->pos().x(), this->_hero->pos().y() + 4.);
        this->_hero->update();
        break;

    case left_:
        this->_hero->setPos(this->_hero->pos().x() - 4., this->_hero->pos().y());
        this->_hero->update();
        break;

    case right_:
        this->_hero->setPos(this->_hero->pos().x() + 4., this->_hero->pos().y());
        this->_hero->update();
        break;
    }
}

void randome_game::start_animation_and_move_hero()
{
    //запускаем анимацию у героя
    this->_hero->mo->start();
    this->_hero->_timer->setInterval(500);
    this->_hero->_timer->start();
    this->_hero->_timer_obnovl->setInterval(10);
    this->_hero->_timer_obnovl->start();

    //запускаем анимацию на сцене
    this->_timer_stop_animation->setInterval(256);
    this->_timer_for_change_position->setInterval(8);
    this->_timer_stop_animation->start();
    this->_timer_for_change_position->start();

    if(this->_pix_chaged_cell != nullptr){
        this->_pix_chaged_cell->hide();
        this->_pix_chaged_cell = nullptr;
    }

    this->is_move_possible = false;
    this->_timer->setInterval(256);
    this->_timer->start();
}

void randome_game::slotTimerAlarm()
{
    this->is_move_possible = true;
    this->_timer->stop();
}

void randome_game::slotTimerStopAnimationAlarm()
{
    this->_timer_for_change_position->stop();
    this->_timer_stop_animation->setInterval(256);
    float new_pos_x = round((this->_hero->pos().x() - 64.) / 128.) * 128. + 64.;
    float new_pos_y = round((this->_hero->pos().y() - 64.) / 128.) * 128. + 64.;
    this->_hero->setPos(new_pos_x, new_pos_y);
    this->_hero->update();
    this->_timer_stop_animation->stop();
}

void randome_game::slotTimerChangePositionAlarm()
{
    this->_timer_for_change_position->setInterval(8);
    this->_timer_for_change_position->start();
    this->move_hero();
}
