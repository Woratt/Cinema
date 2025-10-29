#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    User(const QString&, const QString&, QObject *parent = nullptr);
private:
    QString m_email;
    QString m_login;
};

#endif // USER_H
