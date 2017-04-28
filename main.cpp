#include "functions.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
using std::cin;
using std::cout;
using std::endl;
extern const int WIDTH=1440;
extern const int HEIGHT=900;
extern int hp;
extern int points;
int Ship::width;
int Ship::height;
int main()
{
    srand(time(NULL));
    hp=1;
    points=0;
    Ship *ship=new Ship;
    Enemy *e=new Enemy[10];
    placeEnemies(e);
    sf::RenderWindow win(sf::VideoMode(WIDTH,HEIGHT),"galaganatron");
    sf::Texture shipTex;
    if(!shipTex.loadFromFile("ship.png")) return 1;
    sf::Sprite shipSpr(shipTex);
    Ship::width=shipTex.getSize().x;
    Ship::height=shipTex.getSize().y;
    sf::Texture bkgrTex;
    if(!bkgrTex.loadFromFile("background.png")) return 1;
    sf::Sprite bkgrSpr(bkgrTex);

    ship->setX(WIDTH/2);
    ship->setY(HEIGHT-Ship::height-10);
    while(win.isOpen())
    {
        sf::Event event;
        while(win.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                win.close();
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Escape)
                win.close();
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Left)
                ship->move('L');
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Right)
                ship->move('R');
        }
        shipSpr.setPosition(ship->x(),ship->y());
        win.clear(sf::Color(0,120,120));
        win.draw(bkgrSpr);
        win.draw(shipSpr);
        win.display();
    }
    delete ship;
    delete[] e;
    return 0;
}
