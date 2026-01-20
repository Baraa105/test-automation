//! @todo Add temperature sensor stub here!
/**
 * @brief Temperature sensor interface.
 */
#pragma once

#include <stdint.h>
#include "driver/tempsensor/interface.h"


namespace driver
{
namespace tempsensor
{
class stub final : public Interface
{
public:
/**
 * @brief constructor.
 */

    stub() noexcept
        : myInitialized{true}
        , myTemperature{}
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
};
    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // No move assignment.


private: 
    bool myInitialized;
    int16_t myTemperature;
};


} // namespace tempsensor
} // namespace driver
