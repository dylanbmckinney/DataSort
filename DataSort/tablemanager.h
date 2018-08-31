// Dylan McKinney
// 8-26-2018
#ifndef TABLEMANAGER_H
#define TABLEMANAGER_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTableWidget>
#include <QHeaderView>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QVector>

class TableManager : public QThread
{
    Q_OBJECT
public:
    explicit TableManager(QObject* parent = nullptr);
    TableManager(QObject* parent, QJsonArray& arr, QTableWidget* table);
    ~TableManager();
    void run(); // Begin thread execution when start() is called

signals:
    void done(); // Emitted once the table is populated with the new data

private:
    QJsonArray mArr; // Data to be loaded into table
    QTableWidget* dataTable = nullptr; // Table in which the data will be stored
};

#endif // TABLEMANAGER
