#include <assert.h>
#include <iostream>
using namespace std;

bool TemperatureIsOk(float temperature) {
  return (temperature >= 0 && temperature <= 45);
}

bool SocIsOk(float soc) {
  return (soc >= 20 && soc <= 80);
}

bool ChargeRateIsOk(float chargeRate) {
  return (chargeRate <= 0.8);
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  if(!TemperatureIsOk(temperature)) {
    cout << "Temperature out of range!\n";
    return false;
  }
  if(!SocIsOk(soc)) {
    cout << "State of Charge out of range!\n";
    return false;
  }
  if(!ChargeRateIsOk(chargeRate)) {
    cout << "Charge Rate out of range!\n";
    return false;
  }
  return true;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
}
