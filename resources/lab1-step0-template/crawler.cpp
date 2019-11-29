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
    CrawlerCache *cache;
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
    Q_UNUSED(url)
    Q_UNUSED(content)
    return 0;
}

void 
CrawlerPrivate::getAllLinks(const QByteArray &content, LinksList *llist)
{
    Q_UNUSED(llist)
    Q_UNUSED(content)

}

void 
CrawlerPrivate::addLinksToGraph(const QUrl &u, const LinksList &llist)
{
    Q_UNUSED(u)
    Q_UNUSED(llist)
}

void 
CrawlerPrivate::addPageToIndex(const QUrl &u, const QByteArray &content)
{
    Q_UNUSED(u)
    Q_UNUSED(content)
}

bool
CrawlerPrivate::getPage(const QUrl &url, QByteArray *response)
{
    Q_UNUSED(url)
    Q_UNUSED(response)
    return false;
}

Crawler::Crawler() :
    d(new CrawlerPrivate)
{
    d->cache = 0;
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

void
Crawler::setCrawlerCache(CrawlerCache *cache)
{
    d->cache = cache;
}

bool
Crawler::crawlWeb(const QUrl &seed)
{
#if 0
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
#endif
    Q_UNUSED(seed)
    return true;
}

const QString &
Crawler::lastError()
{
    return d->last_error;
}

const CrawlerCache *
Crawler::cache()
{
    return d->cache;
}


