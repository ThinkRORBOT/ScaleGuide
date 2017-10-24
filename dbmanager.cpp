#include "dbmanager.h"
#include<QSqlDatabase>
#include<QDir>

DbManager::DbManager()
{
    db = QSqlDatabase::addDatabase("ScaleDB");
    db.setDatabaseName("Databases/note_to_scale");

    if(db.open()){
        qDebug("Error: connection with database failed");
    } else {
        qDebug("Database: connection ok");
    }

}
