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
      Klient - tjener arkitektur: En server kjører på en AWS ubuntu maskin med continuous deployment fra repoet [netcode unix](https://github.com/scott-dp/netcodeUnix), jeg måtte lage et eget repo for server kode som kan kjøre på linux maskinen til server, ettersom at jeg har utviklet på en windows maskin, og koden i dette repoet er kode for windows. Hvis man starer en klient kjører event loopen til Client klassen som er implementert, kommuniserer den med UDP til AWS serveren. Når man starter en klient sender den en UDP pakke med payload "idgen" til server. Den får da en svarpakke fra server med payload som inneholder en generert spiller id som klienten kan bruke. I ID svarpakken fra server får klient også tilsendt eventuelle allerede tilkoblede spillere serialisert.
    </li>
    <li>
      Spill funksjonalitet: Et veldig simpelt "spill" ble implementert hvor man kan kontrellere en spiller med tastetrykk på W(opp), A(venstre), S(høyre) og D(ned). Spilleren beveger seg i retningen man har trykket frem til en annen tast er trykket. Man ser spiller figuren til alle andre klienter som kjører og ser deres bevegelse, som man får gjennom serveren.
    </li>
  </ul>
</p>
