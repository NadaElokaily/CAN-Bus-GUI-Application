#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

//QPushButton createButtonWithNameAndIcon(QString p_str)
//{

//}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_iEcuCount = 0;
    m_bEcuSelected = false;
    m_pLoadFile = new QShortcut(QKeySequence(tr("Ctrl+O", "File|Open")),
                             this);
    m_pSaveFile = new QShortcut(QKeySequence(tr("Ctrl+S", "File|Save")),
                             this);
    m_pUndo = new QShortcut(QKeySequence(tr("Ctrl+Z")),
            this);
    this->setMinimumSize(700,600);
    this->setWindowTitle("CAN BUS");

    m_pAddEcuButton = new QPushButton(this);
    m_pAddEcuButton->setIcon(QIcon(":/AddEcuIcon"));
    m_pAddEcuButton->setIconSize(QSize(230,80));
    m_pAddEcuButton->setFixedSize(233,83);
    m_pAddEcuButton->setToolTip("Add New ECU");

    m_pRemoveEcuButton= new QPushButton(this);
    m_pRemoveEcuButton->setIcon(QIcon(":/RemoveEcuIcon"));
    m_pRemoveEcuButton->setIconSize(QSize(230,80));
    m_pRemoveEcuButton->setFixedSize(233,83);
    m_pRemoveEcuButton->setToolTip("Remove ECU");

    m_pSaveButton= new QPushButton(this);
    m_pSaveButton->setIcon(QIcon(":/saveIcon"));
    m_pSaveButton->setIconSize(QSize(80,80));
    m_pSaveButton->setFixedSize(80,83);
    m_pSaveButton->setToolTip("Save Design");

    m_pLoadButton = new QPushButton(this);
    m_pLoadButton->setIcon(QIcon(":/loadIcon"));
    m_pLoadButton->setIconSize(QSize(80,80));
    m_pLoadButton->setFixedSize(80,83);
    m_pLoadButton->setToolTip("Load Existing Design");


    QHBoxLayout *pButtonsLayout = new QHBoxLayout;
    pButtonsLayout->addWidget(m_pAddEcuButton);
    pButtonsLayout->addWidget(m_pRemoveEcuButton);
    pButtonsLayout->addWidget(m_pSaveButton);
    pButtonsLayout->addWidget(m_pLoadButton);

    m_pButtonsGroupBox = new QGroupBox(this);
    m_pButtonsGroupBox->setMinimumSize(700,105);
    m_pButtonsGroupBox->setStyleSheet("background-color: #343633");
    m_pButtonsGroupBox->setLayout(pButtonsLayout);

    m_pEcuScrollArea = new QScrollArea(this);
    m_pEcuScrollArea->setWidgetResizable(true);
    m_pEcuScrollArea->setGeometry(0,105,700,500);

    m_oEcuViewPaintArea = new PaintArea(m_pEcuScrollArea);
    m_pEcuScrollArea->setWidget(m_oEcuViewPaintArea);

    connect(m_pAddEcuButton,SIGNAL(clicked()),this,SLOT(m_sAddNewECU()));
    connect(m_pRemoveEcuButton,SIGNAL(clicked()),this,SLOT(m_sRemoveECU()));
    connect(m_pSaveButton,SIGNAL(clicked()),this,SLOT(m_sSaveProgress()));
    connect(m_pLoadButton,SIGNAL(clicked()),this,SLOT(m_sLoadInfo()));
    connect(m_pLoadFile,SIGNAL(activated()),this, SLOT(m_sLoadInfo()));
    connect(m_pSaveFile,SIGNAL(activated()),this, SLOT(m_sSaveProgress()));
    connect(m_pUndo,SIGNAL(activated()),m_oEcuViewPaintArea,SLOT(m_Undo()));
}

MainWindow::~MainWindow()
{
    delete ui;
    if(m_pAddEcuButton != NULL)
        delete m_pAddEcuButton;

    if(m_pRemoveEcuButton != NULL)
        delete m_pRemoveEcuButton;

    if(m_pSaveButton != NULL)
        delete m_pSaveButton;

    if(m_pLoadButton != NULL)
        delete m_pLoadButton;

    if(m_pButtonsGroupBox != NULL)
        delete m_pButtonsGroupBox;

    if(m_pEcuScrollArea != NULL)
        delete m_pEcuScrollArea;

    if(m_pLoadFile != NULL)
        delete m_pLoadFile;

    if(m_pSaveFile != NULL)
        delete m_pSaveFile;

    if(m_pUndo != NULL)
        delete m_pUndo;

}

void MainWindow::resizeEvent(QResizeEvent* )
{
    m_pEcuScrollArea->resize(this->width(),500);
    m_pButtonsGroupBox->resize(this->width(),105);
}

void MainWindow::m_sAddNewECU()
{
    QString strEcuName = "ECU "+QString::number(m_iEcuCount);
    QString strDefaultProtocol = "CAN";
    bool ok;
    QString strFinalEcuName = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Please Enter ECU Name"), QLineEdit::Normal,
                                            strEcuName, &ok);
    if (strFinalEcuName == ("ECU "+QString::number(m_iEcuCount)))
        m_iEcuCount++;

    strEcuName = strFinalEcuName;
    strEcuName.replace( " ", "" );
    if(strEcuName != "")
    {
        m_oEcuViewPaintArea->addnewEcu(strFinalEcuName,strDefaultProtocol);
        m_oEcuViewPaintArea->update();
    }

}

void MainWindow::m_sRemoveECU()
{
    QString strSelectedEcuName = m_oEcuViewPaintArea->getSelectedEcuName();
    if(strSelectedEcuName=="None")
    {
        bool ok;
        QStringList items = m_oEcuViewPaintArea->getAllECUNames();

        QString strEcuName = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                                            tr("ECUs: "), items, 0, false, &ok);
            if(ok)
            {
                m_oEcuViewPaintArea->removeEcu(strEcuName);
                m_oEcuViewPaintArea->update();
            }
        }
    else
    {
        m_oEcuViewPaintArea->removeEcu(strSelectedEcuName);
        m_oEcuViewPaintArea->update();
    }
}

void MainWindow::m_sSaveProgress()
{
    m_oEcuViewPaintArea->exportDesignToXML();
}

void MainWindow::m_sLoadInfo()
{
    if (!m_oEcuViewPaintArea->getAllECUNames().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Save)
        {
            m_oEcuViewPaintArea->exportDesignToXML();
            m_oEcuViewPaintArea->loadXMLToDesign();
        }
        else if(ret == QMessageBox::Discard)
        {
            m_oEcuViewPaintArea->loadXMLToDesign();
        }
    }
    else
    {
        m_oEcuViewPaintArea->loadXMLToDesign();
    }
}
