#ifndef CRAWLER_H
#define CRAWLER_H

class Graph;
class Index;
class QUrl;
class CrawlerPrivate;
class QString;
class Crawler
{
public:
    Crawler();
    virtual ~Crawler();

    void setGraphContainer(Graph *);
    void setIndexContainer(Index *);
    bool crawlWeb(const QUrl &url);
    const QString & lastError();

private:
    CrawlerPrivate *d;    
};

#endif // !CRAWLER_H
