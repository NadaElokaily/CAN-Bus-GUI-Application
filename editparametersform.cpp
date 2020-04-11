#include "editparametersform.h"
#include "ui_editparametersform.h"

EditParametersForm::EditParametersForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditParametersForm)
{
    ui->setupUi(this);
}

EditParametersForm::~EditParametersForm()
{
    delete ui;
}
