#include "searchui.h"
#include "client.h"

SearchUi::SearchUi()
{
    Client::getInstance()->setSearchUI(this);
}

void SearchUi::findNetizen(QString id)
{
    Client::getInstance()->findNetizen(id.toLong());
}

void SearchUi::addFriend(QString id)
{
    Client::getInstance()->addFriend(id.toLong());
}
