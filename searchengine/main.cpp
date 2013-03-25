#include <QCoreApplication>
#include <QDebug>
#include <QUrl>

#include "crawler.h"
#include "graph.h"
#include "index.h"
#include "search.h"

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
    Index index;
    crawl.setIndexContainer(&index);
    if (! crawl.crawlWeb(url))
        qFatal("%s", qPrintable(crawl.lastError()));

    Ranks ranks;
    graph.computeRanks(&ranks);

    qWarning() << Search::searchOrdered(index, ranks, "hummus");

#if 0
    qWarning() << search.searchOrdered("Hummus");
    qWarning() << search.searchOrdered("the");
    qWarning() << search.searchOrdered("babaganoush");
#endif

    return 0;
}
