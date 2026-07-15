#include "img.hpp"
#include <iostream>
#include "view/SpriteLoader.hpp"

#include <iostream>
#include <stdexcept>

int main()
{
     try {
        Img image = SpriteLoader::loadPieceIdleSprite("BB");
        image.show();
    } catch (const std::exception& ex) {
        std::cerr << "Failed to load sprite: " << ex.what() << std::endl;
        return 1;
    }
}