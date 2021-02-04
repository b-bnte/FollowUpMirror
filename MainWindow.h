#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "WindowAddActivities.h"
#include "WindowAddMeal.h"
#include "WindowAddMealToHistory.h"

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QDateTime>
#include <QTimer>
#include <QDateTimeEdit>
#include <QDateEdit>
#include <QDebug>
#include <QDate>
#include <QTextStream>
#include <QDataStream>
#include <QProgressBar>

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
    MainWindow();

    private slots:
    void updateTime();
    void launchWindowAddActivities();
    void launchWindowAddMeal();
    void launchWindowAddMealToHistory();
    void updateDate();
    void updateProgressBar();

    signals:

    private:
    WindowAddActivities *windowAddActivities;
    WindowAddMeal *windowAddMeal;
    WindowAddMealToHistory *windowAddMealToHistory;

    QGridLayout *mainLayout = new QGridLayout;
    QLabel *label_date;
    QLabel *label_time;
    QLabel *label_weather;
    QLabel *label_inVsOutCalories;
    QPushButton *btn_addActivity;
    QPushButton *btn_addMealToList;
    QPushButton *btn_addMealToHistory;
    QDateEdit *globalDate; // just for Debug.
    QProgressBar *proBar_inVsOutCalories;

    QTimer *oneSecondTimer;
};

#endif // MAINWINDOW_H
