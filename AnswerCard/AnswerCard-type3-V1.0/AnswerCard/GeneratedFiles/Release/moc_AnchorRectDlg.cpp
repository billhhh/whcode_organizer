/****************************************************************************
** Meta object code from reading C++ file 'AnchorRectDlg.h'
**
** Created: Mon Apr 14 15:53:49 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AnchorRectDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnchorRectDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AnchorRectDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      28,   14,   14,   14, 0x09,
      51,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AnchorRectDlg[] = {
    "AnchorRectDlg\0\0anchorDone()\0"
    "on_anchorBtn_clicked()\0on_confirmBtn_clicked()\0"
};

void AnchorRectDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AnchorRectDlg *_t = static_cast<AnchorRectDlg *>(_o);
        switch (_id) {
        case 0: _t->anchorDone(); break;
        case 1: _t->on_anchorBtn_clicked(); break;
        case 2: _t->on_confirmBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AnchorRectDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AnchorRectDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AnchorRectDlg,
      qt_meta_data_AnchorRectDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AnchorRectDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AnchorRectDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AnchorRectDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnchorRectDlg))
        return static_cast<void*>(const_cast< AnchorRectDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int AnchorRectDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AnchorRectDlg::anchorDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
