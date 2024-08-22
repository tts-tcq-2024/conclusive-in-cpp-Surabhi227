#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    EXPECT_EQ(inferBreach(22, 20, 25), NORMAL);  // Value within limits
    EXPECT_EQ(inferBreach(19, 20, 25), TOO_LOW);  // Value below lower limit
    EXPECT_EQ(inferBreach(26, 20, 25), TOO_HIGH);  // Value above upper limit
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 10), NORMAL);  // Within limits for PASSIVE_COOLING
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);  // Above limit for PASSIVE_COOLING
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 45), NORMAL);  // At upper limit for HI_ACTIVE_COOLING
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 41), TOO_HIGH);  // Above limit for MED_ACTIVE_COOLING
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 0), NORMAL);  // At lower limit for MED_ACTIVE_COOLING
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertController) {
    BatteryCharacter batteryChar = {MED_ACTIVE_COOLING, "BrandZ"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_CONTROLLER, batteryChar, 42);  // Should send too high alert to controller
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 2\n");  // Expect TOO_HIGH alert output
}

TEST(TypeWiseAlertTestSuite, CheckAndAlertEmail) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandA"};
    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, -5);  // Should send too low alert via email
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too low\n");  // Expect TOO_LOW email output
}


