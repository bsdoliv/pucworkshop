#ifndef GRAPH_H
#define GRAPH_H

#include <QString>
#include <QStringList>
#include <QMap>

class LinksList : public QList<QUrl> { };
class Graph : public QMap<QUrl, LinksList> { };

//typedef QMap<QString, QStringList> Graph;

#endif // !GRAPH_H
