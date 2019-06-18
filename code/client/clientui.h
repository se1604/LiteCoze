#ifndef CLIENTUI_H
#define CLIENTUI_H
#include <string>

class ClientUI
{
public:
   static ClientUI* getInstance();

   void showAccountInfo();
   void showAllOffLineMessages();
   void selectFriend(long friendID);
   void sendNewMessage(std::string content);

private:
   ClientUI();
   static ClientUI * _instance;
};

#endif // CLIENTUI_H
