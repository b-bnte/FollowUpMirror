#ifndef WINDOWADDMEALTOHISTORY_H
#define WINDOWADDMEALTOHISTORY_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QFormLayout>
#include <QDateEdit>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QString>

class WindowAddMealToHistory : public QWidget
{
    Q_OBJECT

    public:
    WindowAddMealToHistory();

    private slots:
    void addToMealToHistory();

    private:
    QGridLayout *mainLayout = new QGridLayout;
    QFormLayout *formLayout;
    QDateEdit *date;
    QComboBox *meal;
    QPushButton *btn_add;

    // Functions.
    private:
    void GetMealsToComboBox();
};

#endif // WINDOWADDMEALTOHISTORY_H
