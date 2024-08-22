#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    EXPECT_EQ(inferBreach(10, 15, 25), TOO_LOW);
    EXPECT_EQ(inferBreach(30, 15, 25), TOO_HIGH);
    EXPECT_EQ(inferBreach(20, 15, 25), NORMAL);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 15), NORMAL);
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0), NORMAL);
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertController) {
    BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "BrandA"};
    checkAndAlert(TO_CONTROLLER, batteryChar, 42);  // Should send too high alert to controller
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertEmail) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandB"};
    checkAndAlert(TO_EMAIL, batteryChar, 0);  // Should send normal alert via email
}
