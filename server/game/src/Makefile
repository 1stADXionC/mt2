BSD_VERSION = $(shell freebsd-version | grep -oE '[0-9]+\.[0-9]+')
LBITS := $(shell getconf LONG_BIT)

CC = ccache g++14

INCDIR = -I../../../Extern/include
LIBDIR = -L../../../Extern/lib
BINDIR = ../../bin
OBJDIR = OBJDIR
$(shell if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi)

# Standard Setting
LIBS = -pthread -lm -lmd

NOWARN = -Wno-stringop-overflow -Wno-dangling-reference -Wno-array-bounds

CFLAGS = -m32 -g -Wall -O2 -pipe -fexceptions -fstack-protector-all -D_THREAD_SAFE -DNDEBUG -static-libgcc -static-libstdc++ $(NOWARN)
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

# DevIL
INCDIR += -I../../../Extern/include/IL
LIBS += ../../../Extern/lib/libIL.a\
		../../../Extern/lib/libjasper.a\
		../../../Extern/lib/libpng.a\
		../../../Extern/lib/libtiff.a\
		../../../Extern/lib/libjbig.a\
		../../../Extern/lib/libmng.a\

ifeq ($(LBITS),64)
    LIBS += /usr/lib32/liblzma.a
else
    LIBS += /usr/lib/liblzma.a
endif

LIBS += ../../../Extern/lib/liblcms.a\
		../../../Extern/lib/libjpeg.a

# MySQL
INCDIR += -I/usr/local/include
ifeq ($(LBITS),64)
    LIBS += ../../../Extern/lib/libmysqlclient.a /usr/lib32/libz.a
else
    LIBS += /usr/local/lib/mysql/libmysqlclient.a /usr/lib/libz.a
endif

# Miscellaneous external libraries
INCDIR += -I../../../Extern/include
LIBDIR += -L../../../Extern/lib
LIBS += -lcryptopp

# openssl
INCDIR += -I/usr/include
ifeq ($(LBITS),64)
    LIBDIR += -L/usr/lib32
else
    LIBDIR += -L/usr/local/lib
endif
LIBS += -lssl -lcrypto

# Project Library
INCDIR += -I../../liblua/include
INCDIR += -I../../../Extern/include
LIBDIR += -L../../libthecore/lib -L../../libpoly -L../../libsql -L../../libgame/lib -L../../liblua/lib
LIBDIR += -L../../../Extern/lib/
LIBS += -lthecore -lpoly -llua -llualib -lsql -lgame

USE_STACKTRACE = 0
ifeq ($(USE_STACKTRACE), 1)
LIBS += /usr/local/lib/libexecinfo.a
endif

TARGET  = $(BINDIR)/_game_

CFILE	= minilzo.c

CPPFILE = FSM.cpp MarkConvert.cpp MarkImage.cpp MarkManager.cpp OXEvent.cpp ani.cpp\
		  arena.cpp banword.cpp battle.cpp blend_item.cpp buffer_manager.cpp building.cpp\
		  char.cpp char_affect.cpp char_battle.cpp char_change_empire.cpp char_horse.cpp char_item.cpp char_manager.cpp\
		  char_quickslot.cpp char_resist.cpp char_skill.cpp char_state.cpp PetSystem.cpp cmd.cpp cmd_emotion.cpp cmd_general.cpp\
		  cmd_gm.cpp cmd_oxevent.cpp config.cpp constants.cpp crc32.cpp cube.cpp db.cpp desc.cpp\
		  desc_client.cpp desc_manager.cpp desc_p2p.cpp dungeon.cpp empire_text_convert.cpp entity.cpp\
		  entity_view.cpp event.cpp event_queue.cpp exchange.cpp file_loader.cpp fishing.cpp gm.cpp guild.cpp\
		  guild_manager.cpp guild_war.cpp horse_rider.cpp horsename_manager.cpp input.cpp input_auth.cpp input_db.cpp\
		  input_login.cpp input_main.cpp input_p2p.cpp\
		  item.cpp item_addon.cpp item_attribute.cpp item_manager.cpp item_manager_idrange.cpp locale.cpp\
		  locale_service.cpp log.cpp login_data.cpp lzo_manager.cpp marriage.cpp\
		  messenger_manager.cpp mining.cpp mob_manager.cpp motion.cpp p2p.cpp packet_info.cpp\
		  party.cpp polymorph.cpp priv_manager.cpp pvp.cpp\
		  questevent.cpp questlua.cpp questlua_affect.cpp questlua_arena.cpp questlua_building.cpp\
		  questlua_danceevent.cpp questlua_dungeon.cpp questlua_game.cpp questlua_global.cpp\
		  questlua_guild.cpp questlua_horse.cpp questlua_pet.cpp questlua_item.cpp questlua_marriage.cpp\
		  questlua_npc.cpp questlua_oxevent.cpp questlua_party.cpp questlua_pc.cpp\
		  questlua_quest.cpp questlua_target.cpp questmanager.cpp questnpc.cpp questpc.cpp\
		  refine.cpp regen.cpp safebox.cpp sectree.cpp sectree_manager.cpp sequence.cpp shop.cpp\
		  skill.cpp start_position.cpp target.cpp text_file_loader.cpp trigger.cpp utils.cpp vector.cpp war_map.cpp\
		  wedding.cpp xmas_event.cpp panama.cpp map_location.cpp\
		  BlueDragon.cpp BlueDragon_Binder.cpp DragonLair.cpp questlua_dragonlair.cpp\
		  skill_power.cpp affect.cpp\
		  ClientPackageCryptInfo.cpp cipher.cpp\
		  buff_on_attributes.cpp dragon_soul_table.cpp DragonSoul.cpp\
		  group_text_parse_tree.cpp char_dragonsoul.cpp questlua_dragonsoul.cpp\
		  shop_manager.cpp shopEx.cpp item_manager_read_tables.cpp MemleketTitle.cpp


COBJS	= $(CFILE:%.c=$(OBJDIR)/%.o)
CPPOBJS	= $(CPPFILE:%.cpp=$(OBJDIR)/%.o)

MAINOBJ = $(OBJDIR)/main.o
MAINCPP = main.cpp

default: $(TARGET)

$(OBJDIR)/minilzo.o: minilzo.c
	@$(CC) $(CFLAGS) $(CXXFLAGS) $(INCDIR) -c $< -o $@
	@echo compile $<

$(OBJDIR)/%.o: %.cpp
	@echo compile $<
	@$(CC) $(CFLAGS) $(CXXFLAGS) $(INCDIR) -c $< -o $@

$(TARGET): $(CPPOBJS) $(COBJS) $(MAINOBJ)
	@echo linking $(TARGET)...
	@$(CC) $(CFLAGS) $(CXXFLAGS) $(LIBDIR) $(COBJS) $(CPPOBJS) $(MAINOBJ) $(LIBS) -o $(TARGET)

clean:
	@rm -f $(COBJS) $(CPPOBJS) $(MAINOBJ)
	@rm -f $(BINDIR)/_game_ $(BINDIR)/conv

tag:
	ctags *.cpp *.h *.c

dep:
	makedepend -f Depend $(INCDIR) -p$(OBJDIR)/ $(CPPFILE) $(CFILE) $(MAINCPP) 2> /dev/null > Depend

sinclude Depend
