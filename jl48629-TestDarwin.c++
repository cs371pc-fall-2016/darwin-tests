// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------


#include <sstream>  // istringtstream, ostringstream
#include "Darwin.h"
// #include <cstdlib> // rand, srand

using namespace std;

// -------------------
//  tests for Species
// -------------------

TEST(SpeciesFixture, ConstructorTest1) {
    Species x('f');
    ASSERT_EQ(x.program.size(), 0);
    ASSERT_EQ(x._symbol, 'f');
}

TEST(SpeciesFixture, ConstructorTest2) {
    Species x('d');
    x.addInstruction(HOP);
    ASSERT_EQ(x.program.size(), 1);
    ASSERT_EQ(x._symbol, 'd');
}

TEST(SpeciesFixture, ConstructorTest3) {
    Species x('z');
    ASSERT_EQ(x._symbol, 'z');
}

TEST(SpeciesFixture, AddInstructionTest1) {
    Species x('f');
    x.addInstruction(HOP);
    x.addInstruction(HOP);
    x.addInstruction(HOP);
    ASSERT_EQ(x.program.size(), 3);
    ASSERT_EQ(get<0>(x.program.at(0)), HOP);
}

TEST(SpeciesFixture, AddInstructionTest2) {
    Species x('b');
    x.addInstruction(IF_EMPTY, 2);
    x.addInstruction(IF_ENEMY, 4);
    x.addInstruction(HOP);
    x.addInstruction(GO, 0);
    x.addInstruction(INFECT);
    x.addInstruction(GO, 0);
    ASSERT_EQ(x.program.size(), 6);
    ASSERT_EQ(get<0>(x.program.at(0)), IF_EMPTY);
    ASSERT_EQ(get<1>(x.program.at(0)), 2);
}

TEST(SpeciesFixture, AddInstructionTest3) {
    Species x('g');
    x.addInstruction(HOP);
    ASSERT_EQ(get<0>(x.currentInstruction(0)), HOP);
}

TEST(SpeciesFixture, CurrentInstructionTest1) {
    Species x('f');
    x.addInstruction(LEFT);
    x.addInstruction(GO, 0);
    tuple<Instruction, uint32_t> info = x.currentInstruction(0);
    ASSERT_EQ(get<0>(info), LEFT);
    info = x.currentInstruction(1);
    ASSERT_EQ(get<0>(info), GO);
}

TEST(SpeciesFixture, CurrentInstructionTest2) {
    Species x('f');
    bool caught_exception = false;
    try {
        x.currentInstruction(5);
        assert(false);
    } catch (const std::invalid_argument& e) {
        caught_exception = true;
    }
    
    ASSERT_TRUE(caught_exception);
}

TEST(SpeciesFixture, CurrentInstructionTest3) {
    Species x('t');
    x.addInstruction(HOP);
    x.addInstruction(HOP);
    x.addInstruction(GO, 0);
    
    ASSERT_EQ(get<0>(x.currentInstruction(2)), get<0>(x.program.at(2)));
}

TEST(SpeciesFixture, PrintTest1) {
    Species x('f');
    ostringstream w;
    w << x;
    ASSERT_EQ(w.str(), "f");
}

TEST(SpeciesFixture, PrintTest2) {
    Species x('f');
    ostringstream w;
    w << x;
    w << x;
    w << x;
    ASSERT_EQ(w.str(), "fff");
}

TEST(SpeciesFixture, PrintTest3) {
    Species x('f');
    Species y('h');
    ostringstream w;
    w << x << y << y << x;
    ASSERT_EQ(w.str(), "fhhf");
}

// ---------------------
//  tests for Creatures
// ---------------------

TEST(CreatureFixture, DefaultConstructorTest1) {
    Creature x;
    ASSERT_EQ(x._s, nullptr);
    ASSERT_EQ(x._d, WEST);
    ASSERT_EQ(x.moved, false);
    ASSERT_EQ(x.pc, 0);
    ASSERT_EQ(x.pc, x.possible_pc);
}  

TEST(CreatureFixture, DefaultConstructorTest2) {
    Creature x;
    Creature y;
    ASSERT_EQ(x._s, nullptr);
    ASSERT_EQ(x._s, y._s);
    ASSERT_EQ(x.moved, false);
    ASSERT_EQ(x.moved, y.moved);
}  

TEST(CreatureFixture, DefaultConstructorTest3) {
    Creature x;
    x.turn_left();
    ASSERT_EQ(x._d, SOUTH);
}  

TEST(CreatureFixture, ConstructorTest1) {
    Species x('f');
    Creature y(&x, WEST);
    ASSERT_EQ(y._s, &x);
}  

TEST(CreatureFixture, ConstructorTest2) {
    Species x('f');
    Creature y(&x, NORTH);
    Creature z(&x, WEST);
    ASSERT_EQ(y._s, z._s);
    ASSERT_EQ(y.moved, z.moved);
}  

TEST(CreatureFixture, ConstructorTest3) {
    Species x('f');
    Creature y(&x, WEST);
    ostringstream w;
    w << y;
    ASSERT_EQ(w.str(), "f");
}  

TEST(CreatureFixture, ClearStateTest1) {
    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    Creature f1(&food, NORTH);
    ASSERT_FALSE(f1.moved);

    Creature **west_spot = nullptr, **north_spot = nullptr, **east_spot = nullptr, 
             **south_spot = nullptr, **my_spot = nullptr;
    f1.execute_instructions(make_tuple(west_spot, north_spot, east_spot, south_spot, my_spot));
    ASSERT_TRUE(f1.moved);
    f1.clear_state();
    ASSERT_FALSE(f1.moved);
}   

TEST(CreatureFixture, ClearStateTest2) {
    Creature f1;
    ASSERT_FALSE(f1.moved);
    f1.moved = true;
    ASSERT_TRUE(f1.moved);
    f1.clear_state();
    ASSERT_FALSE(f1.moved);
}

TEST(CreatureFixture, ClearStateTest3) {
    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    Creature f1(&food, NORTH);
    ASSERT_FALSE(f1.moved);

    Creature **west_spot = nullptr, **north_spot = nullptr, **east_spot = nullptr, 
             **south_spot = nullptr, **my_spot = nullptr;
    f1.execute_instructions(make_tuple(west_spot, north_spot, east_spot, south_spot, my_spot));
    ASSERT_TRUE(f1.moved);
    f1.execute_instructions(make_tuple(west_spot, north_spot, east_spot, south_spot, my_spot));
    ASSERT_TRUE(f1.moved);
    f1.clear_state();
    ASSERT_FALSE(f1.moved);
}

TEST(CreatureFixture, PerformInstructionTests1) {
    Species food('f');
    Creature c1(&food, WEST);
    Creature **west_spot = nullptr, **north_spot = nullptr, **east_spot = nullptr, 
             **south_spot = nullptr, **my_spot = nullptr;
    Creature *test_board [3][3];
    for (int r=0; r< 3; ++r)
        for (int c=0; c<3; ++c)
            test_board[r][c] = nullptr;
    // place c1 on the board.    
    test_board[1][1] = &c1;

    tuple<Creature**, Creature**,Creature**, Creature**, Creature**> surroundings;
    surroundings = make_tuple(west_spot, north_spot, east_spot, south_spot, my_spot);
    /* TESTING HOP INSTRUCTION */
    ASSERT_TRUE(c1.perform_instruction(HOP, surroundings));

    west_spot = &test_board[1][0];
    my_spot = &test_board[1][1];
    surroundings = make_tuple(west_spot, north_spot, east_spot, south_spot, my_spot);

    ASSERT_EQ(test_board[1][1], &c1);
    ASSERT_EQ(test_board[1][0], nullptr);
    ASSERT_TRUE(c1.perform_instruction(HOP, surroundings));
    ASSERT_EQ(test_board[1][1], nullptr);
    ASSERT_EQ(test_board[1][0], &c1);

    /* TESTING TURN_LEFT AND TURN_RIGHT */
    c1.perform_instruction(LEFT, surroundings);
    ASSERT_EQ(c1._d, SOUTH);
    c1.perform_instruction(LEFT, surroundings);
    ASSERT_EQ(c1._d, EAST);
    c1.perform_instruction(LEFT, surroundings);
    ASSERT_EQ(c1._d, NORTH);
    c1.perform_instruction(LEFT, surroundings);
    ASSERT_EQ(c1._d, WEST);
    c1.perform_instruction(RIGHT, surroundings);
    ASSERT_EQ(c1._d, NORTH);
}   

TEST(CreatureFixture, PerformInstructionTests2) {
    Species food('f');
    Species hopper('h');
    Creature c1(&food, WEST);
    Creature c2(&hopper, WEST);
    Creature **west_spot = nullptr, **north_spot = nullptr, **east_spot = nullptr, 
             **south_spot = nullptr, **my_spot = nullptr;
    Creature *test_board [3][3];
    for (int r=0; r< 3; ++r)
        for (int c=0; c<3; ++c)
            test_board[r][c] = nullptr;
    
    test_board[1][1] = &c1;
    west_spot = &test_board[1][0];
    my_spot = &test_board[1][1];

    tuple<Creature**, Creature**,Creature**, Creature**, Creature**> surroundings;
    surroundings = make_tuple(west_spot, north_spot, east_spot, south_spot, my_spot);
    /* TESTING INFECT */
    ASSERT_EQ(test_board[1][0], nullptr);
    c1.perform_instruction(INFECT, surroundings);
    ASSERT_EQ(test_board[1][0], nullptr);

    test_board[1][0] = &c2;

    ASSERT_EQ(test_board[1][1]->_s, c1._s);
    ASSERT_EQ(test_board[1][0]->_s, c2._s);
    ASSERT_TRUE(c1.perform_instruction(INFECT, surroundings));
    ASSERT_EQ(test_board[1][1]->_s, c1._s);
    ASSERT_EQ(test_board[1][0]->_s, c1._s);
} 

TEST(CreatureFixture, PerformInstructionTests3) {
    Species food('f');
    Species hopper('h');
    Creature c1(&food, WEST);
    Creature c2(&hopper, WEST);
    Creature **west_spot = nullptr, **north_spot = nullptr, **east_spot = nullptr, 
             **south_spot = nullptr, **my_spot = nullptr;
    Creature *test_board [3][3];
    for (int r=0; r< 3; ++r)
        for (int c=0; c<3; ++c)
            test_board[r][c] = nullptr;
    
    test_board[1][1] = &c1;
    west_spot = &test_board[1][0];
    my_spot = &test_board[1][1];

    tuple<Creature**, Creature**,Creature**, Creature**, Creature**> surroundings;
    surroundings = make_tuple(west_spot, north_spot, east_spot, south_spot, my_spot);
    /* TESTING IF_EMPTY */
    c1.possible_pc = 2;
    ASSERT_EQ(c1.pc, 0);
    c1.perform_instruction(IF_EMPTY, surroundings);
    ASSERT_EQ(c1.pc, 2);

    /* TESTING IF_WALL */
    surroundings = make_tuple(nullptr, north_spot, east_spot, south_spot, my_spot);
    c1.possible_pc = 0;
    c1.perform_instruction(IF_WALL, surroundings);
    ASSERT_EQ(c1.pc, 0);

    /* TESTING IF_RANDOM */
    c1.possible_pc = 4;
    srand(0);
    c1.perform_instruction(IF_RANDOM, surroundings);
    ASSERT_EQ(c1.pc, 4);

    /* TESTING IF_ENEMY */
    c1.possible_pc = 0;
    test_board[1][0] = &c2;
    surroundings = make_tuple(west_spot, north_spot, east_spot, south_spot, my_spot);
    c1.perform_instruction(IF_ENEMY, surroundings);
    ASSERT_EQ(c1.pc, 0);

    /* TESTING GO */
    c1.possible_pc = 9;
    c1.perform_instruction(GO, surroundings);
    ASSERT_EQ(c1.pc, 9);
} 

// ----------------
// Tests for Darwin
// ----------------

TEST(DarwinFixture, inbound_tests) {
    Darwin d(10, 10);
    ASSERT_TRUE(d.inbound( 0,  0));
    ASSERT_TRUE(!d.inbound(-1,  0));
    ASSERT_TRUE(!d.inbound( 0, -1));
    ASSERT_TRUE(d.inbound( 9,  9));
    ASSERT_TRUE(!d.inbound(10,  9));
    ASSERT_TRUE(!d.inbound( 9, 10));
}

TEST(DarwinFixture, constructor_tests) {
    Darwin d1(10, 9);
    ASSERT_EQ(d1._m, 10);
    ASSERT_EQ(d1._n,  9);

    Darwin d2(0, 0);
    ASSERT_EQ(d2._m, 0);
    ASSERT_EQ(d2._n, 0);

    Darwin d3(0, 100);
    ASSERT_EQ(d3._m,   0);
    ASSERT_EQ(d3._n, 100);
}

TEST(DarwinFixture, add_creature_tests) {
    Darwin d1(10, 10);
    Creature* c = nullptr;
    d1.add_creature(c, 0, 0);
    ASSERT_TRUE(d1.board[0][0] == nullptr);

    Creature c2;
    d1.add_creature(&c2, 9, 9);
    ASSERT_TRUE(d1.board[9][9] != nullptr);

    d1.add_creature(&c2, 5, 5);
    ASSERT_TRUE(d1.board[5][5] != nullptr);
}

TEST(DarwinFixture, execute_turn_tests) {
    Darwin d(5, 5);
    Species hopper('h');
    hopper.addInstruction(HOP);
    hopper.addInstruction(GO, 0);
    Creature h(&hopper, NORTH);
    d.add_creature(&h, 3, 4);
    ASSERT_EQ(d.board[3][4], &h);
    for(int i = 0; i < 3; ++i) {
        d.execute_turn();
        ASSERT_EQ(d.board[2-i][4], &h);
        ASSERT_EQ(d.board[3-i][4], nullptr);
    }

    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    Creature f(&food, NORTH);
    d.add_creature(&f,4, 0);
    d.execute_turn();
    ASSERT_EQ(d.board[4][0]->_d, WEST);
    d.execute_turn();
    ASSERT_EQ(d.board[4][0]->_d, SOUTH);
}

TEST(DarwinFixture, overloaded_print_tests) {
    Darwin d(2, 2);
    ostringstream w;
    w << d;
    ASSERT_EQ(w.str(), "  01\n0 ..\n1 ..\n");

    Darwin d2(1, 1);
    ostringstream w2;
    w2 << d2;
    ASSERT_EQ(w2.str(), "  0\n0 .\n");

    Darwin d3(3, 3);
    ostringstream w3;
    w3 << d3;
    ASSERT_EQ(w3.str(), "  012\n0 ...\n1 ...\n2 ...\n");
}

TEST(CreatureFixture, overloaded_print_tests) {
    Species food('f');
    Creature f(&food, NORTH);

    ostringstream w;
    w << f;
    ASSERT_EQ(w.str(), "f");

    Species food_2('k');
    Creature f2(&food_2, NORTH);
    w << f2;
    ASSERT_EQ(w.str(), "fk");

    Species food_3('G');
    Creature f3(&food_3, NORTH);
    w << f3;
    ASSERT_EQ(w.str(), "fkG");
}

TEST(CreatureFixture, execute_instructions_tests) {
    Creature **west_spot = nullptr, **north_spot = nullptr, 
                         **east_spot = nullptr, **south_spot = nullptr, 
                         **my_spot = nullptr;
    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(LEFT);
    food.addInstruction(IF_EMPTY, 0);
    food.addInstruction(GO, 0);
    Creature creat(&food, NORTH);
    creat.execute_instructions(make_tuple(west_spot, north_spot, east_spot,
        south_spot, my_spot));
    ASSERT_EQ(creat.moved, true);
    ASSERT_EQ(creat._d, WEST);
    creat.clear_state();
    creat.execute_instructions(make_tuple(west_spot, north_spot, east_spot,
        south_spot, my_spot));
    ASSERT_EQ(creat._d, SOUTH);
    creat.clear_state();
    creat.execute_instructions(make_tuple(west_spot, north_spot, east_spot,
        south_spot, my_spot));
    ASSERT_EQ(creat._d, EAST);
}

TEST(CreatureFixture, fetch_instruction_tests) {
    Species trap('t');
    trap.addInstruction(IF_ENEMY, 3);
    trap.addInstruction(LEFT);
    trap.addInstruction(GO, 0);
    trap.addInstruction(INFECT);
    trap.addInstruction(GO, 0);
    Creature creature(&trap, NORTH);
    Instruction currentInstruction = creature.fetch_instruction();
    ASSERT_EQ(currentInstruction, IF_ENEMY);
    creature.pc = 1;
    currentInstruction = creature.fetch_instruction();
    ASSERT_EQ(currentInstruction, LEFT);
    creature.pc = 2;
    currentInstruction = creature.fetch_instruction();
    ASSERT_EQ(currentInstruction, GO);
    creature.pc = 3;
    currentInstruction = creature.fetch_instruction();
    ASSERT_EQ(currentInstruction, INFECT);
    creature.pc = 4;
    currentInstruction = creature.fetch_instruction();
    ASSERT_EQ(currentInstruction, GO);
}

TEST(CreatureFixture, turn_right_tests) {
    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    Creature creature(&food, NORTH);
    creature.turn_right();
    ASSERT_EQ(creature._d, EAST);
    creature.turn_right();
    ASSERT_EQ(creature._d, SOUTH);
    creature.turn_right();
    ASSERT_EQ(creature._d, WEST);
    creature.turn_right();
    ASSERT_EQ(creature._d, NORTH);
}

TEST(CreatureFixture, turn_left_tests) {
    Species food('f');
    food.addInstruction(LEFT);
    food.addInstruction(GO, 0);
    Creature creature(&food, NORTH);
    creature.turn_left();
    ASSERT_EQ(creature._d, WEST);
    creature.turn_left();
    ASSERT_EQ(creature._d, SOUTH);
    creature.turn_left();
    ASSERT_EQ(creature._d, EAST);
    creature.turn_left();
    ASSERT_EQ(creature._d, NORTH);
}
