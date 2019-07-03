/****************************************************************************
** Meta object code from reading C++ file 'parallelCoordinate.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../parallelCoordinate.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'parallelCoordinate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ParallelCoordinate_t {
    QByteArrayData data[33];
    char stringdata0[341];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParallelCoordinate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParallelCoordinate_t qt_meta_stringdata_ParallelCoordinate = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ParallelCoordinate"
QT_MOC_LITERAL(1, 19, 15), // "volRegionChange"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 11), // "TFIDChanged"
QT_MOC_LITERAL(4, 48, 3), // "idx"
QT_MOC_LITERAL(5, 52, 10), // "getCCScore"
QT_MOC_LITERAL(6, 63, 12), // "vector<int>&"
QT_MOC_LITERAL(7, 76, 6), // "voxels"
QT_MOC_LITERAL(8, 83, 9), // "variables"
QT_MOC_LITERAL(9, 93, 6), // "float&"
QT_MOC_LITERAL(10, 100, 5), // "score"
QT_MOC_LITERAL(11, 106, 9), // "sendRange"
QT_MOC_LITERAL(12, 116, 1), // "v"
QT_MOC_LITERAL(13, 118, 1), // "r"
QT_MOC_LITERAL(14, 120, 1), // "l"
QT_MOC_LITERAL(15, 122, 11), // "setVolDatas"
QT_MOC_LITERAL(16, 134, 16), // "vector<Volume*>&"
QT_MOC_LITERAL(17, 151, 4), // "vols"
QT_MOC_LITERAL(18, 156, 14), // "setFilterDatas"
QT_MOC_LITERAL(19, 171, 4), // "int*"
QT_MOC_LITERAL(20, 176, 4), // "mIdx"
QT_MOC_LITERAL(21, 181, 4), // "cIdx"
QT_MOC_LITERAL(22, 186, 7), // "fColNum"
QT_MOC_LITERAL(23, 194, 16), // "setClusterVoxels"
QT_MOC_LITERAL(24, 211, 11), // "vector<int>"
QT_MOC_LITERAL(25, 223, 10), // "attributes"
QT_MOC_LITERAL(26, 234, 17), // "setGlobalClusters"
QT_MOC_LITERAL(27, 252, 20), // "vector<vector<int> >"
QT_MOC_LITERAL(28, 273, 7), // "gvoxels"
QT_MOC_LITERAL(29, 281, 11), // "gattributes"
QT_MOC_LITERAL(30, 293, 13), // "setAllDisplay"
QT_MOC_LITERAL(31, 307, 14), // "setPartDisplay"
QT_MOC_LITERAL(32, 322, 18) // "setArrangedDisplay"

    },
    "ParallelCoordinate\0volRegionChange\0\0"
    "TFIDChanged\0idx\0getCCScore\0vector<int>&\0"
    "voxels\0variables\0float&\0score\0sendRange\0"
    "v\0r\0l\0setVolDatas\0vector<Volume*>&\0"
    "vols\0setFilterDatas\0int*\0mIdx\0cIdx\0"
    "fColNum\0setClusterVoxels\0vector<int>\0"
    "attributes\0setGlobalClusters\0"
    "vector<vector<int> >\0gvoxels\0gattributes\0"
    "setAllDisplay\0setPartDisplay\0"
    "setArrangedDisplay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParallelCoordinate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    1,   70,    2, 0x06 /* Public */,
       5,    3,   73,    2, 0x06 /* Public */,
      11,    3,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    1,   87,    2, 0x0a /* Public */,
      18,    3,   90,    2, 0x0a /* Public */,
      23,    2,   97,    2, 0x0a /* Public */,
      26,    2,  102,    2, 0x0a /* Public */,
      30,    0,  107,    2, 0x0a /* Public */,
      31,    0,  108,    2, 0x0a /* Public */,
      32,    0,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6, 0x80000000 | 9,    7,    8,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,   12,   13,   14,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 19, 0x80000000 | 19, QMetaType::Int,   20,   21,   22,
    QMetaType::Void, 0x80000000 | 24, 0x80000000 | 24,    7,   25,
    QMetaType::Void, 0x80000000 | 27, 0x80000000 | 27,   28,   29,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ParallelCoordinate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ParallelCoordinate *_t = static_cast<ParallelCoordinate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->volRegionChange(); break;
        case 1: _t->TFIDChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->getCCScore((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< vector<int>(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 3: _t->sendRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->setVolDatas((*reinterpret_cast< vector<Volume*>(*)>(_a[1]))); break;
        case 5: _t->setFilterDatas((*reinterpret_cast< int*(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 6: _t->setClusterVoxels((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< vector<int>(*)>(_a[2]))); break;
        case 7: _t->setGlobalClusters((*reinterpret_cast< vector<vector<int> >(*)>(_a[1])),(*reinterpret_cast< vector<vector<int> >(*)>(_a[2]))); break;
        case 8: _t->setAllDisplay(); break;
        case 9: _t->setPartDisplay(); break;
        case 10: _t->setArrangedDisplay(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ParallelCoordinate::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParallelCoordinate::volRegionChange)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ParallelCoordinate::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParallelCoordinate::TFIDChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ParallelCoordinate::*_t)(vector<int> & , vector<int> & , float & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParallelCoordinate::getCCScore)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ParallelCoordinate::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParallelCoordinate::sendRange)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ParallelCoordinate::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ParallelCoordinate.data,
      qt_meta_data_ParallelCoordinate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ParallelCoordinate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParallelCoordinate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ParallelCoordinate.stringdata0))
        return static_cast<void*>(const_cast< ParallelCoordinate*>(this));
    return QWidget::qt_metacast(_clname);
}

int ParallelCoordinate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ParallelCoordinate::volRegionChange()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ParallelCoordinate::TFIDChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ParallelCoordinate::getCCScore(vector<int> & _t1, vector<int> & _t2, float & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ParallelCoordinate::sendRange(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
