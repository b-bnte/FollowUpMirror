#include "MainWindow.h"

MainWindow::MainWindow() : QWidget()
{
    // Set time and timer for clock.
    update_time = new QTimer();
    update_time->start(1000);
    label_time = new QLabel(QTime::currentTime().toString("hh:mm:ss a"));

    // Labels.
    label_date = new QLabel(QDateTime::currentDateTime().toString("dddd MMMM d yyyy"));

    // Buttons.
    btn_addActivity = new QPushButton("Ajouter activité");
    btn_addMealToHistory = new QPushButton("Ajouter repas");
    btn_addMealToList = new QPushButton("+");

    // Add to Grid Layout.
    layout = new QGridLayout;
    // Labels.
    layout->addWidget(label_date, 0, 0);
    layout->addWidget(label_time, 1, 0);
    layout->addWidget(btn_addMealToHistory, 2, 0);
    layout->addWidget(btn_addMealToList, 2,1);
    layout->addWidget(btn_addActivity, 3,0);

    this->setLayout(layout);

    // Signals.
    QObject::connect(update_time, SIGNAL(timeout()), this, SLOT(updateTime()));
    QObject::connect(btn_addMealToList, SIGNAL(clicked()), this, SLOT(launchWindowAddMeal()));
    QObject::connect(btn_addActivity, SIGNAL(clicked()), this, SLOT(launchWindowAddActivities()));
    QObject::connect(btn_addMealToHistory, SIGNAL(clicked()), this, SLOT(launchWindowAddMealToHistory()));
}

void MainWindow::updateTime()
{
    label_time->setText(QTime::currentTime().toString("hh:mm:ss a"));
}

void MainWindow::launchWindowAddActivities()
{
    windowAddActivities = new WindowAddActivities();
    windowAddActivities->show();
}

void MainWindow::launchWindowAddMeal()
{
    windowAddMeal = new WindowAddMeal();
    windowAddMeal->show();
}

void MainWindow::launchWindowAddMealToHistory()
{
    windowAddMealToHistory = new WindowAddMealToHistory();
    windowAddMealToHistory->show();
}
