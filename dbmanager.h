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

    std::vector<std::string> returnScales(int code);
    QVector<QString> returnNotes(std::string *note_arr);

private:
    QSqlDatabase db;

};

#endif // DBMANAGER_H
