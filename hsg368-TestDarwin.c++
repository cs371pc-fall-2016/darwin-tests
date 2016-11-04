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
#include <ostream>

using namespace std;

// ------------------
// Darwin Constructor
// ------------------

TEST(DarwinConstructor, 1x1) {
	ostringstream oss;
	string expected = ""
		"Turn = 0.\n"
		"  0\n"
		"0 .\n";
	Darwin d(1, 1);

	oss << d;
	ASSERT_EQ(expected, oss.str());
}

TEST(DarwinConstructor, 4x4) {
	ostringstream oss;
	string expected = ""
		"Turn = 0.\n"
		"  0123\n"
		"0 ....\n"
		"1 ....\n"
		"2 ....\n"
		"3 ....\n";
	Darwin d(4, 4);

	oss << d;
	ASSERT_EQ(expected, oss.str());
}

TEST(DarwinConstructor, 15x15) {
	ostringstream oss;
	string expected = ""
		"Turn = 0.\n"
		"  012345678901234\n"
		"0 ...............\n"
		"1 ...............\n"
		"2 ...............\n"
		"3 ...............\n"
		"4 ...............\n"
		"5 ...............\n"
		"6 ...............\n"
		"7 ...............\n"
		"8 ...............\n"
		"9 ...............\n"
		"0 ...............\n"
		"1 ...............\n"
		"2 ...............\n"
		"3 ...............\n"
		"4 ...............\n";
	Darwin d(15, 15);

	oss << d;
	ASSERT_EQ(expected, oss.str());
}

TEST(DarwinConstructor, 100x100) {
	ostringstream oss;
	string expected = ""
		"Turn = 0.\n"
		"  0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n"
		"0 ....................................................................................................\n"
		"1 ....................................................................................................\n"
		"2 ....................................................................................................\n"
		"3 ....................................................................................................\n"
		"4 ....................................................................................................\n"
		"5 ....................................................................................................\n"
		"6 ....................................................................................................\n"
		"7 ....................................................................................................\n"
		"8 ....................................................................................................\n"
		"9 ....................................................................................................\n"
		"0 ....................................................................................................\n"
		"1 ....................................................................................................\n"
		"2 ....................................................................................................\n"
		"3 ....................................................................................................\n"
		"4 ....................................................................................................\n"
		"5 ....................................................................................................\n"
		"6 ....................................................................................................\n"
		"7 ....................................................................................................\n"
		"8 ....................................................................................................\n"
		"9 ....................................................................................................\n"
		"0 ....................................................................................................\n"
		"1 ....................................................................................................\n"
		"2 ....................................................................................................\n"
		"3 ....................................................................................................\n"
		"4 ....................................................................................................\n"
		"5 ....................................................................................................\n"
		"6 ....................................................................................................\n"
		"7 ....................................................................................................\n"
		"8 ....................................................................................................\n"
		"9 ....................................................................................................\n"
		"0 ....................................................................................................\n"
		"1 ....................................................................................................\n"
		"2 ....................................................................................................\n"
		"3 ....................................................................................................\n"
		"4 ....................................................................................................\n"
		"5 ....................................................................................................\n"
		"6 ....................................................................................................\n"
		"7 ....................................................................................................\n"
		"8 ....................................................................................................\n"
		"9 ....................................................................................................\n"
		"0 ....................................................................................................\n"
		"1 ....................................................................................................\n"
		"2 ....................................................................................................\n"
		"3 ....................................................................................................\n"
		"4 ....................................................................................................\n"
		"5 ....................................................................................................\n"
		"6 ....................................................................................................\n"
		"7 ....................................................................................................\n"
		"8 ....................................................................................................\n"
		"9 ....................................................................................................\n"
		"0 ....................................................................................................\n"
		"1 ....................................................................................................\n"
		"2 ....................................................................................................\n"
		"3 ....................................................................................................\n"
		"4 ....................................................................................................\n"
		"5 ....................................................................................................\n"
		"6 ....................................................................................................\n"
		"7 ....................................................................................................\n"
		"8 ....................................................................................................\n"
		"9 ....................................................................................................\n"
		"0 ....................................................................................................\n"
		"1 ....................................................................................................\n"
		"2 ....................................................................................................\n"
		"3 ....................................................................................................\n"
		"4 ....................................................................................................\n"
		"5 ....................................................................................................\n"
		"6 ....................................................................................................\n"
		"7 ....................................................................................................\n"
		"8 ....................................................................................................\n"
		"9 ....................................................................................................\n"
		"0 ....................................................................................................\n"
		"1 ....................................................................................................\n"
		"2 ....................................................................................................\n"
		"3 ....................................................................................................\n"
		"4 ....................................................................................................\n"
		"5 ....................................................................................................\n"
		"6 ....................................................................................................\n"
		"7 ....................................................................................................\n"
		"8 ....................................................................................................\n"
		"9 ....................................................................................................\n"
		"0 ....................................................................................................\n"
		"1 ....................................................................................................\n"
		"2 ....................................................................................................\n"
		"3 ....................................................................................................\n"
		"4 ....................................................................................................\n"
		"5 ....................................................................................................\n"
		"6 ....................................................................................................\n"
		"7 ....................................................................................................\n"
		"8 ....................................................................................................\n"
		"9 ....................................................................................................\n"
		"0 ....................................................................................................\n"
		"1 ....................................................................................................\n"
		"2 ....................................................................................................\n"
		"3 ....................................................................................................\n"
		"4 ....................................................................................................\n"
		"5 ....................................................................................................\n"
		"6 ....................................................................................................\n"
		"7 ....................................................................................................\n"
		"8 ....................................................................................................\n"
		"9 ....................................................................................................\n";
	Darwin d(100, 100);

	oss << d;
	ASSERT_EQ(expected, oss.str());
}

// ------------------
// Darwin AddCreature
// ------------------

TEST(DarwinAddCreature, CheckerBoard) {
	ostringstream oss;
	Darwin d(15, 15);
	Species yeller('!');

	string expected = ""
		"Turn = 0.\n"
		"  012345678901234\n"
		"0 !.!.!.!.!.!.!.!\n"
		"1 .!.!.!.!.!.!.!.\n"
		"2 !.!.!.!.!.!.!.!\n"
		"3 .!.!.!.!.!.!.!.\n"
		"4 !.!.!.!.!.!.!.!\n"
		"5 .!.!.!.!.!.!.!.\n"
		"6 !.!.!.!.!.!.!.!\n"
		"7 .!.!.!.!.!.!.!.\n"
		"8 !.!.!.!.!.!.!.!\n"
		"9 .!.!.!.!.!.!.!.\n"
		"0 !.!.!.!.!.!.!.!\n"
		"1 .!.!.!.!.!.!.!.\n"
		"2 !.!.!.!.!.!.!.!\n"
		"3 .!.!.!.!.!.!.!.\n"
		"4 !.!.!.!.!.!.!.!\n";

	for (int i=0; i<15; i++) {
		for (int j=0; j<15; j++) {
			if ((i*15 + j) % 2 == 0)
				d.addCreature(Creature(yeller, WEST), i, j);
		}
	}

	oss << d;
	ASSERT_EQ(expected, oss.str());
}

TEST(DarwinAddCreature, Fill) {
	ostringstream oss;
	Darwin d(15, 15);
	Species yeller('!');

	string expected = ""
		"Turn = 0.\n"
		"  012345678901234\n"
		"0 !!!!!!!!!!!!!!!\n"
		"1 !!!!!!!!!!!!!!!\n"
		"2 !!!!!!!!!!!!!!!\n"
		"3 !!!!!!!!!!!!!!!\n"
		"4 !!!!!!!!!!!!!!!\n"
		"5 !!!!!!!!!!!!!!!\n"
		"6 !!!!!!!!!!!!!!!\n"
		"7 !!!!!!!!!!!!!!!\n"
		"8 !!!!!!!!!!!!!!!\n"
		"9 !!!!!!!!!!!!!!!\n"
		"0 !!!!!!!!!!!!!!!\n"
		"1 !!!!!!!!!!!!!!!\n"
		"2 !!!!!!!!!!!!!!!\n"
		"3 !!!!!!!!!!!!!!!\n"
		"4 !!!!!!!!!!!!!!!\n";

	for (int i=0; i<15; i++) {
		for (int j=0; j<15; j++) {
			d.addCreature(Creature(yeller, WEST), i, j);
		}
	}

	oss << d;
	ASSERT_EQ(expected, oss.str());
}

TEST(DarwinAddCreature, FillAlternating) {
	ostringstream oss;
	Darwin d(15, 15);
	Species yeller('!');
	Species snake('~');

	string expected = ""
		"Turn = 0.\n"
		"  012345678901234\n"
		"0 !~!~!~!~!~!~!~!\n"
		"1 ~!~!~!~!~!~!~!~\n"
		"2 !~!~!~!~!~!~!~!\n"
		"3 ~!~!~!~!~!~!~!~\n"
		"4 !~!~!~!~!~!~!~!\n"
		"5 ~!~!~!~!~!~!~!~\n"
		"6 !~!~!~!~!~!~!~!\n"
		"7 ~!~!~!~!~!~!~!~\n"
		"8 !~!~!~!~!~!~!~!\n"
		"9 ~!~!~!~!~!~!~!~\n"
		"0 !~!~!~!~!~!~!~!\n"
		"1 ~!~!~!~!~!~!~!~\n"
		"2 !~!~!~!~!~!~!~!\n"
		"3 ~!~!~!~!~!~!~!~\n"
		"4 !~!~!~!~!~!~!~!\n";

	for (int i=0; i<15; i++) {
		for (int j=0; j<15; j++) {
			if ((i*15 + j) % 2 == 0)
				d.addCreature(Creature(yeller, WEST), i, j);
			else
				d.addCreature(Creature(snake, WEST), i, j);
		}
	}

	oss << d;
	ASSERT_EQ(expected, oss.str());
}

// ---------------
// Darwin TakeTurn
// ---------------

TEST(DarwinTakeTurn, SmallRun) {
	ostringstream oss;
	string expected;
	Darwin d(4, 4);
	Species hopper('h');
	hopper.addInstruction("hop");
	hopper.addInstruction("go 0");

	d.addCreature(Creature(hopper, NORTH), 1, 1);
	d.addCreature(Creature(hopper, EAST),  1, 2);
	d.addCreature(Creature(hopper, SOUTH), 2, 2);
	d.addCreature(Creature(hopper, WEST),  2, 1);

	expected = ""
		"Turn = 0.\n"
		"  0123\n"
		"0 ....\n"
		"1 .hh.\n"
		"2 .hh.\n"
		"3 ....\n";
	oss << d;
	ASSERT_EQ(expected, oss.str());
	oss.str("");
	oss.clear();

	d.takeTurn();

	expected = ""
		"Turn = 1.\n"
		"  0123\n"
		"0 .h..\n"
		"1 ...h\n"
		"2 h...\n"
		"3 ..h.\n";
	oss << d;
	ASSERT_EQ(expected, oss.str());
}

TEST(DarwinTakeTurn, LongRun) {
	ostringstream oss;
	string expected;
	Darwin d(4, 4);
	Species hopper('h');
	hopper.addInstruction("hop");
	hopper.addInstruction("go 0");

	d.addCreature(Creature(hopper, NORTH), 1, 1);
	d.addCreature(Creature(hopper, EAST),  1, 2);
	d.addCreature(Creature(hopper, SOUTH), 2, 2);
	d.addCreature(Creature(hopper, WEST),  2, 1);

	expected = ""
		"Turn = 0.\n"
		"  0123\n"
		"0 ....\n"
		"1 .hh.\n"
		"2 .hh.\n"
		"3 ....\n";
	oss << d;
	ASSERT_EQ(expected, oss.str());
	oss.str("");
	oss.clear();

	for (int i=0; i<100; i++)
		d.takeTurn();

	expected = ""
		"Turn = 100.\n"
		"  0123\n"
		"0 .h..\n"
		"1 ...h\n"
		"2 h...\n"
		"3 ..h.\n";
	oss << d;
	ASSERT_EQ(expected, oss.str());
}

TEST(DarwinTakeTurn, LongRunEmpty) {
	ostringstream oss;
	string expected;
	Darwin d(4, 4);

	expected = ""
		"Turn = 0.\n"
		"  0123\n"
		"0 ....\n"
		"1 ....\n"
		"2 ....\n"
		"3 ....\n";
	oss << d;
	ASSERT_EQ(expected, oss.str());
	oss.str("");
	oss.clear();

	for (int i=0; i<100; i++)
		d.takeTurn();

	expected = ""
		"Turn = 100.\n"
		"  0123\n"
		"0 ....\n"
		"1 ....\n"
		"2 ....\n"
		"3 ....\n";
	oss << d;
	ASSERT_EQ(expected, oss.str());
}

TEST(DarwinTakeTurn, Order) {
	ostringstream oss;
	Darwin d(15, 15);
	Species hopper('h');
	Species blocker('|');
	hopper.addInstruction("hop");
	hopper.addInstruction("go 0");
	blocker.addInstruction("hop");
	blocker.addInstruction("go 0");

	for (int i=0; i<15; i++) {
		for (int j=0; j<15; j++) {
			if (i%2 == 0 && j%2 == 1)
				d.addCreature(Creature(blocker, SOUTH), i, j);
			if (i%2 == 1 && j%2 == 0)
				d.addCreature(Creature(hopper, EAST), i, j);
		}
	}

	d.takeTurn();

	string expected = ""
		"Turn = 1.\n"
		"  012345678901234\n"
		"0 ...............\n"
		"1 h|h|h|h|h|h|h|h\n"
		"2 ...............\n"
		"3 h|h|h|h|h|h|h|h\n"
		"4 ...............\n"
		"5 h|h|h|h|h|h|h|h\n"
		"6 ...............\n"
		"7 h|h|h|h|h|h|h|h\n"
		"8 ...............\n"
		"9 h|h|h|h|h|h|h|h\n"
		"0 ...............\n"
		"1 h|h|h|h|h|h|h|h\n"
		"2 ...............\n"
		"3 h|h|h|h|h|h|h|h\n"
		"4 .|.|.|.|.|.|.|.\n";

	oss << d;
	ASSERT_EQ(expected, oss.str());
}

// -------------------
// Species Constructor
// -------------------

TEST(SpeciesConstructor, Letter) {
	ostringstream oss;
	string expected = "a";
	Species s('a');

	oss << s;
	ASSERT_EQ(expected, oss.str());
}

TEST(SpeciesConstructor, Symbol) {
	ostringstream oss;
	string expected = "!";
	Species s('!');

	oss << s;
	ASSERT_EQ(expected, oss.str());
}

TEST(SpeciesConstructor, Number) {
	ostringstream oss;
	string expected = "6";
	Species s('6');

	oss << s;
	ASSERT_EQ(expected, oss.str());
}

// ---------------------
// Species: Instructions
// ---------------------

TEST(SpeciesInstructions, SingleInstruction) {
	Species s('a');
	s.addInstruction("go 0");

	ASSERT_EQ("go 0", s.getInstruction(0));
}

TEST(SpeciesInstructions, GetInstructionMultipleTimes) {
	Species s('a');
	s.addInstruction("go 1");
	s.addInstruction("go 0");

	for(int i=0; i<100; i++) {
		ASSERT_EQ("go 0", s.getInstruction(1));
		ASSERT_EQ("go 1", s.getInstruction(0));
	}
}

TEST(SpeciesInstructions, MultipleInstructions) {
	Species s('a');
	s.addInstruction("go 0");
	s.addInstruction("go 1");
	s.addInstruction("go 2");
	s.addInstruction("go 3");
	s.addInstruction("go 4");

	ASSERT_EQ("go 0", s.getInstruction(0));
	ASSERT_EQ("go 1", s.getInstruction(1));
	ASSERT_EQ("go 2", s.getInstruction(2));
	ASSERT_EQ("go 3", s.getInstruction(3));
	ASSERT_EQ("go 4", s.getInstruction(4));
}

TEST(SpeciesInstructions, MultipleInstructionsRandomAccess) {
	Species s('a');
	s.addInstruction("go 0");
	s.addInstruction("go 1");
	s.addInstruction("go 2");
	s.addInstruction("go 3");
	s.addInstruction("go 4");

	ASSERT_EQ("go 4", s.getInstruction(4));
	ASSERT_EQ("go 1", s.getInstruction(1));
	ASSERT_EQ("go 2", s.getInstruction(2));
	ASSERT_EQ("go 0", s.getInstruction(0));
	ASSERT_EQ("go 3", s.getInstruction(3));
}

TEST(SpeciesInstructions, RoverProgram) {
	Species rover('r');
	rover.addInstruction("if_enemy 9");
	rover.addInstruction("if_empty 7");
	rover.addInstruction("if_random 5");
	rover.addInstruction("left");
	rover.addInstruction("go 0");
	rover.addInstruction("right");
	rover.addInstruction("go 0");
	rover.addInstruction("hop");
	rover.addInstruction("go 0");
	rover.addInstruction("infect");
	rover.addInstruction("go 0");

	ASSERT_EQ("if_enemy 9", rover.getInstruction(0));
	ASSERT_EQ("if_empty 7", rover.getInstruction(1));
	ASSERT_EQ("if_random 5", rover.getInstruction(2));
	ASSERT_EQ("left", rover.getInstruction(3));
	ASSERT_EQ("go 0", rover.getInstruction(4));
	ASSERT_EQ("right", rover.getInstruction(5));
	ASSERT_EQ("go 0", rover.getInstruction(6));
	ASSERT_EQ("hop", rover.getInstruction(7));
	ASSERT_EQ("go 0", rover.getInstruction(8));
	ASSERT_EQ("infect", rover.getInstruction(9));
	ASSERT_EQ("go 0", rover.getInstruction(10));
}

// --------------------
// Creature Constructor
// --------------------

TEST(CreatureConstructor, Default) {
	Creature c;
	ASSERT_EQ(c.s, nullptr);
	ASSERT_EQ(c.dir, 0);
	ASSERT_EQ(c.pc, 0);
}

TEST(CreatureConstructor, NoProgramSpecies) {
	Species w('w');
	Creature c(w, 1);
	ostringstream oss;
	string expected = "w";
	ASSERT_EQ(c.s, &w);
	ASSERT_EQ(c.dir, 1);
	ASSERT_EQ(c.pc, 0);

	oss << c;

	ASSERT_EQ(oss.str(), expected);
}

TEST(CreatureConstructor, FullSpecies) {
	Species t('.');
	t.addInstruction("hop");
	t.addInstruction("go 0");
	Creature c(t, 1);
	ostringstream oss;
	string expected = ".";
	ASSERT_EQ(c.s, &t);
	ASSERT_EQ(c.dir, 1);
	ASSERT_EQ(c.pc, 0);

	oss << c;

	ASSERT_EQ(oss.str(), expected);
}

// -----------------
// Creature TakeTurn
// -----------------

TEST(CreatureTakeTurn, Hopper) {
	Species h('h');
	h.addInstruction("hop");
	h.addInstruction("go 0");
	Creature c(h, 3);
	ostringstream oss;
	string expected = "h";
	ASSERT_EQ(c.s, &h);
	ASSERT_EQ(c.dir, 3);
	ASSERT_EQ(c.pc, 0);

	bool hopNeeded = false;
	Creature dummy = Creature();
	c.takeTurn(hopNeeded, WALL, dummy);
	ASSERT_EQ(hopNeeded, true);
	ASSERT_EQ(c.pc, 1);

	oss << c;

	ASSERT_EQ(oss.str(), expected);
}

TEST(CreatureTakeTurn, Rover) {
	Species r('r');
	r.addInstruction("if_enemy 9");
	r.addInstruction("if_empty 7");
	r.addInstruction("if_random 5");
	r.addInstruction("left");
	r.addInstruction("go 0");
	r.addInstruction("right");
	r.addInstruction("go 0");
	r.addInstruction("hop");
	r.addInstruction("go 0");
	r.addInstruction("infect");
	r.addInstruction("go 0");
	Creature c(r, 3);
	ostringstream oss;
	string expected = "r";
	ASSERT_EQ(c.s, &r);
	ASSERT_EQ(c.dir, 3);
	ASSERT_EQ(c.pc, 0);

	bool hopNeeded = false;
	Creature dummy = Creature();
	c.takeTurn(hopNeeded, EMPTY, dummy);
	ASSERT_EQ(hopNeeded, true);
	ASSERT_EQ(c.pc, 8);

	oss << c;

	ASSERT_EQ(oss.str(), expected);
}

TEST(CreatureTakeTurn, Infect) {
	Species h('h');

	Species r('r');
	r.addInstruction("if_enemy 9");
	r.addInstruction("if_empty 7");
	r.addInstruction("if_random 5");
	r.addInstruction("left");
	r.addInstruction("go 0");
	r.addInstruction("right");
	r.addInstruction("go 0");
	r.addInstruction("hop");
	r.addInstruction("go 0");
	r.addInstruction("infect");
	r.addInstruction("go 0");
	Creature c(r, 3);
	ostringstream oss;
	string expected = "r";
	ASSERT_EQ(c.s, &r);
	ASSERT_EQ(c.dir, 3);
	ASSERT_EQ(c.pc, 0);

	bool hopNeeded = false;
	Creature dummy = Creature(h, 1);
	c.takeTurn(hopNeeded, OCCUPIED, dummy);
	ASSERT_EQ(hopNeeded, false);
	ASSERT_EQ(c.pc, 10);

	ASSERT_EQ(dummy.s, &r);
	ASSERT_EQ(dummy.pc, 0);

	oss << c;

	ASSERT_EQ(oss.str(), expected);
}

// --------------
// Creature Front
// --------------

TEST(CreatureFront, West) {
	Species rover('r');
	rover.addInstruction("if_enemy 9");
	rover.addInstruction("if_empty 7");
	rover.addInstruction("if_random 5");
	rover.addInstruction("left");
	rover.addInstruction("go 0");
	rover.addInstruction("right");
	rover.addInstruction("go 0");
	rover.addInstruction("hop");
	rover.addInstruction("go 0");
	rover.addInstruction("infect");
	rover.addInstruction("go 0");

	Creature c(rover, WEST);
	int frontPos = c.front(3, 8, 8);
	ASSERT_EQ(frontPos, 2);
}

TEST(CreatureFront, North) {
	Species rover('r');
	rover.addInstruction("if_enemy 9");
	rover.addInstruction("if_empty 7");
	rover.addInstruction("if_random 5");
	rover.addInstruction("left");
	rover.addInstruction("go 0");
	rover.addInstruction("right");
	rover.addInstruction("go 0");
	rover.addInstruction("hop");
	rover.addInstruction("go 0");
	rover.addInstruction("infect");
	rover.addInstruction("go 0");

	Creature c(rover, NORTH);
	int frontPos = c.front(50, 7, 11);
	ASSERT_EQ(frontPos, 39);
}

TEST(CreatureFront, East) {
	Species trap('t');
	trap.addInstruction("if_enemy 3");
	trap.addInstruction("left");
	trap.addInstruction("go 0");
	trap.addInstruction("infect");
	trap.addInstruction("go 0");

	Creature c(trap, EAST);
	int frontPos = c.front(50, 11, 7);
	ASSERT_EQ(frontPos, 51);
}

TEST(CreatureFront, South) {
	Species trap('t');
	trap.addInstruction("if_enemy 3");
	trap.addInstruction("left");
	trap.addInstruction("go 0");
	trap.addInstruction("infect");
	trap.addInstruction("go 0");

	Creature c(trap, SOUTH);
	int frontPos = c.front(50, 8, 8);
	ASSERT_EQ(frontPos, 58);
}

TEST(CreatureFront,  WestWall) {
	Species hopper('h');
	hopper.addInstruction("hop");
	hopper.addInstruction("go 0");

	Creature c(hopper, WEST);
	int frontPos = c.front(8, 8, 8);
	ASSERT_EQ(frontPos, -1);
}

TEST(CreatureFront,  NorthWall) {
	Species hopper('h');
	hopper.addInstruction("hop");
	hopper.addInstruction("go 0");

	Creature c(hopper, NORTH);
	int frontPos = c.front(0, 15, 9);
	ASSERT_EQ(frontPos, -1);
}

TEST(CreatureFront,  EastWall) {
	Species trap('t');
	trap.addInstruction("if_enemy 3");
	trap.addInstruction("left");
	trap.addInstruction("go 0");
	trap.addInstruction("infect");
	trap.addInstruction("go 0");

	Creature c(trap, EAST);
	int frontPos = c.front(27, 36, 7);
	ASSERT_EQ(frontPos, -1);
}

TEST(CreatureFront,  SouthWall) {
	Species trap('t');
	trap.addInstruction("if_enemy 3");
	trap.addInstruction("left");
	trap.addInstruction("go 0");
	trap.addInstruction("infect");
	trap.addInstruction("go 0");

	Creature c(trap, SOUTH);
	int frontPos = c.front(60, 8, 8);
	ASSERT_EQ(frontPos, -1);
}

// ----------------
// Creature Program
// ----------------

TEST(CreatureProgram, Basic) {
	ostringstream oss;

	Species s('a');
	s.addInstruction("hop");
	s.addInstruction("hop");
	s.addInstruction("hop");
	s.addInstruction("hop");
	s.addInstruction("hop");
	s.addInstruction("hop");
	s.addInstruction("hop");
	s.addInstruction("hop");
	s.addInstruction("hop");
	s.addInstruction("hop");
	s.addInstruction("go 0");
	ASSERT_EQ("hop", s.getInstruction(0));
	ASSERT_EQ("hop", s.getInstruction(1));
	ASSERT_EQ("hop", s.getInstruction(2));
	ASSERT_EQ("hop", s.getInstruction(3));
	ASSERT_EQ("hop", s.getInstruction(4));
	ASSERT_EQ("hop", s.getInstruction(5));
	ASSERT_EQ("hop", s.getInstruction(6));
	ASSERT_EQ("hop", s.getInstruction(7));
	ASSERT_EQ("hop", s.getInstruction(8));
	ASSERT_EQ("hop", s.getInstruction(9));
	ASSERT_EQ("go 0", s.getInstruction(10));

	Creature c(s, WEST);

	bool hopNeeded = false;
	Creature dummy = Creature();
	for(int i=0; i<10; i++) {
		ASSERT_EQ("hop", s.getInstruction(c.pc));
		c.takeTurn(hopNeeded, EMPTY, dummy);
	}
	ASSERT_EQ("go 0", s.getInstruction(c.pc));
}

TEST(CreatureProgram, Branching) {
	ostringstream oss;

	Species s('a');
	s.addInstruction("if_wall 3");
	s.addInstruction("if_empty 4");
	s.addInstruction("if_enemy 5");
	s.addInstruction("go 6");
	s.addInstruction("go 7");
	s.addInstruction("go 8");
	s.addInstruction("right");
	s.addInstruction("left");
	s.addInstruction("hop");
	s.addInstruction("go 0");

	Creature c1(s, WEST);
	Creature c2(s, WEST);
	Creature c3(s, WEST);

	bool hopNeeded = false;
	Creature dummy = Creature();
	ASSERT_EQ("if_wall 3", s.getInstruction(c1.pc));
	ASSERT_EQ("if_wall 3", s.getInstruction(c2.pc));
	ASSERT_EQ("if_wall 3", s.getInstruction(c3.pc));
	c1.takeTurn(hopNeeded, WALL, dummy);
	ASSERT_EQ(NORTH, c1.dir);
	c2.takeTurn(hopNeeded, EMPTY, dummy);
	ASSERT_EQ(SOUTH, c2.dir);
	c3.takeTurn(hopNeeded, OCCUPIED, dummy);
	ASSERT_EQ(WEST,  c3.dir);
	ASSERT_EQ(9,     c3.pc);
	ASSERT_EQ(true,  hopNeeded);
}

TEST(CreatureProgram, Infection) {
	ostringstream oss;
	bool hopNeeded;

	Species s1('t');
	s1.addInstruction("if_enemy 3");
	s1.addInstruction("right");
	s1.addInstruction("go 0");
	s1.addInstruction("infect");
	s1.addInstruction("go 0");
	Species s2('?');
	s2.addInstruction("right");

	Creature trap(s1,  WEST);
	Creature dummy(s2, WEST);

	oss << dummy;
	ASSERT_EQ("?", oss.str());
	oss.str("");
	oss.clear();

	trap.takeTurn(hopNeeded, OCCUPIED, dummy);

	oss << dummy;
	ASSERT_EQ("t", oss.str());
	ASSERT_EQ("if_enemy 3", dummy.s->getInstruction(0));
	ASSERT_EQ("right", dummy.s->getInstruction(1));
	ASSERT_EQ("go 0", dummy.s->getInstruction(2));
	ASSERT_EQ("infect", dummy.s->getInstruction(3));
	ASSERT_EQ("go 0", dummy.s->getInstruction(4));
}

// -------------------
// Comprehensive Tests
// -------------------

TEST(DarwinComplete, Basic) {
	Species hopper('h');
	hopper.addInstruction("hop");
	hopper.addInstruction("go 0");

	Species rover('r');
	rover.addInstruction("if_enemy 9");
	rover.addInstruction("if_empty 7");
	rover.addInstruction("if_random 5");
	rover.addInstruction("left");
	rover.addInstruction("go 0");
	rover.addInstruction("right");
	rover.addInstruction("go 0");
	rover.addInstruction("hop");
	rover.addInstruction("go 0");
	rover.addInstruction("infect");
	rover.addInstruction("go 0");

	Species trap('t');
	trap.addInstruction("if_enemy 3");
	trap.addInstruction("left");
	trap.addInstruction("go 0");
	trap.addInstruction("infect");
	trap.addInstruction("go 0");

	ostringstream oss;
	string expected = ""
		"Turn = 5.\n"
		"  012345678\n"
		"0 t........\n"
		"1 ....r....\n"
		"2 .........\n"
		"3 .......r.\n"
		"4 .........\n"
		"5 .........\n"
		"6 ........t\n";

	Darwin d(7, 9);
	d.addCreature(Creature(trap, SOUTH), 0, 0);
	d.addCreature(Creature(hopper, EAST), 3, 2);
	d.addCreature(Creature(rover, NORTH), 5, 4);
	d.addCreature(Creature(trap, WEST), 6, 8);

	for(int i = 0; i <5; i++)
	{
		d.takeTurn();
	}
	oss << d;

	ASSERT_EQ(oss.str(), expected);
}

TEST(DarwinComplete, FullHopper) {
	Species hopper('h');
	hopper.addInstruction("hop");
	hopper.addInstruction("go 0");

	ostringstream oss;
	string expected = ""
		"Turn = 5.\n"
		"  012345678901234\n"
		"0 hhhhhhhhhhhhhhh\n"
		"1 hhhhhhhhhhhhhhh\n"
		"2 hhhhhhhhhhhhhhh\n"
		"3 hhhhhhhhhhhhhhh\n"
		"4 hhhhhhhhhhhhhhh\n"
		"5 hhhhhhhhhhhhhhh\n"
		"6 hhhhhhhhhhhhhhh\n"
		"7 hhhhhhhhhhhhhhh\n"
		"8 hhhhhhhhhhhhhhh\n"
		"9 hhhhhhhhhhhhhhh\n"
		"0 hhhhhhhhhhhhhhh\n"
		"1 hhhhhhhhhhhhhhh\n"
		"2 hhhhhhhhhhhhhhh\n"
		"3 hhhhhhhhhhhhhhh\n"
		"4 hhhhhhhhhhhhhhh\n";

	Darwin d(15, 15);
	for(int i = 0; i < d.numRows; i++)
		for(int j = 0; j < d.numCols; j++)
		{
			d.addCreature(Creature(hopper, NORTH), i, j);
		}


	for(int i = 0; i <5; i++)
	{
		d.takeTurn();
	}
	oss << d;

	ASSERT_EQ(oss.str(), expected);
}

TEST(DarwinComplete, HopperColumns) {
	Species hopper('h');
	hopper.addInstruction("hop");
	hopper.addInstruction("go 0");

	ostringstream oss;
	string expected = ""
		"Turn = 5.\n"
		"  012345678901234\n"
		"0 h.h.h.h.h.h.h.h\n"
		"1 h.h.h.h.h.h.h.h\n"
		"2 h.h.h.h.h.h.h.h\n"
		"3 h.h.h.h.h.h.h.h\n"
		"4 h.h.h.h.h.h.h.h\n"
		"5 h.h.h.h.h.h.h.h\n"
		"6 h.h.h.h.h.h.h.h\n"
		"7 h.h.h.h.h.h.h.h\n"
		"8 h.h.h.h.h.h.h.h\n"
		"9 h.h.h.h.h.h.h.h\n"
		"0 h.h.h.h.h.h.h.h\n"
		"1 h.h.h.h.h.h.h.h\n"
		"2 h.h.h.h.h.h.h.h\n"
		"3 h.h.h.h.h.h.h.h\n"
		"4 h.h.h.h.h.h.h.h\n";

	Darwin d(15, 15);
	for(int i = 0; i < d.numRows; i++)
		for(int j = 0; j < d.numCols; j++)
		{
			if(j%2 == 0)
				d.addCreature(Creature(hopper, NORTH), i, j);
		}


	for(int i = 0; i <5; i++)
	{
		d.takeTurn();
	}
	oss << d;

	ASSERT_EQ(oss.str(), expected);
}
