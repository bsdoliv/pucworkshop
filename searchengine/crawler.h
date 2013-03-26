#ifndef CRAWLER_H
#define CRAWLER_H

class Graph;
class Index;
class CrawlerCache;

class QUrl;
class QString;

class CrawlerPrivate;
class Crawler
{
public:
    Crawler();
    virtual ~Crawler();

    void setGraphContainer(Graph *);
    void setCrawlerCache(CrawlerCache *);
    void setIndexContainer(Index *);
    bool crawlWeb(const QUrl &url);
    const QString & lastError();

    const CrawlerCache * cache();

private:
    CrawlerPrivate *d;    
};

#endif // !CRAWLER_H
