/*
   create_lucide_wpi.cmd:

   This uses WarpIN WIC.EXE to create an WPI archive containing
   Lucide and the shipped plugins.

   The created archive can be installed with WarpIN.

   2006 Heiko Nitzsche.
*/

wicdir = "C:\programs\WarpIN"
basedir = directory();

lucide_dir             = basedir"\lucide"
lucide_plugin_pdf_dir  = basedir"\lucide.plugin_pdf"
lucide_plugin_djvu_dir = basedir"\lucide.plugin_djvu"
lucide_plugin_jpeg_dir = basedir"\lucide.plugin_jpeg"

/* package 1: Lucide core    */
/* package 2: Lucide plugin for PDF  (lupplr.dll) */
/* package 3: Lucide plugin for DJVU (ludjvu.dll) */
/* package 4: Lucide plugin for JPEG (lujpeg.dll) */

package1 = "1 -c"lucide_dir" *"
package2 = "2 -c"lucide_plugin_pdf_dir" *"
package3 = "3 -c"lucide_plugin_djvu_dir" *"
package4 = "4 -c"lucide_plugin_jpeg_dir" *"


'SET BEGINLIBPATH='wicdir;

wicdir"\wic.exe -a "basedir"\lucide_wpi "package1" "package2" "package3" "package4" -s "basedir"\lucide_wpi.wis";

call directory basedir;

exit;


