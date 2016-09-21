#include "comports.h"

ComPorts::ComPorts()
{
  COM1 = new QSerialPort("COM1");
  COM2 = new QSerialPort("COM2");
  COM1->setParity(QSerialPort::NoParity);
  COM2->setParity(QSerialPort::NoParity);
  COM1->setBaudRate(QSerialPort::Baud19200);
  COM2->setBaudRate(QSerialPort::Baud19200);
  COM1->setStopBits(QSerialPort::OneStop);
  COM2->setStopBits(QSerialPort::OneStop);
  if(!COM1->open(QIODevice::ReadWrite)||!COM2->open(QIODevice::ReadWrite))
    {
      qDebug("ERROR IN OPENNING");
    }
  connect(COM2,SIGNAL(readyRead()),this,SLOT(com2Read()));
  connect(COM1,SIGNAL(readyRead()),this,SLOT(com1Read()));
}

void MainWindow::com2Read()
{
  QByteArray read;
  read = COM2->readAll();
  ui->text2->setText(read);
}

void MainWindow::com1Read()
{
  QByteArray read;
  read = COM1->readAll();
  ui->text1->setText(read);
}
