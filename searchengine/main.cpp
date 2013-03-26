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
    url.setUrl(qApp->argv()[1]);
    Crawler crawl;

    Graph graph;
    crawl.setGraphContainer(&graph);

    Index index;
    crawl.setIndexContainer(&index);

    if (! crawl.crawlWeb(url))
        qFatal("%s", qPrintable(crawl.lastError()));

    Ranks ranks;
    graph.computeRanks(&ranks);

    foreach (QString w, QStringList() 
             << "crawl"
             << "Hummus"
             << "the"
             << "good"
             << "babaganoush")
        qWarning() << "searching" << w << Search::searchOrdered(index, ranks, w); 

    qWarning() << ranks;
    qWarning() << graph;
    qWarning() << index;
#if 0
#endif

    return 0;
}
