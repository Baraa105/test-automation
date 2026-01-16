# L01 - Kursintroduktion

## Dagordning
* Introduktion - Genomgång av kursens innehåll samt upplägg.
* Implementation samt tester för en smart temperatursensor.

## Mål med lektionen
* Förstå kursens upplägg, mål och examinationsform.
* Känna till varför det är önskvärt att automatisera tester.
* Känna till skillnaden mellan unit-, komponent- och integrationstester.
* Förstå grunderna i Google Test-ramverket.
* Se exempel på implementation av en smart temperatursensor.

## Instruktioner

### Förberedelser
* Läs igenom projektbeskrivningen för kursen [här](../../project/README.md).
* Läs igenom [följande dokument](./cpp/) för bakgrund gällande C++, klasser och interfaces.
* Följ installations och användarinstruktionerna [här](../../README.md#installations--och-användarinstruktioner).

### Köra tester
Navigera till testmappen och kör testerna via kommandot `make`:

```bash
cd library/test
make
```

### Skriva tester
* Öppna testfilen [smart_test.cpp](../../library/test/driver/tempsensor/smart_test.cpp).
* Ta bort `#ifdef LECTURE1` (rad 16) samt motsvarande `#endif` (rad 196) för att aktivera testerna.
* Implementera testfallen enligt kommentarerna i filen.

### Demonstration
* En smart temperatursensor implementeras i helklass.
* Ni får möjlighet att skriva unittester för den smarta temperatursensorn.

## Utvärdering
* Några synpunkter på lektionen i sig?

## Nästa lektion
* Unittester för en GPIO-driver.
