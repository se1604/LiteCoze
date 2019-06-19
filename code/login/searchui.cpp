#include "searchui.h"
#include "client.h"
#include "privatechat.h"

SearchUi::SearchUi()
{
    PrivateChat::getInstance()->setSearchUI(this);
}

void SearchUi::findNetizen(QString id)
{
    PrivateChat::getInstance()->findNetizen(id.toLong());
}

void SearchUi::addFriend(QString id)
{
    PrivateChat::getInstance()->addFriend(id.toLong());
}
