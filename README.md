Pong
====

Simple Pong game for 2 players. Project was done for Computer Network classes @ PUT ([M.Sc. Maurycy Zamorski](http://www.cs.put.poznan.pl/mzamorski/)).

It uses **Box2d** as physics engine and **SFML** as multimedia library.

### Building
```
make
```

### Running
#### Server

Default server (port <code>4000</code>).
```
./pong -s
```

Server with custom port number.
```
./pong -s port_number
```

#### Client

Default client (port <code>4000</code>, server address <code>127.0.0.1</code>).
```
./pong -c
```

Client with custom port number and server address.
```
./pong -c 127.0.0.1 5000
```

### Screenshots

![pong screenshot](./assets/screenshot.png)
