# Test och automatisering - Ei24

Repo för kursen Test och automatisering med klassen Ei24, vt26:

## Innehåll
* Kursinformation finns i katalogen [info](./info/README.md).
* Lektionsplaneringar samt lektionsanteckningar finns i katalogen [lectures](./lectures/README.md).
* Biblioteket som test ska skrivas för finns i katalogen [library](./library/README.md).
* Projektbeskrivningen (kursens enda projekt) finns i katalogen [project](./project/README.md).

## Installations- och användarinstruktioner

### Installera Visual Studio Code

Om du använder en Linux-miljö inuti Windows, såsom WSL eller Git bash, installera Visual Studio Code från Microsoft Store.

Däremot om använder en ren Linux-miljö, skriv följande kommando:

```bash
sudo snap install code --classic
```

### Ladda ned och installera WSL

WSL *(Windows Subsystem For Linux)* möjliggör att vi kan köra en Linux-distribution i terminalmiljö på en Windows-dator. Använd med fördel WSL för att utveckla, bygga samt köra tester.

För att ladda ned WSL, börja med att öppna Windows Powershell som administratör. Skriv sedan följande kommandon:

```bash
wsl --install
wsl --set-default-version 2
```

När installationen är klar, öppna Microsoft Store och ladda ned den senaste versionen av Linux-distributionen `Ubuntu`. Sök därmed på `Ubuntu` i Microsoft Store. Ett flertal alternativ kommer dyka upp:
* Notera att befintliga distributioner är daterade efter släppdatum, så exempelvis `Ubuntu 22.04` släpptes i april 2022.
* Välj den senaste befintliga distributionen (som för tillfället är `Ubuntu 24.04 LTS`).

Efter att installationen är slutförd, skriv `Ubuntu` i Windows Search (sökrutan i det nedra vänsta hörnet). Klicka på din Ubuntu-distribution. En svart ruta kommer öppnas, vilket är din Linux-terminal i din Windows-miljö.

Först gången kommer du ombeds att lägga till användarnamn och lösenord, vilket enbart kommer användas i terminalen:
* Välj ett kort användarnamn, så som ditt förnamn.
* Välj ett lämpligt lösenord och se till att spara detta på lämpligt sätt.

Installera nödvändiga paket för att kompilera kod, använda Git med mera:

```bash
sudo apt -y update
sudo apt -y install build-essential make git tree
```

### Installera Google Test

Installera nödvändiga paket för Google Test:

```bash
sudo apt -y install libgtest-dev libgmock-dev cmake
```

Kompilera och installera sedan Google Test-biblioteken:

```bash
cd /usr/src/gtest
sudo cmake .
sudo make
sudo mv lib/*.a /usr/lib
cd ~
```

### Konfigurera SSH-nycklar för GitHub

För att kunna klona repot behöver du skapa en SSH-nyckel och lägga till den i GitHub:

```bash
ssh-keygen
```

Tryck Enter för alla frågor (acceptera standardvärden). Din publika nyckel visas nu med följande kommando:

```bash
cat ~/.ssh/id_rsa.pub
```

Kopiera hela utskriften (börjar med `ssh-rsa` och slutar med ditt användarnamn). 

Gå till GitHub:
1. Logga in på [github.com](https://github.com).
2. Klicka på din profilbild → **Settings**.
3. Välj **SSH and GPG keys** i menyn till vänster.
4. Klicka på **New SSH key**.
5. Ge nyckeln ett namn (exempelvis "WSL Ubuntu") i **Title**-fältet.
6. Klistra in den kopierade nyckeln i **Key**-fältet.
7. Klicka på **Add SSH key**.

### Konfigurera Git

Konfigurera Git med ditt namn och e-postadress:

```bash
git config --global user.name "Ditt Namn"
git config --global user.email "din.email@example.com"
```

### Forka repot på GitHub

Skapa din egen kopia (fork) av repot på GitHub:

1. Gå till [kursrepot](https://github.com/Yrgo-24/test-automation) på GitHub.
2. Klicka på **Fork** uppe till höger.
3. Välj ditt eget konto som destination.
4. Klicka på **Create fork**.

Nu har du en egen kopia av repot på ditt GitHub-konto där du kan göra ändringar. Du kan också
synkronisera ditt forkade repos main-branch med kursrepots motsvarighet. Instruktioner gällande
synkronisering av andra brancher finns [här](#synka-icke-main-branches-från-kursrepot).

### Klona ditt forkade repo lokalt

Klona ditt forkade repo med följande kommando (ersätt `ditt-användarnamn` med ditt GitHub-användarnamn):

```bash
git clone git@github.com:ditt-användarnamn/test-automation.git
```

Dirigera in i repot och lista eventuella filer via följande kommandon:

```bash
cd test-automation/
tree
```

Öppna repot med Visual Studio Code:

```bash
code .
```

Om du inte kan öppna Visual Studio Code med felmeddelande `Exec format error code`, öpppna filen `/etc/wsl.conf` som root user:

```bash
sudo nano /etc/wsl.conf
```

Kommentera ut `systemd=true` såsom visas nedan:

```bash
[boot]
#systemd=true
```

Öppna Powershell och starta om WSL:

```bash
wsl.exe --shutdown
powershell.exe
```

### Verifiera installationen

Testa att kompilera och köra befintliga tester:

```bash
cd library/test
make
```

Om allt är korrekt installerat kommer testsviten att kompilera och köra.

### Spara dina ändringar till GitHub

När du gjort ändringar i koden, spara dem till ditt forkade repo (ersätt `Din beskrivning` med
vad som ändrades på imperative form, exempelvis "Add GPIO driver unit tests").

```bash
git add .
git commit -m "Din beskrivning"
git push origin main
```

Det som görs ovan är att du:
* Lägger till alla ändrade filer för commit.
* Skapar en commit med ett beskrivande meddelande.
* Pushar ändringarna till ditt forkade repo på GitHub.

### Hämta uppdateringar från kursrepot (valfritt)

Om läraren gör uppdateringar i kursrepot kan du hämta dem:

```bash
git remote add upstream git@github.com:Yrgo-24/test-automation.git
git fetch upstream
git merge upstream/main
```

Detta behöver endast göras om du vill synkronisera med ändringar från kursrepot.

### Arbeta med branches (valfritt)

Om du vill experimentera utan att påverka main-branchen kan du skapa en egen branch.
Ersätt `branch-namn` med ditt val av namn, exempelvis *feature-tests*:

```bash
git checkout -b branch-namn
```

Lista samtliga branches:

```bash
git branch
```

Byt till en annan branch `annan-branch`:

```bash
git checkout annan-branch
```

När du pushar en ny branch till GitHub:

```bash
git push -u origin branch-namn
```

### Synka icke-main branches från kursrepot

Om det finns fler brancher än `main` i kursrepot och du vill synka dessa till din egen fork:

1. Lägg till kursrepot som remote med namnet `upstream`:

```bash
git remote add upstream git@github.com:Yrgo-24/test-automation.git
```

2. Hämta alla branches från kursrepot (dvs. `upstream`):

```bash
git fetch upstream
```

3. Skapa och byt till en lokal branch som spårar upstream-branchen du vill synka.  
**OBS!** Byt ut `<BRANCH_NAME>` mot den branch du vill synka:

```bash
git checkout -b <BRANCH_NAME> upstream/<BRANCH_NAME>
```

4. Pusha branchen till din egen fork på GitHub:

```bash
git push -u origin <BRANCH_NAME>
```

Nu har du en kopia av den specifika branchen från kursrepot både lokalt och i din egen fork.
