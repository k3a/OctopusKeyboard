GO_EASY_ON_ME=1
#DEBUG = 1
NO_RESPRING = 1

include theos/makefiles/common.mk

export TARGET=iphone:latest:5.0
export ARCHS = armv7

TOOL_NAME = octopusd
octopusd_FILES = OctopusDaemon/main.mm OctopusDaemon/TextInput.mm OctopusDaemon/Layouts.mm OctopusDaemon/octopusServer.c OctopusDaemon/octopusUser.c OctopusDaemon/examples.mm
octopusd_FRAMEWORKS = AddressBook CoreGraphics UIKit QuartzCore
octopusd_CFLAGS = -g0 -fvisibility=hidden -Wno-multichar -DIOS=1 -I. -I../include -I../include/pal -I../include/pal/android -I../include/kptapi -I../include/kptapi/android
octopusd_LDFLAGS = -Wl,-s -Xlinker -s -L../lib -lkpt -lsqlite3

include $(THEOS_MAKE_PATH)/tool.mk

before-all:: 

OctopusDaemon/octopusServer.c: OctopusDaemon/octopus.defs
	echo "Compiling MIG..."
	mig -header OctopusDaemon/octopus.h -server OctopusDaemon/octopusServer.c -user OctopusDaemon/octopusUser.c OctopusDaemon/octopus.defs

test: distclean package install
	ssh ufoxy "killall octopusd"

distclean:
	rm *.deb || true

