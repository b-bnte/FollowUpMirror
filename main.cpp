#include "WindowAddActivities.h"
#include "MainWindow.h"
#include "WindowAddMeal.h"
#include "WindowAddMealToHistory.h"

#include <QApplication>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDateEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Test for adding activities.
    //WindowAddMealToHistory windowAddActivities;
    //windowAddActivities.show();



    // Main Window.
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
