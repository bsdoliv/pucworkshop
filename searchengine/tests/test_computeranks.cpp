#include <QtTest/QtTest>
#include <QObject>

#include "../graph.h"

Q_DECLARE_METATYPE(Graph)

class TestComputeRanks : public QObject
{
    Q_OBJECT
public:
    TestComputeRanks() { };
    virtual ~TestComputeRanks() { };
private slots:
    void computeRanks_data();
    void computeRanks();
};

void
TestComputeRanks::computeRanks_data()
{
    QTest::addColumn<Graph>("graph");

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

    QTest::newRow("SUCCESS_CASE") << gph;
}

void
TestComputeRanks::computeRanks()
{
    QFETCH(Graph, graph);

    Graph::const_iterator page;
    for (page = graph.begin(); page != graph.end(); ++page) {
        foreach (const QUrl &node, *page)
            qWarning() << "page" << page.key() << "node" << node.toString();
    }
    Ranks ranks;
    graph.computeRanks(&ranks);

    Ranks::iterator it;
    for (it = ranks.begin(); it != ranks.end(); ++it)
        qWarning() << "key" << it.key() << "value" << it.value();
}

QTEST_MAIN(TestComputeRanks)

#include "test_computeranks.moc"
