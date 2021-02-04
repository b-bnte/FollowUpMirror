#ifndef WINDOWADDACTIVITIES_H
#define WINDOWADDACTIVITIES_H

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QDateEdit>
#include <QDate>
#include <QGridLayout>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QFile>
#include <QDir>
#include <QDebug>

class WindowAddActivities : public QWidget
{
    Q_OBJECT

    public:
    WindowAddActivities();

    private slots:
    void updateLabelMET (int index);
    void calculateCalories ();
    void addToDataFileStorage ();

    private:
    QGridLayout *mainLayout;
    QFormLayout *formLayout;
    QDateEdit *date;
    QComboBox *activity;
    QSpinBox *duration;
    QPushButton *btn_calculate;
    QPushButton *btn_add;
    QPushButton *btn_quit;
    QLabel *label_kcalories;
    QLabel *label_met;

    // Activity & Mets.
    struct sActivityMET {
        QString name;
        float MET;
    };

    std::array<sActivityMET, 9> tabActtivityMET = {
        sActivityMET{ "cyclisme" , 8},
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
