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

// -------------
// Species tests
// -------------

TEST(SpeciesFixture, species_constructor1) {
  Species s('1');
  ASSERT_EQ('1', s.id);
  ASSERT_EQ(0, s.instructionList.size());
}

TEST(SpeciesFixture, species_constructor2) {
  Species s('a');
  ASSERT_EQ('a', s.id);
}

TEST(SpeciesFixture, species_constructor3) {
  Species s('Y');
  Species s1('7');
  Species s2('.');
  ASSERT_EQ('Y', s.id);
  ASSERT_EQ('7', s1.id);
  ASSERT_EQ('.', s2.id);
}

TEST(SpeciesFixture, species_addInstruction_action1) {
  Species s('a');
  s.addInstruction(Instruction::left);
  ASSERT_EQ(Instruction::left, s.instructionList[0].first);
  ASSERT_EQ(-1, s.instructionList[0].second);
}

TEST(SpeciesFixture, species_addInstruction_action2) {
  Species s('a');
  s.addInstruction(Instruction::hop);
  s.addInstruction(Instruction::left);
  s.addInstruction(Instruction::right);
  s.addInstruction(Instruction::infect);

  ASSERT_EQ(Instruction::infect, s.instructionList[3].first);
  ASSERT_EQ(-1, s.instructionList[0].second);
  ASSERT_EQ(Instruction::right, s.instructionList[2].first);
  ASSERT_EQ(-1, s.instructionList[0].second);
  ASSERT_EQ(Instruction::left, s.instructionList[1].first);
  ASSERT_EQ(-1, s.instructionList[0].second);
  ASSERT_EQ(Instruction::hop, s.instructionList[0].first);
  ASSERT_EQ(-1, s.instructionList[0].second);
}

TEST(SpeciesFixture, species_addInstruction_action3) {
  Species s('a');
  s.addInstruction(Instruction::hop);
  s.addInstruction(Instruction::hop);
  ASSERT_EQ(s.instructionList[0].first, s.instructionList[1].first);
}

TEST(SpeciesFixture, species_addInstruction_control1) {
  Species s('a');
  s.addInstruction(Instruction::if_empty, 0);
  ASSERT_EQ(Instruction::if_empty, s.instructionList[0].first);
  ASSERT_EQ(0, s.instructionList[0].second);
}

TEST(SpeciesFixture, species_addInstruction_control2) {
  Species s('a');
  s.addInstruction(Instruction::if_empty, 0);
  s.addInstruction(Instruction::if_wall, 0);
  s.addInstruction(Instruction::if_random, 2);
  s.addInstruction(Instruction::if_enemy, 1);
  s.addInstruction(Instruction::go, 3);

  ASSERT_EQ(Instruction::if_empty, s.instructionList[0].first);
  ASSERT_EQ(0, s.instructionList[0].second);
  ASSERT_EQ(Instruction::if_wall, s.instructionList[1].first);
  ASSERT_EQ(0, s.instructionList[1].second);
  ASSERT_EQ(Instruction::if_random, s.instructionList[2].first);
  ASSERT_EQ(2, s.instructionList[2].second);
  ASSERT_EQ(Instruction::if_enemy, s.instructionList[3].first);
  ASSERT_EQ(1, s.instructionList[3].second);
  ASSERT_EQ(Instruction::go, s.instructionList[4].first);
  ASSERT_EQ(3, s.instructionList[4].second);
}

TEST(SpeciesFixture, species_addInstruction_control3) {
  Species s('a');
  s.addInstruction(Instruction::hop);
  s.addInstruction(Instruction::go, 0);
  ASSERT_NE(s.instructionList[0].first, s.instructionList[1].first);
}

TEST(SpeciesFixture, species_getInstruction1) {
  Species s1('a');
  s1.addInstruction(Instruction::hop);
  ASSERT_EQ(Instruction::hop, s1.getInstruction(0).first);
}

TEST(SpeciesFixture, species_getInstruction2) {
  Species s1('a');
  Species s2('b');
  s1.addInstruction(Instruction::hop);
  s2.addInstruction(Instruction::hop);
  ASSERT_EQ(Instruction::hop, s1.getInstruction(0).first);
  ASSERT_EQ(Instruction::hop, s2.getInstruction(0).first);
  ASSERT_EQ(s1.getInstruction(0).first, s2.getInstruction(0).first);
}

TEST(SpeciesFixture, species_getInstruction3) {
  Species s1('a');
  for (int i = 0; i < 10; ++i) {
    s1.addInstruction(Instruction::hop);
    s1.addInstruction(Instruction::left);
  }
  ASSERT_EQ(Instruction::hop, s1.getInstruction(10).first);
  ASSERT_EQ(Instruction::left, s1.getInstruction(19).first);
}

TEST(SpeciesFixture, species_printID1) {
  Species s1('a');
  ostringstream w;
  s1.printID(w);
  ASSERT_EQ("a", w.str());
}

TEST(SpeciesFixture, species_printID2) {
  Species s1('b');
  ostringstream w;
  s1.printID(w);
  ASSERT_EQ("b", w.str());
}

TEST(SpeciesFixture, species_printID3) {
  Species s1('c');
  ostringstream w;
  s1.printID(w);
  ASSERT_EQ("c", w.str());
}

TEST(SpeciesFixture, species_equaloperator1) {
  Species s1('a');
  Species s2('b');
  ASSERT_FALSE(s1 == s2);
}

TEST(SpeciesFixture, species_equaloperator2) {
  Species s1('a');
  Species s2('a');
  ASSERT_TRUE(s1 == s2);
}

TEST(SpeciesFixture, species_equaloperator3) {
  Species s1('.');
  Species s2(',');
  ASSERT_FALSE(s1 == s2);
}

// --------------
// Creature tests
// --------------

TEST(CreatureFixture, creature_default_constructor1) {
  Creature c;
  Species s1('.'); // equals default species

  ASSERT_TRUE(c.species_type == s1);
  ASSERT_EQ(c.direction, 0);
  ASSERT_EQ(c.program_counter, 0);
}

TEST(CreatureFixture, creature_constructor1) {
  Species s1('1');
  Creature c(s1, 2);

  ASSERT_TRUE(c.species_type == s1);
  ASSERT_EQ(c.direction, 2);
  ASSERT_EQ(c.program_counter, 0);
}

TEST(CreatureFixture, creature_constructor2) {
  Species s1('h');
  Creature c(s1, 1);

  ASSERT_TRUE(c.species_type == s1);
  ASSERT_EQ(c.direction, 1);
  ASSERT_EQ(c.program_counter, 0);
}

TEST(CreatureFixture, creature_constructor3) {
  Species s1('D');
  Creature c(s1, 0);

  ASSERT_TRUE(c.species_type == s1);
  ASSERT_EQ(c.direction, 0);
  ASSERT_EQ(c.program_counter, 0);
}

TEST(CreatureFixture, creature_printID1) {
  Species s1('a');
  Creature c(s1, 0);
  ostringstream w;
  c.printID(w);
  ASSERT_EQ("a", w.str());
}
TEST(CreatureFixture, creature_printID2) {
  Species s1('7');
  Creature c(s1, 3);
  ostringstream w;
  c.printID(w);
  ASSERT_EQ("7", w.str());
}
TEST(CreatureFixture, creature_printID3) {
  Species s1('J');
  Creature c(s1, 2);
  ostringstream w;
  c.printID(w);
  ASSERT_EQ("J", w.str());
}

TEST(CreatureFixture, creature_getFacingSpot1) {
  Creature c; // facing west
  int x = 5;
  int y = 9;
  c.getFacingSpot(x, y);
  ASSERT_EQ(x, 5);
  ASSERT_EQ(y, 8);
}
TEST(CreatureFixture, creature_getFacingSpot2) {
  Species s('1');
  Creature c(s, 1); // facing north
  int x = 5;
  int y = 9;
  c.getFacingSpot(x, y);
  ASSERT_EQ(x, 4);
  ASSERT_EQ(y, 9);
}
TEST(CreatureFixture, creature_getFacingSpot3) {
  Species s('1');
  Creature c(s, 2); // facing east
  int x = 5;
  int y = 9;
  c.getFacingSpot(x, y);
  ASSERT_EQ(x, 5);
  ASSERT_EQ(y, 10);
}
TEST(CreatureFixture, creature_getFacingSpot4) {
  Species s('1');
  Creature c(s, 3); // facing south
  int x = 5;
  int y = 9;
  c.getFacingSpot(x, y);
  ASSERT_EQ(x, 6);
  ASSERT_EQ(y, 9);
}

TEST(CreatureFixture, creature_nextInstruction1) {
  Species s('1');
  s.addInstruction(Instruction::hop);
  s.addInstruction(Instruction::go, 0);
  Creature c(s, 0); // program counter = 0
  int next_i = c.nextInstruction(0); // space ahead = empty
  ASSERT_TRUE(next_i == 2);
}

TEST(CreatureFixture, creature_nextInstruction2) {
  Species s('1');
  s.addInstruction(Instruction::hop);
  s.addInstruction(Instruction::left);
  s.addInstruction(Instruction::right);
  s.addInstruction(Instruction::infect);
  Creature c(s, 0); // program counter = 0
  int next_i1 = c.nextInstruction(0); // space ahead = empty, pc = 1 now
  int next_i2 = c.nextInstruction(0); // pc = 2 now
  int next_i3 = c.nextInstruction(0); // pc = 3 now
  int next_i4 = c.nextInstruction(0);
  ASSERT_EQ(next_i1, 2); // hop west
  ASSERT_EQ(next_i2, -1); // left or right
  ASSERT_EQ(next_i3, -1); // left or right
  ASSERT_EQ(next_i4, 0); // left or right
}

TEST(CreatureFixture, creature_nextInstruction3) {
  Species s('1');
  s.addInstruction(Instruction::if_empty, 2);
  s.addInstruction(Instruction::if_wall, 3);
  s.addInstruction(Instruction::right);
  s.addInstruction(Instruction::infect);
  Creature c(s, 0); // program counter = 0
  int next_i = c.nextInstruction(1); // space ahead = wall
  ASSERT_EQ(next_i, 0); // infect
}

TEST(CreatureFixture, creature_nextInstruction4) {
  Species s('1');
  s.addInstruction(Instruction::go, 1);
  s.addInstruction(Instruction::go, 2);
  s.addInstruction(Instruction::go, 3);
  s.addInstruction(Instruction::hop);
  Creature c(s, 2); // program counter = 0
  int next_i = c.nextInstruction(0); // space ahead = empty
  ASSERT_EQ(next_i, 1); // hop east
}

TEST(CreatureFixture, creature_changeSpecies1) {
  Species s1('1');
  Creature c1(s1, 0);
  Species s2('2');
  Creature c2(s2, 3);
  c1.changeSpecies(c2);
  ASSERT_TRUE(c1 == c2);
}
TEST(CreatureFixture, creature_changeSpecies2) {
  Species s1('1');
  Creature c1(s1, 1);
  Species s2('2');
  Creature c2(s2, 3);
  c1.changeSpecies(c2);
  ASSERT_TRUE(c1 == c2);
}
TEST(CreatureFixture, creature_changeSpecies3) {
  Species s1('H');
  Creature c1(s1, 0);
  Species s2('7');
  Creature c2(s2, 0);
  c1.changeSpecies(c2);
  ASSERT_TRUE(c1 == c2);
}

TEST(CreatureFixture, creature_equalOperator1) {
  Species s1('1');
  Creature c1(s1, 0);
  Creature c2(s1, 3);
  ASSERT_TRUE(c1 == c2);
}

TEST(CreatureFixture, creature_equalOperator2) {
  Species s1('G');
  Creature c1(s1, 2);
  Creature c2(s1, 1);
  ASSERT_TRUE(c1 == c2);
}

TEST(CreatureFixture, creature_equalOperator3) {
  Species s1('7');
  Creature c1(s1, 2);
  Creature c2(s1, 2);
  ASSERT_TRUE(c1 == c2);
}

// --------------
// Darwin tests
// --------------

TEST(DarwinFixture, darwin_constructor1) {
  Darwin x(1, 1);
  ASSERT_EQ(1, x.row);
  ASSERT_EQ(1, x.column);
  ASSERT_EQ(0, x.turn);
  ASSERT_EQ(1, x.board.size());
}

TEST(DarwinFixture, darwin_constructor2) {
  Darwin x(21, 43);
  ASSERT_EQ(21, x.row);
  ASSERT_EQ(43, x.column);
  ASSERT_EQ(0, x.turn);
  ASSERT_EQ(903, x.board.size());
}

TEST(DarwinFixture, darwin_constructor3) {
  Darwin x(2, 9);
  ASSERT_EQ(2, x.row);
  ASSERT_EQ(9, x.column);
  ASSERT_EQ(0, x.turn);
  ASSERT_EQ(18, x.board.size());
}

TEST(DarwinFixture, darwin_runTurn1) {
  Darwin x(2, 2);
  Species s1('s');
  s1.addInstruction(Instruction::hop);
  Creature c1(s1, 2);
  x.addCreature(c1, 0, 0);
  ostringstream w1;
  ostringstream w2;
  x.printBoard(w1);
  ASSERT_EQ("Turn = 0.\n  01\n0 s.\n1 ..\n\n", w1.str());
  x.runTurn();
  x.printBoard(w2);
  ASSERT_EQ("Turn = 1.\n  01\n0 .s\n1 ..\n\n", w2.str());
}
TEST(DarwinFixture, darwin_runTurn2) {
  Darwin x(2, 2);
  Species s1('s');
  s1.addInstruction(Instruction::hop);
  Creature c1(s1, 2);
  Creature c2(s1, 1);
  x.addCreature(c1, 0, 0);
  x.addCreature(c2, 1, 0);
  ostringstream w1;
  ostringstream w2;
  x.printBoard(w1);
  ASSERT_EQ("Turn = 0.\n  01\n0 s.\n1 s.\n\n", w1.str());
  x.runTurn(); // creature c1 hops right, creature c2 hops up
  x.printBoard(w2);
  ASSERT_EQ("Turn = 1.\n  01\n0 ss\n1 ..\n\n", w2.str());
}
TEST(DarwinFixture, darwin_runTurn3) {
  Darwin x(2, 2);
  Species s1('s');
  Species s2('z');
  s1.addInstruction(Instruction::infect);
  Creature c1(s1, 2);
  Creature c2(s2, 2);
  x.addCreature(c1, 0, 0);
  x.addCreature(c2, 0, 1);
  ostringstream w1;
  ostringstream w2;
  x.printBoard(w1);
  ASSERT_EQ("Turn = 0.\n  01\n0 sz\n1 ..\n\n", w1.str());
  x.runTurn(); // creature c1 infects c2
  x.printBoard(w2);
  ASSERT_EQ("Turn = 1.\n  01\n0 ss\n1 ..\n\n", w2.str());
}

TEST(DarwinFixture, darwin_addCreature1) {
  Darwin x(1, 1);
  Species s1('a');
  Creature c1(s1, 0);
  x.addCreature(c1, 0, 0);
  ASSERT_TRUE(c1 == x.board[0 * 1 + 0].first);
}

TEST(DarwinFixture, darwin_addCreature2) {
  Darwin x(4, 4);
  Species s1('a');
  Species s2('b');
  Species s3('c');
  Species s4('d');
  Creature c1(s1, 0);
  Creature c2(s2, 0);
  Creature c3(s3, 0);
  Creature c4(s4, 0);
  x.addCreature(c1, 0, 0);
  x.addCreature(c2, 1, 1);
  x.addCreature(c3, 2, 2);
  x.addCreature(c4, 3, 3);
  ASSERT_TRUE(c1 == x.board[0 * 4 + 0].first);
  ASSERT_TRUE(c2 == x.board[1 * 4 + 1].first);
  ASSERT_TRUE(c3 == x.board[2 * 4 + 2].first);
  ASSERT_TRUE(c4 == x.board[3 * 4 + 3].first);
}
TEST(DarwinFixture, darwin_addCreature3) {
  Darwin x(1, 4);
  Species s1('a');
  Creature c1(s1, 0);
  Creature c2(s1, 0);
  Creature c3(s1, 0);
  Creature c4(s1, 0);
  x.addCreature(c1, 0, 0);
  x.addCreature(c2, 0, 1);
  x.addCreature(c3, 0, 2);
  x.addCreature(c4, 0, 3);
  ASSERT_TRUE(c1 == x.board[0 * 4 + 0].first);
  ASSERT_TRUE(c2 == x.board[0 * 4 + 1].first);
  ASSERT_TRUE(c3 == x.board[0 * 4 + 2].first);
  ASSERT_TRUE(c4 == x.board[0 * 4 + 3].first);
}

TEST(DarwinFixture, darwin_checkSpot1) {
  // Check creature
  Darwin x(2, 2);
  Species s1('a');
  Creature c1(s1, 0);
  Creature c2(s1, 1);
  x.addCreature(c1, 0, 0);
  ASSERT_EQ(2, x.checkSpot(0, 0));
}
TEST(DarwinFixture, darwin_checkSpot2) {
  // Check empty
  Darwin x(2, 2);
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      ASSERT_EQ(0, x.checkSpot(i, j));
    }
  }
}
TEST(DarwinFixture, darwin_checkSpot3) {
  // Check wall
  Darwin x(2, 2);
  ASSERT_EQ(1, x.checkSpot(-1, 0));
  ASSERT_EQ(1, x.checkSpot(0, -1));
  ASSERT_EQ(1, x.checkSpot(2, 0));
  ASSERT_EQ(1, x.checkSpot(0, 2));
}

TEST(DarwinFixture, darwin_printBoard1) {
  Darwin x(2, 2);
  ostringstream w;
  x.printBoard(w);
  ASSERT_EQ("Turn = 0.\n  01\n0 ..\n1 ..\n\n", w.str());
}
TEST(DarwinFixture, darwin_printBoard2) {
  Darwin x(4, 4);
  Species s1('a');
  Species s2('b');
  Species s3('c');
  Species s4('d');
  Creature c1(s1, 0);
  Creature c2(s2, 0);
  Creature c3(s3, 0);
  Creature c4(s4, 0);
  x.addCreature(c1, 0, 0);
  x.addCreature(c2, 1, 1);
  x.addCreature(c3, 2, 2);
  x.addCreature(c4, 3, 3);
  ostringstream w;
  x.printBoard(w);
  ASSERT_EQ("Turn = 0.\n  0123\n0 a...\n1 .b..\n2 ..c.\n3 ...d\n\n", w.str());
}
TEST(DarwinFixture, darwin_printBoard3) {
  Darwin x(6, 6);
  Species s1('s');
  Creature c1(s1, 0);
  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 6; ++j) {
      x.addCreature(c1, i, j);
    }
  }
  ostringstream w;
  x.printBoard(w);
  ASSERT_EQ("Turn = 0.\n  012345\n0 ssssss\n1 ssssss\n2 ssssss\n3 ssssss\n4 "
            "ssssss\n5 ssssss\n\n",
            w.str());
}
