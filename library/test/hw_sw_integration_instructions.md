# HW/SW integration instructions

## Prerequisites
* Build and flash an ATmega328p processor.
* Run the system, open a serial terminal.

## 1. Temperature measurement



### 1.1 Temperature button
* Press the temperature button and verify that the temperature is printed via the serial port.
* Compare the value with the actual room temperature to ensure it is reasonable.
* Warm the sensor (e.g., with your hand) and verify that the temperature value increases.
* Press the button repeatedly to verify the debounce functionality. Repeated presses within 300 ms must be ignored.
### 1.2 Temperature timer
* Start the system.
* Press the temperature button.
* Verify that the temperature is printed every 60 seconds. 
* Ensure that the temperature is printed every 60 seconds, or 60 seconds after the last pressdown.

## 2. Watchdog timer
* Verify that the watchdog timer is active upon system startup.
* To test the watchdog functionality: Introduce a bug in an interrupt handler.
* Ensure 'Logic::handleButtonEvent()' does not terminate while a butto is held down. This prevents 'Logic::run() from running, stopping the wacthdog timer reset. 
* Verify that the system resets automatically after the watchdog timeout. 
* Verify that the system reboots correctly after the watchdog timer reset. 
* Remve the inroduced bug and verify that the system operates normally agian. 

## 3. EEPROM persistence 
* Activate the toggle timer so that the LED starts blinking, then power off the system.
* Restart the system and verify that the toggle state is restored from EEPROM.
* Verification: The LED should immediately start blinking, and 'Toggle timer enabled!' should be printed in the terminal.
* Deactivate the toggle timer so that the LED turns off, then power off the system.
* Restart the system and verify that the toggle state remains inactive (the LED should be off).

## 4. End-to-end scenario 
* Note: Interrupt handling and debounce functionality are already tested in section 1 and 2 above 




