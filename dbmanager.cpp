#include "dbmanager.h"
#include<QSqlDatabase>
#include<QDir>
#include<QString>
#include<string>
#include<vector>
#include<QVector>
#include<QString>
#include<QSqlQuery>
#include<QMessageBox>
#include<QFileInfo>
#include<QVariant>
#include<QDebug>

DbManager::DbManager()
{
    //QString path = fileinfo.absoluteFilePath();
    //qDebug(path.toLatin1());

    //sets up the database connection
    db = QSqlDatabase::addDatabase("QSQLITE");
    //replace path with where this is located on your file system
    db.setDatabaseName("F:/Projects/Programming/cpp/ScaleGuide/Databases/note_to_scale.db");

    if(!db.open()){
        qDebug("Error: connection with database failed");
    } else {
        qDebug("Database: connection ok");
    }



}

//returns a set of notes of a certain scale
QVector<QString> DbManager::returnNotes(std::string *scale_arr){
    QVector<QString> notes(14);
    if(!db.open()) {
        notes.append("NDB");
        return notes;
    }

    notes.append("temp");
    //QSqlQuery query;
}

//todo: get sqlite data into a vector and see if one vector contains another, change qvectors to vectors
//returns a scale for a given set of notes.
std::vector<std::string> DbManager::returnScales(int code){
    std::vector<std::string> scales(7);
    if(!db.open()) {
        scales[0] = "NDB";
        return scales;
    }

    QSqlQuery query;



    QString queryString = "SELECT \"" + QString::number(code) + "\" FROM Scales";

    query.exec(queryString);

    int i = 0;

    int length = query.size();
    qDebug() << QString::number(length);
    //todo, find what is wrong with sql query
    while (query.next()) {
        QString response = query.value(0).toString();
        scales[i] = response.toStdString();
        qDebug() << response;
        i++;
    }

    return scales;


}
