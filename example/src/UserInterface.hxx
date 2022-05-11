#pragma once

#include "CheckResult.hxx"

struct RandomNumberGenerator;

struct UserInterface {
  virtual ~UserInterface() noexcept = default;

  virtual int requestGuess(int tries) = 0;

  virtual bool keepRunning() = 0;

  virtual void showIntro(RandomNumberGenerator const& rng) = 0;

  virtual void showResult(int number, int tries, CheckResult result) = 0;
};
