#ifndef _GUI_CONTACTS_AND_SMS_REPORTS_H_
#define _GUI_CONTACTS_AND_SMS_REPORTS_H_
#include <gtkmm/window.h>
#include <gtkmm/filechooserbutton.h>
#include <gtkmm/builder.h>
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

class GUIContactsAndSmsReports
{
    public:
        GUIContactsAndSmsReports();
        GUIContactsAndSmsReports(const Glib::ustring & applicationId);
        void Run();
        ~GUIContactsAndSmsReports();
    protected:
        void ConnectWidgetsEventSignalsToFunctions();
        void OnGUIContactsFilePathButtonFileSetEvent();
        void OnGUISmsFilePathButtonFileSetEvent();
        void OnGUIDestinationPathButtonFileSetEvent();
        void OnGUIExecuteButton();
        void OnGUIQuitButton();
    private:

        Glib::RefPtr<Gtk::Builder> builder;
        Glib::RefPtr<Gtk::Application> application;
        Gtk::Window * mainWindow;
        Gtk::FileChooserButton * contactsFilePathButton, * smsFilePathButton, * destinationPathButton;
        Gtk::Button * executeButton, * quitButton;

        std::string contactsFilePath, smsFilePath, destinationPathForReportsResults;
        
        ExecContactsAndSmsReports applicationExec;
};

#endif