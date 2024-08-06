// ParameterCheck.cpp
#include "ParameterCheck.hpp"

bool isParameterOk(float value, const ParameterLimits& limits) {
    return value >= limits.min && value <= limits.max;
}

std::string getLowMessage(float value, const ParameterLimits& limits) {
    if (value < limits.min) return limits.lowBreachMessage;
    if (value < limits.min + limits.warningThreshold) return limits.lowWarningMessage;
    return "";
}

std::string getHighMessage(float value, const ParameterLimits& limits) {
    if (value > limits.max) return limits.highBreachMessage;
    if (value > limits.max - limits.warningThreshold) return limits.highWarningMessage;
    return "";
}

std::string getParameterMessage(float value, const ParameterLimits& limits) {
    std::string lowMessage = getLowMessage(value, limits);
    if (!lowMessage.empty()) return lowMessage;

    std::string highMessage = getHighMessage(value, limits);
    if (!highMessage.empty()) return highMessage;

    return limits.normalMessage;
}
