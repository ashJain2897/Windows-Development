Compiling and Linking using VS Developer Command Prompt:

Compile --> cl.exe /c /EHsc YourApplicationName.cpp
               -->rc.exe YourRCfileName

Output--> YourApplicationName.obj
          -->RCfileName.res	

Linking   --> link.exe /EHsc YourApplicationName.obj RCfileName.res user32.lib gdi32.lib /subsystem:WINDOWS



