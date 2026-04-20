#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "FileDefs.h"
#include "TextureSizes.h"

using namespace sf;
using namespace std::literals;

int main()
{
    VideoMode vm({ 1920, 1080 });
    RenderWindow window(vm, "Timber!"s);

    Texture textureBackground;
    if (!textureBackground.loadFromFile(TimberFiles::backGroundName))
        std::cerr << "Failed to upload file"s << std::endl;

    Sprite spriteBackground(textureBackground);
    spriteBackground.setPosition({ 0, 0 });

    Texture textureTree;
    if (!textureTree.loadFromFile(TimberFiles::treeName))
        std::cerr << "Failed to upload file"s << std::endl;

    Sprite spriteTree(textureTree);
    spriteTree.setPosition({ TS::TREE_HORIZONTAL_POSITION, TS::TREE_VERTICAL_POSITION });

    Texture textureBee;
    if (!textureBee.loadFromFile(TimberFiles::beeName))
        std::cerr << "Failed to upload file"s << std::endl;

    Sprite spriteBee(textureBee);
    spriteBee.setPosition({ TS::BEE_HORIZONTAL_POSITION, TS::BEE_VERTICAL_POSITION });

    bool beeActive{ false };
    float beeSpeed{ 0.0f };

    Texture textureCloud;
    if (!textureCloud.loadFromFile(TimberFiles::cloudName))
        std::cerr << "Failed to upload file"s << std::endl;

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

    Clock clock;

    RectangleShape timeBar;
    float timeBarStartWidth{ 400.f };
    float timeBarHeight{ 80.f };
    timeBar.setSize({ timeBarStartWidth, timeBarHeight });
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition({ (1920 / 2) - timeBarStartWidth / 2, 980 });

    Time gameTimeTotal;
    float timeRemaining{ 6.0f };
    float timeBarWidthPerSecond{ timeBarStartWidth / timeRemaining };

    bool paused{ true };

    int score{ 0 };

    Font font;
    if (!font.openFromFile(TimberFiles::fontName))
        std::cerr << "Failed to upload file"s << std::endl;

    Text messageText(font, "Press Enter to start!"s, 75);
    Text scoreText(font, "Score = 0"s, 100);

    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin({ textRect.position.x + textRect.size.x / 2.f, textRect.position.y + textRect.size.y / 2.f });
    
    messageText.setPosition({ 1920 / 2.f, 1080 / 2.f });
    scoreText.setPosition({ 20, 20 });

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
            window.close();

        if (Keyboard::isKeyPressed(Keyboard::Key::Enter))
        {
            paused = false;

            score = 0;
            timeRemaining = 6;
        }

        if (!paused)
        {
            Time dt = clock.restart();

            timeRemaining -= dt.asSeconds();
            timeBar.setSize({ timeBarWidthPerSecond * timeRemaining, timeBarHeight });

            if (timeRemaining <= 0.0f)
            {
                paused = true;
                
                messageText.setString("Time's up!"s);

                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin({ textRect.position.x + textRect.size.x / 2.f, textRect.position.y + textRect.size.y / 2.f });
                messageText.setPosition({ 1920 / 2.f, 1080 / 2.f });
            }

            if (!beeActive)
            {
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 200;

                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition({ 2000, height });
                beeActive = true;
            }
            else
            {
                spriteBee.setPosition({ spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y });
                if (spriteBee.getPosition().x < -100)
                    beeActive = false;
            }

            if (!cloud1Active)
            {
                srand((int)time(0) * 10);
                cloud1Speed = (rand() % 200);

                srand((int)time(0) * 10);
                float height = (rand() % 150);
                spriteCloud1.setPosition({ -200, height });
                cloud1Active = true;
            }
            else
            {
                spriteCloud1.setPosition({ spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y });
                if (spriteCloud1.getPosition().x > 1920)
                    cloud1Active = false;
            }

            if (!cloud2Active)
            {
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);

                srand((int)time(0) * 20);
                float height = (rand() % 300) - 150;
                spriteCloud2.setPosition({ -200, height });
                cloud2Active = true;
            }
            else
            {
                spriteCloud2.setPosition({ spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y });
                if (spriteCloud2.getPosition().x > 1920)
                    cloud2Active = false;
            }

            if (!cloud3Active)
            {
                srand((int)time(0) * 30);
                cloud3Speed = (rand() % 200);

                srand((int)time(0) * 30);
                float height = (rand() % 450) - 150;
                spriteCloud3.setPosition({ -200, height });
                cloud3Active = true;
            }
            else
            {
                spriteCloud3.setPosition({ spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y });
                if (spriteCloud3.getPosition().x > 1920)
                    cloud3Active = false;
            }

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());
        }

        window.clear();

        window.draw(spriteBackground);

        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        window.draw(spriteTree);
        
        window.draw(spriteBee);

        window.draw(scoreText);

        window.draw(timeBar);

        if (paused)
            window.draw(messageText);

        window.display();
    }

    return 0;
}
