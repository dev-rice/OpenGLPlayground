PLATFORM := $(shell uname)

COMPILER := g++
COMPILER_FLAGS := -Wreorder -c -std=c++14 `sdl2-config --cflags` `freetype-config --cflags`

SRCDIR  := src
SRCEXT  := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

OBJDIR  := obj
OBJECTS := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

MAC_LIBRARIES := -framework OpenGl -framework CoreFoundation -I/usr/local/include -lglew -lSOIL `sdl2-config --libs`
LINUX_LIBRARIES := -lGL -lGLEW -I /usr/lib/x86_64-linux-gnu/ -I /usr/local/include -lSOIL -lpthread `sdl2-config --cflags --libs`

LIBRARY_DIR := lib
LOCAL_LIBRARIES := -L$(LIBRARY_DIR) -l pugixml

# Test stuff
GOOGLE_TEST_DIR := gtest-1.7.0
GOOGLE_TEST_SRC_DIR := $(GOOGLE_TEST_DIR)/src
GOOGLE_TEST_INCLUDE_DIR := $(GOOGLE_TEST_DIR)/include

TEST_SRC_DIR := tests
TEST_EXECUTABLE := test_executable
TEST_SRC := $(TEST_SRC_DIR)/all_tests.cpp

GOOGLE_MOCK_DIR := gmock-1.7.0
GOOGLE_MOCK_SRC_DIR := $(GOOGLE_MOCK_DIR)/src
GOOGLE_MOCK_INCLUDE_DIR := $(GOOGLE_MOCK_DIR)/include

PUGIXML_DIR := pugi
PUGIXML_INCLUDE_DIR := $(PUGIXML_DIR)/include

APP_DIR := apps

# Try to auto detect the platform to build for
ifeq ($(PLATFORM),Darwin)
	LIBRARIES := $(MAC_LIBRARIES)
	TIMEOUT_SCRIPT := gtimeout
else ifeq ($(PLATFORM),Linux)
	LIBRARIES := $(LINUX_LIBRARIES)
	TIMEOUT_SCRIPT := timeout
endif

opengl_playground: all
	$(COMPILER) -std=c++11 -I$(SRCDIR) -I$(PUGIXML_INCLUDE_DIR) $(OBJECTS) $(LIBRARIES) $(LOCAL_LIBRARIES) $(APP_DIR)/opengl_playground.$(SRCEXT) -o opengl_playground

all: $(OBJDIR) $(SOURCES) $(OBJECTS)

$(OBJDIR):
	@ mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	$(COMPILER) $(COMPILER_FLAGS) -I$(SRCDIR) -I$(PUGIXML_INCLUDE_DIR) $< -o $@


# Unit Tests
$(OBJDIR)/all_tests.o : $(TEST_SRC)
	$(COMPILER) $(COMPILER_FLAGS) -I $(GOOGLE_TEST_INCLUDE_DIR) -I$(GOOGLE_MOCK_INCLUDE_DIR) -I$(SRCDIR) $< -o $@

all_tests: $(OBJECTS) $(OBJDIR)/all_tests.o
	$(COMPILER) $^ $(LIBRARIES) -L $(LIBRARY_DIR)/ -l gtest -l gmock $(LOCAL_LIBRARIES) -o $@

discard:
	@ git clean -df
	@ git checkout -- .

clean:
	rm -f $(OBJDIR)/*.o
	rm -f *.o

dependencies: $(LIBRARY_DIR) google-test google-mock pugixml

$(LIBRARY_DIR):
	@ mkdir -p $(LIBRARY_DIR)

google-test:
	g++ -I$(GOOGLE_TEST_INCLUDE_DIR) -I$(GOOGLE_TEST_DIR) -c $(GOOGLE_TEST_SRC_DIR)/gtest-all.cc
	@ ar -rv $(LIBRARY_DIR)/libgtest.a gtest-all.o
	@ rm gtest-all.o

google-mock:
	g++ -I$(GOOGLE_MOCK_INCLUDE_DIR) -I$(GOOGLE_MOCK_DIR) -I$(GOOGLE_TEST_INCLUDE_DIR) -c $(GOOGLE_MOCK_SRC_DIR)/gmock-all.cc
	@ ar -rv $(LIBRARY_DIR)/libgmock.a gmock-all.o
	@ rm gmock-all.o

pugixml:
	g++ -I$(PUGIXML_INCLUDE_DIR) -c $(PUGIXML_DIR)/pugixml.cpp
	@ ar -rv $(LIBRARY_DIR)/libpugixml.a pugixml.o
	@ rm pugixml.o

configure-linux:
	@ sudo apt-get install libglew-dev libglm-dev libsdl2-dev curl nmap libjsoncpp-dev
	@ wget http://www.lonesock.net/files/soil.zip
	@ unzip soil.zip -d soil
	@ rm soil.zip
	@ rm soil/Simple\ OpenGL\ Image\ Library/lib/libSOIL.a
	@ mkdir soil/Simple\ OpenGL\ Image\ Library/projects/makefile/obj
	@ cd soil/Simple\ OpenGL\ Image\ Library/projects/makefile && make && sudo make install
	@ rm -r soil
