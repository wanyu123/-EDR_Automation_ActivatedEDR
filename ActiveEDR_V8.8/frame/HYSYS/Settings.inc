[ ] use "generic_library.inc"
[ ] use "24hRunningByNobody.inc"
[ ] use "Frame.inc"
[ ] 
[ ] const string sVersion="V15.0"
[ ] const string sVersionEDR ="V15.0"
[ ]  const string sVersionDB ="V150"
[ ] //const string sVersionNumeric = "39.0"
[ ] const string sProgramFilePath =getProgramFilePath()
[ ] const string sStartMenu = getStartMenu()
[ ] const string sAspenHysysSamples = "{sProgramFilePath}\AspenTech\Aspen Hysys {sVersion}\Samples"
[ ] const string sAspenHysysTemplate = "{sProgramFilePath}\AspenTech\Aspen Hysys {sVersion}\Template"
[ ] const string sEDRSamples = "{sProgramFilePath}\AspenTech\Aspen Exchanger Design and Rating {sVersionEDR}\Examples"
[ ] const string sAspenHysysInstallFolder = "{sProgramFilePath}\AspenTech\Aspen Hysys {sVersion}"
[ ] const string sAHToolTip ="Disabled. Please add an exchanger onto your flowsheet to enable this button."
[ ] //String  sAspenHysys_sProjectDir=StrTran(currentpath,"\frame","")+"\"
[ ] String  sAspenHysys_sProjectDir=StrTran(currentpath,"\frame\HYSYS","")+"\"
[ ] 
[ ] String sTools = "{sAspenHysys_sProjectDir}data\datain\Tools"
[ ] String sDatain = "{sAspenHysys_sProjectDir}data\datain"
[ ] String sDataout = "{sAspenHysys_sProjectDir}data\dataout"
[ ] String sDatatemp = "{sAspenHysys_sProjectDir}data\datatemp"
[ ] String sDatainExampleFiles = "{sDatain}\ExampleFiles"
[ ] String sUserRegisterFile = "{sDatain}\tools\Register.bat"
[ ] String sSavedCasesPath
[ ] String sPrintOutput
[ ] String sOutputCopareResults
[ ] String sCmd
[ ] String sCaseName
[ ] String sValue
[ ] String sTestCaseID
[ ] string dlgType=SetDialogType()
[ ] //const string csToolsPath = StrTran(currentpath,"\frame","")+"\data\datain\tools"
[ ] const string csToolsPath = StrTran(currentpath,"\frame\HYSYS","")+"\data\datain\tools"
[ ] const integer iShortDelay = 3
[ ] const integer iMidDelay = 10
[ ] const integer iLongDelay = 30
[ ] boolean bValue
[ ] list of STRING lstString
[ ] list of STRING lstObjectsToSelect
[ ] HTIMER	hTimer
[ ] HTIMER	hOpenTimer = NULL
[ ] 
[ ] 
[ ] 
[ ] //------------------DBR AMINE PACKAGE CONSTANTS------------------------------------------------------------------------------
[ ] 
[ ] const string  DBRAminePackageName = "DBR Amine Package (v2012.1)"
[ ] const string  DBRAminePackageLocation64 = "C:\Program Files (x86)\Common Files\Hyprotech\DBRAmine\DBRAminePkg.dll"
[ ] const string DBRAminePackageLocation32 = "C:\Program Files\Common Files\Hyprotech\DBRAmine\DBRAminePkg.dll"
[ ] 
[ ] //-----------------------------------------------------------------------------------------------------------------------
[ ] 
[ ] 
[ ] 
[+] //---------------------------------------Adiff configuration-----------------------------------------------------//
	[ ] const float cfRelTol = 0.01 
	[ ] const float cfAbsTol = 0.001
	[ ] const string csAdiffCmdLine = csToolsPath+"\adiff\adiff.exe"
[ ] //method
[-] string getProgramFilePath()
	[+] // if(SYS_DirExists("%ProgramFiles(x86)%"))
		[ ] // return SYS_GetEnv("ProgramFiles(x86)")
	[-] // else
		[ ] return "C:\Program Files"
[+] string getStartMenu()
	[ ] 
	[ ] integer iKey = HKEY_LOCAL_MACHINE
	[ ] string sPath = "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders"
	[ ] string sItem = "Common Start Menu"
	[ ] return SYS_GetRegistryValue (iKey, sPath, sItem)
	[ ] 
	[ ] 
[+] string SetDialogType()
	[+] if(sVersion>"V8.3")
		[ ] dlgType="MainWin"
	[+] else
		[ ] dlgType="DialogBox"
	[ ] return dlgType
[-] TestCaseExit(boolean bException)
	[ ] Agent.SetOption (OPT_BITMAP_MATCH_COUNT, 0)
	[ ] Agent.SetOption (OPT_BITMAP_MATCH_INTERVAL, 0)
	[ ] Agent.SetOption (OPT_BITMAP_MATCH_TIMEOUT, 0)
	[ ] print(sDataout)
	[ ] string sExcepInfo = ExceptData()
	[-] if((sExcepInfo != null) && (!dlgAspenHysysCrashWindow.Exists()))
		[-] if(Len(sExcepInfo)>0)
			[ ] ExceptLog()
			[-] if(sDataout != null)
				[-] do
					[ ] Desktop.CaptureBitmap("{sDataout}\error.bmp")
					[ ] Log.Message("You can reference the screenshot {sDataout}\error.bmp")
				[-] except
					[ ] 
	[+] // if(dlgAspenHysysCrashWindow.Exists())
			[+] // do
				[ ] // Desktop.CaptureBitmap("{sDataout}\Crash.bmp")
				[ ] // Log.Message("You can reference the screenshot {sDataout}\Crash.bmp")
			[+] // except
				[ ] // 
		[ ] // Log.Fail("Case crashed, you can reference the screenshot {sDataout}\Crash.bmp")
		[ ] // dlgAspenHysysCrashWindow.SetActive()
		[ ] // glWaitForMouseIdle(10)
		[ ] // dlgAspenHysysCrashWindow.Close()
		[ ] // dlgAspenHysysCrashWindow.WaitForDisappearance(10)
	[ ] SYS_Execute("tasklist",lstString)
	[-] if(glFindStringInList("WerFault.exe",lstString))
			[-] do
				[ ] Desktop.CaptureBitmap("{sDataout}\Crash.bmp")
				[ ] Log.Message("You can reference the screenshot {sDataout}\Crash.bmp")
			[-] except
				[ ] 
		[ ] Log.Fail("Case crashed, you can reference the screenshot {sDataout}\Crash.bmp")
		[ ] SYS_Execute("taskkill /f /t /im WerFault.Exe")
		[ ] 
[-] TestPlanExit(boolean bException)
	[ ] SYS_Execute("taskkill /f /t /im aspenhysys.exe")
[ ] 
[ ] //-------------------------------------Function Option ENUMs------------------------------------------------
[ ] 
[-] type OPENTYPE is enum
	[ ] OpenCase
	[ ] Template
	[ ] Column
	[ ] Reformer
	[ ] Hydrocracker
	[ ] CatCracker
	[ ] CutCopyPaste
[ ] 
[ ] 
