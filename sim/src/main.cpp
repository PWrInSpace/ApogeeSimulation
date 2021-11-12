#include "../include/RocketStruct.h"

int main(int argc, char **argv)
{
    //CdOverMach[0] = 0.0; // for 0 Mach velocity
    int j = 0;

    // Get Cd values
    RocketStruct r4s;
 

    

    // Get flight numbers
    std::ifstream flight;
    flight.open("data_EUROC2.txt");
    /*
    for (j = 0; j < 500; ++j)
    {
        flight_time >> flightData[0][j];
        flight >> flightData[1][j];
        std::cout << flightData[0][j] << " " << flightData[1][j] << std::endl;
    }
  */

    // MAIN PROGRAM STARTS HERE //
    bool running;           // for the while loop
    bool runningScript = 1; // for end of script marking
    /* 
     * velocity, height, dragForce - self explanatory
     * simTime - time when data was taken and simulation began
     * thrustEndTime - duration of engine working
     * simHeight - height in timestamp n-1 and n respectively
     * rocketMass - mass with motors, without propelant
     * propellantMass - mass of propellant at the time of launch
     * allMass - rocketMass + mass of propellant in time t
     */
    float velocity, dragForce, simTime, simStartTime, thrustEndTime = 6, simHeight[2], rocketMass = 27.3, propellantMass = 4, allMass; // mass in kg
    std::string str;
    int p;
    float i = 0;
    float oldSimHeight = 0.0;
    while (runningScript && i <= 500)
    {

        running = 1;

        simTime = 0.051 * i;
        simHeight[0] = oldSimHeight;

        flight >> simHeight[1];
        velocity = (simHeight[1] - simHeight[0]) / 0.051; // v = (h1 - h0)/dt
        if (simTime < thrustEndTime)
            allMass = rocketMass + propellantMass * ((thrustEndTime - simTime) / thrustEndTime);
        else
            allMass = rocketMass;
        simStartTime = simTime;
        oldSimHeight = simHeight[1];
        p = 0;
        std::cout << "Doing::" << simHeight[1] << " <- height | time of turnoff -> " << simStartTime << " allMass = " << allMass << std::endl;
        while (running && i >= 10)
        {

            if (velocity <= 0)
            {
                running = 0;
                if (simHeight[1] > 2500.0)
                {
                    std::cout << simHeight[1] << " <- height | time of turnoff -> " << simStartTime << " allMass = " << allMass << std::endl;
                    runningScript = 0;
                }
            }
            /*! 
                it would be good to include sth like this:
                
                if (openedPilotParachute || reachedApogee)
                    running = 0;
            */
            dragForce = r4s.calculateDragForce(simHeight[1], velocity);
            simHeight[0] = simHeight[1];                                                                                   // height in t(n) prepare for next step
            simHeight[1] = simHeight[1] + velocity * TIMESTEP - 4.9 * TIMESTEPSQ - dragForce / allMass * TIMESTEPSQ * 0.5; // height in t(n+1)
            simTime += TIMESTEP;                                                                                           // increase simTime
            velocity = (simHeight[1] - simHeight[0]) / TIMESTEP;
            if (++p > 1000)
                running = 0; // changed !!!
        }
        i += 1; // go next
    }
    flight.close();
}