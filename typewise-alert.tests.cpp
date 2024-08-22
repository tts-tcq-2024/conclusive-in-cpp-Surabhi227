#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) 
{     
  EXPECT_EQ(inferBreach(25, 20, 30), NORMAL);     
  EXPECT_EQ(inferBreach(15, 20, 30), TOO_LOW);     
  EXPECT_EQ(inferBreach(35, 20, 30), TOO_HIGH); 
} 

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach)
{     
  EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 30), NORMAL);     
  EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 40), TOO_HIGH);     
  EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50), TOO_HIGH);     
  EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, -1), TOO_LOW);
}
