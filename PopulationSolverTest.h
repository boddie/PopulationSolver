#include <cxxtest/TestSuite.h>
#include <vector>
#include <stdint.h>
#include "PopulationSolver.h"

class PopulationSolverTest : public CxxTest::TestSuite
{
public:

  // Cxx test for PopulationSolver(int16_t minYear, int16_t maxYear)
  void testPopulationSolver(void)
  {
    // Test with valid parameters 1900 and 2000
    {
      PopulationSolver solver(1900, 2000);
      TS_ASSERT_EQUALS(solver.getMinimumYear(), 1900);
      TS_ASSERT_EQUALS(solver.getMaximumYear(), 2000);
    }

    // test with valid equivalent parameters
    {
      PopulationSolver solver(1900, 1900);
      TS_ASSERT_EQUALS(solver.getMinimumYear(), 1900);
      TS_ASSERT_EQUALS(solver.getMaximumYear(), 1900);
    }

    // test with invalid parameters (minimum > maximum)
    {
      try
      {
        PopulationSolver solver(2000, 1900);
        // This next line should not be reached so if
        // it does the test will fail
        TS_ASSERT(false);
      }
      catch (const std::runtime_error& e)
      {
        TS_ASSERT_EQUALS(e.what(), "Minimum year is greater"
             " than or equal to maximum year");
      }
    }
    
    // test with invalid parameters (minimum == maximum)
    {
      try
      {
        PopulationSolver solver(1900, 1900);
        // This next line should not be reached so if
        // it does the test will fail
        TS_ASSERT(false);
      }
      catch (const std::runtime_error& e)
      {
        TS_ASSERT_EQUALS(e.what(), "Minimum year is greater"
             " than or equal to maximum year");
      }
    }
  }

  // Cxx test for const std::vector<int16_t>& getHighestPopulationYear(
  //                      const std::vector<Lifespan>& lifespans) const
  void testGetHighestPopulationYear(void)
  {
    // Test correct error is thrown when no entries in passed in vector
    {
      try
      {
        PopulationSolver solver(1900, 2000);
        std::vector<Lifespan> emptyList;
        std::vector<int16_t> result 
             = solver.getHighestPopulationYear(emptyList);
        // This next line should not be reached so if
        // it does the test will fail
        TS_ASSERT(false);
      }
      catch (const std::runtime_error& e)
      {
        TS_ASSERT_EQUALS(e.what(), "No entries found in parameter lifespans");
      }
    }

    // Test correct error is thrown when passed in vector contains
    // data that is out of range
    {
      // Test birth year out of range
      try
      {
        PopulationSolver solver(1900, 2000);
        Lifespan lifespan1(1903, 1974);
        Lifespan lifespan2(1804, 1935); // Invalid entry
        Lifespan lifespan3(1920, 1999);
        std::vector<Lifespan> rangedList;
        rangedList.push_back(lifespan1);
        rangedList.push_back(lifespan2);
        rangedList.push_back(lifespan3);
        std::vector<int16_t> result 
             = solver.getHighestPopulationYear(rangedList);
        // This next line should not be reached so if
        // it does the test will fail
        TS_ASSERT(false);
      }
      catch (const std::runtime_error& e)
      {
        TS_ASSERT_EQUALS(e.what(), "Entry in parameter lifespans "
             "contains value out of range");
      }
      
      // Test death year out of range
      try
      {
        PopulationSolver solver(1900, 2000);
        Lifespan lifespan1(1903, 1974);
        Lifespan lifespan2(1974, 2006); // Invalid entry
        Lifespan lifespan3(1920, 1999);
        std::vector<Lifespan> rangedList;
        rangedList.push_back(lifespan1);
        rangedList.push_back(lifespan2);
        rangedList.push_back(lifespan3);
        std::vector<int16_t> result 
             = solver.getHighestPopulationYear(rangedList);
        // This next line should not be reached so if
        // it does the test will fail
        TS_ASSERT(false);
      }
      catch (const std::runtime_error& e)
      {
        TS_ASSERT_EQUALS(e.what(), "Entry in parameter lifespans "
             "contains value out of range");
      }
    }
    
    // Test correct error is thrown when passed in vector contains
    // a birth year > death year
    {
      try
      {
        PopulationSolver solver(1900, 2000);
        Lifespan lifespan1(1903, 1974);
        Lifespan lifespan2(1981, 1922); // Invalid entry
        Lifespan lifespan3(1920, 1999);
        std::vector<Lifespan> rangedList;
        rangedList.push_back(lifespan1);
        rangedList.push_back(lifespan2);
        rangedList.push_back(lifespan3);
        std::vector<int16_t> result 
             = solver.getHighestPopulationYear(rangedList);
        // This next line should not be reached so if
        // it does the test will fail
        TS_ASSERT(false);
      }
      catch (const std::runtime_error& e)
      {
        TS_ASSERT_EQUALS(e.what(), "Entry in parameter lifespans "
          "contains birth year > death year");
      }
    }

    // Test successful operation with valid different values and
    // single highest population year (1965)
    {
      PopulationSolver solver(1900, 2000);
      Lifespan lifespan1(1903, 1974);
      Lifespan lifespan2(1922, 1984);
      Lifespan lifespan3(1920, 2000);
      Lifespan lifespan4(1965, 1978);
      Lifespan lifespan5(1942, 1965);
      std::vector<Lifespan> rangedList;
      rangedList.push_back(lifespan1);
      rangedList.push_back(lifespan2);
      rangedList.push_back(lifespan3);
      rangedList.push_back(lifespan4);
      rangedList.push_back(lifespan5);
      std::vector<int16_t> result 
           = solver.getHighestPopulationYear(rangedList);
      TS_ASSERT_EQUALS(result.size(), 1);
      TS_ASSERT_EQUALS(result.at(0), 1965);
    }

    // Test successful operation with valid values with several
    // ties for highest population year
    {
      PopulationSolver solver(1900, 2000);
      Lifespan lifespan1(1903, 1974);
      Lifespan lifespan2(1922, 1984);
      Lifespan lifespan3(1920, 2000);
      Lifespan lifespan4(1965, 1978);
      Lifespan lifespan5(1942, 1967);
      std::vector<Lifespan> rangedList;
      rangedList.push_back(lifespan1);
      rangedList.push_back(lifespan2);
      rangedList.push_back(lifespan3);
      rangedList.push_back(lifespan4);
      rangedList.push_back(lifespan5);
      std::vector<int16_t> result 
           = solver.getHighestPopulationYear(rangedList);
      TS_ASSERT_EQUALS(result.size(), 3);
      TS_ASSERT_EQUALS(result.at(0), 1965);
      TS_ASSERT_EQUALS(result.at(1), 1966);
      TS_ASSERT_EQUALS(result.at(2), 1967);
    }

    // Test successful operation when minimum year and maximum year
    // are both negative
    {
      PopulationSolver solver(-200, -100);
      Lifespan lifespan1(-188, -120);
      Lifespan lifespan2(-174, -150);
      Lifespan lifespan3(-150, -100);
      std::vector<Lifespan> rangedList;
      rangedList.push_back(lifespan1);
      rangedList.push_back(lifespan2);
      rangedList.push_back(lifespan3);
      std::vector<int16_t> result 
           = solver.getHighestPopulationYear(rangedList);
      TS_ASSERT_EQUALS(result.size(), 1);
      TS_ASSERT_EQUALS(result.at(0), -150);
    }

    // Test successful operation when minimum year is negative and
    // maximum year is positive
    {
      PopulationSolver solver(-50, 50);
      Lifespan lifespan1(-36, 10);
      Lifespan lifespan2(-35, 6);
      Lifespan lifespan3(5, 49);
      std::vector<Lifespan> rangedList;
      rangedList.push_back(lifespan1);
      rangedList.push_back(lifespan2);
      rangedList.push_back(lifespan3);
      std::vector<int16_t> result 
           = solver.getHighestPopulationYear(rangedList);
      TS_ASSERT_EQUALS(result.size(), 2);
      TS_ASSERT_EQUALS(result.at(0), 5);
      TS_ASSERT_EQUALS(result.at(1), 6);
    }
  }

  // Cxx test for void setMinimumYear(int16_t year)
  void testSetMinimumYear(void)
  {
    // Update the minimum year and check for correct value
    PopulationSolver solver(1900, 2000);
    solver.setMinimumYear(1950);
    TS_ASSERT_EQUALS(solver.getMinimumYear(), 1950);
  }

  // Cxx test for void setMaximumYear(int16_t year)
  void testSetMaximumYear(void)
  {
    // Update the maximum year and check for correct value
    PopulationSolver solver(1900, 2000);
    solver.setMaximumYear(2050);
    TS_ASSERT_EQUALS(solver.getMaximumYear(), 2050);
  }

  // Cxx test for int16_t getMinimumYear(void) const
  void testGetMinimumYear(void)
  {
    // Make sure correct minimum value is retrieved
    PopulationSolver solver(1900, 2000);
    TS_ASSERT_EQUALS(solver.getMinimumYear(), 1900);
  }

  // Cxx test for int16_t getMaximumYear(void) const
  void testGetMaximumYear(void)
  {
    // Make sure correct maximum value is retrieved
    PopulationSolver solver(1900, 2000);
    TS_ASSERT_EQUALS(solver.getMaximumYear(), 2000);
  }

};