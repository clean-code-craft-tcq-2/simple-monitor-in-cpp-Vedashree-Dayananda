#include <assert.h>
#include <iostream>
using namespace std;
#include "BatteryThresholdDefines.h"

bool checkValueInRange(const float minThreshold, const float maxThreshold, const float valueToCheck, char** out_of_range_factor)
{
	if (valueToCheck < minThreshold)
	{
		*out_of_range_factor = "low"; 
		return false;
	}
	else if (valueToCheck > maxThreshold)
	{
		*out_of_range_factor = "high";
		return false;
	}
	return true;
}

void printOnConsole(const char* factorname, char* out_of_range_factor)
{
	cout << factorname << " value is " << out_of_range_factor << " than the threshhold value "<< endl;
}
bool checkBatteryFactorStatus(const float minThreshold,const float maxThreshold,const float valueOfFactor,const char* factorname)
{
	char* out_of_range_factor = "";
	bool factorIndicator = checkValueInRange(minThreshold, maxThreshold, valueOfFactor, &out_of_range_factor);
	if (!factorIndicator)
	{
		printOnConsole(factorname, out_of_range_factor);
	}
	return factorIndicator;
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
