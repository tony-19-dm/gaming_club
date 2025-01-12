#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "NameScreen.h"
#include "BookingsScreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    nameScreen = new NameScreen(this);
    QPixmap pixmap("/Users/antondmitriev/Desktop/Sibsutis/3 course/vp/helpers/logo.png"); // Укажите путь к изображению
    ui->iconLabel->setPixmap(pixmap);
    ui->iconLabel->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startBookingButton_clicked()
{
    nameScreen->show();  // Открываем экран для ввода имени
    this->hide();
}

void MainWindow::on_showBookings_triggered()
{
    BookingsScreen *bookingsScreen = new BookingsScreen(this);
    bookingsScreen->exec();  // Открываем как модальное окно
}
