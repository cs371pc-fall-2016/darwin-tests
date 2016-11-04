// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include "Darwin.h"
#include "gtest/gtest.h"
#include <sstream> // istringtstream, ostringstream

using namespace std;

/* Species */

// ----
// constructor
// ----

TEST(Species, default_constructor) {
  Species x = Species();
  ASSERT_EQ(0, x.instructions.size());
  ASSERT_EQ(".", x.rep);
}

TEST(Species, constructor) {
  Species x = Species("t");
  ASSERT_EQ(0, x.instructions.size());
  ASSERT_EQ("t", x.rep);
}

// ----
// print
// ----

TEST(Species, species_print1) {
  Species x = Species();
  ostringstream w;
  w << x;
  ASSERT_EQ(".", w.str());
}

TEST(Species, species_print2) {
  Species x = Species("t");
  ostringstream w;
  w << x;
  ASSERT_EQ("t", w.str());
}

TEST(Species, species_print3) {
  Species x = Species("best");
  ostringstream w;
  w << x;
  ASSERT_EQ("best", w.str());
}

//----
// addInstruction
//----

TEST(Species, species_addInstruction1) {
  Species x = Species();
  x.addInstruction("test instruction");
  ASSERT_EQ("test instruction", x.instructions[0]);
}

TEST(Species, species_addInstruction2) {
  Species x = Species();
  for (int i = 0; i < 10; ++i)
    x.addInstruction("test instruction");
  ASSERT_EQ(10, x.instructions.size());
}

TEST(Species, species_addInstruction3) {
  Species x = Species();
  for (int i = 0; i < 1000; ++i)
    x.addInstruction("test instruction");
  ASSERT_EQ(1000, x.instructions.size());
}

//----
// getInstruction
//----

TEST(Species, species_getInstruction1) {
  Species x = Species();
  x.addInstruction("test instruction");
  string ins = x.getInstruction(0);
  ASSERT_EQ("test instruction", ins);
}

TEST(Species, species_getInstruction2) {
  Species x = Species();
  x.addInstruction("test instruction1");
  x.addInstruction("test instruction2");
  string ins = x.getInstruction(0);
  ASSERT_EQ("test instruction1", ins);
  ins = x.getInstruction(1);
  ASSERT_EQ("test instruction2", ins);
}

TEST(Species, species_getInstruction3) {
  Species x = Species("best");
  ostringstream w;
  w << x;
  ASSERT_EQ("best", w.str());
}

/* Creature */

// ----
// constructor
// ----

TEST(Creature, default_constructor) {
  Creature c = Creature();
  ASSERT_EQ(nullptr, c.species);
  ASSERT_EQ(north, c.direction);
  ASSERT_EQ(0, c.pc);
}

TEST(Creature, constructor) {
  Species x = Species("t");
  Creature c = Creature(&x, west);
  ASSERT_EQ(&x, c.species);
  ASSERT_EQ(west, c.direction);
  ASSERT_EQ(0, c.pc);
}

// ----
// print
// ----

TEST(Creature, creature_print1) {
  Creature c = Creature();
  ostringstream w;
  w << c;
  ASSERT_EQ(".", w.str());
}

TEST(Creature, creature_print2) {
  Species x = Species("t");
  Creature c = Creature(&x, north);
  ostringstream w;
  w << c;
  ASSERT_EQ("t", w.str());
}

TEST(Creature, creature_print3) {
  Species x = Species("best");
  Creature c = Creature(&x, south);
  ostringstream w;
  w << c;
  ASSERT_EQ("best", w.str());
}

// ----
// getIntent
// ----

TEST(Creature, creature_getIntent1) {
  Species x = Species("t");
  x.addInstruction("hop");
  Creature c = Creature(&x, north);
  Creature inFront = Creature(&x, south);

  string ins = c.getIntent(true, false, &inFront);
  ASSERT_EQ("hop", ins);
}

TEST(Creature, creature_getIntent2) {
  Species x = Species("t");
  x.addInstruction("infect");
  Creature c = Creature(&x, north);
  Creature inFront = Creature(&x, south);

  string ins = c.getIntent(false, false, &inFront);
  ASSERT_EQ("nothing", ins);
}

TEST(Creature, creature_getIntent3) {
  Species x = Species("t");
  Species xInFront = Species("b");
  x.addInstruction("infect");
  Creature c = Creature(&x, north);
  Creature inFront = Creature(&xInFront, south);

  string ins = c.getIntent(false, false, &inFront);
  ASSERT_EQ("infect", ins);
}

TEST(Creature, creature_getIntent4) {
  Species x = Species("t");
  Species xInFront = Species("b");
  x.addInstruction("if_empty 1");
  x.addInstruction("hop");
  Creature c = Creature(&x, north);
  Creature inFront = Creature(&xInFront, south);

  string ins = c.getIntent(false, false, &inFront);
  ASSERT_EQ("hop", ins);
}

TEST(Creature, creature_getIntent_if_wall1) {
  Species x = Species("r");
  x.addInstruction("if_wall 2");
  x.addInstruction("right");
  x.addInstruction("hop");
  Creature c = Creature(&x, north);

  string ins = c.getIntent(false, true, nullptr);
  ASSERT_EQ("hop", ins);
}

TEST(Creature, creature_getIntent_if_wall2) {
  Species x = Species("r");
  x.addInstruction("if_wall 2");
  x.addInstruction("right");
  x.addInstruction("hop");
  Creature c = Creature(&x, north);

  string ins = c.getIntent(false, false, nullptr);
  ASSERT_EQ("right", ins);
}

TEST(Creature, creature_getIntent_if_empty1) {
  Species x = Species("t");
  x.addInstruction("if_empty 2");
  x.addInstruction("left");
  x.addInstruction("hop");

  Creature c = Creature(&x, south);

  string ins = c.getIntent(true, false, nullptr);
  ASSERT_EQ("hop", ins);
}

TEST(Creature, creature_getIntent_if_empty2) {
  Species x = Species("t");
  x.addInstruction("if_empty 2");
  x.addInstruction("left");
  x.addInstruction("hop");

  Creature c = Creature(&x, south);

  string ins = c.getIntent(false, false, nullptr);
  ASSERT_EQ("left", ins);
}

TEST(Creature, creature_getIntent_if_random1) {
  Species x = Species("t");
  x.addInstruction("if_random 2");
  x.addInstruction("right");
  x.addInstruction("hop");

  Creature c = Creature(&x, south);

  srand(0);
  string intent = c.getIntent(false, false, nullptr);

  srand(0);
  string instruction;

  bool isOdd = (rand() % 2 == 1);
  if (isOdd) {
    instruction = "hop";
  } else {
    instruction = "right";
  }

  ASSERT_EQ(instruction, intent);
}

TEST(Creature, creature_getIntent_if_random2) {
  Species x = Species("t");
  x.addInstruction("if_random 2");
  x.addInstruction("left");
  x.addInstruction("hop");

  Creature c = Creature(&x, south);

  srand(1);
  string intent = c.getIntent(false, false, nullptr);

  srand(1);
  string instruction;

  bool isOdd = (rand() % 2 == 1);
  if (isOdd) {
    instruction = "hop";
  } else {
    instruction = "left";
  }

  ASSERT_EQ(instruction, intent);
}

TEST(Creature, creature_getIntent_go) {
  Species x = Species("t");
  x.addInstruction("go 2");
  x.addInstruction("infect");
  x.addInstruction("hop");

  Creature c = Creature(&x, south);

  string ins = c.getIntent(false, false, nullptr);
  ASSERT_EQ("hop", ins);
}

// ----
// inFront
// ----

TEST(Creature, creature_inFront1) {
  Species x = Species();
  Creature c = Creature(&x, north);

  Coordinate cur = Coordinate(2, 3);
  Coordinate co = c.inFront(cur);
  ASSERT_EQ(3, co.x);
  ASSERT_EQ(1, co.y);
}

TEST(Creature, creature_inFront2) {
  Species x = Species();
  Creature c = Creature(&x, south);

  Coordinate cur = Coordinate(2, 3);
  Coordinate co = c.inFront(cur);
  ASSERT_EQ(3, co.x);
  ASSERT_EQ(3, co.y);
}

TEST(Creature, creature_inFront3) {
  Species x = Species();
  Creature c = Creature(&x, west);

  Coordinate cur = Coordinate(2, 3);
  Coordinate co = c.inFront(cur);
  ASSERT_EQ(2, co.x);
  ASSERT_EQ(2, co.y);
}

TEST(Creature, creature_inFront4) {
  Species x = Species();
  Creature c = Creature(&x, east);

  Coordinate cur = Coordinate(2, 3);
  Coordinate co = c.inFront(cur);
  ASSERT_EQ(4, co.x);
  ASSERT_EQ(2, co.y);
}

// ----
// makeMove
// ----

TEST(Creature, makeMove1) {
  Species x = Species("t");
  x.addInstruction("left");
  Creature c = Creature(&x, north);

  c.makeMove();
  ASSERT_EQ(1, c.pc);
  ASSERT_EQ(west, c.direction);
}

TEST(Creature, makeMove2) {
  Species x = Species("t");
  x.addInstruction("right");
  Creature c = Creature(&x, north);

  c.makeMove();
  ASSERT_EQ(1, c.pc);
  ASSERT_EQ(east, c.direction);
}

TEST(Creature, makeMove3) {
  Species x = Species("t");
  x.addInstruction("hop");
  Creature c = Creature(&x, north);

  c.makeMove();
  ASSERT_EQ(1, c.pc);
  ASSERT_EQ(north, c.direction);
}

TEST(Creature, makeMove4) {
  Species x = Species("t");
  x.addInstruction("infect");
  Creature c = Creature(&x, north);

  c.makeMove();
  ASSERT_EQ(1, c.pc);
  ASSERT_EQ(north, c.direction);
}

TEST(Creature, makeMove5) {
  Species x = Species("t");
  x.addInstruction("left");
  x.addInstruction("hop");
  Creature c = Creature(&x, north);

  c.makeMove();
  c.makeMove();
  ASSERT_EQ(2, c.pc);
  ASSERT_EQ(west, c.direction);
}

TEST(Creature, makeMove6) {
  Species x = Species("t");
  x.addInstruction("right");
  x.addInstruction("right");
  x.addInstruction("right");
  x.addInstruction("right");
  Creature c = Creature(&x, north);

  c.makeMove();
  c.makeMove();
  c.makeMove();
  c.makeMove();
  ASSERT_EQ(4, c.pc);
  ASSERT_EQ(north, c.direction);
}

//
// infectCreature
//

TEST(Creature, infectCreature1) {
  Species x = Species("t");
  Species y = Species();
  Creature c = Creature(&x, north);
  Creature enemy = Creature(&y, south);

  c.infectCreature(&enemy);
  ASSERT_EQ(0, enemy.pc);
  ASSERT_EQ("t", enemy.species->rep);
}

/* Darwin */

//
// getIndex
//

TEST(Darwin, getIndex1) {
  Darwin d(5, 5);
  Coordinate co = Coordinate(3, 3);

  int index = d.getIndex(co);

  ASSERT_EQ(18, index);
}

TEST(Darwin, getIndex2) {
  Darwin d(50, 10);
  Coordinate co = Coordinate(20, 2);

  int index = d.getIndex(co);

  ASSERT_EQ(202, index);
}

TEST(Darwin, getIndex3) {
  Darwin d(20, 8);
  Coordinate co = Coordinate(3, 5);

  int index = d.getIndex(co);

  ASSERT_EQ(29, index);
}

//
// getCoordinate
//

TEST(Darwin, getCoordinate1) {
  Darwin d(5, 5);
  Coordinate realCo = Coordinate(3, 3);

  Coordinate returnedCo = d.getCoordinate(18);

  ASSERT_EQ(realCo.x, returnedCo.x);
  ASSERT_EQ(realCo.y, returnedCo.y);
}

TEST(Darwin, getCoordinate2) {
  Darwin d(50, 10);
  Coordinate realCo = Coordinate(20, 2);

  Coordinate returnedCo = d.getCoordinate(202);

  ASSERT_EQ(realCo.x, returnedCo.x);
  ASSERT_EQ(realCo.y, returnedCo.y);
}

TEST(Darwin, getCoordinate3) {
  Darwin d(20, 8);
  Coordinate realCo = Coordinate(3, 5);

  Coordinate returnedCo = d.getCoordinate(29);

  ASSERT_EQ(realCo.x, returnedCo.x);
  ASSERT_EQ(realCo.y, returnedCo.y);
}

//
// isWall
//

TEST(Darwin, is_wall1) {
  Darwin d(5, 5);
  Coordinate co = Coordinate(-1, 3);

  ASSERT_EQ(true, d.isWall(co));
}

TEST(Darwin, is_wall2) {
  Darwin d(5, 5);
  Coordinate co = Coordinate(3, 3);

  ASSERT_EQ(false, d.isWall(co));
}

TEST(Darwin, is_wall3) {
  Darwin d(5, 5);
  Coordinate co = Coordinate(5, 3);

  ASSERT_EQ(true, d.isWall(co));
}

//
// isEmpty
//

TEST(Darwin, isEmpty1) {
  Darwin d(5, 5);
  Coordinate co = Coordinate(3, 3);

  ASSERT_EQ(true, d.isEmpty(co));
}

TEST(Darwin, isEmpty2) {
  Darwin d(5, 5);
  Coordinate co = Coordinate(-1, 3);

  ASSERT_EQ(false, d.isEmpty(co));
}

TEST(Darwin, isEmpty3) {
  Darwin d(5, 5);
  Coordinate co = Coordinate(3, 3);
  Species s = Species("t");
  Creature c = Creature(&s, north);

  d.addCreature(&c, co);

  ASSERT_EQ(false, d.isEmpty(co));
}

//
// Darwin
//

TEST(Darwin, Darwin1) {
  Darwin d(10, 5);

  ASSERT_EQ(5, d.width);
}

TEST(Darwin, Darwin2) {
  Darwin d(10, 5);

  ASSERT_EQ(10, d.height);
}

TEST(Darwin, Darwin3) {
  Darwin d(10, 5);

  ASSERT_EQ(0, d.turn);

  ostringstream w;
  d.simulate(w, 10);

  ASSERT_EQ(11, d.turn);
}

TEST(Darwin, Darwin4) {
  Darwin darwin(10, 5);

  Creature &dummy = darwin.dummy;

  for (unsigned int i = 0; i < darwin.grid.size(); ++i) {
    Creature *d = darwin.grid[i];
    ASSERT_EQ(d, &dummy);
  }
}

//
// addCreature
//

TEST(Darwin, addCreature1) {
  Darwin d(5, 5);
  Coordinate co = Coordinate(3, 3);

  Creature &dummy = d.dummy;
  ASSERT_EQ(d.grid[d.getIndex(co)], &dummy);

  Species x = Species();
  Creature c = Creature(&x, north);

  d.addCreature(&c, co);
  ASSERT_EQ(d.grid[d.getIndex(co)], &c);
}

TEST(Darwin, addCreature2) {
  Darwin d(5, 5);
  Coordinate co = Coordinate(3, 3);
  Species x = Species("t");
  Creature c = Creature(&x, north);

  d.addCreature(&c, co);
  ASSERT_EQ(d.grid[d.getIndex(co)]->species->rep, "t");
}

TEST(Darwin, addCreature3) {
  Darwin d(5, 5);
  Coordinate co = Coordinate(3, 3);
  Species x = Species("t");
  Creature c = Creature(&x, north);

  ASSERT_EQ(d.isEmpty(co), true);

  d.addCreature(&c, co);
  ASSERT_EQ(d.isEmpty(co), false);
}

//
// print
//

TEST(Darwin, darwin_print1) {
  Darwin d(4, 4);

  ostringstream testOutput;
  testOutput << d;

  ostringstream trueOutput;

  trueOutput << "Turn = 0." << endl;
  trueOutput << "  0123" << endl;

  for (int i = 0; i < 4; ++i) {
    trueOutput << i << " ";
    for (int j = 0; j < 4; ++j) {
      trueOutput << ".";
    }
    trueOutput << endl;
  }
  trueOutput << endl;

  ASSERT_EQ(testOutput.str(), trueOutput.str());
}

TEST(Darwin, darwin_print2) {
  Darwin d(4, 4);

  Species s = Species("s");
  Creature c = Creature(&s, north);
  Coordinate co = Coordinate(2, 2);

  d.addCreature(&c, co);

  ostringstream testOutput;
  testOutput << d;

  ostringstream trueOutput;

  trueOutput << "Turn = 0." << endl;
  trueOutput << "  0123" << endl;

  for (int i = 0; i < 4; ++i) {
    trueOutput << i << " ";
    for (int j = 0; j < 4; ++j) {
      Coordinate newCo = Coordinate(i, j);
      if (co.x == newCo.x && co.y == newCo.y)
        trueOutput << "s";
      else
        trueOutput << ".";
    }
    trueOutput << endl;
  }
  trueOutput << endl;

  ASSERT_EQ(testOutput.str(), trueOutput.str());
}

TEST(Darwin, darwin_print3) {
  Darwin d(4, 4);

  Species s = Species("s");
  Creature c = Creature(&s, north);

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      Coordinate co = Coordinate(i, j);
      d.addCreature(&c, co);
    }
  }

  ostringstream testOutput;
  testOutput << d;

  ostringstream trueOutput;

  trueOutput << "Turn = 0." << endl;
  trueOutput << "  0123" << endl;

  for (int i = 0; i < 4; ++i) {
    trueOutput << i << " ";
    for (int j = 0; j < 4; ++j) {
      trueOutput << "s";
    }
    trueOutput << endl;
  }
  trueOutput << endl;

  ASSERT_EQ(testOutput.str(), trueOutput.str());
}

//
// simulate
//

TEST(Darwin, darwin_simulate1) {
  Darwin d(4, 4);

  Species s = Species("h");
  s.addInstruction("hop");
  s.addInstruction("go 0");
  Creature c = Creature(&s, north);
  Coordinate co = Coordinate(2, 2);

  d.addCreature(&c, co);

  /* before simulate */
  ostringstream testOutput;
  testOutput << d;
  ostringstream trueOutput;
  trueOutput << "Turn = 0." << endl;
  trueOutput << "  0123" << endl;

  for (int i = 0; i < 4; ++i) {
    trueOutput << i << " ";
    for (int j = 0; j < 4; ++j) {
      Coordinate newCo = Coordinate(i, j);
      if (co.x == newCo.x && co.y == newCo.y)
        trueOutput << "h";
      else
        trueOutput << ".";
    }
    trueOutput << endl;
  }
  trueOutput << endl;

  ASSERT_EQ(testOutput.str(), trueOutput.str());

  ostringstream out;

  d.simulate(out, 0);

  /* after simulate */

  co = Coordinate(1, 2);

  ostringstream afterSimTest;
  afterSimTest << d;
  ostringstream afterSimTrue;
  afterSimTrue << "Turn = 1." << endl;
  afterSimTrue << "  0123" << endl;

  for (int i = 0; i < 4; ++i) {
    afterSimTrue << i << " ";
    for (int j = 0; j < 4; ++j) {
      Coordinate newCo = Coordinate(i, j);
      if (co.x == newCo.x && co.y == newCo.y)
        afterSimTrue << "h";
      else
        afterSimTrue << ".";
    }
    afterSimTrue << endl;
  }
  afterSimTrue << endl;

  ASSERT_EQ(afterSimTest.str(), afterSimTrue.str());
}

TEST(Darwin, darwin_simulate2) {
  Darwin d(4, 4);

  Species hopper = Species("h");
  hopper.addInstruction("hop");
  hopper.addInstruction("go 0");
  Creature hopCreature = Creature(&hopper, north);
  Coordinate hopCo = Coordinate(2, 2);

  Species trap = Species("t");
  trap.addInstruction("if_enemy 3");
  trap.addInstruction("left");
  trap.addInstruction("go 0");
  trap.addInstruction("infect");
  trap.addInstruction("go 0");

  Creature trapCreature = Creature(&trap, south);
  Coordinate trapCo = Coordinate(0, 3);

  d.addCreature(&hopCreature, hopCo);
  d.addCreature(&trapCreature, trapCo);

  /* before simulate */
  ostringstream testOutput;
  testOutput << d;
  ostringstream trueOutput;
  trueOutput << "Turn = 0." << endl;
  trueOutput << "  0123" << endl;

  for (int i = 0; i < 4; ++i) {
    trueOutput << i << " ";
    for (int j = 0; j < 4; ++j) {
      Coordinate newCo = Coordinate(i, j);
      if (hopCo.x == newCo.x && hopCo.y == newCo.y)
        trueOutput << "h";
      else if (trapCo.x == newCo.x && trapCo.y == newCo.y)
        trueOutput << "t";
      else
        trueOutput << ".";
    }
    trueOutput << endl;
  }
  trueOutput << endl;

  ASSERT_EQ(testOutput.str(), trueOutput.str());

  ostringstream out;

  d.simulate(out, 4);

  /* after simulate */

  Coordinate hopInfectedCo = Coordinate(0, 2);

  ostringstream afterSimTest;
  afterSimTest << d;
  ostringstream afterSimTrue;
  afterSimTrue << "Turn = 5." << endl;
  afterSimTrue << "  0123" << endl;

  for (int i = 0; i < 4; ++i) {
    afterSimTrue << i << " ";
    for (int j = 0; j < 4; ++j) {
      Coordinate newCo = Coordinate(i, j);
      if (hopInfectedCo.x == newCo.x && hopInfectedCo.y == newCo.y)
        afterSimTrue << "t";
      else if (trapCo.x == newCo.x && trapCo.y == newCo.y)
        afterSimTrue << "t";
      else
        afterSimTrue << ".";
    }
    afterSimTrue << endl;
  }
  afterSimTrue << endl;

  ASSERT_EQ(afterSimTest.str(), afterSimTrue.str());
}

TEST(Darwin, darwin_simulate3) {
  Darwin d(4, 4);

  Species hopper = Species("h");
  hopper.addInstruction("hop");
  hopper.addInstruction("go 0");
  Creature hopCreature = Creature(&hopper, north);
  Coordinate hopCo = Coordinate(2, 1);

  Species trap = Species("t");
  trap.addInstruction("if_enemy 3");
  trap.addInstruction("left");
  trap.addInstruction("go 0");
  trap.addInstruction("infect");
  trap.addInstruction("go 0");

  Creature trapCreature = Creature(&trap, south);
  Coordinate trapCo = Coordinate(0, 3);

  d.addCreature(&hopCreature, hopCo);
  d.addCreature(&trapCreature, trapCo);

  /* before simulate */
  ostringstream testOutput;
  testOutput << d;
  ostringstream trueOutput;
  trueOutput << "Turn = 0." << endl;
  trueOutput << "  0123" << endl;

  for (int i = 0; i < 4; ++i) {
    trueOutput << i << " ";
    for (int j = 0; j < 4; ++j) {
      Coordinate newCo = Coordinate(i, j);
      if (hopCo.x == newCo.x && hopCo.y == newCo.y)
        trueOutput << "h";
      else if (trapCo.x == newCo.x && trapCo.y == newCo.y)
        trueOutput << "t";
      else
        trueOutput << ".";
    }
    trueOutput << endl;
  }
  trueOutput << endl;

  ASSERT_EQ(testOutput.str(), trueOutput.str());

  ostringstream out;

  d.simulate(out, 4);

  /* after simulate */

  hopCo = Coordinate(0, 1);

  ostringstream afterSimTest;
  afterSimTest << d;
  ostringstream afterSimTrue;
  afterSimTrue << "Turn = 5." << endl;
  afterSimTrue << "  0123" << endl;

  for (int i = 0; i < 4; ++i) {
    afterSimTrue << i << " ";
    for (int j = 0; j < 4; ++j) {
      Coordinate newCo = Coordinate(i, j);
      if (hopCo.x == newCo.x && hopCo.y == newCo.y)
        afterSimTrue << "h";
      else if (trapCo.x == newCo.x && trapCo.y == newCo.y)
        afterSimTrue << "t";
      else
        afterSimTrue << ".";
    }
    afterSimTrue << endl;
  }
  afterSimTrue << endl;

  ASSERT_EQ(afterSimTest.str(), afterSimTrue.str());
}

/* Coordinate */

//
// default constructor
//

TEST(Coordinate, Coordinate_constructor_default1) {
  Coordinate co;

  ASSERT_EQ(co.x, 0);
}

TEST(Coordinate, Coordinate_constructor_default2) {
  Coordinate co;

  ASSERT_EQ(co.y, 0);
}

TEST(Coordinate, Coordinate) {
  Coordinate co;

  co.x = 5;
  co.y = 7;

  ASSERT_EQ(co.y, 7);
  ASSERT_EQ(co.x, 5);
}

//
// constructor (int, int)
//

TEST(Coordinate, Coordinate_constructor_int1) {
  Coordinate co = Coordinate(0, 0);

  ASSERT_EQ(co.x, 0);
  ASSERT_EQ(co.y, 0);
}

TEST(Coordinate, Coordinate_constructor_int2) {
  Coordinate co = Coordinate(5, 7);

  ASSERT_EQ(co.y, 5);
  ASSERT_EQ(co.x, 7);
}

TEST(Coordinate, Coordinate_constructor_int3) {
  Coordinate co = Coordinate(1, 1);

  ASSERT_EQ(co.y, 1);
  ASSERT_EQ(co.x, 1);

  co.x = 5;
  co.y = 7;

  ASSERT_EQ(co.y, 7);
  ASSERT_EQ(co.x, 5);
}