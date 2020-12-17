#include "password_dialog.h"
#include "ui_password_dialog.h"

password_dialog::password_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::password_dialog)
{
    ui->setupUi(this);

    QVBoxLayout *hbox = new QVBoxLayout(this);  //todo сделать красиво

    hbox->setContentsMargins(50, 5, 50, 50);
    hbox->setSpacing(15);

    QFont font_for_buttons("Times new roman", 18, QFont::Bold);

    QFont font_for_label("Times new roman", 24, QFont::ExtraBold);

    QLabel *title = new QLabel("Введите пароль:", this);
    title->setFont(font_for_buttons);
    title->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    hbox->addWidget(title);

    //QRegExp letters("/^[а-яё -]+$/i");
    //QRegExpValidator m_card_validator;
    //m_card_validator.setRegExp(letters);

    this->pass_line = new QLineEdit();
    this->pass_line->setFont(font_for_label);
    this->pass_line->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    this->pass_line->setStyleSheet("QLineEdit {    border: 2px solid gray;    border-radius: 10px;    padding: 0 8px;    background:  rgba(255, 255, 0, 120);    selection-background-color: rgba(255, 255, 0, 120);    }");
    this->pass_line->setFont(font_for_buttons);
    //this->pass_line->setValidator(new QRegExpValidator(letters));   //TODO validator
    hbox->addWidget(pass_line);

    QPushButton *OK = new QPushButton("ОК", this);
    OK->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    OK->setCursor(QCursor(Qt::PointingHandCursor));
    OK->setStyleSheet("QPushButton {     background-color: rgba(170, 85, 255, 100);     border-style: outset;     border-width: 2px;	border-radius: 10px;     border-color: rgb(85, 0, 127);     min-width: 10em;     padding:12px;} QPushButton:hover {     background-color:rgba(170, 0, 0, 100);     border-style: outset;     border-width: 2px;     border-radius: 10px;     font: bold 16px;     min-width: 10em;     padding: 6px}");
    OK->setFont(font_for_buttons);
    hbox->addWidget(OK);

    connect(OK, &QPushButton::clicked, this, &password_dialog::OK_clicked);
    connect(pass_line, &QLineEdit::textChanged, this, &password_dialog::textChanged);
}

password_dialog::~password_dialog()
{
    delete ui;
}

void password_dialog::OK_clicked()  //todo добавить regex
{
    QString shit;
    for(auto obj : this->now_line)
        if(obj != '*')
            shit.push_back(obj);

    if(shit.toStdString() == this->password){
        this->is_password_true = true;
        this->close();
    }
    else
        QMessageBox::warning(this, "Внимание", "Неверный пароль, попробуйте еще раз.");
}

void password_dialog::textChanged(const QString &text)
{
    QString line = this->pass_line->text();
    this->now_line.push_back(line[line.size() - 1]);
    int index = line.size() - 1;

    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    timer->setInterval(50);

    connect(timer, &QTimer::timeout, [this,timer,index]() {
        QString line = this->pass_line->text();
        line.replace(index, 1, '*');
        this->pass_line->setText(line);
        timer->deleteLater();
    });

    timer->start();
}
