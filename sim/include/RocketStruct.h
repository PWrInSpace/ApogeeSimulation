#ifndef ROCKET_STRUCT_HH
#define ROCKET_STRUCT_HH
#include "StateStruct.h"

/* 
     * velocity, height, dragForce - self explanatory
     * simTime - time when data was taken and simulation began
     * timeOfTurnoff - duration of engine working
     * simHeight - height in timestamp n-1 and n respectively
     * rocketMass - mass with motors, without propelant
     * propellantMass - mass of propellant at the time of launch
     * allMass - rocketMass + mass of propellant in time t
     */
struct RocketStruct
{
    float rocketMass;     // rocket mass
    float propellantMass; // propellant mass
    float allMass;
    float timeOfTurnoff;   // t of engine shutdown (all propellant deplated)
    float CdOverMach[101]; // array for Cd values,
                           // CdOverMach[1] contains Cd value for Mach 0.01, CdOverMach[2] for Mach 0.02 and so on

    StateStruct rocketState;
    RocketStruct();

    RocketStruct(float rm, float pm, float t, float Cd[101], StateStruct stat);

    void readCd(std::string cdDataName);

    float getCd(float machNumber)
    {
        float machTimes100 = machNumber * 100.0;
        return CdOverMach[(int)machTimes100]; //conversion from float to int*100
    }

    float calculateDragForce(float height, float velocity)
    {
        return rocketState.calculateAirDensity(rocketState.height) * pow(velocity, 2) * AREF * getCd(rocketState.calculateMachNumber(height, velocity)) * 0.5;
    }
};

#endif