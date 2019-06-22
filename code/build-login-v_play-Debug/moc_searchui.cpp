/****************************************************************************
** Meta object code from reading C++ file 'searchui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../login/searchui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'searchui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SearchUi_t {
    QByteArrayData data[13];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SearchUi_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SearchUi_t qt_meta_stringdata_SearchUi = {
    {
QT_MOC_LITERAL(0, 0, 8), // "SearchUi"
QT_MOC_LITERAL(1, 9, 12), // "showSearchUI"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "showFindInfo"
QT_MOC_LITERAL(4, 36, 8), // "nickName"
QT_MOC_LITERAL(5, 45, 2), // "id"
QT_MOC_LITERAL(6, 48, 17), // "showFindGroupInfo"
QT_MOC_LITERAL(7, 66, 4), // "name"
QT_MOC_LITERAL(8, 71, 11), // "findNetizen"
QT_MOC_LITERAL(9, 83, 9), // "findGroup"
QT_MOC_LITERAL(10, 93, 9), // "addFriend"
QT_MOC_LITERAL(11, 103, 8), // "addGroup"
QT_MOC_LITERAL(12, 112, 6) // "roomid"

    },
    "SearchUi\0showSearchUI\0\0showFindInfo\0"
    "nickName\0id\0showFindGroupInfo\0name\0"
    "findNetizen\0findGroup\0addFriend\0"
    "addGroup\0roomid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SearchUi[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    2,   50,    2, 0x06 /* Public */,
       6,    2,   55,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       8,    1,   60,    2, 0x02 /* Public */,
       9,    1,   63,    2, 0x02 /* Public */,
      10,    1,   66,    2, 0x02 /* Public */,
      11,    1,   69,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    5,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void SearchUi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SearchUi *_t = static_cast<SearchUi *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showSearchUI(); break;
        case 1: _t->showFindInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->showFindGroupInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->findNetizen((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->findGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->addFriend((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->addGroup((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SearchUi::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchUi::showSearchUI)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SearchUi::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchUi::showFindInfo)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SearchUi::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchUi::showFindGroupInfo)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SearchUi::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SearchUi.data,
      qt_meta_data_SearchUi,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SearchUi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SearchUi::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SearchUi.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SearchUi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SearchUi::showSearchUI()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SearchUi::showFindInfo(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SearchUi::showFindGroupInfo(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
