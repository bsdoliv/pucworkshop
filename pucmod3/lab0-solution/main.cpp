#include <QtCore>

#if 1
bool operator<(const QPoint &p1, const QPoint &p2)
{
    return ( p1.x() < p2.x() ||
             (p1.x() == p2.x() && p1.y() < p2.y() ) );
}

uint qHash(const QPoint &p)
{
    return qHash(p.x()) ^ qHash(p.y());
}
#endif

int main()
{
#if 0
    QMap<QPoint, int> map;
    map.insert(QPoint(1, 2), 42);
    int value = map.value(QPoint(1, 2));
    Q_ASSERT(value == 42);

    QHash<QPoint, int> hash;
    hash.insert(QPoint(1, 1), 42);

    QSet<QPoint> set;
    set.insert(QPoint(1, 1));
#endif

    // Check the location
    QStringList strings;
    strings << "abc" << "def" << "hij";

#if 0
    QMutableListIterator<QString> it(strings);
    it.toBack();
    qDebug() << "Just iterated over: " << it.previous();
    it.insert("XXX");
    qDebug() << "Next item after the insert is: " << it.previous();

    it = QMutableListIterator<QString>(strings);
    qDebug() << "Just iterated over: " << it.next();
    it.insert("YYY");
    qDebug() << "Next item after the insert is: " << it.next();

    it = QMutableListIterator<QString>(strings);

    while (it.hasNext())
        qDebug() << it.next();
#endif

    qWarning() << "foreach";
    // implementar foreach
    foreach (QString s, strings)
        qWarning() 
            << "value" << s;

    qWarning() << "stl";
    // implemenetar stl iterator
    QStringList::iterator it = strings.begin();
    for (; it != strings.end(); ++it)
        qWarning() 
            << "value" << *it;
    return 0;
}
