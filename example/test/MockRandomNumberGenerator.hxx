#pragma once

#include <catch2/catch.hpp>
#include <catch2/trompeloeil.hpp>

#include "RandomNumberGenerator.hxx"

struct MockRandomNumberGenerator final : RandomNumberGenerator {
  MAKE_MOCK0 (getNextNumber, int(), override);
  MAKE_CONST_MOCK0 (getMinValue, int(), override);
  MAKE_CONST_MOCK0 (getMaxValue, int(), override);
};
