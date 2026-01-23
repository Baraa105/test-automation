# L07 - Komponenttester (del III)

## Dagordning
* Slutförande av komponenttester för systemlogiken i [logic_test.cpp](../../library/test/logic/logic_test.cpp).
* Om tid finns: Tillägg av ytterligare komponenttester för att täcka fler scenarion i systemlogiken.
* Verifiering av att alla krav för komponenttester uppfylls.

## Mål med lektionen
* Slutföra implementationen av alla komponenttester för systemlogiken.
* Kunna skriva komponenttester som verifierar komplex logik med flera hårdvarukomponenter.
* Kunna använda stubklasser effektivt för att simulera och verifiera hårdvarubeteende.
* Kunna skriva testfall med tydlig struktur och god täckning av olika scenarion.
* Identifiera och åtgärda buggar som upptäcks genom testning.

## Förutsättningar
* Genomgång av L05 och L06 där stubklasser utvecklades och komponenttester påbörjades.
* Bekantskap med Google Test-ramverket.
* Förståelse för interface-baserad design i C++.
* Alla stubklasser är implementerade och [logic_test.cpp](../../library/test/logic/logic_test.cpp) kompilerar.
* Förståelse för systemlogiken i [logic.cpp](../../library/source/logic/logic.cpp).

## Krav för godkänd komponenttestning
Följande krav ska uppfyllas innan ni går vidare till SW/HW-integrationstestning:

1. **Alla testfall implementerade**: Samtliga testfall i [logic_test.cpp](../../library/test/logic/logic_test.cpp) ska vara implementerade och körbara.
2. **Alla tester går igenom**: Kör `make` i testmappen och verifiera att alla tester passerar (grönt resultat).
3. **Kodtäckning**: Systemlogiken i [logic.cpp](../../library/source/logic/logic.cpp) ska testas grundligt, inklusive:
   - Alla publika metoder (se [logic.h](../../library/include/logic/logic.h)).
   - Olika kombinationer av knapptryckningar.
   - Alla timer-timeouts.
   - EEPROM-läsning och skrivning.
   - Edge cases och felhantering.
4. **Dokumentation**: Varje testfall ska ha tydliga kommentarer som förklarar vad som testas och varför.
5. **Stubklasser kompletta**: Alla nödvändiga stub-metoder ska vara implementerade för att möjliggöra testningen.

## Instruktioner

### Köra tester
Navigera till testmappen och kör följande kommandon:

```bash
cd library/test
make
```

Målet är att de implementerade testerna ska gå igenom. Om något test misslyckas, analysera felmeddelandet och justera antingen stub-implementationen eller testfallet.

### Felsökning och buggfixar
* Om tester indikerar att buggar förekommer i systemlogiken eller stub-implementationerna:
  * Analysera testresultatet noggrant för att identifiera rotorsaken.
  * Avgör om felet ligger i testfallet, stub-implementationen eller logik-implementationen.
  * Åtgärda buggen och kör testerna igen för att verifiera att problemet är löst.

### Lägg till ytterligare tester
* Lägg gärna ytterligare tester, exempelvis:
  * Testa flera knapptryckningar i snabb följd och verifiera debounce-funktionalitet.
  * Testa extrema temperaturvärden (negativa, mycket höga).
  * Simulera timeout för flera timers samtidigt.
  * Testa vad som händer vid ogiltiga EEPROM-värden.
  * Testa upprepade toggle-operationer.
  * Testa temperaturavläsning om sensorn inte är initialiserad.
  * Verifiera att knappens release-tillstånd hanteras korrekt.

## Utvärdering
* Uppfyller era tester alla krav? Är ni redo för SW/HW-integrationstestning?
* Vilka delar av systemlogiken var svårast att testa?
* Hittades några buggar under testningen? Hur gick felsökningen till?
* Vilka fördelar ger det att kunna kontrollera hårdvarubeteende via stubklasser?
* Hur skiljer sig komponenttester från unittester i komplexitet och omfattning?
* Vilka lärdomar tar ni med er om testbarhet och design?
* Några övriga synpunkter på lektionen?

## Nästa lektion
* Manuell SW/HW-integrationstestning med fysisk hårdvara.
