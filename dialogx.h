#ifndef DIALOGX_H
#define DIALOGX_H

#include <QDialog>

namespace Ui {
class Dialogx;
}

class Dialogx : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogx(QWidget *parent = 0);
    ~Dialogx();

private:
    Ui::Dialogx *ui;
};

#endif // DIALOGX_H
