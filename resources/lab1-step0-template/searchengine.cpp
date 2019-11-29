#include <QUrl>
#include <QCoreApplication>

#include "graph.h"
#include "index.h"
#include "crawler.h"
#include "searchengine.h"

int 
SearchEngine::run()
{
    QUrl url;
    url.setUrl(qApp->argv()[1]);
    Graph graph;
    Index index;
#if 0
    Crawler crawl;
    crawl.setGraphContainer(&graph);
    crawl.setIndexContainer(&index);

    if (! crawl.crawlWeb(url))
        qFatal("%s", qPrintable(crawl.lastError()));
#endif

    Graph::dump(graph);
    //qWarning() << graph;
    //qWarning() << index;
}
