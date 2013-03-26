#include <QtTest/QtTest>
#include <QObject>

#include "../crawler.h"
#include "../index.h"
#include "../graph.h"
#include "../search.h"
#include "../crawlercache.h"
#include "cachefiller.h"

Q_DECLARE_METATYPE(LinksList)

struct Foo {
    CrawlerCache cache;
    Foo() : cache(500) {  };
};

class TestSearch : public QObject
{
    Q_OBJECT
public:
    TestSearch() { };
    virtual ~TestSearch() { };
public slots:
    void initTestCase();
    void cleanupTestCase();
private slots:
    void searchOrdered_data();
    void searchOrdered();
private:
    struct Foo d;
};

void
TestSearch::cleanupTestCase()
{
    d.cache.clear();
}

void
TestSearch::initTestCase()
{
    cacheFiller(&d.cache);
#if 0
    foreach (const QUrl &u, d.cache.keys()) {
        QByteArray *ba = d.cache.object(u);
        qWarning() << "key" << u.toString() << "value" << qPrintable(ba->data());
    }
#endif
}

void
TestSearch::searchOrdered_data()
{
    QTest::addColumn<LinksList>("result_set_Kick");
    QTest::addColumn<LinksList>("result_set_learn");
    QTest::addColumn<LinksList>("result_set_good");

    QTest::newRow("SUCCESS_CASE") 
        // result_set_Kick
        << (LinksList() << "http://www.udacity.com/cs101x/kicking.html")
        // result_set_learn
        << (LinksList() << "http://www.udacity.com/cs101x/index.html")
        << (LinksList() 
            << "http://www.udacity.com/cs101x/index.html"
            << "http://www.udacity.com/cs101x/crawling.html");
}

void
TestSearch::searchOrdered()
{
    Crawler crawl;
    crawl.setCrawlerCache(&d.cache);

    Graph graph;
    crawl.setGraphContainer(&graph);

    Index index;
    crawl.setIndexContainer(&index);

    crawl.crawlWeb(QUrl("http://www.udacity.com/cs101x/index.html"));

    Ranks ranks;
    graph.computeRanks(&ranks);

    QFETCH(LinksList, result_set_Kick);
    QCOMPARE(result_set_Kick, Search::searchOrdered(index, ranks, "Kick"));

    QFETCH(LinksList, result_set_learn);
    QCOMPARE(result_set_learn, Search::searchOrdered(index, ranks, "learn"));

    QFETCH(LinksList, result_set_good);
    QCOMPARE(result_set_good, Search::searchOrdered(index, ranks, "good"));

    QCOMPARE(&d.cache, crawl.cache());
}

QTEST_MAIN(TestSearch)

#include "test_search.moc"
