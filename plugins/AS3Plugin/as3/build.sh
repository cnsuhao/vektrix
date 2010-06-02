#!/bin/bash

#CALL compile.bat flash flash_events.as flash_display.as flash_media.as flash_text.as vektrix_events.as

$CASPIN_HOME/tools/cspcompile.sh flash "flash/display/*.as" "flash/events/*.as" "flash/media/*.as" "flash/net/*.as" "flash/text/*.as" "vektrix/*.as" "*.as"

$CASPIN_HOME/tools/cspgenerate.sh flash

