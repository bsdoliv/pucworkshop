TESTCASES=
TESTCASES+=test_computeranks
TESTCASES+=test_crawler
TESTCASES+=test_search

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
.endfor	# }

.include "../Makefile.inc"
.include "bsd.qt.mk"

# vim: set tw=78:
