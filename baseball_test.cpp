#include "gmock/gmock.h"
#include "baseball.cpp"
#include "baseball_test.h"

class BaseballFixture : public testing::Test
{
public:
  Baseball game{"123"};
  void assertIllegalArgument(string guessNumber)
  {
    try
    {
      game.guess(guessNumber);
      FAIL();
    }
    catch (exception e)
    {
      // PASS
    }
  }

  void CheckAnswer(const string guessNumber, int solved, int answerStrikes, int answerBalls)
  {
    GuessResult result = game.guess(guessNumber);

    EXPECT_TRUE(result.solved == solved);
    EXPECT_EQ(answerStrikes, result.strikes);
    EXPECT_EQ(answerBalls, result.balls);
  }
};

TEST_F(BaseballFixture, ThrowExceptionWhenInvalidCase)
{
  assertIllegalArgument("12");
  assertIllegalArgument("12s");
  assertIllegalArgument("121");
}

TEST_F(BaseballFixture, ReturnSolvedResultIfMatchNumber)
{
  CheckAnswer("123", true, 3, 0);
}

TEST_F(BaseballFixture, ReturnSolvedResultIf2S0BCase1)
{
  CheckAnswer("173", false, 2, 0);
}

TEST_F(BaseballFixture, ReturnSolvedResultIf2S0BCase2)
{
  CheckAnswer("723", false, 2, 0);
}

TEST_F(BaseballFixture, ReturnSolvedResultIf2S0BCase3)
{
  CheckAnswer("127", false, 2, 0);
}

TEST_F(BaseballFixture, ReturnSolvedResultIf1S2BCase1)
{
  CheckAnswer("132", false, 1, 2);
}

TEST_F(BaseballFixture, ReturnSolvedResultIf1S2BCase2)
{
  CheckAnswer("213", false, 1, 2);
}

TEST_F(BaseballFixture, ReturnSolvedResultIf1S2BCase3)
{
  CheckAnswer("321", false, 1, 2);
}

int main()
{
  ::testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}