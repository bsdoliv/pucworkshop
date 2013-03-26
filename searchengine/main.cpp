#include <QCoreApplication>
#include <QDebug>
#include <QUrl>
#include <QTimer>

#include "crawler.h"
#include "crawlercache.h"
#include "graph.h"
#include "index.h"
#include "search.h"

class searchengine : public QObject
{
    Q_OBJECT
signals:
    void finished();
public:
    void run()
    {
        QUrl url;
        url.setUrl(qApp->argv()[1]);
        Crawler crawl;

        CrawlerCache cache(500);
        crawl.setCrawlerCache(&cache);

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

#if 1
        foreach (const QUrl &u, cache.keys()) {
            QByteArray *ba = cache.object(u);
            qWarning() << u.toString() << qPrintable(ba->data());
        }
#endif

        cache.clear();
        QTimer::singleShot(1000, qApp, SLOT(quit()));
        qWarning() << "finished";
#if 0
    qWarning() << ranks;
    qWarning() << graph;
    qWarning() << index;
#endif
    }
};

int
main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    qApp->setApplicationName(qApp->argv()[0]);
    qWarning() << "arguments count" << qApp->argc();
    qWarning() << "arguments vector" << qApp->argv();
    qWarning() << "application name" << qApp->applicationName();

    searchengine s;
    s.run();

    return app.exec();
    //return 0;
}

#include "main.moc"
