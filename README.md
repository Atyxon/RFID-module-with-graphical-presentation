# RFID module with graphical presentation
## Table of contents
* [General info](#general-info)
* [Technologies](#technologies)

## General info
This project uses RFID module to read PICC UID and light green LED is the UID is accepted, or red LED if it not.
<br>File containing code is `RFID_module/RFID_mofule.ino`

### How it works in action
https://user-images.githubusercontent.com/75041222/224062174-befe59af-3fb8-4ef6-92df-66d8912d7328.mp4

### Integration with Unity Engine
This project can communicate with Unity Graphical Engine via serial port, in example below RFID module read if PICC card is valid and send output to Unity, if card is valid, then screen next to door change color to green and door opening animation start, but if the card is not accepted, screen turn red and doors stay closed.
<br>
<br>Integration with Unity can be used as concept or demo of product.
<br> code responsible for for reading data from serial port inside Unity is `SerialReader.cs`

https://user-images.githubusercontent.com/75041222/224062967-2255bd43-483d-4339-b5b0-b9a4739a074b.mp4

### Schematic of project
<img src="https://user-images.githubusercontent.com/75041222/224063904-c7d8916e-0faf-40ef-9380-762adb8ca879.png" width="467" height="486">

## Technologies
Project is created with:
* C++/C#
* Unity Engine
* Fritzing

Electric components used:
* Arduino 101
* RFID-RC522 module
* 2x LED diodes
* 2x 220Ω resistors
* 11x wires
