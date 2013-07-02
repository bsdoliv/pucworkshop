# qt config
QTDIR?=/usr
QMAKE=${QTDIR}/bin/qmake
GMAKE=/usr/bin/make

TESTCASES=
TESTCASES+=test_computeranks
TESTCASES+=test_crawler
TESTCASES+=test_search

QMAKEFILE_OPTS= 
QMAKEPRO_OPTS+=	"-nopwd"
QMAKEPRO_OPTS+=	"-norecursive"
QMAKEPRO_OPTS+=	"CONFIG += qtestlib" 
QMAKEPRO_OPTS+=	"OBJECTS_DIR = ${.CURDIR}/../.objs"
QMAKEPRO_OPTS+=	"MOC_DIR = ${.CURDIR}/../.mocs"
QMAKEPRO_OPTS+=	"QT -= sql"
QMAKEPRO_OPTS+=	"QT -= gui"
QMAKEPRO_OPTS+=	"QT += network"

.MAIN: build
build: ${TESTCASES} .PHONY

.for _test_ in ${TESTCASES} # {
${_test_}: ${_test_}.makefile
	${GMAKE} -f ${.ALLSRC}

${_test_}.makefile: ${_test_}.pro
	${QMAKE} -makefile ${QMAKEFILE_OPTS} ${.ALLSRC} -o ${.TARGET}

${_test_}.pro: ${MAKEFILE}
	${QMAKE} -project ${QMAKEPRO_OPTS} ${_test_}.cpp -o ${.TARGET}

CLEANFILES+=${_test_}
.endfor # }

run: .PHONY build
.for _test in ${TESTCASES} # {
	@[ -x ${_test} -a x${_test} ] && eval ./${_test}
.endfor

clean distclean: .PHONY
.for _mk in ${TESTCASES} # {
.	if exists(${_mk}.makefile) 
		${GMAKE} -f ${_mk}.makefile ${.TARGET}
.	endif
.	if exists(${_mk}.pro)
.		ifmake (distclean)
			rm -v ${_mk}.pro
.		endif
.	endif
.endfor	# {

.include <bsd.prog.mk>

# vim: set tw=78:
