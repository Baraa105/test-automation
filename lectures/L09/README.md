# L09 - SW/HW-integrationstestning (del II)

## Dagordning
* Automatisering av tester genom seriell kommunikation med hårdvaran.
* Demonstration av `serial::read()` för att ta emot kommandon från PC.
* Skriva Python-skript för att skicka kommandon och läsa svar från target.
* Implementera automatiserade tester med Python (för högre betyg).

## Mål med lektionen
* Förstå hur seriell kommunikation kan användas för testautomation.
* Kunna implementera kommandotolkning på embedded-sidan med `serial::read()`.
* Kunna skriva Python-skript för att kommunicera med hårdvara via seriell port.
* **Huvudmål**: Förstå grunderna i automatiserad testning av embedded-system och avsluta projektarbetet.

## Förutsättningar
* Genomförd L08 med fungerande manuell testning på target.
* Python 3 installerat på utvecklingsdatorn.
* Tillgång till Arduino/ATmega328P med fungerande firmware.

## Teori: Manuell vs automatiserad testning

### Manuell testning
* Kräver mänsklig interaktion (knapptryckningar, observation).
* Tidskrävande och repetitivt.
* Risk för mänskliga fel.
* Svårt att dokumentera och reproducera.

### Automatiserad testning
* Tester körs automatiskt via skript.
* Snabbare att köra upprepade tester.
* Konsistenta och reproducerbara resultat.
* Enklare att integrera i CI/CD-pipelines.
* **Nackdelar**: Kräver initial setup och underhåll av testskript.

## Instruktioner

### Förberedelser

#### 1. Installera Python och pyserial
Öppna Git Bash. Kolla om Python är installerat:

```bash
python --version
```

Om inte, installera Python via följande kommando, vilket öppnar Microsoft Store:

```bash
python
```

Installera paketet `pyserial`:

```bash
pip install pyserial
```

#### 2. Hitta serieport
Identifiera vilken serieport Arduino är ansluten till (COM3, COM4, etc.), exempelvis via `Device Manager` (Enhetshanteraren).

### Implementera kommandotolkning på embedded-sidan

Anta att vi implementerar följande kommandon:
* `t`: Står för `toggle` och används för att toggla toggle-timern.
* `s`: Står för `status` och används för att läsa toggle-timerns tillstånd.
* `r`: Står för `read` och används för att läsa rumstemperaturen.

#### Lägg till kommandohantering i systemlogiken
**För högre betyg**: Implementera kommandohantering i er target-logik enligt exemplet nedan.
För att läsa data som skickas från er PC på target, använd `serial::read()` i 
[logic.cpp](../../library/source/logic/logic.cpp), exempelvis via en privat metod som anropas från
logik-loopen. Nedan visas ett exempel på en sådan metod:

```cpp
// -----------------------------------------------------------------------------
bool Logic::readSerialPort() noexcept
{
    constexpr uint16_t readTimeout_ms{100U};
    constexpr uint16_t bufferSize{10U};

    // Create a buffer with room for 10 characters.
    uint8_t buffer[bufferSize]{};

    // Read the serial port, set timeout to 100 ms.
    const int16_t err{mySerial.read(buffer, bufferSize, readTimeout_ms)};

    // Print received data if any.
    if (0 > err) { mySerial.printf("Failed to read serial data!\n"); }
    else if (0 < err)
    {
        //! @todo Remove the next three lines in the real implementation!
        mySerial.printf("Received %d characters from the serial port: ", err);
        for (int16_t i{}; i < err; ++i) { mySerial.printf("%c", buffer[i]); }
        mySerial.printf("\n");

        // Check the first character to determine command:
        const char cmd{static_cast<char>(buffer[0U])};

        switch (cmd)
        {
            case 't':
                //! @todo Toggle the LED here.
                break;
            case 's':
                //! @todo Print the state of the toggle timer here!
                break;
            case 'r':
                //! @todo Read and print the temperature here!
                break;
            default:
                mySerial.printf("Unknown command %c!\n", cmd);
                break;
        }
    }
    // Return true if any data was received.
    return 0 < err;
}
```

### Python-skript för testautomation

#### Python-implementation (för testning och debugging)
Detta skript låter er manuellt skicka kommandon och se svar i realtid, vilket är mycket användbart för att testa att er C++-implementation fungerar innan ni bygger automatiserade tester.

```python
import time

from serial import Serial

def main():
    """Communicate with ATmega328p via UART."""
    # Open serial connection (adjust COM port).
    serial = Serial("COM3", 9600, timeout=1)

    # Wait for the Arduino to start.
    time.sleep(2)

    # Read startup responses.
    print("Reading startup responses from Arduino:")
    while serial.in_waiting > 0:
        msg = serial.readline().decode("utf-8").strip()
        if len(msg) > 0:
            print(f"{msg}")
    print("\nArduino tester ready. Commands: t, s, r, q (quit)")
    
    # Continuously monitor user input.
    while True:
        # Read commands entered by the user, terminate the program if 'q' is received.
        cmd = input("Enter command: ").strip()
        if cmd == 'q':
            break
        
        # Send data to the ATmega328p, encoded as bytes.
        serial.write(cmd.encode())
        
        # Wait for response with timeout.
        timeout = 2.0  # seconds
        start_time = time.time()
        
        while (time.time() - start_time) < timeout:
            if serial.in_waiting > 0:
                msg = serial.readline().decode("utf-8").strip()
                if len(msg) > 0:
                    print(f"Received from Arduino: {msg}")
            else:
                time.sleep(0.1)  # Short sleep to avoid busy-waiting
    
    # Close connection.
    serial.close()

# Invoke the main function if this is the startup script.
if __name__ == "__main__":
    main()
```

#### Kör skriptet
```bash
python main.py
```

### Uppgift: Implementera testautomation med klass

**Mål**: Skapa ett objektorienterat Python-program som automatiserar testfallen från L08.

#### Krav för godkänd implementation (högre betyg):

1. **Separat katalog för seriella moduler**: Skapa en underkatalog döpt `uart` i katalogen
[test/scripts](../../library/test/scripts/) innehållande filerna `interface.py`, `driver.py`, `stub.py`, `factory.py` samt `__init__.py`.
2. **Interface**: Definiera ett interface döpt `Interface` i `interface.py` för seriell kommunikation med UART, innehållande gemensamma metoder oavsett operativsystem.
3. **Driver-klass för seriell kommunikation**: Implementera en driverklass döpt `Driver` i `driver.py`, som ärver från interfacet och hanterar seriell kommunikation när använt operativsystem är Windows. Klassen ska automatiskt hitta rätt COM-port (där mikrokontrollern är ansluten).
4. **Stub-klass vid användning av Linux/Mac**: Implementera en stub-klass döpt `Stub` i `stub.py`, som ärver från interfacet och simulerar seriell kommunikation när använt operativsystem är Linux eller Mac.
5. **Factory-funktion**: Implementera en factory-funktion i `factory.py` som returnerar rätt implementation (Driver eller Stub) baserat på parameter, se exempel nedan.
6. **Testimplementation**: Implementera era tester i [serial_test.py](../../library/test/scripts/serial_test.py). Använd factory-funktionen för att skapa seriell instans - använd `Driver` för Windows, `Stub` för övriga operativsystem.
7. **Loggning till fil**: All seriell data (både kommandon och svar) ska loggas till en textfil för senare analys.
8. **Testmetoder**: Implementera metoder för varje testfall:
   - `test_toggle()` - Testa toggle-funktionalitet.
   - `test_temperature()` - Testa temperaturavläsning.
   - `test_eeprom()` - Verifiera EEPROM-persistens.
   - `test_status()` - Kontrollera systemstatus.
9. **Automatisk verifiering**: Verifiera förväntade svar från target.
10. **Testrapport**: Generera en rapport med PASS/FAIL för varje test.
11. **Robust felhantering**: Hantera timeout, anslutningsfel, ogiltiga svar, etc. Systemet ska vara stabilt även vid fel.

#### Exempel: Factory-funktion

Skapa filen `factory.py` i katalogen `uart/` med följande innehåll:

```python
"""Serial factory implementation."""
from .driver import Driver
from .interface import Interface
from .stub import Stub

def create(port: str, baudrate: int = 9600, stub: bool = False) -> Interface:
    """Create serial instance.
    
    Args:
        port: Serial port (e.g. "COM3").
        baudrate: Baud rate (default = 9600).
        stub: True to create a stub (default = false).

    Returns:
        New serial instance.
    """
    if stub:
        return Stub(port, baudrate)
    else:
        return Driver(port, baudrate)
```

I [serial_test.py](../../library/test/scripts/serial_test.py) kan factoryn användas såsom visas nedan. I detta exempel används `platform.system()` för att bestämma vilket operativsystem som används:

```python
import platform
from uart import factory

# Check OS, use stub on Linux/Mac, real driver on Windows.
use_stub = platform.system() != "Windows"

# Create UART instance connected to COM3, use default baud rate.
uart = factory.create("COM3", use_stub)
```

### Tips för implementation

* **Interface**: Använd `abc.ABC` och `@abstractmethod` för att skapa ett interface i Python.
* **COM-port detektering**: Använd `serial.tools.list_ports` för att lista alla tillgängliga COM-portar.
* **Loggning**: Använd `open()` med mode `'a'` (append) för att skriva till en loggfil. Timestamp:a varje rad med `datetime.now()`.
* **Vänta på svar**: Använd `time.sleep()` eller `serial.in_waiting()` för att vänta på svar från target.
* **Parsing av svar**: Använd `strip()`, `split()` för att tolka svar från Arduino.
* **Timeout-hantering**: Använd attributet `timeout` i `Serial()`-konstruktorn.
* **Try-except**: Använd `try-except` för att hantera fel på ett robust sätt.
* **Debugging**: Skriv ut alla kommandon och svar för att underlätta felsökning.
* **Testsekvenser**: Testa en funktion i taget innan ni kombinerar tester.

### Exempel på testfall att automatisera

1. **Toggle-test**:
   - Skicka 't' för toggla toggle-timern → verifiera att lysdioden börjar blinka samt att "Toggle timer enabled!" skrivs ut i terminalen.
   - Skicka 't' igen → verifiera att lysdioden börjar blinka samt att "Toggle timer disabled!" skrivs ut i terminalen.

2. **Status-test**:
   - Skicka 's' → verifiera att toggle-timerns status skrivs ut i terminalen samt att den matchar aktuellt tillstånd på target.

3. **Temperatur-test**:
   - Skicka 'r' → verifiera att temperaturen skrivs ut i terminalen.

4. **EEPROM-test**:
   - Aktivera toggle → resetta Arduino → verifiera att toggle-timern är aktiv vid start.
   - Inaktivera toggle → resetta Arduino → verifiera att toggle-timern är inaktivt vid start.

5. **End-to-end scenario**:
   - Automatisera hela scenariot från L08 via Python-skript.

### Felsökning

#### Problem: Kan inte ansluta till seriell port
* **Lösning**: Kontrollera att rätt port anges. Stäng alla andra program som använder porten (seriell monitor, etc.).

#### Problem: Inget svar från Arduino
* **Lösning**: Verifiera att baud rate matchar (vanligen 9600 bps). Kontrollera att firmware är uppladdad och kör.

#### Problem: Trasiga tecken i svaret
* **Lösning**: Kontrollera baudrate och encoding (UTF-8).

#### Problem: Serial timeout
* **Lösning**: Öka timeout-värdet som passeras till `Serial()`-konstruktorn eller lägg till en
 längre `time.sleep()`.

## Utvärdering
* Lyckades ni automatisera testfallen med Python?
* Vilka fördelar och nackdelar upptäckte ni med automatiserad testning?
* Hur kan automatiserad testning förbättra utvecklingsprocessen?
* Vilka utmaningar fanns med implementationen?
* Hur skulle ni vidareutveckla testautomationen?
* Några övriga synpunkter på lektionen?

## Nästa lektion
* Slutförande av testsvit och kursavslutning.
