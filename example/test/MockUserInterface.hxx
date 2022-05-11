#pragma once

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include <UserInterface.hxx>
#include <RandomNumberGenerator.hxx>

struct MockUserInterface final : UserInterface {
  MAKE_MOCK1 (requestGuess, int(int), override);
  MAKE_MOCK0 (keepRunning, bool(), override);
  MAKE_MOCK1 (showIntro, void(RandomNumberGenerator const&), override);
  MAKE_MOCK3 (showResult, void(int, int, CheckResult), override);
};
