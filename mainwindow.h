#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QInputDialog>
#include <QIcon>
#include <QSize>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QScrollArea>
#include <QMessageBox>
#include <QShortcut>
#include "paintarea.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void resizeEvent(QResizeEvent*);
    void m_sAddNewECU();
    void m_sRemoveECU();
    void m_sSaveProgress();
    void m_sLoadInfo();

private:
    Ui::MainWindow *ui;
    QPushButton* m_pAddEcuButton;
    QPushButton* m_pRemoveEcuButton;
    QPushButton* m_pSaveButton;
    QPushButton* m_pLoadButton;
    QGroupBox* m_pButtonsGroupBox;
    PaintArea * m_oEcuViewPaintArea;
    QScrollArea * m_pEcuScrollArea;
    bool m_bEcuSelected;
    int m_iEcuCount;
    QShortcut *m_pLoadFile;
    QShortcut *m_pSaveFile;
    QShortcut *m_pUndo;

};

#endif // MAINWINDOW_H
