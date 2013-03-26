#ifndef CRAWLERCACHE_H
#define CRAWLERCACHE_H

#include <QCache>
#include <QByteArray>
#include <QUrl>

class CrawlerCache : public QCache<QUrl, QByteArray> 
{ 
public:
    CrawlerCache(int i) : QCache<QUrl, QByteArray>(i) { }
    void clear() {
        foreach (const QUrl &u, keys()) {
            QByteArray *ba = take(u);
            delete ba;
            ba = 0;
        }

        QCache::clear();
    }
};

#endif //! CRAWLERCACHE_H
