#include <QtTest/QtTest>
#include <QObject>

#include "../crawler.h"
#include "../graph.h"
#include "../index.h"

Q_DECLARE_METATYPE(Graph)

class TestCrawler : public QObject
{
    Q_OBJECT
public:
    TestCrawler() { };
    virtual ~TestCrawler() { };
private slots:
    void crawlWeb_data();
    void crawlWeb();
};

void
TestCrawler::crawlWeb_data()
{
    QTest::addColumn<QUrl>("url");
    QTest::addColumn<QString>("error_message");
    QTest::addColumn<Graph>("graph_result");

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

    QTest::newRow("SUCCESS_CASE") 
        << QUrl("http://www.udacity.com/cs101x/index.html") 
        << "no error"
        << gph;
}

void
TestCrawler::crawlWeb()
{
    Crawler crawl;

    Graph graph;
    crawl.setGraphContainer(&graph);
    Index index;
    crawl.setIndexContainer(&index);

    QFETCH(QUrl, url);
    QVERIFY(crawl.crawlWeb(url));

    QFETCH(QString, error_message);
    QCOMPARE(crawl.lastError(), error_message);

    QCOMPARE(index.size(), 54);

    QFETCH(Graph, graph_result);
    QCOMPARE(graph.size(), graph_result.size());
    QCOMPARE(graph, graph_result);
}

QTEST_MAIN(TestCrawler)

#include "test_crawler.moc"
