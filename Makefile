CXX = x86_64-w64-mingw32-g++ -std=gnu++11
#CXX = i686-w64-mingw32-g++ -std=gnu++11

UNICODE = -municode -DUNICODE -D_UNICODE
#UNICODE =

all: pngview

clean:
	rm -f *~

.PHONY: all clean

pngview: pngview.cc
	$(CXX) -o $@ -mwindows $(UNICODE) -static $< -lgdiplus -lgdi32
