#include "ConsoleUserInterface.hxx"

#include <iostream>
#include <string>

ConsoleUserInterface::ConsoleUserInterface(
    std::ostream& out, std::istream& in,
    InputPolicy inputPolicy
)
    :out{out}, in{in}, inputPolicy{inputPolicy}
{
}

bool ConsoleUserInterface::keepRunning()
{
  out << "Play again? (yes/no)\n";
  std::string response;
  resetInput();
  while (response.empty()) {
    std::getline(in, response);
  }

  return response == "yes";
}

int ConsoleUserInterface::requestGuess(int tries)
{
  int guess;
  do {
    out << "Guess #" << tries << ": ";
    resetInput();
  }
  while (!(in >> guess));
  return guess;
}

void ConsoleUserInterface::showIntro(RandomNumberGenerator const& rng)
{
  out << "Guess the number (between "
      << rng.getMinValue() << " and " << rng.getMaxValue() << "):\n";
}

void ConsoleUserInterface::showResult(int const number, int const tries, CheckResult const result)
{
  switch (result) {
  case CheckResult::Equal:
    out << "Congratulations, you found the number "
        << number << " after " << tries << " tries.\n";
    break;
  case CheckResult::Greater:
    out << "The searched number is greater than your guess.\n";
    break;
  case CheckResult::Less:
    out << "The searched number is less than your guess.\n";
    break;
  }
}

void ConsoleUserInterface::resetInput()
{
  if (inputPolicy == InputPolicy::RESET) {
    in.clear();
    in.ignore(in.rdbuf()->in_avail());
  }
}
