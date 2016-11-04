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

TEST(InstructionFixture, constructor_1) 
{
    Instruction in(HOP);
    ASSERT_EQ(in.command,0);
    ASSERT_EQ(in.target,0);
}

TEST(InstructionFixture, constructor_2)
{
	Instruction in(IF_EMPTY, 8);
	ASSERT_EQ(in.command,4);
	ASSERT_EQ(in.target,8);
}

TEST(InstructionFixture, is_control_1)
{
	Instruction in(HOP);
	bool b = in.is_control();
	ASSERT_FALSE(b);
}

TEST(InstructionFixture, is_control_2)
{
	Instruction in(GO,0);
	bool b = in.is_control();
	ASSERT_TRUE(b);
}

TEST(InstructionFixture, is_action_1)
{
	Instruction in(HOP);
	bool b = in.is_action();
	ASSERT_TRUE(b);
}

TEST(InstructionFixture, is_action_2)
{
	Instruction in(GO,0);
	bool b = in.is_action();
	ASSERT_FALSE(b);
}

TEST(SpeciesFixture, constructor)
{
	Species food('f');
	ASSERT_EQ(food.symbol,'f');
}

TEST(SpeciesFixture, equals_1)
{
	Species food1('f');
	Species food2('f');
	bool b = food1 == food2;
	ASSERT_TRUE(b);
}

TEST(SpeciesFixture, equals_2)
{
	Species food('f');
	Species hopper('h');
	bool b = food == hopper;
	ASSERT_FALSE(b);
}

TEST(SpeciesFixture, not_equals_1)
{
	Species food1('f');
	Species food2('f');
	bool b = food1 != food2;
	ASSERT_FALSE(b);
}

TEST(SpeciesFixture, not_equals_2)
{
	Species food('f');
	Species hopper('h');
	bool b = food != hopper;
	ASSERT_TRUE(b);
}

TEST(SpeciesFixture, add_instruction_1)
{
	Species food('f');
	food.add_instruction(LEFT);             //0
    food.add_instruction(GO,0);             //1
    ASSERT_EQ(food.size(),2);
}

TEST(SpeciesFixture, line_1)
{
	Species food('f');
	food.add_instruction(LEFT);             //0
    food.add_instruction(GO,0);             //1

    Instruction in = food.line(0);
    ASSERT_EQ(in.command, 1);
}

TEST(SpeciesFixture, line_2)
{
	Species food('f');
	Instruction in1(GO,0);
	food.add_instruction(in1);             //0
    Instruction in = food.line(0);
    ASSERT_EQ(in.command, 8);
}

TEST(SpeciesFixture, size_1)
{
	Species food('f');
	food.add_instruction(LEFT);             //0
    food.add_instruction(GO,0);             //1
    food.add_instruction(LEFT);             //0
    food.add_instruction(GO,0);             //1
    food.add_instruction(LEFT);             //0
    food.add_instruction(GO,0);             //1
    ASSERT_EQ(food.size(),6);
}

TEST(CreatureFixture, constructor)
{
	Species s('f');
	Creature c(s);
	ostringstream w;
	c.print_symbol(w);
	ASSERT_EQ("f",w.str());
}

TEST(CreatureFixture, morph_1)
{
	Species food('f');
	Species hopper('h');
	Creature c1(food);
	Creature c2(hopper);
	c1.morph(c2);
	bool b = c1.species == c2.species;
	ASSERT_TRUE(b);
}

TEST(CreatureFixture, morph_2)
{
	Species food('f');
	Species hopper('h');
	Creature c1(food);
	Creature c2(hopper);
	food.add_instruction(LEFT);             //0
    food.add_instruction(GO,0);             //1
    hopper.add_instruction(HOP);            //0
    hopper.add_instruction(GO, 0);          //1
	c1.morph(c2);
	bool b = c1.species.size() == c2.species.size();
	ASSERT_TRUE(b);
}

TEST(CreatureFixture, morph_3)
{
	Species food('f');
	Species hopper('h');
	Creature c1(food);
	Creature c2(hopper);
	food.add_instruction(LEFT);             //0
    food.add_instruction(GO,0);             //1
    hopper.add_instruction(HOP);            //0
    hopper.add_instruction(GO, 0);          //1
	c1.morph(c2);
	ASSERT_EQ(c1.counter, 0);
}

TEST(CreatureFixture, ask)
{
	Species s('f');
	s.add_instruction(LEFT);             //0
    s.add_instruction(GO,0);             //1
    Creature c(s);
    Instruction in = c.ask();
    ASSERT_EQ(in.command, LEFT);
}

TEST(CreatureFixture, tell_1)
{
	Species s('f');
    s.add_instruction(IF_WALL, 4);             //1
    s.add_instruction(LEFT);             //0
    s.add_instruction(LEFT);             //0
    s.add_instruction(LEFT);             //0
    s.add_instruction(LEFT);             //0
    Creature c(s);
    Instruction in = c.ask();
    //ASSERT_EQ(in.target, 4);
    c.tell(in,true);
    ASSERT_EQ(c.counter,4);
}

TEST(CreatureFixture, tell_2)
{
	Species s('f');
    s.add_instruction(IF_WALL, 4);             //1
    Creature c(s);
    Instruction in = c.ask();
    c.tell(in,true);
    ASSERT_EQ(c.counter,0);
}

TEST(CreatureFixture, tell_3)
{
	Species s('f');
    s.add_instruction(HOP);             //1
    s.add_instruction(IF_WALL, 4);  
    Creature c(s);
    Instruction in = c.ask();
    c.tell(in,false);
    ASSERT_EQ(c.counter,1);
}

TEST(DarwinTexture, constructor_1)
{
	Darwin x;
	ASSERT_EQ(x.height, 10);
	ASSERT_EQ(x.width,  10);
}

TEST(DarwinTexture, constructor_2)
{
	Darwin x(8,8);
	ASSERT_EQ(x.height, 8);
	ASSERT_EQ(x.width,  8);
}

TEST(DarwinTexture, WorldData_1)
{
	Darwin x(1,1);
	ASSERT_EQ(x.world[0][0].direction,0);
	ASSERT_FALSE(x.world[0][0].occupied);
	ASSERT_FALSE(x.world[0][0].turn);
}

TEST(DarwinTexture, add_creature_1)
{
	Darwin x(10,10);
	Species s('s');
	Creature c(s);
	x.add_creature(c, EAST, 0,0);
	ASSERT_EQ(x.world[0][0].direction, EAST);
	ASSERT_TRUE(x.world[0][0].occupied);
}

TEST(DarwinTexture,print_world_1)
{
	Darwin x(2,2);
	Species s('s');
	Creature c1(s);
	Creature c2(s);
	x.add_creature(c1,NORTH,0,0);
	x.add_creature(c2,SOUTH,1,1);
	ostringstream w;
	x.print_world(0,w);
	ASSERT_EQ("Turn = 0.\n  01\n0 s.\n1 .s\n",w.str());

}
TEST(DarwinTexture,run_1)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(HOP);
	s.add_instruction(GO,0);
	Creature c1(s);
	Creature c2(s);
	x.add_creature(c1,NORTH,1,0);
	x.add_creature(c2,NORTH,1,1);
	ostringstream w;
	x.run(1,1,w);
	ASSERT_EQ("Turn = 0.\n  01\n0 ..\n1 ss\n\nTurn = 1.\n  01\n0 ss\n1 ..\n\n",w.str());
}
TEST(DarwinTexture,run_prime_1)
{
	Darwin x(4,4);
	Species s('s');
	s.add_instruction(HOP);
	s.add_instruction(GO,0);
	Creature c1(s);
	Creature c2(s);
	x.add_creature(c1,NORTH,3,0);
	x.add_creature(c2,NORTH,3,3);
	ostringstream w;
	x.run_prime(4,2,1,w);
	ASSERT_EQ("Turn = 0.\n  0123\n0 ....\n1 ....\n2 ....\n3 s..s\n\nTurn = 1.\n  0123\n0 ....\n1 ....\n2 s..s\n3 ....\n\nTurn = 2.\n  0123\n0 s..s\n1 ....\n2 ....\n3 ....\n\nTurn = 4.\n  0123\n0 s..s\n1 ....\n2 ....\n3 ....\n\n",w.str());
}
TEST(DarwinTexture, if_empty_1)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(IF_EMPTY,1);		//0
	s.add_instruction(HOP);				//1
	s.add_instruction(GO,0);			//3
	Creature c(s);
	x.add_creature(c,NORTH,1,1);
	x.turn();
	ASSERT_TRUE(x.world[0][1].occupied);
	ASSERT_FALSE(x.world[1][1].occupied);
}
TEST(DarwinTexture, if_empty_2)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(IF_EMPTY,1);		//0
	s.add_instruction(HOP);				//1
	s.add_instruction(GO,0);			//3
	Creature c(s);
	x.add_creature(c,SOUTH,0,0);
	x.turn();
	ASSERT_TRUE(x.world[1][0].occupied);
}
TEST(DarwinTexture, if_empty_3)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(IF_EMPTY,1);		//0
	s.add_instruction(HOP);				//1
	s.add_instruction(GO,0);			//3
	Creature c(s);
	x.add_creature(c,EAST,0,0);
	x.turn();
	ASSERT_TRUE(x.world[0][1].occupied);
}
TEST(DarwinTexture, if_empty_4)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(IF_EMPTY,1);		//0
	s.add_instruction(HOP);				//1
	s.add_instruction(GO,0);			//3
	Creature c(s);
	x.add_creature(c,WEST,1,1);
	x.turn();
	ASSERT_TRUE(x.world[1][0].occupied);
}
TEST(DarwinTexture, if_wall_1)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(IF_WALL,1);		//0
	s.add_instruction(LEFT);			//1
	s.add_instruction(GO,0);			//3
	Creature c(s);
	x.add_creature(c,NORTH,0,1);
	x.turn();
	ASSERT_EQ(x.world[0][1].direction,WEST);
}
TEST(DarwinTexture, if_wall_2)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(IF_WALL,1);		//0
	s.add_instruction(LEFT);			//1
	s.add_instruction(GO,0);			//3
	Creature c(s);
	x.add_creature(c,SOUTH,1,1);
	x.turn();
	ASSERT_EQ(x.world[1][1].direction,EAST);
}
TEST(DarwinTexture, if_wall_3)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(IF_WALL,1);		//0
	s.add_instruction(LEFT);			//1
	s.add_instruction(GO,0);			//3
	Creature c(s);
	x.add_creature(c,EAST,0,1);
	x.turn();
	ASSERT_EQ(x.world[0][1].direction,NORTH);
}
TEST(DarwinTexture, if_wall_4)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(IF_WALL,1);		//0
	s.add_instruction(LEFT);			//1
	s.add_instruction(GO,0);			//3
	Creature c(s);
	x.add_creature(c,WEST,1,1);
	x.turn();
	ASSERT_EQ(x.world[1][1].direction,SOUTH);
}
TEST(DarwinTexture,if_enemy_1)
{
	Darwin x(2,2);
	Species s('s');
	Species t('t');
	s.add_instruction(IF_ENEMY,1);		//0
	s.add_instruction(LEFT);			//1
	s.add_instruction(GO,0);			//3
	t.add_instruction(LEFT);
	t.add_instruction(GO,0);
	Creature c2(s);
	Creature c1(t);
	x.add_creature(c1,NORTH,0,1);
	x.add_creature(c2,NORTH,1,1);
	x.turn();
	ASSERT_EQ(x.world[1][1].direction,WEST);
}
TEST(DarwinTexture,if_enemy_2)
{
	Darwin x(2,2);
	Species s('s');
	Species t('t');
	s.add_instruction(IF_ENEMY,1);		//0
	s.add_instruction(LEFT);			//1
	s.add_instruction(GO,0);			//3
	t.add_instruction(LEFT);
	t.add_instruction(GO,0);
	Creature c2(s);
	Creature c1(t);
	x.add_creature(c1,NORTH,0,0);
	x.add_creature(c2,WEST,0,1);
	x.turn();
	ASSERT_EQ(x.world[0][1].direction,SOUTH);
}
TEST(DarwinTexture,if_enemy_3)
{
	Darwin x(2,2);
	Species s('s');
	Species t('t');
	s.add_instruction(IF_ENEMY,1);		//0
	s.add_instruction(LEFT);			//1
	s.add_instruction(GO,0);			//3
	t.add_instruction(LEFT);
	t.add_instruction(GO,0);
	Creature c2(s);
	Creature c1(t);
	x.add_creature(c1,NORTH,1,0);
	x.add_creature(c2,SOUTH,0,0);
	x.turn();
	ASSERT_EQ(x.world[0][0].direction,EAST);
}
TEST(DarwinTexture,if_enemy_4)
{
	Darwin x(2,2);
	Species s('s');
	Species t('t');
	s.add_instruction(IF_ENEMY,1);		//0
	s.add_instruction(LEFT);			//1
	s.add_instruction(GO,0);			//3
	t.add_instruction(LEFT);
	t.add_instruction(GO,0);
	Creature c2(s);
	Creature c1(t);
	x.add_creature(c1,NORTH,0,1);
	x.add_creature(c2,EAST,0,0);
	x.turn();
	ASSERT_EQ(x.world[0][0].direction,NORTH);
}
TEST(DarwinTexture,go)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(GO,1);
	s.add_instruction(RIGHT);
	s.add_instruction(GO,0);
	Creature c(s);
	x.add_creature(c,NORTH,0,0);
	x.turn();
	ASSERT_EQ(x.world[0][0].direction,EAST);
}
TEST(DarwinTexture,hop_1)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(HOP);
	s.add_instruction(GO,0);
	Creature c(s);
	x.add_creature(c,SOUTH,0,0);
	x.turn();
	ASSERT_TRUE(x.world[1][0].occupied);
}
TEST(DarwinTexture,hop_2)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(HOP);
	s.add_instruction(GO,0);
	Creature c(s);
	x.add_creature(c,EAST,0,0);
	x.turn();
	ASSERT_TRUE(x.world[0][1].occupied);
}
TEST(DarwinTexture,hop_3)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(HOP);
	s.add_instruction(GO,0);
	Creature c(s);
	x.add_creature(c,NORTH,1,1);
	x.turn();
	ASSERT_TRUE(x.world[0][1].occupied);
}
TEST(DarwinTexture,hop_4)
{
	Darwin x(2,2);
	Species s('s');
	s.add_instruction(HOP);
	s.add_instruction(GO,0);
	Creature c(s);
	x.add_creature(c,WEST,1,1);
	x.turn();
	ASSERT_TRUE(x.world[1][0].occupied);
}
TEST(DarwinTexture,infect_1)
{
	Darwin x(2,2);
	Species s('s');
	Species t('t');
	s.add_instruction(IF_ENEMY,1);		//0
	s.add_instruction(INFECT);			//1
	s.add_instruction(GO,0);			//3
	t.add_instruction(LEFT);
	t.add_instruction(GO,0);
	Creature c2(s);
	Creature c1(t);
	x.add_creature(c1,NORTH,0,1);
	x.add_creature(c2,NORTH,1,1);
	x.turn();
	ASSERT_TRUE(x.world[1][1].creature.species == x.world[0][1].creature.species);
	ASSERT_EQ(x.world[0][1].creature.counter,0);
}
TEST(DarwinTexture,infect_2)
{
	Darwin x(2,2);
	Species s('s');
	Species t('t');
	s.add_instruction(IF_ENEMY,1);		//0
	s.add_instruction(INFECT);			//1
	s.add_instruction(GO,0);			//3
	t.add_instruction(LEFT);
	t.add_instruction(GO,0);
	Creature c2(s);
	Creature c1(t);
	x.add_creature(c1,NORTH,1,0);
	x.add_creature(c2,WEST,1,1);
	x.turn();
	ASSERT_TRUE(x.world[1][1].creature.species == x.world[1][0].creature.species);
	ASSERT_EQ(x.world[1][0].creature.counter,0);
}
TEST(DarwinTexture,infect_3)
{
	Darwin x(2,2);
	Species s('s');
	Species t('t');
	s.add_instruction(IF_ENEMY,1);		//0
	s.add_instruction(INFECT);			//1
	s.add_instruction(GO,0);			//3
	t.add_instruction(LEFT);
	t.add_instruction(GO,0);
	Creature c2(s);
	Creature c1(t);
	x.add_creature(c1,NORTH,1,0);
	x.add_creature(c2,SOUTH,0,0);
	x.turn();
	ASSERT_TRUE(x.world[1][0].creature.species == x.world[0][0].creature.species);
	//ASSERT_EQ(x.world[1][0].creature.counter,0);
}
TEST(DarwinTexture,infect_4)
{
	Darwin x(2,2);
	Species s('s');
	Species t('t');
	s.add_instruction(IF_ENEMY,1);		//0
	s.add_instruction(INFECT);			//1
	s.add_instruction(GO,0);			//3
	t.add_instruction(LEFT);
	t.add_instruction(GO,0);
	Creature c2(s);
	Creature c1(t);
	x.add_creature(c1,NORTH,1,1);
	x.add_creature(c2,EAST,1,0);
	x.turn();
	ASSERT_TRUE(x.world[1][1].creature.species == x.world[1][0].creature.species);
	//ASSERT_EQ(x.world[1][1].creature.counter,0);
}



























