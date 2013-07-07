.ifndef BSD_QT_MK # {
BSD_QT_MK=1

# TODO: provide per target build

QTDIR?=/usr
QMAKE?=${QTDIR}/bin/qmake
GMAKE?=/usr/bin/make

QT.makefile?=	${QTARGET}.makefile
QT.profile?=	${QTARGET}.pro

QMAKEOPTS.target?=	${QTARGET}
QMAKEOPTS.template?= 	app
QMAKEOPTS.objs?= 	${.CURDIR}/.objs
QMAKEOPTS.mocs?=	${.CURDIR}/.mocs
QMAKEOPTS.debug?=	no
QMAKEOPTS.incpath?=
QMAKEOPTS.nopwd?=	yes
QMAKEOPTS.recursive?=	no
QMAKEOPTS.config?=	

# default qt options
QMAKEOPTS.qt?= 		core network
# default noqt options
QMAKEOPTS.noqt?=	sql gui webkit xml

# build QMAKEOPTS
QMAKEOPTS= 	"TARGET = ${QMAKEOPTS.target}"
QMAKEOPTS+=	"OBJECTS_DIR = ${QMAKEOPTS.objs}"
QMAKEOPTS+=	"MOC_DIR = ${QMAKEOPTS.mocs}"
.if !empty(QMAKEOPTS.config)
QMAKEOPTS+=	"CONFIG += ${QMAKEOPTS.config}"
.endif
.if (${QMAKEOPTS.debug} == "yes")
QMAKEOPTS+=	"CONFIG += debug"
.endif
.if !empty(QMAKEOPTS.incpath)
QMAKEOPTS+= "INCLUDEPATH += ${QMAKEOPTS.incpath}"
.endif
.if !empty(QMAKEOPTS.qt)
.for _q in ${QMAKEOPTS.qt}
QMAKEOPTS+= "QT += ${_q}"
QMAKEOPTS.noqt:=${QMAKEOPTS.noqt:T:S/${_q}//}
.endfor
.endif
.if !empty(QMAKEOPTS.noqt)
.for _nq in ${QMAKEOPTS.noqt}
.if ${QMAKEOPTS.qt:U${_nq}} != ${_nq}
QMAKEOPTS+= "QT -= ${_nq}"
.endif
.endfor
.endif
.if ${QMAKEOPTS.nopwd} == "yes"
QMAKEOPTS+= "-nopwd"
.endif
.if ${QMAKEOPTS.recursive} == "no"
QMAKEOPTS+= "-norecursive"
.endif

${QTARGET}: ${QT.makefile}
	${GMAKE} -f ${.ALLSRC}

${QT.makefile}: ${QT.profile}
	${QMAKE} -makefile ${MAKEOPTS} -o ${.TARGET} ${.ALLSRC}

${QT.profile}: Makefile
	${QMAKE} -project -t ${QMAKEOPTS.template} \
		${QMAKEOPTS} ${QSRCS} ${QHDRS} -o ${.TARGET} 

.ifmake (clean || distclean) && exists(${QT.makefile})
.BEGIN: _gmake_clean _gmake_dclean

_gmake_clean: .PHONY
	${GMAKE} -f ${QT.makefile} clean

_gmake_dclean: .PHONY
	${GMAKE} -f ${QT.makefile} distclean
.endif

distclean: .PHONY clean
.	for _d in ${.CURDIR}/.objs ${.CURDIR}/.mocs
.		if exists(${_d})
			rmdir ${_d}
.		endif
.	endfor

.MAIN: buildqt
buildqt: .PHONY ${QTARGET}

CLEANFILES+= ui_*.h ${QTARGET} ${QT.makefile} ${QT.profile} 
CLEANFILES+= ${.CURDIR}/.objs/*.o ${.CURDIR}/.mocs/*.moc ${.CURDIR}/.mocs/*.cpp

TARGETS= buildqt
# ugly hack to check if prog has been included since first thing prog does is
# include own.mk
.if !defined(_BSD_OWN_MK_)
.include <bsd.prog.mk>
.endif

.endif # BSD_QT_MK }

# vim: set ts=8 sw=8 noet:
