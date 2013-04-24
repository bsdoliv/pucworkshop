HEADERS += main.h
HEADERS += StructureDB.h
HEADERS += MnemoDB.h
HEADERS += DocumentDB.h
HEADERS += ../util/IntSet.h
HEADERS += ../util/TMDApplication.h
HEADERS += ../common/qlog.h

SOURCES += ../util/Basic.cpp
SOURCES += ../util/IntSet.cpp
SOURCES += ../util/HashTable.cpp
SOURCES += ../util/TMDLog.cpp
SOURCES += ../util/TMDCritSec.cpp
SOURCES += ../../client/vc/EngineCompiler/Analyze.cpp
SOURCES += ../../client/vc/EngineCompiler/CharTo.cpp
SOURCES += ../../client/vc/EngineCompiler/Lex.cpp
SOURCES += ../../client/vc/EngineCompiler/Message.cpp
SOURCES += ../../client/vc/EngineCompiler/ST.cpp
SOURCES += main.cpp 
SOURCES += StructureDB.cpp 
SOURCES += MnemoDB.cpp
SOURCES += DocumentDB.cpp
SOURCES += ../common/qlog.cpp

ECPG_SOURCES += OracleDict.pgc 
ECPG_SOURCES += EngineThread.pc
ECPG_SOURCES += EngineApplication.pc
ECPG_SOURCES += ../../client/vc/EngineCompiler/AST.pgc
ECPG_SOURCES += ../util/TMDApplication.pgc
ECPG_SOURCES += ../util/Oracle.pgc
ECPG_SOURCES += ../util/TMDThread.pgc

ECPG_HEADERS += EngineThread.pgh

# vim: set ft=cfg ts=4 sw=4 et:
