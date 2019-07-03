/****************************************************************************
** Meta object code from reading C++ file 'hierarchyTree.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../hierarchyTree.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hierarchyTree.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HierarchyTree_t {
    QByteArrayData data[16];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HierarchyTree_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HierarchyTree_t qt_meta_stringdata_HierarchyTree = {
    {
QT_MOC_LITERAL(0, 0, 13), // "HierarchyTree"
QT_MOC_LITERAL(1, 14, 19), // "sendSelectedVariate"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 2), // "No"
QT_MOC_LITERAL(4, 38, 20), // "sendSelectedVariates"
QT_MOC_LITERAL(5, 59, 11), // "vector<int>"
QT_MOC_LITERAL(6, 71, 8), // "variates"
QT_MOC_LITERAL(7, 80, 14), // "getCorrelation"
QT_MOC_LITERAL(8, 95, 6), // "float&"
QT_MOC_LITERAL(9, 102, 4), // "corr"
QT_MOC_LITERAL(10, 107, 19), // "getSelectedClusters"
QT_MOC_LITERAL(11, 127, 20), // "vector<vector<int> >"
QT_MOC_LITERAL(12, 148, 13), // "attributesets"
QT_MOC_LITERAL(13, 162, 16), // "getVarianteNames"
QT_MOC_LITERAL(14, 179, 12), // "variatenames"
QT_MOC_LITERAL(15, 192, 16) // "getSelectVariate"

    },
    "HierarchyTree\0sendSelectedVariate\0\0"
    "No\0sendSelectedVariates\0vector<int>\0"
    "variates\0getCorrelation\0float&\0corr\0"
    "getSelectedClusters\0vector<vector<int> >\0"
    "attributesets\0getVarianteNames\0"
    "variatenames\0getSelectVariate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HierarchyTree[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       7,    2,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   55,    2, 0x0a /* Public */,
      13,    1,   58,    2, 0x0a /* Public */,
      15,    1,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 8,    6,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QStringList,   14,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void HierarchyTree::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HierarchyTree *_t = static_cast<HierarchyTree *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendSelectedVariate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sendSelectedVariates((*reinterpret_cast< vector<int>(*)>(_a[1]))); break;
        case 2: _t->getCorrelation((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->getSelectedClusters((*reinterpret_cast< vector<vector<int> >(*)>(_a[1]))); break;
        case 4: _t->getVarianteNames((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 5: _t->getSelectVariate((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HierarchyTree::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HierarchyTree::sendSelectedVariate)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (HierarchyTree::*_t)(vector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HierarchyTree::sendSelectedVariates)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (HierarchyTree::*_t)(vector<int> , float & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HierarchyTree::getCorrelation)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject HierarchyTree::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_HierarchyTree.data,
      qt_meta_data_HierarchyTree,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HierarchyTree::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HierarchyTree::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HierarchyTree.stringdata0))
        return static_cast<void*>(const_cast< HierarchyTree*>(this));
    return QWidget::qt_metacast(_clname);
}

int HierarchyTree::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void HierarchyTree::sendSelectedVariate(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HierarchyTree::sendSelectedVariates(vector<int> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void HierarchyTree::getCorrelation(vector<int> _t1, float & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
