/****************************************************************************
** Meta object code from reading C++ file 'basicopenglview.h'
**
** Created: Tue Sep 30 15:16:42 2014
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "basicopenglview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basicopenglview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BasicOpenGLView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      21,   17,   16,   16, 0x0a,
      52,   46,   16,   16, 0x0a,
      67,   17,   16,   16, 0x0a,
      88,   16,   16,   16, 0x0a,
      97,   95,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BasicOpenGLView[] = {
    "BasicOpenGLView\0\0x,y\0translate(double,double)\0"
    "angle\0rotate(double)\0scale(double,double)\0"
    "undo()\0m\0applyMatrix(double[][3])\0"
};

void BasicOpenGLView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        BasicOpenGLView *_t = static_cast<BasicOpenGLView *>(_o);
        switch (_id) {
        case 0: _t->translate((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 1: _t->rotate((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->scale((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        case 3: _t->undo(); break;
        case 4: _t->applyMatrix((*reinterpret_cast< double(*)[][3]>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData BasicOpenGLView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject BasicOpenGLView::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_BasicOpenGLView,
      qt_meta_data_BasicOpenGLView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BasicOpenGLView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BasicOpenGLView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BasicOpenGLView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BasicOpenGLView))
        return static_cast<void*>(const_cast< BasicOpenGLView*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int BasicOpenGLView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
