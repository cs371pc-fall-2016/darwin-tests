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
#include <iostream>
#include <sstream>

#include "Darwin.h"

using namespace std;

// -------------------------
// Species::copy_constructor
// -------------------------

TEST (SpeciesFixture, copy_constructor_1) {
  Species s;
  ASSERT_EQ(s._species, 'f');
}
TEST (SpeciesFixture, copy_constructor_2) {
  Species s('t');
  ASSERT_EQ(s._species, 't');
}
TEST (SpeciesFixture, copy_constructor_3) {
  Species s('r');
  ASSERT_EQ(s._species, 'r');
}

// ---------------------------------
// Species::copy_assignment_operator
// ---------------------------------

TEST (SpeciesFixture, copy_assignment_operator_1) {
  Species s;
  Species t('t');
  s = t;
  ASSERT_EQ(s._species, 't');
}
TEST (SpeciesFixture, copy_assignment_operator_2) {
  Species s;
  Species r('r');
  s = r;
  ASSERT_EQ(s._species, 'r');
}
TEST (SpeciesFixture, copy_assignment_operator_3) {
  Species s;
  Species h('h');
  s = h;
  ASSERT_EQ(s._species, 'h');
}

// ---------------
// Species::oper==
// ---------------

TEST (SpeciesFixture, oper_equal_1) {
  Species s;
  Species r;
  ASSERT_TRUE(s == r);
}
TEST (SpeciesFixture, oper_equal_2) {
  Species s;
  Species r('f');
  ASSERT_TRUE(s == r);
}
TEST (SpeciesFixture, oper_equal_3) {
  Species s('s');
  Species r('r');
  ASSERT_FALSE(s == r);
}

// ---------------
// Species::oper!=
// ---------------

TEST (SpeciesFixture, oper_not_equal_1) {
  Species s;
  Species r;
  ASSERT_FALSE(s != r);
}
TEST (SpeciesFixture, oper_not_equal_2) {
  Species s;
  Species r('r');
  ASSERT_TRUE(s != r);
}
TEST (SpeciesFixture, oper_not_equal_3) {
  Species s('s');
  Species r('r');
  ASSERT_TRUE(s != r);
}

// ------------------------
// Species::add_instruction
// ------------------------

TEST (SpeciesFixture, add_instruction_1) {
  Species s;
  s.add_instruction(Instructions::GO, 0);
  ASSERT_EQ(s._inst.at(0), Instructions::GO);
  ASSERT_EQ(s._n.at(0), 0);
}
TEST (SpeciesFixture, add_instruction_2) {
  Species s;
  s.add_instruction(Instructions::HOP, 0);
  s.add_instruction(Instructions::GO, 0);
  s.add_instruction(Instructions::IF_ENEMY, 2);
  ASSERT_EQ(s._inst.at(0), Instructions::HOP);
  ASSERT_EQ(s._inst.at(1), Instructions::GO);
  ASSERT_EQ(s._inst.at(2), Instructions::IF_ENEMY);
  ASSERT_EQ(s._n.at(0), 0);
  ASSERT_EQ(s._n.at(1), 0);
  ASSERT_EQ(s._n.at(2), 2);
}
TEST (SpeciesFixture, add_instruction_3) {
  Species s;
  vector<Instructions> insts;
  insts.push_back(Instructions::GO);
  insts.push_back(Instructions::HOP);
  insts.push_back(Instructions::IF_ENEMY);
  insts.push_back(Instructions::IF_EMPTY);
  insts.push_back(Instructions::IF_WALL);
  insts.push_back(Instructions::GO);
  insts.push_back(Instructions::INFECT);
  insts.push_back(Instructions::LEFT);
  insts.push_back(Instructions::RIGHT);
  insts.push_back(Instructions::IF_RANDOM);

  vector<int> ns;
  ns.push_back(0);
  ns.push_back(1);
  ns.push_back(2);
  ns.push_back(3);
  ns.push_back(4);
  ns.push_back(5);
  ns.push_back(6);
  ns.push_back(7);
  ns.push_back(8);
  ns.push_back(9);

  for (int i = 0; i < 10; ++i) {
    s.add_instruction(insts.at(i), ns.at(i));
    ASSERT_EQ(s._inst.at(i), insts.at(i));
    ASSERT_EQ(s._n.at(i), ns.at(i));
  }
}

// ---------------------
// Species::which_action
// ---------------------

TEST (SpeciesFixture, which_action_1) {
  Species s;
  s.add_instruction(Instructions::GO, 0);
  ASSERT_EQ(s.which_action(0), Instructions::GO);
}
TEST (SpeciesFixture, which_action_2) {
  Species s;
  s.add_instruction(Instructions::HOP, 0);
  s.add_instruction(Instructions::GO, 0);
  ASSERT_EQ(s.which_action(0), Instructions::HOP);
  ASSERT_EQ(s.which_action(1), Instructions::GO);
}
TEST (SpeciesFixture, which_action_3) {
  Species s;
  vector<Instructions> insts;
  insts.push_back(Instructions::GO);
  insts.push_back(Instructions::HOP);
  insts.push_back(Instructions::IF_ENEMY);
  insts.push_back(Instructions::IF_EMPTY);
  insts.push_back(Instructions::IF_WALL);
  insts.push_back(Instructions::GO);
  insts.push_back(Instructions::INFECT);
  insts.push_back(Instructions::LEFT);
  insts.push_back(Instructions::RIGHT);
  insts.push_back(Instructions::IF_RANDOM);

  for (int i = 0; i < 10; ++i) {
    s.add_instruction(insts.at(i), 0);
    ASSERT_EQ(s.which_action(i), insts.at(i));
  }
}

// ----------------
// Species::which_n
// ----------------

TEST (SpeciesFixture, which_n_1) {
  Species s;
  s.add_instruction(Instructions::HOP, 0);
  ASSERT_EQ(s.which_n(0), 0);
}
TEST (SpeciesFixture, which_n_2) {
  Species s;
  s.add_instruction(Instructions::GO, 500);
  s.add_instruction(Instructions::HOP, 2);
  ASSERT_EQ(s.which_n(0), 500);
  ASSERT_EQ(s.which_n(1), 2);
}
TEST (SpeciesFixture, which_n_3) {
  Species s;
  vector<int> ns;
  ns.push_back(0);
  ns.push_back(1);
  ns.push_back(2);
  ns.push_back(3);
  ns.push_back(4);
  ns.push_back(5);
  ns.push_back(6);
  ns.push_back(7);
  ns.push_back(8);
  ns.push_back(9);

  for (int i = 0; i < 10; ++i) {
    s.add_instruction(Instructions::GO, ns.at(i));
    ASSERT_EQ(s._n.at(i), ns.at(i));
  }
}

// --------------
// Species::print
// --------------

TEST (SpeciesFixture, print_1) {
  Species s;
  ostringstream os;
  s.print(os);
  ASSERT_EQ(os.str(), "f");
}
TEST (SpeciesFixture, print_2) {
  Species s('r');
  ostringstream os;
  s.print(os);
  ASSERT_EQ(os.str(), "r");
}
TEST (SpeciesFixture, print_3) {
  Species s('h');
  ostringstream os;
  s.print(os);
  ASSERT_EQ(os.str(), "h");
}

// --------------------------
// Creature::copy_constructor
// --------------------------

TEST (CreatureFixture, copy_constructor_1) {
  Species s;
  Creature food(s, NORTH);
  ASSERT_TRUE(food._species == s);
  ASSERT_TRUE(food._direction == NORTH);
  ASSERT_TRUE(food._pc == 0);
}
TEST (CreatureFixture, copy_constructor_2) {
  Species s('r');
  Creature rover(s, SOUTH);
  ASSERT_TRUE(rover._species == s);
  ASSERT_TRUE(rover._direction == SOUTH);
  ASSERT_TRUE(rover._pc == 0);
}
TEST (CreatureFixture, copy_constructor_3) {
  Species s('h');
  Creature hopper(s, EAST);
  ASSERT_TRUE(hopper._species == s);
  ASSERT_TRUE(hopper._direction == EAST);
  ASSERT_TRUE(hopper._pc == 0);
}

// ----------------
// Creature::action
// ----------------

TEST (CreatureFixture, action_1) {
  Species s;
  s.add_instruction(Instructions::LEFT, 0);
  s.add_instruction(Instructions::RIGHT, 0);

  Creature food(s, NORTH);
  Action action = food.action(false, nullptr);
  Action action2 = food.action(false, nullptr);

  ASSERT_TRUE(action == Action::CHANGE_LEFT);
  ASSERT_TRUE(action2 == Action::CHANGE_RIGHT);
}
TEST (CreatureFixture, action_2) {
  Species s;
  s.add_instruction(Instructions::INFECT, 0);
  s.add_instruction(Instructions::HOP, 0);

  Creature food(s, NORTH);
  Action action = food.action(false, nullptr);
  Action action2 = food.action(false, nullptr);

  ASSERT_TRUE(action == Action::INFECT);
  ASSERT_TRUE(action2 == Action::HOP);
}
TEST (CreatureFixture, action_3) {
  Species s;
  s.add_instruction(Instructions::INFECT, 0);
  s.add_instruction(Instructions::HOP, 0);
  Species r('r');
  r.add_instruction(Instructions::RIGHT, 0);

  Creature food(s, NORTH);
  Creature rover(r, SOUTH);
  Action action = food.action(false, &rover);
  Action action2 = food.action(true, nullptr);

  ASSERT_TRUE(action == Action::INFECT);
  ASSERT_TRUE(action2 == Action::NO_ACTION);
}

// -----------------
// Creature::control
// -----------------

TEST (CreatureFixture, control_1) {
  Species s;
  s.add_instruction(Instructions::GO, 1);
  s.add_instruction(Instructions::LEFT, 0);

  Creature food(s, NORTH);
  ASSERT_TRUE(food.action(false, nullptr) == Action::DO_CONTROL);
  food.control(false, nullptr);
  ASSERT_TRUE(food.action(false, nullptr) == Action::CHANGE_LEFT);
}
TEST (CreatureFixture, control_2) {
  Species s;
  s.add_instruction(Instructions::GO, 1);
  s.add_instruction(Instructions::IF_WALL, 3);
  s.add_instruction(Instructions::LEFT, 0);
  s.add_instruction(Instructions::RIGHT, 0);

  Creature food(s, NORTH);
  ASSERT_TRUE(food.action(false, nullptr) == Action::DO_CONTROL);
  food.control(false, nullptr);
  ASSERT_TRUE(food.action(false, nullptr) == Action::DO_CONTROL);
  food.control(false, nullptr);
  ASSERT_TRUE(food.action(false, nullptr) == Action::CHANGE_LEFT);
}
TEST (CreatureFixture, control_3) {
  Species s;
  s.add_instruction(Instructions::GO, 1);
  s.add_instruction(Instructions::IF_WALL, 3);
  s.add_instruction(Instructions::LEFT, 0);
  s.add_instruction(Instructions::RIGHT, 0);

  Creature food(s, NORTH);
  ASSERT_TRUE(food.action(true, nullptr) == Action::DO_CONTROL);
  food.control(true, nullptr);
  ASSERT_TRUE(food.action(true, nullptr) == Action::DO_CONTROL);
  food.control(true, nullptr);
  ASSERT_TRUE(food.action(true, nullptr) == Action::CHANGE_RIGHT);
}

// ---------------
// Creature::print
// ---------------

TEST (CreatureFixture, print_1) {
  Species s;
  Creature food(s, NORTH);
  ostringstream os;
  food.print(os);
  ASSERT_EQ(os.str(), "f");
}
TEST (CreatureFixture, print_2) {
  Species s('r');
  Creature rover(s, NORTH);
  ostringstream os;
  rover.print(os);
  ASSERT_EQ(os.str(), "r");
}
TEST (CreatureFixture, print_3) {
  Species s('h');
  Creature hopper(s, NORTH);
  ostringstream os;
  hopper.print(os);
  ASSERT_EQ(os.str(), "h");
}

// -----------------------
// Darwin::copy_consructor
// -----------------------

TEST (DarwinFixture, copy_constructor_1){
  Darwin x(2, 2);
  ASSERT_TRUE(x._row==2);
  ASSERT_TRUE(x._colm==2);
}
TEST (DarwinFixture, copy_constructor_2){
  Darwin x(100, 124);
  ASSERT_TRUE(x._row==100);
  ASSERT_TRUE(x._colm==124);
}
TEST (DarwinFixture, copy_constructor_3){
  Darwin x(92, 10);
  ASSERT_TRUE(x._row==92);
  ASSERT_TRUE(x._colm==10);

}

// --------------------
// Darwin::add_creature
// --------------------

TEST (DarwinFixture, add_creature_1){
  Species s;
  Creature food(s, SOUTH);
  Darwin x(10, 10);
  x.add_creature(food, 12, SOUTH);
  ASSERT_TRUE(x._grid.at(12)==(long)&food);
  ASSERT_TRUE(x._direction[(long)&food]==3);

}
TEST (DarwinFixture, add_creature_2){
  Species s;
  Creature food(s, NORTH);
  Darwin x(100, 100);
  x.add_creature(food, 1200, NORTH);
  ASSERT_TRUE(x._grid.at(1200)==(long)&food);
  ASSERT_TRUE(x._direction[(long)&food]==1);

}
TEST (DarwinFixture, add_creature_3){
  Species s;
  Creature food(s, WEST);
  Darwin x(1, 8);
  x.add_creature(food, 7, WEST);
  ASSERT_TRUE(x._grid.at(7)==(long)&food);
  ASSERT_TRUE(x._direction[(long)&food]==0);

}

// ----------------------
// Darwin::check_in_front
// ----------------------

TEST (DarwinFixture, check_in_front_1) {
  Species f;
  Creature f1(f, EAST);
  Creature f2(f, EAST);

  Darwin x(4, 4);
  x.add_creature(f1, 1, EAST);
  x.add_creature(f2, 2, EAST);
  ASSERT_EQ(x.check_in_front(1), (long)&f2);
}
TEST (DarwinFixture, check_in_front_2) {
  Species f;
  Creature f1(f, EAST);
  Creature f2(f, WEST);

  Darwin x(4, 4);
  x.add_creature(f1, 1, EAST);
  x.add_creature(f2, 2, WEST);
  ASSERT_EQ(x.check_in_front(2), (long)&f1);
}
TEST (DarwinFixture, check_in_front_3) {
  Species f;
  Creature f1(f, SOUTH);
  Creature f2(f, SOUTH);

  Darwin x(4, 4);
  x.add_creature(f1, 1, SOUTH);
  x.add_creature(f2, 2, SOUTH);
  ASSERT_EQ(x.check_in_front(1), 0);
  ASSERT_EQ(x.check_in_front(2), 0);
}

// ---------------------
// Darwin::wall_in_front
// ---------------------

TEST (DarwinFixture, wall_in_front_1) {
   Species f;
  Creature f1(f, EAST);

  Darwin x(4, 4);
  x.add_creature(f1, 3, EAST);
  ASSERT_TRUE(x.wall_in_front(3));
}
TEST (DarwinFixture, wall_in_front_2) {
  Species f;
  Creature f1(f, SOUTH);

  Darwin x(4, 4);
  x.add_creature(f1, 3, SOUTH);
  ASSERT_FALSE(x.wall_in_front(3));
}
TEST (DarwinFixture, wall_in_front_3) {
  Species f;
  Creature f1(f, NORTH);
  Creature f2(f, NORTH);

  Darwin x(4, 4);
  x.add_creature(f1, 1, NORTH);
  x.add_creature(f2, 2, NORTH);
  ASSERT_TRUE(x.wall_in_front(1));
  ASSERT_TRUE(x.wall_in_front(2));
}

// -----------------
// Darwin::do_action
// -----------------

TEST (DarwinFixture, do_action_1) {
  Species s;
  s.add_instruction(Instructions::HOP, 0);
  Creature f(s, EAST);
  Darwin x(4, 4);
  x.add_creature(f, 0, EAST);
  x.do_action(0);
  ASSERT_EQ(x._grid.at(0), 0);
  ASSERT_EQ(x._grid.at(1), (long)&f);
}
TEST (DarwinFixture, do_action_2) {
  Species s;
  s.add_instruction(Instructions::GO, 1);
  s.add_instruction(Instructions::IF_WALL, 3);
  s.add_instruction(Instructions::LEFT, 0);
  s.add_instruction(Instructions::RIGHT, 0);
  Creature f(s, WEST);
  Darwin x(4, 4);
  x.add_creature(f, 0, WEST);
  x.do_action(0);
  ASSERT_EQ(x._grid.at(0), (long)&f);
  ASSERT_EQ(x._direction[(long)&f], NORTH);
}
TEST (DarwinFixture, do_action_3) {
  Species s;
  s.add_instruction(Instructions::GO, 1);
  s.add_instruction(Instructions::IF_EMPTY, 3);
  s.add_instruction(Instructions::LEFT, 0);
  s.add_instruction(Instructions::HOP, 0);
  Creature f(s, SOUTH);
  Darwin x(4, 4);
  x.add_creature(f, 0, SOUTH);
  x.do_action(0);
  ASSERT_EQ(x._grid.at(0), 0);
  ASSERT_EQ(x._grid.at(4), (long)&f);
}

// -----------------
// Darwin::next_turn
// -----------------

TEST (DarwinFixture, next_turn_1){
  Species s;
  s.add_instruction(Instructions::HOP, 0);
  s.add_instruction(Instructions::GO, 0);
  Creature h1(s, SOUTH);
  Darwin x(5, 5);
  x.add_creature(h1, 2, SOUTH);
  x.next_turn();
  ASSERT_TRUE(x._grid.at(7)==(long)&h1);
  ASSERT_TRUE(x._direction[(long)&h1]==3);
  
}
TEST (DarwinFixture, next_turn_2){
  Species r;
  r.add_instruction(Instructions::IF_ENEMY, 9);
  r.add_instruction(Instructions::IF_EMPTY, 7);
  r.add_instruction(Instructions::IF_RANDOM, 5);
  r.add_instruction(Instructions::LEFT, 0);
  r.add_instruction(Instructions::GO, 0);
  r.add_instruction(Instructions::RIGHT, 0);
  r.add_instruction(Instructions::GO, 0);
  r.add_instruction(Instructions::HOP, 0);
  r.add_instruction(Instructions::GO, 0);
  r.add_instruction(Instructions::INFECT, 0);
  r.add_instruction(Instructions::GO, 0);
  Creature h1(r, EAST);
  Species r2;
  r2.add_instruction(Instructions::IF_ENEMY, 9);
  r2.add_instruction(Instructions::IF_EMPTY, 7);
  r2.add_instruction(Instructions::IF_RANDOM, 5);
  r2.add_instruction(Instructions::LEFT, 0);
  r2.add_instruction(Instructions::GO, 0);
  r2.add_instruction(Instructions::RIGHT, 0);
  r2.add_instruction(Instructions::GO, 0);
  r2.add_instruction(Instructions::HOP, 0);
  r2.add_instruction(Instructions::GO, 0);
  r2.add_instruction(Instructions::INFECT, 0);
  r2.add_instruction(Instructions::GO, 0);
  Creature h2(r, WEST);

  Darwin x(10, 9);
  x.add_creature(h1, 20, EAST);
  x.add_creature(h2, 21, WEST);
  x.next_turn();
  ASSERT_TRUE(x._grid.at(21)==(long)&h2);
  ASSERT_TRUE(x._grid.at(20)==(long)&h1);
  ASSERT_TRUE(x._direction[(long)&h1]==1||x._direction[(long)&h1]==3);
  ASSERT_TRUE(x._direction[(long)&h2]==1||x._direction[(long)&h2]==3);
  
}
TEST (DarwinFixture, next_turn_3){
  Species r('r');
  r.add_instruction(Instructions::IF_ENEMY, 9);
  r.add_instruction(Instructions::IF_EMPTY, 7);
  r.add_instruction(Instructions::IF_RANDOM, 5);
  r.add_instruction(Instructions::LEFT, 0);
  r.add_instruction(Instructions::GO, 0);
  r.add_instruction(Instructions::RIGHT, 0);
  r.add_instruction(Instructions::GO, 0);
  r.add_instruction(Instructions::HOP, 0);
  r.add_instruction(Instructions::GO, 0);
  r.add_instruction(Instructions::INFECT, 0);
  r.add_instruction(Instructions::GO, 0);
  Creature h1(r, EAST);
  Species f;
  f.add_instruction(Instructions::GO, 1);
  f.add_instruction(Instructions::LEFT, 0);
  Creature f1(f, NORTH);
  Darwin x(12, 3);
  x.add_creature(h1, 4, EAST);
  x.add_creature(f1, 5, NORTH);
  x.next_turn();
  ostringstream os;
  f1.print(os);
  ASSERT_TRUE(os.str()=="r");
}

// -------------
// Darwin::print
// -------------

TEST (DarwinFixture, print_1) {
  Species f;
  Creature f1(f, NORTH);
  Darwin x(4,4);
  x.add_creature(f1, 0, NORTH);

  ostringstream os1;
  os1 << "  0123\n" << "0f...\n" << "1....\n" << "2....\n" << "3....\n";
  ostringstream os2;
  x.print(os2);
  ASSERT_EQ(os1.str(), os2.str());
}
TEST (DarwinFixture, print_2) {
  Species f;
  Creature f1(f, NORTH);
  Creature f2(f, SOUTH);
  Creature f3(f, EAST);
  Creature f4(f, WEST);
  Darwin x(4,4);
  x.add_creature(f1, 0, NORTH);
  x.add_creature(f2, 5, SOUTH);
  x.add_creature(f3, 10, EAST);
  x.add_creature(f4, 15, WEST);

  ostringstream os1;
  os1 << "  0123\n" << "0f...\n" << "1.f..\n" << "2..f.\n" << "3...f\n";
  ostringstream os2;
  x.print(os2);
  ASSERT_EQ(os1.str(), os2.str());
}
TEST (DarwinFixture, print_3) {
  Species f;
  Species r('r');
  Species t('t');
  Species h('h');
  Creature f1(f, NORTH);
  Creature r1(r, SOUTH);
  Creature t1(t, EAST);
  Creature h1(h, WEST);
  Darwin x(4,4);
  x.add_creature(f1, 0, NORTH);
  x.add_creature(r1, 5, SOUTH);
  x.add_creature(t1, 10, EAST);
  x.add_creature(h1, 15, WEST);

  ostringstream os1;
  os1 << "  0123\n" << "0f...\n" << "1.r..\n" << "2..t.\n" << "3...h\n";
  ostringstream os2;
  x.print(os2);
  ASSERT_EQ(os1.str(), os2.str());
}
