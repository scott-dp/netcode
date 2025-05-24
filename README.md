command line compilation for windows:
g++ -std=c++17 -o eksamen  main.cpp src/Client.cpp src/Server.cpp src/Game/Player.cpp src/Game/State.cpp src/Game/LocalState.cpp -lws2_32 -lmswsock

# UDPRollbaCPP
[Lenke til CI](https://github.com/scott-dp/netcode/actions)  
[Lenke til CD](https://github.com/scott-dp/netcodeUnix/actions)  

## Hva er UDPRollbaCPP?
<p>
  UDPRollbaCPP er en løsning til en prosjektoppgave i IDATT2104 - Nettverksprogrammering. Oppgaven går ut på å implementere simpel netcode for å skape synkronisitet av spill.
</p>

## Funksjonalitet
<p>
  <ul>
    <li>
      Klient - tjener arkitektur: En server kjører på en AWS ubuntu maskin med continuous deployment fra repoet "netcode unix" (https://github.com/scott-dp/netcodeUnix), jeg måtte lage et eget repo for server kode som kan kjøre på linux maskinen til server, ettersom at jeg har utviklet på en windows maskin, og koden i dette repoet er kode for windows. 
      Hvis man starer en klient så kjører event loopen til Client klassen som er implementert, den kommuniserer med UDP til AWS serveren. Når man starter en klient sender den en UDP pakke med payload "idgen" til server, dette er på en måte en forespørsel om å få en ID fra server og bli med i spillet. Den får da en svarpakke fra server med payload som inneholder en generert spiller id som klienten kan bruke. I ID svarpakken fra server får klient også tilsendt eventuelle allerede tilkoblede spillere serialisert. Server kringkaster også til alle andre oppkoblede klienter at en ny spiller har blitt med. 
      Hver gang en spiller oppdatering skjer så sendes en pakke til server med denne oppdateringen til server. Autoritativ server spill tilstand oppdateres med den nye oppdateringen, og denne oppdaterte tilstanden kringkastes til alle de klienter som er tilkoblet spillet. Den lokale spilltilstanden hos klientene oppdateres da med denne server oppdateringen.
    </li>
    <li>
      Spill funksjonalitet: Et veldig simpelt "spill" ble implementert hvor man kan kontrellere en spiller med tastetrykk på W(opp), A(venstre), S(høyre) og D(ned). Spilleren beveger seg i retningen man har trykket frem til en annen tast er trykket. Man ser spiller figuren til alle andre klienter som kjører og ser deres bevegelse, som man får gjennom serveren.
    </li>
    <li>
      Rollback netcode: Måten netcode er implementert her er at hver spiller har en fart og denne farten brukes til å oppdatere hver spiller for hver ny frame som tegnes. Denne farten antas å være korrekt helt opptil en oppdatering fra server kommer som sier noe annet. På denne måten predikerer hver klient hva den neste bevegelsen til alle de andre klientene er ved å se på hva den lagrede farten deres er. Dette kan jo såklart være en feilpredikering og dette rettes opp i når oppdatering kommer til server, der hver lokal spiller sin tilstand sjekeks opp mot server, og eventuelt trekkes tilbake til den riktige tilstanden gitt av server om den lokale tilstanden ikke stemmer.
    </li>
  </ul>
</p>
