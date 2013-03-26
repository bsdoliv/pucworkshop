#include "crawler.h"
#include "graph.h"
#include "index.h"

#include <QDebug>
#include <QCoreApplication>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QQueue>

struct CrawlerPrivate
{
    Graph *graph;
    Index *index;
    QString last_error;
    QUrl current_url;

    bool getPage(const QUrl &u, QByteArray *response);
    void addPageToIndex(const QUrl &u, const QByteArray &content);
    void getAllLinks(const QByteArray &content, LinksList *llist);
    void addLinksToGraph(const QUrl &u, const LinksList &llist);
    
    int getNextUrl(const QByteArray &content, QUrl *url);
};

int
CrawlerPrivate::getNextUrl(const QByteArray &content, QUrl *url)
{
    int start_link;
    if ((start_link = content.indexOf("<a href=")) < 0) {
        url->clear();
        return -1;
    }
    int start_quote = content.indexOf('"', start_link);
    start_quote++;
    int end_quote = content.indexOf('"', start_quote);
#if 0
    qWarning() 
    << "start_link" << start_link
    << "start_quote" << start_quote
    << "end_quote" << end_quote
    << "content.mid" << content.mid(start_quote, end_quote - start_quote);
#endif
    url->setUrl(content.mid(start_quote, end_quote - start_quote));
    return end_quote;
}

void 
CrawlerPrivate::getAllLinks(const QByteArray &content, LinksList *llist)
{
    QByteArray content_copy(content);
    while (true) {
        QUrl url;
        int endpos = getNextUrl(content_copy, &url);
        if (endpos == -1) 
            break;

        llist->append(url);
        // move buffer forward
        content_copy = content_copy.mid(endpos, -1);
    }
}

void 
CrawlerPrivate::addLinksToGraph(const QUrl &u, const LinksList &llist)
{
    if (! u.isEmpty())
        graph->insert(u, llist);
}

void 
CrawlerPrivate::addPageToIndex(const QUrl &u, const QByteArray &content)
{
    foreach (const QString &word,
             QString(content).split(QRegExp("\\W+"), QString::SkipEmptyParts)) {

        QByteArray w(word.toAscii());

        if (index->contains(w)) {
            if (! index->value(w).contains(u))
                (*index)[w] << u;
        } else
            index->insert(w, LinksList() << u);
    }
}

bool
CrawlerPrivate::getPage(const QUrl &url, QByteArray *response)
{
    QNetworkAccessManager *manager = 0;
    QNetworkReply *reply = 0;

    manager = new QNetworkAccessManager(qApp);
    reply = manager->get(QNetworkRequest(url));
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    loop.exec();


#if 0
    qWarning() << "url" << qPrintable(reply->url().toString());
    qWarning() << "operation" << reply->operation();
    qWarning() << "buffer size" << reply->readBufferSize();
    qWarning() << "buffer" << reply->readAll();
    qWarning() << "errorString" << reply->errorString();
#endif
    response->clear();
    response->append(reply->readAll());
    reply->deleteLater();
    manager->deleteLater();

    return response;
}

Crawler::Crawler() :
    d(new CrawlerPrivate)
{
}

Crawler::~Crawler()
{
    delete d;
    d = 0;
}

void
Crawler::setGraphContainer(Graph *g)
{
    d->graph = g;
}

void
Crawler::setIndexContainer(Index *idx)
{
    d->index = idx;
}

bool
Crawler::crawlWeb(const QUrl &seed)
{
    d->last_error = "no error";
    QQueue<QUrl> crawl_todo;
    QList<QUrl> crawl_done;

    crawl_todo.enqueue(seed);
    while (crawl_todo.size() > 0) {
        const QUrl &url = crawl_todo.dequeue();
        if (crawl_done.contains(url))
            continue;

        d->current_url = url;

        // retrieves page, index content
        QByteArray content;
        d->getPage(url, &content);
        d->addPageToIndex(url, content);

        // extract links, append to graph
        LinksList links;
        d->getAllLinks(content, &links);
        if (links.size() > 0)
            d->addLinksToGraph(url, links);
        foreach (QUrl u, links)
            crawl_todo.enqueue(u);

        crawl_done.append(url);
    }


    return true;
}

const QString &
Crawler::lastError()
{
    return d->last_error;
}


