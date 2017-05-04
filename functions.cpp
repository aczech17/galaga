#include "functions.h"
#include <iostream>
extern const int WIDTH;
extern const int HEIGHT;
int Enemy::number;
int Enemy::_dx;
int Enemy::_dy;
int Bullet::number;
int Ship::number;
int hp;
unsigned int points;
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
void moveEnemies(std::vector <Enemy> &ea)
{
    for(unsigned int i=0; i<ea.size(); i++)
    {
        if(ea[i].x() + Enemy::width>=WIDTH || ea[i].x()<=-10) Enemy::_dx*=-1;
        ea[i]._x+=Enemy::_dx;
    }
}

void addHp()
{
    if(points>0 && points%20==0) hp++;
}

void lookForHits(Ship* s, std::vector <Enemy> &ea)
{
    for(std::vector <Enemy>::iterator e=ea.begin(); e!=ea.end(); e++)
    {
        if(s->collision(&*e) && e->active)
        {
            hp--;
        }
    }
}

void lookForHits(std::vector <Bullet*> &ba,std::vector <Enemy> &sa)
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
void lookForHits(Ship* s,std::vector<Bullet*> &ba)
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
