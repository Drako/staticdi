#include "StdRandomNumberGenerator.hxx"

int StdRandomNumberGenerator::getNextNumber()
{
  return dist(generator);
}

int StdRandomNumberGenerator::getMinValue() const
{
  return MIN_VALUE;
}

int StdRandomNumberGenerator::getMaxValue() const
{
  return MAX_VALUE;
}
