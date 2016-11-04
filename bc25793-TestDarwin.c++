/**
 * @file TestDarwin.c++
 * @brief Contains unit tests for the Darwin project.
 * @copyright Copyright (C) 2016
 * @author Glenn P. Downing
 * @author Brian Cui, Vladislav Manoylo
 */

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include "gtest/gtest.h"
#include <cstdlib> // rand, srand
#include "Darwin.h"

using namespace std;

// ----
// test
// ----

/** Test basic Instruction constructor, without instruction argument */
TEST(DarwinFixture, InstructionTest1) {
  Instruction instr_left(Instruction::Type::left);
  ASSERT_EQ(Instruction::Type::left, instr_left.type);
}

/** Test Instruction constructor containing instruction argument */
TEST(DarwinFixture, InstructionTest2) {
  Instruction instr_go(Instruction::Type::go, 4);
  ASSERT_EQ(Instruction::Type::go, instr_go.type);
  ASSERT_EQ(4, instr_go.arg);
}

/** Test Instruction constructor with if instructions */
TEST(DarwinFixture, InstructionTest3) {
  Instruction instr_empty(Instruction::Type::if_empty, 3);
  ASSERT_EQ(Instruction::Type::if_empty, instr_empty.type);
  ASSERT_EQ(3, instr_empty.arg);

  Instruction instr_wall(Instruction::Type::if_wall, 4);
  ASSERT_EQ(Instruction::Type::if_wall, instr_wall.type);
  ASSERT_EQ(4, instr_wall.arg);

  Instruction instr_random(Instruction::Type::if_random, 5);
  ASSERT_EQ(Instruction::Type::if_random, instr_random.type);
  ASSERT_EQ(5, instr_random.arg);

  Instruction instr_enemy(Instruction::Type::if_enemy, 6);
  ASSERT_EQ(Instruction::Type::if_enemy, instr_enemy.type);
  ASSERT_EQ(6, instr_enemy.arg);
}

/** Test basic Species constructor */
TEST(DarwinFixture, SpeciesTest1) {
  Species basic('b');
  ASSERT_EQ('b', basic._label);
}

/** Test Species addInstruction method */
TEST(DarwinFixture, SpeciesTest2) {
  Species food('f');
  ASSERT_EQ(0, food._i.size());

  food.addInstruction({Instruction::Type::left});
  food.addInstruction({Instruction::Type::go, 0});
  ASSERT_EQ(2, food._i.size());

  food.addInstruction({Instruction::Type::right});
  ASSERT_EQ(3, food._i.size());
}

/** Test Species << operator (for use with printing) */
TEST(DarwinFixture, SpeciesTest3) {
  Species print('p');
  ostringstream w;
  w << print;
  ASSERT_EQ(print._label, *(w.str().c_str()));
}

/** Test Species nextAction if_empty behavior */
TEST(DarwinFixture, SpeciesTest4) {
  Species empty('e');
  empty.addInstruction({Instruction::Type::if_empty, 3});
  empty.addInstruction({Instruction::Type::right});
  empty.addInstruction({Instruction::Type::go, 0});
  empty.addInstruction({Instruction::Type::left});
  empty.addInstruction({Instruction::Type::go, 0});

  int pc = 0;
  ASSERT_EQ(Instruction::Type::right,
            empty.nextAction(pc, false, false, false).type);
  ASSERT_EQ(Instruction::Type::left,
            empty.nextAction(pc, false, true, false).type);
}

/** Test Species nextAction if_wall behavior */
TEST(DarwinFixture, SpeciesTest5) {
  Species wall('e');
  wall.addInstruction({Instruction::Type::if_wall, 3});
  wall.addInstruction({Instruction::Type::right});
  wall.addInstruction({Instruction::Type::go, 0});
  wall.addInstruction({Instruction::Type::left});
  wall.addInstruction({Instruction::Type::go, 0});

  int pc = 0;
  ASSERT_EQ(Instruction::Type::right,
            wall.nextAction(pc, false, false, false).type);
  ASSERT_EQ(Instruction::Type::left,
            wall.nextAction(pc, true, false, false).type);
}

/** Test Species nextAction if_random behavior */
TEST(DarwinFixture, SpeciesTest6) {
  srand(0);

  /* is the first number generated odd? */
  bool first_odd = (rand() % 2 == 1);
  srand(0);

  Species rand('e');
  rand.addInstruction({Instruction::Type::if_random, 3});
  rand.addInstruction({Instruction::Type::right});
  rand.addInstruction({Instruction::Type::go, 0});
  rand.addInstruction({Instruction::Type::left});
  rand.addInstruction({Instruction::Type::go, 0});

  int pc = 0;
  if (first_odd)
    ASSERT_EQ(Instruction::Type::left,
              rand.nextAction(pc, false, false, false).type);
  else
    ASSERT_EQ(Instruction::Type::right,
              rand.nextAction(pc, false, false, false).type);
}

/** Test Species nextAction if_enemy behavior */
TEST(DarwinFixture, SpeciesTest7) {
  Species enemy('e');
  enemy.addInstruction({Instruction::Type::if_enemy, 3});
  enemy.addInstruction({Instruction::Type::right});
  enemy.addInstruction({Instruction::Type::go, 0});
  enemy.addInstruction({Instruction::Type::left});
  enemy.addInstruction({Instruction::Type::go, 0});

  int pc = 0;
  ASSERT_EQ(Instruction::Type::right,
            enemy.nextAction(pc, false, false, false).type);
  ASSERT_EQ(Instruction::Type::left,
            enemy.nextAction(pc, false, false, true).type);
}

/** Test Species nextAction go behavior */
TEST(DarwinFixture, SpeciesTest8) {
  Species go('g');
  go.addInstruction({Instruction::Type::go, 2});
  go.addInstruction({Instruction::Type::go, 3});
  go.addInstruction({Instruction::Type::go, 1});
  go.addInstruction({Instruction::Type::go, 5});
  go.addInstruction({Instruction::Type::go, 6});
  go.addInstruction({Instruction::Type::go, 4});
  go.addInstruction({Instruction::Type::right});

  int pc = 0;
  ASSERT_EQ(Instruction::Type::right,
            go.nextAction(pc, false, false, false).type);
}

/** Test Species nextAction with combination of actions */
TEST(DarwinFixture, SpeciesTest9) {
  Species go('g');
  go.addInstruction({Instruction::Type::go, 2});
  go.addInstruction({Instruction::Type::if_wall, 3});
  go.addInstruction({Instruction::Type::if_empty, 1});
  go.addInstruction({Instruction::Type::if_enemy, 5});
  go.addInstruction({Instruction::Type::right});
  go.addInstruction({Instruction::Type::left});

  int pc = 0;
  ASSERT_EQ(Instruction::Type::left,
            go.nextAction(pc, false, false, true).type);
}

/** Test Species throws error on invalid program counter
    caused by control flow instruction */
TEST(DarwinFixture, SpeciesTest10) {
  Species gobad('g');
  gobad.addInstruction({Instruction::Type::go, 1});
  int pc = 0;
  ASSERT_ANY_THROW(gobad.nextAction(pc, false, false, false));
}

/** Test basic Creature constructor */
TEST(DarwinFixture, CreatureTest1) {
  Species basic('b');
  Creature bcreature(&basic, Direction::west);
  ASSERT_EQ(&basic, bcreature._s);
  ASSERT_EQ(Direction::west, bcreature._d);
  ASSERT_EQ(0, bcreature._pc);
}

/** Test Creature << operator (should print species) */
TEST(DarwinFixture, CreatureTest2) {
  Species letter('l');
  Creature lcreature(&letter, Direction::south);
  ostringstream w;
  w << lcreature;
  ASSERT_EQ(letter._label, *(w.str().c_str()));
}

/** Test Creature << operator after species changes */
TEST(DarwinFixture, CreatureTest2_1) {
  Species letter('l');
  Species alt('a');
  Creature lcreature(&letter, Direction::south);
  lcreature._s = &alt;

  ostringstream w;
  w << lcreature;
  ASSERT_EQ(alt._label, *(w.str().c_str()));
}

/** Test Creature direction change: start east, turn left */
TEST(DarwinFixture, CreatureTest3) {
  Species food('f');
  food.addInstruction({Instruction::Type::left});
  food.addInstruction({Instruction::Type::go, 0});

  Creature fcreature(&food, Direction::east);
  Creature *cptr = &fcreature;
  Creature **center = &cptr;

  fcreature.update(center, nullptr, nullptr, nullptr, nullptr);
  ASSERT_EQ(Direction::north, fcreature._d);
  fcreature.update(center, nullptr, nullptr, nullptr, nullptr);
  ASSERT_EQ(Direction::west, fcreature._d);
  fcreature.update(center, nullptr, nullptr, nullptr, nullptr);
  ASSERT_EQ(Direction::south, fcreature._d);
  fcreature.update(center, nullptr, nullptr, nullptr, nullptr);
  ASSERT_EQ(Direction::east, fcreature._d);
}

/** Test Creature direction change: start east, turn right */
TEST(DarwinFixture, CreatureTest4) {
  Species food('f');
  food.addInstruction({Instruction::Type::right});
  food.addInstruction({Instruction::Type::go, 0});

  Creature fcreature(&food, Direction::east);
  Creature *cptr = &fcreature;
  Creature **center = &cptr;

  fcreature.update(center, nullptr, nullptr, nullptr, nullptr);
  ASSERT_EQ(Direction::south, fcreature._d);
  fcreature.update(center, nullptr, nullptr, nullptr, nullptr);
  ASSERT_EQ(Direction::west, fcreature._d);
  fcreature.update(center, nullptr, nullptr, nullptr, nullptr);
  ASSERT_EQ(Direction::north, fcreature._d);
  fcreature.update(center, nullptr, nullptr, nullptr, nullptr);
  ASSERT_EQ(Direction::east, fcreature._d);
}

/** Test Creature hop instruction */
TEST(DarwinFixture, CreatureTest5) {
  Species hopper('h');
  hopper.addInstruction({Instruction::Type::hop});
  hopper.addInstruction({Instruction::Type::go, 0});

  Creature hcreature(&hopper, Direction::east);
  Creature block(&hopper, Direction::west);
  Creature *game[3] = {nullptr, &hcreature, nullptr};

  /* Should hop into the east spot (index 2) */
  hcreature.update(&game[1], &game[0], nullptr, &game[2], nullptr);
  ASSERT_EQ(game[2], &hcreature);
  ASSERT_EQ(game[1], nullptr);

  /* Should not hop through wall */
  hcreature.update(&game[2], &game[1], nullptr, nullptr, nullptr);
  ASSERT_EQ(game[2], &hcreature);
  ASSERT_EQ(game[1], nullptr);

  /* Should not hop into another creature */
  game[1] = &hcreature;
  game[2] = &block;
  hcreature.update(&game[1], &game[0], nullptr, &game[2], nullptr);
  ASSERT_EQ(game[0], nullptr);
  ASSERT_EQ(game[1], &hcreature);
  ASSERT_EQ(game[2], &block);
}

/** Test Creature actions only runs once per update */
TEST(DarwinFixture, CreatureTest5_1) {
  Species hopper('h');
  hopper.addInstruction({Instruction::Type::hop});
  hopper.addInstruction({Instruction::Type::hop});
  hopper.addInstruction({Instruction::Type::hop});
  hopper.addInstruction({Instruction::Type::go, 0});

  Creature hcreature(&hopper, Direction::east);
  Creature *game[3] = {&hcreature, nullptr, nullptr};

  hcreature.update(&game[0], nullptr, nullptr, &game[1], nullptr);
  ASSERT_EQ(game[1], &hcreature);
  ASSERT_EQ(1, hcreature._pc);
  hcreature.update(&game[1], &game[0], nullptr, &game[2], nullptr);
  ASSERT_EQ(game[2], &hcreature);
  ASSERT_EQ(2, hcreature._pc);
}

/** Test Creature infect instruction */
TEST(DarwinFixture, CreatureTest6) {
  Species infect('i');
  infect.addInstruction({Instruction::Type::infect});
  infect.addInstruction({Instruction::Type::go, 0});

  Species food('f');
  food.addInstruction({Instruction::Type::left});
  food.addInstruction({Instruction::Type::go, 0});

  Creature icreature(&infect, Direction::east);
  Creature fcreature(&food, Direction::east);
  Creature screature(&infect, Direction::east);
  Creature *game[3] = {&icreature, &fcreature, &screature};

  /* Should infect enemy creature by replacing species, pc */
  fcreature.update(&game[1], &game[0], nullptr, &game[2], nullptr);
  icreature.update(&game[0], nullptr, nullptr, &game[1], nullptr);
  ASSERT_EQ((*game[1])._s, &infect);
  ASSERT_EQ((*game[1])._pc, 0);

  /* Should not affect creature of same species */
  screature.update(&game[2], &game[1], nullptr, nullptr, nullptr);
  fcreature.update(&game[1], &game[0], nullptr, &game[2], nullptr);
  ASSERT_EQ(game[1], &fcreature);
  ASSERT_EQ(game[2], &screature);
}

/** Test Creature infect instruction chained */
TEST(DarwinFixture, CreatureTest6_1) {
  Species infect('i');
  infect.addInstruction({Instruction::Type::infect});
  infect.addInstruction({Instruction::Type::go, 0});

  Species food('f');
  food.addInstruction({Instruction::Type::left});
  food.addInstruction({Instruction::Type::go, 0});

  Creature icreature(&infect, Direction::east);
  Creature fcreature(&food, Direction::east);
  Creature screature(&food, Direction::east);
  Creature *game[3] = {&icreature, &fcreature, &screature};

  /* Infections should chain together */
  icreature.update(&game[0], nullptr, nullptr, &game[1], nullptr);
  fcreature.update(&game[1], &game[0], nullptr, &game[2], nullptr);
  screature.update(&game[2], &game[1], nullptr, nullptr, nullptr);
  ASSERT_EQ((*game[0])._s, &infect);
  ASSERT_EQ((*game[1])._s, &infect);
  ASSERT_EQ((*game[2])._s, &infect);
}

/** Test incorrect parameters passed to Creature update */
TEST(DarwinFixture, CreatureTest7) {
  Species bad('b');
  bad.addInstruction({Instruction::Type::left});
  bad.addInstruction({Instruction::Type::go, 0});
  Creature bcreature(&bad, Direction::east);
  Creature *game[2] = {&bcreature, nullptr};

  ASSERT_ANY_THROW(
      bcreature.update(&game[1], &game[0], nullptr, nullptr, nullptr));
}

/** Test Species throws error on invalid program counter
    caused by incrementing */
TEST(DarwinFixture, CreatureTest8) {
  Species gobad('g');
  gobad.addInstruction({Instruction::Type::left});
  Creature bcreature(&gobad, Direction::east);
  Creature *bptr = &bcreature;
  EXPECT_NO_THROW(bcreature.update(&bptr, nullptr, nullptr, nullptr, nullptr));
  ASSERT_ANY_THROW(bcreature.update(&bptr, nullptr, nullptr, nullptr, nullptr));
}

/** Test Darwin basic constructor */
TEST(DarwinFixture, DarwinTest1) {
  Darwin darwin(5, 10);
  ASSERT_EQ(5, darwin._rows);
  ASSERT_EQ(10, darwin._cols);
  ASSERT_EQ(5 * 10, darwin._world.size());
}

/** Test Darwin basic constructor with large world */
TEST(DarwinFixture, DarwinTest1_1) {
  Darwin darwin(100, 100);
  ASSERT_EQ(100, darwin._rows);
  ASSERT_EQ(100, darwin._cols);
  ASSERT_EQ(100 * 100, darwin._world.size());
}

/** Test Darwin _index helper method */
TEST(DarwinFixture, DarwinTest1_2) {
  Darwin darwin(3, 7);
  ASSERT_EQ(2 * 7 + 4, darwin._index(2, 4));
}

/** Test Darwin _index helper method with 1 row */
TEST(DarwinFixture, DarwinTest1_3) {
  Darwin darwin(1, 100);
  ASSERT_EQ(42, darwin._index(0, 42));
}

/** Test Darwin _index helper method with 1 column */
TEST(DarwinFixture, DarwinTest1_4) {
  Darwin darwin(100, 1);
  ASSERT_EQ(42, darwin._index(42, 0));
}

/** Test Darwin addCreature */
TEST(DarwinFixture, DarwinTest2) {
  Darwin darwin(2, 2);
  Species food('f');
  food.addInstruction({Instruction::Type::left});
  food.addInstruction({Instruction::Type::go, 0});
  Creature f1(&food, Direction::east);
  Creature f2(&food, Direction::east);

  darwin.addCreature(&f1, 0, 0);
  ASSERT_EQ(&f1, darwin._world.at(0));

  /* attempt to add two creatures into the same spot */
  ASSERT_ANY_THROW(darwin.addCreature(&f2, 0, 0));
  /* ensure old creature was not replaced */
  ASSERT_EQ(&f1, darwin._world.at(0));
}

/** Test Darwin addCreature into invalid spot */
TEST(DarwinFixture, DarwinTest2_1) {
  Darwin darwin(2, 2);
  Species food('f');
  Creature f1(&food, Direction::east);

  ASSERT_ANY_THROW(darwin.addCreature(&f1, 9, 9));
  darwin.addCreature(&f1, 0, 0);
  ASSERT_EQ(&f1, darwin._world.at(0));
}

/** Test Darwin simulate with simple world */
TEST(DarwinFixture, DarwinTest3) {
  Darwin darwin(2, 2);
  Species hopper('h');
  hopper.addInstruction({Instruction::Type::hop});
  hopper.addInstruction({Instruction::Type::go, 0});
  Creature h1(&hopper, Direction::east);
  Creature h2(&hopper, Direction::east);

  darwin.addCreature(&h1, 0, 0);
  darwin.addCreature(&h2, 1, 0);
  darwin.simulate();

  ASSERT_EQ(&h1, darwin._world.at(darwin._index(0, 1)));
  ASSERT_EQ(&h2, darwin._world.at(darwin._index(1, 1)));
}

/** Test Darwin simulate with a more complex world */
TEST(DarwinFixture, DarwinTest4) {
  Darwin darwin(2, 2);
  Species hopper('h');
  hopper.addInstruction({Instruction::Type::hop});
  hopper.addInstruction({Instruction::Type::go, 0});
  Creature h1(&hopper, Direction::east);
  Creature h2(&hopper, Direction::north);

  Species trap('t');
  trap.addInstruction({Instruction::Type::infect});
  trap.addInstruction({Instruction::Type::go, 0});
  Creature t1(&trap, Direction::west);

  darwin.addCreature(&h1, 0, 0);
  darwin.addCreature(&t1, 0, 1);
  darwin.addCreature(&h2, 1, 0);
  darwin.simulate();

  /* h1 should get infected, but h2 should not  */
  ASSERT_EQ(&h1, darwin._world.at(darwin._index(0, 0)));
  ASSERT_EQ(h1._s, &trap);
  ASSERT_EQ(&t1, darwin._world.at(darwin._index(0, 1)));
  ASSERT_EQ(&h2, darwin._world.at(darwin._index(1, 0)));
  ASSERT_EQ(h2._s, &hopper);
}

/** Test Darwin simulate with empty world */
TEST(DarwinFixture, DarwinTest5) {
  Darwin darwin(2, 2);
  darwin.simulate();

  ASSERT_EQ(nullptr, darwin._world.at(darwin._index(0, 0)));
  ASSERT_EQ(nullptr, darwin._world.at(darwin._index(0, 1)));
  ASSERT_EQ(nullptr, darwin._world.at(darwin._index(1, 0)));
  ASSERT_EQ(nullptr, darwin._world.at(darwin._index(1, 1)));
}

/** Test Darwin << operator (print simple board) */
TEST(DarwinFixture, DarwinTest6) {
  Darwin darwin(1, 2);
  Species hopper('h');
  hopper.addInstruction({Instruction::Type::hop});
  hopper.addInstruction({Instruction::Type::go, 0});
  Creature h1(&hopper, Direction::east);

  darwin.addCreature(&h1, 0, 0);
  darwin.simulate();
  ostringstream w;
  w << darwin;

  ASSERT_EQ(w.str(), "Turn = 1.\n  01\n0 .h\n");
}

/** Test Darwin << operator (print complex board) */
TEST(DarwinFixture, DarwinTest7) {
  Darwin darwin(2, 2);
  Species hopper('h');
  hopper.addInstruction({Instruction::Type::hop});
  hopper.addInstruction({Instruction::Type::go, 0});
  Creature h1(&hopper, Direction::east);
  Creature h2(&hopper, Direction::north);

  Species trap('t');
  trap.addInstruction({Instruction::Type::infect});
  trap.addInstruction({Instruction::Type::go, 0});
  Creature t1(&trap, Direction::west);

  darwin.addCreature(&h1, 0, 0);
  darwin.addCreature(&t1, 0, 1);
  darwin.addCreature(&h2, 1, 0);
  darwin.simulate();
  ostringstream w;
  w << darwin;

  ASSERT_EQ(w.str(), "Turn = 1.\n  01\n0 tt\n1 h.\n");
}

/** Test Darwin << operator (print empty board) */
TEST(DarwinFixture, DarwinTest8) {
  Darwin darwin(2, 4);
  ostringstream w;
  w << darwin;
  ASSERT_EQ(w.str(), "Turn = 0.\n  0123\n0 ....\n1 ....\n");
}

/** Test Darwin << operator
    (print many boards, should have different turns) */
TEST(DarwinFixture, DarwinTest9) {
  Darwin darwin(2, 4);

  ostringstream t0;
  t0 << darwin;
  ASSERT_EQ(t0.str(), "Turn = 0.\n  0123\n0 ....\n1 ....\n");

  darwin.simulate();
  ostringstream t1;
  t1 << darwin;
  ASSERT_EQ(t1.str(), "Turn = 1.\n  0123\n0 ....\n1 ....\n");

  darwin.simulate();
  ostringstream t2;
  t2 << darwin;
  ASSERT_EQ(t2.str(), "Turn = 2.\n  0123\n0 ....\n1 ....\n");
}

/** Test Darwin << operator
    (print wide board, should mod 10 columns) */
TEST(DarwinFixture, DarwinTest10) {
  Darwin darwin(1, 14);
  ostringstream w;
  w << darwin;
  ASSERT_EQ(w.str(), "Turn = 0.\n  01234567890123\n0 ..............\n");
}

/** Test Darwin << operator
    (print wide board, should mod 10 columns) */
TEST(DarwinFixture, DarwinTest11) {
  Darwin darwin(14, 1);
  ostringstream w;
  w << darwin;
  ASSERT_EQ(w.str(), "Turn = 0.\n  0\n0 .\n1 .\n2 .\n3 .\n4 .\n5 .\n6 .\n7 "
                     ".\n8 .\n9 .\n0 .\n1 .\n2 .\n3 .\n");
}
