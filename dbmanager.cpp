#include "dbmanager.h"
#include<QSqlDatabase>
#include<QDir>
#include<QtCore>
#include<QCoreApplication>
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
#include<QFile>

DbManager::DbManager()
{
    //QString path = fileinfo.absoluteFilePath();
    //qDebug(path.toLatin1());

    //sets up the database connection
    db = QSqlDatabase::addDatabase("QSQLITE");

    dbPath = QCoreApplication::applicationDirPath()+"/note_to_scale.db";
    qDebug() << dbPath;
    if (QFile::exists(dbPath))
    {
        QFile::remove(dbPath);
    }

    //replace path with where this is located on your file system
    //db.setDatabaseName("F:/Projects/Programming/cpp/ScaleGuide/Databases/note_to_scale.db");
    if (!QFile::copy(":/note_to_scale.db", dbPath)) {
        QMessageBox msgbox;
        msgbox.setText("Could not copy database to path");
        msgbox.setStandardButtons(QMessageBox::Ok);
        int ret = msgbox.exec();
    }

    db.setDatabaseName(dbPath);
    qDebug() << QCoreApplication::applicationDirPath();
    if(!db.open()){
        qDebug("Error: connection with database failed");
        QMessageBox msgBox;
        msgBox.setText("Error, Database connection failed, please redownload application");
        msgBox.exec();
    } else {
        qDebug("Database: connection ok");
    }



}

//returns a set of notes in a certain scale
QVector<QString> DbManager::returnScales(int code){
    QVector<QString> scales(7);
    if(!db.open()) {
        scales[0] = "NDB";
        return scales;
    }

    QSqlQuery query;

    QString queryString = "SELECT \"" + QString::number(code) + "\" FROM Scales ORDER BY \"13\" ASC";

    query.exec(queryString);

    int i = 0;

    int length = query.size();
    qDebug() << QString::number(length);
    //todo, find what is wrong with sql query
    while (query.next()) {
        QString response = query.value(0).toString();
        scales[i] = response;
        qDebug() << response;
        i++;
    }

    return scales;

}
