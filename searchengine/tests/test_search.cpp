#include <QtTest/QtTest>
#include <QObject>

#include "../crawler.h"
#include "../index.h"
#include "../graph.h"
#include "../search.h"

Q_DECLARE_METATYPE(LinksList)

class TestSearch : public QObject
{
    Q_OBJECT
public:
    TestSearch() { };
    virtual ~TestSearch() { };
private slots:
    void searchOrdered_data();
    void searchOrdered();
};

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

    Graph graph;
    crawl.setGraphContainer(&graph);

    Index index;
    crawl.setIndexContainer(&index);

    QUrl url("http://www.udacity.com/cs101x/index.html");

#if 0
    CrawlerCache cache;
    crawl.setCache(&cache);
#endif

    crawl.crawlWeb(url);

    Ranks ranks;
    graph.computeRanks(&ranks);

    QFETCH(LinksList, result_set_Kick);
    QCOMPARE(result_set_Kick, Search::searchOrdered(index, ranks, "Kick"));

    QFETCH(LinksList, result_set_learn);
    QCOMPARE(result_set_learn, Search::searchOrdered(index, ranks, "learn"));

    QFETCH(LinksList, result_set_good);
    QCOMPARE(result_set_good, Search::searchOrdered(index, ranks, "good"));
}

QTEST_MAIN(TestSearch)

#include "test_search.moc"
