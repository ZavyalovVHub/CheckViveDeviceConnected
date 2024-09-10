#ifndef DIALOGCHECKVR_H
#define DIALOGCHECKVR_H

#include <QDialog>

namespace Ui {
class DialogCheckVR;
}

class DialogCheckVR : public QDialog
{
    Q_OBJECT

public:
    explicit DialogCheckVR(QWidget *parent = nullptr);
    ~DialogCheckVR();
    bool checkVR();

private slots:
    void push_button_clicked();

private:
    Ui::DialogCheckVR *ui;
};

#endif // DIALOGCHECKVR_H
