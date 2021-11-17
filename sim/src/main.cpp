#include "../include/RocketStruct.h"

int main()
{
    int j;
    std::ifstream flight;
    float flightData[500];

    flight.open("../data/data_EUROC2.txt");
    for (j = 0; j < 500; ++j)
    {
        flight >> flightData[j];
        std::cout << flightData[j] << std::endl;
    }
    flight.close();

    // MAIN PROGRAM STARTS HERE //

    float simStart = 0.0, thrustEndTime = 7.0, simHeight[2], rocketMass = 27.3, propellantMass = 4; // for setup
    float simulatedApogee;
    simHeight[1] = flightData[1];
    simHeight[0] = flightData[0];
    std::string cdFile = "../data/dataCdOverMach.txt";
    StateStruct stateAtStart(simHeight, 0.052, simStart);
    RocketStruct rocket(rocketMass, propellantMass, thrustEndTime, stateAtStart, cdFile);

    int i = 0;
    while (i <= 500)
    {
        rocket.rocketState.simHeight[1] = flightData[i + 1];
        rocket.rocketState.simHeight[0] = flightData[i];
        rocket.rocketState.velocity = (rocket.rocketState.simHeight[1] - rocket.rocketState.simHeight[0])/0.052;
        //std::cout << stateAtStart.simHeight[1] << " " << stateAtStart.simHeight[0] << std::endl;
        simStart += 0.052;
        rocket.rocketState.simTime = simStart;
        rocket.apogeeSimulation(2000, simulatedApogee);
        i++;
    }
}