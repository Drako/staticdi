#include "GuessTheNumber.hxx"

#include <iostream>
#include <string>

GuessTheNumber::GuessTheNumber(
    RandomNumberGenerator& rng,
    UserInterface& ui
)
    :rng{rng}, ui{ui}
{
}

void GuessTheNumber::run()
{
  do {
    playSingleGame();
  }
  while (ui.keepRunning());
}

void GuessTheNumber::playSingleGame()
{
  ui.showIntro(rng);

  int const number = rng.getNextNumber();
  int tries = 0;

  for (;;) {
    ++tries;

    int const guess = ui.requestGuess(tries);

    CheckResult const result = checkGuess(guess, number);
    ui.showResult(number, tries, result);
    if (result == CheckResult::Equal) break;
  }
}

CheckResult GuessTheNumber::checkGuess(int const guess, int const number)
{
  return
      guess == number ? CheckResult::Equal :
      guess < number ? CheckResult::Greater :
      CheckResult::Less;
}
