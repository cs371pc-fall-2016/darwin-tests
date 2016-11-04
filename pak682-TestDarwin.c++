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

// -------
// Species
// -------

/* constructor */

TEST(SpeciesFixture, constructor) { Species s('h'); }

/* add_lines */

TEST(SpeciesFixture, add_lines1) {
  Species s('h');
  Line l(hop, 0);
  s.add_line(l);
  ASSERT_TRUE(s.line_at(0).i == l.i);
}

TEST(SpeciesFixture, add_lines2) {
  Species s('h');
  Line l1(hop, 0);
  Line l2(Left, 0);
  s.add_line(l1);
  s.add_line(l2);
  ASSERT_TRUE(s.line_at(1).i == l2.i);
}

TEST(SpeciesFixture, add_lines3) {
  Species s('h');
  Line l1(hop, 0);
  Line l2(Left, 0);
  s.add_line(l1);
  s.add_line(l2);
  ASSERT_TRUE(s.line_at(0).i == l1.i);
}

/* symbol */

TEST(SpeciesFixture, symbol) {
  Species s('h');
  ASSERT_TRUE(s.symbol() == 'h');
}

// --------
// Creature
// --------

/* constructor */

TEST(CreatureFixture, constructor) {
  Species s('h');
  Creature c(s, North);
}

/* execute */

TEST(CreatureFixture, execute1) {
  Species s('h');
  Line l1(go, 2);
  Line l2(Left);
  Line l3(Right);
  Line l4(go, 0);
  s.add_line(l1);
  s.add_line(l2);
  s.add_line(l3);
  s.add_line(l4);
  Creature c(s, North);
  Entity north = Empty;
  Entity east = Empty;
  Entity south = Empty;
  Entity west = Empty;
  Direction v = North;
  Direction *d = &v;
  Instruction ret = c.execute(north, east, south, west, d);

  ASSERT_TRUE(ret == Right);
  ASSERT_TRUE(c._line_num == 3);
  ASSERT_TRUE(c._d == East);
}

TEST(CreatureFixture, execute2) {
  Species s('h');
  Line l1(if_enemy, 2);
  Line l2(Right);
  Line l3(Left);
  Line l4(go, 0);
  s.add_line(l1);
  s.add_line(l2);
  s.add_line(l3);
  s.add_line(l4);
  Creature c(s, North);
  Entity north = Enemy;
  Entity east = Empty;
  Entity south = Empty;
  Entity west = Empty;
  Direction v = North;
  Direction *d = &v;
  Instruction ret = c.execute(north, east, south, west, d);

  ASSERT_TRUE(ret == Left);
  ASSERT_TRUE(c._line_num == 3);
  ASSERT_TRUE(c._d == West);
}

TEST(CreatureFixture, execute3) {
  Species s('h');
  Line l1(if_empty, 2);
  Line l2(Right);
  Line l3(hop);
  Line l4(go, 0);
  s.add_line(l1);
  s.add_line(l2);
  s.add_line(l3);
  s.add_line(l4);
  Creature c(s, North);
  Entity north = Empty;
  Entity east = Empty;
  Entity south = Empty;
  Entity west = Empty;
  Direction v = North;
  Direction *d = &v;
  Instruction ret = c.execute(north, east, south, west, d);

  ASSERT_TRUE(ret == hop);
  ASSERT_TRUE(c._line_num == 3);
  ASSERT_TRUE(c._d == North);
}

TEST(CreatureFixture, execute4) {
  Species s('h');
  Line l1(if_wall, 2);
  Line l2(Right);
  Line l3(infect);
  Line l4(go, 0);
  s.add_line(l1);
  s.add_line(l2);
  s.add_line(l3);
  s.add_line(l4);
  Creature c(s, North);
  Entity north = Wall;
  Entity east = Empty;
  Entity south = Empty;
  Entity west = Empty;
  Direction v = North;
  Direction *d = &v;
  Instruction ret = c.execute(north, east, south, west, d);

  ASSERT_TRUE(ret == infect);
  ASSERT_TRUE(c._line_num == 3);
  ASSERT_TRUE(c._d == North);
}

TEST(CreatureFixture, execute5) {
  Species s('h');
  Line l1(if_enemy, 2);
  Line l2(Right);
  Line l3(infect);
  Line l4(go, 0);
  s.add_line(l1);
  s.add_line(l2);
  s.add_line(l3);
  s.add_line(l4);
  Creature c(s, East);
  Entity north = Wall;
  Entity east = Empty;
  Entity south = Empty;
  Entity west = Empty;
  Direction v = North;
  Direction *d = &v;
  Instruction ret = c.execute(north, east, south, west, d);

  ASSERT_TRUE(ret == Right);
  ASSERT_TRUE(c._line_num == 2);
  ASSERT_TRUE(c._d == South);
}

TEST(CreatureFixture, execute6) {
  Species s('h');
  Line l1(if_empty, 2);
  Line l2(Right);
  Line l3(infect);
  Line l4(go, 0);
  s.add_line(l1);
  s.add_line(l2);
  s.add_line(l3);
  s.add_line(l4);
  Creature c(s, South);
  Entity north = Wall;
  Entity east = Empty;
  Entity south = Wall;
  Entity west = Empty;
  Direction v = North;
  Direction *d = &v;
  Instruction ret = c.execute(north, east, south, west, d);

  ASSERT_TRUE(ret == Right);
  ASSERT_TRUE(c._line_num == 2);
  ASSERT_TRUE(c._d == West);
}

TEST(CreatureFixture, execute7) {
  Species s('h');
  Line l1(if_wall, 2);
  Line l2(Right);
  Line l3(infect);
  Line l4(go, 0);
  s.add_line(l1);
  s.add_line(l2);
  s.add_line(l3);
  s.add_line(l4);
  Creature c(s, West);
  Entity north = Empty;
  Entity east = Empty;
  Entity south = Empty;
  Entity west = Empty;
  Direction v = North;
  Direction *d = &v;
  Instruction ret = c.execute(north, east, south, west, d);

  ASSERT_TRUE(ret == Right);
  ASSERT_TRUE(c._line_num == 2);
  ASSERT_TRUE(c._d == North);
}

TEST(CreatureFixture, execute8) {
  Species s('h');
  Line l1(if_random, 2);
  Line l2(Left);
  Line l3(infect);
  Line l4(go, 0);
  s.add_line(l1);
  s.add_line(l2);
  s.add_line(l3);
  s.add_line(l4);
  std::srand(0);
  Creature c(s, East);
  Entity north = Empty;
  Entity east = Empty;
  Entity south = Empty;
  Entity west = Empty;
  Direction v = North;
  Direction *d = &v;
  Instruction ret = c.execute(north, east, south, west, d);

  ASSERT_TRUE(ret == infect);
  ASSERT_TRUE(c._line_num == 3);
  ASSERT_TRUE(c._d == East);
}

/* turn_left */

TEST(CreatureFixture, turn_left1) {
  Species s('h');
  Line l1(if_wall, 2);
  Line l2(Right);
  Line l3(infect);
  Line l4(go, 0);
  s.add_line(l1);
  s.add_line(l2);
  s.add_line(l3);
  s.add_line(l4);
  Creature c(s, East);
  c.turn_left();
  ASSERT_TRUE(c._d == North);
}

TEST(CreatureFixture, turn_left2) {
  Species s('h');
  Line l1(if_wall, 2);
  Line l2(Right);
  Line l3(infect);
  Line l4(go, 0);
  s.add_line(l1);
  s.add_line(l2);
  s.add_line(l3);
  s.add_line(l4);
  Creature c(s, South);
  c.turn_left();
  ASSERT_TRUE(c._d == East);
}

TEST(CreatureFixture, turn_left3) {
  Species s('h');
  Line l1(if_wall, 2);
  Line l2(Right);
  Line l3(infect);
  Line l4(go, 0);
  s.add_line(l1);
  s.add_line(l2);
  s.add_line(l3);
  s.add_line(l4);
  Creature c(s, West);
  c.turn_left();
  ASSERT_TRUE(c._d == South);
}

/* infect */

TEST(CreatureFixture, infect) {
  Species s1('h');
  Line l1(hop);
  Line l2(go, 0);
  s1.add_line(l1);
  s1.add_line(l2);
  Species s2('i');
  Creature c1(s1, North);
  Creature c2(s2, East);
  Entity north = Empty;
  Entity east = Empty;
  Entity south = Empty;
  Entity west = Empty;
  Direction v = North;
  Direction *d = &v;
  c1.execute(north, east, south, west, d);
  Infect(c1, c2);

  ASSERT_TRUE(c1._s == &s2);
  ASSERT_TRUE(c1._line_num == 0);
  ASSERT_TRUE(c1._d == North);
}

/* are_allies */

TEST(CreatureFixture, are_allies) {
  Species s1('h');
  Line l1(hop);
  Line l2(go, 0);
  s1.add_line(l1);
  s1.add_line(l2);
  Creature c1(s1, North);
  Creature c2(s1, East);
  Entity north = Empty;
  Entity east = Empty;
  Entity south = Empty;
  Entity west = Empty;
  Direction v = North;
  Direction *d = &v;
  c1.execute(north, east, south, west, d);
  ASSERT_TRUE(are_allies(c1, c2));
}

// ------
// Darwin
// ------

/* add_creature */

TEST(DarwinFixture, add_creature) {
  Species s1('h');
  Line l1(hop);
  Line l2(go, 0);
  s1.add_line(l1);
  s1.add_line(l2);
  Creature c1(s1, North);

  Darwin d(2, 1);
  d.add_creature(1, c1);
}

/* turn */

TEST(DarwinFixture, turn1) {
  Species s1('h');
  Line l1(hop);
  Line l2(go, 0);
  s1.add_line(l1);
  s1.add_line(l2);
  Creature c1(s1, North);

  Darwin d(2, 1);
  d.add_creature(1, c1);
  d.turn();
  // d.print();
  ASSERT_TRUE(d.board[0] == &c1);
}

TEST(DarwinFixture, turn2) {
  Species s1('h');
  Species s2('h');
  Line l1(infect);
  Line l2(go, 0);
  Line l3(Left);
  Line l4(go, 0);
  s1.add_line(l1);
  s1.add_line(l2);
  s2.add_line(l3);
  s2.add_line(l4);
  Creature c1(s1, North);
  Creature c2(s2, North);
  Darwin d(2, 1);
  d.add_creature(1, c1);
  d.add_creature(0, c2);
  d.turn();
  ASSERT_TRUE(are_allies(c1, c2));
}

TEST(DarwinFixture, turn3) {
  Species s1('h');
  Species s2('i');
  Line l1(infect);
  Line l2(go, 0);
  Line l3(infect);
  Line l4(go, 0);
  s1.add_line(l1);
  s1.add_line(l2);
  s2.add_line(l3);
  s2.add_line(l4);
  Creature c1(s1, East);
  Creature c2(s2, North);
  Creature c3(s2, North);
  Creature c4(s2, North);
  Creature c5(s2, East);
  Darwin d(3, 3);
  d.add_creature(4, c1);
  d.add_creature(1, c2);
  d.add_creature(3, c3);
  d.add_creature(5, c4);
  d.add_creature(7, c5);
  //  d.print();
  d.turn();

  ASSERT_TRUE(are_allies(c1, c4));
}

TEST(DarwinFixture, turn4) {
  Species s1('h');
  Line l1(hop);
  Line l2(go, 0);
  s1.add_line(l1);
  s1.add_line(l2);
  Creature c1(s1, South);
  Darwin d(3, 3);
  d.add_creature(1, c1);
  d.turn();

  ASSERT_TRUE(d.board[4] == &c1);
}

TEST(DarwinFixture, turn5) {
  Species s1('h');
  Line l1(infect);
  Line l2(Left);
  Line l3(hop);
  Line l4(go, 0);
  s1.add_line(l1);
  s1.add_line(l2);
  s1.add_line(l3);
  s1.add_line(l4);
  Creature c1(s1, West);
  Creature c2(s1, West);
  Creature c3(s1, West);
  Creature c4(s1, West);
  Creature c5(s1, West);
  Darwin d(3, 3);
  d.add_creature(1, c1);
  d.add_creature(3, c2);
  d.add_creature(4, c3);
  d.add_creature(5, c4);
  d.add_creature(7, c5);
  d.turn();
  d.turn();
  d.turn();

  ASSERT_TRUE(d.board[6] == &c2);
  ASSERT_TRUE(d.board[8] == &c4);
}

TEST(DarwinFixture, turn6) {
  Species food('f');
  Line lf0(Left);
  Line lf1(go, 0);
  food.add_line(lf0);
  food.add_line(lf1);
  Creature c1(food, East);
  Darwin d(8, 8);
  d.add_creature(0, c1);
  d.turn();
}

TEST(DarwinFixture, print) {
  Species food('f');
  Line lf0(Left);
  Line lf1(go, 0);
  food.add_line(lf0);
  food.add_line(lf1);
  Creature c1(food, East);
  Darwin d(30, 30);
  d.add_creature(0, c1);
  d.turn();
  d.print();
}
