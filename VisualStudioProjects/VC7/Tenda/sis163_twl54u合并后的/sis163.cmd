@echo off

set ROM_CONFIG=eeprom.ini
set MAC_ADDRESS=macid.txt

sis163 "%ROM_CONFIG%" "%MAC_ADDRESS%"

pause

@echo on