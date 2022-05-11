#include "MockRandomNumberGenerator.hxx"
#include "MockUserInterface.hxx"

#include <catch2/catch.hpp>

#include <GuessTheNumber.hxx>

#include <sdi/container.hxx>

#include <array>
#include <tuple>

class GuessTheNumberTest {
  sdi::container<
      sdi::known_types<MockRandomNumberGenerator, MockUserInterface, GuessTheNumber>
  > test;

protected:
  GuessTheNumber& game = test.resolve<GuessTheNumber>();
  MockUserInterface& ui = test.resolve<MockUserInterface>();
  MockRandomNumberGenerator& rng = test.resolve<MockRandomNumberGenerator>();
};

TEST_CASE_METHOD(GuessTheNumberTest, "play a single game", "[game]")
{
  using trompeloeil::_;
  using trompeloeil::eq;

  constexpr static int const NUMBER = 23;
  constexpr static int const NUM_TRIES = 4;

  REQUIRE_CALL(ui, showIntro(ANY(RandomNumberGenerator & ))).LR_WITH(std::addressof(_1) == std::addressof(rng));

  REQUIRE_CALL(rng, getNextNumber()).RETURN(NUMBER);

  std::array<int, NUM_TRIES> const tries{50, 25, 20, 23};
  REQUIRE_CALL(ui, requestGuess(ANY(int)))
      .WITH(_1 <= NUM_TRIES)
      .TIMES(NUM_TRIES)
      .RETURN(tries[_1 - 1]);

  trompeloeil::sequence seq;
  REQUIRE_CALL(ui, showResult(NUMBER, 1, CheckResult::Less)).IN_SEQUENCE(seq);
  REQUIRE_CALL(ui, showResult(NUMBER, 2, CheckResult::Less)).IN_SEQUENCE(seq);
  REQUIRE_CALL(ui, showResult(NUMBER, 3, CheckResult::Greater)).IN_SEQUENCE(seq);
  REQUIRE_CALL(ui, showResult(NUMBER, 4, CheckResult::Equal)).IN_SEQUENCE(seq);

  game.playSingleGame();
}

TEST_CASE_METHOD(GuessTheNumberTest, "equal numbers should yield equal result", "[game]")
{
  int const number = GENERATE(range(1, 101));
  CHECK(CheckResult::Equal == game.checkGuess(number, number));
}

TEST_CASE_METHOD(GuessTheNumberTest, "number less than guess should yield less", "[game]")
{
  auto const params = GENERATE(
      std::make_tuple(23, 42),
      std::make_tuple(42, 1337)
  );
  auto const number = std::get<0>(params);
  auto const guess = std::get<1>(params);
  CHECK(CheckResult::Less == game.checkGuess(guess, number));
}

TEST_CASE_METHOD(GuessTheNumberTest, "number greater than guess should yield greater", "[game]")
{
  auto const params = GENERATE(
      std::make_tuple(23, 42),
      std::make_tuple(42, 1337)
  );
  auto const number = std::get<1>(params);
  auto const guess = std::get<0>(params);
  CHECK(CheckResult::Greater == game.checkGuess(guess, number));
}
