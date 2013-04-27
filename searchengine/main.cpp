#include <QApplication>
#include <QDebug>
#include <QUrl>
#include <QTimer>

#include "crawler.h"
#include "crawlercache.h"
#include "graph.h"
#include "index.h"
#include "search.h"
#include "webbrowser.h"

class searchengine : public QObject
{
    Q_OBJECT
public:
    searchengine() : 
        cache(500) { }
    virtual ~searchengine() { };

signals:
    void finished();
    void done(const QByteArray &);

private:
    Crawler crawl;
    CrawlerCache cache;
    Graph graph;
    Index index;
    Ranks ranks;

public slots:
    void searchFor(const QString &w) {
        QByteArray result;
        qWarning() << "searching" << w;
        LinksList ll = Search::searchOrdered(index, ranks, w); 
        qWarning() << "searching" << w << ll;

        result.append(QString("<html><body><h2>Resultados para: %1</h2><ul>")
                      .arg(w));

        foreach (QUrl u, ll)
            result.append(QString("<li><a href='%1'>%1</a>")
                           .arg(u.toString()));

        result.append("</ul></body></html>");
        emit done(result);
    }

    void indexRank() {
        QUrl url;
        url.setUrl(qApp->argv()[1]);
        crawl.setCrawlerCache(&cache);
        crawl.setGraphContainer(&graph);
        crawl.setIndexContainer(&index);

        qWarning() << "indexing" << url.toString();
        if (! crawl.crawlWeb(url))
            qFatal("%s", qPrintable(crawl.lastError()));

        qWarning() << "ranking";
        graph.computeRanks(&ranks);
        qWarning() << "ready";
        emit finished();

#if 0
        foreach (QString w, QStringList() 
                 << "crawl"
                 << "Hummus"
                 << "the"
                 << "good"
                 << "babaganoush")
            qWarning() << "searching" << w << Search::searchOrdered(index, ranks, w); 

        Graph::dump(graph);

        cache.clear();
        QTimer::singleShot(1000, qApp, SLOT(quit()));
        qWarning() << "ranks" << ranks;
        qWarning() << graph;
        qWarning() << index;
#endif
    }
};

int
main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qApp->setApplicationName(qApp->argv()[0]);
    qWarning() << "application name" << qApp->applicationName();

    WebBrowser browser;
    searchengine s;
    browser.show();
    browser.connect(&s, SIGNAL(finished()), &browser, SLOT(readyToSearch()));
    browser.connect(&s, SIGNAL(done(const QByteArray &)),
                    &browser, SLOT(showPage(const QByteArray &)));
    browser.connect(&browser, SIGNAL(searchFor(const QString &)),
                    &s, SLOT(searchFor(const QString &)));
    s.indexRank();

    return app.exec();
}

#include "main.moc"
