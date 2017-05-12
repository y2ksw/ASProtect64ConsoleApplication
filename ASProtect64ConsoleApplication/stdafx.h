// stdafx.h
#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <stdio.h>
#include <tchar.h>


// TODO: additional references
#include <stdio.h>
#include <time.h> 
#include <conio.h>

/* ----------------------------------------------------------------------------
This is the header file which you will find in the generated and downloaded
ASProtect SDK made by your own: Create an ASProtect project and do "Generate
SDK".

You need to add these files to your C++ Project, too:

PsaApi.h
PsConfig.h
PsConstants.h

In the project properties, you are required to add the library, too, for each 
of your compilation configurations. Only x64 works:

Project Properties - Linker - Input - Additional References - Modify:
aspexample.lib

You will have to add also the path to the SDK:
Project Properties - Linker - General - Additional Directories - Modify:
C:\aspexample_sdk

Finally, you need to copy the file aspexample.dll and pcnsl.exe to your current 
compilation, in order to test your application and protection. If the DLL can't
be found, an unhandled GPF is generated, and if pcnsl.exe is missing, a handled
exception is generated, after quite some time. However, with the files 
available, the execution speed does not suffer significantly.
*/
#include "PsaApi.h"
#define ASPEXPORTAPI __declspec(dllexport)
