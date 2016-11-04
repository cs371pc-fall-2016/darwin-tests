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

// TEST(DarwinFixture, test_1) {
//     Darwin x = Darwin(8,8);
//     x.print_board();
//     ASSERT_TRUE(true);}

// -----------
// Instruction
// -----------

/**
* Constructors
*/
TEST(Instruction_Constructor, test_1) {
    Instruction i = Instruction(1,1);
    ASSERT_TRUE(i.number == 1);}

TEST(Instruction_Constructor, test_2) {
    Instruction i = Instruction(1,1);
    ASSERT_TRUE(i.line == 1);}

TEST(Instruction_Constructor, test_3) {
    Instruction i = Instruction(2);
    ASSERT_TRUE(i.line == 0);}

TEST(Instruction_Constructor, test_4) {
    Instruction i = Instruction();
    ASSERT_TRUE(i.number == -1);}

TEST(Instruction_Constructor, test_5) {
    Instruction i = Instruction();
    ASSERT_TRUE(i.line == -1);}

TEST(Instruction_Constructor, test_6) {
    Instruction i = Instruction();
    ASSERT_TRUE(i.number == -1 && i.line == -1);}

/**
* is_control
*/

TEST(Instruction_is_control, test_1) {
    Instruction i = Instruction();
    ASSERT_FALSE(i.is_control());}

TEST(Instruction_is_control, test_2) {
    Instruction i = Instruction(HOP);
    ASSERT_FALSE(i.is_control());}

TEST(Instruction_is_control, test_3) {
    Instruction i = Instruction(IF_EMPTY);
    ASSERT_TRUE(i.is_control());}

/**
* is_valid_number
*/

TEST(Instruction_is_valid_number, test_1) {
    Instruction i = Instruction();
    ASSERT_FALSE(i.is_valid_number());}

TEST(Instruction_is_valid_number, test_2) {
    Instruction i = Instruction(INFECT);
    ASSERT_TRUE(i.is_valid_number());}

TEST(Instruction_is_valid_number, test_3) {
    Instruction i = Instruction(GO);
    ASSERT_TRUE(i.is_valid_number());}

// -------
// Species
// -------

/**
* Constructors
*/

TEST(Species_Constructor, test_1) {
    Species s = Species();
    ASSERT_TRUE(s.type == '.');}

TEST(Species_Constructor, test_2) {
    Species s = Species('s');
    ASSERT_TRUE(s.type == 's');}

TEST(Species_Constructor, test_3) {
    Species s = Species('t');
    ASSERT_TRUE(s.type == 't');}

TEST(Species_Constructor, test_4) {
    Species s = Species('.');
    ASSERT_TRUE(s.type == '.');}

TEST(Species_Constructor, test_5) {
    Species s = Species('v');
    ASSERT_TRUE(s.type == 'v');}

TEST(Species_Constructor, test_6) {
    Species s = Species('1');
    ASSERT_TRUE(s.type == '1');}

/**
* bool == operator
*/

TEST(Species_equal, test_1) {
    Species s = Species();
    Species t = Species();
    ASSERT_TRUE(s == t);}

TEST(Species_equal, test_2) {
    Species s = Species('s');
    Species t = Species('s');
    ASSERT_TRUE(s == t);} 

TEST(Species_equal, test_3) {
    Species s = Species();
    Species t = Species('t');
    ASSERT_FALSE(s == t);} 

/**
* bool != operator
*/

TEST(Species_not_equal, test_1) {
    Species s = Species();
    Species t = Species();
    ASSERT_FALSE(s != t);}

TEST(Species_not_equal, test_2) {
    Species s = Species('s');
    Species t = Species('s');
    ASSERT_FALSE(s != t);} 

TEST(Species_not_equal, test_3) {
    Species s = Species();
    Species t = Species('t');
    ASSERT_TRUE(s != t);}

/**
* get_instruction
*/

TEST(Species_get_instruction, test_1) {
    Species s = Species('s');
    s.add_instruction(IF_ENEMY);
    ASSERT_TRUE(s.get_instruction(0).number == IF_ENEMY);}

TEST(Species_get_instruction, test_2) {
    Species s = Species('s');
    s.add_instruction(HOP);
    s.add_instruction(INFECT);
    s.add_instruction(IF_WALL);
    ASSERT_TRUE(s.get_instruction(1).number == INFECT);}

TEST(Species_get_instruction, test_3) {
    Species s = Species('s');
    s.add_instruction(HOP);
    s.add_instruction(INFECT);
    s.add_instruction(GO);
    try {
      Instruction i = s.get_instruction(3);
      if (i.number) {

      } 
      ASSERT_EQ(true, false);}
    catch (std::invalid_argument &e) {
      ASSERT_EQ(true, true);}}


/**
* add_instruction
*/

TEST(Species_add_instruction, test_1) {
    Species s = Species('s');
    s.add_instruction(HOP);
    ASSERT_TRUE(s.get_instruction(0).number == HOP);}

TEST(Species_add_instruction, test_2) {
    Species s = Species('s');
    s.add_instruction(HOP);
    s.add_instruction(INFECT);
    s.add_instruction(IF_WALL);
    ASSERT_TRUE(s.get_instruction(2).number == IF_WALL);}

TEST(Species_add_instruction, test_3) {
    Species s = Species('s');
    s.add_instruction(HOP);
    s.add_instruction(INFECT);
    s.add_instruction(IF_WALL);
    try {
      Instruction i = s.get_instruction(3);
      if (i.number) {

      } 
      ASSERT_EQ(true, false);}
    catch (std::invalid_argument &e) {
      ASSERT_EQ(true, true);}}

/**
* is_valid_line
*/

TEST(Species_is_valid_line, test_1) {
    Species s = Species('s');
    s.add_instruction(HOP);
    ASSERT_TRUE(s.is_valid_line(0));}

TEST(Species_is_valid_line, test_2) {
    Species s = Species('s');
    s.add_instruction(IF_ENEMY, 7);
    Instruction i = s.get_instruction(0);
    ASSERT_FALSE(s.is_valid_line(i.line));}

TEST(Species_is_valid_line, test_3) {
    Species s = Species('s');
    s.add_instruction(HOP);
    s.add_instruction(INFECT);
    s.add_instruction(IF_WALL);
    Instruction i = s.get_instruction(2);
    ASSERT_TRUE(s.is_valid_line(i.line));}


// --------
// Creature
// --------

/**
* Constructors
*/

TEST(Creature_Constructor, test_1) {
    Creature c = Creature();
    ASSERT_TRUE(c.specie.type == '.');}

TEST(Creature_Constructor, test_2) {
    Species s = Species('s');
    Creature c = Creature(s);
    ASSERT_TRUE(c.direction == NORTH);}

TEST(Creature_Constructor, test_3) {
    Species s = Species('t');
    Creature c = Creature(s, SOUTH);
    ASSERT_TRUE(c.direction == SOUTH);}

TEST(Creature_Constructor, test_4) {
    Creature c = Creature();
    ASSERT_TRUE(c.direction == NORTH);}

TEST(Creature_Constructor, test_5) {
    Species s = Species('t');
    Creature c = Creature(s, WEST);
    ASSERT_TRUE(c.direction == WEST);}

TEST(Creature_Constructor, test_6) {
    Species s = Species('t');
    Creature c = Creature(s, EAST);
    ASSERT_TRUE(c.direction == EAST);}

/**
* change_into
*/

TEST(Creature_change_into, test_1) {
    Creature c = Creature();
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    c.change_into(t);
    ASSERT_TRUE(c.specie.type == 's');}

TEST(Creature_change_into, test_2) {
    Creature c = Creature();
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    c.change_into(t);
    ASSERT_TRUE(c.direction == NORTH);}

TEST(Creature_change_into, test_3) {
    Creature c = Creature();
    c.turn_finished();
    c.turn_finished();
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    c.change_into(t);
    ASSERT_TRUE(c.counter == 0);}

/**
* not_completed_turn
*/

TEST(Creature_not_completed_turn, test_1) {
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    ASSERT_TRUE(t.not_completed_turn());}

TEST(Creature_not_completed_turn, test_2) {
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    t.turn_finished();
    ASSERT_FALSE(t.not_completed_turn());}

TEST(Creature_not_completed_turn, test_3) {
    Creature c = Creature();
    ASSERT_TRUE(c.not_completed_turn());}

/**
* turn_left
*/

TEST(Creature_turn_left, test_1) {
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    t.turn_left();
    ASSERT_TRUE(t.direction == EAST);}

TEST(Creature_turn_left, test_2) {
    Species s = Species('s');
    Creature t = Creature(s, WEST);
    t.turn_left();
    ASSERT_TRUE(t.direction == SOUTH);}

TEST(Creature_turn_left, test_3) {
    Species s = Species('s');
    Creature t = Creature(s, EAST);
    t.turn_left();
    ASSERT_TRUE(t.direction == NORTH);}

TEST(Creature_turn_left, test_4) {
    Species s = Species('s');
    Creature t = Creature(s, NORTH);
    t.turn_left();
    ASSERT_TRUE(t.direction == WEST);}

/**
* turn_right
*/

TEST(Creature_turn_right, test_1) {
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    t.turn_right();
    ASSERT_TRUE(t.direction == WEST);}

TEST(Creature_turn_right, test_2) {
    Species s = Species('s');
    Creature t = Creature(s, WEST);
    t.turn_right();
    ASSERT_TRUE(t.direction == NORTH);}

TEST(Creature_turn_right, test_3) {
    Species s = Species('s');
    Creature t = Creature(s, EAST);
    t.turn_right();
    ASSERT_TRUE(t.direction == SOUTH);}

TEST(Creature_turn_right, test_4) {
    Species s = Species('s');
    Creature t = Creature(s, NORTH);
    t.turn_right();
    ASSERT_TRUE(t.direction == EAST);}

/**
* turn_finished
*/

TEST(Creature_turn_finished, test_1) {
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    t.turn_finished();
    ASSERT_FALSE(t.not_completed_turn());} 

TEST(Creature_turn_finished, test_2) {
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    ASSERT_TRUE(t.not_completed_turn());}

TEST(Creature_turn_finised, test_1) {
    Creature t = Creature();
    t.turn_finished();
    ASSERT_FALSE(t.not_completed_turn());}     

/**
* turn_restart
*/

TEST(Creature_turn_restart, test_1) {
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    t.turn_restart();
    ASSERT_TRUE(t.not_completed_turn());} 

TEST(Creature_turn_restart, test_2) {
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    t.turn_finished();
    t.turn_restart();
    ASSERT_TRUE(t.not_completed_turn());}

TEST(Creature_turn_restart, test_3) {
    Creature t = Creature();
    t.turn_restart();
    t.turn_finished();
    t.turn_finished();
    t.turn_restart();
    ASSERT_TRUE(t.not_completed_turn());}  

/**
* reset_counter
*/

TEST(Creature_reset_counter, test_1) {
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    t.reset_counter();
    ASSERT_TRUE(t.counter == 0);} 

TEST(Creature_reset_counter, test_2) {
    Species s = Species('s');
    Creature t = Creature(s, SOUTH);
    t.turn_finished();
    t.reset_counter();
    ASSERT_TRUE(t.counter == 0);}

TEST(Creature_reset_counter, test_3) {
    Creature t = Creature();
    t.turn_finished();
    t.turn_finished();
    t.reset_counter();
    ASSERT_TRUE(t.counter == 0);} 

// ------
// Darwin
// ------

/**
* Constructors
*/

TEST(Darwin_Constructor, test_1) {
    Darwin x = Darwin();
    ASSERT_TRUE(x.height == 8 && x.width == 8);}

TEST(Darwin_Constructor, test_2) {
    Darwin x = Darwin(4,4);
    ASSERT_TRUE(x.height == 4 && x.width == 4);}  

TEST(Darwin_Constructor, test_3) {
    Darwin x = Darwin(4,6);
    ASSERT_TRUE(x.height == 4 && x.width == 6);}

TEST(Darwin_Constructor, test_4) {
    Darwin x = Darwin(6,4);
    ASSERT_TRUE(x.height == 6 && x.width == 4);}  

TEST(Darwin_Constructor, test_5) {
    Darwin x = Darwin(1000,1000);
    ASSERT_TRUE(x.height == 1000 && x.width == 1000);}

TEST(Darwin_Constructor, test_6) {
    Darwin x = Darwin(51, 52);
    ASSERT_TRUE(x.height == 51 && x.width == 52);}  

/**
* place
*/

TEST(Darwin_place, test_1) {
    Darwin x = Darwin();
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    ASSERT_TRUE(c.specie == x.board[4][4].specie);}

TEST(Darwin_place, test_2) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    try {
        x.place(c, 10, 4);
        ASSERT_EQ(false,true);}
    catch (std::invalid_argument &e){
        ASSERT_EQ(true,true);}}

TEST(Darwin_place, test_3) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    try {
        x.place(c, 4, 10);
        ASSERT_EQ(false,true);}
    catch (std::invalid_argument &e){
        ASSERT_EQ(true,true);}}

TEST(Darwin_place, test_4) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    try {
        x.place(c, 11, 4);
        ASSERT_EQ(false,true);}
    catch (std::invalid_argument &e){
        ASSERT_EQ(true,true);}}

TEST(Darwin_place, test_5) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    try {
        x.place(c, 0, 0);
        ASSERT_EQ(true,true);}
    catch (std::invalid_argument &e){
        ASSERT_EQ(false,true);}}

/**
* is_valid
*/

TEST(Darwin_is_valid, test_1) {
    Darwin x = Darwin();
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    ASSERT_TRUE(x.is_valid(5,4));}

TEST(Darwin_is_valid, test_2) {
    Darwin x = Darwin();
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    ASSERT_FALSE(x.is_valid(4,4));}

TEST(Darwin_is_valid, test_3) {
    Darwin x = Darwin();
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    ASSERT_FALSE(x.is_valid(-1,-1));}

TEST(Darwin_is_valid, test_4) {
    Darwin x = Darwin();
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    ASSERT_FALSE(x.is_valid(8,-1));}

/**
* is_wall
*/

TEST(Darwin_is_wall, test_1) {
    Darwin x = Darwin();
    ASSERT_FALSE(x.is_wall(0,4));}

TEST(Darwin_is_wall, test_2) {
    Darwin x = Darwin();
    ASSERT_FALSE(x.is_wall(4,0));}

TEST(Darwin_is_wall, test_3) {
    Darwin x = Darwin();
    ASSERT_TRUE(x.is_wall(8,4));}

TEST(Darwin_is_wall, test_4) {
    Darwin x = Darwin();
    ASSERT_TRUE(x.is_wall(0,8));}

TEST(Darwin_is_wall, test_5) {
    Darwin x = Darwin();
    ASSERT_TRUE(x.is_wall(-1,-1));}

TEST(Darwin_is_wall, test_6) {
    Darwin x = Darwin();
    ASSERT_TRUE(x.is_wall(8,8));}

/**
* is_creature
*/

TEST(Darwin_is_creature, test_1) {
    Darwin x = Darwin();
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    ASSERT_TRUE(x.is_creature(4,4));}

TEST(Darwin_is_creature, test_2) {
    Darwin x = Darwin();
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    ASSERT_FALSE(x.is_creature(5,4));}

TEST(Darwin_is_creature, test_3) {
    Darwin x = Darwin();
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    ASSERT_FALSE(x.is_creature(-1,-1));}

TEST(Darwin_is_creature, test_4) {
    Darwin x = Darwin();
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    ASSERT_FALSE(x.is_creature(8,8));}

/**
* is_enemy
*/

TEST(Darwin_is_enemy, test_1) {
    Darwin x = Darwin();
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    Creature p = Creature(s, SOUTH);
    x.place(c, 4, 4);
    x.place(p, 5, 4);
    ASSERT_FALSE(x.is_enemy(4,5,c.specie));}

TEST(Darwin_is_enemy, test_2) {
    Darwin x = Darwin();
    Species s = Species('s');
    Species r = Species('r');
    Creature c = Creature(s, SOUTH);
    Creature p = Creature(r, SOUTH);
    x.place(c, 4, 4);
    x.place(p, 5, 4);
    ASSERT_TRUE(x.is_enemy(4,5,c.specie));}

TEST(Darwin_is_enemy, test_3) {
    Darwin x = Darwin();
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    ASSERT_FALSE(x.is_enemy(4,5,c.specie));}

/**
* hop
*/

TEST(Darwin_hop, test_1) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(HOP);
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    x.hop(4,4);
    ASSERT_TRUE(x.is_creature(4,5) && !x.is_creature(4,4));}

TEST(Darwin_hop, test_2) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(HOP);
    Creature c = Creature(s, NORTH);
    x.place(c, 4, 4);
    x.hop(4,4);
    ASSERT_TRUE(x.is_creature(4,3) && !x.is_creature(4,4));}

TEST(Darwin_hop, test_3) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(HOP);
    Creature c = Creature(s, WEST);
    x.place(c, 4, 4);
    x.hop(4,4);
    ASSERT_TRUE(x.is_creature(3,4) && !x.is_creature(4,4));}

TEST(Darwin_hop, test_4) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(HOP);
    Creature c = Creature(s, EAST);
    x.place(c, 4, 4);
    x.hop(4,4);
    ASSERT_TRUE(x.is_creature(5,4) && !x.is_creature(4,4));}

TEST(Darwin_hop, test_5) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(HOP);
    Creature c = Creature(s, WEST);
    x.place(c, 0, 0);
    x.hop(0,0);
    ASSERT_TRUE(x.is_creature(0,0));}

TEST(Darwin_hop, test_6) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(HOP);
    Creature c = Creature(s, EAST);
    x.place(c, 9, 9);
    x.hop(9,9);
    ASSERT_TRUE(x.is_creature(9,9));}

/**
* infect
*/

TEST(Darwin_infect, test_1) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Species t = Species('t');
    t.add_instruction(LEFT);
    s.add_instruction(INFECT);
    Creature c = Creature(s, SOUTH);
    Creature d = Creature(t, SOUTH);
    x.place(c, 4, 4);
    x.place(d, 5, 4);
    x.infect(4,4);
    ASSERT_TRUE(x.board[4][4].specie == x.board[5][4].specie);}

TEST(Darwin_infect, test_2) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Species t = Species('t');
    t.add_instruction(LEFT);
    s.add_instruction(INFECT);
    Creature c = Creature(s, NORTH);
    Creature d = Creature(t, SOUTH);
    x.place(c, 4, 4);
    x.place(d, 5, 4);
    x.infect(4,4);
    ASSERT_FALSE(x.board[4][4].specie == x.board[5][4].specie);}

TEST(Darwin_infect, test_3) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Species t = Species('t');
    t.add_instruction(LEFT);
    s.add_instruction(INFECT);
    Creature c = Creature(s, NORTH);
    Creature d = Creature(t, SOUTH);
    x.place(c, 0, 0);
    x.place(d, 1, 0);
    x.infect(0,0);
    ASSERT_TRUE(x.board[1][0].specie == t);}


/**
* if_empty
*/

TEST(Darwin_if_empty, test_1) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_EMPTY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, SOUTH);
    x.place(c,4,4);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_empty(4,4,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_empty, test_2) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_EMPTY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, SOUTH);
    x.place(c,4,4);
    x.place(c,5,4);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_empty(4,4,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

TEST(Darwin_if_empty, test_3) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_EMPTY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, WEST);
    x.place(c,4,4);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_empty(4,4,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_empty, test_4) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_EMPTY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, WEST);
    x.place(c,4,4);
    x.place(c,4,3);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_empty(4,4,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

TEST(Darwin_if_empty, test_5) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_EMPTY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, EAST);
    x.place(c,4,4);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_empty(4,4,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_empty, test_6) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_EMPTY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, EAST);
    x.place(c,4,4);
    x.place(c,4,5);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_empty(4,4,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

TEST(Darwin_if_empty, test_7) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_EMPTY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, NORTH);
    x.place(c,4,4);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_empty(4,4,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_empty, test_8) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_EMPTY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, NORTH);
    x.place(c,4,4);
    x.place(c,3,4);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_empty(4,4,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

/**
* if_wall
*/

TEST(Darwin_if_wall, test_1) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_WALL, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, NORTH);
    x.place(c,0,0);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_wall(0,0,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_wall, test_2) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_WALL, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, NORTH);
    x.place(c,1,1);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_wall(1,1,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

TEST(Darwin_if_wall, test_3) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_WALL, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, SOUTH);
    x.place(c,9,0);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_wall(0,9,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_wall, test_4) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_WALL, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, SOUTH);
    x.place(c,1,1);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_wall(1,1,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

TEST(Darwin_if_wall, test_5) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_WALL, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, WEST);
    x.place(c,0,0);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_wall(0,0,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_wall, test_6) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_WALL, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, WEST);
    x.place(c,1,1);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_wall(1,1,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

TEST(Darwin_if_wall, test_7) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_WALL, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, EAST);
    x.place(c,0,9);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_wall(9,0,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_wall, test_8) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_WALL, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, EAST);
    x.place(c,1,1);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_wall(1,1,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

/**
* if_enemy
*/

TEST(Darwin_if_enemy, test_1) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Species t = Species('t');
    t.add_instruction(LEFT);
    s.add_instruction(IF_ENEMY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, NORTH);
    Creature d = Creature(t, NORTH);
    x.place(c,4,4);
    x.place(d,3,4);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_enemy(4,4,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_enemy, test_2) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_ENEMY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, NORTH);
    x.place(c,1,1);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_enemy(1,1,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

TEST(Darwin_if_enemy, test_3) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Species t = Species('t');
    t.add_instruction(LEFT);
    s.add_instruction(IF_ENEMY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, SOUTH);
    Creature d = Creature(t, NORTH);
    x.place(c,4,4);
    x.place(d,5,4);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_enemy(4,4,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_enemy, test_4) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_ENEMY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, SOUTH);
    x.place(c,1,1);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_enemy(1,1,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

TEST(Darwin_if_enemy, test_5) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Species t = Species('t');
    t.add_instruction(LEFT);
    s.add_instruction(IF_ENEMY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, WEST);
    Creature d = Creature(t, NORTH);
    x.place(c,4,4);
    x.place(d,4,3);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_enemy(4,4,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_enemy, test_6) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_ENEMY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, WEST);
    x.place(c,1,1);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_enemy(1,1,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

TEST(Darwin_if_enemy, test_7) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Species t = Species('t');
    t.add_instruction(LEFT);
    s.add_instruction(IF_ENEMY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, EAST);
    Creature d = Creature(t, NORTH);
    x.place(c,4,4);
    x.place(d,4,5);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_enemy(4,4,index,move);
    ASSERT_TRUE(move.number == RIGHT && index == 2);}

TEST(Darwin_if_enemy, test_8) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(IF_ENEMY, 2);
    s.add_instruction(LEFT);
    s.add_instruction(RIGHT);
    Creature c = Creature(s, EAST);
    x.place(c,1,1);
    int index = 0;
    Instruction move = s.get_instruction(index);
    move = x.if_enemy(1,1,index,move);
    ASSERT_TRUE(move.number == LEFT && index == 1);}

/**
* turn
*/

// No instructions
TEST(Darwin_turn, test_1) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    try {
        x.turn(4,4);
        ASSERT_EQ(false,true);}
    catch (std::invalid_argument &e){
        ASSERT_EQ(true,true);}}

// One instruction
TEST(Darwin_turn, test_2) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(HOP);
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    try {
        x.turn(4,4);
        ASSERT_EQ(true,true);}
    catch (std::invalid_argument &e){
        ASSERT_EQ(false,true);}}

// Multiple instructions
TEST(Darwin_turn, test_3) {
    Darwin x = Darwin(10,10);
    Species s = Species('s');
    s.add_instruction(GO,2);
    s.add_instruction(LEFT);
    s.add_instruction(IF_RANDOM, 0);
    s.add_instruction(IF_RANDOM, 1);
    s.add_instruction(IF_RANDOM, 1);
    s.add_instruction(GO, 1);
    Creature c = Creature(s, SOUTH);
    x.place(c, 4, 4);
    try {
        x.turn(4,4);
        ASSERT_EQ(true,true);}
    catch (std::invalid_argument &e){
        ASSERT_EQ(false,true);}}


