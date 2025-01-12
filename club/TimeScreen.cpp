#include "TimeScreen.h"
#include "ui_TimeScreen.h"
#include "CalendarScreen.h"
#include "DeviceScreen.h"

// Конструктор принимает QDate и передает его в переменную selectedDate
TimeScreen::TimeScreen(QString name, QDate date, QWidget *parent)
    : QDialog(parent), ui(new Ui::TimeScreen), userName(name), selectedDate(date)
{
    ui->setupUi(this);

}

TimeScreen::~TimeScreen()
{
    delete ui;
}

void TimeScreen::on_backButton_clicked()
{
    // Переход обратно на экран CalendarScreen
    CalendarScreen *calendarScreen = new CalendarScreen(userName);
    calendarScreen->show();
    this->close();
}

void TimeScreen::on_nextButton_clicked()
{
    QTime startTime = ui->startTimeEdit->time();
    QTime endTime = ui->endTimeEdit->time();

    QDate today = QDate::currentDate();
    QTime currentTime = QTime::currentTime();

    if(selectedDate == today && startTime < currentTime ){
        QMessageBox::warning(this, "Ошибка", "Время начала должно быть позже текущего времени.");
        return;
    }

    if (startTime >= endTime) {
        // Если время начала не раньше времени окончания, показываем ошибку
        QMessageBox::warning(this, "Ошибка", "Время окончания должно быть позже времени начала.");
        return;
    }

    // Переходим на экран выбора устройств, передаем дату и время
    DeviceScreen *deviceScreen = new DeviceScreen(userName, selectedDate, startTime, endTime);  // Передаем дату и время
    deviceScreen->show();
    this->close();
}
