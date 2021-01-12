#ifndef PASSWORD_DIALOG_H
#define PASSWORD_DIALOG_H

#include "list_of_types.h"

namespace Ui {
class password_dialog;
}

class password_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit password_dialog(QWidget *parent = nullptr);
    ~password_dialog();

    bool is_password_true = false;

private slots:
    void OK_clicked();
    void textChanged(const QString &text);

private:
    void keyPressEvent(QKeyEvent *event);
    QString now_line;
    QLineEdit *pass_line;
    string password = "yava123";

    Ui::password_dialog *ui;
};

#endif // PASSWORD_DIALOG_H
