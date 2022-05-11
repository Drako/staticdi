#pragma once

struct RandomNumberGenerator {
  virtual ~RandomNumberGenerator() noexcept = default;

  virtual int getNextNumber() = 0;

  virtual int getMinValue() const = 0;

  virtual int getMaxValue() const = 0;
};
