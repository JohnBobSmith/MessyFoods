# SpaceyRocks
A space invaders inspired game. Pop the waves of asteroids with your main cannon,
roast them with the laser if they try to get past you, and protect yourself
with a destructible bubble shield! Be careful though! The laser damages you when
in use! Collect powerups to replenish health, energy, shield, or unlock temporary 
upgrades like a rate of fire booster. Beware of things far worse than asteroids...

##Basic storyline:
You are at a research facility on the moon, investigating strange radio signals.
A well established moon colony lay behind you. Your faciliity is positioned at the
very edge of colony, for the best signal. Suddenly, a great deal of space debris
starts rocketing towards you. A meteor shower! You decide to overload your radio, 
turning it into a powerful space cannon! However, the energy drain nearly froze you
and the research facility. You can no longer risk keeping the hot laser
up at all times, for you may freese to death! As if things couldn't get any worse, 
sure enough, the moonbase's defenses have mysteriously gone offline. It looks
like its up to you to save the colony from complete desctruction... And it's 
beginning to look like asteroids are the least of your concerns.

##How to play:
Left mouse - Fire main cannon

Right mouse - Laser

Mouse movement - Aim the main cannon

##Features:
-Full GNU autotools support. This should make compiling/installing a breeze

-Destructible, non-regnerative bubble shield

-Laser, health, shield, and shooting mechanics

-Wave based gameplay

-Basic player health bar or "HUD" if you can call it that

-Reasonably accurate collision models

###Upcoming features:
-Additional enemies

-Powerups

-Improved audio

-Miscellaneous graphical enhancments. I hope to learn how to use shaders, but this is not a very high priority.

##Technical requirements
###I'm a hobby Linux developer, so Windows of any kind is unsupported. If you can make it work for Windows, great!
In order to play this, you will need the SFML 2.4.0-1 runtime libraries, available from http://www.sfml-dev.org/
or your package manager. This project may run against older versions of SFML, however, 2.4.0-1 is the version I am 
building against. You will also  need a C++ compiler. A makefile has been included in the src/ directory, and
should allow you to compile the project. Any bug reports or refinements to the makefile are welcome,as I don't 
normally use one.

##NOTES:
I made a point of making all the artwork myself, using gimp. If you believe there has been a copyright infringement,
please contact me and we will settle it right away. This also means you are free to use all of my art, subject to the MIT license. I'll try to include .xcf (open source image) whenever it makes sense to do so.

Included is the electronic highway sign font from: 
http://www.dafont.com/theme.php?cat=302&page=2
The font description says "100%" free so I hope that means I can include it here. :)

I've made a point of making some, but not all, of the audio myself. Some audio files have been taken from www.freesound.org
Where this occured, I explicitly checked that the license was creative commons 0, thus (hopefully) allowing me to freely
include the audio with my project. Again if you have any problems, email me.

I've used space invaders as a reference and inspiration for this project, and as a reference and inspiration only. I take
no credit for the original space invaders released by Taito in 1978.

####Contributors to this project:
David "JohnBobSmith" Bogner - Lead developer | myrunescapeemail609[AT]gmail[DOT]com

David "drcouzelis" Couzelis - GNU autotools support | drcouzelis[AT]gmail[DOT]com
