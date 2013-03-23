#
#	$Id$

# qt config
#export QTDIR?=/opt/qt450
#export LIBENGINEDIR?=../corelib
QMAKE=${QTDIR}/bin/qmake

TESTS_SOURCES=$(shell ls test*.cpp)
TESTS_TARGETS=$(TESTS_SOURCES:.cpp=)

QMAKEFILES=$(TESTS_SOURCES:.cpp=.makefile)
QMAKEPROS=$(TESTS_SOURCES:.cpp=.pro)

all: build-tests run-tests

.PHONY: build-tests
build-tests: ${TESTS_TARGETS}

${TESTS_TARGETS}: ${QMAKEFILES} ${TESTS_SOURCES}
	${MAKE} -f $@.makefile

.PHONY: run-tests
run-tests: all
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${LIBENGINEDIR} ./run-tests.sh

${QMAKEFILES}: ${QMAKEPROS}
	${QMAKE} -makefile \
		$(@:.makefile=.pro) \
		"TARGET=${TEST}" \
		"INCLUDEPATH+=/opt/google.sparse/include" \
		"INCLUDEPATH+=${LIBENGINEDIR}" \
                "LIBS+=-ldaimeengine -L${LIBENGINEDIR}" \
		"OBJECTS_DIR=./.objs" \
		"MOC_DIR=./.mocs" \
		"QT += sql" \
		"QT -= gui" \
		-o $@

${QMAKEPROS}: Makefile
	${QMAKE} -project \
		"CONFIG += qtestlib" \
		"CONFIG += debug" \
		"DEPENDPATH += ${LIBENGINEDIR}" \
		"INCLUDEPATH += ${LIBENGINEDIR}" \
		-nopwd \
		-norecursive \
		$(@:.pro=.cpp) \
		-o $@

# updates the ignore list on repo
.PHONY: ignoreup
ignoreup: .cvsignore
	svn propset svn:ignore -F $< .

.PHONY: distclean
distclean: cleanlib clean prunebuild
	-[ -d .objs ] && \
		rmdir .objs
	-[ -d .mocs ] && \
		rmdir .mocs

.PHONY: clean
clean:
	-for i in ${QMAKEFILES}; do \
		[ -e $${i} ] && \
		${MAKE} -f $${i} clean; \
	done
	-rm -fv ${TESTS_TARGETS}

.PHONY: prunebuild
prunebuild:
	-for i in ${QMAKEFILES}; do \
		[ -e $${i} ] && \
		rm -fv $${i};\
	done
	-for i in ${QMAKEPROS}; do \
		[ -e $${i} ] && \
		rm -fv $${i};\
	done

# vim: set tw=78:
