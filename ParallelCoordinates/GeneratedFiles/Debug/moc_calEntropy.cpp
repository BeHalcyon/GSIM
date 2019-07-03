/****************************************************************************
** Meta object code from reading C++ file 'calEntropy.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../calEntropy.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calEntropy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CalEntropy_t {
    QByteArrayData data[18];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalEntropy_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalEntropy_t qt_meta_stringdata_CalEntropy = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CalEntropy"
QT_MOC_LITERAL(1, 11, 21), // "sendSelectedVariateNo"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 10), // "selectedNo"
QT_MOC_LITERAL(4, 45, 22), // "sendSelectedVariatesNo"
QT_MOC_LITERAL(5, 68, 11), // "vector<int>"
QT_MOC_LITERAL(6, 80, 16), // "selectedVariates"
QT_MOC_LITERAL(7, 97, 8), // "setDatas"
QT_MOC_LITERAL(8, 106, 16), // "vector<Volume*>&"
QT_MOC_LITERAL(9, 123, 3), // "vds"
QT_MOC_LITERAL(10, 127, 12), // "updateSelect"
QT_MOC_LITERAL(11, 140, 10), // "getEntropy"
QT_MOC_LITERAL(12, 151, 13), // "vector<float>"
QT_MOC_LITERAL(13, 165, 9), // "getMutual"
QT_MOC_LITERAL(14, 175, 3), // "sno"
QT_MOC_LITERAL(15, 179, 11), // "getClickCol"
QT_MOC_LITERAL(16, 191, 3), // "row"
QT_MOC_LITERAL(17, 195, 3) // "col"

    },
    "CalEntropy\0sendSelectedVariateNo\0\0"
    "selectedNo\0sendSelectedVariatesNo\0"
    "vector<int>\0selectedVariates\0setDatas\0"
    "vector<Volume*>&\0vds\0updateSelect\0"
    "getEntropy\0vector<float>\0getMutual\0"
    "sno\0getClickCol\0row\0col"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalEntropy[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   55,    2, 0x0a /* Public */,
      10,    0,   58,    2, 0x0a /* Public */,
      11,    0,   59,    2, 0x0a /* Public */,
      13,    1,   60,    2, 0x0a /* Public */,
      15,    2,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    0x80000000 | 12,
    0x80000000 | 12, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   16,   17,

       0        // eod
};

void CalEntropy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CalEntropy *_t = static_cast<CalEntropy *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendSelectedVariateNo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sendSelectedVariatesNo((*reinterpret_cast< vector<int>(*)>(_a[1]))); break;
        case 2: _t->setDatas((*reinterpret_cast< vector<Volume*>(*)>(_a[1]))); break;
        case 3: _t->updateSelect(); break;
        case 4: { vector<float> _r = _t->getEntropy();
            if (_a[0]) *reinterpret_cast< vector<float>*>(_a[0]) = _r; }  break;
        case 5: { vector<float> _r = _t->getMutual((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< vector<float>*>(_a[0]) = _r; }  break;
        case 6: _t->getClickCol((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CalEntropy::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalEntropy::sendSelectedVariateNo)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CalEntropy::*_t)(vector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CalEntropy::sendSelectedVariatesNo)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject CalEntropy::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CalEntropy.data,
      qt_meta_data_CalEntropy,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CalEntropy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalEntropy::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CalEntropy.stringdata0))
        return static_cast<void*>(const_cast< CalEntropy*>(this));
    if (!strcmp(_clname, "Ui::EntropyForm"))
        return static_cast< Ui::EntropyForm*>(const_cast< CalEntropy*>(this));
    return QWidget::qt_metacast(_clname);
}

int CalEntropy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void CalEntropy::sendSelectedVariateNo(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalEntropy::sendSelectedVariatesNo(vector<int> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
