#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QUrl>

class LinksList : public QList<QUrl> 
{ 
public:
    LinksList &operator<<(const QString &s)
    {
        this->append(QUrl(s));
        return *this;
    }
};

class Graph : public QMap<QUrl, LinksList> { };

//typedef QMap<QString, QStringList> Graph;

#endif // !GRAPH_H
