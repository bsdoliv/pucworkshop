#include "search.h"
#include "graph.h"
#include "index.h"

LinksList
Search::searchOrdered(const Index &i,
                      const Ranks &r,
                      const QString &word)
{
//    if (

    LinksList list;

    return list;
}

LinksList
Search::lookup(const Index &idx, const QByteArray &word)
{
    if (idx.contains(word))
        return idx[word];

    //return 
}
