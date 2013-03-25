#
#	$Id$

# qt config
export QTDIR?=/usr
QMAKE=${QTDIR}/bin/qmake

TESTS_SOURCES=$(shell ls test*.cpp)
TESTS_TARGETS=$(TESTS_SOURCES:.cpp=)

QMAKEFILES=$(TESTS_SOURCES:.cpp=.makefile)
QMAKEPROS=$(TESTS_SOURCES:.cpp=.pro)

all: build 
#run

.PHONY: build
build: ${TESTS_TARGETS}

.PHONY: ${TESTS_TARGETS}
${TESTS_TARGETS}: ${QMAKEFILES} ${TESTS_SOURCES}
	${MAKE} -f $@.makefile

.PHONY: run
run: build
	./run-tests.sh

#		"TARGET=${TEST}" 
${QMAKEFILES}: ${QMAKEPROS}
	${QMAKE} -makefile \
		$(@:.makefile=.pro) \
		"OBJECTS_DIR=../.objs" \
		"MOC_DIR=../.mocs" \
		"QT -= sql" \
		"QT += network" \
		"QT -= gui" \
		-o $@

#		"CONFIG += debug" 
${QMAKEPROS}: Makefile
	${QMAKE} -project \
		"CONFIG += qtestlib" \
		-nopwd \
		-norecursive \
		$(@:.pro=.cpp) \
		-o $@

.PHONY: distclean
distclean: clean prunebuild
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
	-for i in ${TESTS_TARGETS}; do \
		[ -d $${i}.app ] && \
			rm -rfv $${i}.app ;\
	done

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
