# Universal Programmer

für SPI- und CAN-Kommunikation zwischen PC und Hardware. Für deine eigenen Modellbahn Projekte!

Diese Software ist derzeit mit folgender Hardware kompatibel:

| Hardware-Liste                        | Projekt-Liste (mit neuester Version)                      |
|---------------------------------------|----------------------------------------------------------|
| `Arduino Nano atmega328p`<br>`Arduino Uno atmega328p` | DCC Licht-Signaldecoder, DCC Servodecoder, Servo-Control-IO,<br>LocoNet(R) Feedback, RunFlashLight-Control |
| `Arduino Mega atmega2560`            | RunFlashLight-Control                                   |
| `Arduino Nano Every atmega4809`      | DCC Licht-Signaldecoder                                 |

#### Treiberinformationen
Um die Hardware mit dieser Software zu verwenden, benötigen du einen virtuellen COM-Port-Treiber (unter Windows kann der CH340 verwendet werden). Andernfalls kann das Gerät nicht gefunden werden.

#### Hardware- & Softwareinformationen
Bitte beachte: Für jede Hardware wird eine zusätzliche Elektronik benötigt, um diese Software vollständig nutzen zu können (siehe Dokumentation).<br>
Benutzerhandbuch: https://e.pcloud.link/publink/show?code=XZ1PeUZyk0BEzXyK6Vph37g8wQ1pHxeox4k <br>
Bei Software-Updates und Änderungen kann der Inhalt des Benutzerhandbuchs von der neuesten verfügbaren Version abweichen.

Das Programm kann kostenlos genutzt werden (freie Version) (seit Version 1.0.1.1 oder höher).<br>
Um alle Funktionen ohne Einschränkungen freizuschalten (Vollversion), benötigen du einen Lizenzschlüssel.<br>
Bitte beachte, dass die neueste Versionsnummer für die Aktivierung verwendet wird.

| Funktion                             | Kostenlose Version | Vollversion                      |
|--------------------------------------|--------------------|----------------------------------|
| Arduino-Programmer                | ja                 | ja                               |
| Integrierte Programm-Update-Funktion | nein               | ja                               |
| Einschränkungen bei Tool-Objekten    | max. 1 (z.B. 1 Signal oder 2 Sensoren) | auf Software auf Hardware begrenzt |
| Hardware auslesen                    | nein               | ja (sofern von Software auf Hardware unterstützt) |
| Persönlicher Support-Chat             | ja                 | ja                               |

## Installation
### .NET8-Version (Windows, Linux, MacOS)
---
Einfach die Setup_8.zip herunterladen und in den gewünschten Ordner extrahieren.<br>
Die weiteren Schritte sind unten für jedes Betriebssystem erläutert.
| Beschreibung                          | Download                                                   |
|---------------------------------------|----------------------------------------------------------|
| `setup` `release`                    | https://github.com/LMCJC/Universal-Programmer/raw/main/update/files/Setup_8.zip |

#### Windows
Um die Anwendung auszuführen, ist die .NET Framework 8.0 Runtime erforderlich.
| Beschreibung                          | Download                                                   |
|---------------------------------------|----------------------------------------------------------|
| `x64` `runtime`                      | https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-desktop-8.0.20-windows-x64-installer |

##### Einrichtung
Starte **LMCJC UP-Setup.exe** im extrahierten Pfad.
##### Anwendung ausführen
Wenn die Installation abgeschlossen ist, findest du die **LMCJC Programmer.exe** im Anwendungsordner.

#### Linux Debian / MacOS
##### Installationsanleitung (YouTube-Video) für Linux
[![Installations-Tutorial](https://img.youtube.com/vi/QSoDDwdtRv8/0.jpg)](https://www.youtube.com/watch?v=QSoDDwdtRv8)<br>
##### Einrichtung
Um die Anwendung auszuführen, ist es nur notwendig das Startskript aus dem **Scripts**-Ordner zu starten.<br>
Mache das Script ausführbar und starte es im Terminal.<br>
Linux Debian:
```
chmod +x debian_start.sh (oder über das Eigenschaften-Menü ändern)
./debian_start.sh
```
MacOS:
```
chmod +x macos_start.sh
./macos_start.sh
```
***Die Einrichtung installiert die .NET 8.0-Runtime und Abhängigkeiten (Administratorrechte erforderlich).***<br>
##### Programm starten
Wenn die Einrichtung abgeschlossen ist, findest du einen **StartScripts**-Ordner im Anwendungsordner.<br>
Starte folgendes Skript im Terminal.<br>
*Wenn das gnome-terminal installiert ist, kann die Anwendung über den Starter-Link **LMCJC Programmer Linux** im Programmordner mit Doppelklick gestartet werden!*<br><br>
Im **StartScripts**-Ordner:<br>
Linux Debian:
```
./debian_start.sh
```
<br>
MacOS:
```
./macos_start.sh
```
oder ziehe die .sh-Datei in das Terminal und bestätige dann mit der Eingabetaste.
<br>

### .NET6-Version (nur für Windows) - Support eingestellt
---
Es wird nur die neueste .zip-Datei benötigt, diese kann in dem bevorzugten Ordner extrahiert werden.<br>
Um die Anwendung auszuführen, benötigst du die .NET Framework 6.0 Runtime.
| Version | Download |
|-|-|
| `latest` `release` | ~~https://github.com/LMCJC/Universal-Programmer/raw/main/release/latest.zip~~ |
| `x64` | ~~https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-desktop-6.0.32-windows-x64-installer~~ |
| `x86` | ~~https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-desktop-6.0.32-windows-x86-installer~~ |