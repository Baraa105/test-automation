/**
 * @brief Smart temperature sensor implementation.
 */
<<<<<<< HEAD
 
 /**
 * @brief Smart temperature sensor implementation.
 */
=======
>>>>>>> a108fd7ee5b893667e3d33805cf4699427f22260
#pragma once

#include <stdint.h>

#include "driver/tempsensor/interface.h"

namespace ml
{
/** Linear regression interface. */
namespace lin_reg { class Interface; }
} // namespace ml

namespace driver
{
/** ADC (A/D converter) interface. */
namespace adc { class Interface; }

namespace tempsensor
{
/**
 * @brief Smart temperature sensor implementation.
<<<<<<< HEAD
 * 
 *        This class is non-copyable and non-movable.
=======
>>>>>>> a108fd7ee5b893667e3d33805cf4699427f22260
 */
class Smart final : public Interface
{
public:
    /**
     * @brief Constructor.
     * 
     * @param[in] pin Pin the temperature sensor is connected to.
     * @param[in] adc A/D converter for reading the input voltage from the sensor.
<<<<<<< HEAD
     * @param[in] linReg Linear regression model to predict the temperature based on
     *                   the input voltage. Must be pre-trained.
=======
     * @param[in] linReg Linear regression model to predict the temperature based on the 
     *                   input voltage.
>>>>>>> a108fd7ee5b893667e3d33805cf4699427f22260
     */
    explicit Smart(uint8_t pin, adc::Interface& adc, ml::lin_reg::Interface& linReg) noexcept;

    /**
     * @brief Destructor.
     */
    ~Smart() noexcept override = default;

    /**
     * @brief Check if the temperature sensor is initialized.
     * 
     * @return True if the temperature sensor is initialized, false otherwise.
     */
    bool isInitialized() const noexcept override;

    /**
     * @brief Read the temperature sensor.
     *
     * @return The temperature in degrees Celsius.
     */
    int16_t read() const noexcept override;

<<<<<<< HEAD
=======
    Smart()                        = delete; // No default constructor.
    Smart(const Smart&)            = delete; // No copy constructor.
    Smart(Smart&&)                 = delete; // No move constructor.
    Smart& operator=(const Smart&) = delete; // No copy assignment.
    Smart& operator=(Smart&&)      = delete; // No move assignment.

>>>>>>> a108fd7ee5b893667e3d33805cf4699427f22260
private:
    /** A/D converter to read the input voltage from the sensor. */
    adc::Interface& myAdc;

<<<<<<< HEAD
    /** Linear regression model for predict temperature based on the input voltage. */
=======
    /** Linear regression model to predict the temperature based on the input voltage. */
>>>>>>> a108fd7ee5b893667e3d33805cf4699427f22260
    ml::lin_reg::Interface& myLinReg;

    /** Analog pin the temperature sensor is connected to. */
    const uint8_t myPin;
};
} // namespace tempsensor
} // namespace driver
<<<<<<< HEAD
=======


>>>>>>> a108fd7ee5b893667e3d33805cf4699427f22260
