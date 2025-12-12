/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindow.h"
#include <QtNetwork/QSslError>
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10MainWindowE_t {};
} // unnamed namespace

template <> constexpr inline auto MainWindow::qt_create_metaobjectdata<qt_meta_tag_ZN10MainWindowE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MainWindow",
        "reservedPlaces",
        "",
        "unreservedPlaces",
        "colourSeat",
        "onCalculateRemainder",
        "newWindow",
        "backWindow",
        "selectSession",
        "selectPlaces",
        "logIn",
        "adminlogIn",
        "goToPageRegIn",
        "regIn",
        "regDone",
        "onReservePlaces",
        "onUnReservePlaces",
        "goToAdmin",
        "loadUserList",
        "loadAdminList",
        "markReservePlaces",
        "markUnReservePlaces",
        "adminPage",
        "showPassword",
        "backPage",
        "showPasswordAdmin",
        "errorLogIn",
        "errorRegIn",
        "deleteUserClicked",
        "userID",
        "deleteAdminClicked",
        "adminId",
        "on_addMovieButton_clicked",
        "handleMovieAddSuccess",
        "message",
        "handleMovieAddError",
        "error",
        "on_addSessionButton_clicked",
        "handleSessionAddSuccess",
        "handleSessionAddError",
        "loadSessionCreationData",
        "deleteMovieButtonClicked",
        "handleMovieDeleteSuccess",
        "handleMovieDeleteError",
        "loadAdminMovieList",
        "on_registerAdminButton_clicked",
        "handleAdminRegistrationSuccess",
        "handleAdminRegistrationError"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'reservedPlaces'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'unreservedPlaces'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'colourSeat'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCalculateRemainder'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'newWindow'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'backWindow'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'selectSession'
        QtMocHelpers::SlotData<void(int)>(8, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Slot 'selectPlaces'
        QtMocHelpers::SlotData<void(int)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 2 },
        }}),
        // Slot 'logIn'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'adminlogIn'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goToPageRegIn'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'regIn'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'regDone'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onReservePlaces'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onUnReservePlaces'
        QtMocHelpers::SlotData<void()>(16, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'goToAdmin'
        QtMocHelpers::SlotData<void()>(17, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'loadUserList'
        QtMocHelpers::SlotData<void()>(18, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'loadAdminList'
        QtMocHelpers::SlotData<void()>(19, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'markReservePlaces'
        QtMocHelpers::SlotData<void()>(20, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'markUnReservePlaces'
        QtMocHelpers::SlotData<void()>(21, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'adminPage'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'showPassword'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'backPage'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'showPasswordAdmin'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'errorLogIn'
        QtMocHelpers::SlotData<void(const QString &)>(26, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Slot 'errorRegIn'
        QtMocHelpers::SlotData<void(const QString &)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Slot 'deleteUserClicked'
        QtMocHelpers::SlotData<void(int)>(28, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 29 },
        }}),
        // Slot 'deleteAdminClicked'
        QtMocHelpers::SlotData<void(int)>(30, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 31 },
        }}),
        // Slot 'on_addMovieButton_clicked'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleMovieAddSuccess'
        QtMocHelpers::SlotData<void(const QString &)>(33, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 34 },
        }}),
        // Slot 'handleMovieAddError'
        QtMocHelpers::SlotData<void(const QString &)>(35, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
        // Slot 'on_addSessionButton_clicked'
        QtMocHelpers::SlotData<void()>(37, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleSessionAddSuccess'
        QtMocHelpers::SlotData<void(const QString &)>(38, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 34 },
        }}),
        // Slot 'handleSessionAddError'
        QtMocHelpers::SlotData<void(const QString &)>(39, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
        // Slot 'loadSessionCreationData'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'deleteMovieButtonClicked'
        QtMocHelpers::SlotData<void()>(41, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleMovieDeleteSuccess'
        QtMocHelpers::SlotData<void(const QString &)>(42, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 34 },
        }}),
        // Slot 'handleMovieDeleteError'
        QtMocHelpers::SlotData<void(const QString &)>(43, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
        // Slot 'loadAdminMovieList'
        QtMocHelpers::SlotData<void()>(44, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_registerAdminButton_clicked'
        QtMocHelpers::SlotData<void()>(45, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleAdminRegistrationSuccess'
        QtMocHelpers::SlotData<void(const QString &)>(46, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 34 },
        }}),
        // Slot 'handleAdminRegistrationError'
        QtMocHelpers::SlotData<void(const QString &)>(47, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 36 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<MainWindow, qt_meta_tag_ZN10MainWindowE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10MainWindowE_t>.metaTypes,
    nullptr
} };

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindow *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->reservedPlaces(); break;
        case 1: _t->unreservedPlaces(); break;
        case 2: _t->colourSeat(); break;
        case 3: _t->onCalculateRemainder(); break;
        case 4: _t->newWindow(); break;
        case 5: _t->backWindow(); break;
        case 6: _t->selectSession((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->selectPlaces((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->logIn(); break;
        case 9: _t->adminlogIn(); break;
        case 10: _t->goToPageRegIn(); break;
        case 11: _t->regIn(); break;
        case 12: _t->regDone(); break;
        case 13: _t->onReservePlaces(); break;
        case 14: _t->onUnReservePlaces(); break;
        case 15: _t->goToAdmin(); break;
        case 16: _t->loadUserList(); break;
        case 17: _t->loadAdminList(); break;
        case 18: _t->markReservePlaces(); break;
        case 19: _t->markUnReservePlaces(); break;
        case 20: _t->adminPage(); break;
        case 21: _t->showPassword(); break;
        case 22: _t->backPage(); break;
        case 23: _t->showPasswordAdmin(); break;
        case 24: _t->errorLogIn((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 25: _t->errorRegIn((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 26: _t->deleteUserClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 27: _t->deleteAdminClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 28: _t->on_addMovieButton_clicked(); break;
        case 29: _t->handleMovieAddSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 30: _t->handleMovieAddError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 31: _t->on_addSessionButton_clicked(); break;
        case 32: _t->handleSessionAddSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 33: _t->handleSessionAddError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 34: _t->loadSessionCreationData(); break;
        case 35: _t->deleteMovieButtonClicked(); break;
        case 36: _t->handleMovieDeleteSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 37: _t->handleMovieDeleteError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 38: _t->loadAdminMovieList(); break;
        case 39: _t->on_registerAdminButton_clicked(); break;
        case 40: _t->handleAdminRegistrationSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 41: _t->handleAdminRegistrationError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::reservedPlaces, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MainWindow::*)()>(_a, &MainWindow::unreservedPlaces, 1))
            return;
    }
}

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10MainWindowE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 42)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 42;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 42)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 42;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::reservedPlaces()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::unreservedPlaces()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
