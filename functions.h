#include <cstdlib>
#include <ctime>
class Bullet;
class Ship
{
protected:
    int _x;
    int _y;
    int _dx;
public:
    static int number;
    static int width;
    static int height;
    Ship(int __x=400, int __y=300, int __dx=10);
    ~Ship();
    Bullet* shoot();
    void setX(int x);
    void setY(int y);
    int x();
    int y();
    bool collision(Ship);
    bool collision(Bullet);
    void move(char dir);
};
class Enemy :public Ship
{
    friend void moveEnemies(Enemy ea[]);
    friend void placeEnemies(Enemy ea[]);
    bool _ifAttack;
    static int _dx;
    static int _dy;
public:
    static int number;
    static int width;
    static int height;
    Enemy(int __x=500, int __y=600, int __dx=1, int __dy=1);
    ~Enemy();
    void decideIfAttack();
    bool ifAttack();
    void attack();
};
class Bullet
{
    int _x,_y,_dy;
    Ship owner;
public:
    Bullet(Ship, int __dy=1);
    ~Bullet();
    static int number;
    static int width;
    static int height;
    int x();
    int y();
    void move();
    bool ifHit(Ship);
};
void moveEnemies(Enemy ea[]);
void addHp();
void lookForHits(Ship s, Enemy ea[]);
void lookForHits(Bullet ba[], Ship sa[]);
void placeEnemies(Enemy ea[]);
