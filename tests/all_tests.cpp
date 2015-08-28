#include "gtest/gtest.h"

#include <iostream>
#include <cmath>
#include <memory>
#include "includes/gl.hpp"
#include "includes/sdl.hpp"
#include "includes/glm.hpp"

#include "Viewport.hpp"
#include "Window.hpp"
#include "Mouse.hpp"
#include "Camera.hpp"
#include "OpenGLContext.hpp"
#include "ShaderFile.hpp"
#include "VertexShaderCreator.hpp"
#include "FragmentShaderCreator.hpp"
#include "ShaderProgram.hpp"
#include "Unit.hpp"
#include "Transform3D.hpp"

///////////////////////////////
// Camera Tests
///////////////////////////////
class CameraTest : public ::testing::Test {
protected:
    CameraTest() : viewport(1600, 900) {
        field_of_view = 45.0f;
        near_clip = 1.0f;
        far_clip = 1000.0f;
    }

    float field_of_view;
    float near_clip;
    float far_clip;
    Viewport viewport;
};

TEST_F(CameraTest, getProjectionMatrixTest) {
    Camera camera(viewport, Transform3D(), field_of_view, near_clip, far_clip);

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

};

TEST_F(ShaderFileTest, hasErrorsTest) {

    ShaderFile vertex_shader_with_errors("tests/shaders/test_errors.vs", make_unique<VertexShaderCreator>());

    EXPECT_EQ(vertex_shader_with_errors.hasErrors(), true);

    ShaderFile fragment_shader_with_errors("tests/shaders/test_errors.fs", make_unique<FragmentShaderCreator>());

    EXPECT_EQ(fragment_shader_with_errors.hasErrors(), true);

    ShaderFile vertex_shader_okay("tests/shaders/test_okay.vs", make_unique<VertexShaderCreator>());

    EXPECT_EQ(vertex_shader_okay.hasErrors(), false);

    ShaderFile fragment_shader_okay("tests/shaders/test_okay.fs", make_unique<FragmentShaderCreator>());

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

};

TEST_F(ShaderProgramTest, getUniformLocationTest) {
    ShaderFile vertex_shader("tests/shaders/test_okay.vs", make_unique<VertexShaderCreator>());
    ShaderFile fragment_shader("tests/shaders/test_okay.fs", make_unique<FragmentShaderCreator>());

    ShaderProgram shader_program(vertex_shader, fragment_shader);

    EXPECT_NE(shader_program.getUniformLocation("model"), -1);
    EXPECT_NE(shader_program.getUniformLocation("view"), -1);
    EXPECT_NE(shader_program.getUniformLocation("proj"), -1);

}

TEST_F(ShaderProgramTest, getAttributeLocationTest) {

    ShaderFile vertex_shader("tests/shaders/test_okay.vs", make_unique<VertexShaderCreator>());
    ShaderFile fragment_shader("tests/shaders/test_okay.fs", make_unique<FragmentShaderCreator>());

    ShaderProgram shader_program(vertex_shader, fragment_shader);

    EXPECT_EQ(shader_program.getAttributeLocation("position"), 1);
    EXPECT_EQ(shader_program.getAttributeLocation("normal"), 2);
    EXPECT_EQ(shader_program.getAttributeLocation("texture_coordinate"), 3);

}

///////////////////////////////
// Transform3D Tests
///////////////////////////////
class Transform3DTest : public ::testing::Test {
protected:
    Transform3DTest() {

    }
};

TEST_F(Transform3DTest, constructorTest) {
    Transform3D transform_3D;

    EXPECT_EQ(transform_3D.getPosition(), glm::vec3(0, 0, 0));
    EXPECT_EQ(transform_3D.getScale(), glm::vec3(1, 1, 1));
}

TEST_F(Transform3DTest, moveByGlobalTest1) {
    Transform3D transform_3D;

    glm::vec3 start_position = glm::vec3(0, 0, 0);
    transform_3D.setPosition(start_position);

    glm::vec3 move_amount = glm::vec3(1, 0, 52);
    transform_3D.moveByGlobal(move_amount);

    EXPECT_EQ(transform_3D.getPosition(), glm::vec3(1, 0, 52));

}

TEST_F(Transform3DTest, moveByGlobalTest2) {
    Transform3D transform_3D;

    glm::vec3 start_position = glm::vec3(10, -50, 32);
    transform_3D.setPosition(start_position);

    glm::vec3 move_amount = glm::vec3(-40, 0, 52);
    transform_3D.moveByGlobal(move_amount);

    EXPECT_EQ(transform_3D.getPosition(), glm::vec3(-30, -50, 84));
}

TEST_F(Transform3DTest, moveByLocalTest1) {
    Transform3D transform_3D;

    transform_3D.moveByLocal(glm::vec3(1, 0, 0));
    glm::vec3 transform_3D_position = transform_3D.getPosition();
    EXPECT_NEAR(transform_3D_position.x, 1, 0.001);
    EXPECT_NEAR(transform_3D_position.y, 0, 0.001);
    EXPECT_NEAR(transform_3D_position.z, 0, 0.001);

    transform_3D.rotateByGlobal(glm::vec3(0, -M_PI / 2.0, 0));
    transform_3D.moveByLocal(glm::vec3(-1, 0, 0));
    transform_3D_position = transform_3D.getPosition();
    EXPECT_NEAR(transform_3D_position.x, 1, 0.001);
    EXPECT_NEAR(transform_3D_position.y, 0, 0.001);
    EXPECT_NEAR(transform_3D_position.z, -1, 0.001);
}

TEST_F(Transform3DTest, moveByLocalTest2) {
    Transform3D transform_3D;

    transform_3D.moveByLocal(glm::vec3(0, 1, 0));
    glm::vec3 transform_3D_position = transform_3D.getPosition();
    EXPECT_NEAR(transform_3D_position.x, 0, 0.001);
    EXPECT_NEAR(transform_3D_position.y, 1, 0.001);
    EXPECT_NEAR(transform_3D_position.z, 0, 0.001);

    transform_3D.rotateByGlobal(glm::vec3(0, -M_PI / 2.0, 0));
    transform_3D.moveByLocal(glm::vec3(0, -1, 0));
    transform_3D_position = transform_3D.getPosition();
    EXPECT_NEAR(transform_3D_position.x, 0, 0.001);
    EXPECT_NEAR(transform_3D_position.y, 0, 0.001);
    EXPECT_NEAR(transform_3D_position.z, 0, 0.001);

    transform_3D.rotateByGlobal(glm::vec3(0, 0, -M_PI / 2.0));
    transform_3D.moveByLocal(glm::vec3(0, 1, 0));
    transform_3D_position = transform_3D.getPosition();
    EXPECT_NEAR(transform_3D_position.x, 1, 0.001);
    EXPECT_NEAR(transform_3D_position.y, 0, 0.001);
    EXPECT_NEAR(transform_3D_position.z, 0, 0.001);

}

TEST_F(Transform3DTest, moveByLocalTest3) {
    Transform3D transform_3D;

    transform_3D.moveByLocal(glm::vec3(0, 0, -1));
    glm::vec3 transform_3D_position = transform_3D.getPosition();
    EXPECT_NEAR(transform_3D_position.x, 0, 0.001);
    EXPECT_NEAR(transform_3D_position.y, 0, 0.001);
    EXPECT_NEAR(transform_3D_position.z, -1, 0.001);

    transform_3D.rotateByGlobal(glm::vec3(0, -M_PI / 2.0, 0));
    transform_3D.moveByLocal(glm::vec3(0, 0, 1));
    transform_3D_position = transform_3D.getPosition();
    EXPECT_NEAR(transform_3D_position.x, -1, 0.001);
    EXPECT_NEAR(transform_3D_position.y, 0, 0.001);
    EXPECT_NEAR(transform_3D_position.z, -1, 0.001);

}

TEST_F(Transform3DTest, moveByLocalTest4) {
    Transform3D transform;
    transform.moveByLocal(glm::vec3(0, 0, 1));
    glm::vec3 transform_position = transform.getPosition();
    EXPECT_NEAR(transform_position.x, 0, 0.001);
    EXPECT_NEAR(transform_position.y, 0, 0.001);
    EXPECT_NEAR(transform_position.z, 1, 0.001);

    transform.rotateByLocal(glm::vec3(0, M_PI / 2.0, 0));
    transform.moveByLocal(glm::vec3(0, 0, -1));
    transform_position = transform.getPosition();
    EXPECT_NEAR(transform_position.x, -1, 0.001);
    EXPECT_NEAR(transform_position.y, 0, 0.001);
    EXPECT_NEAR(transform_position.z, 1, 0.001);

    transform.rotateByLocal(glm::vec3(M_PI / 2.0, 0, 0));
    transform.moveByLocal(glm::vec3(0, -1, 0));
    transform_position = transform.getPosition();
    EXPECT_NEAR(transform_position.x, -2, 0.001);
    EXPECT_NEAR(transform_position.y, 0, 0.001);
    EXPECT_NEAR(transform_position.z, 1, 0.001);

    transform.rotateByLocal(glm::vec3(0, 0, M_PI / 2.0));
    transform.moveByLocal(glm::vec3(2, -1, 0));
    transform_position = transform.getPosition();
    EXPECT_NEAR(transform_position.x, 0, 0.001);
    EXPECT_NEAR(transform_position.y, 0, 0.001);
    EXPECT_NEAR(transform_position.z, 0, 0.001);

}

///////////////////////////////
// Unit Tests (lol)
///////////////////////////////
class UnitTest : public ::testing::Test {
protected:
    UnitTest() {

    }

};

TEST_F(UnitTest, constructorTest) {
    Unit jimmy(Transform3D(), 200, 7);

    EXPECT_EQ(jimmy.getHealth(), 200);
    EXPECT_EQ(jimmy.getMaxHealth(), 200);
}

TEST_F(UnitTest, takeDamageTest) {
    Unit jimmy(Transform3D(), 100, 7);

    jimmy.takeDamage(24);
    EXPECT_EQ(jimmy.getHealth(), 76);

    jimmy.takeDamage(100);
    EXPECT_EQ(jimmy.getHealth(), 0);
}

TEST_F(UnitTest, healForTest) {
    Unit jimmy(Transform3D(), 100, 7);

    jimmy.takeDamage(82);
    jimmy.healFor(12);
    EXPECT_EQ(jimmy.getHealth(), 30);

    jimmy.healFor(500);
    EXPECT_EQ(jimmy.getHealth(), 100);

}

TEST_F(UnitTest, dieTest) {
    Unit jimmy(Transform3D(), 100, 7);
    jimmy.die();

    EXPECT_EQ(jimmy.getHealth(), 0);
}

TEST_F(UnitTest, isDeadTest) {
    Unit jimmy(Transform3D(), 100, 7);

    EXPECT_EQ(jimmy.isDead(), false);

    jimmy.takeDamage(120);
    // :(
    EXPECT_EQ(jimmy.isDead(), true);

    Unit already_dead(Transform3D(), -2000, 0);
    EXPECT_EQ(already_dead.isDead(), true);
}

TEST_F(UnitTest, attackTest) {
    Unit jimmy(Transform3D(), 200, 7);
    Unit zeratul(Transform3D(), 50, 1);

    jimmy.attack(zeratul, 20);
    EXPECT_EQ(zeratul.getHealth(), 30);

    zeratul.attack(jimmy, 150);
    EXPECT_EQ(jimmy.getHealth(), 50);
}

TEST_F(UnitTest, healTest) {
    Unit uther(Transform3D(), 180, 1);
    Unit tychus(Transform3D(), 200, 5);

    tychus.takeDamage(90);
    uther.heal(tychus, 40);
    EXPECT_EQ(tychus.getHealth(), 150);

    uther.heal(tychus, 100);
    EXPECT_EQ(tychus.getHealth(), 200);

}

TEST_F(UnitTest, isInAttackRangeTest) {
    double uther_attack_range = 1.0;
    Unit uther(Transform3D(), 180, uther_attack_range);
    uther.getTransform3D().setPosition(glm::vec3(0, 0, 0));

    double tychus_attack_range = 5.0;
    Unit tychus(Transform3D(), 200, tychus_attack_range);
    tychus.getTransform3D().setPosition(glm::vec3(2, 0, 0));

    double jimmy_attack_range = 7.0;
    Unit jimmy(Transform3D(), 200, jimmy_attack_range);
    jimmy.getTransform3D().setPosition(glm::vec3(1, 0, -5));

    EXPECT_EQ(uther.isInAttackRange(tychus), false);
    EXPECT_EQ(uther.isInAttackRange(jimmy), false);
    EXPECT_EQ(tychus.isInAttackRange(uther), true);
    EXPECT_EQ(tychus.isInAttackRange(jimmy), false);
    EXPECT_EQ(jimmy.isInAttackRange(uther), true);
    EXPECT_EQ(jimmy.isInAttackRange(tychus), true);

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
