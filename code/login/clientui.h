#ifndef CLIENTUI_H
#define CLIENTUI_H
#include <string>
#include <QObject>

class Client;
class ClientUI : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
public:
   ClientUI();
   static ClientUI* getInstance();


   void showAllOffLineMessages();
   Q_INVOKABLE void selectFriend(QString friendID);
   Q_INVOKABLE void sendNewMessage(QString content);
   Q_INVOKABLE void startSearchUI();
   Q_INVOKABLE void acceptAddFriendRequest(QString id, QString nickname);

   QString id() const;
   void setId(const QString &id);
signals:
   void idChanged();
   void showClientUI();
   void showAccountInfo(QString nickName, QString id);
   void showFriendMsg(QString id, QString msg);
   void showNewFriendInfo(QString nickName, QString id);
private:
   static ClientUI * _instance;
   QString m_id;
};

#endif // CLIENTUI_H
