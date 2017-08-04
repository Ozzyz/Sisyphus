#pragma once

#define DllExport   __declspec(dllexport)
#define DllImport __declspec(dllimport)

//#include "board.h" Remove because of circular dependency
#include "utils.h"
#include "board.h"
#include <string>
#include <vector>
using std::string;
DllExport void parse_fen(string, Board&);

