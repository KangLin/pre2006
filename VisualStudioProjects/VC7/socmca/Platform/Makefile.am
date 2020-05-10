AUTOMAKE_OPTIONS = foreign

LIBS = -ldl -lpthread

CFLAGS = -D__LINUX__ -D_DEBUG
CPPFLAGS = -D__LINUX__ -D_DEBUG

bin_PROGRAMS = test 
#test_SOURCES = dll.c test.c thread.c
test_SOURCES = dll.cpp test.cpp thread.cpp synchronization.cpp

SUBDIRS = lib
