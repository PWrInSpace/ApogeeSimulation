#ifndef STATE_STRUCT_HH
#define STATE_STRUCT_HH

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

/* Struct describes rocket flights parameters
 * Insert values of rocket during the start of the simulation
 * ! These will change when program starts simulating apogee
 */
struct StateStruct
{

    float verticalPos[2]; // verticalPos[0] - position on t0, verticalPos[1] - position on t0 + dt
    float dt;             // sampling in flight time (TIMESTEP relates to simulation steps)
    float height;
    float velocity;
    float dragForce;

    StateStruct() {};
    StateStruct(float pos[2], float diti);

    // ALL MATH FUNCTIONS
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
};

#endif