#ifndef PARAMETERSPOPUP_H
#define PARAMETERSPOPUP_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class ParametersPopUp : public QMainWindow
{
    Q_OBJECT
public:
    explicit ParametersPopUp(QWidget *parent = 0);
    void setECUNameAndType(QString p_strName, QString p_strType);

private:
    QLabel m_nameLabel;
    QLineEdit m_nameLineEdit;
    QLabel m_typeLabel;
    QLineEdit m_typeLineEdit;
    QPushButton* m_pOkButton;
    QPushButton* m_pCancelButton;

};

#endif // PARAMETERSPOPUP_H
