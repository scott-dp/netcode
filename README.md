# UDPRollbaCPP
[Lenke til CI](https://github.com/scott-dp/netcode/actions)  
[Lenke til CD](https://github.com/scott-dp/netcodeUnix/actions)  

## Hva er UDPRollbaCPP?
<p>
  UDPRollbaCPP er en løsning til en prosjektoppgave i IDATT2104 - Nettverksprogrammering. Oppgaven går ut på å implementere simpel netcode for å skape synkronisitet av spill.
</p>

## Funksjonalitet
  <ul>
    <li>
      <p>Klient - tjener arkitektur: En server kjører på en AWS ubuntu maskin med continuous deployment fra repoet "netcode unix" (https://github.com/scott-dp/netcodeUnix), jeg måtte lage et eget repo for server kode som kan kjøre på linux maskinen til server, ettersom at jeg har utviklet på en windows maskin, og koden i dette repoet er kode for windows.</p>
      <p>Hvis man starer en klient så kjører event loopen til Client klassen som er implementert, den kommuniserer med UDP til AWS serveren. Når man starter en klient sender den en UDP pakke med payload "idgen" til server, dette er på en måte en forespørsel om å få en ID fra server og bli med i spillet. Den får da en svarpakke fra server med payload som inneholder en generert spiller id som klienten kan bruke. I ID svarpakken fra server får klient også tilsendt eventuelle allerede tilkoblede spillere serialisert. Server kringkaster også til alle andre oppkoblede klienter at en ny spiller har blitt med. </p>
      <p>Hver gang en spiller oppdatering skjer så sendes en pakke til server med denne oppdateringen til server. Autoritativ server spill tilstand oppdateres med den nye oppdateringen, og denne oppdaterte tilstanden kringkastes til alle de klienter som er tilkoblet spillet. Den lokale spilltilstanden hos klientene oppdateres da med denne server oppdateringen.</p>
    </li>
    <li>
      <p>Spill funksjonalitet: Et veldig simpelt "spill" ble implementert hvor man kan kontrellere en spiller med tastetrykk på W(opp), A(venstre), S(høyre) og D(ned). Spilleren beveger seg i retningen man har trykket frem til en annen tast er trykket. Man ser spiller figuren til alle andre klienter som kjører og ser deres bevegelse, som man får gjennom serveren.</p>
    </li>
    <li>
      <p>Rollback netcode: Måten netcode er implementert her er at hver spiller har en fart og denne farten brukes til å oppdatere hver spiller for hver ny frame som tegnes. Denne farten antas å være korrekt helt opptil en oppdatering fra server kommer som sier noe annet. På denne måten predikerer hver klient hva den neste bevegelsen til alle de andre klientene er ved å se på hva den lagrede farten deres er. Dette kan jo såklart være en feilpredikering og dette rettes opp i når oppdatering kommer til server, der hver lokal spiller sin tilstand sjekeks opp mot server, og eventuelt trekkes tilbake til den riktige tilstanden gitt av server om den lokale tilstanden ikke stemmer.</p>
    </li>
    <li>
      Visning av spill tilstand: Spilltilstanden tegnes bare opp med ASCII grafikk i konsollen som executable filen kjøres i.
    </li>
  </ul>

## Fremtidig arbeid
<p>
  En mangel som jeg kunne lagt til i fremtidig arbeid ville vært istedenfor å sette alle spillere tilbake til server tilstanden hvis deres posisjon er feil, kunne jeg kjørt tilbake til siste riktig tilstand, kjøre en resimulering av spillet med de gitte oppdateringene, da ville aldri den lokale spilleren trekkes tilbake til server tilstanden når en server oppdatering kommer. Dette ville da vært sann rollback netcode, i motsetning til det jeg har implementert.
</p>
<p>
  En ting som kunne gjort programmet litt bedre hadde vært å introdusere en toleranse for rollbacken, slik at hvis en spiller var 1 posisjon feil så lot man det gå og ikke rullet tilbake.
<p>
  En annen ting jeg kunne lagt til er visning av spillet med et ordentlig grafikk bibloitek istedenfor å bruke ASCII grafikk.
</p>
<p>
  Jeg kunne også lagt til tester for å teste programmet.
</p>
<p>
  Arv kunne også vært noe jeg kunne brukt mer i programmet. Server og klient klassene hadde ganske mye til felles (mer enn jeg trodde de kom til å ha da jeg startet å utvikle) og kunne implementert en klasse de kunne arvet fra for å hindre unødvendig repetering av kode.
</p>
<p>
  Klient sender en avkoblingsmelding til server når den kobler av slik at server kan fjerne den klient fra sin tilstand og gi den oppdateringen til de andre tilkoblede klientene.
</p>

## Eksterne avhengigheter
<p>
  mswsock og ws2_32: brukt for å sette opp UDP sockets på klient og server side.
</p>
<p>
  pthread: brukt på unix versjon av programmet for tråder.
</p>

## Installasjon
  Hent fra main branch av dette git repoet. Du kan enten kjøre 
  ```
  ./eksamen.exe c
  ```
  for å kjøre en klient (kobler seg automatisk opp til hostet server) eller kjøre
  ```
  ./eksamen.exe s
  ```
  for å kjøre server (ikke egentlig nødvendig siden server er hostet). Hvis du vil kjøre egen server instans må du endre på koden og legge inn riktig server port og server ip for din kjøring i main.cpp på linje 10 og 11, så kompilere på nytt og kjøre server og klient som du vil.
### Kompilering
  For å kompilere med g++ på windows kan du bruke kommandoen
  ```
  g++ -std=c++17 -o eksamen  main.cpp src/Client.cpp src/Server.cpp src/Game/Player.cpp src/Game/State.cpp src/Game/LocalState.cpp -lws2_32 -lmswsock
  ```
  Eller hvis du har cmake kan du åpne terminalen i roten av prosjektet og skrive i terminalen
  ```
  mkdir build
  cd build
  cmake ..
  cmake --build .
  ```
  og du kan bruke eksamen.exe i "build" mappen på samme måte som beskrevet ovenfor


## Trådmodell
### Klient
<p>
  Det ble brukt 3 hovedtråder i klienten. En tråd som kjørte "spill event loopen", den lyttet til input fra tastaturet, oppdaterte den lokale tilstanden hvis W, A, S eller D ble trykket på, og sendte den oppdateringen til server. Den andre tråden kjørte en "motta loop" som lyttet til socketen sin og mottok oppdateringer fra server. Den tredje og siste tråden kjørte "tegne tråden" og tegnet spill tilstanden for hver frame. Det ble også brukt arbeidstråder som utførte arbeidsoppgaver som å sjekke oppdatering fra server og eventuelt oppdatere lokal tilstand. Det ble brukt en mutex i klienten som ble låst da man skulle gjøre ett eller annet med tilstanden "localState". En atomic boolean "runClient" ble også brukt i while løkkene til hver av hovedtrådene.
</p>
<p>
  Det var også 3 hovedtråder brukt i serveren. Den første tegnet tilstanden for hver frame. Den andre lyttet til tastaturet for å sjekke om quit kommandoen "Q" ble trykket på. I den siste "hovedtråden" hos server kjørte en løkke som lyttet til trafikk på socketen sin. Det ble også brukt arbeidstråder i serveren. Her ble de brukt for å kringkaste oppdateringer til klientene. Det var tre mutexer brukt i serveren. En for å låse tilstanden "authoritativeState" hvis noe arbeid på den skulle gjøres. En annen for å låse settet som holdt på socket adressene til alle de tilkoblede klientene. Den siste for å låse spiller id variabelen, som server brukte for å generere spiller id til klienter som ville koble på. På samme måte som i klient ble en atomic boolean "runServer" brukt i alle while løkkene for å sjekke om server skulle fortsette å kjøre.
</p>
