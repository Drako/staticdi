#pragma once

#ifdef BUILD_TEST

#include <catch2/catch.hpp>

#endif // BUILD_TEST

enum class CheckResult {
  Equal,
  Less,
  Greater
};

#ifdef BUILD_TEST

CATCH_REGISTER_ENUM(CheckResult, CheckResult::Equal, CheckResult::Less, CheckResult::Greater)

#endif // BUILD_TEST
