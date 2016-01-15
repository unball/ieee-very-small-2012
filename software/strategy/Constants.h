#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Config.h>
#include <ProcessLogger.h>
#include <map>
#include <string>
#include <cstdlib>

#define CONST(x) getValueFromConstant(#x)

extern map<string, string> constants_map;
extern double goalBorder;

void initConstants();
void insertNewConstant(string constant_name, string value);
double getValueFromConstant(string constant_name);

#endif
