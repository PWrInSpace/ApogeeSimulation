#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#define P0 100421             // sea level standard pressure,  can be changed to pressure on the launchpad, Pascal
#define T0 288.15             // sea level standard temperature, can be changed to temperature on the launchpad, Kelvin
#define L 0.0065              // temperature lapse rate, kelvin/meter
#define G 9.80665             // gravitational acceleration, meter/second^2
#define R 8.31446             // ideal gas constant, Jule/(mol*Kelvin)
#define M 0.0289652           // molar mass of dry air, kilogram/mol
#define GM_OVER_RL 5.25593278 // GM/RL, constant and used in lots of derivations
#define GAMMA 1.4             // ratio of specific heat of a gas at a constant pressure to heat at a constant volume for air
#define RSTAR 287.058         // specific gas constant of air, = R/M, https://en.wikipedia.org/wiki/Gas_constant#Specific_gas_constant
#define AREF 0.028            // reference area of rocket
#define TIMESTEP 0.001
#define TIMESTEPSQ 0.000001

struct ApogeeSimStruct{
float mass;             // rocket mass
float verticalPos[2];   // verticalPos[0] - position on t0, verticalPos[1] - position on t0 + dt
float dt;               // sampling in flight time (TIMESTEP relates to simulation steps)
};

float CdOverMach[101]; // array for Cd values,
                       // CdOverMach[1] contains Cd value for Mach 0.01, CdOverMach[2] for Mach 0.02 and so on

float calculateTemperature(float height)
{
    return T0 - L * height;
}

/*! P = P0 * (1 - L*height/T0) ^ (GM/RL)
 *  https://en.wikipedia.org/wiki/Density_of_air#Variation_with_altitude\
 *  !!!! Pressure can also be taken from our measurements !!!!
 */
float calculatePressure(float height)
{
    /* read pressure from main comp,
       return pressure
    */
    return P0 * pow((1 - L * height / T0), GM_OVER_RL);
}

/*!
 *  https://en.wikipedia.org/wiki/Density_of_air#Variation_with_altitude
 */
float calculateAirDensity(float height)
{
    return calculatePressure(height) * M / (R * calculateTemperature(height));
}

/*!
 *  https://en.wikipedia.org/wiki/Mach_number#Calculation
 */
float calculateSpeedOfSound(float height)
{
    return pow(GAMMA * RSTAR * calculateTemperature(height), 0.5);
}

/*!
 *  https://en.wikipedia.org/wiki/Mach_number#Calculation
 */
float calculateMachNumber(float height, float velocity)
{
    return velocity / calculateSpeedOfSound(height);
}

float getCd(float machNumber)
{
    float machTimes100 = machNumber * 100.0;
    return CdOverMach[(int)machTimes100]; //conversion from float to int*100
}

float calculateDragForce(float height, float velocity)
{
    return calculateAirDensity(height) * pow(velocity, 2) * AREF * getCd(calculateMachNumber(height, velocity)) * 0.5;
}

int main(int argc, char **argv)
{
    CdOverMach[0] = 0.0; // for 0 Mach velocity
    int j = 0;

    // Get Cd values
    std::ifstream data;
    data.open("data.txt");
    for (j = 1; j < 101; ++j) // save values from data sheet
    {
        data >> CdOverMach[j];
    }
    data.close();

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
    bool runningScript = 1; //for end of script marking
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
    while (runningScript && i <=500)
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
            dragForce = calculateDragForce(simHeight[1], velocity);
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