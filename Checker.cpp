#include <cassert>
#include <iostream>
#include <string>
using namespace std;

class Battery {
public:
    bool batteryIsOk(float temperature, float soc, float chargeRate);

private:
    static constexpr float kMinTemperature = 0.0f;
    static constexpr float kMaxTemperature = 45.0f;
    static constexpr float kMinSoc = 20.0f;
    static constexpr float kMaxSoc = 80.0f;
    static constexpr float kMaxChargeRate = 0.8f;
    static constexpr float kTolerancePercentage = 0.05f;

    bool TemperatureIsOk(float temperature);
    bool SocIsOk(float soc);
    bool ChargeRateIsOk(float chargeRate);
    bool batteryState(bool isTemperatureOk, bool isSocOk, bool isChargeRateOk);
    void printError(const string& parameter, bool isOk);
    void printWarning(const string& parameter, float value, float min, float max);
};

bool Battery::TemperatureIsOk(float temperature) {
    bool isOk = (temperature >= kMinTemperature && temperature <= kMaxTemperature);
    if (isOk) {
        printWarning("Temperature", temperature, kMinTemperature, kMaxTemperature);
    }
    return isOk;
}

bool Battery::SocIsOk(float soc) {
    bool isOk = (soc >= kMinSoc && soc <= kMaxSoc);
    if (isOk) {
        printWarning("State of Charge", soc, kMinSoc, kMaxSoc);
    }
    return isOk;
}

bool Battery::ChargeRateIsOk(float chargeRate) {
    bool isOk = (chargeRate <= kMaxChargeRate);
    if (isOk) {
        printWarning("Charge Rate", chargeRate, 0.0f, kMaxChargeRate);
    }
    return isOk;
}

bool Battery::batteryState(bool isTemperatureOk, bool isSocOk, bool isChargeRateOk) {
    return (isTemperatureOk && isSocOk && isChargeRateOk);
}

void Battery::printError(const string& parameter, bool isOk) {
    if (!isOk) {
        cout << parameter << " out of range!\n";
    }
}

void Battery::printWarning(const string& parameter, float value, float min, float max) {
    float lowerWarningThreshold = min + (max * kTolerancePercentage);
    float upperWarningThreshold = max - (max * kTolerancePercentage);

    if (value <= lowerWarningThreshold) {
        cout << "Warning: " << parameter << " approaching lower limit!\n";
    } else if (value >= upperWarningThreshold) {
        cout << "Warning: " << parameter << " approaching upper limit!\n";
    }
}

bool Battery::batteryIsOk(float temperature, float soc, float chargeRate) {
    bool isTemperatureOk = TemperatureIsOk(temperature);
    bool isSocOk = SocIsOk(soc);
    bool isChargeRateOk = ChargeRateIsOk(chargeRate);

    printError("Temperature", isTemperatureOk);
    printError("State of Charge", isSocOk);
    printError("Charge Rate", isChargeRateOk);

    return batteryState(isTemperatureOk, isSocOk, isChargeRateOk);
}

void runTests() {
    Battery battery;

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
}

int main() {
    runTests();
    cout << "All tests passed!" << endl;
    return 0;
}
