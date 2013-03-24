#ifndef CRAWLER_H
#define CRAWLER_H

class Graph;
class Index;
class QUrl;
class CrawlerPrivate;
class Crawler
{
public:
    Crawler();
    virtual ~Crawler();

    void setGraphContainer(Graph *);
    void setIndexContainer(Index *);
    void crawlWeb(const QUrl &url);
    const QString & lastError();

private:
    CrawlerPrivate *d;    
};

#endif // !CRAWLER_H
