#include "BookingsScreen.h"
#include "ui_BookingsScreen.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

BookingsScreen::BookingsScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BookingsScreen)
{
    ui->setupUi(this);

    // Подключаемся к базе данных SQLite
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/antondmitriev/Desktop/Sibsutis/3 course/vp/helpers/base/bookings.db"); // Путь к вашей базе данных

    if (!db.open()) {
        qDebug() << "Ошибка подключения к базе данных: " << db.lastError().text();
        QMessageBox::critical(this, "Ошибка", "Не удалось подключиться к базе данных.");
        return;
    }

    setupTable();

    ui->searchDateEdit->setDate(QDate::currentDate());

    loadBookings();
}

BookingsScreen::~BookingsScreen()
{
    delete ui;
    db.close();
}

void BookingsScreen::setupTable()
{
    ui->bookingsTableWidget->setColumnCount(5); // Колонки: ID, Имя, Дата, Время, Устройства
    QStringList headers = {"ID", "Имя", "Дата", "Время", "Устройства"};
    ui->bookingsTableWidget->setHorizontalHeaderLabels(headers);
    ui->bookingsTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // Запрет редактирования
    ui->bookingsTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); // Выделение всей строки
    ui->bookingsTableWidget->setSelectionMode(QAbstractItemView::SingleSelection); // Только одна строка
    ui->bookingsTableWidget->horizontalHeader()->setStretchLastSection(true); // Растягивание последней колонки

    ui->bookingsTableWidget->clearSelection();
    ui->bookingsTableWidget->setCurrentCell(-1, -1);
}

void BookingsScreen::loadBookings()
{
    ui->bookingsTableWidget->setRowCount(0); // Очистить таблицу

    QSqlQuery query("SELECT * FROM bookings");
    if (!query.exec()) {
        qDebug() << "Ошибка запроса: " << query.lastError().text();
        QMessageBox::warning(this, "Ошибка", "Не удалось загрузить данные из базы данных.");
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->bookingsTableWidget->insertRow(row);
        ui->bookingsTableWidget->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        ui->bookingsTableWidget->setItem(row, 1, new QTableWidgetItem(query.value("name").toString()));
        ui->bookingsTableWidget->setItem(row, 2, new QTableWidgetItem(query.value("date").toString()));
        ui->bookingsTableWidget->setItem(row, 3, new QTableWidgetItem(query.value("start_time").toString() + " - " + query.value("end_time").toString()));
        ui->bookingsTableWidget->setItem(row, 4, new QTableWidgetItem(query.value("devices").toString()));
        row++;
    }

    ui->bookingsTableWidget->clearSelection();
    ui->bookingsTableWidget->setCurrentCell(-1, -1);
}

void BookingsScreen::on_deleteButton_clicked()
{
    int currentRow = ui->bookingsTableWidget->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "Ошибка", "Выберите запись для удаления.");
        return;
    }

    int bookingId = ui->bookingsTableWidget->item(currentRow, 0)->text().toInt();

    // Удаление бронирования из базы данных
    deleteBooking(bookingId);

    // Удаляем строку из таблицы
    ui->bookingsTableWidget->removeRow(currentRow);

    ui->bookingsTableWidget->clearSelection();
    ui->bookingsTableWidget->setCurrentCell(-1, -1);

    QMessageBox::information(this, "Успех", "Бронирование успешно удалено.");
}

void BookingsScreen::deleteBooking(int id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM bookings WHERE id = :id");
    query.bindValue(":id", id);
    if (!query.exec()) {
        qDebug() << "Ошибка удаления бронирования: " << query.lastError().text();
        QMessageBox::warning(this, "Ошибка", "Не удалось удалить бронирование из базы данных.");
    }
}

void BookingsScreen::on_searchButton_clicked()
{
    // Получаем введенные данные
    QString devices = ui->numberLineEdit->text();
    QDate date = ui->searchDateEdit->date();
    QString name = ui->nameLineEdit->text();
    QSqlQuery query;
    // Очищаем таблицу перед обновлением
    ui->bookingsTableWidget->setRowCount(0);

    if (name.isEmpty()){
        query.prepare("SELECT * FROM bookings WHERE date = :date AND devices LIKE :devices");
        query.bindValue(":date", date.toString("yyyy-MM-dd"));
        query.bindValue(":devices", "%" + devices + "%");
    } else {
        query.prepare("SELECT * FROM bookings WHERE name = :name AND date = :date");
        query.bindValue(":name", name);
        query.bindValue(":date", date.toString("yyyy-MM-dd"));
    }

    if (!query.exec()) {
        qDebug() << "Ошибка фильтрации: " << query.lastError().text();
        QMessageBox::warning(this, "Ошибка", "Не удалось выполнить поиск в базе данных.");
        return;
    }

    // Заполняем таблицу результатами запроса
    int row = 0;
    while (query.next()) {
        ui->bookingsTableWidget->insertRow(row);
        ui->bookingsTableWidget->setItem(row, 0, new QTableWidgetItem(query.value("id").toString()));
        ui->bookingsTableWidget->setItem(row, 1, new QTableWidgetItem(query.value("name").toString()));
        ui->bookingsTableWidget->setItem(row, 2, new QTableWidgetItem(query.value("date").toString()));
        ui->bookingsTableWidget->setItem(row, 3, new QTableWidgetItem(query.value("start_time").toString() + " - " + query.value("end_time").toString()));
        ui->bookingsTableWidget->setItem(row, 4, new QTableWidgetItem(query.value("devices").toString()));
        row++;
    }

    if (name.isEmpty()){
       ui->bookingsTableWidget->sortByColumn(3, Qt::AscendingOrder);
    } else {
        ui->bookingsTableWidget->sortByColumn(2, Qt::AscendingOrder);
    }

    // Снимаем выделение в таблице
    ui->bookingsTableWidget->clearSelection();
    ui->bookingsTableWidget->setCurrentCell(-1, -1);

    if (row == 0) {
        QMessageBox::information(this, "Результаты поиска", "Не найдено бронирований, соответствующих заданным критериям.");
    }
}


