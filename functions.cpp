#include "functions.h"
extern const int WIDTH;
extern const int HEIGHT;
int Enemy::number;
int Enemy::_dx;
int Enemy::_dy;
int Bullet::number;
int Ship::number;
int hp;
int points;
Bullet::Bullet(Ship s, int __dy)
{
    owner=s;
    _dy=__dy;
    _x=owner.x();
    _y=owner.y();
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
void Bullet::move()
{
    _y+=_dy;
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
bool Ship::collision(Ship s)
{
    return x()==s.x() && y()==s.y();
}
bool Ship::collision(Bullet b)
{
    return x()==b.x() && y()==b.y();
}
void Ship::move(char dir)
{
    if(dir=='L') if(_x-_dx>=0) _x-=_dx;
    if(dir=='R') if(_x+width+_dx<WIDTH) _x+=_dx;
}
Bullet* Ship::shoot()
{
    Bullet* b=new Bullet(*this);
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

void moveEnemies(Enemy ea[])
{
    if(ea[Enemy::number-1].x()>=WIDTH || ea[0].x()<=0) Enemy::_dx*=-1;
    for(Enemy* e=ea ; e!=ea+Enemy::number ; e++)
        e->_x += Enemy::_dx;
}

void addHp()
{
    if(points>0 && points%20==0) hp++;
}

void lookForHits(Ship& s, Enemy ea[])
{
    for(Enemy *e=ea; e!=ea+Enemy::number ; e++)
        if(s.collision(*e))
    {
        hp=0;
        s.~Ship();
        return;
    }
}

void lookForHits(Bullet ba[],Ship sa[])
{
    for(Ship *s=sa; s!=sa+Ship::number; s++)
        for(Bullet *b=ba; b!=ba+Bullet::number; b++)
        if(s->collision(*b))
    {
        s->~Ship();
        b->~Bullet();
    }
}
void placeEnemies(Enemy ea[])
{
    int i=0;
    for(Enemy* e=ea;e<ea+Enemy::number;e++,i++)
    {
        if(e) e->_x=WIDTH/(i+1);
        if(e) e->_y=HEIGHT+10;
    }
}
