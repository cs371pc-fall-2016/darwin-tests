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

TEST(DarwinFixture, DarwinConstructor1) {
    Darwin x(0, 0);

    ASSERT_EQ(x.rows, 0);
    ASSERT_EQ(x.columns, 0);
    ASSERT_EQ(x.grid.size(), 0);
}

TEST(DarwinFixture, DarwinConstructor2) {
    Darwin x(10, 10);

    ASSERT_EQ(x.rows, 10);
    ASSERT_EQ(x.columns, 10);
    ASSERT_EQ(x.grid.size(), 10);
    ASSERT_EQ(x.grid[0].size(), 10);
}

TEST(DarwinFixture, CreatureConstructor) {
    Species base("test");
    Creature timmy(base, Direction::north);

    ASSERT_EQ(timmy.species, &base);
    ASSERT_EQ(timmy.direction, Direction::north);
    ASSERT_TRUE(timmy.programCounter == 0);
}

TEST(DarwinFixture, SpeciesConstructor) {
    Species bird("eagle");

    ASSERT_EQ(bird.name, "eagle");
    ASSERT_TRUE(bird.instructionList.size() == 0);
}

TEST(DarwinFixture, AddControl1) {
    Species test("test");

    test.addControl(Instruction::go, 0);
    ASSERT_EQ(test.instructionList[0].first, Instruction::go);
    ASSERT_EQ(test.instructionList[0].second, 0);

    test.addControl(Instruction::if_wall, 1);
    ASSERT_EQ(test.instructionList[1].first, Instruction::if_wall);
    ASSERT_EQ(test.instructionList[1].second, 1);
}

TEST(DarwinFixture, AddControl2) {
    Species test("test");
    ASSERT_THROW(test.addControl(Instruction::hop, 0), std::invalid_argument);
}

TEST(DarwinFixture, AddControl3) {
    Species test("test");

    for(int i = 0; i < 10; ++i)
        test.addControl(Instruction::go, i);
    ASSERT_EQ(test.instructionList.size(), 10);
}

TEST(DarwinFixture, addAction1) {
    Species test("test");

    test.addAction(Instruction::hop);
    ASSERT_EQ(test.instructionList[0].first, Instruction::hop);
    ASSERT_EQ(test.instructionList[0].second, -1);

    test.addAction(Instruction::infect);
    ASSERT_EQ(test.instructionList[1].first, Instruction::infect);
    ASSERT_EQ(test.instructionList[1].second, -1);
}

TEST(DarwinFixture, AddAction2) {
    Species test("test");
    ASSERT_THROW(test.addAction(Instruction::go), std::invalid_argument);
}

TEST(DarwinFixture, AddAction3) {
    Species test("test");

    for(int i = 0; i < 10; ++i)
        test.addAction(Instruction::hop);
    ASSERT_EQ(test.instructionList.size(), 10);
}

TEST(DarwinFixture, addCreature1) {
    Darwin x(3, 3);

    Species a("a");
    Species b("b");
    Creature a1(a, Direction::north);
    Creature b1(b, Direction::east);

    x.addCreature(a1, 0, 0);
    x.addCreature(b1, 2, 1);

    ASSERT_EQ(x.grid[0][0], &a1);
    ASSERT_EQ(x.grid[2][1], &b1);
}

TEST(DarwinFixture, addCreature2) {
    Darwin x(3, 3);

    Species a("a");
    Species b("b");
    Species c("c");
    Creature a1(a, Direction::north);
    Creature b1(b, Direction::east);
    Creature c1(c, Direction::south);
    x.addCreature(a1, 0, 0);
    x.addCreature(b1, 2, 1);
    x.addCreature(c1, 0, 2);

    ostringstream o;
    o << x;

    ASSERT_EQ("  012\n0 a.c\n1 ...\n2 .b.\n\n", o.str());
}

TEST(DarwinFixture, addCreature3) {
    Darwin x(3, 3);

    Species a("a");
    Creature a1(a, Direction::north);

    ASSERT_THROW(x.addCreature(a1, -1, -1), std::invalid_argument);
    ASSERT_THROW(x.addCreature(a1, 3, 4), std::invalid_argument);
}

TEST(DarwinFixture, simulate1) {
    Darwin x(2, 2);

    Species a("a");
    a.addAction(Instruction::hop);
    a.addControl(Instruction::go, 0);
    Creature a1(a, Direction::south);
    x.addCreature(a1, 0, 0);

    ostringstream o;
    o << x;

    ASSERT_EQ("  01\n0 a.\n1 ..\n\n", o.str());
    o.str("");
    o.clear();
    x.simulate();
    o << x;
    ASSERT_EQ("  01\n0 ..\n1 a.\n\n", o.str());
}

TEST(DarwinFixture, simulate2) {
    Darwin x(2, 2);

    Species a("a");
    a.addAction(Instruction::hop);
    a.addControl(Instruction::go, 0);
    Species b("b");
    b.addAction(Instruction::infect);
    b.addControl(Instruction::go, 0);
    Creature a1(a, Direction::south);
    x.addCreature(a1, 0, 0);
    Creature b1(b, Direction::west);
    x.addCreature(b1, 1, 1);

    ostringstream o;
    o << x;

    ASSERT_EQ("  01\n0 a.\n1 .b\n\n", o.str());
    o.str("");
    o.clear();
    x.simulate();
    o << x;
    ASSERT_EQ("  01\n0 ..\n1 bb\n\n", o.str());
}

TEST(DarwinFixture, takeTurn1) {
    Species test("test");
    test.addAction(Instruction::hop);
    test.addControl(Instruction::go, 0);
    Creature a(test, Direction::north);
    Creature* surrounding[] = {nullptr, nullptr, nullptr, nullptr};
    pair<int, int> newPos = a.takeTurn(surrounding);
    ASSERT_EQ(newPos.first, -1);
    ASSERT_EQ(newPos.second, 0);
}

TEST(DarwinFixture, takeTurn2) {
    Species test("test");
    test.addAction(Instruction::right);
    test.addAction(Instruction::right);
    test.addAction(Instruction::right);
    test.addAction(Instruction::left);
    test.addAction(Instruction::left);
    test.addAction(Instruction::left);
    Creature a(test, Direction::north);
    Creature* surrounding[] = {nullptr, nullptr, nullptr, nullptr};
    a.takeTurn(surrounding);
    ASSERT_EQ(a.direction, Direction::east);
    a.takeTurn(surrounding);
    ASSERT_EQ(a.direction, Direction::south);
    a.takeTurn(surrounding);
    ASSERT_EQ(a.direction, Direction::west);
    a.takeTurn(surrounding);
    ASSERT_EQ(a.direction, Direction::south);
    a.takeTurn(surrounding);
    ASSERT_EQ(a.direction, Direction::east);
    a.takeTurn(surrounding);
    ASSERT_EQ(a.direction, Direction::north);
}

TEST(DarwinFixture, takeTurn3) {
    Species test("test");
    test.addControl(Instruction::if_wall, 3);
    test.addAction(Instruction::hop);
    test.addControl(Instruction::go, 0);
    test.addAction(Instruction::right);
    test.addAction(Instruction::right);
    test.addControl(Instruction::go, 0);
    Creature a(test, Direction::north);
    Creature* surrounding[] = {&a, nullptr, nullptr, nullptr};
    a.takeTurn(surrounding);
    ASSERT_EQ(a.programCounter, 4);
}

TEST(DarwinFixture, takeTurn4) {
    Species test("test");
    Species other("other");
    test.addControl(Instruction::if_enemy, 2);
    test.addAction(Instruction::right);
    test.addAction(Instruction::hop);
    test.addControl(Instruction::go, 1);
    Creature a(test, Direction::north);
    Creature b(other, Direction::north);
    Creature* surrounding[] = {&b, nullptr, nullptr, nullptr};
    a.takeTurn(surrounding);
    ASSERT_EQ(a.programCounter, 3);
}

TEST(DarwinFixture, takeTurn5) {
    Species test("test");
    test.addControl(Instruction::if_empty, 4);
    test.addAction(Instruction::hop);
    test.addAction(Instruction::hop);
    test.addAction(Instruction::hop);
    test.addControl(Instruction::go, 5);
    test.addAction(Instruction::infect);
    test.addControl(Instruction::go, 0);
    Creature a(test, Direction::north);
    Creature* surrounding[] = {nullptr, nullptr, nullptr, nullptr};
    a.takeTurn(surrounding);
    ASSERT_EQ(a.programCounter, 6);
}

TEST(DarwinFixture, takeTurn6) {
    srand(0);
    Species test("test");
    test.addControl(Instruction::if_random, 4);
    test.addAction(Instruction::hop);
    test.addAction(Instruction::hop);
    test.addAction(Instruction::hop);
    test.addAction(Instruction::infect);
    test.addControl(Instruction::go, 0);
    Creature a(test, Direction::north);
    Creature* surrounding[] = {nullptr, nullptr, nullptr, nullptr};
    a.takeTurn(surrounding);
    ASSERT_EQ(a.programCounter, 5);
}

TEST(DarwinFixture, takeTurn7) {
    Species test("test");
    Species other("other");
    test.addAction(Instruction::infect);
    test.addControl(Instruction::go, 0);
    Creature a(test, Direction::north);
    Creature b(other, Direction::north);
    Creature* surrounding[] = {&b, nullptr, nullptr, nullptr};
    a.takeTurn(surrounding);
    ASSERT_EQ(a.species, b.species);
}

TEST(DarwinFixture, representation1) {
    Species test("test");
    ASSERT_EQ(test.representation(), 't');
}

TEST(DarwinFixture, representation2) {
    Species empty("");
    ASSERT_EQ(empty.representation(), ' ');
}

TEST(DarwinFixture, representation3) {
    Species weirdo("!@#$^&*()");
    ASSERT_EQ(weirdo.representation(), '!');
}

TEST(DarwinFixture, representation4) {
    Species notEmpty("     ");
    ASSERT_EQ(notEmpty.representation(), ' ');
}

TEST(DarwinFixture, creatureOutput1) {
    ostringstream o;
    Species test("test");
    Creature t(test, Direction::north);
    o << t;
    ASSERT_EQ(o.str(), "t");
}

TEST(DarwinFixture, creatureOutput2) {
    ostringstream o;
    Species empty("");
    Creature e(empty, Direction::north);
    o << e;
    ASSERT_EQ(o.str(), " ");
}

TEST(DarwinFixture, creatureOutput3) {
    ostringstream o;
    Species weirdo("!@#$^&*()");
    Creature e(weirdo, Direction::north);
    o << e;
    ASSERT_EQ(o.str(), "!");
}

TEST(DarwinFixture, creatureOutput4) {
    ostringstream o;
    Species notEmpty("      ");
    Creature e(notEmpty, Direction::north);
    o << e;
    ASSERT_EQ(o.str(), " ");
}

TEST(DarwinFixture, darwinOutput1) {
    ostringstream o;
    Darwin x(3, 3);
    o << x;
    ASSERT_EQ(o.str(), "  012\n0 ...\n1 ...\n2 ...\n\n");
}

TEST(DarwinFixture, darwinOutput2) {
    ostringstream o;
    Darwin x(2, 2);
    Species l("l");
    Creature lGuy(l, Direction::north);
    x.addCreature(lGuy, 0, 0);
    x.addCreature(lGuy, 1, 0);
    x.addCreature(lGuy, 0, 1);
    x.addCreature(lGuy, 1, 1);
    o << x;
    ASSERT_EQ(o.str(), "  01\n0 ll\n1 ll\n\n");
}

TEST(DarwinFixture, darwinOutput3) {
    ostringstream o;
    Darwin x(2, 2);
    Species empty("");
    Creature emptyDude(empty, Direction::north);
    x.addCreature(emptyDude, 0, 0);
    x.addCreature(emptyDude, 1, 0);
    x.addCreature(emptyDude, 0, 1);
    x.addCreature(emptyDude, 1, 1);
    o << x;
    ASSERT_EQ(o.str(), "  01\n0   \n1   \n\n");
}
