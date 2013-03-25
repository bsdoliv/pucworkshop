#include <QtTest/QtTest>
#include <QObject>

#include "../crawler.h"
#include "../index.h"
#include "../graph.h"
#include "../search.h"

Q_DECLARE_METATYPE(Ranks)
Q_DECLARE_METATYPE(Index)

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
#if 0
    QTest::addColumn<Ranks>("ranks");

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

    Ranks ranks;
    gph.computeRanks(&ranks);

    Index idx;

    QTest::newRow("SUCCESS_CASE") 
        << idx
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

#if 0
    qWarning() << "searching" << Search::searchOrdered(index, ranks, "hummus");
    qWarning() << "ranks" << ranks;
    qWarning() << "index" << index.size();
    qWarning() << "graph" << graph.size();

    Graph::const_iterator page;
    for (page = graph.begin(); page != graph.end(); ++page) {
        foreach (const QUrl &node, *page)
            qWarning() << "page" << page.key() << "node" << node.toString();
    }

    QFETCH(Ranks, ranks);
    Ranks::iterator it;
    for (it = ranks.begin(); it != ranks.end(); ++it)
        qWarning() << "key" << it.key() << "value" << it.value();
#endif
}

QTEST_MAIN(TestSearch)

#include "test_search.moc"
