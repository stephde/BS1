Dieser Programmrahmen unterst�tzt x86 als auch x86_64 Zielumgebungen.


VCINSTALLDIR entspricht dem VC Verzeichnis der entsprechenden Visual Studio Version. 
Diese Variable ist in einer Visual Studio Cmd Umgebung gesetzt. Um die Variable in einer 'sauberen' CMD 
zu setzen, kann "%VS100COMNTOOLS%vsvars32.bat" (VS 2010, VS90COMNTOOLS f�r VS 2008) ausgef�hrt werden. 
Das setzt eine x86 Umgebung und erm�glicht auch die im weiteren beschrieben Umgebungswechsel.

z.B. C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC f�r VS 2008
     C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC f�r VS 2010
x86
---
> "%VCINSTALLDIR%\vcvarsall.bat x86"
> nmake


x64
---
F�r eine x64 Bin�rdatei ist die Visual Studio x64 Umgebungen zu setzen

> "%VCINSTALLDIR%\vcvarsall.bat x64"

Beim Wechel zwischen beiden Umgebungen ist ein 

> nmake clean 

auszuf�hren um eine saubere Ausgangsbasis zu schaffen. 
