::CALL compile.bat flash flash_events.as flash_display.as flash_media.as flash_text.as vektrix_events.as

CALL %CASPIN_HOME%/tools/cspcompile.bat flash flash/display/*.as flash/events/*.as flash/media/*.as flash/net/*.as flash/system/*.as flash/text/*.as vektrix/*.as *.as

::CALL %CASPIN_HOME%/tools/cspcompile.bat flash_display flash/display/*.as *.as
::CALL %CASPIN_HOME%/tools/cspcompile.bat flash_events flash/events/*.as *.as
::CALL %CASPIN_HOME%/tools/cspcompile.bat flash_media flash/media/*.as *.as
::CALL %CASPIN_HOME%/tools/cspcompile.bat flash_net flash/net/*.as *.as
::CALL %CASPIN_HOME%/tools/cspcompile.bat flash_text flash/text/*.as *.as
::CALL %CASPIN_HOME%/tools/cspcompile.bat vektrix vektrix/*.as *.as

::CALL %CASPIN_HOME%/tools/cspcompile.bat flash flash_events.abc flash_display.abc *.as

CALL %CASPIN_HOME%/tools/cspgenerate.bat flash
