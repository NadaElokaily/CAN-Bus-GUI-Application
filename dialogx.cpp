#include "dialogx.h"
#include "ui_dialogx.h"

Dialogx::Dialogx(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogx)
{
    ui->setupUi(this);
}

Dialogx::~Dialogx()
{
    delete ui;
}
