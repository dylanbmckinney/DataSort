/****************************************************************************
** Meta object code from reading C++ file 'datasort.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../DataSort/datasort.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'datasort.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataSort_t {
    QByteArrayData data[12];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataSort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataSort_t qt_meta_stringdata_DataSort = {
    {
QT_MOC_LITERAL(0, 0, 8), // "DataSort"
QT_MOC_LITERAL(1, 9, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 13), // "headerClicked"
QT_MOC_LITERAL(4, 48, 23), // "on_cancelButton_clicked"
QT_MOC_LITERAL(5, 72, 13), // "onSortingDone"
QT_MOC_LITERAL(6, 86, 11), // "onTableDone"
QT_MOC_LITERAL(7, 98, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(8, 122, 10), // "onProgress"
QT_MOC_LITERAL(9, 133, 23), // "on_spinBox_valueChanged"
QT_MOC_LITERAL(10, 157, 4), // "arg1"
QT_MOC_LITERAL(11, 162, 26) // "on_actionSave_as_triggered"

    },
    "DataSort\0on_actionOpen_triggered\0\0"
    "headerClicked\0on_cancelButton_clicked\0"
    "onSortingDone\0onTableDone\0"
    "on_actionExit_triggered\0onProgress\0"
    "on_spinBox_valueChanged\0arg1\0"
    "on_actionSave_as_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataSort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    1,   60,    2, 0x08 /* Private */,
       4,    0,   63,    2, 0x08 /* Private */,
       5,    1,   64,    2, 0x08 /* Private */,
       6,    0,   67,    2, 0x08 /* Private */,
       7,    0,   68,    2, 0x08 /* Private */,
       8,    2,   69,    2, 0x08 /* Private */,
       9,    1,   74,    2, 0x08 /* Private */,
      11,    0,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,

       0        // eod
};

void DataSort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DataSort *_t = static_cast<DataSort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionOpen_triggered(); break;
        case 1: _t->headerClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_cancelButton_clicked(); break;
        case 3: _t->onSortingDone((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onTableDone(); break;
        case 5: _t->on_actionExit_triggered(); break;
        case 6: _t->onProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->on_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_actionSave_as_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataSort::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_DataSort.data,
      qt_meta_data_DataSort,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DataSort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataSort::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataSort.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int DataSort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
