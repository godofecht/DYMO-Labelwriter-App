/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   postinstall;
    const int            postinstallSize = 192;

    extern const char*   lprintadd_1;
    const int            lprintadd_1Size = 2602;

    extern const char*   lprintcancel_1;
    const int            lprintcancel_1Size = 1213;

    extern const char*   lprintdefault_1;
    const int            lprintdefault_1Size = 1011;

    extern const char*   lprintdelete_1;
    const int            lprintdelete_1Size = 858;

    extern const char*   lprintdevices_1;
    const int            lprintdevices_1Size = 735;

    extern const char*   lprintdrivers_1;
    const int            lprintdrivers_1Size = 737;

    extern const char*   lprintjobs_1;
    const int            lprintjobs_1Size = 886;

    extern const char*   lprintmodify_1;
    const int            lprintmodify_1Size = 2647;

    extern const char*   lprintoptions_1;
    const int            lprintoptions_1Size = 919;

    extern const char*   lprintprinters_1;
    const int            lprintprinters_1Size = 561;

    extern const char*   lprintserver_1;
    const int            lprintserver_1Size = 3727;

    extern const char*   lprintshutdown_1;
    const int            lprintshutdown_1Size = 556;

    extern const char*   lprintstatus_1;
    const int            lprintstatus_1Size = 884;

    extern const char*   lprintsubmit_1;
    const int            lprintsubmit_1Size = 3961;

    extern const char*   lprint_1;
    const int            lprint_1Size = 1776;

    extern const char*   lprint_conf_5;
    const int            lprint_conf_5Size = 1029;

    extern const char*   configure;
    const int            configureSize = 253;

    extern const char*   lprintserver;
    const int            lprintserverSize = 1272;

    extern const char*   snapcraft_yaml;
    const int            snapcraft_yamlSize = 2608;

    extern const char*   lprintde_strings;
    const int            lprintde_stringsSize = 3018;

    extern const char*   lprinten_strings;
    const int            lprinten_stringsSize = 2810;

    extern const char*   lprintes_strings;
    const int            lprintes_stringsSize = 3103;

    extern const char*   lprintfr_strings;
    const int            lprintfr_stringsSize = 3141;

    extern const char*   lprintit_strings;
    const int            lprintit_stringsSize = 3089;

    extern const char*   lprintlarge_png;
    const int            lprintlarge_pngSize = 24908;

    extern const char*   lprintsmall_png;
    const int            lprintsmall_pngSize = 5964;

    extern const char*   lprint_png;
    const int            lprint_pngSize = 6491;

    extern const char*   badlabel_pwg;
    const int            badlabel_pwgSize = 114399;

    extern const char*   complexlabel_pwg;
    const int            complexlabel_pwgSize = 288143;

    extern const char*   samplelabel_pwg;
    const int            samplelabel_pwgSize = 70142;

    extern const char*   IDEWorkspaceChecks_plist;
    const int            IDEWorkspaceChecks_plistSize = 238;

    extern const char*   UserInterfaceState_xcuserstate;
    const int            UserInterfaceState_xcuserstateSize = 48623;

    extern const char*   contents_xcworkspacedata;
    const int            contents_xcworkspacedataSize = 151;

    extern const char*   xcschememanagement_plist;
    const int            xcschememanagement_plistSize = 453;

    extern const char*   project_pbxproj;
    const int            project_pbxprojSize = 39909;

    extern const char*   CHANGES_md;
    const int            CHANGES_mdSize = 3582;

    extern const char*   config_guess;
    const int            config_guessSize = 49794;

    extern const char*   config_h_in;
    const int            config_h_inSize = 350;

    extern const char*   config_log;
    const int            config_logSize = 8731;

    extern const char*   config_status;
    const int            config_statusSize = 27896;

    extern const char*   config_sub;
    const int            config_subSize = 35406;

    extern const char*   configure2;
    const int            configure2Size = 147496;

    extern const char*   configure_ac;
    const int            configure_acSize = 6393;

    extern const char*   CONTRIBUTING_md;
    const int            CONTRIBUTING_mdSize = 492;

    extern const char*   DOCUMENTATION_md;
    const int            DOCUMENTATION_mdSize = 13192;

    extern const char*   installsh;
    const int            installshSize = 5572;

    extern const char*   LICENSE;
    const int            LICENSESize = 11357;

    extern const char*   lprint;
    const int            lprintSize = 327440;

    extern const char*   lprintcommon_o;
    const int            lprintcommon_oSize = 67248;

    extern const char*   lprintdymo_o;
    const int            lprintdymo_oSize = 102496;

    extern const char*   lprintepl2_o;
    const int            lprintepl2_oSize = 79392;

    extern const char*   lprinttestpage_o;
    const int            lprinttestpage_oSize = 76312;

    extern const char*   lprintzpl_o;
    const int            lprintzpl_oSize = 137320;

    extern const char*   lprint_o;
    const int            lprint_oSize = 240680;

    extern const char*   lprint_service;
    const int            lprint_serviceSize = 254;

    extern const char*   lprint_service_in;
    const int            lprint_service_inSize = 248;

    extern const char*   lprint_spec;
    const int            lprint_specSize = 1670;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 58;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
