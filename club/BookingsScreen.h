#ifndef BOOKINGSSCREEN_H
#define BOOKINGSSCREEN_H

#include <QDialog>
#include <QTableWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

namespace Ui {
class BookingsScreen;
}

class BookingsScreen : public QDialog
{
    Q_OBJECT

public:
    explicit BookingsScreen(QWidget *parent = nullptr);
    ~BookingsScreen();

private slots:
    void on_deleteButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::BookingsScreen *ui;
    QSqlDatabase db;
    void loadBookings();
    void setupTable();
    void deleteBooking(int id);
};

#endif // BOOKINGSSCREEN_H
