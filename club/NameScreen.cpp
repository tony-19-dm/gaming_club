#include "NameScreen.h"
#include "ui_NameScreen.h"
#include "mainwindow.h"
#include "CalendarScreen.h"

NameScreen::NameScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NameScreen)
{
    ui->setupUi(this);
}

NameScreen::~NameScreen()
{
    delete ui;
}

void NameScreen::on_backButton_clicked()
{
    // Возвращаемся на главный экран
    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
    this->close();  // Закрываем текущий экран

}


void NameScreen::on_nextButton_clicked()
{
    // Получаем введенное имя
    QString name = ui->nameLineEdit->text();
    if (name.isEmpty()) {
        // Если имя не введено, показываем сообщение
        QMessageBox::warning(this, "Ошибка", "Пожалуйста, введите ваше имя.");
        return;
    }

    // Переходим на экран выбора даты
    CalendarScreen *calendarScreen = new CalendarScreen(name);
    calendarScreen->show();
    this->close();
}

