#include <QtTest/QtTest>
#include <QObject>

#include "../graph.h"

Q_DECLARE_METATYPE(Graph)
Q_DECLARE_METATYPE(Ranks)

class TestComputeRanks : public QObject
{
    Q_OBJECT
public:
    TestComputeRanks() { };
    virtual ~TestComputeRanks() { };
private slots:
    void computeRanks_data();
    void computeRanks();
    double round(double);
};

double
TestComputeRanks::round(double value)
{
    return (static_cast<double>(static_cast<int>(value * 10000 + 0.000005)) / 10000);
}

void
TestComputeRanks::computeRanks_data()
{
    QTest::addColumn<Graph>("template_graph");
    QTest::addColumn<Ranks>("template_ranks");

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

    Ranks template_ranks;
    template_ranks[QUrl("http://www.udacity.com/cs101x/crawling.html")] 
        = qreal(0.0666667);
    template_ranks[QUrl("http://www.udacity.com/cs101x/index.html")] 
        = qreal(0.152622);
    template_ranks[QUrl("http://www.udacity.com/cs101x/walking.html")] 
        = qreal(0.107444);

    QTest::newRow("SUCCESS_CASE_ROW")
        << gph
        << template_ranks;
}

void
TestComputeRanks::computeRanks()
{
    QFETCH(Graph, template_graph);
    QFETCH(Ranks, template_ranks);

    Ranks ranks;
    template_graph.computeRanks(&ranks);

    QCOMPARE(ranks.size(), template_ranks.size());

    Ranks::iterator it;
    Ranks::iterator template_it;
    for (it = ranks.begin(), template_it = template_ranks.begin(); 
         it != ranks.end(); 
         ++it, ++template_it) {
        double value(it.value());
        double template_value(template_it.value());
        // rounding before comparing
        if (qFuzzyCompare(qMin(value, 1.0), value)) {
            value = round(value);
            template_value = round(template_value);
        }
        QCOMPARE(it.key(), template_it.key());
        QVERIFY(qFuzzyCompare(value, template_value));
    }
}

QTEST_MAIN(TestComputeRanks)

#include "test_computeranks.moc"
