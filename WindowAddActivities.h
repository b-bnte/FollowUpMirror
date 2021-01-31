#ifndef WINDOWADDACTIVITIES_H
#define WINDOWADDACTIVITIES_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDateEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QFile>

#include <iostream>
#include <cmath>

class WindowAddActivities : public QWidget
{
    Q_OBJECT

    public:
    WindowAddActivities();

    public slots:
    void updateLabelMET (int index);
    void calculateCalories ();
    void addToDataFileStorage ();

    signals:

    private:
    // Grid Layout (main layout).
    QGridLayout *layout = new QGridLayout;

    // Creation of a FormLayout.
    QFormLayout *formLayout;
    QDateEdit *date;
    QComboBox *activity;
    QSpinBox *duration;

    // Buttons.
    QPushButton *btn_calculate = new QPushButton("Calculer");
    QPushButton *btn_add = new QPushButton("Ajouter");
    QPushButton *btn_quit = new QPushButton("Quitter");

    // Labels
    QLabel *label_kcalories = new QLabel("... kcal");
    QLabel *label_met = new QLabel("MET : ...");

    // Activity & Mets.
    struct sActivityMET {
        QString name;
        float MET;
    };

    std::array<sActivityMET, 10> tabActtivityMET = {
        sActivityMET{ "cyclisme" , 8},
        sActivityMET{ "course à pied", 8},
        sActivityMET{ "dormir", 0.9},
        sActivityMET{ "pêche", 3},
        sActivityMET{ "basketball", 6},
        sActivityMET{ "curling", 4},
        sActivityMET{ "football", 8},
        sActivityMET{ "rugby", 10},
        sActivityMET{ "tennis", 7},
        sActivityMET{ "marche", 3}
      };

};

#endif // WINDOWADDACTIVITIES_H
