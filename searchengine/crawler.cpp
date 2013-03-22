#include "crawler.h"
#include "graph.h"

struct CrawlerPrivate
{
    Graph *graph;
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
