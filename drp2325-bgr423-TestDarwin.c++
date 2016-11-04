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
#include <iostream>
#include <utility>
#include <sstream>
#include <string>

using namespace std;

// ----
// test
// ----


// =======
// Species
// =======

// Test Species - Default Constructor
TEST(SpeciesFixture, speciesDefault1) {
  try {
    Species s;
  }
  catch(exception& e) {
    ASSERT_EQ(true, false);
  }
}

TEST(SpeciesFixture, speciesDefault2) {
  Species s;
  ASSERT_TRUE(s.program.size() == 0);
}

TEST(SpeciesFixture, speciesDefault3) {
  Species s;
  Species t;
  ASSERT_TRUE(s.program == t.program);
  ASSERT_TRUE(&(s.program) != &(t.program));
}

// Test Species - addInstruction
TEST(SpeciesFixture, addInstruction1) {
  Species s;

  try {
    s.addInstruction(HOP);
  }
  catch(exception& e) {
    ASSERT_EQ(true, false);
  }
}

TEST(SpeciesFixture, addInstruction2) {
  Species s;

  try {
    s.addInstruction(GO, 0);
  }
  catch(exception& e) {
    ASSERT_EQ(true, false);
  }
}

TEST(SpeciesFixture, addInstruction3) {
  Species s;
  ASSERT_TRUE(s.program.size() == 0);

  s.addInstruction(HOP);
  ASSERT_TRUE(s.program.size() == 1);
  ASSERT_TRUE(s.program.at(0).first == HOP);
  ASSERT_TRUE(s.program.at(0).second == -1);
}

TEST(SpeciesFixture, addInstruction4) {
  Species s;
  ASSERT_TRUE(s.program.size() == 0);

  s.addInstruction(GO, 0);
  ASSERT_TRUE(s.program.size() == 1);
  ASSERT_TRUE(s.program.at(0).first == GO);
  ASSERT_TRUE(s.program.at(0).second == 0);
}

TEST(SpeciesFixture, addInstruction5) {
  Species s;
  Species t;
  ASSERT_TRUE(s.program.size() == 0);
  ASSERT_TRUE(t.program.size() == 0);

  s.addInstruction(HOP);
  ASSERT_TRUE(s.program.size() == 1);
  ASSERT_TRUE(t.program.size() == 0);

  t.addInstruction(LEFT);
  ASSERT_TRUE(s.program.size() == 1);
  ASSERT_TRUE(t.program.size() == 1);
  ASSERT_TRUE(&(s.program) != &(t.program));
}

TEST(SpeciesFixture, addInstruction6) {
  Species s;
  Species t;
  ASSERT_TRUE(s.program.size() == 0);
  ASSERT_TRUE(t.program.size() == 0);

  s.addInstruction(HOP);
  ASSERT_TRUE(s.program.size() == 1);
  ASSERT_TRUE(t.program.size() == 0);

  s.addInstruction(GO, 0);
  ASSERT_TRUE(s.program.size() == 2);
  ASSERT_TRUE(t.program.size() == 0);

  t.addInstruction(LEFT);
  t.addInstruction(GO, 0);
  ASSERT_TRUE(s.program.size() == 2);
  ASSERT_TRUE(t.program.size() == 2);
  ASSERT_TRUE(&(s.program) != &(t.program));
}

// Test Species - executeLine
TEST(SpeciesFixture, executeLine1) {
  try {
    Species s;
    Creature c;
    Darwin x(1,1);

    s.executeLine(&x, -1, &c);
  }
  catch(exception& e) {
    ASSERT_EQ(true, true);
  }
}

TEST(SpeciesFixture, executeLine2) {
  try {
    Species s;
    Creature c;
    Darwin x(1,1);

    s.executeLine(&x, 100, &c);
  }
  catch(exception& e) {
    ASSERT_EQ(true, true);
  }
}

TEST(SpeciesFixture, executeLine3) {
  Species s;
  s.addInstruction(LEFT);
  s.addInstruction(GO, 0);
  ASSERT_TRUE(s.program.size() == 2);

  Creature c(s, NORTH, 'c');
  Darwin x(1,1);
  x.addCreature(c, 0, 0);

  s.executeLine(&x, 0, &c);

  ASSERT_TRUE(s.program.size() == 2);
}



// ========
// Creature
// ========

// Test Creature - default Constructor
TEST(CreatureFixture, creatureDefault1) {
  try {
    Creature c;
  }
  catch(exception& e) {
    ASSERT_EQ(true, false);
  }
}

TEST(CreatureFixture, creatureDefault2) {
  Creature c;

  ASSERT_TRUE(c.spec == nullptr);
  ASSERT_TRUE(c.counter == -1);
  ASSERT_TRUE(c.direction == '\0');
  ASSERT_TRUE(c.token == '.');
}

TEST(CreatureFixture,creatureDefault3) {
  Creature c;
  Creature t;

  ASSERT_TRUE(c.spec == nullptr);
  ASSERT_TRUE(c.counter == -1);
  ASSERT_TRUE(c.direction == '\0');
  ASSERT_TRUE(c.token == '.');
  ASSERT_TRUE(t.spec == nullptr);
  ASSERT_TRUE(t.counter == -1);
  ASSERT_TRUE(t.direction == '\0');
  ASSERT_TRUE(t.token == '.');
  ASSERT_TRUE(&c != &t);
}

// Test Creature - object Constructor
TEST(CreatureFixture, objectConstructor1) {
  try {
    Species s;
    Creature c(s, NORTH, 'c');
  }
  catch(exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(CreatureFixture, objectConstructor2) {
  Species s;
  Creature c(s, NORTH, 'c');

  ASSERT_TRUE(c.spec == &s);
  ASSERT_TRUE(c.counter == 0);
  ASSERT_TRUE(c.direction == NORTH);
  ASSERT_TRUE(c.token == 'c');
}

TEST(CreatureFixture,objectConstructor3) {
  Species s;
  Creature c(s, NORTH, 'c');
  Creature t(s, NORTH, 'c');

  ASSERT_TRUE(c.spec == &s);
  ASSERT_TRUE(c.counter == 0);
  ASSERT_TRUE(c.direction == NORTH);
  ASSERT_TRUE(c.token == 'c');
  ASSERT_TRUE(t.spec == &s);
  ASSERT_TRUE(t.counter == 0);
  ASSERT_TRUE(t.direction == NORTH);
  ASSERT_TRUE(t.token == 'c');
  ASSERT_TRUE(&c != &t);
}

// Test Creature - performAction
TEST(CreatureFixture, performAction1) {
  try {
    Creature c;
    Darwin x(1,1);

    c.performAction(&x);
  }
  catch(exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(CreatureFixture, performAction2) {
  try {
    Species s;
    s.addInstruction(HOP);
    s.addInstruction(GO, 0);

    Creature c(s, NORTH, 'c');
    Darwin x(1,1);
    x.addCreature(c, 0, 0);

    c.performAction(&x);
  }
  catch(exception& e) {
    ASSERT_EQ(true, false);
  }
}

TEST(CreatureFixture, performAction3) {
  Creature c;
  Darwin x(1,1);
  x.addCreature(c, 0, 0);

  ASSERT_TRUE(c.spec == nullptr);
  ASSERT_TRUE(c.counter == -1);
  ASSERT_TRUE(c.direction == '\0');
  ASSERT_TRUE(c.token == '.');

  c.performAction(&x);

  ASSERT_TRUE(c.spec == nullptr);
  ASSERT_TRUE(c.counter == -1);
  ASSERT_TRUE(c.direction == '\0');
  ASSERT_TRUE(c.token == '.');
}

// Test Creature - valid
TEST(CreatureFixture, valid1) {
  try {
    Creature c;

    c.valid();
  }
  catch(exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(CreatureFixture, valid2) {
  Creature c;
  ASSERT_EQ(false, c.valid());
}

TEST(CreatureFixture, valid3) {
  Species s;
  Creature c(s, NORTH, 'c');

  ASSERT_EQ(true, c.valid());
}

// Test Creature - go
TEST(CreatureFixture, go1) {
  try {
    int x = 0;

    Creature c;
    c.go(x);
  }
  catch(exception& e) {
    ASSERT_EQ(true, true);
  }
}

TEST(CreatureFixture, go2) {
  try {
    int x = -1;

    Species s;
    Creature c(s, NORTH, 'c');
    c.go(x);
  }
  catch(exception& e) {
    ASSERT_EQ(true, true);
  }
}

TEST(CreatureFixture, go3) {
  int x = 1;

  Species s;
  s.addInstruction(HOP);
  s.addInstruction(GO, 0);

  Creature c(s, NORTH, 'c');
  ASSERT_TRUE(c.counter == 0);

  c.go(x);
  ASSERT_TRUE(c.counter == 1);
}

// Test Creature - turnRight
TEST(CreatureFixture, turnRight1) {
  try {
    int x = 0;
    Creature c;
    c.turnRight(x);
  }
  catch(exception& e) {
    ASSERT_EQ(true, true);
  }
}

TEST(CreatureFixture, turnRight2) {
  try {
    int x = 0;
    Species s;
    Creature c(s, NORTH, 'c');
    c.turnRight(x);
  }
  catch(exception& e) {
    ASSERT_EQ(true, false);
  }
}

TEST(CreatureFixture, turnRight3) {
  int x = 0;
  Species s;
  Creature c(s, NORTH, 'c');
  ASSERT_TRUE(c.direction == NORTH);

  c.turnRight(x);
  ASSERT_TRUE(c.direction == EAST);
}

// Test Creature - turnLeft
TEST(CreatureFixture, turnLeft1) {
  try {
    int x = 0;
    Creature c;
    c.turnLeft(x);
  }
  catch(exception& e) {
    ASSERT_EQ(true, true);
  }
}

TEST(CreatureFixture, turnLeft2) {
  try {
    int x = 0;
    Species s;
    Creature c(s, NORTH, 'c');
    c.turnLeft(x);
  }
  catch(exception& e) {
    ASSERT_EQ(true, false);
  }
}

TEST(CreatureFixture, turnLeft3) {
  int x = 0;
  Species s;
  Creature c(s, NORTH, 'c');
  ASSERT_TRUE(c.direction == NORTH);

  c.turnLeft(x);
  ASSERT_TRUE(c.direction == WEST);
}

// Test Creature - ifEnemy
TEST(CreatureFixture, ifEnemy1) {
  try {
    Creature c;
    Creature t;
    c.ifEnemy(&t);
  }
  catch(exception& e) {
    ASSERT_EQ(true, true);
  }
}

TEST(CreatureFixture, ifEnemy2) {
  try {
    Species s;
    Creature c1(s, NORTH, 'c');
    Creature c2(s, EAST, 'c');
    c1.ifEnemy(&c2);
  }
  catch(exception& e) {
    ASSERT_EQ(true, false);
  }
}

TEST(CreatureFixture, ifEnemy3) {
  Species s;
  Species t;
  Creature c1(s, NORTH, 'c');
  Creature c2(s, EAST, 'c');
  Creature d(t, NORTH, 'd');

  ASSERT_EQ(false, c1.ifEnemy(&c2));
  ASSERT_EQ(true, c1.ifEnemy(&d));
}

// Test Creature - inFront
TEST(CreatureFixture, inFront1) {
  try {
    Creature c;
    c.inFront(0, 0);
  }
  catch(exception &e) {
    ASSERT_EQ(true, true);
  }
}

TEST(CreatureFixture, inFront2) {
  try {
    Species s;
    Creature c(s, NORTH, 'c');
    c.inFront(0, 0);
  }
  catch(exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(CreatureFixture, inFront3) {
  Species s;
  Creature c(s, EAST, 'c');
  std::pair<int, int> p = c.inFront(0,0);
  int x = p.first;
  int y = p.second;

  ASSERT_EQ(x, 1);
  ASSERT_EQ(y, 0);
}

TEST(CreatureFixture, inFront4) {
  Species s;
  Creature c(s, NORTH, 'c');
  std::pair<int, int> p = c.inFront(0,0);
  int x = p.first;
  int y = p.second;

  ASSERT_EQ(x,  0);
  ASSERT_EQ(y, -1);
}

// Test Creature - infect
TEST(CreatureFixture, infect1) {
  try {
    int x = 0;
    Creature c;
    Creature t;

    c.infect(&t, x);
  }
  catch(exception &e) {
    ASSERT_EQ(true, true);
  }
}

TEST(CreatureFixture, infect2) {
  try {
    int x = 0;
    Species s;
    Creature c1(s, NORTH, 'c');
    Creature c2(s, EAST, 'c');

    c1.infect(&c2, x);
  }
  catch(exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(CreatureFixture, infect3) {
  int x = 0;
  Species s;
  Species t;
  Creature c(s, NORTH, 'c');
  Creature d(t, EAST, 'd');

  ASSERT_EQ(d.spec, &t);
  ASSERT_EQ(d.counter, 0);
  ASSERT_EQ(d.direction, EAST);
  ASSERT_EQ(d.token, 'd');

  c.infect(&d, x);

  ASSERT_EQ(d.spec, &s);
  ASSERT_EQ(d.counter, 0);
  ASSERT_EQ(d.direction, EAST);
  ASSERT_EQ(d.token, 'c');
}

// Test Creature - printSpecies
TEST(CreatureFixture, printSpecies1) {
  Creature c;
  std::ostringstream oss;
  std::string str;

  c.printSpecies(oss);
  str = oss.str();

  ASSERT_EQ(str, ".");
}

TEST(CreatureFixture, printSpecies2) {
  Species s;
  Creature c(s, NORTH, 'c');
  std::ostringstream oss;
  std::string str;

  c.printSpecies(oss);
  str = oss.str();

  ASSERT_EQ(str, "c");
}


// ======
// Darwin
// ======

// Test Darwin - single int Constructor
TEST(DarwinFixture, singleConstructor1) {
  try {
    Darwin x(2);
  }
  catch(exception& e) {
    ASSERT_EQ(true, false);
  }
}

TEST(DarwinFixture, singleConstructor2) {
  Darwin x(2);

  ASSERT_EQ(x.D_y, 2);
  ASSERT_EQ(x.D_x, 2);
  ASSERT_EQ(x.C_y, 0);
  ASSERT_EQ(x.C_x, 0);
  ASSERT_EQ(x.grid.size(), 4);
  ASSERT_EQ(x.trackTurn.size(), 4);
}

TEST(DarwinFixture, singleConstructor3) {
  Darwin x(2);
  Darwin y(2);

  ASSERT_EQ(x.D_y, 2);
  ASSERT_EQ(x.D_x, 2);
  ASSERT_EQ(x.C_y, 0);
  ASSERT_EQ(x.C_x, 0);
  ASSERT_EQ(x.grid.size(), 4);
  ASSERT_EQ(x.trackTurn.size(), 4);

  ASSERT_EQ(y.D_y, 2);
  ASSERT_EQ(y.D_x, 2);
  ASSERT_EQ(y.C_y, 0);
  ASSERT_EQ(y.C_x, 0);
  ASSERT_EQ(y.grid.size(), 4);
  ASSERT_EQ(y.trackTurn.size(), 4);

  ASSERT_TRUE(&x != &y);
}

// Test Darwin - two int Constructor
TEST(DarwinFixture, twoIntConstructor1) {
  try {
    Darwin x(1, 2);
  }
  catch(exception& e) {
    ASSERT_EQ(true, false);
  }
}

TEST(DarwinFixture, twoIntConstructor2) {
  Darwin x(1, 2);

  ASSERT_EQ(x.D_y, 1);
  ASSERT_EQ(x.D_x, 2);
  ASSERT_EQ(x.C_y, 0);
  ASSERT_EQ(x.C_x, 0);
  ASSERT_EQ(x.grid.size(), 2);
  ASSERT_EQ(x.trackTurn.size(), 2);
}

TEST(DarwinFixture, twoIntConstructor3) {
  Darwin x(1, 2);
  Darwin y(1, 2);

  ASSERT_EQ(x.D_y, 1);
  ASSERT_EQ(x.D_x, 2);
  ASSERT_EQ(x.C_y, 0);
  ASSERT_EQ(x.C_x, 0);
  ASSERT_EQ(x.grid.size(), 2);
  ASSERT_EQ(x.trackTurn.size(), 2);

  ASSERT_EQ(y.D_y, 1);
  ASSERT_EQ(y.D_x, 2);
  ASSERT_EQ(y.C_y, 0);
  ASSERT_EQ(y.C_x, 0);
  ASSERT_EQ(y.grid.size(), 2);
  ASSERT_EQ(y.trackTurn.size(), 2);

  ASSERT_TRUE(&x != &y);
}

// Test Darwin - addCreature
TEST(DarwinFixture, addCreature1) {
  try {
    Creature c;
    Darwin x(1,1);
    x.addCreature(c, 0, 0);
  }
  catch(exception& e) {
    ASSERT_EQ(true, false);
  }
}

TEST(DarwinFixture, addCreature2) {
  try {
    Creature c;
    Darwin x(1,1);
    x.addCreature(c, -1, 5);
  }
  catch(exception& e) {
    ASSERT_EQ(true, true);
  }
}

TEST(DarwinFixture, addCreature3) {
  Species s;
  Creature c(s, NORTH, 'c');
  Darwin x(2,2);

  Creature before_0_0 = x.grid.at(0);
  Creature before_0_1 = x.grid.at(1);

  ASSERT_EQ(before_0_0.spec, before_0_1.spec);
  ASSERT_EQ(before_0_0.direction, before_0_1.direction);
  ASSERT_EQ(before_0_0.token, before_0_1.token);

  x.addCreature(c, 0, 1);

  Creature after_0_0 = x.grid.at(0);
  Creature after_0_1 = x.grid.at(1);

  ASSERT_TRUE(after_0_0.spec != after_0_1.spec);
  ASSERT_TRUE(after_0_0.direction != after_0_1.direction);
  ASSERT_TRUE(after_0_0.token != after_0_1.token);
  ASSERT_EQ(after_0_1.spec, &s);
  ASSERT_EQ(after_0_1.direction, NORTH);
  ASSERT_EQ(after_0_1.token, 'c');
}

// Test Darwin - hop
TEST(DarwinFixture, hop1) {
  try {
    int pc = 0;
    Species s;
    Creature c(s, EAST, 'c');
    Darwin x(2,2);

    x.addCreature(c, 0, 0);
    x.hop(pc);
  }
  catch(exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(DarwinFixture, hop2) {
  int pc = 0;
  Species s;
  Creature c(s, EAST, 'c');
  Darwin x(2,2);

  x.addCreature(c, 0, 0);

  Creature before_0_0 = x.grid.at(0);
  Creature before_0_1 = x.grid.at(1);

  ASSERT_EQ(before_0_0.spec, &s);
  ASSERT_EQ(before_0_1.spec, nullptr);
  ASSERT_EQ(before_0_0.direction, EAST);
  ASSERT_EQ(before_0_1.direction, '\0');
  ASSERT_EQ(before_0_0.token, 'c');
  ASSERT_EQ(before_0_1.token, '.');

  x.hop(pc);

  Creature after_0_0 = x.grid.at(0);
  Creature after_0_1 = x.grid.at(1);

  ASSERT_EQ(after_0_0.spec, nullptr);
  ASSERT_EQ(after_0_1.spec, &s);
  ASSERT_EQ(after_0_0.direction, '\0');
  ASSERT_EQ(after_0_1.direction, EAST);
  ASSERT_EQ(after_0_0.token, '.');
  ASSERT_EQ(after_0_1.token, 'c');  
}

TEST(DarwinFixture, hop3) {
  int pc = 0;
  Species s;
  Creature c(s, NORTH, 'c');
  Darwin x(2,2);

  x.addCreature(c, 0, 0);

  Creature before_0_0 = x.grid.at(0);

  ASSERT_EQ(before_0_0.spec, &s);
  ASSERT_EQ(before_0_0.direction, NORTH);
  ASSERT_EQ(before_0_0.token, 'c');

  x.hop(pc);

  Creature after_0_0 = x.grid.at(0);

  ASSERT_EQ(after_0_0.spec, &s);
  ASSERT_EQ(after_0_0.direction, NORTH);
  ASSERT_EQ(after_0_0.token, 'c');  
}

TEST(DarwinFixture, hop4) {
  int pc = 0;
  Species s;
  Species t;
  Creature c(s, EAST, 'c');
  Creature d(t, SOUTH, 'd');
  Darwin x(2,2);

  x.addCreature(c, 0, 0);
  x.addCreature(d, 0, 1);

  Creature before_0_0 = x.grid.at(0);
  Creature before_0_1 = x.grid.at(1);

  ASSERT_EQ(before_0_0.spec, &s);
  ASSERT_EQ(before_0_1.spec, &t);
  ASSERT_EQ(before_0_0.direction, EAST);
  ASSERT_EQ(before_0_1.direction, SOUTH);
  ASSERT_EQ(before_0_0.token, 'c');
  ASSERT_EQ(before_0_1.token, 'd');

  x.hop(pc);

  Creature after_0_0 = x.grid.at(0);
  Creature after_0_1 = x.grid.at(1);

  ASSERT_EQ(after_0_0.spec, &s);
  ASSERT_EQ(after_0_1.spec, &t);
  ASSERT_EQ(after_0_0.direction, EAST);
  ASSERT_EQ(after_0_1.direction, SOUTH);
  ASSERT_EQ(after_0_0.token, 'c');
  ASSERT_EQ(after_0_1.token, 'd');
}

// Test Darwin - infect
TEST(DarwinFixture, infect1) {
  try {
    int pc = 0;
    Species s;
    Creature c(s, EAST, 'c');
    Darwin x(2,2);

    x.addCreature(c, 0, 0);
    x.infect(pc);
  }
  catch(exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(DarwinFixture, infect2) {
  int pc = 0;
  Species s;
  Creature c(s, EAST, 'c');
  Darwin x(2,2);

  x.addCreature(c, 0, 0);

  Creature before_0_0 = x.grid.at(0);
  Creature before_0_1 = x.grid.at(1);

  ASSERT_EQ(before_0_0.spec, &s);
  ASSERT_EQ(before_0_1.spec, nullptr);
  ASSERT_EQ(before_0_0.direction, EAST);
  ASSERT_EQ(before_0_1.direction, '\0');
  ASSERT_EQ(before_0_0.token, 'c');
  ASSERT_EQ(before_0_1.token, '.');

  x.infect(pc);

  Creature after_0_0 = x.grid.at(0);
  Creature after_0_1 = x.grid.at(1);

  ASSERT_EQ(after_0_0.spec, &s);
  ASSERT_EQ(after_0_1.spec, nullptr);
  ASSERT_EQ(after_0_0.direction, EAST);
  ASSERT_EQ(after_0_1.direction, '\0');
  ASSERT_EQ(after_0_0.token, 'c');
  ASSERT_EQ(after_0_1.token, '.');
}

TEST(DarwinFixture, infect3) {
  int pc = 0;
  Species s;
  Species t;
  Creature c(s, EAST, 'c');
  Creature d(t, NORTH, 'd');
  Darwin x(2,2);

  x.addCreature(c, 0, 0);
  x.addCreature(d, 0, 1);

  Creature before_0_0 = x.grid.at(0);
  Creature before_0_1 = x.grid.at(1);

  ASSERT_EQ(before_0_0.spec, &s);
  ASSERT_EQ(before_0_1.spec, &t);
  ASSERT_EQ(before_0_0.direction, EAST);
  ASSERT_EQ(before_0_1.direction, NORTH);
  ASSERT_EQ(before_0_0.token, 'c');
  ASSERT_EQ(before_0_1.token, 'd');

  x.infect(pc);

  Creature after_0_0 = x.grid.at(0);
  Creature after_0_1 = x.grid.at(1);

  ASSERT_EQ(after_0_0.spec, &s);
  ASSERT_EQ(after_0_1.spec, &s);
  ASSERT_EQ(after_0_0.direction, EAST);
  ASSERT_EQ(after_0_1.direction, NORTH);
  ASSERT_EQ(after_0_0.token, 'c');
  ASSERT_EQ(after_0_1.token, 'c');
  ASSERT_EQ(after_0_1.counter, 0);
  ASSERT_TRUE(after_0_0.counter != 0);
}

TEST(DarwinFixture, infect4) {
  int pc = 0;
  Species s;
  Creature c(s, NORTH, 'c');
  Darwin x(2,2);

  x.addCreature(c, 0, 0);

  Creature before_0_0 = x.grid.at(0);

  ASSERT_EQ(before_0_0.spec, &s);
  ASSERT_EQ(before_0_0.direction, NORTH);
  ASSERT_EQ(before_0_0.token, 'c');

  x.infect(pc);

  Creature after_0_0 = x.grid.at(0);

  ASSERT_EQ(after_0_0.spec, &s);
  ASSERT_EQ(after_0_0.direction, NORTH);
  ASSERT_EQ(after_0_0.token, 'c');  
}

TEST(DarwinFixture, infect5) {
  int pc = 0;
  Species s;
  Creature c1(s, EAST, 'c');
  Creature c2(s, SOUTH, 'c');
  Darwin x(2,2);

  x.addCreature(c1, 0, 0);
  x.addCreature(c2, 0, 1);

  Creature before_0_0 = x.grid.at(0);
  Creature before_0_1 = x.grid.at(1);

  ASSERT_EQ(before_0_0.spec, &s);
  ASSERT_EQ(before_0_1.spec, &s);
  ASSERT_EQ(before_0_0.direction, EAST);
  ASSERT_EQ(before_0_1.direction, SOUTH);
  ASSERT_EQ(before_0_0.token, 'c');
  ASSERT_EQ(before_0_1.token, 'c');

  x.infect(pc);

  Creature after_0_0 = x.grid.at(0);
  Creature after_0_1 = x.grid.at(1);

  ASSERT_EQ(after_0_0.spec, &s);
  ASSERT_EQ(after_0_1.spec, &s);
  ASSERT_EQ(after_0_0.direction, EAST);
  ASSERT_EQ(after_0_1.direction, SOUTH);
  ASSERT_EQ(after_0_0.token, 'c');
  ASSERT_EQ(after_0_1.token, 'c');
}

// Test Darwin - ifEmpty
TEST(DarwinFixture, ifEmpty1) {
  try {
    int pc = 0;
    Species s;
    Creature c(s, EAST, 'c');
    Darwin x(2,2);

    x.addCreature(c, 0, 0);
    x.ifEmpty(pc, 5);
  }
  catch(exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(DarwinFixture, ifEmpty2) {
  int pc = 0;
  int jumpCondition = 10;
  Species s;
  Creature c(s, EAST, 'c');
  Darwin x(2,2);

  x.addCreature(c, 0, 0);

  Creature before_0_0 = x.grid.at(0);

  ASSERT_EQ(before_0_0.spec, &s);
  ASSERT_EQ(before_0_0.direction, EAST);
  ASSERT_EQ(before_0_0.token, 'c');
  ASSERT_EQ(before_0_0.counter, 0);

  x.ifEmpty(pc, jumpCondition);

  Creature after_0_0 = x.grid.at(0);

  ASSERT_EQ(after_0_0.spec, &s);
  ASSERT_EQ(after_0_0.direction, EAST);
  ASSERT_EQ(after_0_0.token, 'c');
  ASSERT_EQ(after_0_0.counter, jumpCondition);
}

TEST(DarwinFixture, ifEmpty3) {
  int pc = 0;
  int jumpCondition = 10;
  Species s;
  Creature c(s, NORTH, 'c');
  Darwin x(2,2);

  x.addCreature(c, 0, 0);

  Creature before_0_0 = x.grid.at(0);

  ASSERT_EQ(before_0_0.spec, &s);
  ASSERT_EQ(before_0_0.direction, NORTH);
  ASSERT_EQ(before_0_0.token, 'c');
  ASSERT_EQ(before_0_0.counter, 0);

  x.ifEmpty(pc, jumpCondition);

  Creature after_0_0 = x.grid.at(0);

  ASSERT_EQ(after_0_0.spec, &s);
  ASSERT_EQ(after_0_0.direction, NORTH);
  ASSERT_EQ(after_0_0.token, 'c');
  ASSERT_EQ(after_0_0.counter, 1);
}

TEST(DarwinFixture, ifEmpty4) {
  int pc = 0;
  int jumpCondition = 10;
  Species s;
  Creature c1(s, EAST, 'c');
  Creature c2(s, SOUTH, 'c');
  Darwin x(2,2);

  x.addCreature(c1, 0, 0);
  x.addCreature(c2, 0, 1);

  Creature before_0_0 = x.grid.at(0);
  Creature before_0_1 = x.grid.at(1);

  ASSERT_EQ(before_0_0.spec, &s);
  ASSERT_EQ(before_0_0.direction, EAST);
  ASSERT_EQ(before_0_0.token, 'c');
  ASSERT_EQ(before_0_0.counter, 0);
  ASSERT_EQ(before_0_1.spec, &s);
  ASSERT_EQ(before_0_1.direction, SOUTH);
  ASSERT_EQ(before_0_1.token, 'c');
  ASSERT_EQ(before_0_1.counter, 0);

  x.ifEmpty(pc, jumpCondition);

  Creature after_0_0 = x.grid.at(0);
  Creature after_0_1 = x.grid.at(1);

  ASSERT_EQ(after_0_0.spec, &s);
  ASSERT_EQ(after_0_0.direction, EAST);
  ASSERT_EQ(after_0_0.token, 'c');
  ASSERT_EQ(after_0_0.counter, 1);
  ASSERT_EQ(after_0_1.spec, &s);
  ASSERT_EQ(after_0_1.direction, SOUTH);
  ASSERT_EQ(after_0_1.token, 'c');
  ASSERT_EQ(after_0_1.counter, 0);
}

// Test Darwin - ifWall
TEST(DarwinFixture, ifWall1) {
  Species s;
  s.addInstruction(IF_WALL, 2);
  s.addInstruction(RIGHT);
  s.addInstruction(LEFT);
  Creature c(s, NORTH, 'c');
  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, WEST);


}

TEST(DarwinFixture, ifWall2) {
  Species s;
  s.addInstruction(IF_WALL, 2);
  s.addInstruction(LEFT);
  s.addInstruction(RIGHT);
  Creature c(s, NORTH, 'c');
  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, EAST);
  

}

TEST(DarwinFixture, ifWall3) {
  Species s;
  s.addInstruction(IF_WALL, 2);
  s.addInstruction(LEFT);
  s.addInstruction(RIGHT);

  Creature c(s, WEST, 'c');
  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, NORTH);

}

TEST(DarwinFixture, ifWall4) {
  Species s;
  s.addInstruction(IF_WALL, 2);
  s.addInstruction(LEFT);
  s.addInstruction(RIGHT);

  Creature c(s, SOUTH, 'c');
  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, EAST);

}

// Test Darwin - ifRandom
TEST(DarwinFixture, ifRandom1) {
  Species s;
  s.addInstruction(IF_RANDOM, 3);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);

  Creature c(s, WEST, 'c');
  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, SOUTH);

}

TEST(DarwinFixture, ifRandom2) {
  Species s;
  s.addInstruction(IF_RANDOM, 4);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);

  Creature c(s, WEST, 'c');
  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, SOUTH);

}

TEST(DarwinFixture, ifRandom3) {
  Species s;
  s.addInstruction(IF_RANDOM, 2);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);

  Creature c(s, WEST, 'c');
  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, SOUTH);

}

TEST(DarwinFixture, ifRandom4) {
  Species s;
  s.addInstruction(IF_RANDOM, 5);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(LEFT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);
  s.addInstruction(RIGHT);

  Creature c(s, WEST, 'c');
  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, SOUTH);

}


// Test Darwin - ifEnemy
TEST(DarwinFixture, ifEnemy1) {
  Species s;
  s.addInstruction(IF_ENEMY, 2);
  s.addInstruction(RIGHT);
  s.addInstruction(LEFT);
  Creature c(s, NORTH, 'c');
  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, EAST);
}

TEST(DarwinFixture, ifEnemy2) {
  Species s;
  s.addInstruction(IF_ENEMY, 2);
  s.addInstruction(LEFT);
  s.addInstruction(RIGHT);
  Creature c(s, EAST, 'c');
  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, NORTH);
}

TEST(DarwinFixture, ifEnemy3) {
  Species s;
  Species b;
  s.addInstruction(IF_ENEMY, 2);
  s.addInstruction(LEFT);
  s.addInstruction(RIGHT);
  Creature c(s, EAST, 'c');
  Creature f(b, EAST, 'f');

  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  x.addCreature(f, 0, 1);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, SOUTH);
}

TEST(DarwinFixture, ifEnemy4) {
  Species s;
  s.addInstruction(IF_ENEMY, 2);
  s.addInstruction(LEFT);
  s.addInstruction(RIGHT);
  Creature c(s, EAST, 'c');

  Darwin x(2,2);
  x.addCreature(c, 0, 0);
  s.executeLine(&x, 0, &c);
  ASSERT_EQ(c.direction, NORTH);
}

// Test Darwin - simulate
TEST(DarwinFixture, simulate1) {
  std::ostringstream oss;
  std::string str;

  Species food;
  food.addInstruction(LEFT);
  food.addInstruction(GO, 0);

  Species hopper;
  hopper.addInstruction(HOP);
  hopper.addInstruction(GO, 0);

  Species trap;
  trap.addInstruction(IF_ENEMY, 3);
  trap.addInstruction(LEFT);
  trap.addInstruction(GO, 0);
  trap.addInstruction(INFECT);
  trap.addInstruction(GO, 0);

  Creature f1(food, NORTH, 'f');
  Creature f2(food, EAST, 'f');
  Creature h1(hopper, SOUTH, 'h');
  Creature h2(hopper, WEST, 'h');
  Creature t1(trap, NORTH, 't');

  Darwin x(3,3);
  x.addCreature(f1, 0, 0);
  x.addCreature(f2, 1, 0);
  x.addCreature(h1, 0, 2);
  x.addCreature(h2, 2, 2);
  x.addCreature(t1, 2, 0);

  x.simulate(5, 0, 1, oss);
  str = oss.str();

  ASSERT_EQ(str, "Turn = 0.\n  012\n0 f.h\n1 f..\n2 t.h\n\nTurn = 1.\n  012\n0 f..\n1 t.h\n2 th.\n\nTurn = 2.\n  012\n0 t..\n1 t..\n2 thh\n\nTurn = 3.\n  012\n0 t..\n1 t..\n2 thh\n\nTurn = 4.\n  012\n0 t..\n1 t..\n2 thh\n\nTurn = 5.\n  012\n0 t..\n1 t..\n2 tth\n\n");
}

// Test Darwin - display
// see next few test, which call display automatically

// Test Darwin - operator <<
TEST(DarwinFixture, coutOperator1) {
  try {
    Darwin x(1,1);
    std::ostringstream oss;

    oss << x;
  }
  catch(exception &e) {
    ASSERT_EQ(true, false);
  }
}

TEST(DarwinFixture, coutOperator2) {
  Darwin x(1,2);
  std::ostringstream oss;
  std::string str;

  oss << x;
  str = oss.str();

  ASSERT_EQ(str, "  01\n0 ..\n");
}

TEST(DarwinFixture, coutOperator3) {
  Darwin x(12,12);
  std::ostringstream oss;
  std::string str;

  oss << x;
  str = oss.str();

  ASSERT_EQ(str, "  012345678901\n0 ............\n1 ............\n2 ............\n3 ............\n4 ............\n5 ............\n6 ............\n7 ............\n8 ............\n9 ............\n0 ............\n1 ............\n");
}

TEST(DarwinFixture, coutOperator4) {
  Species s;
  Species t;
  Creature c(s, EAST, 'c');
  Creature d(t, NORTH, 'd');
  Darwin x(3,3);
  std::ostringstream oss;
  std::string str;

  x.addCreature(c, 0, 0);
  x.addCreature(d, 0, 2);
  x.addCreature(c, 2, 1);

  oss << x;
  str = oss.str();

  ASSERT_EQ(str, "  012\n0 c.d\n1 ...\n2 .c.\n");

}
