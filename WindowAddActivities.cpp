#include "WindowAddActivities.h"

WindowAddActivities::WindowAddActivities() : QWidget()
{
    // Creation of a FormLayout.
    date = new QDateEdit;
    activity = new QComboBox;
    duration = new QSpinBox;
    duration->setMaximum(1440); // 1440min = 24h.

    // Get all activities for QComboBox (activity).
    for (sActivityMET activityMet : tabActtivityMET)
        activity->addItem(activityMet.name);

    formLayout = new QFormLayout;
    formLayout->addRow("Date", date);
    formLayout->addRow("Activité", activity);
    formLayout->addRow("Durée (min)", duration);

    // Creation of Buttons.
    btn_calculate = new QPushButton("Calculer");
    btn_add = new QPushButton("Ajouter");
    btn_quit = new QPushButton("Quitter");
    btn_add->setEnabled(false); //avoid adding an activity before calculating calories.

    // Creation of Labels.
    label_kcalories = new QLabel("... kcal");
    label_met = new QLabel("MET : ...");

    // Add to Grid Layout.
    layout = new QGridLayout;
    layout->addLayout(formLayout, 0, 0, 3, 2);
    // Buttons.
    layout->addWidget(btn_calculate, 3, 0);
    layout->addWidget(btn_add, 4, 2);
    layout->addWidget(btn_quit, 4, 3);
    // Labels.
    layout->addWidget(label_kcalories, 4, 0);
    layout->addWidget(label_met, 1, 2);

    this->setLayout(layout);

    // Signals.
    QObject::connect(btn_quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QObject::connect(activity, SIGNAL(currentIndexChanged(int)), this, SLOT(updateLabelMET(int)));

    QObject::connect(btn_calculate, SIGNAL(clicked()), this, SLOT(calculateCalories()));

    QObject::connect(btn_add, SIGNAL(clicked()), this, SLOT(addToDataFileStorage()));
}

void WindowAddActivities::updateLabelMET(int index)
{
    label_met->setText("MET : " + QString::number(tabActtivityMET[index].MET));
}

void WindowAddActivities::calculateCalories()
{
    // Get data.
    float met = tabActtivityMET[activity->currentIndex()].MET;
    int t = duration->value();

    // Calculate.
    int res = 70.0 * met * (t/60.0);
    label_kcalories->setText(QString::number(res) + " kcal");

    // Enable button to add a activity in "storage/activity_history.txt".
    btn_add->setEnabled(true);
}

void WindowAddActivities::addToDataFileStorage ()
{
    QFile file("storage/activity_history.txt");
    if (!QDir("storage").exists())
        QDir().mkdir("storage");

    file.open(QIODevice::Append);

    // Date.
    file.write(date->date().toString(Qt::ISODate).toUtf8() +"\t");
    // Activity.
    file.write(tabActtivityMET[activity->currentIndex()].name.toUtf8() + "\t");
    // Duration.
    file.write(duration->text().toUtf8() + "\t");
    // Calories (kcal).
    file.write(label_kcalories->text().chopped(5).toUtf8() + "\n");

    file.close();

    // Disable button to add a activity in "storage/activity_history.txt".
    btn_add->setEnabled(false); //avoid adding an activity twice.
}
