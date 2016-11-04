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
// Species
// ----

TEST(SpeciesFixture, species_construct_1) {
  Species s;
  ASSERT_EQ(s.program.size(), 0);
}

TEST(SpeciesFixture, species_construct_2) {
  Species s;
  ASSERT_EQ(s.id, '.');
}

TEST(SpeciesFixture, species_construct_3) {
  Species s = Species('a');
  ASSERT_EQ(s.id, 'a');
}

TEST(SpeciesFixture, species_size) {
  Species s;
  Instruction i = Instruction(InstructionType::HOP, 0);
  s.addInstruction(i);
  ASSERT_EQ(s.program.size(), 1);
}

TEST(SpeciesFixture, species_size_zero) {
  Species s;
  ASSERT_EQ(s.program.size(), 0);
}

TEST(SpeciesFixture, species_value) {
  Species s;
  Instruction i = Instruction(InstructionType::HOP, 0);
  s.addInstruction(i);
  ASSERT_EQ(s.program[0].line, 0);
}

TEST(SpeciesFixture, species_1) {
  Species s;
  Instruction i = Instruction(InstructionType::HOP, 0);
  s.addInstruction(i);
  Instruction r = s.run(0, State::EMPTY);
  ASSERT_EQ(r.type, InstructionType::HOP);
  ASSERT_EQ(r.line, 0);
}

TEST(SpeciesFixture, species_2) {
  Species s;
  Instruction i = Instruction(InstructionType::HOP, 0);
  s.addInstruction(i);
  i = Instruction(InstructionType::RIGHT, 5);
  s.addInstruction(i);
  Instruction r = s.run(1, State::EMPTY);
  ASSERT_EQ(r.type, InstructionType::RIGHT);
  ASSERT_EQ(r.line, 1);
}

TEST(SpeciesFixture, species_3) {
  Species s;
  Instruction i = Instruction(InstructionType::GO, 2);
  s.addInstruction(i);
  i = Instruction(InstructionType::RIGHT, 5);
  s.addInstruction(i);
  i = Instruction(InstructionType::LEFT, 2);
  s.addInstruction(i);
  Instruction r = s.run(0, State::EMPTY);
  ASSERT_EQ(r.type, InstructionType::LEFT);
  ASSERT_EQ(r.line, 2);
}

// ----
// Creature
// ----

TEST(CreatureFixture, creature_construct_1) {
	ostringstream w;
  Creature c;
  w << c;
  ASSERT_EQ(".", w.str());
}

TEST(CreatureFixture, creature_construct_2) {
  Creature c;
  ASSERT_EQ(c.counter, 0);
}

TEST(CreatureFixture, creature_construct_3) {
  Creature c;
  ASSERT_EQ(c.turnCount, 0);
}

TEST(CreatureFixture, creature_construct_4) {
  Creature c;
  ASSERT_EQ(c.direction, 0);
}

TEST(CreatureFixture, creature_construct_5) {
  Species s;
  Creature c = Creature(s, 2);
  ASSERT_EQ(c.direction, 2);
}

TEST(CreatureFixture, creature_next_coord_1) {
  Species s;
  Creature c = Creature(s, 0);
  Coordinate coord = Coordinate(5, 5);
  coord = c.nextCoordinate(coord);
  ASSERT_EQ(coord.x, 5);
  ASSERT_EQ(coord.y, 4);
}

TEST(CreatureFixture, creature_next_coord_2) {
  Species s;
  Creature c = Creature(s, 1);
  Coordinate coord = Coordinate(5, 5);
  coord = c.nextCoordinate(coord);
  ASSERT_EQ(coord.x, 6);
  ASSERT_EQ(coord.y, 5);
}

TEST(CreatureFixture, creature_next_coord_3) {
  Species s;
  Creature c = Creature(s, 2);
  Coordinate coord = Coordinate(5, 5);
  coord = c.nextCoordinate(coord);
  ASSERT_EQ(coord.x, 5);
  ASSERT_EQ(coord.y, 6);
}

TEST(CreatureFixture, creature_next_coord_4) {
  Species s;
  Creature c = Creature(s, 3);
  Coordinate coord = Coordinate(5, 5);
  coord = c.nextCoordinate(coord);
  ASSERT_EQ(coord.x, 4);
  ASSERT_EQ(coord.y, 5);
}

TEST(CreatureFixture, creature_1) {
  Species s;
  Instruction i = Instruction(InstructionType::HOP, 0);
  s.addInstruction(i);
  Creature c = Creature(s, 0);
  InstructionType r = c.run(0, State::EMPTY);
  ASSERT_EQ(r, InstructionType::HOP);
}

TEST(CreatureFixture, creature_2) {
  Species s;
  Instruction i = Instruction(InstructionType::HOP, 0);
  s.addInstruction(i);
  i = Instruction(InstructionType::RIGHT, 5);
  s.addInstruction(i);
  Creature c = Creature(s, 0);
  InstructionType r = c.run(-1, State::EMPTY);
  ASSERT_EQ(r, InstructionType::PASS);
}

TEST(CreatureFixture, creature_3) {
  Species s;
  Instruction i = Instruction(InstructionType::GO, 2);
  s.addInstruction(i);
  i = Instruction(InstructionType::RIGHT, 5);
  s.addInstruction(i);
  i = Instruction(InstructionType::LEFT, 2);
  s.addInstruction(i);
  Creature c = Creature(s, 0);
  InstructionType r = c.run(0, State::EMPTY);
  ASSERT_EQ(r, InstructionType::LEFT);
}

TEST(CreatureFixture, creature_4) {
  Species s;
  Instruction i = Instruction(InstructionType::INFECT, 0);
  s.addInstruction(i);
  i = Instruction(InstructionType::HOP, 0);
  s.addInstruction(i);
  i = Instruction(InstructionType::GO, 0);
  s.addInstruction(i);
  Creature c = Creature(s, 0);
  c.run(0, State::EMPTY);
  c.run(1, State::EMPTY);
  InstructionType r = c.run(2, State::EMPTY);
  ASSERT_EQ(r, InstructionType::INFECT);
}

TEST(CreatureFixture, creature_infect_1) {
  Species a = Species('a');
  Species b = Species('b');
  Creature ca = Creature(a, 0);
  Creature cb = Creature(b, 0);
  ca.infect(cb);
  ASSERT_EQ(ca.counter, 0);
}

TEST(CreatureFixture, creature_infect_2) {
	ostringstream w;
	ostringstream w2;
  Species a = Species('a');
  Species b = Species('b');
  Creature ca = Creature(a, 0);
  Creature cb = Creature(b, 0);
  ca.infect(cb);
  w << ca;
  w2 << cb;
  ASSERT_EQ(w.str(), w2.str());
}

TEST(CreatureFixture, creature_infect_3) {
	ostringstream w;
	ostringstream w2;
  Species a = Species('a');
  Species b = Species('b');
  Creature ca = Creature(a, 0);
  Creature cb = Creature(b, 0);
  ca.infect(cb);
  w << ca.species;
  w2 << cb.species;
  ASSERT_EQ(w.str(), w2.str());
}

TEST(CreatureFixture, creature_stream_1) {
  ostringstream w;
  Creature c;
  w << c;
  ASSERT_EQ(".", w.str());
}

TEST(CreatureFixture, creature_stream_2) {
  ostringstream w;
  Species s = Species('a');
  Creature c = Creature(s, 0);
  w << c;
  ASSERT_EQ("a", w.str());
}

TEST(CreatureFixture, creature_stream_3) {
  ostringstream w;
  Species s = Species('b');
  Creature c = Creature(s, 0);
  w << c;
  ASSERT_EQ("b", w.str());
}

// ----
// Darwin
// ----

TEST(DarwinFixture, darwin_construct_1) {
  Darwin d = Darwin(10, 10);
  ASSERT_EQ(d.grid.size(), 10);
}

TEST(DarwinFixture, darwin_construct_2) {
  Darwin d = Darwin(10, 10);
  ASSERT_EQ(d.grid[0].size(), 10);
}

TEST(DarwinFixture, darwin_construct_3) {
  Darwin d = Darwin(10, 10);
  ASSERT_EQ(d.counter, 0);
}

TEST(DarwinFixture, darwin_add_1) {
	ostringstream w;
  Species a = Species('a');
  Creature ca = Creature(a, 0);
  Darwin d = Darwin(10, 10);
  d.addCreature(ca, 0, 0);
  w << d.grid[0][0];
  ASSERT_EQ("a", w.str());
}

TEST(DarwinFixture, darwin_add_2) {
	ostringstream w;
	ostringstream w2;
  Species a = Species('a');
  Creature ca = Creature(a, 0);
  Darwin d = Darwin(10, 10);
  d.addCreature(ca, 1, 1);
  w << d.grid[1][1];
  w2 << d.grid[0][0];
  ASSERT_EQ("a", w.str());
  ASSERT_EQ(".", w2.str());
}

TEST(DarwinFixture, darwin_add_3) {
	ostringstream w;
	ostringstream w2;
  Species a = Species('a');
  Creature ca = Creature(a, 0);
  Creature ca2 = Creature(a, 0);
  Darwin d = Darwin(10, 10);
  d.addCreature(ca, 1, 1);
  d.addCreature(ca2, 0, 0);
  w << d.grid[1][1];
  w2 << d.grid[0][0];
  ASSERT_EQ("a", w.str());
  ASSERT_EQ("a", w2.str());
}

TEST(DarwinFixture, darwin_run_1) {
	ostringstream w;
	ostringstream w2;
  Species s = Species('s');
  Instruction infect = Instruction(InstructionType::INFECT, 0);
  Instruction hop = Instruction(InstructionType::HOP, 0);
  Instruction loop = Instruction(InstructionType::GO, 0);
  s.addInstruction(infect);
  s.addInstruction(loop);
  Species t = Species('t');
  t.addInstruction(hop);
  t.addInstruction(loop);
  Creature runner = Creature(t, 1);
  Creature trapper = Creature(s, 3);
  Darwin dar = Darwin(10, 10);
  dar.addCreature(runner, 3, 0);
  dar.addCreature(trapper, 4, 0);
  for (int i = 0; i < 5; ++i) {
    dar.run();
  }
  Creature run = dar.grid[0][3];
  Creature trap = dar.grid[0][4];
  w << run;
  w2 << trap;
  ASSERT_EQ(w.str(), w2.str());
}

TEST(DarwinFixture, darwin_run_2) {
	ostringstream w;
	ostringstream w2;
  Species a = Species('a');
  Species b = Species('b');
  Instruction infect = Instruction(InstructionType::INFECT, 0);
  Instruction hop = Instruction(InstructionType::HOP, 0);
  Instruction loop = Instruction(InstructionType::GO, 0);
  Instruction loopback = Instruction(InstructionType::GO, 1);
  a.addInstruction(hop);

  b.addInstruction(hop);
  b.addInstruction(infect);
  b.addInstruction(loopback);

  a.addInstruction(loop);

  Creature ac = Creature(a, 1);
  Creature bc = Creature(b, 2);

  Darwin dar = Darwin(10, 10);
  dar.addCreature(ac, 0, 2);
  dar.addCreature(bc, 3, 0);
  for (int i = 0; i < 5; ++i) {
    dar.run();
  }
  Creature infected = dar.grid[2][4];
  Creature trap = dar.grid[0][3];
  w << infected;
  w2 << b;
  ASSERT_EQ(w.str(), w2.str());
}

TEST(DarwinFixture, darwin_run_3) {
	ostringstream w;
	ostringstream w2;
  Instruction hop = Instruction(InstructionType::HOP, 0);
  Instruction loop = Instruction(InstructionType::GO, 0);
  Species runnerSpecies = Species('r');
  runnerSpecies.addInstruction(hop);
  runnerSpecies.addInstruction(loop);
  Creature runner = Creature(runnerSpecies, 2);
  Darwin dar = Darwin(10, 10);
  dar.addCreature(runner, 0, 0);
  dar.run();
  Creature runner2 = dar.grid[1][0];
  w << runner2;
  w2 << runnerSpecies;
  ASSERT_EQ(w.str(), w2.str());
}

TEST(DarwinFixture, darwin_stream_1) {
  ostringstream w;
  Darwin d = Darwin(2,2);
  w << d;
  ASSERT_EQ("Turn = 0.\n  01\n0 ..\n1 ..\n", w.str());
}

TEST(DarwinFixture, darwin_stream_2) {
  ostringstream w;
  Darwin d = Darwin(2,2);
  d.run();
  w << d;
  ASSERT_EQ("Turn = 1.\n  01\n0 ..\n1 ..\n", w.str());
}

TEST(DarwinFixture, darwin_stream_3) {
  ostringstream w;
  Species s = Species('a');
  Creature c = Creature(s, 0);
  Darwin d = Darwin(2,2);
  d.addCreature(c, 0, 0);
  w << d;
  ASSERT_EQ("Turn = 0.\n  01\n0 a.\n1 ..\n", w.str());
}
