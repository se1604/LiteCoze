#include "searchui.h"
#include "client.h"

SearchUi::SearchUi()
{
    Client::getInstance()->setSearchUI(this);
}

void SearchUi::startSearch()
{

}
