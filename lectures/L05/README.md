# L05 - Komponenttester (del I)

## Dagordning
* Slutförande av unit-tester för timer-drivern.
* Introduktion till komponenttester och skillnaden mot unittester.
* Inspektion av befintliga stub-implementationer.
* Demonstration: Skapande av en stub-klass för GPIO-drivern.
* Implementering av egna stubklasser.

## Mål med lektionen
* Förstå skillnaden mellan unittester och komponenttester.
* Förstå syftet med stubklasser och när de ska användas.
* Kunna analysera befintliga stub-implementationer.
* Kunna skapa egna stubklasser som implementerar drivrutins-interface.
* Förstå hur man ersätter hårdvaruberoenden med kontrollerbara stub-implementationer.
* **Huvudmål**: Implementera en första version av alla stubklasser så att komponentester för systemlogiken i
[logic_test.cpp](../../library/test/logic/logic_test.cpp) kan kompilera (även om testerna inte nödvändigtvis går igenom).

## Förutsättningar
* Genomgång av L01-L04 och förståelse för unittester.
* Bekantskap med Google Test-ramverket.
* Förståelse för interface-baserad design och polymorfism i C++.

## Instruktioner

### Förberedelse
* Studera befintliga stub-implementationer för att förstå mönstret:
  * [driver::adc::Stub](../../library/include/driver/adc/stub.h)
  * [driver::eeprom::Stub](../../library/include/driver/eeprom/stub.h)
  * [driver::serial::Stub](../../library/include/driver/serial/stub.h)
  * [driver::watchdog::Stub](../../library/include/driver/watchdog/stub.h)
  * [logic::Stub](../../library/include/logic/stub.h) (denna klass är ett specialfall och används 
  specifikt för att göra vissa delar av logikklassen åtkomliga just för testning)

* Observera hur stubklasser:
  * Implementerar samma interface som den riktiga drivrutinen.
  * Ger kontrollerbara, förutsägbara svar istället för att interagera med hårdvara.
  * Tillåter testning av högre komponenter i isolering.

* Vid behov, se information om interfaces i C++ [här](../L01/cpp/05%20-%20Arv%20och%20interfaces.md).

### Demonstration
* Följ med under demonstrationen där en stub-klass skapas för GPIO-drivern.
* Notera hur stub-klassen implementerar interface-metoderna.
* Se hur stub-klassen används i komponenttester.

### Implementera stubklasser
* Skapa en första version av alla stubklasser så att [logic_test.cpp](../../library/test/logic/logic_test.cpp) kan kompilera.

* De stubklasser som behöver implementeras för att komponenttesta systemlogiken är följande:
  * [driver::gpio::Stub](../../library/include/driver/gpio/stub.h) (demonstration under lektionen)
  * [driver::tempsensor::Stub](../../library/include/driver/tempsensor/stub.h)
  * [driver::timer::Stub](../../library/include/driver/timer/stub.h)
* Implementationerna kan skrivas inline, dvs. all kod kan läggas i headerfilen för enkelhets skull.
* Implementera alla interface-metoder (kan vara tomma/returnera default-värden i första versionen).
* Lägg gärna till metoder för att via stub-klassen kunna styra hårdvara, exempelvis genom att
  sätta utsignalen på en GPIO-port, simulera timeouts med mera.
* Verifiera att koden kompilerar genom att ta bort `#ifdef STUBS_IMPLEMENTED` (rad 21) samt motsvarande `#endif` (rad 316) i [logic_test.cpp](../../library/test/logic/logic_test.cpp).

### Köra tester
Navigera till testmappen och kör följande kommandon:

```bash
cd library/test
make
```

## Utvärdering
* Vad är den största skillnaden mellan unittester och komponenttester?
* Varför behöver vi stubklasser istället för att använda riktiga drivrutiner?
* Vilka utmaningar uppstod när ni skapade stubklasser?
* Hur bidrar stubklasser till bättre testbarhet och isolering?
* Vilka fördelar ser ni med interface-baserad design för testning?
* Några övriga synpunkter på lektionen?

## Nästa lektion
* Utveckling av befintliga stubklasser så att befintliga komponenttester fungerar.
* Tillägg av ytterligare komponenttester.
