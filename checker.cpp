#include <assert.h>
#include <iostream>
using namespace std;

const float TEMPERATURE_MIN_THRESHOLD = 0.0F;
const float TEMPERATURE_MAX_THRESHOLD = 45.0F;

const float SOC_MIN_THRESHOLD = 20.0F;
const float SOC_MAX_THRESHOLD = 80.0F;

const float CHARGERATE_MIN_THRESHOLD = 0.0F;
const float CHARGERATE_MAX_THRESHOLD = 0.8F;

//return value  0 - for value in range 
//              1 - for value greater than threshold
//             -1 - for value less than threshold
int checkValueInRange(const float minThreshold,const float maxThreshold,const float valueToCheck)
{
  if (valueToCheck < minThreshold)
  {
    return -1;
  }
  else if ( valueToCheck > maxThreshold)
  {
    return 1;
  }
  return 0;
}

bool checkBatteryFactorStatus(const float minThreshold,const float maxThreshold,const float valueOfFactor,const char* factorname)
{
  int factorIndicator = checkValueInRange(minThreshold,maxThreshold,valueOfFactor);
  bool result = false ;
  switch(factorIndicator)
  {
    case 0 : result = true;
             break;
    case 1 : cout << factorname <<" : value : " << valueOfFactor << " is greater than the Maximum threshhold value " << maxThreshold <<endl;
             result = false;
             break;
    case -1 : cout << factorname <<" : value : " << valueOfFactor << " is less than the Manimum threshhold value " << minThreshold <<endl;
             result = false;
             break;
  }
  return result;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  bool temperatureIndicator = false,socIndicator = false,chargeRateIndicator = false ,result =false;
  temperatureIndicator = checkBatteryFactorStatus(TEMPERATURE_MIN_THRESHOLD,TEMPERATURE_MAX_THRESHOLD,temperature,"temperature");
  socIndicator = checkBatteryFactorStatus(SOC_MIN_THRESHOLD,SOC_MAX_THRESHOLD,soc,"SOC");
  chargeRateIndicator = checkBatteryFactorStatus(CHARGERATE_MIN_THRESHOLD,CHARGERATE_MAX_THRESHOLD,chargeRate,"ChargeRate");
  
  result = temperatureIndicator && socIndicator && chargeRateIndicator;
  return result;
}

void testBatteryStatus(float temperature, float soc, float chargeRate ,bool expectedResult)
{
  assert(batteryIsOk(temperature,soc,chargeRate) == expectedResult);
}

int main() {
  testBatteryStatus(25, 70, 0.7, true);
  testBatteryStatus(50, 85, 0, false);
  testBatteryStatus(46, 40, 0.6, false);
  testBatteryStatus(-1, 30, 0.5, false);
  testBatteryStatus(40, 19, 0.6, false);
  testBatteryStatus(39, 81, 0.5, false);
  testBatteryStatus(40, 50, -0.1, false);
  testBatteryStatus(40, 50, 0.9, false);
  testBatteryStatus(0, 20, 0, true);
  testBatteryStatus(45, 80, 0.8, true);
}
