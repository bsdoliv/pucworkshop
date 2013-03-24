#include <QtTest/QtTest>
#include <QObject>

#include "../crawler.h"
#include "../graph.h"
#include "../index.h"

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
    QTest::addColumn<int>("index_size");
    QTest::addColumn<int>("graph_size");

    QTest::newRow("SUCCESS_CASE") 
        << QUrl("http://www.udacity.com/cs101x/index.html") 
        << "no error"
        << 1 
        << 1;
#if 0
    QTest::newRow("FAIL_CASE") 
        << QUrl("http://www.udacity.com/cs101x/404.html") 
        << "fail to retrieve page 404";
#endif
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

    qWarning() << index;
    QFETCH(int, index_size);
    QCOMPARE(index.size(), index_size);

    qWarning() << graph;
    QFETCH(int, graph_size);
    QCOMPARE(graph.size(), graph_size);
}

QTEST_MAIN(TestCrawler)

#include "test_crawler.moc"
