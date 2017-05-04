#include <cstdlib>
#include <ctime>
#include <vector>
class Bullet;
class Enemy;
class Ship
{
    friend void placeEnemies(std::vector <Enemy> &ea);
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
    bool collision(Ship*);
    bool collision(Bullet*);
    void move(char dir);
};
class Enemy :public Ship
{
    friend void moveEnemies(std::vector <Enemy> &ea);
    friend void placeEnemies(std::vector <Enemy> &ea);
    bool _ifAttack;
    bool _ifShoot;
    static int _dx;
    static int _dy;
public:
    bool active;
    static int number;
    Enemy(int __x=500, int __y=600, int __dx=1, int __dy=1);
    ~Enemy();
    void decideIfAttack();
    bool ifAttack();
    void attack();
    void decideIfShoot();
    bool ifShoot();
};
class Bullet
{
    int _dy;
public:
    Bullet(Ship*, int __dy=1);
    Bullet(Enemy*, int __dy=1);
    ~Bullet();
    Ship* owner;
    int _x,_y;
    static int number;
    static int width;
    static int height;
    bool active;
    int x();
    int y();
    void move(char dir);
    bool ifHit(Ship);
};
void moveEnemies(std::vector <Enemy> &ea);
void addHp();
void lookForHits(Ship* s, std::vector <Enemy> &ea);
void lookForHits(std::vector <Bullet*> &ba, std::vector <Enemy> &sa);
void lookForHits(Ship* s,std::vector <Bullet*> &ba);
void placeEnemies(std::vector <Enemy> &ea);
