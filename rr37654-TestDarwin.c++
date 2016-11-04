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

// ------------------------
// DarwinConstructor2Params
// ------------------------

TEST(DarwinConstructor2Params, test1) {
  // just validate everything works correctly

  Darwin d(8, 8);

  assert(d.rows == 8);
  assert(d.columns == 8);
  assert(d.turns == 0);
}

TEST(DarwinConstructor2Params, test2) {
  // just validate everything works correctly

  Darwin d(4, 7);

  assert(d.rows == 4);
  assert(d.columns == 7);
  assert(d.turns == 0);
}

// ------------------------
// DarwinConstructor0Params
// ------------------------

TEST(DarwinConstructor0Params, test1) {
  // default usage is 10, but really the zero params case should never be used

  Darwin d;

  assert(d.rows == 10);
  assert(d.columns == 10);
  assert(d.turns == 0);
}

// ------------------
// SpeciesConstructor
// ------------------

TEST(SpeciesConstructor, test1) {
  // check char is set and internal vector is initialized

  Species s('s');

  assert(s.data == 's');
  assert(s.instructions.size() == 0);
}

TEST(SpeciesConstructor, test2) {
  // check basic constructor is working by checking default copy constructor

  Species e('e');

  assert(e.data == 'e');
  assert(e.instructions.size() == 0);

  Species s = e;

  assert(s.data == 'e');
  assert(s.instructions.size() == 0);
}

// ---------------------------
// SpeciesAddActionInstruction
// ---------------------------

TEST(SpeciesAddActionInstruction, test1) {
  // check codes in internal vector are correct

  Species s('s');

  s.add_action_instruction(LEFT);
  s.add_action_instruction(RIGHT);
  s.add_control_instruction(
      GO, 0); // for sake of validity of species control program

  assert(s.instructions[0] == LEFT);
  assert(s.instructions[1] == RIGHT);
}

TEST(SpeciesAddActionInstruction, test2) {
  // check internal codes again for different ops

  Species s('s');

  s.add_control_instruction(IF_EMPTY, 2);
  s.add_control_instruction(GO, 0);
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  assert(s.instructions[2] == HOP);
}

// ----------------------------
// SpeciesAddControlInstruction
// ----------------------------

TEST(SpeciesAddControlInstruction, test1) {
  // check that control instruction encoding scheme works for simplest case

  Species s('s');

  s.add_action_instruction(INFECT);
  s.add_control_instruction(GO, 0);

  assert(s.instructions[1] == GO);
}

TEST(SpeciesAddControlInstruction, test2) {
  // check control encoding works for a non-zero jump location

  Species s('s');

  s.add_action_instruction(HOP);
  s.add_action_instruction(INFECT);
  s.add_control_instruction(GO, 1);

  assert(s.instructions[2] == GO + 10);
}

TEST(SpeciesAddControlInstruction, test3) {
  // check all control types

  Species s('s');

  s.add_control_instruction(IF_EMPTY, 8);
  s.add_control_instruction(IF_WALL, 6);
  s.add_control_instruction(IF_RANDOM, 4);
  s.add_action_instruction(RIGHT);
  s.add_action_instruction(LEFT);
  s.add_control_instruction(GO, 0);
  s.add_action_instruction(INFECT);
  s.add_control_instruction(GO, 0);
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  assert(s.instructions[0] == IF_EMPTY + 80);
  assert(s.instructions[1] == IF_WALL + 60);
  assert(s.instructions[2] == IF_RANDOM + 40);
  assert(s.instructions[5] == GO);
  assert(s.instructions[7] == GO);
  assert(s.instructions[9] == GO);
}

// --------------------------
// CreatureConstructor0Params
// --------------------------

TEST(CreatureConstructor0Params, test1) {
  // check default initializes all values as expected

  Creature c;

  assert(c.counter == 0);
  assert(c.direction == 0);
  assert(c.species == NULL);
}

// --------------------------
// CreatureConstructor2Params
// --------------------------

TEST(CreatureConstructor2Params, test1) {
  // check 2 param constructor with simple species

  Species s('s');

  Creature c(&s, WEST);

  assert(c.counter == 0);
  assert(c.direction == WEST);
  assert(c.species == &s);
}

TEST(CreatureConstructor2Params, test2) {
  // check 2 param constructor with more complicated species

  Species s('s');
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  Creature c(&s, EAST);

  assert(c.counter == 0);
  assert(c.direction == EAST);
  assert(c.species->instructions.size() == 2);
}

// ----------
// SpeciesOut
// ----------

TEST(SpeciesOut, test1) {
  // trivial out for species

  ostringstream o;

  Species s('s');
  o << s;

  assert(o.str() == "s");
}

TEST(SpeciesOut, test2) {
  // another trival out for species

  ostringstream o;

  Species s('e');
  o << s;

  assert(o.str() == "e");
}

// -----------
// CreatureOut
// -----------

TEST(CreatureOut, test1) {
  // verify that creature's out also works functionally same as species

  ostringstream o;

  Species s('s');

  Creature c(&s, WEST);
  o << c;

  assert(o.str() == "s");
}

TEST(CreatureOut, test2) {
  // second test case for creature out

  ostringstream o;

  Species s('e');

  Creature c(&s, WEST);
  o << c;

  assert(o.str() == "e");
}

TEST(CreatureOut, test3) {
  // check that species change changes output

  ostringstream o1, o2, o3;

  Species s('s');
  Species t('t');

  Creature c(&s, WEST);
  Creature d(&t, EAST);
  o1 << c;
  o2 << d;

  assert(o1.str() == "s");
  assert(o2.str() == "t");

  c.species = &t;
  o3 << c;

  assert(o3.str() == "t");
}

// -----------------
// DarwinAddCreature
// -----------------

TEST(DarwinAddCreature, test1) {
  // add creatures and check in correct place on internal grid

  Species a('a');
  Species b('b');

  Creature c1(&a, WEST);
  Creature c2(&b, EAST);

  Darwin d(8, 8);

  d.add_creature(&c1, 5, 7);
  d.add_creature(&c2, 4, 1);

  assert(d.grid[47] == &c1);
  assert(d.grid[33] == &c2);
}

TEST(DarwinAddCreature, test2) {
  // fill a grid and verify works correctly

  Species a('a');
  Species b('b');

  Creature c1(&a, WEST);
  Creature c2(&b, EAST);
  Creature c3(&a, WEST);
  Creature c4(&b, EAST);

  Darwin d(2, 2);

  d.add_creature(&c1, 0, 0);
  d.add_creature(&c2, 1, 1);
  d.add_creature(&c3, 1, 0);
  d.add_creature(&c4, 0, 1);

  assert(d.grid[0] == &c1);
  assert(d.grid[1] == &c4);
  assert(d.grid[2] == &c3);
  assert(d.grid[3] == &c2);
}

TEST(DarwinAddCreature, test3) {
  // check if single cell grid works correctly

  Species a('a');

  Creature c1(&a, NORTH);

  Darwin d(1, 1);

  d.add_creature(&c1, 0, 0);

  assert(d.grid[0] == &c1);
}

TEST(DarwinAddCreature, test4) {
  // non-square grid

  Species a('a');

  Creature c1(&a, NORTH);
  Creature c2(&a, SOUTH);
  Creature c3(&a, NORTH);
  Creature c4(&a, SOUTH);

  Darwin d(7, 12);

  d.add_creature(&c1, 4, 5);
  d.add_creature(&c2, 3, 11);
  d.add_creature(&c3, 6, 11);
  d.add_creature(&c4, 6, 10);

  assert(d.grid[53] == &c1);
  assert(d.grid[47] == &c2);
  assert(d.grid[83] == &c3);
  assert(d.grid[82] == &c4);
}

TEST(DarwinAddCreature, test5) {
  // bigger non-square grid, more cases

  Species a('a');

  Creature c1(&a, WEST);
  Creature c2(&a, EAST);
  Creature c3(&a, WEST);
  Creature c4(&a, EAST);
  Creature c5(&a, WEST);
  Creature c6(&a, EAST);
  Creature c7(&a, WEST);
  Creature c8(&a, EAST);

  Darwin d(21, 14);

  d.add_creature(&c1, 20, 13);
  d.add_creature(&c2, 1, 1);
  d.add_creature(&c3, 14, 4);
  d.add_creature(&c4, 1, 11);
  d.add_creature(&c5, 5, 11);
  d.add_creature(&c6, 20, 0);
  d.add_creature(&c7, 8, 8);
  d.add_creature(&c8, 6, 12);

  assert(d.grid[293] == &c1);
  assert(d.grid[15] == &c2);
  assert(d.grid[200] == &c3);
  assert(d.grid[25] == &c4);
  assert(d.grid[81] == &c5);
  assert(d.grid[280] == &c6);
  assert(d.grid[120] == &c7);
  assert(d.grid[96] == &c8);
}

// ---------
// DarwinOut
// ---------

TEST(DarwinOut, test1) {
  // check initial frame with nothing for a 2x2

  Species a('a');
  Species b('b');
  Species c('c');
  Species d('d');

  ostringstream o;

  Darwin darwin(2, 2);

  o << darwin;

  assert(o.str() == "Turn = 0.\n  01\n0 ..\n1 ..\n\n");
}

TEST(DarwinOut, test2) {
  // inital frame, 2x2 filled

  Species a('a');
  Species b('b');
  Species c('c');
  Species d('d');

  Creature c1(&a, WEST);
  Creature c2(&b, EAST);
  Creature c3(&c, WEST);
  Creature c4(&d, EAST);

  ostringstream o;

  Darwin darwin(2, 2);

  darwin.add_creature(&c1, 0, 0);
  darwin.add_creature(&c2, 1, 1);
  darwin.add_creature(&c3, 1, 0);
  darwin.add_creature(&c4, 0, 1);

  o << darwin;

  assert(o.str() == "Turn = 0.\n  01\n0 ad\n1 cb\n\n");
}

TEST(DarwinOut, test3) {
  // initial frame, more sparse grid, place each creature on end of row

  Species a('a');
  Species b('b');
  Species c('c');
  Species d('d');

  Creature c1(&a, WEST);
  Creature c2(&b, EAST);
  Creature c3(&c, WEST);
  Creature c4(&d, EAST);

  ostringstream o;

  Darwin darwin(4, 4);

  darwin.add_creature(&c1, 0, 3);
  darwin.add_creature(&c2, 1, 3);
  darwin.add_creature(&c3, 2, 3);
  darwin.add_creature(&c4, 3, 3);

  o << darwin;

  assert(o.str() == "Turn = 0.\n  0123\n0 ...a\n1 ...b\n2 ...c\n3 ...d\n\n");
}

TEST(DarwinOut, test4) {
  // place each creature at beginning of row

  Species a('a');
  Species b('b');
  Species c('c');
  Species d('d');

  Creature c1(&a, WEST);
  Creature c2(&b, EAST);
  Creature c3(&c, WEST);
  Creature c4(&d, EAST);

  ostringstream o;

  Darwin darwin(4, 4);

  darwin.add_creature(&c1, 0, 0);
  darwin.add_creature(&c2, 1, 0);
  darwin.add_creature(&c3, 2, 0);
  darwin.add_creature(&c4, 3, 0);

  o << darwin;

  assert(o.str() == "Turn = 0.\n  0123\n0 a...\n1 b...\n2 c...\n3 d...\n\n");
}

TEST(DarwinOut, test5) {
  // place 2 creatures adjacently in terms of sequence (one at end of row and
  // next at beginning of next row)

  Species a('a');
  Species b('b');
  Species c('c');
  Species d('d');

  Creature c1(&a, WEST);
  Creature c2(&b, EAST);
  Creature c3(&c, WEST);
  Creature c4(&d, EAST);

  ostringstream o;

  Darwin darwin(4, 4);

  darwin.add_creature(&c1, 0, 3);
  darwin.add_creature(&c2, 1, 0);
  darwin.add_creature(&c3, 2, 3);
  darwin.add_creature(&c4, 3, 0);

  o << darwin;

  assert(o.str() == "Turn = 0.\n  0123\n0 ...a\n1 b...\n2 ...c\n3 d...\n\n");
}

TEST(DarwinOut, test6) {
  // simulate a turn and then check output

  Species a('a');
  Species b('b');
  Species c('c');
  Species d('d');

  a.add_action_instruction(HOP);
  a.add_control_instruction(GO, 0);
  b.add_action_instruction(HOP);
  b.add_control_instruction(GO, 0);
  c.add_action_instruction(HOP);
  c.add_control_instruction(GO, 0);
  d.add_action_instruction(HOP);
  d.add_control_instruction(GO, 0);

  Creature c1(&a, WEST);
  Creature c2(&b, EAST);
  Creature c3(&c, WEST);
  Creature c4(&d, EAST);

  ostringstream o;

  Darwin darwin(4, 4);

  darwin.add_creature(&c1, 0, 3);
  darwin.add_creature(&c2, 1, 0);
  darwin.add_creature(&c3, 2, 3);
  darwin.add_creature(&c4, 3, 0);

  darwin.simulate(1, NULL);

  o << darwin;

  assert(o.str() == "Turn = 1.\n  0123\n0 ..a.\n1 .b..\n2 ..c.\n3 .d..\n\n");
}

// --------------
// DarwinFillUpto
// --------------

TEST(DarwinFillUpto, test1) {
  // check trivial single cell

  ostringstream o;

  Darwin d(1, 1);

  int count = 0;

  d.fill_upto(count, 1, o);

  assert(count == 1);
  assert(o.str() == "\n0 .\n");
}

TEST(DarwinFillUpto, test2) {
  // check only newline if starting at end of grid

  ostringstream o;

  Darwin d(1, 1);

  int count = 1;

  d.fill_upto(count, 1, o);

  assert(count == 1);
  assert(o.str() == "\n");
}

TEST(DarwinFillUpto, test3) {
  // fill a 3x3

  ostringstream o;

  Darwin d(3, 3);

  int count = 0;

  d.fill_upto(count, 9, o);

  assert(count == 9);
  assert(o.str() == "\n0 ...\n1 ...\n2 ...\n");
}

TEST(DarwinFillUpto, test4) {
  // fill only 1 row

  ostringstream o;

  Darwin d(3, 3);

  int count = 0;

  d.fill_upto(count, 3, o);

  assert(count == 3);
  assert(o.str() == "\n0 ...\n1 ");
}

TEST(DarwinFillUpto, test5) {
  // fill half a row

  ostringstream o;

  Darwin d(3, 3);

  int count = 0;

  d.fill_upto(count, 2, o);

  assert(count == 2);
  assert(o.str() == "\n0 ..");
}

TEST(DarwinFillUpto, test6) {
  // fill half the grid

  ostringstream o;

  Darwin d(3, 3);

  int count = 1;

  d.fill_upto(count, 5, o);

  assert(count == 5);
  assert(o.str() == "..\n1 ..");
}

TEST(DarwinFillUpto, test7) {
  // fill 1 row in the middle

  ostringstream o;

  Darwin d(3, 3);

  int count = 3;

  d.fill_upto(count, 6, o);

  assert(count == 6);
  assert(o.str() == "\n1 ...\n2 ");
}

TEST(DarwinFillUpto, test8) {
  // fill last row

  ostringstream o;

  Darwin d(3, 3);

  int count = 6;

  d.fill_upto(count, 9, o);

  assert(count == 9);
  assert(o.str() == "\n2 ...\n");
}

// -----------------
// SpeciesFindAction
// -----------------

TEST(SpeciesFindAction, test1) {
  // check basic case finds the right instructions

  Species a('a');
  a.add_control_instruction(IF_EMPTY, 3);
  a.add_action_instruction(INFECT);
  a.add_control_instruction(GO, 0);
  a.add_action_instruction(HOP);
  a.add_control_instruction(GO, 0);

  Species b('b');

  Creature c1(&a, EAST);
  Creature c2(&b, WEST);

  int index = 0;
  int index2 = 0;

  int next = a.find_action(index, false, false, true);
  int next2 = a.find_action(index2, false, true, false);

  assert(index == 2);
  assert(index2 == 4);

  assert(next == INFECT);
  assert(next2 == HOP);
}

TEST(SpeciesFindAction, test2) {
  // check if wall and if enemy

  Species a('a');
  a.add_control_instruction(IF_WALL, 3);
  a.add_action_instruction(HOP);
  a.add_control_instruction(GO, 0);
  a.add_action_instruction(LEFT);
  a.add_control_instruction(GO, 0);

  Species b('b');
  b.add_control_instruction(IF_ENEMY, 3);
  b.add_action_instruction(RIGHT);
  b.add_control_instruction(GO, 0);
  b.add_action_instruction(INFECT);
  b.add_control_instruction(GO, 0);

  Creature c1(&a, EAST);
  Creature c2(&b, WEST);

  int index = 0;
  int index2 = 0;
  int index3 = 0;

  int next = a.find_action(index, true, false, false);
  int next3 = a.find_action(index3, false, false, true);
  int next2 = b.find_action(index2, false, false, true);

  assert(index == 4);
  assert(index2 == 4);
  assert(index3 == 2);

  assert(next == LEFT);
  assert(next2 == INFECT);
  assert(next3 == HOP);
}

TEST(SpeciesFindAction, test3) {
  // check random seed working

  srand(0);
  // 1 access is 1 pattern

  Species s('s');
  s.add_control_instruction(IF_RANDOM, 3);
  s.add_action_instruction(RIGHT);
  s.add_control_instruction(GO, 0);
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  Creature a(&s, NORTH);

  int index = 0;
  int next = s.find_action(index, false, false, false);

  assert(next == HOP);
}

TEST(SpeciesFindAction, test4) {
  // more strenuous random test

  srand(0);
  // 4 accesses is 1011 pattern

  Species s('s');
  s.add_control_instruction(IF_RANDOM, 3);
  s.add_action_instruction(LEFT);
  s.add_control_instruction(GO, 0);
  s.add_action_instruction(RIGHT);
  s.add_control_instruction(GO, 0);

  Creature a(&s, WEST);
  Creature b(&s, SOUTH);
  Creature c(&s, EAST);
  Creature d(&s, NORTH);

  int index = 0;
  int next = s.find_action(index, false, false, false);
  int index2 = 0;
  int next2 = s.find_action(index2, false, false, false);
  int index3 = 0;
  int next3 = s.find_action(index3, false, false, false);
  int index4 = 0;
  int next4 = s.find_action(index4, false, false, false);

  assert(next == RIGHT);
  assert(next2 == LEFT);
  assert(next3 == RIGHT);
  assert(next4 == RIGHT);
}

TEST(CreatureUpdateSelf, test1) {
  // tests move in a direction against boundaries should not change the position

  Species s('s');
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  Creature c1(&s, NORTH);
  Creature c2(&s, EAST);
  Creature c3(&s, WEST);
  Creature c4(&s, SOUTH);

  int x = 0;
  int y = 0;

  Creature *all_nulls[4] = {NULL, NULL, NULL, NULL};

  bool array1[4] = {true, true, false, false};
  bool array2[4] = {false, true, true, false};
  bool array3[4] = {true, false, false, true};
  bool array4[4] = {false, false, true, true};

  c1.update_self(x, y, all_nulls, array1);
  assert(x == 0);
  assert(y == 0);

  x = 0;
  y = 9;

  c2.update_self(x, y, all_nulls, array2);
  assert(x == 0);
  assert(y == 9);

  x = 9;
  y = 0;

  c3.update_self(x, y, all_nulls, array3);
  assert(x == 9);
  assert(y == 0);

  x = 9;
  y = 9;

  c4.update_self(x, y, all_nulls, array4);
  assert(x == 9);
  assert(y == 9);
}

TEST(CreatureUpdateSelf, test2) {
  // tests move in a direction works for each direction

  Species s('s');
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  Creature c1(&s, EAST);
  Creature c2(&s, SOUTH);
  Creature c3(&s, NORTH);
  Creature c4(&s, WEST);

  int x = 0;
  int y = 0;

  Creature *all_nulls[4] = {NULL, NULL, NULL, NULL};

  bool array1[4] = {true, true, false, false};
  bool array2[4] = {false, true, true, false};
  bool array3[4] = {true, false, false, true};
  bool array4[4] = {false, false, true, true};

  c1.update_self(x, y, all_nulls, array1);
  assert(x == 0);
  assert(y == 1);

  x = 0;
  y = 9;

  c2.update_self(x, y, all_nulls, array2);
  assert(x == 1);
  assert(y == 9);

  x = 9;
  y = 0;

  c3.update_self(x, y, all_nulls, array3);
  assert(x == 8);
  assert(y == 0);

  x = 9;
  y = 9;

  c4.update_self(x, y, all_nulls, array4);
  assert(x == 9);
  assert(y == 8);
}

TEST(CreatureUpdateSelf, test3) {
  // full cycle turns both ways

  Species s('s');
  s.add_action_instruction(LEFT);
  s.add_control_instruction(GO, 0);

  Species t('t');
  t.add_action_instruction(RIGHT);
  t.add_control_instruction(GO, 0);

  Creature c1(&s, EAST);
  Creature c2(&t, EAST);

  int x = 0;
  int y = 0;

  Creature *all_nulls[4] = {NULL, NULL, NULL, NULL};
  bool bools[4] = {true, true, false, false};

  c1.update_self(x, y, all_nulls, bools);
  assert(c1.direction == NORTH);

  c1.update_self(x, y, all_nulls, bools);
  assert(c1.direction == WEST);

  c1.update_self(x, y, all_nulls, bools);
  assert(c1.direction == SOUTH);

  c1.update_self(x, y, all_nulls, bools);
  assert(c1.direction == EAST);

  c2.update_self(x, y, all_nulls, bools);
  assert(c2.direction == SOUTH);

  c2.update_self(x, y, all_nulls, bools);
  assert(c2.direction == WEST);

  c2.update_self(x, y, all_nulls, bools);
  assert(c2.direction == NORTH);

  c2.update_self(x, y, all_nulls, bools);
  assert(c2.direction == EAST);
}

TEST(CreatureUpdateSelf, test4) {
  // check moves correctly with no collision

  Species s('s');
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  Species t('t');
  t.add_action_instruction(HOP);
  t.add_control_instruction(GO, 0);

  Creature c1(&s, NORTH);
  Creature c2(&t, EAST);

  Creature *carray1[4] = {&c2, NULL, NULL, NULL};
  bool barray1[4] = {false, false, false, true};

  int x = 2;
  int y = 1;
  c1.update_self(x, y, carray1, barray1);

  assert(x == 1);
  assert(y == 1);
}

TEST(CreatureUpdateSelf, test5) {
  // checks infect converts correctly

  Species s('s');
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  Species t('t');
  t.add_action_instruction(INFECT);
  t.add_control_instruction(GO, 0);

  Creature c1(&s, NORTH);
  Creature c2(&t, WEST);

  int x = 2;
  int y = 1;

  Creature *carray1[4] = {NULL, NULL, NULL, NULL};
  bool barray1[4] = {false, false, false, true};
  Creature *carray2[4] = {&c1, NULL, NULL, NULL};
  bool barray2[4] = {false, false, true, false};

  c1.update_self(x, y, carray1, barray1);
  assert(x == 1);
  assert(y == 1);

  y = 2;

  c2.update_self(x, y, carray2, barray2);
  assert(c1.species == &t);
  assert(x == 1);
  assert(y == 2);
}

// --------------
// DarwinSimulate
// --------------

TEST(DarwinSimulate, test1) {
  // simulate a creature moving across grid

  Species s('s');
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  Creature c(&s, EAST);

  Darwin d(10, 10);
  d.add_creature(&c, 0, 0);

  d.simulate(7, NULL);

  assert(d.grid[7] == &c);
}

TEST(DarwinSimulate, test2) {
  // checks two moving towards each other will stop when collide

  Species s('s');
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  Creature c1(&s, EAST);
  Creature c2(&s, WEST);

  Darwin d(10, 10);
  d.add_creature(&c1, 2, 0);
  d.add_creature(&c2, 2, 9);

  d.simulate(8, NULL);

  assert(d.grid[24] == &c1);
  assert(d.grid[25] == &c2);
}

TEST(DarwinSimulate, test3) {
  // checks print works fine

  Species s('s');
  s.add_action_instruction(HOP);
  s.add_action_instruction(RIGHT);
  s.add_control_instruction(GO, 0);

  Creature c1(&s, EAST);

  Darwin d(2, 2);
  d.add_creature(&c1, 0, 0);

  ostringstream out;
  d.simulate(3, &out);

  assert(out.str() == "Turn = 1.\n  01\n0 .s\n1 ..\n\nTurn = 2.\n  01\n0 .s\n1 "
                      "..\n\nTurn = 3.\n  01\n0 ..\n1 .s\n\n");
}

TEST(DarwinSimulate, test4) {
  // checks creature won't move if collision

  Species s('s');
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  Creature c1(&s, EAST);
  Creature c2(&s, NORTH);

  Darwin d(4, 4);
  d.add_creature(&c1, 2, 2);
  d.add_creature(&c2, 3, 3);
  d.simulate(1, NULL);

  assert(d.grid[11] == &c1);
  assert(d.grid[15] == &c2);
}

TEST(DarwinSimulate, test5) {
  // checks a creature won't move one a turn even if colliding creature moves
  // afterward

  Species s('s');
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  Creature c1(&s, EAST);
  Creature c2(&s, NORTH);

  Darwin d(4, 4);
  d.add_creature(&c1, 2, 2);
  d.add_creature(&c2, 2, 3);
  d.simulate(1, NULL);

  assert(d.grid[10] == &c1);
  assert(d.grid[7] == &c2);
}

TEST(DarwinSimulate, test6) {
  // checks if colliding creature moves before, the creature can still move

  Species s('s');
  s.add_action_instruction(HOP);
  s.add_control_instruction(GO, 0);

  Creature c1(&s, WEST);
  Creature c2(&s, NORTH);

  Darwin d(4, 4);
  d.add_creature(&c1, 2, 2);
  d.add_creature(&c2, 2, 1);
  d.simulate(1, NULL);

  assert(d.grid[9] == &c1);
  assert(d.grid[5] == &c2);
}
