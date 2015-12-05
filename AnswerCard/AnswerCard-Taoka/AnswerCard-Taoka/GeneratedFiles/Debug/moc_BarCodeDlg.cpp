/****************************************************************************
** Meta object code from reading C++ file 'BarCodeDlg.h'
**
** Created: Mon Jun 30 09:41:38 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AnswerCard/BarCodeDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BarCodeDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BarCodeDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      27,   11,   11,   11, 0x05,
      41,   11,   11,   11, 0x05,
      57,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      77,   11,   11,   11, 0x09,
      97,   11,   11,   11, 0x09,
     121,   11,   11,   11, 0x09,
     149,  144,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_BarCodeDlg[] = {
    "BarCodeDlg\0\0barCodeBegin()\0barCodeDone()\0"
    "barCodeDelete()\0barCodeClicked(int)\0"
    "on_addBtn_clicked()\0on_confirmBtn_clicked()\0"
    "on_deleteBtn_clicked()\0item\0"
    "showClicked(QListWidgetItem*)\0"
};

void BarCodeDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BarCodeDlg *_t = static_cast<BarCodeDlg *>(_o);
        switch (_id) {
        case 0: _t->barCodeBegin(); break;
        case 1: _t->barCodeDone(); break;
        case 2: _t->barCodeDelete(); break;
        case 3: _t->barCodeClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_addBtn_clicked(); break;
        case 5: _t->on_confirmBtn_clicked(); break;
        case 6: _t->on_deleteBtn_clicked(); break;
        case 7: _t->showClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BarCodeDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BarCodeDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_BarCodeDlg,
      qt_meta_data_BarCodeDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BarCodeDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BarCodeDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BarCodeDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BarCodeDlg))
        return static_cast<void*>(const_cast< BarCodeDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int BarCodeDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void BarCodeDlg::barCodeBegin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void BarCodeDlg::barCodeDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void BarCodeDlg::barCodeDelete()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void BarCodeDlg::barCodeClicked(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
