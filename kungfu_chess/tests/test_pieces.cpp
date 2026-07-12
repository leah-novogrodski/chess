#include "doctest.h"
#include "model/position.hpp"

TEST_CASE("Position equality") {
    Position a{1, 2};
    Position b{1, 2};
    Position c{2, 2};
    Position d{1, 3};

    CHECK_EQ(a, b);
    CHECK_NE(a, c);
    CHECK_NE(a, d);
}

TEST_CASE("Position readable representation") {
    Position p{3, 4};
    std::ostringstream os;
    os << p;
    CHECK_EQ(os.str(), "Position(3, 4)");
}
