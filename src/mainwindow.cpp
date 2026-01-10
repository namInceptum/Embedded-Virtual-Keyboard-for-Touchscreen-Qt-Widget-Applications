#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnOk, SIGNAL(clicked()),this,SLOT(on_btnOk_Clicked()));
    connect(ui->btnCancel, SIGNAL(clicked()),this,SLOT(on_btnCancel_Clicked()));


     // setup for virtual keyboard to enter wifi-password
    keyboard = new widgetKeyBoard(true, this, false, ui->keyboard_frame);
    keyboard->enableSwitchingEcho(true);
    keyboard->createKeyboard();
    keyboard->show(this);
    connect(keyboard,SIGNAL(keySignalReceived()),this,SLOT(returnWidgetSignalReceived()));
    externalLineEditPointer = nullptr;
    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOk_Clicked()
{
    qDebug() << "Ok button clicked";
    // processing of the QLineEdit text:
    qDebug() << "LineEdit 1: " << ui->lineEdit->text();
    qDebug() << "LineEdit 2: " << ui->lineEdit_2->text();
}

void MainWindow::on_btnCancel_Clicked()
{
    qDebug() << "Cancel button clicked";
}

// virtual keyboard setup of QLineEdit on which the textinput is taken
void MainWindow::returnWidgetSignalReceived()
{
   QLineEdit* currentQLineEdit =  this->keyboard->currentTextBox(); // getNextTextbox
   QString currentText = currentQLineEdit->text();
   if(externalLineEditPointer != nullptr)
   {
        this->externalLineEditPointer->setText(currentText);
   }
}


void MainWindow::setExternalLineEdit(QLineEdit* myExtLineEdit)
{
    externalLineEditPointer = myExtLineEdit;
    QLineEdit* currentQLineEdit = keyboard->currentTextBox();
    currentQLineEdit->setText((myExtLineEdit->text()));
}

