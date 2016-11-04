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
#include <sstream>

using namespace std;

// ----
// test
// ----

// ---
// Darwin Tests
// ---

TEST(DarwinFixture, test) {
    Darwin x(1,1);
    ASSERT_TRUE(x.dummy());
}

/* Darwin Constructor Tests */
TEST(Darwin, Darwin1){
	Darwin d(1,1);
	ASSERT_EQ(d._rows, 1);
}
TEST(Darwin, Darwin2){
	Darwin d(1,1);
	ASSERT_EQ(d._cols, 1);
}
TEST(Darwin, Darwin3){
	Darwin d(1,1);
	ASSERT_EQ(0, d._grid[0][0]);
}

/* Darwin addCreature Tests */
TEST(Darwin, addCreature1){
	Darwin d(1,1);
	Species s('s');
	Creature c(&s, 0);
	d.addCreature(&c, 0, 0);
	ASSERT_EQ(&c, d._grid[0][0]);
}
TEST(Darwin, addCreature2){
	Darwin d(1,1);
	Species s1('s');
	Species s2('d');
	Creature c1(&s1, 0);
	Creature c2(&s2, 1);
	d.addCreature(&c1, 0, 0);
	d.addCreature(&c2, 0, 0);
	ASSERT_EQ(&c2, d._grid[0][0]);
}
TEST(Darwin, addCreature3){
	Darwin d(2,2);
	Species s1('s');
	Species s2('d');
	Creature c1(&s1, 1);
	Creature c2(&s2, 2);
	d.addCreature(&c1, 0, 0);
	d.addCreature(&c2, 1, 1);
	ASSERT_EQ(&c1, d._grid[0][0]);
}
TEST(Darwin, addCreature4){
	Darwin d(2,2);
	Species s1('s');
	Species s2('d');
	Creature c1(&s1, 3);
	Creature c2(&s2, 4);
	d.addCreature(&c1, 0, 0);
	d.addCreature(&c2, 1, 1);
	ASSERT_EQ(&c2, d._grid[1][1]);
}

/* Darwin execMove Tests */
TEST(Darwin, execMove1){
	Darwin d(2,2);
	Species s('h');
    s.addInstruction("hop");
    s.addInstruction("go 0");
	Creature c(&s, 2);
	d.addCreature(&c, 0, 0);
	d.execMove();
	ASSERT_EQ(&c, d._grid[0][1]);
}
TEST(Darwin, execMove2){
	Darwin d(2,2);
	Species s('h');
    s.addInstruction("hop");
    s.addInstruction("go 0");
	Creature c(&s, 0);
	d.addCreature(&c, 0, 0);
	d.execMove();
	ASSERT_EQ(&c, d._grid[0][0]);
}
TEST(Darwin, execMove3){
	Darwin d(2,2);
	Species s('h');
    s.addInstruction("left");
    s.addInstruction("go 0");
	Creature c(&s, 0);
	d.addCreature(&c, 0, 0);
	d.execMove();
	ASSERT_EQ(&c, d._grid[0][0]);
}
TEST(Darwin, execMove4){
	Darwin d(2,2);
	Species s('h');
    s.addInstruction("right");
    s.addInstruction("go 0");
	Creature c(&s, 0);
	d.addCreature(&c, 0, 0);
	d.execMove();
	ASSERT_EQ(&c, d._grid[0][0]);
}
TEST(Darwin, execMove5){
	Darwin d(2,2);
	Species s1('s');
	Species s2('d');
	Creature c1(&s1, 0);
	Creature c2(&s2, 1);
	s1.addInstruction("hop");
	s1.addInstruction("go 0");
	s2.addInstruction("infect");
    s2.addInstruction("go 0");
	d.addCreature(&c1, 0, 0);
	d.addCreature(&c2, 1, 0);
	d.execMove();
	ASSERT_EQ(c2._s, c1._s);
}

// ---
// Species Tests
// ---

/* Species Constructor Tests */
TEST(Species, Species1){
	Species s('s');
	ASSERT_EQ('s', s._name);
}

/* Species Add Instruction Tests */
TEST(Species, addInstruction1){
	Species s('s');
	ASSERT_EQ(0, s._v.size());
}
TEST(Species, addInstruction2){
	Species s('s');
	s.addInstruction("left");
	ASSERT_EQ(1, s._v.size());
}
TEST(Species, addInstruction3){
	Species s('s');
	s.addInstruction("left");
	s.addInstruction("go 0");
	ASSERT_EQ(2, s._v.size());
}
TEST(Species, addInstruction4){
	Species s('s');
	s.addInstruction("left");
	s.addInstruction("go 0");
	ASSERT_EQ("left", s._v[0]);
}
TEST(Species, addInstruction5){
	Species s('s');
	s.addInstruction("left");
	s.addInstruction("go 0");
	ASSERT_EQ("go 0", s._v[1]);
}

/* Species print */
TEST(Species, print1){
	Species s('s');
	ostringstream os;
	os << s;
	ASSERT_EQ("s", os.str());
}
TEST(Species, print2){
	Species s('s');
	s.addInstruction("left");
	ostringstream os;
	os << s;
	ASSERT_EQ("s", os.str());
}
TEST(Species, print3){
	const char x = 's';
	Species s(x);
	s.addInstruction("left");
	ostringstream os;
	os << s;
	ASSERT_EQ("s", os.str());
}


// ---
// Creature Tests
// ---

/* Creature Constructor Tests */
TEST(Creature, Creature1){
	Species s('s');
	Creature c(&s, 0);
	ASSERT_EQ(c._s, &s);
}
TEST(Creature, Creature2){
	Species s('s');
	Creature c(&s, 1);
	ASSERT_EQ(c._pc, 0);
}
TEST(Creature, Creature3){
	Species s('s');
	Creature c(&s, 2);
	ASSERT_EQ(c._dir, 2);
}

/* Creature spaceAhead Tests */
TEST(Creature, spaceAhead1){
	Species s('s');
	Creature c(&s, 0);
	int row = 1;
	int col = 1;
	c.spaceAhead(row, col);
	ASSERT_EQ(col, 0);
}
TEST(Creature, spaceAhead2){
	Species s('s');
	Creature c(&s, 1);
	int row = 1;
	int col = 1;
	c.spaceAhead(row, col);
	ASSERT_EQ(row, 0);
}
TEST(Creature, spaceAhead3){
	Species s('s');
	Creature c(&s, 2);
	int row = 1;
	int col = 1;
	c.spaceAhead(row, col);
	ASSERT_EQ(col, 2);
}
TEST(Creature, spaceAhead4){
	Species s('s');
	Creature c(&s, 3);
	int row = 1;
	int col = 1;
	c.spaceAhead(row, col);
	ASSERT_EQ(row, 2);
}

/* Creature isEnemy Tests */
TEST(Creature, isEnemy1){
	Species s1('s');
	Creature c1(&s1, 0);
	Creature c2(&s1, 1);
	ASSERT_FALSE(c1.isEnemy(&c2));
}
TEST(Creature, isEnemy2){
	Species s1('s');
	Species s2('d');
	Creature c1(&s1, 1);
	Creature c2(&s2, 2);
	ASSERT_TRUE(c1.isEnemy(&c2));
}
TEST(Creature, isEnemy3){
	Species s1('s');
	Species s2('s');
	Creature c1(&s1, 2);
	Creature c2(&s2, 3);
	ASSERT_TRUE(c1.isEnemy(&c2));
}

/* Creature Execute Tests */
TEST(Creature, execute1){
	Species s('s');
	Creature c(&s, 2);
	s.addInstruction("if_enemy 9");
    s.addInstruction("if_empty 7");
    s.addInstruction("if_random 5");
    s.addInstruction("left");
    s.addInstruction("go 0");
    s.addInstruction("right");
    s.addInstruction("go 0");
    s.addInstruction("hop");
    s.addInstruction("go 0");
    s.addInstruction("infect");
    s.addInstruction("go 0");
	ASSERT_EQ("right", c.execute(false, false, false));
}
TEST(Creature, execute2){
	Species s('s');
	Creature c(&s, 2);
	s.addInstruction("if_enemy 9");
    s.addInstruction("if_empty 7");
    s.addInstruction("if_random 5");
    s.addInstruction("left");
    s.addInstruction("go 0");
    s.addInstruction("right");
    s.addInstruction("go 0");
    s.addInstruction("hop");
    s.addInstruction("go 0");
    s.addInstruction("infect");
    s.addInstruction("go 0");
	ASSERT_EQ("hop", c.execute(true, false, false));
}
TEST(Creature, execute3){
	Species s('s');
	Creature c(&s, 2);
	s.addInstruction("if_enemy 9");
    s.addInstruction("if_empty 7");
    s.addInstruction("if_random 5");
    s.addInstruction("left");
    s.addInstruction("go 0");
    s.addInstruction("right");
    s.addInstruction("go 0");
    s.addInstruction("hop");
    s.addInstruction("go 0");
    s.addInstruction("infect");
    s.addInstruction("go 0");
	ASSERT_EQ("left", c.execute(false, true, false));
}
TEST(Creature, execute4){
	Species s('s');
	Creature c(&s, 2);
	s.addInstruction("if_enemy 9");
    s.addInstruction("if_empty 7");
    s.addInstruction("if_random 5");
    s.addInstruction("left");
    s.addInstruction("go 0");
    s.addInstruction("right");
    s.addInstruction("go 0");
    s.addInstruction("hop");
    s.addInstruction("go 0");
    s.addInstruction("infect");
    s.addInstruction("go 0");
	ASSERT_EQ("infect", c.execute(false, false, true));
}
TEST(Creature, execute5){
	Species s('s');
	Creature c(&s, 2);
	s.addInstruction("if_enemy 9");
    s.addInstruction("if_empty 7");
    s.addInstruction("if_random 5");
    s.addInstruction("left");
    s.addInstruction("go 0");
    s.addInstruction("right");
    s.addInstruction("go 0");
    s.addInstruction("hop");
    s.addInstruction("go 0");
    s.addInstruction("infect");
    s.addInstruction("go 0");
	ASSERT_EQ("hop", c.execute(true, true, false));
}
TEST(Creature, execute6){
	Species s('s');
	Creature c(&s, 2);
	s.addInstruction("if_enemy 9");
    s.addInstruction("if_empty 7");
    s.addInstruction("if_random 5");
    s.addInstruction("left");
    s.addInstruction("go 0");
    s.addInstruction("right");
    s.addInstruction("go 0");
    s.addInstruction("hop");
    s.addInstruction("go 0");
    s.addInstruction("infect");
    s.addInstruction("go 0");
	ASSERT_EQ("infect", c.execute(true, false, true));
}
TEST(Creature, execute7){
	Species s('s');
	Creature c(&s, 2);
	s.addInstruction("if_enemy 9");
    s.addInstruction("if_empty 7");
    s.addInstruction("if_random 5");
    s.addInstruction("left");
    s.addInstruction("go 0");
    s.addInstruction("right");
    s.addInstruction("go 0");
    s.addInstruction("hop");
    s.addInstruction("go 0");
    s.addInstruction("infect");
    s.addInstruction("go 0");
	ASSERT_EQ("infect", c.execute(false, true, true));
}
TEST(Creature, execute8){
	Species s('s');
	Creature c(&s, 2);
	s.addInstruction("if_enemy 9");
    s.addInstruction("if_empty 7");
    s.addInstruction("if_random 5");
    s.addInstruction("left");
    s.addInstruction("go 0");
    s.addInstruction("right");
    s.addInstruction("go 0");
    s.addInstruction("hop");
    s.addInstruction("go 0");
    s.addInstruction("infect");
    s.addInstruction("go 0");
	ASSERT_EQ("infect", c.execute(true, true, true));
}

/* Creature rotateLeft Tests */
TEST(Creature, rotateLeft1){
	Species s('s');
	Creature c(&s, 2);
	c.rotateLeft();
	ASSERT_EQ(c._dir, 1);
}
TEST(Creature, rotateLeft2){
	Species s('s');
	Creature c(&s, 0);
	c.rotateLeft();
	ASSERT_EQ(c._dir, 3);
}

/* Creature rotateRight Tests */
TEST(Creature, rotateRight1){
	Species s('s');
	Creature c(&s, 2);
	c.rotateRight();
	ASSERT_EQ(c._dir, 3);
}
TEST(Creature, rotateRight2){
	Species s('s');
	Creature c(&s, 3);
	c.rotateRight();
	ASSERT_EQ(c._dir, 0);
}

/* Creature infect Tests */
TEST(Creature, infect1){
	Species s1('s');
	Species s2('d');
	Creature c1(&s1, 1);
	Creature c2(&s2, 2);
	c1.infect(&c2);
	ASSERT_EQ(c1._s, c2._s);
}
TEST(Creature, infect2){
	Species s1('s');
	Species s2('d');
	Creature c1(&s1, 1);
	Creature c2(&s2, 2);
	c1.infect(&c2);
	ASSERT_EQ(c2._pc, 0);
}

/* Creature Print Tests */
TEST(Creature, print1){
	Species s('s');
	Creature c(&s, 2);
	ostringstream os;
	os << c;
	ASSERT_EQ("s", os.str());
}
TEST(Creature, print2){
	Species s('s');
	s.addInstruction("left");
	Creature c(&s, 2);
	ostringstream os;
	os << c;
	ASSERT_EQ("s", os.str());
}
TEST(Creature, print3){
	const char x = 's';
	Species s(x);
	Creature c(&s, 2);
	s.addInstruction("left");
	ostringstream os;
	os << c;
	ASSERT_EQ("s", os.str());
}

// TEST(Creature, execute){
// 	Species s('s');
// 	Creature c(&s, 2);
// 	cout << c.execute(false, false, false);
// 	//ASSERT_EQ("s", os.str());
// }

// TEST(Darwin, grid1){
// 	Species food('f');
//     food.addInstruction("left");
//     food.addInstruction("go 0");
//     Creature f0(&food, 2);
//     Darwin d(1, 1);
//     d.addCreature(&f0, 0, 0);
//     ASSERT_EQ("  0\n0 f", d.printBoard(1));
// }

