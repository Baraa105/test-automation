/**
 * @brief Temperature sensor stub.
 */
#pragma once

#include <stdint.h>

#include "driver/tempsensor/interface.h"

namespace driver
{
namespace tempsensor
{
/**
 * @brief Temperature sensor stub.
 */
class Stub final : public Interface
{
public:
    /**
     * @brief Constructor.  
     */
    Stub() noexcept
        : myTemperature{}
        , myInitialized{true}
    {}
    
    /**
     * @brief Destructor.
     */
     ~Stub() noexcept override = default;

    /**
     * @brief Check if the temperature sensor is initialized.
     * 
     * @return True if the temperature sensor is initialized, false otherwise.
     */
    bool isInitialized() const noexcept override { return myInitialized; } 

    /**
     * @brief Read the temperature sensor.
     *
     * @return The temperature in degrees Celsius.
     */
    int16_t read() const noexcept override { return myTemperature; }


    // Skapa en metod döpt setInitialized, som gör det möjligt att sätta initieringsstatusen.
    // Om du sätter den till false, sätt temperaturen till 0 automatiskt.
    // Exempelvis setInitialized(false) för att sätta den som oinitierad.

    bool setInitialized(bool newStatus) noexcept
    {
        myInitialized = newStatus;
        if (!myInitialized)
        {
            myTemperature = 0;
        }
        return myInitialized;

    }

    // Skapa en metod döpt setTemp, som gör det möjligt att sätta temperaturen i stubben, 
    // exempelvis setTemp(25) för 25 grader Celsius. Detta gäller bara om temperaturstubben är initerad;
    // om inte ska temperaturen alltid vara 0.

    bool setTemp(int16_t newTemp) noexcept
    {
        if (myInitialized)
        {
            myTemperature = newTemp;
        }
        else
        {
            myTemperature = 0;
        }
        return myTemperature == newTemp;
    }



    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // No move assignment.

private: 
    int16_t myTemperature;
    bool myInitialized;
}; // class Stub
}  // namespace tempsensor
}  // namespace driver
