.ifndef ABSTOP # {
ABSTOP!= cd ${.PARSEDIR}; pwd

.if ${.MAKEFLAGS:M${ABSTOP}/mk} == ""
.MAKEFLAGS: -I ${ABSTOP}/mk
.endif

QMAKEOPTS.qt+=	webkit
QMAKEOPTS.qt+=	gui
QMAKEOPTS.qt+=	network

.include <bsd.own.mk>
.endif # ABSTOP }

# vim: ts=8 sw=8 ft=make:
