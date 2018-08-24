::##############################################################################
:: *DOCUMENTATION*
:: This SETUP.bat installs mine_sweeper in MS Windows

@echo	off

::##############################################################################
:: Install

call	"%~dp0\UNINSTALL.cmd"

mkdir	"%ProgramFiles(x86)%\mine_sweeper\"
echo	"Create %ProgramFiles(x86)%/mine_sweeper/"
mkdir	"%ProgramFiles(x86)%\mine_sweeper\bin\"
echo	"Create %ProgramFiles(x86)%/mine_sweeper/bin/"
mkdir	"%ProgramFiles(x86)%\mine_sweeper\share\"
echo	"Create %ProgramFiles(x86)%/mine_sweeper/share/"
::	mkdir	"%ProgramFiles(x86)%\mine_sweeper\var\"
::	echo	"Create %ProgramFiles(x86)%/mine_sweeper/var/"
echo	""

copy	"%~dp0\UNINSTALL.cmd"		"%ProgramFiles(x86)%\mine_sweeper"
echo	"Copy UNINSTALL.cmd"
copy	"%~dp0\COPYING.txt"		"%ProgramFiles(x86)%\mine_sweeper"
echo	"Copy COPYING.txt"
copy	"%~dp0\README.txt"		"%ProgramFiles(x86)%\mine_sweeper"
echo	"Copy README.txt"
copy	"%~dp0\bin\mine_sweeper.exe"	"%ProgramFiles(x86)%\mine_sweeper\bin"
echo	"Copy bin/mine_sweeper.exe"
robocopy	"%~dp0\share"		"%ProgramFiles(x86)%\mine_sweeper\share"	/e
echo	"Copy share/*"
::robocopy	"%~dp0\var"		"%ProgramFiles(x86)%\mine_sweeper\var"	/e
::echo	"Copy var/*"
echo	""

echo	"Done"
echo	""

::##############################################################################
:: END

echo	on
