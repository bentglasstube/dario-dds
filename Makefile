SOURCES=$(wildcard src/*.cc)
BUILDDIR=build
OBJECTS=$(patsubst %.cc,$(BUILDDIR)/%.o,$(SOURCES))

CC=clang++
CFLAGS=-g -Wall -Wextra --std=c++03
LDLIBS=`sdl2-config --cflags --libs` -lSDL2_mixer
LDFLAGS=

EXECUTABLE=$(BUILDDIR)/game

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	mkdir -p $(BUILDDIR)
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BUILDDIR) ld32.{glc,mkv}

run: $(EXECUTABLE)
	./$(EXECUTABLE)

video: ld32.mkv

ld32.mkv: ld32.glc
	glc-play $< -o - -y 1 |ffmpeg -i - -preset ultrafast -vcodec libx264 -y $@

ld32.glc: $(EXECUTABLE)
	glc-capture -pso $@ $(EXECUTABLE)

debug: $(EXECUTABLE)
	gdb $(EXECUTABLE)

package: $(EXECUTABLE)
	mkdir dario
	cp $(EXECUTABLE) README.md dario
	cp -R content dario/content
	tar zcf dario.tgz dario
	rm -rf dario

.PHONY: all clean run video debug package
