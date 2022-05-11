#pragma once

#include <random>

#include "RandomNumberGenerator.hxx"

class StdRandomNumberGenerator final : public RandomNumberGenerator {
public:
  constexpr static int const MIN_VALUE = 1;
  constexpr static int const MAX_VALUE = 100;

  int getNextNumber() override;

  int getMinValue() const override;

  int getMaxValue() const override;

private:
  std::random_device rd;
  std::mt19937 generator{rd()};
  std::uniform_int_distribution<> dist{MIN_VALUE, MAX_VALUE};
};
