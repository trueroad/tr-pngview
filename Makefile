ARCH = x86_64-w64-mingw32

UNICODE = -municode -DUNICODE -D_UNICODE
#UNICODE =

CXX = $(ARCH)-g++ -std=gnu++11
WINDRES = $(ARCH)-windres

all: pngview

clean:
	rm -f *~ *.o

.PHONY: all clean

pngview: pngview.o pngview.res.o
	$(CXX) -o $@ -mwindows $(UNICODE) -static $^ -lgdiplus -lgdi32

%.res.o: %.rc
	$(WINDRES) -i $< -o $@

%.o: %.cc
	$(CXX) -c -o $@ -mwindows $(UNICODE) $<
