# 2 levels include, for instance: server/util
INCLUDE_BASE        = ../../
# 3 levels include, for instance: client/vc/EngineCompiler
INCLUDE_BASE        += ../../../
TMDBUILDFLAGS       =-O3 -pthread -DLINUX -Wno-deprecated
QMAKE_CXXFLAGS_WARN_ON=-w

ECPG_PATH           = $(POSTGRES_HOME)/bin/ecpg
ECPG_DEFINE         =
ECPG_HOME           = /usr
ECPG_INCLUDE_PATH   = $${INCLUDE_BASE}

ECPG_SYSINC_PATH    += $(POSTGRES_HOME)/include
ECPG_SYSINC_PATH    += . 
ECPG_SYSINC_PATH    += ../util 
ECPG_SYSINC_PATH    += /usr/include/postgresql

#QMAKE_CFLAGS_DEBUG  += \'$(TMDBUILDFLAGS)\' -trigraphs -fPIC -DPRECOMP 
#QMAKE_CFLAGS_DEBUG  += -D_GNU_SOURCE -D_LARGEFILE64_SOURCE=1 -D_LARGEFILE_SOURCE=1 
#QMAKE_CFLAGS_DEBUG  += -DSLTS_ENABLE -DSLMXMX_ENABLE -D_REENTRANT -DNS_THREADS 
#QMAKE_CFLAGS_DEBUG  += -DDEBUG -D_DEBUG -D__DEBUG 
DEFINES     += LINUX _LINUX_
INCLUDEPATH += $${INCLUDE_BASE}
INCLUDEPATH += $${ECPG_SYSINC_PATH}
LIBS        += -lecpg -lpgtypes
OBJECTS_DIR = .objs
MOC_DIR     = .mocs

# ecpg target for building .pgc files
ecpg_pgc.commands   = $${ECPG_PATH}
ecpg_pgc.commands   += ${QMAKE_FILE_IN}
ecpg_pgc.commands   += -o ${QMAKE_FILE_OUT}
ecpg_pgc.commands   += -I.
ecpg_pgc.commands   += -I../util
ecpg_pgc.dependency_type    = TYPE_C
ecpg_pgc.depends            = $(ECPG_HEADERS)
ecpg_pgc.input              = ECPG_SOURCES
ecpg_pgc.name               = postgre_ecpg
ecpg_pgc.output             = ${QMAKE_FILE_IN_BASE}.cpp
ecpg_pgc.variable_out       = SOURCES
ecpg_pgc.CONFIG             = no_link + target_predeps
QMAKE_EXTRA_COMPILERS       += ecpg_pgc

# ecpg target for building .pgh files
ecpg_pgh.commands   = $${ECPG_PATH}
ecpg_pgh.commands   += ${QMAKE_FILE_IN}
ecpg_pgh.commands   += -o ${QMAKE_FILE_OUT}
ecpg_pgh.commands   += -I.
ecpg_pgh.dependency_type    = TYPE_C
ecpg_pgh.input              = ECPG_HEADERS
ecpg_pgh.name               = postgre_ecpg
ecpg_pgh.output             = ${QMAKE_FILE_IN_BASE}.h
ecpg_pgh.variable_out       = HEADERS
ecpg_pgh.CONFIG             = no_link + target_predeps
QMAKE_EXTRA_COMPILERS       += ecpg_pgh

VERSION = 7,00
QT      = core network sql
TARGET  = engine

include(engine.pri)

# vim: set ft=cfg ts=4 sw=4 et:
