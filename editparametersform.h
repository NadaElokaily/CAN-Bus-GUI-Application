#ifndef EDITPARAMETERSFORM_H
#define EDITPARAMETERSFORM_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class EditParametersForm;
}

class EditParametersForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditParametersForm(QWidget *parent = 0);
    ~EditParametersForm();
    void setECUNameAndType(QString p_strName, QString p_strType);

private:
    Ui::EditParametersForm *ui;
    QLabel m_nameLabel;
    QLineEdit m_nameLineEdit;
    QLabel m_typeLabel;
    QLineEdit m_typeLineEdit;
    QPushButton* m_pOkButton;
    QPushButton* m_pCancelButton;
};

#endif // EDITPARAMETERSFORM_H
