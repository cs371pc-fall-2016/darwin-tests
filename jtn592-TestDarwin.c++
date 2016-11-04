/// ------------------------------
// projects/darwin/TestDarwin.c++
// Copyright (C) 2016
// Glenn P. Downing
// ------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <cstdlib>   // rand, srand
#include <sstream>
#include <iostream>  // cout, endl 

#include "gtest/gtest.h"

#include "Darwin.h"

using namespace std;

// ----
// test
// ----

//Test species default constructor
TEST(DarwinFixture, speciesConstTest1) {
  Darwin x(3, 3, 1);
  Species s;
  Species food("f");
  Creature c(s);
  Creature f1(food);
  x.addCreature(c, NORTH, 0, 0);
  x.addCreature(f1, WEST, 0, 1);
  ASSERT_FALSE(f1.ifEnemy(x));
  ASSERT_TRUE(f1.ifEmpty(x));
}

TEST(DarwinFixture, speciesConstTest2) {
  Species blank;
  Creature b1(blank);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  b1.printMe();

  cout.rdbuf(old_buf);

  ASSERT_EQ(".", ss.str());
}

//Test species String constructor
TEST(DarwinFixture, speciesConstTest3) {
  Species s("s");
  Creature s1(s);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  s1.printMe();

  cout.rdbuf(old_buf);

  ASSERT_EQ("s", ss.str());
}

TEST(DarwinFixture, speciesConstTest4) {
  Darwin x(3, 3, 1);
  Species food("f");
  Species hopper("h");
  Creature f1(food);
  Creature f2(food);
  Creature h1(hopper);
  x.addCreature(f1, EAST, 0, 0);
  x.addCreature(h1, WEST, 0, 1);
  x.addCreature(f2, NORTH, 1, 0);
  ASSERT_TRUE(h1.ifEnemy(x));
  ASSERT_FALSE(f2.ifEnemy(x));
}

//Test species add instruction method
TEST(DarwinFixture, speciesAddInstrTest1) {
  Darwin x(3, 3, 2);
  Species food("f");
  food.addInstruction("left");
  food.addInstruction("go 0");
  Creature f1(food);
  x.addCreature(f1, SOUTH, 0, 0);
  f1.work(x);
  ASSERT_FALSE(f1.ifWall(x));
}

//Test Creature default constructor
TEST(DarwinFixture, creatureConstTest1) {
  Creature c;
  Creature c1;
  Darwin x(3, 3, 1);
  x.addCreature(c, NORTH, 0, 0);
  x.addCreature(c1, WEST, 0, 1);
  ASSERT_FALSE(c1.ifEnemy(x));
  ASSERT_TRUE(c1.ifEmpty(x));
}

//Test Creature Species constructor
TEST(DarwinFixture, creatureConstTest2) {
  Darwin x(3, 3, 1);
  Species food("f");
  Species hopper("h");
  Creature f1(food);
  Creature h1(hopper);
  x.addCreature(f1, NORTH,0, 0);
  x.addCreature(h1, WEST, 0, 1);
  ASSERT_TRUE(h1.ifEnemy(x));
} 

//Test ifEmpty corners
TEST(DarwinFixture, ifEmptyTest1) {
  Darwin x(3, 3, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, WEST, 0, 0);
  ASSERT_FALSE(f1.ifEmpty(x));
  f1.right();
  ASSERT_FALSE(f1.ifEmpty(x));
  
  x.addCreature(f1, WEST, 2, 0);
  ASSERT_FALSE(f1.ifEmpty(x));
  f1.left();
  ASSERT_FALSE(f1.ifEmpty(x));
  
  x.addCreature(f1, EAST, 0, 2);
  ASSERT_FALSE(f1.ifEmpty(x));
  f1.left();
  ASSERT_FALSE(f1.ifEmpty(x));

  x.addCreature(f1, EAST, 2, 2);
  ASSERT_FALSE(f1.ifEmpty(x));
  f1.right();
  ASSERT_FALSE(f1.ifEmpty(x));
}

//Simple Test
TEST(DarwinFixture, ifEmptyTest2) {
  Darwin x(3, 3, 1);
  Species food("f");
  Species blank(".");
  Creature f1(food);
  Creature f2(food);
  Creature b1(blank);
  x.addCreature(f1, EAST, 0, 0);
  x.addCreature(f2, WEST, 0, 1);
  ASSERT_FALSE(f2.ifEmpty(x));
  x.addCreature(b1, EAST, 0, 0);
  ASSERT_TRUE(f2.ifEmpty(x));
}

TEST (DarwinFixture, ifEmptyTest3) {
  Darwin x(3, 3, 1);
  Species food("f");
  Species hopper("h");
  Species rover("r");
  Species trap("t");
  
  Creature f1(food);
  Creature f2(food);
  Creature h1(hopper);
  Creature r1(rover);
  Creature t1(trap);
  
  x.addCreature(f1, NORTH, 0, 1);
  x.addCreature(f2, NORTH, 1, 1);
  x.addCreature(h1, NORTH, 1, 2);
  x.addCreature(r1, NORTH, 2, 1);
  x.addCreature(t1, NORTH, 1, 0);
  
  //TEST for f1
  for (int i = 0; i < 4; ++i) {
    if (i % 2 == 0) 
      ASSERT_FALSE(f1.ifEmpty(x));
    else
      ASSERT_TRUE(f1.ifEmpty(x));
    f1.right();
  }
  //TEST for f2
  for (int i = 0; i < 4; ++i) {
    ASSERT_FALSE(f2.ifEmpty(x));
    f2.right();
  }
  //TEST for h1
  for (int i = 0; i < 4; ++i) {
    if (i % 2 == 1) 
      ASSERT_FALSE(h1.ifEmpty(x));
    else
      ASSERT_TRUE(h1.ifEmpty(x));
    h1.right();
    }
  //TEST for r1
  for (int i = 0; i < 4; ++i) {
    if (i % 2 == 0) 
      ASSERT_FALSE(r1.ifEmpty(x));
    else
      ASSERT_TRUE(r1.ifEmpty(x));
    r1.right();
  }
  //TEST for t1
  for (int i = 0; i < 4; ++i) {
    if (i % 2 == 1) 
      ASSERT_FALSE(t1.ifEmpty(x));
    else
      ASSERT_TRUE(t1.ifEmpty(x));
    t1.right();
  }
}

TEST(DarwinFixture, ifWallTest1) {
  Darwin x(7, 7, 1);
  Species food("f");
  food.addInstruction("left");
  food.addInstruction("go 0");
  Creature f1(food);
  x.addCreature(f1, WEST, 0, 0);
  ASSERT_TRUE(f1.ifWall(x));} 

TEST(DarwinFixture, ifWallTest2) {
  Darwin x(7, 7, 1);
  Species food("f");
  food.addInstruction("left");
  food.addInstruction("go 0");
  Creature f1(food);
  x.addCreature(f1, EAST, 6, 6);
  ASSERT_TRUE(f1.ifWall(x));} 

TEST(DarwinFixture, ifWallTest3) {
  Darwin x(7, 7, 1);
  Species food("f");
  food.addInstruction("left");
  food.addInstruction("go 0");
  Creature f1(food);
  for (int i = 1; i < 5; ++i) {
    for (int j = 1; j < 5; ++j) {
      x.addCreature(f1, WEST, i, j);
      ASSERT_FALSE(f1.ifWall(x));
      x.addCreature(f1, NORTH, i, j);
      ASSERT_FALSE(f1.ifWall(x));
      x.addCreature(f1, EAST, i, j);
      ASSERT_FALSE(f1.ifWall(x));
      x.addCreature(f1, SOUTH, i, j);
      ASSERT_FALSE(f1.ifWall(x));
    }
  }}

TEST(DarwinFixture,ifRandomTest1) {
  Creature x;
  int flag = x.ifRandom();
  ASSERT_TRUE(flag == 0 || flag == 1);
}

TEST(DarwinFixture, ifRandomTest2) {
  Creature x;
  bool flag = x.ifRandom();
  ASSERT_TRUE(flag == true || flag == false);
}

//TEST simple
TEST(DarwinFixture, ifEnemyTest1) {
  Darwin x(10, 10, 1);
  Species food("f");
  Species hopper("h");
  Creature f1(food);
  Creature h1(hopper);
  x.addCreature(f1, EAST, 0, 1);
  x.addCreature(h1, EAST, 0, 0);
  bool flag = h1.ifEnemy(x);
  ASSERT_TRUE(flag);}

//TEST edges
TEST(DarwinFixture, ifEnemyTest2) {
  Darwin x(10, 10, 1);
  Species food("f");
  Creature f1(food);
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      if (i == 0) {
      x.addCreature(f1, NORTH, i, j);
      ASSERT_FALSE(f1.ifEnemy(x));
      }
      else if (j == 9) {
	x.addCreature(f1, EAST, i, j);
	ASSERT_FALSE(f1.ifEnemy(x));
      }		  
      else if (i == 9) {
	x.addCreature(f1, SOUTH, i, j);
	ASSERT_FALSE(f1.ifEnemy(x));
      } 
      else if (j == 0) {
	x.addCreature(f1, WEST, i, j);
	ASSERT_FALSE(f1.ifEnemy(x));
      }
    }
  }
}

//Test all branches
TEST(DarwinFixture, ifEnemyTest3) {
  Darwin x(3, 3, 1);
  Species food("f");
  Species hopper("h");
  Species rover("r");
  Species trap("t");
  
  Creature f1(food);
  Creature f2(food);
  Creature h1(hopper);
  Creature r1(rover);
  Creature t1(trap);
  
  x.addCreature(f1, NORTH, 0, 1);
  x.addCreature(f2, NORTH, 1, 1);
  x.addCreature(h1, NORTH, 1, 2);
  x.addCreature(r1, NORTH, 2, 1);
  x.addCreature(t1, NORTH, 1, 0);
  
  //TEST for f1
  for (int i = 0; i < 4; ++i) { 
    ASSERT_FALSE(f1.ifEnemy(x));
    f1.right();
  }
  //TEST for f2
  for (int i = 0; i < 4; ++i) {
    if (i == 0)
      ASSERT_FALSE(f2.ifEnemy(x));
    else 
      ASSERT_TRUE(f2.ifEnemy(x));
    f2.right();
  }
  //TEST for h1
  for (int i = 0; i < 4; ++i) {
    if (i != 3) 
      ASSERT_FALSE(h1.ifEnemy(x));
    else
      ASSERT_TRUE(h1.ifEnemy(x));
    h1.right();
    }
  //TEST for r1
  for (int i = 0; i < 4; ++i) {
    if (i != 0) 
      ASSERT_FALSE(r1.ifEnemy(x));
    else
      ASSERT_TRUE(r1.ifEnemy(x));
    r1.right();
  }
  //TEST for t1
  for (int i = 0; i < 4; ++i) {
    if (i != 1) 
      ASSERT_FALSE(t1.ifEnemy(x));
    else
      ASSERT_TRUE(t1.ifEnemy(x));
    t1.right();
  }
}

//Test go
TEST(DarwinFixture, goTest1) {
  Species food("f");
  Species hopper("h");
  food.addInstruction("hop");
  food.addInstruction("go 0");
  hopper.addInstruction("left");
  hopper.addInstruction("go 0");
  Creature f1(food);
  Creature h1(hopper);
  Darwin x(3, 3, 4);
  x.addCreature(f1, WEST, 1, 2);
  x.addCreature(h1, NORTH, 1, 1);
  ASSERT_TRUE(f1.ifEnemy(x));
  
  x.addCreature(h1);
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  
  ASSERT_TRUE(f1.ifEnemy(x));
}

TEST(DarwinFixture, goTest2) {
  Species hopper("h");
  hopper.addInstruction("right");
  hopper.addInstruction("hop");
  hopper.addInstruction("go 0");
  Creature h1(hopper);
  Darwin x(3, 3, 8);
  x.addCreature(h1, NORTH, 0, 0);
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  ASSERT_TRUE(h1.ifWall(x));
  h1.left();
  ASSERT_TRUE(h1.ifWall(x));
}

TEST(DarwinFixture, goTest3) {
  Species hopper("h");
  hopper.addInstruction("if_enemy 3");
  hopper.addInstruction("hop");
  hopper.addInstruction("go 0");
  hopper.addInstruction("right");
  hopper.addInstruction("go 1");
  Species food("f");
  food.addInstruction("left");
  food.addInstruction("go 0");
  Creature h1(hopper);
  Creature f1(food);
  Darwin x(3, 3, 3);
  x.addCreature(h1, EAST, 0, 0);
  x.addCreature(f1, EAST, 0, 2);
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  ASSERT_FALSE(h1.ifEnemy(x));
  //cout << ss.str() << endl;
  h1.left();
  h1.hop(x);
  h1.left();
  ASSERT_TRUE(h1.ifWall(x));
  //ASSERT_TRUE(h1.ifEnemy(x));
  
}

//Test left starting WEST
TEST(DarwinFixture, leftTest1) {
  Darwin x(3, 3, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, WEST, 0, 0);
  ASSERT_TRUE(f1.ifWall(x));
  f1.left();
  ASSERT_FALSE(f1.ifWall(x));
}

//Test left starting SOUTH
TEST(DarwinFixture, leftTest2) {
  Darwin x(3, 3, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, SOUTH, 2, 0);
  ASSERT_TRUE(f1.ifWall(x));
  f1.left();
  ASSERT_FALSE(f1.ifWall(x));
}

//Test left starting EAST
TEST(DarwinFixture, leftTest3) {
  Darwin x(3, 3, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, EAST, 2, 2);
  ASSERT_TRUE(f1.ifWall(x));
  f1.left();
  ASSERT_FALSE(f1.ifWall(x));
}

//Test left startng NORTH
TEST(DarwinFixture, leftTest4) {
  Darwin x(3, 3, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, NORTH, 0, 2);
  ASSERT_TRUE(f1.ifWall(x));
  f1.left();
  ASSERT_FALSE(f1.ifWall(x));
}

//Test right starting WEST
TEST(DarwinFixture, rightTest1) {
  Darwin x(3, 3, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, WEST, 2, 0);
  ASSERT_TRUE(f1.ifWall(x));
  f1.right();
  ASSERT_FALSE(f1.ifWall(x));
}

//Test right starting NORTH
TEST(DarwinFixture, rightTest2) {
  Darwin x(3, 3, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, NORTH, 0, 0);
  ASSERT_TRUE(f1.ifWall(x));
  f1.right();
  ASSERT_FALSE(f1.ifWall(x));
}

//Test right starting EAST
TEST(DarwinFixture, righttTest3) {
  Darwin x(3, 3, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, EAST, 0, 2);
  ASSERT_TRUE(f1.ifWall(x));
  f1.right();
  ASSERT_FALSE(f1.ifWall(x));
}

//Test right startng SOUTH
TEST(DarwinFixture, rightTest4) {
  Darwin x(3, 3, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, SOUTH, 2, 2);
  ASSERT_TRUE(f1.ifWall(x));
  f1.right();
  ASSERT_FALSE(f1.ifWall(x));
}

//Test hop() corners
TEST(DarwinFixture, hopTest1) {
  Darwin x(3, 3, 1);
  Species food("f");
  Creature f1(food);
  Creature f2(food);
  Creature f3(food);
  Creature f4(food);
  

  x.addCreature(f1, WEST, 0, 0);
  x.addCreature(f2, NORTH, 0, 2);
  x.addCreature(f3, EAST, 2, 2);
  x.addCreature(f4, SOUTH, 2, 0);
  
  for (int i = 0; i < 4; ++i) {
    if (i == 0) { 
      f1.hop(x);
      ASSERT_TRUE(f1.ifWall(x));
      f1.right();
      ASSERT_TRUE(f1.ifWall(x));
    }
    else if (i == 1) { 
      f2.hop(x);
      ASSERT_TRUE(f2.ifWall(x));
      f2.right();
      ASSERT_TRUE(f2.ifWall(x));
    }
    else if (i == 2) { 
      f3.hop(x);
      ASSERT_TRUE(f3.ifWall(x));
      f3.right();
      ASSERT_TRUE(f3.ifWall(x));
    }
    else if (i == 3) { 
      f4.hop(x);
      ASSERT_TRUE(f4.ifWall(x));
      f4.right();
      ASSERT_TRUE(f4.ifWall(x));
    }
  }
}

//Test square hop
TEST(DarwinFixture, hopTest2) {
  Darwin x(4, 4, 1);
  Species food("f");
  Species rover("h");
  Creature f1(food);
  Creature r1(rover);
  
  x.addCreature(f1, EAST, 1, 1);
  x.addCreature(r1, WEST, 1, 3);
  x.addCreature(r1, EAST, 2, 0);

  f1.hop(x);
  ASSERT_TRUE(f1.ifEnemy(x));
  f1.right();
  f1.hop(x);
  ASSERT_TRUE(f1.ifEmpty(x));
  f1.right();
  f1.hop(x);
  ASSERT_TRUE(f1.ifEnemy(x));
  f1.right();
  f1.hop(x);
  ASSERT_TRUE(f1.ifEmpty(x));
}

//Test diagonal hop
TEST(DarwinFixture, hopTest3) {
  Darwin x(4, 4, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, SOUTH, 0, 0);
  for (int i = 0; i < 6; ++i) {
    if (i != 0 && i % 2 == 0)
      f1.right();
    else if (i % 2 == 1)
      f1.left();
    f1.hop(x);
  }
  ASSERT_TRUE(f1.ifWall(x));
}

//Test blank creature infect
TEST(DarwinFixture, infectTest1) {
  Darwin x(4, 4, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, EAST, 0, 0);
  ASSERT_TRUE(f1.ifEmpty(x));
  f1.infect(x);
  ASSERT_TRUE(f1.ifEmpty(x));
}

//Test simple infection
TEST(DarwinFixture, infectTest2) {
  Darwin x(4, 4, 1);
  Species food("f");
  Species hopper("h");
  Creature f1(food);
  Creature h1(hopper);
  x.addCreature(f1, NORTH, 0, 0);
  x.addCreature(h1, WEST, 0, 1);
  ASSERT_TRUE(h1.ifEnemy(x));
  h1.infect(x);
  ASSERT_FALSE(h1.ifEnemy(x));
}



//Test every cardinal direction infect
TEST(DarwinFixture, infectTest3) {
  Darwin x(4, 4, 1);
  Species food("f");
  Species hopper("h");

  Creature f1(food);
  Creature h1(hopper);
  Creature h2(hopper);
  Creature h3(hopper);
  Creature h4(hopper);

  x.addCreature(f1, NORTH, 1, 1);
  x.addCreature(h1, NORTH, 0, 1);
  x.addCreature(h2, NORTH, 1, 2);
  x.addCreature(h3, NORTH, 2, 1);
  x.addCreature(h4, NORTH, 1, 0);

  for (int i = 0; i < 4; ++i) {
    ASSERT_TRUE(f1.ifEnemy(x));
    f1.infect(x);
    ASSERT_FALSE(f1.ifEnemy(x));
    f1.right();
  }
}

//Test computeNxtX simple case
TEST(DarwinFixture, computeNxtXTest1) {
  Species food("f");
  Creature f1(food);
  Darwin x(3, 3, 1);
  x.addCreature(f1, WEST, 1, 1);
  ASSERT_EQ(1, f1.computeNxtX());
}

//TEST computeNxtX every simple case
TEST(DarwinFixture, computeNxtXTest2) {
  Species food("f");
  Creature f1(food);
  Darwin x(3, 3, 1);
  x.addCreature(f1, WEST, 1, 1);
  ASSERT_EQ(1, f1.computeNxtX());
  f1.right();
  ASSERT_EQ(0, f1.computeNxtX());
  f1.right();
  ASSERT_EQ(1, f1.computeNxtX());
  f1.right();
  ASSERT_EQ(2, f1.computeNxtX());
}

//Test compute NxtX corners
TEST(DarwinFixture, computeNxtXTest3) {
  Species food("f");
  Creature f1(food);
  Creature f2(food);
  Creature f3(food);
  Creature f4(food);
  Darwin x(3, 3, 1);
  x.addCreature(f1, WEST, 0, 0);
  x.addCreature(f2, NORTH, 0, 2);
  x.addCreature(f3, EAST, 2, 2);
  x.addCreature(f4, SOUTH, 2, 0);
  ASSERT_EQ(0, f1.computeNxtX());
  f1.right();
  ASSERT_EQ(-1, f1.computeNxtX());
  ASSERT_EQ(-1, f2.computeNxtX());
  f2.right();
  ASSERT_EQ(0, f2.computeNxtX());
  ASSERT_EQ(2, f3.computeNxtX());
  f3.right();
  ASSERT_EQ(3, f3.computeNxtX());
  ASSERT_EQ(3, f4.computeNxtX());
  f4.right();
  ASSERT_EQ(2, f4.computeNxtX());
}

//Test computeNxtY simple case
TEST(DarwinFixture, computeNxtYTest1) {
  Species food("f");
  Creature f1(food);
  Darwin x(3, 3, 1);
  x.addCreature(f1, WEST, 1, 1);
  ASSERT_EQ(0, f1.computeNxtY());
}

//TEST computeNxtX every simple case
TEST(DarwinFixture, computeNxtYTest2) {
  Species food("f");
  Creature f1(food);
  Darwin x(3, 3, 1);
  x.addCreature(f1, WEST, 1, 1);
  ASSERT_EQ(0, f1.computeNxtY());
  f1.right();
  ASSERT_EQ(1, f1.computeNxtY());
  f1.right();
  ASSERT_EQ(2, f1.computeNxtY());
  f1.right();
  ASSERT_EQ(1, f1.computeNxtY());
}

//Test compute NxtX corners
TEST(DarwinFixture, computeNxtYTest3) {
  Species food("f");
  Creature f1(food);
  Creature f2(food);
  Creature f3(food);
  Creature f4(food);
  Darwin x(3, 3, 1);
  x.addCreature(f1, WEST, 0, 0);
  x.addCreature(f2, NORTH, 0, 2);
  x.addCreature(f3, EAST, 2, 2);
  x.addCreature(f4, SOUTH, 2, 0);
  ASSERT_EQ(-1, f1.computeNxtY());
  f1.right();
  ASSERT_EQ(0, f1.computeNxtY());
  ASSERT_EQ(2, f2.computeNxtY());
  f2.right();
  ASSERT_EQ(3, f2.computeNxtY());
  ASSERT_EQ(3, f3.computeNxtY());
  f3.right();
  ASSERT_EQ(2, f3.computeNxtY());
  ASSERT_EQ(0, f4.computeNxtY());
  f4.right();
  ASSERT_EQ(-1, f4.computeNxtY());
}

TEST(DarwinFixture, printMeTest1) {
  Species blank("");
  Creature b1(blank);
  
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  b1.printMe();
  
  cout.rdbuf(old_buf);

  ASSERT_EQ(ss.str(), "");
}

TEST(DarwinFixture, printMeTest2) {
  Species food("f");
  Creature b1(food);
  
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  b1.printMe();
  
  cout.rdbuf(old_buf);

  ASSERT_EQ(ss.str(), "f");
}

TEST(DarwinFixture, printMeTest3) {
  Species name("Jonathan");
  Creature b1(name);
  
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  b1.printMe();
  
  cout.rdbuf(old_buf);

  ASSERT_EQ(ss.str(), "Jonathan");
}

TEST(DarwinFixture, printMeTest4) {
  Species exclamation("!");
  Creature e1(exclamation);
  
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  e1.printMe();
  
  cout.rdbuf(old_buf);

  ASSERT_EQ(ss.str(), "!");
}

TEST(DarwinFixture, printMeTest5) {
  Species star("*");
  Creature s1(star);
  
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  s1.printMe();
  
  cout.rdbuf(old_buf);

  ASSERT_EQ(ss.str(), "*");
}

TEST(DarwinFixture, printMeTest6) {
  Species doubleBlank("  ");
  Creature dB1(doubleBlank);
  
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  dB1.printMe();
  
  cout.rdbuf(old_buf);

  ASSERT_EQ(ss.str(), "  ");
}

TEST(DarwinFixture, printMeTest7) {
  Species at("@");
  Creature a1(at);
  
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  a1.printMe();
  
  cout.rdbuf(old_buf);

  ASSERT_EQ(ss.str(), "@");
}

TEST(DarwinFixture, printMeTest8) {
  Species hash("#");
  Creature h1(hash);
  
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  h1.printMe();
  
  cout.rdbuf(old_buf);

  ASSERT_EQ(ss.str(), "#");
}

TEST(DarwinFixture, printMeTest9) {
  Species dollar("$");
  Creature d1(dollar);
  
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  d1.printMe();
  
  cout.rdbuf(old_buf);

  ASSERT_EQ(ss.str(), "$");
}

TEST(DarwinFixture, printMeTest10) {
  Species percent("%");
  Creature p1(percent);
  
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  p1.printMe();
  
  cout.rdbuf(old_buf);

  ASSERT_EQ(ss.str(), "%");
}

TEST(DarwinFixture, printMeTest11) {
  Species ampersand("&");
  Creature a1(ampersand);
  
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  a1.printMe();
  
  cout.rdbuf(old_buf);

  ASSERT_EQ(ss.str(), "&");
}

//Test darwin Constructor
TEST(DarwinFixture, darwinConst1) {
  Darwin x(2, 2, 1);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  01\n0 ..\n1 ..\n\nTurn = 1.\n  01\n0 ..\n1 ..\n\n";


  ASSERT_EQ(expected, ss.str());
}


TEST(DarwinFixture, darwinConst2) {
  Darwin x(0, 0, 0);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  \n\n";


  ASSERT_EQ(expected, ss.str());
}

TEST(DarwinFixture, darwinConst3) {
  Darwin x(3, 3, 1);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  012\n0 ...\n1 ...\n2 ...\n\nTurn = 1.\n  012\n0 ...\n1 ...\n2 ...\n\n";


  ASSERT_EQ(expected, ss.str());
}

TEST(DarwinFixture, darwinAddRandTest1) {
  Species hopper("h");
  Creature h1(hopper);
  Darwin x(4, 4, 1);
  x.addCreature(h1);
  for (int i = 0; i < 4; ++i) {
    h1.hop(x);
  }
  ASSERT_TRUE(h1.ifWall(x));
}

TEST(DarwinFixture, darwinAddRandTest2) {
  Species hopper("h");
  Creature h1(hopper);
  Darwin x(1, 1, 0);
  x.addCreature(h1);
  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  0\n0 .\n\n";
  ASSERT_NE(expected, ss.str());
}

/*TEST(DarwinFixture, darwinAddRandTest3) {
  Species hopper("h");
  Creature h1(hopper);
  Creature h2(hopper);
  Creature h3(hopper);
  Creature h4(hopper);
  Creature h5(hopper);
  Creature h6(hopper);
  Creature h7(hopper);
  Creature h8(hopper);
  Creature h9(hopper);
  Darwin x(3, 3, 1);
  x.addCreature(h1);
  x.addCreature(h2);
  x.addCreature(h3);
  x.addCreature(h4);
  x.addCreature(h5);
  x.addCreature(h6);
  x.addCreature(h7);
  x.addCreature(h8);
  x.addCreature(h9);
  x.runSim();
  ASSERT_FALSE(h1.ifEmpty(x));
  ASSERT_FALSE(h2.ifEmpty(x));
  ASSERT_FALSE(h3.ifEmpty(x));
  ASSERT_FALSE(h4.ifEmpty(x));
  ASSERT_FALSE(h5.ifEmpty(x));
  ASSERT_FALSE(h6.ifEmpty(x));
  ASSERT_FALSE(h7.ifEmpty(x));
  ASSERT_FALSE(h8.ifEmpty(x));
  ASSERT_FALSE(h9.ifEmpty(x));
}*/

//Test Darwin addCreature
TEST(DarwinFixture, addCreatureTest1) {
  Darwin x(3, 3, 1);
  Species food("f");
  Creature f1(food);
  x.addCreature(f1, NORTH, 0, 0);
  ASSERT_TRUE(f1.ifWall(x));
}

TEST(DarwinFixture, addCreatureTest2) {
  Darwin x(3, 3, 1);
  Species food("f");
  Species hopper("h");
  Creature f1(food);
  Creature h1(hopper);
  x.addCreature(f1, EAST, 0, 2);
  x.addCreature(h1, EAST, 0, 0);
  ASSERT_TRUE(h1.ifEmpty(x));
  h1.hop(x);
  ASSERT_TRUE(h1.ifEnemy(x));
  h1.infect(x);
  ASSERT_FALSE(h1.ifEnemy(x));
}

TEST(DarwinFixture, addCreatureTest3) {
  Darwin x(3, 3, 1);
  Species food("f");
  Species hopper("h");
  Creature f1(food);
  Creature f2(food);
  Creature h1(hopper);
  x.addCreature(f1, SOUTH, 1, 1);
  x.addCreature(f2, NORTH, 2, 1);
  ASSERT_FALSE(f1.ifEnemy(x));
  x.addCreature(h1, NORTH, 2, 1);
  ASSERT_TRUE(f1.ifEnemy(x));
}

//Test work if_empty 
TEST(DarwinFixture, workTest1) {
  Species hopper("r");
  hopper.addInstruction("if_empty 3");
  hopper.addInstruction("left");
  hopper.addInstruction("go 0");
  hopper.addInstruction("hop");
  hopper.addInstruction("go 0");
  Species food("f");
  food.addInstruction("left");
  food.addInstruction("go 0");
  Creature r1(hopper);
  Creature f1(food);
  Darwin x(3, 3, 2);
  x.addCreature(r1, EAST, 0, 0);
  x.addCreature(f1, NORTH, 0, 2);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  012\n0 r.f\n1 ...\n2 ...\n\nTurn = 1.\n  012\n0 .rf\n1 ...\n2 ...\n\nTurn = 2.\n  012\n0 .rf\n1 ...\n2 ...\n\n";
  ASSERT_EQ(expected, ss.str());
}

//Test work if_enemy
TEST(DarwinFixture, workTest2) {
  Species runner("r");
  runner.addInstruction("if_enemy 3");
  runner.addInstruction("hop");
  runner.addInstruction("go 0");
  runner.addInstruction("left");
  runner.addInstruction("go 0");
  Species food("f");
  food.addInstruction("left");
  food.addInstruction("go 0");
  Creature r1(runner);
  Creature f1(food);
  Darwin x(3, 3, 2);
  x.addCreature(r1, EAST, 0, 0);
  x.addCreature(f1, NORTH, 0, 2);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  012\n0 r.f\n1 ...\n2 ...\n\nTurn = 1.\n  012\n0 .rf\n1 ...\n2 ...\n\nTurn = 2.\n  012\n0 .rf\n1 ...\n2 ...\n\n";
  ASSERT_EQ(expected, ss.str());
}

//Test work if_wall
TEST(DarwinFixture, workTest3) {
  Species rover("r");
  rover.addInstruction("if_wall 3");
  rover.addInstruction("hop");
  rover.addInstruction("go 0");
  rover.addInstruction("left");
  rover.addInstruction("go 0");
  Creature r1(rover);
  Darwin x(3, 3, 2);
  x.addCreature(r1, WEST, 0, 0);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  012\n0 r..\n1 ...\n2 ...\n\nTurn = 1.\n  012\n0 r..\n1 ...\n2 ...\n\nTurn = 2.\n  012\n0 ...\n1 r..\n2 ...\n\n";

  ASSERT_EQ(expected, ss.str());
}

//Test work go 
TEST(DarwinFixture, workTest4) {
  Species hopper("h");
  hopper.addInstruction("hop");
  hopper. addInstruction("go 0");
  Creature h1(hopper);
  Darwin x(3, 3, 2);
  x.addCreature(h1, EAST, 0 , 0);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  012\n0 h..\n1 ...\n2 ...\n\nTurn = 1.\n  012\n0 .h.\n1 ...\n2 ...\n\nTurn = 2.\n  012\n0 ..h\n1 ...\n2 ...\n\n";

  ASSERT_EQ(expected, ss.str());
}

//Test work left 
TEST(DarwinFixture, workTest5) {
  Species food("f");
  food.addInstruction("left");
  food. addInstruction("go 0");
  Creature f1(food);
  Darwin x(3, 3, 2);
  x.addCreature(f1, EAST, 0 , 0);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  012\n0 f..\n1 ...\n2 ...\n\nTurn = 1.\n  012\n0 f..\n1 ...\n2 ...\n\nTurn = 2.\n  012\n0 f..\n1 ...\n2 ...\n\n";

  ASSERT_EQ(expected, ss.str());
}

//Test work right 
TEST(DarwinFixture, workTest6) {
  Species food("f");
  food.addInstruction("right");
  food. addInstruction("go 0");
  Creature f1(food);
  Darwin x(3, 3, 2);
  x.addCreature(f1, EAST, 0 , 0);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  012\n0 f..\n1 ...\n2 ...\n\nTurn = 1.\n  012\n0 f..\n1 ...\n2 ...\n\nTurn = 2.\n  012\n0 f..\n1 ...\n2 ...\n\n";

  ASSERT_EQ(expected, ss.str());
}

//Test work infect 
TEST(DarwinFixture, workTest7) {
  Species food("f");
  Species trap("t");
  food.addInstruction("left");
  food.addInstruction("go 0");
  trap.addInstruction("infect");
  trap.addInstruction("right");
  trap.addInstruction("go 0");
  Creature f1(food);
  Creature t1(trap);
  Darwin x(3, 3, 2);
  x.addCreature(f1, EAST, 0 , 1);
  x.addCreature(t1, EAST, 0, 0);
  

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  012\n0 tf.\n1 ...\n2 ...\n\nTurn = 1.\n  012\n0 tt.\n1 ...\n2 ...\n\nTurn = 2.\n  012\n0 tt.\n1 ...\n2 ...\n\n";

  ASSERT_EQ(expected, ss.str());
}

//Test work invalid 
TEST(DarwinFixture, workTest8) {
  Species invalid("i");
  invalid.addInstruction("invalid");
  invalid.addInstruction("go 0");
  Creature i1(invalid);
  Darwin x(3, 3, 1);
  x.addCreature(i1, EAST, 0 , 0);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  012\n0 i..\n1 ...\n2 ...\n\nTurn = 1.\n  012\n0 i..\n1 ...\n2 ...\n\n";

  ASSERT_TRUE(ss.str().find("INVALID") != string::npos);
}

//Test work ifRandom
TEST(DarwinFixture, workTest9) {
  Species random("r");
  random.addInstruction("if_random 2");
  random.addInstruction("go 0");
  random.addInstruction("left");
  random.addInstruction("go 0");
  Creature r1(random);
  Darwin x(3, 3, 5);
  x.addCreature(r1, EAST, 0, 0);

  stringstream ss;
  auto old_buf = cout.rdbuf(ss.rdbuf());
  
  x.runSim();

  cout.rdbuf(old_buf);
  string expected = "Turn = 0.\n  012\n0 r..\n1 ...\n2 ...\n\nTurn = 1.\n  012\n0 r..\n1 ...\n2 ...\n\nTurn = 2.\n  012\n0 r..\n1 ...\n2 ...\n\nTurn = 3.\n  012\n0 r..\n1 ...\n2 ...\n\nTurn = 4.\n  012\n0 r..\n1 ...\n2 ...\n\nTurn = 5.\n  012\n0 r..\n1 ...\n2 ...\n\n";

  ASSERT_EQ(expected,ss.str());
}

