/***********************************************************************************
Programmer: Tre' Jeter, Computation Scholar at LLNL
Date: May 29, 2019
Purpose: Find the values in the open fields of Intel's MSR_PKG_POWER_LIMIT Register
         in terms of power in watts and in terms of time in seconds
***********************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#define POWERMASK 0x07fff00000000LL //Mask for Package Power Limit #2, bits 32-46
#define TIMEMASK_ONE 0x03f8000LL //Mask for Time Window Power Limit #1, bits 17-23
#define TIMEMASK_TWO 0x7fuLL //Mask for Time Window Power Limit #2, bits 49-55

int main()
{
    uint64_t a, b;
    a = 0x784B0001583E8; //MSR_PKG_POWER_LIMIT Register
    b = 0xA0E03; //MSR_RAPL_POWER_UNIT 
    int Power_Unit_One;
    int Power_Unit_Two;
    float Time_Window_One;
    float Time_Window_Two;
    float Time_Limit_One;
    float Time_Limit_Two;
    double Time_Unit = 0.0009765; //Time Unit for Time Window #1 and #2 from documentation
    double z = 0.0; //Bits 22-23 for Time Window #1 from the given Time Limit equation
    int Watts_One; //Watts for Power Unit #1
    int Watts_Two; //Watts for Power Unit #2
    
    
    printf("How many watts do you want to run through Package Power Limit #1? \n");
    scanf("%d", &Watts_One);
    Power_Unit_One = Watts_One * 8;
    printf("%d%s", Power_Unit_One, " total bits \n");
    
    
    printf("%s%d%s", "How many seconds would you like ", Watts_One, " watts to run through Package Power Limit #1? \n");
    scanf("%fu", &Time_Limit_One);
    float x1 = (1.0 + (z / 4.0)) * Time_Unit;
    float m1 = Time_Limit_One / x1;
    Time_Window_One = log10(m1) / log10(2);
    printf("%s%f\n", "Value between bits: ", Time_Window_One);
    printf("\n");
    
    
    printf("How many watts do you want to run through Package Power Limit #2? \n");
    scanf("%d", &Watts_Two);
    Power_Unit_Two = Watts_Two * 8;
    printf("%d%s", Power_Unit_Two, " total bits \n");
    
    
    printf("%s%d%s", "How many seconds would you like ", Watts_Two, " watts to run through Package Power Limit #2? \n");
    scanf("%fu", &Time_Limit_Two);
    float x2 = (1.0 + (z / 4.0)) * Time_Unit;
    float m2 = Time_Limit_Two / x2;
    Time_Window_Two = log10(m2) / log10(2);
    printf("%s%f\n", "Value between bits: ", Time_Window_Two);
    
    return 0;
}
