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
#include <string>

using namespace std;

class DarwinFixture : public ::testing::Test {
protected:
  /* Instruction */
  string getOpcode(Instruction &i) { return i._instr; }
  int getArg(Instruction &i) { return i._arg; }

  /* Species */
  string getName(Species &s) { return s._name; }

  std::vector<Instruction> getProgram(Species &s) { return s._program; }

  /* Creature */
  Species *getSpecies(Creature &c) { return c._s; }

  Direction getDirection(Creature &c) { return c._d; }

  unsigned int getPc(Creature &c) { return c._pc; }

  unsigned int getId(Creature &c) { return c._id; }

  void setPc(Creature &c, unsigned int pc) { c._pc = pc; }

  /* Darwin */
  std::vector<Creature *> &getGrid(Darwin &d) { return d._grid; }

  unsigned int row(Darwin &d, unsigned int i) { return d.calcRow(i); }

  unsigned int col(Darwin &d, unsigned int i) { return d.calcCol(i); }

  unsigned int getCols(Darwin &d) { return d._cols; }

  unsigned int getRows(Darwin &d) { return d._rows; }

  /* Simulator */
  Darwin &getDarwin(Simulator &s) { return s._d; }

  std::map<Creature *, bool> &getMap(Simulator &s) { return s._turn_map; }
};
// ----
// test
// ----

/* Instruction Tests */

TEST_F(DarwinFixture, is_control_test1) {

  Instruction i("hop", -1);
  ASSERT_FALSE(i.is_control());
}

TEST_F(DarwinFixture, is_control_test2) {

  Instruction i("go", 3);
  ASSERT_TRUE(i.is_control());
}

TEST_F(DarwinFixture, is_control_test3) {

  Instruction i("if_wall", 2);
  ASSERT_TRUE(i.is_control());
}

TEST_F(DarwinFixture, is_opcode_test1) {

  Instruction i("hop", -1);
  ASSERT_TRUE(i.is_opcode("hop"));
}

TEST_F(DarwinFixture, is_opcode_test2) {

  Instruction i("gone", 3);
  ASSERT_FALSE(i.is_opcode("go"));
}

TEST_F(DarwinFixture, is_opcode_test3) {

  Instruction i("if_wall", 2);
  ASSERT_TRUE(i.is_opcode("if_wall"));
}

TEST_F(DarwinFixture, arg_test1) {

  Instruction i("hop", -1);
  ASSERT_TRUE(i.arg() == -1);
}

TEST_F(DarwinFixture, arg_test2) {

  Instruction i("gone", 3);
  ASSERT_FALSE(i.arg() == 1);
}

TEST_F(DarwinFixture, arg_test3) {

  Instruction i("if_wall", 2);
  ASSERT_TRUE(i.arg() == 2);
}

/* Species Tests */

TEST_F(DarwinFixture, addInstruction_test1) {
  Species s("hopper");
  s.addInstruction("hop");
  Instruction i = getProgram(s)[0];

  ASSERT_TRUE(getOpcode(i) == "hop");
  ASSERT_TRUE(getArg(i) == -1);
}

TEST_F(DarwinFixture, addInstruction_test2) {
  Species s("hopper");
  s.addInstruction("hop");
  s.addInstruction("go", 3);
  Instruction i = getProgram(s)[0];

  ASSERT_TRUE(getOpcode(i) == "hop");
  i = getProgram(s)[1];
  ASSERT_TRUE(getOpcode(i) == "go");
  ASSERT_TRUE(getArg(i) == 3);
}

TEST_F(DarwinFixture, addInstruction_test3) {
  Species s("hopper");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("left");
  Instruction i = getProgram(s)[0];

  ASSERT_TRUE(getOpcode(i) == "go");
  i = getProgram(s)[2];
  ASSERT_FALSE(getOpcode(i) == "go");
  ASSERT_TRUE(getArg(i) == -1);
}

TEST_F(DarwinFixture, lineAt_test1) {
  Species s("hopper");
  s.addInstruction("hop");
  Instruction i = getProgram(s)[0];
  Instruction j = s.lineAt(0);
  ASSERT_TRUE(i == j);
}

TEST_F(DarwinFixture, lineAt_test2) {
  Species s("hopper");
  s.addInstruction("hop");
  s.addInstruction("go", 3);
  Instruction i = getProgram(s)[1];
  Instruction j = s.lineAt(1);
  ASSERT_TRUE(i == j);
}

TEST_F(DarwinFixture, lineAt_test3) {
  Species s("hopper");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("left");
  Instruction i = getProgram(s)[2];
  Instruction j = s.lineAt(2);

  ASSERT_TRUE(i == j);
}

TEST_F(DarwinFixture, species_print_test1) {
  Species s("hopper");
  ostringstream o;
  o << s;
  ASSERT_TRUE(o.str() == "h");
}

TEST_F(DarwinFixture, species_print_test2) {
  Species s("food");
  ostringstream o;
  o << s;
  ASSERT_TRUE(o.str() == "f");
}

TEST_F(DarwinFixture, species_print_test3) {
  Species s("unicorn");
  ostringstream o;
  o << s;
  ASSERT_TRUE(o.str() == "u");
}

TEST_F(DarwinFixture, end_1) {
  Species s("hopper");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("left");
  ASSERT_TRUE(s.end(2));
}

TEST_F(DarwinFixture, end_2) {
  Species s("food");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");
  ASSERT_FALSE(s.end(1));
}

TEST_F(DarwinFixture, end_3) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");
  ASSERT_TRUE(s.end(3));
}

/* Creature tests */
TEST_F(DarwinFixture, next_move_test1) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");

  Creature c(&s, WEST, 0);
  Instruction i("go", 2);
  ASSERT_TRUE(c.next_move() == i);
}

TEST_F(DarwinFixture, next_move_test2) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");

  Creature c(&s, WEST, 0);
  Instruction i("hop", -1);
  setPc(c, 2);
  ASSERT_TRUE(c.next_move() == i);
}

TEST_F(DarwinFixture, next_move_test3) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");

  Creature c(&s, WEST, 0);
  Instruction i("infect", -1);
  setPc(c, 3);
  ASSERT_TRUE(c.next_move() == i);
}

TEST_F(DarwinFixture, creature_print_test1) {
  Species s("unicorn");
  Creature c(&s, WEST, 0);
  ostringstream o;
  o << c;
  ASSERT_TRUE(o.str() == "u");
}

TEST_F(DarwinFixture, creature_print_test2) {
  Species s("aliens");
  Creature c(&s, WEST, 0);
  ostringstream o;
  o << c;
  ASSERT_TRUE(o.str() == "a");
}

TEST_F(DarwinFixture, creature_print_test3) {
  Species s("harambe");
  Creature c(&s, WEST, 0);
  ostringstream o;
  o << c;
  ASSERT_TRUE(o.str() == "h");
}

TEST_F(DarwinFixture, inFront_test1) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");

  Creature c(&s, WEST, 0);
  DarwinTuple p(1, 1);
  DarwinTuple q(1, 0);
  DarwinTuple t = c.inFront(p);
  ASSERT_TRUE(t == q);
}

TEST_F(DarwinFixture, inFront_test2) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");

  Creature c(&s, EAST, 0);
  DarwinTuple p(1, 1);
  DarwinTuple q(1, 2);
  DarwinTuple t = c.inFront(p);
  ASSERT_TRUE(t == q);
}

TEST_F(DarwinFixture, inFront_test3) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");

  Creature c(&s, NORTH, 0);
  DarwinTuple p(1, 1);
  DarwinTuple q(0, 1);
  DarwinTuple t = c.inFront(p);
  ASSERT_TRUE(t == q);
}

TEST_F(DarwinFixture, incr_test1) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");

  Creature c(&s, WEST, 0);
  c.incr();
  ASSERT_TRUE(getPc(c) == 1);
}

TEST_F(DarwinFixture, incr_test2) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");

  Creature c(&s, WEST, 0);
  c.incr();
  c.incr();
  ASSERT_TRUE(getPc(c) == 2);
}

TEST_F(DarwinFixture, incr_test3) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);

  Creature c(&s, WEST, 0);
  c.incr();
  c.incr();
  ASSERT_TRUE(getPc(c) == 0);
}

TEST_F(DarwinFixture, cond_update_test1) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");

  Creature c(&s, WEST, 0);
  c.cond_update(true);
  ASSERT_TRUE(getPc(c) == 2);
}

TEST_F(DarwinFixture, cond_update_test2) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");

  Creature c(&s, WEST, 0);
  c.cond_update(false);
  ASSERT_TRUE(getPc(c) == 1);
}

TEST_F(DarwinFixture, cond_update_test3) {
  Species s("unicorn");
  s.addInstruction("go", 2);
  s.addInstruction("go", 5);
  s.addInstruction("hop");
  s.addInstruction("infect");

  Creature c(&s, WEST, 0);
  setPc(c, 3);
  c.cond_update(false);
  ASSERT_TRUE(getPc(c) == 0);
}

TEST_F(DarwinFixture, isSpecies_test1) {
  Species s("unicorn");
  Creature c(&s, WEST, 0);
  Creature d(&s, EAST, 1);

  ASSERT_TRUE(c.isSpecies(d));
}

TEST_F(DarwinFixture, isSpecies_test2) {
  Species s("unicorn");
  Species r("pug");
  Creature c(&s, WEST, 0);
  Creature d(&r, EAST, 1);

  ASSERT_FALSE(c.isSpecies(d));
}

TEST_F(DarwinFixture, infect_test1) {
  Species s("unicorn");
  Species r("pug");
  Darwin x(2, 2);
  Creature c(&s, EAST, 0);
  Creature d(&r, EAST, 1);
  setPc(d, 3);

  x.addCreature(&c, 0, 0);
  x.addCreature(&d, 0, 1);

  Instruction i("infect");
  x.updateState(&c, i);
  ASSERT_TRUE(c.isSpecies(d));
  ASSERT_TRUE(getPc(d) == 0);
  ASSERT_TRUE(getDirection(d) == EAST);
}

TEST_F(DarwinFixture, infect_test2) {
  Species s("unicorn");
  Species r("pug");
  Darwin x(2, 2);
  Creature c(&s, EAST, 0);
  Creature d(&r, EAST, 1);
  setPc(d, 3);

  x.addCreature(&c, 0, 0);
  x.addCreature(&d, 1, 0);

  Instruction i("infect");
  x.updateState(&c, i);
  ASSERT_FALSE(c.isSpecies(d));
  ASSERT_TRUE(getPc(d) == 3);
}

TEST_F(DarwinFixture, infect_test3) {
  Species s("unicorn");
  Species r("pug");
  Darwin x(2, 2);
  Creature c(&s, EAST, 0);
  Creature d(&r, EAST, 1);
  setPc(d, 3);

  x.addCreature(&c, 0, 0);

  Instruction i("infect");
  x.updateState(&c, i);
  ASSERT_TRUE(getGrid(x)[1] == nullptr);
  ASSERT_TRUE(getPc(d) == 3);
}

/* Darwin tests */

TEST_F(DarwinFixture, darwin_print_test1) {

  Species hopper(std::string("hopper"));
  hopper.addInstruction(std::string("hop"));
  hopper.addInstruction(std::string("goto"), 0);
  Creature h(&hopper);
  Creature f(&hopper);
  Creature g(&hopper);

  Darwin x(2, 2);
  x.addCreature(&h, 0, 0);
  x.addCreature(&f, 1, 1);
  ostringstream o;
  ostringstream s("  01\n0 h.\n1 .h\n\n");
  o << x;
  ASSERT_TRUE(o.str() == s.str());
}

TEST_F(DarwinFixture, darwin_print_test2) {

  Species hopper(std::string("pug"));
  hopper.addInstruction(std::string("hop"));
  hopper.addInstruction(std::string("goto"), 0);
  Creature h(&hopper);
  Creature f(&hopper);
  Creature g(&hopper);

  Darwin x(3, 3);
  x.addCreature(&h, 0, 0);
  x.addCreature(&f, 1, 1);
  x.addCreature(&g, 2, 2);
  ostringstream o;
  ostringstream s("  012\n0 p..\n1 .p.\n2 ..p\n\n");
  o << x;
  ASSERT_TRUE(o.str() == s.str());
}

TEST_F(DarwinFixture, darwin_print_test3) {

  Species hopper(std::string("hopper"));
  hopper.addInstruction(std::string("hop"));
  hopper.addInstruction(std::string("goto"), 0);
  Creature h(&hopper);
  Creature f(&hopper);
  Creature g(&hopper);

  Darwin x(2, 2);
  x.addCreature(&h, 0, 1);
  x.addCreature(&f, 1, 1);
  ostringstream o;
  ostringstream s("  01\n0 .h\n1 .h\n\n");
  o << x;
  ASSERT_TRUE(o.str() == s.str());
}

TEST_F(DarwinFixture, addCreature_test1) {

  Species hopper(std::string("hopper"));
  Darwin x(2, 2);
  Creature h(&hopper);
  x.addCreature(&h, 0, 1);
  ASSERT_TRUE(getGrid(x)[1] == &h);
}

TEST_F(DarwinFixture, addCreature_test2) {

  Species hopper(std::string("hopper"));
  Darwin x(2, 2);
  Creature h(&hopper);
  x.addCreature(&h, 1, 1);
  ASSERT_TRUE(getGrid(x)[3] == &h);
}

TEST_F(DarwinFixture, addCreature_test3) {

  Species hopper(std::string("hopper"));
  Darwin x(2, 2);
  Creature h(&hopper);
  x.addCreature(&h, 1, 0);
  ASSERT_TRUE(getGrid(x)[2] == &h);
}

TEST_F(DarwinFixture, left_test1) {

  Species food(std::string("food"));
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food);
  x.addCreature(&f, 1, 0);
  f.left();
  ASSERT_TRUE(getDirection(f) == SOUTH);
}

TEST_F(DarwinFixture, left_test2) {

  Species food(std::string("food"));
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food);
  x.addCreature(&f, 1, 0);
  f.left();
  f.left();
  ASSERT_TRUE(getDirection(f) == EAST);
}

TEST_F(DarwinFixture, left_test3) {

  Species food(std::string("food"));
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, EAST);
  x.addCreature(&f, 1, 0);
  f.left();
  f.left();
  ASSERT_TRUE(getDirection(f) == WEST);
}

TEST_F(DarwinFixture, left_test4) {

  Species food(std::string("food"));
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, NORTH);
  x.addCreature(&f, 1, 0);
  f.left();
  f.left();
  f.left();
  f.left();
  f.left();
  ASSERT_TRUE(getDirection(f) == WEST);
}

TEST_F(DarwinFixture, right_test1) {

  Species food(std::string("food"));
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food);
  x.addCreature(&f, 1, 0);
  f.right();
  ASSERT_TRUE(getDirection(f) == NORTH);
}

TEST_F(DarwinFixture, right_test2) {

  Species food(std::string("food"));
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food);
  x.addCreature(&f, 1, 0);
  f.right();
  f.right();
  ASSERT_TRUE(getDirection(f) == EAST);
}

TEST_F(DarwinFixture, right_test3) {

  Species food(std::string("food"));
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, EAST);
  x.addCreature(&f, 1, 0);
  f.right();
  f.right();
  ASSERT_TRUE(getDirection(f) == WEST);
}

TEST_F(DarwinFixture, right_test4) {

  Species food(std::string("food"));
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, NORTH);
  x.addCreature(&f, 1, 0);
  f.right();
  f.right();
  f.right();
  f.right();
  f.right();
  ASSERT_TRUE(getDirection(f) == EAST);
}

TEST_F(DarwinFixture, if_wall_test1) {

  Species food(std::string("food"));
  food.addInstruction(std::string("if_wall"), 3);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, WEST);
  x.addCreature(&f, 0, 0);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_TRUE(getPc(f) == 3);
}

TEST_F(DarwinFixture, if_wall_test2) {

  Species food(std::string("food"));
  food.addInstruction(std::string("if_wall"), 3);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, EAST);
  x.addCreature(&f, 0, 0);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_TRUE(getPc(f) == 1);
}

TEST_F(DarwinFixture, if_wall_test3) {

  Species food(std::string("food"));
  food.addInstruction(std::string("if_wall"), 3);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, NORTH);
  x.addCreature(&f, 0, 0);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_TRUE(getPc(f) == 3);
}

TEST_F(DarwinFixture, if_empty_test1) {

  Species food(std::string("food"));
  food.addInstruction(std::string("if_empty"), 3);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, EAST);
  x.addCreature(&f, 0, 0);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_EQ(getPc(f), 3);
}

TEST_F(DarwinFixture, if_empty_test2) {

  Species food(std::string("food"));
  food.addInstruction(std::string("if_empty"), 3);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, EAST, 0);
  Creature g(&food, EAST, 1);
  x.addCreature(&f, 0, 0);
  x.addCreature(&g, 0, 1);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_EQ(getPc(f), 1);
}

TEST_F(DarwinFixture, if_empty_test3) {

  Species food(std::string("food"));
  food.addInstruction(std::string("if_empty"), 3);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food);
  x.addCreature(&f, 0, 0);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_EQ(getPc(f), 1);
}

TEST_F(DarwinFixture, if_enemy_test1) {

  Species food(std::string("food"));
  Species hopper(std::string("hopper"));
  food.addInstruction(std::string("if_enemy"), 3);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, EAST, 0);
  Creature h(&hopper, EAST, 1);
  x.addCreature(&f, 0, 0);
  x.addCreature(&h, 0, 1);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_EQ(getPc(f), 3);
}

TEST_F(DarwinFixture, if_enemy_test2) {

  Species food(std::string("food"));
  Species hopper(std::string("hopper"));
  food.addInstruction(std::string("if_enemy"), 3);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, EAST, 0);
  Creature h(&hopper, EAST, 1);
  x.addCreature(&f, 0, 0);
  x.addCreature(&h, 1, 0);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_EQ(getPc(f), 1);
}

TEST_F(DarwinFixture, if_enemy_test3) {

  Species food(std::string("food"));
  Species hopper(std::string("hopper"));
  food.addInstruction(std::string("if_enemy"), 3);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  Darwin x(2, 2);
  Creature f(&food, EAST, 0);
  Creature h(&food, EAST, 1);
  x.addCreature(&f, 0, 0);
  x.addCreature(&h, 0, 1);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_EQ(getPc(f), 1);
}

TEST_F(DarwinFixture, if_random_test1) {

  Species food(std::string("food"));
  Species hopper(std::string("hopper"));
  food.addInstruction(std::string("if_random"), 3);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  srand(0); // 1st num will be odd
  Darwin x(2, 2);
  Creature f(&food, EAST, 0);
  Creature h(&food, EAST, 1);
  x.addCreature(&f, 0, 0);
  x.addCreature(&h, 0, 1);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_EQ(getPc(f), 3);
}

TEST_F(DarwinFixture, if_random_test2) {

  Species food(std::string("food"));
  Species hopper(std::string("hopper"));
  food.addInstruction(std::string("if_random"), 4);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  srand(0); // 1st num will be odd
  Darwin x(2, 2);
  Creature f(&food, EAST, 0);
  Creature h(&food, EAST, 1);
  x.addCreature(&f, 0, 0);
  x.addCreature(&h, 0, 1);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_EQ(getPc(f), 4);
}

TEST_F(DarwinFixture, if_random_test3) {

  Species food(std::string("food"));
  Species hopper(std::string("hopper"));
  food.addInstruction(std::string("if_random"), 2);
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  food.addInstruction(std::string("hop"));
  food.addInstruction(std::string("go"), 0);
  srand(0); // 1st num will be odd
  Darwin x(2, 2);
  Creature f(&food, EAST, 0);
  Creature h(&food, EAST, 1);
  x.addCreature(&f, 0, 0);
  x.addCreature(&h, 0, 1);
  Instruction i = f.next_move();
  x.updateState(&f, i);
  ASSERT_EQ(getPc(f), 2);
}

/* Darwin instructions tests */

TEST_F(DarwinFixture, hop_test_1) {
  unsigned int id = 0;
  Species hopper(std::string("hopper"));
  hopper.addInstruction(std::string("hop"));
  hopper.addInstruction(std::string("go"), 0);
  Creature h(&hopper, WEST, id++);

  Darwin x(3, 3);
  x.addCreature(&h, 1, 1);
  x.hop(h);

  DarwinIterator b = x.begin();
  DarwinIterator e = x.end();
  while (*b != &h && b != e)
    ++b;
  ASSERT_FALSE(b == e);
  ASSERT_TRUE(&h == *b);
  Creature *c = getGrid(x)[3];
  ASSERT_FALSE(c == nullptr);
  ASSERT_TRUE(c == &h);
}

TEST_F(DarwinFixture, hop_test_2) {
  unsigned int id = 0;
  Species hopper(std::string("hopper"));
  hopper.addInstruction(std::string("hop"));
  hopper.addInstruction(std::string("go"), 0);
  Creature h(&hopper, EAST, id++);

  Darwin x(3, 3);
  x.addCreature(&h, 1, 1);
  x.hop(h);

  DarwinIterator b = x.begin();
  DarwinIterator e = x.end();
  while (*b != &h && b != e)
    ++b;
  ASSERT_FALSE(b == e);
  ASSERT_TRUE(&h == *b);
  Creature *c = getGrid(x)[5];
  ASSERT_FALSE(c == nullptr);
  ASSERT_TRUE(c == &h);
}

TEST_F(DarwinFixture, hop_test_3) {
  unsigned int id = 0;
  Species hopper(std::string("hopper"));
  hopper.addInstruction(std::string("hop"));
  hopper.addInstruction(std::string("go"), 0);
  Creature h(&hopper, NORTH, id++);

  Darwin x(3, 3);
  x.addCreature(&h, 1, 1);
  x.hop(h);

  DarwinIterator b = x.begin();
  DarwinIterator e = x.end();
  while (*b != &h && b != e)
    ++b;
  ASSERT_FALSE(b == e);
  ASSERT_TRUE(&h == *b);
  Creature *c = getGrid(x)[1];
  ASSERT_FALSE(c == nullptr);
  ASSERT_TRUE(c == &h);
}

TEST_F(DarwinFixture, hop_test_4) {
  unsigned int id = 0;
  Species hopper(std::string("hopper"));
  hopper.addInstruction(std::string("hop"));
  hopper.addInstruction(std::string("go"), 0);
  Creature h(&hopper, SOUTH, id++);

  Darwin x(3, 3);
  x.addCreature(&h, 1, 1);
  x.hop(h);

  DarwinIterator b = x.begin();
  DarwinIterator e = x.end();
  while (*b != &h && b != e)
    ++b;
  ASSERT_FALSE(b == e);
  ASSERT_TRUE(&h == *b);
  Creature *c = getGrid(x)[7];
  ASSERT_FALSE(c == nullptr);
  ASSERT_TRUE(c == &h);
}

TEST_F(DarwinFixture, cond_update_test_1) {
  unsigned int id = 0;
  Species hopper(std::string("hopper"));
  hopper.addInstruction(std::string("hop"));
  hopper.addInstruction(std::string("if_wall"), 3);
  hopper.addInstruction(std::string("go"), 0);
  hopper.addInstruction(std::string("left"));
  hopper.addInstruction(std::string("go"), 0);
  Creature h(&hopper, SOUTH, id++);

  Darwin x(3, 3);
  x.addCreature(&h, 1, 1);

  setPc(h, 1);
  h.cond_update(true);
  ASSERT_EQ(getPc(h), 3);
}

TEST_F(DarwinFixture, cond_update_test_2) {
  unsigned int id = 0;
  Species hopper(std::string("hopper"));
  hopper.addInstruction(std::string("hop"));
  hopper.addInstruction(std::string("if_wall"), 3);
  hopper.addInstruction(std::string("go"), 0);
  hopper.addInstruction(std::string("left"));
  hopper.addInstruction(std::string("go"), 0);
  Creature h(&hopper, SOUTH, id++);

  Darwin x(3, 3);
  x.addCreature(&h, 1, 1);

  setPc(h, 1);
  h.cond_update(false);
  ASSERT_EQ(getPc(h), 2);
}

/* Simulator tests */
TEST_F(DarwinFixture, simulate_1) {

  unsigned int id = 0;
  Species hopper(std::string("hopper"));
  hopper.addInstruction(std::string("hop"));
  hopper.addInstruction(std::string("go"), 0);
  Creature h(&hopper, SOUTH, id++);
  Creature f(&hopper, SOUTH, id++);
  Creature g(&hopper, SOUTH, id++);

  Darwin x(3, 3);
  x.addCreature(&h, 0, 0);
  x.addCreature(&f, 1, 1);
  x.addCreature(&g, 2, 2);

  unsigned int turns = 1;
  Simulator s(x, turns);
  s.simulate();
  Darwin &d = getDarwin(s);
  ostringstream o;
  o << d;
  ostringstream a("  012\n0 ...\n1 h..\n2 .hh\n\n");
  ASSERT_EQ(a.str(), o.str());
}

/* Simulator tests */
TEST_F(DarwinFixture, simulate_2) {

  unsigned int id = 0;
  Species evil(std::string("evil"));
  evil.addInstruction(std::string("if_enemy"), 6);
  evil.addInstruction(std::string("hop"));
  evil.addInstruction(std::string("if_wall"), 4);
  evil.addInstruction(std::string("go"), 0);
  evil.addInstruction(std::string("left"));
  evil.addInstruction(std::string("go"), 0);
  evil.addInstruction(std::string("infect"));
  evil.addInstruction(std::string("go"), 0);

  Species food(std::string("food"));
  food.addInstruction(std::string("left"));
  food.addInstruction(std::string("go"), 0);
  Creature e(&evil, EAST, id++);
  Creature f(&food, SOUTH, id++);

  Darwin x(3, 3);
  x.addCreature(&e, 0, 0);
  x.addCreature(&f, 0, 1);

  unsigned int turns = 2;
  Simulator s(x, turns);
  s.simulate();
  Darwin &d = getDarwin(s);
  ostringstream o;
  o << d;
  ostringstream a("  012\n0 .e.\n1 ...\n2 .e.\n\n");
  ASSERT_EQ(a.str(), o.str());
}

TEST_F(DarwinFixture, simulate_3) {

  unsigned int id = 0;
  Species cat(std::string("cat"));
  cat.addInstruction(std::string("if_enemy"), 3);
  cat.addInstruction(std::string("left"));
  cat.addInstruction(std::string("go"), 0);
  cat.addInstruction(std::string("infect"));
  Species dog(std::string("dog"));
  dog.addInstruction(std::string("if_enemy"), 3);
  cat.addInstruction(std::string("left"));
  dog.addInstruction(std::string("go"), 0);
  dog.addInstruction(std::string("infect"));

  Creature c(&cat, EAST, id++);
  Creature dd(&dog, WEST, id++);

  Darwin x(2, 2);
  x.addCreature(&c, 0, 0);
  x.addCreature(&dd, 0, 1);

  unsigned int turns = 1;
  Simulator s(x, turns);
  s.simulate();
  Darwin &d = getDarwin(s);
  ostringstream o;
  o << d;
  ostringstream a("  01\n0 cc\n1 ..\n\n");
  ASSERT_EQ(a.str(), o.str());
}
