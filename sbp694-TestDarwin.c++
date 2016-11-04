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
#include <cassert>   // assert
#include "Darwin.h"
#include <iostream>

using namespace std;

//----------------
//addInstruction
//----------------

TEST(DarwinFixture, addInstruction1){
	Species s1;
	s1.addInstruction("hop");
	ASSERT_EQ(s1._inst[0], "hop");
}

TEST(DarwinFixture, addInstruction2){
	Species s2;
	s2.addInstruction("hop");
	s2.addInstruction("infect");
	s2.addInstruction("left");
	s2.addInstruction("right");
	vector<string> x = {"hop", "infect", "left", "right"};
	for(int a = 0; a < 4; a++){
		ASSERT_EQ(s2._inst[a], x[a]);
	}
}

TEST(DarwinFixture, addInstruction3){
	Species s3;
	s3.addInstruction("hop");
	ASSERT_EQ(s3._inst[0], "hop");
}

//---------
//next_inst
//---------

TEST(DarwinFixture, next_inst1){
	Species s;
	s.addInstruction("hop");
	s.addInstruction("if_enemy 3");
	s.addInstruction("go 0");
	s.addInstruction("infect");
	
	string new_inst = s.next_inst(1);
	ASSERT_TRUE(new_inst == "if_enemy 3");
}


TEST(DarwinFixture, next_inst2){
	Species s;
	s.addInstruction("hop");
	s.addInstruction("if_enemy 3");
	s.addInstruction("go 0");
	s.addInstruction("infect");
	s.addInstruction("right");	
	s.addInstruction("go 0");

	string new_inst = s.next_inst(5);
	ASSERT_TRUE(new_inst == "go 0");
	
}

TEST(DarwinFixture, next_inst3){
	Species s;
	s.addInstruction("hop");
	s.addInstruction("if_enemy 3");
	s.addInstruction("go 0");
	s.addInstruction("infect");
	
	string new_inst = s.next_inst(3);
	ASSERT_TRUE(new_inst == "infect");

}

TEST(DarwinFixture, next_inst4){
	Species s;
	s.addInstruction("if_wall 5)");
	s.addInstruction("if_enemy 3");
	s.addInstruction("if_empty 77");
	s.addInstruction("right");
	s.addInstruction("left");
	
	string new_inst = s.next_inst(4);
	ASSERT_TRUE(new_inst == "left");

}

// ----
// move
// ----

TEST(DarwinFixture, move1) {
	Species hopper;
	hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
	Creature c(hopper, 3, 'h');
	pair<int, int> point = c.move(0, 1, true, nullptr);
	ASSERT_EQ(point, make_pair(1, 1));
	ASSERT_TRUE(c._d == 3);
	ASSERT_TRUE(c._name == 'h');
	ASSERT_TRUE(c._pc == 1);
}

TEST(DarwinFixture, move2) {
	Species hopper;
	hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
	Species rover;
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
	Creature c1(rover, 2, 'r');
	Creature c2(hopper, 0, 'h');
	pair<int, int> point = c1.move(0, 1, false, &c2);
	ASSERT_EQ(point, make_pair(0, 1));
	ASSERT_TRUE(c1._d == 2);
	ASSERT_TRUE(c1._name == 'r');
	ASSERT_TRUE(c1._pc == 10);
	ASSERT_TRUE(c2._d == 0);
	ASSERT_TRUE(c2._name == 'r');
	ASSERT_TRUE(c2._pc == 0);

}

TEST(DarwinFixture, move3) {
	Species s;
	s.addInstruction("if_empty 3");
    s.addInstruction("left");
    s.addInstruction("go 0");
	s.addInstruction("hop");
    s.addInstruction("go 0");
	Creature c(s, 1, 's');
	pair<int, int> point = c.move(0, 1, false, nullptr);
	ASSERT_EQ(point, make_pair(0, 1));
	ASSERT_TRUE(c._d == 0);
	ASSERT_TRUE(c._name == 's');
	ASSERT_TRUE(c._pc == 2);
}

// ----------
// print_name
// ----------

TEST(DarwinFixture, print_name1) {
	Species s;
	Creature c(s, 3, 'p');
	ASSERT_TRUE(c._name == 'p');
}

TEST(DarwinFixture, print_name2) {
	Species s;
	Creature c(s, 'v');
	ASSERT_TRUE(c._name == 'v');
}

TEST(DarwinFixture, print_name3) {
	Species s;
	Creature c(s, 'k');
	ASSERT_TRUE(c._name == 'k');
}

//--------------
//find_direction
//--------------

TEST(DarwinFixture, find_direction1){
	Species s;
	Creature c(s, 0, 'a');
	pair<int, int> dir = c.find_direction(1,1);
	ASSERT_TRUE(dir.first == 1);
	ASSERT_TRUE(dir.second == 0);
}

TEST(DarwinFixture, find_direction2){
	Species s;
	Creature c(s, 1, 'b');
	pair<int, int> dir = c.find_direction(1,1);
	ASSERT_TRUE(dir.first == 0);
	ASSERT_TRUE(dir.second == 1);
}

TEST(DarwinFixture, find_direction3){
	Species s;
	Creature c(s, 2, 'c');
	pair<int, int> dir = c.find_direction(1,1);
	ASSERT_TRUE(dir.first == 1);
	ASSERT_TRUE(dir.second == 2);
}

TEST(DarwinFixture, find_direction4){
	Species s;
	Creature c(s, 3, 'd');
	pair<int, int> dir = c.find_direction(1,1);
	ASSERT_TRUE(dir.first == 2);
	ASSERT_TRUE(dir.second == 1);
}

//--------------
//change_species
//--------------

TEST(DarwinFixture, change_species0){
	Species s0;
	Creature c0(s0, 2, 'f');
	Species s1;
	Creature c1(s1, 3, 'v');
	c1.change_species(&c0);
	ASSERT_TRUE(c1._s == c0._s);
}

TEST(DarwinFixture, change_species1){
	Species s1;
	Creature c1(s1, 3, 'd');
	Species s2;
	Creature c2(s2, 0, 'e');
	c2.change_species(&c1);
	ASSERT_TRUE(c2._s == c1._s);
}

TEST(DarwinFixture, change_species2){
	Species s3;
	Creature c3(s3, 1, 'x');
	Species s4;
	Creature c4(s4, 2, 'y');
	c4.change_species(&c3);
	ASSERT_TRUE(c4._s == c3._s);
}

TEST(DarwinFixture,change_species3){
	Species x;
	Creature x1(x, 2, 'p');
	Species y;
	Creature y1(y, 1 , 'z');
	y1.change_species(&x1);
	ASSERT_TRUE(y1._name == 'p');
}

TEST(DarwinFixture, change_species4){
	Species s5;
	Creature c5(s5, 3, 'f');
	Species s6;
	Creature c6(s6, 0, 'g');
	c6.change_species(&c5);
	ASSERT_TRUE(c6._name == 'f');
}

TEST(DarwinFixture, change_species5){
	Species s7;
	Creature c7(s7, 3, 'l');
	Species s8;
	Creature c8(s8, 1, 'k');
	c8.change_species(&c7);
	ASSERT_TRUE(c8._name == 'l');

}

// -----------
// operator <<
// -----------

// ------------
// addCreature1
// ------------

TEST(DarwinFixture, addCreature1_1) {
	Species s;
	Creature c(s, 3, 'l');
	Darwin z(5, 5);
	srand(0);
	z.addCreature(c);
	srand(0);
	int x = std::rand() % z._board.size();
	int y = std::rand() % z._board[0].size();
	for (int i = 0; i < (int)z._board.size(); ++i) {
	    for (int j = 0; j < (int)z._board[0].size(); ++j) {
	    	if (z._board[x][y] != nullptr) {
		        ASSERT_TRUE(z._board[x][y] == &c);
		        ASSERT_TRUE(z._check_board[x][y] == 'f');
		    }
		    else {
		    	ASSERT_TRUE(z._board[x][y] == nullptr);
		        ASSERT_TRUE(z._check_board[x][y] == '\0');
		    }
	    }
	}
}

TEST(DarwinFixture, addCreature1_2) {
	Species s;
	Creature c(s, 1, 'q');
	Darwin z(17, 20);
	srand(0);
	z.addCreature(c);
	srand(0);
	int x = std::rand() % z._board.size();
	int y = std::rand() % z._board[0].size();
	for (int i = 0; i < (int)z._board.size(); ++i) {
	    for (int j = 0; j < (int)z._board[0].size(); ++j) {
	    	if (z._board[x][y] != nullptr) {
		        ASSERT_TRUE(z._board[x][y] == &c);
		        ASSERT_TRUE(z._check_board[x][y] == 'f');
		    }
		    else {
		    	ASSERT_TRUE(z._board[x][y] == nullptr);
		        ASSERT_TRUE(z._check_board[x][y] == '\0');
		    }
	    }
	}
}

TEST(DarwinFixture, addCreature1_3) {
	Species s;
	Creature c(s, 2, 'j');
	Darwin z(6, 4);
	srand(0);
	z.addCreature(c);
	srand(0);
	int x = std::rand() % z._board.size();
	int y = std::rand() % z._board[0].size();
	for (int i = 0; i < (int)z._board.size(); ++i) {
	    for (int j = 0; j < (int)z._board[0].size(); ++j) {
	    	if (z._board[x][y] != nullptr) {
		        ASSERT_TRUE(z._board[x][y] == &c);
		        ASSERT_TRUE(z._check_board[x][y] == 'f');
		    }
		    else {
		    	ASSERT_TRUE(z._board[x][y] == nullptr);
		        ASSERT_TRUE(z._check_board[x][y] == '\0');
		    }
	    }
	}
}

// ------------
// addCreature2
// ------------

TEST(DarwinFixture, addCreature2_1) {
	Species s;
	Creature c(s, 2, 'd');
	Darwin z(15, 9);
	int x = 4;
	int y = 2;
	z.addCreature(c, x, y);
	for (int i = 0; i < (int)z._board.size(); ++i) {
	    for (int j = 0; j < (int)z._board[0].size(); ++j) {
	    	if (z._board[x][y] != nullptr) {
		        ASSERT_TRUE(z._board[x][y] == &c);
		        ASSERT_TRUE(z._check_board[x][y] == 'f');
		    }
		    else {
		    	ASSERT_TRUE(z._board[x][y] == nullptr);
		        ASSERT_TRUE(z._check_board[x][y] == '\0');
		    }
	    }
	}
}

TEST(DarwinFixture, addCreature2_2) {
	Species s;
	Creature c(s, 1, 'n');
	Darwin z(12, 8);
	int x = 10;
	int y = 5;
	z.addCreature(c, x, y);
	for (int i = 0; i < (int)z._board.size(); ++i) {
	    for (int j = 0; j < (int)z._board[0].size(); ++j) {
	    	if (z._board[x][y] != nullptr) {
		        ASSERT_TRUE(z._board[x][y] == &c);
		        ASSERT_TRUE(z._check_board[x][y] == 'f');
		    }
		    else {
		    	ASSERT_TRUE(z._board[x][y] == nullptr);
		        ASSERT_TRUE(z._check_board[x][y] == '\0');
		    }
	    }
	}
}

TEST(DarwinFixture, addCreature2_3) {
	Species s;
	Creature c(s, 3, 'p');
	Darwin z(3, 10);
	int x = 2;
	int y = 7;
	z.addCreature(c, x, y);
	for (int i = 0; i < (int)z._board.size(); ++i) {
	    for (int j = 0; j < (int)z._board[0].size(); ++j) {
	    	if (z._board[x][y] != nullptr) {
		        ASSERT_TRUE(z._board[x][y] == &c);
		        ASSERT_TRUE(z._check_board[x][y] == 'f');
		    }
		    else {
		    	ASSERT_TRUE(z._board[x][y] == nullptr);
		        ASSERT_TRUE(z._check_board[x][y] == '\0');
		    }
	    }
	}
}

// -----
// start
// -----

TEST(DarwinFixture, start1) {
	Species food;
    food.addInstruction("left");
    food.addInstruction("go 0");
    Species hopper;
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");
    Species rover;
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
    Species trap;
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");
	Creature c1(food, 2, 'f');
	Creature c2(hopper, 1, 'h');
	Creature c3(trap, 0, 't');
	Creature c4(rover, 3, 'r');
	Darwin z(5, 5);
	z.addCreature(c1, 3, 1);
	z.addCreature(c2, 4, 3);
	z.addCreature(c3, 2, 2);
	z.addCreature(c4, 0, 2);
	z.start(5);

	ASSERT_TRUE(z._board[3][1] == &c1);
	ASSERT_TRUE(z._board[0][3] == &c2);
	ASSERT_TRUE(z._board[4][1] == &c3);
	ASSERT_TRUE(z._board[3][2] == &c4);
	for (int i = 0; i < (int)z._board.size(); ++i) {
	    for (int j = 0; j < (int)z._board[0].size(); ++j) {
	        if (z._board[i][j] != nullptr) {
		        ASSERT_TRUE(z._check_board[i][j] == 'f');
		    }
		    else {
		    	ASSERT_TRUE(z._board[i][j] == nullptr);
		        ASSERT_TRUE(z._check_board[i][j] == '.' || z._check_board[i][j] == '\0');
		    }
	    }
	}
}