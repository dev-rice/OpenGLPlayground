#include "gtest/gtest.h"

#include "Window.hpp"
#include "Mouse.hpp"

TEST(MouseTest, hideTest) {
    Window window(1600, 900, false);
    Mouse mouse(window);
    mouse.hide();
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
