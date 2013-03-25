#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QUrl>

class Ranks : public QMap<QUrl, qreal> { };

class LinksList : public QList<QUrl> 
{ 
public:
    LinksList &operator<<(const QString &s)
    {
        this->append(QUrl(s));
        return *this;
    }

    LinksList &operator<<(const QUrl &u)
    {
        this->append(u);
        return *this;
    }
};

class Graph : public QMap<QUrl, LinksList> 
{ 
public:
    void computeRanks(Ranks *ranks);
};

#endif // !GRAPH_H
