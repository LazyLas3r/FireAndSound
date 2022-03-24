# Story Portal Stage

Code written for the Story Portal stage (2022 LoveBurn art project).
This was written to time and sequence several propane flame poffers with stage events 
and trigger timed sound effects on a seperate board.

# Features

Each poffer is assigned a number (in this case 1 through 7). The use of indexing through an array
allows for poffers to be fired in any sequence simply by passing in a array listing the firing order.
Poffer firing function also has overloaded verisons allowing for several poffers to be timed and fired at once
by passing in multiple arrays. Some single and double flame firing orders are pre-written and can be easily switched 
in between.

The sound board being used for this project was triggered by sending an 8 bit signal via 8 seperate digtial
pins which are then interpereted into binary. This code includes a class to easliy deal with setting the 8 pins to the correct
high and low values during a call for sound so that up to 255 differnt sounds can be triggered from the sound board.
