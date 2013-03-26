#ifndef CACHEFILLER_H
#define CACHEFILLER_H

#include "../crawlercache.h"
static void 
cacheFiller(CrawlerCache *cache)
{
    // init cache
    cache->insert(QUrl("http://www.udacity.com/cs101x/flying.html"), new QByteArray(
        "<html> \
        <body> \
        The magic words are Squeamish Ossifrage! \
        </body> \
        </html>"));
     
    cache->insert(QUrl("http://www.udacity.com/cs101x/walking.html"), new QByteArray(
        "<html> \
        <body>              \
        I can't get enough  \
        <a href=\"http://www.udacity.com/cs101x/index.html\">crawling</a>! \
        </body>                                                            \
        </html>"));
 
    cache->insert(QUrl("http://www.udacity.com/cs101x/index.html"), new QByteArray(
        "<html> \
        <body> \
        This is a test page for learning to crawl! \
        <p> \
        It is a good idea to  \
        <a href=\"http://www.udacity.com/cs101x/crawling.html\">learn to crawl</a> \
        before you try to \
        <a href=\"http://www.udacity.com/cs101x/walking.html\">walk</a> or \
        <a href=\"http://www.udacity.com/cs101x/flying.html\">fly</a>.\
        </p>\
        </body>\
        </html>"));
 
    cache->insert(QUrl("http://www.udacity.com/cs101x/kicking.html"), new QByteArray(
        "<html>\
        <body>\
        <b>Kick! Kick! Kick!</b>\
        </body>\
        </html>"));
 
    cache->insert(QUrl("http://www.udacity.com/cs101x/crawling.html"), new QByteArray(
        "<html>\
        <body>\
        I have not learned to crawl yet, but I am quite good at \
        <a href=\"http://www.udacity.com/cs101x/kicking.html\">kicking</a>.\
        </body>\
        </html>"));
}

#endif //! CACHEFILLER_H
