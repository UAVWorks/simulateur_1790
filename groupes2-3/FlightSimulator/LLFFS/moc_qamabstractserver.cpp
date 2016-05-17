/****************************************************************************
** Meta object code from reading C++ file 'qamabstractserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Modbus/ModbusTCPWorker/qamabstractserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qamabstractserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QamAbstractServer_t {
    QByteArrayData data[14];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QamAbstractServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QamAbstractServer_t qt_meta_stringdata_QamAbstractServer = {
    {
QT_MOC_LITERAL(0, 0, 17), // "QamAbstractServer"
QT_MOC_LITERAL(1, 18, 7), // "request"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "received"
QT_MOC_LITERAL(4, 36, 4), // "data"
QT_MOC_LITERAL(5, 41, 4), // "sent"
QT_MOC_LITERAL(6, 46, 4), // "info"
QT_MOC_LITERAL(7, 51, 7), // "message"
QT_MOC_LITERAL(8, 59, 17), // "responseToRequest"
QT_MOC_LITERAL(9, 77, 11), // "QByteArray&"
QT_MOC_LITERAL(10, 89, 23), // "responseToClientRequest"
QT_MOC_LITERAL(11, 113, 8), // "response"
QT_MOC_LITERAL(12, 122, 18), // "responseFromServer"
QT_MOC_LITERAL(13, 141, 11) // "networkInfo"

    },
    "QamAbstractServer\0request\0\0received\0"
    "data\0sent\0info\0message\0responseToRequest\0"
    "QByteArray&\0responseToClientRequest\0"
    "response\0responseFromServer\0networkInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QamAbstractServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       3,    1,   62,    2, 0x06 /* Public */,
       5,    1,   65,    2, 0x06 /* Public */,
       6,    1,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   71,    2, 0x0a /* Public */,
      10,    1,   74,    2, 0x0a /* Public */,
      11,    1,   77,    2, 0x0a /* Public */,
      12,    1,   80,    2, 0x0a /* Public */,
      13,    1,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    1,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void, QMetaType::QByteArray,    4,
    QMetaType::Void, QMetaType::QString,    7,

 // slots: parameters
    QMetaType::QByteArray, 0x80000000 | 9,    1,
    QMetaType::QByteArray, 0x80000000 | 9,    1,
    QMetaType::Void, QMetaType::QByteArray,   11,
    QMetaType::Void, QMetaType::QByteArray,   11,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void QamAbstractServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QamAbstractServer *_t = static_cast<QamAbstractServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->request((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->received((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->sent((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->info((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: { QByteArray _r = _t->responseToRequest((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 5: { QByteArray _r = _t->responseToClientRequest((*reinterpret_cast< QByteArray(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QByteArray*>(_a[0]) = _r; }  break;
        case 6: _t->response((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->responseFromServer((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->networkInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QamAbstractServer::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamAbstractServer::request)) {
                *result = 0;
            }
        }
        {
            typedef void (QamAbstractServer::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamAbstractServer::received)) {
                *result = 1;
            }
        }
        {
            typedef void (QamAbstractServer::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamAbstractServer::sent)) {
                *result = 2;
            }
        }
        {
            typedef void (QamAbstractServer::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamAbstractServer::info)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject QamAbstractServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_QamAbstractServer.data,
      qt_meta_data_QamAbstractServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QamAbstractServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QamAbstractServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QamAbstractServer.stringdata0))
        return static_cast<void*>(const_cast< QamAbstractServer*>(this));
    return QObject::qt_metacast(_clname);
}

int QamAbstractServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QamAbstractServer::request(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QamAbstractServer::received(const QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QamAbstractServer::sent(const QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void QamAbstractServer::info(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
