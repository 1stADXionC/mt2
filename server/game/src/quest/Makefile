CXX = g++14
MODE = -m32
CPPFLAGS= -g -std=c++23

LBITS := $(shell getconf LONG_BIT)

ifeq ($(LBITS),64)
    CFLAGS += -L/usr/local/lib32/gcc14
    CFLAGS += -Wl,-rpath=/usr/local/lib32/gcc14
    CXXFLAGS += -L/usr/local/lib32/gcc14
    CXXFLAGS += -Wl,-rpath=/usr/local/lib32/gcc14
else
    CFLAGS += -L/usr/local/lib/gcc14
    CFLAGS += -Wl,-rpath=/usr/local/lib/gcc14
    CXXFLAGS += -L/usr/local/lib/gcc14
    CXXFLAGS += -Wl,-rpath=/usr/local/lib/gcc14
endif

INCLUDEDIR =

INCLUDEDIR += -I../../../liblua/include
INCLUDEDIR += -I../../../liblua/src
LIBS += ../../../liblua/lib/liblua.a ../../../liblua/lib/liblualib.a

qc: qc.cc qc.o crc32.o
	$(CXX) $(MODE) $(CXXFLAGS) $(CPPFLAGS) -o ../../../bin/_qc_ $(INCLUDEDIR) qc.o crc32.o $(LIBS)

crc32.o: crc32.cc
	$(CXX) $(MODE) $(CXXFLAGS) $(CPPFLAGS) -c $< $(INCLUDEDIR)

qc.o: qc.cc
	$(CXX) $(MODE) $(CXXFLAGS) $(CPPFLAGS) -c $< $(INCLUDEDIR)

all: qc create_conversion

create_conversion.o: create_conversion.cc
	$(CXX) $(MODE) $(CXXFLAGS) $(CPPFLAGS) -c $< $(INCLUDEDIR)

create_conversion: crc32.o create_conversion.o
	$(CXX) $(MODE) $(CXXFLAGS) -g -o ../../../bin/_create_conversion_ $(INCLUDEDIR) create_conversion.o crc32.o $(LIBS)

clean:
	rm -f ../../../bin/_qc_ cc qc.o crc32.o cc.o create_conversion.o ../../../bin/_create_conversion_
