#include "prepod_game.h"

prepod_game::prepod_game()
{

}

prepod_game::prepod_game(QWidget *parent, int weight, int height) : randome_game(parent, weight, height){

    QMessageBox::warning(this, "Внимание", "Выберете непустую клетку и нажмите кнопку \"ОК\"");

    this->_coordinate_of_zakladka = make_pair(-1, -1);

    QFont font_for_buttons("Times new roman", 18, QFont::Bold);

    //TODO сделать эту кнопочку поменьше
    start_with_rand = new QPushButton("ОК", this);
    start_with_rand->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_with_rand->setCursor(QCursor(Qt::PointingHandCursor));
    start_with_rand->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
    start_with_rand->setFont(font_for_buttons);

    this->hbox->addWidget(start_with_rand);

    connect(start_with_rand, &QPushButton::clicked, this, &prepod_game::ok_pushed);
}

void prepod_game::ok_pushed()
{
    if(this->_coordinate_of_zakladka == make_pair(-1, -1))
        QMessageBox::warning(this, "Внимание", "Для начала выберете непустую клетку!");
    else{
        this->hbox->removeWidget(this->start_with_rand);
        this->start_with_rand->hide();
    }

    this->_pix_chaged_cell->hide();
    this->_pix_chaged_cell = nullptr;

    for(int i = 0; i < this->vec_of_fluct.size(); ++i)
        fill(this->vec_of_fluct[i].begin(), this->vec_of_fluct[i].end(), make_pair(no_fluct_, 0));

    this->generate_flukt();
}

void prepod_game::mousePressEvent(QMouseEvent *event)
{
    if(this->_coordinate_of_zakladka == make_pair(-1, -1)){
        if(this->_pix_chaged_cell != nullptr){
            this->_pix_chaged_cell->hide();
            this->_pix_chaged_cell = nullptr;
        }

        auto temp =  make_pair(this->view->mapToScene(event->windowPos().x(), event->windowPos().y()).x(), this->view->mapToScene(event->windowPos().x(), event->windowPos().y()).y());   //i dont now how it working, but it working!
        this->_coordinate_of_zakladka = make_pair(floor(temp.second / 128), floor(temp.first / 128));

        if(temp.first - 1 < -1 || (temp.second - 1 < -1) || (temp.first - 1 > this->weight_of_map) || (temp.second - 1 > this->height_of_map))
            return;

        if(this->vec_of_soderzimoe[this->_coordinate_of_zakladka.first][this->_coordinate_of_zakladka.second] == empty_ || (this->vec_of_soderzimoe[this->_coordinate_of_zakladka.first][this->_coordinate_of_zakladka.second] == GG_)){
            this->_coordinate_of_zakladka = make_pair(-1, -1);
            return;
        }

        QPixmap* red_square = new QPixmap();
        red_square->load(":/new/random_game_textures/new/random_game_textures/red_square128x128.png");  //загрузка красного квадрата в png

        this->_pix_chaged_cell = new Pixmap(*red_square);
        this->_pix_chaged_cell->setOffset(-red_square->width()/2, -red_square->height()/2);
        this->_pix_chaged_cell->setPos(this->_vibrannaya_kletka.second * 128. + 64., 128. * this->_vibrannaya_kletka.first + 64.);
        scene->addItem(this->_pix_chaged_cell);

       return;
    }
    else{

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

void prepod_game::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape){
        QMessageBox::StandardButton mb = QMessageBox::question(this, "Внимание!", "Вы уверены, что хотите выйти?", QMessageBox::Yes | QMessageBox::No);

        if(mb == QMessageBox::No)
            return;
        else
            this->close();
    }

    if(this->_coordinate_of_zakladka == make_pair(-1, -1)){           //место закладки не выбрано
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
