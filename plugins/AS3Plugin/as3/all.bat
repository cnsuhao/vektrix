::CALL compile.bat flash flash_events.as flash_display.as flash_media.as flash_text.as vektrix_events.as

CALL compile.bat flash flash\display\*.as flash\events\*.as flash\media\*.as flash\net\*.as flash\text\*.as vektrix\*.as *.as

CALL generate.bat flash
