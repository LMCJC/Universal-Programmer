/* Projekt: DCC Signaldecoder fuer die Roco/Fleischmann z21 Zentrale; mit allen Zentralen kompatibel
 * Autor: MineModellbahn (Lukas)
 * Webseite: www.YouTube.com/maerklinde/videos
 * Version: siehe DCC_Signaldecoder
 * Beschreibung: DCC_Signaldecoder\UI_COM
 */
#ifdef UI_ACCESS
 boolean eeprom_cfg(byte adress, byte save){
  switch (save){
    case 0:
      Signaldecoder[adress].address = EEPROM.read(adress);
      switch (EEPROM.read(Num_Adressen+adress+1)){
        case 14: Signaldecoder[adress].outputpin = A0;
          break;
        case 15: Signaldecoder[adress].outputpin = A1;
          break;
        case 16: Signaldecoder[adress].outputpin = A2;
          break;
        case 17: Signaldecoder[adress].outputpin = A3;
          break;
        default: Signaldecoder[adress].outputpin = EEPROM.read(Num_Adressen+adress+1);
          break;
      }
      Signaldecoder[adress].switchpin = EEPROM.read((Num_Adressen*2)+adress+1);
      Signaldecoder[adress].Signalmode = EEPROM.read((Num_Adressen*3)+adress+1);
      return false;
    case 1:
      EEPROM.update(adress, Signaldecoder[adress].address);
      EEPROM.update(Num_Adressen+adress+1, Signaldecoder[adress].outputpin);
      EEPROM.update((Num_Adressen*2)+adress+1, 0);
      EEPROM.update((Num_Adressen*3)+adress+1, Signaldecoder[adress].Signalmode);
      return true;
  }
 }

 boolean UI_CON(){
  Serial.println("START");
  static byte point = 0;
  int code = getInfoCode();
  if ((code > 0) &&(Serial.available() == 0)){
    Signaldecoder[point].switchpin = 0;
    switch (code){
      case 101:
        Signaldecoder[point].Signalmode = 11;
        while (setSignal("p101", 1, point) == false);
        point++;
        break;
      case 102:
        Signaldecoder[point-1].Signalmode = 12;
        Signaldecoder[point].Signalmode = 1;
        while (setSignal("p102", 2, point) == false);
        point++;
        break;
      case 103:
        Signaldecoder[point-2].Signalmode = 13;
        Signaldecoder[point-1].Signalmode = 1;
        Signaldecoder[point].Signalmode = 3;
        while (setSignal("p103", 3, point) == false);
        point++;
        break;
      case 104:
        Signaldecoder[point-3].Signalmode = 14;
        Signaldecoder[point-2].Signalmode = 1;
        Signaldecoder[point-1].Signalmode = 3;
        Signaldecoder[point].Signalmode = 1;
        while (setSignal("p104", 4, point) == false);
        point++;
        break;
      case 105:
        Signaldecoder[point].Signalmode = 4;
        while (setSignal("p105", 4, point) == false);
        point++;
        break;
      case 200: return true;
      case 210:
        SendInfo("conn", 5);
        break;
      case 211:
        SendInfo("2.54b", 5);
        break;
      case 212:
        SendInfo("22125", 5);
        break;
    }
  }
  return false;
}

boolean setSignal(String nr, byte as, byte point){
  Serial.println(nr);
  int code = getInfoCode();
  if (code == 199) return true;
  while (code == 111) {
    Serial.println("p111");
    int tmpcode = getInfoCode();
    if (tmpcode != 0) {
      Signaldecoder[point].address = tmpcode;
      code = 0;
    }
  }
  while (code == 112) {
    Serial.println("p112");
    int tmpcode = getInfoCode();
    if (tmpcode != 0) {
      Signaldecoder[point].address = Signaldecoder[point-1].address;
      code = 0;
    }
  } while (code == 113) {
    Serial.println("p113");
    int tmpcode = getInfoCode();
    if (tmpcode != 0) {
      Signaldecoder[point].address = tmpcode;
      code = 0;
    }
  }  while (code == 114) {
    Serial.println("p114");
    int tmpcode = getInfoCode();
    if (tmpcode != 0) {
      Signaldecoder[point].address = Signaldecoder[point-3].address;
      code = 0;
    }
  } while (code == 115) {
    Serial.println("p115");
    int tmpcode = getInfoCode();
    if (tmpcode != 0) {
      Signaldecoder[point].address = Signaldecoder[point-2].address;
      code = 0;
    }
  } while (code >= 121 && code <= 125) {
    boolean isOK = false;
    if (code == 121) {
      Serial.println("p121");
      int tmpcode = getInfoCode();
      if (tmpcode > 0) {
        Signaldecoder[point].outputpin = tmpcode;
        if (eeprom_cfg(point, 1)) isOK = true;
      }
    } else if (code == 122){
      Serial.println("p122");
      int tmpcode = getInfoCode();
      if (tmpcode > 0) {
        Signaldecoder[point].outputpin = tmpcode;
        if (eeprom_cfg(point-1, 1)){
          if (eeprom_cfg(point, 1)) isOK = true;
        }
      }
    } else if (code == 123){
      Serial.println("p123");
      int tmpcode = getInfoCode();
      if (tmpcode > 0) {
        Signaldecoder[point].outputpin = tmpcode;
        if ((eeprom_cfg(point-2, 1)) && (eeprom_cfg(point-1, 1))){
          if (eeprom_cfg(point, 1)) isOK = true;
        }
      }
    } else if (code == 124) {
      Serial.println("p124");
      int tmpcode = getInfoCode();
      if (tmpcode > 0) {
        Signaldecoder[point].outputpin = tmpcode;
        if ((eeprom_cfg(point-3, 1)) && (eeprom_cfg(point-2, 1)) && (eeprom_cfg(point-1, 1))) {
          if (eeprom_cfg(point, 1)) isOK = true;
        }
      }
    } else if (code == 125) {
      Serial.println("p125");
      int tmpcode = getInfoCode();
      if (tmpcode > 0) {
        Signaldecoder[point].outputpin = tmpcode;
        if ((eeprom_cfg(point-4, 1)) && (eeprom_cfg(point-3, 1)) && (eeprom_cfg(point-2, 1)) && (eeprom_cfg(point-1, 1))) {
          if (eeprom_cfg(point, 1)) isOK = true;
        }
      }
    }
    while (isOK){
      Serial.println("OK");
      int tmpcode = getInfoCode();
      if (tmpcode == 199) {
        return true;
        }
      }
    }
  return false;
}

 unsigned int getInfoCode(){
  int message = 0;
  while (Serial.available() > 0){
    message = Serial.parseInt(SKIP_ALL);
  }
  return message;
 }

 void SendInfo(String data, byte cnt){
  for (int i = 0; i < cnt; i++){
    Serial.println(data);
  }
 }
#endif

/*
 * (c) 2021-2022 MineModellbahn
 *  YouTube: https://www.youtube.com/maerklinde
 *  Impressum: https://www.facebook.com/pg/minemodellbahn/about/
 */
