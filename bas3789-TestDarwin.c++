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

#include <sstream> //ostringstream
#include <string>  //string

using namespace std;

// ------------------
// Darwin Constructor
// ------------------

TEST(DarwinConstructor, 2x2) {
  ostringstream w;
  Darwin board(2, 2);
  string expected = "Turn = 0.\n  01\n0 ..\n1 ..\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(DarwinConstructor, 2x8) {
  ostringstream w;
  Darwin board(2, 8);
  string expected = "Turn = 0.\n  01234567\n0 ........\n1 ........\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(DarwinConstructor, 12x12) {
  ostringstream w;
  Darwin board(12, 12);
  string expected = "Turn = 0.\n  012345678901\n0 ............\n1 "
                    "............\n2 ............\n3 ............\n4 "
                    "............\n5 ............\n6 ............\n7 "
                    "............\n8 ............\n9 ............\n0 "
                    "............\n1 ............\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

// ---------------------
// Add Creature, Species
// ---------------------

TEST(AddCreature, SpeciesKitten) {
  ostringstream w;
  Darwin board(2, 2);
  Species kitten('k');
  board.add_creature(kitten, WEST, 0, 0);
  string expected = "Turn = 0.\n  01\n0 k.\n1 ..\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(AddCreature, SpeciesTiger) {
  ostringstream w;
  Darwin board(2, 8);
  Species tiger('t');
  board.add_creature(tiger, NORTH, 1, 7);
  board.add_creature(tiger, SOUTH, 0, 6);
  string expected = "Turn = 0.\n  01234567\n0 ......t.\n1 .......t\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(AddCreature, SpeciesDog) {
  ostringstream w;
  Darwin board(12, 12);
  Species dog('d');
  board.add_creature(dog, EAST, 3, 7);
  board.add_creature(dog, WEST, 8, 9);
  string expected = "Turn = 0.\n  012345678901\n0 ............\n1 "
                    "............\n2 ............\n3 .......d....\n4 "
                    "............\n5 ............\n6 ............\n7 "
                    "............\n8 .........d..\n9 ............\n0 "
                    "............\n1 ............\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

// ----------------------
// Add Creature, Creature
// ----------------------

TEST(AddCreature, CreatureKitten) {
  ostringstream w;
  Darwin board(2, 2);
  Species kitten('k');
  Creature one(kitten, WEST, 0, 0);
  board.add_creature(one, 0, 0);
  string expected = "Turn = 0.\n  01\n0 k.\n1 ..\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(AddCreature, CreatureTiger) {
  ostringstream w;
  Darwin board(2, 8);
  Species tiger('t');
  Creature one(tiger, NORTH, 1, 7);
  Creature two(tiger, SOUTH, 0, 6);
  board.add_creature(one, 1, 7);
  board.add_creature(two, 0, 6);
  string expected = "Turn = 0.\n  01234567\n0 ......t.\n1 .......t\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(AddCreature, CreatureDog) {
  ostringstream w;
  Darwin board(12, 12);
  Species dog('d');
  Creature one(dog, EAST, 3, 7);
  Creature two(dog, WEST, 8, 9);
  board.add_creature(one, 3, 7);
  board.add_creature(two, 8, 9);
  string expected = "Turn = 0.\n  012345678901\n0 ............\n1 "
                    "............\n2 ............\n3 .......d....\n4 "
                    "............\n5 ............\n6 ............\n7 "
                    "............\n8 .........d..\n9 ............\n0 "
                    "............\n1 ............\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

// -----------
// Print Board
// -----------

TEST(PrintBoard, 3x3) {
  ostringstream w;
  Darwin board(3, 3);
  string expected = "Turn = 0.\n  012\n0 ...\n1 ...\n2 ...\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(PrintBoard, 3x3wCreature) {
  ostringstream w;
  Darwin board(3, 3);
  Species kitten('k');
  board.add_creature(kitten, SOUTH, 2, 1);
  string expected = "Turn = 0.\n  012\n0 ...\n1 ...\n2 .k.\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(PrintBoard, 24x30wCreature) {
  ostringstream w;
  Darwin board(24, 30);
  Species kitten('k');
  board.add_creature(kitten, SOUTH, 2, 1);
  board.add_creature(kitten, WEST, 6, 12);
  board.add_creature(kitten, EAST, 23, 4);
  string expected = "Turn = 0.\n  012345678901234567890123456789\n"
                    "0 ..............................\n"
                    "1 ..............................\n"
                    "2 .k............................\n"
                    "3 ..............................\n"
                    "4 ..............................\n"
                    "5 ..............................\n"
                    "6 ............k.................\n"
                    "7 ..............................\n"
                    "8 ..............................\n"
                    "9 ..............................\n"
                    "0 ..............................\n"
                    "1 ..............................\n"
                    "2 ..............................\n"
                    "3 ..............................\n"
                    "4 ..............................\n"
                    "5 ..............................\n"
                    "6 ..............................\n"
                    "7 ..............................\n"
                    "8 ..............................\n"
                    "9 ..............................\n"
                    "0 ..............................\n"
                    "1 ..............................\n"
                    "2 ..............................\n"
                    "3 ....k.........................\n";
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

// --------------
// Run Simulation
// --------------

TEST(RunSimulation, 2x2) {
  Darwin board(2, 2);
  Species hopper('h');
  hopper.add_instruction(HOP);
  hopper.add_instruction(GO, 0);
  board.add_creature(hopper, EAST, 0, 0);
  string expected = "Turn = 0.\n  01\n0 h.\n1 ..\n\n"
                    "Turn = 1.\n  01\n0 .h\n1 ..\n\n";
  ostringstream w;
  board.run_simulation(1, w);
  ASSERT_EQ(expected, w.str());
}

TEST(RunSimulation, 3x3) {
  Darwin board(3, 3);
  Species hopper('h');
  hopper.add_instruction(HOP);
  hopper.add_instruction(GO, 0);
  board.add_creature(hopper, EAST, 0, 0);
  board.add_creature(hopper, NORTH, 2, 1);
  string expected = "Turn = 0.\n  012\n0 h..\n1 ...\n2 .h.\n\n"
                    "Turn = 1.\n  012\n0 .h.\n1 .h.\n2 ...\n\n"
                    "Turn = 2.\n  012\n0 .hh\n1 ...\n2 ...\n\n";
  ostringstream w;
  board.run_simulation(2, w);
  ASSERT_EQ(expected, w.str());
}

TEST(RunSimulation, 3x3wTrap) {
  Darwin board(3, 3);
  Species hopper('h');
  hopper.add_instruction(HOP);
  hopper.add_instruction(GO, 0);
  Species trap('t');
  trap.add_instruction(IF_ENEMY, 3);
  trap.add_instruction(LEFT);
  trap.add_instruction(GO, 0);
  trap.add_instruction(INFECT);
  trap.add_instruction(GO, 0);
  board.add_creature(hopper, EAST, 0, 0);
  board.add_creature(trap, WEST, 0, 2);
  string expected = "Turn = 0.\n  012\n0 h.t\n1 ...\n2 ...\n\n"
                    "Turn = 1.\n  012\n0 .tt\n1 ...\n2 ...\n\n"
                    "Turn = 2.\n  012\n0 .tt\n1 ...\n2 ...\n\n";
  ostringstream w;
  board.run_simulation(2, w);
  ASSERT_EQ(expected, w.str());
}

// --------
// In Front
// --------

TEST(InFront, 2x2) {
  Darwin board(2, 2);
  Species kitten('k');
  Creature one(kitten, EAST, 0, 0);
  Creature two(kitten, WEST, 0, 1);
  board.add_creature(one, 0, 0);
  board.add_creature(two, 0, 1);
  Creature *actual = board.in_front(0, 0, EAST);
  ASSERT_EQ(two, *actual);
}

TEST(InFront, 2x2Wall) {
  Darwin board(2, 2);
  Species kitten('k');
  Creature one(kitten, NORTH, 0, 0);
  Creature two(kitten, WEST, 0, 1);
  board.add_creature(one, 0, 0);
  board.add_creature(two, 0, 1);
  Creature *actual = board.in_front(0, 0, NORTH);
  ASSERT_EQ(nullptr, actual);
}

TEST(InFront, 2x2Other) {
  Darwin board(2, 2);
  Species kitten('k');
  Creature one(kitten, EAST, 0, 0);
  Creature two(kitten, WEST, 0, 1);
  board.add_creature(one, 0, 0);
  board.add_creature(two, 0, 1);
  Creature *actual = board.in_front(0, 1, WEST);
  ASSERT_EQ(one, *actual);
}

// ------------
// Run One Turn
// ------------

TEST(RunTurn, 2x2) {
  Darwin board(2, 2);
  Species hopper('h');
  hopper.add_instruction(HOP);
  hopper.add_instruction(GO, 0);
  board.add_creature(hopper, EAST, 0, 0);
  string expected = "Turn = 0.\n  01\n0 .h\n1 ..\n";
  ostringstream w;
  board.run_turn(1);
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(RunTurn, 3x3) {
  Darwin board(3, 3);
  Species hopper('h');
  hopper.add_instruction(HOP);
  hopper.add_instruction(GO, 0);
  board.add_creature(hopper, EAST, 0, 0);
  board.add_creature(hopper, NORTH, 2, 1);
  string expected = "Turn = 0.\n  012\n0 .h.\n1 .h.\n2 ...\n";
  ostringstream w;
  board.run_turn(1);
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(RunTurn, 3x3wTrap) {
  Darwin board(3, 3);
  Species hopper('h');
  hopper.add_instruction(HOP);
  hopper.add_instruction(GO, 0);
  Species trap('t');
  trap.add_instruction(IF_ENEMY, 3);
  trap.add_instruction(LEFT);
  trap.add_instruction(GO, 0);
  trap.add_instruction(INFECT);
  trap.add_instruction(GO, 0);
  board.add_creature(hopper, EAST, 0, 0);
  board.add_creature(trap, WEST, 0, 2);
  string expected = "Turn = 0.\n  012\n0 .tt\n1 ...\n2 ...\n";
  ostringstream w;
  board.run_turn(1);
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

// --------------
// Creature Class
// --------------

// --------------
// Valid Creature
// --------------

TEST(Valid, test1) {
  Species dot('.');
  Creature expected(dot, WEST, 0, 0);
  ASSERT_TRUE(expected.valid(1));
}

TEST(Valid, test2) {
  Species dot('.');
  Creature expected(dot, WEST, 0, 0);
  ASSERT_FALSE(expected.valid(2));
}

TEST(Valid, test3) {
  Species dot('.');
  Creature expected(dot, WEST, 0, 0);
  ASSERT_FALSE(expected.valid(3));
}

TEST(Valid, test4) {
  Species dot('.');
  Creature expected(dot, WEST, 0, 0);
  ASSERT_FALSE(expected.valid(0));
}

TEST(Valid, test5) {
  Species dot('.');
  Creature expected(dot, WEST, 0, 0);
  ASSERT_FALSE(expected.valid(-4));
}

TEST(Valid, test6) {
  Species dot('.');
  Creature expected(dot, WEST, 0, 0);
  ASSERT_FALSE(expected.valid(-31545));
}

// --------------
// Print Creature
// --------------

TEST(PrintCreature, test1) {
  Species dot('.');
  Creature test(dot, NORTH, 0, 4);
  ostringstream w;
  test.print_creature(w);
  ASSERT_EQ(".", w.str());
}

TEST(PrintCreature, test2) {
  Species kitten('k');
  Creature test(kitten, WEST, 56, 3);
  ostringstream w;
  test.print_creature(w);
  ASSERT_EQ("k", w.str());
}

TEST(PrintCreature, test3) {
  Species tiger('t');
  Creature test(tiger, SOUTH, 5, 413);
  ostringstream w;
  test.print_creature(w);
  ASSERT_EQ("t", w.str());
}

TEST(PrintCreature, test4) {
  Species dog('d');
  Creature test(dog, EAST, 0, 4);
  ostringstream w;
  test.print_creature(w);
  ASSERT_EQ("d", w.str());
}

TEST(PrintCreature, test5) {
  Species food('f');
  Creature test(food, NORTH, 13, 4341);
  ostringstream w;
  test.print_creature(w);
  ASSERT_EQ("f", w.str());
}

TEST(PrintCreature, test6) {
  Species trap('t');
  Creature test(trap, EAST, 0, 4);
  ostringstream w;
  test.print_creature(w);
  ASSERT_EQ("t", w.str());
}

// ---------------
// Infect Creature
// ---------------

TEST(Infect, test1) {
  Species one('o');
  Species two('t');
  Creature c1(one, WEST, 1, 1);
  Creature c2(two, EAST, 2, 3);
  c1.infect(c2);
  ASSERT_EQ(c1.specie.symbol, c2.specie.symbol);
}

TEST(Infect, test2) {
  Species one('o');
  Species two('t');
  Creature c1(one, WEST, 1, 1);
  Creature c2(two, EAST, 2, 3);
  c2.infect(c1);
  ASSERT_EQ(c1.specie.symbol, c2.specie.symbol);
}

TEST(Infect, test3) {
  Species one('k');
  Species two('t');
  Creature c1(one, WEST, 1, 1);
  Creature c2(two, EAST, 2, 3);
  c2.infect(c1);
  ASSERT_EQ(c1.specie.symbol, c2.specie.symbol);
}

//
// Execute Instruction
//

TEST(ExecuteIns, test1) {
  Species hopper('h');
  hopper.add_instruction(HOP);
  hopper.add_instruction(GO, 0);
  Darwin board(2, 2);
  Creature test(hopper, EAST, 0, 0);
  board.add_creature(test, 0, 0);
  test.execute_instruction(board);
  string expected = "Turn = 0.\n  01\n0 .h\n1 ..\n";
  ostringstream w;
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(ExpectedIns, test2) {
  Darwin board(3, 3);
  Species hopper('h');
  hopper.add_instruction(HOP);
  hopper.add_instruction(GO, 0);
  Species rover('r');
  rover.add_instruction(IF_ENEMY, 9);
  rover.add_instruction(IF_EMPTY, 7);
  rover.add_instruction(IF_RANDOM, 5);
  rover.add_instruction(LEFT);
  rover.add_instruction(GO, 0);
  rover.add_instruction(RIGHT);
  rover.add_instruction(GO, 0);
  rover.add_instruction(HOP);
  rover.add_instruction(GO, 0);
  rover.add_instruction(INFECT);
  rover.add_instruction(GO, 0);
  Creature one(hopper, EAST, 0, 0);
  Creature two(rover, WEST, 0, 1);
  board.add_creature(one, 0, 0);
  board.add_creature(two, 0, 1);
  string expected = "Turn = 0.\n  012\n0 hr.\n1 ...\n2 ...\n";
  ostringstream w;
  two.execute_instruction(board);
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

TEST(ExpectedIns, test3) {
  Darwin board(3, 3);
  Species hopper('h');
  hopper.add_instruction(HOP);
  hopper.add_instruction(GO, 0);
  Species rover('r');
  rover.add_instruction(IF_ENEMY, 9);
  rover.add_instruction(IF_EMPTY, 7);
  rover.add_instruction(IF_RANDOM, 5);
  rover.add_instruction(LEFT);
  rover.add_instruction(GO, 0);
  rover.add_instruction(RIGHT);
  rover.add_instruction(GO, 0);
  rover.add_instruction(HOP);
  rover.add_instruction(GO, 0);
  rover.add_instruction(INFECT);
  rover.add_instruction(GO, 0);
  Creature one(hopper, EAST, 0, 0);
  Creature two(rover, WEST, 0, 1);
  board.add_creature(one, 0, 0);
  board.add_creature(two, 0, 1);
  string expected = "Turn = 0.\n  012\n0 hr.\n1 ...\n2 ...\n";
  ostringstream w;
  one.execute_instruction(board);
  board.print_board(w);
  ASSERT_EQ(expected, w.str());
}

// ----------
// Turn Right
// ----------

TEST(TurnRight, test1) {
  Species h('h');
  Creature test(h, WEST, 0, 1);
  Creature expected(h, NORTH, 0, 1);
  test.turn_right();
  ASSERT_EQ(test, expected);
}

TEST(TurnRight, test2) {
  Species h('h');
  Creature test(h, NORTH, 0, 1);
  Creature expected(h, EAST, 0, 1);
  test.turn_right();
  ASSERT_EQ(test, expected);
}

TEST(TurnRight, test3) {
  Species h('h');
  Creature test(h, EAST, 0, 1);
  Creature expected(h, SOUTH, 0, 1);
  test.turn_right();
  ASSERT_EQ(test, expected);
}

TEST(TurnRight, test4) {
  Species h('h');
  Creature test(h, SOUTH, 0, 1);
  Creature expected(h, WEST, 0, 1);
  test.turn_right();
  ASSERT_EQ(test, expected);
}

// ---------
// Turn Left
// ---------

TEST(TurnLeft, test1) {
  Species h('h');
  Creature test(h, WEST, 0, 1);
  Creature expected(h, SOUTH, 0, 1);
  test.turn_left();
  ASSERT_EQ(test, expected);
}

TEST(TurnLeft, test2) {
  Species h('h');
  Creature test(h, NORTH, 0, 1);
  Creature expected(h, WEST, 0, 1);
  test.turn_left();
  ASSERT_EQ(test, expected);
}

TEST(TurnLeft, test3) {
  Species h('h');
  Creature test(h, EAST, 0, 1);
  Creature expected(h, NORTH, 0, 1);
  test.turn_left();
  ASSERT_EQ(test, expected);
}

TEST(TurnLeft, test4) {
  Species h('h');
  Creature test(h, SOUTH, 0, 1);
  Creature expected(h, EAST, 0, 1);
  test.turn_left();
  ASSERT_EQ(test, expected);
}

// --------------
// Creature Equal
// --------------

TEST(Equal, test1) {
  Species test('t');
  Creature one(test, WEST, 1, 1);
  Creature two(test, WEST, 1, 1);
  ASSERT_TRUE(one == two);
}

TEST(Equal, test2) {
  Species test('t');
  Creature one(test, EAST, 1, 1);
  Creature two(test, WEST, 1, 1);
  ASSERT_FALSE(one == two);
}

TEST(Equal, test3) {
  Species test('t');
  Creature one(test, WEST, 2, 1);
  Creature two(test, WEST, 1, 1);
  ASSERT_FALSE(one == two);
}

TEST(Equal, test4) {
  Species test('t');
  Creature one(test, WEST, 1, 3);
  Creature two(test, WEST, 1, 1);
  ASSERT_FALSE(one == two);
}

// -------------
// Species Class
// -------------

// ------------
// Constructor
// ------------

TEST(SpeciesConstructor, test1) {
  Species test('t');
  ASSERT_EQ(test.symbol, 't');
}

TEST(SpeciesConstructor, test2) {
  Species test('s');
  ASSERT_EQ(test.symbol, 's');
}

TEST(SpeciesConstructor, test3) {
  Species test('d');
  ASSERT_EQ(test.symbol, 'd');
}

TEST(SpeciesConstructor, test4) {
  Species test('e');
  ASSERT_EQ(test.symbol, 'e');
}

TEST(SpeciesConstructor, test5) {
  Species test('*');
  ASSERT_EQ(test.symbol, '*');
}
// -------------
// Print Symbol
// -------------

TEST(PrintSymbol, test1) {
  Species test('h');
  ostringstream w;
  test.print_symbol(w);
  ASSERT_EQ("h", w.str());
}

TEST(PrintSymbol, test2) {
  Species test('t');
  ostringstream w;
  test.print_symbol(w);
  ASSERT_EQ("t", w.str());
}

TEST(PrintSymbol, test3) {
  Species test('8');
  ostringstream w;
  test.print_symbol(w);
  ASSERT_EQ("8", w.str());
}

TEST(PrintSymbol, test4) {
  Species test('(');
  ostringstream w;
  test.print_symbol(w);
  ASSERT_EQ("(", w.str());
}

TEST(PrintSymbol, test5) {
  Species test('%');
  ostringstream w;
  test.print_symbol(w);
  ASSERT_EQ("%", w.str());
}

// ------
// Valid
// ------

TEST(ValidSpecie, test1) {
  Species test('.');
  ASSERT_FALSE(test.valid());
}

TEST(ValidSpecie, test2) {
  Species test('6');
  ASSERT_TRUE(test.valid());
}

TEST(ValidSpecie, test3) {
  Species test('4');
  ASSERT_TRUE(test.valid());
}

TEST(ValidSpecie, test4) {
  Species test('d');
  ASSERT_TRUE(test.valid());
}

TEST(ValidSpecie, test5) {
  Species test('f');
  ASSERT_TRUE(test.valid());
}

// ------------
// Instructions
// ------------

TEST(Instructions, test1) {
  Instruction i(HOP, 8);
  ASSERT_EQ(i.i, HOP);
  ASSERT_EQ(i.target, 8);
}

TEST(Instructions, test2) {
  Instruction i(HOP);
  ASSERT_EQ(i.i, HOP);
  ASSERT_EQ(i.target, -1);
}

TEST(Instructions, test3) {
  Instruction i(IF_EMPTY, -4);
  ASSERT_EQ(i.i, IF_EMPTY);
  ASSERT_EQ(i.target, -4);
}
