CXX = g++
CSTD = -std=c++14
CLASS_TELEPHONE_NUMBER = telephone_number
CLASS_CONTACT = contact
CLASS_SMS = sms
CLASS_UTILS_STRING = utils_string
CLASS_UTILS_FILE_SYSTEM = utils_file_system
CLASS_UTILS_HTML = utils_html
CLASS_EXEC_CONTACTS_AND_SMS_REPORTS = exec_contacts_and_sms_reports
CLASS_GUI_CONTACTS_AND_SMS_REPORTS = gui_contacts_and_sms_reports
TEST_MAIN = test_main
TEST_TELEPHONE_NUMBER = test_telephone_number
FILE_EXT_INCLUDE = hpp
FILE_EXT_SRC = cpp
FILE_EXT_BUILD = o
MAIN = main
EXE = contacts_and_sms_reports
EXE_TEST = $(TEST_MAIN)
BUILD_DEBUG = debug
BUILD_RELEASE = release
TEST = test
PATH_INCLUDE = ./include
PATH_SRC = ./src
PATH_TEST = ./$(TEST)
PATH_BUILD_ROOT = ./build
PATH_BUILD_DEBUG = $(PATH_BUILD_ROOT)/$(BUILD_DEBUG)
PATH_BUILD_RELEASE = $(PATH_BUILD_ROOT)/$(BUILD_RELEASE)
PATH_BUILD_TEST = $(PATH_BUILD_ROOT)/$(TEST)
PATH_LIB =./lib
PATH_BIN_ROOT = ./bin
PATH_BIN_DEBUG = $(PATH_BIN_ROOT)/$(BUILD_DEBUG)
PATH_BIN_RELEASE = $(PATH_BIN_ROOT)/$(BUILD_RELEASE)
PATH_BIN_TEST = $(PATH_BIN_ROOT)/$(TEST)

#
# Default build mode when no targets
#

BUILD_MODE = $(BUILD_DEBUG)
CFLAGS = $(CSTD) -Wall -g3
PATH_BUILD = $(PATH_BUILD_DEBUG)
PATH_BIN = $(PATH_BIN_DEBUG)

ifeq ($(MAKECMDGOALS),$(BUILD_RELEASE))
	BUILD_MODE = $(BUILD_RELEASE)
	CFLAGS = $(CSTD) -O
	PATH_BUILD = $(PATH_BUILD_RELEASE)
	PATH_BIN = $(PATH_BIN_RELEASE)
endif

all: $(BUILD_MODE) $(TEST)

$(BUILD_MODE): pre_build $(EXE)

$(TEST): pre_test $(EXE_TEST)

$(EXE_TEST): $(PATH_BUILD) $(PATH_BUILD_TEST) $(PATH_BIN_TEST) \
	$(PATH_LIB)/catch.$(FILE_EXT_INCLUDE) \
	$(PATH_TEST)/$(TEST_MAIN).$(FILE_EXT_SRC) \
	$(PATH_TEST)/$(TEST_TELEPHONE_NUMBER).$(FILE_EXT_SRC) \
	$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_BUILD)

	$(CXX) $(CSTD) -c -I$(PATH_LIB) -I$(PATH_INCLUDE) $(PATH_TEST)/$(TEST_MAIN).$(FILE_EXT_SRC) \
	-o $(PATH_BUILD_TEST)/$(TEST_MAIN).$(FILE_EXT_BUILD)

	$(CXX) $(CSTD) -I$(PATH_LIB) -I$(PATH_INCLUDE) $(PATH_BUILD_TEST)/$(TEST_MAIN).$(FILE_EXT_BUILD) \
	$(PATH_BUILD)/$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_BUILD) \
	$(PATH_TEST)/$(TEST_TELEPHONE_NUMBER).$(FILE_EXT_SRC) \
	-o $(PATH_BIN_TEST)/$(TEST_MAIN)
	$(PATH_BIN_TEST)/$(EXE_TEST) --reporter compact --success

$(EXE): $(PATH_BUILD) $(PATH_BIN) $(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_BUILD) \
	$(CLASS_SMS).$(FILE_EXT_BUILD) $(CLASS_CONTACT).$(FILE_EXT_BUILD) \
	$(CLASS_UTILS_STRING).$(FILE_EXT_BUILD) \
	$(CLASS_UTILS_FILE_SYSTEM).$(FILE_EXT_BUILD) \
	$(CLASS_UTILS_HTML).$(FILE_EXT_BUILD) \
	$(CLASS_EXEC_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_BUILD) \
	$(CLASS_GUI_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_BUILD) \
	$(PATH_SRC)/$(MAIN).$(FILE_EXT_SRC)

	$(CXX) $(CFLAGS) -I$(PATH_LIB) -I$(PATH_INCLUDE) \
	$(PATH_BUILD)/$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_BUILD) \
	$(PATH_BUILD)/$(CLASS_CONTACT).$(FILE_EXT_BUILD) \
	$(PATH_BUILD)/$(CLASS_SMS).$(FILE_EXT_BUILD) \
	$(PATH_BUILD)/$(CLASS_UTILS_STRING).$(FILE_EXT_BUILD) \
	$(PATH_BUILD)/$(CLASS_UTILS_FILE_SYSTEM).$(FILE_EXT_BUILD) \
	$(PATH_BUILD)/$(CLASS_UTILS_HTML).$(FILE_EXT_BUILD) \
	$(PATH_BUILD)/$(CLASS_EXEC_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_BUILD) \
	$(PATH_BUILD)/$(CLASS_GUI_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_BUILD) \
	$(PATH_SRC)/$(MAIN).$(FILE_EXT_SRC) -o $(PATH_BIN)/$(EXE) \
	`pkg-config gtkmm-3.0 --cflags --libs`

pre_test:
	@echo Building and running tests...

pre_build:
	@echo Building $(BUILD_MODE) mode...

$(PATH_BUILD):
	mkdir -p -m 755 $(PATH_BUILD)

$(PATH_BIN):
	mkdir -p -m 755 $(PATH_BIN)

$(PATH_BUILD_TEST):
	mkdir -p -m 755 $(PATH_BUILD_TEST)

$(PATH_BIN_TEST):
	mkdir -p -m 755 $(PATH_BIN_TEST)

$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_BUILD): \
	$(PATH_SRC)/$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_SRC) \
	$(PATH_INCLUDE)/$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_INCLUDE)
	
	$(CXX) -c $(CFLAGS) -I$(PATH_INCLUDE) \
	$(PATH_SRC)/$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_SRC) -o \
    $(PATH_BUILD)/$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_BUILD)

$(CLASS_SMS).$(FILE_EXT_BUILD): $(PATH_SRC)/$(CLASS_SMS).$(FILE_EXT_SRC) \
	$(PATH_INCLUDE)/$(CLASS_SMS).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_INCLUDE)

	$(CXX) -c $(CFLAGS) -I$(PATH_INCLUDE) $(PATH_SRC)/$(CLASS_SMS).$(FILE_EXT_SRC) -o \
	$(PATH_BUILD)/$(CLASS_SMS).$(FILE_EXT_BUILD)

$(CLASS_CONTACT).$(FILE_EXT_BUILD): $(PATH_SRC)/$(CLASS_CONTACT).$(FILE_EXT_SRC) \
	$(PATH_INCLUDE)/$(CLASS_CONTACT).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_SMS).$(FILE_EXT_INCLUDE)

	$(CXX) -c $(CFLAGS) -I$(PATH_INCLUDE) $(PATH_SRC)/$(CLASS_CONTACT).$(FILE_EXT_SRC) -o \
	$(PATH_BUILD)/$(CLASS_CONTACT).$(FILE_EXT_BUILD)

$(CLASS_UTILS_STRING).$(FILE_EXT_BUILD): $(PATH_SRC)/$(CLASS_UTILS_STRING).$(FILE_EXT_SRC) \
	$(PATH_INCLUDE)/$(CLASS_UTILS_STRING).$(FILE_EXT_INCLUDE)
	
	$(CXX) -c $(CFLAGS) -I$(PATH_INCLUDE) $(PATH_SRC)/$(CLASS_UTILS_STRING).$(FILE_EXT_SRC) \
	-o $(PATH_BUILD)/$(CLASS_UTILS_STRING).$(FILE_EXT_BUILD)

$(CLASS_UTILS_FILE_SYSTEM).$(FILE_EXT_BUILD): \
	$(PATH_SRC)/$(CLASS_UTILS_FILE_SYSTEM).$(FILE_EXT_SRC) \
	$(PATH_INCLUDE)/$(CLASS_UTILS_FILE_SYSTEM).$(FILE_EXT_INCLUDE)
	
	$(CXX) -c $(CFLAGS) -I$(PATH_INCLUDE) \
	$(PATH_SRC)/$(CLASS_UTILS_FILE_SYSTEM).$(FILE_EXT_SRC) \
	-o $(PATH_BUILD)/$(CLASS_UTILS_FILE_SYSTEM).$(FILE_EXT_BUILD)

$(CLASS_UTILS_HTML).$(FILE_EXT_BUILD): \
	$(PATH_SRC)/$(CLASS_UTILS_HTML).$(FILE_EXT_SRC) \
	$(PATH_INCLUDE)/$(CLASS_UTILS_HTML).$(FILE_EXT_INCLUDE) \
	$(PATH_LIB)/CTML.h $(PATH_INCLUDE)/$(CLASS_CONTACT).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_SMS).$(FILE_EXT_INCLUDE)

	$(CXX) -c $(CFLAGS) -I$(PATH_LIB) -I$(PATH_INCLUDE) \
	$(PATH_SRC)/$(CLASS_UTILS_HTML).$(FILE_EXT_SRC) -o \
	$(PATH_BUILD)/$(CLASS_UTILS_HTML).$(FILE_EXT_BUILD)

$(CLASS_EXEC_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_BUILD): \
	$(PATH_SRC)/$(CLASS_EXEC_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_SRC) \
	$(PATH_INCLUDE)/$(CLASS_EXEC_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_SMS).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_CONTACT).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_UTILS_STRING).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_UTILS_FILE_SYSTEM).$(FILE_EXT_INCLUDE) \
	$(PATH_LIB)/CTML.h $(PATH_INCLUDE)/$(CLASS_UTILS_HTML).$(FILE_EXT_INCLUDE)

	$(CXX) -c $(CFLAGS) -I$(PATH_LIB) -I$(PATH_INCLUDE) \
	$(PATH_SRC)/$(CLASS_EXEC_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_SRC) \
	-o $(PATH_BUILD)/$(CLASS_EXEC_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_BUILD)

$(CLASS_GUI_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_BUILD): \
	$(PATH_SRC)/$(CLASS_GUI_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_SRC) \
	$(PATH_INCLUDE)/$(CLASS_GUI_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_EXEC_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_TELEPHONE_NUMBER).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_SMS).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_CONTACT).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_UTILS_STRING).$(FILE_EXT_INCLUDE) \
	$(PATH_INCLUDE)/$(CLASS_UTILS_FILE_SYSTEM).$(FILE_EXT_INCLUDE) \
	$(PATH_LIB)/CTML.h $(PATH_INCLUDE)/$(CLASS_UTILS_HTML).$(FILE_EXT_INCLUDE)

	$(CXX) -c $(CFLAGS) -I$(PATH_LIB) -I$(PATH_INCLUDE) \
	$(PATH_SRC)/$(CLASS_GUI_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_SRC) -o \
	$(PATH_BUILD)/$(CLASS_GUI_CONTACTS_AND_SMS_REPORTS).$(FILE_EXT_BUILD) \
	`pkg-config gtkmm-3.0 --cflags --libs`

clean:
	rm -Rf $(PATH_BUILD_ROOT) $(PATH_BIN_ROOT)