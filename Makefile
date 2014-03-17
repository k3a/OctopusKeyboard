GO_EASY_ON_ME=1
NO_RESPRING = 1

include theos/makefiles/common.mk

# use latest SDK but use iOS 5.0 as deployment target
export TARGET=iphone:latest:5.0
export ARCHS = armv7
# use CLANG
TARGET_CC = xcrun --sdk iphoneos clang
TARGET_CXX = xcrun --sdk iphoneos clang++
#TARGET_CC = xcrun --sdk iphoneos llvm-gcc
#TARGET_CXX = xcrun --sdk iphoneos llvm-g++

SUBPROJECTS = octopuscore OKPrefs

TWEAK_NAME = OctopusKeyboard
OctopusKeyboard_FILES = Tweak.xm OctopusBeast.mm octopuscore/OctopusDaemon/octopusUser.c
#OctopusKeyboard_FILES = Debug2.xm
OctopusKeyboard_FRAMEWORKS = CoreGraphics UIKit QuartzCore
OctopusKeyboard_PRIVATE_FRAMEWORKS = TextInput
OctopusKeyboard_CFLAGS = -g0 -fvisibility=hidden -Iinclude -Iinclude/pal -Iinclude/pal/android -Iinclude/kptapi -Iinclude/kptapi/android -Ioctopuscore/OctopusDaemon
OctopusKeyboard_LDFLAGS = -Llib 
ifeq ($(DEBUG),1)
OctopusKeyboard_CFLAGS += -DDEBUG=1
endif

include $(THEOS_MAKE_PATH)/tweak.mk
include $(THEOS_MAKE_PATH)/aggregate.mk

testw: distclean package
	install.copyFile "$(THEOS_PACKAGE_DIR)/$(THEOS_PACKAGE_FILENAME).deb" "$(THEOS_PACKAGE_FILENAME).deb"
	install.exec "dpkg -i $(THEOS_PACKAGE_FILENAME).deb ; rm $(THEOS_PACKAGE_FILENAME).deb"
	install.exec "killall MobileSafari ; sleep 1 ; ~mobile/open Safari"

test: distclean package install
	ssh ufoxy "killall MobileNotes; ~/open Notes"

ptest: distclean package install
	ssh root@ufoxy "killall Preferences ; sbopenurl 'prefs:root=Octopus Keyboard'"

testd: distclean package install
	ssh ufoxy "killall octopusd "

distclean:
	rm *.deb || true

dumpdb: dumpdb.cpp
	xcrun -sdk iphoneos g++ -DTARGET_IPHONE=1 -O2 -I/theos//include -include /theos//Prefix.pch -Wall  -isysroot "/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS5.0.sdk" -arch armv6 -D__IPHONE_OS_VERSION_MIN_REQUIRED=__IPHONE_3_0 -miphoneos-version-min=3.0 -Iinclude  -DDEBUG -ggdb -O0 dumpdb.cpp -o dumpdb -lgdbm -Llib
