#ifndef _GUI_CONTACTS_AND_SMS_REPORTS_H_
#define _GUI_CONTACTS_AND_SMS_REPORTS_H_
#include <gtkmm/builder.h>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/button.h>
#include <iostream>
#include <string>
#include "exec_contacts_and_sms_reports.h"

const std::string GLADE_FILE_PATH = "./classes/glade/GUI_contacts_and_sms_reports.glade";
const std::string GLADE_ID_MAIN_WINDOW = "GUIMainWindow";
const std::string GLADE_ID_CONTACTS_FILE_PATH_BUTTON = "GUIContactsFilePathButton";
const std::string GLADE_ID_SMS_FILE_PATH_BUTTON = "GUISmsFilePathButton";
const std::string GLADE_ID_DESTINATION_PATH_BUTTON = "GUIDestinationPathButton";
const std::string GLADE_ID_EXECUTE_BUTTON = "GUIExecuteButton";
const std::string GLADE_ID_QUIT_BUTTON = "GUIQuitButton";
const std::string GLADE_ID_MESSAGE_DIALOG = "GUIMessageDialog";
const std::string GLADE_ID_MESSAGE_DIALOG_OK_BUTTON = "GUIMessageDialogOkButton";
const char MESSAGE_DIALOG_ERROR_TEXT_SEPARATOR_CHAR = ':';
const std::string MESSAGE_DIALOG_MISSING_INPUT_MESSAGE = "Missing contacts or SMS messages";
const std::string MESSAGE_DIALOG_MISSING_OUTPUT_MESSAGE = 
"Missing directory path";
const std::string MESSAGE_DIALOG_SUCCESS_MESSAGE = "Success";
const std::string MESSAGE_DIALOG_MISSING_INPUT_FILE_TEXT = 
"Please, select a contacts file and/or a SMS messages file.";
const std::string MESSAGE_DIALOG_MISSING_OUTPUT_PATH_TEXT = 
"Please, select a directory path for report results files.";
const std::string MESSAGE_DIALOG_SUCCESS_TEXT = "Report results files created in ";

class GUIContactsAndSmsReports
{
    public:
        GUIContactsAndSmsReports();
        GUIContactsAndSmsReports(const Glib::ustring & applicationId);
        int Run();
        ~GUIContactsAndSmsReports();
    private:
        void ConnectWidgetsEventSignalsToFunctions();
        void displayInformationMessageDialog(const std::string & informationMessage,
        const std::string & informationText);
        void displaySuccessMessageDialog(const std::string & successText);
        void displayErrorMessageDialog(const std::string & errorText);
        // Signal handlers
        void OnGUIContactsFilePathButtonFileSetEvent();
        void OnGUISmsFilePathButtonFileSetEvent();
        void OnGUIDestinationPathButtonFileSetEvent();
        void OnGUIExecuteButton();
        void OnGUIQuitButton();
        void OnMessageDialogOkButton();
        // Child widgets
        Glib::RefPtr<Gtk::Builder> builder;
        Glib::RefPtr<Gtk::Application> application;
        Gtk::ApplicationWindow * mainWindow;
        Gtk::MessageDialog * messageDialog;
        Gtk::FileChooserButton * contactsFilePathButton, * smsFilePathButton, * destinationPathButton;
        Gtk::Button * executeButton, * quitButton, * messageDialogOkButton;
        ExecContactsAndSmsReports applicationExec;
};

#endif