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

#include <sstream>
#include <string>

using namespace std;

// ----
// test
// ----

// Critter should be able to hop.
TEST(CritterFixture, test_action_hop) {
  vector<Instruction> inst({{Opcode::hop, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::hop, action.op);
}

// Critter should be able to turn left.
TEST(CritterFixture, test_action_left) {
  vector<Instruction> inst({{Opcode::left, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::left, action.op);
}

// Critter should be able to turn right.
TEST(CritterFixture, test_action_right) {
  vector<Instruction> inst({{Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::right, action.op);
}

// Critter should be able to infect.
TEST(CritterFixture, test_action_infect) {
  vector<Instruction> inst({{Opcode::infect, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::infect, action.op);
}

// Critter should take the branch on if_empty if the space in front of it is
// empty.
TEST(CritterFixture, test_if_empty_y) {
  vector<Instruction> inst(
      {{Opcode::if_empty, 2}, {Opcode::left, 0}, {Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::right, action.op);
}

// Critter should not take the branch on if_empty if the space in front of it is
// not empty.
TEST(CritterFixture, test_if_empty_n) {
  vector<Instruction> inst(
      {{Opcode::if_empty, 2}, {Opcode::left, 0}, {Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;
  front.type = EntityType::wall;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::left, action.op);
}

// Critter should take the branch on if_wall if the space in front of it is
// a wall.
TEST(CritterFixture, test_if_wall_y) {
  vector<Instruction> inst(
      {{Opcode::if_wall, 2}, {Opcode::left, 0}, {Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;
  front.type = EntityType::wall;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::right, action.op);
}

// Critter should not take the branch on if_wall if the space in front of it is
// not a wall.
TEST(CritterFixture, test_if_wall_n) {
  vector<Instruction> inst(
      {{Opcode::if_wall, 2}, {Opcode::left, 0}, {Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::left, action.op);
}

// Critter should take the branch on if_random if the generated random integer
// is odd.
TEST(CritterFixture, test_rand_y) {
  vector<Instruction> inst(
      {{Opcode::if_random, 2}, {Opcode::left, 0}, {Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  srand(0);

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::right, action.op);
}

// Critter should not take the branch on if_random if the space in front of it
// is even.
TEST(CritterFixture, test_rand_n) {
  vector<Instruction> inst(
      {{Opcode::if_random, 2}, {Opcode::left, 0}, {Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  srand(2);

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::left, action.op);
}

// Critter should take the branch on if_enemy if the space in front of it is
// occupied and the thing that occupies it is a critter.
TEST(CritterFixture, test_if_enemy_y) {
  vector<Instruction> inst(
      {{Opcode::if_enemy, 2}, {Opcode::left, 0}, {Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);

  Species s2({'s', inst});
  Critter c2(&s2);
  Entity front;
  front.type = EntityType::critter;
  front.critter = c2;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::right, action.op);
}

// Critter should not take the branch on if_empty if the space in front of it is
// occupied by a critter of the same species.
TEST(CritterFixture, test_if_enemy_n_same_species) {
  vector<Instruction> inst(
      {{Opcode::if_enemy, 2}, {Opcode::left, 0}, {Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);

  Critter c2(&s);
  Entity front;
  front.type = EntityType::critter;
  front.critter = c2;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::left, action.op);
}

// Critter should not take the branch on if_empty if the space in front of it is
// empty.
TEST(CritterFixture, test_if_enemy_n_empty) {
  vector<Instruction> inst(
      {{Opcode::if_enemy, 2}, {Opcode::left, 0}, {Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::left, action.op);
}

// Critter should be able to go.
TEST(CritterFixture, test_go) {
  vector<Instruction> inst(
      {{Opcode::go, 2}, {Opcode::left, 0}, {Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::right, action.op);
}

// Critter should execute an arbitrary number of control flow instructions
// (correctly) before returning an instruction.
TEST(CritterFixture, test_combo) {
  vector<Instruction> inst({{Opcode::go, 2},
                            {Opcode::left, 0},
                            {Opcode::if_random, 4},
                            {Opcode::left, 0},
                            {Opcode::if_enemy, 7},
                            {Opcode::if_wall, 7},
                            {Opcode::if_empty, 8},
                            {Opcode::left, 0},
                            {Opcode::right, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  srand(0);

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::right, action.op);
}

// Critter should be able to execute instructions in a loop.
TEST(CritterFixture, test_loop) {
  vector<Instruction> inst(
      {{Opcode::left, 0}, {Opcode::right, 0}, {Opcode::go, 0}});
  Species s({'s', inst});
  Critter c(&s);
  Entity front;

  srand(0);

  const auto &action = c.next_action(front);
  ASSERT_EQ(Opcode::left, action.op);
  ASSERT_EQ(Opcode::right, c.next_action(front).op);
  ASSERT_EQ(Opcode::left, c.next_action(front).op);
  ASSERT_EQ(Opcode::right, c.next_action(front).op);
}

// When a critter infects an enemy critter, changing its species and resetting
// its program counter.
TEST(CritterFixture, test_infect_enemy) {
  vector<Instruction> inst1({{Opcode::infect, 0}});
  vector<Instruction> inst2({{Opcode::left, 0}, {Opcode::right, 0}});
  Species s1({'s', inst1});
  Critter c1(&s1);
  Species s2({'2', inst2});
  Critter c2(&s2);
  Entity front;

  c2.next_action(front);
  c1.infect(c2);

  // Test species changed.
  ostringstream o2;
  o2 << c2;
  ASSERT_EQ("s", o2.str());

  // Test program counter reset.
  const auto &action = c2.next_action(front);
  ASSERT_EQ(Opcode::infect, action.op);
}

// When a critter infects a critter of its own species, it should not change
// the species or the program counter of the infected critter.
TEST(CritterFixture, test_infect_friend) {
  vector<Instruction> inst({{Opcode::infect, 0}, {Opcode::left, 0}});
  Species s({'s', inst});
  Critter c1(&s);
  Critter c2(&s);
  Entity front;

  c2.next_action(front);
  c1.infect(c2);

  const auto &action = c2.next_action(front);
  ASSERT_EQ(Opcode::left, action.op);
}

// Critter should print its name.
TEST(CritterFixture, test_print) {
  vector<Instruction> inst({{Opcode::left, 0}});
  Species s({'s', inst});
  Critter c(&s);
  ostringstream out;

  out << c;

  ASSERT_EQ("s", out.str());
}

// Board state should reflect adding one critter.
TEST(DarwinFixture, test_add_1) {
  Darwin game(2, 2);
  vector<Instruction> inst({{Opcode::hop, 0}});
  Species s({'s', inst});

  game.add_critter(0, 1, Direction::south, &s);

  ostringstream o;
  o << game;
  ASSERT_EQ("Turn = 0.\n  01\n0 ..\n1 s.\n", o.str());
}

// Board state should reflect a critter hopping forward.
TEST(DarwinFixture, test_hop_turn) {
  Darwin game(2, 2);
  vector<Instruction> inst({{Opcode::hop, 0}});
  Species s({'s', inst});

  game.add_critter(0, 0, Direction::south, &s);
  game.next_turn();

  ostringstream o;
  o << game;
  ASSERT_EQ("Turn = 1.\n  01\n0 ..\n1 s.\n", o.str());
}

// Board state should reflect a critter taking a left turn and then hopping
// forward.
TEST(DarwinFixture, test_left_turn) {
  Darwin game(2, 2);
  vector<Instruction> inst({{Opcode::left, 0}, {Opcode::hop, 0}});
  Species s({'s', inst});

  game.add_critter(0, 0, Direction::south, &s);
  game.next_turn();
  game.next_turn();

  ostringstream o;
  o << game;
  ASSERT_EQ("Turn = 2.\n  01\n0 .s\n1 ..\n", o.str());
}

// Board state should reflect a critter taking a right turn and then hopping
// forward.
TEST(DarwinFixture, test_right_turn) {
  Darwin game(2, 2);
  vector<Instruction> inst({{Opcode::right, 0}, {Opcode::hop, 0}});
  Species s({'s', inst});

  game.add_critter(0, 0, Direction::east, &s);
  game.next_turn();
  game.next_turn();

  ostringstream o;
  o << game;
  ASSERT_EQ("Turn = 2.\n  01\n0 ..\n1 s.\n", o.str());
}

// Board state should reflect a critter infecting the critter in front of it.
TEST(DarwinFixture, test_infect_enemy_turn) {
  Darwin game(2, 2);
  vector<Instruction> inst({{Opcode::infect, 0}});
  Species sa({'a', inst});
  Species sb({'b', inst});

  game.add_critter(0, 0, Direction::east, &sa);
  game.add_critter(1, 0, Direction::west, &sb);
  game.next_turn();

  ostringstream o;
  o << game;
  ASSERT_EQ("Turn = 1.\n  01\n0 aa\n1 ..\n", o.str());
}

// Board state should reflect a critter trying to infect a wall.
TEST(DarwinFixture, test_infect_wall_turn) {
  Darwin game(2, 2);
  vector<Instruction> inst({{Opcode::infect, 0}});
  Species s({'s', inst});

  game.add_critter(0, 0, Direction::west, &s);
  game.next_turn();

  ostringstream o;
  o << game;
  ASSERT_EQ("Turn = 1.\n  01\n0 s.\n1 ..\n", o.str());
}

// Critters should get turns in the right order (row-major, starting at top
// left).
TEST(DarwinFixture, test_turn_order) {
  Darwin game(2, 2);
  vector<Instruction> inst({{Opcode::hop, 0}});
  Species sa({'a', inst});
  Species sb({'b', inst});
  
  game.add_critter(0, 0, Direction::south, &sa);
  game.add_critter(1, 1, Direction::west, &sb);
  game.next_turn();

  ostringstream o;
  o << game;
  ASSERT_EQ("Turn = 1.\n  01\n0 ..\n1 ab\n", o.str());
}

// Darwin should not crash or do anything weird when the board is not square.
TEST(DarwinFixture, test_rectangular_board) {
  Darwin game(3, 2);
  vector<Instruction> inst({{Opcode::hop, 0}, {Opcode::hop, 0}});
  Species s({'s', inst});

  game.add_critter(0, 0, Direction::east, &s);
  game.next_turn();
  game.next_turn();

  ostringstream o;
  o << game;
  ASSERT_EQ("Turn = 2.\n  012\n0 ..s\n1 ...\n", o.str());
}
