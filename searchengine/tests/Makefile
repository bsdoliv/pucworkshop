#.include "../Makefile.inc"

.include <bsd.prog.mk>

TESTCASES=
TESTCASES+=test_computeranks
TESTCASES+=test_crawler
TESTCASES+=test_search

QMAKEOPTS.config+=	qtestlib
QMAKEOPTS.debug=	yes

all: buildall

buildqt buildall: .PHONY ${TESTCASES}

.for _test_ in ${TESTCASES} # {
${_test_}: ${_test_}.makefile
	${GMAKE} -f ${.ALLSRC}

${_test_}.makefile: ${_test_}.pro
	${QMAKE} -makefile ${MAKEOPTS} ${.ALLSRC} -o ${.TARGET}

${_test_}.pro: ${MAKEFILE}
	${QMAKE} -project ${QMAKEOPTS} ${_test_}.cpp -o ${.TARGET}

CLEANFILES+=${_test_}
CLEANFILES+=${_test_}.pro ${_test_}.makefile
.endfor # }

run: .PHONY buildall
.for _test in ${TESTCASES} # {
	@[ -x ${_test} -a x${_test} ] && eval ./${_test}
.endfor

.ifmake (clean || distclean || cleandir) # {
.BEGIN: _distclean

_distclean: .PHONY
.for _mk in ${TESTCASES} # {
.	if exists(${_mk}.makefile) 
		${GMAKE} -f ${_mk}.makefile ${.TARGET} distclean
.	endif
.endfor	# }
.endif # ifname clean }

.include "bsd.qt.mk"

# vim: set tw=78:
