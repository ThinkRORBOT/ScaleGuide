#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QVector>
#include <QSqlDatabase>
#include <QString>
#include <vector>
#include <string>
class DbManager
{
public:
    DbManager();

    QVector<QString> returnScales(int code);

private:
    QSqlDatabase db;

};

#endif // DBMANAGER_H
