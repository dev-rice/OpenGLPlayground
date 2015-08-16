#include "gtest/gtest.h"

#include "Viewport.hpp"
#include "Window.hpp"
#include "Mouse.hpp"

class MouseTest : public ::testing::Test {
protected:
    MouseTest() : viewport(1600, 900), window(viewport, false), mouse(window) {

    }
    Viewport viewport;
    Window window;
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
    EXPECT_EQ(window.shouldClose(), false);
    EXPECT_EQ(window.isOpen(), true);
}

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
