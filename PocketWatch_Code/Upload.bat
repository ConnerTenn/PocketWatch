avrdude -p t88 -P com3 -c avrisp -b 19200 -v -U flash:w:Release\PocketWatch_Code.hex
pause