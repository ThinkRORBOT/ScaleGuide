#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QVector>
#include <QSqlDatabase>
#include <QString>
#include <vector>
#include <string>
#include <QMessageBox>
#include <QFile>

class DbManager
{
public:
    DbManager();

    QVector<QString> returnScales(int code);

private:
    QSqlDatabase db;
    QString dbPath;

};

#endif // DBMANAGER_H
