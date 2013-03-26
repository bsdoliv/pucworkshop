#include <QtTest/QtTest>
#include <QObject>

#include "../crawler.h"
#include "../graph.h"
#include "../index.h"
#include "../crawlercache.h"
#include "cachefiller.h"

Q_DECLARE_METATYPE(Graph);

struct Foo {
    Graph gph;
    CrawlerCache cache;
    Foo() : cache(500) {  };
};

class TestCrawler : public QObject
{
    Q_OBJECT
public:
    TestCrawler() :
        d()
        { };
    virtual ~TestCrawler() { };
public slots:
    void initTestCase();
    void cleanupTestCase();
private slots:
    void crawlWeb_data();
    void crawlWeb();
private:
    struct Foo d;
};

void
TestCrawler::cleanupTestCase()
{
    d.cache.clear();
}

void
TestCrawler::initTestCase()
{
    // init graph
    QUrl key;
    LinksList value;

    key = QUrl("http://www.udacity.com/cs101x/crawling.html");
    value << "http://www.udacity.com/cs101x/kicking.html";
    d.gph.insert(key, value);
    value.clear();

    key = QUrl("http://www.udacity.com/cs101x/index.html");
    value   << "http://www.udacity.com/cs101x/crawling.html"
            << "http://www.udacity.com/cs101x/walking.html"
            << "http://www.udacity.com/cs101x/flying.html";
    d.gph.insert(key, value);
    value.clear();
    
    key = QUrl("http://www.udacity.com/cs101x/walking.html");
    value << "http://www.udacity.com/cs101x/index.html";
    d.gph.insert(key, value);

    cacheFiller(&d.cache);

#if 0
    foreach (const QUrl &u, d.cache.keys()) {
        QByteArray *ba = d.cache.object(u);
        qWarning() << "key" << u.toString() << "value" << qPrintable(ba->data());
    }
#endif
}

void
TestCrawler::crawlWeb_data()
{
    QTest::addColumn<QUrl>("url");
    QTest::addColumn<QString>("error_message");
    QTest::addColumn<Graph>("graph_result");

    QTest::newRow("SUCCESS_CASE") 
        << QUrl("http://www.udacity.com/cs101x/index.html") 
        << "no error"
        << d.gph;
}

void
TestCrawler::crawlWeb()
{
    Crawler crawl;
    crawl.setCrawlerCache(&d.cache);

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
