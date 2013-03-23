#include <QtTest/QtTest>
#include <QObject>

#include "../crawler.h"

class test_Crawler : public QObject
{
    Q_OBJECT
public:
    test_Crawler() { };
    virtual ~test_Crawler() { };
};

QTEST_MAIN(test_Crawler)

#include "test_crawler.moc"
