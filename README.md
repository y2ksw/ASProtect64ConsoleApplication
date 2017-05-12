# ASProtect64ConsoleApplication
This ready to use project demonstrates how to use ASProtect for 64 bit for a console application.

Important Notes:
- The C++ project was created with Visual Studio 2015 Community Edition.
- Some of the files are in Italian, but have absolutely no relevance, since they are generated by the development environment.
- The base code was offered by asprotect.com, but I fixed and tested the code and prepared the example ASProtect project ready to use.
- The included ASProtect project is for demonstration only. Essentially, you should create your own ASProtect project. While developing, you do not need to add your executable (application). Every time you change the protection scheme (demo mode, trial mode, nagging options, etc), you will have to remake the SDK. Due to a bug in the Protection Studio, you must reconnect (Ctrl+R) or reopen the project in order to reenable the "Generate SDK" button.
- Also, if you don't like the random name of the DLL, you can change it opening the *.psf file with wordpad.exe. It is also a way to create rapidly several protection projects using standard copy and paste, provided you know what you are doing.
