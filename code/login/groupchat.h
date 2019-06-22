#ifndef GROUPCHAT_H
#define GROUPCHAT_H
#include <QString>
class SearchUi;
class Netizen;
class ClientUI;


class GroupChat
{
public:
    static GroupChat* getInstance();
    SearchUi *getSearchUI() const;
    void setSearchUI(SearchUi *searchUI);

    ClientUI *getClientUI() const;
    void setClientUI(ClientUI *clientUI);
    void showGrouplistInfo(QString name, QString roomid);     //显示群列表
    void showGroupMsg(QString id, QString msg, QString roomid);    //显示群聊信息
    void showFindGroupInfo(QString name, QString id);    //显示查找的群
    void showNewGroupInfo(QString name, QString id, QString groupName, QString roomid);       //显示添加群请求
    void addInGroup(long roomid, long netizenid);

private:
    GroupChat();

    static GroupChat* _instance;

    SearchUi *_searchUI;
    ClientUI *_clientUI;
};

#endif // GROUPCHAT_H
