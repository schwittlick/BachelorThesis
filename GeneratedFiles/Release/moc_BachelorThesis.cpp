/****************************************************************************
** Meta object code from reading C++ file 'BachelorThesis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../BachelorThesis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BachelorThesis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_BachelorThesis_t {
    QByteArrayData data[9];
    char stringdata[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_BachelorThesis_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_BachelorThesis_t qt_meta_stringdata_BachelorThesis = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 9),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 8),
QT_MOC_LITERAL(4, 35, 19),
QT_MOC_LITERAL(5, 55, 14),
QT_MOC_LITERAL(6, 70, 10),
QT_MOC_LITERAL(7, 81, 11),
QT_MOC_LITERAL(8, 93, 8)
    },
    "BachelorThesis\0loadImage\0\0openFile\0"
    "changePlaybackSpeed\0_playbackSpeed\0"
    "startVideo\0jumpToFrame\0_frameNr\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BachelorThesis[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a,
       3,    0,   40,    2, 0x0a,
       4,    1,   41,    2, 0x0a,
       6,    0,   44,    2, 0x0a,
       7,    1,   45,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void BachelorThesis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BachelorThesis *_t = static_cast<BachelorThesis *>(_o);
        switch (_id) {
        case 0: _t->loadImage(); break;
        case 1: _t->openFile(); break;
        case 2: _t->changePlaybackSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->startVideo(); break;
        case 4: _t->jumpToFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject BachelorThesis::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BachelorThesis.data,
      qt_meta_data_BachelorThesis,  qt_static_metacall, 0, 0}
};


const QMetaObject *BachelorThesis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BachelorThesis::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BachelorThesis.stringdata))
        return static_cast<void*>(const_cast< BachelorThesis*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BachelorThesis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
