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
extern unsigned int points;
int Ship::width;
int Ship::height;
int Bullet::width;
int Bullet::height;
const int enemyCount=6;
int main()
{
    Enemy::number=0;
    Bullet::number=0;
    srand(time(NULL));
    hp=3;
    points=0;
    Ship *ship=new Ship;
    //Enemy *e=new Enemy[enemyCount];
    std::vector <Bullet*> bulVec;
    std::vector <Bullet*> bulVec2;
    sf::RenderWindow win(sf::VideoMode(WIDTH,HEIGHT),"galaga");

    sf::Font font;
    if(!font.loadFromFile("arial.ttf")) return 1;
    sf::Text hpText;
    hpText.setFont(font);
    sf::Text ptsText;
    ptsText.setFont(font);
    ptsText.setPosition(WIDTH-100,10);

    sf::Texture bkgrTex;
    if(!bkgrTex.loadFromFile("background.png")) return 1;
    sf::Sprite bkgrSpr(bkgrTex);

    sf::Texture shipTex;
    if(!shipTex.loadFromFile("ship.png")) return 2;
    sf::Sprite shipSpr(shipTex);
    Ship::width=shipTex.getSize().x;
    Ship::height=shipTex.getSize().y;

    sf::Texture bulTex;
    if(!bulTex.loadFromFile("bullet.png")) return 3;
    std::vector <sf::Sprite> bulSprVec;
    std::vector <sf::Sprite> bulSprVec2;
    Bullet::width=bulTex.getSize().x;
    Bullet::height=bulTex.getSize().y;

    sf::Texture eneTex;
    if(!eneTex.loadFromFile("enemy.png")) return 4;
    std::vector <Enemy> eneVec;
    for(int i=0; i<enemyCount; i++)
    {
        eneVec.push_back(Enemy());
    }
    std::vector <sf::Sprite> eneSprVec;
    for(int i=0; i<enemyCount; i++)
    {
        eneSprVec.push_back(sf::Sprite(eneTex));
    }
    placeEnemies(eneVec);

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
            if(event.type==sf::Event::KeyReleased && event.key.code==sf::Keyboard::Space)
            {
                Bullet* b=new Bullet(ship);
                bulVec.push_back(b);
                bulSprVec.push_back(sf::Sprite(bulTex));
            }
        }//eventy
        shipSpr.setPosition(ship->x(),ship->y());
        std::vector <Enemy>::iterator eneI=eneVec.begin();
        std::vector <sf::Sprite>::iterator eneSprI=eneSprVec.begin();
        while(eneI!=eneVec.end())
        {
            eneSprI->setPosition(eneI->x(),eneI->y());
            eneI++;
            eneSprI++;
        }
        eneI=eneVec.begin();

        std::vector <Bullet*>::iterator bulI=bulVec.begin();
        std::vector <sf::Sprite>::iterator bulSprI=bulSprVec.begin();
        for(eneI=eneVec.begin();eneI!=eneVec.end();eneI++)
        {
            if(eneI->ifShoot() && eneI->active)
            {
                cout<<"Strzał"<<endl;
                Bullet s(&*eneI);
                bulVec2.push_back(&s);
                bulSprVec2.push_back(sf::Sprite(bulTex));
            }
        }
        for(; bulI!=bulVec.end(); bulI++,bulSprI++)
        {
            (*bulI)->move('U');
            bulSprI->setPosition((*bulI)->x(),(*bulI)->y());
        }//bullet pętla
        for(bulI=bulVec2.begin(), bulSprI=bulSprVec2.begin(); bulI!=bulVec2.end(); bulI++, bulSprI++)
        {
            (*bulI)->move('D');
            bulSprI->setPosition((*bulI)->x(),(*bulI)->y());
        }

        moveEnemies(eneVec);
        lookForHits(bulVec,eneVec);
        lookForHits(ship, bulVec2);
        win.clear(sf::Color(0,120,120));//potrzebne to?
        win.draw(bkgrSpr);
        win.draw(shipSpr);
        for(eneSprI=eneSprVec.begin(),eneI=eneVec.begin(); eneSprI!=eneSprVec.end(); eneSprI++,eneI++)
        {
            eneSprI->setPosition(eneI->x(),eneI->y());
            if(eneI->active) win.draw(*eneSprI);
        }//to jest dobre
        for(bulI=bulVec.begin(), bulSprI=bulSprVec.begin(); bulI!=bulVec.end(); bulI++, bulSprI++)
            if((*bulI)->active)
                win.draw(*bulSprI);
        for(bulI=bulVec2.begin(), bulSprI=bulSprVec2.begin(); bulI!=bulVec2.end(); bulI++, bulSprI++)
            if((*bulI)->active) win.draw(*bulSprI);

        hpText.setString("HP: "+std::to_string(hp));
        ptsText.setString("PTS: "+std::to_string(points));
        if(hp==0) win.close();
        if(points==enemyCount && eneVec.begin()->active==0)
        {
            for(eneI=eneVec.begin();eneI!=eneVec.end();eneI++)
                eneI->active=1;
            hp++;
        }
        win.draw(hpText);
        win.draw(ptsText);
        win.display();
    }//główna pętla
    delete ship;
    return 0;
}
