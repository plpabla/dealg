#include "test_helpers.h"

void CompareStringParts(std::string expected, const Canvas c, int col, int row, std::string extra_msg)
{
    std::string part = c.canvas[row].substr(col, expected.length());
    ASSERT_TRUE(expected == part) 
        << expected << " != " << part << std::endl 
        << "[" << c.canvas[row] << "]" 
        << " (row " <<row << ", " << extra_msg << ")" << std::endl;
}