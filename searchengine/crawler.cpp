#include "crawler.h"
#include "graph.h"
#include "index.h"

struct CrawlerPrivate
{
    Graph *graph;
    Index *index;
    QString last_error;
    QUrl;
};

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

void
Crawler::crawlWeb(const QUrl &url)
{
    d->url = url;
}


