#include <iostream>

#include <SFML/Graphics.hpp>

#include "FileDefs.h"
#include "TextureSizes.h"

using namespace sf;

int main()
{
    VideoMode vm({ 1920, 1080 });
    RenderWindow window(vm, "Timber!");

    Texture textureBackground;
    if (!textureBackground.loadFromFile(TimberFiles::backGroundName))
        std::cerr << "Failed to upload file" << std::endl;

    Sprite spriteBackground(textureBackground);
    spriteBackground.setPosition({ 0, 0 });

    Texture textureTree;
    if (!textureTree.loadFromFile(TimberFiles::treeName))
        std::cerr << "Failed to upload file" << std::endl;

    Sprite spriteTree(textureTree);
    spriteTree.setPosition({ TS::TREE_HORIZONTAL_POSITION, TS::TREE_VERTICAL_POSITION });

    Texture textureBee;
    if (!textureBee.loadFromFile(TimberFiles::beeName))
        std::cerr << "Failed to upload file" << std::endl;

    Sprite spriteBee(textureBee);
    spriteBee.setPosition({ TS::BEE_HORIZONTAL_POSITION, TS::BEE_VERTICAL_POSITION });

    bool beeActive{ false };
    float beeSpeed{ 0.0f };

    Texture textureCloud;
    if (!textureCloud.loadFromFile(TimberFiles::cloudName))
        std::cerr << "Failed to upload file" << std::endl;

    Sprite spriteCloud1(textureCloud);
    Sprite spriteCloud2(textureCloud);
    Sprite spriteCloud3(textureCloud);

    spriteCloud1.setPosition({ TS::CLOUD1_HORIZONTAL_POSITION, TS::CLOUD1_VERTICAL_POSITION });
    spriteCloud2.setPosition({ TS::CLOUD2_HORIZONTAL_POSITION, TS::CLOUD2_VERTICAL_POSITION });
    spriteCloud3.setPosition({ TS::CLOUD3_HORIZONTAL_POSITION, TS::CLOUD3_VERTICAL_POSITION });

    bool cloud1Active{false};
    bool cloud2Active{false};
    bool cloud3Active{false};

    float cloud1Speed{ 0.0f };
    float cloud2Speed{ 0.0f };
    float cloud3Speed{ 0.0f };

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
            window.close();

        window.clear();

        window.draw(spriteBackground);

        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        window.draw(spriteTree);
        
        window.draw(spriteBee);

        window.display();
    }

    return 0;
}
