#include "WindowAddMealToHistory.h"

WindowAddMealToHistory::WindowAddMealToHistory() : QWidget()
{
    // Creation of a FormLayout.
    date = new QDateEdit;
    meal = new QComboBox;

    // Get all meals to ComboBox.
    this->GetMealsToComboBox();

    // Add to FormLayout.
    formLayout = new QFormLayout;
    formLayout->addRow("Date", date);
    formLayout->addRow("Repas", meal);

    // Buton.
    btn_add = new QPushButton("Ajouter");

    // Add to Grid Layout.
    layout = new QGridLayout;
    layout->addLayout(formLayout, 0, 0);
    layout->addWidget(btn_add, 1, 0);

    this->setLayout(layout);

    // Signals.
    QObject::connect(btn_add, SIGNAL(clicked()), this, SLOT(addToMealToHistory()));

}

void WindowAddMealToHistory::addToMealToHistory()
{
    QFile file("storage/meal_history.txt");
    if (!QDir("storage").exists())
        QDir().mkdir("storage");

    file.open(QIODevice::Append);

    // Date.
    file.write(date->date().toString(Qt::ISODate).toUtf8() +"\t");
    // Meal.
    file.write(meal->currentText().toUtf8() + "\n");

    file.close();
    this->close();
}

void WindowAddMealToHistory::GetMealsToComboBox ()
{
    QFile file("storage/meal_list.txt");

    if (file.open(QFile::ReadOnly))
    {
        QTextStream data(&file);
        QString mealName;

        while (!data.atEnd())
        {
            data >> mealName;
            meal->addItem(mealName);
            data.readLine(); //skip the rest of the line.
        }
    }

    file.close();
}
