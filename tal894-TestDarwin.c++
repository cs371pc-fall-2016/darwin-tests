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

TEST(DarwinFixture, Darwin_constructor) {
  Darwin x(2, 3);
  ASSERT_EQ(2, x.rows);
  ASSERT_EQ(3, x.cols);
  for (int i = 0; i < x.rows; ++i)
    for (int j = 0; j < x.cols; ++j)
      ASSERT_EQ(nullptr, x.world[i][j]);
}

TEST(DarwinFixture, Darwin_addCreature1) {
  Species f('f');
  Creature a(&f, Direction::west);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 f.\n1 ..\n", w.str());
}

TEST(DarwinFixture, Darwin_addCreature2) {
  Species f('f');
  Creature a(&f, Direction::west);
  Creature b(&f, Direction::west);
  Creature c(&f, Direction::west);
  Creature d(&f, Direction::west);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  x.addCreature(&c, 1, 0);
  x.addCreature(&d, 1, 1);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 ff\n1 ff\n", w.str());
}

TEST(DarwinFixture, Darwin_addCreature3) {
  Species f('f');
  Species t('t');
  Creature a(&f, Direction::west);
  Creature b(&f, Direction::west);
  Creature c(&t, Direction::west);
  Creature d(&t, Direction::west);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  x.addCreature(&c, 1, 0);
  x.addCreature(&d, 1, 1);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 ff\n1 tt\n", w.str());
}

TEST(DarwinFixture, Darwin_addCreature4) {
  Species f('f');
  Creature a(&f, Direction::west);
  Darwin x(2, 2);
  try {
    x.addCreature(&a, -1, 0);
    ASSERT_EQ(true, false);
  } catch (const std::out_of_range &oor) {
    ASSERT_EQ(true, true);
  }
}

TEST(DarwinFixture, Darwin_hop_east) {
  Species h('h');
  Creature a(&h, Direction::east);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 h.\n1 ..\n", w.str());
  w.clear();
  w.str("");
  x.hop(0, 0);
  w << x;
  ASSERT_EQ("  01\n0 .h\n1 ..\n", w.str());
}

TEST(DarwinFixture, Darwin_hop_west) {
  Species h('h');
  Creature a(&h, Direction::west);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 1);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 .h\n1 ..\n", w.str());
  w.clear();
  w.str("");
  x.hop(0, 1);
  w << x;
  ASSERT_EQ("  01\n0 h.\n1 ..\n", w.str());
}

TEST(DarwinFixture, Darwin_hop_south) {
  Species h('h');
  Creature a(&h, Direction::south);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 h.\n1 ..\n", w.str());
  w.clear();
  w.str("");
  x.hop(0, 0);
  w << x;
  ASSERT_EQ("  01\n0 ..\n1 h.\n", w.str());
}

TEST(DarwinFixture, Darwin_hop_north) {
  Species h('h');
  Creature a(&h, Direction::north);
  Darwin x(2, 2);
  x.addCreature(&a, 1, 0);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 ..\n1 h.\n", w.str());
  w.clear();
  w.str("");
  x.hop(1, 0);
  w << x;
  ASSERT_EQ("  01\n0 h.\n1 ..\n", w.str());
}

TEST(DarwinFixture, Darwin_infect_success) {
  Species h('h');
  Species f('f');
  Creature a(&h, Direction::east);
  Creature b(&f, Direction::north);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 hf\n1 ..\n", w.str());
  w.clear();
  w.str("");
  x.infect(0, 0);
  w << x;
  ASSERT_EQ("  01\n0 hh\n1 ..\n", w.str());
}

TEST(DarwinFixture, Darwin_infect_friendly) {
  Species h('h');
  Creature a(&h, Direction::east);
  Creature b(&h, Direction::south);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 hh\n1 ..\n", w.str());
  w.clear();
  w.str("");
  x.infect(0, 0);
  x.infect(0, 1);
  w << x;
  ASSERT_EQ("  01\n0 hh\n1 ..\n", w.str());
}

TEST(DarwinFixture, Darwin_infect_wall) {
  Species h('h');
  Species f('f');
  Creature a(&h, Direction::west);
  Creature b(&f, Direction::north);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 hf\n1 ..\n", w.str());
  w.clear();
  w.str("");
  x.infect(0, 0);
  x.infect(0, 1);
  w << x;
  ASSERT_EQ("  01\n0 hf\n1 ..\n", w.str());
}

TEST(DarwinFixture, Darwin_empty_success) {
  Species h('h');
  Creature a(&h, Direction::south);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  ASSERT_EQ(true, x.empty(0, 0));
}

TEST(DarwinFixture, Darwin_empty_wall) {
  Species h('h');
  Creature a(&h, Direction::north);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  ASSERT_EQ(false, x.empty(0, 0));
}

TEST(DarwinFixture, Darwin_empty_creature) {
  Species h('h');
  Creature a(&h, Direction::east);
  Creature b(&h, Direction::south);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  ASSERT_EQ(false, x.empty(0, 0));
}

TEST(DarwinFixture, Darwin_wall_success) {
  Species h('h');
  Creature a[4] = {
      Creature(&h, Direction::west), Creature(&h, Direction::north),
      Creature(&h, Direction::east), Creature(&h, Direction::south)};
  Darwin x(2, 2);
  x.addCreature(&(a[0]), 0, 0);
  x.addCreature(&(a[1]), 0, 1);
  x.addCreature(&(a[2]), 1, 1);
  x.addCreature(&(a[3]), 1, 0);
  ASSERT_EQ(true, x.wall(0, 0));
  ASSERT_EQ(true, x.wall(0, 1));
  ASSERT_EQ(true, x.wall(1, 0));
  ASSERT_EQ(true, x.wall(1, 1));
}

TEST(DarwinFixture, Darwin_wall_false) {
  Species h('h');
  Creature a[4] = {
      Creature(&h, Direction::east), Creature(&h, Direction::south),
      Creature(&h, Direction::west), Creature(&h, Direction::north)};
  Darwin x(2, 2);
  x.addCreature(&(a[0]), 0, 0);
  x.addCreature(&(a[1]), 0, 1);
  x.addCreature(&(a[2]), 1, 1);
  x.addCreature(&(a[3]), 1, 0);
  ASSERT_EQ(false, x.wall(0, 0));
  ASSERT_EQ(false, x.wall(0, 1));
  ASSERT_EQ(false, x.wall(1, 0));
  ASSERT_EQ(false, x.wall(1, 1));
}

TEST(DarwinFixture, Darwin_wall_hybrid) {
  Species h('h');
  Creature a[4] = {
      Creature(&h, Direction::west), Creature(&h, Direction::north),
      Creature(&h, Direction::west), Creature(&h, Direction::north)};
  Darwin x(2, 2);
  x.addCreature(&(a[0]), 0, 0);
  x.addCreature(&(a[1]), 0, 1);
  x.addCreature(&(a[2]), 1, 1);
  x.addCreature(&(a[3]), 1, 0);
  ASSERT_EQ(true, x.wall(0, 0));
  ASSERT_EQ(true, x.wall(0, 1));
  ASSERT_EQ(false, x.wall(1, 0));
  ASSERT_EQ(false, x.wall(1, 1));
}

TEST(DarwinFixture, Darwin_enemy_success) {
  Species h('h');
  Species f('f');
  Creature a(&h, Direction::east);
  Creature b(&f, Direction::south);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  ASSERT_EQ(true, x.enemy(0, 0));
}

TEST(DarwinFixture, Darwin_enemy_empty) {
  Species h('h');
  Species f('f');
  Creature a(&h, Direction::south);
  Creature b(&f, Direction::south);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  ASSERT_EQ(false, x.enemy(0, 0));
}

TEST(DarwinFixture, Darwin_enemy_wall) {
  Species h('h');
  Species f('f');
  Creature a(&h, Direction::north);
  Creature b(&f, Direction::south);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  ASSERT_EQ(false, x.enemy(0, 0));
}

TEST(DarwinFixture, Darwin_enemy_friendly) {
  Species h('h');
  Creature a(&h, Direction::east);
  Creature b(&h, Direction::south);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  ASSERT_EQ(false, x.enemy(0, 0));
}

TEST(DarwinFixture, Darwin_run1) {
  Species h('h');
  h.addInstruction("hop");
  h.addInstruction("go 0");
  Creature a(&h, Direction::east);
  Darwin x(2, 3);
  x.addCreature(&a, 0, 0);
  ostringstream w;
  w << x;
  ASSERT_EQ("  012\n0 h..\n1 ...\n", w.str());
  w.clear();
  w.str("");
  x.run();
  w << x;
  ASSERT_EQ("  012\n0 .h.\n1 ...\n", w.str());
  w.clear();
  w.str("");
  x.run();
  w << x;
  ASSERT_EQ("  012\n0 ..h\n1 ...\n", w.str());
}

TEST(DarwinFixture, Darwin_run2) {
  Species h('h');
  h.addInstruction("hop");
  h.addInstruction("right");
  h.addInstruction("go 0");
  Creature a(&h, Direction::east);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 h.\n1 ..\n", w.str());
  w.clear();
  w.str("");
  x.run();
  w << x;
  ASSERT_EQ("  01\n0 .h\n1 ..\n", w.str());
  w.clear();
  w.str("");
  x.run();
  w << x;
  ASSERT_EQ("  01\n0 .h\n1 ..\n", w.str());
  w.clear();
  w.str("");
  x.run();
  w << x;
  ASSERT_EQ("  01\n0 ..\n1 .h\n", w.str());
}

TEST(DarwinFixture, Darwin_run3) {
  Species h('h');
  Species f('f');
  h.addInstruction("infect");
  Creature a(&h, Direction::east);
  Creature b(&f, Direction::east);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 hf\n1 ..\n", w.str());
  w.clear();
  w.str("");
  x.run();
  w << x;
  ASSERT_EQ("  01\n0 hh\n1 ..\n", w.str());
}

TEST(DarwinFixture, Darwin_print1) {
  Species h('h');
  Creature a(&h, Direction::east);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&a, 0, 1);
  x.addCreature(&a, 1, 0);
  x.addCreature(&a, 1, 1);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 hh\n1 hh\n", w.str());
}

TEST(DarwinFixture, Darwin_print2) {
  Species h('h');
  Species f('f');
  Creature a(&h, Direction::east);
  Creature b(&f, Direction::east);
  Darwin x(2, 2);
  x.addCreature(&a, 0, 0);
  x.addCreature(&b, 0, 1);
  x.addCreature(&b, 1, 0);
  x.addCreature(&a, 1, 1);
  ostringstream w;
  w << x;
  ASSERT_EQ("  01\n0 hf\n1 fh\n", w.str());
}

TEST(DarwinFixture, Darwin_print3) {
  Species h('h');
  Species f('f');
  Creature a(&h, Direction::east);
  Creature b(&f, Direction::east);
  Darwin x(2, 4);
  for (int i = 0; i < 4; ++i) {
    x.addCreature(&a, 0, i);
    x.addCreature(&b, 1, i);
  }
  ostringstream w;
  w << x;
  ASSERT_EQ("  0123\n0 hhhh\n1 ffff\n", w.str());
}

TEST(DarwinFixture, Creature_default_constructor) {
  Creature a;
  ASSERT_EQ(nullptr, a.species);
  ASSERT_EQ(0, a.dir);
  ASSERT_EQ(0, a.program_counter);
}

TEST(DarwinFixture, Creature_constructor) {
  Species h('h');
  Creature a(&h, 3);
  ASSERT_EQ(&h, a.species);
  ASSERT_EQ(3, a.dir);
  ASSERT_EQ(0, a.program_counter);
}

TEST(DarwinFixture, Creature_turn_left) {
  Species h('h');
  Creature a(&h, Direction::east);
  a.turn(Direction::left);
  ASSERT_EQ(Direction::north, a.dir);
  a.turn(Direction::left);
  ASSERT_EQ(Direction::west, a.dir);
  a.turn(Direction::left);
  ASSERT_EQ(Direction::south, a.dir);
  a.turn(Direction::left);
  ASSERT_EQ(Direction::east, a.dir);
}

TEST(DarwinFixture, Creature_turn_right) {
  Species h('h');
  Creature a(&h, Direction::east);
  a.turn(Direction::right);
  ASSERT_EQ(Direction::south, a.dir);
  a.turn(Direction::right);
  ASSERT_EQ(Direction::west, a.dir);
  a.turn(Direction::right);
  ASSERT_EQ(Direction::north, a.dir);
  a.turn(Direction::right);
  ASSERT_EQ(Direction::east, a.dir);
}

TEST(DarwinFixture, Creature_turn_left_and_right) {
  Species h('h');
  Creature a(&h, Direction::east);
  a.turn(Direction::left);
  ASSERT_EQ(Direction::north, a.dir);
  a.turn(Direction::right);
  ASSERT_EQ(Direction::east, a.dir);
}

TEST(DarwinFixture, Creature_infect) {
  Species h('h');
  Species f('f');
  Creature a(&h, Direction::east);
  Creature b(&f, Direction::east);
  a.infect(&b);
  ASSERT_EQ(a.species, b.species);
  ASSERT_EQ(a.program_counter, 0);
}

TEST(DarwinFixture, Creature_infect_friendly) {
  Species h('h');
  Creature a(&h, Direction::east);
  Creature b(&h, Direction::east);
  a.program_counter = 10;
  a.infect(&b);
  ASSERT_EQ(a.species, &h);
  ASSERT_EQ(a.program_counter, 10);
}

TEST(DarwinFixture, Creature_infect_nullptr) {
  Species h('h');
  Creature a(&h, Direction::east);
  a.program_counter = 10;
  a.infect(nullptr);
  ASSERT_EQ(a.species, &h);
  ASSERT_EQ(a.program_counter, 10);
}

TEST(DarwinFixture, Creature_enemy) {
  Species h('h');
  Species f('f');
  Creature a(&h, Direction::east);
  Creature b(&f, Direction::east);
  ASSERT_EQ(true, a.enemy(&b));
  ASSERT_EQ(true, b.enemy(&a));
}

TEST(DarwinFixture, Creature_enemy_friendly) {
  Species h('h');
  Creature a(&h, Direction::east);
  Creature b(&h, Direction::east);
  ASSERT_EQ(false, a.enemy(&b));
  ASSERT_EQ(false, b.enemy(&a));
}

TEST(DarwinFixture, Creature_enemy_nullptr) {
  Species h('h');
  Creature a(&h, Direction::east);
  ASSERT_EQ(false, a.enemy(nullptr));
}

TEST(DarwinFixture, Creature_next_east) {
  Species h('h');
  Creature a(&h, Direction::east);
  int r = 0, c = 0;
  a.next(r, c);
  ASSERT_EQ(r, 0);
  ASSERT_EQ(c, 1);
}

TEST(DarwinFixture, Creature_next_south) {
  Species h('h');
  Creature a(&h, Direction::south);
  int r = 0, c = 0;
  a.next(r, c);
  ASSERT_EQ(r, 1);
  ASSERT_EQ(c, 0);
}

TEST(DarwinFixture, Creature_next_north) {
  Species h('h');
  Creature a(&h, Direction::north);
  int r = 0, c = 0;
  a.next(r, c);
  ASSERT_EQ(r, -1);
  ASSERT_EQ(c, 0);
}

TEST(DarwinFixture, Creature_next_west) {
  Species h('h');
  Creature a(&h, Direction::west);
  int r = 0, c = 0;
  a.next(r, c);
  ASSERT_EQ(r, 0);
  ASSERT_EQ(c, -1);
}

TEST(DarwinFixture, Creature_print1) {
  Species h('h');
  Creature a(&h, Direction::west);
  ostringstream w;
  w << a;
  ASSERT_EQ("h", w.str());
}

TEST(DarwinFixture, Creature_print2) {
  Species f('f');
  Creature a(&f, Direction::west);
  ostringstream w;
  w << a;
  ASSERT_EQ("f", w.str());
}

TEST(DarwinFixture, Creature_print3) {
  Species r('r');
  Creature a(&r, Direction::west);
  ostringstream w;
  w << a;
  ASSERT_EQ("r", w.str());
}

TEST(DarwinFixture, Species_constructor) {
  Species h('h');
  ASSERT_EQ('h', h.display);
  ASSERT_EQ(0, h.program.size());
}

TEST(DarwinFixture, Species_execute_instruction_hop) {
  Species s('s');
  s.addInstruction("hop");
  Creature c(&s, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(1, ip);
  ostringstream w;
  w << d;
  ASSERT_EQ("  01\n0 .s\n1 ..\n", w.str());
}

TEST(DarwinFixture, Species_execute_instruction_left) {
  Species s('s');
  s.addInstruction("left");
  s.addInstruction("hop");
  Creature c(&s, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 1, 0);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 1, 0);
  ASSERT_EQ(1, ip);
  s.executeInstruction(ip, &c, &d, 1, 0);
  ASSERT_EQ(2, ip);
  ostringstream w;
  w << d;
  ASSERT_EQ("  01\n0 s.\n1 ..\n", w.str());
}

TEST(DarwinFixture, Species_execute_instruction_right) {
  Species s('s');
  s.addInstruction("right");
  s.addInstruction("hop");
  Creature c(&s, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(1, ip);
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(2, ip);
  ostringstream w;
  w << d;
  ASSERT_EQ("  01\n0 ..\n1 s.\n", w.str());
}

TEST(DarwinFixture, Species_execute_instruction_infect) {
  Species s('s');
  Species b('b');
  s.addInstruction("infect");
  Creature c(&s, Direction::east);
  Creature c2(&b, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  d.addCreature(&c2, 0, 1);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(1, ip);
  ostringstream w;
  w << d;
  ASSERT_EQ("  01\n0 ss\n1 ..\n", w.str());
}

TEST(DarwinFixture, Species_execute_instruction_go) {
  Species s('s');
  s.addInstruction("go 10");
  Creature c(&s, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(10, ip);
}

TEST(DarwinFixture, Species_execute_instruction_random) {
  srand(0);
  auto first = rand();
  srand(0);

  Species s('s');
  s.addInstruction("if_random 10");
  Creature c(&s, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(ip == 10, first % 2);
}

TEST(DarwinFixture, Species_execute_instruction_random_false) {
  srand(0);
  int cnt = 1;
  while (rand() % 2 != 0)
    ++cnt;
  srand(0);

  Species s('s');
  s.addInstruction("if_random 10");
  Creature c(&s, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  uint ip = 0;
  for (int i = 0; i < cnt; ++i) {
    ip = 0;
    s.executeInstruction(ip, &c, &d, 0, 0);
  }
  ASSERT_EQ(1, ip);
}

TEST(DarwinFixture, Species_execute_instruction_empty) {
  Species s('s');
  s.addInstruction("if_empty 2");
  Creature c(&s, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(2, ip);
}

TEST(DarwinFixture, Species_execute_instruction_empty_false) {
  Species s('s');
  s.addInstruction("if_empty 2");
  Creature c(&s, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  d.addCreature(&c, 0, 1);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(1, ip);
}

TEST(DarwinFixture, Species_execute_instruction_wall) {
  Species s('s');
  s.addInstruction("if_wall 2");
  Creature c(&s, Direction::north);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(2, ip);
}

TEST(DarwinFixture, Species_execute_instruction_wall_false) {
  Species s('s');
  s.addInstruction("if_wall 2");
  Creature c(&s, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(1, ip);
}

TEST(DarwinFixture, Species_execute_instruction_enemy) {
  Species s('s');
  Species b('b');
  s.addInstruction("if_enemy 2");
  Creature c(&s, Direction::east);
  Creature c2(&b, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  d.addCreature(&c2, 0, 1);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(2, ip);
}

TEST(DarwinFixture, Species_execute_instruction_enemy_false) {
  Species s('s');
  s.addInstruction("if_enemy 2");
  Creature c(&s, Direction::east);
  Creature c2(&s, Direction::east);
  Darwin d(2, 2);
  d.addCreature(&c, 0, 0);
  d.addCreature(&c2, 0, 1);
  uint ip = 0;
  s.executeInstruction(ip, &c, &d, 0, 0);
  ASSERT_EQ(1, ip);
}

TEST(DarwinFixture, Species_print1) {
  Species h('h');
  ostringstream w;
  w << h;
  ASSERT_EQ("h", w.str());
}

TEST(DarwinFixture, Species_print2) {
  Species f('f');
  ostringstream w;
  w << f;
  ASSERT_EQ("f", w.str());
}

TEST(DarwinFixture, Species_print3) {
  Species r('r');
  ostringstream w;
  w << r;
  ASSERT_EQ("r", w.str());
}
