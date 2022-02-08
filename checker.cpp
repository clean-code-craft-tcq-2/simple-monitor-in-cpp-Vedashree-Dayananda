#include <assert.h>
#include <iostream>
using namespace std;

const float TEMPERATURE_MIN_THRESHOLD = 0.0F;
const float TEMPERATURE_MAX_THRESHOLD = 45.0F;

const float SOC_MIN_THRESHOLD = 20.0F;
const float SOC_MAX_THRESHOLD = 80.0F;

const float CHARGERATE_MIN_THRESHOLD = 0.0F;
const float CHARGERATE_MAX_THRESHOLD = 0.8F;

bool valueInRange(const float minThreshold,const float maxThreshold,const float valueToCheck)
{
  if (valueToCheck < minThreshold)
  {
    cout << valueToCheck << "is less than Minimum Threshold value" << minThreshold <<endl;
    return false;
  }
  else if ( valueToCheck > minThreshold)
  {
    cout << valueToCheck << "is greater than Maximum Threshold value" << maxThreshold <<endl;
    return false;
  }
  return true;
}


bool batteryIsOk(float temperature, float soc, float chargeRate) {
  bool temperatureIndicator = false,socIndicator = false,chargeRateIndicator = false ,result =false;
  temperatureIndicator = valueInRange(TEMPERATURE_MIN_THRESHOLD,TEMPERATURE_MAX_THRESHOLD,temperature);
  socIndicator = valueInRange(SOC_MIN_THRESHOLD,SOC_MAX_THRESHOLD,soc);
  chargeRateIndicator = valueInRange(CHARGERATE_MIN_THRESHOLD,CHARGERATE_MAX_THRESHOLD,chargeRate);
  
  result = temperatureIndicator && socIndicator && chargeRateIndicator;
  return result;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
}
