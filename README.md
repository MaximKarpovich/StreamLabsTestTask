# StreamLabsTestTask

Hi 

To complete the test task, I have decided to use StreamLabs existing project (hope you arre not agains it :D ). Steps that I have made during implementation:
1. Downloaded OBS and compiled it for x64. Had some issues with specific path for searching modules (I mean hardcoded ../../obs-plugins), so changed it to (./obs-plugins).
2. Downloaded StreamLabs obs-studio-node project
3. Removed some code that is not neccessary for this test task and compiled.
4. Created native module

## Note:
**I understand that it may seem a bit like a cheat, to use existing implementation. But as long as test task is intended to demonstrate ability to learn new technologies quickly, I think it is step forward. Anyway, now I have the idea of StreamLabs project architecture and workflow** :))

## Steps to build and run:
1. Enter root catalog of test task
2. npm install
3. configure -s
4. Build solution in VS2017
5. Copy ./third_party/lib/obs/* into ./bin/Release/
6. Copy ./third_party/lib/obs_deps/* into ./bin/Release/
7. Copy ./third_party/modules/* into ./bin/Release/
8. In one command line enter ./bin/Release and run: ./obs_server_64bits.exe mysock
8. In another command line enter root catalog and run: npm start

## Note: 
1.Stream URL and Stream Key are stored in consts.h file in obs_server.
