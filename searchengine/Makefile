# qt config
export QTDIR?=/usr
QMAKE=${QTDIR}/bin/qmake

PROG=searchengine
VERSION=0.1

QMAKEFILE=${PROG}.makefile
QMAKEPRO=${PROG}.pro

# dev build opts
QMAKEFILE_OPTS+="TARGET=${PROG}"
QMAKEFILE_OPTS+="OBJECTS_DIR=./.objs"
QMAKEFILE_OPTS+="MOC_DIR=./.mocs"
#QMAKEFILE_OPTS+="CONFIG += debug"
QMAKEFILE_OPTS+="INCLUDEPATH += ${INCLUDEPATH}"
QMAKEFILE_OPTS+="QT += network"
QMAKEFILE_OPTS+="QT -= sql"
QMAKEFILE_OPTS+="QT -= gui"
QMAKEFILE_OPTS+="QT -= xml"
QMAKEFILE_OPTS+="QT += core"

QMAKEPRO_OPTS+= -t app
QMAKEPRO_OPTS+= -nopwd
QMAKEPRO_OPTS+= -norecursive
QMAKEPRO_OPTS+= ${SRCS} ${HDRS}

SRCS=*.cpp
HDRS=*.h

all: build

.PHONY: build
build: ${PROG}

.PHONY: ${PROG}
${PROG}: ${QMAKEFILE}
	${MAKE} -f $<

${QMAKEFILE}: ${QMAKEPRO}
	${QMAKE} -makefile ${QMAKEFILE_OPTS} -o $@ $<

${QMAKEPRO}: Makefile
	${QMAKE} -project ${QMAKEPRO_OPTS} -o $@ $<

.PHONY: tests
tests:
	${MAKE} -C tests build
	${MAKE} -C tests run

.PHONY: testsclean
testsclean:
	${MAKE} -C tests distclean

.PHONY: distclean 
distclean: testsclean clean prunebuild
	-[ -d .objs ] && \
		rmdir .objs
	-[ -d .mocs ] && \
		rmdir .mocs

.PHONY: clean
clean:
	-[ -e ${QMAKEFILE} ] && \
		${MAKE} -f ${QMAKEFILE} clean
	-[ -d ${PROG}.app ] && \
		rm -rfv ${PROG}.app
	-rm -fv ${PROG}
	-rm -fv ui_*.h

.PHONY: prunebuild
prunebuild:
	-rm -fv ${QMAKEFILE}
	-rm -fv ${QMAKEPRO}

# vim: set tw=78:
