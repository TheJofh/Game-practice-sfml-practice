#include <iostream>
#include <thread>
#include "Player.h"
#include "Enemy.h"
#include "SFML/Graphics.hpp"

bool closed = false;
int score = 0;
sf::Font font;

sf::RenderWindow window(sf::VideoMode(1920, 1080), "Client",sf::Style::Fullscreen);
sf::Text text;
sf::Event e;
sf::Time timePerFrame = sf::seconds(1.0f/165.0f);
sf::CircleShape shape(50.0f);
sf::CircleShape enemy(50.0f);

sf::Vector2f enemyPos = enemy.getPosition();
sf::Vector2i windowPos = window.getPosition();

int windowXPos = windowPos.x;
int windowYPos = windowPos.y;

unsigned int frames = 0;

struct Button
{
    sf::Color color;
    float size;
    sf::Vector2f pos;
    

    Button(sf::Vector2f pos, float size, sf::Color color): pos(pos), size(size), color(color)  {}


    void draw(sf::RenderWindow& window)
    {
        sf::CircleShape buttonShape(size);
        buttonShape.setFillColor(color);
        buttonShape.setPosition(pos);
        buttonShape.setOrigin(size, size);

        window.draw(buttonShape);
        
    }
    bool isClicked(sf::Vector2f mousePos)
    {
        float distance = std::sqrt(std::pow(mousePos.x - pos.x, 2) + std::pow(mousePos.y - pos.y, 2));
        return distance <= size;
    }
};



void Movement();
void GameWindow();
void collide();
void MenuScene();

int main()
{
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cout << "ah shit" << std::endl;
    }
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::Cyan);
    text.setPosition(10.f, 10.f);
    text.setFont(font);
    


    shape.setFillColor(sf::Color::Red);
    enemy.setFillColor(sf::Color::Blue);
    enemy.setPosition(600, 400);
    
    

    MenuScene();
 
    return 0;
}
void GameWindow()
{
    sf::Clock clock;
    sf::Time elapsedTime = clock.restart();

    while (window.isOpen())
    {
        closed = false;
        window.getPosition();
        window.display();
        Movement();
        //std::string scoreString;
        //scoreString = std::to_string(score);
        //text.setString(scoreString);

        // Event handling
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                std::cout << "You closed window" << std::endl;
                closed = true;
                window.close();
            }
            

        }
       
        collide();
        // Draw shape
        window.clear();
        window.draw(shape);
        window.draw(enemy);
        window.draw(text);
        
        elapsedTime += clock.restart();
        ++frames;
        if (elapsedTime >= sf::seconds(1.0f)) {
            float fps = frames / elapsedTime.asSeconds();
            std::string thefps = std::to_string(fps);
            text.setString(thefps);

            elapsedTime = sf::Time::Zero;
            frames = 0;
        }
        
        
        sf::Time sleepTime = timePerFrame - elapsedTime;
        if (sleepTime < sf::Time::Zero)
        {
            sf::sleep(sleepTime);
        }
        
    }

}
void Movement()
{
    

        sf::Vector2i localPosition = sf::Mouse::getPosition();
        float playerXPos = localPosition.x;
        float playerYPos = localPosition.y;

        

        

        // Define a velocity for smoother movement
        float velocity = 0.1f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            shape.move(0.f, -velocity);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            shape.move(-velocity, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            shape.move(0.f, velocity);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            shape.move(velocity, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
    
}

void collide()
{

    sf::FloatRect shapeHitBox = shape.getGlobalBounds();
    sf::FloatRect EnemyHitBox = enemy.getGlobalBounds();
    float randomPosX = rand() % 1780 - 1;
    float randomPosY = rand() % 980 - 1;
    sf::Vector2f {randomPosX, randomPosY};
   
    if (shapeHitBox.intersects(EnemyHitBox))
    {
        enemy.setPosition(randomPosX,randomPosY);
        score += 100;
        std::cout << "ENEMY HIT" << std::endl;
    }
}

void MenuScene()
{
    sf::Clock clock;
    sf::Time firstElapsedTime = clock.restart();
    bool startGame = false;
    Button startButton(sf::Vector2f(600, 600), 50.0f, sf::Color::White);
    if (startGame)
    {
        startButton.color = sf::Color::Transparent;

    }
    while (window.isOpen() && startGame == false)
    {
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }

            if (e.type == sf::Event::MouseButtonPressed)
            {
                if (e.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos(sf::Mouse::getPosition(window));
                    if (startButton.isClicked(mousePos))
                    
                    {
                        startGame = true;
                        GameWindow();
                    }
                }
            }
           
            
           
            window.clear();
            startButton.draw(window);
            window.display();
            sf::Time sleepTime = timePerFrame - firstElapsedTime;
            if (sleepTime < sf::Time::Zero)
            {
                sf::sleep(sleepTime);
            }
            window.clear();
        }

       
    }
}