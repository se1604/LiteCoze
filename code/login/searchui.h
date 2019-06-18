#ifndef SEARCHUI_H
#define SEARCHUI_H
#include <string>
#include <QObject>

class SearchUi : public QObject
{
    Q_OBJECT
public:
    SearchUi();
    Q_INVOKABLE void findNetizen(QString id);
    Q_INVOKABLE void addFriend(QString id);
signals:
    void showSearchUI();
    void showFindInfo(QString nickName, QString id);
private slots:

};

#endif // SEARCHUI_H
