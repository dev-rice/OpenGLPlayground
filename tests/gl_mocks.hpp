#include "gmock/gmock.h"

#include "includes/gl.hpp"


class MockGL {
public:
    MOCK_METHOD1(Enable, void(GLenum));
};
