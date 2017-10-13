/****************************************************************************
** Meta object code from reading C++ file 'quote_connect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Network/quote_connect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'quote_connect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VirtualQuote_t {
    QByteArrayData data[4];
    char stringdata0[45];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VirtualQuote_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VirtualQuote_t qt_meta_stringdata_VirtualQuote = {
    {
QT_MOC_LITERAL(0, 0, 12), // "VirtualQuote"
QT_MOC_LITERAL(1, 13, 20), // "sglChangeQuoteStatus"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 9) // "bCanTrade"

    },
    "VirtualQuote\0sglChangeQuoteStatus\0\0"
    "bCanTrade"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VirtualQuote[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void VirtualQuote::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VirtualQuote *_t = static_cast<VirtualQuote *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglChangeQuoteStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VirtualQuote::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VirtualQuote::sglChangeQuoteStatus)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject VirtualQuote::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_VirtualQuote.data,
      qt_meta_data_VirtualQuote,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VirtualQuote::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VirtualQuote::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VirtualQuote.stringdata0))
        return static_cast<void*>(const_cast< VirtualQuote*>(this));
    return QThread::qt_metacast(_clname);
}

int VirtualQuote::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void VirtualQuote::sglChangeQuoteStatus(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_InitContractThread_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InitContractThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InitContractThread_t qt_meta_stringdata_InitContractThread = {
    {
QT_MOC_LITERAL(0, 0, 18) // "InitContractThread"

    },
    "InitContractThread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InitContractThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void InitContractThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject InitContractThread::staticMetaObject = {
    { &VirtualQuote::staticMetaObject, qt_meta_stringdata_InitContractThread.data,
      qt_meta_data_InitContractThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *InitContractThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InitContractThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_InitContractThread.stringdata0))
        return static_cast<void*>(const_cast< InitContractThread*>(this));
    if (!strcmp(_clname, "TLDataCbk"))
        return static_cast< TLDataCbk*>(const_cast< InitContractThread*>(this));
    return VirtualQuote::qt_metacast(_clname);
}

int InitContractThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VirtualQuote::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_CSharpQuote_t {
    QByteArrayData data[14];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CSharpQuote_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CSharpQuote_t qt_meta_stringdata_CSharpQuote = {
    {
QT_MOC_LITERAL(0, 0, 11), // "CSharpQuote"
QT_MOC_LITERAL(1, 12, 14), // "sglSendMessage"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 4), // "data"
QT_MOC_LITERAL(4, 33, 11), // "onConnected"
QT_MOC_LITERAL(5, 45, 21), // "onTextMessageReceived"
QT_MOC_LITERAL(6, 67, 7), // "message"
QT_MOC_LITERAL(7, 75, 7), // "onError"
QT_MOC_LITERAL(8, 83, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(9, 112, 5), // "error"
QT_MOC_LITERAL(10, 118, 14), // "onDisConnected"
QT_MOC_LITERAL(11, 133, 15), // "slotSendMessage"
QT_MOC_LITERAL(12, 149, 16), // "handleMonitTimer"
QT_MOC_LITERAL(13, 166, 11) // "updateQuote"

    },
    "CSharpQuote\0sglSendMessage\0\0data\0"
    "onConnected\0onTextMessageReceived\0"
    "message\0onError\0QAbstractSocket::SocketError\0"
    "error\0onDisConnected\0slotSendMessage\0"
    "handleMonitTimer\0updateQuote"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CSharpQuote[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   57,    2, 0x0a /* Public */,
       5,    1,   58,    2, 0x0a /* Public */,
       7,    1,   61,    2, 0x0a /* Public */,
      10,    0,   64,    2, 0x0a /* Public */,
      11,    1,   65,    2, 0x0a /* Public */,
      12,    0,   68,    2, 0x0a /* Public */,
      13,    1,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVariantMap,    3,

       0        // eod
};

void CSharpQuote::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CSharpQuote *_t = static_cast<CSharpQuote *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglSendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->onConnected(); break;
        case 2: _t->onTextMessageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 4: _t->onDisConnected(); break;
        case 5: _t->slotSendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->handleMonitTimer(); break;
        case 7: _t->updateQuote((*reinterpret_cast< const QMap<QString,QVariant>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CSharpQuote::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CSharpQuote::sglSendMessage)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject CSharpQuote::staticMetaObject = {
    { &VirtualQuote::staticMetaObject, qt_meta_stringdata_CSharpQuote.data,
      qt_meta_data_CSharpQuote,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CSharpQuote::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CSharpQuote::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CSharpQuote.stringdata0))
        return static_cast<void*>(const_cast< CSharpQuote*>(this));
    return VirtualQuote::qt_metacast(_clname);
}

int CSharpQuote::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VirtualQuote::qt_metacall(_c, _id, _a);
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
void CSharpQuote::sglSendMessage(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
