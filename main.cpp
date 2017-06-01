#include "functions.h"
#include <iostream>
using std::cout;
using std::endl;
extern const int WIDTH=1440;
extern const int HEIGHT=900;
int Ship::width;
int Ship::height;
int Bullet::width;
int Bullet::height;
int main()
{

    sf::RenderWindow win(sf::VideoMode(WIDTH,HEIGHT),"galaga");
    Save::number=0;
    sf::Event menuEvent;
    while(win.isOpen())
    {
        std::string indexStr="";
        while(win.pollEvent(menuEvent))
        {
            if(menuEvent.type==sf::Event::Closed)
                win.close();
            if(menuEvent.type==sf::Event::KeyPressed && menuEvent.key.code==sf::Keyboard::Escape)
                win.close();
            if(menuEvent.type==sf::Event::KeyPressed && menuEvent.key.code==sf::Keyboard::N)
            {
                Game game(&win);
                game.play();
            }
            if(menuEvent.type==sf::Event::KeyPressed)
            {
                Game game(&win);
                if(menuEvent.key.code==sf::Keyboard::Num0) game.load("0");
                if(menuEvent.key.code==sf::Keyboard::Num1) game.load("1");
                if(menuEvent.key.code==sf::Keyboard::Num2) game.load("2");
                if(menuEvent.key.code==sf::Keyboard::Num3) game.load("3");
                if(menuEvent.key.code==sf::Keyboard::Num4) game.load("4");
                if(menuEvent.key.code==sf::Keyboard::Num5) game.load("5");
                if(menuEvent.key.code==sf::Keyboard::Num6) game.load("6");
                if(menuEvent.key.code==sf::Keyboard::Num7) game.load("7");
                if(menuEvent.key.code==sf::Keyboard::Num8) game.load("8");
                if(menuEvent.key.code==sf::Keyboard::Num9) game.load("9");
                game.play();
            }
        }//eventy
        win.clear(sf::Color(255,0,0));
        try
        {
            menu(&win);
        }catch(std::string s)
        {
            cout<<s<<endl;
        }
        win.display();
    }//okno otwarte

    return 0;
}
