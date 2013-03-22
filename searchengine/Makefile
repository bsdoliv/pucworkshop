# qt config
export QTDIR?=/usr
QMAKE=${QTDIR}/bin/qmake

PROG=searchengine
VERSION=0.1
PACKAGE=${PROG}-${VERSION}.tgz
QUICKPACKAGE=${PROG}-${VERSION}.zip

QMAKEFILE=${PROG}.makefile
QMAKEPRO=${PROG}.pro

# dev build opts
QMAKEFILE_OPTS+="TARGET=${PROG}"
QMAKEFILE_OPTS+="OBJECTS_DIR=./.objs"
QMAKEFILE_OPTS+="MOC_DIR=./.mocs"
QMAKEFILE_OPTS+="CONFIG += debug"
QMAKEFILE_OPTS+="DEFINES += BOOL=bool"
QMAKEFILE_OPTS+="INCLUDEPATH += ${INCLUDEPATH}"
QMAKEFILE_OPTS+="QMAKE_CXXFLAGS_WARN_ON=-w"
QMAKEFILE_OPTS+="QMAKE_CFLAGS_WARN_ON=-w"
QMAKEFILE_OPTS+="QT -= network"
QMAKEFILE_OPTS+="QT -= sql"
QMAKEFILE_OPTS+="QT -= gui"
QMAKEFILE_OPTS+="QT -= xml"
#QMAKEFILE_OPTS+="DEFINES += WARN_LOG=1"

QMAKEPRO_OPTS+= -t app
QMAKEPRO_OPTS+= -nopwd
QMAKEPRO_OPTS+= -norecursive
QMAKEPRO_OPTS+= ${SRCS} ${HDRS}

SRCS=*.cpp
HDRS=*.h

all: build

.PHONY: build
build: ${PROG} ${PROG}-release

.PHONY: ${PROG}
${PROG}: ${QMAKEFILE}
	${MAKE} -f $<

${PROG}-release: ${PROG}
	strip --strip-unneeded ${PROG} -o $@

${QMAKEFILE}: ${QMAKEPRO}
	${QMAKE} -makefile ${QMAKEFILE_OPTS} -o $@ $<

${QMAKEPRO}: Makefile
	${QMAKE} -project ${QMAKEPRO_OPTS} -o $@ $<

.PHONY: distclean
distclean: clean prunebuild
	-[ -d .objs ] && \
		rmdir .objs
	-[ -d .mocs ] && \
		rmdir .mocs

.PHONY: clean
clean:
	-[ -e ${QMAKEFILE} ] && \
		${MAKE} -f ${QMAKEFILE} clean
	-rm -fv ${PROG}-release
	-rm -fv ${PROG}
	-rm -fv ui_*.h

.PHONY: prunebuild
prunebuild:
	-rm -fv ${QMAKEFILE}
	-rm -fv ${QMAKEPRO}

.PHONY: build
build:
	@true

# vim: set tw=78:
