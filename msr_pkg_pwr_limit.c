/***********************************************************************************
Programmer: Tre' Jeter
Date: May 25, 2019
Purpose: Find the values in the open fields of Intel's MSR_PKG_POWER_LIMIT Register
         in terms of power in watts and in terms of time in seconds
***********************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#define POWERMASK 0x07fff00000000LL //Mask for Package Power Limit #2, bits 32-46
#define TIMEMASK_ONE 0x03f8000LL //Mask for Time Window Power Limit #1, bits 17-23
#define TIMEMASK_TWO 0x7FULL //Mask for Time Window Power Limit #2, bits 49-55

int main()
{
    uint64_t a, b;
    a = 0x784B0001583E8; //MSR_PKG_POWER_LIMIT Register
    b = 0xA0E03; //MSR_RAPL_POWER_UNIT
    int Power_Unit_One;
    int Power_Unit_Two;
    double Time_Window_One;
    double Time_Window_Two;
    double Time_Limit_One;
    double Time_Limit_Two;
    double Time_Unit = 0.0009765; //Time Unit for Time Window #1 and #2 from documentation
    double z = 0.0; //Bits 22-23 for Time Window #1 from the given Time Limit equation
    int Watts_One; //Watts for Power Unit #1
    int Watts_Two; //Watts for Power Unit #2

    printf("%s\n", "Power Unit #1");
    Power_Unit_One = a & 0x07fff;
    printf("%l\n", Power_Unit_One);
    Watts_One = Power_Unit_One / 8;
    printf("%d%s\n", Watts_One, " watts");
    printf("\n");

    printf("%s\n", "Time Unit #1");
    Time_Window_One = ((a & TIMEMASK_ONE) >> 17);
    printf("%l\n", ((a & TIMEMASK_ONE) >> 17));
    double x;
    x = pow(2.0, 10.0);
    //printf("%lf", x);
    Time_Limit_One = x * (1.0 +(z / 4.0)) * Time_Unit;
    printf("%l f%s\n", Time_Limit_One, " seconds");
    printf("\n");

    printf("%s\n", "Power Unit #2");
    Power_Unit_Two = ((a & POWERMASK) >> 32);
    printf("%l u\n", ((a & POWERMASK) >> 32));
    Watts_Two = Power_Unit_Two / 8;
    printf("%d%s\n", Watts_Two, " watts");
    printf("\n");

    printf("%s\n", "Time Unit #2");
    Time_Window_Two = ((a & TIMEMASK_TWO) >> 5);
    printf("%lu\n", ((a & TIMEMASK_TWO) >> 5));
    double y;
    y = pow(2.0, 3.0);
    //printf("%lf", y);
    Time_Limit_Two = y * (1.0 + (z / 4.0)) * Time_Unit;
    printf("%l f%s\n", Time_Limit_Two, " seconds");
    printf("\n");
    return 0;
}
