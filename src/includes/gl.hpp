// Contains all the includes required to use OpenGL
#define GLEW_STATIC
#include <GL/glew.h>

#if defined __APPLE__ && __MACH__
    #include <OpenGL/OpenGL.h>
#elif defined __gnu_linux__
#endif
