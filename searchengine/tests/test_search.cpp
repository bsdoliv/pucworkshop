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

#if 0
    QTest::addColumn<Ranks>("ranks_template");

    Graph gph;
    QUrl key;
    LinksList value;

    key = QUrl("http://www.udacity.com/cs101x/crawling.html");
    value << "http://www.udacity.com/cs101x/kicking.html";
    gph.insert(key, value);
    value.clear();

    key = QUrl("http://www.udacity.com/cs101x/index.html");
    value   << "http://www.udacity.com/cs101x/crawling.html"
            << "http://www.udacity.com/cs101x/walking.html"
            << "http://www.udacity.com/cs101x/flying.html";
    gph.insert(key, value);
    value.clear();
    
    key = QUrl("http://www.udacity.com/cs101x/walking.html");
    value << "http://www.udacity.com/cs101x/index.html";
    gph.insert(key, value);
    value.clear();

    QTest::newRow("SUCCESS_CASE") 
        << ranks;
#endif
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
    crawl.crawlWeb(url);

    Ranks ranks;
    graph.computeRanks(&ranks);
    QFETCH(LinksList, result_set_Kick);
    QCOMPARE(result_set_Kick, Search::searchOrdered(index, ranks, "Kick"));
    QFETCH(LinksList, result_set_learn);
    QCOMPARE(result_set_learn, Search::searchOrdered(index, ranks, "learn"));
    QFETCH(LinksList, result_set_good);
    QCOMPARE(result_set_good, Search::searchOrdered(index, ranks, "good"));
 
#if 0
    qWarning() << "searching hummus" << Search::searchOrdered(index, ranks,
                                                              "hummus");
    qWarning() << "searching learn" << Search::searchOrdered(index, ranks,
                                                             "learn");
    qWarning() << "searching Kick" << Search::searchOrdered(index, ranks,
                                                             "Kick");
    qWarning() << "searching kicking" << Search::searchOrdered(index, ranks,
                                                             "kicking");
    qWarning() << "searching html" << Search::searchOrdered(index, ranks,
                                                             "html");
    qWarning() << "ranks" << ranks;
    qWarning() << "index" << index.size();
    qWarning() << "graph" << graph.size();
#endif

#if 0
    Graph::const_iterator page;
    for (page = graph.begin(); page != graph.end(); ++page) {
        foreach (const QUrl &node, *page)
            qWarning() << "page" << page.key() << "node" << node.toString();
    }

    QFETCH(Ranks, ranks_template);
    Ranks::iterator it;
    for (it = ranks.begin(); it != ranks.end(); ++it)
        qWarning() << "key" << it.key() << "value" << it.value();
#endif
}

QTEST_MAIN(TestSearch)

#include "test_search.moc"
