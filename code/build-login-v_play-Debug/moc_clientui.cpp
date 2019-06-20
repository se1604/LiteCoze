/****************************************************************************
** Meta object code from reading C++ file 'clientui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../login/clientui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientUI_t {
    QByteArrayData data[20];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientUI_t qt_meta_stringdata_ClientUI = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ClientUI"
QT_MOC_LITERAL(1, 9, 9), // "idChanged"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 12), // "showClientUI"
QT_MOC_LITERAL(4, 33, 15), // "showAccountInfo"
QT_MOC_LITERAL(5, 49, 8), // "nickName"
QT_MOC_LITERAL(6, 58, 2), // "id"
QT_MOC_LITERAL(7, 61, 6), // "roomid"
QT_MOC_LITERAL(8, 68, 16), // "clearAccountInfo"
QT_MOC_LITERAL(9, 85, 13), // "showFriendMsg"
QT_MOC_LITERAL(10, 99, 3), // "msg"
QT_MOC_LITERAL(11, 103, 17), // "showNewFriendInfo"
QT_MOC_LITERAL(12, 121, 12), // "selectFriend"
QT_MOC_LITERAL(13, 134, 8), // "friendID"
QT_MOC_LITERAL(14, 143, 14), // "sendNewMessage"
QT_MOC_LITERAL(15, 158, 7), // "content"
QT_MOC_LITERAL(16, 166, 13), // "startSearchUI"
QT_MOC_LITERAL(17, 180, 22), // "acceptAddFriendRequest"
QT_MOC_LITERAL(18, 203, 8), // "nickname"
QT_MOC_LITERAL(19, 212, 16) // "flushAccountInfo"

    },
    "ClientUI\0idChanged\0\0showClientUI\0"
    "showAccountInfo\0nickName\0id\0roomid\0"
    "clearAccountInfo\0showFriendMsg\0msg\0"
    "showNewFriendInfo\0selectFriend\0friendID\0"
    "sendNewMessage\0content\0startSearchUI\0"
    "acceptAddFriendRequest\0nickname\0"
    "flushAccountInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       1,  104, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    3,   71,    2, 0x06 /* Public */,
       8,    0,   78,    2, 0x06 /* Public */,
       9,    3,   79,    2, 0x06 /* Public */,
      11,    2,   86,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      12,    1,   91,    2, 0x02 /* Public */,
      14,    1,   94,    2, 0x02 /* Public */,
      16,    0,   97,    2, 0x02 /* Public */,
      17,    2,   98,    2, 0x02 /* Public */,
      19,    0,  103,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    5,    6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    6,   10,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,   18,
    QMetaType::Void,

 // properties: name, type, flags
       6, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,

       0        // eod
};

void ClientUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientUI *_t = static_cast<ClientUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->idChanged(); break;
        case 1: _t->showClientUI(); break;
        case 2: _t->showAccountInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: _t->clearAccountInfo(); break;
        case 4: _t->showFriendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 5: _t->showNewFriendInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->selectFriend((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->sendNewMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->startSearchUI(); break;
        case 9: _t->acceptAddFriendRequest((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->flushAccountInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClientUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientUI::idChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ClientUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientUI::showClientUI)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ClientUI::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientUI::showAccountInfo)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ClientUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientUI::clearAccountInfo)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ClientUI::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientUI::showFriendMsg)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ClientUI::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientUI::showNewFriendInfo)) {
                *result = 5;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        ClientUI *_t = static_cast<ClientUI *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->id(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        ClientUI *_t = static_cast<ClientUI *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setId(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ClientUI::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientUI.data,
      qt_meta_data_ClientUI,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ClientUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientUI.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ClientUI::idChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ClientUI::showClientUI()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ClientUI::showAccountInfo(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ClientUI::clearAccountInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ClientUI::showFriendMsg(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClientUI::showNewFriendInfo(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
