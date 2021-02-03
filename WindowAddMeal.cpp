#include "WindowAddMeal.h"

WindowAddMeal::WindowAddMeal() : QWidget()
{
    // Creation of a FormLayout.
    name = new QLineEdit;
    calories = new QSpinBox;
    carbs = new QSpinBox;
    protein = new QSpinBox;
    lipid = new QSpinBox;
    btn_add = new QPushButton("Ajouter");

    // Set range QSpinBox.
    calories->setMaximum(50000);
    carbs->setMaximum(900);
    protein->setMaximum(900);
    lipid->setMaximum(900);

    // Add to FormLayout.
    formLayout = new QFormLayout;
    formLayout->addRow("name", name);
    formLayout->addRow("calories (kcal)", calories);
    formLayout->addRow("carbs (g)", carbs);
    formLayout->addRow("protein (g)", protein);
    formLayout->addRow("lipid (g)", lipid);
    formLayout->addRow(btn_add);

    this->setLayout(formLayout);

    // Signals.
    QObject::connect(btn_add, SIGNAL(clicked()), this, SLOT(addToMealList()));
}

void WindowAddMeal::addToMealList()
{
    QFile file("storage/meal_list.txt");
    if (!QDir("storage").exists())
        QDir().mkdir("storage");

    file.open(QIODevice::Append);

    // Name.
    file.write(name->text().replace(" ", "_").toUtf8() + "\t");
    // Calories.
    file.write(calories->text().toUtf8() + "\t");
    // Carbs.
    file.write(carbs->text().toUtf8() + "\t");
    // Protein.
    file.write(protein->text().toUtf8() + "\t");
    // Lipid.
    file.write(lipid->text().toUtf8() + "\n");

    file.close();
    this->close();
}
