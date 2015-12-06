/****************************************************************************
** Meta object code from reading C++ file 'CardSetDlg.h'
**
** Created: Sun Mar 30 10:01:47 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CardSetDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CardSetDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_CardSetDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      26,   11,   11,   11, 0x05,
      46,   11,   11,   11, 0x05,
      53,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   11,   11,   11, 0x09,
      82,   11,   11,   11, 0x09,
     105,   11,   11,   11, 0x09,
     126,   11,   11,   11, 0x09,
     151,   11,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CardSetDlg[] = {
    "CardSetDlg\0\0edit(QString)\0deleteCard(QString)\0"
    "save()\0import()\0on_addBtn_clicked()\0"
    "on_deleteBtn_clicked()\0on_editBtn_clicked()\0"
    "on_saveFileBtn_clicked()\0"
    "on_importXMLBtn_clicked()\0"
};

void CardSetDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CardSetDlg *_t = static_cast<CardSetDlg *>(_o);
        switch (_id) {
        case 0: _t->edit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->deleteCard((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->save(); break;
        case 3: _t->import(); break;
        case 4: _t->on_addBtn_clicked(); break;
        case 5: _t->on_deleteBtn_clicked(); break;
        case 6: _t->on_editBtn_clicked(); break;
        case 7: _t->on_saveFileBtn_clicked(); break;
        case 8: _t->on_importXMLBtn_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData CardSetDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject CardSetDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CardSetDlg,
      qt_meta_data_CardSetDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &CardSetDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *CardSetDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *CardSetDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CardSetDlg))
        return static_cast<void*>(const_cast< CardSetDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int CardSetDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void CardSetDlg::edit(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CardSetDlg::deleteCard(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CardSetDlg::save()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void CardSetDlg::import()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
