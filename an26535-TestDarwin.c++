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

TEST(DarwinFixture, Species_addInstruction0){

	Species food('f');

	ASSERT_TRUE(food.addInstruction("hop"));
    ASSERT_TRUE(food.addInstruction("left"));
    ASSERT_TRUE(food.addInstruction("right"));
    ASSERT_TRUE(food.addInstruction("infect"));
    ASSERT_TRUE(food.addInstruction("if_empty 0"));
    ASSERT_TRUE(food.addInstruction("if_wall 0"));
    ASSERT_TRUE(food.addInstruction("if_random 0"));
    ASSERT_TRUE(food.addInstruction("if_enemy 0"));
    ASSERT_TRUE(food.addInstruction("go 0"));

}

TEST(DarwinFixture, Species_addInstruction1){

	Species food('f');

	ASSERT_TRUE(food.addInstruction("hop 0"));
    ASSERT_TRUE(food.addInstruction("left 0"));
    ASSERT_TRUE(food.addInstruction("right 0"));
    ASSERT_TRUE(food.addInstruction("infect 0"));
    ASSERT_TRUE(food.addInstruction("if_empty 0"));
    ASSERT_TRUE(food.addInstruction("if_wall 0"));
    ASSERT_TRUE(food.addInstruction("if_random 0"));
    ASSERT_TRUE(food.addInstruction("if_enemy 0"));
    ASSERT_TRUE(food.addInstruction("go 0"));

}

TEST(DarwinFixture, Species_addInstruction2){

	Species food('f');

	ASSERT_FALSE(food.addInstruction("abc"));
    ASSERT_FALSE(food.addInstruction("test"));
    ASSERT_FALSE(food.addInstruction("hops"));

}

TEST(DarwinFixture, Species_act0){

	Species food('f');

	int a = 0;
	int pc = 0;

	ASSERT_TRUE(food.addInstruction("hop"));

	ASSERT_EQ(food.act(a, pc), (int)Instr::hop);


}

TEST(DarwinFixture, Species_act1){

	Species food('f');

	int a = 0;
	int pc = 1;

    ASSERT_TRUE(food.addInstruction("left"));

	ASSERT_EQ(food.act(a, pc), (int)Instr::left);


}

TEST(DarwinFixture, Species_act2){

	Species food('f');

	int a = 0;
	int pc = 2;

    ASSERT_TRUE(food.addInstruction("right"));

	ASSERT_EQ(food.act(a, pc), (int)Instr::right);


}

TEST(DarwinFixture, Species_act3){

	Species food('f');

	int a = 0;
	int pc = 3;

    ASSERT_TRUE(food.addInstruction("infect"));

	ASSERT_EQ(food.act(a, pc), (int)Instr::infect);

}

TEST(DarwinFixture, Species_act4){

	Species food('f');

	int a = 0;
	int pc = 4;

    ASSERT_TRUE(food.addInstruction("if_empty 0"));

	ASSERT_EQ(food.act(a, pc), (int)Instr::if_empty);


}

TEST(DarwinFixture, Species_act5){

	Species food('f');

	int a = 0;
	int pc = 5;

    ASSERT_TRUE(food.addInstruction("if_wall 0"));

	ASSERT_EQ(food.act(a, pc), (int)Instr::if_wall);


}

TEST(DarwinFixture, Species_act6){

	Species food('f');

	int a = 0;
	int pc = 6;

    ASSERT_TRUE(food.addInstruction("if_random 0"));

	ASSERT_EQ(food.act(a, pc), (int)Instr::if_random);


}

TEST(DarwinFixture, Species_act7){

	Species food('f');

	int a = 0;
	int pc = 7;

    ASSERT_TRUE(food.addInstruction("if_enemy 0"));

	ASSERT_EQ(food.act(a, pc), (int)Instr::if_enemy);


}

TEST(DarwinFixture, Species_act8){

	Species food('f');

	int a = 0;
	int pc = 8;

    ASSERT_TRUE(food.addInstruction("go 0"));

	ASSERT_EQ(food.act(a, pc), (int)Instr::go);


}

TEST(DarwinFixture, Species_s_print_self0){

	Species food('f');

	ostringstream output;
	food.s_print_self(output);

	ASSERT_EQ("f", output.str());

}

TEST(DarwinFixture, Species_s_print_self1){

	Species food('.');

	ostringstream output;
	food.s_print_self(output);

	ASSERT_EQ(".", output.str());

}

TEST(DarwinFixture, Species_s_print_self2){

	Species food('f');

	ostringstream output;
	food.s_print_self(output);

	ASSERT_EQ("f", output.str());

}

TEST(DarwinFixture, Creature_c_print_self0){

	Species food('.');
	Creature c(&food);

	ostringstream output;
	c.c_print_self(output);

	ASSERT_EQ(".", output.str());

}

TEST(DarwinFixture, Creature_c_print_self1){

	Species food('a');
	Creature c(&food);

	ostringstream output;
	c.c_print_self(output);

	ASSERT_EQ("a", output.str());

}

TEST(DarwinFixture, Creature_c_print_self2){

	Species food('\n');
	Creature c(&food);

	ostringstream output;
	c.c_print_self(output);

	ASSERT_EQ("\n", output.str());
}


TEST(DarwinFixture, Creature_act0){ //hop

	int turn = 1;
	int z = (int)Front::empty;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 2");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 0;

	ASSERT_EQ(c.act(z, turn), (int)Instr::hop);

}
TEST(DarwinFixture, Creature_act1){ //left

	int turn = 1;
	int z = (int)Front::empty;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 2");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 1;

	ASSERT_EQ(c.act(z, turn), (int)Instr::left);

}


TEST(DarwinFixture, Creature_act2){ //right

	int turn = 1;
	int z = (int)Front::empty;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 2");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 2;

	ASSERT_EQ(c.act(z, turn), (int)Instr::right);

}

TEST(DarwinFixture, Creature_act3){ //infect

	int turn = 1;
	int z = (int)Front::empty;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 2");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 3;

	ASSERT_EQ(c.act(z, turn), (int)Instr::infect);

}

TEST(DarwinFixture, Creature_act4){ //empty

	int turn = 1;
	int z = (int)Front::empty;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 2");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 4;

	ASSERT_EQ(c.act(z, turn), (int)Instr::hop);

}

TEST(DarwinFixture, Creature_act5){ //empty 

	int turn = 1;
	int z = (int)Front::wall;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 2");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 4;

	ASSERT_FALSE(c.act(z, turn) == (int)Instr::hop);

}

TEST(DarwinFixture, Creature_act6){ //wall

	int turn = 1;
	int z = (int)Front::wall;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 2");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 5;

	ASSERT_EQ(c.act(z, turn), (int)Instr::left);

}

TEST(DarwinFixture, Creature_act7){ //wall

	int turn = 1;
	int z = (int)Front::empty;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_random 2");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 5;

	ASSERT_FALSE(c.act(z, turn) == (int)Instr::left);

}

TEST(DarwinFixture, Creature_act8){ //random

	srand(0);

	int turn = 1;
	int z = (int)Front::creature;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 0");
    food.addInstruction("left");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 6;

	ASSERT_EQ(c.act(z, turn), (int)Instr::hop);

}
TEST(DarwinFixture, Creature_act9){ //random

	srand(0);

	int turn = 1;
	int z = (int)Front::creature;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("if_random 7");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 2");
    food.addInstruction("left");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 6;

	ASSERT_EQ(c.act(z, turn), (int)Instr::infect);

}

TEST(DarwinFixture, Creature_act10){ //enemy

	int turn = 1;
	int z = (int)Front::creature;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 2");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 7;

	ASSERT_EQ(c.act(z, turn), (int)Instr::left);

}

TEST(DarwinFixture, Creature_act11){ //enemy

	int turn = 1;
	int z = (int)Front::empty;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 2");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 7;

	ASSERT_EQ(c.act(z, turn), (int)Instr::hop);

}

TEST(DarwinFixture, Creature_act12){ //go

	int turn = 1;
	int z = (int)Front::empty;

	Species food('f');

	food.addInstruction("hop");
    food.addInstruction("left");
    food.addInstruction("right");
    food.addInstruction("infect");
    food.addInstruction("if_empty 0");
    food.addInstruction("if_wall 1");
    food.addInstruction("if_random 2");
    food.addInstruction("if_enemy 1");
    food.addInstruction("go 0");

	Creature c(&food);
	c._pc = 8;

	ASSERT_EQ(c.act(z, turn), (int)Instr::hop);

}



TEST(DarwinFixture, Creature_infect0){

	Species food('f');
	Species rover('r');

	Creature c1(&food);
	Creature c2(&rover);

	ASSERT_TRUE(c1.infect(&c1, &c2));
}

TEST(DarwinFixture, Creature_infect1){

	Species food('f');
	Species trap('t');

	Creature c1(&food);
	Creature c2(&trap);

	ASSERT_TRUE(c1.infect(&c1, &c2));
}

TEST(DarwinFixture, Creature_infect2){

	Species food('f');

	Creature c1(&food);
	Creature c2(&food);

	ASSERT_FALSE(c1.infect(&c1, &c2));
}

TEST(DarwinFixture, Creature_same0){

	Species food('f');

	Creature a0 (&food);

	ASSERT_TRUE(a0.same(&a0, &a0));

}

TEST(DarwinFixture, Creature_same1){

	Species food('f');
	Species flying('f');

	Creature a0 (&food);
	Creature a1 (&flying);

	ASSERT_FALSE(a0.same(&a0, &a1));

}

TEST(DarwinFixture, Creature_same2){

	Species food('f');
	Species rover('r');

	Creature a0 (&food);
	Creature a2 (&rover);

	ASSERT_FALSE(a0.same(&a0, &a2));

}


TEST(DarwinFixture, Darwin_addCreature0){

	Species food('f');

	Creature c1(&food);
	Creature c2(&food);

	Darwin x(10,10);
    ASSERT_TRUE(x.addCreature(&c1, 0, 0, (int)Direction::south));

}


TEST(DarwinFixture, Darwin_addCreature1){

	Species food('f');

	Creature c1(&food);
	Creature c2(&food);

	Darwin x(10,10);
    ASSERT_FALSE(x.addCreature(&c1, 100, 100, (int)Direction::south));

}


TEST(DarwinFixture, Darwin_addCreature2){

	Species food('f');

	Creature c1(&food);
	Creature c2(&food);

	Darwin x(10,10);
    ASSERT_FALSE(x.addCreature(&c2, -1, 0, (int)Direction::south));

}

TEST(DarwinFixture, Darwin_drawBoard0){

	Darwin x(8,8);

	ostringstream output;
	x.drawBoard(output);

	ASSERT_EQ("Turn = 0.\n  01234567\n0 ........\n1 ........\n2 ........\n3 ........\n4 ........\n5 ........\n6 ........\n7 ........\n\n", output.str());
}


TEST(DarwinFixture, Darwin_drawBoard1){

	Darwin x(8,8);

	Species food('f');
	Species hopper('h');

	Creature c0(&food);
    Creature c1(&hopper);
    Creature c2(&hopper);
    Creature c3(&hopper);
    Creature c4(&hopper);
    Creature c5(&food);

	x.addCreature(&c0, 0, 0, (int)Direction::east);
    x.addCreature(&c1, 3, 3, (int)Direction::north);
    x.addCreature(&c2, 3, 4, (int)Direction::east);
    x.addCreature(&c3, 4, 4, (int)Direction::south);
    x.addCreature(&c4, 4, 3, (int)Direction::west);
    x.addCreature(&c5, 7, 7, (int)Direction::north);

	ostringstream output;
	x.drawBoard(output);

	ASSERT_EQ("Turn = 0.\n  01234567\n0 f.......\n1 ........\n2 ........\n3 ...hh...\n4 ...hh...\n5 ........\n6 ........\n7 .......f\n\n", output.str());
}

TEST(DarwinFixture, Darwin_drawBoard2){

	Darwin x(1,1);

	Species food('f');

	Creature c0(&food);

	//x.addCreature(&c0, (int)Direction::east, 0, 0);

	ostringstream output;
	x.drawBoard(output);

	ASSERT_EQ("Turn = 0.\n  0\n0 .\n\n", output.str());
}

TEST(DarwinFixture, Darwin_play0){

	Darwin x(1,1);

	x.play(4);
	ASSERT_EQ(x.turn, 5);

}


TEST(DarwinFixture, Darwin_play1){

	Darwin x(1,1);

	x.play(0);
	ASSERT_EQ(x.turn, 0);

}


TEST(DarwinFixture, Darwin_play2){

	Darwin x(1,1);

	x.play(-1);
	ASSERT_EQ(x.turn, 0);

}

TEST(DarwinFixture, Darwin_minor_update0){

	Darwin x(8,8);

	Species food('f');

	Creature c0(&food);

	x.addCreature(&c0, 0, 0, (int)Direction::east);

    x.minor_update(&c0, (int)Direction::east, (int)Instr::hop, 0, 0);

    ASSERT_EQ(x.map[0][1], &c0);


}

TEST(DarwinFixture, Darwin_minor_update1){

	Darwin x(8,8);

	Species food('f');

	Creature c0(&food);

	x.addCreature(&c0, 0, 0, (int)Direction::south);

    x.minor_update(&c0, (int)Direction::south, (int)Instr::hop, 0, 0);

    ASSERT_EQ(x.map[1][0], &c0);


}

TEST(DarwinFixture, Darwin_minor_update2){

	Darwin x(8,8);

	Species food('f');
	Species hopper('h');

	Creature c0(&food);
	Creature c1(&hopper);

	x.addCreature(&c0, 0, 0, (int)Direction::east);
	x.addCreature(&c1, 0, 1, (int)Direction::south);

    x.minor_update(&c0, (int)Direction::east, (int)Instr::infect, 0, 0);

    ASSERT_EQ(x.map[0][1]->_s, c0._s);


}

TEST(DarwinFixture, Darwin_update0){

	Darwin x(8,8);

	Species food('f');

    food.addInstruction("hop");

	Creature c0(&food);

	x.addCreature(&c0, 2, 2, (int)Direction::north);
	x.turn = 1;
    x.update();
    ASSERT_EQ(x.map[1][2], &c0);

}


TEST(DarwinFixture, Darwin_update1){

	Darwin x(8,8);

	Species food('f');
	Species hopper('h');

    food.addInstruction("hop");
    hopper.addInstruction("hop");

	Creature c0(&food);
	Creature c1(&hopper);

	x.addCreature(&c0, 2, 2, (int)Direction::north);
	x.addCreature(&c1, 1, 2, (int)Direction::east);

	x.turn = 1;
    x.update();

    ASSERT_EQ(x.map[1][2], &c0);
    ASSERT_EQ(x.map[1][3], &c1);

}


TEST(DarwinFixture, Darwin_update2){

	Darwin x(8,8);

	Species food('f');
	Species hopper('h');

    food.addInstruction("hop");
    hopper.addInstruction("infect");

	Creature c0(&food);
	Creature c1(&hopper);

	x.addCreature(&c0, 2, 2, (int)Direction::east);
	x.addCreature(&c1, 3, 3, (int)Direction::north);

	x.turn = 1;
    x.update();

    ASSERT_EQ(x.map[2][3], &c0);
    ASSERT_EQ(x.map[2][3]->_s, c1._s);

}

TEST(DarwinFixture, Darwin_update3){

	Darwin x(3,3);

	Species food('f');

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);

	x.addCreature(&c0, 1, 1, (int)Direction::north);

	x.turn = 1;
    x.update();

    ASSERT_EQ(x.map[0][1], &c0);
}
TEST(DarwinFixture, Darwin_update4){

	Darwin x(3,3);

	Species food('f');

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);

	x.addCreature(&c0, 1, 1, (int)Direction::east);

	x.turn = 1;
    x.update();

    ASSERT_EQ(x.map[1][2], &c0);
}
TEST(DarwinFixture, Darwin_update5){

	Darwin x(3,3);

	Species food('f');

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);

	x.addCreature(&c0, 1, 1, (int)Direction::south);

	x.turn = 1;
    x.update();

    ASSERT_EQ(x.map[2][1], &c0);
}
TEST(DarwinFixture, Darwin_update6){

	Darwin x(3,3);

	Species food('f');

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);

	x.addCreature(&c0, 1, 1, (int)Direction::west);

	x.turn = 1;
    x.update();

    ASSERT_EQ(x.map[1][0], &c0);
}
TEST(DarwinFixture, Darwin_update7){

	Darwin x(3,3);

	Species food('f');

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);

	x.addCreature(&c0, 0, 1, (int)Direction::north);

	x.turn = 1;
    x.update();

    ASSERT_EQ(x.map[0][1], &c0);
}
TEST(DarwinFixture, Darwin_update8){

	Darwin x(3,3);

	Species food('f');

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);

	x.addCreature(&c0, 1, 2, (int)Direction::east);

	x.turn = 1;
    x.update();

    ASSERT_EQ(x.map[1][2], &c0);
}
TEST(DarwinFixture, Darwin_update9){

	Darwin x(3,3);

	Species food('f');

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);

	x.addCreature(&c0, 2, 1, (int)Direction::south);

	x.turn = 1;
    x.update();

    ASSERT_EQ(x.map[2][1], &c0);
}
TEST(DarwinFixture, Darwin_update10){

	Darwin x(3,3);

	Species food('f');

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);

	x.addCreature(&c0, 1, 0, (int)Direction::west);

	x.turn = 1;
    x.update();

    ASSERT_EQ(x.map[1][0], &c0);
}

TEST(DarwinFixture, Darwin_update11){

	Darwin x(3,3);

	Species food('f');
	Species hopper('h');
	hopper.addInstruction("left");
	hopper.addInstruction("go 0");

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);
	Creature c1(&hopper);

	x.addCreature(&c0, 1, 1, (int)Direction::north);
	x.addCreature(&c1, 0, 1, (int)Direction::north);

	x.turn = 1;
    x.update();

    ASSERT_TRUE(c0._s == c1._s);
}
TEST(DarwinFixture, Darwin_update12){

	Darwin x(3,3);

	Species food('f');
	Species hopper('h');
	hopper.addInstruction("left");
	hopper.addInstruction("go 0");

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);
	Creature c1(&hopper);

	x.addCreature(&c0, 1, 1, (int)Direction::east);
	x.addCreature(&c1, 1, 2, (int)Direction::east);

	x.turn = 1;
    x.update();

    ASSERT_TRUE(c0._s == c1._s);
}
TEST(DarwinFixture, Darwin_update13){

	Darwin x(3,3);

	Species food('f');
	Species hopper('h');
	hopper.addInstruction("left");
	hopper.addInstruction("go 0");

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);
	Creature c1(&hopper);

	x.addCreature(&c0, 1, 1, (int)Direction::south);
	x.addCreature(&c1, 2, 1, (int)Direction::south);

	x.turn = 1;
    x.update();

    ASSERT_TRUE(c0._s == c1._s);
}
TEST(DarwinFixture, Darwin_update14){

	Darwin x(3,3);

	Species food('f');
	Species hopper('h');
	hopper.addInstruction("left");
	hopper.addInstruction("go 0");

	food.addInstruction("if_empty 3");
	food.addInstruction("if_wall 4");
	food.addInstruction("if_enemy 5");
	food.addInstruction("hop");
	food.addInstruction("left");
    food.addInstruction("infect");
	food.addInstruction("go 0");

	Creature c0(&food);
	Creature c1(&hopper);

	x.addCreature(&c0, 1, 1, (int)Direction::west);
	x.addCreature(&c1, 1, 0, (int)Direction::west);

	x.turn = 1;
    x.update();

    ASSERT_TRUE(c0._s == c1._s);
}
TEST(DarwinFixture, Darwin_update15){

	Darwin x(3,3);

	Species hopper('h');
	hopper.addInstruction("if_enemy 2");
	hopper.addInstruction("left");
	hopper.addInstruction("infect");
	hopper.addInstruction("go 0");

	Creature c0(&hopper);
	Creature c1(&hopper);

	x.addCreature(&c0, 1, 1, (int)Direction::north);
	x.addCreature(&c1, 0, 1, (int)Direction::north);

	x.turn = 1;
    x.update();

    ASSERT_TRUE(c0._s == c1._s);
}
TEST(DarwinFixture, Darwin_update16){

	Darwin x(3,3);

	Species hopper('h');
	hopper.addInstruction("if_enemy 2");
	hopper.addInstruction("left");
	hopper.addInstruction("infect");
	hopper.addInstruction("go 0");

	Creature c0(&hopper);
	Creature c1(&hopper);

	x.addCreature(&c0, 1, 1, (int)Direction::east);
	x.addCreature(&c1, 1, 2, (int)Direction::east);

	x.turn = 1;
    x.update();

    ASSERT_TRUE(c0._s == c1._s);
}
TEST(DarwinFixture, Darwin_update17){

	Darwin x(3,3);

	Species hopper('h');
	hopper.addInstruction("if_enemy 2");
	hopper.addInstruction("left");
	hopper.addInstruction("infect");
	hopper.addInstruction("go 0");

	Creature c0(&hopper);
	Creature c1(&hopper);

	x.addCreature(&c0, 1, 1, (int)Direction::south);
	x.addCreature(&c1, 2, 1, (int)Direction::south);

	x.turn = 1;
    x.update();

    ASSERT_TRUE(c0._s == c1._s);
}
TEST(DarwinFixture, Darwin_update18){

	Darwin x(3,3);

	Species hopper('h');
	hopper.addInstruction("if_enemy 2");
	hopper.addInstruction("left");
	hopper.addInstruction("infect");
	hopper.addInstruction("go 0");

	Creature c0(&hopper);
	Creature c1(&hopper);

	x.addCreature(&c0, 1, 1, (int)Direction::west);
	x.addCreature(&c1, 1, 0, (int)Direction::west);

	x.turn = 1;
    x.update();

    ASSERT_TRUE(c0._s == c1._s);
}