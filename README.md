# PopulationSolver

My requested solution for the problem: 

"Given a list of people with their birth and end years (all between 1900 and 
2000), find the year with the most number of people alive."

For this I created a class with the capabilities of also solving the problem
for other year ranges as well. I then created a series of CxxTest tests to test my
code in many various scenarios to make sure they were properly handled. All of 
the 6 test cases passed. This solution runs in linear time with linear space
complexity. 

The output is not very useful since the demonstration is in the unit tests, but
if your interested the output of the test is as follows:

"Running cxxtest tests (6 tests)......OK!"

The requirements to run this yourself include having CxxTest installed from
"https://sourceforge.net/projects/cxxtest/?source=navbar". I used version 4.4.
This does not require the newer C++11 capabilities and sould run on many older
g++ compilers just fine. 

example building of the tests:

$ python <cxxtestgen_location> --error-printer -o test.cpp PopulationSolverTest.h
$ g++ -I <cxxtest_dir> -o test test.cpp PopulationSolver.cpp