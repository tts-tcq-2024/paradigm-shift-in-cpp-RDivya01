// ParameterCheck.hpp
#ifndef PARAMETER_CHECK_HPP
#define PARAMETER_CHECK_HPP

#include "Battery.hpp"
#include <string>

bool isParameterOk(float value, const ParameterLimits& limits);
std::string getParameterMessage(float value, const ParameterLimits& limits);
std::string getLowMessage(float value, const ParameterLimits& limits);
std::string getHighMessage(float value, const ParameterLimits& limits);

#endif // PARAMETER_CHECK_HPP
