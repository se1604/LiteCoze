#include "loginUI.h"
#include "client.h"
LogInUI::LogInUI()
{

}

void LogInUI::logIn(long id, std::string password)
{
    Client::getInstance()->logIn(id, password);
}
