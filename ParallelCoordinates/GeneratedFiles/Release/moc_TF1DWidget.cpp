/****************************************************************************
** Meta object code from reading C++ file 'TF1DWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../1dtf/TF1DWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TF1DWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TF1DWidget_t {
    QByteArrayData data[22];
    char stringdata0[261];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TF1DWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TF1DWidget_t qt_meta_stringdata_TF1DWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "TF1DWidget"
QT_MOC_LITERAL(1, 11, 12), // "colorChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 1), // "c"
QT_MOC_LITERAL(4, 27, 9), // "tfChanged"
QT_MOC_LITERAL(5, 37, 7), // "tfReset"
QT_MOC_LITERAL(6, 45, 9), // "tmpsignal"
QT_MOC_LITERAL(7, 55, 6), // "sendTF"
QT_MOC_LITERAL(8, 62, 14), // "unsigned char*"
QT_MOC_LITERAL(9, 77, 10), // "sematicAdd"
QT_MOC_LITERAL(10, 88, 22), // "on_canvas_colorChanged"
QT_MOC_LITERAL(11, 111, 31), // "on_canvas_resetTransferFunction"
QT_MOC_LITERAL(12, 143, 17), // "on_canvas_changed"
QT_MOC_LITERAL(13, 161, 16), // "on_canvas_sendTF"
QT_MOC_LITERAL(14, 178, 4), // "data"
QT_MOC_LITERAL(15, 183, 18), // "on_btnSave_clicked"
QT_MOC_LITERAL(16, 202, 18), // "on_btnLoad_clicked"
QT_MOC_LITERAL(17, 221, 9), // "setVolume"
QT_MOC_LITERAL(18, 231, 13), // "const Volume*"
QT_MOC_LITERAL(19, 245, 6), // "volume"
QT_MOC_LITERAL(20, 252, 5), // "getTF"
QT_MOC_LITERAL(21, 258, 2) // "TF"

    },
    "TF1DWidget\0colorChanged\0\0c\0tfChanged\0"
    "tfReset\0tmpsignal\0sendTF\0unsigned char*\0"
    "sematicAdd\0on_canvas_colorChanged\0"
    "on_canvas_resetTransferFunction\0"
    "on_canvas_changed\0on_canvas_sendTF\0"
    "data\0on_btnSave_clicked\0on_btnLoad_clicked\0"
    "setVolume\0const Volume*\0volume\0getTF\0"
    "TF"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TF1DWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    0,   87,    2, 0x06 /* Public */,
       5,    0,   88,    2, 0x06 /* Public */,
       6,    0,   89,    2, 0x06 /* Public */,
       7,    1,   90,    2, 0x06 /* Public */,
       9,    0,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   94,    2, 0x0a /* Public */,
      11,    0,   97,    2, 0x0a /* Public */,
      12,    0,   98,    2, 0x0a /* Public */,
      13,    1,   99,    2, 0x0a /* Public */,
      15,    0,  102,    2, 0x0a /* Public */,
      16,    0,  103,    2, 0x0a /* Public */,
      17,    1,  104,    2, 0x0a /* Public */,
      20,    1,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QColor,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 8,   21,

       0        // eod
};

void TF1DWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TF1DWidget *_t = static_cast<TF1DWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->colorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 1: _t->tfChanged(); break;
        case 2: _t->tfReset(); break;
        case 3: _t->tmpsignal(); break;
        case 4: _t->sendTF((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 5: _t->sematicAdd(); break;
        case 6: _t->on_canvas_colorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 7: _t->on_canvas_resetTransferFunction(); break;
        case 8: _t->on_canvas_changed(); break;
        case 9: _t->on_canvas_sendTF((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 10: _t->on_btnSave_clicked(); break;
        case 11: _t->on_btnLoad_clicked(); break;
        case 12: _t->setVolume((*reinterpret_cast< const Volume*(*)>(_a[1]))); break;
        case 13: _t->getTF((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TF1DWidget::*_t)(const QColor & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TF1DWidget::colorChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TF1DWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TF1DWidget::tfChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TF1DWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TF1DWidget::tfReset)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TF1DWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TF1DWidget::tmpsignal)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (TF1DWidget::*_t)(unsigned char * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TF1DWidget::sendTF)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (TF1DWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TF1DWidget::sematicAdd)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject TF1DWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TF1DWidget.data,
      qt_meta_data_TF1DWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TF1DWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TF1DWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TF1DWidget.stringdata0))
        return static_cast<void*>(const_cast< TF1DWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int TF1DWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void TF1DWidget::colorChanged(const QColor & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TF1DWidget::tfChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void TF1DWidget::tfReset()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void TF1DWidget::tmpsignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void TF1DWidget::sendTF(unsigned char * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TF1DWidget::sematicAdd()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
