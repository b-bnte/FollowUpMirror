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

    public slots:
    void updateTime();
    void launchWindowAddActivities();
    void launchWindowAddMeal();
    void launchWindowAddMealToHistory();
    void updateDate();
    void updateProgressBar();

    signals:

    private:
    // Windows.
    WindowAddActivities *windowAddActivities;
    WindowAddMeal *windowAddMeal;
    WindowAddMealToHistory *windowAddMealToHistory;

    // Grid Layout (main layout).
    QGridLayout *layout = new QGridLayout;

    // Labels.
    QLabel *label_date;
    QLabel *label_time;
    QLabel *label_weather;
    QLabel *label_inVsOut;

    // Buttons.
    QPushButton *btn_addActivity;
    QPushButton *btn_addMealToList;
    QPushButton *btn_addMealToHistory;

    // Clock.
    QTimer *update_time;

    // DateEdit for test and Debug application.
    QDateEdit *globalDate;

    // ProgressBar for display input/output energy.
    QProgressBar *proBar_inVsOut;
};

#endif // MAINWINDOW_H
