/****************************************************************************
** Meta object code from reading C++ file 'RenderProperty.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RenderProperty.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RenderProperty.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RenderPropertyWidget_t {
    QByteArrayData data[12];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RenderPropertyWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RenderPropertyWidget_t qt_meta_stringdata_RenderPropertyWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "RenderPropertyWidget"
QT_MOC_LITERAL(1, 21, 12), // "colorChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 12), // "alphaChanged"
QT_MOC_LITERAL(4, 48, 2), // "id"
QT_MOC_LITERAL(5, 51, 3), // "val"
QT_MOC_LITERAL(6, 55, 11), // "buttonJudge"
QT_MOC_LITERAL(7, 67, 8), // "buttonId"
QT_MOC_LITERAL(8, 76, 13), // "alpha1Changed"
QT_MOC_LITERAL(9, 90, 13), // "alpha2Changed"
QT_MOC_LITERAL(10, 104, 13), // "alpha3Changed"
QT_MOC_LITERAL(11, 118, 13) // "alpha4Changed"

    },
    "RenderPropertyWidget\0colorChanged\0\0"
    "alphaChanged\0id\0val\0buttonJudge\0"
    "buttonId\0alpha1Changed\0alpha2Changed\0"
    "alpha3Changed\0alpha4Changed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RenderPropertyWidget[] = {

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
       1,    0,   49,    2, 0x06 /* Public */,
       3,    2,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   55,    2, 0x0a /* Public */,
       8,    1,   58,    2, 0x0a /* Public */,
       9,    1,   61,    2, 0x0a /* Public */,
      10,    1,   64,    2, 0x0a /* Public */,
      11,    1,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Double,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void RenderPropertyWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RenderPropertyWidget *_t = static_cast<RenderPropertyWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->colorChanged(); break;
        case 1: _t->alphaChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 2: _t->buttonJudge((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->alpha1Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->alpha2Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->alpha3Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->alpha4Changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RenderPropertyWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RenderPropertyWidget::colorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RenderPropertyWidget::*_t)(int , double );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RenderPropertyWidget::alphaChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject RenderPropertyWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RenderPropertyWidget.data,
      qt_meta_data_RenderPropertyWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RenderPropertyWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderPropertyWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RenderPropertyWidget.stringdata0))
        return static_cast<void*>(const_cast< RenderPropertyWidget*>(this));
    if (!strcmp(_clname, "Ui::RenderProperties"))
        return static_cast< Ui::RenderProperties*>(const_cast< RenderPropertyWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int RenderPropertyWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void RenderPropertyWidget::colorChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void RenderPropertyWidget::alphaChanged(int _t1, double _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
