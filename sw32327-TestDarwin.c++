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
#include "Darwin.h"
#include <vector>

using namespace std;

// -------------------
// Darwin::addCreature
// -------------------

/** test basic add creatre functionality on 1x1 grid */
TEST(DarwinFixture, darwin_add_creature_1) {
  ostringstream s;
  Darwin d(1, 1);
  Species a("A");
  Creature c(a);
  d.addCreature(c, 0, 0);
  d.draw(s);
  ASSERT_EQ(s.str(), "  0\n0 A\n");
}

/** fill entire 3x3 grid with creatures */
TEST(DarwinFixture, darwin_add_creature_2) {
  ostringstream s;
  Darwin d(3, 3);
  Species a("A");
  vector<Creature> creatures(9, Creature(a));
  for (int i = 0; i < 9; i++)
    d.addCreature(creatures[i], i % 3, i / 3);
  d.draw(s);
  ASSERT_EQ(s.str(), "  012\n0 AAA\n1 AAA\n2 AAA\n");
}

/** adding a creature on top of another one removes the old */
TEST(DarwinFixture, darwin_add_creature_3) {
  ostringstream s;
  Darwin d(3, 3);
  Species a("A");
  Species b("B");
  vector<Creature> creatures(9, Creature(a));
  for (int i = 0; i < 9; i++)
    d.addCreature(creatures[i], i % 3, i / 3);
  Creature cb(b);
  d.addCreature(cb, 1, 1);
  d.draw(s);
  ASSERT_EQ(s.str(), "  012\n0 AAA\n1 ABA\n2 AAA\n");
}

// -----------------------
// Species::addInstruction
// -----------------------

/** size of instruction list should increase with instruction add */
TEST(DarwinFixture, species_add_instruction_1) {
  Species a("A");
  a.addInstruction("a");
  a.addInstruction("b");
  a.addInstruction("c");
  string comp[] = {"a", "b", "c"};
  ASSERT_TRUE(equal(begin(a.instructions), end(a.instructions), comp));
}

/** instructions should be added to the end of the list in order */
TEST(DarwinFixture, species_add_instruction_2) {
  Species a("A");
  a.addInstruction("a");
  a.addInstruction("b");
  int before = a.instructions.size();
  a.addInstruction("c");
  int after = a.instructions.size();
  ASSERT_EQ(before, after - 1);
}

// ------------
// Darwin::draw
// ------------

/** draw an empty 3x3 board */
TEST(DarwinFixture, darwin_draw_1) {
  ostringstream s;
  Darwin d(3, 3);
  d.draw(s);
  ASSERT_EQ(s.str(), "  012\n0 ...\n1 ...\n2 ...\n");
}

/** draw an empty 3x3 board with a hopper in the middle */
TEST(DarwinFixture, darwin_draw_2) {
  ostringstream s;
  Darwin d(3, 3);
  Species hopper("hopper");
  Creature c(hopper);
  d.addCreature(c, 1, 1);
  d.draw(s);
  ASSERT_EQ(s.str(), "  012\n0 ...\n1 .h.\n2 ...\n");
}

/** draw a board with width greater than 10 */
TEST(DarwinFixture, darwin_draw_3) {
  ostringstream s;
  Darwin d(1, 12);
  d.draw(s);
  // column number is modulated by 10
  ASSERT_EQ(s.str(), "  012345678901\n0 ............\n");
}

/** draw a board with length greater than 10 */
TEST(DarwinFixture, darwin_draw_4) {
  ostringstream s;
  Darwin d(12, 1);
  d.draw(s);
  // row number is modulated by 10
  ASSERT_EQ(
      s.str(),
      "  0\n0 .\n1 .\n2 .\n3 .\n4 .\n5 .\n6 .\n7 .\n8 .\n9 .\n0 .\n1 .\n");
}

// --------------
// Creature::draw
// --------------

/** Creature should print the first letter of its Species */
TEST(DarwinFixture, creature_draw_1) {
  ostringstream s;
  Species test("test");
  Creature c(test);
  c.draw(s);
  ASSERT_EQ(s.str(), "t");
}

// --------------
// Species::draw
// --------------

/** Species should print the first letter of its name */
TEST(DarwinFixture, species_draw_1) {
  ostringstream s;
  Species test("test");
  test.draw(s);
  ASSERT_EQ(s.str(), "t");
}

// ------------
// Darwin::move
// ------------

/** test hopping a creature in its direction */
TEST(DarwinFixture, darwin_move_1) {
  ostringstream s;
  Species test("test");
  test.addInstruction("hop");
  test.addInstruction("go 0");
  Darwin x(2, 1);
  Creature c(test, 3);
  x.addCreature(c, 0, 0);
  x.move();
  x.draw(s);
  ASSERT_EQ(s.str(), "  0\n0 .\n1 t\n");
}

/** creatures should be moved from upper left to bottom right */
TEST(DarwinFixture, darwin_move_2) {
  ostringstream s;
  Species a("A");
  a.addInstruction("hop");
  a.addInstruction("go 0");
  Species b("B");
  b.addInstruction("hop");
  b.addInstruction("go 0");
  Darwin x(2, 2);
  Creature c(a, 2);
  Creature c2(b, 1);
  x.addCreature(c, 0, 0);
  x.addCreature(c2, 1, 1);
  x.move();
  x.draw(s);

  // c should block c2's attempt to move up to (0,1)
  ASSERT_EQ(s.str(), "  01\n0 .A\n1 .B\n");
}

/** a creature who has already moved out of the way should not be infected */
TEST(DarwinFixture, darwin_move_3) {
  ostringstream s;
  Species a("A");
  a.addInstruction("hop");
  a.addInstruction("go 0");
  Species b("B");
  b.addInstruction("infect");
  b.addInstruction("go 0");
  Darwin x(2, 2);
  Creature c(a, 2);
  Creature c2(b, 1);
  x.addCreature(c, 0, 0);
  x.addCreature(c2, 1, 0);
  x.move();
  x.draw(s);

  // c should escape c2's attempt to infect it
  ASSERT_EQ(s.str(), "  01\n0 .A\n1 B.\n");
}

/** a creature who has just moved into the way should be infected */
TEST(DarwinFixture, darwin_move_4) {
  ostringstream s;
  Species a("A");
  a.addInstruction("hop");
  a.addInstruction("go 0");
  Species b("B");
  b.addInstruction("infect");
  b.addInstruction("go 0");
  Darwin x(2, 2);
  Creature c(a, 2);
  Creature c2(b, 1);
  x.addCreature(c, 0, 0);
  x.addCreature(c2, 1, 1);
  x.move();
  x.draw(s);

  // c should escape c2's attempt to infect it
  ASSERT_EQ(s.str(), "  01\n0 .B\n1 .B\n");
}

// --------------
// Creature::move
// --------------

/** a creature surrounded by walls should not return a motion */
TEST(DarwinFixture, creature_move_1) {
  Species test("test");
  test.addInstruction("hop");
  test.addInstruction("go 0");
  Creature c(test, 0);
  // a pointer to itself represents a wall
  Creature *neighbors[] = {&c, &c, &c, &c};
  // a return value of -1 indicates no motion
  ASSERT_EQ(c.move(neighbors), -1);
}

/** a creature who has been infected should set its pc to 0 */
TEST(DarwinFixture, creature_move_2) {
  Species a("A");
  Species b("B");
  b.addInstruction("infect");
  b.addInstruction("go 0");
  Creature c(b, 0);
  Creature c2(a, 0);
  // neighbor above c is c2
  Creature *neighbors[] = {&c2, &c, &c, &c};
  c.move(neighbors);
  ASSERT_EQ(c2.pc, 0);
}

/** a creature who is infected should not change direction */
TEST(DarwinFixture, creature_move_3) {
  Species a("A");
  Species b("B");
  b.addInstruction("hop");
  b.addInstruction("infect");
  b.addInstruction("go 0");
  Creature c(b, 0);
  Creature c2(a, 3);
  // move c to infect instruction
  Creature *no_neighbors[] = {nullptr, nullptr, nullptr, nullptr};
  c.move(no_neighbors);
  // infect c2
  Creature *c2_above[] = {&c2, nullptr, nullptr, nullptr};
  c.move(c2_above);
  // move with c2 should be in direction 3
  ASSERT_EQ(c2.move(no_neighbors), 3);
}

/** a left instruction should rotation Creatures dir field */
TEST(DarwinFixture, creature_move_4) {
  Species a("A");
  a.addInstruction("right");
  a.addInstruction("go 0");
  Creature c(a, 3);
  Creature *no_neighbors[] = {nullptr, nullptr, nullptr, nullptr};
  c.move(no_neighbors);
  Species b("B");
  b.addInstruction("left");
  b.addInstruction("go 0");
  Creature c2(b, 1);
  c2.move(no_neighbors);
  // c and c2 should both be in the 0 direction
  ASSERT_EQ(c.dir, c2.dir);
}

// -------------
// Species::move
// -------------

/** species move should return first action instruction */
TEST(DarwinFixture, species_move_1) {
  Species a("A");
  a.addInstruction("go 1");
  a.addInstruction("go 2");
  a.addInstruction("left");
  bool status[] = {false, false, false, false};
  // first action is left
  ASSERT_EQ(a.move(status, 0).first, "left");
}

/** species move should evaluate randoms by if rand() returns an odd number */
TEST(DarwinFixture, species_move_2) {
  Species a("A");
  a.addInstruction("if_rand 2");
  a.addInstruction("right");
  a.addInstruction("left");
  bool status[] = {false, false, false, false};
  // reset rand, first value off rand should be even
  srand(0);
  // first action is right
  ASSERT_EQ(a.move(status, 0).first, "right");
}

/** species move should evaluate conditionals based on the status arguement */
TEST(DarwinFixture, species_move_3) {
  Species a("A");
  // a only goes left if all conditions are true
  a.addInstruction("if_empty 4");
  a.addInstruction("if_wall 4");
  a.addInstruction("if_enemy 4");
  a.addInstruction("left");
  a.addInstruction("if_wall 6");
  a.addInstruction("go 3");
  a.addInstruction("if_enemy 8");
  a.addInstruction("go 3");
  a.addInstruction("right");
  bool all_false[] = {false, false, false};
  bool all_true[] = {true, true, true};
  ASSERT_TRUE((a.move(all_true, 0).first == "right") &&
              (a.move(all_false, 0).first == "left"));
}

/** species move starts evaluating at the given pc */
TEST(DarwinFixture, species_move_4) {
  Species a("A");
  // a only goes left if all conditions are true
  a.addInstruction("left");
  a.addInstruction("left");
  a.addInstruction("left");
  a.addInstruction("right");
  a.addInstruction("left");
  a.addInstruction("left");

  bool status[] = {false, false, false, false};
  ASSERT_EQ(a.move(status, 3).first, "right");
}

/** species move returns pc of next instruction */
TEST(DarwinFixture, species_move_5) {
  Species a("A");
  // next instruction after execution should be 3
  a.addInstruction("go 2");
  a.addInstruction("left");
  a.addInstruction("left");
  a.addInstruction("left");
  a.addInstruction("left");
  a.addInstruction("left");

  bool status[] = {false, false, false, false};
  ASSERT_EQ(a.move(status, 0).second, 3);
}
