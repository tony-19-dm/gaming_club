#include "DeviceScreen.h"
#include "ui_DeviceScreen.h"
#include "TimeScreen.h"
#include "mainwindow.h"
#include "QStandardPaths"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

DeviceScreen::DeviceScreen(QString name, QDate date, QTime startTime, QTime endTime, QWidget *parent)
    : QDialog(parent), userName(name), selectedDate(date), startTime(startTime), endTime(endTime), ui(new Ui::DeviceScreen)
{
    ui->setupUi(this);

    // Подключение к базе данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/antondmitriev/Desktop/Sibsutis/3 course/vp/helpers/base/bookings.db");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
        QMessageBox::warning(this, "Ошибка", "Не удалось подключиться к базе данных.");
    }

    // Список всех кнопок устройств
    QList<QPushButton*> deviceButtons = {
        ui->deviceButton_1, ui->deviceButton_2, ui->deviceButton_3, ui->deviceButton_4,
        ui->deviceButton_5, ui->deviceButton_6, ui->deviceButton_7, ui->deviceButton_8,
        ui->deviceButton_9, ui->deviceButton_10
    };

    for (QPushButton *button : deviceButtons) {
        QString deviceName = button->text(); // Текст кнопки используется как имя устройства
        if (isDeviceBooked(deviceName)) {
            button->setEnabled(false); // Устройство уже забронировано
            button->setStyleSheet("background-color: rgb(131, 143, 143); color: rgb(73, 236, 253); border-radius: 5px; border: 1px solid rgb(73, 236, 253);");
            button->setToolTip("Это устройство уже забронировано на выбранное время."); //подпись при наведении курсора на кнопку
        } else {
            // Подключаем сигнал clicked только для доступных кнопок
            connect(button, &QPushButton::clicked, this, &DeviceScreen::on_deviceButton_clicked);
        }
    }
}


DeviceScreen::~DeviceScreen()
{
    delete ui;
}

void DeviceScreen::on_deviceButton_clicked() {
    QPushButton *button = qobject_cast<QPushButton*>(sender());  // Получаем кнопку, которая была нажата
    if (button) {
        QString deviceName = button->text();  // Получаем текст на кнопке (например, "1", "2", и т.д.)
        if (!selectedDevices.contains(deviceName)) {
            button->setStyleSheet("background-color: rgb(255, 254, 250); color: rgb(29, 13, 32); border-radius: 5px; border: 1px solid rgb(73, 236, 253);");
            selectedDevices.append(deviceName);            // Добавляем устройство в список
        } else {
            button->setStyleSheet("background-color: rgb(73, 236, 253); color: rgb(29, 13, 32); border-radius: 5px; border: 1px solid rgb(131, 143, 143);");
            selectedDevices.removeAll(deviceName);  // Убираем устройство из списка
        }

        // Обновляем список выбранных устройств в QListWidget
        ui->devicesListWidget->clear();
        ui->devicesListWidget->addItems(selectedDevices);
    }
}

void DeviceScreen::on_confirmButton_clicked()
{
    if (selectedDevices.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, выберите хотя бы одно устройство.");
        return;
    }

    // Подключение к базе данных SQLite
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/antondmitriev/Desktop/Sibsutis/3 course/vp/helpers/base/bookings.db");

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных:" << db.lastError().text();
        QMessageBox::warning(this, "Ошибка", "Не удалось подключиться к базе данных.");
        return;
    }

    // Вставка бронирования в таблицу bookings
    QSqlQuery query;
    query.prepare("INSERT INTO bookings (name, date, start_time, end_time, devices) "
                  "VALUES (:name, :date, :start_time, :end_time, :devices)");
    query.bindValue(":name", userName);
    query.bindValue(":date", selectedDate.toString("yyyy-MM-dd"));
    query.bindValue(":start_time", startTime.toString("HH:mm"));
    query.bindValue(":end_time", endTime.toString("HH:mm"));
    query.bindValue(":devices", selectedDevices.join(", "));

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        QMessageBox::warning(this, "Ошибка", "Не удалось сохранить бронирование в базе данных.");
        return;
    }

    QMessageBox::information(this, "Успех", "Бронирование успешно сохранено!");

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();
}

bool DeviceScreen::isDeviceBooked(const QString &deviceName) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM bookings "
                  "WHERE devices LIKE :device "
                  "AND date = :date "
                  "AND ("
                  "(start_time <= :start_time AND end_time > :start_time) OR "
                  "(start_time < :end_time AND end_time >= :end_time) OR "
                  "(start_time >= :start_time AND end_time <= :end_time)"
                  ")");
    query.bindValue(":device", "%" + deviceName + "%");
    query.bindValue(":date", selectedDate.toString("yyyy-MM-dd"));
    query.bindValue(":start_time", startTime.toString("HH:mm"));
    query.bindValue(":end_time", endTime.toString("HH:mm"));

    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
        return false; // Если запрос не выполнен, по умолчанию считаем устройство доступным.
    }

    if (query.next()) {
        return query.value(0).toInt() > 0; // Если есть записи, устройство забронировано.
    }

    return false; // Если записей нет, устройство доступно.
}


void DeviceScreen::on_backButton_clicked()
{
    TimeScreen *timeScreen = new TimeScreen(userName, selectedDate);
    timeScreen->show();
    this->close();
}
