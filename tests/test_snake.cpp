#include "doctest.h"
#include "../snake.h"

TEST_CASE("Test snake_game constructor") {
    snake_game s;

    REQUIRE((s.length == 1));
    REQUIRE((s.fruit_coord.x < FIELD_SIZE && s.fruit_coord.x >= 0 && s.fruit_coord.y >= 0 && s.fruit_coord.y < FIELD_SIZE));
    REQUIRE((s.tail.size() == 1));
    REQUIRE((s.tail[0].x < FIELD_SIZE && s.tail[0].x >= 0 && s.tail[0].y >= 0 && s.tail[0].y < FIELD_SIZE));
    REQUIRE((s.direction.first == 0 && s.direction.second == 0));
    REQUIRE((s.score == 0));
}

TEST_CASE("Test snake_game get_field") {
    snake_game s;

    s.tail.clear();
    s.tail.emplace_back(coord(FIELD_SIZE / 2, FIELD_SIZE / 2));
    s.tail.emplace_back(coord(FIELD_SIZE / 2 + 1, FIELD_SIZE / 2));
    s.tail.emplace_back(coord(FIELD_SIZE / 2 + 2, FIELD_SIZE / 2));
    s.tail.emplace_back(coord(FIELD_SIZE / 2 + 2, FIELD_SIZE / 2 + 1));

    s.fruit_coord = coord(FIELD_SIZE / 2, FIELD_SIZE / 2 - 1);
    s.get_field();

    for (auto el : s.tail) {
        REQUIRE((s.field[el.x][el.y] == 'O'));
    }

    REQUIRE((s.field[s.fruit_coord.x][s.fruit_coord.y] == '#'));
}

TEST_CASE("Test check_fruit fruit in snake") {
    snake_game s;
    s.fruit_coord = coord(0, 0);
    s.tail.clear();
    s.tail.emplace_back(coord(0, 0));
    REQUIRE(s.check_fruit());
}

TEST_CASE("Test check_fruit fruit not in snake") {
    snake_game s;
    s.fruit_coord = coord(1, 0);
    s.tail.clear();
    s.tail.emplace_back(coord(0, 0));
    REQUIRE(!s.check_fruit());
}


TEST_CASE("Test check_fruit fruit in the middle of the snake") {
    snake_game s;
    s.fruit_coord = coord(1, 0);
    s.tail.clear();
    s.tail.emplace_back(coord(0, 0));
    s.tail.emplace_back(coord(1, 0));
    s.tail.emplace_back(coord(2, 0));
    REQUIRE(s.check_fruit());
}

TEST_CASE("Check that set_random_fruit dont put fruit in snake") {
    snake_game s;
    s.tail.clear();
    s.tail.emplace_back(coord(0, 0));
    s.tail.emplace_back(coord(1, 0));
    s.tail.emplace_back(coord(2, 0));

    for (int i = 0; i < 100; i++) {
        s.set_random_fruit();
        for (auto el : s.tail) {
            REQUIRE((el.x != s.fruit_coord.x && el.y != s.fruit_coord.y));
        }
    }
}

TEST_CASE("Test check_intersection when head not in snake") {
    snake_game s;
    s.tail.clear();
    s.tail.emplace_back(coord(0, 0));
    s.tail.emplace_back(coord(1, 0));
    s.tail.emplace_back(coord(2, 0));

    REQUIRE(!s.check_intersection());
}

TEST_CASE("Test check_intersection when head in snake") {
    snake_game s;
    s.tail.clear();
    s.tail.emplace_back(coord(0, 0));
    s.tail.emplace_back(coord(1, 0));
    s.tail.emplace_back(coord(2, 0));
    s.tail.emplace_back(coord(2, 1));
    s.tail.emplace_back(coord(1, 1));
    s.tail.emplace_back(coord(1, 0));

    REQUIRE(s.check_intersection());
}

TEST_CASE("Test that nothing changed in iteration in beginning") {
    snake_game s;
    coord tmp = s.fruit_coord;
    coord tmp_head = s.tail[0];
    for (int i = 0; i < 10; i++) {
        bool a = s.iteration();
        REQUIRE(!a);
        REQUIRE((s.tail.size() == 1));
        REQUIRE((tmp.x == s.fruit_coord.x && tmp.y == s.fruit_coord.y));
        REQUIRE((s.tail[0].x == tmp_head.x && s.tail[0].y == tmp_head.y));
    }
}

TEST_CASE("Test snake moving") {
    snake_game s;
    s.tail[0] = coord(0, 0);
    s.direction = std::make_pair(0, 1);
    s.fruit_coord = coord(FIELD_SIZE, FIELD_SIZE);

    s.iteration();
    REQUIRE((s.tail.size() == 1)    );
    REQUIRE((s.tail[0].x == 0 && s.tail[0].y == 1));

    s.direction = std::make_pair(0, -1);
    s.iteration();
    s.iteration();
    REQUIRE((s.tail[0].x == 0 && s.tail[0].y == FIELD_SIZE - 1));


    s.direction = std::make_pair(1, 0);
    s.iteration();
    REQUIRE((s.tail[0].x == 1 && s.tail[0].y == FIELD_SIZE - 1));


    s.direction = std::make_pair(-1, 0);
    s.iteration();
    s.iteration();
    REQUIRE((s.tail[0].x == FIELD_SIZE - 1 && s.tail[0].y == FIELD_SIZE - 1));
}

TEST_CASE("Test game ending") {
    snake_game s;
    s.tail.clear();
    s.tail.emplace_back(coord(0, 0));
    s.tail.emplace_back(coord(1, 0));
    s.tail.emplace_back(coord(2, 0));
    s.tail.emplace_back(coord(2, 1));
    s.tail.emplace_back(coord(1, 1));

    s.direction = std::make_pair(0, -1);
    REQUIRE(s.iteration());
}

TEST_CASE("Test score increasing when head in fruit") {
    snake_game s;

    s.tail.clear();
    s.tail.emplace_back(coord(0, 0));
    s.tail.emplace_back(coord(1, 0));
    s.tail.emplace_back(coord(2, 0));
    s.fruit_coord = coord(3, 0);

    s.direction = std::make_pair(1, 0);
    s.iteration();
    REQUIRE((s.score == 1));
}
