/**
 * @brief Timer interface.
 */
#pragma once

#include <stdint.h>
#include "driver/timer/interface.h"

namespace driver
{
namespace timer
{
/**
 * @brief Timer interface.
 */
class Stub final : public Interface
{
public:
     /**
     * @brief constructor.
     */
    Stub() noexcept
        : myInitialized{true}
        , myEnabled{false}
        , myTimedOut{false}
    {}


    /**
     * @brief Destructor.
     */
     ~Stub() noexcept = default;

    /**
     * @brief Check if the timer is initialized.
     * 
     *        An uninitialized timer indicates that no timer circuit was available when the timer 
     *        was created.
     * 
     * @return True if the timer is initialized, false otherwise.
     */
     bool isInitialized() const noexcept override { return myInitialized; }

    /**
     * @brief Check whether the timer is enabled.
     *
     * @return True if the timer is enabled, false otherwise.
     */
     bool isEnabled() const noexcept override { return myEnabled; }

    /**
     * @brief Check whether the timer has timed out.
     *
     * @return True if the timer has timed out, false otherwise.
     */
     bool hasTimedOut() const noexcept override{ return myTimedOut; }

    /**
     * @brief Get the timeout of the timer.
     * 
     * @return The timeout in milliseconds.
     */
     uint32_t timeout_ms() const noexcept override 
     { 
        // Timeout is irrelevant for the stub, return 0.
        return 0U; 
    }

    /**
     * @brief Set timeout of the timer.
     * 
     * @param[in] timeout_ms The new timeout in milliseconds.
     */
     void setTimeout_ms(uint32_t timeout_ms) noexcept override 
     {
        // Timeout is irrelevant for the stub, ignore the input.
        (void) (timeout_ms);
     }

    /**
     * @brief Start the timer.
     */
     void start() noexcept override 
     { 
        // Starta bara timern om den är initierad, annars gör inget.
        myEnabled = true; 
        myTimedOut = false; 
    } 

    /**
     * @brief Stop the timer.
     */
     void stop() noexcept override 
     { 
        // Stoppa bara timern om den är initierad, annars gör inget.
        myEnabled = false; 
        myTimedOut = false; 
     }

    /**
     * @brief Toggle the timer.
     */
     void toggle() noexcept override 
     {
        // Toggla bara timern om den är initierad, annars gör inget. 
        myEnabled = !myEnabled; myTimedOut = false; 
     } 

    /**
     * @brief Restart the timer.
     */
    void restart() noexcept override 
    {
        // Starta bara om timern om den är initierad, annars gör inget. 
        myEnabled = true; 
        myTimedOut = false;
    } 

    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // No move assignment.x

private:
    bool myInitialized;

    bool myEnabled;

    bool myTimedOut;
};
} // namespace timer
} // namespace driver
