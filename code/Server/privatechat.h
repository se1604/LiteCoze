#ifndef PRIVATECHAT_H
#define PRIVATECHAT_H


class PrivateChat
{
public:
    PrivateChat();
    void initFriend();//初始化所有网民之间的好友关系
    long allocatePrivateChatRoomID();//每当添加一段好友关系就会分配私聊房间的id号
};

#endif // PRIVATECHAT_H
