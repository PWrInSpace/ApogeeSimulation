#include "../include/RocketStruct.h"

RocketStruct::RocketStruct()
{
CdOverMach[0] = 0.0;
}

RocketStruct::RocketStruct(float rm, float pm, float t, float Cd[101], StateStruct stat)
{
    int i;
    for(i=0; i< 101; ++i)
    {
    this->CdOverMach[i] = Cd[i];    
    }
    this->CdOverMach[0] = 0.0;
    this->rocketMass = rm;
    this->propellantMass = pm;
    this->allMass = rocketMass + propellantMass;
    this->timeOfTurnoff = t;
}