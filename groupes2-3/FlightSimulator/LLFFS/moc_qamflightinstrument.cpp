/****************************************************************************
** Meta object code from reading C++ file 'qamflightinstrument.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QamFlightInstruments-0.4/qamflightinstrument.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qamflightinstrument.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QamFlightInstrument_t {
    QByteArrayData data[18];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QamFlightInstrument_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QamFlightInstrument_t qt_meta_stringdata_QamFlightInstrument = {
    {
QT_MOC_LITERAL(0, 0, 19), // "QamFlightInstrument"
QT_MOC_LITERAL(1, 20, 8), // "lowLevel"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "axis"
QT_MOC_LITERAL(4, 35, 11), // "normalLevel"
QT_MOC_LITERAL(5, 47, 9), // "highLevel"
QT_MOC_LITERAL(6, 57, 12), // "valueChanged"
QT_MOC_LITERAL(7, 70, 5), // "value"
QT_MOC_LITERAL(8, 76, 10), // "alarmState"
QT_MOC_LITERAL(9, 87, 2), // "id"
QT_MOC_LITERAL(10, 90, 3), // "num"
QT_MOC_LITERAL(11, 94, 5), // "state"
QT_MOC_LITERAL(12, 100, 8), // "setValue"
QT_MOC_LITERAL(13, 109, 13), // "selectPressed"
QT_MOC_LITERAL(14, 123, 8), // "longClic"
QT_MOC_LITERAL(15, 132, 17), // "adjustmentChanged"
QT_MOC_LITERAL(16, 150, 19), // "spinBoxValueChanged"
QT_MOC_LITERAL(17, 170, 16) // "pbuSelectClicked"

    },
    "QamFlightInstrument\0lowLevel\0\0axis\0"
    "normalLevel\0highLevel\0valueChanged\0"
    "value\0alarmState\0id\0num\0state\0setValue\0"
    "selectPressed\0longClic\0adjustmentChanged\0"
    "spinBoxValueChanged\0pbuSelectClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QamFlightInstrument[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       1,    0,   97,    2, 0x26 /* Public | MethodCloned */,
       4,    1,   98,    2, 0x06 /* Public */,
       4,    0,  101,    2, 0x26 /* Public | MethodCloned */,
       5,    1,  102,    2, 0x06 /* Public */,
       5,    0,  105,    2, 0x26 /* Public | MethodCloned */,
       6,    2,  106,    2, 0x06 /* Public */,
       6,    1,  111,    2, 0x26 /* Public | MethodCloned */,
       8,    3,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,  121,    2, 0x0a /* Public */,
      12,    1,  126,    2, 0x2a /* Public | MethodCloned */,
      13,    2,  129,    2, 0x0a /* Public */,
      13,    1,  134,    2, 0x2a /* Public | MethodCloned */,
      15,    2,  137,    2, 0x0a /* Public */,
      16,    1,  142,    2, 0x08 /* Private */,
      17,    0,  145,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Float, QMetaType::Int,    7,    3,
    QMetaType::Void, QMetaType::Float,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    9,   10,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::Float, QMetaType::Int,    7,    3,
    QMetaType::Void, QMetaType::Float,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,   10,   14,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,   10,    7,
    QMetaType::Void, QMetaType::Double,    7,
    QMetaType::Void,

       0        // eod
};

void QamFlightInstrument::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QamFlightInstrument *_t = static_cast<QamFlightInstrument *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->lowLevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->lowLevel(); break;
        case 2: _t->normalLevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->normalLevel(); break;
        case 4: _t->highLevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->highLevel(); break;
        case 6: _t->valueChanged((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->valueChanged((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 8: _t->alarmState((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->setValue((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->setValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 11: _t->selectPressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 12: _t->selectPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->adjustmentChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 14: _t->spinBoxValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->pbuSelectClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QamFlightInstrument::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamFlightInstrument::lowLevel)) {
                *result = 0;
            }
        }
        {
            typedef void (QamFlightInstrument::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamFlightInstrument::normalLevel)) {
                *result = 2;
            }
        }
        {
            typedef void (QamFlightInstrument::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamFlightInstrument::highLevel)) {
                *result = 4;
            }
        }
        {
            typedef void (QamFlightInstrument::*_t)(float , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamFlightInstrument::valueChanged)) {
                *result = 6;
            }
        }
        {
            typedef void (QamFlightInstrument::*_t)(int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamFlightInstrument::alarmState)) {
                *result = 8;
            }
        }
    }
}

const QMetaObject QamFlightInstrument::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QamFlightInstrument.data,
      qt_meta_data_QamFlightInstrument,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QamFlightInstrument::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QamFlightInstrument::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QamFlightInstrument.stringdata0))
        return static_cast<void*>(const_cast< QamFlightInstrument*>(this));
    return QWidget::qt_metacast(_clname);
}

int QamFlightInstrument::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void QamFlightInstrument::lowLevel(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void QamFlightInstrument::normalLevel(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void QamFlightInstrument::highLevel(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 6
void QamFlightInstrument::valueChanged(float _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 8
void QamFlightInstrument::alarmState(int _t1, int _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_END_MOC_NAMESPACE
