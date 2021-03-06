#include <iostream>
#include "exception/exception.h"
#include "test/test.h"

// add new tests below
#define TESTS( BEFORE, AFTER) \
BEFORE cppmake_test_executor AFTER \
// add new tests here

TESTS(__declspec(dllimport) void, (std::ostream& os, int& count);)

static void print_failed_count(std::ostream& os, int count)
{
    if (count == 1)
    {
        std::cout << "1 test failed" << std::endl;
    }
    else
    {
        std::cout << count << " tests failed" << std::endl;
    }
}

int main()
{
    int count = 0;
    try
    {
        std::cout << "Test" << std::endl;
        TESTS((void), (std::cout, count);) // expands to calling all tests
        if (count)
        {
            print_failed_count(std::cout, count);
            return -1;
        }
        else
        {
            std::cout << "====== Tests: succeeded ===============================================" << std::endl;
            return 0;
        }
    }
    catch (test::error_t const& e)
    {
        std::cout << e.what() << std::endl;
        print_failed_count(std::cout, ++count);
        return -2;
    }
    catch (std::exception const& e)
    {
        std::cout << FILE_LINE(exception) << "Unexpected exception: " << e.what() << std::endl;
        print_failed_count(std::cout, ++count);
        return -3;
    }
    catch (...)
    {
        std::cout << FILE_LINE(exception) << "Unexpeted non-standard exception" << std::endl;
        print_failed_count(std::cout, ++count);
        return -4;
    }
}