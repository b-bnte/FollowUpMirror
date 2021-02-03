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

    // Buttons.
    QPushButton *btn_addActivity;
    QPushButton *btn_addMealToList;
    QPushButton *btn_addMealToHistory;

    // Clock.
    QTimer *update_time;

};

#endif // MAINWINDOW_H
