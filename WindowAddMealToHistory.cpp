#include "WindowAddMealToHistory.h"

WindowAddMealToHistory::WindowAddMealToHistory() : QWidget() {
    date = new QDateEdit(QDate::currentDate());
    meal = new QComboBox;
    this->GetMealsToComboBox();

    formLayout = new QFormLayout;
    formLayout->addRow("Date", date);
    formLayout->addRow("Repas", meal);

    btn_add = new QPushButton("Ajouter");

    mainLayout = new QGridLayout;
    mainLayout->addLayout(formLayout, 0, 0);
    mainLayout->addWidget(btn_add, 1, 0);

    this->setLayout(mainLayout);

    // Signals.
    QObject::connect(btn_add, SIGNAL(clicked()), this, SLOT(addToMealToHistory()));
}

void WindowAddMealToHistory::addToMealToHistory() {
    QFile file("storage/meal_history.dat");
    if (!QDir("storage").exists())
        QDir().mkdir("storage");

    file.open(QIODevice::Append);

    // New version.
    QDataStream data(&file);
    data << QDate(date->date());
    data << QString(meal->currentText());

    /* Old version.
    // Date.
    file.write(date->date().toString(Qt::ISODate).toUtf8() +"\t");
    // Meal.
    file.write(meal->currentText().toUtf8() + "\n");
    */

    file.close();
    this->close();
}

void WindowAddMealToHistory::GetMealsToComboBox() {
    QFile file("storage/meal_list.txt");

    if (file.open(QFile::ReadOnly)) {
        QTextStream data(&file);
        QString mealName;

        while (!data.atEnd()) {
            data >> mealName;
            meal->addItem(mealName);
            data.readLine(); //skip the rest of the line.
        }
    }
    file.close();
}
