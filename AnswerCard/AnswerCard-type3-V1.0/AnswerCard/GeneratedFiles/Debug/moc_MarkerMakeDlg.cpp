/****************************************************************************
** Meta object code from reading C++ file 'MarkerMakeDlg.h'
**
** Created: Sun Mar 30 10:01:48 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MarkerMakeDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MarkerMakeDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MarkerMakeDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      33,   14,   14,   14, 0x05,
      50,   14,   14,   14, 0x05,
      69,   14,   14,   14, 0x05,
      89,   14,   14,   14, 0x05,
     100,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
     111,   14,   14,   14, 0x09,
     132,   14,   14,   14, 0x09,
     152,   14,   14,   14, 0x09,
     172,   14,   14,   14, 0x09,
     192,   14,   14,   14, 0x09,
     215,   14,   14,   14, 0x09,
     238,   14,   14,   14, 0x09,
     268,   14,   14,   14, 0x09,
     297,   14,   14,   14, 0x09,
     318,   14,   14,   14, 0x09,
     359,   14,   14,   14, 0x09,
     381,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MarkerMakeDlg[] = {
    "MarkerMakeDlg\0\0MarkerMakeBegin()\0"
    "MarkerMakeDone()\0MarkerMakeDelete()\0"
    "MarkerMakeClicked()\0rowBegin()\0"
    "colBegin()\0on_sizeBtn_clicked()\0"
    "on_horBtn_clicked()\0on_verBtn_clicked()\0"
    "on_addBtn_clicked()\0on_cancelBtn_clicked()\0"
    "on_deleteBtn_clicked()\0"
    "showClicked(QListWidgetItem*)\0"
    "on_deleteMarkerBtn_clicked()\0"
    "on_editBtn_clicked()\0"
    "on_subList_itemClicked(QListWidgetItem*)\0"
    "on_vDragBtn_clicked()\0on_hDragBtn_clicked()\0"
};

void MarkerMakeDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MarkerMakeDlg *_t = static_cast<MarkerMakeDlg *>(_o);
        switch (_id) {
        case 0: _t->MarkerMakeBegin(); break;
        case 1: _t->MarkerMakeDone(); break;
        case 2: _t->MarkerMakeDelete(); break;
        case 3: _t->MarkerMakeClicked(); break;
        case 4: _t->rowBegin(); break;
        case 5: _t->colBegin(); break;
        case 6: _t->on_sizeBtn_clicked(); break;
        case 7: _t->on_horBtn_clicked(); break;
        case 8: _t->on_verBtn_clicked(); break;
        case 9: _t->on_addBtn_clicked(); break;
        case 10: _t->on_cancelBtn_clicked(); break;
        case 11: _t->on_deleteBtn_clicked(); break;
        case 12: _t->showClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 13: _t->on_deleteMarkerBtn_clicked(); break;
        case 14: _t->on_editBtn_clicked(); break;
        case 15: _t->on_subList_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 16: _t->on_vDragBtn_clicked(); break;
        case 17: _t->on_hDragBtn_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MarkerMakeDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MarkerMakeDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MarkerMakeDlg,
      qt_meta_data_MarkerMakeDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MarkerMakeDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MarkerMakeDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MarkerMakeDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MarkerMakeDlg))
        return static_cast<void*>(const_cast< MarkerMakeDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int MarkerMakeDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void MarkerMakeDlg::MarkerMakeBegin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void MarkerMakeDlg::MarkerMakeDone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MarkerMakeDlg::MarkerMakeDelete()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MarkerMakeDlg::MarkerMakeClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void MarkerMakeDlg::rowBegin()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void MarkerMakeDlg::colBegin()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
