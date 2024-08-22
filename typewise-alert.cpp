#include "typewise-alert.h"
#include <stdio.h>

typedef struct {
    double lowerLimit;
    double upperLimit;
} BreachLimits;

BreachLimits getBreachLimits(CoolingType coolingType) {
    switch(coolingType) {
        case PASSIVE_COOLING: return {0, 35};
        case HI_ACTIVE_COOLING: return {0, 45};
        case MED_ACTIVE_COOLING: return {0, 40};
        default: return {0, 0};
    }
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    BreachLimits limits = getBreachLimits(coolingType);
    return inferBreach(temperatureInC, limits.lowerLimit, limits.upperLimit);
}

void handleAlert(AlertTarget alertTarget, BreachType breachType) {
    if (alertTarget == TO_CONTROLLER) {
        sendToController(breachType);
    } else if (alertTarget == TO_EMAIL) {
        sendToEmail(breachType);
    }
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    handleAlert(alertTarget, breachType);
}

void sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
    const char* recipient = "a.b@c.com";
    if (breachType == TOO_LOW) {
        printf("To: %s\nHi, the temperature is too low\n", recipient);
    } else if (breachType == TOO_HIGH) {
        printf("To: %s\nHi, the temperature is too high\n", recipient);
    }
}

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    if (value < lowerLimit) {
        return TOO_LOW;
    }
    if (value > upperLimit) {
        return TOO_HIGH;
    }
    return NORMAL;
}
