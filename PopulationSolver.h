#ifndef POPULATION_SOLVER_H
#define POPULATION_SOLVER_H

#include <vector>
#include <stdexcept>
#include <stdint.h>

/**
 * Helper struct which serves as a tuple that represents a
 * person's lifespan
 */
struct Lifespan
{
  int16_t birthYear; ///< The year of which the person was born
  int16_t deathYear; ///< The year of which the person has died

  /**
   * Constructor to initialize member variables for person's lifespan.
   *
   * @param birthYear The year of which the person was born
   * @param deathYear The year of which the person has died
   */
  Lifespan(int16_t birthYear, int16_t deathYear)
   : birthYear(birthYear), deathYear(deathYear)
  {}
};

/**
 * @class PopulationServer
 *
 * This class serves as a solution to the following problem:
 *
 * "Given a list of people with their birth and end years
 * (all between 1900 and 2000), find the year with the most
 * number of people alive."
 *
 * This solution is also capable of solving the problem outside
 * of the years 1900 and 2000 within the limitation of a
 * INT16_t data-type.
 *
 * No methods within this class have been designed to be
 * thread safe.
 */
class PopulationSolver
{
public:

  /**
   * Constructor which sets the initial boundaries for minimum and maximum
   * years to solve for highest population.
   *
   * parameter maxYear must be greater than or equal to parameter minYear.
   *
   * @param minYear The lowest year to test in year-to-year population count
   * @param maxYear The highest year to test in year-to-year population count
   */
  inline PopulationSolver(int16_t minYear, int16_t maxYear);

  /**
   * Method used to get the highest population year within a set year range. If
   * multiple years are tied for the highest population all years will be included
   * within the returned vector.
   *
   * All Lifespan data members must have values within minYear and maxYear given to
   * this classes constructor.
   *
   * n = number of entries within parameter lifespans
   * Time complexity: O(n)
   * Space complexity: 2n
   *
   * @param lifespans Vector which will be populated with highest
   *        population year
   * @return Vector containing year(s) with highest population
   */
  std::vector<int16_t> getHighestPopulationYear(
                   const std::vector<Lifespan>& lifespans) const;

  /**
   * Sets the minimum year which serves as a boundary for calculating the
   * highest population year.
   *
   * @param year The minimum year boundary
   */
  inline void setMinimumYear(int16_t year);

  /**
   * Sets the maximum year which serves as a boundary for calculating the
   * highest population year.
   *
   * @param year The maximum year boundary
   */
  inline void setMaximumYear(int16_t year);

  /**
   * Gets the minimum year which serves as a boundary for calculating the
   * highest population year.
   *
   * @return The minimum year boundary
   */
  inline int16_t getMinimumYear(void) const;

  /**
   * Gets the maximum year which serves as a boundary for calculating the
   * highest population year.
   *
   * @return The maximum year boundary
   */
  inline int16_t getMaximumYear(void) const;

private:

  // Unsupported methods
  PopulationSolver(const PopulationSolver& other);
  PopulationSolver& operator=(const PopulationSolver& other);

  // Data members
  int16_t mMinYear; ///< The minimum year boundary
  int16_t mMaxYear; ///< The maximum year boundary
};

inline PopulationSolver::PopulationSolver(int16_t minYear, int16_t maxYear)
 : mMinYear(minYear), mMaxYear(maxYear)
{
  if(mMinYear > mMaxYear)
  {
    throw std::runtime_error("Minimum year is greater than maximum year");
  }
}

inline void PopulationSolver::setMinimumYear(int16_t year)
{
  mMinYear = year;
}

inline void PopulationSolver::setMaximumYear(int16_t year)
{
  mMaxYear = year;
}

inline int16_t PopulationSolver::getMinimumYear(void) const
{
  return mMinYear;
}

inline int16_t PopulationSolver::getMaximumYear(void) const
{
  return mMaxYear;
}

#endif /* POPULATION_SOLVER_H */
