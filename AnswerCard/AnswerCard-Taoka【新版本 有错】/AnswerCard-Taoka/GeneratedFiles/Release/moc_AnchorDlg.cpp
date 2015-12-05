/****************************************************************************
** Meta object code from reading C++ file 'AnchorDlg.h'
**
** Created: Thu Apr 10 19:33:52 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AnswerCard/AnchorDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnchorDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AnchorDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      24,   10,   10,   10, 0x09,
      49,   10,   10,   10, 0x09,
      74,   10,   10,   10, 0x09,
      99,   10,   10,   10, 0x09,
     124,   10,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AnchorDlg[] = {
    "AnchorDlg\0\0anchorDone()\0"
    "on_anchorLTBtn_clicked()\0"
    "on_anchorRTBtn_clicked()\0"
    "on_anchorLBBtn_clicked()\0"
    "on_anchorRBBtn_clicked()\0"
    "on_confirmBtn_clicked()\0"
};

void AnchorDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AnchorDlg *_t = static_cast<AnchorDlg *>(_o);
        switch (_id) {
        case 0: _t->anchorDone(); break;
        case 1: _t->on_anchorLTBtn_clicked(); break;
        case 2: _t->on_anchorRTBtn_clicked(); break;
        case 3: _t->on_anchorLBBtn_clicked(); break;
        case 4: _t->on_anchorRBBtn_clicked(); break;
        case 5: _t->on_confirmBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AnchorDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AnchorDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AnchorDlg,
      qt_meta_data_AnchorDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AnchorDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AnchorDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AnchorDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnchorDlg))
        return static_cast<void*>(const_cast< AnchorDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int AnchorDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void AnchorDlg::anchorDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
