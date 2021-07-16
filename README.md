# Arduino bus mouse tester

Arduino project creates to help testing bus mice with quadrature encoders or even optical mouse sensors with quadrature output. Just DB9 male connector and a couple of wires. Its perfectly works with Amiga mouse, but rewiring required for others bus mouse. 

In case of precision, at least one pin of mouse encoders should be connected to [interruptable pins](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt). By default, Arduino pins are connected to the mouse by the following schema:

| Arduino | D0 | D1 | D2 | D4 | D5 | D6 | D7 | +5v | GND |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| Mouse | LMB | MMB | RMB | X2 | X1 | Y1 | Y2 | +5v | GND |

## Bus mouse pinouts 
List of bus mouse with DB9 female connector.

| DB9 pin | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| Amiga | Y1 | X1 | Y2 | X2 | MMB | LMB | +5v | GND | RMB |
| Atari ST | X1 | X2 | Y1 | Y2 | MMB | LMB | +5v | GND | RMB |
| Mac Plus | GND | VCC | GND | X2 | X1 | NONE | LMB | Y2 | Y1 |
| Kempston | +5v | X1 | Y2 | LMB | RMB | GND | NONE | Y1 | X2 |
| Datel | +5v | X1 | Y2 | LMB | RMB | GND | NONE | Y1 | X2 |
| PC-98 | +5v | X1 | X2 | Y1 | Y2 | LMB | MMB | RMB | GND |

## Installation

Project requires [Arduino Encoder library](https://www.arduino.cc/reference/en/libraries/encoder/) to build.

## Screenshots