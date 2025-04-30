/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"


class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


TEST(GuesserTest, match){
	Guesser g("correct");
	EXPECT_TRUE(g.match("correct"));
}

TEST(GuesserTest, wrong){
	Guesser g("correct");
	EXPECT_FALSE(g.match("wrong"));
}

TEST(GuesserTest, maxSeceret_GuessOver32){
	Guesser g("maxsecretupto32characters1234567");
	EXPECT_TRUE(g.match("maxsecretupto32characters1234567890overmax"));
}

TEST(GuesserTest, limit){
	Guesser g("limit");
	g.match("fail");
	g.match("fail");
	g.match("fail");
	EXPECT_FALSE(g.match("limit"));
}

TEST(GuesserTest, noPW){
	Guesser g("");
	EXPECT_TRUE(g.match(""));
}

TEST(GuesserTest, remaining){
        Guesser g("fire");
	g.match("nope");
	g.match("nah");
	ASSERT_EQ( g.remaining(), 1);
}

TEST(GuesserTest, distance){
        Guesser g("farfaraway");
        g.match("farfarawaY");
	g.match("notevenclose");
	g.match("FARfaraway");
	EXPECT_TRUE(g.match("farfaraway"));
}//there might be a bug as match checks if distance is >2 and it locks if it is

TEST(GuesserTest, distance1){
        Guesser g("minecraft");
	g.match("Minecraft");
        EXPECT_TRUE(g.match("minecraft"));
}

TEST(GuesserTest, distance2){
        Guesser g("shouldfail");
	g.match("shouldFAil");
        EXPECT_FALSE(g.match("shouldfail"));
}//there is bug/error/unintended 

TEST(GuesserTest, remainingOnPass){
        Guesser g("pass");
        g.match("pass");
	ASSERT_EQ(g.remaining(), 3);
}
