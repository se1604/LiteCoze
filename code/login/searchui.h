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
    void start();
private slots:
    void startSearch();
};

#endif // SEARCHUI_H
