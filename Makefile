UNAME=$(shell uname)

SOURCES=$(wildcard src/*.cc)
BUILDDIR=build
OBJECTS=$(patsubst %.cc,$(BUILDDIR)/%.o,$(SOURCES))
APP_NAME=DrDario

CC=clang++
#CFLAGS=-g -Wall -Wextra --std=c++03
CFLAGS=-g --std=c++03

ifeq ($(UNAME), Linux)
	LDLIBS=`sdl2-config --cflags --libs` -lSDL2_mixer
	PACKAGE=dario.tgz
endif
ifeq ($(UNAME), Darwin)
	LDLIBS=-framework SDL2 -framework SDL2_mixer -rpath @executable_path/../Frameworks
	PACKAGE=$(APP_NAME).app/Contents/MacOS/game
endif

EXECUTABLE=$(BUILDDIR)/game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(BUILDDIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BUILDDIR) ld32.{glc,mkv} $(APP_NAME).app dario.tgz

run: $(EXECUTABLE)
	./$(EXECUTABLE)

video: ld32.mkv

ld32.mkv: ld32.glc
	glc-play $< -o - -y 1 |ffmpeg -i - -preset ultrafast -vcodec libx264 -y $@

ld32.glc: $(EXECUTABLE)
	glc-capture -pso $@ $(EXECUTABLE)

debug: $(EXECUTABLE)
	gdb $(EXECUTABLE)

package: $(PACKAGE)

dario.tgz: $(EXECUTABLE)
	mkdir dario
	cp $(EXECUTABLE) README.md dario
	cp -R content dario/content
	tar zcf dario.tgz dario
	rm -rf dario

$(APP_NAME).app/Contents/MacOS/game: $(EXECUTABLE)
	rm -rf $(APP_NAME).app
	mkdir -p $(APP_NAME).app/Contents/{MacOS,Frameworks}
	cp $(EXECUTABLE) $(APP_NAME).app/Contents/MacOS/game
	cp launcher $(APP_NAME).app/Contents/MacOS/launcher
	cp -R content $(APP_NAME).app/Contents/MacOS/content
	cp Info.plist $(APP_NAME).app/Contents/Info.plist
	cp -R /Library/Frameworks/SDL2.framework $(APP_NAME).app/Contents/Frameworks/SDL2.framework
	cp -R /Library/Frameworks/SDL2_mixer.framework $(APP_NAME).app/Contents/Frameworks/SDL2_mixer.framework

install: $(EXECUTABLE)
	mkdir -p $(DESTDIR)/usr/share/dario
	cp -r content $(DESTDIR)/usr/share/dario/
	cp $(EXECUTABLE) $(DESTDIR)/usr/share/dario/dario
	install -D -m755  runner $(DESTDIR)/usr/bin/dario

.PHONY: all clean run video debug package install
