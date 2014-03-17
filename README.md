OctopusKeyboard
===============

Predictive keyboard add-on for jailbroken iOS devices showing word suggestions above individual keys.

NOTE NOTE NOTE
==============
This is initial commit of what I have locally at the moment.
The purpose of it is so that you can look on the code now but don't start using it yet.
There are two issues:
1. Preference bundle crashes at the moment (due to parts of the license system code). Will be fixed soon.
2. I commented some code for iOS7 debugging so it may not work well. I will make all changes needed in one of the following days.

libkpt.a is compiled version of unmodified OpenAdaptxt library which can be downloaded at:
http://openadaptxt.sourceforge.net/

Project is divided into two parts:
1. Client Tweak - Tweak.xm - this is loaded into any UIKit application as any other tweak, hooks some keyboard functions and communicates with octopusd daemon via Mach-O IPC. There is mach manual pdf to help get you started with Mach IPC.
2. Octopusd Daemon - octopuscore - this daemon contains connection to the prediction engine and exploses IPC functions

octopusd binary has -s argument which queries running octopusd daemon to get its uptime. 
This simple function can help you understand how this IPC works.

I will update this document soon.
