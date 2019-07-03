/****************************************************************************
** Meta object code from reading C++ file 'donutbreakdownchart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../donutbreakdownchart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'donutbreakdownchart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DonutBreakdownChart_t {
    QByteArrayData data[20];
    char stringdata0[257];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DonutBreakdownChart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DonutBreakdownChart_t qt_meta_stringdata_DonutBreakdownChart = {
    {
QT_MOC_LITERAL(0, 0, 19), // "DonutBreakdownChart"
QT_MOC_LITERAL(1, 20, 20), // "sendSelectedVariates"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 11), // "vector<int>"
QT_MOC_LITERAL(4, 54, 18), // "sendSelectedSubset"
QT_MOC_LITERAL(5, 73, 14), // "getCorrelation"
QT_MOC_LITERAL(6, 88, 8), // "variates"
QT_MOC_LITERAL(7, 97, 6), // "float&"
QT_MOC_LITERAL(8, 104, 4), // "corr"
QT_MOC_LITERAL(9, 109, 12), // "sendcolormap"
QT_MOC_LITERAL(10, 122, 13), // "QList<QColor>"
QT_MOC_LITERAL(11, 136, 8), // "colormap"
QT_MOC_LITERAL(12, 145, 17), // "getVariateSubsets"
QT_MOC_LITERAL(13, 163, 15), // "vector<VSubset>"
QT_MOC_LITERAL(14, 179, 13), // "attributesets"
QT_MOC_LITERAL(15, 193, 14), // "highlightSlice"
QT_MOC_LITERAL(16, 208, 9), // "highlight"
QT_MOC_LITERAL(17, 218, 8), // "selected"
QT_MOC_LITERAL(18, 227, 16), // "getVarianteNames"
QT_MOC_LITERAL(19, 244, 12) // "variatenames"

    },
    "DonutBreakdownChart\0sendSelectedVariates\0"
    "\0vector<int>\0sendSelectedSubset\0"
    "getCorrelation\0variates\0float&\0corr\0"
    "sendcolormap\0QList<QColor>\0colormap\0"
    "getVariateSubsets\0vector<VSubset>\0"
    "attributesets\0highlightSlice\0highlight\0"
    "selected\0getVarianteNames\0variatenames"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DonutBreakdownChart[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       5,    2,   60,    2, 0x06 /* Public */,
       9,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   68,    2, 0x0a /* Public */,
      15,    1,   71,    2, 0x0a /* Public */,
      17,    0,   74,    2, 0x0a /* Public */,
      18,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 7,    6,    8,
    QMetaType::Void, 0x80000000 | 10,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   19,

       0        // eod
};

void DonutBreakdownChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DonutBreakdownChart *_t = static_cast<DonutBreakdownChart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendSelectedVariates((*reinterpret_cast< vector<int>(*)>(_a[1]))); break;
        case 1: _t->sendSelectedSubset((*reinterpret_cast< vector<int>(*)>(_a[1]))); break;
        case 2: _t->getCorrelation((*reinterpret_cast< vector<int>(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 3: _t->sendcolormap((*reinterpret_cast< QList<QColor>(*)>(_a[1]))); break;
        case 4: _t->getVariateSubsets((*reinterpret_cast< vector<VSubset>(*)>(_a[1]))); break;
        case 5: _t->highlightSlice((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->selected(); break;
        case 7: _t->getVarianteNames((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QColor> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DonutBreakdownChart::*_t)(vector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DonutBreakdownChart::sendSelectedVariates)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (DonutBreakdownChart::*_t)(vector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DonutBreakdownChart::sendSelectedSubset)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (DonutBreakdownChart::*_t)(vector<int> , float & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DonutBreakdownChart::getCorrelation)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (DonutBreakdownChart::*_t)(QList<QColor> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DonutBreakdownChart::sendcolormap)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject DonutBreakdownChart::staticMetaObject = {
    { &QChartView::staticMetaObject, qt_meta_stringdata_DonutBreakdownChart.data,
      qt_meta_data_DonutBreakdownChart,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DonutBreakdownChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DonutBreakdownChart::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DonutBreakdownChart.stringdata0))
        return static_cast<void*>(const_cast< DonutBreakdownChart*>(this));
    return QChartView::qt_metacast(_clname);
}

int DonutBreakdownChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QChartView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void DonutBreakdownChart::sendSelectedVariates(vector<int> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DonutBreakdownChart::sendSelectedSubset(vector<int> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DonutBreakdownChart::getCorrelation(vector<int> _t1, float & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DonutBreakdownChart::sendcolormap(QList<QColor> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
