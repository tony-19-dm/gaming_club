#ifndef CALENDARSCREEN_H
#define CALENDARSCREEN_H

#include <QDialog>
#include <QWidget>
#include <QCalendarWidget>
#include <QPushButton>
#include <QMessageBox>

namespace Ui {
class CalendarScreen;
}

class CalendarScreen : public QDialog
{
    Q_OBJECT

public:
    explicit CalendarScreen(QString name, QWidget *parent = nullptr);
    ~CalendarScreen();

private slots:
    void on_backButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::CalendarScreen *ui;
    QString userName;
};

#endif // CALENDARSCREEN_H
