#include <cassert>
#include <iostream>
#include <string>
using namespace std;

struct ParameterLimits {
    float min;
    float max;
    float warningThreshold;
    string lowBreachMessage;
    string lowWarningMessage;
    string normalMessage;
    string highWarningMessage;
    string highBreachMessage;
};

class Battery {
public:
    bool batteryIsOk(float temperature, float soc, float chargeRate);

private:
    static constexpr float kMinTemperature = 0.0f;
    static constexpr float kMaxTemperature = 45.0f;
    static constexpr float kMinSoc = 20.0f;
    static constexpr float kMaxSoc = 80.0f;
    static constexpr float kMaxChargeRate = 0.8f;

    static constexpr float kTemperatureWarningThreshold = kMaxTemperature * 0.05f;
    static constexpr float kSocWarningThreshold = kMaxSoc * 0.05f;
    static constexpr float kChargeRateWarningThreshold = kMaxChargeRate * 0.05f;

    ParameterLimits temperatureLimits {
        kMinTemperature, kMaxTemperature, kTemperatureWarningThreshold, 
        "Temperature too low!", "Temperature approaching low limit!", "Temperature is normal.", 
        "Temperature approaching high limit!", "Temperature too high!"
    };

    ParameterLimits socLimits {
        kMinSoc, kMaxSoc, kSocWarningThreshold, 
        "SOC too low!", "SOC approaching low limit!", "SOC is normal.", 
        "SOC approaching high limit!", "SOC too high!"
    };

    ParameterLimits chargeRateLimits {
        0.0f, kMaxChargeRate, kChargeRateWarningThreshold, 
        "Charge rate too high!", "", "Charge rate is normal.", 
        "Charge rate approaching high limit!", "Charge rate too high!"
    };

    bool isParameterOk(float value, const ParameterLimits& limits);
    string getParameterMessage(float value, const ParameterLimits& limits);
    string getLowMessage(float value, const ParameterLimits& limits);
    string getHighMessage(float value, const ParameterLimits& limits);
};

bool Battery::isParameterOk(float value, const ParameterLimits& limits) {
    return value >= limits.min && value <= limits.max;
}

string Battery::getLowMessage(float value, const ParameterLimits& limits) {
    if (value < limits.min) return limits.lowBreachMessage;
    if (value < limits.min + limits.warningThreshold) return limits.lowWarningMessage;
    return "";
}

string Battery::getHighMessage(float value, const ParameterLimits& limits) {
    if (value > limits.max) return limits.highBreachMessage;
    if (value > limits.max - limits.warningThreshold) return limits.highWarningMessage;
    return "";
}

string Battery::getParameterMessage(float value, const ParameterLimits& limits) {
    string lowMessage = getLowMessage(value, limits);
    if (!lowMessage.empty()) return lowMessage;

    string highMessage = getHighMessage(value, limits);
    if (!highMessage.empty()) return highMessage;

    return limits.normalMessage;
}

bool Battery::batteryIsOk(float temperature, float soc, float chargeRate) {
    bool isTemperatureOk = isParameterOk(temperature, temperatureLimits);
    bool isSocOk = isParameterOk(soc, socLimits);
    bool isChargeRateOk = isParameterOk(chargeRate, chargeRateLimits);

    cout << getParameterMessage(temperature, temperatureLimits) << endl;
    cout << getParameterMessage(soc, socLimits) << endl;
    cout << getParameterMessage(chargeRate, chargeRateLimits) << endl;

    return isTemperatureOk && isSocOk && isChargeRateOk;
}

void runTests() {
    Battery battery;

    // Failing test for low SOC warning
    assert(battery.batteryIsOk(25, 21, 0.7) == true);  // Should print "SOC approaching low limit!"

    // Valid case
    assert(battery.batteryIsOk(25, 70, 0.7) == true);

    // Temperature tests
    assert(battery.batteryIsOk(-1, 70, 0.7) == false);
    assert(battery.batteryIsOk(46, 70, 0.7) == false);

    // SOC tests
    assert(battery.batteryIsOk(25, 19, 0.7) == false);
    assert(battery.batteryIsOk(25, 81, 0.7) == false);

    // Charge rate tests
    assert(battery.batteryIsOk(25, 70, 0.9) == false);

    // Combined tests
    assert(battery.batteryIsOk(0, 20, 0.8) == true);
    assert(battery.batteryIsOk(45, 80, 0.8) == true);
    assert(battery.batteryIsOk(25, 70, 0) == true);
    assert(battery.batteryIsOk(50, 85, 1.0) == false);

    // Warning tests
    assert(battery.batteryIsOk(1, 25, 0.05) == true);
    assert(battery.batteryIsOk(44, 75, 0.75) == true);

    // Additional tests
    assert(battery.batteryIsOk(0.1f, 20.1f, 0.01f) == true);  // All within warning thresholds
    assert(battery.batteryIsOk(44.9f, 79.9f, 0.79f) == true);  // All within warning thresholds
    assert(battery.batteryIsOk(0, 80, 0.8) == true);  // Boundary values
}

int main() {
    runTests();
    cout << "All tests passed!" << endl;
    return 0;
}
