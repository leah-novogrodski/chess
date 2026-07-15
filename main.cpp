#include "img.hpp"
#include <iostream>

int main()
{
    try
    {
        std::cout << "Testing Img class..." << std::endl;
        Img img;
        img.read(R"(..\..\board.png)", {640, 480}, true);
        img.show();

        std::cout << "Img class test completed successfully!" << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}