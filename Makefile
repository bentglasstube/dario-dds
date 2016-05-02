UNAME=$(shell uname)

SOURCES=$(wildcard src/*.cc)
CONTENT=$(wildcard conten/*)
BUILDDIR=build
OBJECTS=$(patsubst %.cc,$(BUILDDIR)/%.o,$(SOURCES))
NAME=dario
APP_NAME=Dario

CC=clang++
CFLAGS=-O3 --std=c++03 -Wall -Wextra -pedantic -Werror

ifeq ($(UNAME), Linux)
	PACKAGE=$(NAME)-linux.tgz
	LDFLAGS=-static-libstdc++ -static-libgcc
	LDLIBS=`sdl2-config --cflags --libs` -lSDL2_mixer
endif
ifeq ($(UNAME), Darwin)
	PACKAGE=$(NAME)-osx.tgz
	LDLIBS=-framework SDL2 -framework SDL2_mixer -rpath @executable_path/../Frameworks
	CFLAGS+=-mmacosx-version-min=10.5
endif

EXECUTABLE=$(BUILDDIR)/$(NAME)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -rf $(BUILDDIR) $(APP_NAME).app $(PACKAGE) $(NAME).{mkv,glc,wav}

video: $(NAME).mkv

$(NAME).mkv: $(NAME).glc $(NAME).wav
	glc-play $< -o - -y 1 |ffmpeg -i - -i $(NAME).wav -acodec flac -vcodec libx264 -y $@

$(NAME).wav: $(NAME).glc
	glc-play $< -a 1 -o $@

$(NAME).glc: $(EXECUTABLE)
	glc-capture -pso $@ $(EXECUTABLE)

$(NAME)-linux.tgz: $(EXECUTABLE)
	mkdir $(NAME)
	cp $(EXECUTABLE) README.md $(NAME)
	cp -R content $(NAME)/content
	tar zcf $@ $(NAME)
	rm -rf $(NAME)

$(NAME)-osx.tgz: $(APP_NAME).app
	mkdir $(NAME)
	cp -r $(APP_NAME).app $(NAME)/.
	tar zcf $@ $(NAME)
	rm -rf $(NAME)

# template.dmg: template.dmg.bz2
# 	bunzip2 -k $<

# $(APP_NAME).dmg: template.dmg $(APP_NAME).app
# 	mkdir -p working
# 	hdiutil attach "template.dmg" -noautoopen -quiet -mountpoint "working"
# 	ditto -rsrc "$(APP_NAME).app" "working/$(APP_NAME).app"
# 	hdiutil detach `hdiutil info |grep working |grep -o '/dev/disk\d\+'` -quiet -force
# 	rm -f $(APP_NAME).dmg
# 	hdiutil convert template.dmg -quiet -format UDZO -imagekey zlib-level=9 -o "$@"
# 	rmdir working

package: $(PACKAGE)

$(APP_NAME).app: $(EXECUTABLE) launcher $(CONTENT) Info.plist build/icon.icns
	rm -rf $(APP_NAME).app
	mkdir -p $(APP_NAME).app/Contents/{MacOS,Frameworks,Resources}
	cp $(EXECUTABLE) $(APP_NAME).app/Contents/MacOS/game
	cp launcher $(APP_NAME).app/Contents/MacOS/launcher
	cp -R content $(APP_NAME).app/Contents/MacOS/content
	cp Info.plist $(APP_NAME).app/Contents/Info.plist
	cp -R /Library/Frameworks/SDL2.framework $(APP_NAME).app/Contents/Frameworks/SDL2.framework
	cp -R /Library/Frameworks/SDL2_mixer.framework $(APP_NAME).app/Contents/Frameworks/SDL2_mixer.framework
	cp build/icon.icns $(APP_NAME).app/Contents/Resources/icon.icns

build/icon.icns: res/icon/icon.iconset/*
	iconutil -c icns -o $@ res/icon/icon.iconset

.PHONY: all clean package run video
