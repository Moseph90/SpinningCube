Hi!

This is simple spinning cube program that prints characters to a terminal in a particular order to give the effect. Please be advised that the cube is rather large, and you may have to zoom out or maximize the window in order to fully see it (also give it a minute to reassemble).

***Possible issue that you might run into***
For some reason, Visual Studio on Windows couldn't run this program at full speed. It moves incredibly slow. I don't know if it's a VS thing or a Windows thing. WSL (Linux Subsystem) runs this program perfectly though.

If you'd like to mess with the rate of spinning, or the point of view distance, you can alter the cameraDistance variable as well as the cubeWidth variable. You'll have to play with those values together to get the right fit. The spin speed can be changed by adjust the incrementSpeed variable or removing the delay() function call at the bottom of the main function. I would not reccomend trying to move the Cube itself, simply because some 'if' statements rely on certain values to be true. But it's your code now so enjoy. 
