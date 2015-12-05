/****************************************************************************
** Meta object code from reading C++ file 'AnswerCardDlg.h'
**
** Created: Thu Apr 10 19:33:52 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../AnswerCard/AnswerCardDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AnswerCardDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AnswerCardDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x09,
      36,   14,   14,   14, 0x09,
      49,   14,   14,   14, 0x09,
      62,   14,   14,   14, 0x09,
      74,   14,   14,   14, 0x09,
      89,   14,   14,   14, 0x09,
     106,   14,   14,   14, 0x09,
     118,   14,   14,   14, 0x09,
     137,   14,   14,   14, 0x09,
     155,   14,   14,   14, 0x09,
     172,   14,   14,   14, 0x09,
     191,  187,   14,   14, 0x09,
     208,  187,   14,   14, 0x09,
     228,  187,   14,   14, 0x09,
     250,  187,   14,   14, 0x09,
     270,  187,   14,   14, 0x09,
     287,   14,   14,   14, 0x09,
     309,   14,   14,   14, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_AnswerCardDlg[] = {
    "AnswerCardDlg\0\0on_backBtn_clicked()\0"
    "anchorDone()\0markerDone()\0enableDlg()\0"
    "barCodeBegin()\0fillPointBegin()\0"
    "clipBegin()\0deleteBtnClicked()\0"
    "lineDetectBegin()\0lineDetectDone()\0"
    "idPointBegin()\0idx\0clipClicked(int)\0"
    "barCodeClicked(int)\0fillPointClicked(int)\0"
    "idPointClicked(int)\0pageChanged(int)\0"
    "on_clearBtn_clicked()\0on_changePicBtn_clicked()\0"
};

void AnswerCardDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AnswerCardDlg *_t = static_cast<AnswerCardDlg *>(_o);
        switch (_id) {
        case 0: _t->on_backBtn_clicked(); break;
        case 1: _t->anchorDone(); break;
        case 2: _t->markerDone(); break;
        case 3: _t->enableDlg(); break;
        case 4: _t->barCodeBegin(); break;
        case 5: _t->fillPointBegin(); break;
        case 6: _t->clipBegin(); break;
        case 7: _t->deleteBtnClicked(); break;
        case 8: _t->lineDetectBegin(); break;
        case 9: _t->lineDetectDone(); break;
        case 10: _t->idPointBegin(); break;
        case 11: _t->clipClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->barCodeClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->fillPointClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->idPointClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->pageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_clearBtn_clicked(); break;
        case 17: _t->on_changePicBtn_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AnswerCardDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AnswerCardDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AnswerCardDlg,
      qt_meta_data_AnswerCardDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AnswerCardDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AnswerCardDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AnswerCardDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AnswerCardDlg))
        return static_cast<void*>(const_cast< AnswerCardDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int AnswerCardDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
