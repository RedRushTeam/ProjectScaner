#ifndef GRAPHIC_WINDOW_H
#define GRAPHIC_WINDOW_H
#pragma once

#include "list_of_types.h"

enum type_of_item{empty_, neprohod_object_, prohod_object_, GG_};
enum type_of_fluctuation{no_fluct_, inactive_semiconductors_, active_semiconductors_, bluetooth_, _5g_, _4g_, _3g_, GPS_, radio_, GLONASS_};

using namespace std;

namespace Ui {
class graphic_window;
}

class graphic_window : public QDialog
{
    Q_OBJECT

public:
    explicit graphic_window(vector<vector<type_of_item>>* vec_of_soderzimoe, vector<vector<pair<type_of_fluctuation, float>>>* vec_of_fluct, vector<pair<float, float>>* vec_of_graphik, QWidget *parent = nullptr);
    ~graphic_window();

    vector<vector<type_of_item>>* vec_of_soderzimoe;
    vector<vector<pair<type_of_fluctuation, float>>>* vec_of_fluct;
    vector<pair<float, float>>* vec_of_graphik;
    void keyPressEvent(QKeyEvent *event);

private slots:
    void _50mgz_plused();
    void _50mgz_minused();
    void _100mgz_plused();
    void _100mgz_minused();
    void zoom_0_9_x_clicked();
    void zoom_1_1_x_clicked();
    void zoom_0_9_y_clicked();
    void zoom_1_1_y_clicked();

private:
    QBarSeries *series_2th_formanta;
    pair<int, int>  _now_range_2th_command = make_pair(-1, -1);
    pair<float, float>  _now_range_2th_command_y = make_pair(-1, -1);
    QBarCategoryAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;
    QChartView *chartView_2th_formanta = nullptr;
    QChartView *chartView_3th_formanta = nullptr;
    Ui::graphic_window *ui;
};

#endif // GRAPHIC_WINDOW_H
