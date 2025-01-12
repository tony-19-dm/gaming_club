#ifndef TIMESCREEN_H
#define TIMESCREEN_H

#include <QDialog>
#include <QWidget>
#include <QTimeEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>

namespace Ui {
class TimeScreen;
}

class TimeScreen : public QDialog
{
    Q_OBJECT

public:
    explicit TimeScreen(QString name, QDate date, QWidget *parent = nullptr);  // Конструктор с параметром QDate
    ~TimeScreen();

private slots:
    void on_backButton_clicked();
    void on_nextButton_clicked();

private:
    Ui::TimeScreen *ui;
    QString userName;
    QDate selectedDate;  // Переменная для хранения выбранной даты
};

#endif // TIMESCREEN_H
