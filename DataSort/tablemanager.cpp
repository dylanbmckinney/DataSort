// Dylan McKinney
// 8-26-2018
#include "tablemanager.h"

TableManager::TableManager(QObject *parent): QThread(parent)
{
}

TableManager::TableManager(QObject *parent, QJsonArray &arr, QTableWidget *table): TableManager(parent)
{
    mArr = arr;
    dataTable = table;
}

TableManager::~TableManager()
{
}

void TableManager::run()
{
    // Erase the current table completely
    dataTable->clear();
    if (!mArr.isEmpty()){
        // Establish number of entries
        dataTable->setRowCount(mArr.count());
        if(mArr[0].isObject()){
            // Create columns, under the assumption that data keys are consistent with first element
            QStringList keys = mArr[0].toObject().keys();
            dataTable->setColumnCount(keys.count());
            dataTable->setHorizontalHeaderLabels(keys);
            dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
            dataTable->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            // Iterate through elements of the array
            for(int i = 0; i < mArr.count(); ++i){
                if(!mArr[i].isObject()){
                    return;
                }
                QJsonObject object = mArr[i].toObject();
                // Adjust columns if data entry has more keys than the first, may affect sorting
                if(object.keys().count() > keys.count()){
                    keys = object.keys();
                    dataTable->setColumnCount(keys.count());
                    dataTable->setHorizontalHeaderLabels(keys);
                }
                // Iterate by column for each row
                for(int j = 0; j < keys.count(); ++j){
                    if(object.keys().count() > j){
                        // Obtain value from the key corresponding to the column
                        QJsonValue value = object[keys[j]];
                        // Create the item to be stored in this cell
                        QTableWidgetItem *item = nullptr;
                        if(value.isBool()){
                            item = new QTableWidgetItem(QString(value.toBool()));
                        }else if (value.isDouble()){
                            item = new QTableWidgetItem(QString::number(value.toDouble()));
                        }else if (value.isString()){
                            item = new QTableWidgetItem(value.toString());
                        } else if (value.isNull() || value.isUndefined()){
                            item = new QTableWidgetItem(QString());
                        } else if (value.isObject() || value.isArray()){
                            QJsonDocument toDoc(value.toObject());
                            item = new QTableWidgetItem(QString(toDoc.toJson(QJsonDocument::Indented)));
                        } else {
                            return;
                        }
                        // Store item in the cell
                        dataTable->setItem(i, j, item);
                    }
                }
            }
        } else {
            return;
        }
    } else {
        return;
    }
    // Signal completion of table generation
    emit done();
}
