OctopusKeyboard
===============

Predictive keyboard add-on for jailbroken iOS devices showing word suggestions above individual keys.

Website: http://ok.k3a.me <br/>
Developer & User forums: http://forum.k3a.me

libkpt.a is compiled version of unmodified OpenAdaptxt library which can be downloaded at:
http://openadaptxt.sourceforge.net/

Project is divided into two parts:
 1. Client Tweak - Tweak.xm - this is loaded into any UIKit application as any other tweak, hooks some keyboard functions and communicates with octopusd daemon via Mach-O IPC. There is mach manual pdf to help get you started with Mach IPC.
 2. Octopusd Daemon - octopuscore - this daemon contains connection to the prediction engine and exploses IPC functions

In order to complile it, set the correct theos symlink to your theos installation and run 'make package' command.

There is also 'make test' makefile rule but it won't work without modifying theos. I used it to automate package creation, installing the packge on the device and respringing the device. This is not needed though as you can install the package standard theos way or via 'dpkg -i path to deb' on the device.

octopusd binary has -s argument which queries running octopusd daemon to get its uptime. 
This simple function can help you understand how this IPC works.

