/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Jun 11 21:35:34 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      38,   11,   11,   11, 0x08,
      81,   75,   11,   11, 0x08,
     119,   11,   11,   11, 0x08,
     146,   11,   11,   11, 0x08,
     175,   11,   11,   11, 0x08,
     201,   11,   11,   11, 0x08,
     224,   11,   11,   11, 0x08,
     248,   11,   11,   11, 0x08,
     274,   11,   11,   11, 0x08,
     300,   11,   11,   11, 0x08,
     324,   11,   11,   11, 0x08,
     350,   11,   11,   11, 0x08,
     376,   11,   11,   11, 0x08,
     427,   11,   11,   11, 0x08,
     451,   11,   11,   11, 0x08,
     475,   11,   11,   11, 0x08,
     501,   11,   11,   11, 0x08,
     527,   11,   11,   11, 0x08,
     572,   11,   11,   11, 0x08,
     615,  608,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_actionQuit_triggered()\0"
    "on_horizontalSlider_sliderReleased()\0"
    "value\0on_horizontalSlider_valueChanged(int)\0"
    "on_actionBlank_triggered()\0"
    "on_actionRestore_triggered()\0"
    "on_actionFull_triggered()\0"
    "on_action5_triggered()\0on_pushButton_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_action20_triggered()\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "trayIconClicked(QSystemTrayIcon::ActivationReason)\0"
    "on_action50_triggered()\0on_action75_triggered()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_7_clicked()\0"
    "on_actionSee_savedbacklight_file_triggered()\0"
    "on_horizontalSlider_sliderPressed()\0"
    "action\0on_horizontalSlider_actionTriggered(int)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_actionQuit_triggered(); break;
        case 1: _t->on_horizontalSlider_sliderReleased(); break;
        case 2: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_actionBlank_triggered(); break;
        case 4: _t->on_actionRestore_triggered(); break;
        case 5: _t->on_actionFull_triggered(); break;
        case 6: _t->on_action5_triggered(); break;
        case 7: _t->on_pushButton_clicked(); break;
        case 8: _t->on_pushButton_2_clicked(); break;
        case 9: _t->on_pushButton_3_clicked(); break;
        case 10: _t->on_action20_triggered(); break;
        case 11: _t->on_pushButton_5_clicked(); break;
        case 12: _t->on_pushButton_4_clicked(); break;
        case 13: _t->trayIconClicked((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 14: _t->on_action50_triggered(); break;
        case 15: _t->on_action75_triggered(); break;
        case 16: _t->on_pushButton_6_clicked(); break;
        case 17: _t->on_pushButton_7_clicked(); break;
        case 18: _t->on_actionSee_savedbacklight_file_triggered(); break;
        case 19: _t->on_horizontalSlider_sliderPressed(); break;
        case 20: _t->on_horizontalSlider_actionTriggered((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
