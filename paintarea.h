#ifndef PAINTAREA_H
#define PAINTAREA_H
#define Y_LOWER_BOUND 200
#define Y_UPPER_BOUND 250

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QString>
#include <QPushButton>
#include <QMap>
#include <QPainter>
#include <QRect>
#include <QVector>
#include <QtMath>
#include <QBrush>
#include <QColor>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QFileDialog>
#include <QStack>
#include <QList>
#include "propertieswindow.h"

class PaintArea : public QWidget
{
    Q_OBJECT
public:
    explicit PaintArea(QWidget *parent = 0);
    ~PaintArea();
    void addnewEcu(QString p_strEcuName,QString p_strProtocolType);
    void removeEcu(QString p_strEcuName);
    void exportDesignToXML();
    void loadXMLToDesign();
    void m_DrawECUs(QPainter* p_pPainter);
    void createPopUpEditWindow(int index);
    int EcuAt(int p_iXCoordinate, int p_iYCoordinate);
    QString getLastEcuName();
    QString getSelectedEcuName();
    QList<QString> getAllECUNames();

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    int m_iSelectedIndex;
    QVector<QMap<QString,QString> > m_EcuVector;
    QMap<QString,QVector<int> > m_EcuDrawingMap;
    QStack<QMap<QString,QString> > m_UndoStack;
    QStack<int> m_RemovedIndexStack;
    bool m_LastActionIsDelete;
    PropertiesWindow* m_pEditParametersWindow;

signals:

public slots:
    void m_Undo();
    void m_updateECU(QString,QString,int);

};

#endif // PAINTAREA_H
