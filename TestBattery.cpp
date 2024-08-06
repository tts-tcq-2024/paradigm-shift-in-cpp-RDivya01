// TestBattery.cpp
#include "Battery.hpp"
#include <cassert>
#include <iostream>

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
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
