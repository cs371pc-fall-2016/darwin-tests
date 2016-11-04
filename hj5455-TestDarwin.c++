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
#include <assert.h> /* assert */
#include <cstdlib>  // rand, srand
#include <string>

#include "Darwin.h"

using namespace std;

// Test that printDescription() only goes up to index

TEST(DarwinFixture, species_test_add4) {
  Species s('a');
  s.addInstruction(4, "blah");
  s.addInstruction(5, "blah");
  s.addInstruction(6, "blah");
  ostringstream w;
  s.printDescription(3, w);
  ASSERT_EQ("a\n0 \n1 \n2 \n", w.str());
}

// ----------------------------
// test Species add instruction
// ----------------------------

TEST(DarwinFixture, species_test_add1) {
  Species s('f');
  s.addInstruction(0, "hop");
  s.addInstruction(1, "go 2");
  s.addInstruction(2, "right");
  ostringstream w;
  s.printDescription(3, w);
  ASSERT_EQ("f\n0 hop\n1 go 2\n2 right\n", w.str());
}

TEST(DarwinFixture, species_test_add2) {
  Species s('a');
  s.addInstruction(0, "go 1");
  s.addInstruction(1, "go 2");
  s.addInstruction(2, "go 3");
  s.addInstruction(3, "left");
  ostringstream w;
  s.printDescription(4, w);
  ASSERT_EQ("a\n0 go 1\n1 go 2\n2 go 3\n3 left\n", w.str());
}
TEST(DarwinFixture, species_test_add3) {
  Species s('a');
  s.addInstruction(0, "if_enemy 2");
  s.addInstruction(1, "right");
  s.addInstruction(2, "left");
  ostringstream w;
  s.printDescription(3, w);
  ASSERT_EQ("a\n0 if_enemy 2\n1 right\n2 left\n", w.str());
}

// ----------------------------
// test Species same type
// ----------------------------

TEST(DarwinFixture, species_test_same_type1) {
  Species s('f');
  Species s2('f');
  ASSERT_TRUE(s.sameType(s2));
}

TEST(DarwinFixture, species_test_same_type2) {
  Species s('f');
  Species s3('g');
  ASSERT_FALSE(s.sameType(s3));
}
TEST(DarwinFixture, species_test_same_type3) {
  Species s('a');
  Species s2('a');
  Species s3('b');
  ASSERT_FALSE(s.sameType(s3));
  ASSERT_TRUE(s.sameType(s2));
}

// ----------------------------
// test changeSpecies
// ----------------------------

TEST(DarwinFixture, species_test_change_species1) {
  Species s('f');
  Species s2('c');
  s.changeSpecies(s2);
  ASSERT_TRUE(s.sameType(s2));
}

TEST(DarwinFixture, species_test_change_species2) {
  Species s('f');
  Species s2('c');
  Species s3('f');
  s.changeSpecies(s2);
  ASSERT_FALSE(s.sameType(s3));
}

TEST(DarwinFixture, species_test_change_species3) {
  Species s('f');
  Species s2('c');
  Species s3('a');
  s.changeSpecies(s2);
  s3.changeSpecies(s);
  ASSERT_TRUE(s3.sameType(s2));
}

// ----------------------------
// test incrCounter
// ----------------------------

TEST(DarwinFixture, species_test_incr_counter1) {
  unsigned int pc = 5;
  Species s('f');
  s.incrCounter(pc);
  ASSERT_EQ(pc, 6);
}

TEST(DarwinFixture, species_test_incr_counter2) {
  unsigned int pc = 5;
  Species s('f');
  s.incrCounter(pc);
  s.incrCounter(pc);
  s.incrCounter(pc);
  s.incrCounter(pc);
  ASSERT_EQ(pc, 9);
}

// ----------------------------
// test Species execute control flow
// ----------------------------

TEST(DarwinFixture, species_test_control_flow1) {
  Species rover('r');
  rover.addInstruction(0, "if_enemy 9");
  rover.addInstruction(1, "if_empty 7");
  rover.addInstruction(2, "if_random 5");
  rover.addInstruction(3, "left");
  rover.addInstruction(4, "go 0");
  rover.addInstruction(5, "right");
  rover.addInstruction(6, "go 0");
  rover.addInstruction(7, "hop");
  rover.addInstruction(8, "go 0");
  rover.addInstruction(9, "infect");
  rover.addInstruction(10, "go 0");
  unsigned int pc = 0;

  string instr = rover.executeControlFlow(false, false, true, pc);

  ASSERT_EQ(instr, "infect");
}

TEST(DarwinFixture, species_test_control_flow2) {
  srand(0);
  Species rover('r');
  rover.addInstruction(0, "if_enemy 9");
  rover.addInstruction(1, "if_empty 7");
  rover.addInstruction(2, "if_random 5");
  rover.addInstruction(3, "left");
  rover.addInstruction(4, "go 0");
  rover.addInstruction(5, "right");
  rover.addInstruction(6, "go 0");
  rover.addInstruction(7, "hop");
  rover.addInstruction(8, "go 0");
  rover.addInstruction(9, "infect");
  rover.addInstruction(10, "go 0");

  unsigned int pc = 1;
  string instr = rover.executeControlFlow(true, false, false, pc);

  ASSERT_EQ(instr, "hop");
}

TEST(DarwinFixture, species_test_control_flow6) {
  srand(0);
  Species rover('r');
  rover.addInstruction(0, "if_enemy 9");
  rover.addInstruction(1, "if_empty 7");
  rover.addInstruction(2, "if_random 5");
  rover.addInstruction(3, "left");
  rover.addInstruction(4, "go 0");
  rover.addInstruction(5, "right");
  rover.addInstruction(6, "go 0");
  rover.addInstruction(7, "hop");
  rover.addInstruction(8, "go 0");
  rover.addInstruction(9, "infect");
  rover.addInstruction(10, "go 0");
  unsigned int pc2 = 1;
  string instr2 = rover.executeControlFlow(false, false, false, pc2);
  ASSERT_EQ(instr2, "right");
}

TEST(DarwinFixture, species_test_control_flow3) {
  srand(0);
  Species rover('r');
  rover.addInstruction(0, "if_enemy 9");
  rover.addInstruction(1, "if_empty 7");
  rover.addInstruction(2, "if_random 5");
  rover.addInstruction(3, "left");
  rover.addInstruction(4, "go 0");
  rover.addInstruction(5, "right");
  rover.addInstruction(6, "go 0");
  rover.addInstruction(7, "hop");
  rover.addInstruction(8, "go 0");
  rover.addInstruction(9, "infect");
  rover.addInstruction(10, "go 0");

  unsigned int pc = 2;

  string instr = rover.executeControlFlow(true, false, false, pc);

  assert(instr == "left" || instr == "right");
}

TEST(DarwinFixture, species_test_control_flow4) {
  srand(0);
  Species rover('r');
  rover.addInstruction(0, "if_enemy 9");
  rover.addInstruction(1, "if_empty 7");
  rover.addInstruction(2, "if_random 5");
  rover.addInstruction(3, "left");
  rover.addInstruction(4, "go 0");
  rover.addInstruction(5, "right");
  rover.addInstruction(6, "go 0");
  rover.addInstruction(7, "hop");
  rover.addInstruction(8, "go 0");
  rover.addInstruction(9, "infect");
  rover.addInstruction(10, "go 0");

  unsigned int pc = 3;

  string instr = rover.executeControlFlow(true, false, false, pc);

  ASSERT_EQ(instr, "left");
}

TEST(DarwinFixture, species_test_control_flow5) {
  srand(0);
  Species rover('r');
  rover.addInstruction(0, "if_enemy 9");
  rover.addInstruction(1, "if_empty 7");
  rover.addInstruction(2, "if_random 5");
  rover.addInstruction(3, "left");
  rover.addInstruction(4, "go 0");
  rover.addInstruction(5, "right");
  rover.addInstruction(6, "go 0");
  rover.addInstruction(7, "hop");
  rover.addInstruction(8, "go 0");
  rover.addInstruction(9, "infect");
  rover.addInstruction(10, "go 0");

  unsigned int pc = 4;

  string instr = rover.executeControlFlow(false, false, true, pc);

  ASSERT_EQ(instr, "infect");
}

TEST(DarwinFixture, species_test_control_flow7) {
  srand(0);
  Species rover('r');
  rover.addInstruction(0, "if_enemy 9");
  rover.addInstruction(1, "if_empty 7");
  rover.addInstruction(2, "if_random 5");
  rover.addInstruction(3, "left");
  rover.addInstruction(4, "go 0");
  rover.addInstruction(5, "right");
  rover.addInstruction(6, "go 0");
  rover.addInstruction(7, "hop");
  rover.addInstruction(8, "go 0");
  rover.addInstruction(9, "infect");
  rover.addInstruction(10, "go 0");

  unsigned int pc2 = 4;
  string instr2 = rover.executeControlFlow(true, false, false, pc2);
  ASSERT_EQ(instr2, "hop");
}

// executeControlFlow (bool isEmpty, bool isWall, bool isEnemy, unsigned int&
// programCounter)

// --------------------------------
// test create execute control flow
// --------------------------------

TEST(DarwinFixture, creature_test_execute1) {
  Darwin d(5, 5, 2);

  Creature c(0, d.findSpecies('r'));

  int i = c.executeInstruction(false, false, true, 1);

  ASSERT_EQ(i, 1);
}

TEST(DarwinFixture, creatuer_test_execute2) {
  Darwin d(5, 5, 2);

  Creature c(0, d.findSpecies('r'));

  int i = c.executeInstruction(false, false, true, 1);

  ASSERT_EQ(i, 1);
  i = c.executeInstruction(false, false, true, 1);
  ASSERT_EQ(i, -1);
}

TEST(DarwinFixture, creature_test_execute3) {
  Darwin d(5, 5, 2);

  Creature c(0, d.findSpecies('h'));

  int i = c.executeInstruction(true, false, true, 1);

  ASSERT_EQ(i, 0);
}

// ------------
// test inFront
// ------------

TEST(DarwinFixture, creature_test_in_front1) {
  Darwin d(5, 5, 2);

  Creature c(1, d.findSpecies('h'));

  int i = c.inFront(0, 5);

  ASSERT_EQ(i, 1);
}

TEST(DarwinFixture, creature_test_in_front2) {
  Darwin d(5, 5, 2);

  Creature c(2, d.findSpecies('h'));

  int i = c.inFront(0, 5);

  ASSERT_EQ(i, 5);
}

TEST(DarwinFixture, creature_test_in_front3) {
  Darwin d(5, 5, 3);

  Creature c(3, d.findSpecies('h'));

  int i = c.inFront(4, 5);

  ASSERT_EQ(i, 3);
}

TEST(DarwinFixture, creature_test_in_front4) {
  Darwin d(5, 5, 2);

  Creature c(0, d.findSpecies('h'));

  int i = c.inFront(5, 5);

  ASSERT_EQ(i, 0);
}

// ------------
// test isEnemy
// ------------

TEST(DarwinFixture, creature_test_is_enemy1) {
  Creature c(0, 'h');
  Creature d(0, '.');
  ASSERT_FALSE(c.isEnemy(d));
}

TEST(DarwinFixture, creature_test_is_enemy2) {
  Creature c(0, '.');
  Creature d(0, '.');
  ASSERT_TRUE(c.isEnemy(d));
}

// ------------
// test infect
// ------------

TEST(DarwinFixture, creature_test_infect1) {
  Creature c(0, 'h');
  Creature d(0, '.');
  d.infect(c);
  ASSERT_TRUE(d.isEnemy(c));
}

TEST(DarwinFixture, creature_test_infect2) {
  Creature c(0, 'h');
  Creature d(0, '.');
  Creature f(0, 'f');
  d.infect(c);
  ASSERT_FALSE(d.isEnemy(f));
}

TEST(DarwinFixture, creature_test_infect3) {
  Creature c(0, 'h');
  Creature d(0, '.');
  Creature f(0, 'f');
  d.infect(c);
  d.infect(f);
  ASSERT_TRUE(d.isEnemy(f));
  ASSERT_TRUE(d.isEnemy(c));
}

// ----------------
// test addCreature
// ----------------
TEST(DarwinFixture, darwin_test_add_creature1) {
  Darwin d(5, 5, 2);
  d.addCreature('f', 1, 1, 1);
  Creature f(1, 'f');
  ASSERT_TRUE(d.board[6].isEnemy(f));
}

TEST(DarwinFixture, darwin_test_add_creature2) {
  Darwin d(5, 5, 2);
  d.addCreature('f', 1, 1, 1);
  Creature f(1, '.');
  ASSERT_FALSE(d.board[6].isEnemy(f));
}

TEST(DarwinFixture, darwin_test_add_creature3) {
  Darwin d(5, 5, 2);
  d.addCreature('f', 1, 1, 1);
  int i = d.board[6].inFront(6, 1);
  ASSERT_EQ(i, 7);
}

// ----------------
// test findSpecies
// ----------------

TEST(DarwinFixture, darwin_test_find_species1) {
  Darwin d(5, 5, 2);
  Species c = d.findSpecies('f');
  ASSERT_TRUE(c.sameType(Species('f')));
}

TEST(DarwinFixture, darwin_test_find_species2) {
  Darwin d(5, 5, 2);
  Species c = d.findSpecies('t');
  ASSERT_TRUE(c.sameType(Species('t')));
}

TEST(DarwinFixture, darwin_test_find_species3) {
  Darwin d(5, 5, 2);
  Species c = d.findSpecies('f');
  ASSERT_FALSE(c.sameType(Species('d')));
}

// -----------
// test isWall
// -----------

// test isWall for spots along north side
TEST(DarwinFixture, creatue_test_isWall0) {
  Darwin d(5, 5, 2);

  bool wall;

  for (int i = 1; i < 4; ++i) {
    wall = d.isWall(i, 0);
    ASSERT_TRUE(wall);
  }
  // check corner
  bool wall0 = d.isWall(0, 0);
  ASSERT_TRUE(wall0);
  // check corner
  bool wall2 = d.isWall(4, 0);
  ASSERT_TRUE(wall2);
}

// test isWall for spots along north side, facing south
TEST(DarwinFixture, creatue_test_isWall01) {
  Darwin d(5, 5, 2);

  bool wall;

  for (int i = 1; i < 4; ++i) {
    wall = d.isWall(i, 2);
    ASSERT_FALSE(wall);
  }
  // check corner
  bool wall0 = d.isWall(0, 2);
  ASSERT_FALSE(wall0);
  // check corner
  bool wall2 = d.isWall(4, 2);
  ASSERT_FALSE(wall2);
}

// test isWall for spots along east side
TEST(DarwinFixture, creatue_test_isWall1) {
  Darwin d(5, 5, 2);

  bool wall;
  for (int i = 1; i < 5; ++i) {
    wall = d.isWall(i * 5 - 1, 1);
    ASSERT_TRUE(wall);
  }
  bool wall0 = d.isWall(4, 1);
  ASSERT_TRUE(wall0);
  bool wall2 = d.isWall(24, 1);
  ASSERT_TRUE(wall2);
}

// test isWall for spots along east side, facing west
TEST(DarwinFixture, creatue_test_isWall11) {
  Darwin d(5, 5, 2);

  bool wall;
  for (int i = 1; i < 5; ++i) {
    wall = d.isWall(i * 5 - 1, 3);
    ASSERT_FALSE(wall);
  }
  bool wall0 = d.isWall(4, 3);
  ASSERT_FALSE(wall0);
  bool wall2 = d.isWall(24, 3);
  ASSERT_FALSE(wall2);
}

// test isWall for spots along south side
TEST(DarwinFixture, creatue_test_isWall2) {
  Darwin d(5, 5, 2);

  bool wall;
  for (int i = 20; i < 25; ++i) {
    wall = d.isWall(i, 2);
    ASSERT_TRUE(wall);
  }
  // check corner
  bool wall2 = d.isWall(24, 2);
  ASSERT_TRUE(wall2);
}

// test isWall for spots along south side, facing north
TEST(DarwinFixture, creatue_test_isWall21) {
  Darwin d(5, 5, 2);

  bool wall;
  for (int i = 20; i < 25; ++i) {
    wall = d.isWall(i, 0);
    ASSERT_FALSE(wall);
  }
  // check corner
  bool wall2 = d.isWall(24, 0);
  ASSERT_FALSE(wall2);
}

// test isWall for spots along west side
TEST(DarwinFixture, creatue_test_isWall3) {
  Darwin d(5, 5, 2);
  bool wall;

  for (int i = 0; i < 4; ++i) {

    wall = d.isWall(i * 5, 3);
    ASSERT_TRUE(wall);
  }

  bool wall2 = d.isWall(20, 3);
  ASSERT_TRUE(wall2);
}

// test isWall for spots along west side, facing east
TEST(DarwinFixture, creatue_test_isWall31) {
  Darwin d(5, 5, 2);
  bool wall;

  for (int i = 0; i < 4; ++i) {

    wall = d.isWall(i * 5, 1);
    ASSERT_FALSE(wall);
  }

  bool wall2 = d.isWall(20, 1);
  ASSERT_FALSE(wall2);
}

// -----------
// test isEmpty
// -----------

// test that entire board is empty
TEST(DarwinFixture, creatue_test_isEmpty0) {
  Darwin d(5, 5, 2);

  bool empty;

  for (int i = 0; i < 25; ++i) {
    empty = d.isEmpty(i);
    ASSERT_TRUE(empty);
  }
}

// test that entire board is not empty
TEST(DarwinFixture, creatue_test_isEmpty1) {
  Darwin d(3, 3, 2);

  bool empty;

  for (int i = 0; i < 9; ++i) {
    d.addCreature('f', i / 3, i % 3, 0);

    empty = d.isEmpty(i);
    ASSERT_FALSE(empty);
  }
}

TEST(DarwinFixture, creatue_test_isEmpty2) {
  Darwin d(3, 3, 2);

  bool empty;

  for (int i = 0; i < 9; ++i) {
    d.addCreature('f', i / 3, i % 3, 0);

    empty = d.isEmpty(i, false);
    ASSERT_FALSE(empty);
  }
}

TEST(DarwinFixture, creatue_test_isEmpty3) {
  Darwin d(5, 5, 2);

  bool empty;

  for (int i = 0; i < 25; ++i) {
    empty = d.isEmpty(i, true);
    ASSERT_FALSE(empty);
  }
}

TEST(DarwinFixture, creatue_test_isEmpty4) {
  Darwin d(5, 5, 2);

  bool empty;

  for (int i = 0; i < 25; ++i) {
    empty = d.isEmpty(i, false);
    ASSERT_TRUE(empty);
  }
}

// ------------------
// test calcDirection
// ------------------

TEST(DarwinFixture, darwin_test_calc_direction1) {
  Darwin d(5, 5, 2);

  int i = d.calcDirection(2, 3);
  ASSERT_EQ(i, 1);
}

TEST(DarwinFixture, darwin_test_calc_direction2) {
  Darwin d(5, 5, 2);

  int i = d.calcDirection(2, 1);
  ASSERT_EQ(i, 3);
}

TEST(DarwinFixture, darwin_test_calc_direction3) {
  Darwin d(5, 5, 2);

  int i = d.calcDirection(2, 7);
  ASSERT_EQ(i, 2);
}

TEST(DarwinFixture, darwin_test_calc_direction4) {
  Darwin d(5, 5, 2);

  int i = d.calcDirection(7, 2);
  ASSERT_EQ(i, 0);
}

// -------------
// test isAEnemy
// -------------

TEST(DarwinFixture, creatue_test_isAEnemy0) {
  Darwin d(5, 5, 2);

  bool enemy;
  d.addCreature('r', 0, 0, 1);
  for (int i = 1; i < 25; ++i) {
    d.addCreature('f', i / 5, i % 5, 0);
  }

  enemy = d.isAEnemy(2, d.board[0], 1);
  ASSERT_TRUE(enemy);

  enemy = d.isAEnemy(5, d.board[0], 1);
  ASSERT_TRUE(enemy);

  enemy = d.isAEnemy(0, d.board[0], 1);
  ASSERT_FALSE(enemy);
}

TEST(DarwinFixture, creatue_test_isAEnemy1) {
  Darwin d(5, 5, 2);

  bool enemy;
  d.addCreature('r', 0, 0, 1);

  enemy = d.isAEnemy(0, Creature(1, 'r'), 1);
  ASSERT_FALSE(enemy);
}

TEST(DarwinFixture, creatue_test_isAEnemy2) {
  Darwin d(5, 5, 2);

  bool enemy;
  d.addCreature('r', 0, 0, 1);

  enemy = d.isAEnemy(0, Creature(1, 'f'), 1);
  ASSERT_TRUE(enemy);
}

// --------------------
// test rover movement
// --------------------

TEST(DarwinFixture, test_rover_movement) {
  Darwin d(3, 3, 5);

  d.addCreature('r', 1, 2, 3);
  d.executeGame(false);
  bool isRover = d.isAEnemy(0, d.board[0], 2);
  ASSERT_FALSE(isRover);
}

TEST(DarwinFixture, test_rover_movement2) {
  Darwin d(3, 3, 5);
  srand(0);

  d.addCreature('r', 1, 2, 0);
  d.executeGame(false);
  bool isRover = d.isAEnemy(2, d.board[2], 2);
  ASSERT_FALSE(isRover);
}

TEST(DarwinFixture, test_rover_movement3) {
  Darwin d(3, 3, 5);

  srand(0);

  d.addCreature('r', 1, 0, 2);
  d.executeGame(false);
  bool isRover = d.isAEnemy(6, d.board[6], 1);
  ASSERT_FALSE(isRover);
}

// --------------------
// test rover infection
// --------------------

// test that trap infects
TEST(DarwinFixture, test_rover_exe0) {
  Darwin d(3, 3, 7);
  bool isRover;

  for (int i = 0; i < 9; ++i) {
    d.addCreature('f', i / 3, i % 3, 0);
  }
  d.addCreature('r', 1, 1, 0);
  d.executeGame(false);

  for (int i = 0; i < 9; ++i) {
    isRover = d.isAEnemy(i, d.board[4], 2);
    ASSERT_FALSE(isRover);
  }
}

TEST(DarwinFixture, test_rover_exe1) {
  Darwin d(3, 3, 100);
  bool isRover;
  for (int i = 0; i < 9; ++++i) {
    d.addCreature('h', i / 3, i % 3, 0);
  }
  d.addCreature('r', 1, 1, 0);
  Species r('r');
  Creature rover(0, r);
  d.executeGame(false);

  for (int i = 0; i < 9; ++i) {
    if (d.isEmpty(i) == false) {
      isRover = d.isAEnemy(i, rover, 2);
      ASSERT_FALSE(isRover);
    }
  }
}

// --------------------
// test hopper execution
// --------------------

TEST(DarwinFixture, test_hopper_exe0) {
  Darwin d(3, 3, 4);

  d.addCreature('h', 1, 2, 3);
  d.executeGame(false);
  bool isHopper = d.isAEnemy(3, d.board[3], 2);
  ASSERT_FALSE(isHopper);
}

TEST(DarwinFixture, test_hopper_exe2) {
  Darwin d(3, 3, 4);

  d.addCreature('h', 0, 0, 3);
  d.executeGame(false);
  bool isHopper = d.isAEnemy(0, d.board[0], 2);
  ASSERT_FALSE(isHopper);
}

TEST(DarwinFixture, test_hopper_exe3) {
  Darwin d(3, 3, 4);

  d.addCreature('h', 1, 2, 3);
  d.executeGame(false);
  bool isHopper = d.isAEnemy(6, d.board[6], 2);
  ASSERT_FALSE(isHopper);
}

TEST(DarwinFixture, test_hopper_exe4) {
  Darwin d(3, 3, 4);

  d.addCreature('h', 0, 2, 1);
  d.executeGame(false);
  bool isHopper = d.isAEnemy(2, d.board[2], 2);
  ASSERT_FALSE(isHopper);
}

// ------------------
// test trap movement
// ------------------

// test that trap isn't moving
TEST(DarwinFixture, test_trap_movement_exe0) {
  Darwin d(3, 3, 4);

  d.addCreature('t', 1, 2, 3);
  d.executeGame(false);
  bool isTrap = d.isAEnemy(5, d.board[5], 2);
  ASSERT_FALSE(isTrap);
}

TEST(DarwinFixture, test_trap_movement_exe2) {
  Darwin d(3, 3, 4);

  d.addCreature('t', 0, 0, 3);
  d.executeGame(false);
  bool isTrap = d.isAEnemy(0, d.board[0], 2);
  ASSERT_FALSE(isTrap);
}

TEST(DarwinFixture, test_trap_movement_exe3) {
  Darwin d(3, 3, 4);

  d.addCreature('t', 1, 1, 3);
  d.executeGame(false);
  bool isTrap = d.isAEnemy(4, d.board[4], 2);
  ASSERT_FALSE(isTrap);
}

TEST(DarwinFixture, test_trap_movement_exe4) {
  Darwin d(3, 3, 4);

  d.addCreature('t', 2, 2, 1);
  d.executeGame(false);
  bool isTrap = d.isAEnemy(8, d.board[8], 2);
  ASSERT_FALSE(isTrap);
}

TEST(DarwinFixture, test_trap_movement_exe5) {
  Darwin d(3, 3, 1);

  d.addCreature('t', 0, 0, 1);
  d.executeGame(false);
  int i = d.calcDirection(0, d.board[0].inFront(0, 3));
  ASSERT_EQ(i, 0);
}

TEST(DarwinFixture, test_trap_movement_exe6) {
  Darwin d(3, 3, 3);

  d.addCreature('t', 0, 0, 1);
  d.executeGame(false);
  int i = d.calcDirection(0, d.board[0].inFront(0, 3));
  ASSERT_EQ(i, 2);
}

// ------------------
// test trap infection
// ------------------

// test that trap infects
TEST(DarwinFixture, test_trap_exe0) {
  Darwin d(3, 3, 7);

  for (int i = 0; i < 9; ++i) {
    d.addCreature('f', i / 3, i % 3, 0);
  }
  d.addCreature('t', 1, 1, 0);
  d.executeGame(false);

  for (int i = 0; i < 9; ++i) {
    bool isTrap = d.isAEnemy(i, d.board[4], 2);
    ASSERT_FALSE(isTrap);
  }
}
// test that trap infects
TEST(DarwinFixture, test_trap_exe1) {
  Darwin d(3, 3, 7);
  bool isTrap;
  for (int i = 0; i < 9; ++++i) {
    d.addCreature('h', i / 3, i % 3, 0);
  }
  d.addCreature('t', 1, 1, 0);
  d.executeGame(false);

  for (int i = 0; i < 9; ++i) {
    if (d.isEmpty(i) == false) {
      isTrap = d.isAEnemy(i, d.board[4], 2);
      ASSERT_FALSE(isTrap);
    }
  }
}

TEST(DarwinFixture, test_trap_exe2) {
  Darwin d(3, 3, 8);
  bool isTrap;
  for (int i = 0; i < 9; ++i) {
    if (i % 2)
      d.addCreature('h', i / 3, i % 3, 0);
    else
      d.addCreature('f', i / 3, i % 3, 0);
  }
  d.addCreature('t', 1, 1, 0);
  d.executeGame(false);

  for (int i = 0; i < 9; ++i) {
    isTrap = d.isAEnemy(i, d.board[4], 2);
    ASSERT_FALSE(isTrap);
  }
}

// test that trap infects
TEST(DarwinFixture, test_trap_exe3) {
  Darwin d(5, 5, 100);
  bool isTrap;
  for (int i = 0; i < 25; ++++i) {
    d.addCreature('h', i / 5, i % 5, 0);
  }

  for (int i = 1; i < 24; ++++i) {
    d.addCreature('f', i / 5, i % 5, 0);
  }

  d.addCreature('t', 2, 2, 0);
  d.executeGame(false);

  for (int i = 0; i < 25; ++i) {
    isTrap = d.isAEnemy(i, d.board[4], 2);
    ASSERT_FALSE(isTrap);
  }
}

// -------------------
// test food movement
// -------------------
TEST(DarwinFixture, test_food_exe1) {
  Darwin d(3, 3, 1);
  d.addCreature('f', 0, 0, 0);
  d.executeGame(false);
  int i = d.calcDirection(0, d.board[0].inFront(0, 3));
  ASSERT_EQ(i, 3);
}

TEST(DarwinFixture, test_food_exe2) {
  Darwin d(3, 3, 2);
  d.addCreature('f', 0, 0, 0);
  d.executeGame(false);
  int i = d.calcDirection(0, d.board[0].inFront(0, 3));
  ASSERT_EQ(i, 2);
}

TEST(DarwinFixture, test_food_exe3) {
  Darwin d(3, 3, 3);
  d.addCreature('f', 0, 0, 0);
  d.executeGame(false);
  int i = d.calcDirection(0, d.board[0].inFront(0, 3));
  ASSERT_EQ(i, 1);
}
