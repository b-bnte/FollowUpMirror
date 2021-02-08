#include "WindowAddActivities.h"

WindowAddActivities::WindowAddActivities() : QWidget() {
    date = new QDateEdit(QDate::currentDate());
    activity = new QComboBox;
    duration = new QSpinBox;
    duration->setMaximum(1440); // 1440min = 24h.

    // Get all activities for QComboBox (activity).
    for (const sActivityMET &activityMet : tabActtivityMET)
        activity->addItem(activityMet.name);

    formLayout = new QFormLayout;
    formLayout->addRow("Date", date);
    formLayout->addRow("Activité", activity);
    formLayout->addRow("Durée (min)", duration);

    btn_calculate = new QPushButton("Calculer");
    btn_add = new QPushButton("Ajouter");
    btn_quit = new QPushButton("Quitter");
    btn_add->setEnabled(false); //avoid adding an activity before calculating calories.

    label_kcalories = new QLabel("... kcal");
    label_met = new QLabel("MET : ...");

    mainLayout = new QGridLayout;
    mainLayout->addLayout(formLayout, 0, 0, 3, 2);
    mainLayout->addWidget(btn_calculate, 3, 0);
    mainLayout->addWidget(btn_add, 4, 2);
    mainLayout->addWidget(btn_quit, 4, 3);
    mainLayout->addWidget(label_kcalories, 4, 0);
    mainLayout->addWidget(label_met, 1, 2);

    this->setLayout(mainLayout);

    // Signals.
    QObject::connect(btn_quit, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(activity, SIGNAL(currentIndexChanged(int)), this, SLOT(updateLabelMET(int)));
    QObject::connect(btn_calculate, SIGNAL(clicked()), this, SLOT(calculateCalories()));
    QObject::connect(btn_add, SIGNAL(clicked()), this, SLOT(addToDataFileStorage()));
}

void WindowAddActivities::updateLabelMET(int index) {
    label_met->setText("MET : " + QString::number(tabActtivityMET[index].MET));
}

void WindowAddActivities::calculateCalories() {
    float met = tabActtivityMET[activity->currentIndex()].MET;
    int t = duration->value();

    int res = 70.0 * met * (t/60.0);
    label_kcalories->setText(QString::number(res) + " kcal");

    // Enable button to add a activity in "storage/activity_history.txt".
    btn_add->setEnabled(true);
}

void WindowAddActivities::addToDataFileStorage() {
    QFile file("storage/activity_history.dat");
    if (!QDir("storage").exists())
        QDir().mkdir("storage");

    file.open(QIODevice::Append);

    // New version.
    QDataStream data(&file);
    data << QDate(date->date());
    data << QString(tabActtivityMET[activity->currentIndex()].name);
    data << int(duration->value());
    data << int(label_kcalories->text().chopped(5).toInt());

    // Old versions.
    /*// Date.
    file.write(date->date().toString(Qt::ISODate).toUtf8() +"\t");
    // Activity.
    file.write(tabActtivityMET[activity->currentIndex()].name.toUtf8() + "\t");
    // Duration.
    file.write(duration->text().toUtf8() + "\t");
    // Calories (kcal).
    file.write(label_kcalories->text().chopped(5).toUtf8() + "\n");*/

    file.close();

    // Help to reading a line from "storage/activity_history.dat".
    file.open(QIODevice::ReadOnly);

    QDataStream dataRead(&file);
    QDate dateRead;
    QString typeOfActivityRead;
    int durationOfActivityRead;
    int kcaloriesOfActivityRead;

    while (!data.atEnd()) {
        dataRead >> dateRead;
        qDebug () << dateRead;

        dataRead >> typeOfActivityRead;
        qDebug () << typeOfActivityRead;

        dataRead >> durationOfActivityRead;
        qDebug () << durationOfActivityRead << "min";

        dataRead >> kcaloriesOfActivityRead;
        qDebug () << kcaloriesOfActivityRead << "kcal";

        qDebug () << "------";
    }

    // Disable button to add a activity in "storage/activity_history.txt".
    btn_add->setEnabled(false); //avoid adding an activity twice.
}
