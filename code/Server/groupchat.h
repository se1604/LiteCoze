#ifndef GROUPCHAT_H
#define GROUPCHAT_H


class GroupChat
{
public:
    GroupChat();
    void initFriend();//初始化所有网民之间的好友关系
    long allocateGroupChatRoomID();
};

#endif // GROUPCHAT_H
