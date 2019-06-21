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
   Q_INVOKABLE void acceptAddGroupRequest(QString id, QString name);
   Q_INVOKABLE void flushAccountInfo();

   QString id() const;
   void setId(const QString &id);
signals:
   void idChanged();
   void showClientUI();
   void showAccountInfo(QString nickName, QString id, QString roomid);
   void showGrouplistInfo(QString name, QString roomid);     //显示群列表
   void clearAccountInfo();
   void showFriendMsg(QString id, QString msg, QString roomid);
   void showGroupMsg(QString id, QString msg, QString roomid);   //显示群聊信息
   void showNewFriendInfo(QString nickName, QString id);
   void showNewGroupInfo(QString name, QString id);       //显示添加群请求
private:
   static ClientUI * _instance;
   QString m_id;
};

#endif // CLIENTUI_H
