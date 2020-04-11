#include "paintarea.h"
#include <QDebug>
#include <mainwindow.h>

PaintArea::PaintArea(QWidget *parent) :
    QWidget(parent)
{
    //qDebug()<<"PaintArea";
    m_iSelectedIndex = -1;
    m_EcuVector = QVector<QMap<QString,QString> >();
    m_EcuDrawingMap = QMap<QString,QVector<int> >();
    m_UndoStack = QStack<QMap<QString,QString> >();
    m_RemovedIndexStack = QStack<int>();

    m_LastActionIsDelete = true;

    this->setMinimumSize(2000,400);
}

PaintArea::~PaintArea()
{
    //qDebug()<<"~PaintArea";
    m_EcuVector.clear();
    m_EcuDrawingMap.clear();
    m_UndoStack.clear();
    m_RemovedIndexStack.clear();

    if(m_pEditParametersWindow != NULL)
        delete m_pEditParametersWindow;
}

void PaintArea::addnewEcu(QString p_strEcuName,QString p_strProtocolType)
{
    //qDebug()<<"addnewEcu";
    QMap<QString,QString> oEcuDefaultInfoMap;
    oEcuDefaultInfoMap["Name"] = p_strEcuName;
    oEcuDefaultInfoMap["Protocol_type"] = p_strProtocolType;
    m_EcuVector.append(oEcuDefaultInfoMap);
    m_LastActionIsDelete = false;
}

void PaintArea::removeEcu(QString p_strEcuName)
{
    //qDebug()<<"removeEcu";
    for(int i =0; i<m_EcuVector.length();i++)
    {
        if (m_EcuVector[i]["Name"]== p_strEcuName)
        {
            QMap<QString,QString> tempMap;
            tempMap = m_EcuVector[i];
            m_EcuVector.remove(i);
            m_UndoStack.push(tempMap);
            m_RemovedIndexStack.push(i);
            m_LastActionIsDelete = true;
            break;
        }
    }
}

QString PaintArea::getLastEcuName()
{

    //qDebug()<<"getLastEcuName";
    if (m_EcuVector.isEmpty())
        return "None";
    else
        return m_EcuVector[m_EcuVector.length()-1]["Name"];

}

QString PaintArea::getSelectedEcuName()
{
    //qDebug()<<"getSelectedEcuName";
    if (m_iSelectedIndex == -1)
        return "None";
    else
    {
        return m_EcuVector[m_iSelectedIndex]["Name"];
    }

}

QList<QString> PaintArea::getAllECUNames()
{
    //qDebug()<<"getAllECUNames";
    return m_EcuDrawingMap.keys();
}

void PaintArea::exportDesignToXML()
{
    //qDebug()<<"exportDesignToXML";
    QDomDocument outputXMLDomDocument("ECU_XML");
    QDomElement ecuTreeRootDomElement = outputXMLDomDocument.createElement("CAN_BUS");
    outputXMLDomDocument.appendChild(ecuTreeRootDomElement);
    for (int i =0; i<m_EcuVector.length();i++)
    {
        QDomElement ecuTagDomElement = outputXMLDomDocument.createElement("ECU");
        ecuTreeRootDomElement.appendChild(ecuTagDomElement);
        QMap<QString,QString>::iterator j ;
        for(j = m_EcuVector[i].begin(); j!= m_EcuVector[i].end(); j++)
        {
            QDomElement ecuInfoTagDomElement = outputXMLDomDocument.createElement(j.key());
            ecuTagDomElement.appendChild(ecuInfoTagDomElement);

            QDomText ecuInfoTagInnerText = outputXMLDomDocument.createTextNode(j.value());
            ecuInfoTagDomElement.appendChild(ecuInfoTagInnerText);
        }
    }
    QString xml = outputXMLDomDocument.toString();

    QString strOutputFileName = QFileDialog::getSaveFileName(this,
            tr("Save XML File"), "",
            tr("XMl File (*.xml);;All Files (*)"));

    QFile outputFile(strOutputFileName);
    outputFile.open(QIODevice::WriteOnly);
    outputFile.write(xml.toUtf8());
    outputFile.close();
}

void PaintArea::loadXMLToDesign()
{
    QDomDocument inputDoc("inputDoc");
    QString strInputFileName = QFileDialog::getOpenFileName(this,
                                  tr("Open XML File"), "",
                                  tr("XMl File (*.xml);;All Files (*)"));
    QFile inputFile(strInputFileName);
    if (!inputFile.open(QIODevice::ReadOnly))
        return;
    if (!inputDoc.setContent(&inputFile)) {
        inputFile.close();
        return;
    }
    inputFile.close();

    m_EcuVector = QVector<QMap<QString,QString> >();
    QDomElement documentElem = inputDoc.documentElement();

    QDomNode EcuTagNode = documentElem.firstChild();
    QMap<QString,QString> EcuParameterMap;
    QDomNode EcuParameterTagNode;
    while((!EcuTagNode.isNull()) && (EcuTagNode.nodeName()=="ECU"))
    {
        EcuParameterTagNode = EcuTagNode.firstChild();
        EcuParameterMap = QMap<QString,QString>();
        while (!EcuParameterTagNode.isNull())
        {
            EcuParameterMap[EcuParameterTagNode.nodeName()] = EcuParameterTagNode.firstChild().nodeValue();
            EcuParameterTagNode = EcuParameterTagNode.nextSibling();
        }
        m_EcuVector.append(EcuParameterMap);
        EcuTagNode = EcuTagNode.nextSibling();
    }
    update();
}

void PaintArea::m_DrawECUs(QPainter *p_pPainter)
{
    QMap<QString,QMap<QString,QString> >::iterator i;
    m_EcuDrawingMap = QMap<QString,QVector<int> >();
    int iStartx = 50;
    int iStarty = Y_LOWER_BOUND;
    int iMinSizex = 50;
    int iFinalWidth =0;
    int iFinalHeight =50;
    int iIncrementX = 0;
    QRect oEcuRect;
    QVector<int> EcuXCoordinates;
    for(int i =0; i<m_EcuVector.length();i++)
    {
        if (m_EcuVector[i]["Name"].length() > 5)
            iIncrementX = (m_EcuVector[i]["Name"].length()-5)*6;

        iFinalWidth = iMinSizex+iIncrementX;
        oEcuRect = QRect(iStartx,iStarty,iFinalWidth,iFinalHeight);
        if (m_iSelectedIndex == i)
        {
            p_pPainter->setBrush(QColor(42, 186, 192,100));
        }
        else
        {
            p_pPainter->setBrush(QColor(255,255,255));
        }
        p_pPainter->drawRect(oEcuRect);
        p_pPainter->drawText(oEcuRect,Qt::AlignCenter,m_EcuVector[i]["Name"]);

        //
        EcuXCoordinates = QVector<int>();
        EcuXCoordinates.append(i);
        EcuXCoordinates.append(iStartx);
        EcuXCoordinates.append(iStartx+iFinalWidth);
        m_EcuDrawingMap[m_EcuVector[i]["Name"]] = EcuXCoordinates;

        //link between ECU Block and the Can bus
        int iXStartOfLine = iStartx+iFinalWidth/2;
        int iYStartOfLine = iStarty+iFinalHeight;
        p_pPainter->drawLine(iXStartOfLine,iYStartOfLine,iXStartOfLine,iYStartOfLine+50);
        iStartx+=iFinalWidth+25;
        iIncrementX = 0;

    }
}

int PaintArea::EcuAt(int p_iXCoordinate, int p_iYCoordinate)
{
    if ((p_iYCoordinate < Y_LOWER_BOUND)||(p_iYCoordinate > Y_UPPER_BOUND))
    {
        return -1;
    }
    else
    {
        QMap<QString,QVector<int> >::iterator i;
        for(i = m_EcuDrawingMap.begin(); i != m_EcuDrawingMap.end(); i++)
        {
            if ((p_iXCoordinate > i.value()[1])&&(p_iXCoordinate < i.value()[2]))
            {
                return i.value()[0];
            }
        }

    }
    return -1;
}

void PaintArea::createPopUpEditWindow(int index)
{
    m_pEditParametersWindow = new PropertiesWindow(m_EcuVector[index]["Name"],m_EcuVector[index]["Protocol_type"],index,this);
    connect(m_pEditParametersWindow,SIGNAL(SubmitChanges(QString,QString,int)),this,SLOT(m_updateECU(QString,QString,int)));
    m_pEditParametersWindow->show();
}

void PaintArea::paintEvent(QPaintEvent *event)
{
    //qDebug()<<"paintEvent";
    QPainter *painter=new QPainter(this);
    QBrush pPainterBrush = QBrush(QColor(255,255,255));
    painter->setBrush(pPainterBrush);
    painter->drawLine(0,300,m_EcuVector.length()*70+100,300);
    painter->drawText(0,280,"CAN BUS");
    m_DrawECUs(painter);
    painter->end();
    //qDebug()<<"exit paintEvent";

}

void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        int index = EcuAt(event->pos().x(),event->pos().y());
        if (index != -1) {
            m_iSelectedIndex = index;
            update();
        }
        else
        {
            m_iSelectedIndex = -1;
            update();
        }
    }
}

void PaintArea::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        {
            int index = EcuAt(event->pos().x(),event->pos().y());
            if (index != -1) {
                createPopUpEditWindow(index);
                m_iSelectedIndex = index;
                update();
            }
            else
            {
                m_iSelectedIndex = -1;
                update();
            }
        }
}

void PaintArea::m_Undo()
{
    if ((m_LastActionIsDelete == true)&&(!m_RemovedIndexStack.isEmpty()))
    {
        m_EcuVector.insert(m_RemovedIndexStack.pop(),m_UndoStack.pop());
        m_LastActionIsDelete = false;
        update();
    }
    else if (m_LastActionIsDelete == false)
    {
        m_EcuVector.remove(m_EcuVector.length()-1);
        update();
    }

}

void PaintArea::m_updateECU(QString p_strEcuName,QString p_strProtocolType,int p_iEcuIndex)
{
    m_EcuVector[p_iEcuIndex]["Name"] = p_strEcuName;
    m_EcuVector[p_iEcuIndex]["Protocol_type"] = p_strProtocolType;
    update();
}
