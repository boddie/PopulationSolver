#include "PopulationSolver.h"

std::vector<int16_t> PopulationSolver::getHighestPopulationYear(
                 const std::vector<Lifespan>& lifespans) const
{
  if(lifespans.size() == 0)
  {
    throw std::runtime_error("No entries found in parameter lifespans");
  }

  std::vector<int16_t> highestYear;

  uint16_t yearSpan = (mMaxYear - mMinYear) + 1;
  int16_t populationDelta[yearSpan] = {0};

  // Populate an array with the change in population as the years progress
  for(uint16_t entry = 0; entry < lifespans.size(); ++entry)
  {
    if((lifespans.at(entry).birthYear < mMinYear)
      || (lifespans.at(entry).deathYear > mMaxYear))
    {
      throw std::runtime_error("Entry in parameter lifespans "
          "contains value out of range");
    }
    if(lifespans.at(entry).birthYear > lifespans.at(entry).deathYear)
    {
      throw std::runtime_error("Entry in parameter lifespans "
          "contains birth year > death year");
    }
    int16_t birthYear = lifespans.at(entry).birthYear - mMinYear;
    ++populationDelta[birthYear];
    int16_t deathYear = lifespans.at(entry).deathYear - mMinYear;
    --populationDelta[deathYear + 1];
  }

  // As the population changes over the years check to see if the years
  // population is the highest of all years.
  uint16_t currentPopulation = 0;
  uint16_t highestPopulation = 0;
  for(int16_t year = 0; year < yearSpan; ++year)
  {
    currentPopulation += populationDelta[year];
    if(currentPopulation > highestPopulation)
    {
      highestPopulation = currentPopulation;
      highestYear.clear();
      highestYear.push_back(year + mMinYear);
    }
    else if(currentPopulation == highestPopulation)
    {
      highestYear.push_back(year + mMinYear);
    }
  }

  return highestYear;
}
