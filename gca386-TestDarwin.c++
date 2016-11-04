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

#include <sstream>  // istringtstream, ostringstream

#include <tuple>

using namespace std;

// -----------
// test Darwin
// -----------

TEST(DarwinFixture, testConstructor1) {
  try {
    Darwin x(10,10);
  }
  catch (exception &e) {
    ASSERT_EQ(true,false);
  }
}

TEST(DarwinFixture, testConstructor2) {
  try {
    Darwin x;
  }
  catch (exception &e) {
    ASSERT_EQ(true,false);
  }
}

//Test isEmpty method
TEST(DarwinFixture, testIsEmpty1) {
  Darwin x(3,3);
  ASSERT_TRUE(x.isEmpty(0,0));
}

TEST(DarwinFixture, testIsEmpty2) {
  Darwin x(3,3);
  ASSERT_FALSE(x.isEmpty(4, 3));
}

TEST(DarwinFixture, testIsEmpty3) {
   Darwin x(3, 3);
   Species s("test");
   Creature c(&s, 0);
   x.addCreature(&c, 0, 0);
   ASSERT_FALSE(x.isEmpty(0, 0));
}

//Test isWall method
TEST(DarwinFixture, testIsWall1) {
  Darwin x(3, 3);
  ASSERT_TRUE(x.isWall(2, 3));
}

TEST(DarwinFixture, testIsWall2) {
  Darwin x(3, 3);
  ASSERT_FALSE(x.isWall(2,2));
}

TEST(DarwinFixture, testIsWall3) {
  Darwin x(3, 3);
  Species s("test");
  Creature c(&s, 0);
  x.addCreature(&c, 0, 0);
  ASSERT_FALSE(x.isWall(0, 0));
}

//Test isEnemy method
TEST(DarwinFixture, testIsEnemy1) {
  Darwin x(3, 3);
  Species s("test");
  Creature c(&s, 0);
  ASSERT_FALSE(x.isEnemy(1, 1, &c));
}

TEST(DarwinFixture, testIsEnemy2) {
  Darwin x(3, 3);
  Species s("test");
  Creature c(&s, 0);
  ASSERT_FALSE(x.isEnemy(4, 4, &c));
}

TEST(DarwinFixture, testIsEnemy3) {
  Darwin x(3, 3);
  Species s("test");
  Creature c1(&s, 0);
  Creature c2(&s, 1);
  x.addCreature(&c1, 1, 1);
  ASSERT_FALSE(x.isEnemy(1, 1, &c2));
}

TEST(DarwinFixture, testIsEnemy4) {
  Darwin x(3, 3);
  Species s1("test1");
  Species s2("test2");
  Creature c1(&s1, 0);
  Creature c2(&s2, 1);
  x.addCreature(&c1, 1, 1);
  ASSERT_TRUE(x.isEnemy(1, 1, &c2));
}

//Test newLoc method in all 4 directions
TEST(DarwinFixture, testNewLoc1) {
  Darwin x(3, 3);
  //West
  tuple<int, int> loc = x.newLoc(1, 1, 0);
  ASSERT_EQ(get<0>(loc), 1);
  ASSERT_EQ(get<1>(loc), 0);
}

TEST(DarwinFixture, testNewLoc2) {
  Darwin x(3, 3);
  //North
  tuple<int, int> loc = x.newLoc(1, 1, 1);
  ASSERT_EQ(get<0>(loc), 0);
  ASSERT_EQ(get<1>(loc), 1);
}

TEST(DarwinFixture, testNewLoc3) {
  Darwin x(3, 3);
  //East
  tuple<int, int> loc = x.newLoc(1, 1, 2);
  ASSERT_EQ(get<0>(loc), 1);
  ASSERT_EQ(get<1>(loc), 2);
}

TEST(DarwinFixture, testNewLoc4) {
  Darwin x(3, 3);
  //South
  tuple<int, int> loc = x.newLoc(1, 1, 3);
  ASSERT_EQ(get<0>(loc), 2);
  ASSERT_EQ(get<1>(loc), 1);
}

//Test Darwin's printGrid method
TEST(DarwinFixture, testPrintGrid1) {
  Darwin x;
  try {
    x.printGrid(2);
  }
  catch (exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(DarwinFixture, testPrintGrid2) {
  Darwin x(3, 3);
  try {
    x.printGrid(2);
  }
  catch (exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(DarwinFixture, testPrintGrid3) {
  Darwin x(3, 3);
  Species s("test1");
  Creature c(&s, 0);
  x.addCreature(&c, 1, 1);
  try {
    x.printGrid(2);
  }
  catch (exception &e) {
    ASSERT_EQ(true, false);
  }
}

//Test addCreature method
TEST(DarwinFixture, testAddCreature1) {
  Darwin x(3, 3);
  Species s("test");
  Creature c(&s, 0);
  try {
    x.addCreature(&c, 1, 1);
  }
  catch (exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(DarwinFixture, testAddCreature2) {
  Darwin x(3, 3);
  Species s("test");
  Creature c(&s, 0);
  ASSERT_THROW(x.addCreature(&c, 3, 3), invalid_argument);
}

TEST(DarwinFixture, testAddCreature3) {
  Darwin x(3, 3);
  Species s("test");
  Creature c1(&s, 0);
  Creature c2(&s, 0);
  x.addCreature(&c1, 1, 1);
  ASSERT_THROW(x.addCreature(&c2, 1, 1), invalid_argument);
}

TEST(DarwinFixture, testAddCreature4) {
  Darwin x(3, 3);
  Species s1("test1");
  Species s2("test2");
  Creature c1(&s1, 0);
  Creature c2(&s2, 0);
  x.addCreature(&c1, 1, 1);
  ASSERT_THROW(x.addCreature(&c2, 1, 1), invalid_argument);
}

//Test giveturn method

//Test left instruction
TEST(DarwinFixture, testGiveTurn1) {
  Darwin x(3, 3);
  Species food = Species("f");
  food.addInstruction("left");
  food.addInstruction("go", 0);
  Creature c(&food, 0);
  x.addCreature(&c, 1, 1);
  int pc = c._programCounter;
  ASSERT_TRUE(pc == c._programCounter);
  x.giveTurn(&c, 1, 1);
  ASSERT_FALSE(pc == c._programCounter);
}

//Test go instruction
TEST(DarwinFixture, testGiveTurn2) {
  Darwin x(3, 3);
  Species food = Species("f");
  food.addInstruction("go", 1);
  food.addInstruction("left");
  Creature c(&food, 0);
  x.addCreature(&c, 1, 1);
  x.giveTurn(&c, 1, 1);
  ASSERT_EQ(2, c._programCounter);
}

//Test right instruction
TEST(DarwinFixture, testGiveTurn3) {
  Darwin x(3, 3);
  Species food = Species("f");
  food.addInstruction("right");
  food.addInstruction("go", 0);
  Creature c(&food, 0);
  x.addCreature(&c, 1, 1);
  int pc = c._programCounter;
  ASSERT_TRUE(pc == c._programCounter);
  x.giveTurn(&c, 1, 1);
  ASSERT_FALSE(pc == c._programCounter);
}

//Test hop instruction
TEST(DarwinFixture, testGiveTurn4) {
  Darwin x(3, 3);
  Species food = Species("f");
  food.addInstruction("hop");
  food.addInstruction("go", 0);
  Creature c(&food, 0);
  x.addCreature(&c, 1, 1);
  int pc = c._programCounter;
  ASSERT_TRUE(pc == c._programCounter);
  x.giveTurn(&c, 1, 1);
  ASSERT_FALSE(pc == c._programCounter);
}

//Test infect instruction with nothing to infect
TEST(DarwinFixture, testGiveTurn5) {
  Darwin x(3, 3);
  Species food = Species("f");
  food.addInstruction("infect");
  food.addInstruction("go", 0);
  Creature c(&food, 0);
  x.addCreature(&c, 1, 1);
  int pc = c._programCounter;
  ASSERT_TRUE(pc == c._programCounter);
  x.giveTurn(&c, 1, 1);
  ASSERT_FALSE(pc == c._programCounter);
}

//Test infect instruction with something to infect
TEST(DarwinFixture, testGiveTurn6) {
  Darwin x(3, 3);
  Species food = Species("f");
  food.addInstruction("infect");
  food.addInstruction("go", 1);
  Species s = Species("s");
  Creature c1(&food, 0);
  Creature c2(&s, 0);
  x.addCreature(&c1, 1, 1);
  x.addCreature(&c2, 0, 1);
  int pc = c1._programCounter;
  ASSERT_TRUE(pc == c1._programCounter);
  x.giveTurn(&c1, 1, 1);
  ASSERT_FALSE(pc == c1._programCounter);
}

//Test if_empty instruction
TEST(DarwinFixture, testGiveTurn7) {
  Darwin x(3, 3);
  Species food = Species("f");
  food.addInstruction("if_empty", 1);
  food.addInstruction("left");
  Creature c(&food, 0);
  x.addCreature(&c, 1, 1);
  x.giveTurn(&c, 1, 1);
  ASSERT_EQ(2, c._programCounter);
}

//Test if_wall instruction
TEST(DarwinFixture, testGiveTurn8) {
  Darwin x(3, 3);
  Species food = Species("f");
  food.addInstruction("if_wall", 1);
  food.addInstruction("left");
  Creature c(&food, 0);
  x.addCreature(&c, 1, 1);
  x.giveTurn(&c, 1, 1);
  ASSERT_EQ(2, c._programCounter);
}

//Test if_enemy instruction
TEST(DarwinFixture, testGiveTurn9) {
  Darwin x(3, 3);
  Species food = Species("f");
  food.addInstruction("if_enemy", 1);
  food.addInstruction("left");
  Creature c(&food, 0);
  x.addCreature(&c, 1, 1);
  x.giveTurn(&c, 1, 1);
  ASSERT_EQ(2, c._programCounter);
}

TEST(DarwinFixture, testExecute) {
  Darwin x(3, 3);
  ASSERT_EQ(x._turn, 0);
  x.execute(1000);
  ASSERT_EQ(x._turn, 1001);
}

// -----------
// test Species
// -----------

//Test addInstruction method
TEST(SpeciesFixture, testInstruction) {
  Species x("test");
  x.addInstruction("testInstruction");
  ASSERT_EQ("testInstruction", get<0>(x.getInstruction(0)));
}

TEST(SpeciesFixture, testInstruction2) {
  Species x("test");
  x.addInstruction("testInstruction");
  ASSERT_EQ(-1, get<1>(x.getInstruction(0)));
}

TEST(SpeciesFixture, testInstruction3) {
  Species x("test");
  x.addInstruction("testInstruction", 3);
  ASSERT_EQ(3, get<1>(x.getInstruction(0)));
}

// Test that initial instructions vector size is 0
TEST(SpeciesFixture, addInstruction) {
  Species x("test");
  ASSERT_EQ(x._instructions.size(), 0);
}

// Test that addInstruction is incrementing the size of instruction vector
TEST(SpeciesFixture, addInstruction2) {
  Species x("test");
  ASSERT_EQ(x._instructions.size(), 0);
  x.addInstruction("hop");
  ASSERT_EQ(x._instructions.size(), 1);
}

TEST(SpeciesFixture, addInstruction3) {
  Species x("test");
  ASSERT_EQ(x._instructions.size(), 0);
  x.addInstruction("hop");
  ASSERT_EQ(get<0>(x._instructions[0]), "hop");
}

TEST(SpeciesFixture, addInstruction4) {
  Species x("test");
  ASSERT_EQ(x._instructions.size(), 0);
  x.addInstruction("hop");
  ASSERT_EQ(get<1>(x._instructions[0]), -1);
}

// Test print method
TEST(SpeciesFixture, print) {
  Species x("test");
  try {
    x.print();
  } catch (exception& e) {
    ASSERT_EQ(true, false);
  }
}

// Test constructor
TEST(SpeciesFixture, constructor) {
  Species x("test");
  ASSERT_EQ(x._identifier, "test");
}

TEST(SpeciesFixture, constructor2) {
  Species x("test");
  ASSERT_EQ(x._instructions.empty(), true);
}

// -----------
// test Creature
// -----------

//Check that turn left from west works
TEST(CreatureFixture, testTurnLeft1) {
  Species x("test");
  //West
  Creature c(&x, 0);
  c.turnLeft();
  ASSERT_EQ(3, c._direction);
}
//Check that turn left from north works
TEST(CreatureFixture, testTurnLeft2) {
  Species x("test");
  //North
  Creature c(&x, 1);
  c.turnLeft();
  ASSERT_EQ(0, c._direction);
}
//Check that turn left from east works
TEST(CreatureFixture, testTurnLeft3) {
  Species x("test");
  //East
  Creature c(&x, 2);
  c.turnLeft();
  ASSERT_EQ(1, c._direction);
}
//Check that turn left from south works
TEST(CreatureFixture, testTurnLeft4) {
  Species x("test");
  //South
  Creature c(&x, 3);
  c.turnLeft();
  ASSERT_EQ(2, c._direction);
}

//Check that turn right from west works
TEST(CreatureFixture, testTurnRight1) {
  Species x("test");
  //West
  Creature c(&x, 0);
  c.turnRight();
  ASSERT_EQ(1, c._direction);
}
//Check that turn right from north works
TEST(CreatureFixture, testTurnRight2) {
  Species x("test");
  //North
  Creature c(&x, 1);
  c.turnRight();
  ASSERT_EQ(2, c._direction);
}
//Check that turn right from east works
TEST(CreatureFixture, testTurnRight3) {
  Species x("test");
  //East
  Creature c(&x, 2);
  c.turnRight();
  ASSERT_EQ(3, c._direction);
}
//Check that turn right from south works
TEST(CreatureFixture, testTurnRight4) {
  Species x("test");
  //South
  Creature c(&x, 3);
  c.turnRight();
  ASSERT_EQ(0, c._direction);
}

//Check signalSuccessfulUpdate(true)
TEST(CreatureFixture, testSignalSuccessfulUpdate) {
  Species x("test");
  Creature c(&x, 3);
  ASSERT_EQ(c._programCounter, 0);
  c._potentialProgramCounter = 2;
  c.signalSuccessfulUpdate(true);
  ASSERT_EQ(c._programCounter, 2);
}

//Check signalSuccessfulUpdate(false)
TEST(CreatureFixture, testSignalSuccessfulUpdate2) {
  Species x("test");
  Creature c(&x, 3);
  ASSERT_EQ(c._programCounter, 0);
  c._potentialProgramCounter = 2;
  c.signalSuccessfulUpdate(false);
  ASSERT_EQ(c._programCounter, 1);
}

//Check that not calling signalSuccessfulUpdate doesn't affect program counters
TEST(CreatureFixture, testSignalSuccessfulUpdate3) {
  Species x("test");
  Creature c(&x, 3);
  ASSERT_EQ(c._programCounter, 0);
  c._potentialProgramCounter = 2;
  ASSERT_EQ(c._programCounter, 0);
}

//Test constructor
TEST(CreatureFixture, constructor) {
  Species x("test");
  Creature c(&x, 3);
  ASSERT_EQ(&x, c._species);
}

TEST(CreatureFixture, constructor2) {
  Species x("test");
  Creature c(&x, 3);
  ASSERT_EQ(c._direction, 3);
}

// Test that constructor initializes program counter to 0
TEST(CreatureFixture, constructor3) {
  Species x("test");
  Creature c(&x, 3);
  ASSERT_EQ(c._programCounter, 0);
}

// Test that constructor initializes potential program counter to 0
TEST(CreatureFixture, constructor4) {
  Species x("test");
  Creature c(&x, 3);
  ASSERT_EQ(c._potentialProgramCounter, 0);
}

//Check turn right then left
TEST(CreatureFixture, testTurnRightAndLeft) {
  Species x("test");
  //South
  Creature c(&x, 3);
  c.turnRight();
  c.turnLeft();
  ASSERT_EQ(3, c._direction);
}

//Following test sameSpecies method
TEST(CreatureFixture, testSameSpecies1) {
  Species x("test");
  Creature c1(&x, 0);
  Creature c2(&x, 0);
  ASSERT_TRUE(c1.sameSpecies(&c2));
}

TEST(CreatureFixture, testSameSpecies2) {
  Species x("test");
  Creature c1(&x, 0);
  Creature c2(&x, 1);
  ASSERT_TRUE(c1.sameSpecies(&c2));
}

TEST(CreatureFixture, testSameSpecies3) {
  Species x("test");
  Species y("test");
  Creature c1(&x, 0);
  Creature c2(&y, 0);
  ASSERT_FALSE(c1.sameSpecies(&c2));
}

TEST(CreatureFixture, testSameSpecies4) {
  Species x("test1");
  Species y("test2");
  Creature c1(&x, 0);
  Creature c2(&y, 0);
  ASSERT_FALSE(c1.sameSpecies(&c2));
}

//Test Infected
TEST(CreatureFixture, testInfected1) {
  Species x("test1");
  Species y("test2");
  Creature c1(&x, 0);
  Creature c2(&y, 0);
  ASSERT_FALSE(c1.sameSpecies(&c2));
  c1.infected(&c2);
  ASSERT_TRUE(c1.sameSpecies(&c2));
}

TEST(CreatureFixture, testInfected2) {
  Species x("x");
  Species y("y");
  Creature c1(&x, 0);
  Creature c2(&y, 0);
  Creature c3(&x, 0);
  ASSERT_TRUE(c1.sameSpecies(&c3));
  c2.infected(&c1);
  ASSERT_TRUE(c1.sameSpecies(&c3));
}

//Test printSpecies doesn't fail
TEST(CreatureFixture, testPrint1) {
  Species x("x");
  Creature c1(&x, 0);
  try {
    c1.printSpecies();
  }
  catch (exception &e){
    ASSERT_EQ(true, false);
  }
}

// Test returnInstructionInfo descriptor with action instruction
TEST(CreatureFixture, testReturnInstructionInfo) {
  Species x("x");
  x.addInstruction("hop");
  Creature c(&x, 0);
  ASSERT_EQ(c._programCounter, 0);
  tuple<string, int> instruction = get<0>(c.returnInstructionInfo());
  string instr_descriptor = get<0>(instruction);
  ASSERT_EQ(instr_descriptor, "hop");
}

// Test returnInstructionInfo n value with action instruction
TEST(CreatureFixture, testReturnInstructionInfo2) {
  Species x("x");
  x.addInstruction("hop");
  Creature c(&x, 0);
  ASSERT_EQ(c._programCounter, 0);
  tuple<string, int> instruction = get<0>(c.returnInstructionInfo());
  int instr_n = get<1>(instruction);
  ASSERT_EQ(instr_n, -1);
}

// Test returnInstructionInfo descriptor with action instruction
TEST(CreatureFixture, testReturnInstructionInfo3) {
  Species x("x");
  x.addInstruction("go", 0);
  Creature c(&x, 0);
  ASSERT_EQ(c._programCounter, 0);
  tuple<string, int> instruction = get<0>(c.returnInstructionInfo());
  string instr_descriptor = get<0>(instruction);
  ASSERT_EQ(instr_descriptor, "go");
}

// Test returnInstructionInfo n value with action instruction
TEST(CreatureFixture, testReturnInstructionInfo4) {
  Species x("x");
  x.addInstruction("go", 0);
  Creature c(&x, 0);
  ASSERT_EQ(c._programCounter, 0);
  tuple<string, int> instruction = get<0>(c.returnInstructionInfo());
  int instr_n = get<1>(instruction);
  ASSERT_EQ(instr_n, 0);
}
