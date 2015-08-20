#include "gtest/gtest.h"

#include <iostream>
#include <cmath>
#include "includes/gl.hpp"

#include "Viewport.hpp"
#include "Window.hpp"
#include "Mouse.hpp"
#include "Camera.hpp"
#include "OpenGLContext.hpp"
#include "ShaderFile.hpp"
#include "VertexShaderCreator.hpp"
#include "FragmentShaderCreator.hpp"
#include "ShaderProgram.hpp"

///////////////////////////////
// Camera Tests
///////////////////////////////
class CameraTest : public ::testing::Test {
protected:
    CameraTest() : viewport(1600, 900) {

    }

    Viewport viewport;
};

TEST_F(CameraTest, constructorTest) {
    Camera camera(viewport, 45.0f, 0.1, 500.0f);

    EXPECT_EQ(camera.getPosition(), glm::vec3(0, 0, 0));
    EXPECT_EQ(camera.getRotationInLocalCoordinates(), glm::vec3(0, 0, 0));

}

TEST_F(CameraTest, moveByGlobalTest1) {
    Camera camera(viewport, 45.0f, 0.1, 500.0f);

    glm::vec3 start_position = glm::vec3(0, 0, 0);
    camera.setPosition(start_position);

    glm::vec3 move_amount = glm::vec3(1, 0, 52);
    camera.moveByGlobal(move_amount);

    EXPECT_EQ(camera.getPosition(), start_position + move_amount);
}

TEST_F(CameraTest, moveByGlobalTest2) {
    Camera camera(viewport, 45.0f, 0.1, 500.0f);

    glm::vec3 start_position = glm::vec3(10, -50, 32);
    camera.setPosition(start_position);

    glm::vec3 move_amount = glm::vec3(-40, 0, 52);
    camera.moveByGlobal(move_amount);

    EXPECT_EQ(camera.getPosition(), start_position + move_amount);
}

TEST_F(CameraTest, moveByLocalTest) {
    Camera camera(viewport, 45.0f, 0.1, 500.0f);

    camera.moveByLocal(glm::vec3(0, 0, -1));
    glm::vec3 camera_position = camera.getPosition();
    EXPECT_NEAR(camera_position.x, 0, 0.001);
    EXPECT_NEAR(camera_position.y, 0, 0.001);
    EXPECT_NEAR(camera_position.z, -1, 0.001);

    camera.rotateByLocal(glm::vec3(0, -M_PI / 2.0, 0));
    camera.moveByLocal(glm::vec3(0, 0, -1));
    camera_position = camera.getPosition();
    EXPECT_NEAR(camera_position.x, 1, 0.001);
    EXPECT_NEAR(camera_position.y, 0, 0.001);
    EXPECT_NEAR(camera_position.z, -1, 0.001);

    camera.rotateByLocal(glm::vec3(-M_PI / 2.0, 0, 0));
    camera.moveByLocal(glm::vec3(0, 1, 0));
    camera_position = camera.getPosition();
    EXPECT_NEAR(camera_position.x, 0, 0.001);
    EXPECT_NEAR(camera_position.y, 0, 0.001);
    EXPECT_NEAR(camera_position.z, -1, 0.001);

    camera.rotateByLocal(glm::vec3(0, 0, M_PI));
    camera.moveByLocal(glm::vec3(1, 0, 0));
    camera_position = camera.getPosition();
    EXPECT_NEAR(camera_position.x, 0, 0.001);
    EXPECT_NEAR(camera_position.y, 0, 0.001);
    EXPECT_NEAR(camera_position.z, 0, 0.001);

}

TEST_F(CameraTest, rotateByLocalTest) {
    Camera camera(viewport, 45.0f, 0.1, 500.0f);

    camera.rotateByLocal(glm::vec3(1, 2, 0));
    EXPECT_EQ(camera.getRotationInLocalCoordinates(), glm::vec3(1, 2, 0));

    camera.rotateByLocal(glm::vec3(-1, 0, 1.5));
    EXPECT_EQ(camera.getRotationInLocalCoordinates(), glm::vec3(0, 2, 1.5));

    camera.rotateByLocal(glm::vec3(0, -2, -1.5));
    EXPECT_EQ(camera.getRotationInLocalCoordinates(), glm::vec3(0, 0, 0));

}

TEST_F(CameraTest, getProjectionMatrixTest) {
    float field_of_view = 45.0f;
    float near_clip = 0.1f;
    float far_clip = 500.0f;
    Camera camera(viewport, field_of_view, near_clip, far_clip);

    EXPECT_EQ(camera.getProjectionMatrix(), glm::perspective(field_of_view, viewport.getAspectRatio(), near_clip, far_clip));

}

///////////////////////////////
// Drawable Tests
///////////////////////////////
class DrawableTest : public ::testing::Test {
protected:
    DrawableTest() {

    }
};

///////////////////////////////
// Mesh Tests
///////////////////////////////
class MeshTest : public ::testing::Test {
protected:
    MeshTest() {

    }
};

///////////////////////////////
// Mouse Tests
///////////////////////////////
class MouseTest : public ::testing::Test {
protected:
    MouseTest() {

    }
};

TEST_F(MouseTest, hideTest) {
    Mouse mouse;
    mouse.hide();
    EXPECT_EQ(mouse.isHidden(), true);
}

TEST_F(MouseTest, showTest) {
    Mouse mouse;
    mouse.show();
    EXPECT_EQ(mouse.isHidden(), false);
}

TEST_F(MouseTest, toggleVisibilityTest) {
    Mouse mouse;
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

    Mouse mouse;
    mouse.centerInWindow(window);
    EXPECT_EQ(mouse.getPosition(), viewport.getCenter());
}

TEST_F(MouseTest, setPositionInWindowTest) {
    Viewport viewport(1600, 900);
    Window window(viewport, false);

    Mouse mouse;
    mouse.setPositionInWindow(window, glm::vec2(100, 100));
    EXPECT_EQ(mouse.getPosition(), glm::vec2(100, 100));
}

///////////////////////////////
// OpenGLContext Tests
///////////////////////////////
class OpenGLContextTest : public ::testing::Test {
protected:
    OpenGLContextTest() : viewport(1600, 900), window(viewport, false) {

    }

    Viewport viewport;
    Window window;
};

///////////////////////////////
// ShaderFile Tests
///////////////////////////////
class ShaderFileTest : public ::testing::Test {
protected:
    ShaderFileTest() : viewport(1600, 900), window(viewport, false), open_gl_context(4, 1, window) {

    }

    Viewport viewport;
    Window window;

    OpenGLContext open_gl_context;

    VertexShaderCreator vertex_shader_creator;
    FragmentShaderCreator fragment_shader_creator;
};

TEST_F(ShaderFileTest, hasErrorsTest) {

    ShaderFile vertex_shader_with_errors("tests/shaders/test_errors.vs", vertex_shader_creator);

    EXPECT_EQ(vertex_shader_with_errors.hasErrors(), true);

    ShaderFile fragment_shader_with_errors("tests/shaders/test_errors.fs", fragment_shader_creator);

    EXPECT_EQ(fragment_shader_with_errors.hasErrors(), true);

    ShaderFile vertex_shader_okay("tests/shaders/test_okay.vs", vertex_shader_creator);

    EXPECT_EQ(vertex_shader_okay.hasErrors(), false);

    ShaderFile fragment_shader_okay("tests/shaders/test_okay.fs", fragment_shader_creator);

    EXPECT_EQ(fragment_shader_okay.hasErrors(), false);

}

///////////////////////////////
// ShaderProgram Tests
///////////////////////////////
class ShaderProgramTest : public ::testing::Test {
protected:
    ShaderProgramTest() : viewport(1600, 900), window(viewport, false), open_gl_context(4, 1, window)  {

    }

    Viewport viewport;
    Window window;

    OpenGLContext open_gl_context;

    VertexShaderCreator vertex_shader_creator;
    FragmentShaderCreator fragment_shader_creator;
};

TEST_F(ShaderProgramTest, getUniformLocationTest) {
    ShaderFile vertex_shader("tests/shaders/test_okay.vs", vertex_shader_creator);
    ShaderFile fragment_shader("tests/shaders/test_okay.fs", fragment_shader_creator);

    ShaderProgram shader_program(vertex_shader, fragment_shader);

    EXPECT_NE(shader_program.getUniformLocation("model"), -1);
    EXPECT_NE(shader_program.getUniformLocation("view"), -1);
    EXPECT_NE(shader_program.getUniformLocation("proj"), -1);

}

TEST_F(ShaderProgramTest, getAttributeLocationTest) {

    ShaderFile vertex_shader("tests/shaders/test_okay.vs", vertex_shader_creator);
    ShaderFile fragment_shader("tests/shaders/test_okay.fs", fragment_shader_creator);

    ShaderProgram shader_program(vertex_shader, fragment_shader);

    EXPECT_EQ(shader_program.getAttributeLocation("position"), 1);
    EXPECT_EQ(shader_program.getAttributeLocation("normal"), 2);
    EXPECT_EQ(shader_program.getAttributeLocation("texture_coordinate"), 3);

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

TEST(ViewportTest, getAspectRatioTest) {
    Viewport viewport(1600, 900);
    EXPECT_NEAR(viewport.getAspectRatio(), 1.778, 0.01);

    viewport = Viewport(800, 600);
    EXPECT_NEAR(viewport.getAspectRatio(), 1.333, 0.01);
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
