#include "MockRandomNumberGenerator.hxx"

#include <catch2/catch.hpp>

#include <ConsoleUserInterface.hxx>

#include <string>
#include <sstream>
#include <tuple>

using namespace std::literals::string_literals;

class ConsoleUserInterfaceTest {
public:
  std::ostringstream out;
  std::istringstream in;
  ConsoleUserInterface ui{out, in, InputPolicy::DONT_RESET};
};

TEST_CASE_METHOD(ConsoleUserInterfaceTest, "showIntro should show wanted number range", "[ui]")
{
  auto const params = GENERATE(
      std::make_tuple(1, 100, "Guess the number (between 1 and 100):\n"),
      std::make_tuple(23, 42, "Guess the number (between 23 and 42):\n"),
      std::make_tuple(-273, 100, "Guess the number (between -273 and 100):\n")
  );
  int const minValue = std::get<0>(params);
  int const maxValue = std::get<1>(params);
  std::string const message = std::get<2>(params);

  SECTION(message) {
    MockRandomNumberGenerator rng;
    REQUIRE_CALL(rng, getMinValue()).RETURN(minValue);
    REQUIRE_CALL(rng, getMaxValue()).RETURN(maxValue);

    ui.showIntro(rng);

    CHECK(message == out.str());
  }
}

TEST_CASE_METHOD(ConsoleUserInterfaceTest, "keepRunning if input is yes", "[ui]")
{
  auto const params = GENERATE(
      std::make_tuple("yes", true),
      std::make_tuple("no", false),
      std::make_tuple("1234567890", false),
      std::make_tuple("affe", false),
      std::make_tuple("@€", false)
  );
  std::string const input = std::get<0>(params);
  bool const expected = std::get<1>(params);

  SECTION(input + " => "s + (expected ? "true" : "false")) {
    in.str(input);
    CHECK(expected == ui.keepRunning());
  }
}
