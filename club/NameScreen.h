#ifndef NAMESCREEN_H
#define NAMESCREEN_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class NameScreen;
}

class NameScreen : public QDialog
{
    Q_OBJECT

public:
    explicit NameScreen(QWidget *parent = nullptr);
    ~NameScreen();

private slots:
    void on_backButton_clicked();

    void on_nextButton_clicked();

private:
    Ui::NameScreen *ui;
};

#endif // NAMESCREEN_H
