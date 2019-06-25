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
    Q_INVOKABLE void findGroup(QString id);     //查找群
    Q_INVOKABLE void addFriend(QString id);
    Q_INVOKABLE void addGroup(QString roomid);      //添加群

signals:
    void showSearchUI();
    void showFindInfo(QString nickName, QString id);     //显示查找的网民
    void showFindGroupInfo(QString name, QString id);    //显示查找的群
private slots:

};

#endif // SEARCHUI_H
