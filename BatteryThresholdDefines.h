#define TolerenceValueCalculator(threshold,tolerence_percentage) threshold*tolerence_percentage/100
#define LowerTolerenceLimit(threshold,tolerence) threshold + tolerence
#define UpperTolerenceLimit(threshold,tolerence) threshold - tolerence

const float TEMPERATURE_MIN_THRESHOLD = 0.0F;
const float TEMPERATURE_MAX_THRESHOLD = 45.0F;

const float SOC_MIN_THRESHOLD = 20.0F;
const float SOC_MAX_THRESHOLD = 80.0F;

const float CHARGERATE_MIN_THRESHOLD = 0.0F;
const float CHARGERATE_MAX_THRESHOLD = 0.8F;

const float TOLERENCE_PERCENTAGE = 5.0F;
const float TEMPERATURE_TOLERENCE = TolerenceValueCalculator(TEMPERATURE_MAX_THRESHOLD, TOLERENCE_PERCENTAGE);
const float SOC_TOLERENCE = TolerenceValueCalculator(SOC_MAX_THRESHOLD, TOLERENCE_PERCENTAGE);
const float CHARGERATE_TOLERENCE = TolerenceValueCalculator(CHARGERATE_MAX_THRESHOLD, TOLERENCE_PERCENTAGE);

const float TEMPERATURE_LOWER_TOLERENCE_LIMIT = LowerTolerenceLimit(TEMPERATURE_MIN_THRESHOLD, TEMPERATURE_TOLERENCE);
const float TEMPERATURE_UPPER_TOLERENCE_LIMIT = UpperTolerenceLimit(TEMPERATURE_MAX_THRESHOLD, TEMPERATURE_TOLERENCE);

const float SOC_LOWER_TOLERENCE_LIMIT = LowerTolerenceLimit(SOC_MIN_THRESHOLD, SOC_TOLERENCE);
const float SOC_UPPER_TOLERENCE_LIMIT = UpperTolerenceLimit(SOC_MAX_THRESHOLD, SOC_TOLERENCE);

const float CHARGERATE_LOWER_TOLERENCE_LIMIT = LowerTolerenceLimit(CHARGERATE_MIN_THRESHOLD, CHARGERATE_TOLERENCE);
const float CHARGERATE_UPPER_TOLERENCE_LIMIT = UpperTolerenceLimit(CHARGERATE_MAX_THRESHOLD, CHARGERATE_TOLERENCE);
