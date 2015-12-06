/****************************************************************************
** Meta object code from reading C++ file 'ClearDlg.h'
**
** Created: Mon Apr 14 15:53:49 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ClearDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClearDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ClearDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      22,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,    9,    9,    9, 0x09,
      56,    9,    9,    9, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_ClearDlg[] = {
    "ClearDlg\0\0changePic()\0clearCard()\0"
    "on_clearBtn_clicked()\0on_changePicBtn_clicked()\0"
};

void ClearDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ClearDlg *_t = static_cast<ClearDlg *>(_o);
        switch (_id) {
        case 0: _t->changePic(); break;
        case 1: _t->clearCard(); break;
        case 2: _t->on_clearBtn_clicked(); break;
        case 3: _t->on_changePicBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData ClearDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ClearDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ClearDlg,
      qt_meta_data_ClearDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ClearDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ClearDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ClearDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClearDlg))
        return static_cast<void*>(const_cast< ClearDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int ClearDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ClearDlg::changePic()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ClearDlg::clearCard()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
