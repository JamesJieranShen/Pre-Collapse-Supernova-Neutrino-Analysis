#ifndef __CREATEFILE_H_INCLUDED__
#define __CREATEFILE_H_INCLUDED__

#define _USE_MATH_DEFINES
// load C++ standard libraries
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <stdio.h>

// load local libraries
#include "../include/katoRead.h"
/* TO DO ************************

   - calculate fluences from fluxes, and change this in the writing process
      -> probably multiply by one year

********************************/

void createGlobesFile(const sndata &data, const std::string & writePath,const int timeBinNum,const double timeLow, const double timeUp);

#endif