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
#include <sstream>

#include "Darwin.h"

using namespace std;

// ------------------------
// Species::add_instruction
// ------------------------

// action instruction, should default to -1 for second value in pair.
TEST(SpeciesFixture, add_instruction_1)
{
	Species s('T');
	s.add_instruction(Instruction::Hop);
	ASSERT_TRUE(s._program[0].first == Instruction::Hop && s._program[0].second == -1);
}

// if instruction, jmp to line 5
TEST(SpeciesFixture, add_instruction_2)
{
	Species s('T');
	s.add_instruction(Instruction::Empty, 5);
	ASSERT_TRUE(s._program[0].first == Instruction::Empty && s._program[0].second == 5);
}

// go instruction, jmp to 4
TEST(SpeciesFixture, add_instruction_3)
{
	Species s('T');
	s.add_instruction(Instruction::Go, 4);
	ASSERT_TRUE(s._program[0].first == Instruction::Go && s._program[0].second == 4);
}

// check that multiple lines is correct
TEST(SpeciesFixture, add_instruction_4)
{
	Species s('T');
	s.add_instruction(Instruction::Enemy, 3);
	s.add_instruction(Instruction::Left);
	s.add_instruction(Instruction::Go, 0);
	s.add_instruction(Instruction::Infect);
	s.add_instruction(Instruction::Go, 0);
	ASSERT_TRUE(s._program[0].first == Instruction::Enemy  && s._program[0].second == 3);
	ASSERT_TRUE(s._program[1].first == Instruction::Left   && s._program[1].second == -1);
	ASSERT_TRUE(s._program[2].first == Instruction::Go     && s._program[2].second == 0);
	ASSERT_TRUE(s._program[3].first == Instruction::Infect && s._program[3].second == -1);
	ASSERT_TRUE(s._program[4].first == Instruction::Go     && s._program[4].second == 0);
}

// --------------------------
// Species::execute_program()
// --------------------------

// tests left, if enemy, go.
TEST(SpeciesFixture, test_execute_1)
{
	Species X('X');
	Creature x(&X);
	// trap
	X.add_instruction(Instruction::Enemy, 3);
	X.add_instruction(Instruction::Left);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Infect);
	X.add_instruction(Instruction::Go, 0);

	Darwin::Tile cur, front;
	cur.creature = &x;
	Darwin::State s(cur, front);

	int pc = 0;

	// Left: Direction is now West, pc = 2
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::West);
	ASSERT_EQ(pc, 2);

	// Left: Direction is now South, pc = 2
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::South);
	ASSERT_EQ(pc, 2);

	// Left: Direction is now East, pc = 2
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::East);
	ASSERT_EQ(pc, 2);

	// Left: Direction is now North, pc = 2
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::North);
	ASSERT_EQ(pc, 2);
}

// tests right, if enemy, infect, go.
TEST(SpeciesFixture, test_execute_2)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);
	// modified trap
	X.add_instruction(Instruction::Enemy, 3);
	X.add_instruction(Instruction::Right);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Infect);
	X.add_instruction(Instruction::Right);
	X.add_instruction(Instruction::Go, 0);

	Darwin::Tile cur, front;
	cur.creature = &x;
	front.creature = &y;
	Darwin::State s(cur, front);

	int pc = 0;

	// Infect: Direction is same, y is now species X, pc = 4
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::North);
	ASSERT_EQ(front.creature, &y);
	ASSERT_EQ(4, pc);
	ASSERT_FALSE(x.is_enemy(y));

	// Right: Direction is now East, pc = 5
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::East);
	ASSERT_EQ(5, pc);

	// Right: Direction is now South, pc = 2
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::South);
	ASSERT_EQ(2, pc);

	// Right: Direction is now West, pc = 2
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::West);
	ASSERT_EQ(2, pc);

	// Right: Direction is now North, pc = 2
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::North);
	ASSERT_EQ(2, pc);
}

// tests hop, left, if empty, go.
TEST(SpeciesFixture, test_execute_3)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);

	// If empty, hop. Else, turn left.
	X.add_instruction(Instruction::Empty, 3);
	X.add_instruction(Instruction::Left);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Hop);
	X.add_instruction(Instruction::Go, 0);

	Darwin::Tile cur, front;
	cur.creature = &x;
	front.creature = &y;
	Darwin::State s(cur, front);

	int pc = 0;

	// Left: Direction is now West, pc = 2
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::West);
	ASSERT_EQ(front.creature, &y);
	ASSERT_EQ(2, pc);
	ASSERT_TRUE(x.is_enemy(y));

	// front is now wall
	front.creature = nullptr;
	front.wall = true;

	// Left: Direction is now South, pc = 2
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::South);
	ASSERT_EQ(2, pc);

	// front is now empty
	front.wall = false;

	// Hop: cur is now empty, x is now in front, direction is the same, pc = 4
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, nullptr);
	ASSERT_EQ(front.creature, &x);
	ASSERT_EQ(front.dir, Direction::South);
	ASSERT_EQ(4, pc);
}

// tests left, right, hop, if wall, if random, go.
TEST(SpeciesFixture, test_execute_4)
{
	srand(0);
	Species X('X');
	Creature x(&X);

	// If empty, hop. Else, turn left.
	X.add_instruction(Instruction::Wall, 3);
	X.add_instruction(Instruction::Hop);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Random, 6);
	X.add_instruction(Instruction::Left);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Right);
	X.add_instruction(Instruction::Go, 0);

	Darwin::Tile cur, front;
	cur.creature = &x;
	front.wall = true;
	Darwin::State s(cur, front);

	int pc = 0;

	// Right: Direction is now East, pc = 7
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::East);
	ASSERT_EQ(7, pc);

	// Left: Direction is now North, pc = 5
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::North);
	ASSERT_EQ(5, pc);

	// front is now empty
	front.wall = false;

	// Hop: cur is now empty, x is now in front, direction is the same, pc = 2
	pc = X.execute_program(pc, s);
	ASSERT_EQ(cur.creature, nullptr);
	ASSERT_EQ(front.creature, &x);
	ASSERT_EQ(front.dir, Direction::North);
	ASSERT_EQ(2, pc);
}

// ------------------------
// Creature::do_next_action
// ------------------------

// mirrors Species::execute_program, but also checks
// that _pc is correct in creature.

// tests left, if enemy, go.
TEST(CreatureFixture, test_action_1)
{
	Species X('X');
	Creature x(&X);
	// trap
	X.add_instruction(Instruction::Enemy, 3);
	X.add_instruction(Instruction::Left);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Infect);
	X.add_instruction(Instruction::Go, 0);

	Darwin::Tile cur, front;
	cur.creature = &x;
	Darwin::State s(cur, front);

	// Left: Direction is now West, pc = 2
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::West);
	ASSERT_EQ(x._pc, 2);

	// Left: Direction is now South, pc = 2
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::South);
	ASSERT_EQ(x._pc, 2);

	// Left: Direction is now East, pc = 2
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::East);
	ASSERT_EQ(x._pc, 2);

	// Left: Direction is now North, pc = 2
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::North);
	ASSERT_EQ(x._pc, 2);
}

// tests right, if enemy, infect, go.
TEST(CreatureFixture, test_action_2)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);
	// modified trap
	X.add_instruction(Instruction::Enemy, 3);
	X.add_instruction(Instruction::Right);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Infect);
	X.add_instruction(Instruction::Right);
	X.add_instruction(Instruction::Go, 0);

	Darwin::Tile cur, front;
	cur.creature = &x;
	front.creature = &y;
	Darwin::State s(cur, front);

	// Infect: Direction is same, y is now species X, pc = 4
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::North);
	ASSERT_EQ(front.creature, &y);
	ASSERT_EQ(4, x._pc);
	ASSERT_FALSE(x.is_enemy(y));

	// Right: Direction is now East, pc = 5
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::East);
	ASSERT_EQ(5, x._pc);

	// Right: Direction is now South, pc = 2
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::South);
	ASSERT_EQ(2, x._pc);

	// Right: Direction is now West, pc = 2
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::West);
	ASSERT_EQ(2, x._pc);

	// Right: Direction is now North, pc = 2
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::North);
	ASSERT_EQ(2, x._pc);
}

// tests hop, left, if empty, go.
TEST(CreatureFixture, test_action_3)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);

	// If empty, hop. Else, turn left.
	X.add_instruction(Instruction::Empty, 3);
	X.add_instruction(Instruction::Left);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Hop);
	X.add_instruction(Instruction::Go, 0);

	Darwin::Tile cur, front;
	cur.creature = &x;
	front.creature = &y;
	Darwin::State s(cur, front);

	// Left: Direction is now West, pc = 2
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::West);
	ASSERT_EQ(front.creature, &y);
	ASSERT_EQ(2, x._pc);
	ASSERT_TRUE(x.is_enemy(y));

	// front is now wall
	front.creature = nullptr;
	front.wall = true;

	// Left: Direction is now South, pc = 2
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::South);
	ASSERT_EQ(2, x._pc);

	// front is now empty
	front.wall = false;

	// Hop: cur is now empty, x is now in front, direction is the same, pc = 4
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, nullptr);
	ASSERT_EQ(front.creature, &x);
	ASSERT_EQ(front.dir, Direction::South);
	ASSERT_EQ(4, x._pc);
}

// tests left, right, hop, if wall, if random, go.
TEST(CreatureFixture, test_action_4)
{
	srand(0);
	Species X('X');
	Creature x(&X);

	// If empty, hop. Else, turn left.
	X.add_instruction(Instruction::Wall, 3);
	X.add_instruction(Instruction::Hop);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Random, 6);
	X.add_instruction(Instruction::Left);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Right);
	X.add_instruction(Instruction::Go, 0);

	Darwin::Tile cur, front;
	cur.creature = &x;
	front.wall = true;
	Darwin::State s(cur, front);

	// Right: Direction is now East, pc = 7
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::East);
	ASSERT_EQ(7, x._pc);

	// Left: Direction is now North, pc = 5
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, &x);
	ASSERT_EQ(cur.dir, Direction::North);
	ASSERT_EQ(5, x._pc);

	// front is now empty
	front.wall = false;

	// Hop: cur is now empty, x is now in front, direction is the same, pc = 2
	x.do_next_action(s);
	ASSERT_EQ(cur.creature, nullptr);
	ASSERT_EQ(front.creature, &x);
	ASSERT_EQ(front.dir, Direction::North);
	ASSERT_EQ(2, x._pc);
}

// ----------------
// Creature::infect
// ----------------

// simple infection
TEST(CreatureFixture, test_infect_1)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);

	x.infect(y);
	ASSERT_EQ(x._s, y._s);
	ASSERT_EQ(0, y._pc);
}

// x is infected AFTER infecting y
TEST(CreatureFixture, test_infect_2)
{
	Species X('X');
	Species Y('Y');
	Species Z('Z');
	Creature x(&X);
	Creature y(&Y);
	Creature z(&Z);

	x.infect(y);
	ASSERT_EQ(x._s, y._s);
	ASSERT_NE(x._s, z._s);
	ASSERT_NE(y._s, z._s);

	z.infect(x);
	ASSERT_NE(x._s, y._s);
	ASSERT_EQ(x._s, z._s);
	ASSERT_NE(y._s, z._s);
}

// z infects y after x infects y
TEST(CreatureFixture, test_infect_3)
{
	Species X('X');
	Species Y('Y');
	Species Z('Z');
	Creature x(&X);
	Creature y(&Y);
	Creature z(&Z);

	x.infect(y);
	ASSERT_EQ(x._s, y._s);
	ASSERT_NE(x._s, z._s);
	ASSERT_NE(y._s, z._s);

	z.infect(y);
	ASSERT_NE(x._s, y._s);
	ASSERT_NE(x._s, z._s);
	ASSERT_EQ(y._s, z._s);
}

// ------------------
// Creature::is_enemy
// ------------------

// Creatures are different species
TEST(CreatureFixture, test_enemy_1)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);

	ASSERT_TRUE(x.is_enemy(y));
}

// Creatures are same species
TEST(CreatureFixture, test_enemy_2)
{
	Species X('X');
	Creature x(&X);
	Creature y(&X);

	ASSERT_FALSE(x.is_enemy(y));
}

// x and y are different species, then x infects y
TEST(CreatureFixture, test_enemy_3)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);

	ASSERT_TRUE(x.is_enemy(y));
	x.infect(y);
	ASSERT_FALSE(x.is_enemy(y));
}

// --------------------------
// Darwin::State::evaluate_if
// --------------------------

// if wall, when there is a wall
TEST(StateFixture, evaluate_if_1)
{
	Species s('T');
	Creature c(&s);
	Instruction i = Instruction::Wall;
	Darwin::Tile cur, front;

	cur.creature = &c;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = nullptr;
	front.dir = Direction::North;
	front.wall = true;

	Darwin::State state(cur,front);
	ASSERT_TRUE(state.evaluate_if(i));
}

// if wall, when there is not a wall
TEST(StateFixture, evaluate_if_2)
{
	Species s('T');
	Creature c(&s);
	Instruction i = Instruction::Wall;
	Darwin::Tile cur, front;

	cur.creature = &c;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = nullptr;
	front.dir = Direction::North;
	front.wall = false;

	Darwin::State state(cur,front);
	ASSERT_FALSE(state.evaluate_if(i));
}

// if empty, when it is empty
TEST(StateFixture, evaluate_if_3)
{
	Species s('T');
	Creature c(&s);
	Instruction i = Instruction::Empty;
	Darwin::Tile cur, front;

	cur.creature = &c;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = nullptr;
	front.dir = Direction::North;
	front.wall = false;

	Darwin::State state(cur,front);
	ASSERT_TRUE(state.evaluate_if(i));
}

// if empty, when there is a wall
TEST(StateFixture, evaluate_if_4)
{
	Species s('T');
	Creature c(&s);
	Instruction i = Instruction::Empty;
	Darwin::Tile cur, front;

	cur.creature = &c;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = nullptr;
	front.dir = Direction::North;
	front.wall = true;

	Darwin::State state(cur,front);
	ASSERT_FALSE(state.evaluate_if(i));
}

// if empty, when there is a creature
TEST(StateFixture, evaluate_if_5)
{
	Species s('T');
	Creature c(&s);
	Creature d(&s);
	Instruction i = Instruction::Empty;
	Darwin::Tile cur, front;

	cur.creature = &c;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = &d;
	front.dir = Direction::North;
	front.wall = false;

	Darwin::State state(cur,front);
	ASSERT_FALSE(state.evaluate_if(i));
}

// if enemy, when there is an enemy
TEST(StateFixture, evaluate_if_6)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);
	Instruction i = Instruction::Enemy;
	Darwin::Tile cur, front;

	cur.creature = &x;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = &y;
	front.dir = Direction::North;
	front.wall = false;

	Darwin::State state(cur,front);
	ASSERT_TRUE(state.evaluate_if(i));
}

// if enemy, when there is a creature that is not an enemy
TEST(StateFixture, evaluate_if_7)
{
	Species X('X');
	Creature x(&X);
	Creature y(&X);
	Instruction i = Instruction::Enemy;
	Darwin::Tile cur, front;

	cur.creature = &x;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = &y;
	front.dir = Direction::North;
	front.wall = false;

	Darwin::State state(cur,front);
	ASSERT_FALSE(state.evaluate_if(i));
}

// if enemy, when tile in front is empty
TEST(StateFixture, evaluate_if_8)
{
	Species X('X');
	Creature x(&X);
	Instruction i = Instruction::Enemy;
	Darwin::Tile cur, front;

	cur.creature = &x;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = nullptr;
	front.dir = Direction::North;
	front.wall = false;

	Darwin::State state(cur,front);
	ASSERT_FALSE(state.evaluate_if(i));
}

// if enemy, when tile in front is a wall
TEST(StateFixture, evaluate_if_9)
{
	Species X('X');
	Creature x(&X);
	Instruction i = Instruction::Enemy;
	Darwin::Tile cur, front;

	cur.creature = &x;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = nullptr;
	front.dir = Direction::North;
	front.wall = true;

	Darwin::State state(cur,front);
	ASSERT_FALSE(state.evaluate_if(i));
}

// ------------------------
// Darwin::State::do_action
// ------------------------

// do a hop
TEST(StateFixture, do_action_1)
{
	Species X('X');
	Creature x(&X);
	Instruction i = Instruction::Hop;
	Darwin::Tile cur, front;

	cur.creature = &x;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = nullptr;
	front.dir = Direction::North;
	front.wall = false;

	Darwin::State state(cur, front);
	state.do_action(i);
	ASSERT_EQ(cur.creature, nullptr);
	ASSERT_EQ(cur.dir, front.dir);
	ASSERT_EQ(front.creature, &x);
}

// turn left
TEST(StateFixture, do_action_2)
{
	Species X('X');
	Creature x(&X);
	Instruction i = Instruction::Left;
	Darwin::Tile cur, front;

	cur.creature = &x;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = nullptr;
	front.dir = Direction::North;
	front.wall = false;

	Darwin::State state(cur, front);
	state.do_action(i);
	ASSERT_EQ(cur.dir, Direction::West);
	state.do_action(i);
	ASSERT_EQ(cur.dir, Direction::South);
	state.do_action(i);
	ASSERT_EQ(cur.dir, Direction::East);
	state.do_action(i);
	ASSERT_EQ(cur.dir, Direction::North);
}

// turn right
TEST(StateFixture, do_action_3)
{
	Species X('X');
	Creature x(&X);
	Instruction i = Instruction::Right;
	Darwin::Tile cur, front;

	cur.creature = &x;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = nullptr;
	front.dir = Direction::North;
	front.wall = false;

	Darwin::State state(cur, front);
	state.do_action(i);
	ASSERT_EQ(cur.dir, Direction::East);
	state.do_action(i);
	ASSERT_EQ(cur.dir, Direction::South);
	state.do_action(i);
	ASSERT_EQ(cur.dir, Direction::West);
	state.do_action(i);
	ASSERT_EQ(cur.dir, Direction::North);
}

// infect
TEST(StateFixture, do_action_4)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);
	Instruction i = Instruction::Infect;
	Darwin::Tile cur, front;

	cur.creature = &x;
	cur.dir = Direction::North;
	cur.wall = false;

	front.creature = &y;
	front.dir = Direction::North;
	front.wall = false;

	Darwin::State state(cur, front);
	state.do_action(i);
	ASSERT_FALSE(x.is_enemy(y));
}

// ----------------------
// Darwin::add_creature()
// ----------------------

// add creatures facing in various directions and positions
TEST(DarwinFixture, add_creature_1)
{
	Species  X('X');
	Creature x1(&X);
	Creature x2(&X);
	Creature x3(&X);
	Creature x4(&X);
	Darwin d(3,3);

	d.add_creature(x1, 0,1, Direction::North);
	d.add_creature(x2, 1,0, Direction::West);
	d.add_creature(x3, 1,2, Direction::East);
	d.add_creature(x4, 2,1, Direction::South);

	Darwin::Tile t1 = d._grid[0][1];
	Darwin::Tile t2 = d._grid[1][0];
	Darwin::Tile t3 = d._grid[1][2];
	Darwin::Tile t4 = d._grid[2][1];

	ASSERT_EQ(t1.creature, &x1);
	ASSERT_EQ(t1.dir, Direction::North);
	ASSERT_FALSE(t1.wall);

	ASSERT_EQ(t2.creature, &x2);
	ASSERT_EQ(t2.dir, Direction::West);
	ASSERT_FALSE(t2.wall);

	ASSERT_EQ(t3.creature, &x3);
	ASSERT_EQ(t3.dir, Direction::East);
	ASSERT_FALSE(t3.wall);

	ASSERT_EQ(t4.creature, &x4);
	ASSERT_EQ(t4.dir, Direction::South);
	ASSERT_FALSE(t4.wall);
}

// add creatures of different species at extreme corners (top left, bottom right)
TEST(DarwinFixture, add_creature_2)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);
	Darwin d(3,3);

	d.add_creature(x, 0,0, Direction::East);
	d.add_creature(y, 2,2, Direction::West);

	Darwin::Tile t1 = d._grid[0][0];
	Darwin::Tile t2 = d._grid[2][2];

	ASSERT_EQ(t1.creature, &x);
	ASSERT_EQ(t1.dir, Direction::East);
	ASSERT_FALSE(t1.wall);

	ASSERT_EQ(t2.creature, &y);
	ASSERT_EQ(t2.dir, Direction::West);
	ASSERT_FALSE(t2.wall);
}

// --------------------
// Darwin::execute_turn
// --------------------

// tests that correct tiles are retrieved for a simple
// hop cases
TEST(DarwinFixture, execute_turn_1)
{
	Species X('X');
	Creature w(&X);
	Creature x(&X);
	Creature y(&X);
	Creature z(&X);

	X.add_instruction(Instruction::Hop);
	X.add_instruction(Instruction::Go, 0);

	Darwin d(5,5);

	// should be at 0,1 after execute turn
	d.add_creature(w,1,1,Direction::North);

	// should be at 3,1 after execute turn
	d.add_creature(x,2,1,Direction::South);

	// should be at 4,0 after execute turn
	d.add_creature(y,4,1,Direction::West);

	// should be at 4,4 after execute turn
	d.add_creature(z,4,3,Direction::East);

	d.execute_turn();

	ASSERT_EQ(d._grid[0][1].creature, &w);
	ASSERT_EQ(d._grid[3][1].creature, &x);
	ASSERT_EQ(d._grid[4][0].creature, &y);
	ASSERT_EQ(d._grid[4][4].creature, &z);
}

// tests that walls are correctly determined
TEST(DarwinFixture, execute_turn_2)
{
	Species X('X');
	Creature w(&X);
	Creature x(&X);
	Creature y(&X);
	Creature z(&X);

	X.add_instruction(Instruction::Wall, 3);
	X.add_instruction(Instruction::Hop);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Left);
	X.add_instruction(Instruction::Go, 0);

	Darwin d(4,4);

	//d etects North wall
	d.add_creature(w, 0,1, Direction::North);

	// detects the South wall
	d.add_creature(x, 3,1,Direction::South);

	// detects the West wall
	d.add_creature(y, 1,0, Direction::West);

	// detects the East wall
	d.add_creature(z, 1,3, Direction::East);

	d.execute_turn();

	ASSERT_EQ(d._grid[0][1].creature, &w);
	ASSERT_EQ(d._grid[0][1].dir, Direction::West);

	ASSERT_EQ(d._grid[3][1].creature, &x);
	ASSERT_EQ(d._grid[3][1].dir, Direction::East);

	ASSERT_EQ(d._grid[1][0].creature, &y);
	ASSERT_EQ(d._grid[1][0].dir, Direction::South);

	ASSERT_EQ(d._grid[1][3].creature, &z);
	ASSERT_EQ(d._grid[1][3].dir, Direction::North);
}

// tests that a creature in column j goes before
// a creature in column j+1
TEST(DarwinFixture, execute_turn_3)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);

	X.add_instruction(Instruction::Enemy, 3);
	X.add_instruction(Instruction::Left);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Infect);
	X.add_instruction(Instruction::Go, 0);

	Y.add_instruction(Instruction::Enemy, 3);
	Y.add_instruction(Instruction::Left);
	Y.add_instruction(Instruction::Go, 0);
	Y.add_instruction(Instruction::Infect);
	Y.add_instruction(Instruction::Go, 0);

	Darwin d(3,3);

	// x should infect y before y can infect x
	d.add_creature(x,1,1,Direction::East);
	d.add_creature(y,1,2,Direction::West);

	d.execute_turn();

	// x is in the same direction, since it infected y
	ASSERT_EQ(d._grid[1][1].creature, &x);
	ASSERT_EQ(d._grid[1][1].dir, Direction::East);

	ASSERT_FALSE(x.is_enemy(y));

	// y turned left, since x is no longer an enemy
	ASSERT_EQ(d._grid[1][2].creature, &y);
	ASSERT_EQ(d._grid[1][2].dir, Direction::South);
}

// Test that creature's turns are not done multiple
// times when moving along the grid
TEST(DarwinFixture, execute_turn_4)
{
	Species X('X');
	Creature w(&X);
	Creature x(&X);

	X.add_instruction(Instruction::Hop);
	X.add_instruction(Instruction::Go, 0);

	Darwin d(5,5);

	// should be at 0,2 after execute turn
	d.add_creature(w,0,1,Direction::East);

	// should be at 2,0 after execute turn
	d.add_creature(x,1,0,Direction::South);

	d.execute_turn();

	ASSERT_EQ(d._grid[0][2].creature, &w);
	ASSERT_EQ(d._grid[2][0].creature, &x);
}

// Test that a creature's turn is not skipped
// when it is in front of another creature that
// executes an action.
TEST(DarwinFixture, execute_turn_5)
{
	Species X('X');
	Creature w(&X);
	Creature x(&X);
	Creature y(&X);
	Creature z(&X);

	X.add_instruction(Instruction::Empty, 3);
	X.add_instruction(Instruction::Left);
	X.add_instruction(Instruction::Go, 0);
	X.add_instruction(Instruction::Hop);
	X.add_instruction(Instruction::Go, 0);

	Darwin d(5,5);

	// should be facing North after execute turn
	d.add_creature(w,0,1,Direction::East);

	// should be at 0,3 after execute turn
	d.add_creature(x,0,2,Direction::East);

	// should be facing West after execute turn
	d.add_creature(y,1,0,Direction::South);

	// should be at 3,0 after execute turn
	d.add_creature(z,2,0,Direction::South);

	d.execute_turn();

	ASSERT_EQ(d._grid[0][1].creature, &w);
	ASSERT_EQ(d._grid[0][1].dir, Direction::North);
	ASSERT_EQ(d._grid[0][3].creature, &x);
	ASSERT_EQ(d._grid[0][3].dir, Direction::East);
	ASSERT_EQ(d._grid[1][0].creature, &y);
	ASSERT_EQ(d._grid[1][0].dir, Direction::East);
	ASSERT_EQ(d._grid[3][0].creature, &z);
	ASSERT_EQ(d._grid[3][0].dir, Direction::South);
}

// ---------------
// print functions
// ---------------

// Species::print_id()
TEST(ProjectPrintFixture, print_species)
{
	Species s('T');
	ostringstream w;
	s.print_id(w);
	ASSERT_EQ("T", w.str());
}

// Creature::print_id()
TEST(ProjectPrintFixture, print_creature_1)
{
	Species s('T');
	Creature c(&s);
	ostringstream w;
	c.print_id(w);
	ASSERT_EQ("T", w.str());
}

// Creature::print_id()
// test when infected
TEST(ProjectPrintFixture, print_creature_2)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);
	ostringstream w;
	x.infect(y);
	x.print_id(w);
	y.print_id(w);
	ASSERT_EQ("XX", w.str());
}

// Darwin::print_grid()
// test with two different species
TEST(ProjectPrintFixture, print_grid_1)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);
	Darwin d(2,2);
	ostringstream w;

	d.add_creature(x,0,1,Direction::North);
	d.add_creature(y,1,0,Direction::South);
	d.print_grid(w);
	ASSERT_EQ("  01\n0 .X\n1 Y.\n", w.str());
}

// Darwin::print_grid()
// make sure infected creature prints the new species character
TEST(ProjectPrintFixture, print_grid_2)
{
	Species X('X');
	Species Y('Y');
	Species Z('Z');
	Creature x(&X);
	Creature y(&Y);
	Creature z1(&Z);	// infected z
	Creature z2(&Z);	// uninfected z
	Darwin d(3,3);
	ostringstream w;

	d.add_creature(x,0,0,  Direction::East);
	d.add_creature(z1,0,1, Direction::West);
	d.add_creature(y,1,1,  Direction::South);
	d.add_creature(z2,2,2, Direction::North);

	x.infect(z1);

	d.print_grid(w);
	ASSERT_EQ("  012\n0 XX.\n1 .Y.\n2 ..Z\n", w.str());
}

// test numbering for grid rows > 10
TEST(ProjectPrintFixture, print_grid_3)
{
	Darwin d(12,1);
	ostringstream w;

	d.print_grid(w);

	ASSERT_EQ("  0\n0 .\n1 .\n2 .\n3 .\n4 .\n5 .\n6 .\n7 .\n8 .\n9 .\n0 .\n1 .\n", w.str());
}

// test numbering for grid columns > 10
TEST(ProjectPrintFixture, print_grid_4)
{
	Darwin d(1,12);
	ostringstream w;

	d.print_grid(w);

	ASSERT_EQ("  012345678901\n0 ............\n", w.str());
}

// ------------
// constructors
// ------------

// Tile constructor
TEST(ConstructorFixture, Tile)
{
	Darwin::Tile t;
	ASSERT_EQ(t.creature, nullptr);
	ASSERT_EQ(t.dir, Direction::North);
	ASSERT_EQ(t.wall, false);
}

// State constructor
TEST(ConstructorFixture, State_1)
{
	Species X('X');
	Species Y('Y');
	Creature x(&X);
	Creature y(&Y);
	Darwin::Tile t1, t2;

	// An impossible configuration, but testing that all values
	// are the same after creating the state.
	t1.creature = &x;
	t2.creature = &y;
	t1.dir = Direction::North;
	t2.dir = Direction::South;
	t2.wall = true;

	Darwin::State s(t1, t2);
	ASSERT_EQ(s._cur.creature, &x);
	ASSERT_EQ(s._front.creature, &y);
	ASSERT_EQ(s._cur.dir, Direction::North);
	ASSERT_EQ(s._front.dir, Direction::South);
	ASSERT_FALSE(s._cur.wall);
	ASSERT_TRUE(s._front.wall);
}

// State constructor
TEST(ConstructorFixture, State_2)
{
	Species X('X');
	Creature x(&X);
	Darwin::Tile t1, t2;

	Darwin::State s(t1, t2);

	s._front.creature = &x;
	s._front.wall = true;
	s._front.dir = Direction::South;

	// check that modifying tiles in state modifies the original tile.
	ASSERT_EQ(t2.creature, &x);
	ASSERT_EQ(t2.dir, Direction::South);
	ASSERT_TRUE(t2.wall);
}

// Darwin constructor
TEST(ConstructorFixture, Darwin_1)
{
	Darwin d(50, 50);
	ASSERT_EQ(d._ni, 50);
	ASSERT_EQ(d._nj, 50);
}

// Darwin constructor
TEST(ConstructorFixture, Darwin_2)
{
	Darwin d(25, 50);
	ASSERT_EQ(d._ni, 25);
	ASSERT_EQ(d._nj, 50);
}

// Darwin constructor
TEST(ConstructorFixture, Darwin_3)
{
	Darwin d(50, 25);
	ASSERT_EQ(d._ni, 50);
	ASSERT_EQ(d._nj, 25);
}

// Species constructor
TEST(ConstructorFixture, Species)
{
	Species s('X');
	ASSERT_EQ(s._id, 'X');
}

// Creature constructor
TEST(ConstructorFixture, Creature)
{
	Species s('X');
	Creature c(&s);
	ASSERT_EQ(&s, c._s);
}
