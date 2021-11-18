#include "../include/RocketStruct.h"

int main()
{
    int j;
    std::ifstream flight;
    float flightData[500];

    flight.open("../data/data_EUROC3.txt");
    for (j = 0; j < 500; ++j)
    {
        flight >> flightData[j];
        std::cout << flightData[j] << std::endl;
    }
    flight.close();

    // MAIN PROGRAM STARTS HERE //

    float simStart = 0.0, thrustEndTime = 7.0, simHeight[2], rocketMass = 27.3, propellantMass = 4; // for setup
    simHeight[1] = flightData[1];
    simHeight[0] = flightData[0];
    std::string cdFile = "../data/dataCdOverMach.txt";
    StateStruct stateAtStart(simHeight, 0.052, simStart);
    RocketStruct rocket(rocketMass, propellantMass, thrustEndTime, stateAtStart, cdFile);

    float tempLastHeight = flightData[0];
    int i = 1;
    while (i <= 500)
    {
        
        float tempVel = (flightData[i] - tempLastHeight)/0.052;
        simStart += 0.052;
        std::cout << rocket.apogeeSimulation(flightData[i], tempLastHeight, tempVel, simStart) << "\n";
        tempLastHeight = flightData[i];
        
        i++;
    }
}