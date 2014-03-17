GO_EASY_ON_ME=1

include theos/makefiles/common.mk

BUNDLE_NAME = OKPrefs
OKPrefs_FILES = OKPrefs.mm OKDicts.mm ../octopuscore/OctopusDaemon/octopusUser.c
OKPrefs_INSTALL_PATH = /Library/PreferenceBundles
OKPrefs_FRAMEWORKS = UIKit Accounts Twitter MessageUI
OKPrefs_PRIVATE_FRAMEWORKS = Preferences AppSupport
OKPrefs_CFLAGS = -I../include
OKPrefs_LDFLAGS = -L../lib

include $(THEOS_MAKE_PATH)/bundle.mk

internal-stage::
	$(ECHO_NOTHING)mkdir -p $(THEOS_STAGING_DIR)/Library/PreferenceLoader/Preferences$(ECHO_END)
	$(ECHO_NOTHING)cp entry.plist $(THEOS_STAGING_DIR)/Library/PreferenceLoader/Preferences/OKPrefs.plist$(ECHO_END)

test: all stage
	ssh root@ufoxy "rm -rf /Library/PreferenceBundles/OKPrefs.bundle ; killall Preferences || true"
	scp -r $(THEOS_STAGING_DIR)/* root@ufoxy:/
	ssh root@ufoxy "sbopenurl 'prefs:root=Octopus Keyboard'"
