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

class WindowAddMealToHistory : public QWidget
{
    Q_OBJECT

    public:
    WindowAddMealToHistory();

    public slots:
    void addToMealToHistory();

    signals:

    private:
    // Grid Layout (main layout).
    QGridLayout *layout = new QGridLayout;

    // Creation of a FormLayout.
    QFormLayout *formLayout;
    QDateEdit *date;
    QComboBox *meal;

    // Button.
    QPushButton *btn_add;

    // Functions.
    void GetMealsToComboBox();
};

#endif // WINDOWADDMEALTOHISTORY_H
