#ifndef INDEX_H
#define INDEX_H

#include <QUrl>
#include <QByteArray>
#include <QMap>

// LinksList
#include "graph.h"

class Index : public QMap<QByteArray, LinksList> { };

#endif // !INDEX_H
