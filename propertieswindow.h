#ifndef PROPERTIESWINDOW_H
#define PROPERTIESWINDOW_H

#include <QMainWindow>

namespace Ui {
class PropertiesWindow;
}

class PropertiesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PropertiesWindow(QWidget *parent = 0);
    ~PropertiesWindow();
    PropertiesWindow(QString p_strEcuName="",QString p_strProtocolType="",int p_iEcuIndex = -1,QWidget *parent = 0);

signals:
    void SubmitChanges(QString,QString,int);

public slots:

private:
    Ui::PropertiesWindow *ui;
    int m_iEcuIndex;

private slots:
    void on_pushButton_clicked();
};

#endif // PROPERTIESWINDOW_H
