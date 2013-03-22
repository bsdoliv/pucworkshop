#include <QCoreApplication>
#include <QDebug>

#include "crawl.h"
#include "graph.h"
#include "index.h"
#include "search.h"

int
main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    qApp->setApplicationName(qApp->argv()[0]);
    qWarning() << qApp->argc();
    qWarning() << qApp->argv();

    QUrl url;
    Crawler crawl;

    Graph graph;
    crawl.setGraphContainer(&graph);
    Index index;
    crawl.setIndexContainer(&index);
    if (! crawl.crawlWeb(url))
        qFatal() << craw.lastError();

    Ranks ranks;
    graph.computeRanks(&ranks);

    Search search;
    search.setIndex(index);
    search.setRanks(ranks);

    qWarning() << search.searchOrdered("Hummus");
    qWarning() << search.searchOrdered("the");
    qWarning() << search.searchOrdered("babaganoush");

    return 0;
//    return app.exec();
}
