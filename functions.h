#include <cstdlib>
#include <stdlib.h>
class Enemy;
class Bullet;
class Ship
{
    int _x;
    int _y;
    int _hp;
    int _points;
public:
    Ship(int __x=400, int __y=300, int __hp=100, int __points=0);
    Bullet* shoot();
    int x();
    int y();
    int hp();
    int points();
    bool collision(Enemy&);//do dopracowania
};
class Enemy
{
    int _x,_y;//position
public:
    bool ifAttack();
    void attack();
    int x();
    int y();
};
class Bullet
{
    int _x,_y,_dy;
    Ship owner;
public:
    Bullet(Ship, int __dy=1);
    int x();
    int y();
    void move();
};
