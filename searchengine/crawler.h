#ifndef CRAWLER_H
#define CRAWLER_H

class Graph;
class CrawlerPrivate;
class Crawler
{
public:
    Crawler();
    virtual ~Crawler();

    void setGraphContainer(Graph *);

private:
    CrawlerPrivate *d;    
};

#endif // !CRAWLER_H
