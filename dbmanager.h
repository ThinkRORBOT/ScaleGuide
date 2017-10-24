#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QVector>
#include <QSqlDatabase>
#include <QString>

class DbManager
{
public:
    DbManager();

    QVector<QString> returnScales();
    QVector<QString> returnNotes();

private:
    QSqlDatabase db;

};

#endif // DBMANAGER_H
