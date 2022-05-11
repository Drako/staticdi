#pragma once

#include "CheckResult.hxx"
#include "RandomNumberGenerator.hxx"
#include "UserInterface.hxx"

#include <sdi/component.hxx>

/**
 * Main class of the guess the number game.
 */
class GuessTheNumber {
public:
  using dependencies = sdi::dependencies<RandomNumberGenerator, UserInterface>;

  GuessTheNumber(
      RandomNumberGenerator& rng,
      UserInterface& ui
  );

  void run();

  void playSingleGame();

  static CheckResult checkGuess(int guess, int number);

private:
  RandomNumberGenerator& rng;
  UserInterface& ui;
};
