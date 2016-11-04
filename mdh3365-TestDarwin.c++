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

#include <string>

using namespace std;

/*
* Tests for Species
*/

// Test species constructor
TEST(SpeciesFixture, species_constructor1) {
  Species s("s");
  ASSERT_EQ(s.to_string(), "s");
}
TEST(SpeciesFixture, species_constructor2) {
  Species s("f");
  ASSERT_EQ(s.to_string(), "f");
}
TEST(SpeciesFixture, species_constructor3) {
  Species a("a");
  Species b(a);
  ASSERT_EQ(b.to_string(), "a");
}

// Test execute
TEST(SpeciesFixture, species_execute1) {
  Species a("a");
  a.addInstruction(Action::hop);
  ASSERT_EQ(a.execute(0)._a, Action::hop);
}
TEST(SpeciesFixture, species_execute2) {
  Species a("a");
  a.addInstruction(Action::hop);
  a.addInstruction(Action::go, 0);
  a.execute(0);
  ASSERT_EQ(a.execute(1)._a, Action::go);
}

// Test Creature Constructor
TEST(CreatureFixture, creature_constructor1) {
  Creature c;
  ASSERT_EQ(c.front(), Direction::N);
}
TEST(CreatureFixture, creature_constructor2) {
  Species s("s");
  Creature c(s, Direction::S);
  ASSERT_EQ(c.front(), Direction::S);
}
TEST(CreatureFixture, creature_constructor3) {
  Species s("s");
  Creature c(s, Direction::E);
  ASSERT_EQ(c.front(), Direction::E);
}

// Test is_control_action
TEST(CreatureFixture, is_control_action1) {
  Creature c;
  ASSERT_TRUE(c.is_control_action(Action::go));
}
TEST(CreatureFixture, is_control_action2) {
  Creature c;
  ASSERT_TRUE(c.is_control_action(Action::if_enemy));
}
TEST(CreatureFixture, is_control_action3) {
  Creature c;
  ASSERT_FALSE(c.is_control_action(Action::hop));
}

// Test take_turn
TEST(CreatureFixture, take_turn1) {
  Species s("s");
  s.addInstruction(Action::hop);
  Creature c(s, Direction::E);
  ASSERT_EQ(c.take_turn(0)._a, Action::hop);
}
TEST(CreatureFixture, take_turn2) {
  Species s("s");
  s.addInstruction(Action::hop);
  s.addInstruction(Action::if_empty);
  Creature c(s, Direction::E);
  c.take_turn(0);
  ASSERT_EQ(c.take_turn(1)._a, Action::if_empty);
}
TEST(CreatureFixture, take_turn3) {
  Species s("s");
  s.addInstruction(Action::hop);
  s.addInstruction(Action::go);
  Creature c(s, Direction::E);
  c.take_turn(0);
  ASSERT_EQ(c.take_turn(1)._a, Action::go);
}

// Test most_recent_turn
TEST(CreatureFixture, most_recent_turn1) {
  Species s("s");
  s.addInstruction(Action::hop);
  Creature c(s, Direction::E);
  c.take_turn(0);
  ASSERT_EQ(c.most_recent_turn(), 0);
}
TEST(CreatureFixture, most_recent_turn2) {
  Species s("s");
  s.addInstruction(Action::hop);
  s.addInstruction(Action::if_wall);
  Creature c(s, Direction::E);
  c.take_turn(0);
  c.take_turn(1);
  ASSERT_EQ(c.most_recent_turn(), 0);
}
TEST(CreatureFixture, most_recent_turn3) {
  Species s("s");
  s.addInstruction(Action::hop);
  s.addInstruction(Action::hop);
  Creature c(s, Direction::E);
  c.take_turn(0);
  c.take_turn(1);
  ASSERT_EQ(c.most_recent_turn(), 1);
}

// Test control_jump
TEST(CreatureFixture, control_jump1) {
  Species s("s");
  s.addInstruction(Action::hop);
  s.addInstruction(Action::hop);
  s.addInstruction(Action::go, 0);
  Creature c(s, Direction::E);
  c.take_turn(0);
  c.control_jump(0);
  ASSERT_EQ(c.take_turn(1)._a, Action::hop);
}
TEST(CreatureFixture, control_jump2) {
  Species s("s");
  s.addInstruction(Action::hop);
  s.addInstruction(Action::hop);
  s.addInstruction(Action::left);
  s.addInstruction(Action::go, 0);
  Creature c(s, Direction::E);
  c.take_turn(0);
  c.control_jump(2);
  ASSERT_EQ(c.take_turn(1)._a, Action::left);
}
TEST(CreatureFixture, control_jump3) {
  Species s("s");
  s.addInstruction(Action::hop);
  s.addInstruction(Action::hop);
  s.addInstruction(Action::left);
  s.addInstruction(Action::go, 0);
  Creature c(s, Direction::E);
  c.take_turn(0);
  c.control_jump(3);
  ASSERT_EQ(c.take_turn(1)._a, Action::go);
}

// Test turn_left
TEST(CreatureFixture, turn_left1) {
  Species s("s");
  Creature c(s, Direction::E);
  c.turn_left();
  ASSERT_EQ(c.front(), Direction::N);
}
TEST(CreatureFixture, turn_left2) {
  Species s("s");
  Creature c(s, Direction::N);
  c.turn_left();
  ASSERT_EQ(c.front(), Direction::W);
}
TEST(CreatureFixture, turn_left3) {
  Species s("s");
  Creature c(s, Direction::S);
  c.turn_left();
  ASSERT_EQ(c.front(), Direction::E);
}
TEST(CreatureFixture, turn_left4) {
  Species s("s");
  Creature c(s, Direction::W);
  c.turn_left();
  ASSERT_EQ(c.front(), Direction::S);
}

// Test turn_right
TEST(CreatureFixture, turn_right1) {
  Species s("s");
  Creature c(s, Direction::E);
  c.turn_right();
  ASSERT_EQ(c.front(), Direction::S);
}
TEST(CreatureFixture, turn_right2) {
  Species s("s");
  Creature c(s, Direction::N);
  c.turn_right();
  ASSERT_EQ(c.front(), Direction::E);
}
TEST(CreatureFixture, turn_right3) {
  Species s("s");
  Creature c(s, Direction::S);
  c.turn_right();
  ASSERT_EQ(c.front(), Direction::W);
}
TEST(CreatureFixture, turn_right4) {
  Species s("s");
  Creature c(s, Direction::W);
  c.turn_right();
  ASSERT_EQ(c.front(), Direction::N);
}

// Test front
TEST(CreatureFixture, front1) {
  Species s("s");
  Creature c(s, Direction::N);
  ASSERT_EQ(c.front(), Direction::N);
}
TEST(CreatureFixture, front2) {
  Species s("s");
  Creature c(s, Direction::S);
  ASSERT_EQ(c.front(), Direction::S);
}
TEST(CreatureFixture, front3) {
  Species s("s");
  Creature c(s, Direction::E);
  ASSERT_EQ(c.front(), Direction::E);
}

// Test is_enemy
TEST(CreatureFixture, is_enemy1) {
  Species a("a");
  Creature ac(a, Direction::N);
  Species b("b");
  Creature bc(b, Direction::S);
  ASSERT_TRUE(ac.is_enemy(bc));
}
TEST(CreatureFixture, is_enemy2) {
  Species a("a");
  Creature ac(a, Direction::N);
  Species b("a");
  Creature bc(b, Direction::S);
  ASSERT_FALSE(ac.is_enemy(bc));
}
TEST(CreatureFixture, is_enemy3) {
  Species a("a");
  Creature ac(a, Direction::N);
  ASSERT_FALSE(ac.is_enemy(ac));
}

// Test infected_by
TEST(CreatureFixture, infected_by1) {
  Species a("a");
  Creature ac(a, Direction::N);
  Species b("b");
  Creature bc(b, Direction::S);
  ASSERT_TRUE(ac.is_enemy(bc));
  ac.infected_by(bc);
  ASSERT_FALSE(ac.is_enemy(bc));
}
TEST(CreatureFixture, infected_by2) {
  Species a("a");
  Creature ac(a, Direction::N);
  Species b("b");
  Creature bc(b, Direction::S);
  ac.infected_by(bc);
  ASSERT_EQ(ac.front(), Direction::N);
  ASSERT_EQ(bc.front(), Direction::S);
}
TEST(CreatureFixture, infected_by3) {
  Species a("a");
  Creature ac(a, Direction::N);
  Species b("b");
  b.addInstruction(Action::hop);
  b.addInstruction(Action::left);
  Creature bc(b, Direction::S);
  ac.take_turn(0);
  ac.infected_by(bc);
  ASSERT_EQ(ac.take_turn(1)._a, Action::hop);
}

/*
* Tests for Darwin
*/

// Test add_creature and get_creature
TEST(DarwinFixture, add_creature1) {
  Darwin x(8, 8);
  Species s("s");
  Creature c(s, Direction::N);
  x.add_creature(c, 1, 1);
  ASSERT_FALSE(x.get_creature(1, 1).is_enemy(c));
}
TEST(DarwinFixture, add_creature2) {
  Darwin x(8, 8);
  Species s("s");
  Creature c(s, Direction::N);
  x.add_creature(c, 1, 1);
  ASSERT_TRUE(x.get_creature(2, 2).is_enemy(c));
}
TEST(DarwinFixture, add_creature3) {
  Darwin x(8, 8);
  Species s("s");
  Creature c(s, Direction::N);
  x.add_creature(c, 5, 3);
  ASSERT_FALSE(x.get_creature(5, 3).is_enemy(c));
}

// Test run_num_turns
TEST(DarwinFixture, run_num_turns1) {
  Darwin x(2, 2);
  Species s("s");
  Creature c(s, Direction::N);
  x.add_creature(c, 1, 1);
  ostringstream w;
  x.run_num_turns(0, w);
  ASSERT_EQ("Turn = 0.\n  01\n0 ..\n1 .s\n\n", w.str());
}
TEST(DarwinFixture, run_num_turns2) {
  Darwin x(8, 8);
  Species s("s");
  Creature c(s, Direction::N);
  x.add_creature(c, 5, 5);
  ostringstream w;
  x.run_num_turns(0, w);
  ASSERT_EQ("Turn = 0.\n  01234567\n0 ........\n1 ........\n2 ........\n3 "
            "........\n4 ........\n5 .....s..\n6 ........\n7 ........\n\n",
            w.str());
}
TEST(DarwinFixture, run_num_turns3) {
  Darwin x(8, 8);
  Species s("s");
  s.addInstruction(Action::hop);
  Species b("b");
  b.addInstruction(Action::hop);
  b.addInstruction(Action::left);
  Creature c(s, Direction::N);
  Creature bc(b, Direction::S);
  x.add_creature(c, 5, 5);
  x.add_creature(bc, 1, 1);
  ostringstream w;
  x.run_num_turns(3, w);
  ASSERT_EQ("Turn = 0.\n  01234567\n0 ........\n1 .b......\n2 ........\n3 "
            "........\n4 ........\n5 .....s..\n6 ........\n7 ........\n\nTurn "
            "= 1.\n  01234567\n0 ........\n1 ........\n2 .b......\n3 "
            "........\n4 .....s..\n5 ........\n6 ........\n7 ........\n\nTurn "
            "= 2.\n  01234567\n0 ........\n1 ........\n2 .b......\n3 "
            ".....s..\n4 ........\n5 ........\n6 ........\n7 ........\n\nTurn "
            "= 3.\n  01234567\n0 ........\n1 ........\n2 ..b..s..\n3 "
            "........\n4 ........\n5 ........\n6 ........\n7 ........\n\n",
            w.str());
}
