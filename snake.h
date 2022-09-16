#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <vector>
#include <random>

#define FIELD_SIZE 15

/*! A coord struct */
struct coord {
public:
    int x, y;

    coord();

    coord(int _x, int _y);
};

/*! Struct for snake game */
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

    /** get_field function
     *  check game data and write it to field variable
     */
    void get_field();

    /** Check button function
     *  Get data from keyboard input and place it to direction variable
     */
    void check_button();

    /** set_random_fruit function
     *  put fruit on random coord in field(not snake coord)
     */
    void set_random_fruit();

    /** Check_fruit function
     *  Check whether snake in fruit or not
     *  @return true if yes, false otherwise
     */
    bool check_fruit();

    /** Check intersection function
     *  Check whether snake head in tail or not
     *  @return true if yes, false otherwise
     */
    bool check_intersection();

    /** iteration function
     *  Do all logic in one step
     *  @return true if game over, false otherwise
     */
    bool iteration();

    /** clear function
     *  clear console
     */
    void clear();

    /** draw function
     *  draw field variable to console
     */
    void draw();

    /** game_over function
     *  print game over message to console
     */
    void game_over();

    /** run function
     *  start game
     */
    void run();
};

#endif //SNAKE_SNAKE_H
