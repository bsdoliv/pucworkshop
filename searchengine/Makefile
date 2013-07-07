.include "Makefile.inc"

QTARGET=searchengine
VERSION=0.1

QSRCS= crawler.cpp graph.cpp main.cpp search.cpp webbrowser.cpp
QHDRS= crawler.h crawlercache.h graph.h index.h search.h webbrowser.h

QMAKEOPTS.debug=	yes

QMAKEOPTS.qt+=	webkit
QMAKEOPTS.qt+=	gui
QMAKEOPTS.qt+=	network

tests: .PHONY
	cd tests && ${MAKE} build
	cd tests && ${MAKE} run

.include "bsd.qt.mk"

SUBDIR= tests
.include <bsd.subdir.mk>

# vim: set tw=78:
