
Directory structure for creating a WarpIN archive
=================================================

This is just a proposal. It allows easily adding further plugins.


lucide
  changelog
  Lucide.exe
  Lucide.lng
  ludoc.dll
  readme

lucide.plugin_djvu
  ddjvuapi.dll
  ludjvu.dll

lucide.plugin_jpeg
  lujpeg.dll

lucide.plugin_pdf
  lupplr.dll

create_lucide_wpi.cmd
lucide_wpi.wis


Adapt the file create_lucide_wpi.cmd to include other files.

Adapt the file lucide_wpi.wis (the installer descriptions)
to your needs (e.g. company, versions, WPS objects, license).


Heiko
(HeikoDOTNitzscheDESPAM@DESPAMgmxDOT.de)
