#### Description
Chess clocks are used to keep track of time for each player. Once player makes move, hits the button and opponent's time starts to count down.  

This is indeed very old hobby project, sitting in my dusty hard drive. I slightly organized the content and shared online. Maybe helps somebody. :slightly_smiling_face:  

#### Notes on project
- It is based on PIC16F877 micro-controller, uses 32.768 KHz external xtal as source of "seconds tic".  
- Hi-Tech PICC Lite compiler and MPLAB IDE was used. It seems those are retired, anymore. :thinking:  
  - A starter page is here: https://www.cs.ucr.edu/~eblock/pages/pictools/install.html  
- It was developed using Proteus 7.7. Design file (and its PDF version) can be found under [schematics](schematics) folder.  
- A snip of simulation environment and breadboard prototype of design can be seen under [images](images) folder.  
- In [appendix](appendix) folder, there is simple guide how to flash hex file to pic device. It is based on JDM programmer and IC-Prog. Very old style. :grinning:  

#### Resources
Origin repo at github.com/eardali

#### License
Since this work includes some hardware stuff, I am not sure which license is more appropriate, I choose as below.  

This work is licensed under
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cc-by-nc-sa].  

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png
[cc-by-nc-sa-shield]: https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg
