#include "MainWindow.h"

MainWindow::MainWindow() : QWidget()
{
    // Set time and timer for clock.
    update_time = new QTimer();
    update_time->start(1000);
    label_time = new QLabel(QTime::currentTime().toString("hh:mm:ss a"));

    // Labels.
    label_date = new QLabel(QDateTime::currentDateTime().toString("dddd MMMM d yyyy"));
    label_inVsOut = new QLabel();

    // Dare for Debug init.
    globalDate = new QDateEdit(QDate::currentDate());

    // Buttons.
    btn_addActivity = new QPushButton("Ajouter activité");
    btn_addMealToHistory = new QPushButton("Ajouter repas");
    btn_addMealToList = new QPushButton("+");

    // ProgressBar.
    proBar_inVsOut = new QProgressBar();
    this->updateProgressBar();

    // Add to Grid Layout.
    layout = new QGridLayout;
    // Labels.
    layout->addWidget(label_date, 1, 0);
    layout->addWidget(label_time, 2, 0);
    layout->addWidget(btn_addMealToHistory, 3, 0);
    layout->addWidget(btn_addMealToList, 3,1);
    layout->addWidget(btn_addActivity, 4,0);
    layout->addWidget(label_inVsOut, 6, 0);
    // ProgressBar.
    layout->addWidget(proBar_inVsOut, 5, 0);
    // DateEdit for Debug.
    layout->addWidget(globalDate, 0, 0);

    this->setLayout(layout);

    // Signals.
    QObject::connect(update_time, SIGNAL(timeout()), this, SLOT(updateTime()));
    QObject::connect(btn_addMealToList, SIGNAL(clicked()), this, SLOT(launchWindowAddMeal()));
    QObject::connect(btn_addActivity, SIGNAL(clicked()), this, SLOT(launchWindowAddActivities()));
    QObject::connect(btn_addMealToHistory, SIGNAL(clicked()), this, SLOT(launchWindowAddMealToHistory()));
    QObject::connect(globalDate, SIGNAL(dateChanged(QDate)), this, SLOT(updateDate()));
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

void MainWindow::updateDate()
{
    label_date->setText(globalDate->date().toString("dddd MMMM d yyyy"));
    this->updateProgressBar();
}

void MainWindow::updateProgressBar()
{
    int input = 1;
    int output = 1;

    // Input.
    QFile file1("storage/meal_history.dat");
    if(file1.open(QFile::ReadOnly))
    {
        QDataStream data1(&file1);
        QDate date;
        QString mealName_history;
        while (!data1.atEnd())
        {
            data1 >> date;
            data1 >> mealName_history;
            if (date == globalDate->date())
            {
                QFile file2("storage/meal_list.txt");
                file2.open(QIODevice::ReadOnly);
                QTextStream data2(&file2);
                QString mealName_list;

                while (!data2.atEnd())
                {
                    data2 >> mealName_list;

                    if (mealName_list == mealName_history)
                    {
                        int cal;
                        data2 >> cal;
                        input += cal;
                    }
                }

                file2.close();
            }
        }
    }
    file1.close();

    // Output.
    QFile file3("storage/activity_history.txt");
    if(file3.open(QFile::ReadOnly))
    {
        QTextStream data3(&file3);
        QString dateOfActivity;
        QString typeOfActivity;
        int duration;
        int calories;

        while (!data3.atEnd())
        {
            data3 >> dateOfActivity;
            data3 >> typeOfActivity;
            data3 >> duration;
            data3 >> calories;

            if (QDate::fromString(dateOfActivity, Qt::ISODate) == globalDate->date())
                output += calories;
        }
    }
    file3.close();

    // Calaculate.
    int value = (double(output)/double(input))*100;
    if (value >100)
        value = 100;
    // Update ProgressBar.
    proBar_inVsOut->setValue(value);

    // Add value below ProgressBar.
    int res = input-output;
    if (res <= 0)
    {
        label_inVsOut->setText("-");
        label_inVsOut->setStyleSheet("QLabel {color : green}");
    }
    else
    {
        label_inVsOut->setText("+");
        label_inVsOut->setStyleSheet("QLabel {color : red}");
    }

    label_inVsOut->setText( label_inVsOut->text() + QString::number(abs(res)) + " kcal");
}
