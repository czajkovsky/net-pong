Net-Pong
====

Prosta gra sieciowa - Pong dla 2 graczy. Wykonana w ramach przedmiotu Sieci Komputerowe 2 na Politechnice Poznańskiej (prowadzący [mgr inż. Maurycy Zamorski](http://www.cs.put.poznan.pl/mzamorski/))

Używa **Box2d** jako silnik fizyczny oraz **SFML** jako biblioteka multimediów.

Obliczenia związane z fizyką gry wykonywane są po stronie serwera. Aplikacja działa wielowątkowo, w oddzielnych wątkach realizowane są:
* komunikacja
* wyświetlanie GUI
* silnik gry (tylko po stronie serwera)

Aby zachować spójność zastosowano mechanizm pamięci współdzielonej.

### Sterowanie
<table>
  <tr>
    <th>Klawisz</th><th>Akcja</th>
  </tr>
  <tr>
    <td><code>strzałki</code></td><td>sterowanie lewo/prawo</td>
  </tr>
  <tr>
    <td><code>ESC</code></td><td>zamknięcie gry</td>
  </tr>
</table>


### Protokół
Do realizacji projektu został zastosowany prosty protokół:
<table>
  <tr>
    <th>Kod</th><th>Nazwa</th><th>Opis</th>
  </tr>
  <tr>
    <td><code>0xAB</code></td>
    <td><code>REQUEST_UPDATE</code></td>
    <td>klient prosi o stan gry</td>
  </tr>
  <tr>
    <td><code>0x12</code></td>
    <td><code>REQUEST_END</code></td>
    <td>klient/server chce zakończyć grę</td>
  </tr>
  <tr>
    <td><code>0x11</code></td>
    <td><code>UPDATE_STATE</code></td>
    <td>server odpowiada jaki jest stan gry</td>
  </tr>
  <tr>
    <td><code>0x13</code></td>
    <td><code>END_ACK</code></td>
    <td>klient potwierdza odbiór informacji o końcu gry</td>
  </tr>
</table>

### Kompilacja
```
make
```

### Uruchomienie
#### Serwer

Domyślny serwer (port <code>4000</code>).
```
./pong -s
```

Serwer działający pod konkretnym portem
```
./pong -s port_number
```

#### Klient

Domyślny klient (port <code>4000</code>, server address <code>127.0.0.1</code>).
```
./pong -c
```

Klient łączący się z konkretnym adresem oraz portem
```
./pong -c 127.0.0.1 5000
```

### Zrzuty aplikacji

![pong screenshot](./assets/screenshot.png)
