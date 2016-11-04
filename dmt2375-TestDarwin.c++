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
// ----

TEST(DarwinFixture, test) {
    Darwin x = Darwin(2,2);
    ASSERT_TRUE(x.dummy());}

/*
	CREATURE
		constructor
		run
		action

	SPECIES
		constructor
		addInstruction
		currentInstruction
		printName
		==

	DARWIN
		constructor
		addCreature
		run
		findObstacle
		checkBounds
		<<
*/


// --------
// creature
// --------

// constructor
TEST(DarwinFixture, creature_constructor_1) {
    Species food = Species('f');
    Creature test = Creature(&food, Direction::north);
    ASSERT_TRUE(*test.spec == food);
    ASSERT_TRUE(test.dir == Direction::north);
}

TEST(DarwinFixture, creature_constructor_2) {
    Species rover = Species('r');
    Creature test = Creature(&rover, Direction::south);
    ASSERT_TRUE(*test.spec == rover);
    ASSERT_TRUE(test.dir == Direction::south);
}

TEST(DarwinFixture, creature_constructor_3) {
    Species hopper = Species('h');
    Creature test = Creature(&hopper, Direction::east);
    ASSERT_TRUE(*test.spec == hopper);
    ASSERT_FALSE(test.dir == Direction::north);
}

// run

// Tests that creature turns left when given left Instruction
TEST(DarwinFixture, creature_run_1) {
    Species rover = Species('r');
    rover.addInstruction(Instruction::left);
    rover.addInstruction(Instruction::go, 0);
    Creature c = Creature(&rover, Direction::north);
    Instruction ins = c.run(Obstacle::nothing);
    ASSERT_TRUE(ins == Instruction::left);
}

// Tests that creature turns right when given right Instruction
TEST(DarwinFixture, creature_run_2) {
    Species turner = Species('t');
    turner.addInstruction(Instruction::right);
    turner.addInstruction(Instruction::go, 0);
    Creature c = Creature(&turner, Direction::south);
    Instruction ins = c.run(Obstacle::nothing);
    ASSERT_TRUE(ins == Instruction::right);
}

TEST(DarwinFixture, creature_run_3) {
    Species hopper = Species('h');
    hopper.addInstruction(Instruction::hop);
    hopper.addInstruction(Instruction::go, 0);
    Creature c = Creature(&hopper, Direction::east);
    Instruction ins = c.run(Obstacle::nothing);
    ASSERT_TRUE(ins == Instruction::hop);
}

//action

//test hop
TEST(DarwinFixture, creature_action_hop) {
	Species hopper = Species('h');
    hopper.addInstruction(Instruction::hop);
    hopper.addInstruction(Instruction::go, 0);
    Creature c = Creature(&hopper, Direction::east);

    bool ret = c.action(c.spec->currentInstruction(0), Obstacle::nothing);

    ASSERT_FALSE(ret);
    ASSERT_EQ(c.pc, 1);
}

//test if_enemy
TEST(DarwinFixture, creature_action_enemy) {
	Species rover = Species('r');
    rover.addInstruction(Instruction::if_enemy, 9);
    rover.addInstruction(Instruction::if_empty, 7);
    rover.addInstruction(Instruction::if_random, 5);
    rover.addInstruction(Instruction::left);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::right);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::hop);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::infect);
    rover.addInstruction(Instruction::go, 0);

    Creature c = Creature(&rover, Direction::east);

    bool ret = c.action(c.spec->currentInstruction(0), Obstacle::enemy);

    ASSERT_TRUE(ret);
    ASSERT_EQ(c.pc, 9);
}

//test if_empty
TEST(DarwinFixture, creature_action_empty) {
	Species rover = Species('r');
    rover.addInstruction(Instruction::if_enemy, 9);
    rover.addInstruction(Instruction::if_empty, 7);
    rover.addInstruction(Instruction::if_random, 5);
    rover.addInstruction(Instruction::left);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::right);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::hop);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::infect);
    rover.addInstruction(Instruction::go, 0);

    Creature c = Creature(&rover, Direction::east);
   	c.pc = 1;
    bool ret = c.action(c.spec->currentInstruction(1), Obstacle::nothing);

    ASSERT_TRUE(ret);
    ASSERT_EQ(c.pc, 7);
}

//test left
TEST(DarwinFixture, creature_action_left) {
	Species rover = Species('r');
    rover.addInstruction(Instruction::if_enemy, 9);
    rover.addInstruction(Instruction::if_empty, 7);
    rover.addInstruction(Instruction::if_random, 5);
    rover.addInstruction(Instruction::left);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::right);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::hop);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::infect);
    rover.addInstruction(Instruction::go, 0);

    Creature c = Creature(&rover, Direction::east);
    c.pc = 3;
    bool ret = c.action(c.spec->currentInstruction(3), Obstacle::nothing);

    ASSERT_FALSE(ret);
    ASSERT_EQ(c.pc, 4);
    ASSERT_EQ(c.dir, Direction::north);
}

//test right
TEST(DarwinFixture, creature_action_right) {
	Species rover = Species('r');
    rover.addInstruction(Instruction::if_enemy, 9);
    rover.addInstruction(Instruction::if_empty, 7);
    rover.addInstruction(Instruction::if_random, 5);
    rover.addInstruction(Instruction::left);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::right);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::hop);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::infect);
    rover.addInstruction(Instruction::go, 0);

    Creature c = Creature(&rover, Direction::east);
    c.pc = 5;
    bool ret = c.action(c.spec->currentInstruction(5), Obstacle::nothing);

    ASSERT_FALSE(ret);
    ASSERT_EQ(c.pc, 6);
    ASSERT_EQ(c.dir, Direction::south);
}

//test infect
TEST(DarwinFixture, creature_action_infect) {
	Species rover = Species('r');
    rover.addInstruction(Instruction::if_enemy, 9);
    rover.addInstruction(Instruction::if_empty, 7);
    rover.addInstruction(Instruction::if_random, 5);
    rover.addInstruction(Instruction::left);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::right);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::hop);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::infect);
    rover.addInstruction(Instruction::go, 0);

    Creature c = Creature(&rover, Direction::east);
    c.pc = 9;
    bool ret = c.action(c.spec->currentInstruction(9), Obstacle::enemy);

    ASSERT_FALSE(ret);
    ASSERT_EQ(c.pc, 10);
    ASSERT_EQ(c.dir, Direction::east);
}

// -------
// species
// -------

// constructor
TEST(DarwinFixture, species_constructor_1) {
	Species test = Species('t');
	ASSERT_TRUE(test.name == 't');
}

TEST(DarwinFixture, species_constructor_2) {
	Species test = Species('r');
	ASSERT_TRUE(test.name != 'z');
}

TEST(DarwinFixture, species_constructor_3) {
	Species test = Species('f');
	ASSERT_TRUE(test.name == 'f');
}

// addInstruction
TEST(DarwinFixture, species_add_instruction_1) {
	Species test = Species('s');
	test.addInstruction(Instruction::hop);

	ProgramInstruction pi = ProgramInstruction(Instruction::hop, -1);

	ASSERT_EQ(test.ins_list[0].inst, pi.inst);
	ASSERT_EQ(test.ins_list[0].inst_value, pi.inst_value);
}

TEST(DarwinFixture, species_add_instruction_2) {
	Species test = Species('s');
	test.addInstruction(Instruction::if_empty, 4);

	ProgramInstruction pi = ProgramInstruction(Instruction::if_empty, 4);

	ASSERT_EQ(test.ins_list[0].inst, pi.inst);
	ASSERT_EQ(test.ins_list[0].inst_value, pi.inst_value);
}

TEST(DarwinFixture, species_add_instruction_3) {
	Species rover = Species('r');
	rover.addInstruction(Instruction::if_enemy, 9);
    rover.addInstruction(Instruction::if_empty, 7);
    rover.addInstruction(Instruction::if_random, 5);
    rover.addInstruction(Instruction::left);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::right);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::hop);
    rover.addInstruction(Instruction::go, 0);
    rover.addInstruction(Instruction::infect);
    rover.addInstruction(Instruction::go, 0);

    ProgramInstruction ar[11] = {
		ar[0] = ProgramInstruction(Instruction::if_enemy, 9),
		ar[1] = ProgramInstruction(Instruction::if_empty, 7),
		ar[2] = ProgramInstruction(Instruction::if_random, 5),
		ar[3] = ProgramInstruction(Instruction::left, -1),
		ar[4] = ProgramInstruction(Instruction::go, 0),
		ar[5] = ProgramInstruction(Instruction::right, -1),
		ar[6] = ProgramInstruction(Instruction::go, 0),
		ar[7] = ProgramInstruction(Instruction::hop, -1),
		ar[8] = ProgramInstruction(Instruction::go, 0),
		ar[9] = ProgramInstruction(Instruction::infect, -1),
		ar[10] = ProgramInstruction(Instruction::go, 0)
	};

	for(int i = 0; i < 11; ++i) {
		ASSERT_EQ(rover.ins_list[i].inst, ar[i].inst);
		ASSERT_EQ(rover.ins_list[i].inst_value, ar[i].inst_value);
	}
	
}


// currentInstruction
TEST(DarwinFixture, species_current_instruction_1) {
    Species test = Species('a');
    test.addInstruction(Instruction::go, 0);
    ASSERT_TRUE(test.ins_list[0].inst == Instruction::go);
}

TEST(DarwinFixture, species_current_instruction_2) {
    Species test = Species('j');
    test.addInstruction(Instruction::hop);
    ASSERT_TRUE(test.ins_list[0].inst == Instruction::hop);
}

TEST(DarwinFixture, species_current_instruction_3) {
    Species test = Species('k');
    test.addInstruction(Instruction::hop);
    test.addInstruction(Instruction::hop);
    test.addInstruction(Instruction::left);
    ASSERT_TRUE(test.ins_list[(int) test.ins_list.size() - 1].inst == Instruction::left);
}

TEST(DarwinFixture, species_current_instruction_4) {
    Species test = Species('p');
    test.addInstruction(Instruction::left);
    test.addInstruction(Instruction::right);
    ASSERT_TRUE(test.ins_list[1].inst == Instruction::right);
}

// ==
TEST(DarwinFixture, species_equal_1) {
	Species s1 = Species('s');
	Species s2 = Species('s');

	ASSERT_TRUE(s1 == s2);
}

TEST(DarwinFixture, species_equal_2) {
	Species s1 = Species('s');
	s1.addInstruction(Instruction::hop);
	Species s2 = Species('s');
	s2.addInstruction(Instruction::infect);

	ASSERT_TRUE(s1 == s2);
}

TEST(DarwinFixture, species_equal_3) {
	Species s1 = Species('s');
	s1.addInstruction(Instruction::hop);
	Species s2 = Species('a');
	s2.addInstruction(Instruction::hop);

	ASSERT_FALSE(s1 == s2);
}

TEST(DarwinFixture, species_equal_4) {
	Species s1 = Species('s');
	s1.addInstruction(Instruction::hop);

	ASSERT_TRUE(s1 == s1);
}

// ------
// darwin
// ------
/*
	DARWIN
		constructor *
		addCreature *
		run
		findObstacle *
		checkBounds *
		<<
*/

// constructor
TEST(DarwinFixture, darwin_constructor_1) {
    Darwin test = Darwin(0, 0);
    ASSERT_TRUE((int) test.world.size() == 0);
}

TEST(DarwinFixture, darwin_constructor_2) {
    Darwin test = Darwin(75, 75);
    ASSERT_TRUE((int) test.world.size() == 75);
    ASSERT_TRUE((int) test.world[0].size() == 75);
}

TEST(DarwinFixture, darwin_constructor_3) {
    Darwin test = Darwin(99, 99);
    ASSERT_TRUE((int) test.world.size() != 0);
    ASSERT_FALSE((int) test.world[0].size() == 100);
}


// add creatures
TEST(DarwinFixture, darwin_addCreature_1) {
	Darwin test = Darwin(4,4);
	Species s = Species('s');
	test.addCreature(&s, Direction::north, 0, 0);
	ASSERT_TRUE(test.world[0][0] != -1);
}

TEST(DarwinFixture, darwin_addCreature_2) {
	Darwin test = Darwin(4,4);
	Species s = Species('s');
	test.addCreature(&s, Direction::north, 0, 0);
	test.addCreature(&s, Direction::south, 0, 1);
	ASSERT_TRUE(test.world[0][1] != -1);
}

TEST(DarwinFixture, darwin_addCreature_3) {
	Darwin test = Darwin(16,9);
	Species s = Species('s');
	test.addCreature(&s, Direction::north);
	test.addCreature(&s, Direction::south);
	// search through the world and ensure there have been two placed
	int count = 0;
	for(int row = 0; row < (int)test.world.size(); row++) {
		for(int col = 0; col < (int)test.world[row].size(); col++) {
			if(test.world[row][col] != -1) {
				++count;
			}
		}
	}
	ASSERT_TRUE(count == 2);
}

// find Obstacle
TEST(DarwinFixture, darwin_find_obstacle_1) {
    Darwin d = Darwin(10, 10);
    ASSERT_TRUE(d.findObstacle(0, 0, 0, Direction::north) == Obstacle::wall);
}

TEST(DarwinFixture, darwin_find_obstacle_2) {
    Darwin d = Darwin(50, 50);
    ASSERT_TRUE(d.findObstacle(0, 25, 25, Direction::north) == Obstacle::nothing);
}

TEST(DarwinFixture, darwin_find_obstacle_3) {
    Darwin d = Darwin(100, 100);
    Species trap = Species('t');
    d.addCreature(&trap, Direction::east, 0, 0);
    d.addCreature(&trap, Direction::east, 0, 1);
    ASSERT_TRUE(d.findObstacle(0, 0, 0, Direction::east) == Obstacle::friendly);
}

TEST(DarwinFixture, darwin_find_obstacle_4) {
    Darwin d = Darwin(25, 25);
    Species trap = Species('t');
    Species food = Species('f');
    d.addCreature(&trap, Direction::east, 0, 0);
    d.addCreature(&food, Direction::east, 0, 1);
    ASSERT_TRUE(d.findObstacle(0, 0, 0, Direction::east) == Obstacle::enemy);
}

TEST(DarwinFixture, darwin_find_obstacle_5) {
    Darwin d = Darwin(30, 30);
    ASSERT_TRUE(d.findObstacle(0, 29, 29, Direction::north) == Obstacle::nothing);
}

// check bounds
TEST(DarwinFixture, darwin_check_bounds_1) {
    Darwin d = Darwin(100, 100);
    ASSERT_TRUE(d.checkBounds(0, 99) == true);
}

TEST(DarwinFixture, darwin_check_bounds_2) {
    Darwin d = Darwin(100, 100);
    ASSERT_TRUE(d.checkBounds(0, 100) == false);
}

TEST(DarwinFixture, darwin_check_bounds_3) {
    Darwin d = Darwin(4, 4);
    ASSERT_TRUE(d.checkBounds(0, -1) == false);
}

TEST(DarwinFixture, darwin_check_bounds_4) {
    Darwin d = Darwin(50, 50);
    ASSERT_TRUE(d.checkBounds(40, 32) == true);
}

TEST(DarwinFixture, darwin_check_bounds_5) {
    Darwin d = Darwin(0, 0);
    ASSERT_TRUE(d.checkBounds(0, 0) == false);
}

TEST(DarwinFixture, darwin_run_1) {
	Darwin d = Darwin(4,4);
	Species s = Species('s');
	s.addInstruction(Instruction::hop);
    s.addInstruction(Instruction::go, 0);

    d.addCreature(&s, Direction::north, 3, 0);
    d.addCreature(&s, Direction::north, 3, 1);
    d.addCreature(&s, Direction::north, 3, 2);
    d.addCreature(&s, Direction::north, 3, 3);

    d.run();

    ASSERT_TRUE(d.world[2][0] == 0 && 
    	d.world[2][1] == 1 && 
    	d.world[2][2] == 2 &&
    	d.world[2][3] == 3);
}

TEST(DarwinFixture, darwin_run_2) {
	Darwin d = Darwin(4,4);
	Species s = Species('s');
	s.addInstruction(Instruction::hop);
	s.addInstruction(Instruction::left);
    s.addInstruction(Instruction::go, 0);

    d.addCreature(&s, Direction::south, 0, 0);

    d.run();
    ASSERT_TRUE(d.world[1][0] == 0);

    d.run();
    d.run();
    ASSERT_TRUE(d.world[1][1] == 0);

    d.run();
    d.run();
    ASSERT_TRUE(d.world[0][1] == 0);
}

TEST(DarwinFixture, darwin_run_3) {
	Darwin d = Darwin(4,4);
	Species s = Species('s');
	s.addInstruction(Instruction::if_wall, 2);
    s.addInstruction(Instruction::hop);
    s.addInstruction(Instruction::left);
    s.addInstruction(Instruction::go, 0);

    d.addCreature(&s, Direction::north, 0, 0);

    d.run();
    ASSERT_TRUE(d.world[0][0] == 0);

    d.run();
    ASSERT_TRUE(d.world[0][0] == 0);

    d.run();
    ASSERT_TRUE(d.world[1][0] == 0);
}


// << operator
TEST(DarwinFixture, output_operator_1) {
	string board = "  0123\n0 ....\n1 ....\n2 ....\n3 ....\n\n";
    Darwin d = Darwin(4, 4);

    ostringstream w;
    w << d;

    ASSERT_EQ(board, w.str());
}

TEST(DarwinFixture, output_operator_2) {
	string board = "  0123\n0 .s..\n1 ....\n2 ....\n3 ....\n\n";
    Darwin d = Darwin(4, 4);
    Species s = Species('s');

    d.addCreature(&s, Direction::north, 0, 1);
    ostringstream w;
    w << d;

    ASSERT_EQ(board, w.str());
}

TEST(DarwinFixture, output_operator_3) {
	string board = "  0123\n0 .s..\n1 .s..\n2 .s..\n3 ....\n\n";
    Darwin d = Darwin(4, 4);
    Species s = Species('s');

    d.addCreature(&s, Direction::north, 0, 1);
    d.addCreature(&s, Direction::north, 1, 1);
    d.addCreature(&s, Direction::north, 2, 1);
    ostringstream w;
    w << d;

    ASSERT_EQ(board, w.str());
}

TEST(DarwinFixture, output_operator_4) {
	string board = "  01\n0 ts\n1 st\n\n";
    Darwin d = Darwin(2, 2);
    Species s = Species('s');
    Species s2 = Species('t');

    d.addCreature(&s, Direction::north, 0, 1);
    d.addCreature(&s, Direction::north, 1, 0);
    d.addCreature(&s2, Direction::north, 0, 0);
    d.addCreature(&s2, Direction::north, 1, 1);
    ostringstream w;
    w << d;

    ASSERT_EQ(board, w.str());
}

TEST(DarwinFixture, output_operator_5) {
	string board = "  01234\n0 s...t\n1 .....\n2 t...s\n\n";
    Darwin d = Darwin(3, 5);
    Species s = Species('s');
    Species s2 = Species('t');

    d.addCreature(&s, Direction::north, 0, 0);
    d.addCreature(&s, Direction::north, 2, 4);
    d.addCreature(&s2, Direction::north, 0, 4);
    d.addCreature(&s2, Direction::north, 2, 0);
    ostringstream w;
    w << d;

    ASSERT_EQ(board, w.str());
}