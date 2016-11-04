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
#include <sstream> // istringtstream, ostringstream

#include "Darwin.h"

using namespace std;

// ----
// Species
// ----

TEST(SpeciesFixture, species_constuct1) {
  Species one('.');
  ostringstream out;
  out << one;
  ASSERT_EQ(".", out.str());
}

TEST(SpeciesFixture, species_constuct2) {
  Species one('r');
  ostringstream out;
  out << one;
  ASSERT_EQ("r", out.str());
}

TEST(SpeciesFixture, species_constuct3) {
  Species one('e');
  ostringstream out;
  out << one;
  ASSERT_EQ("e", out.str());
}

TEST(SpeciesFixture, species_eq1) {
  Species one('r');
  Species two('r');
  ASSERT_EQ(one, two);
}

TEST(SpeciesFixture, species_eq2) {
  Species one('e');
  Species two('e');
  ASSERT_EQ(one, two);
}

TEST(SpeciesFixture, species_eq3) {
  Species one('.');
  Species two('.');
  ASSERT_EQ(one, two);
}

TEST(SpeciesFixture, species_ne1) {
  Species one('r');
  Species two('e');
  ASSERT_NE(one, two);
}

TEST(SpeciesFixture, species_ne2) {
  Species one('e');
  Species two('r');
  ASSERT_NE(one, two);
}

TEST(SpeciesFixture, species_ne3) {
  Species one('.');
  Species two('r');
  ASSERT_NE(one, two);
}

TEST(SpeciesFixture, species_print1) {
  Species one('.');
  ostringstream out;
  out << one;
  ASSERT_EQ(".", out.str());
}

TEST(SpeciesFixture, species_print2) {
  Species one('r');
  ostringstream out;
  out << one;
  ASSERT_EQ("r", out.str());
}

TEST(SpeciesFixture, species_print3) {
  Species one('e');
  ostringstream out;
  out << one;
  ASSERT_EQ("e", out.str());
}

TEST(SpeciesFixture, species_execute1) {
  Species one('r');
  one.add(InstructionType::HOP);
  unsigned int i = 0;
  InstructionType a = one.execute(Cell::EMPTY, i);
  ASSERT_EQ(i, 1);
  ASSERT_EQ(a, InstructionType::HOP);
}

TEST(SpeciesFixture, species_execute2) {
  Species one('r');
  one.add(InstructionType::LEFT);
  unsigned int i = 0;
  InstructionType a = one.execute(Cell::EMPTY, i);
  ASSERT_EQ(i, 1);
  ASSERT_EQ(a, InstructionType::LEFT);
}

TEST(SpeciesFixture, species_execute3) {
  Species one('r');
  one.add(InstructionType::RIGHT);
  unsigned int i = 0;
  InstructionType a = one.execute(Cell::EMPTY, i);
  ASSERT_EQ(i, 1);
  ASSERT_EQ(a, InstructionType::RIGHT);
}

TEST(SpeciesFixture, species_execute4) {
  Species one('r');
  one.add(InstructionType::INFECT);
  unsigned int i = 0;
  InstructionType a = one.execute(Cell::EMPTY, i);
  ASSERT_EQ(i, 1);
  ASSERT_EQ(a, InstructionType::INFECT);
}

TEST(SpeciesFixture, species_execute_conditional1) {
  Species one('r');
  one.add(InstructionType::IF_EMPTY, 1);
  one.add(InstructionType::HOP);
  unsigned int i = 0;
  InstructionType a = one.execute(Cell::EMPTY, i);
  ASSERT_EQ(i, 2);
  ASSERT_EQ(a, InstructionType::HOP);
}

TEST(SpeciesFixture, species_execute_conditional2) {
  Species one('r');
  one.add(InstructionType::IF_ENEMY, 1);
  one.add(InstructionType::HOP);
  unsigned int i = 0;
  InstructionType a = one.execute(Cell::ENEMY, i);
  ASSERT_EQ(i, 2);
  ASSERT_EQ(a, InstructionType::HOP);
}

TEST(SpeciesFixture, species_execute_conditional3) {
  Species one('r');
  one.add(InstructionType::IF_WALL, 1);
  one.add(InstructionType::HOP);
  unsigned int i = 0;
  InstructionType a = one.execute(Cell::WALL, i);
  ASSERT_EQ(i, 2);
  ASSERT_EQ(a, InstructionType::HOP);
}

TEST(SpeciesFixture, species_execute_conditional4) {
  Species one('r');
  one.add(InstructionType::IF_EMPTY, 2);
  one.add(InstructionType::LEFT);
  one.add(InstructionType::HOP);
  unsigned int i = 0;
  InstructionType a = one.execute(Cell::WALL, i);
  ASSERT_EQ(i, 2);
  ASSERT_EQ(a, InstructionType::LEFT);
}

TEST(SpeciesFixture, species_execute_goto1) {
  Species one('r');
  one.add(InstructionType::IF_ENEMY, 1);
  one.add(InstructionType::GOTO, 2);
  one.add(InstructionType::HOP);
  unsigned int i = 0;
  InstructionType a = one.execute(Cell::ENEMY, i);
  ASSERT_EQ(i, 3);
  ASSERT_EQ(a, InstructionType::HOP);
}

TEST(SpeciesFixture, species_execute_goto2) {
  Species one('r');
  one.add(InstructionType::IF_EMPTY, 1);
  one.add(InstructionType::GOTO, 5);
  one.add(InstructionType::HOP);
  one.add(InstructionType::HOP);
  one.add(InstructionType::HOP);
  one.add(InstructionType::HOP);
  unsigned int i = 0;
  InstructionType a = one.execute(Cell::EMPTY, i);
  ASSERT_EQ(i, 6);
  ASSERT_EQ(a, InstructionType::HOP);
}

TEST(SpeciesFixture, species_execute_goto3) {
  Species one('r');
  one.add(InstructionType::IF_WALL, 1);
  one.add(InstructionType::GOTO, 3);
  one.add(InstructionType::HOP);
  one.add(InstructionType::HOP);
  unsigned int i = 0;
  InstructionType a = one.execute(Cell::WALL, i);
  ASSERT_EQ(i, 4);
  ASSERT_EQ(a, InstructionType::HOP);
}

TEST(CreatureFixture, creature_constuct1) {
  Species one('.');
  Creature creature(one, Direction::NORTH);
  ostringstream out;
  out << creature;
  ASSERT_EQ(".", out.str());
}

TEST(CreatureFixture, creature_constuct2) {
  Species one('r');
  Creature creature(one, Direction::NORTH);
  ostringstream out;
  out << creature;
  ASSERT_EQ("r", out.str());
}

TEST(CreatureFixture, creature_constuct3) {
  Species one('e');
  Creature creature(one, Direction::NORTH);
  ostringstream out;
  out << creature;
  ASSERT_EQ("e", out.str());
}

TEST(CreatureFixture, creature_print1) {
  Species one('.');
  Creature creature(one, Direction::NORTH);
  ostringstream out;
  out << creature;
  ASSERT_EQ(".", out.str());
}

TEST(CreatureFixture, creature_print2) {
  Species one('r');
  Creature creature(one, Direction::NORTH);
  ostringstream out;
  out << creature;
  ASSERT_EQ("r", out.str());
}

TEST(CreatureFixture, creature_print3) {
  Species one('e');
  Creature creature(one, Direction::NORTH);
  ostringstream out;
  out << creature;
  ASSERT_EQ("e", out.str());
}

TEST(CreatureFixture, creature_friend_self1) {
  Species one('e');
  Creature creature1(one, Direction::NORTH);
  ASSERT_TRUE(creature1.friendWith(creature1));
}

TEST(CreatureFixture, creature_friend_self2) {
  Species one('r');
  Creature creature1(one, Direction::NORTH);
  ASSERT_TRUE(creature1.friendWith(creature1));
}

TEST(CreatureFixture, creature_friend_self3) {
  Species one('.');
  Creature creature1(one, Direction::NORTH);
  ASSERT_TRUE(creature1.friendWith(creature1));
}

TEST(CreatureFixture, creature_friend1) {
  Species one('r');
  Species two('r');
  Creature creature1(one, Direction::NORTH);
  Creature creature2(two, Direction::NORTH);
  ASSERT_TRUE(creature1.friendWith(creature2));
}

TEST(CreatureFixture, creature_friend2) {
  Species one('e');
  Species two('e');
  Creature creature1(one, Direction::NORTH);
  Creature creature2(two, Direction::NORTH);
  ASSERT_TRUE(creature1.friendWith(creature2));
}

TEST(CreatureFixture, creature_friend3) {
  Species one('.');
  Species two('.');
  Creature creature1(one, Direction::NORTH);
  Creature creature2(two, Direction::NORTH);
  ASSERT_TRUE(creature1.friendWith(creature2));
}

TEST(CreatureFixture, creature_enemy1) {
  Species one('e');
  Species two('r');
  Creature creature1(one, Direction::NORTH);
  Creature creature2(two, Direction::NORTH);
  ASSERT_FALSE(creature1.friendWith(creature2));
}

TEST(CreatureFixture, creature_enemy2) {
  Species one('r');
  Species two('e');
  Creature creature1(one, Direction::NORTH);
  Creature creature2(two, Direction::NORTH);
  ASSERT_FALSE(creature1.friendWith(creature2));
}

TEST(CreatureFixture, creature_enemy3) {
  Species one('.');
  Species two('r');
  Creature creature1(one, Direction::NORTH);
  Creature creature2(two, Direction::NORTH);
  ASSERT_FALSE(creature1.friendWith(creature2));
}

TEST(CreatureFixture, creature_infect1) {
  Species one('e');
  Species two('r');
  Creature creature1(one, Direction::NORTH);
  Creature creature2(two, Direction::NORTH);
  creature1.infect(creature2);
  ASSERT_TRUE(creature1.friendWith(creature2));
}

TEST(CreatureFixture, creature_infect2) {
  Species one('e');
  Species two('e');
  Creature creature1(one, Direction::NORTH);
  Creature creature2(two, Direction::NORTH);
  creature1.infect(creature2);
  ASSERT_TRUE(creature1.friendWith(creature2));
}

TEST(CreatureFixture, creature_infect3) {
  Species one('e');
  Species two('.');
  Creature creature1(one, Direction::NORTH);
  Creature creature2(two, Direction::NORTH);
  creature1.infect(creature2);
  ASSERT_TRUE(creature1.friendWith(creature2));
}

TEST(CreatureFixture, creature_execute1) {
  Species one('e');
  one.add(InstructionType::IF_WALL, 1);
  one.add(InstructionType::GOTO, 3);
  one.add(InstructionType::HOP);
  one.add(InstructionType::HOP);
  Creature creature1(one, Direction::WEST);
  array<Cell, 4> neighbors = {Cell::WALL, Cell::EMPTY, Cell::EMPTY,
                              Cell::EMPTY};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::HOP);
  ASSERT_EQ(a.direction, Direction::WEST);
}

TEST(CreatureFixture, creature_execute2) {
  Species one('e');
  one.add(InstructionType::IF_EMPTY, 2);
  one.add(InstructionType::INFECT);
  one.add(InstructionType::HOP);
  Creature creature1(one, Direction::WEST);
  array<Cell, 4> neighbors = {Cell::EMPTY, Cell::EMPTY, Cell::EMPTY,
                              Cell::EMPTY};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::HOP);
  ASSERT_EQ(a.direction, Direction::WEST);
}

TEST(CreatureFixture, creature_execute3) {
  Species one('e');
  one.add(InstructionType::IF_EMPTY, 2);
  one.add(InstructionType::INFECT);
  one.add(InstructionType::HOP);
  Creature creature1(one, Direction::WEST);
  array<Cell, 4> neighbors = {Cell::WALL, Cell::EMPTY, Cell::EMPTY,
                              Cell::EMPTY};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::INFECT);
  ASSERT_EQ(a.direction, Direction::WEST);
}

TEST(CreatureFixture, creature_execute_direction1) {
  Species one('e');
  one.add(InstructionType::IF_EMPTY, 2);
  one.add(InstructionType::LEFT);
  one.add(InstructionType::HOP);
  Creature creature1(one, Direction::WEST);
  array<Cell, 4> neighbors = {Cell::WALL, Cell::EMPTY, Cell::EMPTY,
                              Cell::EMPTY};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::LEFT);
  ASSERT_EQ(a.direction, Direction::SOUTH);
}

TEST(CreatureFixture, creature_execute_direction2) {
  Species one('e');
  one.add(InstructionType::IF_EMPTY, 2);
  one.add(InstructionType::LEFT);
  one.add(InstructionType::HOP);
  Creature creature1(one, Direction::EAST);
  array<Cell, 4> neighbors = {Cell::WALL, Cell::EMPTY, Cell::WALL, Cell::EMPTY};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::LEFT);
  ASSERT_EQ(a.direction, Direction::NORTH);
}

TEST(CreatureFixture, creature_execute_direction3) {
  Species one('e');
  one.add(InstructionType::IF_EMPTY, 2);
  one.add(InstructionType::LEFT);
  one.add(InstructionType::HOP);
  Creature creature1(one, Direction::NORTH);
  array<Cell, 4> neighbors = {Cell::WALL, Cell::WALL, Cell::EMPTY, Cell::EMPTY};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::LEFT);
  ASSERT_EQ(a.direction, Direction::WEST);
}

TEST(CreatureFixture, creature_execute_direction4) {
  Species one('e');
  one.add(InstructionType::IF_EMPTY, 2);
  one.add(InstructionType::LEFT);
  one.add(InstructionType::HOP);
  Creature creature1(one, Direction::SOUTH);
  array<Cell, 4> neighbors = {Cell::WALL, Cell::EMPTY, Cell::EMPTY, Cell::WALL};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::LEFT);
  ASSERT_EQ(a.direction, Direction::EAST);
}

TEST(CreatureFixture, creature_execute_direction5) {
  Species one('e');
  one.add(InstructionType::IF_EMPTY, 2);
  one.add(InstructionType::RIGHT);
  one.add(InstructionType::HOP);
  Creature creature1(one, Direction::WEST);
  array<Cell, 4> neighbors = {Cell::WALL, Cell::EMPTY, Cell::EMPTY,
                              Cell::EMPTY};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::RIGHT);
  ASSERT_EQ(a.direction, Direction::NORTH);
}

TEST(CreatureFixture, creature_execute_direction6) {
  Species one('e');
  one.add(InstructionType::IF_EMPTY, 2);
  one.add(InstructionType::RIGHT);
  one.add(InstructionType::HOP);
  Creature creature1(one, Direction::EAST);
  array<Cell, 4> neighbors = {Cell::WALL, Cell::EMPTY, Cell::WALL, Cell::EMPTY};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::RIGHT);
  ASSERT_EQ(a.direction, Direction::SOUTH);
}

TEST(CreatureFixture, creature_execute_direction7) {
  Species one('e');
  one.add(InstructionType::IF_EMPTY, 2);
  one.add(InstructionType::RIGHT);
  one.add(InstructionType::HOP);
  Creature creature1(one, Direction::NORTH);
  array<Cell, 4> neighbors = {Cell::WALL, Cell::WALL, Cell::EMPTY, Cell::EMPTY};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::RIGHT);
  ASSERT_EQ(a.direction, Direction::EAST);
}

TEST(CreatureFixture, creature_execute_direction8) {
  Species one('e');
  one.add(InstructionType::IF_EMPTY, 2);
  one.add(InstructionType::RIGHT);
  one.add(InstructionType::HOP);
  Creature creature1(one, Direction::SOUTH);
  array<Cell, 4> neighbors = {Cell::WALL, Cell::EMPTY, Cell::EMPTY, Cell::WALL};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::RIGHT);
  ASSERT_EQ(a.direction, Direction::WEST);
}

TEST(CreatureFixture, creature_execute_direction9) {
  srand(0);
  Species rover('r');
  rover.add(InstructionType::IF_ENEMY, 9);
  rover.add(InstructionType::IF_EMPTY, 7);
  rover.add(InstructionType::IF_RANDOM, 5);
  rover.add(InstructionType::LEFT);
  rover.add(InstructionType::GOTO, 0);
  rover.add(InstructionType::RIGHT);
  rover.add(InstructionType::GOTO, 0);
  rover.add(InstructionType::HOP);
  rover.add(InstructionType::GOTO, 0);
  rover.add(InstructionType::INFECT);
  rover.add(InstructionType::GOTO, 0);
  Creature creature1(rover, Direction::NORTH);
  array<Cell, 4> neighbors = {Cell::WALL, Cell::WALL, Cell::EMPTY, Cell::WALL};
  Action a = creature1.execute(neighbors);
  ASSERT_EQ(a.type, InstructionType::RIGHT);
  ASSERT_EQ(a.direction, Direction::EAST);
}

TEST(DarwinFixture, darwin_construct1) {
  Darwin d(1, 1);
  ostringstream out;
  out << d;
  ASSERT_EQ("Turn = 0.\n  0\n0 .\n\n", out.str());
}

TEST(DarwinFixture, darwin_construct2) {
  Darwin d(1, 2);
  ostringstream out;
  out << d;
  ASSERT_EQ("Turn = 0.\n  01\n0 ..\n\n", out.str());
}

TEST(DarwinFixture, darwin_construct3) {
  Darwin d(2, 1);
  ostringstream out;
  out << d;
  ASSERT_EQ("Turn = 0.\n  0\n0 .\n1 .\n\n", out.str());
}

TEST(DarwinFixture, darwin_print1) {
  Darwin d(11, 11);
  ostringstream out;
  out << d;
  ASSERT_EQ(string("Turn = 0.\n  01234567890\n") + string("0 ...........\n") +
                string("1 ...........\n") + string("2 ...........\n") +
                string("3 ...........\n") + string("4 ...........\n") +
                string("5 ...........\n") + string("6 ...........\n") +
                string("7 ...........\n") + string("8 ...........\n") +
                string("9 ...........\n") + string("0 ...........\n") +
                string("\n"),
            out.str());
}

TEST(DarwinFixture, darwin_print2) {
  Darwin d(11, 11);
  Species e('e');
  Creature c(e, Direction::WEST);
  d.add(c, 0, 0);
  ostringstream out;
  out << d;
  ASSERT_EQ(string("Turn = 0.\n  01234567890\n") + string("0 e..........\n") +
                string("1 ...........\n") + string("2 ...........\n") +
                string("3 ...........\n") + string("4 ...........\n") +
                string("5 ...........\n") + string("6 ...........\n") +
                string("7 ...........\n") + string("8 ...........\n") +
                string("9 ...........\n") + string("0 ...........\n") +
                string("\n"),
            out.str());
}

TEST(DarwinFixture, darwin_print3) {
  Darwin d(11, 11);
  Species e('e');
  Creature c(e, Direction::WEST);
  d.add(c, 0, 1);
  ostringstream out;
  out << d;
  ASSERT_EQ(string("Turn = 0.\n  01234567890\n") + string("0 .e.........\n") +
                string("1 ...........\n") + string("2 ...........\n") +
                string("3 ...........\n") + string("4 ...........\n") +
                string("5 ...........\n") + string("6 ...........\n") +
                string("7 ...........\n") + string("8 ...........\n") +
                string("9 ...........\n") + string("0 ...........\n") +
                string("\n"),
            out.str());
}

TEST(DarwinFixture, darwin_print4) {
  Darwin d(11, 11);
  Species e('e');
  Creature c(e, Direction::WEST);
  d.add(c, 1, 0);
  ostringstream out;
  out << d;
  ASSERT_EQ(string("Turn = 0.\n  01234567890\n") + string("0 ...........\n") +
                string("1 e..........\n") + string("2 ...........\n") +
                string("3 ...........\n") + string("4 ...........\n") +
                string("5 ...........\n") + string("6 ...........\n") +
                string("7 ...........\n") + string("8 ...........\n") +
                string("9 ...........\n") + string("0 ...........\n") +
                string("\n"),
            out.str());
}

TEST(DarwinFixture, darwin_print5) {
  Darwin d(11, 11);
  Species e('e');
  Species r('r');
  Creature c(e, Direction::WEST);
  Creature c2(r, Direction::WEST);
  d.add(c, 1, 0);
  d.add(c2, 0, 1);
  ostringstream out;
  out << d;
  ASSERT_EQ(string("Turn = 0.\n  01234567890\n") + string("0 .r.........\n") +
                string("1 e..........\n") + string("2 ...........\n") +
                string("3 ...........\n") + string("4 ...........\n") +
                string("5 ...........\n") + string("6 ...........\n") +
                string("7 ...........\n") + string("8 ...........\n") +
                string("9 ...........\n") + string("0 ...........\n") +
                string("\n"),
            out.str());
}

TEST(DarwinFixture, darwin_print6) {
  Darwin d(11, 11);
  Species e('e');
  Species r('r');
  Creature c(e, Direction::WEST);
  Creature c2(r, Direction::WEST);
  d.add(c, 10, 0);
  d.add(c2, 0, 10);
  ostringstream out;
  out << d;
  ASSERT_EQ(string("Turn = 0.\n  01234567890\n") + string("0 ..........r\n") +
                string("1 ...........\n") + string("2 ...........\n") +
                string("3 ...........\n") + string("4 ...........\n") +
                string("5 ...........\n") + string("6 ...........\n") +
                string("7 ...........\n") + string("8 ...........\n") +
                string("9 ...........\n") + string("0 e..........\n") +
                string("\n"),
            out.str());
}

TEST(DarwinFixture, darwin_print7) {
  Darwin d(11, 11);
  Species e('e');
  Species r('r');
  Creature c(e, Direction::WEST);
  Creature c2(r, Direction::WEST);
  d.add(c, 5, 4);
  d.add(c2, 6, 7);
  ostringstream out;
  out << d;
  ASSERT_EQ(string("Turn = 0.\n  01234567890\n") + string("0 ...........\n") +
                string("1 ...........\n") + string("2 ...........\n") +
                string("3 ...........\n") + string("4 ...........\n") +
                string("5 ....e......\n") + string("6 .......r...\n") +
                string("7 ...........\n") + string("8 ...........\n") +
                string("9 ...........\n") + string("0 ...........\n") +
                string("\n"),
            out.str());
}

TEST(DarwinFixture, darwin_print8) {
  Darwin d(11, 11);
  Species e('e');
  Species r('r');
  Creature c(e, Direction::WEST);
  Creature c2(r, Direction::WEST);
  d.add(c, 1, 2);
  d.add(c2, 8, 9);
  ostringstream out;
  out << d;
  ASSERT_EQ(string("Turn = 0.\n  01234567890\n") + string("0 ...........\n") +
                string("1 ..e........\n") + string("2 ...........\n") +
                string("3 ...........\n") + string("4 ...........\n") +
                string("5 ...........\n") + string("6 ...........\n") +
                string("7 ...........\n") + string("8 .........r.\n") +
                string("9 ...........\n") + string("0 ...........\n") +
                string("\n"),
            out.str());
}

TEST(DarwinFixture, darwin_loop1) {
  Darwin d(11, 11);
  Species e('e');
  e.add(InstructionType::HOP);
  Species r('r');
  r.add(InstructionType::HOP);
  Creature c(e, Direction::WEST);
  Creature c2(r, Direction::WEST);
  d.add(c, 1, 2);
  d.add(c2, 8, 9);
  d.loop();
  ostringstream out;
  out << d;
  ASSERT_EQ(string("Turn = 1.\n  01234567890\n") + string("0 ...........\n") +
                string("1 .e.........\n") + string("2 ...........\n") +
                string("3 ...........\n") + string("4 ...........\n") +
                string("5 ...........\n") + string("6 ...........\n") +
                string("7 ...........\n") + string("8 ........r..\n") +
                string("9 ...........\n") + string("0 ...........\n") +
                string("\n"),
            out.str());
}