#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
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
    void move();
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
class TextureManager
{
public:
    sf::Font font;
    sf::Text hpText;
    sf::Text ptsText;
    sf::Texture bkgrTex;
    sf::Texture shipTex;
    sf::Texture bulTex;
    sf::Texture eneTex;
    sf::Sprite bkgrSpr;
    sf::Sprite shipSpr;
    std::vector <sf::Sprite> bulSprVec;
    std::vector <sf::Sprite> bulSprVec2;
    std::vector <sf::Sprite> eneSprVec;
    TextureManager();
};
class Game
{
    std::vector <Enemy> eneVec;
    void lookForHits(Ship* s, std::vector <Enemy> &ea);
    void lookForHits(std::vector <Bullet*> &ba, std::vector <Enemy> &sa);
    void lookForHits(Ship* s,std::vector <Bullet*> &ba);
    sf::RenderWindow* win;
    bool inGame;
public:
    int enemyCount;
    int hp;
    int points;
    Game(sf::RenderWindow* winParam);
    void play();
    void load(std::string index);
};
class Save
{
    std::ofstream saveStream;
    int points;
    int hp;
public:
    static int number;
    Save(Game);
    void save(Game,std::string index);
};
void moveEnemies(std::vector <Enemy> &ea);
void addHp();
void placeEnemies(std::vector <Enemy> &ea);
