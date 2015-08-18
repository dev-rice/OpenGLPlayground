
#include "gtest/gtest.h"

#include <iostream>

#include "Viewport.hpp"
#include "Window.hpp"
#include "Mouse.hpp"

///////////////////////////////
// Camera Tests
///////////////////////////////
class CameraTest : public ::testing::Test {
protected:
    CameraTest() : viewport(1600, 900) {

    }

    Viewport viewport;
};

TEST_F(CameraTest, moveByGlobalTest) {

}

TEST_F(CameraTest, moveByLocalTest) {

}

TEST_F(CameraTest, rotateByLocalTest) {

}

TEST_F(CameraTest, getViewMatrixTest) {

}

TEST_F(CameraTest, getProjectionMatrixTest) {

}

///////////////////////////////
// Drawable Tests
///////////////////////////////
class DrawableTest : public ::testing::Test {
protected:
    DrawableTest() {

    }
};

TEST_F(DrawableTest, drawTest) {

}

///////////////////////////////
// Mesh Tests
///////////////////////////////
class MeshTest : public ::testing::Test {
protected:
    MeshTest() {

    }
};

TEST_F(MeshTest, drawTest) {

}

TEST_F(MeshTest, prepareToBeDrawnTest) {

}

TEST_F(MeshTest, linkToShaderTest) {

}

///////////////////////////////
// Mouse Tests
///////////////////////////////
class MouseTest : public ::testing::Test {
protected:
    MouseTest() {

    }

    Mouse mouse;
};

TEST_F(MouseTest, hideTest) {
    mouse.hide();
    EXPECT_EQ(mouse.isHidden(), true);
}

TEST_F(MouseTest, showTest) {
    mouse.show();
    EXPECT_EQ(mouse.isHidden(), false);
}

TEST_F(MouseTest, toggleVisibilityTest) {
    mouse.hide();
    mouse.toggleVisibility();
    EXPECT_EQ(mouse.isHidden(), false);

    mouse.show();
    mouse.toggleVisibility();
    EXPECT_EQ(mouse.isHidden(), true);
}

TEST_F(MouseTest, centerInWindowTest) {
    Viewport viewport(1600, 900);
    Window window(viewport, false);

    mouse.centerInWindow(window);
    EXPECT_EQ(mouse.getPosition(), viewport.getCenter());
}

TEST_F(MouseTest, setPositionGlobalTest) {

}

TEST_F(MouseTest, setPositionInWindowTest) {

}

///////////////////////////////
// OpenGLContext Tests
///////////////////////////////
class OpenGLContextTest : public ::testing::Test {
protected:
    OpenGLContextTest() {

    }
};

TEST_F(OpenGLContextTest, enableDepthTestTest) {

}

TEST_F(OpenGLContextTest, enableBackfaceCullingTest) {

}

TEST_F(OpenGLContextTest, setupAlphaBlendingTest) {

}

TEST_F(OpenGLContextTest, getRendererStringTest) {

}

TEST_F(OpenGLContextTest, getVersionStringTest) {

}

TEST_F(OpenGLContextTest, getGLSLVersionStringTest) {

}

///////////////////////////////
// ShaderFile Tests
///////////////////////////////
class ShaderFileTest : public ::testing::Test {
protected:
    ShaderFileTest() {

    }
};

TEST_F(ShaderFileTest, attachToTest) {

}

TEST_F(ShaderFileTest, getErrorsTest) {

}

TEST_F(ShaderFileTest, hasErrorsTest) {

}

///////////////////////////////
// ShaderProgram Tests
///////////////////////////////
class ShaderProgramTest : public ::testing::Test {
protected:
    ShaderProgramTest() {

    }
};

TEST_F(ShaderProgramTest, useTest) {

}

TEST_F(ShaderProgramTest, getUniformLocationTest) {

}

///////////////////////////////
// Viewport Tests
///////////////////////////////
TEST(ViewportTest, getCenterTest) {
    Viewport viewport(1600, 900);
    EXPECT_EQ(viewport.getCenter(), glm::vec2(800, 450));

    viewport = Viewport(1920, 1080);
    EXPECT_EQ(viewport.getCenter(), glm::vec2(960, 540));
}

///////////////////////////////
// Window Tests
///////////////////////////////
class WindowTest : public ::testing::Test {
protected:
    WindowTest() : viewport(1600, 900), window(viewport, false) {

    }
    Viewport viewport;
    Window window;
};

TEST_F(WindowTest, displayTest) {

}

TEST_F(WindowTest, closeTest) {

}

TEST_F(WindowTest, clearBuffersTest) {

}

TEST_F(WindowTest, setFullscreenTest) {

}

TEST_F(WindowTest, setVsyncTest) {

}

TEST_F(WindowTest, requestCloseTest) {
    window.requestClose();
    EXPECT_EQ(window.shouldClose(), true);
}

TEST_F(WindowTest, isOpenTest) {
    // No close request was sent, so it should not expect to close, and be open
    EXPECT_EQ(window.isOpen(), true);
}

///////////////////////////////
// Test Execution
///////////////////////////////
int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    int returnValue;

    //Do whatever setup here you will need for your tests here
    //
    //

    returnValue =  RUN_ALL_TESTS();

    //Do Your teardown here if required
    //
    //

    return returnValue;
}
