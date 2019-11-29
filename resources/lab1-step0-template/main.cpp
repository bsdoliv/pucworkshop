#include <QCoreApplication>
#include <QDebug>

#include "crawler.h"
#include "graph.h"
#include "index.h"
#include "searchengine.h"

int
main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

    qApp->setApplicationName(qApp->argv()[0]);
    qWarning() << "application name" << qApp->applicationName();

    SearchEngine s;
    s.run();

    return 0;
}
