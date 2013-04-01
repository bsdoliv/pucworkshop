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
    // TODO dump
#if 0
        foreach (const QUrl &u, cache.keys()) {
            QByteArray *ba = cache.object(u);
            qWarning() << u.toString() << qPrintable(ba->data());
        }
#endif
};

#endif //! CRAWLERCACHE_H
