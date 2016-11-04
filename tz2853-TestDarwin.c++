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
// Species
// ----

/*testing constructor*/
TEST(DarwinFixture, species_constructor_0) {
    Species food('f');
    ASSERT_EQ(food.speciesType, 'f');
}

TEST(DarwinFixture, species_constructor_1) {
    Species hopper('h');
    ASSERT_EQ(hopper.speciesType, 'h');
}

TEST(DarwinFixture, species_constructor_2) {
    Species rover('r');
    ASSERT_EQ(rover.speciesType, 'r');
}

TEST(DarwinFixture, species_constructor_3) {
    Species trap('t');
    ASSERT_EQ(trap.speciesType, 't');
}

/*testing addInstruction()*/
TEST(DarwinFixture, test_addInstruction_0) {
    Species food('f');
    vector<string> foodInstruction;
    foodInstruction.push_back("left");
    foodInstruction.push_back("-1");
    food.addInstruction(foodInstruction);
    //Creature food1(food, 1);    //North
    
    vector<vector<string>> tmp = food.instructionSet;
    ASSERT_EQ(tmp[0][0], "left");
    ASSERT_EQ(tmp[0][1], "-1");
}

TEST(DarwinFixture, test_addInstruction_1) {
    Species trap('t');
    vector<string> trapInstruction;
    trapInstruction.push_back("if_enemy");
    trapInstruction.push_back("3");
    trap.addInstruction(trapInstruction);
    
    vector<vector<string>> tmp = trap.instructionSet;
    ASSERT_EQ(tmp[0][0], "if_enemy");
    ASSERT_EQ(tmp[0][1], "3");
}

TEST(DarwinFixture, test_addInstruction_2) {
    Species rover('r');
    vector<string> roverInstruction;
    roverInstruction.push_back("go");
    roverInstruction.push_back("0");
    rover.addInstruction(roverInstruction);
    
    vector<vector<string>> tmp = rover.instructionSet;
    ASSERT_EQ(tmp[0][0], "go");
    ASSERT_EQ(tmp[0][1], "0");
}

//-------------------------------
TEST(DarwinFixture, test_addInstruction_3) {
    Species food('f');
    vector<string> foodInstruction;
    foodInstruction.push_back("infect");
    foodInstruction.push_back("-1");
    food.addInstruction(foodInstruction);
    //Creature food1(food, 1);    //North
    
    vector<vector<string>> tmp = food.instructionSet;
    ASSERT_EQ(tmp[0][0], "infect");
    ASSERT_EQ(tmp[0][1], "-1");
}

TEST(DarwinFixture, test_addInstruction_4) {
    Species trap('t');
    vector<string> trapInstruction;
    trapInstruction.push_back("left");
    trapInstruction.push_back("-1");
    trap.addInstruction(trapInstruction);
    
    vector<vector<string>> tmp = trap.instructionSet;
    ASSERT_EQ(tmp[0][0], "left");
    ASSERT_EQ(tmp[0][1], "-1");
}

TEST(DarwinFixture, test_addInstruction_5) {
    Species rover('r');
    vector<string> roverInstruction;
    roverInstruction.push_back("right");
    roverInstruction.push_back("-1");
    rover.addInstruction(roverInstruction);
    
    vector<vector<string>> tmp = rover.instructionSet;
    ASSERT_EQ(tmp[0][0], "right");
    ASSERT_EQ(tmp[0][1], "-1");
}

/*testing singleInstruction()*/
TEST(DarwinFixture, test_singleInstruction_0) {
    Species food('f');
    vector<string> foodInstruction;
    foodInstruction.push_back("left");
    foodInstruction.push_back("-1");
    food.addInstruction(foodInstruction);
    
    vector<string> tmp = food.singleInstruction(0);
    ASSERT_EQ(tmp[0], "left");
    ASSERT_EQ(tmp[1], "-1");
}

TEST(DarwinFixture, test_singleInstruction_1) {
    Species trap('t');
    vector<string> trapInstruction;
    trapInstruction.push_back("if_enemy");
    trapInstruction.push_back("3");
    trap.addInstruction(trapInstruction);
    vector<string> trapInstruction1;
    trapInstruction1.push_back("left");
    trapInstruction1.push_back("-1");
    trap.addInstruction(trapInstruction1);
    
    vector<string> tmp = trap.singleInstruction(1);
    ASSERT_EQ(tmp[0], "left");
    ASSERT_EQ(tmp[1], "-1");
}

TEST(DarwinFixture, test_singleInstruction_2) {
    Species rover('r');
    vector<string> roverInstruction;
    roverInstruction.push_back("if_random");
    roverInstruction.push_back("5");
    rover.addInstruction(roverInstruction);
    
    vector<string> tmp = rover.singleInstruction(0);
    ASSERT_EQ(tmp[0], "if_random");
    ASSERT_EQ(tmp[1], "5");
}

// ----
// Creature
// ----

/*testing runInstruction()*/
TEST(DarwinFixture, test_runInstruction_hop) {
    Species hopper('h');
    vector<string> hopperInstruction;
    hopperInstruction.push_back("hop");
    hopperInstruction.push_back("-1");
    hopper.addInstruction(hopperInstruction);
    
    Creature hopper1(hopper, 1);    //North

    vector<Creature*> newCoordnates = hopper1.runInstruction(0, nullptr);
    ASSERT_EQ(newCoordnates[0], nullptr);
    ASSERT_EQ(newCoordnates[1], &hopper1);
}


TEST(DarwinFixture, test_runInstruction_left) {
    Species food('f');
    vector<string> foodInstruction;
    foodInstruction.push_back("left");
    foodInstruction.push_back("3");
    food.addInstruction(foodInstruction);
    
    Creature food1(food, 1);    //North

    vector<Creature*> newCoordnates = food1.runInstruction(0, nullptr);
    ASSERT_EQ(food1.direction, 0);
}

TEST(DarwinFixture, test_runInstruction_right) {
    Species food('f');
    vector<string> foodInstruction;
    foodInstruction.push_back("right");
    foodInstruction.push_back("3");
    food.addInstruction(foodInstruction);
    
    Creature food1(food, 1);    //North

    vector<Creature*> newCoordnates = food1.runInstruction(0, nullptr);
    ASSERT_EQ(food1.direction, 2);
}

TEST(DarwinFixture, test_runInstruction_infect) {
    Species rover('r');
    vector<string> roverInstruction;
    roverInstruction.push_back("infect");
    roverInstruction.push_back("-1");
    rover.addInstruction(roverInstruction);

    Species hopper('h');
    
    Creature rover1(rover, 1);    //North
    Creature hopper1(rover, 1);    //North

    vector<Creature*> newCoordnates = rover1.runInstruction(0, &hopper1);
    ASSERT_EQ(hopper1.ptrSpecies, rover1.ptrSpecies);
}

TEST(DarwinFixture, test_runInstruction_complete) {
    Darwin d(3, 2);

    Species hopper('h');
    vector<string> hopperInstruction0;
    hopperInstruction0.push_back("hop");
    hopperInstruction0.push_back("-1");
    hopper.addInstruction(hopperInstruction0);
    vector<string> hopperInstruction1;
    hopperInstruction1.push_back("go");
    hopperInstruction1.push_back("0");
    hopper.addInstruction(hopperInstruction1);

    Species rover('r');
    vector<string> roverInstruction0;
    roverInstruction0.push_back("if_enemy");
    roverInstruction0.push_back("9");
    rover.addInstruction(roverInstruction0);
    vector<string> roverInstruction1;
    roverInstruction1.push_back("if_empty");
    roverInstruction1.push_back("7");
    rover.addInstruction(roverInstruction1);
    vector<string> roverInstruction2;
    roverInstruction2.push_back("if_random");
    roverInstruction2.push_back("5");
    rover.addInstruction(roverInstruction2);
    vector<string> roverInstruction3;
    roverInstruction3.push_back("left");
    roverInstruction3.push_back("-1");
    rover.addInstruction(roverInstruction3);
    vector<string> roverInstruction4;
    roverInstruction4.push_back("go");
    roverInstruction4.push_back("0");
    rover.addInstruction(roverInstruction4);
    vector<string> roverInstruction5;
    roverInstruction5.push_back("right");
    roverInstruction5.push_back("-1");
    rover.addInstruction(roverInstruction5);
    vector<string> roverInstruction6;
    roverInstruction6.push_back("go");
    roverInstruction6.push_back("0");
    rover.addInstruction(roverInstruction6);
    vector<string> roverInstruction7;
    roverInstruction7.push_back("hop");
    roverInstruction7.push_back("-1");
    rover.addInstruction(roverInstruction7);
    vector<string> roverInstruction8;
    roverInstruction8.push_back("go");
    roverInstruction8.push_back("0");
    rover.addInstruction(roverInstruction8);
    vector<string> roverInstruction9;
    roverInstruction9.push_back("infect");
    roverInstruction9.push_back("-1");
    rover.addInstruction(roverInstruction9);
    vector<string> roverInstruction10;
    roverInstruction10.push_back("go");
    roverInstruction10.push_back("0");
    rover.addInstruction(roverInstruction10);

    Creature hopper1(hopper, 1);
    Creature rover1(rover, 1);       

    d.addCreature(hopper1, 0, 1);
    d.addCreature(rover1, 1, 1);

    d.runDarwin(1);
    Creature* tmp = d.grid[1];
    ASSERT_EQ((*tmp).ptrSpecies, rover1.ptrSpecies);
}

/*testing constructor*/
TEST(DarwinFixture, creature_constructor_0){
    Species food('f');
    Creature food1(food, 0);
    ASSERT_EQ(food1.ptrSpecies, &food);
}

TEST(DarwinFixture, creature_constructor_1){
    Species hopper('h');
    Creature hopper1(hopper, 0);
    ASSERT_EQ(hopper1.ptrSpecies, &hopper);
}

TEST(DarwinFixture, creature_constructor_2){
    Species rover('r');
    Creature rover1(rover, 0);
    ASSERT_EQ(rover1.ptrSpecies, &rover);
}

TEST(DarwinFixture, creature_constructor_3){
    Species trap('t');
    Creature trap1(trap, 0);
    ASSERT_EQ(trap1.ptrSpecies, &trap);
}

//----------------------------------
TEST(DarwinFixture, creature_constructor_4){
    Species food('f');
    Creature food1(food, 0);
    ASSERT_EQ(food1.direction, 0);
}

TEST(DarwinFixture, creature_constructor_5){
    Species hopper('h');
    Creature hopper1(hopper, 1);
    ASSERT_EQ(hopper1.direction, 1);
}

TEST(DarwinFixture, creature_constructor_6){
    Species rover('r');
    Creature rover1(rover, 2);
    ASSERT_EQ(rover1.direction, 2);
}

TEST(DarwinFixture, creature_constructor_7){
    Species trap('t');
    Creature trap1(trap, 3);
    ASSERT_EQ(trap1.direction, 3);
}


/*testing coordInFront()*/
TEST(DarwinFixture, test_coordInFront_0) {
    Species food('f');
    Creature food1(food, 1);    //North
    
    vector<int> coordinates;
    coordinates.push_back(1);
    coordinates.push_back(1);
    
    vector<int> newCoordnates = food1.coordInFront(coordinates);
    ASSERT_EQ(newCoordnates[0], 0);
    ASSERT_EQ(newCoordnates[1], 1);
}

TEST(DarwinFixture, test_coordInFront_1) {
    Species food('f');
    Creature food1(food, 0);    
    
    vector<int> coordinates;
    coordinates.push_back(1);
    coordinates.push_back(1);
    
    vector<int> newCoordnates = food1.coordInFront(coordinates);
    ASSERT_EQ(newCoordnates[0], 1);
    ASSERT_EQ(newCoordnates[1], 0);
}

TEST(DarwinFixture, test_coordInFront_2) {
    Species food('f');
    Creature food1(food, 2);    
    
    vector<int> coordinates;
    coordinates.push_back(0);
    coordinates.push_back(0);
    
    vector<int> newCoordnates = food1.coordInFront(coordinates);
    ASSERT_EQ(newCoordnates[0], 0);
    ASSERT_EQ(newCoordnates[1], 1);
}

TEST(DarwinFixture, test_coordInFront_3) {
    Species food('f');
    Creature food1(food, 3);    
    
    vector<int> coordinates;
    coordinates.push_back(0);
    coordinates.push_back(0);
    
    vector<int> newCoordnates = food1.coordInFront(coordinates);
    ASSERT_EQ(newCoordnates[0], 1);
    ASSERT_EQ(newCoordnates[1], 0);
}

// ----
// Darwin
// ----

/*addCreature*/
TEST(DarwinFixture, test_addCreature_0) {
    Species food('f');
    Creature food1(food, 1);    //North
    
    Darwin d(10, 10);
    d.addCreature(food1, 3, 3);
    vector<Creature*> tmp = d.grid;
    
    ASSERT_EQ(tmp[33], &food1);
}

TEST(DarwinFixture, test_addCreature_1) {
    Species hopper('h');
    Creature hopper1(hopper, 1);    //North
    
    Darwin d(10, 10);
    d.addCreature(hopper1, 1, 3);
    vector<Creature*> tmp = d.grid;
    
    ASSERT_EQ(tmp[13], &hopper1);
}

TEST(DarwinFixture, test_addCreature_2) {
    Species rover('r');
    Creature rover1(rover, 1);    //North
    
    Darwin d(10, 10);
    d.addCreature(rover1, 5, 1);
    vector<Creature*> tmp = d.grid;
    
    ASSERT_EQ(tmp[51], &rover1);
}

TEST(DarwinFixture, test_addCreature_3) {
    Species trap('t');
    Creature trap1(trap, 1);    //North
    
    Darwin d(10, 10);
    d.addCreature(trap1, 8, 7);
    vector<Creature*> tmp = d.grid;
    
    ASSERT_EQ(tmp[87], &trap1);
}

/*testing darwin constructor*/
TEST(DarwinFixture, darwin_constructor_0){
    Darwin d(1, 1);
    ASSERT_EQ(d.height, 1);
    ASSERT_EQ(d.width, 1);
}

TEST(DarwinFixture, darwin_constructor_1){
    Darwin d(100, 120);
    ASSERT_EQ(d.height, 100);
    ASSERT_EQ(d.width, 120);
}

TEST(DarwinFixture, darwin_constructor_2){
    Darwin d(72, 71);
    ASSERT_NE(d.height, 71);
    ASSERT_NE(d.width, 72);
}

TEST(DarwinFixture, darwin_constructor_3){
    Darwin d(10, 1);
    ASSERT_EQ(d.height, 10);
    ASSERT_EQ(d.width, 1);
}