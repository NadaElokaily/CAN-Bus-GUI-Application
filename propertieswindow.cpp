#include "propertieswindow.h"
#include "ui_propertieswindow.h"

PropertiesWindow::PropertiesWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::PropertiesWindow)
{
    ui->setupUi(this);
    m_iEcuIndex = -1;
}
PropertiesWindow::~PropertiesWindow()
{
    delete ui;
}

PropertiesWindow::PropertiesWindow(QString p_strEcuName,QString p_strProtocolType,int p_iEcuIndex,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PropertiesWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText(p_strEcuName);

    //protocol types combobox items
    QComboBox* ProtocolTypesComboBox = ui->comboBox ;
    ProtocolTypesComboBox->addItem(tr("CAN"));
    ProtocolTypesComboBox->addItem(tr("TTCAN"));
    ProtocolTypesComboBox->addItem(tr("CANFD"));

    //get current protocol type
    int icurrentIndex = 0;
    if(p_strProtocolType=="CAN")
        icurrentIndex = 0;
    else if(p_strProtocolType=="TTCAN")
        icurrentIndex = 1;
    else if(p_strProtocolType=="CANFD")
        icurrentIndex = 2;

    //view current protocol type
    ProtocolTypesComboBox->setCurrentIndex(icurrentIndex);
    m_iEcuIndex = p_iEcuIndex;

}

void PropertiesWindow::on_pushButton_clicked()
{
    emit SubmitChanges(ui->lineEdit->text(),ui->comboBox->currentText(),m_iEcuIndex);
    this->close();
}
