#!/bin/bash

#CALL compile.bat flash flash_events.as flash_display.as flash_media.as flash_text.as vektrix_events.as

python $CASPIN_HOME/tools/cspcompile.py flash flash/accessibility/*.as flash/display/*.as flash/events/*.as flash/filters/*.as flash/geom/*.as flash/media/*.as flash/net/*.as flash/system/*.as flash/text/*.as flash/utils/*.as vektrix/*.as *.as

$CASPIN_HOME/tools/cspgenerate.sh flash

