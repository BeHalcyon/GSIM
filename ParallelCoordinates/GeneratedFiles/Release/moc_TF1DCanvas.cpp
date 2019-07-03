/****************************************************************************
** Meta object code from reading C++ file 'TF1DCanvas.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../1dtf/TF1DCanvas.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TF1DCanvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TF1DCanvas_t {
    QByteArrayData data[21];
    char stringdata0[231];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TF1DCanvas_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TF1DCanvas_t qt_meta_stringdata_TF1DCanvas = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TF1DCanvas"
QT_MOC_LITERAL(1, 11, 12), // "colorChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 1), // "c"
QT_MOC_LITERAL(4, 27, 7), // "changed"
QT_MOC_LITERAL(5, 35, 21), // "resetTransferFunction"
QT_MOC_LITERAL(6, 57, 21), // "toggleInteractionMode"
QT_MOC_LITERAL(7, 79, 2), // "on"
QT_MOC_LITERAL(8, 82, 6), // "sendTF"
QT_MOC_LITERAL(9, 89, 14), // "unsigned char*"
QT_MOC_LITERAL(10, 104, 9), // "deleteKey"
QT_MOC_LITERAL(11, 114, 7), // "resetTF"
QT_MOC_LITERAL(12, 122, 18), // "changeCurrentColor"
QT_MOC_LITERAL(13, 141, 20), // "toggleClipThresholds"
QT_MOC_LITERAL(14, 162, 7), // "enabled"
QT_MOC_LITERAL(15, 170, 12), // "setHistogram"
QT_MOC_LITERAL(16, 183, 19), // "IntensityHistogram*"
QT_MOC_LITERAL(17, 203, 9), // "histogram"
QT_MOC_LITERAL(18, 213, 4), // "load"
QT_MOC_LITERAL(19, 218, 4), // "save"
QT_MOC_LITERAL(20, 223, 7) // "getKeys"

    },
    "TF1DCanvas\0colorChanged\0\0c\0changed\0"
    "resetTransferFunction\0toggleInteractionMode\0"
    "on\0sendTF\0unsigned char*\0deleteKey\0"
    "resetTF\0changeCurrentColor\0"
    "toggleClipThresholds\0enabled\0setHistogram\0"
    "IntensityHistogram*\0histogram\0load\0"
    "save\0getKeys"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TF1DCanvas[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    0,   87,    2, 0x06 /* Public */,
       5,    0,   88,    2, 0x06 /* Public */,
       6,    1,   89,    2, 0x06 /* Public */,
       8,    1,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   95,    2, 0x0a /* Public */,
      11,    0,   96,    2, 0x0a /* Public */,
      12,    0,   97,    2, 0x0a /* Public */,
      12,    1,   98,    2, 0x0a /* Public */,
      13,    1,  101,    2, 0x0a /* Public */,
      15,    1,  104,    2, 0x0a /* Public */,
      18,    0,  107,    2, 0x0a /* Public */,
      19,    0,  108,    2, 0x0a /* Public */,
      20,    1,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, 0x80000000 | 9,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void, 0x80000000 | 9,    2,

       0        // eod
};

void TF1DCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TF1DCanvas *_t = static_cast<TF1DCanvas *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->colorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 1: _t->changed(); break;
        case 2: _t->resetTransferFunction(); break;
        case 3: _t->toggleInteractionMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->sendTF((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 5: _t->deleteKey(); break;
        case 6: _t->resetTF(); break;
        case 7: _t->changeCurrentColor(); break;
        case 8: _t->changeCurrentColor((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 9: _t->toggleClipThresholds((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->setHistogram((*reinterpret_cast< IntensityHistogram*(*)>(_a[1]))); break;
        case 11: _t->load(); break;
        case 12: { bool _r = _t->save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 13: _t->getKeys((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TF1DCanvas::*_t)(const QColor & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TF1DCanvas::colorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TF1DCanvas::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TF1DCanvas::changed)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TF1DCanvas::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TF1DCanvas::resetTransferFunction)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TF1DCanvas::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TF1DCanvas::toggleInteractionMode)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (TF1DCanvas::*_t)(unsigned char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TF1DCanvas::sendTF)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject TF1DCanvas::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TF1DCanvas.data,
      qt_meta_data_TF1DCanvas,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TF1DCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TF1DCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TF1DCanvas.stringdata0))
        return static_cast<void*>(const_cast< TF1DCanvas*>(this));
    return QWidget::qt_metacast(_clname);
}

int TF1DCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void TF1DCanvas::colorChanged(const QColor & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TF1DCanvas::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void TF1DCanvas::resetTransferFunction()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void TF1DCanvas::toggleInteractionMode(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TF1DCanvas::sendTF(unsigned char * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
