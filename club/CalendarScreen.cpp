#include "CalendarScreen.h"
#include "ui_CalendarScreen.h"
#include "NameScreen.h"
#include "TimeScreen.h"

CalendarScreen::CalendarScreen(QString name, QWidget *parent)
    : QDialog(parent)
    , userName(name)
    , ui(new Ui::CalendarScreen)
{
    ui->setupUi(this);
}

CalendarScreen::~CalendarScreen()
{
    delete ui;
}

void CalendarScreen::on_backButton_clicked()
{
    NameScreen *nameScreen = new NameScreen();
    nameScreen->show();
    this->close();
}


void CalendarScreen::on_nextButton_clicked()
{
    // Предположим, что selectedDate это текущая выбранная дата в календаре
    QDate selectedDate = ui->calendarWidget->selectedDate();

    QDate today = QDate::currentDate();

    if(selectedDate < today){
        QMessageBox::warning(this, "Ошибка", "Выбранный день не может быть рвньше, чем сегодня.");
        return;
    }

    // Создаем объект TimeScreen и передаем в него выбранную дату
    TimeScreen *timeScreen = new TimeScreen(userName, selectedDate);
    timeScreen->show();
    this->close();
}

