#include "parameterspopup.h"

#include <QGroupBox>
#include <QHBoxLayout>

ParametersPopUp::ParametersPopUp(QWidget *parent) :
    QMainWindow(parent)
{
    m_nameLabel = QLabel();
//    m_nameLabel.setText("ECU Name:");
//    m_nameLineEdit = QLineEdit();

//    m_typeLabel = QLabel();
//    m_typeLabel.setText("Protocol type:");
//    m_typeLineEdit = QLineEdit();

//    m_pOkButton = new QPushButton(this);
//    m_pCancelButton = new QPushButton(this);

//    QHBoxLayout* pbuttonsLayout = new QHBoxLayout();
//    pbuttonsLayout->addWidget(m_pOkButton);
//    pbuttonsLayout->addWidget(m_pCancelButton);

//    QGroupBox* pbuttonsGroupBox = new QGroupBox(this);
//    pbuttonsGroupBox->setLayout(pbuttonsLayout);

//    QVBoxLayout


}

void ParametersPopUp::setECUNameAndType(QString p_strName, QString p_strType)
{
//    m_nameLineEdit.setText(p_strName);
//    m_typeLineEdit.setText(p_strType);
}


