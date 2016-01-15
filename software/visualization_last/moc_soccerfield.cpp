/****************************************************************************
** Meta object code from reading C++ file 'soccerfield.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.0.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "soccerfield.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'soccerfield.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.0.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SoccerField_t {
    QByteArrayData data[19];
    char stringdata[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SoccerField_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SoccerField_t qt_meta_stringdata_SoccerField = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 5),
QT_MOC_LITERAL(2, 18, 0),
QT_MOC_LITERAL(3, 19, 11),
QT_MOC_LITERAL(4, 31, 7),
QT_MOC_LITERAL(5, 39, 8),
QT_MOC_LITERAL(6, 48, 8),
QT_MOC_LITERAL(7, 57, 4),
QT_MOC_LITERAL(8, 62, 5),
QT_MOC_LITERAL(9, 68, 7),
QT_MOC_LITERAL(10, 76, 1),
QT_MOC_LITERAL(11, 78, 7),
QT_MOC_LITERAL(12, 86, 17),
QT_MOC_LITERAL(13, 104, 1),
QT_MOC_LITERAL(14, 106, 3),
QT_MOC_LITERAL(15, 110, 7),
QT_MOC_LITERAL(16, 118, 11),
QT_MOC_LITERAL(17, 130, 12),
QT_MOC_LITERAL(18, 143, 13)
    },
    "SoccerField\0timer\0\0restartGame\0endGame\0"
    "copyThis\0char[30]\0read\0write\0savePos\0"
    "n\0loadPos\0unsigned long int\0p\0fwd\0"
    "getPose\0goalDisplay\0getPositions\0"
    "readPositions\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SoccerField[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       3,    0,   65,    2, 0x0a,
       4,    0,   66,    2, 0x0a,
       5,    2,   67,    2, 0x0a,
       9,    2,   72,    2, 0x0a,
      11,    3,   77,    2, 0x0a,
      15,    0,   84,    2, 0x0a,
      16,    0,   85,    2, 0x0a,
      17,    0,   86,    2, 0x08,
      18,    0,   87,    2, 0x08,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    7,    8,
    QMetaType::Void, 0x80000000 | 6, QMetaType::Bool,    8,   10,
    0x80000000 | 12, 0x80000000 | 6, 0x80000000 | 12, QMetaType::Bool,    7,   13,   14,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SoccerField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SoccerField *_t = static_cast<SoccerField *>(_o);
        switch (_id) {
        case 0: _t->timer(); break;
        case 1: _t->restartGame(); break;
        case 2: _t->endGame(); break;
        case 3: _t->copyThis((*reinterpret_cast< char(*)[30]>(_a[1])),(*reinterpret_cast< char(*)[30]>(_a[2]))); break;
        case 4: _t->savePos((*reinterpret_cast< char(*)[30]>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: { unsigned long int _r = _t->loadPos((*reinterpret_cast< char(*)[30]>(_a[1])),(*reinterpret_cast< unsigned long int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< unsigned long int*>(_a[0]) = _r; }  break;
        case 6: _t->getPose(); break;
        case 7: { int _r = _t->goalDisplay();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 8: _t->getPositions(); break;
        case 9: _t->readPositions(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SoccerField::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SoccerField::timer)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SoccerField::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SoccerField.data,
      qt_meta_data_SoccerField,  qt_static_metacall, 0, 0}
};


const QMetaObject *SoccerField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SoccerField::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SoccerField.stringdata))
        return static_cast<void*>(const_cast< SoccerField*>(this));
    return QWidget::qt_metacast(_clname);
}

int SoccerField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SoccerField::timer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
