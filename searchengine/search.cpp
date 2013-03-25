#include "search.h"
#include "graph.h"
#include "index.h"

LinksList
Search::searchOrdered(const Index &index,
                      const Ranks &ranks,
                      const QString &word)
{
//    if (

    LinksList ranked_list;
    Search search;
    LinksList list = search.lookup(index, word.toAscii());

    if (list.isEmpty())
        return LinksList();

    while (list.size() > 0) {
        QUrl top_page = list[0];
        foreach (const QUrl &u, list) {
            if (ranks[u] > ranks[top_page])
                top_page = u;
        }
        ranked_list.append(top_page);
        list.removeOne(top_page);
    }

    return ranked_list;
}

LinksList
Search::lookup(const Index &idx, const QByteArray &word)
{
    if (idx.contains(word))
        return idx[word];

    return LinksList();
}
