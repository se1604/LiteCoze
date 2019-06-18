#ifndef SEARCHUI_H
#define SEARCHUI_H
#include <string>
#include <QObject>

class SearchUi : public QObject
{
    Q_OBJECT
public:
    SearchUi();
signals:
    void showSearchUI();
private slots:

};

#endif // SEARCHUI_H
