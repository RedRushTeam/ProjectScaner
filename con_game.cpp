#include "con_game.h"
#include "ui_con_game.h"

con_game::con_game(QWidget *parent, int weight, int height, QString full_fname) : randome_game(parent, weight, height), full_fname(full_fname)
{
    this->vec_of_concr_texture.resize(this->height_of_map + 2);
    for(int i = 0; i < this->vec_of_soderzimoe.size(); ++i)
        this->vec_of_concr_texture[i].resize(this->weight_of_map + 2);

    this->download();

    for(int i = 0; i < this->vec_of_fluct.size(); ++i)
        fill(this->vec_of_fluct[i].begin(), this->vec_of_fluct[i].end(), make_pair(no_fluct_, 0));

    this->generate_flukt();

    if(_pix_chaged_cell != nullptr){
        this->scene->removeItem(_pix_chaged_cell);
        _pix_chaged_cell = nullptr;
    }

}

con_game::~con_game()
{
}

void con_game::clear_all()
{
    for(int i = 0; i < (this->height_of_map + 2); ++i)
        for(int j = 0; j < (this->weight_of_map + 2); ++j)
            if(!(i == 0 || (j == 0) || (i == this->height_of_map + 1) || (j == this->weight_of_map + 1))){

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

void con_game::download()
{
    this->clear_all();

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

    make_pair(stoi(instr.substr(instr.find("z") + 1, instr.find(":") - 1)) - 2, stoi(instr.substr(instr.find(":") + 1, instr.find(";") - 3)) - 2);

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

    int b1 = 0;
}
