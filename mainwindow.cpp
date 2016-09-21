#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPort>
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  ui->label1->setStyleSheet("QTextEdit { background-color: rgb(104, 249, 79); }");
  ui->label2->setStyleSheet("QTextEdit { background-color: rgb(249, 112, 91); }");
  ui->pushButton->setStyleSheet("QPushButton { background-color: rgb(10, 141, 16); }");
  ui->pushButton_2->setStyleSheet("QPushButton { background-color: rgb(200, 27, 2); }");
  ui->centralWidget->setStyleSheet("QWidget { background-color: rgb(200, 188, 250); }");
  ui->text1->setStyleSheet("QTextEdit { background-color: rgb(196, 254, 171); }");
  ui->text2->setStyleSheet("QTextEdit { background-color: rgb(254, 213, 192); }");

  ui->comboBox->addItem("2400");
  ui->comboBox->addItem("4800");
  ui->comboBox->addItem("9600");
  ui->comboBox->addItem("19200");

  ui->comboBox_2->addItem("2400");
  ui->comboBox_2->addItem("4800");
  ui->comboBox_2->addItem("9600");
  ui->comboBox_2->addItem("19200");


  COM1 = new QSerialPort("COM1");
  COM2 = new QSerialPort("COM2");
  COM1->setParity(QSerialPort::NoParity);
  COM2->setParity(QSerialPort::NoParity);
  COM1->setBaudRate(QSerialPort::Baud2400);
  COM2->setBaudRate(QSerialPort::Baud2400);
  COM1->setStopBits(QSerialPort::OneStop);
  COM2->setStopBits(QSerialPort::OneStop);
  if(!COM1->open(QIODevice::ReadWrite)||!COM2->open(QIODevice::ReadWrite))
    {
      qDebug("ERROR IN OPENNING");
    }
  connect(COM2,SIGNAL(readyRead()),this,SLOT(com2Read()));
  connect(COM1,SIGNAL(readyRead()),this,SLOT(com1Read()));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::com2Read()
{
  QByteArray read;
  read = "com1: " + COM2->readAll();
  ui->label2->setText(ui->label2->toPlainText().toUtf8() + read + "\n");
  ui->label1->setText(ui->label1->toPlainText().toUtf8() + read + "\n");
  ui->text1->clear();

}

void MainWindow::com1Read()
{
  QByteArray read;
  read = "com2: " + COM1->readAll();
  ui->label2->setText(ui->label2->toPlainText().toUtf8() + read + "\n");
  ui->label1->setText(ui->label1->toPlainText().toUtf8() + read + "\n");
  ui->text2->clear();
}

void MainWindow::on_pushButton_clicked()
{
  COM1->write(ui->text1->toPlainText().toUtf8());

}

void MainWindow::on_spinBox_editingFinished()
{
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
}

void MainWindow::on_pushButton_2_clicked()
{
  COM2->write(ui->text2->toPlainText().toUtf8());

}


void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if(ui->comboBox->currentText()== "2400")
      {
      COM1->setBaudRate(QSerialPort::Baud2400);
      }

    if(ui->comboBox->currentText()== "4800")
      {
      COM1->setBaudRate(QSerialPort::Baud4800);
      }

    if(ui->comboBox->currentText()== "9600")
      {
      COM1->setBaudRate(QSerialPort::Baud9600);
      }

    if(ui->comboBox->currentText()== "19200")
      {
      COM1->setBaudRate(QSerialPort::Baud19200);
      }

}

void MainWindow::on_checkBox_clicked()
{
    if (ui->checkBox->isChecked())
      {
      COM1->setParity(QSerialPort::OddParity);
      }
    else
      {
      COM1->setParity(QSerialPort::NoParity);
      }

}

void MainWindow::on_comboBox_2_activated(const QString &arg1)
{
  if(ui->comboBox_2->currentText()== "2400")
    {
    COM2->setBaudRate(QSerialPort::Baud2400);
    }

  if(ui->comboBox_2->currentText()== "4800")
    {
    COM2->setBaudRate(QSerialPort::Baud4800);
    }

  if(ui->comboBox_2->currentText()== "9600")
    {
    COM2->setBaudRate(QSerialPort::Baud9600);
    }

  if(ui->comboBox_2->currentText()== "19200")
    {
    COM2->setBaudRate(QSerialPort::Baud19200);
    }

}

void MainWindow::on_checkBox_2_clicked()
{
  if (ui->checkBox_2->isChecked())
    {
    COM2->setParity(QSerialPort::OddParity);
    }
  else
    {
    COM2->setParity(QSerialPort::NoParity);
    }
}
