#include "WindowActivitiesHistory.h"

WindowActivitiesHistory::WindowActivitiesHistory(): QWidget(){
    //label_test = new QLabel("date\t\tType\t\t Durer(min)\t\tEnergie(Kcal)");
    //label_test->setStyleSheet("QLabel {color : black; background-color : grey}");

    mainLayout = new QGridLayout;
    //mainLayout->addWidget(label_test,0,0);
    //this->setLayout(mainLayout);



    this->ReadToDataFileStorage();
    this->setLayout(mainLayout);



}

void WindowActivitiesHistory::ReadToDataFileStorage(){
    QFile file("storage/activity_history.dat");
    QDataStream dataRead(&file);
    QDate dateRead;
    QString typeOfActivityRead;
    int durationOfActivityRead;

    int kcaloriesOfActivityRead;

    //label_Activity << new QLabel(this);



    file.open(QIODevice::ReadOnly);
    QDataStream data(&file);
    labelDate<< new QLabel("Date");
    labelDate[0]->setStyleSheet("QLabel {color : black; background-color : grey}");
    mainLayout->addWidget(labelDate[0],0,0);


    labelType<< new QLabel("Type");
    labelType[0]->setStyleSheet("QLabel {color : black; background-color : grey}");
    mainLayout->addWidget(labelType[0],0,1);

    labelDuration<< new QLabel("durée(min)");
    labelDuration[0]->setStyleSheet("QLabel {color : black; background-color : grey}");
    mainLayout->addWidget(labelDuration[0],0,2);

    labelKcalories<< new QLabel("Energie(Kcal)");
    labelKcalories[0]->setStyleSheet("QLabel {color : black; background-color : grey}");
    mainLayout->addWidget(labelKcalories[0],0,3);
    int taille=8;
    float NGrey;
    for(int i=1; i<=taille && !data.atEnd();i++){
        qDebug () << i;
        NGrey=i*255;
        qDebug () << NGrey;
        QString Grey="QLabel {color : rgba("
                      + QString::number(0)+ ","
                      + QString::number(0)+ ","
                      + QString::number(0)+ ","
                      + QString::number(int((taille-i)*255/taille))+ ")}";
        qDebug () << Grey;
        dataRead >> dateRead;
        qDebug () << dateRead;
        labelDate<< new QLabel(dateRead.toString());
        labelDate[i]->setStyleSheet(Grey);
        labelDate[i]->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(labelDate[i],i,0);


        dataRead >> typeOfActivityRead;
        qDebug () << typeOfActivityRead;
        labelType<< new QLabel(typeOfActivityRead);
        labelType[i]->setStyleSheet(Grey);
        labelType[i]->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(labelType[i],i,1);

        dataRead >> durationOfActivityRead;
        qDebug () << durationOfActivityRead << "min";
        labelDuration<< new QLabel(QString::number(durationOfActivityRead));
        labelDuration[i]->setStyleSheet(Grey);
        labelDuration[i]->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(labelDuration[i],i,2);

        dataRead >> kcaloriesOfActivityRead;
        qDebug () << kcaloriesOfActivityRead << "kcal";
        labelKcalories<< new QLabel(QString::number(kcaloriesOfActivityRead));
        labelKcalories[i]->setStyleSheet(Grey);
        labelKcalories[i]->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(labelKcalories[i],i,3);

        qDebug () << "------";
        //label_Activity[i]->setText();
    }
     qDebug () << "banana\n";

}
