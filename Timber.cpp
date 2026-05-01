#include <iostream>
#include <sstream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "FileDefs.h"
#include "TextureSizes.h"

using namespace sf;
using namespace std::literals;

const int NUM_CLOUDS = 3;
std::vector<Sprite> clouds;
std::vector<bool> cloudsActive{ false, false, false };
std::vector<float> cloudsSpeed{ 0.0f, 0.0f, 0.0f };

void initClouds(Texture& textureCloud);
void placementClouds(Time& dt);

const int NUM_BRANCHES = 6;
std::vector<Sprite> branches;

void initBranches(Texture& textureBranch);
void placementBranches();
void updateBranches(int seed);

enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

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

    initClouds(textureCloud);

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

    Texture textureBranch;
    if (!textureBranch.loadFromFile(TimberFiles::branchName))
        std::cerr << "Failed to upload file"s << std::endl;

    initBranches(textureBranch);

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
                beeSpeed = static_cast<float>((rand() % 200) + 200);

                srand((int)time(0) * 10);
                float height = static_cast<float>((rand() % 500) + 500);
                spriteBee.setPosition({ 2000, height });
                beeActive = true;
            }
            else
            {
                spriteBee.setPosition({ spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y });
                if (spriteBee.getPosition().x < -100)
                    beeActive = false;
            }

            placementClouds(dt);

            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

            placementBranches();
        }

        window.clear();

        window.draw(spriteBackground);

        for (int i = 0; i < NUM_CLOUDS; ++i)
            window.draw(clouds[i]);

        for (int i = 0; i < NUM_BRANCHES; ++i)
            window.draw(branches[i]);

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

void initClouds(Texture& textureCloud)
{
    clouds.reserve(NUM_CLOUDS);

    float cloudHorizontalPosition{ 0 };
    float cloudVerticalPosition{ 0 };

    for (int i = 0; i < NUM_CLOUDS; ++i)
    {
        clouds.emplace_back(textureCloud);
        clouds[i].setPosition({ cloudHorizontalPosition, cloudVerticalPosition });

        cloudVerticalPosition += 250;
    }
}

void placementClouds(Time& dt)
{
    int seeds[]   = { 10, 20, 30 };
    int mods[]    = { 150, 300, 450 };
    int offsets[] = { 0, 150, 150 };

    for (int i = 0; i < NUM_CLOUDS; ++i)
    {
        if (cloudsActive[i])
        {
            clouds[i].setPosition({ clouds[i].getPosition().x + (cloudsSpeed[i] * dt.asSeconds()), clouds[i].getPosition().y });
            if (clouds[i].getPosition().x > 1920)
                cloudsActive[i] = false;
        }
        else
        {
            srand((int)time(0) * seeds[i]);
            cloudsSpeed[i] = static_cast<float>((rand() % 200));

            srand((int)time(0) * seeds[i]);
            float height = static_cast<float>((rand() % mods[i]) - offsets[i]);
            clouds[i].setPosition({ -200, height });
            cloudsActive[i] = true;
        }
    }
}

void initBranches(Texture& textureBranch)
{
    branches.reserve(NUM_BRANCHES);
    for (int i = 0; i < NUM_BRANCHES; ++i)
    {
        branches.emplace_back(textureBranch);
        branches[i].setPosition({ -2000, -2000 });
        branches[i].setOrigin({ 220, 20 });
    }
}

void placementBranches()
{
    for (int i = 0; i < NUM_BRANCHES; ++i)
    {
        float height = i * 150.f;

        switch (branchPositions[i])
        {
        case side::LEFT:
            branches[i].setPosition({ 610, height });
            branches[i].setRotation(degrees(180));
            break;
        case side::RIGHT:
            branches[i].setPosition({ 1330, height });
            branches[i].setRotation(degrees(0));
            break;
        default:
            branches[i].setPosition({ 3000, height });
            break;
        }
    }
}

void updateBranches(int seed)
{
    for (int i = NUM_BRANCHES - 1; i > 0; --i)
        branchPositions[i] = branchPositions[i - 1];

    srand((int)time(0) + seed);
    int r = (rand() % 5);

    switch (r)
    {
    case 0:
        branchPositions[0] = side::LEFT;
        break;
    case 1:
        branchPositions[0] = side::RIGHT;
        break;
    default:
        branchPositions[0] = side::NONE;
        break;
    }
}