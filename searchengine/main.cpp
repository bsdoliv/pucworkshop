#include <QCoreApplication>
#include <QDebug>
#include <QUrl>

#include "crawler.h"
#include "graph.h"
#if 0
#include "index.h"
#include "search.h"
#endif

int
main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    qApp->setApplicationName(qApp->argv()[0]);
    qWarning() << "arguments count" << qApp->argc();
    qWarning() << "arguments vector" << qApp->argv();
    qWarning() << "application name" << qApp->applicationName();

    QUrl url;
    Crawler crawl;

    Graph graph;
    crawl.setGraphContainer(&graph);
#if 1
    Index index;
    crawl.setIndexContainer(&index);
    if (! crawl.crawlWeb(url))
        qFatal() << crawl.lastError();

    Ranks ranks;
    graph.computeRanks(&ranks);

    Search search;
    search.setIndex(index);
    search.setRanks(ranks);

    qWarning() << search.searchOrdered("Hummus");
    qWarning() << search.searchOrdered("the");
    qWarning() << search.searchOrdered("babaganoush");
#endif

    return 0;
}
