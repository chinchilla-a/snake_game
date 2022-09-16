#include "snake.h"

#include <iostream>
#include <vector>
#include <random>
#include <conio.h>
#include <windows.h>

coord::coord() {
    x = 0;
    y = 0;
}

coord::coord(int _x, int _y) {
    x = _x;
    y = _y;
}

snake_game::snake_game() {
    length = 1;
    fruit_coord = coord(dist(gen), dist(gen));
    tail.emplace_back(coord(dist(gen), dist(gen)));
    direction = std::make_pair(0, 0);
    get_field();
    score = 0;
}

void snake_game::get_field() {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            field[i][j] = ' ';
        }
    }

    for (auto el : tail) {
        field[el.x][el.y] = 'O';
    }

    field[fruit_coord.x][fruit_coord.y] = '#';
}

void snake_game::check_button() {
    if (_kbhit()) {
        int ch = _getch();
        if (ch == 'w') {
            direction.first = -1;
            direction.second = 0;
        } else if (ch == 's') {
            direction.first = 1;
            direction.second = 0;
        } else if (ch == 'd') {
            direction.first = 0;
            direction.second = 1;
        } else if (ch == 'a') {
            direction.first = 0;
            direction.second = -1;
        }
    }
}

void snake_game::set_random_fruit() {
    while (check_fruit())
        fruit_coord = coord(dist(gen), dist(gen));
}

bool snake_game::check_fruit() {
    for (auto el : tail) {
        if (el.x == fruit_coord.x && el.y == fruit_coord.y) {
            return true;
        }
    }
    return false;
}

bool snake_game::check_intersection() {
    for (int i = 0; i < tail.size() - 1; i++) {
        if (tail[i].x == tail[tail.size() - 1].x && tail[i].y == tail[tail.size() - 1].y) {
            return true;
        }
    }
    return false;
}

bool snake_game::iteration() {
    if (direction.first == 0 && direction.second == 0) {
        return false;
    }
    coord head = tail[tail.size() - 1];
    coord next = coord(head.x + direction.first, head.y + direction.second);
    if (next.x == -1) {
        next.x = FIELD_SIZE - 1;
    }

    if (next.x == FIELD_SIZE) {
        next.x = 0;
    }

    if (next.y == -1) {
        next.y = FIELD_SIZE - 1;
    }

    if (next.y == FIELD_SIZE) {
        next.y = 0;
    }

    tail.push_back(next);

    if (check_intersection()) {
        return true;
    }

    if (check_fruit()) {
        score++;
        set_random_fruit();
    } else {
        tail.erase(tail.begin());
    }
    return false;
}

void snake_game::clear() {
    std::cout << "\x1B[2J\x1B[H";
}


void snake_game::draw() {
    system("cls");
    clear();
    for (int i = 0; i < FIELD_SIZE + 2; i++) {
        std::cout << "#";
    }
    std::cout << std::endl;
    for (int i = 0; i < FIELD_SIZE; i++) {
        std::cout << "#";
        for (int j = 0; j < FIELD_SIZE; j++) {
            std::cout << field[i][j];
        }
        std::cout << "#" << std::endl;
    }
    for (int i = 0; i < FIELD_SIZE + 2; i++) {
        std::cout << "#";
    }
    std::cout << "\nSCORE: " << score << std::endl;
}

void snake_game::game_over() {
    clear();
    std::cout << "GAME OVER\nSCORE: " << score;
}

void snake_game::run() {
    while (true) {
        check_button();
        bool is_end = iteration();
        if (is_end) {
            game_over();
            break;
        }
        get_field();
        draw();
        Sleep(500 / (score + 1));
    }
    game_over();
    Sleep(5000);
}