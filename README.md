# Universal Programmer

for SPI and CAN communication between pc and hardware.

This software is actually compatible to the following hardware:

| Hardware List |
|-|
| `Arduino Nano atmega328p` |
| `Arduino Uno atmega328p` |
| `Arduino Mega atmega2560` |
| `Arduino Nano Every atmega4809` |

#### Driver information
To use the hardware with this software you need a virtual com port driver (for Windows OS you can use CH340). Otherwise the device cannot be found.

#### Hardware & Software information
Please note: for any hardware you need more electronics to use this fully with the software (see documentation)\
user manual: https://drive.google.com/file/d/17PNFl44WY-SDedSeV-k9Ff4tLWkQUlAu/view \
In case of software updates and changes, some content from user manual may differ to the latest available version.

You can use the program for free (free version) (since release 1.0.1.1 or higher).\
If you would like to unlock all functions without limits (full version), you need a license key.

feature | free version | full version |
|-|-|-|
Arduino Programmer | yes | yes |
Integrated program update function | no | yes |
tool objects limits | max. 1 (e.g. 1 signal) | limited to software on hardware |
read out hardware | no | yes (if supported from software on hardware) |

## Installation
### .NET6 version (Windows OS only) - update support ended
---
You only need to download the latest .zip file and extract into your favourite folder.\
To run the application you need .NET Framework 6.0 runtime
| Version | Download                |
|-|-|
| `latest` `release` | https://github.com/LMCJC/Universal-Programmer/raw/main/release/latest.zip |
| `x64` | https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-desktop-6.0.32-windows-x64-installer |
| `x86` | https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-desktop-6.0.32-windows-x86-installer |