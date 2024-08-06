// Battery.cpp
#include "Battery.hpp"
#include "ParameterCheck.hpp"
#include <iostream>

Battery::Battery()
    : temperatureLimits{0.0f, 45.0f, 45.0f * 0.05f, "Temperature too low!", "Temperature approaching low limit!", "Temperature is normal.", "Temperature approaching high limit!", "Temperature too high!"},
      socLimits{20.0f, 80.0f, 80.0f * 0.05f, "SOC too low!", "SOC approaching low limit!", "SOC is normal.", "SOC approaching high limit!", "SOC too high!"},
      chargeRateLimits{0.0f, 0.8f, 0.8f * 0.05f, "Charge rate too low!", "", "Charge rate is normal.", "Charge rate approaching high limit!", "Charge rate too high!"} {}

bool Battery::batteryIsOk(float temperature, float soc, float chargeRate) {
    bool isTemperatureOk = isParameterOk(temperature, temperatureLimits);
    bool isSocOk = isParameterOk(soc, socLimits);
    bool isChargeRateOk = isParameterOk(chargeRate, chargeRateLimits);

    std::cout << getParameterMessage(temperature, temperatureLimits) << std::endl;
    std::cout << getParameterMessage(soc, socLimits) << std::endl;
    std::cout << getParameterMessage(chargeRate, chargeRateLimits) << std::endl;

    return isTemperatureOk && isSocOk && isChargeRateOk;
}
