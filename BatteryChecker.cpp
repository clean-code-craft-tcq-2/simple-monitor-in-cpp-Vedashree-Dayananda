#include <assert.h>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;
#include "BatteryThresholdDefines.h"
#include "BatteryChecker.h"

using funcptr = float(*)(float);

std::map < char, funcptr > TemperatureConverterFunctionMap = {
	{ 'F', convertFarenhietToCelcius },
	{ 'K', convertKelvinToCelcius }
};

//Checks if the value passed has breached any limit and sets the factor of breach low or high
bool checkValueInRange(const float minThreshold, const float maxThreshold, const float valueToCheck, string* out_of_range_factor)
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
bool checkValueInEarlyWarningRange(const float lowerLimit, const float upperLimit, const float value)
{
	if ((value >= lowerLimit) &&  (value <= upperLimit))
		return true;
	return false;
}

void printOnConsole(string message)
{
	cout << message << endl;
}

string format_message(string messageType, string out_of_range_factor, string factor_name)
{
	string message = "";
	if (messageType == "Warning")
		message = messageType + " : " + factor_name + " Approaching " + out_of_range_factor + " Threshold\n";
	else
		message = factor_name + " value is " + out_of_range_factor + " than the threshhold value\n ";
	return message;
}

void format_and_print_message(string messageType,string out_of_range_factor, string factor_name)
{
	string message = format_message(messageType, out_of_range_factor, factor_name);
	printOnConsole(message);
}
void checkForEarlyWarnings(const float minThreshold, const float maxThreshold, const float minWarningThreshold, const float maxWarningThreshold, const float valueOfFactor, string factorname)
{
	string message = "";
	if (checkValueInEarlyWarningRange(minThreshold, minWarningThreshold ,valueOfFactor))
	{
		format_and_print_message("Warning","low", factorname);
	}
	else if (checkValueInEarlyWarningRange(maxWarningThreshold, maxThreshold, valueOfFactor))
	{
		format_and_print_message("Warning", "high", factorname);
	}

}
				   
bool checkBatteryFactorStatus(const float minThreshold, const float maxThreshold, const float minWarningThreshold, const float maxWarningThreshold, const float valueOfFactor, string factorname)
{
	string out_of_range_factor = "";
	string message = "";
	bool factorIndicator = checkValueInRange(minThreshold, maxThreshold, valueOfFactor, &out_of_range_factor);
	if (!factorIndicator)
	{
		format_and_print_message("Breach",out_of_range_factor, factorname);
	}
	checkForEarlyWarnings(minThreshold,maxThreshold,minWarningThreshold, maxWarningThreshold,valueOfFactor,factorname);
	return factorIndicator;
}

float convertFarenhietToCelcius(float temperature)
{
	return ((temperature - 32) * 5 / 9);
}

float convertKelvinToCelcius(float temperature)
{
	return (temperature - 273.15);
}

float convertTemperatureToCelcius(string temperature)
{
	string temperatureValueInString(temperature, 0, temperature.length() - 2);
	float temperatureInCelcius = 0.0, temperatureValue = 0.0;
	stringstream ss;
	ss << temperatureValueInString;
	ss >> temperatureValue;
	temperatureInCelcius = temperatureValue;
	if (temperature.back() != 'C')
	{
		funcptr coverterFunction = TemperatureConverterFunctionMap[temperature.back()];
		temperatureInCelcius = (*coverterFunction)(temperatureValue);
	}
	return temperatureInCelcius;
}

bool batteryIsOk(string temperature, float soc, float chargeRate) {
	bool temperatureIndicator = false, socIndicator = false, chargeRateIndicator = false, result = false;
	float temperatureInCelcius = convertTemperatureToCelcius(temperature);
	temperatureIndicator = checkBatteryFactorStatus(TEMPERATURE_MIN_THRESHOLD, TEMPERATURE_MAX_THRESHOLD, TEMPERATURE_LOWER_TOLERENCE_LIMIT, TEMPERATURE_UPPER_TOLERENCE_LIMIT, temperatureInCelcius, "temperature");
	socIndicator = checkBatteryFactorStatus(SOC_MIN_THRESHOLD, SOC_MAX_THRESHOLD, SOC_LOWER_TOLERENCE_LIMIT, SOC_UPPER_TOLERENCE_LIMIT, soc, "SOC");
	chargeRateIndicator = checkBatteryFactorStatus(CHARGERATE_MIN_THRESHOLD, CHARGERATE_MAX_THRESHOLD, CHARGERATE_LOWER_TOLERENCE_LIMIT, CHARGERATE_UPPER_TOLERENCE_LIMIT, chargeRate, "ChargeRate");

	result = temperatureIndicator && socIndicator && chargeRateIndicator;
	return result;
}

void testBatteryStatus(string temperature, float soc, float chargeRate, bool expectedResult)
{
	assert(batteryIsOk(temperature, soc, chargeRate) == expectedResult);
}

int main() {
	testBatteryStatus("32.0F", 70, 0.7, true);
	testBatteryStatus("25.0C", 70, 0.7, true);
	testBatteryStatus("50.0C", 85, 0, false);
	testBatteryStatus("46.0C", 40, 0.6, false);
	testBatteryStatus("30.2F", 30, 0.5, false);
	testBatteryStatus("40.0C", 19, 0.6, false);
	testBatteryStatus("39.0C", 81, 0.5, false);
	testBatteryStatus("40.0C", 50, -0.1, false);
	testBatteryStatus("40.0C", 50, 0.9, false);
	testBatteryStatus("0.0C", 20, 0, true);
	testBatteryStatus("45.0C", 80, 0.8, true);
	testBatteryStatus("22.0C", 70, 0.7, true);
	testBatteryStatus("50.0C", 85, 0, false);
	testBatteryStatus("46.0C", 40, 0.6, false);
	testBatteryStatus("-1.0C", 30, 0.5, false);
	testBatteryStatus("40.0C", 19, 0.6, false);
	testBatteryStatus("39.0C", 81, 0.5, false);
	testBatteryStatus("40.0C", 50, -0.1, false);
	testBatteryStatus("40.0C", 50, 0.9, false);
	testBatteryStatus("1.0C", 20, 0, true);
	testBatteryStatus("44.0C", 80, 0.8, true); 
	testBatteryStatus("30.0C", 22, 0.7, true);
	testBatteryStatus("25.0C", 77, 0.7, true);
	testBatteryStatus("32.0F", 70, 0.1, true);
	testBatteryStatus("25.0C", 70, 0.7, true);
}
