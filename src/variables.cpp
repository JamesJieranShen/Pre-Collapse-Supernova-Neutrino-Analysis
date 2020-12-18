#include "variables.h"

katoWidth = 0.05; // [MeV] step width of simulation results
double snowWidth = 0.2;  // [MeV] step width expected by SNOwGLoBES

double parsec = 3.0857 * pow(10,16); //one parsec is approximately 3.0857e16 meters
double distance = 200;  // assuming a distance of 200 parsec to the SN
double surface =  4 * M_PI * pow( (distance * parsec), 2);
double solidAngle = pow( 0.01,2) / surface; // square meter to square cm