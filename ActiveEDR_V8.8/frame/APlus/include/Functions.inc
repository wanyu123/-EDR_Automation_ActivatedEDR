[ ] 
[ ] // use "../frame/Frame.inc"
[ ] use "msw32.inc"
[ ] use "24hRunningByNobody.inc"
[ ] use "../frame/Settings.inc"
[ ] use "../include/APChildwin.inc"
[ ] 
[+] string getInstallationFolder()
	[+] if SYS_FileExists("{sProgramFilePath}\AspenTech\Aspen Plus {sVersion}\GUI\Xeq\AspenPlus.exe")
		[ ] return "{sProgramFilePath}\AspenTech\Aspen Plus {sVersion}\GUI\Xeq\AspenPlus.exe"
	[+] else
		[ ] return "{sProgramFilePath}\AspenTech (x86)\Aspen Plus {sVersion}\GUI\Xeq\AspenPlus.exe"
[ ] 
[+] // void glWaitForMouseIdle(integer iTimeOut)
	[ ] // integer iTime=0
	[ ] // sleep(2)
	[+] // while(Cursor.GetType()=="WAIT" || Cursor.GetType()=="DELAY" && iTime < iTimeOut)
		[ ] // iTime = iTime+5
		[ ] // sleep(5)
	[+] // if(iTime > iTimeOut)
		[ ] // LogError("Component list can not be ctreated in {iTimeOut} seconds")
	[ ] // sleep(3)
[+] void glWaitForMouseIdle(integer iTimeOut optional, integer waitTimes optional)
	[ ] //Default wait of 2.5 Seconds unless mouse is active
	[ ] //waitTimes is the number of sucessive 0.5 second loops with the mouse idle before this function will exit. Min exit time = waitTimes * 0.5 seconds
	[+] if( iTimeOut == NULL )
		[ ] iTimeOut = 30
	[ ] real rTime=0
	[ ] integer counter = 0
	[ ] integer Exit = 5
	[+] if( waitTimes != NULL)
		[+] if( waitTimes <=  0)
			[ ] Log.warning("The wait times should be a positive integer, but you used a 0 or negative one, we will use the default value 5")
		[+] else
			[ ] Exit = waitTimes
	[ ] 
	[+] while( rTime < iTimeOut && counter < Exit)
		[ ] rTime = rTime+0.5
		[ ] sleep(0.5)
		[ ] 
		[+] if( Cursor.GetType()=="WAIT" || Cursor.GetType()=="DELAY" )
			[ ] counter = 0
		[+] else
			[ ] counter++
		[ ] 
		[ ] 
	[+] if(rTime > iTimeOut)
		[ ] Log.Error("ERROR: TIMEOUT REACHED BUT YOUR COMPUTER IS STILL THINKING REALLY HARD")
	[ ] 
[ ] 
[ ] 
[+] void DeteleFolderWithFiles(String filepath)
	[+] //---------------------Log---------------------//
		[ ] // Author		:	Cheers Li
		[ ] // Date			:	2009-09-15
		[ ] //-----------------------------------------------// 
	[ ] filepath=Trim(filepath)
	[+] if(SubStr(filepath,Len(filepath),1)=="\")
		[ ] filepath=SubStr(filepath,1,Len(filepath)-1)
	[+] else
		[ ] filepath=SubStr(filepath,1,Len(filepath))
	[ ] String tempfilepath
	[ ] String tmDir
	[+] if(!SYS_DirExists(filepath))
		[ ] RaiseError(13,"The path : {filepath} does not exists! ")
	[ ] List of FILEINFO fFileContents=SYS_GetDirContents(filepath)
	[+] FILEINFO item
		[+] for each item in fFileContents
			[ ] tempfilepath="{filepath}\"+item.sName
			[+] if(item.bIsDir)
				[+] if(ListCount(SYS_GetDirContents(tempfilepath))==0)
					[ ] SYS_RemoveDir(tempfilepath)
				[+] else
					[ ] DeteleFolderWithFiles(tempfilepath)
					[ ] SYS_RemoveDir(tempfilepath)
			[+] else
				[ ] SYS_RemoveFile(tempfilepath)
[ ] 
[+] void CaptureBitMapNew(window wName,String sPath,String sFileName)
	[+] if(!SYS_DirExists(sPath))
		[ ] SYS_MakeDir(sPath)
	[+] if( SYS_FileExists(sPath+"\"+sFileName))
		[ ] SYS_RemoveFile(sPath+"\"+sFileName)
		[ ] sleep(2)
		[ ] wName.SetActive()
		[ ] sleep(1)
		[ ] wName.CaptureBitmap(sPath+"\"+sFileName)
		[ ] sleep(2)
	[+] else
		[ ] wName.SetActive()
		[ ] wName.CaptureBitmap(sPath+"\"+sFileName)
		[ ] sleep(2)
[ ] 
[+] void CaseCrashHandle(window wObj,string sCaseName)
	[+] if(wObj.Exists())
		[ ] wObj.SetActive()
		[ ] SendMessage(wObj.hWnd,WM_CLOSE,0,0)
		[ ] LogWarning("****** Case: {sCaseName} with crashed message. ******")
[ ] 
[+] string Aspen_GetWPFFControlObjText(window wpfControlObj)	// This method is useful to get combox and textbox  selected value.
	[ ] string sText
	[ ] sText=wpfControlObj.GetProperty("DisplayText")
	[ ] return sText
[ ] 
[+] string Aspen_GetComboxSelectedText(window ComboxObj)
	[ ] string sSelectedText
	[ ] // ComboxObj.Open()
	[ ] sSelectedText=ComboxObj.GetProperty("SelectedItemText")
	[ ] return sSelectedText
[ ] 
[+] void BS_Clean()
	[ ] 
	[ ] Case.RunBy24h(gbRunBy24hRunning)
	[ ] SYS_Execute("taskkill /f /t /im aspenplus.exe")
	[ ] 
	[ ] 
[ ] 
[-] VOID CleanUp ()
	[ ] //--------------------------------------------------------------------------------------------
	[ ] //Function:			End the process of Htfs+ program.
	[ ] //Author:			Danny Wang (Danny.Wang@aspentech.com)
	[ ] //Date:				Aug-28-2008
	[ ] //Usage Scope: 	It is a part a recovery base state 'BaseState'.
	[ ] //Pre: 				It is a globle funtion, only make sure no task manager window currently exists.
	[ ] //Post: 				Clean Htfs+, A+, AProp programs.
	[ ] //--------------------------------------------------------------------------------------------
	[+] LIST OF STRING lsProcess={...}
		[ ] "aspenplus.exe"
		[ ] "AspenSplash.exe"
		[ ] "bjacwin.exe"
		[ ] "AspenProperties.exe"
		[ ] "APropMain.exe"
		[ ] "notepad.exe"
		[ ] "CompareEDRFiles.exe"
		[ ] "iexplore.exe"
		[ ] "SaveAsEDR.exe"
		[ ] "MSPVIEW.EXE"
		[ ] "WINWORD.EXE"
		[ ] "EXCEL.EXE"
		[ ] "taskmgr.exe"
		[ ] "AspenModeler.exe"
    
	[ ] INT i
	[ ] LIST OF STRING lsResult
	[ ] 
	[-] for(i=1;i<listcount(lsProcess)+1;i++)
		[ ] SYS_EXECUTE("taskkill /f /t /im {lsProcess[i]}",lsResult)
	[ ] 
	[ ] 
[ ] 
[ ] 
[+] void CopyFilesToDatatemp(string sOriginalDir)
	[ ] 
	[ ] list of string lsOutput
	[ ] 
	[ ] glSYS_MakeDirDirect(sDatatemp)
	[ ] sOriginalDir = StrTran(sOriginalDir, "\\", "\")
	[+] if (Right(sOriginalDir, 1) == "\")
		[ ] 
		[ ] sOriginalDir = Left(sOriginalDir, Len(sOriginalDir) - 1)
		[ ] 
	[ ] 
	[ ] string sCmd = "XCOPY {chr(34)}{sOriginalDir}{chr(34)} {chr(34)}{sDatatemp}{chr(34)} /E /Y"
	[ ] SYS_Execute(sCmd, lsOutput)
	[ ] 
	[ ] 
[ ] 
[+] void WaitCursorType(CURSOR curTypeExpected, real rTimeOut)
	[ ] 
	[ ] CURSOR curType
	[ ] 
	[ ] real rTime = 0
	[ ] real rStep = 1
	[+] while(rTime <= rTimeOut)
		[ ] curType = Cursor.GetType()
		[ ] 
		[+] if (curType == curTypeExpected)
			[ ] 
			[ ] return
			[ ] 
		[+] else
			[ ] sleep(rStep)
			[ ] rTime += rStep
			[ ] 
		[ ] 
		[ ] 
	[ ] 
	[ ] 
[ ] 
[+] void WaitCursorNotNotDelay(real rTimeOut)
	[ ] 
	[ ] CURSOR curType
	[ ] 
	[ ] real rTime = 0
	[ ] real rStep = 1
	[ ] 
	[ ] sleep(iMidDelay)
	[+] while(rTime <= rTimeOut)
		[ ] curType = Cursor.GetType()
		[ ] 
		[+] if (curType == "DELAY")
			[ ] 
			[ ] sleep(rStep)
			[ ] rTime += rStep
			[ ] 
		[+] else
			[ ] 
			[ ] break
			[ ] 
		[ ] 
		[ ] 
	[ ] sleep(iMidDelay)
	[ ] 
	[ ] 
[ ] 
[+] void CreateFolder(String sFolder, String sDir NULL optional)
	[+] //---------------------Log---------------------//
		[ ] // Info			:	A folder with the name of sFolder will be created under sDir.
		[ ] //					If sDir is NULL, the default path it the output folder.
		[ ] //					If a folder with the duplicate name exists already, the creation will be canceled.
		[ ] // Author		:	Eric Lu
		[ ] // Date			:	December 06, 2011	
	[ ] 
	[ ] String sOutputFolder
	[ ] 
	[+] if ( sDir != NULL )
		[ ] sOutputFolder = "{sDir}{sFolder}"
	[+] else
		[ ] sOutputFolder = "{sFolder}"
	[ ] 
	[+] do //*** Create a folder with the name of CQ number ***//
		[ ] SYS_MakeDir (sOutputFolder)
	[+] except
		[ ] SYS_Execute('mkdir "{sOutputFolder}"')
		[ ] // print("====================================================================")
		[ ] // print(" The folder ""{sFolder}"" is already existing")
		[ ] // print("====================================================================")
[ ] 
[+] void DeleteFolder(String sFolder, String sDir NULL optional)
	[ ] String sOutputFolder
	[ ] 
	[+] if ( sDir != NULL )
		[ ] sOutputFolder = "{sDir}{sFolder}"
	[+] else
		[ ] sOutputFolder = "{sFolder}"
	[+] do
		[ ] SYS_Execute('rmdir "{sOutputFolder}" /s /q')
	[+] except
		[ ] Log.Error("Remove folder {sOutputFolder} failed.")
[ ] 
[+] void glSelectItemInComboBox(window wParentWindow, string sAttribute, string sValue, string sItemName, int iIndex optional)
		[ ] //Description:
		[ ] //AP.SelectItemInComboBox("automationId","PART_editControl","11",3)
		[ ] // use to select combox item in A+ user interface.
		[ ] //sAttribute:  such as caption, automationid , classtype...
		[ ] //sValue : the actual value of caption, automationid , classtype...
		[ ] //sItemName: the  item to be selected.
		[ ] //index :the index for sValue; e.g.  "2"  in the @className='AesXamComboEdit'][2]"
		[ ] 
		[ ] window comboBox
		[+] if(iIndex == null)
			[ ] comboBox = wParentWindow.Find("//WPFControl[@{sAttribute}='{sValue}']")
			[ ] comboBox.Click()
			[ ] sleep(0.5)
			[+] do
				[ ] comboBox.SetProperty("MaxDropDownHeight",650)
				[ ] wParentWindow.Find("//WPFComboBoxItem[@caption='{sItemName}']").Click()
			[+] except
				[ ] wParentWindow.TypeKeys("{sItemName}<enter>",0.2)
		[+] else
			[ ] comboBox = wParentWindow.Find("//WPFControl[@{sAttribute}='{sValue}'][{iIndex}]")
			[ ] comboBox.Click()
			[ ] sleep(0.5)
			[+] do
				[ ] comboBox.SetProperty("MaxDropDownHeight",650)
				[ ] wParentWindow.Find("//WPFComboBoxItem[@caption='{sItemName}']").Click()
			[+] except
				[ ] wParentWindow.TypeKeys("{sItemName}<enter>",0.2)
				[ ] 
		[ ] 
[ ] 
[ ] //Use Adiff.exe compare tool to compare two text files. if files out of tolerance, an error message will print and followed with detailed diffs.
[+] boolean CompareFileByAdiff (string sLeftFile, string sRightFile, float fReltol optional, float fAbstol optional, string sIgnorePatternFile optional)
	[ ] //sLeftFile: the first file to compared, usually baseline file
	[ ] //sRightFile: the second file to compared, usually the actually result file
	[ ] //fReltol: the relative tolerance. default value is global const cfRelTol
	[ ] //fAbstol: the absolute tolerance. default value is global const cfAbsTol
	[ ] //sIgnorePatternFile: the ignore pattern file, please input adiff.exe --help in command line to see more details.
	[ ] 
	[ ] string sIgnorePatthenFileArg=""
	[+] if (fReltol == NULL)
		[ ] fReltol = cfRelTol
	[+] if (fAbstol == NULL)
		[ ] fAbstol = cfAbsTol
	[ ] sleep(5)
	[+] if (sIgnorePatternFile != NULL)
		[ ] sIgnorePatthenFileArg = '--ignore-patterns-file="{sIgnorePatternFile}"'
	[+] if (!SYS_FileExists (sLeftFile))
		[ ] LogError ("File: {sLeftFile} not Exists")
		[ ] return False
	[+] else
		[ ] Print ("Left file: {sLeftFile}")
	[+] if (!SYS_FileExists (sRightFile))
		[ ] LogError ("File: {sRightFile} not Exists")
		[ ] return False
	[+] else
		[ ] Print ("Right file: {sRightFile}")
	[ ] list of string lsCMDLine
	[ ] //Use Classic Agent to SYS_Execute some command, this is a walkaroud of Open Agent. Open Agent can't correct SYS_Execute
	[ ] //scripts created by Classic agent.
	[ ] disconnectall()
	[ ] connect(null, CLASSIC_AGENT)
	[ ] string sCmd = '"{csAdiffCmdLine}" --spiff -b -i -B --abstol={fAbstol} --reltol={fReltol} --ignore-aplus-history {sIgnorePatthenFileArg} "{sLeftFile}" "{sRightFile}"'
	[ ] print(sCmd)
	[ ] SYS_Execute ('"{csAdiffCmdLine}" --spiff -b -i -B --abstol={fAbstol} --reltol={fReltol} --ignore-aplus-history {sIgnorePatthenFileArg} "{sLeftFile}" "{sRightFile}"', lsCMDLine)
	[ ] 
	[+] if (lsCMDLine == {})
		[ ] return True
	[+] else
		[ ] LogError("xxx--Files out of tolerance, please manual check it!!!")
		[ ] print("============================diff begins===========================================")
		[ ] ListPrint (lsCMDLine)
		[ ] print("============================diff ends=============================================")
		[ ] return False
[ ] 
[+] void WaitForEnabled(window wWindow, int iTimeOut optional)			//Accepts a window name, and waits until said window is unabled (gl function not compatible with Open Agent)
	[ ] int iTime = 0
	[ ] boolean bEnabled = wWindow.GetProperty("Enabled")
	[+] if (iTimeOut  == NULL)
		[ ] iTimeOut  = 150
	[+] while(bEnabled==FALSE && (iTime <= iTimeOut))										//	Waits for the results to be calculated and for the AP main win to be enabled again
		[ ] sleep(0.2)
		[ ] bEnabled= wWindow.GetProperty("Enabled")
		[ ] iTime++
	[ ] sleep(1)															//
	[ ] 
[ ] 
[-] void ErrorHandler (string name optional)
	[ ] //Name is the name of the Error image, if not NULL
	[ ] CALL Call
	[ ] LIST OF CALL lCall
	[ ] // ExceptPrint () 
	[ ] lCall = ExceptCalls ()
	[ ] // string exceptData = ExceptData()
	[+] // if( exceptData != NULL )
		[ ] // Log.Warning(exceptData)
	[+] // for each Call in lCall
		[ ] // Log.Warning("Module: {Call.sModule}") 
		[ ] // Log.Warning( "Function: {Call.sFunction}" )
		[ ] // Log.Warning( "Line: {Call.iLine} ")
		[ ] // PRINT("*********")
	[ ] exceptLog()
	[ ] exceptClear()
	[ ] 
	[+] if( name != NULL )
		[+] do
			[ ] Agent.SetOption(OPT_BITMAP_MATCH_COUNT,0)
			[ ] Agent.SetOption(OPT_BITMAP_MATCH_TIMEOUT,0)
			[ ] Agent.SetOption(OPT_BITMAP_MATCH_INTERVAL,0)
			[+] if( APlus.Exists() )
				[ ] APlus.CaptureBitmap(name)
			[+] else if( APR.Exists() )
				[ ] APR.CaptureBitmap(name)
			[+] else
				[ ] 
		[+] except
			[ ] Log.Error("Unable to Capture Bitmap")
			[ ] 
		[ ] 
		[ ] 
	[ ] 
	[+] if( checkForProgramError())
		[ ] 
	[+] else
		[ ] Log.Error("THIS SCRIPT HAS EITHER FAILED BECAUSE THIS SCRIPT NEEDS MAINTENANCE OR THE AUTOMATION ENGINEER ISN'T VERY GOOD AT THEIR JOB")
	[ ] 
	[ ] KillPrograms() // Kill Everything that shouldn't be running
	[ ] 
[ ] 
[+] int copyDirectory( string inPath, string outPath, boolean copyInnerDir )
	[ ] //Copies contents of a directory to another directory, if that directory
	[ ] //Have not tested this yet
	[ ] 
	[ ] list of FILEINFO contents = SYS_GETDIRCONTENTS(inPath)
	[ ] FILEINFO content
	[ ] int totalFiles = 0
	[+] if( !SYS_DIREXISTS(outPath) )
		[ ] SYS_MAKEDIR( outPath)
	[+] for each content in contents
		[+] if( content.bIsDir  )
			[+] if(  copyInnerDir  )
				[ ] PRINT( "*******Sending {inPath}\{content.sName}  and {outPath}\{content.sName} *************")
				[ ] totalFiles += copyDirectory("{inPath}\{content.sName}", "{outPath}\{content.sName}", TRUE)
				[ ] 
			[+] else
				[ ] PRINT("*****{inPath}\{content.sName} was not copied because copy sub-Directories is off")
		[+] else
			[ ] PRINT(" COPYING FILE {inPath}\{content.sName}")
			[+] if( SYS_FILEEXISTS("{outPath}\{content.sName}") )
				[ ] Log.Warning("A File by the name of {chr(34)}{content.sName}{chr(34)} is already in {chr(34)}{outPath}{chr(34)}. Old File will be overwritten")
				[ ] SYS_REMOVEFILE("{outPath}\{content.sName}")
				[ ] SYS_COPYFILE( "{inPath}\{content.sName}", "{outPath}\{content.sName}")
			[+] else
				[ ] SYS_COPYFILE( "{inPath}\{content.sName}", "{outPath}\{content.sName}")
			[ ] totalFiles++
	[ ] PRINT("FINISHED COPYING { totalFiles} files from  {inPath}")
	[ ] return totalFiles
	[ ] 
	[ ] 
[ ] 
[+] void getFilePathsInDir(String  sDir, inout List of String paths)
	[ ] List of FILEINFO files = SYS_GETDIRCONTENTS( sDir )
	[ ] FILEINFO file
	[+] for each file in files
		[+] if( file.bIsDir)
			[ ] getFilePathsInDir("{sDir}\{file.sName}", paths)
		[+] else
			[ ] ListAppend( paths, "{sDir}\{file.sName}")
			[ ] 
[ ] 
[+] boolean checkTolerance( number base, number toCheck, real  tolerance)
	[+] if( base == 0 && toCheck == 0)
		[ ] PRINT( "Base: {base}  , Checking: {toCheck},   Error: 0%     Error Limit: {tolerance * 100.0}% ")
		[ ] return True
	[+] else if( base == 0 && toCheck != 0)
		[ ] PRINT( "Base: {base}  , Checking: {toCheck},   Error: inf     Error Limit: {tolerance * 100.0}% ")
		[ ] return false
	[+] else if(      abs( (base - toCheck)/(1.0*base)) > tolerance )
		[ ] PRINT( "Base: {base}  , Checking: {toCheck},   Error: {abs( (base - toCheck)/(1.0*base))*100.0}%     Error Limit: {tolerance * 100.0}% ")
		[ ] return False
	[+] else
		[ ] PRINT( "Base: {base}  , Checking: {toCheck},   Error: {abs( (base - toCheck)/(1.0*base))*100.0}%     Error Limit: {tolerance * 100.0}% ")
		[ ] return true
		[ ] 
[ ] 
[+] void makeDir( string path) 
	[ ] // print(getField( path, "\", 3))
	[+] if( getField( path, "\", 3) == "")
		[+] if(!SYS_DirExists(path) )
			[ ] SYS_MakeDIR(path)
	[+] else
		[ ] // PRINT(   strpos( "\", path, TRUE)-1)
		[ ] makeDir( substr(path,1,(strpos( "\", path, TRUE)-1)))
		[+] if(!SYS_DirExists(path) )
			[ ] SYS_MakeDIR(path)
[ ] 
[-]  void killPrograms()
	[ ] SYS_Execute("taskkill /f /t /im aspenplus.exe")
	[ ] SYS_Execute("taskkill /f /t /im aspenhysys.exe")
	[ ] SYS_Execute("taskkill /f /t /im aspenproperties.exe")
	[ ] SYS_EXECUTE("taskkill /im AspenTech.Visualisation.Assistant.Run.exe /f")
	[ ] SYS_EXECUTE("taskkill /im mmc.exe /f")
	[ ] SYS_EXECUTE("taskkill /im cmd.exe /f")     
	[ ] SYS_EXECUTE("taskkill /im hh.exe /f")     
	[ ] SYS_EXECUTE("taskkill /im IcarusAdapterExe.exe /f")     
	[ ] SYS_EXECUTE("taskkill /im concepts.exe /f")     
	[ ] SYS_EXECUTE("taskkill /im rundll32.exe    /f")     
	[ ] SYS_EXECUTE("taskkill /im setaped.exe    /f")     
	[ ] SYS_EXECUTE("taskkill /im WerFault.exe    /f")   
	[ ] SYS_EXECUTE("taskkill /im aspenSplash.exe    /f")   
	[ ] SYS_EXECUTE("taskkill /im dbTesterAdv.exe    /f")  
	[ ] 
[+] boolean checkForProgramError()
	[+] if( wRuntimeError.Exists() )
		[ ] Log.Error(" THIS SCRIPT HAS FAILED DUE TO A MICROSOFT VISUAL C++ RUNTIME ERROR")
		[ ] PRINT ("THIS ERROR READS"{wRuntimeError.txtWarning.GetText()} ")
	[+] else if( wAspenPlusError.Exists() )
		[ ] Log.Error(" ERROR: Generic Aspen Properties Error")
	[+] else if( wAspenPropertiesError.Exists() )
		[ ] Log.Error(" ERROR: Generic Aspen Properties Error")
	[+] else if( wAspenPlusErrorMainWin.Exists() )
		[ ] Log.Error(" ERROR: Generic Aspen Plus Error")
	[+] else if( wAspenPropertiesErrorMainWin.Exists() )
		[ ] Log.Error(" ERROR: Generic Aspen Properties Error")
	[+] else if( wAspenPlusHasStoppedWorking.Exists() )
		[ ] Log.Error("ERROR: Aspen Plus Has Stopped Working")
	[+] else if( wAspenPropertiesHasStoppedWorking.Exists() )
		[ ] Log.Error("ERROR: Aspen Properties Has Stopped Working")
		[ ] 
	[+] else
		[ ] return FALSE
	[ ] 
	[ ] programErrorCount++
	[ ] killPrograms()
	[ ] return TRUE
[ ] 
[+] boolean checkText( string base, string toCheck)
	[+] if( base == toCheck)
		[ ] Log.Pass("Found: {base}")
		[ ] return TRUE
	[+] else
		[ ] Log.Error("Expected: {base}           Found: {toCheck}")
		[ ] return FALSE
[ ] 
[+] timer( int timeOut)
	[ ] handle timer = timerCreate()
	[+] timerStart(timer)                           
		[+] while( timerValue(timer) < timeOut)
			[ ] Print("Time is {timerValue(timer)}")
			[ ] sleep(1)
		[ ] timerDestroy(timer)
		[ ] critical
		[ ] Log.ERROR("ERROR: Timeout Had Been Reached")
		[ ] exit
[+] void CollapseAll(window wTreeView optional)
	[ ] window w,w1
	[ ]  boolean bEnd
	[+] if !wTreeView.Exists()
			[ ] Log.Fail("Unable to find the target {wTreeView} REF:=Functions.inc=CollapseAll")
	[+] else
			[ ]  list of window lw=wTreeView.GetChildren()
			[+] if ListCount(lw)!=0
				[+] for each w1 in lw
					[+] if w1.GetClass()==WPFTreeViewItem
						[ ] w1.BringIntoView()
						[ ] //CollapseAll(w1)
						[ ] w1.Collapse()
						[ ] 
	[ ] 
[+] list of STRING tableReturnRange(string sRange,string sGroupBox_orNone optional,string sExtraCommand optional,window wTarget optional,list of string lsExistedTable optional)
	[ ] //Created by www 
	[ ] //This function try to make it easier to select a range of value within a data grid
	[ ] //This function works like excel A-Z stands for column and 1-n stands for rows
	[ ] //Sample format tableReturnRange("A1,A2,A1:B2",none,APlus)
	[ ] //Sample format tableReturnRange("sum(A1:A2),sum(b1:b2)","none") return the sum 
	[ ] //The format of return will be
	[ ] //A1
	[ ] //A2
	[ ] //A1 A2
	[ ] //B1 B2
	[ ] //All
	[ ] //sExtraCommand is sepearated by ,
	[ ] //"Delete Ending Blank Lines"=DEBL
	[ ] //ERR5: =Function.inc=tableReturnRange= REF:
	[ ] 
	[ ] //Definition
	[ ] int iComma=1 //it is number of segment in the command sepearated by ,
	[ ] list of STRING lsCommaSeg,lsCommaSegEx
	[ ] string sCommaSeg,s,s1
	[ ] window wWin,wItem
	[ ] list of WINDOW lwItem
	[ ] list of STRING lsTable
	[ ] real rTable
	[ ] string sTable,sTemp
	[ ] boolean bTable=false
	[ ] boolean bDEBL=false
	[ ] list of STRING lsResult,lsResult1
	[ ] ListAppend(lsResult,"Error: fail to find the cell")
	[ ] int i,iCell,iRow,iColumn,j,iRowe,iColumne,iRowt,iColumnt,iTable
	[ ] list of INT liCell
	[ ] boolean bSum
	[ ] //Log.Fail("ERR6: =Functions.inc=tableReturnRange= REF:
	[+] //Extra Command-Delete Ending Blank Line #1?
		[+] if sExtraCommand!=null
			[+] if MatchStr("*DEBL*",sExtraCommand)||MatchStr("*debl*",sExtraCommand)
				[ ] sExtraCommand=StrTran(sExtraCommand,",DEBL,",",")
				[ ] sExtraCommand=StrTran(sExtraCommand,",DEBL","")
				[ ] sExtraCommand=StrTran(sExtraCommand,"DEBL,","")
				[ ] sExtraCommand=StrTran(sExtraCommand,"DEBL","")
				[ ] bDEBL=true
	[ ] 
	[ ] 
	[+] //Analyze sRange
		[+] while true
			[ ] sCommaSeg=GetField(sRange,",",iComma)
			[+] if sCommaSeg==""
				[ ] iComma--     
				[ ] break
			[ ] ListAppend(lsCommaSeg,sCommaSeg)
			[ ] iComma++
	[ ] 
	[+] //Use existed table or obtain from the program
		[+] if lsExistedTable==null
			[ ] //Get Value within Table
			[+] //Locate groupbox
				[+] if wTarget==null
					[ ] wTarget=APlus
				[+] if sGroupBox_orNone!=null
					[+] if (sGroupBox_orNone=="none")||(sGroupBox_orNone=="None")||(sGroupBox_orNone=="NONE")
						[+] if FindWPFContentControl("//WPFContentControl[@automationId='MMTabPage_1']").Exists()
							[ ] wWin=FindWPFContentControl("//WPFContentControl[@automationId='MMTabPage_1']")
					[+] else if wTarget.FindWPFGroupBox("WPFGroupBox[@caption='*{sGroupBox_orNone}*']").Exists()
						[ ] wWin=wTarget.FindWPFGroupBox("WPFGroupBox[@caption='*{sGroupBox_orNone}*']")
					[+] else if wTarget.FindWPFGroupBox("//WPFGroupBox[@automationId='Template_GroupBox']").Exists()
						[ ] wWin=wTarget.FindWPFGroupBox("//WPFGroupBox[@automationId='Template_GroupBox']")
					[+] else
						[ ] Log.Error("ERR1: =Functions.inc=tableReturnRange= REF: Unable to locate Groupbox. Try to go without GroupBox")
						[ ] sGroupBox_orNone=null
				[+] if (sGroupBox_orNone==null)
					[+] if FindWPFContentControl("//WPFContentControl[@automationId='MMTabPage_1']").Exists()
						[ ] wWin=FindWPFContentControl("//WPFContentControl[@automationId='MMTabPage_1']")
					[+] else if wTarget.FindWPFTabControl("//WPFTabControl[@className='TabGroupPane']").Exists()
						[ ] wWin=wTarget.FindWPFTabControl("//WPFTabControl[@className='TabGroupPane']")
					[+] else
						[ ] Log.Fail("ERR3: =Functions.inc=tableReturnRange= REF: Failed to find table")
			[+] //Clean Clipboard
				[+] while true
					[+] do
						[ ] Clipboard.SetText(null)
						[ ] break
						[ ] Print("ERR4: =Functions.inc=tableReturnRange= REF: fail to clean Clipboard")
					[ ] except
					[ ] 
			[+] //Copy the table
				[+] if wWin.FindWPFButton("//WPFButton[@automationId='SelectAll']").Exists()
					[ ] wWin=wWin.Find("//WPFButton[@automationId='SelectAll']")
				[+] else if wWin.FindWPFContentControl("WPFContentControl[@caption='Selet All']").Exists()
					[ ] wWin=wWin.FindWPFContentControl("WPFContentControl[@caption='Selet All']")
				[+] else
					[ ] Log.Fail("ERR5: =Functions.inc=tableReturnRange= REF:Failed to find select all button in the table")
					[ ] return lsResult
				[ ] wWin.BringIntoView()
				[+] for(i=0;i<=15;i++)
					[ ] wWin.Click()
					[ ] sleep(0.8)
					[ ] wWin.Click(MB_RIGHT)
					[ ] sleep(0.3)
					[+] if FindWPFMenuItem("//WPFMenuItem[@caption='_copy']").Exists(5)
						[+] if FindWPFMenuItem("//WPFMenuItem[@caption='_copy']").GetProperty("IsEnabled")
							[ ] sleep(0.5)
							[+] do
								[ ] FindWPFMenuItem("//WPFMenuItem[@caption='_copy']").Select()
							[+] except
								[ ] continue
						[+] else
							[ ] FindWPFMenuItem("//WPFMenuItem[@caption='_copy']").TypeKeys("<ESC>")
							[ ] continue
					[+] else if FindWPFMenuItem("//WPFContextMenu//WPFMenuItem[@caption='Copy']").Exists()
						[+] if FindWPFMenuItem("//WPFContextMenu//WPFMenuItem[@caption='Copy']").GetProperty("IsEnabled")
							[+] do
								[ ] FindWPFMenuItem("//WPFContextMenu//WPFMenuItem[@caption='Copy']").Select()
							[+] except
								[ ] continue
						[+] else
							[ ] FindWPFMenuItem("//WPFContextMenu//WPFMenuItem[@caption='Copy']").TypeKeys("<ESC>")
							[ ] continue
					[+] if FindDialogBox("//DialogBox[@caption='*error*']").Exists()
						[ ] FindDialogBox("//DialogBox[@caption='*error*']").Close()
						[ ] continue
					[+] if FindDialogBox("//DialogBox[@caption='*Error*']").Exists()
						[ ] FindDialogBox("//DialogBox[@caption='*Error*']").Close()
						[ ] continue
					[+] if FindDialogBox("//DialogBox[@caption='*ERROR*']").Exists()
						[ ] FindDialogBox("//DialogBox[@caption='*ERROR*']").Close()
						[ ] continue
					[ ] bTable=false
					[+] for each sTable in Clipboard.GetText()
						[+] if sTable!=""
							[ ] bTable=true
							[ ] break
					[+] if bTable==true
						[ ] sleep(1)
						[ ] break
					[+] else
						[ ] continue
				[+] if i>=15
					[ ] Log.Fail("ERR5: =Functions.inc=tableReturnRange= REF:Fail to copy table into clipboard after 15 trials")
					[ ] return lsResult
				[ ] sTable=""
				[ ] lsTable=Clipboard.GetText()
		[+] else
			[ ] lsTable=lsExistedTable
		[ ] 
	[+] //Transform the list of string table into into array
		[ ] iColumn=1
		[ ] iRow=ListCount(lsTable)
		[+] for each sTable in lsTable
			[ ] i=1
			[ ] s=sTable
			[ ] iTable=1
			[+] // while GetField(sTable,"{chr(9)}",i)!=""
				[ ] // i++
			[ ] // i--
			[+] while iTable!=0
				[ ] iTable=StrPos("	",s)
				[ ] s=SubStr(s,iTable+1)
				[ ] i++
			[+] if i>iColumn
				[ ] iColumn=i
		[ ] iRowt=iRow
		[ ] iColumnt=iColumn
		[ ] array[iRow][iColumn] of string arTable
		[+] for (i=1;i<=iRow;i++)
			[+] for (j=1;j<=iColumn;j++)
				[ ] arTable[i][j]=GetField(lsTable[i],"{chr(9)}",j)
		[ ] 
	[+] //Extra Command
		[ ] //1.Change table value
		[ ] //2.Search cell with desired value
		[ ] 
		[+] if sExtraCommand!=null&&sExtraCommand!=""
			[ ] iComma=1
			[ ] //Chop Extra command into small pieces
			[+] while true
				[ ] sCommaSeg=GetField(sExtraCommand,",",iComma)
				[+] if sCommaSeg==""
					[ ] iComma--     
					[ ] break
				[ ] ListAppend(lsCommaSegEx,sCommaSeg)
				[ ] iComma++
			[ ] //Make change into the table
			[ ] //Convert Extra Command into cell# or range#
			[+] for each sCommaSeg in lsCommaSegEx
				[ ] iRow=0
				[ ] iColumn=0
				[ ] iRowe=0
				[ ] iColumne=0
				[ ] s=GetField(sCommaSeg,"=",2)
				[+] if !MatchStr("*:*",sCommaSeg)
					[+] if (sCommaSeg=="all")||(sCommaSeg=="All")||(sCommaSeg=="ALL")
						[ ] sCommaSeg="A1:{Chr(iColumnt+64)}{iRowt}"
					[+] else
						[ ] //Single Cell
						[+] while IsAlpha(sCommaSeg)
							[ ] i=Asc(SubStr(lower(sCommaSeg),1,1))-96
							[ ] iColumn=iColumn*10+i
							[ ] sCommaSeg=Stuff(sCommaSeg,1,1,"")
						[+] while IsDigit(sCommaSeg)
							[ ] i=val(SubStr(sCommaSeg,1,1))
							[ ] iRow=iRow*10+i
							[ ] sCommaSeg=Stuff(sCommaSeg,1,1,"")
						[ ] arTable[iRow][iColumn]=s
				[ ] //Cell Group
				[+] if MatchStr("*:*",sCommaSeg)
					[ ] //Within a range
					[ ] 
					[ ] //interpret first part before :
					[ ] sTable=GetField(sCommaSeg,":",1)
					[+] while IsAlpha(sTable)
						[ ] i=Asc(SubStr(lower(sTable),1,1))-96
						[ ] iColumn=iColumn*10+i
						[ ] sTable=Stuff(sTable,1,1,"")
					[+] while IsDigit(sTable)
						[ ] i=val(SubStr(sTable,1,1))
						[ ] iRow=iRow*10+i
						[ ] sTable=Stuff(sTable,1,1,"")
					[ ] sTable=GetField(sCommaSeg,":",2)
					[ ] //interpret 2nd part after :
					[+] while IsAlpha(sTable)
						[ ] i=Asc(SubStr(lower(sTable),1,1))-96
						[ ] iColumne=iColumne*10+i
						[ ] sTable=Stuff(sTable,1,1,"")
					[+] while IsDigit(sTable)
						[ ] i=val(SubStr(sTable,1,1))
						[ ] iRowe=iRowe*10+i
						[ ] sTable=Stuff(sTable,1,1,"")
					[+] if iRowe>iRowt
						[ ] iRowe=iRowt
						[ ] print("WARNING:Specified number of rows is beyond the range, return the value to the maximum range")
					[+] if iColumne>iColumnt
						[ ] iColumne=iColumnt
						[ ] print("WARNING:Specified number of rows is beyond the range, return the value to the maximum range")
					[ ] print("Start of row {iRow}, Start of Column {iColumn},End of row {iRowe}, End of column {iColumne}, s value is {s}")
					[+] for (i=iRow;i<=iRowe;i++)
						[+] for (j=iColumn;j<=iColumne;j++)
							[ ] arTable[i][j]=s
							[ ] 
	[+] //output generation
		[+] for each sCommaSeg in lsCommaSeg
			[ ] iRow=0
			[ ] iColumn=0
			[ ] iRowe=0
			[ ] iColumne=0
			[+] if MatchStr("*Find(*)*",sCommaSeg)||MatchStr("*find(*)*",sCommaSeg)||MatchStr("*FIND(*)*",sCommaSeg)
				[ ] //Find Function
				[ ] //sTemp in this situation is the text we are looking for
				[ ] sTemp=sCommaSeg
				[ ] sTemp=strtran(sTemp,"Find(","")
				[ ] sTemp=strtran(sTemp,"find(","")
				[ ] sTemp=strtran(sTemp,"FIND(","")
				[ ] sTemp=strtran(sTemp,")","")
				[+] for (iRow=1;iRow<=iRowt;iRow++)
					[+] for (iColumn=1;iColumn<=iColumnt;iColumn++)
						[+] if arTable[iRow][iColumn]==sTemp
							[ ] ListAppend(lsResult1,"{chr(64+iColumn)}{iRow}")
			[+] else 
				[ ] sCommaSeg=Upper(sCommaSeg)
				[+] if MatchStr("*SUM*",sCommaSeg)
					[ ] //Sum function
					[ ] sCommaSeg=StrTran(sCommaSeg,"SUM(","")
					[ ] sCommaSeg=StrTran(sCommaSeg,")","")
					[ ] AnalyzeRange(sCommaSeg,iRow,iColumn,iRowe,iColumne,iRowt,iColumnt)
					[ ] rTable=0
					[+] for (i=iRow;i<=iRowe;i++)
						[+] for (j=iColumn;j<=iColumne;j++)
							[ ] rTable=val(arTable[i][j])+rTable
					[ ] ListAppend(lsResult1,str(rTable))
				[+] else
					[+] if !MatchStr("*:*",sCommaSeg)
						[ ] //print(sCommaSeg)
						[+] if (sCommaSeg=="all")||(sCommaSeg=="All")||(sCommaSeg=="ALL")
							[ ] sCommaSeg="A1:{Chr(iColumnt+64)}{iRowt}"
						[+] else
							[ ] //Single Cell
							[+] while IsAlpha(sCommaSeg)
								[ ] 
								[ ] i=Asc(SubStr(sCommaSeg,1,1))-64
								[ ] iColumn=iColumn*10+i
								[ ] sCommaSeg=Stuff(sCommaSeg,1,1,"")
							[+] while IsDigit(sCommaSeg)
								[ ] i=val(SubStr(sCommaSeg,1,1))
								[ ] iRow=iRow*10+i
								[ ] sCommaSeg=Stuff(sCommaSeg,1,1,"")
							[ ] ListAppend(lsResult1,arTable[iRow][iColumn])
					[+] if MatchStr("*:*",sCommaSeg)
						[ ] //Within a range
						[ ] //interpret first part before :
						[ ] sTable=GetField(sCommaSeg,":",1)
						[+] while IsAlpha(sTable)
							[ ] i=Asc(SubStr(sTable,1,1))-64
							[ ] iColumn=iColumn*10+i
							[ ] sTable=Stuff(sTable,1,1,"")
						[+] while IsDigit(sTable)
							[ ] i=val(SubStr(sTable,1,1))
							[ ] iRow=iRow*10+i
							[ ] sTable=Stuff(sTable,1,1,"")
						[ ] sTable=GetField(sCommaSeg,":",2)
						[ ] //interpret 2nd part after :
						[+] while IsAlpha(sTable)
							[ ] i=Asc(SubStr(sTable,1,1))-64
							[ ] iColumne=iColumne*10+i
							[ ] sTable=Stuff(sTable,1,1,"")
						[+] while IsDigit(sTable)
							[ ] i=val(SubStr(sTable,1,1))
							[ ] iRowe=iRowe*10+i
							[ ] sTable=Stuff(sTable,1,1,"")
						[+] if iRowe>iRowt
							[ ] iRowe=iRowt
							[ ] print("WARNING:Specified number of rows is beyond the range, return the value to the maximum range")
						[+] if iColumne>iColumnt
							[ ] print("WARNING:Specified number of rows {iColumne} is beyond the total range {iColumnt}, return the value to the maximum range")
							[ ] iColumne=iColumnt
						[+] for (i=iRow;i<=iRowe;i++)
							[ ] sTable=""
							[+] for (j=iColumn;j<=iColumne;j++)
								[ ] //print("i={i} j={j} {arTable[i][j]}")
								[ ] sTable=sTable+"{chr(9)}"+arTable[i][j]
							[ ] sTable=Stuff(sTable,1,1,"")
							[ ] ListAppend(lsResult1,sTable)
						[ ] 
	[+] //Extra Command-Delete Ending Blank Line #1
		[ ] iTable=0
		[+] while iTable<=100
			[ ] iTable++
			[ ] i=Listcount(lsResult1)
			[ ] sTable=lsResult1[i]
			[ ] sTable=strtran(sTable,"	","")
			[ ] sTable=strtran(sTable,"{chr(9)}","")
			[+] if (sTable=="")
				[ ] ListDelete(lsResult1,i)
			[+] else
				[ ] break
			[ ] 
	[ ] return lsResult1
[+] void AnalyzeRange(string sCommaSeg,inout int iRow,inout int iColumn,inout int iRowe,inout int iColumne,int iRowt optional,int iColumnt optional)
	[ ] int i
	[ ] string sTable
	[ ] iRow=0
	[ ] iColumn=0
	[ ] iRowe=0
	[ ] iColumne=0
	[ ] sCommaSeg=Upper(sCommaSeg)
	[+] if !MatchStr("*:*",sCommaSeg)
		[+] if (sCommaSeg=="all")||(sCommaSeg=="All")||(sCommaSeg=="ALL")
			[ ] sCommaSeg="A1:{Chr(iColumnt+64)}{iRowt}"
		[+] else
			[ ] //Single Cell
			[+] while IsAlpha(sCommaSeg)
				[ ] 
				[ ] i=Asc(SubStr(sCommaSeg,1,1))-64
				[ ] iColumn=iColumn*10+i
				[ ] sCommaSeg=Stuff(sCommaSeg,1,1,"")
			[+] while IsDigit(sCommaSeg)
				[ ] i=val(SubStr(sCommaSeg,1,1))
				[ ] iRow=iRow*10+i
				[ ] sCommaSeg=Stuff(sCommaSeg,1,1,"")
			[ ] iRowe=iRow
			[ ] iColumne=iColumn
	[+] if MatchStr("*:*",sCommaSeg)
		[ ] //Within a range
		[ ] //interpret first part before :
		[ ] sTable=GetField(sCommaSeg,":",1)
		[+] while IsAlpha(sTable)
			[ ] i=Asc(SubStr(sTable,1,1))-64
			[ ] iColumn=iColumn*10+i
			[ ] sTable=Stuff(sTable,1,1,"")
		[+] while IsDigit(sTable)
			[ ] i=val(SubStr(sTable,1,1))
			[ ] iRow=iRow*10+i
			[ ] sTable=Stuff(sTable,1,1,"")
		[ ] sTable=GetField(sCommaSeg,":",2)
		[ ] //interpret 2nd part after :
		[+] while IsAlpha(sTable)
			[ ] i=Asc(SubStr(sTable,1,1))-64
			[ ] iColumne=iColumne*10+i
			[ ] sTable=Stuff(sTable,1,1,"")
		[+] while IsDigit(sTable)
			[ ] i=val(SubStr(sTable,1,1))
			[ ] iRowe=iRowe*10+i
			[ ] sTable=Stuff(sTable,1,1,"")
[+] void cleanList(inout list of ANYTYPE laListToClean)
	[+] while ListCount(laListToClean)!=0
		[ ] ListDelete(laListToClean,1)
[+] void SearchTree(string sTarget,window trvItemOrigin optional,inout int iMode optional)
	[ ] //Are you able to find the treeviewitem specified in the procedure?
	[ ] //QE people never update the procedure. As a result, I really have a hard time finding them
	[ ] //After spending days and night in searching, I give up and write this function
	[ ] //Sample Format
	[ ] //SearchTree(FindWPFTreeViewItem("Pumparounds","//WPFTreeViewItem[@caption='B1']"))
	[ ] //You can leave iMode blank in the most of case.
	[ ] //iMode--find the nth result,default, find 1st one
	[ ] int i
	[ ] window w1,w
	[ ] list of STRING lsLocation
	[ ] string sLocation
	[+] if trvItemOrigin==null
		[ ] trvItemOrigin=APlus.trvPartTree
	[ ] list of WINDOW lw=trvItemOrigin.GetChildren()
	[+] if iMode==null
		[ ] iMode=1
	[+] if listcount(lw)!=0
		[+] for each w1 in lw
			[+] if w1.GetClass()==WPFTreeViewItem
				[+] if MatchStr("*{sTarget}*",w1.TextCapture())
					[ ] w1.Select()
					[ ] w=w1.GetParent()
					[ ] cleanList(lsLocation)
					[ ] sLocation=""
					[+] while w.GetClass()==WPFTreeViewItem
						[ ] ListAppend(lsLocation,w.GetCaption())
						[ ] w=w.GetParent()
					[+] for (i=ListCount(lsLocation);i>=1;i--)
						[ ] sLocation=sLocation+lsLocation[i]+"/"
					[ ] print("Location: {sLocation}")
					[ ] iMode--
					[+] if iMode==0
						[ ] iMode=256
					[ ] return
				[+] else
					[ ] w1.Expand()
					[ ] SearchTree(sTarget,w1,iMode)
					[+] if iMode==256
						[ ] return
					[+] else
						[ ] w1.Collapse()
			[+] else
				[ ] continue
[+] void SearchAll(string sTarget,window trvItemOrigin optional,inout int iMode optional)
	[ ] //Are you able to find the treeviewitem specified in the procedure?
	[ ] //QE people never update the procedure. As a result, I really have a hard time finding them
	[ ] //After spending days and night in searching, I give up and write this function
	[ ] //Sample Format
	[ ] //SearchTree(FindWPFTreeViewItem("Pumparounds","//WPFTreeViewItem[@caption='B1']"))
	[ ] //You can leave iMode blank in the most of case.
	[ ] //iMode--find the nth result,default, find 1st one
	[ ] int i
	[ ] window w1,w
	[ ] list of STRING lsLocation
	[ ] string sLocation,sScreen
	[+] if trvItemOrigin==null
		[ ] trvItemOrigin=APlus.trvPartTree
	[ ] list of WINDOW lw=trvItemOrigin.GetChildren()
	[+] if iMode==null
		[ ] iMode=1
	[+] if listcount(lw)!=0
		[+] for each w1 in lw
			[+] if w1.GetClass()==WPFTreeViewItem
				[ ] sScreen=""
				[+] while sScreen==""
					[ ] sScreen=APlus.TextCapture()
				[+] if MatchStr("*{sTarget}*",sScreen)
					[ ] w1.Select()
					[ ] w=w1.GetParent()
					[ ] cleanList(lsLocation)
					[ ] sLocation=""
					[ ] ListAppend(lsLocation,w1.GetCaption())
					[+] while w.GetClass()==WPFTreeViewItem
						[ ] ListAppend(lsLocation,w.GetCaption())
						[ ] w=w.GetParent()
					[+] for (i=ListCount(lsLocation);i>=1;i--)
						[ ] sLocation=sLocation+lsLocation[i]+"/"
					[ ] print("Location: {sLocation}")
					[ ] iMode--
					[+] if iMode==0
						[ ] iMode=256
				[+] else
					[ ] w1.Expand()
					[ ] w1.Select()
					[ ] SearchAll(sTarget,w1,iMode)
				[+] if iMode==256
					[ ] return
				[+] else
					[ ] w1.Collapse()
			[+] else
				[ ] continue
			[+] if iMode==256
				[ ] return
			[ ] 
[+] boolean wVal(string sInput,inout real rValue)
	[ ] //This function is an advanced version of val. It can analyze whether a string is number and understand "e"format
	[ ] //Don't enter any input bPower if you don't know what it does
	[ ] string sBase,sPower,sTemp
	[ ] real rBase,rPower
	[ ] int i,iBig,iSmall,iDot,ie
	[ ] boolean bExit=false
	[ ] sInput=lower(sInput)
	[+] //Analyze whether it is a number
		[ ] sTemp=sInput
		[ ] iDot=0
		[ ] ie=0
		[+] for (i=1;i<=Len(sInput);i++)
			[+] if !IsDigit(sTemp)
				[+] switch (sTemp[1])
					[+] case "."
						[ ] iDot++
					[+] case "e"
						[ ] ie++
					[+] default
						[ ] bExit=true
				[ ] //more than one e
				[+] if ie>1
					[ ] bExit=true
				[ ] //more than 2 dots
				[+] if iDot>2
					[ ] bExit=true
				[ ] //when there is no e ,two .
				[+] if ie!=1&&iDot>1
					[ ] bExit=true
				[ ] //when there is one e, more than 2 .
				[+] if ie==1&&iDot>2
					[ ] bExit=true
					[ ] 
				[+] if bExit==true
					[ ] rValue=0
					[ ] return false
			[ ] sTemp=Stuff(sTemp,1,1,"")
		[+] if bExit==true
			[ ] return false
	[+] //Get the base of a number
		[ ] sBase=GetField(sInput,"e",1)
	[+] //Get the power of a number
		[ ] sPower=GetField(sInput,"e",2)
		[+] if sPower==""
			[ ] sPower="0"
	[ ] //Number Analysis
	[ ] rBase=val(sBase)
	[ ] rPower=val(sPower)
	[ ] rValue=rBase*(10**rPower)
	[ ] return true
[+] list of string stringToTable(string sTable,boolean bTrimSpace optional)
	[ ] int i=1
	[ ] int iLocation,iLen,iEnd,iTable
	[ ] string s=GetField(sTable,"{chr(10)}",i)
	[ ] list of string ls
	[ ] iTable=len(sTable)
	[+] while iTable!=0
		[ ] s=GetField(sTable,"{chr(10)}",1)
		[+] if bTrimSpace!=null
			[ ] s=Ltrim(s)
			[ ] s=Rtrim(s)
		[ ] ListAppend(ls,s)
		[ ] iLocation=StrPos("{s}",sTable)
		[ ] iEnd=StrPos("{chr(10)}",sTable)
		[+] if iEnd==0
			[ ] iEnd=iTable
		[ ] sTable=Stuff(sTable,iLocation,iEnd,"")
		[ ] iTable=len(sTable)
	[ ] return ls
[+] list of string PerformanceMonitor(string sCounter,string sProcess,int iSamples optional)
	[ ] list of STRING lsTable,lsOutput
	[ ] string sTable,sTemp,sCommand
	[+] if iSamples==null
		[ ] iSamples=1
	[+] switch(sCounter)
		[+] case "CPU"
			[ ] sCommand="typeperf {chr(34)}\Process({sProcess})\% Processor Time{chr(34)} -sc {iSamples}"
		[+] case "Memory"
			[ ] sCommand="typeperf {chr(34)}\Process({sProcess})\Working Set{chr(34)} -sc {iSamples}"
		[+] case "Allocated Memory"
			[ ] sCommand="typeperf {chr(34)}\Process({sProcess})\Private Bytes{chr(34)} -sc {iSamples}"
		[+] case "Managed Memory"
			[ ] sCommand="typeperf {chr(34)}\.Net CLR Memory({sProcess})\# Bytes in all Heaps{chr(34)} -sc {iSamples}"
		[+] case "User Time"
			[ ] sCommand="typeperf {chr(34)}\Processor\% User Time{chr(34)} -sc {iSamples}"
		[+] default
			[ ] sCommand="dir"
	[ ] SYS_Execute(sCommand,lsTable)
	[ ] print(sCommand)
	[+] for each sTable in lsTable
		[ ] // print(sTable)
		[+] if MatchStr("*/*:*:*",sTable)
			[ ] sTemp=GetField(sTable,"{chr(34)}",4)
			[ ] ListAppend(lsOutput,sTemp)
		[+] else
			[ ] continue
	[ ] return lsOutput
	[ ] 
[+] Launch(string sFile)
	[ ] //Created by Weiwei Wu
	[ ] //In the performance test, we need to launch a file directly. SYS_execute cannot recognize .bkp file. Therefore, we implement this method to launch the file.
	[ ] //restriction:
	[ ] //Run silktest as administrator
	[ ] //Set executionpolicy for powershell unrestricted
	[ ] HFILE hfile
	[ ] SYS_Execute("powershell.exe set-executionpolicy unrestricted")
	[+] if sDataout[len(sDataout)]!="\"
		[ ] sDataout=sDataout+"\"
	[ ] string sLocation="{sDataout}launch.ps1"
	[+] if SYS_FileExists("{sLocation}")
		[ ] Sys_RemoveFile("{sLocation}")
	[ ] hfile=FileOpen(sLocation,FM_APPEND)
	[ ] FileWriteLine(hfile,"Start-Process -FilePath {chr(34)}{sFile}{chr(34)}")
	[ ] FileClose(hfile)
	[ ] sLocation="powershell.exe -File {chr(34)}{sLocation}{chr(34)}"
	[ ] SYS_Execute(sLocation,null,EM_CONTINUE_RUNNING)
	[ ] print(sLocation)
[ ] 
[ ] 
[ ] //==============Appended By Susan Shi===========
[+] list of string SplitStringToList(string sStringToSplit, string separator optional)
	[+] if(separator==null)
		[ ] separator="."
	[ ] integer i=StrPos(separator,sStringToSplit)
	[ ] list of string y
	[ ] //ListAppend(y,SubStr(x,1,(StrPos(".",x)-1)))
	[+] while(i!=0)
		[+] if(SubStr(sStringToSplit,1,(i-1))=="")
			[ ] sStringToSplit=SubStr(sStringToSplit,(i+1))
			[ ] i=StrPos(separator,sStringToSplit)
			[ ] continue
		[+] else
			[ ] ListAppend(y,SubStr(sStringToSplit,1,(i-1)))
		[ ] sStringToSplit=SubStr(sStringToSplit,(i+1))
		[ ] i=StrPos(separator,sStringToSplit)
	[ ] ListAppend(y,sStringToSplit)
	[ ] return y
[+] list of string ReverseList(list of string lsNeedReverse)
	[ ] list of string lsReversed
	[ ] integer inum=ListCount(lsNeedReverse)
	[ ] integer i
	[+] for(i=inum;i>=1;i--)
		[ ] ListAppend(lsReversed,lsNeedReverse[i])
	[ ] return lsReversed
[+] list of string GetHeaders(window wTable, int iFirstCol optional)
	[ ] list of window lwHeaders
	[ ] list of string lsHeaders
	[ ] integer i
	[+] if(iFirstCol==null)
		[ ] iFirstCol=1
	[ ] lwHeaders=wTable.FindAll("//WPFDataGridColumnHeader")
	[+] for(i=iFirstCol;i<=ListCount(lwHeaders);i++)
		[ ] ListAppend(lsHeaders,lwHeaders[i].sCaption)
	[ ] return lsHeaders
[+] list of string GetAllDataInOneColumn(window wTable, integer icol)
	[ ] list of string lsAllModels
	[ ] integer i, inum
	[ ] inum=ListCount(wTable.FindAll("//WPFDataGridRow"))
	[+] for(i=1;i<=inum;i++)
		[ ] ListAppend(lsAllModels,wTable.Find("//WPFDataGridRow[{i}]").Find("//WPFDataGridCell[{icol}]").sCaption)
	[ ] return lsAllModels
[-] string GetFieldContent(integer iFieldOrder, window w optional)
	[-] if(w==null)
		[ ] return APlus.Find("//WPFControl[@automationId='PART_editControl'][{iFieldOrder}]/WPFTextBlock").sCaption
	[+] else
		[ ] return w.Find("//WPFControl[@automationId='PART_editControl'][{iFieldOrder}]/WPFTextBlock").sCaption
[+] void SaveToNotepad(string sFileName)
	[ ] SYS_EXECUTE("taskkill /im notepad.exe /f")
	[ ] sleep(1)
	[ ] glwNotepad.Invoke()
	[+] if(glwNotepad.Exists(2))
		[ ] glwNotepad.SetActive()
		[ ] glwNotepad.TypeKeys("<Ctrl-V>")
		[ ] sleep(1)
		[ ] glwNotepad.SaveFile(sFileName)
		[ ] glwNotepad.SetActive()
		[ ] glwNotepad.mnuFile.miExit.Pick()
	[+] else
		[ ] Log.Fail("Notepad may not be launched.")
[+] boolean CompareStringValue(string sVal1,string sVal2, number iTolerance optional)
	[ ] boolean bFlag=false
	[+] if(iTolerance==null)
		[ ] iTolerance=0.01
	[+] if(Abs(Val(sVal1)-Val(sVal2))/Val(sVal2)<iTolerance)
		[ ] bFlag=true
	[ ] return bFlag
	[ ] 
[+] boolean CompareList(list of ANYTYPE lsLeft, list of ANYTYPE lsRight)
	[ ] integer i
	[+] if(TypeOf(lsLeft)==TypeOf(lsRight) && ListCount(lsLeft)==ListCount(lsRight))
		[+] for(i=1;i<=ListCount(lsLeft);i++)
			[+] if(lsLeft[i]!=lsRight[i])
				[ ] break
	[+] else
		[ ] return false
	[+] if(i>ListCount(lsLeft))
		[ ] return true
	[+] else
		[ ] return false
	[ ] 
[+] void ComparePlot(string sLeftFile, string sRightFile, string sDataout)
	[ ] integer i,j
	[ ] string sLine
	[ ] list of string lsCap1,lsCap2,lsTemp
	[ ] HFILE hFile1,hFile2,hFile3,hFile4
	[ ] 
	[+] if(SYS_FileExists("{sDataout}\RightTemp.txt"))
		[ ] File.Delete("{sDataout}\RightTemp.txt")
	[+] if(SYS_FileExists("{sDataout}\LeftTemp.txt"))
		[ ] File.Delete("{sDataout}\LeftTemp.txt")
	[ ] 
	[ ] hFile1=SYS_FileOpen(sLeftFile,FM_READ)
	[ ] hFile3=SYS_FileOpen("{sDataout}\LeftTemp.txt",FM_APPEND)
	[+] while(SYS_FileReadLine(hFile1,sLine))
		[+] if(MatchStr("*<PlotSettings Value*",sLine))
			[ ] lsTemp=SplitStringToList(sLine,"&#xA;")
			[+] for(i=1;i<=ListCount(lsTemp);i++)
				[+] if(MatchStr("Title:*",lsTemp[i]))
					[ ] ListAppend(lsCap1,sLine)
				[+] else if(MatchStr("Xlab:*",lsTemp[i]))
					[ ] ListAppend(lsCap1,sLine)
				[+] else if(MatchStr("Ylab:*",lsTemp[i]))
					[ ] ListAppend(lsCap1,sLine)
				[+] else if(MatchStr("Label:*",lsTemp[i]))
					[ ] ListAppend(lsCap1,sLine)
				[+] else if(MatchStr("Legend:*",lsTemp[i]))
					[ ] ListAppend(lsCap1,sLine)
				[+] else
					[ ] continue
		[+] else if(MatchStr("*<Point XData=*",sLine))
			[ ] sLine=StrTran(sLine,"<Point XData=","")
			[ ] sLine=StrTran(sLine,"{chr(34)}YData=","")
			[ ] sLine=StrTran(sLine,"{chr(34)} />}","")
			[ ] SYS_FileWriteLine(hFile3,sLine)
		[+] else
			[ ] ListAppend(lsCap1,sLine)
	[ ] SYS_FileClose(hFile1)
	[ ] SYS_FileClose(hFile3)
	[ ] 
	[ ] hFile2=SYS_FileOpen(sRightFile,FM_READ)
	[ ] hFile4=SYS_FileOpen("{sDataout}\RightTemp.txt",FM_APPEND)
	[+] while(SYS_FileReadLine(hFile2,sLine))
		[+] if(MatchStr("*<PlotSettings Value*",sLine))
			[ ] lsTemp=SplitStringToList(sLine,"&#xA;")
			[+] for(i=1;i<=ListCount(lsTemp);i++)
				[+] if(MatchStr("Title:*",lsTemp[i]))
					[ ] ListAppend(lsCap2,sLine)
				[+] else if(MatchStr("Xlab:*",lsTemp[i]))
					[ ] ListAppend(lsCap2,sLine)
				[+] else if(MatchStr("Ylab:*",lsTemp[i]))
					[ ] ListAppend(lsCap2,sLine)
				[+] else if(MatchStr("Label:*",lsTemp[i]))
					[ ] ListAppend(lsCap2,sLine)
				[+] else if(MatchStr("Legend:*",lsTemp[i]))
					[ ] ListAppend(lsCap2,sLine)
				[+] else
					[ ] continue
		[+] else if(MatchStr("*<Point XData=*",sLine))
			[ ] sLine=StrTran(sLine,"<Point XData=","")
			[ ] sLine=StrTran(sLine,"{chr(34)}YData=","")
			[ ] sLine=StrTran(sLine,"{chr(34)} />}","")
			[ ] SYS_FileWriteLine(hFile4,sLine)
		[+] else
			[ ] ListAppend(lsCap2,sLine)
	[ ] SYS_FileClose(hFile2)
	[ ] SYS_FileClose(hFile4)
	[ ] 
	[+] if(CompareList(lsCap1,lsCap2) && CompareFileByAdiff("{sDataout}\LeftTemp.txt","{sDataout}\RightTemp.txt"))
		[ ] Log.Pass("The plot displays as expected.")
	[+] else
		[ ] Log.Fail("The plot does not display as expected.")
[+] void ExpandNaviPane()
	[ ] RECT rectNavPane
	[ ] rectNavPane=APlus.Find("//WPFContentControl[@name='PART_SelectedGroupContent']").GetRect()
	[+] if(rectNavPane.xSize<=34)
		[ ]  APlus.Find("//WPFToggleButton[@automationId='MinimizeButton']").Click()
		[ ] sleep(1)
[ ] //==============Appended Done===========
[ ] 
[ ] //==================Added by Zhangya================
[ ] //Basic Library 
[+] BOOLEAN IsWndNotFound(STRING locatorstr,window wnd optional)
	[+] FINDOPTIONS opts = {...}
		[ ] 10
		[ ] true
	[+] do
		[+] if(wnd != null)
			[ ] wnd.find(locatorstr,opts)
		[+] else
			[ ] Desktop.find(locatorstr,opts)
	[+] except
		[+] if(ExceptNum () == E_WINDOW_NOT_FOUND)
			[ ] return true
		[+] else if(ExceptNum () == E_INVALID_XPATH)
			[ ] Print("Find locator exception: the XPath locator is syntactically incorrect")
			[ ] return false
		[+] else if(ExceptNum () == E_WINDOW_INVALIDATED)
			[ ] Print("Find locator exception: window had been closed")
			[ ] return false
		[+] else
			[ ] Print("Find locator exception: Unknow Excpetion")
			[ ] return false
	[ ] return false
	[ ] 
[+] window MyFind(STRING locatorstr,window wnd optional)
	[+] FINDOPTIONS opts = {...}
		[ ] 10
		[ ] true
	[ ] window retval = null
	[+] do
		[+] if(wnd != null)
			[ ] retval = wnd.find(locatorstr,opts)
		[+] else
			[ ] retval = Desktop.find(locatorstr,opts)
	[+] except
		[+] if(ExceptNum () == E_WINDOW_NOT_FOUND)
			[ ] Print("Find locator exception: no object is found")
		[+] else if(ExceptNum () == E_INVALID_XPATH)
			[ ] Print("Find locator exception: the XPath locator is syntactically incorrect")
		[+] else if(ExceptNum () == E_WINDOW_INVALIDATED)
			[ ] Print("Find locator exception: window had been closed")
		[+] else
			[ ] Print("Find locator exception: Unknow Excpetion")
	[ ] return retval
[+] list of window MyFindAll(STRING locatorstr,window wnd optional)
	[+] FINDOPTIONS opts = {...}
		[ ] 10
		[ ] true
	[ ] List of window finds = null
	[ ] 
	[+] do
		[+] if(wnd != null)
			[ ] finds = wnd.FindAll(locatorstr,opts)
		[+] else
			[ ] finds = Desktop.FindAll(locatorstr,opts)
	[+] except
		[+] if(ExceptNum () == E_WINDOW_NOT_FOUND)
			[ ] Print("FindAll locator exception: no object is found")
		[+] else if(ExceptNum () == E_INVALID_XPATH)
			[ ] Print("FindAll locator exception: the XPath locator is syntactically incorrect")
		[+] else if(ExceptNum () == E_WINDOW_INVALIDATED)
			[ ] Print("FindAll locator exception: window had been closed")
		[+] else
			[ ] Print("FindAll locator exception: Unknow Excpetion")
		[ ] 
	[ ] return finds
[+] list of window MyFindByWndRectRelationship(window ContainerWnd, STRING targetlocatorstr,window wnd optional)
	[ ] RECT baserc = ContainerWnd.GetRect(true)
	[+] if(baserc == null)
		[ ] return null
	[ ] 
	[ ] list of window finds = MyFindAll(targetlocatorstr,wnd)
	[+] if(finds == null || ListCount(finds) <= 0)
		[ ] return null
	[ ] 
	[+] list of window ret = {...}
		[ ] 
	[ ] int i = 0
	[+] for(i = 1; i <= ListCount(finds); i++)
		[ ] RECT rc = finds[i].GetRect(true)
		[+] if(rc.xPos >= baserc.xPos && rc.yPos >= baserc.yPos && rc.xSize <= baserc.xSize && rc.ySize <= baserc.ySize)
			[ ] ListAppend(ret,finds[i])
		[ ] 
	[ ] 
	[+] if(ret == null || ListCount(ret) <= 0)
		[ ] return null
	[+] else
		[ ] return ret
	[ ] 
[+] BOOLEAN IsEqualStringList(list of string list1, list of string list2)
	[+] if((list1 != null && ListCount(list1) > 0) && (list2 != null && ListCount(list2) > 0))
		[ ] int i=0
		[ ] int j=0
		[ ] BOOLEAN allcanfind = true
		[+] for(i=1;i<=ListCount(list1);i++)
			[+] for(j=1;j<=ListCount(list2);j++)
				[+] if(list2[j] == list1[i])
					[ ] break
			[+] if(j > ListCount(list2))
				[ ] allcanfind = false
				[ ] break
		[+] if(false == allcanfind)
			[ ] return false
		[ ] 
		[+] for(i=1;i<=ListCount(list2);i++)
			[+] for(j=1;j<=ListCount(list1);j++)
				[+] if(list1[j] == list2[i])
					[ ] break
			[+] if(j > ListCount(list1))
				[ ] allcanfind = false
				[ ] break
		[ ] return allcanfind
		[ ] 
	[+] else if(list1 ==null && list2 == null)
		[ ] return true
	[+] else if(ListCount(list1) <= 0 && ListCount(list2) <= 0)
		[ ] return true
	[+] else
		[ ] return false
		[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
[ ] //PLEASE KEEP THESE FUNCTIONS SYNCHRONIZED WITH THE ASPEN PLUS FUNCTIONS.INC
[ ] //PLEASE KEEP THESE FUNCTIONS SYNCHRONIZED WITH THE ASPEN PLUS APMAINFRAME.INC FILE
[+] void verifyTable(int rows, int columns, list of string expectedValues, int ignoreRows, boolean countCells optional,  window dataGrid , boolean selectAll optional, string file optional, real tolerance optional, real absTol optional )
	[ ] //expected values should be a copy of the table you want to verify
	[ ] //Verification will proceed with by using perfect match with strings and relTol with numbers
	[ ] //Ignore Rows---> Ignores the amount of intial specified rows in the table
	[ ] //USE "BLANK" to specify a blank row in expected input
	[ ] //Absolute tolerance is used if relative tolerance fails
	[ ] 
	[ ] //SET THE VALUE OF HOW LOW OF NUMBERS TO IGNORE
	[ ] setPrecision(1e-15)
	[ ] 
	[ ] 
	[+] if( tolerance == NULL)
		[ ] tolerance =  relTol 
	[+] if( file == NULL)
		[ ] 
		[ ] Clipboard.SetText()
		[ ] sleep(1)
		[+] if( selectAll == NULL || selectAll == TRUE)
			[+] do
				[ ] dataGrid.click()
			[+] except
				[ ] exceptClear()
				[ ] Log.ERROR("ERROR: Cannot find indicated First Cell.")
				[ ] return
			[ ] dataGrid.TypeKeys("<ctrl-a>")
			[ ] 
		[ ] dataGrid.TypeKeys("<ctrl-c>")
		[ ] sleep(1)
		[ ] list of string clipboard = Clipboard.GetText()
	[+] else // Input From a file
		[ ] handle hFile = FileOpen(file, FM_WRITE)
		[ ] string nextLine
		[+] expectedValues = {...}
			[ ] 
		[+] while( FileReadLine(hFile, nextLine) )
			[ ] listAppend(expectedValues, nextLine)
		[ ] FileClose(hFile)
		[ ] 
	[ ] int i = 1, j = 1, k = 1
	[ ] string line
	[ ] list of string foundCells
	[ ] list of string expectedCells
	[ ] int length
	[ ] int lastTab =0
	[ ] clipboard = divideListByString(clipboard, chr(10))
	[ ] int clipboardLen = listCount(clipboard)
	[+] for( k = 1+ignoreRows; k <=clipboardLen; k++)
		[ ] line = clipboard[k]
		[ ] lastTab = 0
		[ ] length = len(line)
		[ ] int cells = 0
		[+] for( i = 1; i <= length; i++)
			[+] if( subStr(line, i, 1) == chr(9))
				[+] if( lastTab < i - 1)
					[ ] listAppend(foundCells, substr(line, lastTab + 1, i - lastTab - 1))
				[+] else
					[ ] listAppend(foundCells, "BLANK")
				[ ] lastTab = i
				[ ] cells++
		[+] if(            (    i > 1 && subStr(line, i, 1) == chr(0) && subStr(line, i-1, 1) == chr(9) )      ||     (   subStr(line, i, 1) == chr(9) )       ||   (  i == 1 && subStr(line, i, 1) == chr(0)  )  )
			[ ] listAppend(foundCells, "BLANK")
			[ ] cells++
		[+] else
			[ ] listAppend(foundCells, substr(line, lastTab + 1, i - lastTab)) // Add last celll to the list
			[ ] cells++
			[ ] 
		[ ] 
	[+] for each line in expectedValues
		[ ] cells = 0
		[+] if( line == "BLANK")
			[+] for(j =1; j <= columns; j++)
				[ ] listAppend(expectedCells, "BLANK")
				[ ] cells++
		[+] else
			[ ] length = len(line)
			[ ] lastTab =0
			[+] for( i = 1; i <= length; i++)
				[+] if( subStr(line, i, 1) == chr(9))
					[+] if( lastTab < i - 1)
						[ ] listAppend(expectedCells, substr(line, lastTab + 1, i - lastTab - 1))
					[+] else
						[ ] listAppend(expectedCells, "BLANK")
					[ ] cells++
					[ ] lastTab = i
			[+] if(            (    i > 1 && subStr(line, i, 1) == chr(0) && subStr(line, i-1, 1) == chr(9) )      ||     (   subStr(line, i, 1) == chr(9) )       ||   (  i == 1 && subStr(line, i, 1) == chr(0)  )  )
				[ ] listAppend(expectedCells, "BLANK")
				[ ] cells++
			[+] else
				[ ] listAppend(expectedCells, substr(line, lastTab + 1, i - lastTab)) // Add last celll to the list
				[ ] cells++
		[ ] 
	[+] if( countCells != NULL && countCells == TRUE )
		[+] if( listcount(foundCells) != rows*columns)
			[ ] Log.Error("ERROR:The table you are trying to verify({listcount(foundCells) } cells) doesn't match parameter dimensions({rows*columns} cells}")
			[ ] return
		[+] if( listcount(expectedCells) != rows*columns)
			[ ] Log.Error("ERROR:The  expected values for the table you are trying to verify doesn't match parameter dimensions    Expected {rows*columns} cells,     InputData: {listCount(expectedCells)} ")
			[ ] return
	[ ] 
	[ ] print()
	[ ] print()
	[ ] print("----------------------------Starting Table Comparison----------------------------------------")
	[ ] print("RELATIVE TOLERANCE:                {tolerance}")
	[+] if( absTol  == NULL )
		[ ] print("ABSOLUTE TOLERANCE:         UNSPECIFIED")
	[+] else
		[ ] print("ABSOLUTE TOLERANCE:        {absTol}")
	[ ]  print()
	[ ] print()
	[ ] 
	[ ] 
	[ ] i = 0
	[+] for( i =1; i <= listCount(foundCells); i++ )
		[ ] //Check for out of range integers beyond 32 bits. Val function doesn't support long ints.
		[ ] 
		[ ] //Exit in case you are checking a table that is longer than the expected but still ok.
		[+] if( listCount(expectedCells) < i)
			[ ] break
		[ ] 
		[+] do
			[ ] val(expectedCells[i])
		[+] except
			[ ] exceptClear()
			[ ] expectedCells[i] = expectedCells[i] +".0"
			[ ] 
		[+] do
			[ ] val(foundCells[i])
		[+] except
			[ ] exceptClear()
			[ ] foundCells[i] = foundCells[i] +".0"
		[ ] real expectedVal = val(expectedCells[i]) 
		[ ] real foundVal = val(foundCells[i])
		[+] if( expectedVal == 0) // No number present or Number 0
			[+] if( (matchstr("0.0*", expectedCells[i]) && matchstr("0", foundCells[i]) ) || (matchstr("0.0*", foundCells[i]) && matchstr("0", expectedCells[i]) ))
				[ ] Log.Pass(" Row{ ((i-1)/columns)+1}  Column: { (i-1)%columns + 1}     Matched:{expectedCells[i]}       With Found: {foundCells[i]}         Absolute Error: {abs(expectedVal -foundVal) } ")
			[+] else if( !matchstr(expectedCells[i],foundCells[i]))
				[+] if( absTol != NULL && absTol >= abs(expectedVal -foundVal)  )
					[ ]  Log.Pass(" Row{ ((i-1)/columns)+1}  Column: { (i-1)%columns + 1}     Matched:{expectedCells[i]}       With Found: {foundCells[i]}         Absolute Error: {abs(expectedVal -foundVal) } ")
				[+] else
					[ ] Log.Error(" Row{ ((i-1)/columns)+1}  Column: { (i-1)%columns + 1}     Expected:{expectedCells[i]}       Actual: {foundCells[i]} ")
			[+] else
				[ ] Log.Pass(" Row{ ((i-1)/columns)+1}  Column: { (i-1)%columns + 1}     Found:{expectedCells[i]} ")
		[+] else
			[+] if(  abs( (expectedVal -foundVal )/ expectedVal ) > tolerance)
				[ ] 
				[+] if( absTol != NULL && absTol >= abs(expectedVal -foundVal)  )
					[ ] Log.Pass(" Row{ ((i-1)/columns)+1}  Column: { (i-1)%columns + 1}     Matched: {expectedCells[i]}		  	With Found: {foundCells[i]}	        Relative Error (FAIL):	 { abs( (expectedVal -foundVal )/ expectedVal )*100.0 }%        Absolute Error(PASS): {abs(expectedVal -foundVal)}  ")
				[+] else
					[ ] Log.Error(" Row{ ((i-1)/columns)+1}  Column: { (i-1)%columns + 1}     Expected:{expectedCells[i]}       Actual: {foundCells[i]}           Releative Error (FAIL):	 { abs( (expectedVal -foundVal )/ expectedVal )*100.0 }%        Absolute Error(FAIL): {abs(expectedVal -foundVal)}      ")
			[+] else
				[ ] Log.Pass(" Row{ ((i-1)/columns)+1}  Column: { (i-1)%columns + 1}     Matched: {expectedCells[i]}		  	With Found: {foundCells[i]}	   		Relative Error:	 { abs( (expectedVal -foundVal )/ expectedVal )*100.0 }%              Absolute Error: {abs(expectedVal -foundVal)}")
	[ ] 
	[ ] 
	[ ] //PUT PRECISION BACK TO DEFAULT VALUE
	[ ] setPrecision(0.000001)
	[ ] 
	[ ] 
[+] void verifyTableIsFull( window dataGrid optional , real percentFilled, real percentNonZero, boolean errorOnEmpty optional,   int ignoreRows optional,  boolean selectAll optional, list of string ignoreColumn optional, int maxBlank optional)
	[ ] //Checks to make sure a certain percentage of the table is filled in and not zero values
	[ ] //If maxBlank is specified, this is used instead of the percentage limits to evaluate
	[ ] //<empty> is counted as a blank cell
	[ ] //Specify errorOnEmpty as TRUE to log an error if a <empty> is found in the table
	[ ] //Ignore Rows -- Specifies the number of rows to ignore off the top of the table. Useful when the headers are included in the table.
	[ ] //ingoreColumns -- Specify a list of columns to ignore
	[ ] 
	[ ] 
	[ ] //SET THE VALUE OF HOW LOW OF NUMBERS TO IGNORE
	[ ] setPrecision(1e-15)
	[ ] 
	[ ] PRINT("------------------------Checking Table for Completion --------------------------------")
	[ ] PRINT("Requirements:")
	[ ] PRINT("Percent Filled: {percentFilled}")
	[ ] PRINT("Percent Non-Zero: {percentNonZero}")
	[+] if( maxBlank != NULL)
		[ ] PRINT("Maximum Blank Cells:  {maxBlank}")
	[ ] PRINT()
	[ ] 
	[ ] int i = 1, j = 1, k = 1
	[ ] string line
	[ ] list of string foundCells
	[ ] list of string expectedCells
	[ ] int length
	[ ] int lastTab =0
	[+] if( ignoreRows == NULL)
		[ ] ignoreRows = 0
	[ ] 
	[+] Clipboard.SetText()
		[+] if( selectAll == NULL || selectAll != FALSE)
			[ ] dataGrid.typeKeys("<ctrl-a>")
		[ ] sleep(0.25)
		[ ] dataGrid.find("//WPFDataGridCell[1]").BringIntoView()
		[ ] dataGrid.find("//WPFDataGridCell[1]").typeKeys("<ctrl-c>")
		[ ] sleep(0.25)
	[ ] 
	[ ] list of string clipboard = Clipboard.GetText()
	[ ] clipboard = divideListByString(clipboard, chr(10))
	[ ] int clipboardLen = listCount(clipboard)
	[ ] int columns = 0
	[ ] int rows =  listCount(clipboard) - ignoreRows
	[ ] 
	[ ] 
	[+] for( k = 1+ignoreRows; k <=clipboardLen; k++)
		[ ] line = clipboard[k]
		[ ] lastTab = 0
		[ ] length = len(line)
		[ ] int cells = 0
		[ ] int column = 1
		[+] for( i = 1; i <= length; i++)
			[+] if( subStr(line, i, 1) == chr(9))
				[+] if( lastTab < i - 1)
					[ ] listAppend(foundCells, substr(line, lastTab + 1, i - lastTab - 1))
				[+] else
					[ ] listAppend(foundCells, "BLANK")
				[ ] column++
				[ ] lastTab = i
		[+] if(            (    i > 1 && subStr(line, i, 1) == chr(0) && subStr(line, i-1, 1) == chr(9) )      ||     (   subStr(line, i, 1) == chr(9) )       ||   (  i == 1 && subStr(line, i, 1) == chr(0)  )  )
			[ ] listAppend(foundCells, "BLANK")
			[ ] column++
		[+] else
			[ ] listAppend(foundCells, substr(line, lastTab + 1, i - lastTab)) // Add last celll to the list
			[ ] column++
		[ ] 
		[+] if( k == 1+ignoreRows) // Save the number of columns the first time through. Column increments each time one a cell is found so it will be 1 greater than the actual number of columns.
			[ ] columns = column -1
	[ ] 
	[ ] string cell
	[ ] int blankCells = 0
	[ ] int nonZeroCells = 0
	[ ] int cellsChecked = listCount(foundCells)
	[ ] column = 1
	[ ] 
	[ ] //Count the number of Blank, Empty, and Non-Zero cells, ignore the ones in column from the ignore list.
	[+] for each cell in foundCells
		[+] if( column > columns)
			[ ] column = 1
		[+] if( ignoreColumn != NULL && listFind(ignoreColumn, column) != 0)
			[ ] cellsChecked--
			[ ] column++
			[ ] continue
		[+] do
			[ ] val(cell)
		[+] except
			[ ] cell = cell + ".0"
		[+] if( val(cell) != 0  )
			[ ] nonZeroCells++
		[+] else if( cell == "BLANK")
			[ ] blankCells++
		[+] else if(matchstr("*<empty>*", cell) )
				[ ] blankCells++
			[+] if( errorOnEmpty == NULL || errorOnEmpty == FALSE) 
				[ ] Log.Error("{chr(34)}<empty>{chr(34)} cell found in datagrid")
			[ ] 
		[+] else
			[ ] 
		[ ] column++
		[ ] 
	[ ] 
	[+] if( cellsChecked > 0 )
		[ ] 
		[+] if( maxBlank != NULL && maxBlank < blankCells)
			[ ] Log.Error("ERROR:  {blankCells}  of  {cellsChecked} are Blank")
		[+] else if( maxBlank != NULL && maxBlank >= blankCells)
			[ ] Log.Pass("{blankCells}  of  {cellsChecked} are Blank")
			[ ] 
			[ ] real percentFilledFound = ((cellsChecked - blankCells)* 1.0)/ cellsChecked
			[ ] 
			[ ] real percentNonZeroFound = ((cellsChecked - nonZeroCells)* 1.0)/ cellsChecked
			[ ] 
			[+] if(  percentFilledFound < percentFilled )
				[ ] Log.Error("ERROR:   Only {percentFilledFound*100}%  of the Table is Filled.     Required :  {percentFilled*100}%")
			[+] else
				[ ] Log.Pass(" {percentFilledFound*100}%  of the table is filled.     Required :  {percentFilled*100}%")
			[ ] 
			[+] if(  percentNonZeroFound < percentNonZero )
				[ ] Log.Error("ERROR:   Only {percentNonZeroFound*100}%  of the Table is Non-Zero Values.    	 Required :  {percentNonZero*100}%")
			[+] else
				[ ] Log.Pass(" {percentNonZeroFound*100}%  of the table is non-Zero Values.    		 Required :  {percentNonZero*100}%")
	[+] else
		[ ] Log.Warning("-------------------- !!! No Cells to Check !!! --------------------------")
	[ ] 
	[ ] PRINT("-------------------------------------------------------------------------- --------------------------------")
	[ ] 
	[ ] 
	[ ] 
	[ ] 
[+] list of STRING divideListByString(list of STRING listIn, string divider  )
	[ ] list of string dividedGrid = {...}
	[ ] 
	[ ] string row
	[ ] string section
	[+] for each row in listIn
		[ ] //Remove all Double NewLines
		[+] while(matchStr("*{divider}{divider}*", row))
			[ ] row = strTran(row, "{divider}{divider}", divider)
		[ ] int i = 1
		[ ] section = getField(row, divider, i) 
		[+] while(section != "")
			[ ] listAppend(dividedGrid, section)
			[ ] i++
			[ ] section = getField(row, divider, i) 
	[+] if( listCount(dividedGrid) > listCount(listIn))
		[ ] Clipboard.SetText(dividedGrid)
		[ ] return dividedGrid
	[+] else
		[ ] return listIn
	[ ] 
	[ ] 
[ ] 
[ ] //PLEASE KEEP THESE FUNCTIONS SYNCHRONIZED WITH THE ASPEN PLUS FUNCTIONS.INC
[+] boolean setValueByHeader(window dataGrid, string value,  string rowHeader, string columnHeader optional, int moveRight optional )
	[ ] //USE ONLY FOR WHEN HEADERS ARE ON THE GRID
	[ ] int maxNav = 200
	[ ] int i = 0
	[ ] window mainWin =dataGrid.GetParent().GetParent()
	[ ] dataGrid.typeKeys("<ctrl-home>")
	[+] if( columnHeader != NULL )
		[+] while( dataGrid.selectedCellText != columnHeader &&  i < maxNav )
			[ ] mainWin.typeKeys("<Right>")
			[ ] i++
		[+] do
			[ ] dataGrid.typeKeys("<ctrl-home>")
		[+] except
			[+] do
				[ ] mainWin.Typekeys("<Left {i}>")
				[ ] dataGrid.SelectCell(1,1)
			[+] except
				[ ] Log.Error("ERROR: Unable To Navigate through Grid")
		[ ] 
		[+] if( i > maxNav)
			[ ] Log.Error("ERROR: Unable to Find Column Header")
		[ ] 
	[+] int j = 0
		[+] while( dataGrid.selectedCellText != rowHeader &&  j < maxNav)
			[ ] mainWin.typeKeys("<Down>")
			[ ] j++
	[ ] 
	[+] if( j > maxNav )
		[ ] Log.Error("ERROR: Unable to find Row Header in the grid")
	[ ] 
	[+] if( columnHeader != NULL )
		[ ] mainWin.typeKeys("<Right {i}>")
	[+] else
		[+] if( moveRight == NULL)
			[ ] mainWin.typeKeys("<Right 1>")
		[+] else
			[ ] mainWin.typeKeys("<Right {moveRight}>")
	[ ] 
	[ ] mainWin.typeKeys("{value}<Enter>")
	[+] if( dataGrid.selectedCellText != value && val( dataGrid.selectedCellText) != val(value) )
		[ ] Log.Error("ERROR: Failed to input desired value into dataGrid")
		[ ] return False
	[+] else
		[ ] return True
	[ ] 
[+] String findValueByHeaders(string rowHeader, string columnHeader optional, window dataGrid , int moveRight optional, boolean copyWithLabels optional, boolean copyGrid optional)
	[ ] //Specify a unique row reader to search Clipboard text for to get row index
	[ ] //Specify the value of the column you want to check
	[ ] //specify a base value
	[ ] //Specify a visible grid cell to do a Select-All on.
	[ ] 
	[+] if( copyGrid == NULL || copyGrid == True)
		[ ] Clipboard.setText()
		[ ] dataGrid.typeKeys("<ctrl-Home>")
		[ ] dataGrid.typeKeys("<Ctrl-a>")
		[+] if( copyWithLabels != NULL && copyWithLabels == TRUE)
			[ ] dataGrid.typeKeys("<ctrl-Shift-c>")
		[+] else
			[ ] dataGrid.typeKeys("<ctrl-c>")
	[+] if( copyGrid == NULL || copyGrid == True)
		[ ] sleep(0.5)
	[ ] list of STRING grid = Clipboard.getText()
	[ ] 
	[ ] //Need to check if there are lines to be divided
	[ ] int i
	[ ] 
	[ ] grid = divideListByString(grid, chr(10))
	[ ] 
	[ ] int line = -1
	[ ] 
	[ ] boolean foundColumn = FALSE
	[ ] boolean foundRow = FALSE
	[ ] 
	[+] for( i = 1; i <= listCount(grid); i++)
		[+] if( matchstr( "{rowHeader}*", grid[i]) )
			[ ] foundRow = TRUE
			[ ] break
			[ ] 
	[+] if( columnHeader != NULL )
		[ ] int j = 1
		[+] while( getField(grid[1], chr(9), j ) != "" || j == 1 || getField(grid[1], chr(9), j+1 ) != "" || getField(grid[1], chr(9), j+2 ) != "")  //Adding extra checks in case there is a blank column header, 
			[+] if( matchstr( "{columnHeader}*", getField(grid[1], chr(9), j ) ) )
				[ ] foundColumn = TRUE
				[ ] break
			[ ] j++
		[ ] 
		[+] if( !foundColumn || !foundRow )
			[ ] Log.Error("ERROR: Unable to find desired header pair    ROW: {rowHeader}      COLUMN: {columnHeader}  ")
			[ ] PRINT("FOUND COLUMN: {foundColumn}")
			[ ] PRINT("FOUND ROW: {foundRow}")
			[ ] return "MEH!"
		[ ] 
		[ ] PRINT("Row Header: {chr(34)}{rowHeader}{chr(34)}                       Column Header: {chr(34)}{columnHeader}{chr(34)}                       LOCATED AT: ({i} , {j})                    FOUND VALUE:  {getField(grid[i], chr(9), j )}   ")
		[ ] return getField(grid[i], chr(9), j )
	[+] else
		[ ] j = 2
		[ ] 
		[+] if(  !foundRow )
			[ ] Log.Error("ERROR: Unable to find desired header  ROW: {rowHeader}   ")
			[ ] return "MEH!"
		[ ] 
		[ ] //For some Reason, HYSYS sometimes copied with a column of spaces
		[+] if( getField(grid[i], chr(9), j ) == " " )
			[ ] j++
		[ ] 
		[+] if( moveRight  == NULL )
			[ ] moveRight = 0
		[+] else
			[ ] j+= moveRight
		[ ] 
		[ ] PRINT("Row Header: {chr(34)}{rowHeader}{chr(34)}                      LOCATED AT: ({i} , {j})                    FOUND VALUE:  {getField(grid[i], chr(9), j )}   ")
		[ ] return getField(grid[i], chr(9), j )
		[ ] 
	[ ] 
	[ ] 
[+] boolean checkValueByHeaders(string rowHeader, string columnHeader optional, anyType base, window dataGrid, real tolerance optional, int moveRight optional, boolean copyWithLabels optional, boolean copyGrid optional)
	[ ] //Specify a unique row reader to search Clipboard text for to get row index
	[ ] //Specify the value of the column you want to check
	[ ] //specify a base value
	[ ] //Specify a visible grid cell to do a Select-All on.
	[ ] //copyGrid --- Specify FALSE for multiple checks on the same grid so it won't recopy
	[ ] 
	[ ] string sValue = findValueByHeaders( rowHeader, columnHeader, dataGrid, moveRight, copyWithLabels, copyGrid )
	[ ] 
	[+] if( sValue == "MEH!" )
		[ ] return FALSE
	[ ] 
	[+] if( tolerance == NULL )
		[ ] tolerance = relTol
	[ ] 
	[+] if( typeOf( base )  == REAL )
		[ ] return checkTolerance(base, val( sValue), tolerance)
		[ ] 
	[+] else if( typeOf(base) == INTEGER )
		[ ] return checkTolerance([REAL]base, val( sValue), tolerance)
		[ ] 
	[+] else if( typeOf(base) == STRING )
		[+] if( !matchstr(base, sValue))
			[ ] return FALSE
		[+] else
			[ ] return TRUE
		[ ] 
	[+] else
		[ ] Log.Error("ERROR: Unrecognized base type passed to checkValueInDataGrid  Function: {typeOf(base)}")
		[ ] return false
	[ ] 
	[ ] 
	[ ] 
	[ ] 
[ ] 
[ ] 
[ ] 
[+] //Things That Trevor doesn't want to type Log. before to use
		[ ] LIST OF STRING lsLog
		[+] VOID Step (STRING sLog) //Used for output cases setp 
			[ ] prINT("==={sLog}")
			[ ] ListAppend(lsLog,"==={sLog}")
			[ ] 
[ ] 
[ ] 
