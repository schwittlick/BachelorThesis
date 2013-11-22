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
    QByteArrayData data[24];
    char stringdata[366];
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
QT_MOC_LITERAL(4, 35, 14),
QT_MOC_LITERAL(5, 50, 19),
QT_MOC_LITERAL(6, 70, 14),
QT_MOC_LITERAL(7, 85, 10),
QT_MOC_LITERAL(8, 96, 11),
QT_MOC_LITERAL(9, 108, 8),
QT_MOC_LITERAL(10, 117, 27),
QT_MOC_LITERAL(11, 145, 24),
QT_MOC_LITERAL(12, 170, 24),
QT_MOC_LITERAL(13, 195, 21),
QT_MOC_LITERAL(14, 217, 17),
QT_MOC_LITERAL(15, 235, 11),
QT_MOC_LITERAL(16, 247, 21),
QT_MOC_LITERAL(17, 269, 22),
QT_MOC_LITERAL(18, 292, 13),
QT_MOC_LITERAL(19, 306, 6),
QT_MOC_LITERAL(20, 313, 16),
QT_MOC_LITERAL(21, 330, 9),
QT_MOC_LITERAL(22, 340, 15),
QT_MOC_LITERAL(23, 356, 8)
    },
    "BachelorThesis\0loadImage\0\0openFile\0"
    "openSampleFile\0changePlaybackSpeed\0"
    "_playbackSpeed\0startVideo\0jumpToFrame\0"
    "_frameNr\0toggleBackgroundSubtraction\0"
    "_doBackgroundSubtraction\0"
    "toggleMeanShiftFiltering\0_doMeanShiftFiltering\0"
    "blurAmountChanged\0_blurAmount\0"
    "openLukasKanadeWindow\0openHardwareInfoDialog\0"
    "changeLKIters\0_iters\0changeLKMaxlevel\0"
    "_maxLevel\0changeLKWinSize\0_winSize\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BachelorThesis[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x0a,
       3,    0,   85,    2, 0x0a,
       4,    0,   86,    2, 0x0a,
       5,    1,   87,    2, 0x0a,
       7,    0,   90,    2, 0x0a,
       8,    1,   91,    2, 0x0a,
      10,    1,   94,    2, 0x0a,
      12,    1,   97,    2, 0x0a,
      14,    1,  100,    2, 0x0a,
      16,    0,  103,    2, 0x0a,
      17,    0,  104,    2, 0x0a,
      18,    1,  105,    2, 0x0a,
      20,    1,  108,    2, 0x0a,
      22,    1,  111,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void, QMetaType::Int,   23,

       0        // eod
};

void BachelorThesis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        BachelorThesis *_t = static_cast<BachelorThesis *>(_o);
        switch (_id) {
        case 0: _t->loadImage(); break;
        case 1: _t->openFile(); break;
        case 2: _t->openSampleFile(); break;
        case 3: _t->changePlaybackSpeed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->startVideo(); break;
        case 5: _t->jumpToFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->toggleBackgroundSubtraction((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->toggleMeanShiftFiltering((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->blurAmountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->openLukasKanadeWindow(); break;
        case 10: _t->openHardwareInfoDialog(); break;
        case 11: _t->changeLKIters((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->changeLKMaxlevel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->changeLKWinSize((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
