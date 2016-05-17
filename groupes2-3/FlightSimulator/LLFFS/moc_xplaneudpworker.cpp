/****************************************************************************
** Meta object code from reading C++ file 'xplaneudpworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LLF-FS-sources/xplaneudpworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'xplaneudpworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_XPlaneUdpWorker_t {
    QByteArrayData data[10];
    char stringdata0[74];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_XPlaneUdpWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_XPlaneUdpWorker_t qt_meta_stringdata_XPlaneUdpWorker = {
    {
QT_MOC_LITERAL(0, 0, 15), // "XPlaneUdpWorker"
QT_MOC_LITERAL(1, 16, 7), // "udpInfo"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "rrefReceived"
QT_MOC_LITERAL(4, 38, 2), // "id"
QT_MOC_LITERAL(5, 41, 5), // "value"
QT_MOC_LITERAL(6, 47, 4), // "send"
QT_MOC_LITERAL(7, 52, 4), // "data"
QT_MOC_LITERAL(8, 57, 8), // "received"
QT_MOC_LITERAL(9, 66, 7) // "timeout"

    },
    "XPlaneUdpWorker\0udpInfo\0\0rrefReceived\0"
    "id\0value\0send\0data\0received\0timeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_XPlaneUdpWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    2,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   47,    2, 0x0a /* Public */,
       8,    1,   50,    2, 0x08 /* Private */,
       9,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Float,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void,

       0        // eod
};

void XPlaneUdpWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        XPlaneUdpWorker *_t = static_cast<XPlaneUdpWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->udpInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->rrefReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 2: _t->send((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->received((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 4: _t->timeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (XPlaneUdpWorker::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&XPlaneUdpWorker::udpInfo)) {
                *result = 0;
            }
        }
        {
            typedef void (XPlaneUdpWorker::*_t)(int , float );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&XPlaneUdpWorker::rrefReceived)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject XPlaneUdpWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_XPlaneUdpWorker.data,
      qt_meta_data_XPlaneUdpWorker,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *XPlaneUdpWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *XPlaneUdpWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_XPlaneUdpWorker.stringdata0))
        return static_cast<void*>(const_cast< XPlaneUdpWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int XPlaneUdpWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void XPlaneUdpWorker::udpInfo(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void XPlaneUdpWorker::rrefReceived(int _t1, float _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
