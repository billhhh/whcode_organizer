/****************************************************************************
** Meta object code from reading C++ file 'LineDetectDlg.h'
**
** Created: Thu Apr 10 19:33:51 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AnswerCard/LineDetectDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LineDetectDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LineDetectDlg[] = {

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
      15,   14,   14,   14, 0x05,
      26,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      38,   14,   14,   14, 0x09,
      64,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_LineDetectDlg[] = {
    "LineDetectDlg\0\0lineDone()\0lineBegin()\0"
    "on_blackLineBtn_clicked()\0"
    "on_whiteLineBtn_clicked()\0"
};

void LineDetectDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LineDetectDlg *_t = static_cast<LineDetectDlg *>(_o);
        switch (_id) {
        case 0: _t->lineDone(); break;
        case 1: _t->lineBegin(); break;
        case 2: _t->on_blackLineBtn_clicked(); break;
        case 3: _t->on_whiteLineBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData LineDetectDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LineDetectDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LineDetectDlg,
      qt_meta_data_LineDetectDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LineDetectDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LineDetectDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LineDetectDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LineDetectDlg))
        return static_cast<void*>(const_cast< LineDetectDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int LineDetectDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void LineDetectDlg::lineDone()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void LineDetectDlg::lineBegin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
