#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QStringList>
#include <QMap>
#include <QUrl>
#include <QDebug>

class Ranks : public QMap<QUrl, qreal> { };

class LinksList : public QList<QUrl> 
{ 
public:
    LinksList &operator<<(const QString &s)
    {
        Q_UNUSED(s)
        // implementar
        return *this;
    }

    LinksList &operator<<(const QUrl &u)
    {
        Q_UNUSED(u)
        // implementar
        return *this;
    }
};

class Graph
{ 
public:
    void computeRanks(Ranks *ranks);
    static void dump(const Graph &g)
    {
        Q_UNUSED(g)
        // implementar
    }
};

#endif // !GRAPH_H
