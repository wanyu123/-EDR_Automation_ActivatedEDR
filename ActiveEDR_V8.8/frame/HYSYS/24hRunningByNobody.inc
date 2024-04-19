[ ] //*********************************************************************************
[ ] //
[ ] //	Description:			24 Hours by Nobody resolution core Libs
[ ] //	Pre Condition:		None
[ ] //	Author:				Danny,Wang(Danny.Wang@AspenTech.com)
[ ] //	Date:				Mar 12, 2009
[ ] //	History:				None
[ ] //
[ ] //*********************************************************************************
[ ] 
[ ] use "generic_library.inc"
[ ] //use "highLight_library.inc"
[ ] //use "projectSetting_library.inc"--Your project setting file
[ ] 
[ ] //For 24h running by nobody
[ ] const STRING gcsTCRunStatus			="C:\RefSYS\Result\TestCaseRunStatus.ini"
[ ] INT giCaseWaitTime						=1
[ ] BOOLEAN gbRunBy24hRunning			=True
[ ] 
[ ] const STRING PASS					="Pass"
[ ] const STRING FAIL						="Fail"
[ ] const STRING UNRUN					="Unrun"
[ ] const STRING SCRIPTERR				="ScriptErr"
[ ] const STRING WARNING				="Warning"
[ ] const STRING MANUALCHECK			="ManualCheck"
[ ] 
[+] //Case
	[+] winclass wcCase
		[ ] STRING  sStatus=PASS //Case actual status
		[ ] STRING sExpectStatus=PASS //Test case expected status
		[ ] 
		[ ] //Method
		[+] VOID UpdateRun (STRING sCaseName, STRING sStauts, STRING sExpectStatus optional)
			[ ] HINIFILE hIni
			[ ] STRING sCaseInfo
			[ ] 
			[ ] hIni = IniFileOpen (gcsTCRunStatus) //"{gcsTestDir}\Result\RunFailRecord.ini")
			[ ] sCaseInfo = IniFileGetValue (hIni, "RunRecords", sCaseName)
			[ ] //PRINT(sValue)
			[+] if(sCaseInfo=="")
				[ ] //PRINT("ADD NEW")
				[ ] IniFileSetValue (hIni, "RunRecords", sCaseName,"1^{sStauts}^{sExpectStatus}")
			[+] else
				[ ] //PRINT("UPDATE")
				[ ] LIST OF ANYTYPE lsValue={}
				[ ] INT iRunLoop=-1
				[ ] lsValue=glCastStrToList(sCaseInfo,"^")
				[ ] iRunLoop=val(lsValue[1])+1
				[ ] IniFileSetValue (hIni, "RunRecords", sCaseName,"{iRunLoop}^{sStauts}^{sExpectStatus}")
				[ ] //sValue = IniFileGetValue (hIni, "RunRecords", sCaseName)
				[ ] //PRINT(sValue)
			[ ] IniFileClose (hIni)
		[ ] 
		[+] VOID RunBy24h (BOOLEAN gbRunBy24hRunning optional)
			[+] if(gbRunBy24hRunning==NULL)
				[ ] gbRunBy24hRunning=FALSE
			[ ] 
			[+] if(gbRunBy24hRunning)
				[ ] HINIFILE hIni
				[ ] STRING sValue
				[ ] INT iRunLoop=-1
				[ ] 
				[ ] hIni = IniFileOpen (gcsTCRunStatus) 
				[ ] STRING sCaseName
				[ ] LIST OF ANYTYPE latArgs={}
				[ ] 
				[ ] latArgs=GetTestCaseArgs()
				[ ] 
				[+] if(ListCount(latArgs)>0)
					[+] if(MatchStr("CQ00*",latArgs[1])==TRUE)
						[ ] sCaseName=latArgs[1]
					[+] else
						[ ] sCaseName=GetTestCaseName()
				[+] else
					[ ] sCaseName=GetTestCaseName()
				[ ] sValue = IniFileGetValue (hIni, "RunRecords",sCaseName )
				[+] if(sValue!=NULL&&sValue!="")
					[ ] LIST OF STRING lsValue={}
					[ ] lsValue=glCastStrToList(sValue,"^")
					[+] if(lsValue[2]==lsValue[3])
						[ ] print("√√√Passed!")
						[ ] exit
						[ ] 
					[+] else
						[ ] Case.RunSpeed(iRunLoop)
				[ ] 
				[ ] IniFileClose (hIni)
		[ ] 
		[+] VOID Exit ()
			[ ] STRING ID=""
			[ ] LIST OF ANYTYPE latArgs={}
			[ ] 
			[ ] latArgs=GetTestCaseArgs()
			[+] if(ListCount(latArgs)>0)
				[+] if(MatchStr("CQ00*",latArgs[1])==TRUE)
					[ ] ID=latArgs[1]
				[+] else
					[ ] ID=GetTestCaseName()
			[+] else
				[ ] ID=GetTestCaseName()
			[ ] 
			[+] if(GetTestCaseErrorCount()>0&&Case.sStatus!=FAIL&&Case.sStatus!=MANUALCHECK)
				[ ] Case.sStatus=SCRIPTERR
			[+] if(GetTestCaseWarningCount()>0&&Case.sStatus!=FAIL&&Case.sStatus!=MANUALCHECK&&Case.sStatus!=SCRIPTERR)
				[ ] Case.sStatus=WARNING
			[ ] 
			[ ] Case.UpdateRun(ID,Case.sStatus,Case.sExpectStatus)
			[ ] 
		[ ] 
		[+] VOID RunSpeed (INT iMode)
			[+] switch iMode
				[+] case 1
					[ ] Agent.SetOption (OPT_KEYBOARD_DELAY, 0.2)
					[ ] Agent.SetOption (OPT_MOUSE_DELAY, 0.2)
					[ ] sleep(1*giCaseWaitTime)
				[+] case 2
					[ ] Agent.SetOption (OPT_KEYBOARD_DELAY, 0.4)
					[ ] Agent.SetOption (OPT_MOUSE_DELAY, 0.4)
					[ ] sleep(2*giCaseWaitTime)
				[+] case 3
					[ ] Agent.SetOption (OPT_KEYBOARD_DELAY, 0.5)
					[ ] Agent.SetOption (OPT_MOUSE_DELAY, 0.5)
					[ ] sleep(4*giCaseWaitTime)
				[+] default
					[ ] Agent.SetOption (OPT_KEYBOARD_DELAY, 0.1)
					[ ] Agent.SetOption (OPT_MOUSE_DELAY,0.1)
					[ ] sleep(6*giCaseWaitTime)
					[ ] 
		[ ] 
	[ ] 
	[ ] window wcCase Case
[ ] 
[ ] 
[+] //Log
	[ ] //Run Mode of Log 
	[ ] BOOLEAN gbDisplayPass				=TRUE
	[ ] BOOLEAN gbDisplayDebug				=FALSE
	[ ] BOOLEAN gbDisplayFail				=TRUE
	[ ] BOOLEAN gbDisplayWarning			=TRUE
	[ ] BOOLEAN gbDisplayMessage			=TRUE
	[ ] BOOLEAN gbDisplayWarningMessage	=TRUE
	[ ] BOOLEAN gbDisplayError				=TRUE
	[ ] BOOLEAN gbDisplayManualCheck		=TRUE
	[ ] 
	[+] winclass wcLog
		[ ] LIST OF STRING lsLog
		[ ] 
		[ ] //------------
		[+] VOID Verify (STRING sLog) //Used for verify step
			[ ] prINT("###{sLog}")
			[ ] ListAppend(lsLog,"###{sLog}")
			[ ] 
		[ ] 
		[+] VOID Pass (ANYTYPE sLog) //Used for check point is successfully
			[+] if(gbDisplayPass==TRUE)
				[+] if(TypeOf(sLog)==list of string)
					[ ] LIST OF STRING lsLog=sLog
					[ ] INT i=-1
					[+] for(i=1;i<=ListCount(lsLog);i++)
						[ ] Print("√√√{lsLog[i]}")
				[+] else
					[ ] Print("√√√{sLog}")
				[ ] 
			[ ] ListAppend(lsLog,"√√√{sLog}")
		[ ] 
		[+] VOID Fail (ANYTYPE sLog) //Used for check point is failed
			[+] if(gbDisplayFail==TRUE)
				[+] if(TypeOf(sLog)==LIST OF STRING)
					[ ] LIST OF STRING lsLog=sLog
					[ ] INT i=-1
					[+] for(i=1;i<=ListCount(lsLog);i++)
						[ ] LogError("xxx{lsLog[i]}")
				[+] else
					[ ] LogError("xxx{sLog}")
				[ ] 
			[ ] ListAppend(lsLog,"xxx{sLog}")
			[ ] Case.sStatus=FAIL
		[ ] 
		[ ] //------------
		[+] VOID Error (ANYTYPE sLog) //Used for comman script error
			[+] if(gbDisplayError==TRUE)
				[+] if(TypeOf(sLog)==LIST OF STRING)
					[ ] LIST OF STRING lsLog=sLog
					[ ] INT i=-1
					[+] for(i=1;i<=ListCount(lsLog);i++)
						[ ] LogError("***{lsLog[i]}")
				[+] else
					[ ] LogError("***{sLog}")
				[ ] 
			[ ] Case.sStatus=SCRIPTERR
			[ ] ListAppend(lsLog,"***Script Error:{sLog}")
			[ ] 
		[ ] 
		[+] VOID Warning (ANYTYPE sLog) //Used for giving a warning
			[+] if(gbDisplayWarning==TRUE)
				[+] if(TypeOf(sLog)==list of string)
					[ ] LIST OF STRING lsLog=sLog
					[ ] INT i=-1
					[+] for(i=1;i<=ListCount(lsLog);i++)
						[ ] LogWarning("???{lsLog[i]}")
				[+] else
					[ ] LogWarning("???{sLog}")
		[ ] 
		[+] VOID WarningMessage (ANYTYPE sLog) //Used for output a warning message
			[+] if(gbDisplayWarningMessage==TRUE)
				[+] if(TypeOf(sLog)==LIST OF STRING)
					[ ] LIST OF STRING lsLog=sLog
					[ ] INT i=-1
					[+] for(i=1;i<=ListCount(lsLog);i++)
						[ ] LogWarning(">>>{lsLog[i]}")
				[+] else
					[ ] LogWarning(">>>{sLog}")
		[ ] 
		[ ] //------------
		[+] VOID Debug (ANYTYPE sLog) //Used for output debug message
			[+] if(gbDisplayDebug==TRUE)
				[+] if(TypeOf(sLog)==list of string)
					[ ] LIST OF STRING lsLog=sLog
					[ ] INT i=-1
					[+] for(i=1;i<ListCount(lsLog);i++)
						[ ] prINT("---{lsLog[i]}")
				[+] else
					[ ] prINT("---{sLog}")
		[ ] 
		[ ] //------------
		[+] VOID Step (STRING sLog) //Used for output cases setp 
			[ ] prINT("==={sLog}")
			[ ] ListAppend(lsLog,"==={sLog}")
			[ ] 
		[ ] 
		[ ] //------------
		[+] VOID Message (STRING sLog) //Used for output comman message
			[+] if(gbDisplayMessage==TRUE)
				[ ] prINT(">>>{sLog}")
		[ ] 
		[ ] //------------
		[+] VOID ManualCheck (ANYTYPE sLog) //Used for manual check
			[+] if(gbDisplayManualCheck==TRUE)
				[+] if(TypeOf(sLog)==list of string)
					[ ] LIST OF STRING lsLog=sLog
					[ ] INT i=-1
					[+] for(i=1;i<=ListCount(lsLog);i++)
						[ ] prINT("@@@{lsLog[i]}")
				[+] else
					[ ] LogWarning("@@@{sLog}")
				[ ] 
			[ ] Case.sStatus=MANUALCHECK
			[ ] 
	[ ] 
	[ ] window wcLog Log
[ ] 
[ ] 
[+] //Dir
	[+] winclass wcDir
		[+] BOOLEAN New(STRING sDir, BOOLEAN bOver optional)
			[+] //Description
				[ ] //--------------------------------------------------------------------------------------------
				[ ] //Function:			Creat a floder, if it has exists then delete and make new
				[ ] //Author: 			Danny.Wang
				[ ] //Date: 				May 26,2008
				[ ] //Usage Scope: 	Creat a foler whenever it has exists
				[ ] //Pre: 				It is a globle funtion, and no specific window is needed before using it.
				[ ] //Post: 				A specified folder is created and retern a STRING holding the path of the new created folder.
				[ ] //--------------------------------------------------------------------------------------------
			[+] if(bOver==NULL)
				[ ] bOver=TRUE
			[+] // if(right(sDir,1)!="\")
				[ ] // sDir+="\"
			[ ] 
			[ ] // print(SYS_DirExists(sDir))
			[+] if(SYS_DirExists(sDir)&&!bOver)
				[ ] return TRUE
			[+] else if(SYS_DirExists(sDir)&&bOver)
				[ ] SYS_EXECUTE("rmdir /S /Q ""{sDir}""")
				[ ] int i=0
				[+] while SYS_DirExists(sDir)
					[ ] sleep(2)
					[ ] i+=1
					[+] if i>20 
						[ ] Log.Fail("Delete dir <{sDir}> failed!")
						[ ] break
				[ ] sleep(1)
				[ ] // print("come delete")
				[ ] 
			[ ] //Comment by Danny.Wang on Mar 04, 2009
			[ ] // int CreateLoop=0
			[+] // while CreateLoop<5
				[ ] // // print("Come create")
				[ ] // glSYS_MakeDirDirect(sDir)
				[ ] // i=0
				[+] // while !SYS_DirExists(sDir)
					[ ] // sleep(1)
					[ ] // i+=1
					[+] // if i>20
						[ ] // Log.Fail("Create dir <{sDir}> failed!")
						[ ] // break
				[+] // if( SYS_DirExists(sDir))
					[ ] // break
				[ ] // CreateLoop++
			[ ] // sleep(1)
			[ ] //@@@@@@@@@@@@@@@
			[ ] glSYS_MakeDirDirect(sDir)
			[ ] return TRUE
		[ ] 
		[+] VOID Delete(STRING sDir)
			[+] if(SYS_DirExists(sDir))
				[+] do 
					[ ] SYS_RemoveDir(sDir)
				[+] except
					[ ] SYS_EXECUTE("rmdir /S /Q ""{sDir}""")
				[ ] sleep(2)
			[+] if (SYS_DirExists(sDir))
				[ ] SYS_EXECUTE("rmdir /S /Q ""{sDir}""")
		[ ] 
		[+] VOID Copy(STRING sFromDir,STRING sToDir,BOOLEAN bMakeDir optional)
			[ ] 
			[+] if (bMakeDir == NULL)
				[ ] bMakeDir = true
			[+] if (!SYS_DirExists(sFromDir))
				[ ] RaiseError(-3,"Directory '{sFromDir}' is not exists!")
			[+] if (!SYS_DirExists(sToDir))
				[+] if (!bMakeDir)
					[ ] RaiseError(-3,"Directory '{sToDir}' is not exists!")
				[+] else
					[ ] glSYS_MakeDirDirect(sToDir)
			[ ] sFromDir = Trim(sFromDir)
			[ ] sToDir = Trim(sToDir)
			[+] if (Right(sFromDir,1) == "\")
				[ ] sFromDir = SubStr(sFromDir,1,Len(sFromDir)-1)
			[+] if (Right(sToDir,1) == "\")
				[ ] sToDir = SubStr(sToDir,1,Len(sToDir)-1)
			[ ] LIST OF FILEINFO lfContents= SYS_GetDirContents(sFromDir)
			[ ] FILEINFO fItem
			[+] for each fItem in lfContents
				[+] if (fItem.bIsDir)
					[ ] this.Copy(sFromDir+"\"+fItem.sName,sToDir+"\"+fItem.sName,true)
				[+] else
					[+] if(SYS_FILEEXISTS(sToDir+"\"+fItem.sName))
						[ ] SYS_REMOVEFILE(sToDir+"\"+fItem.sName)
						[ ] int i=0
						[+] while !SYS_FILEEXISTS(sToDir+"\"+fItem.sName)
							[ ] sleep(1)
							[ ] i+=1
							[+] if i>20 
								[ ] Log.Fail("Create file <{sToDir}\{fItem.sName}> failed!")
								[ ] break
						[ ] sleep(1)
					[ ] SYS_CopyFile(sFromDir+"\"+fItem.sName,sToDir+"\"+fItem.sName)
			[ ] 
	[ ] window wcDir Dir
[ ] 
[+] //File
	[+] winclass cwFile
		[+] BOOLEAN Exists (STRING sDir)
			[+] if(SYS_FILEEXISTS(sDir))
				[ ] return TRUE
			[+] else
				[ ] return FALSE
		[ ] 
		[+] VOID New (STRING sDir,LIST OF STRING lsContents)
			[ ] HFILE hFile,hBLFile
			[ ] INT i
			[ ] 
			[+] if(SYS_FILEEXISTS(sDir))
				[ ] SYS_REMOVEFILE(sDir)
			[ ] 
			[ ] hFile=SYS_FILEOPEN(sDir,FM_APPEND)
			[ ] 
			[+] for(i=1;i<listcount(lsContents)+1;i++)
				[ ] SYS_FILEWRITELINE(hFile,lsContents[i])
			[ ] 
			[ ] SYS_FILECLOSE(hFile)
			[ ] 
		[ ] 
		[+] VOID Create (STRING sDir)
			[ ] HFILE hFile,hBLFile
			[ ] INT i
			[ ] 
			[+] if(SYS_FILEEXISTS(sDir))
				[ ] exit
			[ ] 
			[ ] hFile=SYS_FILEOPEN(sDir,FM_APPEND)
			[ ] 
			[ ] SYS_FILECLOSE(hFile)
			[ ] 
		[ ] 
		[+] VOID MultiDelete (LIST OF STRING lsDir)
			[ ] INT iCout=-1
			[ ] INT i
			[ ] 
			[+] for(i=1;i<=listcount(lsDir);i++)
				[+] if(SYS_FILEEXISTS(lsDir[i]))
					[ ] SYS_REMOVEFILE(lsDir[i])
				[+] else
					[ ] Log.Fail("File <{lsDir[i]}> is not exists, please check it!")
		[ ] 
		[+] VOID Delete (STRING sDir)
			[+] if(SYS_FILEEXISTS(sDir))
				[ ] SYS_REMOVEFILE(sDir)
			[+] // else
				[ ] // Log.Fail("File <{sDir}> is not exists, please check it!")
		[ ] 
		[+] VOID Copy (STRING sCopyFrom,STRING sCopyTo)
			[ ] STRING sFileName=glGetReverseField(sCopyFrom,"\",1)
			[+] if(SYS_FILEEXISTS(sCopyFrom)&&SYS_DirEXISTS(sCopyTo))
				[+] if(SYS_FILEEXISTS("{sCopyTo}\{sFileName}"))
					[ ] SYS_RemoveFile("{sCopyTo}\{sFileName}")
				[ ] SYS_COPYFILE(sCopyFrom,"{sCopyTo}\{sFileName}")
			[+] else if(!SYS_FILEEXISTS(sCopyFrom))
				[ ] Log.Fail("File <{sCopyFrom} >is not exists, please check it!")
			[+] else
				[ ] Log.Fail("Dir <{sCopyTo}> is not exists, please check it!")
			[ ] 
		[ ] 
		[+] LIST OF STRING Read (STRING sDir)
			[ ] HFILE hFile,hBLFile
			[ ] INT i
			[ ] LIST OF STRING lsContents
			[ ] STRING sLine
			[ ] 
			[+] if(!SYS_FILEEXISTS(sDir))
				[ ] Log.Fail("File <{sDir}> is not exists, please check it!")
				[ ] return lsContents
			[ ] 
			[ ] hFile=SYS_FILEOPEN(sDir,FM_READ)
			[ ] 
			[+] while(SYS_FILEREADLINE(hFile,sLine))
				[ ] listappend(lsContents,sLine)
			[ ] 
			[ ] SYS_FILECLOSE(hFile)
			[ ] 
			[ ] return lsContents
			[ ] 
		[ ] 
		[+] VOID Write (LIST OF STRING lsContents)
			[ ] 
		[ ] 
		[+] VOID MergeList (STRING sDir,LIST OF STRING lsContents)
			[ ] HFILE hFile,hBLFile
			[ ] INT i
			[ ] 
			[+] if(!SYS_FILEEXISTS(sDir))
				[ ] Log.Fail("File <{sDir}> is not exists, please check it!")
				[ ] exit
			[ ] 
			[ ] hFile=SYS_FILEOPEN(sDir,FM_APPEND)
			[ ] 
			[ ] SYS_FILEWRITELINE(hFile,Chr(10))
			[+] for(i=1;i<listcount(lsContents)+1;i++)
				[ ] SYS_FILEWRITELINE(hFile,lsContents[i])
			[ ] 
			[ ] SYS_FILECLOSE(hFile)
		[ ] 
		[+] VOID Append (STRING sDir,STRING sContents)
			[ ] HFILE hFile,hBLFile
			[ ] INT i
			[ ] 
			[+] if(!SYS_FILEEXISTS(sDir))
				[ ] Log.Fail("File <{sDir}> is not exists, please check it!")
				[ ] exit
			[ ] 
			[ ] hFile=SYS_FILEOPEN(sDir,FM_APPEND)
			[ ] 
			[ ] SYS_FILEWRITELINE(hFile,sContents)
			[ ] 
			[ ] SYS_FILECLOSE(hFile)
		[ ] 
		[+] VOID AppendList (STRING sDir,LIST OF STRING lsContents)
			[ ] HFILE hFile,hBLFile
			[ ] INT i
			[ ] 
			[+] // if(!SYS_FILEEXISTS(sDir))
				[ ] // Log.Fail("File <{sDir}> is not exists, please check it!")
				[ ] // exit
			[ ] 
			[ ] hFile=SYS_FILEOPEN(sDir,FM_APPEND)
			[ ] 
			[+] for(i=1;i<listcount(lsContents)+1;i++)
				[ ] SYS_FILEWRITELINE(hFile,lsContents[i])
			[ ] SYS_FILEWRITELINE(hFile,Chr(10))
			[ ] 
			[ ] SYS_FILECLOSE(hFile)
			[ ] 
		[ ] 
		[+] BOOLEAN VerifyText (STRING sDir,STRING sVerify)
			[ ] HFILE hFile
			[ ] STRING sLine
			[ ] INT i
			[ ] BOOLEAN bFlag=FALSE
			[ ] 
			[ ] hFile=SYS_FILEOPEN(sDir,FM_READ)
			[ ] 
			[+] while(SYS_FILEREADLINE(hFile,sLine))
				[+] // for(i=0;i<listcount(lsVerify);i++)
					[+] if(MatchStr("*{sVerify}*",sLine))
						[ ] Log.Pass("Verify <{sVerify}> exists in file <{sDir}> successfully!")
						[ ] bFlag=TRUE
						[ ] 
			[ ] 
			[ ] SYS_FILECLOSE(hFile)
			[ ] return bFlag
			[ ] 
			[+] // for(i=0;i<listcount(lbFlag);i++)
				[+] // if(lbFlag[i]==false)
					[ ] // 
		[ ] 
		[+] VOID VerifyResults(STRING sDir,LIST of  STRING sVerify)
			[ ] HFILE hFile
			[ ] STRING sLine
			[ ] INT i
			[ ] INT findresults=0
			[ ] 
			[ ] hFile=SYS_FILEOPEN(sDir,FM_READ)
			[ ] 
			[+] while(SYS_FILEREADLINE(hFile,sLine))
				[+] for(i=0;i<listcount(sVerify);i++)
					[+] if(MatchStr("*{sVerify[i+1]}*",sLine))
						[ ] Log.Pass("Verify <{sVerify[i+1]}> exists in file <{sDir}> successfully!")
						[ ] findresults++
			[+] if(findresults<listcount(sVerify))
				[ ] Log.Fail("Verify failed!!! Please check the above information")
			[ ] 
			[ ] SYS_FILECLOSE(hFile)
			[ ] 
			[ ] 
		[ ] 
		[+] BOOLEAN Compare (STRING sBaselineDir,STRING sDir, BOOLEAN bDisplayMessage optional, STRING sOmmit optional)
			[ ] HFILE hFile,hBLFile
			[ ] STRING sLine
			[ ] LIST OF STRING lsContents,lsBLContents
			[ ] INT i
			[ ] BOOLEAN bFlag=true
			[ ] 
			[+] if(!SYS_FILEEXISTS(sDir))
				[ ] Log.Fail("File <{sDir}> is not exists, please check it!")
				[ ] exit
			[+] if(!SYS_FILEEXISTS(sBaselineDir))
				[ ] Log.Fail("File <{sBaselineDir}> is not exists, please check it!")
				[ ] exit
			[+] if(sOmmit==NULL)
				[ ] sOmmit="secs"
				[ ] 
			[+] if bDisplayMessage==NULL
				[ ] bDisplayMessage=TRUE
			[ ] 
			[ ] hFile=SYS_FILEOPEN(sDir,FM_READ)
			[ ] hBLFile=SYS_FILEOPEN(sBaselineDir,FM_READ)
			[ ] 
			[+] while(SYS_FILEREADLINE(hFile,sLine))
				[ ] listappend(lsContents,sLine)
			[ ] // listprINT(lsContents)
			[ ] 
			[+] while(SYS_FILEREADLINE(hBLFile,sLine))
				[ ] listappend(lsBLContents,sLine)
			[ ] // prINT("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@")
			[ ] // listprINT(lsBLContents)
			[ ] 
			[+] for(i=0;i<listcount(lsContents);i++)
				[+] if(trim(lsContents[i+1])!=trim(lsBLContents[i+1])&&!MatchStr("*{sOmmit}*",lsContents[i+1]))
					[ ] // if(lsContents[i+1]!=lsBLContents[i+1]&&!MatchStr("*{sOmmit}*",lsContents[i+1]))
					[+] if bDisplayMessage
						[ ] Log.Error("Compare file <{sDir}> line <{i+1}>failed:")
						[ ] Log.WarningMessage("Baseline:	<{lsBLContents[i+1]}>")
						[ ] Log.WarningMessage("Acutal:	<{lsContents[i+1]}>")
						[ ] Log.WarningMessage("please check it!")
					[ ] bFlag=false
				[+] else if(lsContents[i+1]!=lsBLContents[i+1]&&MatchStr("*{sOmmit}*",lsContents[i+1]))
					[ ] //Log.Warning("Baseline file is <{lsBLContents[i+1]}>,but realize file is <{lsContents[i+1]}>, please check it!")
					[ ] bFlag=TRUE
			[ ] 
			[+] if(bFlag==TRUE&&bDisplayMessage)
				[ ] Log.Pass("Compare file <{sDir}> and <{sBaselineDir}> successfully! ")
			[ ] 
			[ ] SYS_FILECLOSE(hFile)
			[ ] SYS_FILECLOSE(hBLFile)
			[ ] 
			[ ] return bFlag
		[ ] 
		[+] VOID VerifyEixsts (LIST OF STRING lsDir)
			[+] if(listcount(lsDir)==0)
				[ ] Log.Error("Parameter <{lsDir}> for  function <VerifyEixsts> is null, please check it!")
			[+] else
				[ ] INT iLoop=-1
				[ ] 
				[+] for(iLoop=1;iLoop<=ListCount(lsDir);++iLoop)
					[+] if(SYS_FILEEXISTS(lsDir[iLoop]))
						[ ] Log.Pass("Verify file <{lsDir[iLoop]}> exists successfully!")
					[+] else
						[ ] Log.Fail("Can't find file <{lsDir[iLoop]}>, please check it!")
		[ ] 
		[+] BOOLEAN VerifyByTool (STRING sBaselineDir,STRING sDir, STRING sMessage optional)
			[+] if(!SYS_FileExists(sBaselineDir))
				[ ] Log.Error("Can't find the file <{sBaselineDir}>, please check it!")
				[ ] return FALSE
			[+] if(!SYS_FileExists(sDir))
				[ ] Log.Error("Can't find the file <{sDir}>, please check it!")
				[ ] return FALSE
			[ ] 
			[+] // if(sMessage==NULL||sMessage=="")
				[ ] // sMessage="Verify file <{sDir}>"
			[ ] Case.sStatus=MANUALCHECK
			[ ] 
			[ ] //ExceptClear()
			[ ] SYS_VerifyText(sBaselineDir,sDir )
			[+] // if(GetTestCaseErrorCount()==0)
				[ ] // Log.Pass("{sMessage} successfully!")
			[+] // else
				[ ] // Log.Fail("{sMessage} failed, please check it!>")
			[ ] 
			[ ] return TRUE
		[ ] 
		[+] VOID Verify (STRING sDir,STRING sBaselineDir, STRING sVerifyMsg optional)
			[+] if(!Compare(sDir,sBaselineDir,FALSE))
				[ ] Case.sStatus=MANUALCHECK
				[ ] this.VerifyByTool(sDir,sBaselineDir) 
			[+] else
				[ ] Log.Pass(sVerifyMsg+" successfully!")
		[ ] 
		[+] VOID VerifyFileSize (STRING sDir, STRING sFileName, STRING sExpectSize, STRING sVerifyMsg optional)
			[ ] LIST OF FILEINFO lfInfo
			[ ] INT i=-1
			[ ] INT iSize=-1
			[ ] INT Size=-1
			[ ] LIST OF STRING lsSize={}
			[ ] 
			[+] if sVerifyMsg==NULL
				[ ] sVerifyMsg="Verify file <"+sDir+"\"+sFileName+">'s size"
			[ ] lfInfo=SYS_GetDirContents(sDir)
			[+] for(i=1;i<ListCount(lfInfo)+1;++i)
				[+] if lfInfo[i].sName==sFileName
					[ ] iSize=lfInfo[i].iSize
					[ ] 
			[+] if iSize==-1
				[ ] Log.Error("File <"+sDir+"\"+sFileName+"> is not found, please check it!")
				[ ] return
			[+] if UPPER(Right(sExpectSize,1))=="K"
				[ ] Size=val(Left(sExpectSize,Len(sExpectSize)-1))*1024
			[+] else if UPPER(Right(sExpectSize,1))=="M"
				[ ] Size=val(Left(sExpectSize,Len(sExpectSize)-1))*1024*1024
			[+] else if UPPER(Right(sExpectSize,1))=="G"
				[ ] Size=val(Left(sExpectSize,Len(sExpectSize)-1))*1024*1024*1024
			[ ] // lsSize=Str.Split(sExpectSize,"+") 
			[+] if iSize>Size //val(lsSize[1])-val(lsSize[2])&&iSize<val(lsSize[1])+val(lsSize[2])
				[ ] Log.Pass(sVerifyMsg+" successfully!")
			[+] else
				[ ] Log.Fail(sVerifyMsg+" failed, please check it!")
	[ ] 
	[ ] window cwFile File
[ ] 
[+] //Registry
	[+] winclass wcRegistry
		[ ] 
		[ ] // hidecalls STRING GetRootKey (STRING sRegistryPath)
		[+] // STRING GetKeys (STRING sRegistryPath)
			[ ] // 
		[ ] // 
		[+] // STRING NewKey (STRING sRegistryPath, STRING sKeyName)
			[ ] // 
		[ ] // 
		[+] VOID VerifyKey (LONG lRootKey, STRING sKeyPath, STRING sExpectedKeyName)
			[ ] LIST OF STRING lsKeys = Reg_EnumKeys(lRootKey, sKeyPath)
			[ ] INT iLoop
			[ ] 
			[+] for(iLoop=1;iLoop<=ListCount(lsKeys);++iLoop)
				[+] if (StrPos(Lower(sExpectedKeyName),Lower(lsKeys[iLoop])) != 0)
					[ ] Log.Pass("Verify the Key <{sExpectedKeyName}> exists under <{sKeyPath}> successfully!")
					[ ] break
				[ ] 
			[ ] 
			[+] if(iLoop>ListCount(lsKeys))
				[ ] Log.Fail("Verify the Key <{sExpectedKeyName}> exists under <{sKeyPath}> failed, please ckeck it!")
			[ ] 
		[ ] 
		[+] VOID VerifyKeyAndValue (LONG lRootKey, STRING sKeyPath, STRING sExpectedKeyName, STRING sExpectedKeyValue)
			[ ] LIST OF REGVALUE lsValues = Reg_EnumValues(lRootKey, sKeyPath)
			[ ] INT iLoop
			[ ] 
			[+] for(iLoop=1;iLoop<=ListCount(lsValues);++iLoop)
				[+] if (StrPos(Lower(sExpectedKeyName),Lower(lsValues[iLoop].sValueName)) != 0)
					[+] if(StrPos(Lower(sExpectedKeyValue),Lower(lsValues[iLoop].sValueData)) != 0)
						[ ] Log.Pass("Verify the Key <{sExpectedKeyName}>'s value under <{sKeyPath}> successfully!")
						[ ] break
					[+] else
						[ ] Log.Fail("Verify the Key <{sExpectedKeyName}> failed, Expected value: <{sExpectedKeyValue}>, Actual value: <{lsValues[iLoop].sValueData}>, please ckeck it!")
						[ ] break
				[ ] 
			[ ] 
			[+] if(iLoop>ListCount(lsValues))
				[ ] Log.Fail("Can't find the key <{sExpectedKeyName}> in <{sKeyPath}>, please check it!")
	[ ] 
	[ ] window wcRegistry Registry
[ ] 
[+] //STRING
	[+] winclass wcString
		[+] LIST OF STRING Split (STRING sStr, STRING sDelim)
			[ ] return glCastStrToList(sStr,sDelim)
    
		[ ] 
		[+] STRING Transfer (STRING sStr)
			[+] if(glsLanguage=="Germany")
				[ ] return strtran(sStr,",",".")
			[+] if(glsLanguage=="Chinese"&&val(sStr)<1)
				[ ] return strtran(sStr,"0.",".")
			[+] else
				[ ] return sStr
		[ ] 
		[+] STRING GetField (STRING sStr, STRING sDelim, INT iField)
			[ ] LIST OF STRING lsItem=this.split(sStr,sDelim)
			[+] if(iField>0)
				[ ] return lsItem[iField]
			[+] else if(iField<0)
				[ ] return lsItem[ListCount(lsItem)+iField+1]
			[+] else
				[ ] Log.Error("The field index can't be <0>!")
			[ ] 
		[ ] 
		[+] BOOLEAN Find (LIST OF STRING lsStr, STRING sItem, BOOLEAN bDisplayErrorMessage optional)
			[+] if(bDisplayErrorMessage==NULL)
				[ ] bDisplayErrorMessage=TRUE
			[+] if(ListCount(lsStr)==0&&bDisplayErrorMessage)
				[ ] Log.Error("The list is null as parameter for Str.Find function, please check it!")
				[ ] return FALSE
				[ ] 
			[+] if(glListMatch(lsStr,sItem)==0)
				[ ] return FALSE
				[ ] 
			[+] else
				[ ] return TRUE
		[ ] 
		[+] LIST OF STRING UpperList(LIST OF STRING lsStr, BOOLEAN bDisplayErrorMessage optional)
			[ ] INT iLoop=-1
			[ ] LIST OF STRING lsRes
			[ ] 
			[+] if(bDisplayErrorMessage==NULL)
				[ ] bDisplayErrorMessage=TRUE
			[+] if(ListCount(lsStr)==0&&bDisplayErrorMessage)
				[ ] Log.Error("The list is null, please check it!")
				[ ] 
			[+] else
				[+] for(iLoop=1;iLoop<=ListCount(lsStr);++iLoop)
					[ ] ListAppend(lsRes,upper(lsStr[iLoop]))
					[ ] 
			[ ] return lsRes
		[ ] 
		[+] VOID ListUnique (inout LIST OF STRING lsStr, BOOLEAN bDisplayErrorMessage optional)
			[ ] INT iStart=-1
			[ ] INT iSearch=-1
			[ ] 
			[+] if(bDisplayErrorMessage==NULL)
				[ ] bDisplayErrorMessage=TRUE
			[ ] 
			[+] if(ListCount(lsStr)==0)
				[ ] Log.Error("The list is null, please check it!")
				[ ] return
				[ ] 
			[ ] 
			[+] for(iStart=1;iStart<=ListCount(lsStr);++iStart)
				[+] for(iSearch=iStart+1;iSearch<=ListCount(lsStr);++iSearch)
					[+] if(lsStr[iStart]==lsStr[iSearch])
						[ ] ListDelete(lsStr,iSearch)
						[ ] 
			[+] // for (iToRead = 2;iToRead <= ListCount(In);iToRead++)
				[+] // if (In[iToRead] == In[iUniqued])
					[ ] // ListDelete(In,iToRead)
					[ ] // iToRead--
				[+] // else
					[ ] // iUniqued = iToRead
			[ ] 
		[ ] 
		[+] BOOLEAN CompareList (LIST OF STRING lsBaseline, LIST OF STRING lsActual)
			[ ] INT iLen=-1,iLoop=-1
			[ ] INT iLen1=listcount(lsBaseline)
			[ ] INT iLen2=listcount(lsActual)
			[ ] BOOLEAN bRes=TRUE
			[ ] 
			[+] if(iLen1!=iLen2)
				[ ] Log.Warning("the two list's count is not equal, please check it!")
				[ ] listprint(lsBaseline)
				[ ] print("-------------------------------------")
				[ ] listprint(lsActual)
			[ ] iLen=iLen1>iLen2 ? iLen2 : iLen1
			[+] for(iLoop=1;iLoop<=iLen;++iLoop)
				[+] if(lsBaseline[iLoop]!=lsActual[iLoop])
					[ ] Log.Warning("Line <{iLoop}>:Expected is <{lsBaseline[iLoop]}>, Actual is <{lsActual[iLoop]}>")
					[ ] bRes=FALSE
			[ ] return bRes
		[ ] 
		[+] BOOLEAN MatchList(LIST OF STRING lsSearch, LIST OF STRING lsSubSearch)
			[ ] INT iLen1=-1
			[ ] INT iLen2=-1
			[ ] INT iLoop=-1
			[ ] INT iLoopIn=-1
			[ ] BOOLEAN bRes=TRUE
			[ ] 
			[ ] iLen1=ListCount(lsSearch)
			[ ] iLen2=ListCount(lsSubSearch)
			[ ] 
			[+] if(iLen1<iLen2)
				[ ] return FALSE
				[ ] 
			[ ] 
			[+] for(iLoop=1;iLoop<=iLen2;++iLoop)
					[+] if(!this.Find(lsSearch,lsSubSearch[iLoop]))
						[ ] Log.Warning("Item <{lsSubSearch[iLoop]}> is not in list, please check it!")
						[ ] bRes=FALSE
					[ ] 
			[ ] 
			[ ] return bRes
			[ ] 
		[ ] 
		[+] LIST OF STRING GetPartList (LIST OF STRING lsStr, INT iStart, INT iEnd)
			[ ] LIST OF STRING lsPartList={}
			[ ] INT iListCout=-1
			[ ] INT iLoop=-1
			[ ] 
			[ ] iListCout=ListCount(lsStr)
			[+] if(iListCout==0)
				[ ] Log.Error("List is null !")
				[ ] return lsPartList
			[+] if(iStart>0&&iEnd>0)
				[+] if(iEnd<iStart)
					[ ] Log.Error("End index must greater than start index!")
					[ ] return lsPartList
				[+] if(iEnd>iListCout)
					[ ] Log.Error("End index must lesser than list count!")
					[ ] return lsPartList
				[+] for(iLoop=iStart;iLoop<iEnd+1;++iLoop)
					[ ] ListAppend(lsPartList,lsStr[iLoop])
				[ ] return lsPartList
			[+] else if(iStart<0&&iEnd<0)
				[+] if(iEnd<iStart)
					[ ] Log.Error("End index must greater than start index!")
					[ ] return lsPartList
				[+] if(abs(iStart)>iListCout)
					[ ] Log.Error("Start index must lesser than list count!")
					[ ] return lsPartList
				[+] for(iLoop=iListCout+iStart+1;iLoop<iListCout+iEnd+2;++iLoop)
					[ ] ListAppend(lsPartList,lsStr[iLoop])
				[ ] return lsPartList
			[+] else
				[ ] Log.Error("Prameter error of function <Str.GetPartList>, Plese check it!")
	[ ] window wcString Str
[ ] 
[+] //KeyBoard
	[+] winclass wcKB
		[+] VOID PageDown (window w)
			[ ] w.WaitToExist(10)
			[ ] w.SetActive()
			[ ] w.Click(1,20,3)
			[ ] w.TypeKeys("<PgDn>")
			[ ] 
	[ ] 
	[ ] window wcKB KB
[ ] 
[+] //List
	[+] winclass wcList
		[+] BOOLEAN Find (LIST OF STRING lsStr, STRING sItem, BOOLEAN bDisplayErrorMessage optional)
			[+] if(bDisplayErrorMessage==NULL)
				[ ] bDisplayErrorMessage=TRUE
			[+] if(ListCount(lsStr)==0&&bDisplayErrorMessage)
				[ ] Log.Error("The list is null as parameter for Str.Find function, please check it!")
				[ ] return FALSE
				[ ] 
			[+] if(glListMatch(lsStr,sItem)==0)
				[ ] return FALSE
				[ ] 
			[+] else
				[ ] return TRUE
		[ ] 
		[+] LIST OF STRING UpperTo (LIST OF STRING lsStr, BOOLEAN bDisplayErrorMessage optional)
			[ ] INT iLoop=-1
			[ ] LIST OF STRING lsRes
			[ ] 
			[+] if(bDisplayErrorMessage==NULL)
				[ ] bDisplayErrorMessage=TRUE
			[+] if(ListCount(lsStr)==0&&bDisplayErrorMessage)
				[ ] Log.Error("The list is null, please check it!")
				[ ] 
			[+] else
				[+] for(iLoop=1;iLoop<=ListCount(lsStr);++iLoop)
					[ ] ListAppend(lsRes,upper(lsStr[iLoop]))
					[ ] 
			[ ] return lsRes
		[ ] 
		[+] VOID Unique (inout LIST OF STRING lsStr, BOOLEAN bDisplayErrorMessage optional)
			[ ] INT iStart=-1
			[ ] INT iSearch=-1
			[ ] 
			[+] if(bDisplayErrorMessage==NULL)
				[ ] bDisplayErrorMessage=TRUE
			[ ] 
			[+] if(ListCount(lsStr)==0)
				[ ] Log.Error("The list is null, please check it!")
				[ ] return
				[ ] 
			[ ] 
			[+] for(iStart=1;iStart<=ListCount(lsStr);++iStart)
				[+] for(iSearch=iStart+1;iSearch<=ListCount(lsStr);++iSearch)
					[+] if(lsStr[iStart]==lsStr[iSearch])
						[ ] ListDelete(lsStr,iSearch)
						[ ] 
			[+] // for (iToRead = 2;iToRead <= ListCount(In);iToRead++)
				[+] // if (In[iToRead] == In[iUniqued])
					[ ] // ListDelete(In,iToRead)
					[ ] // iToRead--
				[+] // else
					[ ] // iUniqued = iToRead
			[ ] 
		[ ] 
		[+] BOOLEAN Compare (LIST OF STRING lsBaseline, LIST OF STRING lsActual)
			[ ] INT iLen=-1,iLoop=-1
			[ ] INT iLen1=listcount(lsBaseline)
			[ ] INT iLen2=listcount(lsActual)
			[ ] BOOLEAN bRes=TRUE
			[ ] 
			[+] if(iLen1!=iLen2)
				[ ] Log.Warning("the two list's count is not equal, please check it!")
				[ ] listprint(lsBaseline)
				[ ] print("-------------------------------------")
				[ ] listprint(lsActual)
			[ ] iLen=iLen1>iLen2 ? iLen2 : iLen1
			[+] for(iLoop=1;iLoop<=iLen;++iLoop)
				[+] if(lsBaseline[iLoop]!=lsActual[iLoop])
					[ ] Log.Warning("Line <{iLoop}>:Expected is <{lsBaseline[iLoop]}>, Actual is <{lsActual[iLoop]}>")
					[ ] bRes=FALSE
			[ ] return bRes
		[ ] 
		[+] BOOLEAN Match (LIST OF STRING lsSearch, LIST OF STRING lsSubSearch, BOOLEAN bDisplayMsg optional)
			[ ] INT iLen1=-1
			[ ] INT iLen2=-1
			[ ] INT iLoop=-1
			[ ] INT iLoopIn=-1
			[ ] BOOLEAN bRes=TRUE
			[ ] 
			[ ] iLen1=ListCount(lsSearch)
			[ ] iLen2=ListCount(lsSubSearch)
			[+] if(bDisplayMsg==NULL)
				[ ] bDisplayMsg=TRUE
			[+] if(iLen1<iLen2)
				[ ] return FALSE
				[ ] 
			[ ] 
			[+] for(iLoop=1;iLoop<=iLen2;++iLoop)
					[+] if(!this.Find(lsSearch,lsSubSearch[iLoop]))
						[+] if(bDisplayMsg)
							[ ] Log.Warning("Item <{lsSubSearch[iLoop]}> is not in list, please check it!")
						[ ] bRes=FALSE
					[ ] 
			[ ] 
			[ ] return bRes
			[ ] 
		[ ] 
		[+] BOOLEAN NotMatch (LIST OF STRING lsSearch, LIST OF STRING lsSubSearch, BOOLEAN bDisplayMsg optional)
			[ ] INT iLen1=-1
			[ ] INT iLen2=-1
			[ ] INT iLoop=-1
			[ ] INT iLoopIn=-1
			[ ] BOOLEAN bRes=TRUE
			[ ] 
			[ ] iLen1=ListCount(lsSearch)
			[ ] iLen2=ListCount(lsSubSearch)
			[+] if(bDisplayMsg==NULL)
				[ ] bDisplayMsg=TRUE
			[+] if(iLen1<iLen2)
				[ ] return FALSE
				[ ] 
			[ ] 
			[+] for(iLoop=1;iLoop<=iLen2;++iLoop)
					[+] if(this.Find(lsSearch,lsSubSearch[iLoop]))
						[+] if(bDisplayMsg)
							[ ] Log.Warning("Item <{lsSubSearch[iLoop]}> exists in the list, please check it!")
						[ ] bRes=FALSE
					[ ] 
			[ ] 
			[ ] return bRes
			[ ] 
		[ ] 
		[+] LIST OF STRING GetMatch (LIST OF STRING lsSearch, LIST OF STRING lsSubSearch)
			[ ] INT iLen1=-1
			[ ] INT iLen2=-1
			[ ] INT iLoop=-1
			[ ] INT iLoopIn=-1
			[ ] LIST OF STRING lsRes={}
			[ ] BOOLEAN bRes=TRUE
			[ ] 
			[ ] iLen1=ListCount(lsSearch)
			[ ] iLen2=ListCount(lsSubSearch)
			[ ] 
			[+] // if(iLen1<iLen2)
				[ ] // return FALSE
				[ ] // 
			[ ] 
			[+] for(iLoop=1;iLoop<=iLen2;++iLoop)
					[+] for(iLoopIn=1;iLoopIn<=iLen1;++iLoopIn)
						[+] if(MatchStr("*{lsSubSearch[iLoop]}*",lsSearch[iLoopIn]))
							[ ] ListAppend(lsRes,lsSearch[iLoopIn])
			[ ] 
			[ ] return lsRes
		[ ] 
		[+] LIST OF STRING GetPart (LIST OF STRING lsStr, INT iStart, INT iEnd)
			[ ] LIST OF STRING lsPartList={}
			[ ] INT iListCout=-1
			[ ] INT iLoop=-1
			[ ] 
			[ ] iListCout=ListCount(lsStr)
			[+] if(iListCout==0)
				[ ] Log.Error("List is null !")
				[ ] return lsPartList
			[+] if(iStart>0&&iEnd>0)
				[+] if(iEnd<iStart)
					[ ] Log.Error("End index must greater than start index!")
					[ ] return lsPartList
				[+] if(iEnd>iListCout)
					[ ] Log.Error("End index must lesser than list count!")
					[ ] return lsPartList
				[+] for(iLoop=iStart;iLoop<iEnd+1;++iLoop)
					[ ] ListAppend(lsPartList,lsStr[iLoop])
				[ ] return lsPartList
			[+] else if(iStart<0&&iEnd<0)
				[+] if(iEnd<iStart)
					[ ] Log.Error("End index must greater than start index!")
					[ ] return lsPartList
				[+] if(abs(iStart)>iListCout)
					[ ] Log.Error("Start index must lesser than list count!")
					[ ] return lsPartList
				[+] for(iLoop=iListCout+iStart+1;iLoop<iListCout+iEnd+2;++iLoop)
					[ ] ListAppend(lsPartList,lsStr[iLoop])
				[ ] return lsPartList
			[+] else
				[ ] Log.Error("Prameter error of function <Str.GetPartList>, Plese check it!")
		[ ] 
		[+] VOID Clear (inout LIST OF ANYTYPE ls)
			[ ] glListClear(ls)
		[ ] 
		[+] // VOID WriteToFile(LIST OF STRING ls, STRING sFile)
			[ ] // 
	[ ] 
	[ ] window wcList StdList
[ ] 
[+] //Check
	[+] winclass wcCheck
		[ ] 
		[+] DialogBox Str
			[ ] tag ""
			[ ] 
			[ ] //method
			[+] boolean Equal(string sTest, string sExpected, string sMsg)
				[+] //@API
					[+] //[Function]
						[ ] //Compare {sTest} {sExpected}, if "EQUAL" the check point is pass and vice versa
					[+] //[Input]
						[ ] //sTest - - test string
						[ ] //sExpected - - expcted string
						[ ] //sMsg - - check point description
						[ ] 
					[ ] 
				[ ] gllog.Raw("sTest - - {sTest}")
				[ ] gllog.Raw("sExpected - - {sExpected}")
				[ ] 
				[ ] boolean b
				[+] if (sTest == sExpected)
					[ ] 
					[ ] b = true
					[ ] gllog.Pass(sMsg)
					[ ] 
				[+] else
					[ ] 
					[ ] b = false
					[ ] gllog.Fail(sMsg)
					[ ] 
				[ ] 
				[ ] return b
				[ ] 
			[ ] 
			[+] boolean Match(string sTest, string sPattern, string sMsg)
				[+] //@API
					[+] //[Function]
						[ ] //Compare {sTest} {sExpected}, if "MATCH" the check point is pass and vice versa
					[+] //[Input]
						[ ] //sTest - - test string
						[ ] //sExpected - - expcted string
						[ ] //sMsg - - check point description
						[ ] 
					[ ] 
				[ ] gllog.Raw("sTest - - {sTest}")
				[ ] gllog.Raw("sExpected - - {sPattern}")
				[ ] 
				[ ] boolean b
				[+] if (MatchStr(sPattern, sTest))
					[ ] 
					[ ] b = true
					[ ] gllog.Pass(sMsg)
					[ ] 
				[+] else
					[ ] 
					[ ] b = false
					[ ] gllog.Fail(sMsg)
					[ ] 
				[ ] 
				[ ] return b
				[ ] 
			[ ] 
			[ ] 
		[+] DialogBox Num
			[ ] tag ""
			[ ] 
			[+] void Equal(number sTest, number sExpected, string sMsg)
				[+] //@API
					[+] //[Function]
						[ ] //Compare {sTest} {sExpected}, if "EQUAL" the check point is pass and vice versa
					[+] //[Input]
						[ ] //sTest - - test number
						[ ] //sExpected - - expcted number
						[ ] //sMsg - - check point description
						[ ] 
					[ ] 
				[ ] gllog.Raw("sTest - - {sTest}")
				[ ] gllog.Raw("sExpected - - {sExpected}")
				[+] if (sTest == sExpected)
					[ ] gllog.Pass(sMsg)
					[ ] 
				[+] else
					[ ] gllog.Fail(sMsg)
					[ ] 
				[ ] 
			[ ] 
		[+] DialogBox L
			[ ] tag ""
			[ ] 
			[+] void Equal(list of string lsTest, list of string lsExpected, string sMsg)
				[+] //@API
					[+] //[Function]
						[ ] //Compare {lsTest} {lsExpected}, if "EQUAL" the check point is pass and vice versa
					[+] //[Input]
						[ ] //lsTest - - test list of string
						[ ] //lsExpected - - expcted list of string
						[ ] //sMsg - - check point description
						[ ] 
					[ ] 
				[ ] 
				[ ] integer i
				[ ] integer iMin
				[ ] 
				[ ] gllog.Raw("sTest - - {lsTest}")
				[ ] gllog.Raw("sExpected - - {lsExpected}")
				[+] if (lsTest == lsExpected)
					[ ] 
					[ ] gllog.Pass(sMsg)
					[ ] 
				[+] else
					[ ] gllog.Fail(sMsg)
					[ ] 
					[+] if (ListCount(lsTest) == ListCount(lsExpected))
						[ ] 
						[ ] gllog.LogEntity("List Count is equal {lsExpected}")
						[ ] iMin = Min(ListCount(lsTest), ListCount(lsExpected))
						[ ] 
					[+] else
						[ ] 
						[ ] gllog.Fail("List Count is different lsTest: {ListCount(lsTest)}, lsExpected: {ListCount(lsExpected)}")
						[ ] iMin = Min(ListCount(lsTest), ListCount(lsExpected))
						[ ] 
					[+] if (iMin >0)
						[ ] 
						[+] for(i=1; i<=iMin; i++)
							[ ] 
							[+] if (lsTest[i] != lsExpected[i])
								[ ] 
								[ ] gllog.Fail("lsTest[{i}]: {lsTest[i]}, lsExpected[{i}]: {lsExpected[i]}")
								[ ] 
							[ ] 
						[ ] 
					[ ] 
				[ ] 
			[ ] 
		[ ] 
		[ ] //method
		[+] void B(boolean b, string sMsg, string sErrorLevel optional)
			[+] //@API
				[+] //[Function]
					[ ] // if {b} is true the check point is pass and vice versa
				[+] //[Input]
					[ ] //b - - boolean value
					[ ] //sMsg - - check point description
					[ ] 
				[ ] 
			[ ] 
			[+] if (b)
				[ ] gllog.Pass(sMsg)
				[ ] 
			[+] else
				[ ] 
				[ ] gllog.Fail(sMsg)
				[ ] 
				[ ] 
			[ ] 
		[ ] 
		[+] void Exist(window w, real rTimeOut)
			[ ] 
			[ ] real rTime = 0
			[ ] real rStep = Agent.GetOption (OPT_WINDOW_RETRY)
			[+] if (rTimeOut  == NULL)
				[ ] rTimeOut = Agent.GetOption(OPT_WINDOW_TIMEOUT)
			[+] while(rTime <= rTimeOut)
				[+] if (w.Exists() == true)
					[ ] sleep(1)
					[ ] gllog.Pass("Object {w} is appear")
					[ ] return
					[ ] 
				[+] else
					[ ] sleep(rStep)
					[ ] rTime += rStep
					[ ] 
			[ ] gllog.Fail("Object {w} does not appear")
			[ ] 
			[ ] 
		[ ] 
		[ ] 
	[ ] 
	[ ] window wcCheck Check
	[ ] 
[ ] 
[ ] 
[ ] 
