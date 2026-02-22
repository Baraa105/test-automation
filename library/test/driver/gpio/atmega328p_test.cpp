/**
 * @brief Unit tests for the Atmega328p GPIO driver.
 */
#include <cstdint>
#include <cstdio>
#include <gtest/gtest.h>

// --- HÅRDVARU-MOCK (GLOBAL) ---
// Vi allokerar minne för alla register här.
// Drivrutinen (atmega328p.cpp) kommer att leta efter dessa "externa" variabler.
volatile std::uint8_t DDRB;
volatile std::uint8_t PORTB;
volatile std::uint8_t PINB;

volatile std::uint8_t DDRC;
volatile std::uint8_t PORTC;
volatile std::uint8_t PINC;

volatile std::uint8_t DDRD;
volatile std::uint8_t PORTD;
volatile std::uint8_t PIND;

// Lägg till dessa för säkerhets skull, ifall drivrutinen rör interrupt eller pull-up globalt
volatile std::uint8_t SREG;
volatile std::uint8_t MCUCR;
// ------------------------------

// VIKTIGT: Vi går tillbaka till standard-headern.
// Makefilen ser till att denna header beter sig som "extern" när vi kör tester.
#include "arch/avr/hw_platform.h"

#include "driver/gpio/atmega328p.h"
#include "utils/utils.h"

#ifdef TESTSUITE

namespace driver
{
namespace
{

// Dummy callback för att undvika krasch om nullptr anropas
void dummyCallback() {}

struct GpioRegs
{
    volatile std::uint8_t& ddrx;
    volatile std::uint8_t& portx;
    volatile std::uint8_t& pinx;
};

struct PinOffset
{
    static constexpr std::uint8_t D{0U};
    static constexpr std::uint8_t B{8U};
    static constexpr std::uint8_t C{14U};
};

constexpr std::uint8_t PinCount{20U};

constexpr bool isPinValid(const std::uint8_t id) noexcept { return PinCount > id; }

constexpr std::uint8_t getPhysicalPin(const std::uint8_t id) noexcept
{
    if (!isPinValid(id))        { return static_cast<std::uint8_t>(-1); }
    if (PinOffset::B > id)      { return id; } 
    else if (PinOffset::C > id) { return id - PinOffset::B; }
    return id - PinOffset::C;
}

constexpr void simulateToggle(GpioRegs& regs) noexcept
{
    constexpr std::uint8_t bitCount{8U};
    for (std::uint8_t pin{}; pin < bitCount; ++pin)
    {
        if (utils::read(regs.ddrx, pin) && utils::read(regs.pinx, pin))
        {
            utils::toggle(regs.portx, pin);
            utils::clear(regs.pinx, pin);
        }
    }
}

void runOutputTest(const std::uint8_t id, GpioRegs& regs) noexcept
{
    const std::uint8_t pin{getPhysicalPin(id)};

    {
        gpio::Atmega328p gpio{id, gpio::Direction::Output, dummyCallback};

        std::printf("Testing Output Pin: %u\n", id); // Debug print

        const bool pinValid{isPinValid(id)};
        EXPECT_EQ(gpio.isInitialized(), pinValid);
        
        EXPECT_TRUE(utils::read(regs.ddrx, pin));

        gpio.write(true);
        EXPECT_TRUE(utils::read(regs.portx, pin));

        gpio.write(false);
        EXPECT_FALSE(utils::read(regs.portx, pin));

        gpio.toggle();
        simulateToggle(regs);
        EXPECT_TRUE(utils::read(regs.portx, pin));

        gpio.toggle();
        simulateToggle(regs);
        EXPECT_FALSE(utils::read(regs.portx, pin));
        
        gpio.toggle();
        simulateToggle(regs);
        EXPECT_TRUE(utils::read(regs.portx, pin));
    }
    EXPECT_FALSE(utils::read(regs.ddrx, pin));
    EXPECT_FALSE(utils::read(regs.portx, pin));
}

void runInputTest(const std::uint8_t id, GpioRegs& regs) noexcept
{
    const std::uint8_t pin{getPhysicalPin(id)};

    {
        gpio::Atmega328p gpio{id, gpio::Direction::Input, dummyCallback};

        std::printf("Testing Input Pin: %u\n", id); // Debug print

        const bool pinValid{isPinValid(id)};
        EXPECT_EQ(gpio.isInitialized(), pinValid);
        
        EXPECT_EQ(regs.ddrx & (1U << pin), 0U);
        
        // Pullup check (kan variera beroende på implementering, men vi behåller din logik)
        EXPECT_EQ(regs.portx & (1U << pin), (1U << pin));

        regs.pinx |= (1U << pin);
        EXPECT_TRUE(gpio.read());

        regs.pinx &= ~(1U << pin);
        EXPECT_FALSE(gpio.read());
    }
    EXPECT_EQ(regs.ddrx & (1U << pin), 0U);
    EXPECT_EQ(regs.portx & (1U << pin), 0U);
}

TEST(Gpio_Atmega328p, Initialization)
{
    constexpr std::uint8_t pinMax{20U};

    for (std::uint8_t pin{}; pin < pinMax; ++pin)
    {
        // Debug print för att se exakt var det kraschar
        // std::printf("Init Test Pin: %u\n", pin); 
        
        gpio::Atmega328p gpio{pin, gpio::Direction::Output, dummyCallback};

        EXPECT_EQ(gpio.isInitialized(), isPinValid(pin));

        if (gpio.isInitialized()) 
        {
            // Försök skapa en dubblett
            gpio::Atmega328p gpioDuplicate{pin, gpio::Direction::Output, dummyCallback};
            EXPECT_FALSE(gpioDuplicate.isInitialized());
        }
    }
}

TEST(Gpio_Atmega328p, Output)
{
    for (std::uint8_t pin{}; pin < PinOffset::B; ++pin)
    {
        GpioRegs regs{DDRD, PORTD, PIND};
        runOutputTest(pin, regs);
    }

    for (std::uint8_t pin{PinOffset::B}; pin < PinOffset::C; ++pin)
    {
        GpioRegs regs{DDRB, PORTB, PINB};
        runOutputTest(pin, regs);
    }

    for (std::uint8_t pin{PinOffset::C}; pin < PinCount; ++pin)
    {
        GpioRegs regs{DDRC, PORTC, PINC};
        runOutputTest(pin, regs);
    }
}

TEST(Gpio_Atmega328p, Input)
{
    for (std::uint8_t pin{}; pin < PinOffset::B; ++pin)
    {
        GpioRegs regs{DDRD, PORTD, PIND};
        runInputTest(pin, regs);
    }

    for (std::uint8_t pin{PinOffset::B}; pin < PinOffset::C; ++pin)
    {
        GpioRegs regs{DDRB, PORTB, PINB};
        runInputTest(pin, regs);
    }

    for (std::uint8_t pin{PinOffset::C}; pin < PinCount; ++pin)
    {
        GpioRegs regs{DDRC, PORTC, PINC};
        runInputTest(pin, regs);
    }
}

} // namespace
} // namespace driver

#endif /** TESTSUITE */