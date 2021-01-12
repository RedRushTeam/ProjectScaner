#include "nastr_game.h"
#include "ui_nastr_game.h"

nastr_game::nastr_game(QWidget *parent, int weight, int height) : randome_game(parent, weight, height)
{
    //QMessageBox::warning(this, "Внимание", "Выберете непустую клетку и нажмите кнопку \"ОК\"");

    this->_coordinate_of_zakladka = make_pair(-1, -1);

    QFont font_for_buttons("Times new roman", 18, QFont::Bold);
    QFont font_for_menue_bar("Times new roman", 16, QFont::Thin);

    QMenuBar *mb = new QMenuBar(this);          //todo оформитб его покрасивее
    mb->setFont(font_for_menue_bar);
    mb->setStyleSheet("QMenuBar {    background-color: grey;    margin: 2px; /* some spacing around the menu */} QMenuBar::item {    padding: 2px 25px 2px 20px;    border: 1px solid transparent; /* reserve space for selection border */}QMenuBar::item:selected {    border-color: darkblue;    background: rgba(100, 100, 100, 150);} QMenuBar::icon:checked { /* appearance of a 'checked' icon */    background: gray;    border: 1px inset gray;    position: absolute;    top: 1px;    right: 1px;    bottom: 1px;    left: 1px;} QMenuBar::separator {   height: 2px;    background: lightblue;    margin-left: 10px;    margin-right: 5px;} QMenuBar::indicator {    width: 13px;    height: 13px;}");

    QMenu *menuOne = new QMenu("&Действия с картой");
    //menuOne->addSeparator();

    menuOne->setStyleSheet("QMenu {    background-color: white;    margin: 2px; /* some spacing around the menu */} QMenu::item {    padding: 2px 25px 2px 20px;    border: 1px solid transparent; /* reserve space for selection border */}QMenu::item:selected {    border-color: darkblue;    background: rgba(100, 100, 100, 150);}QMenu::icon:checked { /* appearance of a 'checked' icon */    background: gray;    border: 1px inset gray;    position: absolute;    top: 1px;    right: 1px;    bottom: 1px;    left: 1px;}QMenu::separator {   height: 2px;    background: lightblue;    margin-left: 10px;    margin-right: 5px;} QMenu::indicator {    width: 13px;    height: 13px;}");

    QAction *upload = new QAction("&Выгрузить конфигурацию в файл", this);
    menuOne->addAction(upload);

    QAction *download = new QAction("&Загрузить конфигурацию из файла", this);
    menuOne->addAction(download);
    menuOne->addSeparator();

    QAction *clear_all = new QAction("&Очистить конфигурацию", this);
    menuOne->addAction(clear_all);
    menuOne->addSeparator();

    QAction *start_game = new QAction("&Начать игру", this);
    menuOne->addAction(start_game);

    connect(upload, SIGNAL(triggered()), this, SLOT(upload()));
    connect(download, SIGNAL(triggered()), this, SLOT(download()));
    connect(clear_all, SIGNAL(triggered()), this, SLOT(clear_all()));
    connect(start_game, SIGNAL(triggered()), this, SLOT(start_game()));

    this->vec_of_concr_texture.resize(this->height_of_map + 2);
    for(int i = 0; i < this->vec_of_soderzimoe.size(); ++i)
        this->vec_of_concr_texture[i].resize(this->weight_of_map + 2);

    for(int i = 0; i < this->weight_of_map + 2; ++i){
        //verhnie
        this->vec_of_concr_texture[0][i] = Bricks_H_;
        //niznie
        this->vec_of_concr_texture[this->height_of_map + 1][i] = Bricks_H_;
    }

    //vertical walls
    for(int i = 0; i < this->height_of_map + 2; ++i){
        //levie
        this->vec_of_concr_texture[i][0] = Bricks_V_;

        //pravie
        this->vec_of_concr_texture[i][this->weight_of_map + 1] = Bricks_V_;
    }

    //floor
    for(int i = 1; i < this->height_of_map + 1; ++i)
        for(int j = 1; j < this->weight_of_map + 1; ++j)
            this->vec_of_concr_texture[i][j] = pol_128x128_;

    mb->addMenu(menuOne);
    //mb->addSeparator();

    this->hbox->setMenuBar(mb);

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);

    QWidget* ScrollAreaWidgetContents = new QWidget(scrollArea);

    scrollArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    QGridLayout *grid = new QGridLayout(ScrollAreaWidgetContents);


    QLabel* title_white_chair = new QLabel("Белое кресло", this);
    title_white_chair->setFont(font_for_buttons);
    title_white_chair->setStyleSheet("color: rgb(0, 0, 0);");
    title_white_chair->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    grid->addWidget(title_white_chair, 0, 0, 1, 1, Qt::AlignHCenter);

    QPushButton* white_chair = new QPushButton(" ", this);
    white_chair->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    white_chair->setCursor(QCursor(Qt::PointingHandCursor));
    white_chair->setStyleSheet("QPushButton {border-image: url(:/new/random_game_textures/new/random_game_textures/white_chair_128x128.png);}");
    white_chair->setFont(font_for_buttons);
    white_chair->setMinimumSize(128., 128.);
    white_chair->setMaximumSize(128., 128.);
    grid->addWidget(white_chair, 1, 0, 1, 1, Qt::AlignHCenter);

    QLabel* title_divan_big = new QLabel("\"Тройной\" диван", this);
    title_divan_big->setFont(font_for_buttons);
    title_divan_big->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    grid->addWidget(title_divan_big, 2, 0, 1, 1, Qt::AlignHCenter);

    QPushButton* divan_big = new QPushButton(" ", this);
    divan_big->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    divan_big->setCursor(QCursor(Qt::PointingHandCursor));
    divan_big->setStyleSheet("QPushButton {border-image: url(:/new/random_game_textures/new/random_game_textures/divan_128x384.png);}");
    divan_big->setFont(font_for_buttons);
    divan_big->setMinimumSize(384., 128.);
    divan_big->setMaximumSize(384., 128.);
    grid->addWidget(divan_big, 3, 0, 1, 1, Qt::AlignHCenter);

    QLabel* title_simpe_divan = new QLabel("\"Двойной\" диван", this);
    title_simpe_divan->setFont(font_for_buttons);
    title_simpe_divan->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    grid->addWidget(title_simpe_divan, 0, 1, 1, 1, Qt::AlignHCenter);

    QPushButton* simpe_divan = new QPushButton(" ", this);
    simpe_divan->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    simpe_divan->setCursor(QCursor(Qt::PointingHandCursor));
    simpe_divan->setStyleSheet("QPushButton {border-image: url(:/new/random_game_textures/new/random_game_textures/divanH 256x128.jpg);}");
    simpe_divan->setFont(font_for_buttons);
    simpe_divan->setMinimumSize(256., 128.);
    simpe_divan->setMaximumSize(256., 128.);
    grid->addWidget(simpe_divan, 1, 1, 1, 1, Qt::AlignHCenter);

    QLabel* title_pro_table = new QLabel("Стол с вещами", this);
    title_pro_table->setFont(font_for_buttons);
    title_pro_table->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    grid->addWidget(title_pro_table, 2, 1, 1, 1, Qt::AlignHCenter);

    QPushButton* pro_table = new QPushButton(" ", this);
    pro_table->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    pro_table->setCursor(QCursor(Qt::PointingHandCursor));
    pro_table->setStyleSheet("QPushButton {border-image: url(:/new/random_game_textures/new/random_game_textures/table_pro_128x256.png);}");
    pro_table->setFont(font_for_buttons);
    pro_table->setMinimumSize(256., 128.);
    pro_table->setMaximumSize(256., 128.);
    grid->addWidget(pro_table, 3, 1, 1, 1, Qt::AlignHCenter);

    QLabel* title_wood_chair = new QLabel("Деревянное кресло", this);
    title_wood_chair->setFont(font_for_buttons);
    title_wood_chair->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    grid->addWidget(title_wood_chair, 4, 1, 1, 1, Qt::AlignHCenter);

    QPushButton* wood_chair_128x128 = new QPushButton(" ", this);
    wood_chair_128x128->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    wood_chair_128x128->setCursor(QCursor(Qt::PointingHandCursor));
    wood_chair_128x128->setStyleSheet("QPushButton {border-image: url(:/new/random_game_textures/new/random_game_textures/wood_chair_128x128.png);}");
    wood_chair_128x128->setFont(font_for_buttons);
    wood_chair_128x128->setMinimumSize(128., 128.);
    wood_chair_128x128->setMaximumSize(128., 128.);
    grid->addWidget(wood_chair_128x128, 5, 1, 1, 1, Qt::AlignHCenter);

    QLabel* title_pol = new QLabel("Пустая клетка", this);
    title_pol->setFont(font_for_buttons);
    title_pol->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    grid->addWidget(title_pol, 4, 0, 1, 1, Qt::AlignHCenter);

    QPushButton* pol_128x128 = new QPushButton(" ", this);
    pol_128x128->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    pol_128x128->setCursor(QCursor(Qt::PointingHandCursor));
    pol_128x128->setStyleSheet("QPushButton {border-image: url(:/new/random_game_textures/228.1.jpg);}");
    pol_128x128->setFont(font_for_buttons);
    pol_128x128->setMinimumSize(128., 128.);
    pol_128x128->setMaximumSize(128., 128.);
    grid->addWidget(pol_128x128, 5, 0, 1, 1, Qt::AlignHCenter);

    QLabel* title_Bricks_H = new QLabel("Горизонтальная стена", this);
    title_Bricks_H->setFont(font_for_buttons);
    title_Bricks_H->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    grid->addWidget(title_Bricks_H, 6, 1, 1, 1, Qt::AlignHCenter);

    QPushButton* Bricks_H = new QPushButton(" ", this);
    Bricks_H->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    Bricks_H->setCursor(QCursor(Qt::PointingHandCursor));
    Bricks_H->setStyleSheet("QPushButton {border-image: url(:/new/random_game_textures/Bricks_H.jpg);}");
    Bricks_H->setFont(font_for_buttons);
    Bricks_H->setMinimumSize(128., 128.);
    Bricks_H->setMaximumSize(128., 128.);
    grid->addWidget(Bricks_H, 7, 1, 1, 1, Qt::AlignHCenter);

    QLabel* title_Bricks_V = new QLabel("Вертикальная стена", this);
    title_Bricks_V->setFont(font_for_buttons);
    title_Bricks_V->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    grid->addWidget(title_Bricks_V, 6, 0, 1, 1, Qt::AlignHCenter);

    QPushButton* Bricks_V = new QPushButton(" ", this);
    Bricks_V->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    Bricks_V->setCursor(QCursor(Qt::PointingHandCursor));
    Bricks_V->setStyleSheet("QPushButton {border-image: url(:/new/random_game_textures/Bricks_V.jpg);}");
    Bricks_V->setFont(font_for_buttons);
    Bricks_V->setMinimumSize(128., 128.);
    Bricks_V->setMaximumSize(128., 128.);
    grid->addWidget(Bricks_V, 7, 0, 1, 1, Qt::AlignHCenter);

    QLabel* title_tableH = new QLabel("Тройной стол", this);
    title_tableH->setFont(font_for_buttons);
    title_tableH->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    grid->addWidget(title_tableH, 8, 1, 1, 1, Qt::AlignHCenter);

    QPushButton* tableH = new QPushButton(" ", this);
    tableH->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    tableH->setCursor(QCursor(Qt::PointingHandCursor));
    tableH->setStyleSheet("QPushButton {border-image: url(:/new/random_game_textures/new/random_game_textures/tableH 384x128.jpg);}");
    tableH->setFont(font_for_buttons);
    tableH->setMinimumSize(384., 128.);
    tableH->setMaximumSize(384., 128.);
    grid->addWidget(tableH, 9, 1, 1, 1, Qt::AlignHCenter);

    QLabel* title_red_square = new QLabel("Закладка", this);
    title_red_square->setFont(font_for_buttons);
    title_red_square->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    grid->addWidget(title_red_square, 8, 0, 1, 1, Qt::AlignHCenter);

    QPushButton* red_square = new QPushButton(" ", this);
    red_square->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    red_square->setCursor(QCursor(Qt::PointingHandCursor));
    red_square->setStyleSheet("QPushButton {border-image: url(:/new/random_game_textures/new/random_game_textures/red_square128x128.png);}");
    red_square->setFont(font_for_buttons);
    red_square->setMinimumSize(128., 128.);
    red_square->setMaximumSize(128., 128.);
    grid->addWidget(red_square, 9, 0, 1, 1, Qt::AlignHCenter);

    QLabel* title_hero = new QLabel("Герой", this);
    title_hero->setFont(font_for_buttons);
    title_hero->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    grid->addWidget(title_hero, 10, 0, 1, 1, Qt::AlignHCenter);

    QPushButton* hero = new QPushButton(" ", this);
    hero->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    hero->setCursor(QCursor(Qt::PointingHandCursor));
    hero->setStyleSheet("QPushButton {border-image: url(:/new/random_game_textures/new/random_game_textures/Animation.gif);}");
    hero->setFont(font_for_buttons);
    hero->setMinimumSize(128., 128.);
    hero->setMaximumSize(128., 128.);
    grid->addWidget(hero, 11, 0, 1, 1, Qt::AlignHCenter);

    /*QPushButton* start_pushed = new QPushButton("Начать игру", this);
    start_pushed->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_pushed->setCursor(QCursor(Qt::PointingHandCursor));
    start_pushed->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
    start_pushed->setFont(font_for_buttons);
    start_pushed->setMinimumSize(768., 128.);
    start_pushed->setMaximumSize(768., 128.);
    grid->addWidget(start_pushed, 10, 0, 2, 2, Qt::AlignHCenter);*/

    scrollArea->setWidget(ScrollAreaWidgetContents);

    connect(white_chair, &QPushButton::clicked, this, &nastr_game::white_chair_add);
    connect(divan_big, &QPushButton::clicked, this, &nastr_game::divan_big_add);
    connect(simpe_divan, &QPushButton::clicked, this, &nastr_game::simpe_divan_add);
    connect(pro_table, &QPushButton::clicked, this, &nastr_game::pro_table_add);
    connect(wood_chair_128x128, &QPushButton::clicked, this, &nastr_game::wood_chair_128x128_add);
    connect(pol_128x128, &QPushButton::clicked, this, &nastr_game::pol_128x128_add);
    connect(Bricks_H, &QPushButton::clicked, this, &nastr_game::Bricks_H_add);
    connect(tableH, &QPushButton::clicked, this, &nastr_game::tableH_add);
    connect(red_square, &QPushButton::clicked, this, &nastr_game::red_square_add);
    connect(Bricks_V, &QPushButton::clicked, this, &nastr_game::Bricks_V_add);
    connect(hero, &QPushButton::clicked, this, &nastr_game::hero_add);

    this->hbox->addWidget(scrollArea);

    this->clear_all();
}

void nastr_game::white_chair_add()
{
    this->type_of_texture_ = white_chair_;
}

void nastr_game::divan_big_add()
{
    this->type_of_texture_ = divan_big_;
}

void nastr_game::simpe_divan_add()
{
    this->type_of_texture_ = simpe_divan_;
}

void nastr_game::pro_table_add()
{
    this->type_of_texture_ = pro_table_;
}

void nastr_game::wood_chair_128x128_add()
{
    this->type_of_texture_ = wood_chair_128x128_;
}

void nastr_game::pol_128x128_add()
{
    this->type_of_texture_ = pol_128x128_;
}

void nastr_game::Bricks_H_add()
{
    this->type_of_texture_ = Bricks_H_;
}

void nastr_game::tableH_add()
{
    this->type_of_texture_ = tableH_;
}

void nastr_game::red_square_add()
{
    this->type_of_texture_ = red_square_;
}

void nastr_game::Bricks_V_add()
{
    this->type_of_texture_ = Bricks_V_;
}

void nastr_game::hero_add()
{
    this->type_of_texture_ = GG__;
}

void nastr_game::upload()
{

    if(this->_coordinate_of_zakladka == make_pair(-1, -1) || (this->_hero->coordinate == make_pair(-1, -1))){
        QMessageBox::warning(this, "Внимание!", "Перед сохранением необходимо добавить героя и закладку!");
        return;
    }

    QString full_fname = QFileDialog::getSaveFileName(this, "Выберите папку", "", "BIN(*.bin)");

    if(full_fname.size() == 0)
        return;

    QFile out(full_fname);
    out.open(QIODevice::WriteOnly);
    QDataStream stream(&out);
    QByteArray array;

    for(int i = 0; i < (this->height_of_map + 2); ++i){
        array.append("{");
        for(int j = 0; j < (this->weight_of_map + 2); ++j){
                array.append(QString::fromStdString("[" + to_string(this->vec_of_concr_texture[i][j]) + "]"));
            }
        array.append("}");
    }

    array.append(QString::fromStdString("h" + to_string(this->_hero->coordinate.first) + ":" + to_string(this->_hero->coordinate.second) + ";"));
    array.append(QString::fromStdString("z" + to_string(this->_coordinate_of_zakladka.first + 1) + ":" + to_string(this->_coordinate_of_zakladka.second + 1) + ";"));

    stream << array;

    out.close();
}

void nastr_game::download()
{
    this->clear_all();

    QString full_fname = QFileDialog::getOpenFileName(this, tr("Выберите файл"), "" , (tr("*.bin")));

    if(full_fname.size() == 0)
        return;

    QFile in(full_fname);

    if(!in.open(QFile::ReadOnly)){
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл.");
        return;
    }

    QByteArray array;
    QDataStream instream(&in);
    instream >> array;

    QString instr_ = QTextCodec::codecForMib(106)->toUnicode(array);
    string instr = instr_.toStdString();

    int i1 = -1;
    int j1 = -1;

    while(true){
        auto np = instr.npos;
        if(instr.find("}") == np)
            break;

        ++i1;

        string now_line = instr.substr(1, instr.find("}") - 1); //взятая "строка" целиком
        instr = instr.substr(instr.find("}") + 1, instr.size());    //сокращаем главную строку

        while(true){
            if(now_line.find("]") == now_line.npos){
                j1 = -1;
                break;
            }
            ++j1;

            this->vec_of_concr_texture[i1][j1] = type_of_texture(stoi(now_line.substr(1, now_line.find("]"))));
            //this->vec_of_soderzimoe[i][j] = type_of_item(stoi(now_line.substr(1, now_line.find("]"))));
            now_line = now_line.substr(now_line.find("]") + 1, now_line.size());
        }
    }
    in.close();

    //расстановка объектов на сцену
    for(int i = 0; i < (this->height_of_map + 2); ++i)
        for(int j = 0; j < (this->weight_of_map + 2); ++j){
    auto temp = make_pair(i - 1, j - 1);

    switch (this->vec_of_concr_texture[i][j]) {
    case white_chair_:{
        QPixmap* QPix_ = new QPixmap();
        QPix_->load(":/new/random_game_textures/new/random_game_textures/white_chair_128x128.png");
        Pixmap *Pix_ = new Pixmap(*QPix_);

        if(temp.first < -1 || (temp.second < -1) || (temp.first > this->weight_of_map) || (temp.second > this->height_of_map))
            break;

        /*if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_)
            return;*/

        this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
        this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
        Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
        Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
        this->scene->addItem(Pix_);
    }
        break;

    case divan_big_:{
        QPixmap* QPix_ = new QPixmap();
        QPix_->load(":/new/random_game_textures/new/random_game_textures/divan_128x384.png");
        Pixmap *Pix_ = new Pixmap(*QPix_);

        if(temp.first < -1 || (temp.second < -1) || (temp.first > this->weight_of_map) || (temp.second > this->height_of_map))
            break;
        if(temp.first < -1 || (temp.second - 1 < -1) || (temp.first > this->weight_of_map) || (temp.second - 1 > this->height_of_map))
            break;
        if(temp.first < -1 || (temp.second + 1 < -1) || (temp.first > this->weight_of_map) || (temp.second + 1 > this->height_of_map))
            break;

        /*if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_ || (this->vec_of_soderzimoe[temp.first + 1][temp.second] != empty_) || (this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] != empty_))
            return;*/

        is_las_texture_was_be_3x = true;

        this->vec_of_soderzimoe[temp.first + 1][temp.second] = neprohod_object_;
        this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] = neprohod_object_;
        this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
        this->vec_of_pixmaps[temp.first + 1][temp.second] = Pix_;
        this->vec_of_pixmaps[temp.first + 1][temp.second + 2] = Pix_;
        this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
        Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
        Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
        scene->addItem(Pix_);
    }
        break;

    case simpe_divan_:{
        QPixmap* QPix_ = new QPixmap();
        QPix_->load(":/new/random_game_textures/new/random_game_textures/divanH 256x128.jpg");
        Pixmap *Pix_ = new Pixmap(*QPix_);

        if(temp.first < -1 || (temp.second < -1) || (temp.first > this->weight_of_map) || (temp.second > this->height_of_map))
            break;
        if(temp.first < -1 || (temp.second + 1 < -1) || (temp.first > this->weight_of_map) || (temp.second + 1 > this->height_of_map))
            break;

        /*if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_ || (this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] != empty_))
            return;*/

        is_las_texture_was_be_3x = true;

        this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
        this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] = neprohod_object_;
        this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
        this->vec_of_pixmaps[temp.first + 1][temp.second + 2] = Pix_;
        Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
        Pix_->setPos(128. * temp.second + 256., 192. + 128 * temp.first);
        scene->addItem(Pix_);
    }
        break;

    case pro_table_:{
        QPixmap* QPix_ = new QPixmap();
        QPix_->load(":/new/random_game_textures/new/random_game_textures/table_pro_128x256.png");
        Pixmap *Pix_ = new Pixmap(*QPix_);

        if(temp.first < -1 || (temp.second < -1) || (temp.first > this->weight_of_map) || (temp.second > this->height_of_map))
            break;
        if(temp.first < -1 || (temp.second + 1 < -1) || (temp.first > this->weight_of_map) || (temp.second + 1 > this->height_of_map))
            break;

        /*if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_ || (this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] != empty_))
            return;*/

        is_las_texture_was_be_3x = true;

        this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
        this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] = neprohod_object_;
        this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
        this->vec_of_pixmaps[temp.first + 1][temp.second + 2] = Pix_;
        Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
        Pix_->setPos(128. * temp.second + 256., 192. + 128 * temp.first);
        scene->addItem(Pix_);
    }
        break;

    case wood_chair_128x128_:{
        QPixmap* QPix_ = new QPixmap();
        QPix_->load(":/new/random_game_textures/new/random_game_textures/wood_chair_128x128.png");
        Pixmap *Pix_ = new Pixmap(*QPix_);

        if(temp.first < -1 || (temp.second < -1) || (temp.first > this->weight_of_map) || (temp.second > this->height_of_map))
            break;

        /*if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_)
            return;*/

        this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
        this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
        Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
        Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
        this->scene->addItem(Pix_);
    }
        break;

    case pol_128x128_:{

        if(is_las_texture_was_be_3x){
            is_las_texture_was_be_3x = !is_las_texture_was_be_3x;
            break;;
        }

        QPixmap* QPix_ = new QPixmap();
        QPix_->load(":/new/random_game_textures/228.1.jpg");
        Pixmap *Pix_ = new Pixmap(*QPix_);

        if(temp.first < -1 || (temp.second < -1) || (temp.first > this->weight_of_map) || (temp.second > this->height_of_map))
            break;

        /*if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] == empty_)
            return;*/

        this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
        this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = empty_;
        Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
        Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
        this->scene->addItem(Pix_);
    }
        break;

    case Bricks_H_:{
        QPixmap* QPix_ = new QPixmap();
        QPix_->load(":/new/random_game_textures/Bricks_H.jpg");
        Pixmap *Pix_ = new Pixmap(*QPix_);

        if(temp.first < -1 || (temp.second < -1) || (temp.first > this->weight_of_map) || (temp.second > this->height_of_map))
            break;

        /*if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_)
            return;*/

        this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
        this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
        Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
        Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
        this->scene->addItem(Pix_);
    }
        break;

    case tableH_:{
        QPixmap* QPix_ = new QPixmap();
        QPix_->load(":/new/random_game_textures/new/random_game_textures/tableH 384x128.jpg");
        Pixmap *Pix_ = new Pixmap(*QPix_);

        if(temp.first < -1 || (temp.second < -1) || (temp.first > this->weight_of_map) || (temp.second > this->height_of_map))
            break;
        if(temp.first < -1 || (temp.second - 1 < -1) || (temp.first > this->weight_of_map) || (temp.second - 1 > this->height_of_map))
            break;
        if(temp.first < -1 || (temp.second + 1 < -1) || (temp.first > this->weight_of_map) || (temp.second + 1 > this->height_of_map))
            break;

        is_las_texture_was_be_3x = true;

        /*if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_ || (this->vec_of_soderzimoe[temp.first + 1][temp.second] != empty_) || (this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] != empty_))
            return;*/

        this->vec_of_soderzimoe[temp.first + 1][temp.second] = neprohod_object_;
        this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] = neprohod_object_;
        this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
        this->vec_of_pixmaps[temp.first + 1][temp.second] = Pix_;
        this->vec_of_pixmaps[temp.first + 1][temp.second + 2] = Pix_;
        this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
        Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
        Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
        scene->addItem(Pix_);
    }
        break;

    case Bricks_V_:{
        QPixmap* QPix_ = new QPixmap();
        QPix_->load(":/new/random_game_textures/Bricks_V.jpg");
        Pixmap *Pix_ = new Pixmap(*QPix_);

        if(temp.first < -1 || (temp.second < -1) || (temp.first > this->weight_of_map) || (temp.second > this->height_of_map))
            break;

        this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
        this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
        Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
        Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
        this->scene->addItem(Pix_);
    }
        break;
    };
}

    this->_hero->coordinate = make_pair(stoi(instr.substr(instr.find("h") + 1, instr.find(":") - 1)), stoi(instr.substr(instr.find(":") + 1, instr.find(";") - 3)));
    this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second] = GG_;
    _hero->setPos(128. * this->_hero->coordinate.second + 64, 128. * this->_hero->coordinate.first + 64);
    scene->addItem(_hero);

    instr = instr.substr(instr.find(";") + 1, instr.size());

    this->_coordinate_of_zakladka = make_pair(stoi(instr.substr(instr.find("z") + 1, instr.find(":") - 1)) - 1, stoi(instr.substr(instr.find(":") + 1, instr.find(";") - 3)) - 1);

    if(this->_pix_chaged_cell != nullptr){
        scene->removeItem(this->_pix_chaged_cell);
        this->_pix_chaged_cell->hide();
        this->_pix_chaged_cell = nullptr;
    }

    QPixmap* red_square = new QPixmap();
    red_square->load(":/new/random_game_textures/new/random_game_textures/red_square128x128.png");  //загрузка красного квадрата в png

    this->_pix_chaged_cell = new Pixmap(*red_square);
    this->_pix_chaged_cell->setOffset(-red_square->width()/2, -red_square->height()/2);
    this->_pix_chaged_cell->setPos(this->_coordinate_of_zakladka.second * 128. + 128. + 64., 128. * this->_coordinate_of_zakladka.first + 64. + 128.);
    scene->addItem(this->_pix_chaged_cell);

    int blyadovka1 = 0;
}

bool nastr_game::dialog_method()
{
    QMessageBox::StandardButton mb = QMessageBox::question(this, "Внимание!", "Вы уверены, что хотите удалить текущую конфигурацию?", QMessageBox::Yes | QMessageBox::No);

    if(mb == QMessageBox::No)
        return true;
    return false;
}

void nastr_game::clear_all()
{
    static bool shit_b = true;
    if(!shit_b){
        if(this->dialog_method())
            return;
    }
    else
        shit_b = false;

    for(int i = 0; i < (this->height_of_map + 2); ++i)
        for(int j = 0; j < (this->weight_of_map + 2); ++j)
            if(!(i == 0 || (j == 0) || (i == this->height_of_map + 1) || (j == this->weight_of_map + 1))){

                //очистка типа хранимой текстуры
                this->vec_of_concr_texture[i][j] = pol_128x128_;

                //GG пока не трогаем
                /*if(this->vec_of_soderzimoe[i][j] == GG_)
                    continue;*/

                //очищаем карту
                this->vec_of_soderzimoe[i][j] = empty_;

                //очищаем сущности на сцене
                this->scene->removeItem(this->vec_of_pixmaps[i][j]);
            }

    this->_hero->coordinate = make_pair(-1, -1);

    this->scene->removeItem(this->_hero);

    if(this->_pix_chaged_cell != nullptr){
       this->_pix_chaged_cell->hide();
       this->_pix_chaged_cell = nullptr;
    }

    this->_coordinate_of_zakladka = make_pair(-1, -1);
}

void nastr_game::start_game()
{

}

void nastr_game::mousePressEvent(QMouseEvent *event)        //todo удаление объекта целиком при коллизии
{
    if(event->button() == Qt::RightButton){
        auto temp = make_pair(this->view->mapToScene(event->windowPos().x(), event->windowPos().y()).x(), this->view->mapToScene(event->windowPos().x(), event->windowPos().y()).y());   //i dont now how it working, but it working!
        temp = make_pair(trunc(temp.second / 128), trunc(temp.first / 128));    //нормализованная координата
        temp = make_pair(temp.first - 1, temp.second - 1);     //нормализованная координата для написанного мной костыля

        if(temp.first <= -1 || (temp.second <= -1) || (temp.first >= this->weight_of_map) || (temp.second >= this->height_of_map))
            return;

//enum type_of_texture{empty__, white_chair_, divan_big_, simpe_divan_, pro_table_, wood_chair_128x128_, pol_128x128_, Bricks_H_, tableH_, red_square_, Bricks_V_, GG__};
        if(this->vec_of_concr_texture[temp.first + 1][temp.second + 1] == empty__ ||
                (this->vec_of_concr_texture[temp.first + 1][temp.second + 1] == GG__) ||
                (this->vec_of_concr_texture[temp.first + 1][temp.second + 1] == pol_128x128_) ||
                (this->vec_of_concr_texture[temp.first + 1][temp.second + 1] == divan_big_) ||
                (this->vec_of_concr_texture[temp.first + 1][temp.second + 1] == simpe_divan_) ||
                (this->vec_of_concr_texture[temp.first + 1][temp.second + 1] == pro_table_) ||
                (this->vec_of_concr_texture[temp.first + 1][temp.second + 1] == tableH_))
            return;

        this->vec_of_pixmaps[temp.first + 1][temp.second + 1]->setRotation(this->vec_of_pixmaps[temp.first + 1][temp.second + 1]->rotation() + 90.);
    }

    if(!this->is_game_started_now){

        if(event->button() == Qt::RightButton)
            return;

        auto temp = make_pair(this->view->mapToScene(event->windowPos().x(), event->windowPos().y()).x(), this->view->mapToScene(event->windowPos().x(), event->windowPos().y()).y());   //i dont now how it working, but it working!
        temp = make_pair(trunc(temp.second / 128), trunc(temp.first / 128));    //нормализованная координата
        temp = make_pair(temp.first - 1, temp.second - 1);     //нормализованная координата для написанного мной костыля

        if(temp.first <= -1 || (temp.second <= -1) || (temp.first > this->weight_of_map) || (temp.second > this->height_of_map))
            return;

        //выборка нужной тектсуры
        switch (this->type_of_texture_) {

        case GG__:{
            this->_hero->coordinate = make_pair(temp.first + 1, temp.second + 1);
            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second] = empty_;

            this->vec_of_soderzimoe[this->_hero->coordinate.first][this->_hero->coordinate.second] = GG_;
            _hero->setPos(128. * this->_hero->coordinate.second + 64, 128. * this->_hero->coordinate.first + 64);

            scene->addItem(_hero);
        }
            break;

        case white_chair_:{
            QPixmap* QPix_ = new QPixmap();
            QPix_->load(":/new/random_game_textures/new/random_game_textures/white_chair_128x128.png");
            Pixmap *Pix_ = new Pixmap(*QPix_);

            if(temp.first <= -1 || (temp.second <= -1) || (temp.first >= this->weight_of_map) || (temp.second >= this->height_of_map))
                return;

            if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_)
                return;

            this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
            this->vec_of_concr_texture[temp.first + 1][temp.second + 1] = white_chair_; //велосипед
            this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
            Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
            Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
            this->scene->addItem(Pix_);
        }
            break;

        case divan_big_:{
            QPixmap* QPix_ = new QPixmap();
            QPix_->load(":/new/random_game_textures/new/random_game_textures/divan_128x384.png");
            Pixmap *Pix_ = new Pixmap(*QPix_);

            if(temp.first <= -1 || (temp.second <= -1) || (temp.first >= this->weight_of_map) || (temp.second >= this->height_of_map))
                return;
            if(temp.first <= -1 || (temp.second - 1 <= -1) || (temp.first >= this->weight_of_map) || (temp.second - 1 >= this->height_of_map))
                return;
            if(temp.first <= -1 || (temp.second + 1 <= -1) || (temp.first >= this->weight_of_map) || (temp.second + 1 >= this->height_of_map))
                return;

            if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_ || (this->vec_of_soderzimoe[temp.first + 1][temp.second] != empty_) || (this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] != empty_))
                return;

            //this->vec_of_concr_texture[temp.first + 1][temp.second] = divan_big_; //велосипед
            //this->vec_of_concr_texture[temp.first + 1][temp.second + 2] = divan_big_; //велосипед
            this->vec_of_concr_texture[temp.first + 1][temp.second + 1] = divan_big_; //велосипед

            this->vec_of_soderzimoe[temp.first + 1][temp.second] = neprohod_object_;
            this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] = neprohod_object_;
            this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
            this->vec_of_pixmaps[temp.first + 1][temp.second] = Pix_;
            this->vec_of_pixmaps[temp.first + 1][temp.second + 2] = Pix_;
            this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
            Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
            Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
            scene->addItem(Pix_);
        }
            break;

        case simpe_divan_:{
            QPixmap* QPix_ = new QPixmap();
            QPix_->load(":/new/random_game_textures/new/random_game_textures/divanH 256x128.jpg");
            Pixmap *Pix_ = new Pixmap(*QPix_);

            if(temp.first <= -1 || (temp.second <= -1) || (temp.first >= this->weight_of_map) || (temp.second >= this->height_of_map))
                return;
            if(temp.first <= -1 || (temp.second + 1 <= -1) || (temp.first >= this->weight_of_map) || (temp.second + 1 >= this->height_of_map))
                return;

            if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_ || (this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] != empty_))
                return;

            //this->vec_of_concr_texture[temp.first + 1][temp.second + 2] = simpe_divan_; //велосипед
            this->vec_of_concr_texture[temp.first + 1][temp.second + 1] = simpe_divan_; //велосипед

            this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
            this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] = neprohod_object_;
            this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
            this->vec_of_pixmaps[temp.first + 1][temp.second + 2] = Pix_;
            Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
            Pix_->setPos(128. * temp.second + 256., 192. + 128 * temp.first);
            scene->addItem(Pix_);
        }
            break;

        case pro_table_:{
            QPixmap* QPix_ = new QPixmap();
            QPix_->load(":/new/random_game_textures/new/random_game_textures/table_pro_128x256.png");
            Pixmap *Pix_ = new Pixmap(*QPix_);

            if(temp.first <= -1 || (temp.second <= -1) || (temp.first >= this->weight_of_map) || (temp.second >= this->height_of_map))
                return;
            if(temp.first <= -1 || (temp.second + 1 <= -1) || (temp.first >= this->weight_of_map) || (temp.second + 1 >= this->height_of_map))
                return;

            if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_ || (this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] != empty_))
                return;

            //this->vec_of_concr_texture[temp.first + 1][temp.second + 2] = pro_table_; //велосипед
            this->vec_of_concr_texture[temp.first + 1][temp.second + 1] = pro_table_; //велосипед

            this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
            this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] = neprohod_object_;
            this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
            this->vec_of_pixmaps[temp.first + 1][temp.second + 2] = Pix_;
            Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
            Pix_->setPos(128. * temp.second + 256., 192. + 128 * temp.first);
            scene->addItem(Pix_);
        }
            break;

        case wood_chair_128x128_:{
            QPixmap* QPix_ = new QPixmap();
            QPix_->load(":/new/random_game_textures/new/random_game_textures/wood_chair_128x128.png");
            Pixmap *Pix_ = new Pixmap(*QPix_);

            if(temp.first <= -1 || (temp.second <= -1) || (temp.first >= this->weight_of_map) || (temp.second >= this->height_of_map))
                return;

            if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_)
                return;

            this->vec_of_concr_texture[temp.first + 1][temp.second + 1] = wood_chair_128x128_; //велосипед

            this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
            this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
            Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
            Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
            this->scene->addItem(Pix_);
        }
            break;

        case pol_128x128_:{
            QPixmap* QPix_ = new QPixmap();
            QPix_->load(":/new/random_game_textures/228.1.jpg");
            Pixmap *Pix_ = new Pixmap(*QPix_);

            if(temp.first <= -1 || (temp.second <= -1) || (temp.first >= this->weight_of_map) || (temp.second >= this->height_of_map))
                return;

            if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] == empty_)
                return;

            this->vec_of_concr_texture[temp.first + 1][temp.second + 1] = pol_128x128_; //велосипед

            this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
            this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = empty_;
            Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
            Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
            this->scene->addItem(Pix_);
        }
            break;

        case Bricks_H_:{
            QPixmap* QPix_ = new QPixmap();
            QPix_->load(":/new/random_game_textures/Bricks_H.jpg");
            Pixmap *Pix_ = new Pixmap(*QPix_);

            if(temp.first <= -1 || (temp.second <= -1) || (temp.first >= this->weight_of_map) || (temp.second >= this->height_of_map))
                return;

            if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_)
                return;

            this->vec_of_concr_texture[temp.first + 1][temp.second + 1] = Bricks_H_; //велосипед

            this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
            this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
            Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
            Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
            this->scene->addItem(Pix_);
        }
            break;

        case tableH_:{
            QPixmap* QPix_ = new QPixmap();
            QPix_->load(":/new/random_game_textures/new/random_game_textures/tableH 384x128.jpg");
            Pixmap *Pix_ = new Pixmap(*QPix_);

            if(temp.first <= -1 || (temp.second <= -1) || (temp.first >= this->weight_of_map) || (temp.second >= this->height_of_map))
                return;
            if(temp.first <= -1 || (temp.second - 1 <= -1) || (temp.first >= this->weight_of_map) || (temp.second - 1 >= this->height_of_map))
                return;
            if(temp.first <= -1 || (temp.second + 1 <= -1) || (temp.first >= this->weight_of_map) || (temp.second + 1 >= this->height_of_map))
                return;

            if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] != empty_ || (this->vec_of_soderzimoe[temp.first + 1][temp.second] != empty_) || (this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] != empty_))
                return;

            //this->vec_of_concr_texture[temp.first + 1][temp.second] = tableH_; //велосипед
            //this->vec_of_concr_texture[temp.first + 1][temp.second + 2] = tableH_; //велосипед
            this->vec_of_concr_texture[temp.first + 1][temp.second + 1] = tableH_; //велосипед

            this->vec_of_soderzimoe[temp.first + 1][temp.second] = neprohod_object_;
            this->vec_of_soderzimoe[temp.first + 1][temp.second + 2] = neprohod_object_;
            this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
            this->vec_of_pixmaps[temp.first + 1][temp.second] = Pix_;
            this->vec_of_pixmaps[temp.first + 1][temp.second + 2] = Pix_;
            this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
            Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
            Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
            scene->addItem(Pix_);
        }
            break;

        case red_square_:{  //this code is shit

            if(this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] == empty_ || (this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] == GG_))
                return;

            if(this->_pix_chaged_cell != nullptr){
                scene->removeItem(this->_pix_chaged_cell);
                this->_pix_chaged_cell->hide();
                this->_pix_chaged_cell = nullptr;
            }

            this->_coordinate_of_zakladka = make_pair(temp.first + 1, temp.second + 1);

            QPixmap* red_square = new QPixmap();
            red_square->load(":/new/random_game_textures/new/random_game_textures/red_square128x128.png");  //загрузка красного квадрата в png

            this->_pix_chaged_cell = new Pixmap(*red_square);
            this->_pix_chaged_cell->setOffset(-red_square->width()/2, -red_square->height()/2);
            this->_pix_chaged_cell->setPos(temp.second * 128. + 128. + 64., 128. * temp.first + 64. + 128.);
            scene->addItem(this->_pix_chaged_cell);
        }
            break;

        case Bricks_V_:{
            QPixmap* QPix_ = new QPixmap();
            QPix_->load(":/new/random_game_textures/Bricks_V.jpg");
            Pixmap *Pix_ = new Pixmap(*QPix_);

            if(temp.first <= -1 || (temp.second <= -1) || (temp.first >= this->weight_of_map) || (temp.second >= this->height_of_map))
                return;

            this->vec_of_concr_texture[temp.first + 1][temp.second + 1] = Bricks_V_; //велосипед

            this->vec_of_pixmaps[temp.first + 1][temp.second + 1] = Pix_;
            this->vec_of_soderzimoe[temp.first + 1][temp.second + 1] = neprohod_object_;
            Pix_->setOffset(-QPix_->width()/2, -QPix_->height()/2);
            Pix_->setPos(128. * temp.second + 192., 192. + 128 * temp.first);
            this->scene->addItem(Pix_);
        }
            break;
        }
    }
    else{

        if(event->button() == Qt::RightButton)
            return;

        if(this->_pix_chaged_cell != nullptr){
            this->_pix_chaged_cell->hide();
            this->_pix_chaged_cell = nullptr;
        }
        auto temp = make_pair(this->view->mapToScene(event->windowPos().x(), event->windowPos().y()).x(), this->view->mapToScene(event->windowPos().x(), event->windowPos().y()).y());   //i dont now how it working, but it working!
        this->_vibrannaya_kletka = make_pair(floor(temp.second / 128), floor(temp.first / 128));

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
}

void nastr_game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        QMessageBox::StandardButton mb = QMessageBox::question(this, "Внимание!", "Вы уверены, что хотите выйти?", QMessageBox::Yes | QMessageBox::No);

        if(mb == QMessageBox::No)
            return;
        else
            this->close();
    }

    if(!this->is_game_started_now){           //место закладки не выбрано
        return; //не делаем ничего
    }
    else{           //место закладки выбрано
        if(!this->is_move_possible)
            return;

        //_list_of_pushed_buttons.push_back(event->key());        //это для двойных клавиш, но нужны ли они?


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
        }

        if(event->key() == Qt::Key_G || event->key() == 0x041f){

            this->generate_graphik_perems();

            auto graphik_window = new graphic_window(&(this->vec_of_soderzimoe), &(this->vec_of_fluct), this->vec_of_graphik_of_second_formanta, this->vec_of_graphik_of_trird_formanta, this);
            graphik_window->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
            graphik_window->setWindowTitle("Просмотр графика");
            graphik_window->showMaximized();
            graphik_window->setModal(true);
            //this->close();
            graphik_window->exec();
        }
    }
}
