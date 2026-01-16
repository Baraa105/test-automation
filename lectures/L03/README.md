# L03 - Unittester (del II)

## Dagordning
* Slutförande av unit-tester för GPIO-drivern.
* Skapande av unittester för en serial-driver.
* Korrigering av eventuella buggar.

## Mål med lektionen
* Kunna skriva unittester för en UART-baserad serial-driver.
* Kunna använda Google Test-ramverket för att skriva testfall.
* Förstå hur man använder en virtuell hårdvaruplattform för att testa hårdvarunära kod.
* Kunna använda `std::thread` för att simulera samtidig hårdvaruaktivitet.
* Kunna testa olika scenarion såsom:
  * Initialisering av serial-porten.
  * Aktivering och avaktivering av serial-transmission.
  * Transmission av data via UART (UDR0).
  * Synkronisering med hårdvaruregister (UDRE0-flaggan).
  * Läsning av data från virtuella hårdvaruregister.
* Kunna identifiera och åtgärda buggar genom systematiska tester.

## Förutsättningar
* Genomgång av L01 och L02 samt förståelse för grundläggande testbegrepp.
* Bekantskap med Google Test-ramverket.
* Grundläggande förståelse för UART-kommunikation och registerhantering.

## Instruktioner

### Förberedelse
* Studera serial-drivern [driver::serial::Atmega328p](../../library/include/driver/serial/atmega328p.h) ([källkod](../../library/source/driver/serial/atmega328p.cpp)).
* Läs igenom testfilen [atmega328p_test.cpp](../../library/test/driver/serial/atmega328p_test.cpp) för att förstå strukturen.
* Observera hur `std::thread` används för att simulera samtidig hårdvaruaktivitet:
  * `simulateDataReg()` - simulerar hårdvarubeteendet för UART-dataregistret (redan implementerad).
  * `printThread()` - ska transmittera meddelanden via serial-drivern.
  * `readDataRegThread()` - ska verifiera att rätt data skrivs till UDR0-registret.

### Skriva tester
* Öppna testfilen [atmega328p_test.cpp](../../library/test/driver/serial/atmega328p_test.cpp).
* Ta bort `#ifdef LECTURE3` (rad 17) samt motsvarande `#endif` (rad 151) för att aktivera testerna.
* Implementera de ofullständiga funktionerna:
  * `printThread()` - använd `serial.print()` för att transmittera meddelandet, sätt sedan `stop = true`.
  * `readDataRegThread()` - läs och verifiera varje tecken från UDR0, hantera UDRE0-flaggan.
* Implementera `Serial_Atmega328p.Initialization` testet enligt kommentarerna.
* Testet `Serial_Atmega328p.Transmit` är redan strukturerat men kräver att trådarna fungerar korrekt.
* Ni är välkomna att lägga till fler tester vid behov.

### Köra tester
Navigera till testmappen och kör följande kommandon:

```bash
cd library/test
make
```

### Buggräkning
* Analysera eventuella testfel.
* Identifiera buggar i drivern.
* Åtgärda eventuella buggar i [atmega328p.cpp](../../library/source/driver/serial/atmega328p.cpp).
* Kör om testerna tills alla blir gröna.

## Utvärdering
* Vilka buggar hittade ni? Hur skulle de ha påverkat systemet i produktion?
* Vilka utmaningar uppstod när ni skrev testerna?
* Hur fungerade det att arbeta med trådar för att simulera hårdvarubeteende?
* Vilka synkroniseringsproblem stötte ni på mellan trådarna?
* Vad tycker ni om användningen av den virtuella hårdvaruplattformen jämfört med att testa på riktig hårdvara?
* Några övriga synpunkter på lektionen?

## Nästa lektion
* Slutförande av unit-tester för serial-drivern.
* Unittester för en timer-driver.
