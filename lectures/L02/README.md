# L02 - Unittester (del I)

## Dagordning
* Skapande av unittester för en GPIO-driver.
* Korrigering av eventuella buggar.

## Mål med lektionen
* Kunna skriva unittester för en hårdvarudrivrutin (GPIO-driver).
* Kunna använda Google Test-ramverket för att skriva testfall.
* Förstå hur man använder en virtuell hårdvaruplattform för att testa hårdvarunära kod.
* Kunna testa olika scenarion såsom:
  * Initialisering och validering av pin-nummer.
  * Konfiguration av pinnar som in- eller utgångar.
  * Läsning och skrivning av pin-värden.
  * Toggle-funktionalitet.
  * Resurshantering (att endast en instans per pin tillåts).
* Kunna identifiera och åtgärda buggar genom systematiska tester.

## Förutsättningar
* Genomgång av L01 och förståelse för grundläggande testbegrepp.
* Bekantskap med Google Test-ramverket.

## Instruktioner

### Förberedelse
* Studera GPIO-drivern [driver::gpio::Atmega328p](../../library/include/driver/gpio/atmega328p.h) ([källkod](../../library/source/driver/gpio/atmega328p.cpp)).
* Läs igenom testfilen [atmega328p_test.cpp](../../library/test/driver/gpio/atmega328p_test.cpp) för att förstå strukturen.

### Skriva tester
* Öppna testfilen [atmega328p_test.cpp](../../library/test/driver/gpio/atmega328p_test.cpp).
* Ta bort `#ifdef LECTURE2` (rad 15) samt motsvarande `#endif` (rad 215) för att aktivera testerna.
* Implementera testfallen enligt kommentarerna i filen.
* Börja med `Gpio_Atmega328p.Initialization` testet, fortsätt sedan med output- och input-testen.
* Kommentarer för vad som bör testas finns i testfilen. Ni är välkomna att lägga till fler tester vid behov.

### Köra tester
Navigera till testmappen och kör följande kommandon:

```bash
cd library/test
make
```

### Buggräkning
* Analysera eventuella testfel.
* Identifiera buggar i drivern.
* Åtgärda eventuella buggar i [atmega328p.cpp](../../library/source/driver/gpio/atmega328p.cpp).
* Kör om testerna tills alla blir gröna.

## Utvärdering
* Vilka buggar hittade ni? Hur skulle de ha påverkat systemet i produktion?
* Vilka utmaningar uppstod när ni skrev testerna?
* Vad tycker ni om användningen av den virtuella hårdvaruplattformen jämfört med att testa på riktig hårdvara?
* Några övriga synpunkter på lektionen?

## Nästa lektion
* Slutförande av unit-tester för GPIO-drivern.
* Unittester för en serial-driver.
