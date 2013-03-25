#ifndef SEARCH_H
#define SEARCH_H

class Index;
class Ranks;
class LinksList;
class QString;
class QByteArray;
class QUrl;

class Search
{
public:
    static LinksList searchOrdered(const Index &i, 
                                   const Ranks &r, 
                                   const QString &word);
private:
    LinksList lookup(const Index &idx, const QByteArray &word);
};

#endif //! SEARCH_H
