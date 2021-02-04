#include "MainWindow.h"

MainWindow::MainWindow() : QWidget() {
    oneSecondTimer = new QTimer();
    oneSecondTimer->start(1000);

    label_time = new QLabel(QTime::currentTime().toString("hh:mm:ss a"));
    label_date = new QLabel(QDateTime::currentDateTime().toString("dddd MMMM d yyyy"));
    label_inVsOutCalories = new QLabel();

    globalDate = new QDateEdit(QDate::currentDate());

    btn_addActivity = new QPushButton("Ajouter activité");
    btn_addMealToHistory = new QPushButton("Ajouter repas");
    btn_addMealToList = new QPushButton("+");

    proBar_inVsOutCalories = new QProgressBar();
    this->updateProgressBar();

    // Construct the Layout.
    mainLayout = new QGridLayout;
    mainLayout->addWidget(globalDate, 0, 0);
    mainLayout->addWidget(label_date, 1, 0);
    mainLayout->addWidget(label_time, 2, 0);
    mainLayout->addWidget(btn_addMealToHistory, 3, 0);
    mainLayout->addWidget(btn_addMealToList, 3,1);
    mainLayout->addWidget(btn_addActivity, 4,0);
    mainLayout->addWidget(label_inVsOutCalories, 6, 0);
    mainLayout->addWidget(proBar_inVsOutCalories, 5, 0);

    this->setLayout(mainLayout);

    // Signals.
    QObject::connect(oneSecondTimer, SIGNAL(timeout()), this, SLOT(updateTime()));
    QObject::connect(btn_addMealToList, SIGNAL(clicked()), this, SLOT(launchWindowAddMeal()));
    QObject::connect(btn_addActivity, SIGNAL(clicked()), this, SLOT(launchWindowAddActivities()));
    QObject::connect(btn_addMealToHistory, SIGNAL(clicked()), this, SLOT(launchWindowAddMealToHistory()));
    QObject::connect(globalDate, SIGNAL(dateChanged(QDate)), this, SLOT(updateDate()));
}

void MainWindow::updateTime() {
    label_time->setText(QTime::currentTime().toString("hh:mm:ss a"));
}

void MainWindow::launchWindowAddActivities() {
    windowAddActivities = new WindowAddActivities();
    windowAddActivities->show();
}

void MainWindow::launchWindowAddMeal() {
    windowAddMeal = new WindowAddMeal();
    windowAddMeal->show();
}

void MainWindow::launchWindowAddMealToHistory() {
    windowAddMealToHistory = new WindowAddMealToHistory();
    windowAddMealToHistory->show();
}

void MainWindow::updateDate() {
    label_date->setText(globalDate->date().toString("dddd MMMM d yyyy"));
    this->updateProgressBar();
}

// TO-DO: prototype function for the moment. Need improvement.
void MainWindow::updateProgressBar() {
    int input = 1;
    int output = 1;

    // Input.
    QFile file1("storage/meal_history.dat");
    file1.open(QFile::ReadOnly);
    QDataStream data1(&file1);
    QDate date;
    QString mealName_history;

    while (!data1.atEnd()) {
        data1 >> date;
        data1 >> mealName_history;
        if (date == globalDate->date()) {
            QFile file2("storage/meal_list.txt");
            file2.open(QIODevice::ReadOnly);
            QTextStream data2(&file2);
            QString mealName_list;

            while (!data2.atEnd()) {
                data2 >> mealName_list;
                if (mealName_list == mealName_history) {
                    int cal;
                    data2 >> cal;
                    input += cal;
                }
            }
            file2.close();
        }
    }
    file1.close();

    // Output.
    QFile file3("storage/activity_history.txt");
    if (file3.open(QFile::ReadOnly)) {
        QTextStream data3(&file3);
        QString dateOfActivity;
        QString typeOfActivity;
        int duration;
        int calories;

        while (!data3.atEnd()) {
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
    int value = (double(output)/double(input)) * 100;
    if (value >100)
        value = 100;
    // Update ProgressBar.
    proBar_inVsOutCalories->setValue(value);

    // Add value below ProgressBar.
    int res = input-output;
    if (res <= 0) {
        label_inVsOutCalories->setText("-");
        label_inVsOutCalories->setStyleSheet("QLabel {color : green}");
    }
    else {
        label_inVsOutCalories->setText("+");
        label_inVsOutCalories->setStyleSheet("QLabel {color : red}");
    }

    label_inVsOutCalories->setText( label_inVsOutCalories->text() + QString::number(abs(res)) + " kcal");
}
