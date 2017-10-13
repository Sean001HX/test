/****************************************************************************
** Meta object code from reading C++ file 'TCPImpl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Network/TCPImpl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TCPImpl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TCPImpl_t {
    QByteArrayData data[40];
    char stringdata0[667];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TCPImpl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TCPImpl_t qt_meta_stringdata_TCPImpl = {
    {
QT_MOC_LITERAL(0, 0, 7), // "TCPImpl"
QT_MOC_LITERAL(1, 8, 17), // "sglOrderInsertCbk"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 23), // "AllTrade::ErrorCodeType"
QT_MOC_LITERAL(4, 51, 7), // "errcode"
QT_MOC_LITERAL(5, 59, 11), // "std::string"
QT_MOC_LITERAL(6, 71, 7), // "user_id"
QT_MOC_LITERAL(7, 79, 37), // "AllTrade::NPTradeCenter::Orde..."
QT_MOC_LITERAL(8, 117, 9), // "order_ptr"
QT_MOC_LITERAL(9, 127, 40), // "AllTrade::NPMgrCenter::SOnlin..."
QT_MOC_LITERAL(10, 168, 8), // "user_ptr"
QT_MOC_LITERAL(11, 177, 17), // "sglOrderCancelCbk"
QT_MOC_LITERAL(12, 195, 17), // "sglOrderChangeCbk"
QT_MOC_LITERAL(13, 213, 11), // "sglTradeCbk"
QT_MOC_LITERAL(14, 225, 37), // "AllTrade::NPTradeCenter::Trad..."
QT_MOC_LITERAL(15, 263, 9), // "trade_ptr"
QT_MOC_LITERAL(16, 273, 14), // "sglPositionCbk"
QT_MOC_LITERAL(17, 288, 40), // "AllTrade::NPTradeCenter::Posi..."
QT_MOC_LITERAL(18, 329, 12), // "position_ptr"
QT_MOC_LITERAL(19, 342, 11), // "sglMoneyCbk"
QT_MOC_LITERAL(20, 354, 36), // "AllTrade::NPMgrCenter::SMoney..."
QT_MOC_LITERAL(21, 391, 9), // "money_ptr"
QT_MOC_LITERAL(22, 401, 17), // "sglRiskControlCbk"
QT_MOC_LITERAL(23, 419, 9), // "date_time"
QT_MOC_LITERAL(24, 429, 25), // "AllTrade::RiskControlType"
QT_MOC_LITERAL(25, 455, 7), // "rc_type"
QT_MOC_LITERAL(26, 463, 11), // "remark_text"
QT_MOC_LITERAL(27, 475, 17), // "slotNewConnection"
QT_MOC_LITERAL(28, 493, 8), // "slotRead"
QT_MOC_LITERAL(29, 502, 15), // "slotSendMessage"
QT_MOC_LITERAL(30, 518, 3), // "msg"
QT_MOC_LITERAL(31, 522, 10), // "socketDesc"
QT_MOC_LITERAL(32, 533, 15), // "slotSocketError"
QT_MOC_LITERAL(33, 549, 18), // "slotOrderInsertCbk"
QT_MOC_LITERAL(34, 568, 18), // "slotOrderCancelCbk"
QT_MOC_LITERAL(35, 587, 18), // "slotOrderChangeCbk"
QT_MOC_LITERAL(36, 606, 12), // "slotTradeCbk"
QT_MOC_LITERAL(37, 619, 15), // "slotPositionCbk"
QT_MOC_LITERAL(38, 635, 12), // "slotMoneyCbk"
QT_MOC_LITERAL(39, 648, 18) // "slotRiskControlCbk"

    },
    "TCPImpl\0sglOrderInsertCbk\0\0"
    "AllTrade::ErrorCodeType\0errcode\0"
    "std::string\0user_id\0"
    "AllTrade::NPTradeCenter::OrderInfoPtr\0"
    "order_ptr\0AllTrade::NPMgrCenter::SOnlineAccountPtr\0"
    "user_ptr\0sglOrderCancelCbk\0sglOrderChangeCbk\0"
    "sglTradeCbk\0AllTrade::NPTradeCenter::TradeInfoPtr\0"
    "trade_ptr\0sglPositionCbk\0"
    "AllTrade::NPTradeCenter::PositionInfoPtr\0"
    "position_ptr\0sglMoneyCbk\0"
    "AllTrade::NPMgrCenter::SMoneyInfoPtr\0"
    "money_ptr\0sglRiskControlCbk\0date_time\0"
    "AllTrade::RiskControlType\0rc_type\0"
    "remark_text\0slotNewConnection\0slotRead\0"
    "slotSendMessage\0msg\0socketDesc\0"
    "slotSocketError\0slotOrderInsertCbk\0"
    "slotOrderCancelCbk\0slotOrderChangeCbk\0"
    "slotTradeCbk\0slotPositionCbk\0slotMoneyCbk\0"
    "slotRiskControlCbk"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TCPImpl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,  104,    2, 0x06 /* Public */,
      11,    3,  113,    2, 0x06 /* Public */,
      12,    3,  120,    2, 0x06 /* Public */,
      13,    3,  127,    2, 0x06 /* Public */,
      16,    3,  134,    2, 0x06 /* Public */,
      19,    2,  141,    2, 0x06 /* Public */,
      22,    4,  146,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      27,    0,  155,    2, 0x0a /* Public */,
      28,    0,  156,    2, 0x0a /* Public */,
      29,    2,  157,    2, 0x0a /* Public */,
      32,    0,  162,    2, 0x0a /* Public */,
      33,    4,  163,    2, 0x08 /* Private */,
      34,    3,  172,    2, 0x08 /* Private */,
      35,    3,  179,    2, 0x08 /* Private */,
      36,    3,  186,    2, 0x08 /* Private */,
      37,    3,  193,    2, 0x08 /* Private */,
      38,    2,  200,    2, 0x08 /* Private */,
      39,    4,  205,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 9,    4,    6,    8,   10,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 14,    4,    6,   15,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 17,    4,    6,   18,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 20,    6,   21,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 24, 0x80000000 | 5,    6,   23,   25,   26,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   30,   31,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7, 0x80000000 | 9,    4,    6,    8,   10,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 14,    4,    6,   15,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 17,    4,    6,   18,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 20,    6,   21,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5, 0x80000000 | 24, 0x80000000 | 5,    6,   23,   25,   26,

       0        // eod
};

void TCPImpl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TCPImpl *_t = static_cast<TCPImpl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sglOrderInsertCbk((*reinterpret_cast< AllTrade::ErrorCodeType(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const AllTrade::NPTradeCenter::OrderInfoPtr(*)>(_a[3])),(*reinterpret_cast< const AllTrade::NPMgrCenter::SOnlineAccountPtr(*)>(_a[4]))); break;
        case 1: _t->sglOrderCancelCbk((*reinterpret_cast< AllTrade::ErrorCodeType(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const AllTrade::NPTradeCenter::OrderInfoPtr(*)>(_a[3]))); break;
        case 2: _t->sglOrderChangeCbk((*reinterpret_cast< AllTrade::ErrorCodeType(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const AllTrade::NPTradeCenter::OrderInfoPtr(*)>(_a[3]))); break;
        case 3: _t->sglTradeCbk((*reinterpret_cast< AllTrade::ErrorCodeType(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const AllTrade::NPTradeCenter::TradeInfoPtr(*)>(_a[3]))); break;
        case 4: _t->sglPositionCbk((*reinterpret_cast< AllTrade::ErrorCodeType(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const AllTrade::NPTradeCenter::PositionInfoPtr(*)>(_a[3]))); break;
        case 5: _t->sglMoneyCbk((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const AllTrade::NPMgrCenter::SMoneyInfoPtr(*)>(_a[2]))); break;
        case 6: _t->sglRiskControlCbk((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< AllTrade::RiskControlType(*)>(_a[3])),(*reinterpret_cast< const std::string(*)>(_a[4]))); break;
        case 7: _t->slotNewConnection(); break;
        case 8: _t->slotRead(); break;
        case 9: _t->slotSendMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->slotSocketError(); break;
        case 11: _t->slotOrderInsertCbk((*reinterpret_cast< AllTrade::ErrorCodeType(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const AllTrade::NPTradeCenter::OrderInfoPtr(*)>(_a[3])),(*reinterpret_cast< const AllTrade::NPMgrCenter::SOnlineAccountPtr(*)>(_a[4]))); break;
        case 12: _t->slotOrderCancelCbk((*reinterpret_cast< AllTrade::ErrorCodeType(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const AllTrade::NPTradeCenter::OrderInfoPtr(*)>(_a[3]))); break;
        case 13: _t->slotOrderChangeCbk((*reinterpret_cast< AllTrade::ErrorCodeType(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const AllTrade::NPTradeCenter::OrderInfoPtr(*)>(_a[3]))); break;
        case 14: _t->slotTradeCbk((*reinterpret_cast< AllTrade::ErrorCodeType(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const AllTrade::NPTradeCenter::TradeInfoPtr(*)>(_a[3]))); break;
        case 15: _t->slotPositionCbk((*reinterpret_cast< AllTrade::ErrorCodeType(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const AllTrade::NPTradeCenter::PositionInfoPtr(*)>(_a[3]))); break;
        case 16: _t->slotMoneyCbk((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const AllTrade::NPMgrCenter::SMoneyInfoPtr(*)>(_a[2]))); break;
        case 17: _t->slotRiskControlCbk((*reinterpret_cast< const std::string(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< AllTrade::RiskControlType(*)>(_a[3])),(*reinterpret_cast< const std::string(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TCPImpl::*_t)(AllTrade::ErrorCodeType , const std::string & , const AllTrade::NPTradeCenter::OrderInfoPtr & , const AllTrade::NPMgrCenter::SOnlineAccountPtr & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPImpl::sglOrderInsertCbk)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TCPImpl::*_t)(AllTrade::ErrorCodeType , const std::string & , const AllTrade::NPTradeCenter::OrderInfoPtr & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPImpl::sglOrderCancelCbk)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TCPImpl::*_t)(AllTrade::ErrorCodeType , const std::string & , const AllTrade::NPTradeCenter::OrderInfoPtr & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPImpl::sglOrderChangeCbk)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TCPImpl::*_t)(AllTrade::ErrorCodeType , const std::string & , const AllTrade::NPTradeCenter::TradeInfoPtr & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPImpl::sglTradeCbk)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (TCPImpl::*_t)(AllTrade::ErrorCodeType , const std::string & , const AllTrade::NPTradeCenter::PositionInfoPtr & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPImpl::sglPositionCbk)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (TCPImpl::*_t)(const std::string & , const AllTrade::NPMgrCenter::SMoneyInfoPtr & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPImpl::sglMoneyCbk)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (TCPImpl::*_t)(const std::string & , const std::string & , AllTrade::RiskControlType , const std::string & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TCPImpl::sglRiskControlCbk)) {
                *result = 6;
                return;
            }
        }
    }
}

const QMetaObject TCPImpl::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_TCPImpl.data,
      qt_meta_data_TCPImpl,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TCPImpl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TCPImpl::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TCPImpl.stringdata0))
        return static_cast<void*>(const_cast< TCPImpl*>(this));
    if (!strcmp(_clname, "std::enable_shared_from_this<TCPImpl>"))
        return static_cast< std::enable_shared_from_this<TCPImpl>*>(const_cast< TCPImpl*>(this));
    if (!strcmp(_clname, "CommonTools::dispatcher_callback<CommonTools::CommandPtr>"))
        return static_cast< CommonTools::dispatcher_callback<CommonTools::CommandPtr>*>(const_cast< TCPImpl*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int TCPImpl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void TCPImpl::sglOrderInsertCbk(AllTrade::ErrorCodeType _t1, const std::string & _t2, const AllTrade::NPTradeCenter::OrderInfoPtr & _t3, const AllTrade::NPMgrCenter::SOnlineAccountPtr & _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TCPImpl::sglOrderCancelCbk(AllTrade::ErrorCodeType _t1, const std::string & _t2, const AllTrade::NPTradeCenter::OrderInfoPtr & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TCPImpl::sglOrderChangeCbk(AllTrade::ErrorCodeType _t1, const std::string & _t2, const AllTrade::NPTradeCenter::OrderInfoPtr & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TCPImpl::sglTradeCbk(AllTrade::ErrorCodeType _t1, const std::string & _t2, const AllTrade::NPTradeCenter::TradeInfoPtr & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TCPImpl::sglPositionCbk(AllTrade::ErrorCodeType _t1, const std::string & _t2, const AllTrade::NPTradeCenter::PositionInfoPtr & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void TCPImpl::sglMoneyCbk(const std::string & _t1, const AllTrade::NPMgrCenter::SMoneyInfoPtr & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void TCPImpl::sglRiskControlCbk(const std::string & _t1, const std::string & _t2, AllTrade::RiskControlType _t3, const std::string & _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
