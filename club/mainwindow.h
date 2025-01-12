#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "NameScreen.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startBookingButton_clicked();

    void on_showBookings_triggered();

private:
    Ui::MainWindow *ui;
    NameScreen *nameScreen;
};
#endif // MAINWINDOW_H
