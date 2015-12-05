/****************************************************************************
** Meta object code from reading C++ file 'MarkerDlg.h'
**
** Created: Mon Jun 30 09:41:37 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AnswerCard/MarkerDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MarkerDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MarkerDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      24,   10,   10,   10, 0x09,
      51,   10,   10,   10, 0x09,
      78,   10,   10,   10, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MarkerDlg[] = {
    "MarkerDlg\0\0markerDone()\0"
    "on_horMarkersBtn_clicked()\0"
    "on_verMarkersBtn_clicked()\0"
    "on_confirmBtn_clicked()\0"
};

void MarkerDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MarkerDlg *_t = static_cast<MarkerDlg *>(_o);
        switch (_id) {
        case 0: _t->markerDone(); break;
        case 1: _t->on_horMarkersBtn_clicked(); break;
        case 2: _t->on_verMarkersBtn_clicked(); break;
        case 3: _t->on_confirmBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MarkerDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MarkerDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_MarkerDlg,
      qt_meta_data_MarkerDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MarkerDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MarkerDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MarkerDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MarkerDlg))
        return static_cast<void*>(const_cast< MarkerDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int MarkerDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void MarkerDlg::markerDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
