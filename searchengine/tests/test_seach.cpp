#include <QtTest/QtTest>
#include <QObject>

#include "../index.h"
#include "../graph.h"

Q_DECLARE_METATYPE(Ranks)
Q_DECLARE_METATYPE(Index)

class TestSearch : public QObject
{
    Q_OBJECT
public:
    TestSearch() { };
    virtual ~TestSearch() { };
private slots:
    void computeSearch_data();
    void computeSearch();
};

void
TestSearch::computeSearch_data()
{
    QTest::addColumn<Index>("index");
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
    graph.computeRanks(&ranks);

//    Index idx;
//    idx


    QTest::newRow("SUCCESS_CASE") 
        << idx
        << ranks;
}

void
TestSearch::searchOrdered()
{
    QFETCH(Graph, graph);

    Graph::const_iterator page;
    for (page = graph.begin(); page != graph.end(); ++page) {
        foreach (const QUrl &node, *page)
            qWarning() << "page" << page.key() << "node" << node.toString();
    }

    Ranks::iterator it;
    for (it = ranks.begin(); it != ranks.end(); ++it)
        qWarning() << "key" << it.key() << "value" << it.value();
}

QTEST_MAIN(TestSearch)

#include "test_search.moc"
