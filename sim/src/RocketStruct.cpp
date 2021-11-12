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

void RocketStruct::readCd(std::string cdDataName)
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