#include <QtTest/QtTest>
#include <QObject>

#include "../graph.h"
#include "../index.h"
#include "cachefiller.h"

Q_DECLARE_METATYPE(Graph);

class TestGraphIndex : public QObject
{
    Q_OBJECT
public:
    virtual ~TestGraphIndex() { };
public slots:
    void initTestCase() { };
    void cleanupTestCase() { };
private slots:
    void graph();
    void index();
};

void
TestGraphIndex::index()
{
    Index   index;

#if 0
    QUrl u1("http://america/sul");
    QUrl u2("http://america/sul/brasil");
    (*index)["brasil"] = u1;
    (*index)["pais"] = u2;
    (*index)["futuro"] = u2;
    QCOMPARE(index.size(), 3);
#endif
}

void
TestGraphIndex::graph()
{
    Graph graph;
#if 0
    QUrl u1("http://america/sul");
    QUrl u2("http://america/sul/brasil");
    QUrl u3("http://america/sul/brasil");

    LinksList l << u1 << u2 << u3;
    graph.insert(u1, l);
    graph.insert(u2, l);
    graph.insert(u3, l);
    QCOMPARE(graph.size(), 3);
#endif

}

QTEST_MAIN(TestGraphIndex)

#include "test_graphindex.moc"
