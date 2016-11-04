// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

// ----
// test
// ----

TEST(Darwin_isEmpty, test1) {
    Darwin darwin(5, 5);
    Species food("f");
    Creature f(&food, 0);
    Creature f2(&food, 0);
    darwin.addCreature(f, 3, 3);
    darwin.addCreature(f2, 2, 3);
    bool x = f.is_empty(darwin, 2, 3); 
    ASSERT_FALSE(x);}

TEST(Darwin_isEmpty, test2) {
    Darwin darwin(5, 5);
    Species food("f");
    Creature f(&food, 0);
    Creature f2(&food, 0);
    darwin.addCreature(f, 3, 3);
    darwin.addCreature(f2, 2, 3);
    bool x = f2.is_empty(darwin, 1, 3);
    ASSERT_TRUE(x);
}

TEST(Darwin_isEmpty, test3) {
    Darwin darwin(5, 5);
    Species food("f");
    Creature f(&food, 1);
    darwin.addCreature(f, 3, 3);
    ASSERT_TRUE(f.is_empty(darwin ,3, 4));
}

TEST(Darwin_isEnemy, test1) {
    Darwin darwin(5, 5);
    Species food("f");
    Creature f(&food, 0);
    Creature f1(&food, 0);
    darwin.addCreature(f, 3, 3);
    darwin.addCreature(f1, 2, 3);
    ASSERT_FALSE(f.is_enemy(darwin, 2, 3, 3, 3));
}

TEST(Darwin_isEnemy, test2) {
    Darwin darwin(5, 5);
    Species food("f");
    Creature f(&food, 0);
    Creature f1(&food, 0);
    darwin.addCreature(f, 3, 3);
    darwin.addCreature(f1, 2, 3);
    ASSERT_FALSE(f1.is_enemy(darwin, 1, 3, 2, 3));
}

TEST(Darwin_isEnemy, test3) {
    Darwin darwin(5, 5);
    Species food("f");
    Species rover("r");
    Creature r(&rover, 0);
    Creature f(&food, 0);
    darwin.addCreature(r, 3, 3);
    darwin.addCreature(f, 2, 3);
    ASSERT_TRUE(r.is_enemy(darwin, 2, 3, 3, 3));
}

TEST(Darwin_takeTurn, test1) {
    Species food1("f");
    food1.addInstruction("left");
    food1.addInstruction("go", 0);
    Species hopper1("h");
    hopper1.addInstruction("hop");
    hopper1.addInstruction("go", 0);
    Creature f1(&food1, 1); 
    Creature h1(&hopper1, 0);
    Creature h2(&hopper1, 1);
    Creature h3(&hopper1, 2);
    Creature h4(&hopper1, 3);
    Creature f2(&food1, 1);
    Darwin darwin1(8, 8);
    srand(0);
    darwin1.addCreature(f1, 0, 0);
    darwin1.addCreature(f2, 7, 7);
    darwin1.addCreature(h1, 3, 3);
    darwin1.addCreature(h2, 3, 4);
    darwin1.addCreature(h3, 4, 4);
    darwin1.addCreature(h4, 4, 3);
    darwin1.takeTurn();
    ASSERT_TRUE(true);

}

TEST(Darwin_takeTurn, test2) {
    Species food2("f");
    food2.addInstruction("left");
    food2.addInstruction("go", 0);
    Species hopper2("h");
    hopper2.addInstruction("hop");
    hopper2.addInstruction("go", 0);
    Species rover2("r");
    rover2.addInstruction("if_enemy", 9);
    rover2.addInstruction("if_empty", 7);
    rover2.addInstruction("if_random", 5);
    rover2.addInstruction("left");
    rover2.addInstruction("go", 0);
    rover2.addInstruction("right");
    rover2.addInstruction("go", 0);
    rover2.addInstruction("hop");
    rover2.addInstruction("go", 0);
    rover2.addInstruction("infect");
    rover2.addInstruction("go", 0);
    Species trap2("t");
    trap2.addInstruction("if_enemy", 3);
    trap2.addInstruction("left");
    trap2.addInstruction("go", 0);
    trap2.addInstruction("infect");
    trap2.addInstruction("go", 0);
    Creature tt1(&trap2, 2);
    Creature hh1(&hopper2, 1);
    Creature rr1(&rover2, 0);
    Creature tt2(&trap2, 3);
    Darwin darwin2(100, 100);
    darwin2.addCreature(tt1, (rand()%10000)/100, (rand()%10000)%100);
    darwin2.addCreature(hh1, (rand()%10000)/100, (rand()%10000)%100);
    darwin2.addCreature(rr1, (rand()%10000)/100, (rand()%10000)%100);
    darwin2.addCreature(tt2, (rand()%10000)/100, (rand()%10000)%100);
    int i = 0; 
    while(i < 40){
        darwin2.takeTurn();
        i++;
    }

}


TEST(Darwin_takeTurn, test3) {
    Species food1("f");
    food1.addInstruction("left");
    food1.addInstruction("go", 0);
    Species hopper1("h");
    hopper1.addInstruction("hop");
    hopper1.addInstruction("go", 0);
    Creature f1(&food1, 1); 
    Creature h1(&hopper1, 0);
    Creature h2(&hopper1, 1);
    Creature h3(&hopper1, 2);
    Creature h4(&hopper1, 3);
    Creature f2(&food1, 1);
    Darwin darwin1(10, 8);
    srand(0);
    darwin1.addCreature(f1, 0, 0);
    darwin1.addCreature(f2, 7, 7);
    darwin1.addCreature(h1, 3, 3);
    darwin1.addCreature(h2, 3, 4);
    darwin1.addCreature(h3, 4, 4);
    darwin1.addCreature(h4, 4, 3);
    darwin1.takeTurn();
    ASSERT_TRUE(true);

}
