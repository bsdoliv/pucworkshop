# qt config
QTDIR?=/usr
QMAKE=${QTDIR}/bin/qmake
GMAKE=/usr/bin/make

TARGET=searchengine
VERSION=0.1

QMAKEFILE=${TARGET}.makefile
QMAKEPRO=${TARGET}.pro

# dev build opts
QMAKEPRO_OPTS+= "TARGET=${TARGET}"
QMAKEPRO_OPTS+= "OBJECTS_DIR=${.CURDIR}/.objs"
QMAKEPRO_OPTS+= "MOC_DIR=${.CURDIR}/.mocs"
QMAKEPRO_OPTS+= "CONFIG += debug"
QMAKEPRO_OPTS+= "INCLUDEPATH += ${INCLUDEPATH}"
QMAKEPRO_OPTS+= "QT += network"
QMAKEPRO_OPTS+= "QT -= sql"
#QMAKEPRO_OPTS+= "QT -= gui"
QMAKEPRO_OPTS+= "QT += gui"
QMAKEPRO_OPTS+= "QT += webkit"
QMAKEPRO_OPTS+= "QT += core"
QMAKEPRO_OPTS+= -t app
QMAKEPRO_OPTS+= -nopwd
QMAKEPRO_OPTS+= -norecursive

SRCS=*.cpp
HDRS=*.h

.MAIN: build
build: .PHONY ${TARGET}

${TARGET}: ${QMAKEFILE}
	${GMAKE} -f ${.ALLSRC}

${QMAKEFILE}: ${QMAKEPRO}
	${QMAKE} -makefile ${QMAKEFILE_OPTS} -o ${.TARGET} ${.ALLSRC}

${QMAKEPRO}: Makefile
	${QMAKE} -project ${QMAKEPRO_OPTS} ${SRCS} ${HDRS} -o ${.TARGET} 

distclean: .PHONY
.	for _d in ${.CURDIR}/.objs ${.CURDIR}/.mocs
.		if exists(${_d})
			rmdir ${_d}
.		endif
.	endfor

tests: .PHONY
	cd tests && ${MAKE} build
	cd tests && ${MAKE} run

TARGETS= build
SUBDIR= tests

CLEANFILES+= ui_*.h ${TARGET} ${QMAKEFILE} ${QMAKEPRO} 
CLEANFILES+= ${.CURDIR}/.objs/* ${.CURDIR}/.mocs/*

.include <bsd.subdir.mk>
.include <bsd.prog.mk>

# vim: set tw=78:
