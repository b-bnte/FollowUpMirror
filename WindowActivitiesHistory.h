#ifndef WINDOWACTIVITIESHISTORY_H
#define WINDOWACTIVITIESHISTORY_H

#include <QApplication>
#include <QWidget>
//#include <QLineEdit>
//#include <QPushButton>
//#include <QVBoxLayout>
//#include <QFormLayout>
//#include <QDateEdit>
//#include <QDate>
#include <QGridLayout>
//#include <QSpinBox>
//#include <QComboBox>
#include <QLabel>
#include <QFile>
#include <QDir>
#include <QDebug>

class WindowActivitiesHistory : public QWidget
{
    Q_OBJECT
    public:
    WindowActivitiesHistory();
    void ReadToDataFileStorage();


    private slots:

    signals:

    private:
    QGridLayout *mainLayout;
    QLabel *label_test;

    QVector<QLabel*> labelDate;
    QVector<QLabel*> labelType;
    QVector<QLabel*> labelDuration;
    QVector<QLabel*> labelKcalories;



};

#endif // WINDOWACTIVITIESHISTORY_H
