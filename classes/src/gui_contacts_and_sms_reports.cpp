#include "gui_contacts_and_sms_reports.h"

GUIContactsAndSmsReports::GUIContactsAndSmsReports(){}

GUIContactsAndSmsReports::GUIContactsAndSmsReports(const Glib::ustring & applicationId)
{
    application = Gtk::Application::create(applicationId);
    builder = Gtk::Builder::create_from_file(GLADE_FILE_PATH);
    builder->get_widget(GLADE_ID_MAIN_WINDOW,mainWindow);
    builder->get_widget(GLADE_ID_CONTACTS_FILE_PATH_BUTTON,contactsFilePathButton);
    builder->get_widget(GLADE_ID_SMS_FILE_PATH_BUTTON,smsFilePathButton);
    builder->get_widget(GLADE_ID_DESTINATION_PATH_BUTTON,destinationPathButton);
    builder->get_widget(GLADE_ID_EXECUTE_BUTTON,executeButton);
    builder->get_widget(GLADE_ID_QUIT_BUTTON,quitButton);
    
    ConnectWidgetsEventSignalsToFunctions();
}

void GUIContactsAndSmsReports::Run()
{
    application->run(*mainWindow);
}

GUIContactsAndSmsReports::~GUIContactsAndSmsReports(){}

/**************************************/

void GUIContactsAndSmsReports::ConnectWidgetsEventSignalsToFunctions()
{
    contactsFilePathButton->signal_file_set().connect(sigc::mem_fun(*this,
    &GUIContactsAndSmsReports::OnGUIContactsFilePathButtonFileSetEvent));
    smsFilePathButton->signal_file_set().connect(sigc::mem_fun(*this,
    &GUIContactsAndSmsReports::OnGUISmsFilePathButtonFileSetEvent));
    destinationPathButton->signal_file_set().connect(sigc::mem_fun(*this,
    &GUIContactsAndSmsReports::OnGUIDestinationPathButtonFileSetEvent));
    executeButton->signal_clicked().connect(sigc::mem_fun(*this,
    &GUIContactsAndSmsReports::OnGUIExecuteButton));
    quitButton->signal_clicked().connect(sigc::mem_fun(*this,
    &GUIContactsAndSmsReports::OnGUIQuitButton));
}

void GUIContactsAndSmsReports::OnGUIContactsFilePathButtonFileSetEvent()
{
    contactsFilePath = contactsFilePathButton->get_filename();
}

void GUIContactsAndSmsReports::OnGUISmsFilePathButtonFileSetEvent()
{
    smsFilePath = smsFilePathButton->get_filename();
}

void GUIContactsAndSmsReports::OnGUIDestinationPathButtonFileSetEvent()
{
    destinationPathForReportsResults = UTILS_FILE_SYSTEM.GetFileOrDirectoryPathString
    (destinationPathButton->get_filename(),DIR_NAME_FOR_REPORT_RESULTS);
}

void GUIContactsAndSmsReports::OnGUIExecuteButton()
{
    if((!contactsFilePath.empty() || !smsFilePath.empty()) && !destinationPathForReportsResults.empty())
    {
        std::pair<bool,std::string> applicationExecResult;
        applicationExec = ExecContactsAndSmsReports(contactsFilePath,smsFilePath,
        destinationPathForReportsResults);
        applicationExecResult = applicationExec.Run();
        if(!applicationExecResult.first)
        {
            std::cerr << applicationExecResult.second << std::endl;
        }
    }
}

void GUIContactsAndSmsReports::OnGUIQuitButton()
{
    exit(0);
}