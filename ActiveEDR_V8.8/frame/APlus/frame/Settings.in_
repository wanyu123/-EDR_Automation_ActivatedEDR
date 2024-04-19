[ ] 
[ ] use "..\include\generic_library.inc"
[ ] use "..\include\Functions.inc"
[ ] 
[ ] const string sVersion="V15.0"
[ ] const string sVersionEDR ="V15.0"
[ ] const string sDatabaseVersion="APV150"
[ ] const string sProgramFilePath =getProgramFilePath()
[ ] const string sStartMenu = getStartMenu()
[ ] const string sAspenPlusExamples = "{sProgramFilePath}\AspenTech\Aspen Plus {sVersion}\GUI\Examples"
[ ] const string sAspenPlusEngine ="{sProgramFilePath}\AspenTech\Aspen Plus {sVersion}\Engine"
[ ] const string sAprSystemEngine="{sProgramFilePath}\AspenTech\AprSystem {sVersion}\Engine\Xeq"
[ ] const string sAspenPlusFavorites = "{sProgramFilePath}\AspenTech\Aspen Plus {sVersion}\Favorites"
[ ] const string sAspenPropertiesExamples = "{sProgramFilePath}\AspenTech\Aspen Properties {sVersion}\GUI\Examples"
[ ] String sAspenPlus_DynamicsDir="{sProgramFilePath}\AspenTech\AMSystem {sVersion}\Bin"
[ ] String sAspenPlus_DynamicsExamples ="{sProgramFilePath}\AspenTech\Aspen Plus Dynamics {sVersion}\Examples"
[ ] //String  sAspenPlus_sProjectDir=StrTran(currentpath,"\frame","")+"\"
[ ] String  sAspenPlus_sProjectDir=StrTran(currentpath,"\frame\APlus\frame","")+"\"
[ ] string sPlanHomeDir = "{sAspenPlus_sProjectDir}plan"
[ ] string sScriptHomeDir = "{sAspenPlus_sProjectDir}script"
[ ] string sDefaultWorkingFolder = "C:\ProgramData\AspenTech\Aspen Plus {sVersion}"
[ ] const string sAPlusToolTip ="Disabled. Please add an exchanger onto your flowsheet to enable this button."
[ ] const sAPED = "{sProgramFilePath}\\AspenTech\APrSystem {sVersion}\PropertiesDatabase\Bin\dbTesterAdv.exe"
[ ] 
[ ] 
[ ] String sDatain = "{sAspenPlus_sProjectDir}data\datain"
[ ] String sDataout = "{sAspenPlus_sProjectDir}data\dataout"
[ ] String sDatatemp = "{sAspenPlus_sProjectDir}data\datatemp"
[ ] String sSavedCasesPath
[ ] String sPrintOutput
[ ] String	sOutputCopareResults
[ ] String	sCmd
[ ] String sCaseName
[ ] String sTestCaseID
[ ] const string csToolsPath = StrTran(currentpath,"\frame","")+"\data\datain\tools"
[ ] const integer iShortDelay = 3
[ ] const integer iMidDelay = 10
[ ] const integer iLongDelay = 30
[ ] HTIMER	hOpenTimer = NULL
[ ] type ListStringOrString is STRING, LIST OF STRING
[ ] const double dbTolerance = 0.01
[ ] 
[+] //---------------------------------------Adiff configuration-----------------------------------------------------//
	[ ] const float cfRelTol = 0.01 
	[ ] const float cfAbsTol = 0.001
	[ ] const string csAdiffCmdLine = csToolsPath+"\adiff\adiff.exe"
[ ] 
[+] //---------------------------------------Example update configuration------------------------------------//
	[ ] //A+ will update the example files two or three media earlier before final release,
	[ ] //So set bAfterUpdateExmaples to false on earlier media to suppress the upward compatibility dialog(upgrade databanks)
	[ ] //and don't report defect. But after examples updating, file a defect if upward compatibilityupgrade databanks) dialog pops up 
	[ ] boolean bAfterUpdateExmaples = true
[ ] 
[ ] //method
[-] string getProgramFilePath()
	[-] // if(SYS_DirExists("%ProgramFiles(x86)%"))
		[ ] // return SYS_GetEnv("ProgramFiles(x86)")
	[-] // else
		[ ] return "C:\Program Files"
[ ] 
[+] string getStartMenu()
	[ ] 
	[ ] integer iKey = HKEY_LOCAL_MACHINE
	[ ] string sPath = "SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders"
	[ ] string sItem = "Common Start Menu"
	[ ] return SYS_GetRegistryValue (iKey, sPath, sItem)
	[ ] 
	[ ] 
[ ] 
[+] list of STRING GetScriptList(string sDir)
	[ ] //Get all script file(.t) in {sDir}, include sub directory
	[ ] 
	[ ] integer i
	[ ] list of STRING IsScript
	[ ] 
	[ ] list of FILEINFO IfiDir = glSYS_GetDirContents(sDir)
	[ ] 
	[+] for(i=1;i<=ListCount(IfiDir);i++)
		[ ] 
		[ ] FILEINFO fi = IfiDir[i]
		[+] if !fi.bIsDir
			[ ] 
			[+] if MatchStr("*.t", fi.sName)
				[ ] 
				[ ] ListAppend(IsScript, "{sDir}\{fi.sName}")
		[+] else
			[ ] 
			[ ] sDir = "{sDir}\{fi.sName}"
			[ ] ListMerge(IsScript, GetScriptList(sDir))
	[ ] 
	[ ] return IsScript
	[ ] 
	[ ] 
[ ] 
[-] string GetScriptFile(string sTestCase)
	[ ] //Get the script file(.t) which contains testcase(sTestcase)
	[ ] 
	[ ] integer i
	[ ] integer j
	[ ] string sScript
	[ ] string sLine
	[ ] string sReturn
	[ ] 
	[ ] string sDir = "{sAspenPlus_sProjectDir}script"
	[ ] 
	[ ] list of STRING IsScript = GetScriptList(sDir)
	[ ] 
	[ ] boolean b = false
	[-] for(i=1;i<=ListCount(IsScript);i++)
		[ ] 
		[ ] list of string IsLine
		[ ] sScript = IsScript[i]
		[ ] ListRead(IsLine, sScript)
		[ ] 
		[+] for (j=1;j<=ListCount(IsLine);j++)
			[ ] sLine = IsLine[j]
			[+] if (MatchStr("*testcase*{lower(sTestCase)}*", lower(sLine)))
				[ ] b = true
				[ ] return sScript
				[ ] 
		[ ] 
	[+] if !b
		[ ] LogError("Failed to find testcase {sTestCase} in {sDir}")
	[ ] return ""
[ ] 
[ ] int lastErrorCount = -1
[ ] int programErrorCount = 0
[ ] int bitmapErrorCount = 0
[ ] 
[-] TestCaseEnter()
	[ ] //This is just to initialize error counting variables
	[ ] DefaultTestCaseEnter()
	[ ] lastErrorCount = -1
	[ ] programErrorCount = 0
	[ ] bitmapErrorCount = 0
	[ ] Agent.SetOption(OPT_SYNC_TIMEOUT, 5)
[ ] 
[-] TestCaseExit (BOOLEAN bException)
	[ ] //Rewrite TestCaseExit, add testcase to Fail Plan when it has exception
	[ ] 
	[ ] checkForProgramError()
	[-] if( ExceptNum( ) == E_BITMAPS_DIFFERENT)
		[ ] Log.Warning("THIS TEST HAS EXITED WHEN FAILING TO VERIFY A BITMAP")
	[ ] 
	[ ] string sTestCase  = GetTestCaseName()
	[ ] string sScript = GetScriptFile(sTestCase)
	[ ] boolean bAdded = false
	[ ] List of ANYTYPE IaArg = GetTestCaseArgs()
	[ ] string sArgs=""
	[ ] int i=1
	[-] if(IaArg!=null)
		[ ] int sArgsCount = ListCount(IaArg)
		[-] for(i=1;i<=sArgsCount;i++)
			[ ] //No ',' at the last argrment.
			[-] if(i==sArgsCount)
				[-] if(IaArg[i] ==null)
					[ ] sArgs = SubStr(sArgs,1,Len(sArgs)-1)
				[-] else 
					[ ] sArgs = sArgs+""""+IaArg[i]+""""
				[ ] break
			[ ] sArgs = sArgs+""""+IaArg[i]+""","
			[ ] 
	[ ] //Testcase will be added to Fail Plan only when it has exception
	[+] if (bException)
		[ ] 
		[+] if(GetTestPlanName()!=NULL)
			[ ] string sPlanName = GetTestPlanName()
			[+] if(!MatchStr("*_fail.pln",lower(sPlanName)))
				[ ] sPlanName = StrTran(sPlanName, ".pln","_Fail.pln")
				[ ] string sFailPlan = "{sPlanHomeDir}\{sPlanName}"
				[ ] 
				[ ] HFILE hFile = FileOpen(sFailPlan, FM_APPEND)
				[ ] FileWriteLine(hFile,"script: {sScript}")
				[ ] FileWriteLine(hFile, sTestCase)
				[ ] FileWriteLine(hFile, "{chr(9)}testcase: {sTestCase}()")
				[+] if(IaArg !=null)
					[ ] FileWriteLine(hFile, "{chr(9)}testdata: {sArgs}")
				[ ] bAdded = true
				[ ] FileClose(hFile)
	[ ] 
	[ ] DefaultTestCaseExit(bException)
	[ ] //Testcase will be added to Fail Plan when it failed
	[ ] 
	[ ] // int iErrCount = GetTestCaseErrorCount()
	[+] // if ((bAdded ==false) && (iErrCount >=1))
		[+] // if(GetTestPlanName()!=NULL)
			[ ] // string sPlanName = GetTestPlanName()
			[ ] // 
			[+] // if(!MatchStr("*_fail.pln",lower(sPlanName)))
				[ ] // sPlanName = StrTran(sPlanName, ".pln","_Fail.pln")
				[ ] // string sFailPlan = "{sPlanHomeDir}\{sPlanName}"
				[ ] // 
				[ ] // HFILE hFile = FileOpen(sFailPlan, FM_APPEND)
				[ ] // FileWriteLine(hFile,"script: {sScript}")
				[ ] // FileWriteLine(hFile, sTestCase)
				[ ] // FileWriteLine(hFile, "{chr(9)}testcase: {sTestCase}()")
				[ ] // bAdded = true
				[ ] // FileClose(hFile)
		[ ] // 
	[ ] 
	[ ] 
	[ ] lastErrorCount = GetTestCaseErrorCount()
	[ ] lastErrorCount -= bitmapErrorCount
	[ ] 
[ ] 
[-] TestPlanEnter()
	[ ] //Rewrit TestPlanEnter, Remove Fail Plan if current plan is not Fail Plan
	[ ] string sPlanName = GetTestPlanName()
	[+] if(!MatchStr("*_fail.pln",lower(sPlanName)))
		[ ] 
		[ ] sPlanName = StrTran(sPlanName, ".pln","_Fail.pln")
		[ ] string sFailPlan = "{sPlanHomeDir}\{sPlanName}"
		[+] if(SYS_FileExists(sFailPlan))
			[ ] SYS_RemoveFile(sFailPlan)
	[ ] Agent.SetOption(OPT_SYNC_TIMEOUT, 5)
	[ ] DefaultTestPlanEnter()
[ ] 
[ ] 
[ ] 
