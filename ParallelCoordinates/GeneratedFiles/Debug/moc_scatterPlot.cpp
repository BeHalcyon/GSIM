/****************************************************************************
** Meta object code from reading C++ file 'scatterPlot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../scatterPlot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scatterPlot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScatterPlot_t {
    QByteArrayData data[32];
    char stringdata0[326];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScatterPlot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScatterPlot_t qt_meta_stringdata_ScatterPlot = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ScatterPlot"
QT_MOC_LITERAL(1, 12, 7), // "sendIdx"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 3), // "idx"
QT_MOC_LITERAL(4, 25, 16), // "sendGlobalSelect"
QT_MOC_LITERAL(5, 42, 10), // "sendAGroup"
QT_MOC_LITERAL(6, 53, 11), // "vector<int>"
QT_MOC_LITERAL(7, 65, 5), // "group"
QT_MOC_LITERAL(8, 71, 10), // "sendGroups"
QT_MOC_LITERAL(9, 82, 20), // "vector<vector<int> >"
QT_MOC_LITERAL(10, 103, 6), // "groups"
QT_MOC_LITERAL(11, 110, 12), // "sendDistence"
QT_MOC_LITERAL(12, 123, 13), // "vector<float>"
QT_MOC_LITERAL(13, 137, 3), // "dis"
QT_MOC_LITERAL(14, 141, 17), // "getDistanceMatrix"
QT_MOC_LITERAL(15, 159, 6), // "float*"
QT_MOC_LITERAL(16, 166, 6), // "matrix"
QT_MOC_LITERAL(17, 173, 3), // "dim"
QT_MOC_LITERAL(18, 177, 30), // "vector<MaximalDimentionalSet*>"
QT_MOC_LITERAL(19, 208, 3), // "mds"
QT_MOC_LITERAL(20, 212, 8), // "getRange"
QT_MOC_LITERAL(21, 221, 3), // "vno"
QT_MOC_LITERAL(22, 225, 1), // "l"
QT_MOC_LITERAL(23, 227, 1), // "r"
QT_MOC_LITERAL(24, 229, 11), // "getCutValue"
QT_MOC_LITERAL(25, 241, 1), // "v"
QT_MOC_LITERAL(26, 243, 12), // "clusterSplit"
QT_MOC_LITERAL(27, 256, 12), // "clusterMerge"
QT_MOC_LITERAL(28, 269, 15), // "setPieChartShow"
QT_MOC_LITERAL(29, 285, 15), // "isPieChartShow_"
QT_MOC_LITERAL(30, 301, 14), // "setRepNodeOnly"
QT_MOC_LITERAL(31, 316, 9) // "simulShow"

    },
    "ScatterPlot\0sendIdx\0\0idx\0sendGlobalSelect\0"
    "sendAGroup\0vector<int>\0group\0sendGroups\0"
    "vector<vector<int> >\0groups\0sendDistence\0"
    "vector<float>\0dis\0getDistanceMatrix\0"
    "float*\0matrix\0dim\0vector<MaximalDimentionalSet*>\0"
    "mds\0getRange\0vno\0l\0r\0getCutValue\0v\0"
    "clusterSplit\0clusterMerge\0setPieChartShow\0"
    "isPieChartShow_\0setRepNodeOnly\0simulShow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScatterPlot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       5,    1,   85,    2, 0x06 /* Public */,
       8,    1,   88,    2, 0x06 /* Public */,
      11,    1,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    3,   94,    2, 0x0a /* Public */,
      20,    3,  101,    2, 0x0a /* Public */,
      24,    1,  108,    2, 0x0a /* Public */,
      26,    0,  111,    2, 0x0a /* Public */,
      27,    0,  112,    2, 0x0a /* Public */,
      28,    1,  113,    2, 0x0a /* Public */,
      30,    0,  116,    2, 0x0a /* Public */,
      31,    0,  117,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int, 0x80000000 | 18,   16,   17,   19,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   21,   22,   23,
    QMetaType::Void, QMetaType::Float,   25,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ScatterPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScatterPlot *_t = static_cast<ScatterPlot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendIdx((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sendGlobalSelect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sendAGroup((*reinterpret_cast< vector<int>(*)>(_a[1]))); break;
        case 3: _t->sendGroups((*reinterpret_cast< vector<vector<int> >(*)>(_a[1]))); break;
        case 4: _t->sendDistence((*reinterpret_cast< vector<float>(*)>(_a[1]))); break;
        case 5: _t->getDistanceMatrix((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< vector<MaximalDimentionalSet*>(*)>(_a[3]))); break;
        case 6: _t->getRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->getCutValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->clusterSplit(); break;
        case 9: _t->clusterMerge(); break;
        case 10: _t->setPieChartShow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->setRepNodeOnly(); break;
        case 12: _t->simulShow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScatterPlot::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScatterPlot::sendIdx)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ScatterPlot::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScatterPlot::sendGlobalSelect)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ScatterPlot::*_t)(vector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScatterPlot::sendAGroup)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ScatterPlot::*_t)(vector<vector<int>> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScatterPlot::sendGroups)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ScatterPlot::*_t)(vector<float> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScatterPlot::sendDistence)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject ScatterPlot::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ScatterPlot.data,
      qt_meta_data_ScatterPlot,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ScatterPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScatterPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ScatterPlot.stringdata0))
        return static_cast<void*>(const_cast< ScatterPlot*>(this));
    return QWidget::qt_metacast(_clname);
}

int ScatterPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ScatterPlot::sendIdx(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScatterPlot::sendGlobalSelect(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScatterPlot::sendAGroup(vector<int> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ScatterPlot::sendGroups(vector<vector<int>> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ScatterPlot::sendDistence(vector<float> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
