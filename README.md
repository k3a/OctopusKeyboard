OctopusKeyboard
===============

Predictive keyboard add-on for jailbroken iOS devices showing word suggestions above individual keys.

Website: http://ok.k3a.me <br/>
Developer & User forums: http://forum.k3a.me

libkpt.a is compiled version of unmodified OpenAdaptxt library which can be downloaded at:
http://openadaptxt.sourceforge.net/
It has been a long time since I compiled it so I don't remember the details. I might have combined two openadaptxt libraries into one but I am sure the openadaptxt was not modified so it should be possible to compile it for arm64.

Project is divided into two parts:
 1. Client Tweak - Tweak.xm - this is loaded into any UIKit application as any other tweak, hooks some keyboard functions and communicates with octopusd daemon via Mach-O IPC. There is mach manual pdf to help get you started with Mach IPC.
 2. Octopusd Daemon - octopuscore - this daemon contains connection to the prediction engine and exploses IPC functions

Some known problematic parts which needs to be updated for iOS7 compatibility are marked by "TODO:ios7".

octopusd binary has -s argument which queries running octopusd daemon to get its uptime. 
This simple function can help you understand how this IPC works.

How to compile it
=================

You need to have Xcode installed. The project uses theos makefiles (xcode project is there just for convenience and may not work at all).
Read  more about theos here: http://iphonedevwiki.net/index.php/Theos/Getting_Started.

It was tested and compiles fine with these versions:<br/>
 - https://github.com/rpetrich/theos put into /theos
 - https://github.com/rpetrich/iphoneheaders put into /theos/include

In order to complile it, set the correct theos symlink to your theos installation (or put theos to /theos and keep my simlink) and run:
PATH="bin:$PATH" make package

There is also 'PATH="bin:$PATH" make package' test makefile rule but it won't work without setting your ~/.ssh/config on your mac (see bellow).
I used it to automate package creation, installing the packge on the device and respringing the device.
This is not needed though as you can install the package standard theos way or via 'dpkg -i path to deb' on the device.

For instructions how to copy files through scp over USB into your device, see this:
http://iphonedevwiki.net/index.php/SSH_Over_USB

If you pan to use USB SSH connection, make sure to speed it up by:
 - using SSH key for (root and mobile user) authentication (http://www.priyaontech.com/2012/01/ssh-into-your-jailbroken-idevice-without-a-password/)
 - using ~/.ssh/config on your mac with a record like this one (last two lines will allow you switching iOS devices without hassle):
  Host ufoxy
  User mobile
  Port 2222
  HostName localhost
  StrictHostKeyChecking no
  UserKnownHostsFile=/dev/null

If you have trouble compiling it, you can contact me and others at http://forum.k3a.me or simply create a github issue. I will try to help you and/or update this readme.
