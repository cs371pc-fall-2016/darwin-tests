/** @file TestDarwin.c++
 *  @brief Darwin Tests.
 */

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include "Darwin.h"
#include "gtest/gtest.h"
#include <iostream>
#include <sstream>
#include <streambuf>

using namespace std;

// -------------
// Species Tests
// -------------

TEST(SpeciesFixture, addInstruction1) {
  Species s('a');
  s.addInstruction(HOP);
}

TEST(SpeciesFixture, addInstruction2) {
  Species s('a');
  s.addInstruction(GO, 0);
}

TEST(SpeciesFixture, addInstruction3) {
  Species s('a');
  s.addInstruction(HOP);
  s.addInstruction(GO, 0);
}

TEST(SpeciesFixture, think1) {
  Species s('a');
  s.addInstruction(IF_EMPTY, 3);
  s.addInstruction(LEFT);
  s.addInstruction(GO, 0);
  s.addInstruction(HOP);
  s.addInstruction(GO, 0);
  int c = 0;
  ASSERT_EQ(s.think(c, false, true, false), LEFT);
  ASSERT_EQ(c, 2);
  ASSERT_EQ(s.think(c, false, false, false), HOP);
  ASSERT_EQ(c, 4);
}

TEST(SpeciesFixture, think2) {
  Species s('a');
  s.addInstruction(IF_WALL, 3);
  s.addInstruction(HOP);
  s.addInstruction(GO, 0);
  s.addInstruction(LEFT);
  s.addInstruction(GO, 0);
  int c = 0;
  ASSERT_EQ(s.think(c, false, false, false), HOP);
  ASSERT_EQ(c, 2);
  ASSERT_EQ(s.think(c, true, false, false), LEFT);
  ASSERT_EQ(c, 4);
}

TEST(SpeciesFixture, think3) {
  Species s('a');
  s.addInstruction(IF_ENEMY, 3);
  s.addInstruction(LEFT);
  s.addInstruction(GO, 0);
  s.addInstruction(INFECT);
  s.addInstruction(GO, 0);
  int c = 0;
  ASSERT_EQ(s.think(c, false, false, false), LEFT);
  ASSERT_EQ(c, 2);
  ASSERT_EQ(s.think(c, false, false, true), INFECT);
  ASSERT_EQ(c, 4);
}

TEST(SpeciesFixture, think4) {
  Species s('a');
  s.addInstruction(IF_RANDOM, 3);
  s.addInstruction(RIGHT);
  s.addInstruction(GO, 0);
  s.addInstruction(GO, 1);
  int c = 0;

  srand(0);

  s.think(c, false, false, false);
  ASSERT_EQ(c, 2);
  s.think(c, false, false, false);
  ASSERT_EQ(c, 2);
}

TEST(SpeciesFixture, print1) {
  stringstream buffer;
  streambuf *cbuf = cout.rdbuf();
  cout.rdbuf(buffer.rdbuf());

  Species s('a');
  s.print();
  ASSERT_EQ('a', buffer.peek());

  cout.rdbuf(cbuf);
}

TEST(SpeciesFixture, print2) {
  stringstream buffer;
  streambuf *cbuf = cout.rdbuf();
  cout.rdbuf(buffer.rdbuf());

  Species a('a');
  Species b('b');
  Species c('c');

  a.print();
  ASSERT_EQ(buffer.get(), 'a');

  b.print();
  ASSERT_EQ(buffer.get(), 'b');

  c.print();
  ASSERT_EQ(buffer.get(), 'c');

  a.print();
  ASSERT_EQ(buffer.get(), 'a');

  b.print();
  ASSERT_EQ(buffer.get(), 'b');

  c.print();
  ASSERT_EQ(buffer.get(), 'c');

  cout.rdbuf(cbuf);
}

TEST(SpeciesFixture, print3) {
  stringstream buffer;
  streambuf *cbuf = cout.rdbuf();
  cout.rdbuf(buffer.rdbuf());

  Species a('a');
  Species b('b');
  Species c('c');

  a.print();
  b.print();
  c.print();
  a.print();
  b.print();
  c.print();
  a.print();
  b.print();
  c.print();

  ASSERT_EQ(buffer.str(), "abcabcabc");

  cout.rdbuf(cbuf);
}

// ---------------
// Creature Tests
// ---------------

// Think()

TEST(CreatureFixture, think_simple) {
  Species s('s');
  s.addInstruction(IF_WALL, 4);
  s.addInstruction(IF_ENEMY, 4);
  s.addInstruction(IF_EMPTY, 3);
  s.addInstruction(LEFT, -1);
  s.addInstruction(GO, 0);

  Darwin::Creature c(&s, 0);
  Instruction inst = c.think(false, false, false);

  ASSERT_EQ(inst, LEFT);
}

TEST(CreatureFixture, think_complex) {
  Species s('s');
  s.addInstruction(IF_WALL, 5);
  s.addInstruction(IF_ENEMY, 7);
  s.addInstruction(IF_EMPTY, 3);
  s.addInstruction(HOP, -1);
  s.addInstruction(GO, 0);
  s.addInstruction(LEFT, -1);
  s.addInstruction(GO, 0);
  s.addInstruction(INFECT, -1);
  s.addInstruction(GO, 0);

  Darwin::Creature c(&s, 0);

  ASSERT_EQ(c.think(false, false, false), HOP);
  ASSERT_EQ(c.think(true, false, false), LEFT);
  ASSERT_EQ(c.think(false, false, true), INFECT);
}

TEST(CreatureFixture, think_long) {
  Species s('s');
  s.addInstruction(LEFT, -1);
  s.addInstruction(RIGHT, -1);
  s.addInstruction(INFECT, -1);
  s.addInstruction(HOP, -1);
  s.addInstruction(LEFT, -1);
  s.addInstruction(GO, 0);

  Darwin::Creature c(&s, 0);

  ASSERT_EQ(c.think(true, false, false), LEFT);
  ASSERT_EQ(c.think(false, false, true), RIGHT);
  ASSERT_EQ(c.think(true, false, false), INFECT);
  ASSERT_EQ(c.think(false, false, true), HOP);
  ASSERT_EQ(c.think(true, false, false), LEFT);
  ASSERT_EQ(c.think(false, false, true), LEFT);
}

// Print() Tests

TEST(CreatureFixture, print_simple) {
  stringstream buffer;
  streambuf *cbuf = cout.rdbuf();
  cout.rdbuf(buffer.rdbuf());

  Species a('a');

  Darwin::Creature c(&a, 0);

  c.print();
  ASSERT_EQ('a', buffer.peek());

  cout.rdbuf(cbuf);
}

TEST(CreatureFixture, print_multiple) {
  stringstream buffer;
  streambuf *cbuf = cout.rdbuf();
  cout.rdbuf(buffer.rdbuf());

  Species a('a');
  Species b('b');
  Species c('c');

  Darwin::Creature ca(&a, 0);
  Darwin::Creature cb(&b, 0);
  Darwin::Creature cc(&c, 0);

  ca.print();
  ASSERT_EQ(buffer.get(), 'a');

  cb.print();
  ASSERT_EQ(buffer.get(), 'b');

  cc.print();
  ASSERT_EQ(buffer.get(), 'c');

  ca.print();
  ASSERT_EQ(buffer.get(), 'a');

  cb.print();
  ASSERT_EQ(buffer.get(), 'b');

  cc.print();
  ASSERT_EQ(buffer.get(), 'c');

  cout.rdbuf(cbuf);
}

TEST(CreatureFixture, print_long) {
  stringstream buffer;
  streambuf *cbuf = cout.rdbuf();
  cout.rdbuf(buffer.rdbuf());

  Species a('a');
  Species b('b');
  Species c('c');

  Darwin::Creature ca(&a, 0);
  Darwin::Creature cb(&b, 0);
  Darwin::Creature cc(&c, 0);

  ca.print();
  cb.print();
  cc.print();
  ca.print();
  cb.print();
  cc.print();
  ca.print();
  cb.print();
  cc.print();

  ASSERT_EQ(buffer.str(), "abcabcabc");

  cout.rdbuf(cbuf);
}

// --------------
// Darwin Tests
// --------------

// iterability

TEST(DarwinFixture, begin1) {
  Darwin d(1, 2);
  Species s('s');
  d.addCreature(&s, 0, 0, 0);
  ASSERT_EQ(d.begin()->first, 0);
}

TEST(DarwinFixture, begin2) {
  Darwin d(1, 2);
  Species s('s');
  d.addCreature(&s, 0, 0, 0);
  d.addCreature(&s, 0, 1, 0);
  map<int, Darwin::Creature *>::iterator b = d.begin();
  ASSERT_EQ(b->first, 0);
  ++b;
  ASSERT_EQ(b->first, 1);
}

TEST(DarwinFixture, begin3) {
  Darwin d(1, 2);
  Species s('s');
  d.addCreature(&s, 0, 0, 0);
  d.addCreature(&s, 0, 1, 0);
  map<int, Darwin::Creature *>::iterator b = d.begin();
  ASSERT_EQ(b->first, 0);
  ++b;
  ASSERT_EQ(b->first, 1);
  b = d.begin();
  ASSERT_EQ(b->first, 0);
}

TEST(DarwinFixture, end1) {
  Darwin d(1, 2);
  ASSERT_EQ(d.begin(), d.end());
}

TEST(DarwinFixture, end2) {
  Darwin d(1, 2);
  Species s('s');
  d.addCreature(&s, 0, 0, 0);
  d.addCreature(&s, 0, 1, 0);
  ASSERT_EQ(++++(d.begin()), d.end());
}

TEST(DarwinFixture, end3) {
  Darwin d(1, 2);
  Species s('s');
  d.addCreature(&s, 0, 0, 0);
  map<int, Darwin::Creature *>::iterator e = d.end();
  d.addCreature(&s, 0, 1, 0);
  ASSERT_EQ(e, d.end());
}

TEST(DarwinFixture, at1) {
  Darwin d(1, 2);
  Species s('s');
  d.addCreature(&s, 0, 0, 0);
  d.addCreature(&s, 0, 1, 0);
  ASSERT_EQ(d.at(0, 1)->species, &s);
}

TEST(DarwinFixture, at2) {
  Darwin d(1, 2);
  Species s('s');
  d.addCreature(&s, 0, 0, 0);
  ASSERT_FALSE(d.at(0, 1));
}

TEST(DarwinFixture, at3) {
  Darwin d(1, 2);
  Species s('s');
  d.addCreature(&s, 0, 0, 0);
  d.addCreature(&s, 0, 1, 0);
  ASSERT_EQ(d.at(0, 1)->species, &s);
  ASSERT_EQ(d.at(0, 0)->species, &s);
}

// AddCreature() Tests

TEST(DarwinFixture, addCreature_tight) {
  Darwin d(1, 1);

  Species s('s');
  d.addCreature(&s, 0, 0, 0);

  ASSERT_EQ(d._board.size(), 1);
}

TEST(DarwinFixture, addCreature_sparse) {
  Darwin d(50, 50);

  Species s('s');
  Species t('t');
  Species u('u');
  d.addCreature(&s, 0, 0, 0);
  d.addCreature(&s, 15, 5, 0);
  d.addCreature(&t, 30, 45, 0);
  d.addCreature(&t, 1, 40, 0);
  d.addCreature(&u, 12, 46, 0);
  d.addCreature(&u, 9, 25, 0);

  ASSERT_EQ(d._board.size(), 6);
}

TEST(DarwinFixture, addCreature_edges) {
  Darwin d(2, 2);

  Species s('s');
  d.addCreature(&s, 0, 0, 0);
  d.addCreature(&s, 0, 1, 0);
  d.addCreature(&s, 1, 0, 0);
  d.addCreature(&s, 1, 1, 0);
  ASSERT_EQ(d._board.size(), 4);
}

// Simulate() Tests

TEST(DarwinFixture, simulate_simple) {
  Species food('f');
  food.addInstruction(LEFT, -1);
  food.addInstruction(GO, 0);

  Species hopper('h');
  hopper.addInstruction(HOP, -1);
  hopper.addInstruction(GO, 0);

  Darwin D8x8(8, 8);
  D8x8.addCreature(&food, 0, 0, 1);
  D8x8.addCreature(&hopper, 3, 3, 0);
  D8x8.addCreature(&hopper, 3, 4, 1);
  D8x8.addCreature(&hopper, 4, 4, 2);
  D8x8.addCreature(&hopper, 4, 3, 3);
  D8x8.addCreature(&food, 7, 7, 0);

  for (int i = 0; i < 10; ++i)
    D8x8.simulate();
}

TEST(DarwinFixture, simulate_tight) {
  Species food('f');
  food.addInstruction(LEFT, -1);
  food.addInstruction(GO, 0);

  Species hopper('h');
  hopper.addInstruction(HOP, -1);
  hopper.addInstruction(GO, 0);

  Darwin D8x8(2, 2);
  D8x8.addCreature(&food, 0, 0, 1);
  D8x8.addCreature(&hopper, 1, 1, 0);
  D8x8.addCreature(&food, 1, 0, 0);

  for (int i = 0; i < 25; ++i)
    D8x8.simulate();
}

TEST(DarwinFixture, simulate_large) {
  Species food('f');
  food.addInstruction(LEFT, -1);
  food.addInstruction(GO, 0);

  Species hopper('h');
  hopper.addInstruction(HOP, -1);
  hopper.addInstruction(GO, 0);

  Species rover('r');
  rover.addInstruction(IF_ENEMY, 9);
  rover.addInstruction(IF_EMPTY, 7);
  rover.addInstruction(IF_RANDOM, 5);
  rover.addInstruction(LEFT, -1);
  rover.addInstruction(GO, 0);
  rover.addInstruction(RIGHT, -1);
  rover.addInstruction(GO, 0);
  rover.addInstruction(HOP, -1);
  rover.addInstruction(GO, 0);
  rover.addInstruction(INFECT, -1);
  rover.addInstruction(GO, 0);

  Species trap('t');
  trap.addInstruction(IF_ENEMY, 3);
  trap.addInstruction(LEFT, -1);
  trap.addInstruction(GO, 0);
  trap.addInstruction(INFECT, -1);
  trap.addInstruction(GO, 0);

  Darwin D8x8(50, 40);
  D8x8.addCreature(&food, 0, 0, 1);
  D8x8.addCreature(&food, 13, 26, 0);
  D8x8.addCreature(&food);
  D8x8.addCreature(&hopper, 10, 3, 2);
  D8x8.addCreature(&hopper, 32, 22, 1);
  D8x8.addCreature(&hopper);
  D8x8.addCreature(&rover, 1, 1, 2);
  D8x8.addCreature(&rover, 17, 44, 3);
  D8x8.addCreature(&rover);
  D8x8.addCreature(&trap, 5, 7, 3);
  D8x8.addCreature(&trap, 18, 32, 1);
  D8x8.addCreature(&trap);

  srand(0);

  for (int i = 0; i < 300; ++i)
    D8x8.simulate();
  ASSERT_EQ(D8x8._board.size(), 12);
}

TEST(DarwinFixture, simulate_complex) {
  Species food('f');
  food.addInstruction(LEFT, -1);
  food.addInstruction(GO, 0);

  Species hopper('h');
  hopper.addInstruction(HOP, -1);
  hopper.addInstruction(GO, 0);

  Species rover('r');
  rover.addInstruction(IF_ENEMY, 9);
  rover.addInstruction(IF_EMPTY, 7);
  rover.addInstruction(IF_RANDOM, 5);
  rover.addInstruction(LEFT, -1);
  rover.addInstruction(GO, 0);
  rover.addInstruction(RIGHT, -1);
  rover.addInstruction(GO, 0);
  rover.addInstruction(HOP, -1);
  rover.addInstruction(GO, 0);
  rover.addInstruction(INFECT, -1);
  rover.addInstruction(GO, 0);

  Species trap('t');
  trap.addInstruction(IF_ENEMY, 3);
  trap.addInstruction(LEFT, -1);
  trap.addInstruction(GO, 0);
  trap.addInstruction(INFECT, -1);
  trap.addInstruction(GO, 0);

  Species terminator('O');
  terminator.addInstruction(IF_WALL, 4);
  terminator.addInstruction(IF_ENEMY, 6);
  terminator.addInstruction(HOP, -1);
  terminator.addInstruction(GO, 0);
  terminator.addInstruction(LEFT, -1);
  terminator.addInstruction(GO, 0);
  terminator.addInstruction(INFECT, -1);
  terminator.addInstruction(GO, 0);

  srand(0);

  Darwin d(100, 200);
  // four fors for creatures
  for (int i = 0; i < 10; ++i)
    d.addCreature(&food);

  for (int i = 0; i < 10; ++i)
    d.addCreature(&hopper);

  for (int i = 0; i < 10; ++i)
    d.addCreature(&rover);

  for (int i = 0; i < 10; ++i)
    d.addCreature(&trap);

  for (int i = 0; i < 10; ++i)
    d.addCreature(&terminator);

  for (int i = 0; i < 100; ++i)
    d.simulate();
}

// Print() Tests

TEST(DarwinFixture, print) {
  stringstream buffer;
  streambuf *cbuf = cout.rdbuf();
  cout.rdbuf(buffer.rdbuf());

  Darwin d(1, 1);
  Species s('s');
  d.addCreature(&s, 0, 0, 0);
  d.print();

  ASSERT_EQ(buffer.str(), "Turn = 0.\n  0\n0 s\n\n");

  cout.rdbuf(cbuf);
}

// size() Tests

TEST(DarwinFixture, size_small) {
  Darwin d(1, 1);
  ASSERT_EQ(d.size(), 1);
}

TEST(DarwinFixture, size_disporportionate) {
  Darwin d(30, 1);
  ASSERT_EQ(d.size(), 30);
}

TEST(DarwinFixture, size_large) {
  Darwin d(50, 50);
  ASSERT_EQ(d.size(), 2500);
}
