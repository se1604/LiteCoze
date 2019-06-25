#include "clientui.h"
#include "client.h"

ClientUI *ClientUI::_instance = nullptr;

ClientUI::ClientUI()
{

}

ClientUI *ClientUI::getInstance()
{
    if(_instance != nullptr)
        return _instance;
    _instance = new ClientUI();
    return _instance;
}

void ClientUI::logIn(long id, std::string password)
{
    Client::getInstance()->logIn(id, password);

}

void ClientUI::selectFriend(long friendID)
{
    Client::getInstance()->selectFriend(friendID);
}

void ClientUI::sendNewMessage(std::string content)
{
    Client::getInstance()->sendNewMessage(content);
}
