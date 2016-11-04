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

// ------------------
// Darwin constructor
// ------------------

TEST(DarwinFixture, test_1) {
    Darwin d(1, 1);
}

TEST(DarwinFixture, test_2) {
    Darwin d(72, 72);
}

TEST(DarwinFixture, test_3) {
    Darwin d(100, 100);
}

TEST(DarwinFixture, test_4) {
    for(int i = 0; i < 10; ++i) {
        Darwin d(10, 10);}
}

// ---------------------
// Species constructor 1
// ---------------------

TEST(DarwinFixture, test_5) {
    Species s('s');
}

TEST(DarwinFixture, test_6) {
    for(int i = 0; i < 10; ++i) {
        Species s('s');}
}

TEST(DarwinFixture, test_7) {
    Species w('w');
    Species h('h');
    Species a('a');
    Species t('t');
}

// ---------------------
// Species constructor 2
// ---------------------

TEST(DarwinFixture, test_8) {
    Species s('s');
    Species s2(s);
}

TEST(DarwinFixture, test_9) {
    Species s('s');
    for(int i = 0; i < 10; ++i) {
        Species q(s);}
}

TEST(DarwinFixture, test_10) {
    Species s('s');
    Species s2(s);
    Species s3(s2);    
    Species s4(s3);
    Species s5(s4);
}
// --------------------
// Creature constructor
// --------------------

TEST(DarwinFixture, test_11) {
    Species s('w');
    Creature c(s, east);
}

TEST(DarwinFixture, test_12) {
    Species s('w');
    for(int i = 0; i < 10; ++i) {
    Creature c(s, east);}
}

TEST(DarwinFixture, test_13) {
    Species s('w');
    Creature c(s, east);
    Creature c1(s, west);
    Creature c2(s, north);
    Creature c3(s, south);
}

TEST(DarwinFixture, test_14) {
    Darwin d(4,4);

    Species hopper('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go", 0);
    Species trap('t');
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left");
    trap.addInstruction("go", 0);
    trap.addInstruction("infect");
    trap.addInstruction("go", 0);

    Creature t1(trap, east); // (west 0, north 1, east 2, south 3) 
    d.addCreature(t1, 0, 0);
    Creature h1(hopper, south);
    d.addCreature(h1, 0, 1);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(1);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  0123\n0 th..\n1 ....\n2 ....\n3"
        " ....\n\nTurn = 1.\n  0123\n0 tt..\n1 ....\n2 ....\n3 ....\n\n") == 0);
}

TEST(DarwinFixture, test_15) {
    Darwin d(1,1);

    Species hopper('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go", 0);
    Creature h1(hopper, south);
    d.addCreature(h1, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(1);
    cout.rdbuf(old_buf);

    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  0\n0 h\n\n"
        "Turn = 1.\n  0\n0 h\n\n") == 0);
}

TEST(DarwinFixture, test_16) {
    Darwin d(1,1);

    Species trap('t');
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left");
    trap.addInstruction("go", 0);
    trap.addInstruction("infect");
    trap.addInstruction("go", 0);

    Creature t1(trap, east); // (west 0, north 1, east 2, south 3) 
    d.addCreature(t1, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(1);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  0\n0 t\n\n"
        "Turn = 1.\n  0\n0 t\n\n") == 0);
}

TEST(DarwinFixture, test_17) {
    Darwin d(1,1);

    Species trap('t');
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left");
    trap.addInstruction("go", 0);
    trap.addInstruction("infect");
    trap.addInstruction("go", 0);

    Creature t1(trap, east); // (west 0, north 1, east 2, south 3) 
    d.addCreature(t1, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(2);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  0\n0 t\n\n"
        "Turn = 1.\n  0\n0 t\n\n"
        "Turn = 2.\n  0\n0 t\n\n") == 0);
}

TEST(DarwinFixture, test_18) {
    Darwin d(2,2);

    Species trap('t');
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left");
    trap.addInstruction("go", 0);
    trap.addInstruction("infect");
    trap.addInstruction("go", 0);
    Creature t1(trap, east); // (west 0, north 1, east 2, south 3) 
    d.addCreature(t1, 0, 0);
    Creature t2(trap, west);
    d.addCreature(t2, 0, 1);
    
    Species hopper('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go", 0);
    Creature h1(hopper, south);
    d.addCreature(h1, 1, 0);
    Creature h2(hopper, north);
    d.addCreature(h2, 1, 1);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(2);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  01\n0 tt\n1 hh\n\n"
        "Turn = 1.\n  01\n0 tt\n1 hh\n\n"
        "Turn = 2.\n  01\n0 tt\n1 ht\n\n") == 0);
}

TEST(DarwinFixture, test_19) {
    Darwin d(2,2);
    
    Species hopper('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go", 0);
    Creature h1(hopper, south);
    d.addCreature(h1, 0, 0);
    Creature h2(hopper, north);
    d.addCreature(h2, 1, 1);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(2);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  01\n0 h.\n1 .h\n\n"
        "Turn = 1.\n  01\n0 .h\n1 h.\n\n"
        "Turn = 2.\n  01\n0 .h\n1 h.\n\n") == 0);
}

TEST(DarwinFixture, test_20) {
    Darwin d(4,4);

    Species r('r');
    r.addInstruction("if_enemy", 9);
    r.addInstruction("if_empty", 7);
    r.addInstruction("if_random", 5);
    r.addInstruction("left");
    r.addInstruction("go", 0);
    r.addInstruction("right");
    r.addInstruction("go", 0);
    r.addInstruction("hop");
    r.addInstruction("go", 0);
    r.addInstruction("infect");
    r.addInstruction("go", 0);

    Species b('b');
    b.addInstruction("if_enemy", 9);
    b.addInstruction("if_empty", 7);
    b.addInstruction("if_random", 5);
    b.addInstruction("right");
    b.addInstruction("go", 0);
    b.addInstruction("left");
    b.addInstruction("go", 0);
    b.addInstruction("hop");
    b.addInstruction("go", 0);
    b.addInstruction("infect");
    b.addInstruction("go", 0);

    Creature r1(r, south);
    d.addCreature(r1, 3, 3);
    Creature b1(b, south);
    d.addCreature(b1, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(4);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare(
        "Turn = 0.\n  0123\n0 b...\n1 ....\n2 ....\n3 ...r\n\n"
        "Turn = 1.\n  0123\n0 ....\n1 b...\n2 ....\n3 ...r\n\n"
        "Turn = 2.\n  0123\n0 ....\n1 ....\n2 b...\n3 ..r.\n\n"
        "Turn = 3.\n  0123\n0 ....\n1 ....\n2 ....\n3 br..\n\n"
        "Turn = 4.\n  0123\n0 ....\n1 ....\n2 ....\n3 rr..\n\n") == 0);
}

TEST(DarwinFixture, test_21) {
    Darwin d(4,4);

    Species r('r');
    r.addInstruction("if_enemy", 9);
    r.addInstruction("if_empty", 7);
    r.addInstruction("if_random", 5);
    r.addInstruction("left");
    r.addInstruction("go", 0);
    r.addInstruction("right");
    r.addInstruction("go", 0);
    r.addInstruction("hop");
    r.addInstruction("go", 0);
    r.addInstruction("infect");
    r.addInstruction("go", 0);

    Species b('b');
    b.addInstruction("if_enemy", 6);
    b.addInstruction("if_empty", 4);
    b.addInstruction("right");
    b.addInstruction("go", 0);
    b.addInstruction("hop");
    b.addInstruction("go", 0);
    b.addInstruction("infect");
    b.addInstruction("go", 0);

    Creature r1(r, south);
    d.addCreature(r1, 3, 3);
    Creature b1(b, south);
    d.addCreature(b1, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(4);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare(
        "Turn = 0.\n  0123\n0 b...\n1 ....\n2 ....\n3 ...r\n\n"
        "Turn = 1.\n  0123\n0 ....\n1 b...\n2 ....\n3 ...r\n\n"
        "Turn = 2.\n  0123\n0 ....\n1 ....\n2 b...\n3 ..r.\n\n"
        "Turn = 3.\n  0123\n0 ....\n1 ....\n2 ....\n3 br..\n\n"
        "Turn = 4.\n  0123\n0 ....\n1 ....\n2 ....\n3 rr..\n\n") == 0);
}

TEST(DarwinFixture, test_22) {
    Darwin d(4,4);

    Species r('r');
    r.addInstruction("if_enemy", 9);
    r.addInstruction("if_empty", 7);
    r.addInstruction("if_random", 5);
    r.addInstruction("left");
    r.addInstruction("go", 0);
    r.addInstruction("right");
    r.addInstruction("go", 0);
    r.addInstruction("hop");
    r.addInstruction("go", 0);
    r.addInstruction("infect");
    r.addInstruction("go", 0);

    Species b('b');
    b.addInstruction("if_enemy", 6);
    b.addInstruction("if_empty", 4);
    b.addInstruction("right");
    b.addInstruction("go", 0);
    b.addInstruction("hop");
    b.addInstruction("go", 0);
    b.addInstruction("infect");
    b.addInstruction("go", 0);

    Creature r1(r, south);
    d.addCreature(r1, 0, 0);
    Creature b1(b, south);
    d.addCreature(b1, 3, 3);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(4);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare(
        "Turn = 0.\n  0123\n0 r...\n1 ....\n2 ....\n3 ...b\n\n"
        "Turn = 1.\n  0123\n0 ....\n1 r...\n2 ....\n3 ...b\n\n"
        "Turn = 2.\n  0123\n0 ....\n1 ....\n2 r...\n3 ..b.\n\n"
        "Turn = 3.\n  0123\n0 ....\n1 ....\n2 ....\n3 rb..\n\n"
        "Turn = 4.\n  0123\n0 ....\n1 ....\n2 ....\n3 bb..\n\n") == 0);
}

TEST(DarwinFixture, test_23) {
    Darwin d(2,2);
    string action = "hop";
    string inFront = "enemy";
    ASSERT_FALSE(d.actionValid(action, inFront));
}

TEST(DarwinFixture, test_24) {
    Darwin d(2,2);
    string action = "hop";
    string inFront = "";
    ASSERT_TRUE(d.actionValid(action, inFront));
}

TEST(DarwinFixture, test_25) {
    Darwin d(2,2);
    string action = "infect";
    string inFront = "enemy";
    ASSERT_TRUE(d.actionValid(action, inFront));
}

TEST(DarwinFixture, test_26) {
    Darwin d(2,2);
    string action = "infect";
    string inFront = "";
    ASSERT_FALSE(d.actionValid(action, inFront));
}

TEST(DarwinFixture, test_27) {
    Darwin d(2,2);
    string action = "right";
    string inFront = "enemy";
    ASSERT_TRUE(d.actionValid(action, inFront));
}

TEST(DarwinFixture, test_28) {
    Darwin d(1,1);

    Species hopper('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go", 0);
    Creature h1(hopper, south);
    d.addCreature(h1, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(1);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  0\n0 h\n\n"
        "Turn = 1.\n  0\n0 h\n\n") == 0);
}

TEST(DarwinFixture, test_29) {
    Darwin d(1,1);

    Species best('b');
    best.addInstruction("if_enemy", 10);    //0
    best.addInstruction("if_empty", 12);    //1
    best.addInstruction("right");           //2
    best.addInstruction("if_enemy", 10);    //3
    best.addInstruction("if_empty", 12);    //4
    best.addInstruction("if_random", 8);    //5
    best.addInstruction("right");           //6
    best.addInstruction("go", 0);           //7
    best.addInstruction("right");            //8
    best.addInstruction("go", 0);           //9
    best.addInstruction("infect");          //10
    best.addInstruction("go", 0);           //11
    best.addInstruction("hop");             //12
    best.addInstruction("go", 0);           //13
    Creature b1(best, south);
    d.addCreature(b1, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(5);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  0\n0 b\n\n"
        "Turn = 1.\n  0\n0 b\n\n"
        "Turn = 2.\n  0\n0 b\n\n"
        "Turn = 3.\n  0\n0 b\n\n"
        "Turn = 4.\n  0\n0 b\n\n"
        "Turn = 5.\n  0\n0 b\n\n") == 0);
}

TEST(DarwinFixture, test_30) {
    Darwin d(4,4);

    Species best('b');
    best.addInstruction("if_enemy", 10);    //0
    best.addInstruction("if_empty", 12);    //1
    best.addInstruction("right");           //2
    best.addInstruction("if_enemy", 10);    //3
    best.addInstruction("if_empty", 12);    //4
    best.addInstruction("if_random", 8);    //5
    best.addInstruction("right");           //6
    best.addInstruction("go", 0);           //7
    best.addInstruction("right");            //8
    best.addInstruction("go", 0);           //9
    best.addInstruction("infect");          //10
    best.addInstruction("go", 0);           //11
    best.addInstruction("hop");             //12
    best.addInstruction("go", 0);           //13
    Creature b1(best, south);
    d.addCreature(b1, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(5);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare(
        "Turn = 0.\n  0123\n0 b...\n1 ....\n2 ....\n3 ....\n\n"
        "Turn = 1.\n  0123\n0 ....\n1 b...\n2 ....\n3 ....\n\n"
        "Turn = 2.\n  0123\n0 ....\n1 ....\n2 b...\n3 ....\n\n"
        "Turn = 3.\n  0123\n0 ....\n1 ....\n2 ....\n3 b...\n\n"
        "Turn = 4.\n  0123\n0 ....\n1 ....\n2 ....\n3 b...\n\n"
        "Turn = 5.\n  0123\n0 ....\n1 ....\n2 ....\n3 b...\n\n") == 0);
}

TEST(DarwinFixture, test_31) {
    Darwin d(4,4);

    Species rover('r');
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left");
    rover.addInstruction("go", 0);
    rover.addInstruction("right");
    rover.addInstruction("go", 0);
    rover.addInstruction("hop");
    rover.addInstruction("go", 0);
    rover.addInstruction("infect");
    rover.addInstruction("go", 0);

    Creature r1(rover, south);
    d.addCreature(r1, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(5);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare(
        "Turn = 0.\n  0123\n0 r...\n1 ....\n2 ....\n3 ....\n\n"
        "Turn = 1.\n  0123\n0 ....\n1 r...\n2 ....\n3 ....\n\n"
        "Turn = 2.\n  0123\n0 ....\n1 ....\n2 r...\n3 ....\n\n"
        "Turn = 3.\n  0123\n0 ....\n1 ....\n2 ....\n3 r...\n\n"
        "Turn = 4.\n  0123\n0 ....\n1 ....\n2 ....\n3 r...\n\n"
        "Turn = 5.\n  0123\n0 ....\n1 ....\n2 ....\n3 .r..\n\n") == 0);
}

TEST(DarwinFixture, test_32) {
    Darwin d(1,1);

    Species rover('r');
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left");
    rover.addInstruction("go", 0);
    rover.addInstruction("right");
    rover.addInstruction("go", 0);
    rover.addInstruction("hop");
    rover.addInstruction("go", 0);
    rover.addInstruction("infect");
    rover.addInstruction("go", 0);

    Creature r1(rover, south);
    d.addCreature(r1, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(5);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  0\n0 r\n\n"
        "Turn = 1.\n  0\n0 r\n\n"
        "Turn = 2.\n  0\n0 r\n\n"
        "Turn = 3.\n  0\n0 r\n\n"
        "Turn = 4.\n  0\n0 r\n\n"
        "Turn = 5.\n  0\n0 r\n\n") == 0);
}

TEST(DarwinFixture, test_33) {
    Darwin d(1,1);

    Species trap('t');
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left");
    trap.addInstruction("go", 0);
    trap.addInstruction("infect");
    trap.addInstruction("go", 0);
    Creature t1(trap, east); // (west 0, north 1, east 2, south 3) 
    d.addCreature(t1, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(5);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  0\n0 t\n\n"
        "Turn = 1.\n  0\n0 t\n\n"
        "Turn = 2.\n  0\n0 t\n\n"
        "Turn = 3.\n  0\n0 t\n\n"
        "Turn = 4.\n  0\n0 t\n\n"
        "Turn = 5.\n  0\n0 t\n\n") == 0);
}

TEST(DarwinFixture, test_34) {
    Species trap('t');
    Creature t1(trap, east);
    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    t1.print();
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("t") == 0);
}

TEST(DarwinFixture, test_35) {
    Species hopper('h');
    Creature h1(hopper, east);
    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    h1.print();
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("h") == 0);
}

TEST(DarwinFixture, test_36) {
    Species s('r');
    Creature c(s, east);
    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    c.print();
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("r") == 0);
}

TEST(DarwinFixture, test_37) {
    Species s('f');
    Creature c(s, east);
    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    c.print();
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("f") == 0);
}

TEST(DarwinFixture, test_38) {
    Species s('b');
    Creature c(s, east);
    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    c.print();
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("b") == 0);
}

TEST(DarwinFixture, test_39) {
    Darwin d(2,2);

    Species trap('t');
    trap.addInstruction("if_enemy", 3);
    trap.addInstruction("left");
    trap.addInstruction("go", 0);
    trap.addInstruction("infect");
    trap.addInstruction("go", 0);
    Creature t1(trap, east); // (west 0, north 1, east 2, south 3) 
    d.addCreature(t1, 0, 0);

    Species food('f');
    food.addInstruction("left");
    food.addInstruction("go", 0);
    Creature f1(food, west);
    d.addCreature(f1, 0, 1);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(1);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  01\n0 tf\n1 ..\n\n"
        "Turn = 1.\n  01\n0 tt\n1 ..\n\n") == 0);
}

TEST(DarwinFixture, test_40) {
    Darwin d(2,2);

    Species rover('r');
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left");
    rover.addInstruction("go", 0);
    rover.addInstruction("right");
    rover.addInstruction("go", 0);
    rover.addInstruction("hop");
    rover.addInstruction("go", 0);
    rover.addInstruction("infect");
    rover.addInstruction("go", 0);
    Creature r1(rover, east);
    d.addCreature(r1, 0, 0);

    Species food('f');
    food.addInstruction("left");
    food.addInstruction("go", 0);
    Creature f1(food, west);
    d.addCreature(f1, 0, 1);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(1);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare("Turn = 0.\n  01\n0 rf\n1 ..\n\n"
        "Turn = 1.\n  01\n0 rr\n1 ..\n\n") == 0);
}

TEST(DarwinFixture, test_41) {
    Darwin d(2,2);

    Species rover('r');
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left");
    rover.addInstruction("go", 0);
    rover.addInstruction("right");
    rover.addInstruction("go", 0);
    rover.addInstruction("hop");
    rover.addInstruction("go", 0);
    rover.addInstruction("infect");
    rover.addInstruction("go", 0);
    Creature r1(rover, east);
    d.addCreature(r1, 1, 0);

    Species food('f');
    food.addInstruction("left");
    food.addInstruction("go", 0);
    Creature f1(food, west);
    d.addCreature(f1, 0, 1);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(5);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare(
        "Turn = 0.\n  01\n0 .f\n1 r.\n\n"
        "Turn = 1.\n  01\n0 .f\n1 .r\n\n"
        "Turn = 2.\n  01\n0 .f\n1 .r\n\n"
        "Turn = 3.\n  01\n0 .f\n1 .r\n\n"
        "Turn = 4.\n  01\n0 .f\n1 .r\n\n"
        "Turn = 5.\n  01\n0 .r\n1 .r\n\n") == 0);
}

TEST(DarwinFixture, test_42) {
    Darwin d(2,2);

    Species rover('r');
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left");
    rover.addInstruction("go", 0);
    rover.addInstruction("right");
    rover.addInstruction("go", 0);
    rover.addInstruction("hop");
    rover.addInstruction("go", 0);
    rover.addInstruction("infect");
    rover.addInstruction("go", 0);
    Creature r1(rover, east);
    d.addCreature(r1, 0, 0);

    Species food('f');
    food.addInstruction("left");
    food.addInstruction("go", 0);
    Creature f1(food, west);
    d.addCreature(f1, 0, 1);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(1);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare(
        "Turn = 0.\n  01\n0 rf\n1 ..\n\n"
        "Turn = 1.\n  01\n0 rr\n1 ..\n\n") == 0);
}

TEST(DarwinFixture, test_43) {
    Darwin d(2,2);

    Species rover('r');
    rover.addInstruction("if_enemy", 9);
    rover.addInstruction("if_empty", 7);
    rover.addInstruction("if_random", 5);
    rover.addInstruction("left");
    rover.addInstruction("go", 0);
    rover.addInstruction("right");
    rover.addInstruction("go", 0);
    rover.addInstruction("hop");
    rover.addInstruction("go", 0);
    rover.addInstruction("infect");
    rover.addInstruction("go", 0);
    Creature r1(rover, east);
    d.addCreature(r1, 1, 1);

    Species food('f');
    food.addInstruction("left");
    food.addInstruction("go", 0);
    Creature f1(food, west);
    d.addCreature(f1, 0, 1);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(2);
    cout.rdbuf(old_buf);
    ASSERT_TRUE(ss.str().compare(
        "Turn = 0.\n  01\n0 .f\n1 .r\n\n"
        "Turn = 1.\n  01\n0 .f\n1 .r\n\n"
        "Turn = 2.\n  01\n0 .r\n1 .r\n\n") == 0);
}

TEST(DarwinFixture, test_44) {
    Darwin d(2,2);

    Species s('c');
    s.addInstruction("left");
    s.addInstruction("go", 0);
    Creature c(s, south);
    d.addCreature(c, 0, 0);

    stringstream ss;
    auto old_buf = cout.rdbuf(ss.rdbuf());
    d.startGame(5);
    cout.rdbuf(old_buf);

    ASSERT_TRUE(ss.str().compare(
        "Turn = 0.\n  01\n0 c.\n1 ..\n\n"
        "Turn = 1.\n  01\n0 c.\n1 ..\n\n"
        "Turn = 2.\n  01\n0 c.\n1 ..\n\n"
        "Turn = 3.\n  01\n0 c.\n1 ..\n\n"
        "Turn = 4.\n  01\n0 c.\n1 ..\n\n"
        "Turn = 5.\n  01\n0 c.\n1 ..\n\n") == 0);
}

TEST(DarwinFixture, test_45) {
    Darwin d(2,2);
    Species s('c');
    Creature c(s, south);
    d.addCreature(c, 0, 0);
    ASSERT_TRUE(c.lookAhead(d).compare("") == 0);
}

TEST(DarwinFixture, test_46) {
    Darwin d(2,2);
    Species s('c');
    Creature c(s, north);
    d.addCreature(c, 0, 0);
    ASSERT_TRUE(c.lookAhead(d).compare("wall") == 0);
}

TEST(DarwinFixture, test_47) {
    Darwin d(2,2);
    Species s('c');
    Creature c(s, east);
    d.addCreature(c, 0, 0);
    ASSERT_TRUE(c.lookAhead(d).compare("") == 0);
}

TEST(DarwinFixture, test_48) {
    Darwin d(2,2);
    Species s('c');
    Creature c(s, east);
    d.addCreature(c, 1, 0);
    ASSERT_TRUE(c.lookAhead(d).compare("") == 0);
}

TEST(DarwinFixture, test_49) {
    Darwin d(2,2);
    Species s('c');
    Creature c(s, west);
    d.addCreature(c, 0, 1);
    ASSERT_TRUE(c.lookAhead(d).compare("wall") == 0);
}

TEST(DarwinFixture, test_50) {
    Darwin d(2,2);
    Species s('c');
    Creature c(s, west);
    d.addCreature(c, 1, 1);
    ASSERT_TRUE(c.lookAhead(d).compare("wall") == 0);
}
