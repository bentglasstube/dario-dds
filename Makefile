UNAME=$(shell uname)

SOURCES=$(wildcard src/*.cc)
CONTENT=$(wildcard conten/*)
BUILDDIR=build
OBJECTS=$(patsubst %.cc,$(BUILDDIR)/%.o,$(SOURCES))
APP_NAME=Dario

CC=clang++
CFLAGS=-g --std=c++03
#CFLAGS+=-Wall -Wextra

ifeq ($(UNAME), Linux)
	LDLIBS=`sdl2-config --cflags --libs` -lSDL2_mixer
	PACKAGE=dario.tgz
endif
ifeq ($(UNAME), Darwin)
	LDLIBS=-framework SDL2 -framework SDL2_mixer -rpath @executable_path/../Frameworks
	PACKAGE=$(APP_NAME).dmg
	CFLAGS+=-mmacosx-version-min=10.5
endif

EXECUTABLE=$(BUILDDIR)/game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

run: $(EXECUTABLE)
	./$(EXECUTABLE)

video: ld32.mkv

ld32.mkv: ld32.glc ld32.wav
	glc-play $< -o - -y 1 |ffmpeg -i - -preset ultrafast -i ld32.wav -acodec flac -vcodec libx264 -y $@

ld32.wav: ld32.glc
	glc-play $< -a 1 -o $@

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

template.dmg: template.dmg.bz2
	bunzip2 -k $<

$(APP_NAME).dmg: template.dmg $(APP_NAME).app
	mkdir -p working
	hdiutil attach "template.dmg" -noautoopen -quiet -mountpoint "working"
	ditto -rsrc "$(APP_NAME).app" "working/$(APP_NAME).app"
	hdiutil detach `hdiutil info |grep working |grep -o '/dev/disk\d\+'` -quiet -force
	rm -f $(APP_NAME).dmg
	hdiutil convert template.dmg -quiet -format UDZO -imagekey zlib-level=9 -o "$@"
	rmdir working

$(APP_NAME).app: $(EXECUTABLE) launcher $(CONTENT) Info.plist
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

clean:
	rm -rf $(BUILDDIR) ld32.* $(APP_NAME).app *.dmg dario.tgz

.PHONY: all clean run video debug package install
