/* Projekt: DCC Signaldecoder fuer die Roco/Fleischmann z21 Zentrale; mit allen Zentralen kompatibel
 * Autor: MineModellbahn (Lukas)
 * Webseite: www.YouTube.com/maerklinde/videos, www.minemodellbahn.de/dcc-signaldecoder
 * Video: https://youtu.be/Am3XhZEi6sM
 * Version: 2.5  public beta
 * Beschreibung: Dieses Programm ist ausgelegt fuer die Ansteuerung von einfachen LEDs mit der Roco/Fleischmann z21 Zentrale.
 *               Es gibt eine Option, um den Offset der z21 zu entfernen
 *               Beachte auch das Video, um die Konfiguration besser zu verstehen.
 *               
 * Dir gefällt das Projekt? Dann würde ich mich sehr über eine kleine Spende freuen :)
 *  Spendenlink: https://www.paypal.com/paypalme/lukasmarek
 * Quellen: DCC_Basis_ACC_Decoder Beispiel (wird in der Bibliothek mitgeliefert)
 */

#define Num_Adressen 16 // 0-16 = 17

//#define Startadresse 600 //erste Adresse, optional kann auch immer eine eigene Adresse gewaehlt werden
#define helligkeit_gelb 3 // hier kann die Helligkeit der gelben LED eingestellt werden: 0 = ohne dimmen -> 1 < ... dunkler (max. 200)
#define helligkeit_weiss 10 // hier kann die Helligkeit der weissen LED eingestellt werden: 0 = ohne dimmen -> 1 < ... dunkler (max. 200)
#define Uebergangszeit 500 // Pause in Millisekunden, zwischen naechsten Signalbild (mind. 300, max. 3000)

//#define z21_standard //wenn du an der z21 keine Einstellungen mit dem Offset geändert hast, aktiviere diese Funktion um Offset Fehler zu vermeiden

#define betafunction //zum testen der neuen Funktionen aktivieren, siehe changelog (bei Betaversion standardmaeßig aktiviert)
#define UI_ACCESS 666 // muss geschalten werden, damit über das UI konfiguriert werden kann

/* 
 * ### KEINE NEUEN WERTE AB HIER EINTRAGEN OHNE KENNTNISSE ### AENDERUNGEN VORBEHALTEN UND DUERFEN VORGESCHLAGEN WERDEN ###
 */

//Bibliotheken einbinden, ohne diese gibt es keine Funktion!
#include <DCC_Decoder.h>
#ifdef betafunction
  #ifdef UI_ACCESS
    #include <EEPROM.h>
  #endif
#endif

typedef struct DCC_Programdata {
  int  address;   // Adresse festlegen
  byte outputpin; // Gibt Pin zum schalten weiter
  byte dccstate;  // speichert den Zustand der DCC Adresse
  byte switchpin, Signalmode;
};
#ifdef UI_ACCESS
DCC_Programdata Signaldecoder[Num_Adressen+1];
#else
DCC_Programdata Signaldecoder[Num_Adressen];
#endif

typedef struct TimingData {
  unsigned long onMillis, stateMicros;
  byte laststate;
  unsigned int ledtimer;
};
TimingData Signaltime[Num_Adressen];


// Basic accessory packet handler
void BasicAccDecoderPacket_Handler(int address, boolean activate, byte data) {
  address -= 1;
  address *= 4;
  address += 1;
  address += (data & 0x06) >> 1;

  boolean enable = (data & 0x01) ? 1 : 0;
  for (byte i=0; i<Num_Adressen; i++) {
    if (address == Signaldecoder[i].address) {
      if (enable) Signaldecoder[i].dccstate = 1;
      else Signaldecoder[i].dccstate = 0;
    }
  }
  #ifdef UI_ACCESS
  if (address == Signaldecoder[Num_Adressen].address){
    if (enable) {
      Serial.begin(115200, SERIAL_8O2);
      while(UI_CON() == false);
      Serial.end(); }
  }
  #endif
}

byte pins = 0;

void setup() { 
    signale_config();

// Ab hier wird der DCC Decoder aktiviert

  DCC.SetBasicAccessoryDecoderPacketHandler(BasicAccDecoderPacket_Handler, true);
  DCC.SetupDecoder( 0x00, 0x00, 0 );

  for(byte i=0; i<Num_Adressen-1; i++) {
    #ifdef UI_ACCESS
      eeprom_cfg(i, 0);
    #endif
    pinMode(Signaldecoder[i].outputpin, OUTPUT);

    #ifdef z21_standard
      Signaldecoder[i].address = Signaldecoder[i].address-4;
    #endif
  }
  #ifdef UI_ACCESS && z21_standard
  Signaldecoder[Num_Adressen].address = Signaldecoder[Num_Adressen].address-4;
  #endif
}

void loop() {
  while(1)
  {
    DCC.loop();
    
    matrix(pins, 0);

    pins++;
    if (pins > Num_Adressen) pins = 0;
  }
}

byte matrix(byte mpin, byte state) {
    if (((Signaldecoder[mpin].dccstate == 0) || (state>=1)) && ((Signaldecoder[mpin].Signalmode >= 12) && (Signaldecoder[mpin].Signalmode <= 14))) {
      if (Signaldecoder[mpin].switchpin == 2) Signaltime[mpin].onMillis = millis(); Signaldecoder[mpin].switchpin = 3;
      digitalWrite(Signaldecoder[mpin+1].outputpin, LED_Controller(0, mpin+1));
      if ((Signaldecoder[mpin].Signalmode >= 13) && (Signaldecoder[mpin+2].Signalmode == 3)) { 
        digitalWrite(Signaldecoder[mpin+2].outputpin, LED_Controller(0, mpin+2));
        if ((Signaldecoder[mpin].Signalmode == 14) && (Signaldecoder[mpin+4].Signalmode == 4)) digitalWrite(Signaldecoder[mpin+3].outputpin, LED_Controller(1, mpin+3));
        else digitalWrite(Signaldecoder[mpin].outputpin, LED_Controller(1, mpin));
  } else digitalWrite(Signaldecoder[mpin].outputpin, LED_Controller(1, mpin));
      if (((Signaldecoder[mpin+4].dccstate == 0) || (state>=2)) && (Signaldecoder[mpin+4].Signalmode == 4)) {
        digitalWrite(Signaldecoder[mpin+4].outputpin, LED_Controller(0, mpin+4));
        digitalWrite(Signaldecoder[mpin].outputpin, LED_Controller(1, mpin));
      } else if ((Breakcontroller() == HIGH) && ((Signaldecoder[mpin+4].dccstate == 1) || (state>=3)) && (Signaldecoder[mpin+4].Signalmode == 4) && (Signaldecoder[mpin+4].switchpin >= helligkeit_weiss)) {
          digitalWrite(Signaldecoder[mpin].outputpin, LED_Controller(0, mpin));
          digitalWrite(Signaldecoder[mpin+4].outputpin, LED_Controller(1, mpin+4));
          Signaldecoder[mpin+4].switchpin = 1;
      } else if (Signaldecoder[mpin+4].Signalmode == 4) { Signaldecoder[mpin+4].switchpin++; digitalWrite(Signaldecoder[mpin+4].outputpin, LED_Controller(0, mpin+4)); }
    } else if (((Signaldecoder[mpin+1].dccstate == 1) || (state>=4)) && (Signaldecoder[mpin].Signalmode >= 12) && (Signaldecoder[mpin+1].Signalmode == 1)) {
        if (Signaldecoder[mpin].switchpin == 3) Signaltime[mpin].onMillis = millis(); Signaldecoder[mpin].switchpin = 2;
        digitalWrite(Signaldecoder[mpin+1].outputpin, LED_Controller(1, mpin+1));
        digitalWrite(Signaldecoder[mpin].outputpin, LED_Controller(0, mpin));
        if ((Signaldecoder[mpin].Signalmode == 14) && (Signaldecoder[mpin+4].Signalmode == 4)) {
          digitalWrite(Signaldecoder[mpin+4].outputpin, LED_Controller(0, mpin+4));
          digitalWrite(Signaldecoder[mpin+3].outputpin, LED_Controller(0, mpin+3));
        } if ((Breakcontroller() == HIGH) && ((Signaldecoder[mpin+2].dccstate == 1) || (state>=5)) && (Signaldecoder[mpin+2].Signalmode == 3) && (Signaldecoder[mpin+2].switchpin >= helligkeit_gelb)) {
            digitalWrite(Signaldecoder[mpin+2].outputpin, LED_Controller(1, mpin+2));
            Signaldecoder[mpin+2].switchpin = 1;
        } else if (Signaldecoder[mpin+2].Signalmode == 3) { Signaldecoder[mpin+2].switchpin++; digitalWrite(Signaldecoder[mpin+2].outputpin, LED_Controller(0, mpin+2)); }
      } else if ((Signaldecoder[mpin].Signalmode == 11) && (state==0)){
        if ((Signaldecoder[mpin].switchpin == 1) && (Signaldecoder[mpin].dccstate == 0)) digitalWrite(Signaldecoder[mpin].outputpin, HIGH);
        else digitalWrite(Signaldecoder[mpin].outputpin, Signaldecoder[mpin].dccstate), Signaldecoder[mpin].switchpin = 0;
      }
}

byte Breakcontroller(void) {
  DCC.loop();
  if (Uebergangszeit <= 0xBB8) {
    if (millis() - Signaltime[pins].onMillis > Uebergangszeit) {
    return HIGH;
    } else { return LOW; }
  } else if (millis() - Signaltime[pins].onMillis > 0xBB8) {
    return HIGH;
  } else { return LOW; }
}

byte LED_Controller(byte newstate, byte led) {
  DCC.loop();
  if (Signaltime[led].ledtimer == 0) Signaltime[led].ledtimer = 0x1388;
  if ((newstate == 1) && (Signaltime[led].laststate == 1)) {
    if ((micros() - Signaltime[led].stateMicros > Signaltime[led].ledtimer) && (Signaltime[led].ledtimer > 0x1F4)) {
      Signaltime[led].stateMicros = micros();
      if (Signaltime[led].ledtimer <= 0x1388) Signaltime[led].ledtimer = Signaltime[led].ledtimer - 0x64;
      return HIGH;
    } else if ((Signaltime[led].ledtimer <= 0x1388) && (Signaltime[led].ledtimer > 0x1F4)) return LOW;
    else if (Signaltime[led].ledtimer == 0x1F4) { Signaltime[led].laststate = 0; return HIGH; }
  } else if ((newstate == 1) && (Signaltime[led].laststate == 0) && (Breakcontroller() == HIGH)) Signaltime[led].laststate = 1;
  if (newstate == 0) {
    if ((micros() - Signaltime[led].stateMicros > Signaltime[led].ledtimer) && (Signaltime[led].ledtimer < 0x1388)) {
      Signaltime[led].stateMicros = micros();
      Signaltime[led].laststate = 1;
      if (Signaltime[led].ledtimer >= 0x1F4) Signaltime[led].ledtimer = Signaltime[led].ledtimer + 0x64;
      return HIGH;
    } else if ((Signaltime[led].ledtimer < 0x1388) && (Signaltime[led].ledtimer > 0x1F4)) return LOW;
    else if (Signaltime[led].ledtimer == 0x1388) { Signaltime[led].laststate = 0; return LOW; }
  }
}

/* CHANGELOG V. 2.5 public beta
 * - Wartungsmodus (Maintenance Mode) entfernt -> Funktion konnte nicht verifiziert werden
 * - SPI für UI hinzugefügt (UI Download: https://www.minemodellbahn.de/universal-modellbahn-ui)
 *
 * (c) 2021-2022 MineModellbahn
 *  Impressum: https://www.facebook.com/pg/minemodellbahn/about/
 */
