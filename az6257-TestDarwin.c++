// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <sstream> // istringtstream, ostringstream
#include <stdlib.h>

#include "Darwin.h"
#include "gtest/gtest.h"

// ----
// test
// ----

/* Test Darwin Execute method */

TEST(Darwin_execute_print, test_execute_print_1) {
  Darwin d(1, 1);

  Species hopper('h');
  hopper.addInstruction(Instruction::HOP, -1); // hop
  hopper.addInstruction(Instruction::GO, 0);   // go 0

  Creature hopper1_D(0, Direction::NORTH, &hopper);
  d.addCreature(&hopper1_D, 0, 0);

  std::ostringstream w1, w2;

  d.print(w1);

  ASSERT_EQ("  0\n0 h\n\n", w1.str());

  d.execute(1);

  d.print(w2);

  ASSERT_EQ("  0\n0 h\n\n", w2.str());
}

TEST(Darwin_execute_print, test_execute_print_2) {
  Darwin d(4, 4);

  Species hopper('h');
  hopper.addInstruction(Instruction::HOP, -1); // hop
  hopper.addInstruction(Instruction::GO, 0);   // go 0

  Creature hopper1_D(0, Direction::EAST, &hopper);
  d.addCreature(&hopper1_D, 2, 2);

  std::ostringstream w1, w2;

  d.print(w1);

  ASSERT_EQ("  0123\n0 ....\n1 ....\n2 ..h.\n3 ....\n\n", w1.str());

  d.execute(1);

  d.print(w2);

  ASSERT_EQ("  0123\n0 ....\n1 ....\n2 ...h\n3 ....\n\n", w2.str());
}

TEST(Darwin_execute_print, test_execute_print_3) {
  Darwin d(16, 16);

  Species food('f');
  food.addInstruction(Instruction::LEFT, -1); // left
  food.addInstruction(Instruction::GO, 0);    // go 0

  Species hopper('h');
  hopper.addInstruction(Instruction::HOP, -1); // hop
  hopper.addInstruction(Instruction::GO, 0);   // go 0

  Species trap('t');
  trap.addInstruction(Instruction::IF_ENEMY, 3); // if_enemy 3
  trap.addInstruction(Instruction::LEFT, -1);    // left
  trap.addInstruction(Instruction::GO, 0);       // go 0
  trap.addInstruction(Instruction::INFECT, -1);  // infect
  trap.addInstruction(Instruction::GO, 0);       // go 0

  Species best('b');
  best.addInstruction(Instruction::IF_ENEMY, 6); // if_enemy 9
  best.addInstruction(Instruction::IF_EMPTY, 4); // if_empty 7
  best.addInstruction(Instruction::LEFT, -1);    // left
  best.addInstruction(Instruction::GO, 0);       // go 0
  best.addInstruction(Instruction::HOP, -1);     // hop
  best.addInstruction(Instruction::GO, 0);       // go 0
  best.addInstruction(Instruction::INFECT, -1);  // infect
  best.addInstruction(Instruction::GO, 0);       // go 0

  Creature food1_D(0, Direction::EAST, &food);
  Creature food2_D(0, Direction::NORTH, &food);
  Creature hopper1_D(0, Direction::EAST, &hopper);
  Creature hopper2_D(0, Direction::SOUTH, &hopper);
  Creature trap1_D(0, Direction::EAST, &trap);
  Creature trap2_D(0, Direction::NORTH, &trap);
  Creature best1_D(0, Direction::WEST, &best);
  Creature best2_D(0, Direction::NORTH, &best);
  d.addCreature(&food1_D, 5, 5);
  d.addCreature(&food2_D, 4, 4);
  d.addCreature(&hopper1_D, 6, 13);
  d.addCreature(&hopper2_D, 3, 2);
  d.addCreature(&trap1_D, 9, 10);
  d.addCreature(&trap2_D, 15, 1);
  d.addCreature(&best1_D, 12, 13);
  d.addCreature(&best2_D, 10, 7);

  std::ostringstream w1, w2;

  d.print(w1);

  ASSERT_EQ("  0123456789012345\n0 ................\n1 ................\n2 "
            "................\n3 ..h.............\n4 ....f...........\n5 "
            ".....f..........\n6 .............h..\n7 ................\n8 "
            "................\n9 ..........t.....\n0 .......b........\n1 "
            "................\n2 .............b..\n3 ................\n4 "
            "................\n5 .t..............\n\n",
            w1.str());

  for (int i = 1; i <= 30; ++i) {
    d.execute(i);
  }

  d.print(w2);

  ASSERT_EQ("  0123456789012345\n0 ................\n1 ................\n2 "
            "................\n3 ................\n4 ....f...........\n5 "
            ".....f..........\n6 ...............h\n7 ................\n8 "
            "..b.............\n9 ..........t.....\n0 ................\n1 "
            "b...............\n2 ................\n3 ................\n4 "
            "................\n5 .tt.............\n\n",
            w2.str());
}

/* Test Darwin isValid method in all four directions */

TEST(Darwin_isValid, test_invalid_1) {
  Darwin x(5, 5);

  // Check top of map
  bool valid = x.isValid(std::pair<int, int>(-1, 1));
  ASSERT_FALSE(valid);
}

TEST(Darwin_isValid, test_invalid_2) {
  Darwin x(5, 5);

  // Check bottom of map
  bool valid = x.isValid(std::pair<int, int>(10, 1));
  ASSERT_FALSE(valid);
}

TEST(Darwin_isValid, test_invalid_3) {
  Darwin x(5, 5);

  // Check left of map
  bool valid = x.isValid(std::pair<int, int>(3, -1));
  ASSERT_FALSE(valid);
}

TEST(Darwin_isValid, test_invalid_4) {
  Darwin x(5, 5);

  // Check right of map
  bool valid = x.isValid(std::pair<int, int>(3, 10));
  ASSERT_FALSE(valid);
}

TEST(Darwin_isValid, test_valid_1) {
  Darwin x(5, 5);

  // Check middle of map
  bool valid = x.isValid(std::pair<int, int>(3, 3));
  ASSERT_TRUE(valid);
}

/* Testing Darwin's isWall method in all four directions */

TEST(Darwin_isWall, test_wall_1) {
  Darwin x(5, 5);
  bool wall = x.isWall(std::pair<int, int>(-1, 1));
  ASSERT_TRUE(wall);
}

TEST(Darwin_isWall, test_wall_2) {
  Darwin x(5, 5);
  bool wall = x.isWall(std::pair<int, int>(10, 1));
  ASSERT_TRUE(wall);
}

TEST(Darwin_isWall, test_wall_3) {
  Darwin x(5, 5);
  bool wall = x.isWall(std::pair<int, int>(3, -1));
  ASSERT_TRUE(wall);
}

TEST(Darwin_isWall, test_wall_4) {
  Darwin x(5, 5);
  bool wall = x.isWall(std::pair<int, int>(3, 10));
  ASSERT_TRUE(wall);
}

TEST(Darwin_isWall, test_not_wall_1) {
  Darwin x(5, 5);
  bool wall = x.isWall(std::pair<int, int>(3, 3));
  ASSERT_FALSE(wall);
}

/* Testing Darwin addCreature and isEmpty */

TEST(Darwin_addCreature, test_single_1) {
  Darwin x(5, 5);
  Species food('f');
  Creature food1(0, Direction::NORTH, &food);

  x.addCreature(&food1, 3, 3);
  bool empty = x.isEmpty(std::pair<int, int>(3, 3));
  ASSERT_FALSE(empty);
}

TEST(Darwin_addCreature, test_single_2) {
  Darwin x(5, 5);
  Species food('f');
  Creature food1(0, Direction::NORTH, &food);

  x.addCreature(&food1, 0, 0);
  bool empty = x.isEmpty(std::pair<int, int>(0, 0));
  ASSERT_FALSE(empty);
}

TEST(Darwin_addCreature, test_single_3) {
  Darwin x(5, 5);
  Species food('f');
  Creature food1(0, Direction::NORTH, &food);

  x.addCreature(&food1, 2, 4);
  bool empty = x.isEmpty(std::pair<int, int>(2, 4));
  ASSERT_FALSE(empty);
}

TEST(Darwin_addCreature, test_multiple_1) {
  Darwin x(5, 5);
  Species food('f');
  Creature food1(0, Direction::NORTH, &food);
  Creature food2(0, Direction::NORTH, &food);
  Creature food3(0, Direction::NORTH, &food);

  x.addCreature(&food1, 2, 4);
  x.addCreature(&food2, 2, 3);
  x.addCreature(&food3, 2, 2);
  bool empty1 = x.isEmpty(std::pair<int, int>(2, 4));
  bool empty2 = x.isEmpty(std::pair<int, int>(2, 3));
  bool empty3 = x.isEmpty(std::pair<int, int>(2, 2));
  ASSERT_FALSE(empty1);
  ASSERT_FALSE(empty2);
  ASSERT_FALSE(empty3);
}

TEST(Darwin_addCreature, test_multiple_2) {
  Darwin x(5, 5);
  Species food('f');
  Creature food1(0, Direction::NORTH, &food);
  Creature food2(0, Direction::NORTH, &food);
  Creature food3(0, Direction::NORTH, &food);
  Species rover('r');
  Creature rover1(0, Direction::NORTH, &rover);
  Creature rover2(0, Direction::NORTH, &rover);
  Creature rover3(0, Direction::NORTH, &rover);

  x.addCreature(&food1, 2, 4);
  x.addCreature(&food2, 2, 3);
  x.addCreature(&food3, 2, 2);
  x.addCreature(&rover1, 1, 4);
  x.addCreature(&rover2, 1, 3);
  x.addCreature(&rover3, 1, 2);
  bool empty1 = x.isEmpty(std::pair<int, int>(2, 4));
  bool empty2 = x.isEmpty(std::pair<int, int>(2, 3));
  bool empty3 = x.isEmpty(std::pair<int, int>(2, 2));
  bool empty4 = x.isEmpty(std::pair<int, int>(1, 4));
  bool empty5 = x.isEmpty(std::pair<int, int>(1, 3));
  bool empty6 = x.isEmpty(std::pair<int, int>(1, 2));
  bool empty7 = x.isEmpty(std::pair<int, int>(0, 0));
  bool empty8 = x.isEmpty(std::pair<int, int>(0, 1));
  ASSERT_FALSE(empty1);
  ASSERT_FALSE(empty2);
  ASSERT_FALSE(empty3);
  ASSERT_FALSE(empty4);
  ASSERT_FALSE(empty5);
  ASSERT_FALSE(empty6);
  ASSERT_TRUE(empty7);
  ASSERT_TRUE(empty8);
}

/* Test Creature's Left and Right and inFront Methods */
TEST(Creature_left, test_north) {
  Species food('f');
  Creature food1(0, Direction::NORTH, &food);

  food1.left();

  std::pair<int, int> coord(3, 3);
  std::pair<int, int> front = food1.inFront(coord);

  ASSERT_EQ(front.first, 3);
  ASSERT_EQ(front.second, 2);
}
TEST(Creature_left, test_east) {
  Species food('f');
  Creature food1(0, Direction::EAST, &food);

  food1.left();

  std::pair<int, int> coord(3, 3);
  std::pair<int, int> front = food1.inFront(coord);

  ASSERT_EQ(front.first, 2);
  ASSERT_EQ(front.second, 3);
}
TEST(Creature_left, test_south) {
  Species food('f');
  Creature food1(0, Direction::SOUTH, &food);

  food1.left();

  std::pair<int, int> coord(3, 3);
  std::pair<int, int> front = food1.inFront(coord);

  ASSERT_EQ(front.first, 3);
  ASSERT_EQ(front.second, 4);
}
TEST(Creature_left, test_west) {
  Species food('f');
  Creature food1(0, Direction::WEST, &food);

  food1.left();

  std::pair<int, int> coord(3, 3);
  std::pair<int, int> front = food1.inFront(coord);

  ASSERT_EQ(front.first, 4);
  ASSERT_EQ(front.second, 3);
}

TEST(Creature_right, test_north) {
  Species food('f');
  Creature food1(0, Direction::NORTH, &food);

  food1.right();

  std::pair<int, int> coord(3, 3);
  std::pair<int, int> front = food1.inFront(coord);

  ASSERT_EQ(front.first, 3);
  ASSERT_EQ(front.second, 4);
}
TEST(Creature_right, test_east) {
  Species food('f');
  Creature food1(0, Direction::EAST, &food);

  food1.right();

  std::pair<int, int> coord(3, 3);
  std::pair<int, int> front = food1.inFront(coord);

  ASSERT_EQ(front.first, 4);
  ASSERT_EQ(front.second, 3);
}
TEST(Creature_right, test_south) {
  Species food('f');
  Creature food1(0, Direction::SOUTH, &food);

  food1.right();

  std::pair<int, int> coord(3, 3);
  std::pair<int, int> front = food1.inFront(coord);

  ASSERT_EQ(front.first, 3);
  ASSERT_EQ(front.second, 2);
}
TEST(Creature_right, test_west) {
  Species food('f');
  Creature food1(0, Direction::WEST, &food);

  food1.right();

  std::pair<int, int> coord(3, 3);
  std::pair<int, int> front = food1.inFront(coord);

  ASSERT_EQ(front.first, 2);
  ASSERT_EQ(front.second, 3);
}

/* Test increment PC */

TEST(Creature_incrementPC, test_1) {
  Species food('f');
  Creature food1(0);

  food1.incrementPC();
  ASSERT_EQ(food1.pc, 1);
}

TEST(Creature_incrementPC, test_2) {
  Species food('f');
  Creature food1(5);

  food1.incrementPC();
  ASSERT_EQ(food1.pc, 6);
}

TEST(Creature_incrementPC, test_3) {
  Species food('f');
  Creature food1(2);

  food1.incrementPC();
  food1.incrementPC();
  food1.incrementPC();
  ASSERT_EQ(food1.pc, 5);
}

/* Test increment EC */

TEST(Creature_incrementEC, test_1) {
  Species food('f');
  Creature food1(0);

  food1.incrementEC();
  ASSERT_EQ(food1.ec, 1);
}

TEST(Creature_incrementEC, test_2) {
  Species food('f');
  Creature food1(0);

  food1.incrementEC();
  food1.incrementEC();
  ASSERT_EQ(food1.ec, 2);
}

TEST(Creature_incrementEC, test_3) {
  Species food('f');
  Creature food1(2);

  food1.incrementEC();
  food1.incrementEC();
  food1.incrementEC();
  ASSERT_EQ(food1.ec, 3);
}

/* Test has executed */

TEST(Creature_hasExecuted, test_1) {
  Species food('f');
  Creature food1(0);

  food1.incrementEC();
  ASSERT_TRUE(food1.hasExecuted(1));
}

TEST(Creature_hasExecuted, test_2) {
  Species food('f');
  Creature food1(0);

  food1.incrementEC();
  food1.incrementEC();
  ASSERT_TRUE(food1.hasExecuted(2));
}

TEST(Creature_hasExecuted, test_3) {
  Species food('f');
  Creature food1(0);

  food1.incrementEC();
  food1.incrementEC();
  food1.incrementEC();
  ASSERT_TRUE(food1.hasExecuted(3));
}

/* Test isEnemy */

TEST(Creature_isEnemy, test_enemy_1) {
  Species food('f');
  Species rover('r');
  Creature food1(0, Direction::NORTH, &food);
  Creature rover1(0, Direction::NORTH, &rover);
  Creature *rover1_p = &rover1;

  ASSERT_TRUE(food1.isEnemy(rover1_p));
}

TEST(Creature_isEnemy, test_enemy_2) {
  Species food('f');
  Species trap('t');
  Creature food1(0, Direction::NORTH, &food);
  Creature trap1(5, Direction::SOUTH, &trap);
  Creature *trap1_p = &trap1;

  ASSERT_TRUE(food1.isEnemy(trap1_p));
}

TEST(Creature_isEnemy, test_friend_1) {
  Species food('f');
  Creature food1(0, Direction::NORTH, &food);
  Creature food2(0, Direction::NORTH, &food);
  Creature *food2_p = &food1;

  ASSERT_FALSE(food1.isEnemy(food2_p));
}

TEST(Creature_isEnemy, test_friend_2) {
  Species food('f');
  Creature food1(0, Direction::NORTH, &food);
  Creature food2(5, Direction::SOUTH, &food);
  Creature *food2_p = &food1;

  ASSERT_FALSE(food1.isEnemy(food2_p));
}

/* Creature infect */

TEST(Creature_infect, test_infect_1) {
  Species food('f');
  Species rover('r');
  Creature food1(0, Direction::NORTH, &food);
  Creature rover1(0, Direction::NORTH, &rover);

  Creature *rover1_p = &rover1;
  food1.infect(rover1_p);

  std::ostringstream w;
  rover1.print(w);
  ASSERT_EQ("f", w.str());
}

TEST(Creature_infect, test_infect_2) {
  Species food('f');
  Species rover('b');
  Creature food1(0, Direction::NORTH, &food);
  Creature rover1(0, Direction::NORTH, &rover);

  Creature *rover1_p = &rover1;
  food1.infect(rover1_p);

  std::ostringstream w;
  rover1.print(w);
  ASSERT_EQ("f", w.str());
}

TEST(Creature_infect, test_infect_3) {
  Species food('r');
  Species rover('r');
  Creature food1(0, Direction::NORTH, &food);
  Creature rover1(0, Direction::NORTH, &rover);

  Creature *rover1_p = &rover1;
  food1.infect(rover1_p);

  std::ostringstream w;
  rover1.print(w);
  ASSERT_EQ("r", w.str());
}

/* Creature step */

TEST(Creature_step, test_step_1) {
  Species food('f');
  food.addInstruction(Instruction::HOP, -1);
  food.addInstruction(Instruction::HOP, 0);
  food.addInstruction(Instruction::LEFT, 1);
  food.addInstruction(Instruction::HOP, 2);
  food.addInstruction(Instruction::HOP, 3);

  Creature food1(0, Direction::NORTH, &food);
  ASSERT_EQ(food1.step(), Instruction::HOP);
  ++food1.pc;
  ASSERT_EQ(food1.step(), Instruction::HOP);
  ++food1.pc;
  ASSERT_EQ(food1.step(), Instruction::LEFT);
  ++food1.pc;
}

TEST(Creature_step, test_step_2) {
  Species food('f');
  food.addInstruction(Instruction::GO, -1);
  food.addInstruction(Instruction::RIGHT, 0);
  food.addInstruction(Instruction::LEFT, 1);
  food.addInstruction(Instruction::HOP, 2);
  food.addInstruction(Instruction::HOP, 3);

  Creature food1(0, Direction::NORTH, &food);
  ASSERT_EQ(food1.step(), Instruction::GO);
  ++food1.pc;
  ASSERT_EQ(food1.step(), Instruction::RIGHT);
  ++food1.pc;
  ASSERT_EQ(food1.step(), Instruction::LEFT);
  ++food1.pc;
}

TEST(Creature_step, test_step_3) {
  Species food('f');
  food.addInstruction(Instruction::IF_RANDOM, 5);
  food.addInstruction(Instruction::IF_WALL, 0);
  food.addInstruction(Instruction::LEFT, 1);
  food.addInstruction(Instruction::HOP, 2);
  food.addInstruction(Instruction::HOP, 3);

  Creature food1(0, Direction::NORTH, &food);
  ASSERT_EQ(food1.step(), Instruction::IF_RANDOM);
  ++food1.pc;
  ASSERT_EQ(food1.step(), Instruction::IF_WALL);
  ++food1.pc;
  ASSERT_EQ(food1.step(), Instruction::LEFT);
  ++food1.pc;
}

/* Creature take jump */
TEST(Creature_takeJump, test_jump_1) {
  Species food('f');
  food.addInstruction(Instruction::IF_WALL, 2);
  food.addInstruction(Instruction::HOP, -1);
  food.addInstruction(Instruction::LEFT, -1);

  Creature food1(0, Direction::NORTH, &food);

  ASSERT_EQ(food1.step(), Instruction::IF_WALL);
  food1.takeJump();
  ASSERT_EQ(food1.step(), Instruction::LEFT);
}

TEST(Creature_takeJump, test_jump_2) {
  Species food('f');
  food.addInstruction(Instruction::IF_WALL, 5);
  food.addInstruction(Instruction::HOP, -1);
  food.addInstruction(Instruction::LEFT, -1);
  food.addInstruction(Instruction::LEFT, -1);
  food.addInstruction(Instruction::LEFT, -1);
  food.addInstruction(Instruction::RIGHT, -1);
  food.addInstruction(Instruction::LEFT, -1);

  Creature food1(0, Direction::NORTH, &food);

  ASSERT_EQ(food1.step(), Instruction::IF_WALL);
  food1.takeJump();
  ASSERT_EQ(food1.step(), Instruction::RIGHT);
}

TEST(Creature_takeJump, test_jump_3) {
  Species food('f');
  food.addInstruction(Instruction::IF_WALL, 3);
  food.addInstruction(Instruction::HOP, -1);
  food.addInstruction(Instruction::LEFT, -1);
  food.addInstruction(Instruction::IF_EMPTY, 5);
  food.addInstruction(Instruction::LEFT, -1);
  food.addInstruction(Instruction::RIGHT, -1);
  food.addInstruction(Instruction::LEFT, -1);

  Creature food1(0, Direction::NORTH, &food);

  ASSERT_EQ(food1.step(), Instruction::IF_WALL);
  food1.takeJump();
  ASSERT_EQ(food1.step(), Instruction::IF_EMPTY);
  food1.takeJump();
  ASSERT_EQ(food1.step(), Instruction::RIGHT);
}

/* Creature Print */

TEST(Creature_print, test_print_1) {
  Species food('f');
  Creature food1(0, Direction::NORTH, &food);
  std::ostringstream w;
  food1.print(w);

  ASSERT_EQ("f", w.str());
}

TEST(Creature_print, test_print_2) {
  Species food('b');
  Creature food1(0, Direction::NORTH, &food);
  std::ostringstream w;
  food1.print(w);

  ASSERT_EQ("b", w.str());
}

TEST(Creature_print, test_print_3) {
  Species food('r');
  Creature food1(0, Direction::NORTH, &food);
  std::ostringstream w;
  food1.print(w);

  ASSERT_EQ("r", w.str());
}

/* Species Add Instruction and Get Action */
TEST(Species_add, test_single_1) {
  Species food('f');
  food.addInstruction(Instruction::HOP, -1);
  ASSERT_EQ(food.getAction(0), Instruction::HOP);
}

TEST(Species_add, test_single_2) {
  Species food('f');
  food.addInstruction(Instruction::IF_RANDOM, -1);
  ASSERT_EQ(food.getAction(0), Instruction::IF_RANDOM);
}

TEST(Species_add, test_single_3) {
  Species food('f');
  food.addInstruction(Instruction::GO, -1);
  ASSERT_EQ(food.getAction(0), Instruction::GO);
}

TEST(Species_add, test_multiple_1) {
  Species food('f');
  food.addInstruction(Instruction::HOP, -1);
  food.addInstruction(Instruction::GO, -1);
  food.addInstruction(Instruction::HOP, -1);
  ASSERT_EQ(food.getAction(0), Instruction::HOP);
}

TEST(Species_add, test_multiple_2) {
  Species food('f');
  food.addInstruction(Instruction::HOP, -1);
  food.addInstruction(Instruction::GO, -1);
  food.addInstruction(Instruction::HOP, -1);
  ASSERT_EQ(food.getAction(1), Instruction::GO);
}

TEST(Species_add, test_multiple_3) {
  Species food('f');
  food.addInstruction(Instruction::HOP, -1);
  food.addInstruction(Instruction::GO, -1);
  food.addInstruction(Instruction::HOP, -1);
  ASSERT_EQ(food.getAction(2), Instruction::HOP);
}

TEST(Species_add, test_multiple_4) {
  Species food('f');
  food.addInstruction(Instruction::HOP, -1);
  food.addInstruction(Instruction::GO, -1);
  food.addInstruction(Instruction::HOP, -1);
  food.addInstruction(Instruction::HOP, -1);
  food.addInstruction(Instruction::LEFT, -1);
  food.addInstruction(Instruction::HOP, -1);
  ASSERT_EQ(food.getAction(4), Instruction::LEFT);
}

/* Species Get Action Aux */

TEST(Species_get_aux, test_single_1) {
  Species food('f');
  food.addInstruction(Instruction::HOP, -1);
  ASSERT_EQ(food.getActionAux(0), -1);
}

TEST(Species_get_aux, test_single_2) {
  Species food('f');
  food.addInstruction(Instruction::HOP, 1);
  ASSERT_EQ(food.getActionAux(0), 1);
}

TEST(Species_get_aux, test_single_3) {
  Species food('f');
  food.addInstruction(Instruction::HOP, 55);
  ASSERT_EQ(food.getActionAux(0), 55);
}

TEST(Species_get_aux, test_multiple_1) {
  Species food('f');
  food.addInstruction(Instruction::HOP, -1);
  food.addInstruction(Instruction::HOP, 0);
  food.addInstruction(Instruction::HOP, 1);
  food.addInstruction(Instruction::HOP, 2);
  food.addInstruction(Instruction::HOP, 3);
  ASSERT_EQ(food.getActionAux(0), -1);
  ASSERT_EQ(food.getActionAux(1), 0);
  ASSERT_EQ(food.getActionAux(2), 1);
  ASSERT_EQ(food.getActionAux(3), 2);
  ASSERT_EQ(food.getActionAux(4), 3);
}

/* Species Print */

TEST(Species_print, test_print_1) {
  Species food('f');
  std::ostringstream w;
  food.print(w);

  ASSERT_EQ("f", w.str());
}

TEST(Species_print, test_print_2) {
  Species rover('r');
  std::ostringstream w;
  rover.print(w);

  ASSERT_EQ("r", w.str());
}

TEST(Species_print, test_print_3) {
  Species rover('b');
  std::ostringstream w;
  rover.print(w);

  ASSERT_EQ("b", w.str());
}
