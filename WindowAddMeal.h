#ifndef WINDOWADDMEAL_H
#define WINDOWADDMEAL_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QSpinBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QFile>
#include <QDir>
#include <QDebug>

class WindowAddMeal : public QWidget
{
    Q_OBJECT

    public:
    WindowAddMeal();

    private slots:
    void addToMealList();

    private:
    QFormLayout *formLayout;
    QLineEdit *name;
    QSpinBox *calories;
    QSpinBox *carbs;
    QSpinBox *protein;
    QSpinBox *lipid;
    QPushButton *btn_add;
};

#endif // WINDOWADDMEAL_H
