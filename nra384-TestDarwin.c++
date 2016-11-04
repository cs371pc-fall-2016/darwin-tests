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

// ---
// test Species
//

TEST(DarwinFixture, test_ids) {
  Species s("stuff");
  ASSERT_EQ('s', s.GridRep());
}

TEST(DarwinFixture, test_ids_2) {
  Species s;
  ASSERT_EQ('.', s.GridRep());
}

TEST(DarwinFixture, test_ids_3) {
  Species s("a long string");
  ASSERT_EQ('a', s.GridRep());
}

TEST(DarwinFixture, test_commands_1) {
  Species s("a long string");
  s.AddCommand("go 10");
  ASSERT_STREQ("go 10", s.Program(0).c_str());
}

TEST(DarwinFixture, test_commands_2) {
  Species s("a long string");
  s.AddCommand("go 10");
  s.AddCommand("go 9");
  s.AddCommand("go 8");
  s.AddCommand("go 7");
  s.AddCommand("go 6");
  s.AddCommand("go 5");
  ASSERT_STREQ("go 5", s.Program(5).c_str());
}

TEST(DarwinFixture, test_commands_3) {
  Species s("a long string");
  ASSERT_STREQ("", s.Program(0).c_str());
}

TEST(DarwinFixture, test_program_1) {
  Species s("a long string");
  ASSERT_STREQ("", s.Program(-1).c_str());
}

TEST(DarwinFixture, test_program_2) {
  Species s("a long string");
  ASSERT_STREQ("", s.Program(3).c_str());
}

TEST(DarwinFixture, test_program_3) {
  Species s("a long string");
  s.AddCommand("go 10");
  ASSERT_STREQ("go 10", s.Program(0).c_str());
}

// ---
// test creature
// ---

TEST(DarwinFixture, test_creature_1) {
  Creature c;
  ASSERT_EQ(c.curTurn, 0);
  ASSERT_EQ(c.counter, 0);
  ASSERT_EQ(c.spec.GridRep(), '.');
  ASSERT_EQ(c.direction, 0);
  ASSERT_EQ(c.x, 0);
  ASSERT_EQ(c.y, 0);
}

TEST(DarwinFixture, test_creature_2) {
  Species s("spec");
  Creature c(s, 2);
  ASSERT_EQ(c.curTurn, 0);
  ASSERT_EQ(c.counter, 0);
  ASSERT_EQ(c.spec.GridRep(), 's');
  ASSERT_EQ(c.direction, 2);
  ASSERT_EQ(c.x, 0);
  ASSERT_EQ(c.y, 0);
}

TEST(DarwinFixture, test_infected_1) {
  Species f("food");
  f.AddCommand("hop");
  Species h("hopper");
  Creature food(f, 0);
  Darwin x(4, 4);
  food.HaveTurn(1, x);
  ASSERT_EQ(food.counter, 1);
  food.Infected(h);
  ASSERT_EQ(food.counter, 0);
  ASSERT_EQ(food.GridRep(), 'h');
}

TEST(DarwinFixture, test_left_1) {
  Species f("food");
  Creature food(f, 0);
  food.Left();
  ASSERT_EQ(food.direction, 3);
}

TEST(DarwinFixture, test_right_1) {
  Species f("food");
  Creature food(f, 3);
  food.Right();
  ASSERT_EQ(food.direction, 0);
}

TEST(DarwinFixture, test_x_1) {
  Species f("food");
  Creature food(f, 0);
  food.Position(1, 1);
  ASSERT_EQ(food.NextX(), 0);
}

TEST(DarwinFixture, test_x_2) {
  Species f("food");
  Creature food(f, 1);
  food.Position(1, 1);
  ASSERT_EQ(food.NextX(), 1);
}

TEST(DarwinFixture, test_x_3) {
  Species f("food");
  Creature food(f, 2);
  food.Position(1, 1);
  ASSERT_EQ(food.NextX(), 2);
}

TEST(DarwinFixture, test_x_4) {
  Species f("food");
  Creature food(f, 3);
  food.Position(1, 1);
  ASSERT_EQ(food.NextX(), 1);
}

TEST(DarwinFixture, test_x_5) {
  Species f("food");
  Creature food(f, -1);
  ASSERT_EQ(food.NextX(), -1);
}

TEST(DarwinFixture, test_y_1) {
  Species f("food");
  Creature food(f, 0);
  food.Position(1, 1);
  ASSERT_EQ(food.NextY(), 1);
}

TEST(DarwinFixture, test_y_2) {
  Species f("food");
  Creature food(f, 1);
  food.Position(1, 1);
  ASSERT_EQ(food.NextY(), 2);
}

TEST(DarwinFixture, test_y_3) {
  Species f("food");
  Creature food(f, 2);
  food.Position(1, 1);
  ASSERT_EQ(food.NextY(), 1);
}

TEST(DarwinFixture, test_y_4) {
  Species f("food");
  Creature food(f, 3);
  food.Position(1, 1);
  ASSERT_EQ(food.NextY(), 0);
}

TEST(DarwinFixture, test_y_5) {
  Species f("food");
  Creature food(f, -1);
  ASSERT_EQ(food.NextY(), -1);
}

TEST(DarwinFixture, test_turn_1) {
  Species f("food");
  f.AddCommand("hop");
  Creature food(f, 0);
  Darwin x(4, 4);
  food.HaveTurn(1, x);
  ASSERT_EQ(food.counter, 1);
}

TEST(DarwinFixture, test_turn_2) {
  Species f("food");
  f.AddCommand("hop");
  Creature food(f, 0);
  Darwin x(4, 4);
  food.HaveTurn(1, x);
  food.HaveTurn(1, x);
  ASSERT_EQ(food.counter, 1);
}

TEST(DarwinFixture, test_execute_1) {
  Species f("food");
  f.AddCommand("hop");
  Creature food(f, 0);
  Darwin x(4, 4);
  food.HaveTurn(1, x);
  ASSERT_EQ(food.counter, 1);
}

TEST(DarwinFixture, test_execute_2) {
  Species f("food");
  f.AddCommand("left");
  Creature food(f, 0);
  Darwin x(4, 4);
  food.HaveTurn(1, x);
  ASSERT_EQ(food.counter, 1);
  ASSERT_EQ(food.direction, 3);
}

TEST(DarwinFixture, test_execute_3) {
  Species f("food");
  f.AddCommand("right");
  Creature food(f, 0);
  Darwin x(4, 4);
  food.HaveTurn(1, x);
  ASSERT_EQ(food.counter, 1);
  ASSERT_EQ(food.direction, 1);
}

TEST(DarwinFixture, test_execute_4) {
  Species f("food");
  f.AddCommand("go 10");
  Creature food(f, 0);
  Darwin x(4, 4);
  food.HaveTurn(1, x);
  ASSERT_EQ(food.counter, 10);
}

TEST(DarwinFixture, test_execute_5) {
  Species f("food");
  f.AddCommand("infect");
  Creature food(f, 0);
  Darwin x(4, 4);
  food.Position(1, 1);
  food.HaveTurn(1, x);
  ASSERT_EQ(food.counter, 1);
}

TEST(DarwinFixture, test_execute_6) {
  Species f("food");
  f.AddCommand("if_wall 10");
  Creature food(f, 0);
  Darwin x(4, 4);
  food.Position(0, 0);
  food.HaveTurn(1, x);
  ASSERT_EQ(food.counter, 10);
}

TEST(DarwinFixture, test_execute_7) {
  Species f("food");
  f.AddCommand("if_empty 10");
  Creature food(f, 0);
  Darwin x(4, 4);
  food.Position(1, 1);
  food.HaveTurn(1, x);
  ASSERT_EQ(food.counter, 10);
}

TEST(DarwinFixture, test_execute_8) {
  Species f("food");
  Species h("hop");
  f.AddCommand("if_enemy 10");
  Creature food(f, 0);
  Creature hop(h, 0);
  Darwin x(4, 4);
  x.addCreature(hop, 0, 1);
  food.Position(1, 1);
  food.HaveTurn(1, x);
  ASSERT_EQ(food.counter, 10);
}

// ----
// test Darwin
// ----

TEST(DarwinFixture, test_darwin_1) {
  Darwin x(4, 3);
  ASSERT_EQ(x.rows, 4);
  ASSERT_EQ(x.columns, 3);
  ASSERT_EQ(x.turn, 0);
}

TEST(DarwinFixture, test_add_1) {
  Species s("food");
  Creature food1(s, 0);
  Darwin x(4, 4);
  ASSERT_TRUE(x.addCreature(food1, 1, 1));
}

TEST(DarwinFixture, test_add_2) {
  Species s("food");
  Creature food1(s, 0);
  Darwin x(4, 4);
  ASSERT_FALSE(x.addCreature(food1, -1, -1));
}

TEST(DarwinFixture, test_add_3) {
  Species s("food");
  Creature food1(s, 0);
  Creature food2(s, 0);
  Darwin x(4, 4);
  ASSERT_TRUE(x.addCreature(food1, 1, 1));
  ASSERT_FALSE(x.addCreature(food2, 1, 1));
}

TEST(DarwinFixture, test_wall_1) {
  Darwin x(4, 4);
  ASSERT_TRUE(x.Wall(-1, 0));
}

TEST(DarwinFixture, test_wall_2) {
  Darwin x(4, 4);
  ASSERT_TRUE(x.Wall(0, -1));
}

TEST(DarwinFixture, test_wall_3) {
  Darwin x(4, 4);
  ASSERT_FALSE(x.Wall(0, 0));
}

TEST(DarwinFixture, test_empty_1) {
  Darwin x(4, 4);
  ASSERT_TRUE(x.Empty(0, 0));
}

TEST(DarwinFixture, test_empty_2) {
  Darwin x(4, 4);
  ASSERT_FALSE(x.Empty(-1, 0));
}

TEST(DarwinFixture, test_empty_3) {
  Species s("food");
  Creature food1(s, 0);
  Darwin x(4, 4);
  x.addCreature(food1, 1, 1);
  ASSERT_FALSE(x.Empty(1, 1));
}

TEST(DarwinFixture, test_diff_1) {
  Species s("food");
  Creature food1(s, 0);
  Darwin x(4, 4);
  x.addCreature(food1, 1, 1);
  ASSERT_FALSE(x.DiffSpec(1, 1, s));
}

TEST(DarwinFixture, test_diff_2) {
  Species s("food");
  Darwin x(4, 4);
  ASSERT_FALSE(x.DiffSpec(1, 1, s));
}

TEST(DarwinFixture, test_diff_3) {
  Species s("food");
  Darwin x(4, 4);
  ASSERT_FALSE(x.DiffSpec(-1, 1, s));
}

TEST(DarwinFixture, test_diff_4) {
  Species f("food");
  Species t("trap");
  Creature food1(f, 0);
  Darwin x(4, 4);
  x.addCreature(food1, 1, 1);
  ASSERT_TRUE(x.DiffSpec(1, 1, t));
}

TEST(DarwinFixture, test_can_move_1) {
  Species f("food");
  Creature food1(f, 0);
  Darwin x(4, 4);
  x.addCreature(food1, 1, 1);
  ASSERT_FALSE(x.CanMove(1, 1));
}

TEST(DarwinFixture, test_can_move_2) {
  Darwin x(4, 4);
  ASSERT_FALSE(x.CanMove(-1, 1));
}

TEST(DarwinFixture, test_can_move_3) {
  Darwin x(4, 4);
  ASSERT_TRUE(x.CanMove(1, 1));
}

TEST(DarwinFixture, test_move_1) {
  Species f("food");
  Creature food1(f, 0);
  Darwin x(4, 4);
  x.addCreature(food1, 1, 1);
  x.Move(1, 1, 2, 2);
  ASSERT_EQ(x.grid[1][1].GridRep(), '.');
  ASSERT_EQ(x.grid[2][2].GridRep(), 'f');
}

TEST(DarwinFixture, test_move_2) {
  Species f("food");
  Creature food1(f, 0);
  Darwin x(4, 4);
  x.addCreature(food1, 1, 1);
  x.Move(1, 1, -1, -1);
  ASSERT_EQ(x.grid[1][1].GridRep(), 'f');
}

TEST(DarwinFixture, test_run_1) {
  Species s("food");
  s.AddCommand("a");
  s.AddCommand("2");
  Creature food1(s, 0);
  Darwin x(4, 4);
  ASSERT_TRUE(x.addCreature(food1, 1, 1));
  x.RunTurn();
  x.RunTurn();
  ASSERT_EQ(x.grid[1][1].curTurn, 2);
}

TEST(DarwinFixture, test_run_2) {
  Darwin x(4, 4);
  x.RunTurn();
  x.RunTurn();
  ASSERT_EQ(x.turn, 2);
}

TEST(DarwinFixture, test_infect_1) {
  Species s("food");
  Species h("hopper");
  Darwin x(4, 4);
  Creature food1(s, 0);
  ASSERT_TRUE(x.addCreature(food1, 1, 1));
  x.Infect(1, 1, h);
  ASSERT_EQ(x.grid[1][1].GridRep(), 'h');
}

TEST(DarwinFixture, test_print_1) {
  Darwin x(1, 2);
  ASSERT_STREQ("  01\n0 ..\n", x.PrintGrid().c_str());
}

TEST(DarwinFixture, test_print_2) {
  Darwin x(4, 4);
  ASSERT_STREQ("  0123\n0 ....\n1 ....\n2 ....\n3 ....\n",
               x.PrintGrid().c_str());
}

TEST(DarwinFixture, test_print_3) {
  Species s("food");
  Creature c(s, 0);
  Darwin x(4, 4);
  x.addCreature(c, 1, 1);
  ASSERT_STREQ("  0123\n0 ....\n1 .f..\n2 ....\n3 ....\n",
               x.PrintGrid().c_str());
}

TEST(DarwinFixture, test_transform_1) { ASSERT_EQ(Transform(0), 3); }

TEST(DarwinFixture, test_transform_2) { ASSERT_EQ(Transform(1), 0); }

TEST(DarwinFixture, test_transform_3) { ASSERT_EQ(Transform(2), 1); }

TEST(DarwinFixture, test_transform_4) { ASSERT_EQ(Transform(3), 2); }
