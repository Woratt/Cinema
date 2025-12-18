#include "user.h"

User::User(const QString& login, const QString& email, QObject *parent) : m_login(login),
                                                                    m_email(email),
                                                                    QObject(parent){}
