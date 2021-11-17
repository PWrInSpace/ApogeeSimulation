#include "../include/RocketStruct.h"

RocketStruct::RocketStruct()
{
    CdOverMach[0] = 0.0;
}

RocketStruct::RocketStruct(float rm, float pm, float t, StateStruct stat, std::string cdDataName)
{
    int i;
    this->readCd(cdDataName);
    this->CdOverMach[0] = 0.0;
    this->rocketMass = rm;
    this->propellantMass = pm;
    this->allMass = rocketMass + propellantMass;
    this->timeOfTurnoff = t;
}

void RocketStruct::readCd(std::string cdDataName)
{
    int i;
    std::ifstream data;
    data.open(cdDataName.c_str());

    for (i = 1; i < 101; ++i) // save values from data sheet
    {
        data >> this->CdOverMach[i];
        //std::cout<< this->CdOverMach[i];
    }
    data.close();
}

bool RocketStruct::apogeeSimulation(float targetApogee, float simulatedApogee)
{
    bool apogeeAchieved = 0;
    float simStartTime = rocketState.simTime;
    bool targetAchieved = 0;
    int p = 0;
    calculateAllMass();
    std::cout << "Doing::" << rocketState.simHeight[1] << " <- height | start time -> " << simStartTime << " allMass = " << allMass << std::endl;
    std::cout<< "Data: " << rocketState.velocity << " <- velocity | mach -> " << rocketState.calculateMachNumber(rocketState.simHeight[1]) << std::endl;
    while (!apogeeAchieved)
    {

        if (rocketState.velocity <= 0)
        {
            apogeeAchieved = 1;
            if (rocketState.simHeight[1] > targetApogee)
            {
                std::cout << rocketState.simHeight[1] << " <- simHeight !!! ACHIEVED <----------------------!!!!!!" << std::endl;
            }
        }
        rocketState.dragForce = calculateDragForce(rocketState.simHeight[1], rocketState.velocity);                                                                                                          // height in t(n) prepare for next step
        rocketState.simHeight[1] = rocketState.simHeight[1] + (rocketState.velocity * TIMESTEP) - (4.9 * TIMESTEPSQ) - (rocketState.dragForce / allMass * TIMESTEPSQ * 0.5); // height in t(n+1)
        rocketState.simTime += TIMESTEP;                                                                                                                               // increase simTime
        rocketState.velocity = rocketState.velocity - 9.8 * TIMESTEP - rocketState.dragForce / allMass *TIMESTEP;
        //std::cout<<rocketState.velocity<<std::endl;

        if (rocketState.simTime >= 30)
            apogeeAchieved = 1; // changed !!!
    }
    //std::cout << rocketState.simHeight[1] << " <- simHeight" << std::endl;
    return targetAchieved;
}