/* Projekt: DCC Signaldecoder fuer die Roco/Fleischmann z21 Zentrale; mit allen Zentralen kompatibel
 * Autor: MineModellbahn (Lukas)
 * Webseite: www.YouTube.com/maerklinde/videos
 * Version: siehe DCC_Signaldecoder
 * Beschreibung: DCC_Signaldecoder\Signale_config_DCC_Signaldecoder
 */


  /* Anleitung Signalmode: (definieren der Signaltypen)
   * Signaltyp bei rot (links) definieren:
   *                      14  = Ausfahrsignal
   *                      13  = Einfahrsignal
   *                      12  = Blocksignal
   *                      11  = einzelne LED (Zustand bei Signaldecoder.switchpin definieren)
   * 
   * Für Aus- und Einfahrsignale gilt:
   * gruen = 1; (+1 von rot)
   * gelb = 3; (+2 von rot)
   * weiss = 4; (+4 von rot)
   * mehr auf: www.YouTube.com/maerklinde/videos
   * Video: https://youtu.be/Am3XhZEi6sM
   */

// ### FUER UPDATE NUR BIS "UPDATE ENDE" UEBERSCHREIBEN ###
void signale_config(void) {
/* Hier werden die Ausgaenge und Adressen definiert
 * Die Adressen sind standardmaeßig mit fortlaufender Adresse eingestellt.
 */
 // HIER SIND KEINE EINTRÄGE MEHR NOTWENDIG!
 // Die UI Schnittstelle ist standardmäßig aktiviert!

 Signaldecoder[Num_Adressen].address = UI_ACCESS;
}

/*
 * (c) 2021-2022 MineModellbahn
 *  YouTube: https://www.youtube.com/maerklinde
 *  Impressum: https://www.facebook.com/pg/minemodellbahn/about/
 */
