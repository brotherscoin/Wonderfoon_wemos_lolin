// gewijzigd naar gebruik van DFRobotDFPlayerMini.h 
// niet compleet !

void checkPlaying()
{
  //debug("Check Playing:");
  if (digitalRead(busyPin) == 1) {
    if (PlayingContinuesly) 
    { debug("Check Playing: start next random number");
      delay(1000);
      playRandom();
    }
  }
}

void setMP3Volume(int volume)
{
  myDFPlayer.volume(volume);  //Set volume value. From 0 to 30
  //execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
}

void storeMP3Volume(int volume)
{
  EEPROM_storeVolume(volume);
  }

void playRandom() {
  myDFPlayer.playFolder(foldRand(), playRand());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
  //playTrackInFolder(playRand(), foldRand());
}

void mp3Wake()
{
  // ik kan geen overeenkomende functie vinden in de nieuwe library. dit lijkt echter prima te werken..
  execute_CMD(0x09, 0, 2); // Set Playmode to SD
  //delay(500);
}

void mp3Sleep()
{
  myDFPlayer.sleep();
  //execute_CMD(0x09, 0, 3); // Set MP3 player in sleep mode

  //execute_CMD(0x0A, 0, 0); // Set MP3 player in power loss
}

void playTrackInFolder(int track, int folder)
{
  debug( "playTrackInFolder" + String(track) + "-" + String(folder));
  //amplifier(1);
  if (!playMode && !PlayingContinuesly || folder == 4) // if not Playmode = random or playinRandom is true
    //execute_CMD(0x0F, folder, track);
  myDFPlayer.playFolder(folder,track);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
  else
    //execute_CMD(0x0F, foldRand(), playRand());
    myDFPlayer.playFolder(foldRand(), playRand());  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
}

void MP3stop()
{
  myDFPlayer.stop();
  //execute_CMD(0x16, 0, 0);
}

void execute_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
  //debug(millis());
  debug("CMD " + String(CMD) + " - " + String (Par1) + " - " + String(Par2));
  // Calculate the checksum (2 bytes)
  word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
  // Build the command line
  byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
                            Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte
                          };
  //Send the command line to the module
  for (byte k = 0; k < 10; k++)
  {
    Serial.write( Command_line[k]);
  }
  delay(500);
  //debug(millis());
}

void playFolder(int folder) {
  myDFPlayer.playFolder(4,folder + 10);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
  //playTrackInFolder(folder + 10, 4);
  //delay(2000);
}

void playAlarm() {
  myDFPlayer.playFolder(4,112);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
  //setMP3Volume(19);
  //playTrackInFolder(112, 4);
  delay(14000);
  //setMP3Volume(EEPROM_getVolume());
  countedPulses = 99;
  folderNumber = 4;
}

void playVolume() {
  myDFPlayer.playFolder(4,audioVolume + 11);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
  //playTrackInFolder(audioVolume + 11, 4);
  //delay(2000);
}

void playWillekeurig(int pm) {
  myDFPlayer.playFolder(4,pm + 3);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
  //playTrackInFolder(pm + 3, 4);
  //delay(2000);
}

void playContinu(){
myDFPlayer.playFolder(4,5);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
  //playTrackInFolder(5,4);
  //delay(2000);
}
void playReset(){
myDFPlayer.playFolder(4,6);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
  //playTrackInFolder(6,4);
  //delay(2000);
}
