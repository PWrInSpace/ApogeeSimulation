#ifndef ROCKET_STRUCT_HH
#define ROCKET_STRUCT_HH
#include "StateStruct.h"

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

    void readCd(std::string cdDataName)
    {
        int i;
        std::ifstream data;
        data.open(cdDataName.c_str());

        for (i = 1; i < 101; ++i) // save values from data sheet
        {
            data >> this->CdOverMach[i];
        }
        data.close();
    }

    float getCd(float machNumber)
    {
        float machTimes100 = machNumber * 100.0;
        return CdOverMach[(int)machTimes100]; //conversion from float to int*100
    }

    float calculateDragForce(float height, float velocity)
    {
        return rocketState.calculateAirDensity(rocketState.height) * pow(velocity, 2) * AREF * getCd(rocketState.calculateMachNumber(height, velocity)) * 0.5;
    }

    // dorobic strukture stanow (polozenie itp)
};

#endif