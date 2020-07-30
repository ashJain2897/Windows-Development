Compiling and Linking using VS Developer Command Prompt:

Compile --> cl.exe /c /EHsc YourApplicationName.cpp

Output--> YourApplicationName.obj

Linking   --> link.exe /EHsc YourApplicationName.obj user32.lib gdi32.lib /subsystem:WINDOWS


