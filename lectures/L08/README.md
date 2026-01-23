# L08 - SW/HW-integrationstestning (del I)

## Dagordning
* Introduktion till SW/HW-integrationstestning och skillnader mot komponenttester.
* Manuell testning av systemet på fysisk hårdvara (Arduino/ATmega328P).
* Testning av watchdog-timern, interrupts och systemlogiken.
* End-to-end verifiering av hela systemet.

## Mål med lektionen
* Förstå skillnaden mellan komponenttester och SW/HW-integrationstester.
* Känna till när man använder sig av SW/HW-integrationstester i stället för unit- eller komponenttester.
* Kunna utföra manuell end-to-end testning av hela systemet.
* **Huvudmål**: Verifiera att systemet fungerar korrekt på riktig hårdvara och identifiera eventuella problem som endast uppstår vid körning på target-hårdvara.

## Förutsättningar
* Alla komponenttester från L07 ska vara klara och gå igenom.
* Tillgång till Arduino/ATmega328P med nödvändig hårdvara (knappar, lysdiod, temperatursensor). 
* Fungerande utvecklingsmiljö för att bygga och ladda upp kod till Arduino (Microchip Studio eller PlatformIO).

***OBS!** Under lektionen finns en Arduino/ATmega328P (med nödvändig hårdvara) att låna.  
Ta dock gärna med en egen för att inte behöva vänta på att få tillgång till hårdvara vid testmomenten.*

## Teori: Komponenttester vs SW/HW-integrationstester

### Komponenttester
* Testas i isolerad miljö på utvecklingsdator (exempelvis PC/Mac/Linux).
* Använder stubklasser för att simulera hårdvara.
* Snabba att köra och ger deterministiska resultat.
* Verifierar logik och mjukvarukomponenter.
* **Nackdelar**: Kan inte upptäcka hårdvarurelaterade problem.

### SW/HW-integrationstester
* Testas på faktisk target-hårdvara och använder därmed riktig hårdvara (GPIO, timers, EEPROM, sensorer).
* Kan upptäcka timing-problem, hårdvarufel, och verkliga miljöförhållanden (höga temperatur kan exempelvis medföra problem i vissa inbyggda system).
* Kompletterar komponenttester genom att verifiera hela systemet end-to-end.
* **Nackdelar**: Långsammare att köra, kan vara icke-deterministiska.

## Instruktioner

### Förberedelser
1. Se till att alla komponenttester från L07 går igenom.
2. Om ni tog med ett eget system, kontrollera att er Arduino/ATmega328P är korrekt uppsatt med:
   - Knappar anslutna till pin 12 - 13.
   - En lysdiod ansluten till pin 8.
   - En temperatursensor (TMP36) ansluten till analog pin A2.
3. Verifiera att ni kan bygga och ladda upp koden till target.

### Manuell testning

#### 1. Basic funktionalitet
* **Power-on test**: Ladda upp programmet och öppna en seriell monitor för att verifiera att systemet startar korrekt och skriver ut förväntade meddelanden.

#### 2. Toggle-funktionalitet
* Tryck på toggle-knappen (pin 12) och verifiera att lysdioden börjar blinka.
* Tryck igen och verifiera att lysdioden slutar blinka.
* Mät blinkhastigheten - stämmer den med förväntad timing?
* Testa upprepade tryckningar för att säkerställa debounce fungerar - upprepade knapptryckningar inom 300 ms ska ignoreras.

#### 3. Temperaturavläsning
* Tryck på temperaturknappen och verifiera att temperaturen skrivs ut via seriell port.
* Jämför med rumstemperatur - är värdet rimligt?
* Testa att värma sensorn (med handen) och verifiera att temperaturen ökar.
* Verifiera att automatisk temperaturutskrift sker enligt timer.
* Testa upprepade tryckningar för att säkerställa debounce fungerar - upprepade knapptryckningar inom 300 ms ska ignoreras.

#### 4. Watchdog timer
* Verifiera att watchdog timer är aktiverad vid uppstart.
* För att testa watchdog-funktionaliteten: Introducera en bugg i form av en oändlig loop i en interrupt-handler, exempelvis genom att metoden `Logic::handleButtonEvent()` inte termineras så länge
en av knapparna hålls nedtryckt. När ni gör detta kommer `Logic::run()` inte längre köras och 
watchdog-timern kommer därmed inte återställas i tid.
* Verifiera att systemet resettar automatiskt efter watchdog-timeout.
* Kontrollera att systemet startar om korrekt efter watchdog reset.
* Ta bort den tillsatta buggen och verifiera att systemet fungerar normalt igen.

#### 5. EEPROM-persistens
* Aktivera toggle-timern så att lysdioden börjar blinka och stäng sedan av systemet.
* Starta om och verifiera att toggle-tillståndet återställs från EEPROM - Lysdioden bör direkt börja blinka efter omstart och utskriften `Toggle timer enabled!` bör skrivas ut i terminalen.
* Inaktivera toggle-timern så att lysdioden släcks och stäng sedan av systemet.
* Starta om och verifiera att toggle-tillståndet fortfarande är inaktivt - Lysdioden bör vara släckt.

#### 6. End-to-end scenario
**OBS!** Interrupt-hantering och debounce-funktionalitet testas redan i sektionerna 2-3 ovan.

Kör ett komplett scenario:
1. Starta systemet från reset.
2. Tryck på toggle-knappen → lysdioden ska blinka.
3. Tryck på temperaturknappen → temperatur ska skrivas ut.
4. Vänta på automatisk temperaturavläsning.
5. Tryck på toggle-knappen igen → lysdioden ska sluta blinka.
6. Tryck på toggle-knappen igen → lysdioden ska börja blinka.
7. Resetta systemet och verifiera att toggle-tillståndet är aktivt vid start, dvs. lysdioden ska börja blinka efter omstart.
8. Tryck på toggle-knappen igen → lysdioden ska sluta blinka.
9. Resetta systemet och verifiera att toggle-tillståndet är inaktivt vid start, dvs. lysdioden ska vara släckt efter omstart.

### Dokumentera testresultat
Skapa ett testprotokoll där ni dokumenterar:
* Vilka tester som kördes.
* Förväntat vs faktiskt resultat.
* Eventuella buggar eller problem som upptäcktes.
* Tidsåtgång för varje test.

### Felsökning och buggfixar
* Om tester indikerar att buggar förekommer i systemlogiken efter testning på target:
  * Analysera testresultatet noggrant för att identifiera rotorsaken.
  * Kontrollera om problemet är hårdvarurelaterat (felaktig koppling, trasig komponent) eller mjukvarurelaterat.
  * Använd seriell output för debugging - lägg till extra loggning vid behov.
  * Jämför beteendet med komponenttesterna - fungerar samma logik i stubbad miljö?
  * Åtgärda buggen och kör testerna igen för att verifiera att problemet är löst.

## Vanliga problem och lösningar

### Problem: Lysdioden blinkar inte med rätt hastighet
* **Orsak**: Timer-konfiguration eller klock-hastighet.
* **Lösning**: Verifiera timer-prescaler och jämför med förväntad frekvens.

### Problem: Temperaturavläsning ger konstiga värden
* **Orsak**: ADC-konfiguration, felaktig spänningsreferens, eller dålig koppling.
* **Lösning**: Kontrollera hårdvarukoppling och ADC-inställningar.

### Problem: Knapptryckningar registreras flera gånger
* **Orsak**: Debounce fungerar inte korrekt.
* **Lösning**: Öka debounce-tiden eller kontrollera att debounce-timer fungerar.

## Utvärdering
* Fungerade systemet som förväntat på hårdvaran?
* Vilka skillnader upptäckte ni mellan komponenttester och hårdvarutester?
* Hittades några buggar som inte upptäcktes i komponenttesterna? Varför?
* Hur fungerade watchdog timer och interrupt-hantering?
* Vilka utmaningar fanns med manuell testning?
* Vilka fördelar skulle automatiserad testning ge?
* Några övriga synpunkter på lektionen?

## Nästa lektion
* Automatisering av tester genom att skicka kommandon och läsa svar från hårdvaran.
