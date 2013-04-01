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
    static void dump(const Graph &g)
    {
        for (Graph::const_iterator it = g.begin();
             it != g.end();
             ++it)
            foreach (const QUrl &u, it.value())
                qWarning() << Q_FUNC_INFO << "key" << it.key() << "value" << u.toString();
    }
};

#endif // !GRAPH_H
