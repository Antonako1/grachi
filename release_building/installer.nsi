unicode True

!include LogicLib.nsh
!define WM_WININICHANGE 0x001A
!define HWND_BROADCAST 0xFFFF
!define WM_SETTINGCHANGE 0x001A

!define VERSION "0.0.1"
!define PROJECTNAME "grachi"

Outfile "${PROJECTNAME}-win-installer-v${VERSION}.exe"
BrandingText /TRIMCENTER "${PROJECTNAME} Setup V${VERSION}"
Name "${PROJECTNAME} Setup V${PROJECTNAME}"
RequestExecutionLevel admin

ManifestSupportedOS Win10
DetailsButtonText "Show progress"

######### LICENSE ############
PageEx license
    LicenseText "LICENSE"
    LicenseData LICENSE
    LicenseForceSelection checkbox
PageExEnd

############ DIRECTORY ######################
Var INSTALL_DIR

PageEx directory
    DirVar $INSTALL_DIR
    DirVerify leave
PageExEnd

Function .onVerifyInstDir
    Var /GLOBAL ext
    StrCpy $ext "${PROJECTNAME}"
    StrCpy $INSTALL_DIR "$INSTALL_DIR$ext"
    ; Checks if folder already exists
    Call CheckFolder
FunctionEnd

; Checks if the folder exists, if it exists and user wants to delete
; it and it's contents the script will continue
Function CheckFolder
DetailPrint "Checking folder."
${If}  ${FileExists} $INSTALL_DIR
    ; Delete it
    MessageBox MB_YESNO|MB_ICONQUESTION `"$INSTALL_DIR" already exists, delete its contents and continue installing?` IDYES agree
    Abort "Setup aborted by user."
agree:
    DetailPrint 'Removing "$INSTALL_DIR" and its contents.'
    RMDir /r $INSTALL_DIR
${EndIf}
FunctionEnd

##########INSTFILE"######################
PageEx instfiles
PageExEnd

############## INIT ######################
; Set the default installation directory
Function .onInit
    InitPluginsDir
    StrCpy $INSTALL_DIR $PROGRAMFILES64\${PROJECTNAME}
FunctionEnd

############################## START ##############################
Section 

; After deletion begin with setup

; Check the folder
Call CheckFolder

; Set the installation directory
SetOutPath $INSTALL_DIR

; Create the installation directory if it doesn't exist
CreateDirectory $INSTALL_DIR

; Files to install
File "${PROJECTNAME}.exe"
File "LICENSE"
File "README.txt"

SectionEnd

############# SETUP ################
Section 

########## EXTRACTION ##########
; Extract files based on section selection


; Create an uninstaller in the same directory as the installer
WriteUninstaller "$INSTALL_DIR\Uninstall.exe"
DetailPrint 'You can now close this windows by pressing "Close".' 

SectionEnd

########## UNINSTALL ##########

UninstPage uninstConfirm
UninstPage instfiles

Section "Uninstall"
########################### DELETE FILES ###########################
; Remove installed files during uninstallation

Delete "$INSTDIR\${PROJECTNAME}.exe"
Delete "$INSTDIR\license"

; Remove the installation directory if it still exists
RMDir /r $INSTDIR

SectionEnd