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
// test
//

TEST(Darwin, rcti1) {
  Darwin x(2, 2);
  ASSERT_EQ(x.rcti(1, 1), 3);
}

TEST(Darwin, rcti2) {
  Darwin x(2, 2);
  ASSERT_EQ(x.rcti(1, 2), -1);
}

TEST(Darwin, rcti3) {
  Darwin x(2, 2);
  ASSERT_EQ(x.rcti(0, 1), 1);
}

TEST(Darwin, findNextCreature1) {
  Darwin x(2, 2);
  ASSERT_EQ(x.findNextCreature(-1), -1);
}

TEST(Darwin, findNextCreature2) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::east);
  ASSERT_EQ(x.findNextCreature(-1), 0);
}

TEST(Darwin, findNextCreature3) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::east);
  ASSERT_EQ(x.findNextCreature(0), -1);
}

TEST(Darwin, findCreatureIndex1) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::east);
  ASSERT_EQ(x.findCreatureIndex(x._board[0]._creature), 0);
}

TEST(Darwin, findCreatureIndex2) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  Creature creature(&food);
  ASSERT_EQ(x.findCreatureIndex(creature), -1);
}

TEST(Darwin, findCreatureIndex3) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::east);
  x.addCreature(&food, 0, 1, Direction::east);
  ASSERT_EQ(x.findCreatureIndex(x._board[1]._creature), 1);
}

TEST(Darwin, findIndexFront1) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::east);
  ASSERT_EQ(x.findIndexFront(x._board[0]._creature), 1);
}

TEST(Darwin, findIndexFront2) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::north);
  ASSERT_EQ(x.findIndexFront(x._board[0]._creature), -1);
}

TEST(Darwin, findIndexFront3) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  ASSERT_EQ(x.findIndexFront(x._board[0]._creature), 2);
}

TEST(Darwin, frontEmpty1) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::north);
  ASSERT_FALSE(x.frontEmpty(x._board[0]._creature));
}
TEST(Darwin, frontEmpty2) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::east);
  x.addCreature(&food, 0, 1, Direction::north);
  ASSERT_FALSE(x.frontEmpty(x._board[0]._creature));
}
TEST(Darwin, frontEmpty3) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  ASSERT_TRUE(x.frontEmpty(x._board[0]._creature));
}
TEST(Darwin, doAction1) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  Creature *actor = &(x._board[0]._creature);
  x.doAction(Instruction::hop, *actor);
  ASSERT_EQ(x._board[0]._creature._species, &Creature::_default);
  ASSERT_EQ(x._board[2]._creature._species, &food);
}
TEST(Darwin, doAction2) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  Creature *actor = &(x._board[0]._creature);
  x.doAction(Instruction::left, *actor);
  ASSERT_EQ(x._board[0]._direction, Direction::east);
}
TEST(Darwin, doAction3) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  Creature *actor = &(x._board[0]._creature);
  x.doAction(Instruction::right, *actor);
  ASSERT_EQ(x._board[0]._direction, Direction::west);
}
TEST(Darwin, doAction4) {
  Darwin x(2, 2);
  Species food("food");
  Species notFood("notFood");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  x.addCreature(&notFood, 1, 0, Direction::north);
  Creature *actor = &(x._board[2]._creature);
  x.doAction(Instruction::infect, *actor);
  ASSERT_EQ(x._board[0]._creature._species, &notFood);
}
TEST(Darwin, hop1) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  Creature *actor = &(x._board[0]._creature);
  x.hop(*actor);
  ASSERT_EQ(x._board[0]._creature._species, &Creature::_default);
  ASSERT_EQ(x._board[2]._creature._species, &food);
}
TEST(Darwin, hop2) {
  Darwin x(2, 2);
  Species food("food");
  Species notFood("notFood");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  x.addCreature(&notFood, 1, 0, Direction::south);
  Creature *actor = &(x._board[0]._creature);
  x.hop(*actor);
  ASSERT_EQ(x._board[0]._creature._species, &food);
  ASSERT_EQ(x._board[2]._creature._species, &notFood);
}
TEST(Darwin, hop3) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::north);
  Creature *actor = &(x._board[0]._creature);
  x.hop(*actor);
  ASSERT_EQ(x._board[0]._creature._species, &food);
}
TEST(Darwin, turn1) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  Creature *actor = &(x._board[0]._creature);
  x.turn(*actor, -1);
  ASSERT_EQ(x._board[0]._direction, Direction::east);
}
TEST(Darwin, turn2) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  Creature *actor = &(x._board[0]._creature);
  x.turn(*actor, 0);
  ASSERT_EQ(x._board[0]._direction, Direction::east);
}
TEST(Darwin, turn3) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  Creature *actor = &(x._board[0]._creature);
  x.turn(*actor, 1);
  ASSERT_EQ(x._board[0]._direction, Direction::west);
}
TEST(Darwin, infect1) {
  Darwin x(2, 2);
  Species food("food");
  Species notFood("notFood");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  x.addCreature(&notFood, 1, 0, Direction::south);
  Creature *actor = &(x._board[0]._creature);
  x.infect(*actor);
  ASSERT_EQ(x._board[0]._creature._species, &food);
  ASSERT_EQ(x._board[2]._creature._species, &food);
}
TEST(Darwin, infect2) {
  Darwin x(2, 2);
  Species food("food");
  Species notFood("notFood");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  x.addCreature(&notFood, 1, 0, Direction::north);
  Creature *actor = &(x._board[2]._creature);
  x.infect(*actor);
  ASSERT_EQ(x._board[0]._creature._species, &notFood);
  ASSERT_EQ(x._board[2]._creature._species, &notFood);
}
TEST(Darwin, infect3) {
  Darwin x(2, 2);
  Species food("food");
  Species notFood("notFood");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  x.addCreature(&notFood, 1, 0, Direction::south);
  Creature *actor = &(x._board[2]._creature);
  x.infect(*actor);
  ASSERT_EQ(x._board[0]._creature._species, &food);
  ASSERT_EQ(x._board[2]._creature._species, &notFood);
}
TEST(Darwin, frontCreature1) {
  Darwin x(2, 2);
  Species food("food");
  Species notFood("notFood");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  x.addCreature(&notFood, 1, 0, Direction::south);
  Creature *actor = &(x._board[2]._creature);

  ASSERT_EQ(x.frontCreature(*actor), nullptr);
}
TEST(Darwin, frontCreature2) {
  Darwin x(2, 2);
  Species food("food");
  Species notFood("notFood");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  x.addCreature(&notFood, 1, 0, Direction::north);
  Creature *actor = &(x._board[2]._creature);

  ASSERT_EQ(x.frontCreature(*actor), &(x._board[0]._creature));
}
TEST(Darwin, frontCreature3) {
  Darwin x(2, 2);
  Species food("food");
  Species notFood("notFood");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  x.addCreature(&notFood, 1, 0, Direction::east);
  Creature *actor = &(x._board[2]._creature);

  ASSERT_EQ(x.frontCreature(*actor), nullptr);
}

TEST(Darwin, construct1) {
  Darwin x;
  ASSERT_EQ(x._rows, 0);
  ASSERT_EQ(x._columns, 0);
}
TEST(Darwin, construct2) {
  Darwin x(1, 5);
  ASSERT_EQ(x._rows, 1);
  ASSERT_EQ(x._columns, 5);
}
TEST(Darwin, construct3) {
  Darwin x(5, 1);
  ASSERT_EQ(x._rows, 5);
  ASSERT_EQ(x._columns, 1);
}
TEST(Darwin, step1) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);

  x.step();
  ASSERT_EQ(x._board[0]._direction, Direction::east);
  x.step();
  ASSERT_EQ(x._board[0]._direction, Direction::north);
}
TEST(Darwin, step2) {
  Darwin x(2, 2);
  Species food("food");
  Species trap("trap");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);

  trap.addInstruction(Instruction::if_enemy, 3);
  trap.addInstruction(Instruction::left);
  trap.addInstruction(Instruction::go, 0);
  trap.addInstruction(Instruction::infect);
  trap.addInstruction(Instruction::go, 0);
  x.addCreature(&trap, 1, 0, Direction::north);

  x.step();
  ASSERT_EQ(x._board[0]._direction, Direction::east);
  ASSERT_EQ(x._board[1]._direction, Direction::west);
  x.step();
  ASSERT_EQ(x._board[0]._direction, Direction::north);
  ASSERT_EQ(x._board[1]._direction, Direction::west);
  ASSERT_EQ(x._board[0]._creature._species, &trap);
}
TEST(Darwin, step3) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  x.addCreature(&food, 1, 0, Direction::south);

  x.step();
  ASSERT_EQ(x._board[0]._direction, Direction::east);
  ASSERT_EQ(x._board[2]._direction, Direction::east);
  x.step();
  ASSERT_EQ(x._board[0]._direction, Direction::north);
  ASSERT_EQ(x._board[2]._direction, Direction::north);
}
TEST(Darwin, addCreature1) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  ASSERT_EQ(x._board[0]._creature._species, &food);
}
TEST(Darwin, addCreature2) {
  Darwin x(2, 2);
  Species food("food");
  Species notFood("notFood");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  x.addCreature(&notFood, 0, 0, Direction::south);
  ASSERT_EQ(x._board[0]._creature._species, &notFood);
}
TEST(Darwin, addCreature3) {
  Darwin x(2, 2);
  Species food("food");
  food.addInstruction(Instruction::left);
  food.addInstruction(Instruction::go, 0);
  x.addCreature(&food, 0, 0, Direction::south);
  x.addCreature(&food, 1, 0, Direction::south);
  ASSERT_EQ(x._board[0]._creature._species, &food);
  ASSERT_EQ(x._board[2]._creature._species, &food);
}

TEST(Creature, constructor1) {
  Creature x;
  ASSERT_EQ(x._species, &Creature::_default);
}
TEST(Creature, constructor2) {
  Species food("food");
  Creature x(&food);
  ASSERT_EQ(x._species, &food);
}
TEST(Creature, constructor3) {
  Species food("food");
  Creature x(&food);
  ASSERT_EQ(x._programCounter, 0);
}
TEST(Creature, act1) {
  Species trap("trap");
  Species notTrap("notTrap");
  trap.addInstruction(Instruction::if_enemy, 3);
  trap.addInstruction(Instruction::left);
  trap.addInstruction(Instruction::go, 0);
  trap.addInstruction(Instruction::infect);
  trap.addInstruction(Instruction::go, 0);

  Creature x(&trap);
  Creature y(&notTrap);
  ASSERT_EQ(x.act(false, false, &y), Instruction::infect);
}
TEST(Creature, act2) {
  Species trap("trap");
  trap.addInstruction(Instruction::if_enemy, 3);
  trap.addInstruction(Instruction::left);
  trap.addInstruction(Instruction::go, 0);
  trap.addInstruction(Instruction::infect);
  trap.addInstruction(Instruction::go, 0);

  Creature x(&trap);
  ASSERT_EQ(x.act(false, false, nullptr), Instruction::left);
}
TEST(Creature, act3) {
  Species trap("trap");
  trap.addInstruction(Instruction::if_enemy, 3);
  trap.addInstruction(Instruction::left);
  trap.addInstruction(Instruction::go, 0);
  trap.addInstruction(Instruction::infect);
  trap.addInstruction(Instruction::go, 0);

  Creature x(&trap);
  Creature y(&trap);
  ASSERT_EQ(x.act(false, false, &y), Instruction::left);
}
TEST(Creature, infected1) {
  Species trap("trap");

  Creature x(&trap);
  Creature y(&trap);

  x.infected(y);

  ASSERT_EQ(x._species, &trap);
  ASSERT_EQ(x._programCounter, 0);
}
TEST(Creature, infected2) {
  Species trap("trap");
  Species notTrap("notTrap");

  Creature x(&trap);
  Creature y(&notTrap);

  x.infected(y);

  ASSERT_EQ(x._species, &notTrap);
  ASSERT_EQ(x._programCounter, 0);
}

TEST(Species, constructor1) {
  Species x;
  ASSERT_EQ(x._name, ".");
}
TEST(Species, constructor2) {
  Species x("five");
  ASSERT_EQ(x._name, "five");
}
TEST(Species, constructor3) {
  Species x("why");
  ASSERT_EQ(x._name, "why");
}
TEST(Species, act1) {
  Species trap("trap");
  trap.addInstruction(Instruction::if_enemy, 3);
  trap.addInstruction(Instruction::left);
  trap.addInstruction(Instruction::go, 0);
  trap.addInstruction(Instruction::infect);
  trap.addInstruction(Instruction::go, 0);
  ASSERT_EQ(trap.act(0, false, false, false)._instruction, Instruction::left);
  ASSERT_EQ(trap.act(0, false, false, false)._line, 2);
}
TEST(Species, act2) {
  Species trap("trap");
  trap.addInstruction(Instruction::if_enemy, 3);
  trap.addInstruction(Instruction::left);
  trap.addInstruction(Instruction::go, 0);
  trap.addInstruction(Instruction::infect);
  trap.addInstruction(Instruction::go, 0);
  ASSERT_EQ(trap.act(3, false, false, true)._instruction, Instruction::infect);
  ASSERT_EQ(trap.act(3, false, false, true)._line, 4);
}
TEST(Species, act3) {
  Species trap("trap");
  trap.addInstruction(Instruction::if_enemy, 3);
  trap.addInstruction(Instruction::left);
  trap.addInstruction(Instruction::go, 0);
  trap.addInstruction(Instruction::infect);
  trap.addInstruction(Instruction::go, 0);
  ASSERT_EQ(trap.act(0, false, false, true)._instruction, Instruction::infect);
  ASSERT_EQ(trap.act(0, false, false, true)._line, 4);
}
TEST(Species, add1) {
  Species trap("trap");
  trap.addInstruction(Instruction::if_enemy, 3);
  ASSERT_EQ(trap._program.size(), 1);
}
TEST(Species, add2) {
  Species trap("trap");
  trap.addInstruction(Instruction::if_enemy, 3);
  trap.addInstruction(Instruction::left);

  ASSERT_EQ(trap._program[1]._instruction, Instruction::left);
  ASSERT_EQ(trap._program.size(), 2);
}
TEST(Species, add3) {
  Species trap("trap");
  trap.addInstruction(Instruction::if_enemy, 3);
  trap.addInstruction(Instruction::left);
  trap.addInstruction(Instruction::go, 0);

  ASSERT_EQ(trap._program[2]._instruction, Instruction::go);
  ASSERT_EQ(trap._program.size(), 3);
}
