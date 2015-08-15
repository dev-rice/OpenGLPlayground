#include "gtest/gtest.h"

#include "Window.hpp"
#include "Mouse.hpp"

class MouseTest : public ::testing::Test {
public:
    MouseTest() : window(1600, 900, false), mouse(window) {

    }
protected:
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
