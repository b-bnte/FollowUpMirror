#include "WindowAddActivities.h"

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

    WindowAddActivities windowAddActivities;
    windowAddActivities.show();

    // test

    return app.exec();
}
