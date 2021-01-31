#include "WindowAddActivities.h"

WindowAddActivities::WindowAddActivities() : QWidget()
{
    // Creation of a FormLayout.
    date = new QDateEdit;
    activity = new QComboBox;
    duration = new QSpinBox;

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
}

void WindowAddActivities::addToDataFileStorage ()
{
    std::cout << "add" << std::endl;
    QFile outputFile("activity_history.txt");
    outputFile.open(QIODevice::WriteOnly);
    outputFile.write("data");
    outputFile.close();
}
