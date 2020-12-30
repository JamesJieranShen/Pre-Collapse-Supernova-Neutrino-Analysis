#ifndef __VARIABLES_H_INCLUDED__
#define __VARIABLES_H_INCLUDED__

#include <cmath>

#define katoWidth 0.05      // [MeV] step width of simulation results
#define snowWidth 0.2       // [MeV] step width expected by SNOwGLoBES
#define snowOutFactor 0.5   // snowglobes output is per 0.5 MeV
#define parsec 3.0857e16    //one parsec is approximately 3.0857e16 meters
#define distance 200        // assuming a distance of 200 parsec to the SN
#define surface (4 * M_PI * pow( (distance * parsec), 2))
#define solidAngle pow(0.01,2) / surface // square meter to square c

#endif