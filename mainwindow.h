#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

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
  void on_pushButton_clicked();

  void on_spinBox_editingFinished();

  void on_spinBox_valueChanged(int arg1);

  void com2Read();

  void com1Read();

  void on_pushButton_2_clicked();

  void on_comboBox_activated(const QString &arg1);

  void on_checkBox_clicked();

  void on_comboBox_2_activated(const QString &arg1);

  void on_checkBox_2_clicked();

private:
  Ui::MainWindow *ui;
  QSerialPort *COM1;
  QSerialPort *COM2;

};

#endif // MAINWINDOW_H
