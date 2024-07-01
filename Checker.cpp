#include <cassert>
#include <iostream>
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

    bool TemperatureIsOk(float temperature);
    bool SocIsOk(float soc);
    bool ChargeRateIsOk(float chargeRate);
    bool batteryState(bool isTemperatureOk, bool isSocOk, bool isChargeRateOk);
    void printError(const string& parameter, bool isOk);
};

bool Battery::TemperatureIsOk(float temperature) {
    return (temperature >= kMinTemperature && temperature <= kMaxTemperature);
}

bool Battery::SocIsOk(float soc) {
    return (soc >= kMinSoc && soc <= kMaxSoc);
}

bool Battery::ChargeRateIsOk(float chargeRate) {
    return (chargeRate <= kMaxChargeRate);
}

bool Battery::batteryState(bool isTemperatureOk, bool isSocOk, bool isChargeRateOk) {
    return (isTemperatureOk && isSocOk && isChargeRateOk);
}

void Battery::printError(const string& parameter, bool isOk) {
    if (!isOk) {
        cout << parameter << " out of range!\n";
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
}

int main() {
    runTests();
    cout << "All tests passed!" << endl;
    return 0;
}
