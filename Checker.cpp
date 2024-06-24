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

bool batteryState(bool isTemperatureOk, bool isSocOk, bool isChargeRateOk){
  return (isTemperatureOk && isSocOk && isChargeRateOk);
}

void tempError (bool isTemperatureOk) {
  if(!isTemperatureOk) {
    cout << "Temperature out of range!\n";
  }
}

void socError(bool isSocOk){
  if(!isSocOk) {
    cout << "State of Charge out of range!\n";
  } 
}

void chargeRateError( bool isChargeRateOk){
  if(!isChargeRateOk) {
    cout << "Charge Rate out of range!\n";
  } 
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  bool isTemperatureOk = TemperatureIsOk(temperature);
  bool isSocOk = SocIsOk(soc);
  bool isChargeRateOk = ChargeRateIsOk(chargeRate);
  tempError(isTemperatureOk);
  socError(isSocOk);
  chargeRateError(isChargeRateOk);

  bool stateOfBattery = batteryState(isTemperatureOk, isSocOk, isChargeRateOk);
  return stateOfBattery;
}


int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
}
