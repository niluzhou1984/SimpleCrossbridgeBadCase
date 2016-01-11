#!/usr/bin/make
include MakefileCfg.mk

all:
	"$(FLASCC)/usr/bin/g++"  -c  simpletest.cpp  -emit-llvm -o simpletest.cpp.o
	"$(FLASCC)/usr/bin/g++"  -save-temps simpletest.cpp.o -o simpletest_crossbridge.exe
	"./llvm/bin/llvm-g++" simpletest.cpp -o simpletest_llvm.exe
	rm -f simpletest.cpp.o simpletest.cpp.lto.2.as simpletest.cpp.lto.abc simpletest.cpp.lto.bc
clean:
	rm -f simpletest_crossbridge.exe simpletest.ccp.lto.1.as simpletest_llvm.exe
