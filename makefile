PLATFORM := $(shell uname)

COMPILER := g++
COMPILER_FLAGS := -Wreorder -c -std=c++11 `sdl2-config --cflags` `freetype-config --cflags`

SRCDIR  := src
SRCEXT  := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

OBJDIR  := obj
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

EXECUTABLE := opengl_playground

MAC_LIBRARIES := -framework OpenGl -framework CoreFoundation -I/usr/local/include -lglew -lSOIL `sdl2-config --libs` `freetype-config --libs` -ljsoncpp
LINUX_LIBRARIES := -lGL -lGLEW -I /usr/lib/x86_64-linux-gnu/ -I /usr/local/include -lSOIL -lpthread `sdl2-config --cflags --libs` `freetype-config --libs` -ljsoncpp

KILL_TIME := 5s
# BUILD_SCRIPT := ./tools/buildcount_timeout.sh $(TIMEOUT_SCRIPT) $(KILL_TIME)
BUILD_SCRIPT :=

# Test stuff
GOOGLE_TEST_DIR := gtest-1.7.0
LIBRARY_DIR := lib
TEST_SRC_DIR := test
TEST_EXECUTABLE := test_executable


# Try to auto detect the platform to build for
ifeq ($(PLATFORM),Darwin)
	LIBRARIES := $(MAC_LIBRARIES)
	TIMEOUT_SCRIPT := gtimeout
else ifeq ($(PLATFORM),Linux)
	LIBRARIES := $(LINUX_LIBRARIES)
	TIMEOUT_SCRIPT := timeout
endif

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) -I$(SRCDIR) $(OBJECTS) $(LIBRARIES) -o $@

	@ $(BUILD_SCRIPT)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(COMPILER) $(COMPILER_FLAGS) -I$(SRCDIR) $< -o $@

configure-linux:
	@ sudo apt-get install libglew-dev libglm-dev libsdl2-dev curl nmap libjsoncpp-dev
	@ wget http://www.lonesock.net/files/soil.zip
	@ unzip soil.zip -d soil
	@ rm soil.zip
	@ rm soil/Simple\ OpenGL\ Image\ Library/lib/libSOIL.a
	@ mkdir soil/Simple\ OpenGL\ Image\ Library/projects/makefile/obj
	@ cd soil/Simple\ OpenGL\ Image\ Library/projects/makefile && make && sudo make install
	@ rm -r soil

discard:
	@ git clean -df
	@ git checkout -- .

clean:
	rm -f $(OBJDIR)/*.o

Window.o : $(SRCDIR)/Window.cpp
	$(COMPILER) $(COMPILER_FLAGS) -I$(SRCDIR) $< -o $@

Mouse.o : $(SRCDIR)/Mouse.cpp
	$(COMPILER) $(COMPILER_FLAGS) -I$(SRCDIR) $< -o $@

test_test.o : $(TEST_SRC_DIR)/test.cpp
	$(COMPILER) $(COMPILER_FLAGS) -I $(GOOGLE_TEST_DIR)/include -I$(SRCDIR) $< -o $@


test_test: Window.o Mouse.o test_test.o
	g++  -pthread -L $(LIBRARY_DIR)/ -l gtest $(LIBRARIES)  $^ -o $@
