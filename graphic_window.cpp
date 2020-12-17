#include "graphic_window.h"
#include "ui_graphic_window.h"

    //TODO переписать генерацию графиков(по частям), если в графике много переменных, он лагает

graphic_window::graphic_window(vector<vector<type_of_item>>* vec_of_soderzimoe, vector<vector<pair<type_of_fluctuation, float>>>* vec_of_fluct, vector<pair<float, float>>* vec_of_graphik_of_second_formanta, vector<pair<float, float>>* vec_of_graphik_of_third_formanta, QWidget *parent) :
    QDialog(parent), vec_of_soderzimoe(vec_of_soderzimoe), vec_of_fluct(vec_of_fluct), vec_of_graphik_of_second_formanta(vec_of_graphik_of_second_formanta), vec_of_graphik_of_third_formanta(vec_of_graphik_of_third_formanta),
    ui(new Ui::graphic_window)
{
    ui->setupUi(this);

    //window build
    QGridLayout *grid = new QGridLayout(this);
    grid->setVerticalSpacing(15);
    grid->setHorizontalSpacing(5);

    QFont font_for_buttons("Times new roman", 14, QFont::Bold);
    QFont font_for_label("Times new roman", 18, QFont::ExtraBold);

    QLabel *title_mashtab = new QLabel("Навигация по графику");
    title_mashtab->setFont(font_for_label);
    title_mashtab->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    title_mashtab->setAlignment(Qt::AlignCenter);

    QLabel *title_zoom = new QLabel("Изменение масштаба");
    title_zoom->setFont(font_for_label);
    title_zoom->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    title_zoom->setAlignment(Qt::AlignCenter);

    QPushButton *plus_50_k_masht = new QPushButton("+50 МГц к масштабу");
    plus_50_k_masht->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    plus_50_k_masht->setCursor(QCursor(Qt::PointingHandCursor));
    plus_50_k_masht->setFont(font_for_buttons);

    QPushButton *zoom_0_9_x = new QPushButton("Отдалить график по оси X");
    zoom_0_9_x->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    zoom_0_9_x->setCursor(QCursor(Qt::PointingHandCursor));
    zoom_0_9_x->setFont(font_for_buttons);

    QPushButton *zoom_1_1_x = new QPushButton("Приблизить график по оси X");
    zoom_1_1_x->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    zoom_1_1_x->setCursor(QCursor(Qt::PointingHandCursor));
    zoom_1_1_x->setFont(font_for_buttons);

    QPushButton *zoom_1_1_y = new QPushButton("Приблизить график по оси Y");
    zoom_1_1_y->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    zoom_1_1_y->setCursor(QCursor(Qt::PointingHandCursor));
    zoom_1_1_y->setFont(font_for_buttons);

    QPushButton *zoom_0_9_y = new QPushButton("Отдалить график по оси Y");
    zoom_0_9_y->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    zoom_0_9_y->setCursor(QCursor(Qt::PointingHandCursor));
    zoom_0_9_y->setFont(font_for_buttons);

    QPushButton *minus_50_k_masht = new QPushButton("-50 МГц к масштабу");
    minus_50_k_masht->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    minus_50_k_masht->setCursor(QCursor(Qt::PointingHandCursor));
    minus_50_k_masht->setFont(font_for_buttons);

    QPushButton *minus_100_k_masht = new QPushButton("-100 МГц к масштабу");
    minus_100_k_masht->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    minus_100_k_masht->setCursor(QCursor(Qt::PointingHandCursor));
    minus_100_k_masht->setFont(font_for_buttons);

    QPushButton *plus_100_k_masht = new QPushButton("+100 МГц к масштабу");
    plus_100_k_masht->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    plus_100_k_masht->setCursor(QCursor(Qt::PointingHandCursor));
    plus_100_k_masht->setFont(font_for_buttons);

    chartView_2th_formanta = new QChartView();
    chartView_2th_formanta->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    //chartView_3th_formanta = new QChartView();
    //chartView_3th_formanta->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    //chartView_2th_formanta->setRenderHint(QPainter::Antialiasing);
    //chartView_3th_formanta->setRenderHint(QPainter::Antialiasing);

    QChart *chart_2th_formanta = new QChart();
    chart_2th_formanta->setTitle("Вторая и третья форманты");
    chart_2th_formanta->setTitleFont(font_for_buttons);
    //chartView_2th_formanta->l

    this->series_2th_formanta = new QBarSeries(chart_2th_formanta);
    //this->series_3th_formanta = new QBarSeries(chart_2th_formanta);

    QBarSet *set = new QBarSet("№2 450-500 МГц");
    //добавление первых 50 отсчетов на график
    QBarSet *set_3th_formanta = new QBarSet("№3 450-500 МГц");

    QStringList categories;

    //выборка второй форманты
    for(int i = 0; i < 51; ++i){
        categories << QString::number(this->vec_of_graphik_of_second_formanta->operator[](i).first);
        *set << this->vec_of_graphik_of_second_formanta->operator[](i).second;
    }

    //добавление второй форманты на график
    series_2th_formanta->append(set);


    //выборка третьей форманты
    for(int i = 0; i < 51; ++i)
        *set_3th_formanta << this->vec_of_graphik_of_third_formanta->operator[](i).second;

    series_2th_formanta->append(set_3th_formanta);
        chart_2th_formanta->addSeries(series_2th_formanta);

    //добавление третьей форманты на график
    //series_3th_formanta->append(set_3th_formanta);
    //chart_2th_formanta->addSeries(series_3th_formanta);

    //настройка осей
    QFont font_for_axis("Times new roman", 8, QFont::Bold);
    axisX = new QBarCategoryAxis();
    axisX->setTitleFont(font_for_axis);
    axisX->append(categories);
    axisX->setRange("450", "500");
    this->_now_range_2th_command = make_pair(450, 500);
    chart_2th_formanta->setAxisX(axisX, series_2th_formanta);
    series_2th_formanta->attachAxis(axisX);

    this->axisY = new QValueAxis();
    this->axisY->setRange(0., 20.);
    _now_range_2th_command_y = make_pair(0., 20.);
    chart_2th_formanta->addAxis(this->axisY, Qt::AlignLeft);
    series_2th_formanta->attachAxis(this->axisY);

    //chart_2th_formanta->createDefaultAxes();
    chartView_2th_formanta->setChart(chart_2th_formanta);

    this->chartView_2th_formanta->chart()->update();

    grid->addWidget(chartView_2th_formanta, 0, 0, 8, 8);
    //grid->addWidget(chartView_3th_formanta, 0, 1, 5, 5);

    grid->addWidget(title_mashtab, 9, 0, 1, 4);
    grid->addWidget(plus_50_k_masht, 10, 0, 1, 2);
    grid->addWidget(minus_50_k_masht, 10, 2, 1, 2);
    grid->addWidget(plus_100_k_masht, 11, 0, 1, 2);
    grid->addWidget(minus_100_k_masht, 11, 2, 1, 2);

    grid->addWidget(title_zoom, 9, 4, 1, 4);
    grid->addWidget(zoom_0_9_x, 10, 4, 2, 1);
    grid->addWidget(zoom_1_1_x, 10, 5, 2, 1);
    grid->addWidget(zoom_0_9_y, 10, 6, 2, 1);
    grid->addWidget(zoom_1_1_y, 10, 7, 2, 1);


    connect(plus_50_k_masht, &QPushButton::clicked, this, &graphic_window::_50mgz_plused);
    connect(minus_50_k_masht, &QPushButton::clicked, this, &graphic_window::_50mgz_minused);
    connect(plus_100_k_masht, &QPushButton::clicked, this, &graphic_window::_100mgz_plused);
    connect(minus_100_k_masht, &QPushButton::clicked, this, &graphic_window::_100mgz_minused);

    connect(zoom_0_9_x, &QPushButton::clicked, this, &graphic_window::zoom_0_9_x_clicked);
    connect(zoom_1_1_x, &QPushButton::clicked, this, &graphic_window::zoom_1_1_x_clicked);
    connect(zoom_0_9_y, &QPushButton::clicked, this, &graphic_window::zoom_0_9_y_clicked);
    connect(zoom_1_1_y, &QPushButton::clicked, this, &graphic_window::zoom_1_1_y_clicked);
}

graphic_window::~graphic_window()
{
    delete ui;
}

void graphic_window::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_A || event->key() == 0x0424)
        this->_50mgz_minused();

    if(event->key() == Qt::Key_D || event->key() == 0x0412)
        this->_50mgz_plused();
}

void graphic_window::_50mgz_plused()    //done!
{
    if(this->_now_range_2th_command.second <= 5500){
        this->_now_range_2th_command = make_pair(this->_now_range_2th_command.first + 50, this->_now_range_2th_command.second + 50);
        //this->axisX->setRange(QString::number(this->_now_range_2th_command.first), QString::number(this->_now_range_2th_command.second));

        axisX->clear();
        series_2th_formanta->clear();

        QBarSet *set_3th_formanta = new QBarSet(QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
        QBarSet *set = new QBarSet(QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
        QStringList categories;

        for(int i = this->_now_range_2th_command.first; i <= this->_now_range_2th_command.second; ++i){
            categories << QString::number(this->vec_of_graphik_of_second_formanta->operator[](i - 450).first);
            *set_3th_formanta << this->vec_of_graphik_of_third_formanta->operator[](i - 450).second;
            *set << this->vec_of_graphik_of_second_formanta->operator[](i - 450).second;
        }

        series_2th_formanta->append(set);
        series_2th_formanta->append(set_3th_formanta);
        axisX->append(categories);
        axisX->setRange(QString::number(this->_now_range_2th_command.first), (QString::number(this->_now_range_2th_command.second)));

        this->chartView_2th_formanta->chart()->update();
    }
}

void graphic_window::_50mgz_minused()   //done!
{
    if(this->_now_range_2th_command.first >= 500){
        this->_now_range_2th_command = make_pair(this->_now_range_2th_command.first - 50, this->_now_range_2th_command.second - 50);
        //this->axisX->setRange(QString::number(this->_now_range_2th_command.first), QString::number(this->_now_range_2th_command.second));

        axisX->clear();
        series_2th_formanta->clear();

        QBarSet *set_3th_formanta = new QBarSet(QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
        QBarSet *set = new QBarSet(QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
        QStringList categories;

        for(int i = this->_now_range_2th_command.first; i <= this->_now_range_2th_command.second; ++i){
            categories << QString::number(this->vec_of_graphik_of_second_formanta->operator[](i - 450).first);
            *set_3th_formanta << this->vec_of_graphik_of_third_formanta->operator[](i - 450).second;
            *set << this->vec_of_graphik_of_second_formanta->operator[](i - 450).second;
        }

        series_2th_formanta->append(set);
        series_2th_formanta->append(set_3th_formanta);
        axisX->append(categories);
        axisX->setRange(QString::number(this->_now_range_2th_command.first), (QString::number(this->_now_range_2th_command.second)));

        this->chartView_2th_formanta->chart()->update();
    }
}

void graphic_window::_100mgz_plused()
{
    if(this->_now_range_2th_command.second <= 5450){
        if(this->_now_range_2th_command.second - this->_now_range_2th_command.first < 100)
            this->_now_range_2th_command = make_pair(this->_now_range_2th_command.first, this->_now_range_2th_command.first + 100);

        this->_now_range_2th_command = make_pair(this->_now_range_2th_command.first + 100, this->_now_range_2th_command.second + 100);
        //this->axisX->setRange(QString::number(this->_now_range_2th_command.first), QString::number(this->_now_range_2th_command.second));

        axisX->clear();
        series_2th_formanta->clear();

        QBarSet *set_3th_formanta = new QBarSet(QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
        QBarSet *set = new QBarSet(QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
        QStringList categories;

        for(int i = this->_now_range_2th_command.first; i <= this->_now_range_2th_command.second; ++i){
            categories << QString::number(this->vec_of_graphik_of_second_formanta->operator[](i - 450).first);
            *set_3th_formanta << this->vec_of_graphik_of_third_formanta->operator[](i - 450).second;
            *set << this->vec_of_graphik_of_second_formanta->operator[](i - 450).second;
        }

        series_2th_formanta->append(set);
        series_2th_formanta->append(set_3th_formanta);
        axisX->append(categories);
        axisX->setRange(QString::number(this->_now_range_2th_command.first), (QString::number(this->_now_range_2th_command.second)));

        this->chartView_2th_formanta->chart()->update();
    }
}

void graphic_window::_100mgz_minused()
{
    if(this->_now_range_2th_command.first >= 550){
        if(this->_now_range_2th_command.second - this->_now_range_2th_command.first < 100)
            this->_now_range_2th_command = make_pair(this->_now_range_2th_command.first, this->_now_range_2th_command.first + 100);

        this->_now_range_2th_command = make_pair(this->_now_range_2th_command.first - 100, this->_now_range_2th_command.second - 100);
        //this->axisX->setRange(QString::number(this->_now_range_2th_command.first), QString::number(this->_now_range_2th_command.second));

        axisX->clear();
        series_2th_formanta->clear();

        QBarSet *set_3th_formanta = new QBarSet(QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
        QBarSet *set = new QBarSet(QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
        QStringList categories;

        for(int i = this->_now_range_2th_command.first; i <= this->_now_range_2th_command.second; ++i){
            categories << QString::number(this->vec_of_graphik_of_second_formanta->operator[](i - 450).first);
            *set << this->vec_of_graphik_of_second_formanta->operator[](i - 450).second;
            *set_3th_formanta << this->vec_of_graphik_of_third_formanta->operator[](i - 450).second;
        }

        series_2th_formanta->append(set);
        series_2th_formanta->append(set_3th_formanta);
        axisX->append(categories);
        axisX->setRange(QString::number(this->_now_range_2th_command.first), (QString::number(this->_now_range_2th_command.second)));

        this->chartView_2th_formanta->chart()->update();
    }
}

void graphic_window::zoom_0_9_x_clicked()
{
    int now_size_of_range = this->_now_range_2th_command.second - this->_now_range_2th_command.first;
    if(this->_now_range_2th_command.second - this->_now_range_2th_command.first >= 200 || ((this->_now_range_2th_command.first + now_size_of_range * 1.02) > 5550))
        return;

    this->_now_range_2th_command.second = this->_now_range_2th_command.first + now_size_of_range * 1.02;

    axisX->clear();
    series_2th_formanta->clear();

    QBarSet *set_3th_formanta = new QBarSet("№3 " + QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
    QBarSet *set = new QBarSet("№2 " + QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
    QStringList categories;

    for(int i = this->_now_range_2th_command.first; i <= this->_now_range_2th_command.second; ++i){
        categories << QString::number(this->vec_of_graphik_of_second_formanta->operator[](i - 450).first);
        *set << this->vec_of_graphik_of_second_formanta->operator[](i - 450).second;
        *set_3th_formanta << this->vec_of_graphik_of_third_formanta->operator[](i - 450).second;
    }

    series_2th_formanta->append(set);
    series_2th_formanta->append(set_3th_formanta);
    axisX->append(categories);
    axisX->setRange(QString::number(this->_now_range_2th_command.first), (QString::number(this->_now_range_2th_command.second)));

    this->chartView_2th_formanta->chart()->update();
}

void graphic_window::zoom_1_1_x_clicked()
{
    if(this->_now_range_2th_command.second - this->_now_range_2th_command.first <= 50)
        return;

    int now_size_of_range = this->_now_range_2th_command.second - this->_now_range_2th_command.first;
    this->_now_range_2th_command.second = this->_now_range_2th_command.first + now_size_of_range * 0.98;

    axisX->clear();
    series_2th_formanta->clear();

    QBarSet *set_3th_formanta = new QBarSet(QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
    QBarSet *set = new QBarSet(QString::number(this->_now_range_2th_command.first) + "-" + QString::number(this->_now_range_2th_command.second) + " МГц");
    QStringList categories;

    for(int i = this->_now_range_2th_command.first; i <= this->_now_range_2th_command.second; ++i){
        categories << QString::number(this->vec_of_graphik_of_second_formanta->operator[](i - 450).first);
        *set << this->vec_of_graphik_of_second_formanta->operator[](i - 450).second;
        *set_3th_formanta << this->vec_of_graphik_of_third_formanta->operator[](i - 450).second;
    }

    series_2th_formanta->append(set);
    series_2th_formanta->append(set_3th_formanta);
    axisX->append(categories);
    axisX->setRange(QString::number(this->_now_range_2th_command.first), (QString::number(this->_now_range_2th_command.second)));

    this->chartView_2th_formanta->chart()->update();
}

void graphic_window::zoom_0_9_y_clicked()
{
    if(_now_range_2th_command_y.second >= 55)
        return;

    this->axisY->setRange(0., _now_range_2th_command_y.second * 1.05);
    _now_range_2th_command_y = make_pair(0., _now_range_2th_command_y.second * 1.05);
}

void graphic_window::zoom_1_1_y_clicked()
{
    if(_now_range_2th_command_y.second <= 18)
        return;

    this->axisY->setRange(0., _now_range_2th_command_y.second * 0.95);
    _now_range_2th_command_y = make_pair(0., _now_range_2th_command_y.second * 0.95);
}
