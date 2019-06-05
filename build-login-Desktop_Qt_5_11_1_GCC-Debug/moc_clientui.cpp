/****************************************************************************
** Meta object code from reading C++ file 'clientui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LiteCoze_du/login/clientui.h"
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
    QByteArrayData data[12];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientUI_t qt_meta_stringdata_ClientUI = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ClientUI"
QT_MOC_LITERAL(1, 9, 12), // "showClientUI"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "showAccountInfo"
QT_MOC_LITERAL(4, 39, 8), // "nickName"
QT_MOC_LITERAL(5, 48, 2), // "id"
QT_MOC_LITERAL(6, 51, 13), // "showFriendMsg"
QT_MOC_LITERAL(7, 65, 3), // "msg"
QT_MOC_LITERAL(8, 69, 12), // "selectFriend"
QT_MOC_LITERAL(9, 82, 8), // "friendID"
QT_MOC_LITERAL(10, 91, 14), // "sendNewMessage"
QT_MOC_LITERAL(11, 106, 7) // "content"

    },
    "ClientUI\0showClientUI\0\0showAccountInfo\0"
    "nickName\0id\0showFriendMsg\0msg\0"
    "selectFriend\0friendID\0sendNewMessage\0"
    "content"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    2,   40,    2, 0x06 /* Public */,
       6,    2,   45,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       8,    1,   50,    2, 0x02 /* Public */,
      10,    1,   53,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    7,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,

       0        // eod
};

void ClientUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientUI *_t = static_cast<ClientUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showClientUI(); break;
        case 1: _t->showAccountInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->showFriendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->selectFriend((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sendNewMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClientUI::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientUI::showClientUI)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ClientUI::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientUI::showAccountInfo)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ClientUI::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientUI::showFriendMsg)) {
                *result = 2;
                return;
            }
        }
    }
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
void ClientUI::showClientUI()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ClientUI::showAccountInfo(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClientUI::showFriendMsg(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
