#ifndef LOGIN_H
#define LOGIN_H
#include <string>
#include <QObject>
#include <QString>

class Client;

class LogInUI : public QObject
{
    Q_OBJECT
public:
    LogInUI();
    Q_INVOKABLE void logIn(QString id, QString password);
    Q_INVOKABLE void startClientUI();
    Q_INVOKABLE void myRegister(QString id, QString nickname, QString password);
signals:
    void showList(QString id);
private:
};

#endif // LOGIN_H
