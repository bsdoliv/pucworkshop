include(engine.pri)

# variables
INCLUDE_BASE        += ../../
INCLUDE_BASE        += ../../../

# ecpg stuff
ECPG_PATH           = $(POSTGRES_HOME)/bin/ecpg
ECPG_INCLUDE_PATH   = $${INCLUDE_BASE}
ECPG_SYSINC_PATH    += $(POSTGRES_HOME)/include
ECPG_SYSINC_PATH    += ${POSTGRES_HOME}/include/postgresql
ECPG_SYSINC_PATH    += . 
ECPG_SYSINC_PATH    += ../util 

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

# qmake stuff
INCLUDEPATH += $${ECPG_SYSINC_PATH} $${INCLUDE_BASE}
QMAKE_CXXFLAGS_WARN_ON=-w
DEFINES     += LINUX _LINUX_
LIBS        += -lecpg -lpgtypes
OBJECTS_DIR = .objs
MOC_DIR     = .mocs
VERSION = 7,00
QT      = core network sql
TARGET  = engine

# vim: set ft=cfg ts=4 sw=4 et:
