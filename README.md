# Welcome
**Phone contacts and SMS reports** is a software that lets you create web documents with all your smartphone contacts and SMS messages. Thanks to a web browser you can navigate easily and friendly through this information.

# Requirements
- A computer with **GNU/Linux** or **Macintosh**.
- The **contacts file** must be a **vCard** file (_.vcf_ or _.vcard_ file extension).
- The **SMS file** must be an **XML** file (_.xml_ file extension).

## How to get the contacts and SMS files
These files need to be exported and stored on the PC or Mac. Each mobile OS and version shows a different way to perform this task. It is recommended to use **Super Backup app** to achieve this goal in a **easy way**.

* Android: https://play.google.com/store/apps/details?id=com.idea.backup.smscontacts
* iOS: https://itunes.apple.com/us/app/super-backup-export-import/id1052684097

### Android
- How to export contacts: https://www.androidcentral.com/move-contacts-android

### iOS
- How to export contacts: https://www.techadvisor.co.uk/how-to/apple/how-copy-iphone-contacts-your-pc-3300299/

# Compiling the application (GNU/Linux, MacOS)
1. Download the source code.
2. Open a terminal and navigate to the root folder.
2. Run `$ make` to perform the compilation.

Now you can run the application.

# Running the application (GNU/Linux, MacOS)
## GUI mode
1. Open a terminal and navigate to the root folder.
2. Execute the command `$ ./phone_contacts_report`.

![GUI main window](https://github.com/zerosk8/phone-contacts-sms-report/blob/master/documentation/images/gui_main.png)

## Console mode
1. Open a terminal and navigate to the root folder.
2. Execute the command `$ ./phone_contacts_report` and specify:
* `-c` (`--contacts`) option with the contacts file path.
* `-s` (`--sms`) option with the SMS file path.
* `-o` (`--output`) option with a folder path, to generate the report files in this folder.

Examples:
- `./phone_contacts_report -c ./TestFiles/short_example_contacts_file.vcf -s ./TestFiles/short_example_sms_file.xml -o /home/user/Desktop/`. 
This will generate web documents with phone contacts and SMS messages in the desktop folder.

- `./phone_contacts_report -c ./TestFiles/short_example_contacts_file.vcf -s ./TestFiles/short_example_sms_file.xml -o /home/user/Desktop/`. 
This will generate a web document with phone contacts in the desktop folder.

- `./phone_contacts_report -s ./TestFiles/short_example_sms_file.xml -o /home/user/Desktop/`. 
This will generate a web document with SMS messages in the desktop folder.

- `./phone_contacts_report -c ./TestFiles/short_example_contacts_file.vcf`. 
This will generate a web document with phone contacts in the root application folder.

# Result files
## Contacts report file

![Contacts report file](https://github.com/zerosk8/phone-contacts-sms-report/blob/master/documentation/images/contacts_report.png)

## SMS messages report file

![SMS messages report file](https://github.com/zerosk8/phone-contacts-sms-report/blob/master/documentation/images/sms_messages_report.png)

## SMS messages per contact report file

![SMS messages per contact report file](https://github.com/zerosk8/phone-contacts-sms-report/blob/master/documentation/images/contact_sms_messages_report.png)
