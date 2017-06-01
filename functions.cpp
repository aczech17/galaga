#include "functions.h"
#include <iostream>
extern const int WIDTH;
extern const int HEIGHT;
int Enemy::number;
int Enemy::_dx;
int Enemy::_dy;
int Bullet::number;
int Ship::number;
int Save::number;
int hp;
unsigned int points;
using std::cout;
using std::endl;
Bullet::Bullet(Ship* s, int __dy)
{
    owner=s;
    _dy=__dy;
    _x=owner->x()+width/2;
    _y=owner->y()-owner->height;
    active=1;
    number++;
}

Bullet::Bullet(Enemy* s, int __dy)
{
    owner=s;
    _dy=__dy;
    _x=owner->x()+width/2;
    _y=owner->y()+owner->height;
    active=1;
    number++;
}

Bullet::~Bullet()
{
    number--;
}
int Bullet::x()
{
    return _x;
}
int Bullet::y()
{
    return _y;
}
void Bullet::move(char dir)
{
    if(dir=='U') _y-=1;
    else if(dir=='D') _y+=1;
}

Ship::Ship(int __x,int __y, int __dx)
{
    _x=__x;
    _y=__y;
    _dx=__dx;
    number++;
}
Ship::~Ship()
{
    number--;
}
int Ship::x()
{
    return _x;
}
int Ship::y()
{
    return _y;
}
bool Ship::collision(Ship* s)
{
    return s->x()+s->width>=x() && s->x()<=x()+width && s->y()<=y()+height && s->y()+s->height>=y();
}
bool Ship::collision(Bullet* b)
{
    return b->x()+b->width>=x() && b->x()<=x()+width && b->y()<=y()+height && b->y()+b->height>=y();
}
void Ship::move(char dir)
{
    if(dir=='L') if(_x-_dx>=0) _x-=_dx;
    if(dir=='R') if(_x+width+_dx<WIDTH) _x+=_dx;
}
Bullet* Ship::shoot()
{
    Bullet* b=new Bullet(this);
    return b;
}
void Ship::setX(int x)
{
    _x=x;
}
void Ship::setY(int y)
{
    _y=y;
}
Enemy::Enemy(int __x, int __y, int __dx, int __dy)
{
    _x=__x;
    _y=__y;
    _dx=__dx;
    _dy=__dy;
    _ifAttack=0;
    active=1;
    number++;
}
Enemy::~Enemy()
{
    number--;
}
void Enemy::decideIfAttack()
{
    _ifAttack=(rand()%20<4);
}
bool Enemy::ifAttack()
{
    return _ifAttack;
}
bool Enemy::ifShoot()
{
    return rand()%10000<5;
}
void Enemy::move()
{
    if(x() + width>=WIDTH || x()<=-10) _dx*=-1;
    _x+=_dx;
}
TextureManager::TextureManager()
{
    font.loadFromFile("arial.ttf");
    hpText.setFont(font);
    ptsText.setFont(font);
    ptsText.setPosition(WIDTH-100,10);
    bkgrTex.loadFromFile("background.png");
    bkgrSpr.setTexture(bkgrTex);
    shipTex.loadFromFile("ship.png");
    shipSpr.setTexture(shipTex);
    Ship::width=shipTex.getSize().x;
    Ship::height=shipTex.getSize().y;
    bulTex.loadFromFile("bullet.png");
    Bullet::width=bulTex.getSize().x;
    Bullet::height=bulTex.getSize().y;
    eneTex.loadFromFile("enemy.png");
}
Game::Game(sf::RenderWindow* winParam)
{
    win=winParam;
    inGame=1;
    enemyCount=6;
    hp=3;
    points=0;
}
void Game::play()
{
    TextureManager texm;
    Enemy::number=0;
    Bullet::number=0;
    srand(time(NULL));
    Ship *ship=new Ship;
    std::vector <Bullet*> bulVec;
    std::vector <Bullet*> bulVec2;
    for(int i=0; i<enemyCount; i++)
        eneVec.push_back(Enemy());
    for(int i=0; i<enemyCount; i++)
        texm.eneSprVec.push_back(sf::Sprite(texm.eneTex));

    placeEnemies(eneVec);
    ship->setX(WIDTH/2);
    ship->setY(HEIGHT-Ship::height-10);
    while(inGame)
    {
        sf::Event event;
        while(win->pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                win->close();
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Escape)
                inGame=0;
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Left)
                ship->move('L');
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Right)
                ship->move('R');
                if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Num0)
            {
                Save s(*this);
                s.save(*this,"0");
            }
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Num1)
            {
                Save s(*this);
                s.save(*this,"1");
            }
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Num1)
            {
                Save s(*this);
                s.save(*this,"1");
            }
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Num2)
            {
                Save s(*this);
                s.save(*this,"2");
            }
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Num3)
            {
                Save s(*this);
                s.save(*this,"3");
            }
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Num4)
            {
                Save s(*this);
                s.save(*this,"4");
            }if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Num5)
            {
                Save s(*this);
                s.save(*this,"5");
            }
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Num6)
            {
                Save s(*this);
                s.save(*this,"6");
            }
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Num7)
            {
                Save s(*this);
                s.save(*this,"7");
            }
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Num8)
            {
                Save s(*this);
                s.save(*this,"8");
            }
            if(event.type==sf::Event::KeyPressed && event.key.code==sf::Keyboard::Num9)
            {
                Save s(*this);
                s.save(*this,"9");
            }
            if(event.type==sf::Event::KeyReleased && event.key.code==sf::Keyboard::Space)
            {
                Bullet* b=new Bullet(ship);
                bulVec.push_back(b);
                texm.bulSprVec.push_back(sf::Sprite(texm.bulTex));
            }
        }//eventy
        texm.shipSpr.setPosition(ship->x(),ship->y());
        std::vector <Enemy>::iterator eneI=eneVec.begin();
        std::vector <sf::Sprite>::iterator eneSprI=texm.eneSprVec.begin();
        while(eneI!=eneVec.end())
        {
            eneSprI->setPosition(eneI->x(),eneI->y());
            eneI++;
            eneSprI++;
        }
        eneI=eneVec.begin();

        std::vector <Bullet*>::iterator bulI=bulVec.begin();
        std::vector <sf::Sprite>::iterator bulSprI=texm.bulSprVec.begin();
        for(eneI=eneVec.begin(); eneI!=eneVec.end(); eneI++)
        {
            if(eneI->ifShoot() && eneI->active)
            {
                Bullet s(&*eneI);
                bulVec2.push_back(&s);
                texm.bulSprVec2.push_back(sf::Sprite(texm.bulTex));
            }
        }
        for(; bulI!=bulVec.end(); bulI++,bulSprI++)
        {
            (*bulI)->move('U');
            bulSprI->setPosition((*bulI)->x(),(*bulI)->y());
        }//bullet pętla
        for(bulI=bulVec2.begin(), bulSprI=texm.bulSprVec2.begin(); bulI!=bulVec2.end(); bulI++, bulSprI++)
        {
            (*bulI)->move('D');
            bulSprI->setPosition((*bulI)->x(),(*bulI)->y());
        }

        moveEnemies(eneVec);
        lookForHits(bulVec,eneVec);
        lookForHits(ship, bulVec2);
        win->draw(texm.bkgrSpr);
        win->draw(texm.shipSpr);
        for(eneSprI=texm.eneSprVec.begin(),eneI=eneVec.begin(); eneSprI!=texm.eneSprVec.end(); eneSprI++,eneI++)
        {
            eneSprI->setPosition(eneI->x(),eneI->y());
            if(eneI->active) win->draw(*eneSprI);
        }//to jest dobre
        for(bulI=bulVec.begin(), bulSprI=texm.bulSprVec.begin(); bulI!=bulVec.end(); bulI++, bulSprI++)
            if((*bulI)->active)
                win->draw(*bulSprI);
        for(bulI=bulVec2.begin(), bulSprI=texm.bulSprVec2.begin(); bulI!=bulVec2.end(); bulI++, bulSprI++)
            if((*bulI)->active) win->draw(*bulSprI);

        texm.hpText.setString("HP: "+std::to_string(hp));
        texm.ptsText.setString("PTS: "+std::to_string(points));
        if(hp==0) inGame=0; //ŚMIERĆ!!!
        if(points==enemyCount && eneVec.begin()->active==0)
        {
            for(eneI=eneVec.begin(); eneI!=eneVec.end(); eneI++)
                eneI->active=1;
            hp++;
        }
        win->draw(texm.hpText);
        win->draw(texm.ptsText);
        win->display();
    }//główna pętla
    delete ship;
}
void moveEnemies(std::vector <Enemy> &ea)
{
    for(unsigned int i=0; i<ea.size(); i++)
    {
        ea[i].move();
    }
}

void addHp()
{
    if(points>0 && points%20==0) hp++;
}

void Game::lookForHits(Ship* s, std::vector <Enemy> &ea)
{
    for(std::vector <Enemy>::iterator e=ea.begin(); e!=ea.end(); e++)
    {
        if(s->collision(&*e) && e->active)
        {
            hp--;
        }
    }
}

void Game::lookForHits(std::vector <Bullet*> &ba,std::vector <Enemy> &sa)
{
    for(std::vector<Enemy>::iterator s=sa.begin(); s!=sa.end(); s++)
        for(std::vector <Bullet*>::iterator b=ba.begin(); b!=ba.end(); b++)
        {
            if(s->collision(*b) && (*b)->active && s->active)
            {
                (*b)->active=0;
                s->active=0;
                points++;
            }
            if((*b)->y()+(*b)->height<0) (*b)->active=0;
        }
}
void placeEnemies(std::vector <Enemy> &ea)
{
    unsigned int i=0;
    while(i<ea.size())
    {
        ea[i]._x=i*WIDTH/ea.size();
        ea[i]._y=20;
        i++;
    }
}
void Game::lookForHits(Ship* s,std::vector<Bullet*> &ba)
{
    for(std::vector <Bullet*>::iterator b=ba.begin(); b!=ba.end(); b++)
    {
        if(s->collision(*b) && ((*b)->active))
        {
            hp--;
            (*b)->active=0;
        }
    }
}
Save::Save(Game g)
{
    number++;
    hp=g.hp;
    points=g.points;
}
void Save::save(Game g, std::string index)
{
    saveStream.open("save"+index+".txt");
    saveStream<<hp<<std::endl<<points;
    saveStream.close();
}

void Game::load(std::string index)
{
    std::fstream saveStream;
    saveStream.open("save"+index+".txt");
    saveStream>>hp;
    saveStream>>points;
    enemyCount=6-points%6;
    saveStream.close();
}
