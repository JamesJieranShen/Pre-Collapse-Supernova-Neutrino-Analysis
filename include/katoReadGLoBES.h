#ifndef __KATOREADGLOBES_H_INCLUDED__
#define __KATOREADGLOBES_H_INCLUDED__

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <sstream>

#include "spectrumRead.h"
#include "katoRead.h"

sndata katoReadGLoBES(const std::string & globesfile_path, const std::string & path, const std::string & option);

#endif
