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
signals:
    void showList(QString id);
private:
};

#endif // LOGIN_H
