#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H
#include <QString>
class SearchUi;
class Netizen;

class PrivateChat
{
public:
    static PrivateChat* getInstance();
    void selectFriend(long friendID);
    void findNetizen(long id);//查找
    void addFriend(long id);//请求添加好友
    void acceptAddFriendRequest(Netizen *f);//接受请求

    void showFindInfo(QString nickName, long id);
    void startSearchUI();

    SearchUi *getSearchUI() const;            /////////////////
    void setSearchUI(SearchUi *searchUI);

private:
    PrivateChat();

    static PrivateChat* _instance;

    SearchUi * _searchUI;
};

#endif // PRIVATECHAT_H
