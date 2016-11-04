// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <sstream>
#include <string>

#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

// ----
// test
// ----

TEST(DarwinFixture, species_constructor_1) {
  Species s('s');
  ASSERT_EQ(s.icon, 's');
}

TEST(DarwinFixture, species_constructor_2) {
  Species m('m');
  ASSERT_EQ(m.icon, 'm');
}

TEST(DarwinFixture, species_constructor_3) {
  Species j('j');
  ASSERT_EQ(j.icon, 'j');
}

TEST(DarwinFixture, species_add_instruction_1) {
  Species s('s');
  s.add_instruction(hop);
  ASSERT_EQ(s._program.size(), 1);
}

TEST(DarwinFixture, species_add_instruction_2) {
  Species m('m');
  m.add_instruction(hop);
  m.add_instruction(go, 0);
  ASSERT_EQ(m._program[0].instruction, hop);
  ASSERT_EQ(m._program[1].instruction, go);
  ASSERT_EQ(m._program[1].argument, 0);
}

TEST(DarwinFixture, species_add_instruction_3) {
  Species j('j');
  j.add_instruction(if_empty, 1);
  j.add_instruction(infect);
  j.add_instruction(if_wall, 3);
  j.add_instruction(Instructions::left);
  ASSERT_EQ(j._program[0].instruction, if_empty);
  ASSERT_EQ(j._program[0].argument, 1);
  ASSERT_EQ(j._program[1].instruction, infect);
  ASSERT_EQ(j._program[2].instruction, if_wall);
  ASSERT_EQ(j._program[2].argument, 3);
  ASSERT_EQ(j._program[3].instruction, Instructions::left);
}

TEST(DarwinFixture, species_index_operator_1) {
  Species s('s');
  s.add_instruction(hop);
  ASSERT_EQ(s._program[0].instruction, s[0].instruction);
}

TEST(DarwinFixture, species_index_operator_2) {
  Species m('m');
  m.add_instruction(hop);
  m.add_instruction(go, 0);
  ASSERT_EQ(m._program[0].instruction, m[0].instruction);
  ASSERT_EQ(m._program[1].instruction, m[1].instruction);
  ASSERT_EQ(m._program[1].argument, m[1].argument);
}

TEST(DarwinFixture, species_index_operator_3) {
  Species j('j');
  j.add_instruction(if_empty, 1);
  j.add_instruction(infect);
  j.add_instruction(if_wall, 3);
  j.add_instruction(Instructions::left);
  ASSERT_EQ(j._program[0].instruction, j[0].instruction);
  ASSERT_EQ(j._program[0].argument, j[0].argument);
  ASSERT_EQ(j._program[1].instruction, j[1].instruction);
  ASSERT_EQ(j._program[2].instruction, j[2].instruction);
  ASSERT_EQ(j._program[2].argument, j[2].argument);
  ASSERT_EQ(j._program[3].instruction, j[3].instruction);
}

TEST(DarwinFixture, creature_constructor_1) {
  Species x('x');
  Creature c(&x, west);
  ASSERT_EQ(c.species, &x);
  ASSERT_EQ(c.direction, west);
}

TEST(DarwinFixture, creature_reset_program_counter) {
  Species x('x');
  Creature c(&x, west);
  c._program_counter = 5;
  c.reset_program_counter();
  ASSERT_EQ(c._program_counter, 0);
}

TEST(DarwinFixture, creature_turn_left_1) {
  Species s('s');
  Creature c(&s, west);
  c.turn_left();
  ASSERT_EQ(c.direction, south);
}

TEST(DarwinFixture, creature_turn_left_2) {
  Species s('s');
  Creature c(&s, south);
  c.turn_left();
  ASSERT_EQ(c.direction, east);
}

TEST(DarwinFixture, creature_turn_left_3) {
  Species s('s');
  Creature c(&s, east);
  c.turn_left();
  ASSERT_EQ(c.direction, north);
}

TEST(DarwinFixture, creature_turn_left_4) {
  Species s('s');
  Creature c(&s, north);
  c.turn_left();
  ASSERT_EQ(c.direction, west);
}

TEST(DarwinFixture, creature_turn_right_1) {
  Species s('s');
  Creature c(&s, west);
  c.turn_right();
  ASSERT_EQ(c.direction, north);
}

TEST(DarwinFixture, creature_turn_right_2) {
  Species s('s');
  Creature c(&s, south);
  c.turn_right();
  ASSERT_EQ(c.direction, west);
}

TEST(DarwinFixture, creature_turn_right_3) {
  Species s('s');
  Creature c(&s, east);
  c.turn_right();
  ASSERT_EQ(c.direction, south);
}

TEST(DarwinFixture, creature_turn_right_4) {
  Species s('s');
  Creature c(&s, north);
  c.turn_right();
  ASSERT_EQ(c.direction, east);
}

TEST(DarwinFixture, darwin_constructor_1) {
  Darwin x(2, 2);
  ASSERT_EQ(x.world.size(), 2);
  ASSERT_EQ(x.world[0].size(), 2);
  ASSERT_EQ(x.current_acting_creature, -1);
}

TEST(DarwinFixture, darwin_constructor_2) {
  Darwin x(5, 2);
  ASSERT_EQ(x.world.size(), 5);
  ASSERT_EQ(x.world[0].size(), 2);
  ASSERT_EQ(x.current_acting_creature, -1);
}

TEST(DarwinFixture, darwin_constructor_3) {
  Darwin x(100, 100);
  ASSERT_EQ(x.world.size(), 100);
  ASSERT_EQ(x.world[0].size(), 100);
  ASSERT_EQ(x.current_row, 0);
  ASSERT_EQ(x.current_col, 0);
  ASSERT_EQ(x.turn, 0);
}

TEST(DarwinFixture, darwin_add_creature_1) {
  Darwin x(2, 2);
  Species s('s');
  Creature c(&s, north);
  x.add_creature(c, 0, 0);
  ASSERT_EQ(x.world[0][0], 0);
  ASSERT_EQ(x.creatures[0].species, &s);
}

TEST(DarwinFixture, darwin_add_creature_2) {
  Darwin x(2, 2);
  Species s('s');
  Creature c1(&s, north);
  Creature c2(&s, west);
  x.add_creature(c1, 0, 0);
  x.add_creature(c2, 1, 1);
  ASSERT_EQ(x.world[0][0], 0);
  ASSERT_EQ(x.world[1][1], 1);
}

TEST(DarwinFixture, darwin_add_creature_3) {
  Darwin x(5, 5);
  Species s('s');
  for (int i = 0; i < 5; ++i) {
    Creature c(&s, east);
    x.add_creature(c, i, i);
  }
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(x.world[i][i], i);
  }
}

TEST(DarwinFixture, darwin_get_value_in_direction_1) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, north);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_EQ(x.get_value_in_direction(c.direction), -2);
}

TEST(DarwinFixture, darwin_get_value_in_direction_2) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, west);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_EQ(x.get_value_in_direction(c.direction), -2);
}

TEST(DarwinFixture, darwin_get_value_in_direction_3) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, east);
  x.add_creature(c, 4, 4);
  x.current_acting_creature = 0;
  x.current_row = 4;
  x.current_col = 4;
  ASSERT_EQ(x.get_value_in_direction(c.direction), -2);
}

TEST(DarwinFixture, darwin_get_value_in_direction_4) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, south);
  x.add_creature(c, 4, 4);
  x.current_acting_creature = 0;
  x.current_row = 4;
  x.current_col = 4;
  ASSERT_EQ(x.get_value_in_direction(c.direction), -2);
}

TEST(DarwinFixture, darwin_get_value_in_direction_5) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, south);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_EQ(x.get_value_in_direction(c.direction), -1);
}

TEST(DarwinFixture, darwin_get_value_in_direction_6) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, south);
  Creature o(&s, north);
  x.add_creature(c, 0, 0);
  x.add_creature(o, 1, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_EQ(x.get_value_in_direction(c.direction), 1);
}

TEST(DarwinFixture, darwin_facing_empty_1) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, south);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_TRUE(x.facing_empty());
}

TEST(DarwinFixture, darwin_facing_empty_2) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, west);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_FALSE(x.facing_empty());
}

TEST(DarwinFixture, darwin_facing_empty_3) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, south);
  Creature o(&s, north);
  x.add_creature(c, 0, 0);
  x.add_creature(o, 1, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_FALSE(x.facing_empty());
}

TEST(DarwinFixture, darwin_facing_enemy_1) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, south);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_FALSE(x.facing_enemy());
}

TEST(DarwinFixture, darwin_facing_enemy_2) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, west);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_FALSE(x.facing_enemy());
}

TEST(DarwinFixture, darwin_facing_enemy_3) {
  Darwin x(5, 5);
  Species s('s');
  Species n('n');
  Creature c(&s, south);
  Creature o(&n, north);
  x.add_creature(c, 0, 0);
  x.add_creature(o, 1, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_TRUE(x.facing_enemy());
}

TEST(DarwinFixture, darwin_facing_enemy_4) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, south);
  Creature o(&s, north);
  x.add_creature(c, 0, 0);
  x.add_creature(o, 1, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_FALSE(x.facing_enemy());
}

TEST(DarwinFixture, darwin_facing_wall_1) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, north);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_TRUE(x.facing_wall());
}

TEST(DarwinFixture, darwin_facing_wall_2) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, west);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  ASSERT_TRUE(x.facing_wall());
}

TEST(DarwinFixture, darwin_facing_wall_3) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, east);
  x.add_creature(c, 4, 4);
  x.current_acting_creature = 0;
  x.current_row = 4;
  x.current_col = 4;
  ASSERT_TRUE(x.facing_wall());
}

TEST(DarwinFixture, darwin_facing_wall_4) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, south);
  x.add_creature(c, 4, 4);
  x.current_acting_creature = 0;
  x.current_row = 4;
  x.current_col = 4;
  ASSERT_TRUE(x.facing_wall());
}

TEST(DarwinFixture, darwin_facing_wall_5) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, north);
  x.add_creature(c, 4, 4);
  x.current_acting_creature = 0;
  x.current_row = 4;
  x.current_col = 4;
  ASSERT_FALSE(x.facing_wall());
}

TEST(DarwinFixture, darwin_hop_1) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, north);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  x.hop();
  ASSERT_EQ(x.world[0][0], 0);
}

TEST(DarwinFixture, darwin_hop_2) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, south);
  Creature o(&s, north);
  x.add_creature(c, 0, 0);
  x.add_creature(c, 1, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  x.hop();
  ASSERT_EQ(x.world[0][0], 0);
}

TEST(DarwinFixture, darwin_hop_3) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, south);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  x.hop();
  ASSERT_EQ(x.world[0][0], -1);
  ASSERT_EQ(x.world[1][0], 0);
}

TEST(DarwinFixture, darwin_infect_1) {
  Darwin x(5, 5);
  Species s('s');
  Creature c(&s, south);
  Creature o(&s, north);
  o._program_counter = 3;
  x.add_creature(c, 0, 0);
  x.add_creature(o, 1, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  x.infect();
  ASSERT_EQ(x.creatures[1]._program_counter, 3);
}

TEST(DarwinFixture, darwin_infect_2) {
  Darwin x(5, 5);
  Species s('s');
  Species n('n');
  Creature c(&s, south);
  Creature o(&n, north);
  o._program_counter = 3;
  x.add_creature(c, 0, 0);
  x.add_creature(o, 1, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  x.infect();
  ASSERT_EQ(x.creatures[1]._program_counter, 0);
  ASSERT_EQ(x.creatures[1].species, &s);
}

TEST(DarwinFixture, creature_act_1) {
  Darwin x(5, 5);
  Species s('s');
  s.add_instruction(hop);
  Creature c(&s, south);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  c.act(&x);
  ASSERT_EQ(x.world[1][0], 0);
  ASSERT_EQ(x.world[0][0], -1);
}

TEST(DarwinFixture, creature_act_2) {
  Darwin x(5, 5);
  Species s('s');
  s.add_instruction(go, 1);
  s.add_instruction(if_wall, 3);
  s.add_instruction(hop);
  s.add_instruction(Instructions::right);
  Creature c(&s, south);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  c.act(&x);
  ASSERT_EQ(x.world[1][0], 0);
  ASSERT_EQ(x.world[0][0], -1);
}

TEST(DarwinFixture, creature_act_3) {
  Darwin x(5, 5);
  Species s('s');
  s.add_instruction(go, 1);
  s.add_instruction(if_wall, 3);
  s.add_instruction(hop);
  s.add_instruction(Instructions::right);
  Creature c(&s, north);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  c.act(&x);
  ASSERT_EQ(x.world[0][0], 0);
  ASSERT_EQ(c.direction, east);
}

TEST(DarwinFixture, creature_act_4) {
  Darwin x(5, 5);
  Species s('s');
  s.add_instruction(if_empty, 1);
  s.add_instruction(Instructions::right);
  Creature c(&s, east);
  x.add_creature(c, 0, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  c.act(&x);
  ASSERT_EQ(c.direction, south);
}

TEST(DarwinFixture, creature_act_5) {
  Darwin x(5, 5);
  Species s('s');
  s.add_instruction(if_enemy, 1);
  s.add_instruction(infect);
  Species n('n');
  Creature c(&s, south);
  Creature o(&n, south);
  x.add_creature(c, 0, 0);
  x.add_creature(o, 1, 0);
  x.current_acting_creature = 0;
  x.current_row = 0;
  x.current_col = 0;
  c.act(&x);
  ASSERT_EQ(x.creatures[1].species, &s);
}

TEST(DarwinFixture, darwin_simulate_1) {
  Darwin x(5, 5);
  Species s('s');
  s.add_instruction(hop);
  s.add_instruction(go, 0);
  for (int i = 0; i < 5; ++i) {
    Creature c(&s, east);
    x.add_creature(c, i, 0);
  }
  x.simulate_turn();
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(x.world[i][0], -1);
    ASSERT_EQ(x.world[i][1], i);
  }
}

TEST(DarwinFixture, darwin_simulate_2) {
  Darwin x(5, 5);
  Species s('s');
  s.add_instruction(infect);
  Species n('n');
  s.add_instruction(Instructions::left);
  for (int i = 0; i < 5; ++i) {
    Creature c(&s, east);
    x.add_creature(c, i, 0);
    Creature o(&n, west);
    x.add_creature(o, i, 1);
  }
  x.simulate_turn();
  for (int i = 1; i < 10; i += 2) {
    ASSERT_EQ(x.creatures[i].species, &s);
  }
}

TEST(DarwinFixture, darwin_simulate_3) {
  Darwin x(5, 5);
  Species s('s');
  s.add_instruction(hop);
  for (int i = 0; i < 5; ++i) {
    Creature c(&s, west);
    x.add_creature(c, i, 0);
  }
  x.simulate_turn();
  for (int i = 0; i < 5; ++i) {
    ASSERT_EQ(x.world[i][0], i);
  }
}

TEST(DarwinFixture, darwin_output_1) {
  string expected =
      "Turn = 0.\n  01234\n0 s....\n1 .s...\n2 ..s..\n3 ...s.\n4 ....s\n";
  ostringstream w;
  Darwin x(5, 5);
  Species s('s');
  for (int i = 0; i < 5; ++i) {
    Creature c(&s, east);
    x.add_creature(c, i, i);
  }
  w << x;
  ASSERT_EQ(expected, w.str());
}

TEST(DarwinFixture, darwin_output_2) {
  string expected =
      "Turn = 1.\n  01234\n0 .s...\n1 .....\n2 .....\n3 .....\n4 .....\n";
  ostringstream w;
  Darwin x(5, 5);
  Species s('s');
  s.add_instruction(hop);
  Creature c(&s, east);
  x.add_creature(c, 0, 0);
  x.simulate_turn();
  w << x;
  ASSERT_EQ(expected, w.str());
}

TEST(DarwinFixture, darwin_output_3) {
  string expected =
      "Turn = 0.\n  01234\n0 .....\n1 .....\n2 .....\n3 .....\n4 .....\n";
  ostringstream w;
  Darwin x(5, 5);
  w << x;
  ASSERT_EQ(expected, w.str());
}
