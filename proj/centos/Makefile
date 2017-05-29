CC=LD_LIBRARY_PATH=/usr/local/lib64 g++ -I/usr/include/ffmpeg -I/usr/include/SDL2/SDL2_mixer-2.0.1/ -I/usr/include/SDL2/SDL2_net-2.0.1/ -I/usr/local/include/SDL2/ -I/usr/local/include/ -I/usr/include/
CFLAGS=-c -Wall -std=c++0x
LDFLAGS=-L/usr/lib64 -lGL -lSDL2 -lSDL2_mixer -lSDL2_net -lGLEW -lavcodec -lavutil -lavformat -lavfilter -lswscale -lpng -ljpeg
SOURCES=../../source/app/appmain.cpp\
../../source/debug.cpp\
../../source/gui/cursor.cpp\
../../source/gui/inevent.cpp\
../../source/gui/gui.cpp\
../../source/gui/widget.cpp\
../../source/gui/icon.cpp\
../../source/render/shader.cpp\
../../source/gui/font.cpp\
../../source/gui/richtext.cpp\
../../source/platform.cpp\
../../source/utils.cpp\
../../source/sys/unicode.cpp\
../../source/sys/utf8.cpp\
../../source/window.cpp\
../../source/ustring.cpp\
../../source/texture.cpp\
../../source/sim/simflow.cpp\
../../source/sim/simdef.cpp\
../../source/input/input.cpp\
../../source/math/3dmath.cpp\
../../source/math/camera.cpp\
../../source/math/matrix.cpp\
../../source/math/quaternion.cpp\
../../source/math/vec3f.cpp\
../../source/math/vec4f.cpp\
../../source/math/plane3f.cpp\
../../source/gui/draw2d.cpp\
../../source/gui/widgets/winw.cpp\
../../source/gui/widgets/image.cpp\
../../source/gui/widgets/button.cpp\
../../source/gui/widgets/editbox.cpp\
../../source/gui/widgets/text.cpp\
../../source/gui/widgets/droplist.cpp\
../../source/gui/layouts/appgui.cpp\
../../source/algo/localmap.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=../../testfolder/pl

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o $(EXECUTABLE)
	rm -rf $(OBJECTS) 
