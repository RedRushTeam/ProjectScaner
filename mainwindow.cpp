#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setStyleSheet("background-color: lightGrey;");

    vbox = new QVBoxLayout(this);

    vbox->setContentsMargins(100, 15, 100, 50);
    vbox->setSpacing(20);

    QFont font_for_buttons("Times new roman", 14, QFont::Bold);

    QFont font_for_label("Times new roman", 24, QFont::ExtraBold);

    title = new QLabel("Project SCANER", this);
    title->setFont(font_for_buttons);
    title->setScaledContents(true);
    QPixmap* title_pixmap = new QPixmap();
    title_pixmap->load(":/new/random_game_textures/new/random_game_textures/proekt.png");  //загрузка красного квадрата в png
    title->setPixmap(*title_pixmap);
    title->resize(title_pixmap->size());
    title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    vbox->addWidget(title);

    start_with_rand = new QPushButton("Случайный режим", this);
    start_with_rand->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_with_rand->setCursor(QCursor(Qt::PointingHandCursor));
    start_with_rand->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 26px;     min-width: 10em;     padding: 6px}");
    start_with_rand->setFont(font_for_buttons);
    vbox->addWidget(start_with_rand);

    start_with_con = new QPushButton("Режим готовой конфигурации", this);
    start_with_con->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_with_con->setCursor(QCursor(Qt::PointingHandCursor));
    start_with_con->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 26px;     min-width: 10em;     padding: 6px}");
    start_with_con->setFont(font_for_buttons);
    vbox->addWidget(start_with_con);

    start_with_prep = new QPushButton("Режим с преподавателем", this);
    start_with_prep->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_with_prep->setCursor(QCursor(Qt::PointingHandCursor));
    start_with_prep->setStyleSheet("QPushButton {     background-color: rgba(0, 85, 0, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 26px;     min-width: 10em;     padding: 6px}");
    start_with_prep->setFont(font_for_buttons);
    vbox->addWidget(start_with_prep);

    start_with_settings = new QPushButton("Настраиваемый режим", this);
    start_with_settings->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    start_with_settings->setCursor(QCursor(Qt::PointingHandCursor));
    start_with_settings->setStyleSheet("QPushButton {     background-color: rgba(0, 85, 0, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 26px;     min-width: 10em;     padding: 6px}");
    start_with_settings->setFont(font_for_buttons);
    vbox->addWidget(start_with_settings);

    _pass = new QPushButton("Разблокировка режимов преподавателя", this);
    _pass->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    _pass->setCursor(QCursor(Qt::PointingHandCursor));
    _pass->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 26px;     min-width: 10em;     padding: 6px}");
    _pass->setFont(font_for_buttons);
    vbox->addWidget(_pass);

    help_ = new QPushButton("Помощь", this);
    help_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    help_->setCursor(QCursor(Qt::PointingHandCursor));
    help_->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 26px;     min-width: 10em;     padding: 6px}");
    help_->setFont(font_for_buttons);
    vbox->addWidget(help_);

    about_ = new QPushButton("О программе", this);
    about_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    about_->setCursor(QCursor(Qt::PointingHandCursor));
    about_->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;  font: bold 26px;   min-width: 10em;     padding: 6px}");
    about_->setFont(font_for_buttons);
    vbox->addWidget(about_);

    exit_ = new QPushButton("Выход", this);
    exit_->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    exit_->setCursor(QCursor(Qt::PointingHandCursor));
    exit_->setStyleSheet("QPushButton {      background-color: rgba(0, 0, 0, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 26px;     min-width: 10em;     padding: 6px}");
    exit_->setFont(font_for_buttons);
    vbox->addWidget(exit_);

    std::mt19937* gen = new std::mt19937(time(NULL));
    std::uniform_int_distribution<> uid(1, 5);
    int rint = uid(*gen);

    QFont font_for_QTextBrowser("Times new roman", 24, QFont::ExtraBold);
    QTextBrowser* tips = new QTextBrowser(this);
    tips->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    tips->setStyleSheet("QTextBrowser {min-width: 10em;     padding:12px;}");
    tips->setFont(font_for_QTextBrowser);
    tips->setFocus();
    tips->setFontItalic(true);
    tips->append("Совет дня: \n");
    switch (rint) {
    case 1:
        tips->append("Закладки могут быть не только в мебели, но и в стенах!");
        break;
    case 2:
        tips->append("Активные полупроводники находятся на частоте от 800, до 1200Мгц!");
        break;
    case 3:
        tips->append("Bluetooth находится на частоте от 2400, до 2500Мгц!");
        break;
    case 4:
        tips->append("Ничего не получается? Загляните во вкладку \"Помощь\"");
        break;
    case 5:
        tips->append("Видишь сигнал? И я не вижу, а он есть.");
        break;
    }
    vbox->addWidget(tips);

    connect(exit_, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(help_, &QPushButton::clicked, this, &MainWindow::open_help_window);
    connect(about_, &QPushButton::clicked, this, &MainWindow::open_about_window);
    connect(start_with_rand, &QPushButton::clicked, this, &MainWindow::open_game_window);
    connect(start_with_prep, &QPushButton::clicked, this, &MainWindow::open_prep_window);
    connect(start_with_settings, &QPushButton::clicked, this, &MainWindow::open_constr_window);
    connect(_pass, &QPushButton::clicked, this, &MainWindow::open_password_window);
    connect(start_with_con, &QPushButton::clicked, this, &MainWindow::open_con_window);

    this->setMinimumSize(720, 420);
    //this->showMaximized();
}

void MainWindow::mousePressEvent(QGraphicsSceneMouseEvent  *mEvent)
{
    //this->view->mapToScene(mEvent->windowPos().x(), mEvent->windowPos().y()).x(), this->view->mapToScene(mEvent->windowPos().x(), mEvent->windowPos().y()).y();
}

void MainWindow::open_help_window() const
{
    help* _help_window = new help();
    _help_window->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
    _help_window->setWindowTitle("Помощь");
    _help_window->setMinimumSize(720, 420);
    _help_window->show();
}

void MainWindow::open_about_window() const
{
    auto dialog_for_about = new about();
    dialog_for_about->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    dialog_for_about->setWindowTitle("О программе");
    dialog_for_about->setMinimumSize(480, 320);
    dialog_for_about->setMaximumSize(480, 320);
    dialog_for_about->setModal(true);
    dialog_for_about->exec();
}

void MainWindow::open_password_window()
{
    if(this->is_password_true)
        return;

    auto password_dialog_ = new password_dialog();
    password_dialog_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    password_dialog_->setWindowTitle("Вход в режим с преподавателем");
    password_dialog_->showFullScreen();
    password_dialog_->exec();

    if(password_dialog_->is_password_true){
        this->is_password_true = true;
        _pass->setStyleSheet("QPushButton {     background-color: rgba(0, 85, 0, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 26px;     min-width: 10em;     padding: 6px}");

        start_with_prep->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;  font: bold 26px;   min-width: 10em;     padding: 6px}");
        start_with_settings->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;  font: bold 26px;   min-width: 10em;     padding: 6px}");
    }

}

void MainWindow::open_game_window()
{
    auto change_size_ = new change_size(this);
    change_size_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    change_size_->setWindowTitle("Выберете размер карты");
    change_size_->showFullScreen();
    change_size_->is_this_will_be_random_game = true;
}

void MainWindow::open_prep_window()
{
    if(!this->is_password_true)   //TODO УБРАТЬ КОММЕНТЫ ТУТ, СЕЙЧАС ЭТО ПРОСТО ДЛЯ ОБЛЕГЧЕНИЯ ОТЛАДКИ КОДА
        return;

    auto change_size_ = new change_size(this);
    change_size_->setWindowTitle("Выберете размер карты");
    change_size_->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::Tool);
    change_size_->showFullScreen();
    change_size_->is_this_will_be_prep_game = true;
}

void MainWindow::open_con_window()
{
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

    int weight = std::count(instr.begin(), instr.end(), '}');

    string now_line = instr.substr(1, instr.find("}") - 1); //взятая "строка" целиком

    int height = std::count(now_line.begin(), now_line.end(), ']');

    in.close();

    auto con_game_ = new con_game(this, weight - 2, height - 2, full_fname);
    con_game_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
    con_game_->setWindowTitle("Режим с конфигурацией");
    con_game_->showFullScreen();
}

void MainWindow::open_constr_window()
{
    if(!this->is_password_true)
        return;

    auto change_size_ = new change_size(this);
    change_size_->setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint);
    change_size_->setWindowTitle("Выберете размер карты");
    change_size_->showFullScreen();
    change_size_->is_this_will_be_god_game = true;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
        this->close();
}
