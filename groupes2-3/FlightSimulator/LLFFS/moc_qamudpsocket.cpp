/****************************************************************************
** Meta object code from reading C++ file 'qamudpsocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LLF-FS-sources/qamudpsocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qamudpsocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QamUdpSocket_t {
    QByteArrayData data[11];
    char stringdata0[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QamUdpSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QamUdpSocket_t qt_meta_stringdata_QamUdpSocket = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QamUdpSocket"
QT_MOC_LITERAL(1, 13, 12), // "sockReceived"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "sockInfo"
QT_MOC_LITERAL(4, 36, 8), // "sockRead"
QT_MOC_LITERAL(5, 45, 10), // "lookupHost"
QT_MOC_LITERAL(6, 56, 9), // "QHostInfo"
QT_MOC_LITERAL(7, 66, 8), // "hostInfo"
QT_MOC_LITERAL(8, 75, 9), // "sockWrite"
QT_MOC_LITERAL(9, 85, 4), // "data"
QT_MOC_LITERAL(10, 90, 4) // "port"

    },
    "QamUdpSocket\0sockReceived\0\0sockInfo\0"
    "sockRead\0lookupHost\0QHostInfo\0hostInfo\0"
    "sockWrite\0data\0port"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QamUdpSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       3,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   50,    2, 0x08 /* Private */,
       5,    1,   51,    2, 0x08 /* Private */,
       8,    2,   54,    2, 0x0a /* Public */,
       8,    1,   59,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QByteArray, QMetaType::UShort,    9,   10,
    QMetaType::Void, QMetaType::QByteArray,    9,

       0        // eod
};

void QamUdpSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QamUdpSocket *_t = static_cast<QamUdpSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sockReceived((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->sockInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->sockRead(); break;
        case 3: _t->lookupHost((*reinterpret_cast< const QHostInfo(*)>(_a[1]))); break;
        case 4: _t->sockWrite((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2]))); break;
        case 5: _t->sockWrite((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QHostInfo >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QamUdpSocket::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamUdpSocket::sockReceived)) {
                *result = 0;
            }
        }
        {
            typedef void (QamUdpSocket::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QamUdpSocket::sockInfo)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject QamUdpSocket::staticMetaObject = {
    { &QUdpSocket::staticMetaObject, qt_meta_stringdata_QamUdpSocket.data,
      qt_meta_data_QamUdpSocket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QamUdpSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QamUdpSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QamUdpSocket.stringdata0))
        return static_cast<void*>(const_cast< QamUdpSocket*>(this));
    return QUdpSocket::qt_metacast(_clname);
}

int QamUdpSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QUdpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QamUdpSocket::sockReceived(const QByteArray & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QamUdpSocket::sockInfo(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
