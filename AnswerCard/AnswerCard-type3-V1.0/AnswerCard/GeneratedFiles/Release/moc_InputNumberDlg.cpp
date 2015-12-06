/****************************************************************************
** Meta object code from reading C++ file 'InputNumberDlg.h'
**
** Created: Mon Apr 14 15:53:50 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../InputNumberDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'InputNumberDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_InputNumberDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      16,   15,   15,   15, 0x09,
      35,   15,   15,   15, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_InputNumberDlg[] = {
    "InputNumberDlg\0\0on_okBtn_clicked()\0"
    "on_cancelBtn_clicked()\0"
};

void InputNumberDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        InputNumberDlg *_t = static_cast<InputNumberDlg *>(_o);
        switch (_id) {
        case 0: _t->on_okBtn_clicked(); break;
        case 1: _t->on_cancelBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData InputNumberDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject InputNumberDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InputNumberDlg,
      qt_meta_data_InputNumberDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &InputNumberDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *InputNumberDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *InputNumberDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InputNumberDlg))
        return static_cast<void*>(const_cast< InputNumberDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int InputNumberDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
static const uint qt_meta_data_TipMsgBox[] = {

 // content:
       6,       // revision
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

static const char qt_meta_stringdata_TipMsgBox[] = {
    "TipMsgBox\0"
};

void TipMsgBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData TipMsgBox::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TipMsgBox::staticMetaObject = {
    { &QMessageBox::staticMetaObject, qt_meta_stringdata_TipMsgBox,
      qt_meta_data_TipMsgBox, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TipMsgBox::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TipMsgBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TipMsgBox::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TipMsgBox))
        return static_cast<void*>(const_cast< TipMsgBox*>(this));
    return QMessageBox::qt_metacast(_clname);
}

int TipMsgBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMessageBox::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
