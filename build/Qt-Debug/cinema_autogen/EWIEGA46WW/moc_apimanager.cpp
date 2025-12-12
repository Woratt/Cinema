/****************************************************************************
** Meta object code from reading C++ file 'apimanager.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../apimanager.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apimanager.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN10ApiManagerE_t {};
} // unnamed namespace

template <> constexpr inline auto ApiManager::qt_create_metaobjectdata<qt_meta_tag_ZN10ApiManagerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "ApiManager",
        "registrationSuccess",
        "",
        "registrationError",
        "adminLoginSuccess",
        "adminLoginError",
        "loginSuccess",
        "loginError",
        "hallSuccess",
        "hallError",
        "reservePlaceSucces",
        "reservePlaceError",
        "uploadFinished",
        "fileUrl",
        "uploadFailed",
        "error",
        "movieAddSuccess",
        "message",
        "movieAddError",
        "sessionAddSuccess",
        "sessionAddError",
        "movieDeleteSuccess",
        "movieDeleteError",
        "adminRegistrationSuccess",
        "adminRegistrationError",
        "onReplyFinished",
        "QNetworkReply*",
        "onUploadProgress",
        "bytesSent",
        "bytesTotal",
        "onUploadFinished",
        "onNetworkError",
        "QNetworkReply::NetworkError",
        "onReadyRead"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'registrationSuccess'
        QtMocHelpers::SignalData<void(const QString &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'registrationError'
        QtMocHelpers::SignalData<void(const QString &)>(3, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'adminLoginSuccess'
        QtMocHelpers::SignalData<void(const QString &)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'adminLoginError'
        QtMocHelpers::SignalData<void(const QString &)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'loginSuccess'
        QtMocHelpers::SignalData<void(const QString &)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'loginError'
        QtMocHelpers::SignalData<void(const QString &)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'hallSuccess'
        QtMocHelpers::SignalData<void(const QString &)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'hallError'
        QtMocHelpers::SignalData<void(const QString &)>(9, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'reservePlaceSucces'
        QtMocHelpers::SignalData<void(const QString &)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'reservePlaceError'
        QtMocHelpers::SignalData<void(const QString &)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 2 },
        }}),
        // Signal 'uploadFinished'
        QtMocHelpers::SignalData<void(const QString &)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
        // Signal 'uploadFailed'
        QtMocHelpers::SignalData<void(const QString &)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Signal 'movieAddSuccess'
        QtMocHelpers::SignalData<void(const QString &)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Signal 'movieAddError'
        QtMocHelpers::SignalData<void(const QString &)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Signal 'sessionAddSuccess'
        QtMocHelpers::SignalData<void(const QString &)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Signal 'sessionAddError'
        QtMocHelpers::SignalData<void(const QString &)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Signal 'movieDeleteSuccess'
        QtMocHelpers::SignalData<void(const QString &)>(21, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Signal 'movieDeleteError'
        QtMocHelpers::SignalData<void(const QString &)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Signal 'adminRegistrationSuccess'
        QtMocHelpers::SignalData<void(const QString &)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 17 },
        }}),
        // Signal 'adminRegistrationError'
        QtMocHelpers::SignalData<void(const QString &)>(24, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Slot 'onReplyFinished'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(25, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 26, 2 },
        }}),
        // Slot 'onUploadProgress'
        QtMocHelpers::SlotData<void(qint64, qint64)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 28 }, { QMetaType::LongLong, 29 },
        }}),
        // Slot 'onUploadFinished'
        QtMocHelpers::SlotData<void()>(30, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onNetworkError'
        QtMocHelpers::SlotData<void(QNetworkReply::NetworkError)>(31, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 32, 15 },
        }}),
        // Slot 'onReadyRead'
        QtMocHelpers::SlotData<void()>(33, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<ApiManager, qt_meta_tag_ZN10ApiManagerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject ApiManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ApiManagerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ApiManagerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10ApiManagerE_t>.metaTypes,
    nullptr
} };

void ApiManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<ApiManager *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->registrationSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->registrationError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->adminLoginSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->adminLoginError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->loginSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->loginError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->hallSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 7: _t->hallError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->reservePlaceSucces((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 9: _t->reservePlaceError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->uploadFinished((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 11: _t->uploadFailed((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 12: _t->movieAddSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 13: _t->movieAddError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->sessionAddSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 15: _t->sessionAddError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 16: _t->movieDeleteSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 17: _t->movieDeleteError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 18: _t->adminRegistrationSuccess((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 19: _t->adminRegistrationError((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->onReplyFinished((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 21: _t->onUploadProgress((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qint64>>(_a[2]))); break;
        case 22: _t->onUploadFinished(); break;
        case 23: _t->onNetworkError((*reinterpret_cast< std::add_pointer_t<QNetworkReply::NetworkError>>(_a[1]))); break;
        case 24: _t->onReadyRead(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 20:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::registrationSuccess, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::registrationError, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::adminLoginSuccess, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::adminLoginError, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::loginSuccess, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::loginError, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::hallSuccess, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::hallError, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::reservePlaceSucces, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::reservePlaceError, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::uploadFinished, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::uploadFailed, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::movieAddSuccess, 12))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::movieAddError, 13))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::sessionAddSuccess, 14))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::sessionAddError, 15))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::movieDeleteSuccess, 16))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::movieDeleteError, 17))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::adminRegistrationSuccess, 18))
            return;
        if (QtMocHelpers::indexOfMethod<void (ApiManager::*)(const QString & )>(_a, &ApiManager::adminRegistrationError, 19))
            return;
    }
}

const QMetaObject *ApiManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApiManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10ApiManagerE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ApiManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 25)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 25;
    }
    return _id;
}

// SIGNAL 0
void ApiManager::registrationSuccess(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void ApiManager::registrationError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void ApiManager::adminLoginSuccess(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void ApiManager::adminLoginError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 3, nullptr, _t1);
}

// SIGNAL 4
void ApiManager::loginSuccess(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void ApiManager::loginError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 5, nullptr, _t1);
}

// SIGNAL 6
void ApiManager::hallSuccess(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 6, nullptr, _t1);
}

// SIGNAL 7
void ApiManager::hallError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 7, nullptr, _t1);
}

// SIGNAL 8
void ApiManager::reservePlaceSucces(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 8, nullptr, _t1);
}

// SIGNAL 9
void ApiManager::reservePlaceError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 9, nullptr, _t1);
}

// SIGNAL 10
void ApiManager::uploadFinished(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 10, nullptr, _t1);
}

// SIGNAL 11
void ApiManager::uploadFailed(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 11, nullptr, _t1);
}

// SIGNAL 12
void ApiManager::movieAddSuccess(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1);
}

// SIGNAL 13
void ApiManager::movieAddError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 13, nullptr, _t1);
}

// SIGNAL 14
void ApiManager::sessionAddSuccess(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 14, nullptr, _t1);
}

// SIGNAL 15
void ApiManager::sessionAddError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 15, nullptr, _t1);
}

// SIGNAL 16
void ApiManager::movieDeleteSuccess(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 16, nullptr, _t1);
}

// SIGNAL 17
void ApiManager::movieDeleteError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 17, nullptr, _t1);
}

// SIGNAL 18
void ApiManager::adminRegistrationSuccess(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 18, nullptr, _t1);
}

// SIGNAL 19
void ApiManager::adminRegistrationError(const QString & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 19, nullptr, _t1);
}
QT_WARNING_POP
