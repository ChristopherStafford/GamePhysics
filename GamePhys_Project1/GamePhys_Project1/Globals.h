#ifndef GLOBALS_H
#define GLOBALS_H


#include <string>
#include <vector>
using namespace std;

//extern string g_ApplicationName;

extern bool forwardDown;
extern bool backwardDown;
extern bool leftDown;
extern bool rightDown;
extern bool showDebug;
extern bool resetSim;

extern vector<bool> numPressed;

extern double deltaTime;
extern double timeSinceLaunch;

#endif