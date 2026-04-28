MAKE = gmake
CC = ccache g++14

LBITS := $(shell getconf LONG_BIT)

INCDIR = -I../../../Extern/include
LIBDIR = -L../../../Extern/lib
BINDIR = ../../bin
OBJDIR = OBJDIR

BSD_VERSION = $(shell freebsd-version | grep -oE '[0-9]+\.[0-9]+')

$(shell if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi)

TARGET = $(BINDIR)/_db_

CFLAGS = -m32 -g -Wall -O2 -pipe -fno-rtti -fno-exceptions -pthread -D_THREAD_SAFE -static-libgcc -static-libstdc++
CXXFLAGS = -std=c++23

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

# Project Library
LIBDIR += -L../../libthecore/lib -L../../libsql -L../../libpoly -L../../libgame/lib
LIBS = -lthecore -lsql -lpoly -lgame -lm

# MySQL
INCDIR += -I/usr/local/include
ifeq ($(LBITS),64)
    LIBS += ../../../Extern/lib/libmysqlclient.a /usr/lib32/libz.a
else
    LIBS += /usr/local/lib/mysql/libmysqlclient.a /usr/lib/libz.a
endif

# openssl
INCDIR += -I/usr/include
ifeq ($(LBITS),64)
    LIBDIR += -L/usr/lib32
else
    LIBDIR += -L/usr/local/lib
endif
LIBS += -lssl -lcrypto

SRCS =	Config.cpp NetBase.cpp Peer.cpp PeerBase.cpp Main.cpp Lock.cpp DBManager.cpp \
		Cache.cpp LoginData.cpp ClientManager.cpp ClientManagerPlayer.cpp ClientManagerLogin.cpp \
		ClientManagerBoot.cpp ClientManagerParty.cpp ClientManagerGuild.cpp GuildManager.cpp \
		PrivManager.cpp MoneyLog.cpp ItemAwardManager.cpp ClientManagerEventFlag.cpp Marriage.cpp \
		ItemIDRangeManager.cpp ClientManagerHorseName.cpp \
		ProtoReader.cpp CsvReader.cpp 

OBJS = $(SRCS:%.cpp=$(OBJDIR)/%.o)

default: $(TARGET)

$(TARGET): $(OBJS)
	@echo linking $(TARGET)...
	@$(CC) $(CFLAGS) $(CXXFLAGS) $(LIBDIR) $(OBJS) $(LIBS) -o $(TARGET)

$(OBJDIR)/%.o: %.cpp
	@echo compile $<
	@$(CC) $(CFLAGS) $(CXXFLAGS) $(INCDIR) -c $< -o $@

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@rm -f $(OBJS) $(BINDIR)/_db_

dep:
	@touch Depend
	makedepend -fDepend $(INCDIR) -I/usr/include/c++/v1 -p$(OBJDIR)/ $(SRCS) 2> /dev/null

sinclude Depend
