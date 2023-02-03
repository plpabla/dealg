#pragma once

#include <gtest/gtest.h>
#include <string>
#include "../Canvas.h"

void CompareStringParts(std::string expected, const Canvas c, int col, int row, std::string extra_msg="");