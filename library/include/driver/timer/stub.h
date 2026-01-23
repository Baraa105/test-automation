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
     */
    bool isInitialized() const noexcept override { return myInitialized; }

    /**
     * @brief Check whether the timer is enabled.
     */
    bool isEnabled() const noexcept override { return myEnabled; }

    /**
     * @brief Check whether the timer has timed out.
     */
    bool hasTimedOut() const noexcept override { return myTimedOut; }

    /**
     * @brief Get the timeout of the timer.
     */
    uint32_t timeout_ms() const noexcept override 
    { 
        return 0U; 
    }

    /**
     * @brief Set timeout of the timer.
     */
    void setTimeout_ms(uint32_t timeout_ms) noexcept override 
    {
        (void) (timeout_ms);
    }

    /**
     * @brief Start the timer.
     */
    void start() noexcept override 
    { 
        // FIXAT: Nu matchar koden kommentaren!
        if (myInitialized)
        {
            myEnabled = true; 
            myTimedOut = false; 
        }
    } 

    /**
     * @brief Stop the timer.
     */
    void stop() noexcept override 
    { 
        // FIXAT: Nu matchar koden kommentaren!
        if (myInitialized)
        {
            myEnabled = false; 
            myTimedOut = false; 
        }
    }

    /**
     * @brief Toggle the timer.
     */
    void toggle() noexcept override 
    { 
        // FIXAT: Nu matchar koden kommentaren!
        if (myInitialized)
        {
            myEnabled = !myEnabled; 
            myTimedOut = false; 
        }
    } 

    /**
     * @brief Restart the timer.
     */
    void restart() noexcept override 
    { 
        // FIXAT: Nu matchar koden kommentaren!
        if (myInitialized)
        {
            myEnabled = true; 
            myTimedOut = false;
        }
    } 

    // --- TEST-METODER ---

    // Denna lade du till själv, och den är helt rätt nu!
    void setTimedOut(bool status) noexcept
    {
        if (myEnabled)
        {
            myTimedOut = status;
        }
    }

    // Denna kan vara bra att ha om du vill testa initieringsfel (Case 3)
    void setInitialized(bool status) noexcept
    {
        myInitialized = status;
        // Om den stängs av (false), så stänger vi av timern också
        if (!myInitialized) 
        {
            myEnabled = false;
            myTimedOut = false;
        }
    }

    Stub(const Stub&)            = delete; // No copy constructor.
    Stub(Stub&&)                 = delete; // No move constructor.
    Stub& operator=(const Stub&) = delete; // No copy assignment.
    Stub& operator=(Stub&&)      = delete; // FIXAT: Tog bort 'x' härifrån

private:
    bool myInitialized;
    bool myEnabled;
    bool myTimedOut;
};
} // namespace timer
} // namespace driver