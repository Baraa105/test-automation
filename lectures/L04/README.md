# L04 - Unittester (del III)

## Dagordning
* Skapande av unittester för en timer-driver.
* Simulering av interrupt-driven hårdvara.
* Korrigering av eventuella buggar.

## Mål med lektionen
* Kunna skriva unittester för en interrupt-driven timer-driver.
* Kunna använda Google Test-ramverket för att skriva testfall.
* Förstå hur man simulerar interrupt-baserad hårdvara i unittester.
* Förstå callback-mekanismen och hur timers interagerar med hårdvaruinterrupt.
* Kunna testa olika scenarion såsom:
  * Initialisering av timers och resurshantering.
  * Aktivering och avaktivering av timers.
  * Konfiguration och validering av timeout-värden.
  * Callback-funktionalitet vid timeout.
  * Omstart av timers.
* Kunna identifiera och åtgärda buggar genom systematiska tester.

## Förutsättningar
* Genomgång av L01, L02 och L03 samt förståelse för grundläggande testbegrepp.
* Bekantskap med Google Test-ramverket.
* Grundläggande förståelse för timers och interrupt-hantering.

## Instruktioner

### Förberedelse
* Studera timer-drivern [driver::timer::Atmega328p](../../library/include/driver/timer/atmega328p.h) ([källkod](../../library/source/driver/timer/atmega328p.cpp)).
* Läs igenom testfilen [atmega328p_test.cpp](../../library/test/driver/timer/atmega328p_test.cpp) för att förstå strukturen.
* Observera att timer-drivern är interrupt-driven:
  * ATmega328P har tre hårdvaru-timer-kretsar (Timer0, Timer1, Timer2).
  * `handleCallback()` simulerar ett timer-interrupt - den ökar räknaren och anropar callback vid timeout.
  * I unittester anropar vi `handleCallback()` manuellt istället för att vänta på riktiga interrupts.

### Skriva tester
* Öppna testfilen [atmega328p_test.cpp](../../library/test/driver/timer/atmega328p_test.cpp).
* Ta bort `#ifdef LECTURE4` (rad 14) samt motsvarande `#endif` (rad 120) för att aktivera testerna.
* Implementera testfallen enligt kommentarerna:
  * `Timer_Atmega328p.Initialization` - testa resurshantering (max 3 timers).
  * `Timer_Atmega328p.EnableDisable` - testa start/stop/toggle-funktionalitet.
  * `Timer_Atmega328p.Timeout` - testa timeout-konfiguration.
  * `Timer_Atmega328p.Callback` - testa callback-anrop genom att anropa `handleCallback()` upprepade gånger.
  * `Timer_Atmega328p.Restart` - testa omstartsfunktionalitet.
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
* Åtgärda eventuella buggar i [atmega328p.cpp](../../library/source/driver/timer/atmega328p.cpp).
* Kör om testerna tills alla blir gröna.

## Utvärdering
* Vilka buggar hittade ni? Hur skulle de ha påverkat systemet i produktion?
* Vilka utmaningar uppstod när ni skrev testerna?
* Hur fungerade det att simulera interrupt-baserad hårdvara genom att anropa `handleCallback()` manuellt?
* Vilka skillnader noterade ni jämfört med att testa serial-drivern (som använde trådar)?
* Hur upplevde ni att hantera resurshanteringen för de tre timer-kretsarna?
* Vad tycker ni om användningen av den virtuella hårdvaruplattformen jämfört med att testa på riktig hårdvara?
* Några övriga synpunkter på lektionen?

## Nästa lektion
* Slutförande av unit-tester för timer-drivern.
* Introduktion till komponenttester.
* Skapande av stubklasser för att testa högre komponenter i isolering.
