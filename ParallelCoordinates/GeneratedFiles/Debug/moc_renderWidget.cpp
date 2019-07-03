/****************************************************************************
** Meta object code from reading C++ file 'renderWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../renderWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'renderWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RenderWidget_t {
    QByteArrayData data[28];
    char stringdata0[264];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RenderWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RenderWidget_t qt_meta_stringdata_RenderWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "RenderWidget"
QT_MOC_LITERAL(1, 13, 14), // "sendViewMatrix"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 6), // "float*"
QT_MOC_LITERAL(4, 36, 10), // "viewmatrix"
QT_MOC_LITERAL(5, 47, 10), // "dataLoaded"
QT_MOC_LITERAL(6, 58, 13), // "const Volume*"
QT_MOC_LITERAL(7, 72, 11), // "getVolumeTF"
QT_MOC_LITERAL(8, 84, 14), // "unsigned char*"
QT_MOC_LITERAL(9, 99, 2), // "tf"
QT_MOC_LITERAL(10, 102, 12), // "updateRender"
QT_MOC_LITERAL(11, 115, 10), // "illumParam"
QT_MOC_LITERAL(12, 126, 10), // "illumparam"
QT_MOC_LITERAL(13, 137, 7), // "setData"
QT_MOC_LITERAL(14, 145, 7), // "Volume*"
QT_MOC_LITERAL(15, 153, 13), // "regionsUpdate"
QT_MOC_LITERAL(16, 167, 18), // "setBoundingBoxShow"
QT_MOC_LITERAL(17, 186, 5), // "setKa"
QT_MOC_LITERAL(18, 192, 3), // "ka_"
QT_MOC_LITERAL(19, 196, 5), // "setKd"
QT_MOC_LITERAL(20, 202, 3), // "kd_"
QT_MOC_LITERAL(21, 206, 5), // "setKs"
QT_MOC_LITERAL(22, 212, 3), // "ks_"
QT_MOC_LITERAL(23, 216, 10), // "setOpacity"
QT_MOC_LITERAL(24, 227, 8), // "opacity_"
QT_MOC_LITERAL(25, 236, 11), // "colorUpdate"
QT_MOC_LITERAL(26, 248, 12), // "setOpacities"
QT_MOC_LITERAL(27, 261, 2) // "id"

    },
    "RenderWidget\0sendViewMatrix\0\0float*\0"
    "viewmatrix\0dataLoaded\0const Volume*\0"
    "getVolumeTF\0unsigned char*\0tf\0"
    "updateRender\0illumParam\0illumparam\0"
    "setData\0Volume*\0regionsUpdate\0"
    "setBoundingBoxShow\0setKa\0ka_\0setKd\0"
    "kd_\0setKs\0ks_\0setOpacity\0opacity_\0"
    "colorUpdate\0setOpacities\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RenderWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       5,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   85,    2, 0x0a /* Public */,
      10,    1,   88,    2, 0x0a /* Public */,
      13,    1,   91,    2, 0x0a /* Public */,
      15,    0,   94,    2, 0x0a /* Public */,
      16,    0,   95,    2, 0x0a /* Public */,
      17,    1,   96,    2, 0x0a /* Public */,
      19,    1,   99,    2, 0x0a /* Public */,
      21,    1,  102,    2, 0x0a /* Public */,
      23,    1,  105,    2, 0x0a /* Public */,
      25,    0,  108,    2, 0x0a /* Public */,
      26,    2,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   18,
    QMetaType::Void, QMetaType::Double,   20,
    QMetaType::Void, QMetaType::Double,   22,
    QMetaType::Void, QMetaType::Double,   24,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Double,   27,   24,

       0        // eod
};

void RenderWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RenderWidget *_t = static_cast<RenderWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendViewMatrix((*reinterpret_cast< float*(*)>(_a[1]))); break;
        case 1: _t->dataLoaded((*reinterpret_cast< const Volume*(*)>(_a[1]))); break;
        case 2: _t->getVolumeTF((*reinterpret_cast< unsigned char*(*)>(_a[1]))); break;
        case 3: _t->updateRender((*reinterpret_cast< illumParam(*)>(_a[1]))); break;
        case 4: _t->setData((*reinterpret_cast< Volume*(*)>(_a[1]))); break;
        case 5: _t->regionsUpdate(); break;
        case 6: _t->setBoundingBoxShow(); break;
        case 7: _t->setKa((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 8: _t->setKd((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->setKs((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->setOpacity((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->colorUpdate(); break;
        case 12: _t->setOpacities((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RenderWidget::*_t)(float * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RenderWidget::sendViewMatrix)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (RenderWidget::*_t)(const Volume * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RenderWidget::dataLoaded)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject RenderWidget::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_RenderWidget.data,
      qt_meta_data_RenderWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *RenderWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_RenderWidget.stringdata0))
        return static_cast<void*>(const_cast< RenderWidget*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int RenderWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
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
void RenderWidget::sendViewMatrix(float * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void RenderWidget::dataLoaded(const Volume * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
