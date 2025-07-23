#include <stdexcept>
using namespace std;

struct GuessResult
{
  bool solved;
  int strikes;
  int balls;
};

class Baseball
{
public:
  explicit Baseball(const string& answer)
    : answerNumber(answer)
  {
  }

  GuessResult guess(const string& guessNumber)
  {
    assertIllegalArgument(guessNumber);

    int strike = countStrike(guessNumber);
    if (strike == 3)
    {
      return { true, strike, 0 };
    }

    return { false, strike, countball(guessNumber)};
  }

  int countStrike(const std::string& guessNumber)
  {
    int strike = 0;
    for (int i = 0; i < 3; i++)
    {
      if (guessNumber[i] == answerNumber[i])
      {
        strike++;
      }
    }

    return strike;
  }

  int countball(const std::string& guessNumber)
  {
    int ball = 0;
    for (int i = 0; i < 3; i++)
    {
      for (int j = 0; j < 3; j++)
      {
        if (i == j) continue;
        if (guessNumber[i] == answerNumber[j])
        {
          ball++;
        }
      }
    }

    return ball;
  }

  // Illegal Case
  void assertIllegalArgument(const std::string& guessNumber)
  {
    if (guessNumber.length() != 3)
    {
      throw length_error("Must be three letters.");
    }

    for (char ch : guessNumber)
    {
      if (ch >= '0' && ch <= '9') continue;
      throw invalid_argument("Must be number");
    }

    if (isDuplicatedNumber(guessNumber))
    {
      throw invalid_argument("Must not have the same number.");
    }
  }
  bool isDuplicatedNumber(const std::string& guessNumber)
  {
    return guessNumber[0] == guessNumber[1]
      || guessNumber[0] == guessNumber[2]
      || guessNumber[1] == guessNumber[2];
  }

private:
  string answerNumber;
};