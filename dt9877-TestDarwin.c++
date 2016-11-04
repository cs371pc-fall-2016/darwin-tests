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

// ----
// Instruction struct tests
// ----

/* Test Instruction constructor for no operand instruction*/
TEST(DarwinFixture, TestInstruction1) {
  Instruction i(HOP);
  ASSERT_TRUE(i.instruction == HOP);
  ASSERT_TRUE(i.operand == -1);
}

/* Test Instruction constructor for instruction with one operand*/
TEST(DarwinFixture, TestInstruction2) {
  Instruction i(GO, 123);
  ASSERT_TRUE(i.instruction == GO);
  ASSERT_TRUE(i.operand == 123);
}

/* Test Instruction constructor for instruction with one operand*/
TEST(DarwinFixture, TestInstruction3) {
  Instruction i(IFRANDOM, 123);
  ASSERT_TRUE(i.instruction == IFRANDOM);
  ASSERT_TRUE(i.operand == 123);
}

// ----
// Specie class tests
// ----

/* Test Specie constructor*/
TEST(DarwinFixture, TestSpecie1) {
  Specie s("Food");
  ASSERT_EQ(s._name.compare("Food"), 0);
}

/* Test Specie constructor for its id*/
TEST(DarwinFixture, TestSpecie2) {
  Specie s("Food");
  ASSERT_EQ(s.id(), 'F');
}

/* Test Specie constructor for an empty program*/
TEST(DarwinFixture, TestSpecie3) {
  Specie s("Food");
  ASSERT_EQ(s._program.size(), 0);
}

/* Test Specie addInstruction method*/
TEST(DarwinFixture, TestSpecie4) {
  Specie s("Food");
  Instruction i(LEFT);
  s.addInstruction(i);
  ASSERT_TRUE(s.getInstruction(0).instruction == LEFT); 
}

/* Test Specie addInstruction method*/
TEST(DarwinFixture, TestSpecie5) {
  Specie s("Food");
  Instruction i1(LEFT);
  Instruction i2(GO, 0);
  s.addInstruction(i1);
  s.addInstruction(i2);
  ASSERT_TRUE(s.getInstruction(0).instruction == LEFT); 
  ASSERT_TRUE(s.getInstruction(1).instruction == GO);
  ASSERT_TRUE(s.getInstruction(1).operand == 0);
}

/* Test Specie addInstruction method*/
TEST(DarwinFixture, TestSpecie6) {
  Specie s("Food");
  Instruction i1(LEFT);
  Instruction i2(GO, 0);
  s.addInstruction(i1);
  s.addInstruction(i2);
  ASSERT_TRUE(s._program[0].instruction == LEFT); 
  ASSERT_TRUE(s._program.size() == 2);
}

/* Test Specie getInstruction method*/
TEST(DarwinFixture, TestSpecie7) {
  Specie s("Food");
  Instruction i(LEFT);
  s.addInstruction(i);
  ASSERT_TRUE(s.getInstruction(0).instruction == LEFT); 
}

/* Test Specie getInstruction method*/
TEST(DarwinFixture, TestSpecie8) {
  Specie s("Food");
  vector<Instruction> p;
  p.push_back(Instruction(LEFT));
  s._program = p;
  ASSERT_TRUE(s.getInstruction(0).instruction == LEFT); 
}

/* Test Specie getInstruction method*/
TEST(DarwinFixture, TestSpecie9) {
  Specie s("Food");
  vector<Instruction> p;
  p.push_back(Instruction(LEFT));
  p.push_back(Instruction(IFRANDOM, 0));
  s._program = p;
  ASSERT_TRUE(s.getInstruction(1).instruction == IFRANDOM);
  ASSERT_TRUE(s.getInstruction(1).operand == 0); 
}

/* Test Specie getId method*/
TEST(DarwinFixture, TestSpecie10) {
  Specie s("F");
  ASSERT_TRUE(s.id() == 'F'); 
}

/* Test Specie getId method*/
TEST(DarwinFixture, TestSpecie11) {
  Specie s("Food");
  ASSERT_TRUE(s.id() == 'F'); 
}


// ----
// Creature class tests
// ----



/* Test Creature constructor*/
TEST(DarwinFixture, TestCreature2) {
  Specie food("Food");
  Creature c(&food, NORTH);
  ASSERT_TRUE(c._specie == &food);
  ASSERT_TRUE(c._direction == NORTH);
  ASSERT_TRUE(c._programCounter == 0);
}

/* Test Creature inFront() method*/
TEST(DarwinFixture, TestCreature3) {
  Creature c(NULL, SOUTH);
  pair<int, int> location(0,0);
  ASSERT_TRUE(c.inFront(location) == make_pair(1,0));
}

/* Test Creature inFront() method*/
TEST(DarwinFixture, TestCreature4) {
  Creature c(NULL, EAST);
  pair<int, int> location(0,0);
  ASSERT_TRUE(c.inFront(location) == make_pair(0,1));
}

/* Test Creature inFront() method*/
TEST(DarwinFixture, TestCreature5) {
  Creature c(NULL, NORTH);
  pair<int, int> location(1,1);
  ASSERT_TRUE(c.inFront(location) == make_pair(0,1));
}

/* Test Creature inFront() method*/
TEST(DarwinFixture, TestCreature6) {
  Creature c(NULL, WEST);
  pair<int, int> location(1,1);
  ASSERT_TRUE(c.inFront(location) == make_pair(1,0));
}

/* Test Creature Hop action */
TEST(DarwinFixture, TestCreature7) {
  Specie specie("specie");
  specie.addInstruction(Instruction(HOP));
  Creature c(&specie, EAST);
  pair<int, int> location(0, 0);
  pair<int, int> newLocation = c.doInstruction(location, NULL);
  ASSERT_TRUE(newLocation == make_pair(0,1));
  ASSERT_TRUE(c._programCounter == 1);
  ASSERT_TRUE(c._direction == EAST);
}

/* Test Creature id */
TEST(DarwinFixture, TestCreature8) {
  Specie food("Food");
  Creature c(&food, NORTH);
  ASSERT_TRUE(c.id() == 'F');
}

/* Test Creature right action */
TEST(DarwinFixture, TestCreature9) {
  Specie specie("specie");
  specie.addInstruction(Instruction(RIGHT));
  Creature c(&specie, EAST);
  pair<int, int> location(0, 0);
  pair<int, int> newLocation = c.doInstruction(location, NULL);
  ASSERT_TRUE(newLocation == make_pair(-1,-1));
  ASSERT_TRUE(c._direction == SOUTH);
}

/* Test Creature left action */
TEST(DarwinFixture, TestCreature10) {
  Specie specie("specie");
  specie.addInstruction(Instruction(LEFT));
  Creature c(&specie, EAST);
  pair<int, int> location(0, 0);
  pair<int, int> newLocation = c.doInstruction(location, NULL);
  ASSERT_TRUE(newLocation == make_pair(-1,-1));
  ASSERT_TRUE(c._direction == NORTH);
}

/* Test Creature ifempty action */
TEST(DarwinFixture, TestCreature11) {
  Specie specie("specie");
  specie.addInstruction(Instruction(IFEMPTY, 2));
  specie.addInstruction(Instruction(LEFT));
  specie.addInstruction(Instruction(HOP));
  Creature c(&specie, SOUTH);
  pair<int, int> location(0, 0);
  pair<int, int> newLocation = c.doInstruction(location, NULL);
  ASSERT_TRUE(newLocation == make_pair(1,0));
}

/* Test Creature ifempty action */
TEST(DarwinFixture, TestCreature12) {
  Specie specie("specie");
  specie.addInstruction(Instruction(IFEMPTY, 2));
  specie.addInstruction(Instruction(LEFT));
  specie.addInstruction(Instruction(HOP));
  Creature c(&specie, SOUTH);
  Creature creatureInFront(NULL, 0);			  
  pair<int, int> location(0, 0);
  pair<int, int> newLocation = c.doInstruction(location, &creatureInFront);
  ASSERT_TRUE(newLocation == make_pair(-1,-1));
}

/* Test Creature go action */
TEST(DarwinFixture, TestCreature13) {
  Specie specie("specie");
  specie.addInstruction(Instruction(GO, 2));
  specie.addInstruction(Instruction(LEFT));
  specie.addInstruction(Instruction(HOP));
  Creature c(&specie, SOUTH);
  pair<int, int> location(0, 0);
  pair<int, int> newLocation = c.doInstruction(location, NULL);
  ASSERT_TRUE(newLocation == make_pair(1,0));
}

/* Test Creature ifwall action */
TEST(DarwinFixture, TestCreature14) {
  Specie specie("specie");
  specie.addInstruction(Instruction(IFWALL, 2));
  specie.addInstruction(Instruction(HOP));
  specie.addInstruction(Instruction(LEFT));
  Creature c(&specie, SOUTH);
  pair<int, int> location(0, 0);
  pair<int, int> newLocation = c.doInstruction(location, &c);
  ASSERT_TRUE(newLocation == make_pair(-1,-1));
}

/* Test Creature ifwall action */
TEST(DarwinFixture, TestCreature15) {
  Specie specie("specie");
  specie.addInstruction(Instruction(IFWALL, 2));
  specie.addInstruction(Instruction(HOP));
  specie.addInstruction(Instruction(LEFT));
  Creature c(&specie, SOUTH);
  pair<int, int> location(0, 0);
  pair<int, int> newLocation = c.doInstruction(location, NULL);
  ASSERT_EQ(newLocation, make_pair(1,0));
}

// ----
// Darwin class tests
// ----

/* Test Darwin constructor for an empty grid of the specified size*/
TEST(DarwinFixture, TestDarwin1) {
  Darwin d(3,3);
  ASSERT_EQ(d.grid.size(), 3);
}

/* Test Darwin constructor for an empty grid of the specified size*/
TEST(DarwinFixture, TestDarwin2) {
  Darwin d(3,5);
  ASSERT_EQ(d.grid.size(), 3);
  for (int i = 0; i < 3; i++){
    ASSERT_EQ(d.grid[i].size(), 5);
  }
}

/* Test Darwin constructor for an empty grid of the specified size. Check that the entire grid is pointing to NULL*/
TEST(DarwinFixture, TestDarwin3) {
  Darwin d(3,5);
  ASSERT_EQ(d.grid.size(), 3);
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 5; j++){
      ASSERT_TRUE(d.grid[i][j] == NULL);
    }
  }
}

/* Test printing an empty grid*/
TEST(DarwinFixture, TestDarwin4) {
  ostringstream w;
  Darwin d(2,2);
  d.print(w);
  ASSERT_EQ("Turn = 0.\n  01\n0 ..\n1 ..\n\n", w.str());
}

/* Test printing on turn 2*/
/* Test printing an empty grid*/
TEST(DarwinFixture, TestDarwin5) {
  ostringstream w;
  Darwin d(2,2);
  d.simulate();
  d.simulate();
  d.print(w);
  ASSERT_EQ("Turn = 2.\n  01\n0 ..\n1 ..\n\n", w.str());
}

/* Test printing a nonempty grid*/
TEST(DarwinFixture, TestDarwin6) {
  ostringstream w;
  Specie asdf("FOOD");
  Creature c(&asdf, 0);

  Darwin d(2,2);
  d.addCreature(&c, make_pair(0,0));
  d.print(w);
  ASSERT_EQ("Turn = 0.\n  01\n0 F.\n1 ..\n\n", w.str());
}

/* Test adding one creature*/
TEST(DarwinFixture, TestDarwin7) {
  Specie food("FOOD");
  Creature creature(&food, 0);
  Darwin d(2,2);
  d.addCreature(&creature, make_pair(0,0));
  ASSERT_TRUE(d.grid[0][0] == &creature);
}

/* Test adding multiple creatures*/
TEST(DarwinFixture, TestDarwin8) {
  Specie food("FOOD");
  Creature creature(&food, 0);
  Creature creature2(&food, 1);
  Darwin d(2,2);
  d.addCreature(&creature, make_pair(0,0));
  d.addCreature(&creature2, make_pair(1,1));
  ASSERT_TRUE(d.grid[0][0] == &creature);
  ASSERT_TRUE(d.grid[1][1] == &creature2);
}

/* Test filling grid with creatuers*/
TEST(DarwinFixture, TestDarwin9) {
  Specie food("FOOD");
  Creature creature1(&food, 0);
  Creature creature2(&food, 0);
  Creature creature3(&food, 0);
  Creature creature4(&food, 0);
  Darwin d(2,2);
  d.addCreature(&creature1, make_pair(0,0));
  d.addCreature(&creature2, make_pair(0,1));
  d.addCreature(&creature3, make_pair(1,0));
  d.addCreature(&creature4, make_pair(1,1));
  ASSERT_TRUE(d.grid[0][0] == &creature1);
  ASSERT_TRUE(d.grid[0][1] == &creature2);
  ASSERT_TRUE(d.grid[1][0] == &creature3);
  ASSERT_TRUE(d.grid[1][1] == &creature4);
}

/* Simulate creature hop */
TEST(DarwinFixture, TestDarwin10) {
  Specie hopper("hopper");
  hopper.addInstruction(Instruction(HOP));
  Creature creature1(&hopper, EAST);
  Darwin d(2,2);
  d.addCreature(&creature1, make_pair(0,0));
  ASSERT_TRUE(d.grid[0][0] == &creature1);
  ASSERT_TRUE(d.grid[0][1] == NULL);
  d.simulate();
  ASSERT_TRUE(d.grid[0][0] == NULL);
  ASSERT_TRUE(d.grid[0][1] == &creature1);
}

/* Simulate multiple turns */ 
TEST(DarwinFixture, TestDarwin11) {
  Specie hopper("hopper");
  hopper.addInstruction(Instruction(HOP));
  hopper.addInstruction(Instruction(GO, 0));
  Creature creature1(&hopper, EAST);
  Darwin d(2,4);
  d.addCreature(&creature1, make_pair(0,0));
  ASSERT_TRUE(d.grid[0][0] == &creature1);
  ASSERT_TRUE(d.grid[0][3] == NULL);
  d.simulate(3);
  ASSERT_TRUE(d.grid[0][0] == NULL);
  ASSERT_TRUE(d.grid[0][3] == &creature1);
}

/* Make sure turn variable is being incremented */
TEST(DarwinFixture, TestDarwin12) {
  Darwin d(2,2);
  ASSERT_TRUE(d.turn == 0);
  d.simulate();
  ASSERT_TRUE(d.turn == 1);  
}

/* Make sure turn variable is being incremented with multiple turns at a time*/
TEST(DarwinFixture, TestDarwin13) {
  Darwin d(2,2);
  ASSERT_TRUE(d.turn == 0);
  d.simulate(5);
  ASSERT_TRUE(d.turn == 5);  
}

/* Make sure a creature moving down only gets one turn */
TEST(DarwinFixture, TestDarwin14) {
  Specie hopper("hopper");
  hopper.addInstruction(Instruction(HOP));
  hopper.addInstruction(Instruction(GO, 0));
  Creature creature1(&hopper, SOUTH);
  Darwin d(2,2);
  d.addCreature(&creature1, make_pair(0,0));
  ASSERT_TRUE(d.grid[0][0] == &creature1);
  ASSERT_TRUE(d.grid[1][0] == NULL);
  d.simulate();
  ASSERT_TRUE(d.grid[0][0] == NULL);
  ASSERT_TRUE(d.grid[1][0] == &creature1);
}

/* Make sure a creature moving down only gets one turn, with multiple creatures*/
TEST(DarwinFixture, TestDarwin15) {
  Specie hopper("hopper");
  hopper.addInstruction(Instruction(HOP));
  hopper.addInstruction(Instruction(GO, 0));
  Creature creature1(&hopper, SOUTH);
  Creature creature2(&hopper, SOUTH);
  Darwin d(2,2);
  d.addCreature(&creature1, make_pair(0,0)); 
  d.addCreature(&creature2, make_pair(0,1));
  ASSERT_TRUE(d.grid[0][0] == &creature1);
  ASSERT_TRUE(d.grid[1][0] == NULL);
  ASSERT_TRUE(d.grid[0][1] == &creature2);
  ASSERT_TRUE(d.grid[1][1] == NULL);
  d.simulate();
  ASSERT_TRUE(d.grid[0][0] == NULL);
  ASSERT_TRUE(d.grid[1][0] == &creature1);
  ASSERT_TRUE(d.grid[0][1] == NULL);
  ASSERT_TRUE(d.grid[1][1] == &creature2);
}

/* Simulate creature trying to hop into another creature's position*/
TEST(DarwinFixture, TestDarwin16) {
  Specie hopper("hopper");
  hopper.addInstruction(Instruction(HOP));
  hopper.addInstruction(Instruction(GO, 0));
  Specie turn("turn");
  turn.addInstruction(Instruction(LEFT));
  turn.addInstruction(Instruction(GO, 0));
  Creature creature1(&hopper, EAST);
  Creature creature2(&turn, SOUTH);
  Darwin d(2,2);
  d.addCreature(&creature1, make_pair(0,0)); 
  d.addCreature(&creature2, make_pair(0,1));
  ASSERT_TRUE(d.grid[0][0] == &creature1);
  ASSERT_TRUE(d.grid[0][1] == &creature2);
  d.simulate();
  ASSERT_TRUE(d.grid[0][0] == &creature1);
  ASSERT_TRUE(d.grid[0][1] == &creature2);
}

/* Simulate creature hop to a wall, creature should stay at the same position*/
TEST(DarwinFixture, TestDarwin17) {
  Specie hopper("hopper");
  hopper.addInstruction(Instruction(HOP));
  Creature creature1(&hopper, NORTH);
  Darwin d(2,2);
  d.addCreature(&creature1, make_pair(0,0));
  ASSERT_TRUE(d.grid[0][0] == &creature1);
  d.simulate();
  ASSERT_TRUE(d.grid[0][0] == &creature1);
}


