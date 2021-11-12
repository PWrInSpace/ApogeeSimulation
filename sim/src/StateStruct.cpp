#include"../include/StateStruct.h"

StateStruct::StateStruct(float pos[2], float diti)
{
    this->verticalPos[0] = pos[0];
    this->verticalPos[1] = pos[1];
    this->dt = diti;
    this->height = verticalPos[1];
    this->velocity = (verticalPos[1] - verticalPos[0]) / dt;
}