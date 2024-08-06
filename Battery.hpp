// Battery.hpp
#ifndef BATTERY_HPP
#define BATTERY_HPP

#include <string>

struct ParameterLimits {
    float min;
    float max;
    float warningThreshold;
    std::string lowBreachMessage;
    std::string lowWarningMessage;
    std::string normalMessage;
    std::string highWarningMessage;
    std::string highBreachMessage;
};

class Battery {
public:
    Battery();
    bool batteryIsOk(float temperature, float soc, float chargeRate);

private:
    ParameterLimits temperatureLimits;
    ParameterLimits socLimits;
    ParameterLimits chargeRateLimits;
};

#endif // BATTERY_HPP
