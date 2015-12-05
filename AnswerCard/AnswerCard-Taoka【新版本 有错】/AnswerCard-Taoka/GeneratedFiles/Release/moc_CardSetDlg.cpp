/****************************************************************************
** Meta object code from reading C++ file 'CardSetDlg.h'
**
** Created: Thu Apr 10 19:33:51 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CardSet/CardSetDlg.h"
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
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x09,
      37,   11,   11,   11, 0x09,
      65,   11,   11,   11, 0x09,
      91,   11,   11,   11, 0x09,
     117,   11,   11,   11, 0x09,
     145,   11,   11,   11, 0x09,
     170,   11,   11,   11, 0x09,
     194,   11,   11,   11, 0x09,
     223,  221,   11,   11, 0x09,
     250,   11,   11,   11, 0x09,
     276,   11,   11,   11, 0x09,
     305,   11,   11,   11, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_CardSetDlg[] = {
    "CardSetDlg\0\0on_addPaperBtn_clicked()\0"
    "on_deletePaperBtn_clicked()\0"
    "on_openPaperBtn_clicked()\0"
    "on_savePaperBtn_clicked()\0"
    "on_importPaperBtn_clicked()\0"
    "on_editPageBtn_clicked()\0"
    "on_addPageBtn_clicked()\0"
    "on_deletePageBtn_clicked()\0,\0"
    "updatePageDetails(int,int)\0"
    "on_addCourseBtn_clicked()\0"
    "on_deleteCourseBtn_clicked()\0"
    "courseChanged(int)\0"
};

void CardSetDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        CardSetDlg *_t = static_cast<CardSetDlg *>(_o);
        switch (_id) {
        case 0: _t->on_addPaperBtn_clicked(); break;
        case 1: _t->on_deletePaperBtn_clicked(); break;
        case 2: _t->on_openPaperBtn_clicked(); break;
        case 3: _t->on_savePaperBtn_clicked(); break;
        case 4: _t->on_importPaperBtn_clicked(); break;
        case 5: _t->on_editPageBtn_clicked(); break;
        case 6: _t->on_addPageBtn_clicked(); break;
        case 7: _t->on_deletePageBtn_clicked(); break;
        case 8: _t->updatePageDetails((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->on_addCourseBtn_clicked(); break;
        case 10: _t->on_deleteCourseBtn_clicked(); break;
        case 11: _t->courseChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
