#ifndef DEVICESCREEN_H
#define DEVICESCREEN_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDate>    // Добавляем подключение QDate
#include <QTime>
#include <QStringList>

namespace Ui {
class DeviceScreen;
}

class DeviceScreen : public QDialog
{
    Q_OBJECT

public:
    explicit DeviceScreen(QString name, QDate date, QTime startTime, QTime endTime, QWidget *parent = nullptr);
    ~DeviceScreen();

private slots:
    void on_deviceButton_clicked();
    void on_confirmButton_clicked();
    void on_backButton_clicked();

private:
    bool isDeviceBooked(const QString &deviceName);

    Ui::DeviceScreen *ui;
    QString userName;
    QDate selectedDate;
    QTime startTime;
    QTime endTime;
    QStringList selectedDevices;
};

#endif // DEVICESCREEN_H
