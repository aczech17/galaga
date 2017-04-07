#include "functions.h"
Ship::Ship(int __x, int __y, int __hp, int __points)
{
    _x=__x;
    _y=__y;
    _hp=__hp;
    _points=__points;
}
int Ship::x()
{
    return _x;
}
int Ship::y()
{
    return _y;
}
Bullet* Ship::shoot()
{
    Bullet *b=new Bullet(*this);
    return b;
}
int Ship::hp()
{
    return _hp;
}
int Ship::points()
{
    return _points;
}
bool Ship::collision(Enemy& e)
{
    return e.x()==x() && e.y()==y();
}
Bullet::Bullet(Ship s, int __dy)
{
    owner=s;
    _x=owner.x();
    _y=owner.y();
    _dy=__dy;
}
void Bullet::move()
{
    _y+=_dy;
}
int Bullet::x()
{
    return _x;
}
int Bullet::y()
{
    return _y;
}
int Enemy::x()
{
    return _x;
}
int Enemy::y()
{
    return _y;
}
bool Enemy::ifAttack()
{
    return rand()%20==1;
}
