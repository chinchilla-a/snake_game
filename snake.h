#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <vector>
#include <random>

#define FIELD_SIZE 15

struct coord {
public:
    int x, y;

    coord();

    coord(int _x, int _y);
};

struct snake_game {
public:
    int length, score;
    std::vector<coord> tail;
    coord fruit_coord;

    std::pair<int, int> direction;

    std::random_device rd;
    std::mt19937 gen = std::mt19937(rd());
    std::uniform_int_distribution<> dist = std::uniform_int_distribution<>(0,FIELD_SIZE - 1);

    char field[FIELD_SIZE][FIELD_SIZE];

    snake_game();

    void get_field();

    void check_button();

    void set_random_fruit();

    bool check_fruit();

    bool check_intersection();

    bool iteration();

    void clear();

    void draw();

    void game_over();

    void run();
};

#endif //SNAKE_SNAKE_H
