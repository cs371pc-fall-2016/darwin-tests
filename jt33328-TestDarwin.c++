// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <gtest/gtest.h>

#include "Darwin.h"

using namespace std;

// ----
// test
// ----

// Test instructionToIdMap.

TEST(Species, instruction_to_id_map_1) {
  map<string, int> instruction_to_id;
	instruction_to_id["hop"] = 1;
	instruction_to_id["left"] = 2;
	instruction_to_id["right"] = 3;
	instruction_to_id["infect"] = 4;
	instruction_to_id["if_empty"] = 5;
	instruction_to_id["if_random"] = 6;
	instruction_to_id["go"] = 7;
	instruction_to_id["if_wall"] = 8;
	instruction_to_id["if_enemy"] = 9;
  ASSERT_EQ(createInstructionToIdMap(), instruction_to_id);
}

TEST(Creature, instruction_to_id_map_2) {
  map<string, int> instruction_to_id;
	instruction_to_id["hop"] = 1;
	instruction_to_id["left"] = 2;
	instruction_to_id["right"] = 3;
	instruction_to_id["infect"] = 4;
	instruction_to_id["if_empty"] = 5;
	instruction_to_id["if_random"] = 6;
	instruction_to_id["go"] = 7;
	instruction_to_id["if_wall"] = 8;
	instruction_to_id["if_enemy"] = 9;
  ASSERT_EQ(createInstructionToIdMap(), instruction_to_id);
}

TEST(Darwin, instruction_to_id_map_3) {
  map<string, int> instruction_to_id;
	instruction_to_id["hop"] = 1;
	instruction_to_id["left"] = 2;
	instruction_to_id["right"] = 3;
	instruction_to_id["infect"] = 4;
	instruction_to_id["if_empty"] = 5;
	instruction_to_id["if_random"] = 6;
	instruction_to_id["go"] = 7;
	instruction_to_id["if_wall"] = 8;
	instruction_to_id["if_enemy"] = 9;
  ASSERT_EQ(createInstructionToIdMap(), instruction_to_id);
}

// Test idToInstructionMap.

TEST(Species, id_to_instruction_map_1) {
  map<int, string> id_to_instruction;
	id_to_instruction[1] = "hop";
	id_to_instruction[2] = "left";
	id_to_instruction[3] = "right";
	id_to_instruction[4] = "infect";
	id_to_instruction[5] = "if_empty";
	id_to_instruction[6] = "if_random";
	id_to_instruction[7] = "go";
	id_to_instruction[8] = "if_wall";
	id_to_instruction[9] = "if_enemy";
  ASSERT_EQ(createIdToInstructionMap(), id_to_instruction);
}

TEST(Creature, id_to_instruction_map_2) {
  map<int, string> id_to_instruction;
	id_to_instruction[1] = "hop";
	id_to_instruction[2] = "left";
	id_to_instruction[3] = "right";
	id_to_instruction[4] = "infect";
	id_to_instruction[5] = "if_empty";
	id_to_instruction[6] = "if_random";
	id_to_instruction[7] = "go";
	id_to_instruction[8] = "if_wall";
	id_to_instruction[9] = "if_enemy";
  ASSERT_EQ(createIdToInstructionMap(), id_to_instruction);
}

TEST(Darwin, id_to_instruction_map_3) {
  map<int, string> id_to_instruction;
	id_to_instruction[1] = "hop";
	id_to_instruction[2] = "left";
	id_to_instruction[3] = "right";
	id_to_instruction[4] = "infect";
	id_to_instruction[5] = "if_empty";
	id_to_instruction[6] = "if_random";
	id_to_instruction[7] = "go";
	id_to_instruction[8] = "if_wall";
	id_to_instruction[9] = "if_enemy";
  ASSERT_EQ(createIdToInstructionMap(), id_to_instruction);
}

// Test constructor for Species.

TEST(Species, species_constructor_1) {
  Species s("1");
  ASSERT_EQ(s.species_name, std::string("1"));

}

TEST(Species, species_constructor_2) {
  Species s("2");
  ASSERT_EQ(s.species_name, std::string("2"));
}

TEST(Species, species_constructor_3) {
  Species s("3");
  ASSERT_EQ(s.species_name, std::string("3"));
}

// Test addInstruction for Species.

TEST(Species, species_add_instruction_1) {
  Species s("1");
  s.addInstruction(std::string("left"));
  ASSERT_EQ(s.instructionAt(0).first, std::string("left"));
}

TEST(Species, species_add_instruction_2) {
  Species s("1");
  s.addInstruction(std::string("right"));
  ASSERT_EQ(s.instructionAt(0).first, std::string("right"));
}

TEST(Species, species_add_instruction_3) {
  Species s("1");
  s.addInstruction(std::string("hop"));
  ASSERT_EQ(s.instructionAt(0).first, std::string("hop"));
}

// Test numberOfInstructions for Species.

TEST(Species, species_number_instructions_1) {
  Species s("1");
  s.addInstruction(std::string("left"));
  ASSERT_EQ(s.numberOfInstructions(), 1);
}

TEST(Species, species_number_instructions_2) {
  Species s("1");
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  ASSERT_EQ(s.numberOfInstructions(), 2);
}

TEST(Species, species_number_instructions_3) {
  Species s("1");
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  ASSERT_EQ(s.numberOfInstructions(), 3);
}

TEST(Species, species_number_instructions_4) {
  Species s("1");
  ASSERT_EQ(s.numberOfInstructions(), 0);
}

TEST(Species, species_number_instructions_5) {
  Species s("1");
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  ASSERT_EQ(s.numberOfInstructions(), 4);
}

TEST(Species, species_number_instructions_6) {
  Species s("1");
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("left"));
  ASSERT_EQ(s.numberOfInstructions(), 7);
}

// Test instructionAt for Species.

TEST(Species, species_instruction_at_1) {
  Species s("1");
  s.addInstruction(std::string("left"));
  ASSERT_EQ(s.instructionAt(0).first, std::string("left"));
}

TEST(Species, species_instruction_at_2) {
  Species s("1");
  s.addInstruction(std::string("right"));
  s.addInstruction(std::string("right"));
  s.addInstruction(std::string("right"));
  ASSERT_EQ(s.instructionAt(2).first, std::string("right"));
}

TEST(Species, species_instruction_at_3) {
  Species s("1");
  s.addInstruction(std::string("hop"));
  s.addInstruction(std::string("hop"));
  ASSERT_EQ(s.instructionAt(1).first, std::string("hop"));
}

// Test Creature constructor.

TEST(Creature, creature_constructor_1) {
  Species s("1");
  Creature c(s, NORTH);
  ASSERT_EQ(c.s->species_name, std::string("1"));
}

TEST(Creature, creature_constructor_2) {
  Species s("1");
  Creature c(s, SOUTH);
  ASSERT_EQ(c.s->species_name, std::string("1"));
}

TEST(Creature, creature_constructor_3) {
  Species s("1");
  Creature c(s, EAST);
  ASSERT_EQ(c.s->species_name, std::string("1"));
}

// Test Creature movePC.

TEST(Creature, move_pc_1) {
  Species s("1");
  s.addInstruction(std::string("hop"));
  Creature c(s, NORTH);
  c.movePC();
  ASSERT_EQ(c.pc, 0);
}

TEST(Creature, move_pc_2) {
  Species s("1");
  s.addInstruction(std::string("hop"));
  s.addInstruction(std::string("hop"));
  Creature c(s, NORTH);
  c.movePC(1);
  ASSERT_EQ(c.pc, 1);
}

TEST(Creature, move_pc_3) {
  Species s("1");
  s.addInstruction(std::string("hop"));
  s.addInstruction(std::string("hop"));
  s.addInstruction(std::string("hop"));
  Creature c(s, NORTH);
  c.movePC(2);
  ASSERT_EQ(c.pc, 2);
}

// Test changeToSpecies.

TEST(Creature, change_to_species_1) {
  Species s("a");
  Species t("b");
  Creature c(s, NORTH);
  c.changeToSpecies(&t);
  ASSERT_EQ(c.s->species_name, std::string("b"));
}

TEST(Creature, change_to_species_2) {
  Species s("1");
  Species t("2");
  Creature c(s, NORTH);
  c.changeToSpecies(&t);
  ASSERT_EQ(c.s->species_name, std::string("2"));
}

TEST(Creature, change_to_species_3) {
  Species s("c");
  Species t("d");
  Creature c(s, NORTH);
  c.changeToSpecies(&t);
  ASSERT_EQ(c.s->species_name, std::string("d"));
}

// Test nextInstruction.

TEST(Creature, next_instruction_1) {
  Species s("a");
  s.addInstruction(std::string("hop"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("right"));
  Creature c(s, NORTH);
  ASSERT_EQ(c.nextInstruction().first, std::string("hop"));
}

TEST(Creature, next_instruction_2) {
  Species s("a");
  s.addInstruction(std::string("hop"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("right"));
  Creature c(s, NORTH);
  c.movePC(1);
  ASSERT_EQ(c.nextInstruction().first, std::string("left"));
}

TEST(Creature, next_instruction_3) {
  Species s("a");
  s.addInstruction(std::string("hop"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("right"));
  Creature c(s, NORTH);
  c.movePC(2);
  ASSERT_EQ(c.nextInstruction().first, std::string("right"));
}

// Test task.

TEST(Creature, task_1) {
  Species s("a");
  s.addInstruction(std::string("hop"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("right"));
  Creature c(s, NORTH);
  ASSERT_EQ(c.task(0,0).first, std::string("hop"));
}

TEST(Creature, task_2) {
  Species s("a");
  s.addInstruction(std::string("hop"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("right"));
  Creature c(s, NORTH);
  ASSERT_EQ(c.task(0,0).second.first, -1);
}

TEST(Creature, task_3) {
  Species s("a");
  s.addInstruction(std::string("hop"));
  s.addInstruction(std::string("left"));
  s.addInstruction(std::string("right"));
  Creature c(s, EAST);
  ASSERT_EQ(c.task(0,0).second.second, 1);
}

// Test turnDirection.
TEST(Creature, turn_direction_1) {
  Species s("a");
  s.addInstruction(std::string("right"));
  Creature c(s, EAST);
  c.turnDirection(std::string("left"));
  ASSERT_EQ(c.d, NORTH);
}

TEST(Creature, turn_direction_2) {
  Species s("a");
  s.addInstruction(std::string("right"));
  Creature c(s, EAST);
  c.turnDirection(std::string("right"));
  ASSERT_EQ(c.d, SOUTH);
}

TEST(Creature, turn_direction_3) {
  Species s("a");
  s.addInstruction(std::string("right"));
  Creature c(s, WEST);
  c.turnDirection(std::string("right"));
  ASSERT_EQ(c.d, NORTH);
}

// Test getPositionAhead.

TEST(Creature, get_position_ahead_1) {
  Species s("a");
  s.addInstruction(std::string("right"));
  Creature c(s, WEST);
  ASSERT_EQ(c.getPositionAhead(0,0).second, -1);
}

TEST(Creature, get_position_ahead_2) {
  Species s("a");
  s.addInstruction(std::string("right"));
  Creature c(s, SOUTH);
  ASSERT_EQ(c.getPositionAhead(0,0).first, 1);
}

TEST(Creature, get_position_ahead_3) {
  Species s("a");
  s.addInstruction(std::string("right"));
  Creature c(s, NORTH);
  ASSERT_EQ(c.getPositionAhead(0,0).first, -1);
}

// Test Darwin constructor.

TEST(Darwin, darwin_constructor_1) {
  Darwin d(72, 72);
  ASSERT_EQ(d.board[0].size(), 72);
  ASSERT_EQ(d.board.size(), 72);
  ASSERT_EQ(d.creatures.size(), 200);
  ASSERT_EQ(d.r, 72);
  ASSERT_EQ(d.c, 72);
}

TEST(Darwin, darwin_constructor_2) {
  Darwin d(5, 5);
  ASSERT_EQ(d.board[0].size(), 5);
  ASSERT_EQ(d.board.size(), 5);
  ASSERT_EQ(d.creatures.size(), 200);
  ASSERT_EQ(d.r, 5);
  ASSERT_EQ(d.c, 5);
}

TEST(Darwin, darwin_constructor_3) {
  Darwin d(10, 20);
  ASSERT_EQ(d.board[0].size(), 20);
  ASSERT_EQ(d.board.size(), 10);
  ASSERT_EQ(d.creatures.size(), 200);
  ASSERT_EQ(d.r, 10);
  ASSERT_EQ(d.c, 20);
}

// Test addCreature.

TEST(Darwin, add_creature_1) {
  Darwin d(10, 20);
  Species s("a");
  Creature c(s, SOUTH);
  d.addCreature(c,0,0);
  ASSERT_EQ(d.nextCreatureIndex, 1);
}

TEST(Darwin, add_creature_2) {
  Darwin d(10, 20);
  Species s("a");
  Creature c(s, SOUTH);
  d.addCreature(c,0,0);
  ASSERT_EQ(d.creatures[0], &c);
}

TEST(Darwin, add_creature_3) {
  Darwin d(10, 20);
  Species s("a");
  Creature c(s, SOUTH);
  Creature c2(s, NORTH);
  d.addCreature(c,0,0);
  d.addCreature(c2, 5, 5);
  ASSERT_EQ(d.nextCreatureIndex, 2);
}

// Test simulate.

TEST(Darwin, simulate_1) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("hop");
  Creature c(s, SOUTH);
  d.addCreature(c,5,5);
  d.simulate(1);
  ASSERT_EQ(d.board[6][5], 0);
}

TEST(Darwin, simulate_2) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("hop");
  Creature c(s, NORTH);
  d.addCreature(c,5,5);
  d.simulate(1);
  ASSERT_EQ(d.board[4][5], 0);
}

TEST(Darwin, simulate_3) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("hop");
  Creature c(s, EAST);
  d.addCreature(c,5,5);
  d.simulate(1);
  ASSERT_EQ(d.board[5][6], 0);
}

// Test creatureTurn.

TEST(Darwin, creature_turn_1) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("hop");
  Creature c(s, EAST);
  d.addCreature(c,5,5);
  d.creatureTurn(5,5);
  ASSERT_EQ(d.board[5][6], 0);
}

TEST(Darwin, creature_turn_2) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("hop");
  Creature c(s, SOUTH);
  d.addCreature(c,5,5);
  d.creatureTurn(5,5);
  ASSERT_EQ(d.board[6][5], 0);
}

TEST(Darwin, creature_turn_3) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("hop");
  Creature c(s, NORTH);
  d.addCreature(c,5,5);
  d.creatureTurn(5,5);
  ASSERT_EQ(d.board[4][5], 0);
}

// Test getCreatureAt.

TEST(Darwin, get_creature_at_1) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("hop");
  Creature c(s, NORTH);
  d.addCreature(c,5,5);
  ASSERT_EQ(d.getCreatureAt(5,5), &c);
}

TEST(Darwin, get_creature_at_2) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("left");
  Creature c(s, NORTH);
  d.addCreature(c,1,5);
  ASSERT_EQ(d.getCreatureAt(1,5), &c);
}

TEST(Darwin, get_creature_at_3) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("hop");
  Creature c(s, NORTH);
  d.addCreature(c,0,0);
  ASSERT_EQ(d.getCreatureAt(0,0), &c);
}

// Test hop.

TEST(Darwin, hop_1) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("hop");
  Creature c(s, NORTH);
  d.addCreature(c,5,5);
  d.hop(5,5,4,5);
  ASSERT_EQ(d.getCreatureAt(4,5), &c);
}

TEST(Darwin, hop_2) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("hop");
  Creature c(s, NORTH);
  d.addCreature(c,0,0);
  d.hop(0,0,-1,0);
  ASSERT_EQ(d.getCreatureAt(0,0), &c);
}

TEST(Darwin, hop_3) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("hop");
  Creature c(s, SOUTH);
  d.addCreature(c,5,5);
  d.hop(5,5,6,5);
  ASSERT_EQ(d.getCreatureAt(6,5), &c);
}

// Test infect.

TEST(Darwin, infect_1) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  Creature c(s, SOUTH);
  Creature c2(s, SOUTH);
  d.addCreature(c,5,5);
  d.addCreature(c2,6,5);
  d.infect(5,5,6,5);
  ASSERT_EQ(d.getCreatureAt(6,5)->s->species_name, c.s->species_name);
}

TEST(Darwin, infect_2) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  Creature c(s, SOUTH);
  Creature c2(s, SOUTH);
  d.addCreature(c,5,5);
  d.addCreature(c2,7,5);
  d.infect(5,5,6,5);
  ASSERT_EQ(d.board[6][5], -1);
}

TEST(Darwin, infect_3) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  Creature c(s, NORTH);
  Creature c2(s, SOUTH);
  d.addCreature(c,5,5);
  d.addCreature(c2,4,5);
  d.infect(5,5,4,5);
  ASSERT_EQ(d.getCreatureAt(4,5)->s->species_name, c.s->species_name);
}

// Test if_empty.

TEST(Darwin, if_empty_1) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, NORTH);
  Creature c2(s, SOUTH);
  d.addCreature(c,5,5);
  d.if_empty(5,5,1,6,5);
  ASSERT_EQ(c.pc, 1);
}

TEST(Darwin, if_empty_2) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, NORTH);
  Creature c2(s, SOUTH);
  d.addCreature(c,5,5);
  d.addCreature(c2, 6,5);
  d.if_empty(5,5,2,6,5);
  ASSERT_EQ(c.pc, 1);
}

TEST(Darwin, if_empty_3) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, NORTH);
  Creature c2(s, SOUTH);
  d.addCreature(c,5,5);
  d.addCreature(c2,7,5);
  d.if_empty(5,5,2,6,5);
  ASSERT_EQ(c.pc, 2);
}

TEST(Darwin, if_empty_4) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  Creature c(s, NORTH);
  d.addCreature(c,5,5);
  d.if_empty(5,5,0,1,1);
  ASSERT_EQ(c.pc, 0);
}

TEST(Darwin, if_empty_5) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, SOUTH);
  d.addCreature(c,0,1);
  d.if_empty(0,1,0,4,5);
  ASSERT_EQ(c.pc, 0);
}

TEST(Darwin, if_empty_6) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, NORTH);
  Creature c2(s, SOUTH);
  d.addCreature(c,0,0);
  d.addCreature(c2,7,5);
  d.if_empty(0,0,2,-1,0);
  ASSERT_EQ(c.pc, 1);
}

// Test if_wall.

TEST(Darwin, if_wall_1) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, NORTH);
  Creature c2(s, SOUTH);
  d.addCreature(c,0,0);
  d.if_wall(0,0,2,-1,0);
  ASSERT_EQ(c.pc, 2);
}

TEST(Darwin, if_wall_2) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, NORTH);
  d.addCreature(c,5,5);
  d.if_wall(5,5,2,6,5);
  ASSERT_EQ(c.pc, 1);
}

TEST(Darwin, if_wall_3) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, WEST);
  d.addCreature(c,5,0);
  d.if_wall(5,0,2,5,-1);
  ASSERT_EQ(c.pc, 2);
}

// Test if_enemy.

TEST(Darwin, if_enemy_1) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, WEST);
  d.addCreature(c,5,0);
  d.if_enemy(5,0,2,5,-1);
  ASSERT_EQ(c.pc, 1);
}

TEST(Darwin, if_enemy_2) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, SOUTH);
  d.addCreature(c,0,0);
  d.if_enemy(0,0,0,1,0);
  ASSERT_EQ(c.pc, 1);
}

TEST(Darwin, if_enemy_3) {
  Darwin d(72, 72);
  Species s("a");
  Species a("s");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, SOUTH);
  Creature c2(a, SOUTH);
  d.addCreature(c,0,0);
  d.addCreature(c2, 1, 0);
  d.if_enemy(0,0,2,1,0);
  ASSERT_EQ(c.pc, 2);
}

TEST(Darwin, if_enemy_4) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, SOUTH);
  Creature c2(s, SOUTH);
  d.addCreature(c,0,0);
  d.addCreature(c2, 1, 0);
  d.if_enemy(0,0,2,1,0);
  ASSERT_EQ(c.pc, 1);
}

// Test go.

TEST(Darwin, go_1) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, SOUTH);
  d.addCreature(c,0,0);
  d.go(0,0,2);
  ASSERT_EQ(c.pc, 2);
}

TEST(Darwin, go_2) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, SOUTH);
  d.addCreature(c,0,0);
  d.go(0,0,1);
  ASSERT_EQ(c.pc, 1);
}

TEST(Darwin, go_3) {
  Darwin d(72, 72);
  Species s("a");
  s.addInstruction("infect");
  s.addInstruction("infect");
  s.addInstruction("infect");
  Creature c(s, SOUTH);
  d.addCreature(c,0,0);
  d.go(0,0,0);
  ASSERT_EQ(c.pc, 0);
}
