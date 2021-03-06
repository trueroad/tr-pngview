all: pngview

#
# Build settings
#

# HOST: x86_64-w64-mingw32 (64 bit) / i686-w64-mingw32 (32 bit)
HOST = x86_64-w64-mingw32
#HOST = i686-w64-mingw32

# API_STRINGS: Unicode / ANSI
API_STRINGS = Unicode
#API_STRINGS = ANSI

# LDFLAGS_STATIC: (Depends on MinGW DLLs) / -static (No MinGW DLLs required)
LDFLAGS_STATIC =
#LDFLAGS_STATIC = -static


#
# Objects and libraries
#
OBJS = pngview.o \
	pngview_window.o stretch.o \
	bitmap_loader.o per_monitor_dpi.o fileopendialog.o \
	about.o timer.o \
	pngview.res.o
LDLIBS = -lgdiplus -lgdi32 -lole32


#
# Programs and other settings
#
WINDRES = windres
CXXFLAGS_STD = -std=c++11
LDFLAGS_WINDOWS = -mwindows


#
# Dependencies
#
DEPS = $(OBJS:.o=.d)
CPPFLAGS += -MMD -MP -MF $(@:.o=.d) -MT $@
-include $(DEPS)

#
# Toolchain prefix
#
ifneq ($(HOST),)
CXX := $(HOST)-$(CXX)
WINDRES := $(HOST)-$(WINDRES)
endif

#
# Unicode
#
ifeq ($(API_STRINGS),Unicode)
CPPFLAGS_UNICODE = -DUNICODE -D_UNICODE
LDFLAGS_UNICODE = -municode
else
CPPFLAGS_UNICODE =
LDFLAGS_UNICODE =
endif


#
# Flags
#
CXXFLAGS += $(CXXFLAGS_STD)
CPPFLAGS += $(CPPFLAGS_UNICODE)
LDFLAGS += $(LDFLAGS_STATIC) $(LDFLAGS_WINDOWS) $(LDFLAGS_UNICODE)
WINDRESFLAGS += $(foreach ARG,$(CPPFLAGS),--preprocessor-arg=$(ARG))


#
# Rules
#

clean:
	$(RM) *~ $(OBJS) $(DEPS)

.PHONY: all clean

pngview: $(OBJS)
	$(CXX) $(LDFLAGS) $(TARGET_ARCH) $^ $(LOADLIBES) $(LDLIBS) -o $@

%.res.o: %.rc
	$(WINDRES) $(WINDRESFLAGS) -i $< $(OUTPUT_OPTION)


#
# Other dependencies
#
pngview.res.o: pngview.manifest


#
# Implicit variables (from `make -p`)
#

#CXX = g++
#RM = rm -f
#COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
#COMPILE.C = $(COMPILE.cc)
#COMPILE.cpp = $(COMPILE.cc)
#OUTPUT_OPTION = -o $@


#
# Implicit rules (from `make -p`)
#

#%.o: %.cc
#	$(COMPILE.cc) $(OUTPUT_OPTION) $<
#
#%.o: %.C
#	$(COMPILE.C) $(OUTPUT_OPTION) $<
#
#%.o: %.cpp
#	$(COMPILE.cpp) $(OUTPUT_OPTION) $<
