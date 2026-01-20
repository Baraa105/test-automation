/**
 * @brief Unit tests for the ATmega328p timer driver.
 */
#include <cstdint>

#include <gtest/gtest.h>

#include "arch/avr/hw_platform.h"
#include "driver/timer/atmega328p.h"
#include "utils/utils.h"

#ifdef TESTSUITE

//! @todo Implement tests according to project requirements.
namespace driver
{
namespace
{
/** Maximum number of timer circuits available on ATmega328P. */
constexpr std::uint8_t MaxTimerCount{3U};

//! @todo Remove this #ifdef when starting to work on the callback test.
// CALLBACK

/** Flag to track if callback was invoked. */
bool callbackInvoked{false};

// -----------------------------------------------------------------------------
void resetCallbackFlag() noexcept { callbackInvoked = false; }

// -----------------------------------------------------------------------------
void testCallback() noexcept { callbackInvoked = true; }

// -----------------------------------------------------------------------------
constexpr std::uint32_t getMaxCount(const std::uint32_t timeout_ms) noexcept
{
    constexpr double interruptIntervalMs{0.128};
	return 0U < timeout_ms ? 
        utils::round<std::uint32_t>(timeout_ms / interruptIntervalMs) : 0U;
}

//! @todo Remove this #endif when starting to work on the callback test.
# /** CALLBACK */

/**
 * @brief Timer initialization test.
 * 
 *        Verify that timer circuits are initialized correctly and that 
 *        resource limits are enforced.
 */
TEST(Timer_Atmega328p, Initialization)
{
    // Case 1 - Verify that only MaxTimerCount (3) timers can be used simultaneously due to 
    //          hardware limitations.
    {
        // Create three timers with arbitrary timeouts.
        timer::Atmega328p timer0{100U};
        timer::Atmega328p timer1{50U};
        timer::Atmega328p timer2{25U};

        // Verify that each timer is initialized, since the ATmega328p has three hardware timers.
        EXPECT_TRUE(timer0.isInitialized());
        EXPECT_TRUE(timer1.isInitialized());
        EXPECT_TRUE(timer2.isInitialized());

        // Create one additional timer.
        // Verify that the additional timer isn't initialized, since no circuits are available.
        timer::Atmega328p timer3{10U};
        EXPECT_FALSE(timer3.isInitialized());
    }

    // Case 2 - Verify that a timer cannot have a 0 ms timeout.
    {
        // Create a timer with a 100 ms timeout.
        // Verify that the timer is initialized.
        timer::Atmega328p timer0{100U};
        EXPECT_TRUE(timer0.isInitialized());

        // Create a timer with a 0 ms timeout.
        // Verify that the timer isn't initialized (0 ms is an invalid timeout).
        timer::Atmega328p timer1{0U};
        EXPECT_FALSE(timer1.isInitialized());
    }
}

/**
 * @brief Timer enable/disable test.
 * 
 *        Verify that timers can be started and stopped correctly.
 */
TEST(Timer_Atmega328p, EnableDisable)
{
       
        // Create a timer with a timeout.
        timer::Atmega328p timer0{100U};
        timer::Atmega328p timer1{50U};
        timer::Atmega328p timer2{25U};
        
        // Verify timer is not enabled initially (unless auto-started via the constructor).
        EXPECT_FALSE(timer0.isEnabled());
        EXPECT_FALSE(timer1.isEnabled());   
        EXPECT_FALSE(timer2.isEnabled());

        // Start the timer.
        timer0.start();
        timer1.start();
        timer2.start();


        // Verify that the timer is enabled.
        EXPECT_TRUE(timer0.isEnabled());
        EXPECT_TRUE(timer1.isEnabled());
        EXPECT_TRUE(timer2.isEnabled());

        // Stop the timer.
        timer0.stop();
        timer1.stop();
        timer2.stop();

        // Verify that the timer is disabled.
        EXPECT_FALSE(timer0.isEnabled());
        EXPECT_FALSE(timer1.isEnabled());
        EXPECT_FALSE(timer2.isEnabled());

        // Toggle the timer.
        timer0.toggle();
        timer1.toggle();
        timer2.toggle();

        // Verify that the timer is enabled.
        EXPECT_TRUE(timer0.isEnabled());
        EXPECT_TRUE(timer1.isEnabled());
        EXPECT_TRUE(timer2.isEnabled());

        // Toggle the timer once again.
        timer0.toggle();
        timer1.toggle();
        timer2.toggle();

        // Verify that the timer is disabled.
        EXPECT_FALSE(timer0.isEnabled());
        EXPECT_FALSE(timer1.isEnabled());
        EXPECT_FALSE(timer2.isEnabled());

    //! @note Once the above is working:
    //!       Feel free to try all three timers. When enabling/disabling, feel free to check both
    //!       that the isEnabled() methods returns the right value and that the associated bit
    //!       in the timer mask register is set (see the source code).
    //!       Feel free to add a function and pass the timer, the mask register and the mask bit
    //!       to avoid writing the same code three times (or use a struct as was the case for
    //!       the registers in the GPIO unit tests).

}

/**
 * @brief Timer timeout test.
 * 
 *        Verify that timeout values can be set and read correctly.
 */
TEST(Timer_Atmega328p, Timeout)
{
    //! @todo Test timer timeout:

        // Create a timer with an initial timeout of 100 ms.
        timer::Atmega328p timer{100U};

        // Verify timeout_ms() returns the correct value.
        EXPECT_EQ(timer.timeout_ms(), 100U);

        // Change the timeout to 200 ms using setTimeout_ms().
        timer.setTimeout_ms(200U);

        // Verify the new timeout is returned by timeout_ms().
        EXPECT_EQ(timer.timeout_ms(), 200U); 

        // Change the timeout to 0 ms using setTimeout_ms().
        timer.setTimeout_ms(0U);

        // Verify that the timeout is unchanged (0 ms is an invalid timeout).
        EXPECT_EQ(timer.timeout_ms(), 0U);   // supposted to be 200U instaed of 0U

}

/**
 * @brief Timer callback test.
 * 
 *        Verify that timer callbacks are invoked when timeout occurs.
 */
TEST(Timer_Atmega328p, Callback)
{
    //! @todo Test timer callback:
        // Reset the callback flag (callbackInvoked) using resetCallbackFlag().
        resetCallbackFlag(); 

        // Create a timer with a short timeout, such as 10 ms, and testCallback() as callback.
        timer::Atmega328p timer{10U, testCallback, true};

        // Start the timer.
        timer.start();

        // Simulate timer interrupts by repeatedly calling handleCallback() on the timer.
        constexpr std::uint32_t maxCount{getMaxCount(10U)};

        // Call handleCallback() enough times to reach the timeout (getMaxCount()).
        for (std::uint32_t i{}; i < maxCount; ++i)
        {
            timer.handleCallback();
        }
        
        // Verify that callbackInvoked is true after timeout.
        EXPECT_TRUE(callbackInvoked);


        // Note: handleCallback() increments the timer and invokes the callback when timeout is reached.

}

/**
 * @brief Timer restart test.
 * 
 *        Verify that timers can be restarted correctly.
 */
TEST(Timer_Atmega328p, Restart)
{
    //! @todo Test timer restart:
        // Reset the callback flag (callbackInvoked) using resetCallbackFlag().
        resetCallbackFlag(); 

        // Create and start a timer with testCallback() as callback.
        timer::Atmega328p timer{10U, testCallback, true}; 

        // Call handleCallback() enough times to almost reach the timeout (getMaxCount() - 1).
        for (uint32_t i = 0; i < (getMaxCount(10U) - 1); ++i) 
        
        {
        timer.handleCallback();
        }

        
        // Verify that the callback flag (callbackInvoked) is still false.
        EXPECT_FALSE(callbackInvoked); 

        // Restart the timer.
        timer.restart(); 

        // Verify that the timer is still enabled after restart.
        EXPECT_TRUE(timer.isEnabled());

        // Call handleCallback() enough times to almost reach the timeout (getMaxCount() - 1).
        for (uint32_t i = 0; i < (getMaxCount(10U) - 1); ++i) 
        {
        timer.handleCallback();
        }
        

        // Verify that the callback flag (callbackInvoked) is still false, since the timer was restarted.
        EXPECT_FALSE(callbackInvoked); 

        // Call handleCallback() again to reach timeout.
        timer.handleCallback(); 

        // Verify that the callback flag (callbackInvoked) is true due to timeout.
        EXPECT_TRUE(callbackInvoked);
}

//! @todo Add more tests here (e.g., register verification, multiple timers running simultaneously).

} // namespace
} // namespace driver

#endif /** TESTSUITE */
