/****************************************************************************
** Meta object code from reading C++ file 'biclusters.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../biclusters.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'biclusters.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Bicluster_t {
    QByteArrayData data[59];
    char stringdata0[703];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Bicluster_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Bicluster_t qt_meta_stringdata_Bicluster = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Bicluster"
QT_MOC_LITERAL(1, 10, 13), // "sendMaxDegree"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 4), // "maxd"
QT_MOC_LITERAL(4, 30, 19), // "clusterRegionChange"
QT_MOC_LITERAL(5, 50, 17), // "sendClusterVoxels"
QT_MOC_LITERAL(6, 68, 11), // "vector<int>"
QT_MOC_LITERAL(7, 80, 13), // "clusterVoxels"
QT_MOC_LITERAL(8, 94, 17), // "clusterAttributes"
QT_MOC_LITERAL(9, 112, 17), // "sendGlobalCluster"
QT_MOC_LITERAL(10, 130, 20), // "vector<vector<int> >"
QT_MOC_LITERAL(11, 151, 18), // "sendVariateSubsets"
QT_MOC_LITERAL(12, 170, 15), // "vector<VSubset>"
QT_MOC_LITERAL(13, 186, 14), // "variateSubsets"
QT_MOC_LITERAL(14, 201, 18), // "sendDistanceMatrix"
QT_MOC_LITERAL(15, 220, 6), // "float*"
QT_MOC_LITERAL(16, 227, 1), // "m"
QT_MOC_LITERAL(17, 229, 3), // "dim"
QT_MOC_LITERAL(18, 233, 15), // "sendFilterDatas"
QT_MOC_LITERAL(19, 249, 4), // "int*"
QT_MOC_LITERAL(20, 254, 4), // "mIdx"
QT_MOC_LITERAL(21, 259, 4), // "cIdx"
QT_MOC_LITERAL(22, 264, 7), // "fColNum"
QT_MOC_LITERAL(23, 272, 30), // "vector<MaximalDimentionalSet*>"
QT_MOC_LITERAL(24, 303, 3), // "mds"
QT_MOC_LITERAL(25, 307, 11), // "setVolDatas"
QT_MOC_LITERAL(26, 319, 16), // "vector<Volume*>&"
QT_MOC_LITERAL(27, 336, 4), // "vols"
QT_MOC_LITERAL(28, 341, 18), // "SelectedVariatesNo"
QT_MOC_LITERAL(29, 360, 10), // "selectedNo"
QT_MOC_LITERAL(30, 371, 17), // "getVariateSubsets"
QT_MOC_LITERAL(31, 389, 12), // "getClusterNo"
QT_MOC_LITERAL(32, 402, 2), // "No"
QT_MOC_LITERAL(33, 405, 14), // "calCorrelation"
QT_MOC_LITERAL(34, 420, 8), // "variates"
QT_MOC_LITERAL(35, 429, 6), // "float&"
QT_MOC_LITERAL(36, 436, 4), // "corr"
QT_MOC_LITERAL(37, 441, 12), // "calCoherence"
QT_MOC_LITERAL(38, 454, 3), // "coh"
QT_MOC_LITERAL(39, 458, 21), // "calCorrelationPearson"
QT_MOC_LITERAL(40, 480, 15), // "getGlobalSelect"
QT_MOC_LITERAL(41, 496, 3), // "idx"
QT_MOC_LITERAL(42, 500, 9), // "getAGroup"
QT_MOC_LITERAL(43, 510, 6), // "agroup"
QT_MOC_LITERAL(44, 517, 15), // "getGlobalGroups"
QT_MOC_LITERAL(45, 533, 6), // "groups"
QT_MOC_LITERAL(46, 540, 12), // "getMaxORatio"
QT_MOC_LITERAL(47, 553, 5), // "ratio"
QT_MOC_LITERAL(48, 559, 12), // "getMinORatio"
QT_MOC_LITERAL(49, 572, 10), // "calCCScore"
QT_MOC_LITERAL(50, 583, 12), // "vector<int>&"
QT_MOC_LITERAL(51, 596, 6), // "voxels"
QT_MOC_LITERAL(52, 603, 9), // "variables"
QT_MOC_LITERAL(53, 613, 5), // "score"
QT_MOC_LITERAL(54, 619, 19), // "setSubsetsContained"
QT_MOC_LITERAL(55, 639, 12), // "iscontained_"
QT_MOC_LITERAL(56, 652, 22), // "setJaccardDistanceUsed"
QT_MOC_LITERAL(57, 675, 14), // "isJaccardUsed_"
QT_MOC_LITERAL(58, 690, 12) // "getGSIMValue"

    },
    "Bicluster\0sendMaxDegree\0\0maxd\0"
    "clusterRegionChange\0sendClusterVoxels\0"
    "vector<int>\0clusterVoxels\0clusterAttributes\0"
    "sendGlobalCluster\0vector<vector<int> >\0"
    "sendVariateSubsets\0vector<VSubset>\0"
    "variateSubsets\0sendDistanceMatrix\0"
    "float*\0m\0dim\0sendFilterDatas\0int*\0"
    "mIdx\0cIdx\0fColNum\0vector<MaximalDimentionalSet*>\0"
    "mds\0setVolDatas\0vector<Volume*>&\0vols\0"
    "SelectedVariatesNo\0selectedNo\0"
    "getVariateSubsets\0getClusterNo\0No\0"
    "calCorrelation\0variates\0float&\0corr\0"
    "calCoherence\0coh\0calCorrelationPearson\0"
    "getGlobalSelect\0idx\0getAGroup\0agroup\0"
    "getGlobalGroups\0groups\0getMaxORatio\0"
    "ratio\0getMinORatio\0calCCScore\0"
    "vector<int>&\0voxels\0variables\0score\0"
    "setSubsetsContained\0iscontained_\0"
    "setJaccardDistanceUsed\0isJaccardUsed_\0"
    "getGSIMValue"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Bicluster[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      25,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  139,    2, 0x06 /* Public */,
       4,    0,  142,    2, 0x06 /* Public */,
       5,    2,  143,    2, 0x06 /* Public */,
       9,    2,  148,    2, 0x06 /* Public */,
      11,    1,  153,    2, 0x06 /* Public */,
      14,    2,  156,    2, 0x06 /* Public */,
      18,    3,  161,    2, 0x06 /* Public */,
      14,    3,  168,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      25,    1,  175,    2, 0x0a /* Public */,
      25,    0,  178,    2, 0x0a /* Public */,
      28,    1,  179,    2, 0x0a /* Public */,
      30,    0,  182,    2, 0x0a /* Public */,
      31,    1,  183,    2, 0x0a /* Public */,
      33,    2,  186,    2, 0x0a /* Public */,
      37,    2,  191,    2, 0x0a /* Public */,
      39,    2,  196,    2, 0x0a /* Public */,
      40,    1,  201,    2, 0x0a /* Public */,
      42,    1,  204,    2, 0x0a /* Public */,
      44,    1,  207,    2, 0x0a /* Public */,
      46,    1,  210,    2, 0x0a /* Public */,
      48,    1,  213,    2, 0x0a /* Public */,
      49,    3,  216,    2, 0x0a /* Public */,
      54,    1,  223,    2, 0x0a /* Public */,
      56,    1,  226,    2, 0x0a /* Public */,
      58,    1,  229,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    8,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10,    7,    8,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int,   16,   17,
    QMetaType::Void, 0x80000000 | 19, 0x80000000 | 19, QMetaType::Int,   20,   21,   22,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int, 0x80000000 | 23,   16,   17,   24,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   32,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 35,   34,   36,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 35,   34,   38,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 35,   34,   36,
    QMetaType::Void, QMetaType::Int,   41,
    QMetaType::Void, 0x80000000 | 6,   43,
    QMetaType::Void, 0x80000000 | 10,   45,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void, QMetaType::Double,   47,
    QMetaType::Void, 0x80000000 | 50, 0x80000000 | 50, 0x80000000 | 35,   51,   52,   53,
    QMetaType::Void, QMetaType::Int,   55,
    QMetaType::Void, QMetaType::Int,   57,
    QMetaType::Void, QMetaType::Float,    2,

       0        // eod
};

void Bicluster::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Bicluster *_t = static_cast<Bicluster *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMaxDegree((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->clusterRegionChange(); break;
        case 2: _t->sendClusterVoxels((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< vector<int>(*)>(_a[2]))); break;
        case 3: _t->sendGlobalCluster((*reinterpret_cast< vector<vector<int> >(*)>(_a[1])),(*reinterpret_cast< vector<vector<int> >(*)>(_a[2]))); break;
        case 4: _t->sendVariateSubsets((*reinterpret_cast< vector<VSubset>(*)>(_a[1]))); break;
        case 5: _t->sendDistanceMatrix((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->sendFilterDatas((*reinterpret_cast< int*(*)>(_a[1])),(*reinterpret_cast< int*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 7: _t->sendDistanceMatrix((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< vector<MaximalDimentionalSet*>(*)>(_a[3]))); break;
        case 8: _t->setVolDatas((*reinterpret_cast< vector<Volume*>(*)>(_a[1]))); break;
        case 9: _t->setVolDatas(); break;
        case 10: _t->SelectedVariatesNo((*reinterpret_cast< vector<int>(*)>(_a[1]))); break;
        case 11: _t->getVariateSubsets(); break;
        case 12: _t->getClusterNo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->calCorrelation((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 14: _t->calCoherence((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 15: _t->calCorrelationPearson((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 16: _t->getGlobalSelect((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->getAGroup((*reinterpret_cast< vector<int>(*)>(_a[1]))); break;
        case 18: _t->getGlobalGroups((*reinterpret_cast< vector<vector<int> >(*)>(_a[1]))); break;
        case 19: _t->getMaxORatio((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 20: _t->getMinORatio((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 21: _t->calCCScore((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< vector<int>(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 22: _t->setSubsetsContained((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->setJaccardDistanceUsed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->getGSIMValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Bicluster::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bicluster::sendMaxDegree)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Bicluster::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bicluster::clusterRegionChange)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Bicluster::*_t)(vector<int> , vector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bicluster::sendClusterVoxels)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Bicluster::*_t)(vector<vector<int>> , vector<vector<int>> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bicluster::sendGlobalCluster)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Bicluster::*_t)(vector<VSubset> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bicluster::sendVariateSubsets)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (Bicluster::*_t)(float * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bicluster::sendDistanceMatrix)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (Bicluster::*_t)(int * , int * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bicluster::sendFilterDatas)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (Bicluster::*_t)(float * , int , vector<MaximalDimentionalSet*> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Bicluster::sendDistanceMatrix)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject Bicluster::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Bicluster.data,
      qt_meta_data_Bicluster,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Bicluster::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Bicluster::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Bicluster.stringdata0))
        return static_cast<void*>(const_cast< Bicluster*>(this));
    return QObject::qt_metacast(_clname);
}

int Bicluster::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void Bicluster::sendMaxDegree(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Bicluster::clusterRegionChange()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void Bicluster::sendClusterVoxels(vector<int> _t1, vector<int> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Bicluster::sendGlobalCluster(vector<vector<int>> _t1, vector<vector<int>> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Bicluster::sendVariateSubsets(vector<VSubset> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Bicluster::sendDistanceMatrix(float * _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Bicluster::sendFilterDatas(int * _t1, int * _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Bicluster::sendDistanceMatrix(float * _t1, int _t2, vector<MaximalDimentionalSet*> _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
