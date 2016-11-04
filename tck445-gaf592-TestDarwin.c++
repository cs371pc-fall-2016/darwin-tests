// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// Define used to make test fixtures friends
#define IS_TESTING

// --------
// includes
// --------

#include "gtest/gtest.h"

#include <cstdlib>
#include <utility>

#include "Darwin.h"

using namespace std;

// ---------------
// TestInstruction
// ---------------

TEST(TestInstruction, test_action_state_true) {
    Instruction ins(InstructionType::LEFT);
    ASSERT_TRUE(ins.is_action);
}

TEST(TestInstruction, test_action_state_false) {
    Instruction ins(InstructionType::IF_EMPTY);
    ASSERT_FALSE(ins.is_action);
}

TEST(TestInstruction, test_default_jump_pc) {
    Instruction ins(InstructionType::LEFT);
    ASSERT_TRUE(!ins.jump_pc);
}

// -----------
// TestSpecies
// -----------

TEST(TestSpecies, test_instruction_getting) {
   vector<Instruction> turner_ins;

   Instruction ins(InstructionType::LEFT);
   turner_ins.push_back(ins);

   Species turner(turner_ins, "Turner", 't');
   ASSERT_TRUE(turner.get_instruction_at(0).ins_type == ins.ins_type);
}

TEST(TestSpecies, test_instruction_getting_bad) {
   vector<Instruction> turner_ins;

   Instruction ins(InstructionType::LEFT);
   turner_ins.push_back(ins);

   Species turner(turner_ins, "Turner", 't');
   ASSERT_ANY_THROW(turner.get_instruction_at(1));
}

TEST(TestSpecies, test_symbol_output) {
   vector<Instruction> turner_ins;

   Instruction ins(InstructionType::LEFT);
   turner_ins.push_back(ins);

   Species turner(turner_ins, "Turner", 't');

   ostringstream o;
   o << turner;

   ASSERT_TRUE(o.str() == "t");
}

TEST(TestSpecies, test_symbol_cout) {
   vector<Instruction> turner_ins;

   Instruction ins(InstructionType::LEFT);
   turner_ins.push_back(ins);

   Species turner(turner_ins, "Turner", 't');
   ostringstream o;
   ASSERT_NO_THROW(o << turner);
}

// ------------
// TestCreature
// ------------

// Get a species populated with basic instructions
Species get_simple_species() {
    vector<Instruction> simple_instructions;
    simple_instructions.push_back(Instruction(InstructionType::LEFT));
    simple_instructions.push_back(Instruction(InstructionType::GO));

    return Species(simple_instructions, "Simple");
}

TEST(TestCreature, test_constructor) {
    Species species = get_simple_species();

    Creature creature(species, Direction::NORTH);

    ASSERT_EQ(species, creature._species);
    ASSERT_EQ(Direction::NORTH, creature._dir);
    ASSERT_EQ(0, creature._pc);
}

TEST(TestCreature, test_turn_basic) {
    Creature creature(get_simple_species(), Direction::NORTH);

    creature.turn_right();
    ASSERT_EQ(Direction::EAST, creature._dir);

    creature.turn_left();
    ASSERT_EQ(Direction::NORTH, creature._dir);
}

// ----------
// TestDarwin
// ----------

TEST(TestDarwin, test_constructor) {
    const uint32_t height = 5;
    const uint32_t width = 9;

    Darwin darwin(height, width);

    ASSERT_EQ(height, darwin._board.size());

    // Iterate over the board to check its dimensions
    for (size_t board_idx = 0; board_idx < height; ++board_idx) {
        ASSERT_EQ(width, darwin._board[board_idx].size());
    }

    ASSERT_EQ(1, darwin._current_turn);
}

TEST(TestDarwin, test_add_creature_basic) {
    const uint32_t height = 5;
    const uint32_t width = 9;

    Darwin darwin(height, width);
    Creature creature(get_simple_species(), Direction::NORTH);
    darwin.add_creature(&creature, 0, 0);

    ASSERT_EQ(&creature, darwin._board[0][0]);
    ASSERT_EQ((make_pair(0, 0)), (darwin._creature_to_pos[&creature]));
    ASSERT_EQ(0, darwin._creature_to_last_turn[&creature]);
}

TEST(TestDarwin, test_execute_instruction_hop_basic) {
    Darwin darwin(5, 5);

    Creature creature(get_simple_species(), Direction::NORTH);
    const Creature creature_copy = creature;
    darwin.add_creature(&creature, 0, 0);

    bool result = darwin.execute_instruction(&creature, InstructionType::HOP, Direction::EAST);

    ASSERT_TRUE(result);
    ASSERT_EQ(NULL, darwin._board[0][0]);
    ASSERT_EQ(&creature, darwin._board[0][1]);
    ASSERT_EQ(creature_copy, creature);
}

TEST(TestDarwin, test_execute_instruction_hop_invalid) {
    Darwin darwin(4, 4);

    Creature creature(get_simple_species(), Direction::SOUTH);

    const Creature creature_copy = creature;
    darwin.add_creature(&creature, 3, 3);

    bool result = darwin.execute_instruction(&creature, InstructionType::HOP, Direction::SOUTH);

    ASSERT_FALSE(result);
    ASSERT_EQ(&creature, darwin._board[3][3]);
    ASSERT_EQ(creature_copy, creature);
}

TEST(TestDarwin, test_execute_instruction_left_basic) {
    Darwin darwin(4, 4);

    Creature creature(get_simple_species(), Direction::NORTH);
    darwin.add_creature(&creature, 0, 0);

    bool result = darwin.execute_instruction(&creature, InstructionType::LEFT, Direction::NORTH);

    ASSERT_TRUE(result);
    ASSERT_EQ(&creature, darwin._board[0][0]);
    ASSERT_EQ(Direction::WEST, creature._dir);
}

TEST(TestDarwin, test_execute_instruction_right_basic) {
    Darwin darwin(4, 4);

    Creature creature(get_simple_species(), Direction::NORTH);
    darwin.add_creature(&creature, 0, 0);

    bool result = darwin.execute_instruction(&creature, InstructionType::RIGHT, Direction::NORTH);

    ASSERT_TRUE(result);
    ASSERT_EQ(&creature, darwin._board[0][0]);
    ASSERT_EQ(Direction::EAST, creature._dir);
}

TEST(TestDarwin, test_execute_instruction_infect_basic) {
    Darwin darwin(4, 4);

    Species simple_spec = get_simple_species();
    Creature infector(simple_spec, Direction::SOUTH);

    Species dummy_spec(vector<Instruction>(), "dummy");
    Creature infectee(dummy_spec, Direction::EAST);
    // Set the PC to a non-zero number to check that infect works correctly
    infectee._pc = 4;

    darwin.add_creature(&infector, 0, 0);
    darwin.add_creature(&infectee, 1, 0);

    bool result = darwin.execute_instruction(&infector, InstructionType::INFECT, Direction::SOUTH);

    ASSERT_TRUE(result);

    // Verify that board state is still valid
    ASSERT_EQ(&infector, darwin._board[0][0]);
    ASSERT_EQ(&infectee, darwin._board[1][0]);
    ASSERT_EQ(simple_spec, infector._species);

    // Verify that infection was actually successful
    ASSERT_EQ(simple_spec, infectee._species);
    ASSERT_EQ(0, infectee._pc);
}

TEST(TestDarwin, test_execute_instruction_infect_invalid_empty) {
    Darwin darwin(4, 4);

    Species simple_spec = get_simple_species();
    Creature infector(simple_spec, Direction::SOUTH);

    darwin.add_creature(&infector, 0, 0);

    bool result = darwin.execute_instruction(&infector, InstructionType::INFECT, Direction::SOUTH);

    ASSERT_FALSE(result);

    // Verify that board state is still valid
    ASSERT_EQ(&infector, darwin._board[0][0]);
    ASSERT_EQ(simple_spec, infector._species);
}

TEST(TestDarwin, test_execute_instruction_infect_invalid_not_enemy) {
    Darwin darwin(4, 4);

    Species simple_spec = get_simple_species();
    Creature infector(simple_spec, Direction::SOUTH);
    Creature infectee(simple_spec, Direction::EAST);
    // Set the PC to a non-zero number to see if infect was called
    infectee._pc = 1;

    darwin.add_creature(&infector, 0, 0);
    darwin.add_creature(&infectee, 1, 0);

    bool result = darwin.execute_instruction(&infector, InstructionType::INFECT, Direction::SOUTH);

    ASSERT_FALSE(result);

    // Verify that board state is still valid
    ASSERT_EQ(&infector, darwin._board[0][0]);
    ASSERT_EQ(&infectee, darwin._board[1][0]);
    ASSERT_EQ(simple_spec, infector._species);
    ASSERT_EQ(simple_spec, infectee._species);
    ASSERT_EQ(1, infectee._pc);
}

TEST(TestDarwin, test_execute_instruction_infect_invalid_wall) {
    Darwin darwin(4, 4);

    Species simple_spec = get_simple_species();
    Creature infector(simple_spec, Direction::NORTH);

    darwin.add_creature(&infector, 0, 0);

    bool result = darwin.execute_instruction(&infector, InstructionType::INFECT, Direction::NORTH);

    ASSERT_FALSE(result);

    // Verify that board state is still valid
    ASSERT_EQ(&infector, darwin._board[0][0]);
    ASSERT_EQ(simple_spec, infector._species);
}

TEST(TestDarwin, test_execute_instruction_ifs_on_empty) {
    Darwin darwin(4, 4);
    Creature probe(get_simple_species(), Direction::EAST);

    darwin.add_creature(&probe, 0, 0);

    bool if_empty_res = darwin.execute_instruction(&probe, InstructionType::IF_EMPTY, Direction::EAST);
    bool if_wall_res = darwin.execute_instruction(&probe, InstructionType::IF_WALL, Direction::EAST);
    bool if_enemy_res = darwin.execute_instruction(&probe, InstructionType::IF_ENEMY, Direction::EAST);

    // Check that the board state is still valid
    ASSERT_EQ(&probe, darwin._board[0][0]);

    ASSERT_TRUE(if_empty_res);
    ASSERT_FALSE(if_wall_res);
    ASSERT_FALSE(if_enemy_res);
}

TEST(TestDarwin, test_execute_instruction_ifs_on_wall) {
    Darwin darwin(4, 4);
    Creature probe(get_simple_species(), Direction::NORTH);

    darwin.add_creature(&probe, 0, 0);

    bool if_empty_res = darwin.execute_instruction(&probe, InstructionType::IF_EMPTY, Direction::NORTH);
    bool if_wall_res = darwin.execute_instruction(&probe, InstructionType::IF_WALL, Direction::NORTH);
    bool if_enemy_res = darwin.execute_instruction(&probe, InstructionType::IF_ENEMY, Direction::NORTH);

    // Check that the board state is still valid
    ASSERT_EQ(&probe, darwin._board[0][0]);

    ASSERT_FALSE(if_empty_res);
    ASSERT_TRUE(if_wall_res);
    ASSERT_FALSE(if_enemy_res);
}

TEST(TestDarwin, test_execute_instruction_ifs_on_enemy) {
    Darwin darwin(4, 4);
    Creature probe(get_simple_species(), Direction::EAST);
    Creature enemy(Species(vector<Instruction>(), "dumb"), Direction::NORTH);

    darwin.add_creature(&probe, 0, 0);
    darwin.add_creature(&enemy, 0, 1);

    bool if_empty_res = darwin.execute_instruction(&probe, InstructionType::IF_EMPTY, Direction::EAST);
    bool if_wall_res = darwin.execute_instruction(&probe, InstructionType::IF_WALL, Direction::EAST);
    bool if_enemy_res = darwin.execute_instruction(&probe, InstructionType::IF_ENEMY, Direction::EAST);

    // Check that the board state is still valid
    ASSERT_EQ(&probe, darwin._board[0][0]);
    ASSERT_EQ(&enemy, darwin._board[0][1]);

    ASSERT_FALSE(if_empty_res);
    ASSERT_FALSE(if_wall_res);
    ASSERT_TRUE(if_enemy_res);
}

TEST(TestDarwin, test_execute_instruction_ifs_on_friend) {
    Darwin darwin(4, 4);
    Creature probe(get_simple_species(), Direction::EAST);
    Creature friendly(get_simple_species(), Direction::NORTH);

    darwin.add_creature(&probe, 0, 0);
    darwin.add_creature(&friendly, 0, 1);

    bool if_empty_res = darwin.execute_instruction(&probe, InstructionType::IF_EMPTY, Direction::EAST);
    bool if_wall_res = darwin.execute_instruction(&probe, InstructionType::IF_WALL, Direction::EAST);
    bool if_enemy_res = darwin.execute_instruction(&probe, InstructionType::IF_ENEMY, Direction::EAST);

    // Check that the board state is still valid
    ASSERT_EQ(&probe, darwin._board[0][0]);
    ASSERT_EQ(&friendly, darwin._board[0][1]);

    ASSERT_FALSE(if_empty_res);
    ASSERT_FALSE(if_wall_res);
    ASSERT_FALSE(if_enemy_res);
}

TEST(TestDarwin, test_execute_instruction_if_random) {
    // Set the random seed to 0
    srand(0);

    Darwin darwin(4, 4);
    Creature probe(get_simple_species(), Direction::NORTH);

    darwin.add_creature(&probe, 0, 0);

    // These calls are guaranteed to be deterministic since a seed was set
    ASSERT_TRUE(darwin.execute_instruction(&probe, InstructionType::IF_RANDOM, Direction::NORTH));
    ASSERT_FALSE(darwin.execute_instruction(&probe, InstructionType::IF_RANDOM, Direction::NORTH));

    // Check that the board state is still valid
    ASSERT_EQ(&probe, darwin._board[0][0]);
}

TEST(TestDarwin, test_execute_two_action_instructions) {
    Darwin darwin(4, 4);
    Creature probe(get_simple_species(), Direction::EAST);

    darwin.add_creature(&probe, 0, 0);

    ASSERT_TRUE(darwin.execute_instruction(&probe, InstructionType::HOP, Direction::EAST));
    ASSERT_EQ(&probe, darwin._board[0][1]);

    EXPECT_ANY_THROW({
        darwin.execute_instruction(&probe, InstructionType::HOP, Direction::EAST);
    });

    ASSERT_EQ(&probe, darwin._board[0][1]);
}

TEST(TestDarwin, test_simulate_basic) {
    vector<Instruction> instructions;
    instructions.push_back(InstructionType::HOP);
    instructions.push_back(Instruction(InstructionType::GO, 0));

    Species go_forward(instructions, "forward");
    Creature creature(go_forward, Direction::EAST);

    const size_t board_dim = 4;
    Darwin darwin(board_dim, board_dim);
    darwin.add_creature(&creature, 0, 0);

    for (size_t col_idx = 0; col_idx < board_dim; ++col_idx) {
        ASSERT_EQ(&creature, darwin._board[0][col_idx]);

        darwin.simulate();
    }
}

TEST(TestDarwin, test_simulate_predator_and_bait) {
    vector<Instruction> instructions;
    instructions.push_back(Instruction(InstructionType::IF_ENEMY, 3));
    instructions.push_back(Instruction(InstructionType::HOP));
    instructions.push_back(Instruction(InstructionType::GO, 0));
    instructions.push_back(Instruction(InstructionType::INFECT, 3));
    instructions.push_back(Instruction(InstructionType::GO, 0));

    Species pred_species(instructions, "pred");
    Species bait_species(instructions, "bait");

    Creature pred_creature(pred_species, Direction::EAST);
    Creature bait_creature(bait_species, Direction::NORTH);

    const size_t board_dim = 4;
    Darwin darwin(board_dim, board_dim);
    darwin.add_creature(&pred_creature, 0, 0);
    darwin.add_creature(&bait_creature, 0, 3);

    // Simulate enough turns for the predator to infect the bait
    for (size_t col_idx = 0; col_idx < board_dim; ++col_idx) {
        darwin.simulate();
    }

    ASSERT_EQ(&pred_creature, darwin._board[0][2]);
    ASSERT_EQ(&bait_creature, darwin._board[0][3]);
    ASSERT_FALSE(pred_creature.is_enemy(bait_creature));
}
