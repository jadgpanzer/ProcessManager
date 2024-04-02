#pragma once
#include <windows.h>  
#include <iostream>  
#include <tlhelp32.h> 
#include <iomanip>
#include <string>
#include <time.h>
#include <stdio.h>
#include <regex>
using namespace std;
#define MAX_ENUM_PROCESS_NUM 1024
static locale loc = std::locale::global(std::locale(""));