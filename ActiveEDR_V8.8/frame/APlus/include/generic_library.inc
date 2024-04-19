[ ] //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[ ] //////////////////////////////// ! ! ! Do not modify this library yourself. Any modification request please submit to automation team ! ! ! //////////////////////////////////////////////
[ ] //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
[ ] 
[ ] // Name: the Silktest Generic Library for aspentech automation
[ ] // Version: v28.8
[ ] // Date: 2010.3.8
[ ] // Source and Doc Path:  //depot/qe/dev/AUTOMATION/generic library/
[ ] 
[ ] use "Registry.inc"
[ ] use "24hRunningByNobody.inc"
[ ] use "../frame/Settings.inc"
[ ] 
[-] //----------------------- OS const ---------------------//
	[ ] const glsAPPDATA = SYS_GetEnv ("APPDATA")
	[ ] const glsCommonProgramFiles = SYS_GetEnv ("CommonProgramFiles") 
	[ ] const glsCOMPUTERNAME	= SYS_GetEnv ("COMPUTERNAME")
	[ ] const glsHOMEDRIVE = SYS_GetEnv ("HOMEDRIVE")
	[ ] const glsHOMEPATH = SYS_GetEnv ("HOMEPATH")
	[ ] const glsSYSTEMDRIVE = SYS_GetEnv ("SYSTEMDRIVE")
	[ ] const glsSYSTEMROOT = SYS_GetEnv ("SYSTEMROOT")
	[ ] const glsWINDIR = SYS_GetEnv("WINDIR")
	[ ] const glsProgramFiles = SYS_GetEnv("ProgramFiles")
	[ ] const glsUSERNAME = SYS_GetEnv("USERNAME")
	[ ] 
	[+] const glsLanguage = getLang()
		[ ] // all available values: English, Chinese, Germany,Japanese,Korean
		[ ] // check whether the value is null to ensure no exception occur
	[+] private STRING getLang()
		[+] do
			[ ] INTEGER iKey = HKEY_LOCAL_MACHINE
			[ ] STRING strPath = "SYSTEM\ControlSet001\Control\Nls\Language"
			[ ] STRING strItem = "InstallLanguage"
			[ ] STRING strLang = SYS_GetRegistryValue(iKey, strPath, strItem)
			[+] switch strLang
				[+] case "0409"
					[ ] return "English"
				[+] case "0804"
					[ ] return "Chinese"
				[+] case "0407"
					[ ] return "Germany"
				[+] case "0411"
					[ ] return "Japanese"
				[+] case "0412"
					[ ] return "Korean"
				[+] default
					[ ] return  null
		[+] except
			[ ] return null
	[ ] 
	[+] const glsOS = getOS()
		[ ] // all available values: vista, xp, 2003
		[ ] // check whether the value is null to ensure no exception occur
	[+] private STRING getOS()
		[+] do
			[ ] INTEGER iKey = HKEY_LOCAL_MACHINE
			[ ] STRING strPath = "SOFTWARE\Microsoft\Windows NT\CurrentVersion"
			[ ] STRING strItem = "ProductName"
			[ ] STRING strOS = SYS_GetRegistryValue(iKey, strPath, strItem)
			[ ] 
			[+] if (StrPos("Windows XP",strOS) != 0)
				[ ] return "xp"
			[+] if (StrPos("Windows Vista",strOS) != 0)
				[ ] return "vista"
			[+] if (StrPos("Windows 7",strOS) != 0)
				[ ] return "7"
			[+] if (StrPos("Windows Server 2003 R2",strOS) != 0)
				[ ] return "2003 r2"
			[+] if (StrPos("Windows Server (R) 2008 R2",strOS) != 0 || StrPos ("Windows Server 2008 R2 Standard", strOS) !=0)
				[ ] return "2008 r2"
			[+] if (StrPos("Windows Server 2003",strOS) != 0)
				[ ] return "2003"
			[+] if (StrPos("Windows Server (R) 2008",strOS) != 0)
				[ ] return "2008"
			[+] if (StrPos("Windows 8", strOS) != 0)
				[ ] return "8"
			[+] if (StrPos("Windows 10 Pro", strOS) != 0)
				[ ] return "10"
			[ ] 
			[ ] return null
		[+] except
			[ ] return null
	[ ] 
	[+] const glsDriveName = getDriveName()
		[ ] // return the current driver name directory, like "Local Disk"
		[ ] // check whether the value is null to ensure no exception occur
	[+] private STRING getDriveName()
		[+] switch glsLanguage
			[+] case "English"
				[ ] return "Local Disk"
			[+] case "Chinese"
				[ ] return "本地磁盘"
			[+] case "Germany"
				[ ] return "Lokaler Datenträger"
			[+] case "Japanese"
				[ ] return "ローカル ディスク"
			[+] case "Korean"
				[ ] return "로컬 디스크"
			[+] default
				[ ] return null
	[ ] 
	[ ] // const glsALLUSERSPROFILE = GetALLUSERSPROFILE()
	[+] // private STRING GetALLUSERSPROFILE()
		[+] // switch glsOS
			[+] // case "xp"
				[ ] // return SYS_GetEnv ("ALLUSERSPROFILE")+"\Application Data" //it's a XP or 2003
			[+] // case  "2003 r2"
				[ ] // return SYS_GetEnv ("ALLUSERSPROFILE")+"\Application Data" //it's a XP or 2003
			[+] // case "2003"
				[ ] // return SYS_GetEnv ("ALLUSERSPROFILE")+"\Application Data" //it's a XP or 2003
			[+] // case "vista"
				[ ] // return SYS_GetEnv ("ALLUSERSPROFILE") //it's a Vista, Win7 or Win08server
			[+] // case "7"
				[ ] // return SYS_GetEnv ("ALLUSERSPROFILE") //it's a Vista, Win7 or Win08server
			[+] // case "2008 r2"
				[ ] // return SYS_GetEnv ("ALLUSERSPROFILE") //it's a Vista, Win7 or Win08server
			[+] // case "2008"
				[ ] // return SYS_GetEnv ("ALLUSERSPROFILE") //it's a Vista, Win7 or Win08server
			[+] // case "8"
				[ ] // return SYS_GetEnv ("ALLUSERSPROFILE")
			[+] // case "10"
				[ ] // return SYS_GetEnv ("ALLUSERSPROFILE")
			[ ] // 
[ ] 
[-] //--------------------------------------------------------------------------------- useful functions ------------------------------------------------------------------------------------------//
	[+] // Function template
		[ ] 
		[+] // StructureListSelector
			[+] boolean glStructureListSelector_Expand(window w,string sPath,string sDelim optional, string sExpandMethod optional, string sSelectMethod optional, string sFindMethod optional) // defines how to expand a "sPath" of string text from the  "StructureList", need to ensure "sPath" is expanded
				[+] do
					[ ] w.Expand(sPath)
					[ ] return true
				[+] except
					[ ] return false
			[+] boolean glStructureListSelector_Select(window w,string sPath,string sDelim optional, string sExpandMethod optional, string sSelectMethod optional, string sFindMethod optional) // defines how to select a "sPath" of string text from the "StructureList", need to ensure "sPath" is selected
				[+] do
					[ ] w.Select(sPath)
					[ ] return true
				[+] except
					[ ] return false
			[+] boolean glStructureListClicker_Click(window w,string sPath,string sDelim optional, string sExpandMethod optional, string sSelectMethod optional, string sFindMethod optional) // defines how to select a "sPath" of string text from the "StructureList", need to ensure "sPath" is selected
				[+] do
					[ ] RECT r = w.GetItemRect (sPath)
					[ ] w.Click(1,r.xPos+r.xSize/2,r.yPos+r.ySize/2,false)
					[ ] return true
				[+] except
					[ ] return false
			[+] int glStructureListSelector_Find(window w,string sPath,string sDelim optional, string sExpandMethod optional, string sSelectMethod optional, string sFindMethod optional) // defines how to find a "sPath" in the "StructureList", and return the index number, return 0 for not found
				[ ] list of string ls = w.GetContents()
				[ ] int i
				[+] for (i = 1; i <= ListCount(ls); i++)
					[+] if (ls[i] == sPath)
						[ ] return i
				[ ] return 0
			[+] boolean glStructureListSelectorTemplate(window w,string sPath,string sDelim, string sExpandMethod, string sSelectMethod, string sFindMethod)  // simply 
				[ ] string sFinding
				[ ] string sToFind
				[ ] string sFound
				[ ] sToFind = ""
				[ ] sFinding = sPath
				[ ] sFound = ""
				[ ] 
				[+] while (sFound != sFinding && sFinding != "")
					[+] if (sToFind == "")
						[+] if (@(sFindMethod)(w,sFinding,sDelim,sExpandMethod,sSelectMethod,sFindMethod) != 0)
							[+] if(@(sSelectMethod)(w,sFinding,sDelim,sExpandMethod,sSelectMethod,sFindMethod))
								[ ] sFound = sFinding
								[ ] return true
							[+] else
								[ ] return false
						[+] else
							[ ] // left move
							[ ] sToFind = sDelim + glGetReverseField(sFinding,sDelim,1)
							[ ] sFinding = left(sFinding,StrPos(sToFind,sFinding,true)-1)
					[+] else
						[+] if (@(sFindMethod)(w,sFinding,sDelim,sExpandMethod,sSelectMethod,sFindMethod) != 0)
							[+] if(@(sExpandMethod)(w,sFinding,sDelim,sExpandMethod,sSelectMethod,sFindMethod))
								[ ] // right move
								[ ] sFound = sFinding
								[ ] sFinding = sFinding + sDelim + GetField(sToFind,sDelim,2)
								[ ] sToFind = right(sToFind,Len(sToFind) - Len(GetField(sToFind,sDelim,2)) - 1)
							[+] else
								[ ] return false
						[+] else
							[ ] // left move
							[ ] sToFind = sDelim + glGetReverseField(sFinding,sDelim,1)   + sToFind
							[ ] sFinding = left(sFinding,StrPos(glGetReverseField(sFinding,sDelim,1),sFinding,true)-2)
				[ ] return false
		[ ] 
		[+] // FlatListSelector
			[+] boolean glFlatViewSelector_CascadeAll(window w,list of string lsPath optional, string sCascadeAllMethod optional, string sExpandMehod optional, string sSelectMethod optional)
				[+] do
					[ ] RECT rec
					[ ] int j
					[ ] int n
					[+] for (j = 1; j <= w.GetItemCount(); j++)
						[ ] n = w.GetItemCount()
						[ ] rec = w.GetItemRect("#{j}")
						[ ] w.MultiClick(2,1,rec.xPos+1, rec.yPos + rec.ySize/2)
						[+] if (w.GetItemCount() > n)
							[ ] w.MultiClick(2,1,rec.xPos+1, rec.yPos + rec.ySize/2)
					[ ] return true
				[+] except
					[ ] return false
			[+] boolean glFlatViewSelector_Expand(window w,string sPath optional, string sCascadeAllMethod optional, string sExpandMehod optional, string sSelectMethod optional) // bug fix
				[+] do
					[ ] int n = w.GetItemCount()
					[ ] RECT rec = w.GetItemRect(sPath)
					[ ] w.MultiClick(2,1,rec.xPos, rec.yPos + rec.ySize/2)
					[ ] return true
				[+] except
					[ ] return false
			[+] boolean glFlatViewSelector_Select(window w,string sPath optional, string sCascadeAllMethod optional, string sExpandMehod optional, string sSelectMethod optional) // bug fix
				[+] do
					[ ] int n = w.GetItemCount()
					[ ] RECT rec = w.GetItemRect(sPath)
					[ ] w.MultiClick(1,1,rec.xPos, rec.yPos + rec.ySize/2)
					[ ] return true
				[+] except
					[ ] return false
			[+] boolean glFlatViewSelectorTemplate(window w,list of string lsPath, string sCascadeAllMethod, string sExpandMehod, string sSelectMethod) // bug fix
				[+] if (@(sCascadeAllMethod)(w, lsPath, sCascadeAllMethod,sExpandMehod,sSelectMethod) == false)
					[ ] return false
				[ ] int i = 1
				[+] while(ListCount(lsPath) > i )
					[+] if (!@(sExpandMehod)(w, lsPath[i], sCascadeAllMethod,sExpandMehod,sSelectMethod))
						[ ] return false
					[ ] i+=1
				[ ] return @(sSelectMethod)(w, lsPath[ListCount(lsPath)], sCascadeAllMethod,sExpandMehod,sSelectMethod)
	[ ] 
	[+] // Addtion to 4T registry function
		[+] boolean glReg_CheckKey(long hRootKey, string sPath,string sKey)
			[ ] list of string lsKeys = Reg_EnumKeys(hRootKey, sPath)
			[ ] string temp
			[+] for each temp in lsKeys
				[+] if (StrPos(Lower(sKey),Lower(temp)) != 0)
					[ ] return true
			[ ] return false
		[ ] 
		[+] boolean glReg_CheckValue(long hRootKey, string sPath, string sValueName) 
			[ ] list of REGVALUE lsValues = Reg_EnumValues(hRootKey, sPath)
			[ ] REGVALUE temp
			[+] for each temp in lsValues
				[+] if (StrPos(Lower(sValueName),Lower(temp.sValueName)) != 0)
					[ ] return true
			[ ] return false
		[ ] 
		[+] boolean glReg_CheckKeyAll(long hRootKey, string sPath,string sKey)
			[ ] list of string lsKeys = Reg_EnumKeysAll(hRootKey, sPath)
			[ ] string temp
			[+] for each temp in lsKeys
				[+] if (StrPos(Lower(sKey),Lower(temp)) != 0)
					[ ] return true
			[ ] return false
		[ ] 
		[+] boolean glReg_CheckValueAll(long hRootKey, string sPath, string sValueName)
			[ ] list of REGVALUE lsValues = Reg_EnumValuesAll(hRootKey, sPath)
			[ ] REGVALUE temp
			[+] for each temp in lsValues
				[+] if (StrPos(Lower(sValueName),Lower(temp.sValueName)) != 0)
					[ ] return true
			[ ] return false
	[ ] 
	[+] // Addtion to 4T directory function
		[+] void glSYS_MakeDirDirect(STRING sDir)
			[+] if (!glSYS_MakeDirDirect_1(sDir) && !glSYS_MakeDirDirect_2(sDir))
				[ ] RaiseError(-255,"Exception in glSYS_MakeDirDirect")
		[ ] 
		[+] private boolean glSYS_MakeDirDirect_1(STRING sDir) // return boolean
			[ ] list of string ls
			[+] if (SYS_Execute("md ""{sDir}""",ls) != 0)
				[ ] return false
			[+] else
				[ ] return true
		[ ] 
		[+] private boolean glSYS_MakeDirDirect_2(STRING sDir) // return boolean // local only
			[ ] // make dir directly. if the parent dir is not exists, the function will make it
			[ ] // the parameter sDir must be the absolute path start with a driver letter
			[ ]  // local only
			[+] do
				[+] if (SubStr(sDir,2,2)!= ":\")
					[ ] return false
				[ ] sDir = Trim(sDir)
				[ ] list of STRING lsDirs = glCastStrToList(sDir,"\")
				[ ] int i
				[+] STRING sCurrentDir = null
					[+] for (i = 1; i <= ListCount(lsDirs);i++)
						[+] if (sCurrentDir == null)
							[ ] sCurrentDir = lsDirs[i]
						[+] else
							[ ] sCurrentDir += "\"+lsDirs[i]
						[+] if (SYS_DirExists(sCurrentDir))
							[ ] continue
						[+] else
							[ ] SYS_MakeDir(sCurrentDir)
				[ ] return true
			[+] except
				[ ] return false
		[ ] 
		[+] list of FILEINFO glSYS_GetDirContents(string sDir,int datasize NULL optional)
			[+] if (SubStr(sDir,2,1)==":")
				[ ] return SYS_GetDirContents(sDir,datasize)
			[+] else if (left(sDir,2)=="\\")
				[ ] int i
				[+] for (i = 90; i >= 67; i--)
					[+] if (SYS_DirExists("{chr(i)}:"))
						[ ] continue
					[+] else
						[ ] list of string l
						[+] if (SYS_Execute("net use {chr(i)}: ""{sDir}""",l) != 0)
							[ ] RaiseError(-255,"Exception in glSYS_GetDirContents")
						[+] else
							[ ] while (!SYS_DirExists("{chr(i)}:"))
							[ ] list of FILEINFO ls = SYS_GetDirContents("{chr(i)}:\",datasize)
							[ ] while(SYS_Execute("net use {chr(i)}: /delete",l) != 0)
							[ ] while (SYS_DirExists("{chr(i)}:"))
							[ ] return ls
			[+] else
				[ ] RaiseError(-255,"Exception in glSYS_GetDirContents")
		[ ] 
		[+] void glSYS_CopyDir(STRING sToCopy, STRING sToCopyTo, boolean bMakeDir optional)
			[ ] // eg:
			[ ] // copy c:\SrcDir    to     d:\TgtDir
			[ ] // SYS_CopyDir("c:\SrcDir","d:\TrgDir")
			[ ] // then all contents under c:\SrcDir copy to d:\TrgDir
			[ ] // bMakeDir is use to control whether the target dir should be created automatically, default false
			[+] if (bMakeDir == null)
				[ ] bMakeDir = false
			[+] if (!SYS_DirExists(sToCopy))
				[ ] RaiseError(-255,"Exception in glSYS_CopyDir")
			[+] if (!SYS_DirExists(sToCopyTo))
				[+] if (!bMakeDir)
					[ ] RaiseError(-255,"Exception in glSYS_CopyDir")
				[+] else
					[ ] glSYS_MakeDirDirect(sToCopyTo)
			[ ] sToCopy = Trim(sToCopy)
			[ ] sToCopyTo = Trim(sToCopyTo)
			[+] if (Right(sToCopy,1) == "\")
				[ ] sToCopy = SubStr(sToCopy,1,Len(sToCopy)-1)
			[+] if (Right(sToCopyTo,1) == "\")
				[ ] sToCopyTo = SubStr(sToCopyTo,1,Len(sToCopyTo)-1)
			[ ] list of FILEINFO lfContents= glSYS_GetDirContents(sToCopy)
			[ ] FILEINFO fItem
			[+] for each fItem in lfContents
				[+] if (fItem.bIsDir)
					[ ] glSYS_CopyDir(sToCopy+"\"+fItem.sName,sToCopyTo+"\"+fItem.sName,true)
				[+] else
					[ ] SYS_CopyFile(sToCopy+"\"+fItem.sName,sToCopyTo+"\"+fItem.sName)
		[ ] 
		[+] void glSYS_ClearDir(STRING sDir, boolean bContainsSubDir optional, boolean bKeepSubDir optional)
			[+] if (!glSYS_ClearDir_1(sDir, bContainsSubDir, bKeepSubDir) && !glSYS_ClearDir_2(sDir, bContainsSubDir, bKeepSubDir))
				[ ] RaiseError(-255,"Exception in glSYS_ClearDir")
		[ ] 
		[+] private boolean glSYS_ClearDir_1(STRING sDir, boolean bContainsSubDir optional, boolean bKeepSubDir optional) // return boolean
			[ ] // clear all the files and folds in the sDir, but remain sDir
			[+] if (bContainsSubDir == null)
				[ ] bContainsSubDir = false
			[+] if (bKeepSubDir == null)
				[ ] bKeepSubDir = true
			[+] if (!SYS_DirExists(sDir))
				[ ] return false
			[ ] sDir = Trim(sDir)
			[ ] list of FILEINFO lfContents= glSYS_GetDirContents(sDir)
			[ ] FILEINFO fItem
			[ ] list of string ls
			[+] for each fItem in lfContents
				[+] if (fItem.bIsDir)  // is a directory
					[+] if (bContainsSubDir)  // whether to clear the sub directory
						[ ] glSYS_ClearDir(sDir+"\"+fItem.sName,bContainsSubDir,bKeepSubDir)
						[+] if (!bKeepSubDir)
							[+] if (SYS_Execute("rd "+""""+sDir+"\"+fItem.sName+"""",ls) != 0)
								[ ] return false
				[+] else
					[+] if (SYS_Execute("attrib -s -r -h -a "+""""+sDir+"\"+fItem.sName+"""",ls) != 0)
						[ ] return false
					[+] if (SYS_Execute("del /F /Q "+""""+sDir+"\"+fItem.sName+"""",ls) != 0)
						[ ] return false
			[ ] return true
		[ ] 
		[+] private boolean glSYS_ClearDir_2(STRING sDir, boolean bContainsSubDir optional, boolean bKeepSubDir optional) // return boolean
			[ ] // clear all the files and folds in the sDir, but remain sDir
			[+] do
				[+] if (bContainsSubDir == null)
					[ ] bContainsSubDir = false
				[+] if (bKeepSubDir == null)
					[ ] bKeepSubDir = true
				[+] if (!SYS_DirExists(sDir))
					[ ] return false
				[ ] sDir = Trim(sDir)
				[ ] list of FILEINFO lfContents= glSYS_GetDirContents(sDir)
				[ ] FILEINFO fItem
				[+] for each fItem in lfContents
					[+] if (fItem.bIsDir)  // is a directory
						[+] if (bContainsSubDir)  // whether to clear the sub directory
							[ ] glSYS_ClearDir(sDir+"\"+fItem.sName,bContainsSubDir,bKeepSubDir)
							[+] if (!bKeepSubDir)
								[ ] SYS_RemoveDir(sDir+"\"+fItem.sName)
					[+] else
						[ ] SYS_RemoveFile(sDir+"\"+fItem.sName)
				[ ] return true
			[+] except
				[ ] return false
		[ ] 
		[+] list of STRING  glSYS_SearchFile(STRING sSrhDir, STRING sPattern optional, boolean bContainsSubDir optional)
			[ ] // find all files whose file name matched sPattern under sDir, ignore case
			[ ] // return the expected file path
			[+] if (SubStr(sSrhDir,2,1)==":")
				[+] if(right(sSrhDir,1) == ":")
					[ ] sSrhDir += "\"
				[+] if (sPattern == null)
					[ ] sPattern = "*"
				[+] if (bContainsSubDir == null)
					[ ] bContainsSubDir = false
				[+] if (!SYS_DirExists(sSrhDir))
					[ ] RaiseError(-255,"Exception in glSYS_SearchFile")
				[ ] sSrhDir = Trim(sSrhDir)
				[ ] list of STRING lsResult
				[ ] list of FILEINFO lfContents = glSYS_GetDirContents(sSrhDir)
				[ ] FILEINFO fItem
				[+] for each fItem in lfContents
					[+] if (fItem.bIsDir)  // is a directory
						[+] if (bContainsSubDir)  // whether to clear the sub directory
							[ ] ListMerge(lsResult,(glSYS_SearchFile((right(sSrhDir,1)=="\"?sSrhDir:(sSrhDir+"\"))+fItem.sName,sPattern,true)))
					[+] else
						[+] if (MatchStr(lower(sPattern),lower(fItem.sName)))
							[ ] ListAppend(lsResult,(right(sSrhDir,1)=="\"?sSrhDir:(sSrhDir+"\"))+fItem.sName)
				[ ] return lsResult
			[+] else if (left(sSrhDir,2)=="\\")
				[ ] int i
				[+] for (i = 90; i >= 67; i--)
					[+] if (SYS_DirExists("{chr(i)}:"))
						[ ] continue
					[+] else
						[ ] list of string l
						[+] if (right(sSrhDir,1) == "\")
							[ ] sSrhDir = SubStr(sSrhDir,1,len(sSrhDir)-1)
						[+] if (SYS_Execute("net use {chr(i)}: ""{sSrhDir}""",l) != 0)
							[ ] RaiseError(-255,"Exception in glSYS_SearchFile")
						[+] else
							[ ] while (!SYS_DirExists("{chr(i)}:"))
							[ ] list of string lsReturn
							[ ] string sReplaceTo = right(sSrhDir,1) == "\"? sSrhDir:(sSrhDir + "\")
							[ ] list of string ls = glSYS_SearchFile("{chr(i)}:\",sPattern,bContainsSubDir)
							[ ] string s
							[+] for each s in ls
									[ ] ListAppend(lsReturn,StrTran(s,"{chr(i)}:\",sReplaceTo))
							[ ] while(SYS_Execute("net use {chr(i)}: /delete",l) != 0)
							[ ] while (SYS_DirExists("{chr(i)}:"))
							[ ] return lsReturn
			[+] else
				[ ] RaiseError(-255,"Exception in glSYS_SearchFile")
	[ ] 
	[+] // Addtion to 4T string function
		[+] STRING glGetReverseField(STRING sString,STRING sDelim,int iField)
			[ ] list of STRING lsFields = glCastStrToList (sString,sDelim)
			[+] if (iField > ListCount(lsFields))
				[ ] RaiseError(-255,"Exception in glGetReverseField")
			[ ] return lsFields[ListCount(lsFields)-iField+1]
		[ ] 
		[+] LIST of STRING glCastStrToList( STRING sString, STRING sDelim)
			[ ] //---------------------------------------------------------------------------------
			[ ] // Author: Rajashri Ranadive
			[ ] // Date:   Feb 27, 2005
			[ ] 
			[ ] // Convert a string of fields separated by a delimiter into a list of string
			[ ] // Example: "abcd|efghij|klm" is converted as {"abcd", "efghij", "klm"}
			[ ] //
			[ ] // Input: 
			[ ] //			sSTRING:	String containing text separated by delimiter
			[ ] //			sDelim:		Delimiter separating the text ("|" in the example)
			[ ] //
			[ ] // Output:	Converted list
			[ ] //
			[ ] // Pre:		Text should be separated by specifid delimiter
			[ ] //---------------------------------------------------------------------------------
			[ ] 
			[ ] // List to be returned
			[ ] LIST of STRING lsReturn = {}
			[ ] 
			[ ] // Each character of the input string
			[ ] STRING  sChar
			[ ] 
			[ ] // Substring between two delimeters
			[ ] STRING  sWord = ""
			[ ] 
			[ ] // Current Character count
			[ ] INT iChar = 0
			[ ] 
			[ ] // Length of the string
			[ ] INT iLen = 0
			[ ] 
			[ ] iLen = Len(sString)
			[ ] sWord = ""
			[ ] 
			[ ] // Scan all the positions
			[+] for iChar = 1 to iLen
				[ ] // Extract the character in the current position
				[ ] sChar = SubStr(sString, iChar,1)
				[ ] 
				[ ] // If delimiter encountered
				[+] if	(sChar == sDelim) || (sDelim == "SPACE" && IsSpace(sChar))
					[ ] // If a word (substring between two delimiters) was already extracted
					[+] if	(sWord != "")
						[ ] // Append the word into the list
						[ ] ListAppend( lsReturn, sWord )
						[ ] // Initialize to start forming next word
						[ ] sWord = ""
				[ ] // If current position does not have a delimiter, append the character in this position to the word
				[+] else
					[ ] sWord = sWord + sChar
			[ ] // Last word will be at the end of the string, so no delimiter will be encountered. Append it to the list
			[+] if	(sWord != "")
				[ ] ListAppend( lsReturn, sWord )
				[ ] sWord = ""
			[ ] 
			[ ] // Return the list
			[ ] return lsReturn
		[ ] 
		[+] window glCastStrToWin(STRING s,WINDOW wPrefix optional)
			[ ] WINDOW w	
			[ ] INTEGER iLevels	
			[ ] INTEGER i	
			[ ] iLevels = 1
			[+] for (i=1;i<=Len(s);i++)	
				[+] if SubStr(s,i,1) == "."	
					[ ] iLevels ++	
			[ ] w = wPrefix	
			[+] for (i=1;i<=iLevels;i++)	
				[+] if w != NULL
					[ ] w = w.@GetField(s,".",i)
				[+] else
					[ ] w = @GetField(s,".",i)
			[ ] return w
		[ ] 
		[+] number glVal(string str) // updated
			[ ] string sDecimal = SYS_GetRegistryValue(HKEY_CURRENT_USER, "Control Panel\International","sDecimal")
			[ ] string sThousand = SYS_GetRegistryValue(HKEY_CURRENT_USER, "Control Panel\International","sThousand")
			[ ] return val(StrTran(StrTran(str,sThousand,""),sDecimal,"."))
	[ ] 
	[+] // Addtion to 4T list datatype
		[+] int glListMatch(list of string lsList, string sItem, int iBegPos optional, boolean bReverse optional)
			[ ] // find the first sItem from lsList
			[ ] // when bReverse is false(default), do a forward search and at this time the iBegPos is the iBegPos item from the front
			[ ] // when bReverse is true, do a backward search and at this time the iBegPos is the iBegPos item from the back
			[ ] // return the index number of the list
			[+] if (iBegPos == null)
				[ ] iBegPos = 1
			[+] else
				[+] if (iBegPos > ListCount(lsList))
					[ ] RaiseError(-255,"Exception in glListMatch")
			[+] if (bReverse == null)
				[ ] bReverse = false
			[ ] int iPos
			[+] for (iPos = (bReverse?ListCount(lsList)-iBegPos+1:iBegPos);bReverse?(iPos >= 1):(iPos <= ListCount(lsList));iPos=(bReverse?iPos-1:iPos+1))
				[+] if (MatchStr(sItem,lsList[iPos]))
					[ ] return iPos
			[ ] return 0
		[ ] 
		[+] void glListUnique(inout list of AnyType In)
			[ ] // dremove duplicates from consecutive group, so use listsort before invoke this
			[+] if (In == null)
				[ ] return
			[ ] int iToRead
			[ ] int iUniqued = 1
			[+] for (iToRead = 2;iToRead <= ListCount(In);iToRead++)
				[+] if (In[iToRead] == In[iUniqued])
					[ ] ListDelete(In,iToRead)
					[ ] iToRead--
				[+] else
					[ ] iUniqued = iToRead
		[ ] 
		[+] void glListClear(inout list of AnyType In)
			[+] while(ListCount(In) >0)
				[ ] ListDelete(In,1)
	[ ] 
	[+] // Program invoke and process
		[+] boolean glInvokeFromStartMenu(string sPath) 
			[ ] // requirment: classic Start Menu, not scroll program, sPath is like"Accessories/Calculator"
			[ ] Desktop.Click(1,glGetWindowCenter(Taskbar.Start).x,glGetWindowCenter(Taskbar.Start).y)
			[+] if (glsOS == "7" || glsOS == "2008 r2") // currently, support english only
				[ ] sPath = "/Programs Folder and Fast Items/"+sPath
				[+] while(dlgNewStartMenu.btnAllprograms.Exists())
					[ ] dlgNewStartMenu.btnAllprograms.Click()
				[+] if (!glWaitForExists(dlgNewStartMenu.trvAllPrograms))
					[ ] return false
				[ ] return glTreeViewClicker(dlgNewStartMenu.trvAllPrograms,sPath,"/")
				[ ] // return glTreeViewClicker(dlgNewStartMenu.trvAllPrograms,sPath,"\")
			[+] else
				[ ] // sleep(1)
				[ ] dlgMenuContent.Menu.bar.btnPrograms.Click()
				[ ] sleep(1)
				[ ] int i = 1
				[+] while(true)
					[ ] string sTag = GetField(sPath, "/", i)
					[+] if (sTag == "")
						[+] if (dlgMenuContent.Menu.Exists() == false)
							[ ] return true
						[+] if (dlgMenuContent.Menu.Exists() == true)
							[ ] return false
					[+] if (dlgMenuContent.Menu.bar.PushButton(sTag).Exists())
						[ ] dlgMenuContent.Menu.bar.PushButton(sTag).Click()
						[ ] sleep(1)
					[+] else
						[ ] return false
					[ ] i++
		[ ] 
		[+] boolean glInvokeFromRun(string sPath)
			[ ] Desktop.Click(1,glGetWindowCenter(Taskbar.Start).x,glGetWindowCenter(Taskbar.Start).y)
			[+] if (glsOS == "7" || glsOS == "2008 r2")
				[ ] dlgNewStartMenu.txtSearchBox.SetText("run")
				[ ] sleep(1)
				[ ] dlgNewStartMenu.TypeKeys("<Enter>")
			[+] else
				[ ] dlgMenuContent.Menu.bar.btnRun.Click()
			[+] if (glWaitForExists(gldlgRun,5) == false)
				[ ] return false
			[+] else
				[ ] gldlgRun.SetActive()
				[ ] gldlgRun.cboOpen.SetText(sPath)
				[+] do
					[ ] gldlgRun.btnOK.Click()
				[+] except
					[ ] gldlgRun.TypeKeys("<Enter>")
				[+] list of WINDOW lwToAppear = {...}
					[ ] gldlgRun.dlgLocationNotFound
					[ ] dlgCommandNotFound("{sPath}")
				[ ] window  w = glWaitForAnyWin (lwToAppear, 2)
				[+] if (w == null)
					[ ] return true
				[+] else
					[ ] w.SetActive()
					[ ] w.Close()
					[ ] gldlgRun.Close()
					[ ] return false
		[ ] 
		[+] void glEndFromProcess(list of string lsPrcs)
			[+] if (!glEndFromProcess_1(lsPrcs) && !glEndFromProcess_2(lsPrcs))
				[ ] RaiseError(-255,"Exception in glEndFromProcess")
		[ ] 
		[+] private boolean glEndFromProcess_1(list of string lsPrcsImage)
			[ ] string sPrcsImageName
			[ ] list of string ls
			[+] for each sPrcsImageName in lsPrcsImage
				[ ] int i = SYS_Execute("taskkill /f /t /im ""{sPrcsImageName}""",ls)
				[+] if ( i != 0 && i != 128)
					[ ] return false
			[ ] return true
		[ ] 
		[+] private boolean glEndFromProcess_2(list of string lsPrcs) // return boolean
			[+] do
				[ ] glwTaskManager.Invoke()
				[ ] glwTaskManager.EndFromProcess(lsPrcs)
				[ ] glwTaskManager.Close()
				[ ] return true
			[+] except
				[ ] return false
		[ ] 
		[+] Boolean glProcessExists (STRING sProcess)
			[ ] Boolean bExists
			[ ] glwTaskManager.Invoke()
			[ ] bExists = glwTaskManager.ProcessExists( sProcess )
			[ ] glwTaskManager.Close()
			[ ] return bExists
	[ ] 
	[-] // Window verification
		[+] boolean glWaitForEnabled(window wObject, real rTimeOut optional)	// wait while wObject is Enabled in rTimeOut seconds, return true for success and false for failed
			[ ] real rTime = 0
			[ ] real rStep = Agent.GetOption (OPT_WINDOW_RETRY)
			[+] if (rTimeOut  == NULL)
				[ ] rTimeOut  = Agent.GetOption(OPT_WINDOW_TIMEOUT)
			[+] while(rTime <= rTimeOut)
				[+] if (wObject.IsEnabled())
					[ ] sleep(1)
					[ ] return true
				[+] else
					[ ] sleep(rStep)
					[ ] rTime += rStep
			[ ] return false
		[ ] 
		[+] boolean glWaitForActive(window wObject, real rTimeOut optional)	// wait while wObject is Active in rTimeOut seconds, return true for success and false for failed
			[ ] real rTime = 0
			[ ] real rStep = Agent.GetOption (OPT_WINDOW_RETRY)
			[-] if (rTimeOut == NULL)
				[ ] rTimeOut = Agent.GetOption(OPT_WINDOW_TIMEOUT)
			[-] while(rTime <= rTimeOut &&  wObject.IsActive() == false)
				[-] if (wObject.IsActive())
					[ ] sleep(1)
					[ ] return true
				[+] else
					[ ] sleep(rStep)
					[ ] rTime += 1
			[ ] return false
		[ ] 
		[+] boolean glWaitForExists(window wObject, real rTimeOut optional)	// wait while wObject is Exists in rTimeOut seconds, return true for success and false for failed
			[+] if (rTimeOut == NULL)
				[ ] rTimeOut = Agent.GetOption(OPT_WINDOW_TIMEOUT)
			[+] if (wObject.Exists(rTimeOut))
				[ ] sleep(1)
				[ ] return true
			[+] else
				[ ] return false
		[ ] 
		[+] boolean glWaitForDispose(window wObject, real rTimeOut optional)	// wait while wObject is Dispose in rTimeOut seconds, return true for success and false for failed
			[ ] real rTime = 0
			[ ] real rStep = Agent.GetOption (OPT_WINDOW_RETRY)
			[+] if (rTimeOut  == NULL)
				[ ] rTimeOut = Agent.GetOption(OPT_WINDOW_TIMEOUT)
			[+] while(rTime <= rTimeOut)
				[+] if (wObject.Exists() == false)
					[ ] sleep(1)
					[ ] return true
				[+] else
					[ ] sleep(rStep)
					[ ] rTime += rStep
			[ ] return false
		[ ] 
		[+] window glWaitForAnyWin (LIST of WINDOW lwToAppear, real rTimeout optional)	// Waiting for the first one of a list of windows to exist
			[ ] // Measures time elapsed
			[ ] real rTimer = 0
			[ ] 
			[ ] real rRetry = 1
			[ ] 
			[ ] // Window that appeared first
			[ ] WINDOW wReturn = NULL
			[ ] 
			[ ] // Temporary variable to look for one of the windows to appear
			[ ] WINDOW twToAppear
			[ ] 
			[ ] // If timeout is not specified, default to agent setting
			[+] if rTimeout== NULL
				[ ] rTimeout = Agent.GetOption( OPT_WINDOW_TIMEOUT )
			[ ] 
			[ ] // Until timeout
			[+] for rTimer = 0 to rTimeout step rRetry
				[ ] 
				[ ] // Look for each of the windows in the list
				[+] for each twToAppear in lwToAppear
					[ ] 
					[ ] // If one of the windows appears
					[+] if	twToAppear.Exists()
						[ ] // Store the window and stop searching for other windows
						[ ] wReturn = twToAppear
						[ ] break
				[ ] // If a window was found, stop the search 
				[+] if	wReturn != NULL
					[ ] break
				[ ] 
				[ ] sleep(rRetry)
			[ ] 
			[ ] // Return the window that was found
			[ ] return wReturn
	[ ] 
	[+] // dispose message box
		[ ] private const int iCommitTime = 5
		[ ] private const boolean bDebug = false
		[+] void glTryToCommitMessage(int iSeconds optional,string sTag optional)	// click Yes button or OK button on windows with tag sTag in iSecond
			[+] if (iSeconds == null)
				[ ] iSeconds = iCommitTime
			[+] if (sTag == null)
				[ ] sTag = "*"
			[+] if (iSeconds ==0)
				[+] while (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").Exists(2))
					[+] do
						[+] if (bDebug)
							[ ] ListPrint(glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").getStaticTexts())
					[+] except
						[ ] 
					[+] if (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnOK.Exists(0))
						[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").SetActive()
						[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnOK.Click()
						[+] if (bDebug)
							[ ] print("choose OK as response")
					[+] if (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnYes.Exists(0))
						[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").SetActive()
						[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnYes.Click()
						[+] if (bDebug)
							[ ] print("choose Yes as response")
				[+] while (glwcMessageBox("[DialogBox]{sTag}").Exists(2))
					[+] do
						[+] if (bDebug)
							[ ] ListPrint(glwcMessageBox("[DialogBox]{sTag}").getStaticTexts())
					[+] except
						[ ] 
					[+] if (glwcMessageBox("[DialogBox]{sTag}").btnOK.Exists(0))
						[ ] glwcMessageBox("[DialogBox]{sTag}").SetActive()
						[ ] glwcMessageBox("[DialogBox]{sTag}").btnOK.Click()
						[+] if (bDebug)
							[ ] print("choose OK as response")
					[+] if (glwcMessageBox("[DialogBox]{sTag}").btnYes.Exists(0))
						[ ] glwcMessageBox("[DialogBox]{sTag}").SetActive()
						[ ] glwcMessageBox("[DialogBox]{sTag}").btnYes.Click()
						[+] if(bDebug)
							[ ] print("choose Yes as response")
			[+] else
				[ ] int i = 0
				[ ] int hop = Agent.GetOption (OPT_WINDOW_RETRY)
				[+] while (i <= iSeconds)
					[+] if (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").Exists(0.5))
						[+] do
							[+] if (bDebug)
								[ ] ListPrint(glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").getStaticTexts())
						[+] except
							[ ] 
						[+] if (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnOK.Exists(0))
							[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").SetActive()
							[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnOK.Click()
							[+] if (bDebug)
								[ ] print("choose OK as response")
						[+] if (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnYes.Exists(0))
							[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").SetActive()
							[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnYes.Click()
							[+] if (bDebug)
								[ ] print("choose Yes as response")
					[+] if (glwcMessageBox("[DialogBox]{sTag}").Exists(0.5))
						[+] do
							[+] if (bDebug)
								[ ] ListPrint(glwcMessageBox("[DialogBox]{sTag}").getStaticTexts())
						[+] except
							[ ] 
						[+] if (glwcMessageBox("[DialogBox]{sTag}").btnOK.Exists(0))
							[ ] glwcMessageBox("[DialogBox]{sTag}").SetActive()
							[ ] glwcMessageBox("[DialogBox]{sTag}").btnOK.Click()
							[+] if (bDebug)
								[ ] print("choose OK as response")
						[+] if (glwcMessageBox("[DialogBox]{sTag}").btnYes.Exists(0))
							[ ] glwcMessageBox("[DialogBox]{sTag}").SetActive()
							[ ] glwcMessageBox("[DialogBox]{sTag}").btnYes.Click()
							[+] if(bDebug)
								[ ] print("choose Yes as response")
					[ ] i ++
		[ ] 
		[ ] private int iRejectTime = 5
		[+] void glTryToRejectMessage(int iSeconds optional,string sTag optional)	// click No button or OK button on windows with tag sTag in iSecond
			[+] if (iSeconds == null)
				[ ] iSeconds = iRejectTime
			[+] if (sTag == null)
				[ ] sTag = "*"
			[ ] int i = 0
			[+] if (iSeconds ==0)
				[+] while (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").Exists(2))
					[+] do
						[+] if (bDebug)
							[ ] ListPrint(glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").getStaticTexts())
					[+] except
						[ ] 
					[+] if (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnOK.Exists(0))
						[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").SetActive()
						[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnOK.Click()
						[+] if (bDebug)
							[ ] print("choose OK as response")
					[+] if (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnNo.Exists(0))
						[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").SetActive()
						[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnNo.Click()
						[+] if (bDebug)
							[ ] print("choose No as response")
				[+] while (glwcMessageBox("[DialogBox]{sTag}").Exists(2))
					[+] do
						[+] if (bDebug)
							[ ] ListPrint(glwcMessageBox("[DialogBox]{sTag}").getStaticTexts())
					[+] except
						[ ] 
					[+] if (glwcMessageBox("[DialogBox]{sTag}").btnOK.Exists(0))
						[ ] glwcMessageBox("[DialogBox]{sTag}").SetActive()
						[ ] glwcMessageBox("[DialogBox]{sTag}").btnOK.Click()
						[+] if (bDebug)
							[ ] print("choose OK as response")
					[+] if (glwcMessageBox("[DialogBox]{sTag}").btnNo.Exists(0))
						[ ] glwcMessageBox("[DialogBox]{sTag}").SetActive()
						[ ] glwcMessageBox("[DialogBox]{sTag}").btnNo.Click()
						[+] if(bDebug)
							[ ] print("choose No as response")
			[+] else
				[+] while (i <= iSeconds)
					[+] if (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").Exists(0.5))
						[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").SetActive()
						[+] do
							[+] if (bDebug)
								[ ] ListPrint(glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").getStaticTexts())
						[+] except
							[ ] 
						[+] if (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnOK.Exists(0))
							[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnOK.Click()
							[+] if (bDebug)
								[ ] print("choose OK as response")
						[+] if (glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnNo.Exists(0))
							[ ] glwcMessageBox("~ActiveApp/[DialogBox]{sTag}").btnNo.Click()
							[+] if (bDebug)
								[ ] print("choose No as response")
					[+] if (glwcMessageBox("[DialogBox]{sTag}").Exists(0.5))
						[ ] glwcMessageBox("[DialogBox]{sTag}").SetActive()
						[+] do
							[+] if (bDebug)
								[ ] ListPrint(glwcMessageBox("[DialogBox]{sTag}").getStaticTexts())
						[+] except
							[ ] 
						[+] if (glwcMessageBox("[DialogBox]{sTag}").btnOK.Exists(0))
							[ ] glwcMessageBox("[DialogBox]{sTag}").btnOK.Click()
							[+] if (bDebug)
								[ ] print("choose OK as response")
						[+] if (glwcMessageBox("[DialogBox]{sTag}").btnNo.Exists(0))
							[ ] glwcMessageBox("[DialogBox]{sTag}").btnNo.Click()
							[+] if (bDebug)
								[ ] print("choose No as response")
					[ ] i ++
	[ ] 
	[+] // service
		[+] boolean glStartService (STRING sServiceName, inout list of string lsOutput optional)
			[ ] return !(SYS_Execute ("net start ""{sServiceName}""",lsOutput))
		[ ] 
		[+] boolean glStopService (STRING sServiceName, inout list of string lsOutput optional)
			[ ] return !(SYS_Execute ("net stop ""{sServiceName}""",lsOutput))
	[ ] 
	[+] // log
		[+] private winclass glwcLog
			[ ] list of string lsRecords
			[ ] 
			[ ] string sDataOutDir
			[ ] int iCurrentIndex
			[ ] string sScreenshotExt
			[ ] 
			[+] init (string sOutputDir, string sPicExt optional)
				[+] if (sPicExt == null)
					[ ] sPicExt = ".bmp"
				[ ] this.sScreenshotExt = sPicExt
				[ ] 
				[ ] glListClear(this.lsRecords)
				[ ] this.iCurrentIndex = 1
				[ ] int i = 1
				[ ] while (SYS_DirExists(sOutputDir+"\Resultset{i++}"))
				[ ] this.sDataOutDir = sOutputDir+"\Resultset{--i}"
				[+] if (!SYS_DirExists(this.sDataOutDir))
					[ ] glSYS_MakeDirDirect(this.sDataOutDir)
				[+] if (sPicExt == null)
					[ ] sPicExt = ".bmp"
				[ ] this.sScreenshotExt = sPicExt
			[+] list of string LogEntity(anytype at)
				[ ] list of string lsReturn = {}
				[ ] string s
				[+] switch (typeof(at))
					[+] case window
						[ ] s = str(this.iCurrentIndex) + this.sScreenshotExt
						[+] if (SYS_FileExists(this.sDataOutDir + "\" + s))
							[ ] SYS_RemoveFile(this.sDataOutDir + "\" + s)
						[ ] lsRecords[ListCount(lsRecords)] += "	>>> SCREENSHOT " + glScreenShot(at,this.sDataOutDir + "\" + s)
						[ ] this.iCurrentIndex++
						[ ] ListAppend(lsReturn,this.sDataOutDir + "\" + s)
					[+] case number
						[ ] lsRecords[ListCount(lsRecords)] += "	>>> " + str(at)
						[ ] return {}
					[+] case string
						[+]  if (SYS_DirExists(trim(at)))
							[ ] at = trim(at)
							[+] if (MatchStr(lower(this.sDataOutDir+"*"),lower(at)))
								[ ] lsRecords[ListCount(lsRecords)] += "	>>> FOLDER " + at
							[+] else
								[+] while (right(at,1) == "/" || right(at,1) == "\")
									[ ]  at = SubStr(at,1,len(at)-1)
								[ ] s = str(this.iCurrentIndex) + "-" + glGetReverseField(glGetReverseField(at,"/",1),"\",1)
								[+] if (SYS_DirExists(this.sDataOutDir + "\" + s))
									[ ] glSYS_ClearDir(this.sDataOutDir + "\" + s, true, false)
									[ ] SYS_RemoveDir(this.sDataOutDir + "\" + s)
								[ ] glSYS_CopyDir(at,this.sDataOutDir + "\" + s,true)
								[ ] lsRecords[ListCount(lsRecords)] += "	>>> FOLDER " + this.sDataOutDir + "\" + s
								[ ] this.iCurrentIndex++
								[ ] ListAppend(lsReturn,this.sDataOutDir + "\" + s)
						[+] else if  (SYS_FileExists(trim(at)))
							[ ] at = trim(at)
							[+] if (MatchStr(lower(this.sDataOutDir+"*"),lower(at)))
								[ ] lsRecords[ListCount(lsRecords)] += "	>>> FILE " + at
							[+] else
								[ ] s = str(this.iCurrentIndex) + "-" + glGetReverseField(glGetReverseField(at,"/",1),"\",1)
								[+] if (SYS_FileExists(this.sDataOutDir + "\" + s))
									[ ] SYS_RemoveFile(this.sDataOutDir + "\" + s)
								[ ] SYS_CopyFile(at,this.sDataOutDir + "\" + s)
								[ ] lsRecords[ListCount(lsRecords)] += "	>>> FILE " + this.sDataOutDir + "\" + s
								[ ] this.iCurrentIndex++
								[ ] ListAppend(lsReturn,this.sDataOutDir + "\" + s)
						[+] else
							[ ] lsRecords[ListCount(lsRecords)] += "	>>> " + at
					[+] case list
						[ ] lsRecords[ListCount(lsRecords)] += "	vvv"
						[ ] anytype a
						[+] for each a in at
							[ ] ListAppend(this.lsRecords,"")
							[ ] ListMerge(lsReturn,this.LogEntity(a))
					[+] default
						[ ] RaiseError(-255,"unsupported entity, contact automation team!")
				[ ] return lsReturn
			[ ] 
			[+] Raw(string sLog)
				[ ] ListAppend(lsRecords,sLog)
			[+] Step(string sLog)
				[ ] this.Raw("=== " + sLog)
			[+] Pass(string sLog, anytype aActual optional)
				[ ] this.Raw("√√√ " + sLog)
				[+] if (aActual != null)
					[ ] this.LogEntity(aActual)
			[+] Fail(string sLog, anytype aActual optional)
				[ ] this.Raw("xxx " + sLog)
				[+] if (aActual != null)
					[ ] this.LogEntity(aActual)
			[+] Warning(string sLog, anytype aActual optional)
				[ ] this.Raw("!!! " + sLog)
				[+] if (aActual != null)
					[ ] this.LogEntity(aActual)
			[+] Error(string sLog)
				[ ] RaiseError(-255,sLog)
			[+] Check(string sLog, anytype aActual optional, anytype aExpect optional)
				[ ] this.Raw("??? " + sLog)
				[+] if (aActual != null)
					[ ] ListAppend(lsRecords,"??? ACTUAL")
					[ ] this.LogEntity(aActual)
					[+] if (aExpect != null)
						[ ] ListAppend(lsRecords,"??? REFFERENCE")
						[ ] this.LogEntity(aExpect)
			[ ] 
			[+] ExtractToLog()
				[ ] string s
				[+] for each s in this.lsRecords
					[ ] s = ltrim(s)
					[+] switch (SubStr(s,1,3))
						[+] case "==="
							[ ] print(s)
						[+] case "√√√"
							[ ] print(s)
						[+] case "xxx"
							[ ] logerror(s)
						[+] case "***"
							[ ] logerror(s)
						[+] case "???"
							[ ] logwarning(s)
						[+] case "!!!"
							[ ] logwarning(s)
						[+] default
							[ ] print(s)
			[+] ExtractToFile()
				[ ] string s
				[ ] // s = "Result" + "-" + RandStr ("AAA") + ".txt"
				[+] // while (SYS_FileExists(this.sDataOutDir + "\" + s))
					[ ] // s = "Result" + "-" + RandStr ("AAA") + ".txt"
				[ ] s = "Result.txt"
				[+] if (SYS_FileExists(this.sDataOutDir + "\" + s))
					[ ] RaiseError(-255,"Exception in glwcLog")
				[ ] handle h = SYS_FileOpen(this.sDataOutDir + "\" + s, FM_WRITE, FS_DENY_WRITE,FT_UNICODE)
				[+] for each s in this.lsRecords
					[ ] SYS_FileWriteLine(h,s)
				[ ] 
				[ ] SYS_FileClose(h)
		[ ] window glwcLog gllog
	[ ] 
	[ ] 
	[ ] 
	[+] // other
		[+] string glScreenShot(window w, string sFileName, RECT rect optional) // new
			[ ] int iOPT_BITMAP_MATCH_COUNT = Agent.GetOption (OPT_BITMAP_MATCH_COUNT)
			[ ] int iOPT_BITMAP_MATCH_INTERVAL = Agent.GetOption (OPT_BITMAP_MATCH_INTERVAL)
			[+] if (lower(right(sFileName,4)) != ".bmp")
				[ ] sFileName += ".bmp"
			[ ] w.CaptureBitmap (sFileName, rect)
			[ ] Agent.SetOption (OPT_BITMAP_MATCH_COUNT, iOPT_BITMAP_MATCH_COUNT)
			[ ] Agent.SetOption (OPT_BITMAP_MATCH_INTERVAL, iOPT_BITMAP_MATCH_INTERVAL)
			[ ] return sFileName
		[ ] 
		[+] void glRemoveShareConnection(string sServer optional,string sLocalName optional, string sRemoteName optional) // new
			[+] if (sServer != null)
				[ ] sServer = lower(sServer)
			[+] if (sLocalName != null)
				[ ] sLocalName = lower(sLocalName)
			[+] if (sRemoteName != null)
				[ ] sRemoteName = lower(sRemoteName)
			[ ] 
			[ ] list of string lsOutput
			[ ] string s
			[ ] list of string lsShareToDelete
			[ ] int iStatus = null
			[ ] int iLocal = null
			[ ] int iRemote = null
			[ ] int iNetWork = null
			[ ] SYS_Execute("NET USE",lsOutput)
			[+] for each s in lsOutput
				[+] if (iStatus == null || iLocal == null ||  iRemote == null || iNetWork == null)
					[+] if (StrPos("Status",s) == 1)
						[ ] iStatus = StrPos("Status",s)
						[ ] iLocal = StrPos("Local",s)
						[ ] iRemote = StrPos("Remote",s)
						[ ] iNetWork = StrPos("Network",s)
				[+] else
					[ ] break
			[+] if (iStatus == null && iLocal == null &&  iRemote == null && iNetWork == null)
				[ ] print("no connetction from this computer exists!")
				[ ] return
			[+] else if (iStatus == null || iLocal == null ||  iRemote == null || iNetWork == null || iStatus == 0 || iLocal == 0 ||  iRemote == 0 || iNetWork == 0)
				[ ] RaiseError(-255,"Exception in glRemoveShareConnection")
			[+] else
				[+] for each s in lsOutput
					[+] if (StrPos("OK",s) == 1 || StrPos("Disconnected",s) == 1)
						[ ] string sStatus = lower(trim(SubStr(s,iStatus,iLocal-iStatus)))
						[ ] string sLocal = lower(trim(SubStr(s,iLocal,iRemote-iLocal)))
						[ ] string sRemote = lower(trim(SubStr(s,iRemote,iNetWork-iRemote)))
						[ ] string sNetWork = lower(trim(SubStr(s,iNetWork)))
						[+] if (sServer != null)
							[+] if (sLocalName != null)
								[+] if (sRemoteName != null)
									[+] if (sLocalName == sLocal)
										[+] if (sRemoteName == sRemote)
											[+] if (StrPos("\\{sServer}",sRemote) == 1)
												[ ] ListAppend(lsShareToDelete,sLocal)
											[+] else
												[ ] break
										[+] else
											[ ] break
									[+] else
										[ ] continue
								[+] else
									[+] if (sLocalName == sLocal)
										[+] if (StrPos("\\{sServer}",sRemote) == 1)
											[ ] ListAppend(lsShareToDelete,sLocal)
										[+] else
											[ ] break
									[+] else
										[ ] continue
							[+] else
								[+] if (sRemoteName != null)
									[+] if (sRemoteName == sRemote)
										[+] if (StrPos("\\{sServer}",sRemote) == 1)
											[+] if (sLocal == "")
												[ ] ListAppend(lsShareToDelete,sRemote)
											[+] else
												[ ] ListAppend(lsShareToDelete,sLocal)
										[+] else
											[ ] break
									[+] else
										[ ] continue
								[+] else
									[+] if (StrPos("\\{sServer}",sRemote) == 1)
										[+] if (sLocal != "")
											[ ] ListAppend(lsShareToDelete,sLocal)
										[+] else
											[ ] ListAppend(lsShareToDelete,sRemote)
									[+] else
										[ ] continue
						[+] else
							[+] if (sLocalName != null)
								[+] if (sRemoteName != null)
									[+] if (sLocalName == sLocal)
										[+] if (sRemoteName == sRemote)
											[ ] ListAppend(lsShareToDelete,sLocal)
										[+] else
											[ ] break
									[+] else
										[ ] continue
								[+] else
									[+] if (sLocalName == sLocal)
										[ ] ListAppend(lsShareToDelete,sLocal)
									[+] else
										[ ] continue
							[+] else
								[+] if (sRemoteName != null)
									[+] if (sRemoteName == sRemote)
										[+] if (sLocal == "")
											[ ] ListAppend(lsShareToDelete,sRemote)
										[+] else
											[ ] ListAppend(lsShareToDelete,sLocal)
									[+] else
										[ ] continue
								[+] else
									[+] if (sLocal != "")
										[ ] ListAppend(lsShareToDelete,sLocal)
									[+] else
										[ ] ListAppend(lsShareToDelete,sRemote)
					[+] else
						[ ] continue
			[ ] 
			[+] if (ListCount(lsShareToDelete) == 0)
				[ ] print(" √√√ no connetction matches server {sServer} local name {sLocalName} remote name {sRemoteName} from this computer exists!")
				[ ] return
			[+] for each s in lsShareToDelete
				[+] if (SYS_Execute("NET USE ""{s}"" /DELETE",lsOutput) ==0)
					[ ] print("√√√ share connection {s} deleted!")
				[+] else
					[ ] logerror("xxx error in delete share connection {s}!")
		[ ] 
		[+] boolean glTreeViewSelector(window trvSource,string sPath,string sDelim optional)
			[+] if (sDelim == null)
				[ ] sDelim = "/"
			[+] if (Left(sPath,1) != sDelim)
				[ ] sPath = sDelim + sPath
			[ ] 
			[ ] return glStructureListSelectorTemplate(trvSource,sPath,sDelim,"glStructureListSelector_Expand","glStructureListSelector_Select","glStructureListSelector_Find")
		[ ] 
		[+] boolean glTreeViewClicker(window trvSource,string sPath,string sDelim optional)
			[+] if (sDelim == null)
				[ ] sDelim = "/"
			[+] if (Left(sPath,1) != sDelim)
				[ ] sPath = sDelim + sPath
			[ ] 
			[ ] return glStructureListSelectorTemplate(trvSource,sPath,sDelim,"glStructureListClicker_Click","glStructureListClicker_Click","glStructureListSelector_Find")
		[ ] 
		[+] boolean glListViewSelector(window lstSource,string sPath,string sDelim optional)
			[+] if (sDelim == null)
				[ ] sDelim = "/"
			[ ] list of STRING lsLabels
			[ ] int i = 1
			[+] while(true)
				[ ] string sTemp = GetField(sPath, sDelim, i)
				[+] if (trim(sTemp) != "")
					[ ] ListAppend(lsLabels,sTemp)
				[+] else
					[ ] break
				[ ] i++
			[ ] return glFlatViewSelectorTemplate(lstSource,lsLabels,"glFlatViewSelector_CascadeAll","glFlatViewSelector_Expand","glFlatViewSelector_Select")
		[ ] 
		[ ] private int iStepLength = 5
		[+] POINT glFindToolbarIcon(window wBar, string sIconName, int iStepLen optional,int hint optional)	// this function is used to find a button on a customizes toolbar by the popup tip when the mouse is over the button
			[+] if(iStepLen ==null)
				[ ] iStepLen = iStepLength
			[ ] RECT r = wBar.GetRect()
			[ ] int iXStart = 0
			[ ] int iXEnd = r.xSize
			[ ] POINT pos ={0,0}
			[ ] int iX = iXStart
			[ ] int iY = r.ySize/2
			[+] if (hint != null)
				[ ] wBar.MoveMouse(hint, iY)
				[ ] sleep(1)
				[+] if  (DialogBox("#1").Exists(3) && strpos(sIconName,DialogBox("#1").GetCaption()) != 0)
					[ ] pos.x = hint
					[ ] pos.y = iY
					[ ] return pos
			[+] while( iX<iXEnd)
				[ ] wBar.MoveMouse(iX, iY)
				[ ] sleep(1)
				[+] if  (DialogBox("#1").Exists(3) && strpos(sIconName,DialogBox("#1").GetCaption()) != 0)
					[ ] pos.x = iX
					[ ] pos.y = iY
					[ ] break
				[ ] iX = iX+iStepLen
			[ ] return pos
		[ ] 
		[+] list of string glGetChildrenTags(window wSource,string sTag optional)	// return all control tags which contains sTag from wSource
			[+] if (sTag == null)
				[ ] sTag = ""
			[ ] int i
			[ ] list of string lsContents, lsResults
			[ ] lsContents = wSource.GetContents()
			[+] for(i=1;i<ListCount(lsContents)+1;i++)
				[+] if( StrPos(sTag, lsContents[i])!=0 )
					[ ] ListAppend( lsResults, lsContents[i])
			[ ] return lsResults
		[ ] 
		[+] POINT glGetWindowCenter(window w) // return the global coordination of the center point of the window w
			[ ] POINT pos
			[ ] RECT rec = w.getRect(true)
			[ ] pos.x = rec.xPos+rec.xSize/2
			[ ] pos.y = rec.yPos+rec.ySize/2
			[ ] return pos
[ ] 
[+] //-------------------------------------------------------------------------------- common winclass -----------------------------------------------------------------------------------------//
	[+] // open and save file dialog, select folder
		[+] winclass			glwcDlgOpenFile			:			DialogBox
			[+] multitag "*Open*"
				[ ] "*開く*"
				[ ] "*打开*"
				[ ] "*Öffnen*"
				[ ] "*열기*"
			[+] // mswvista multitag "*Open*"
				[ ] // "*開く*"
				[ ] // "*打开*"
				[ ] // "*Öffnen*"
				[ ] // "*열기*"
			[+] // msw2003 multitag "*Open*"
				[ ] // "*開く*"
				[ ] // "*打开*"
				[ ] // "*Öffnen*"
				[ ] // "*열기*"
			[+] //-------------------------------------------------------- Menu  --------------------------------------------------------//
				[+] ComboBox cboFileName
					[ ] tag "#1"
					[+] // mswxp multitag "File name:"
						[ ] // "ファイル名(N):"
						[ ] // "文件名(N):"
						[ ] // "Dateiname:"
						[ ] // "파일 이름(N):"
					[+] // mswvista multitag "File name:[1]|File name:"
						[ ] // "ファイル名(N):[1]|ファイル名(N):"
						[ ] // "文件名(N):[1]|文件名(N):"
						[ ] // "Dateiname:[1]|Dateiname:"
						[ ] // "파일 이름(N):[1]|파일 이름(N):"
					[+] // msw2003 multitag "File name:"
						[ ] // "ファイル名(N):"
						[ ] // "文件名(N):"
						[ ] // "Dateiname:"
						[ ] // "파일 이름(N):"
				[+] property btnOpen
					[+] window get()
						[+] if (this.CustomWin("[Button]#1").Exists())
							[ ] return this.CustomWin("[Button]#1")
						[+] if (this.PushButton("#1").Exists())
							[ ] return this.PushButton("#1")
				[+] // PushButton btnOpen
					[ ] // tag "#1"
					[+] // // mswxp multitag "Open"
						[ ] // // "開く(O)"
						[ ] // // "打开(O)"
						[ ] // // "Öffnen"
						[ ] // // "열기(O)"
					[+] // // mswvista multitag "Open|[Button]Open"
						[ ] // // "開く(O)|[Button]開く(O)"
						[ ] // // "打开(O)|[Button]打开(O)"
						[ ] // // "Öffnen|[Button]Öffnen"
						[ ] // // "열기(O)|[Button]열기(O)"
					[+] // // msw2003 multitag "Open"
						[ ] // // "開く(O)"
						[ ] // // "打开(O)"
						[ ] // // "Öffnen"
						[ ] // // "열기(O)"
			[+] //-------------------------------------------------------- Dialog  -------------------------------------------------------//
				[+] DialogBox dlgOpenFileWarning
					[ ] tag "$MessageBox"
					[+] property btnOK
						[+] window get()
							[+] if (this.PushButton("#1").Exists())
								[ ] return this.PushButton("#1")
							[+] if (this.PushButton("~/#1").Exists())
								[ ] return this.PushButton("~/#1")
					[+] // AnyWin btnOK_
						[ ] // tag "#1"
						[+] // void Click()
							[ ] // window w
							[+] // if (this.GetParent().PushButton("#1").Exists())
								[ ] // w = this.GetParent().PushButton("#1").Exists()
							[+] // if (this.GetParent().PushButton("~/#1").Exists())
								[ ] // w = this.GetParent().PushButton("~/#1").Exists()
							[ ] // w.Click()
					[+] // PushButton btnOK1
						[ ] // tag "#1"
						[+] // // mswxp multitag "OK"
							[ ] // // "确定"
							[ ] // // "확인"
						[+] // // mswvista multitag "[DirectUIHWND]#1/[CtrlNotifySink]#1/OK"
							[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/确定"
							[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/확인"
						[+] // // msw2003 multitag "OK"
							[ ] // // "确定"
							[ ] // // "확인"
					[+] // PushButton btnOK2
						[ ] // tag "~/#1"
						[+] // // mswxp multitag "OK"
							[ ] // // "确定"
							[ ] // // "확인"
						[+] // // mswvista multitag "[DirectUIHWND]#1/[CtrlNotifySink]#1/OK"
							[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/确定"
							[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/확인"
						[+] // // msw2003 multitag "OK"
							[ ] // // "确定"
							[ ] // // "확인"
			[+] //------------------------------------------------------- Method -------------------------------------------------------//
				[+] void OpenFile(string sFile)
					[+] if (sFile == null || trim(sFile) == "")
						[ ] RaiseError(-255,"Exception in OpenFile")
					[ ] this.cboFileName.SetText(sFile)
					[ ] sleep(1)
					[ ] this.btnOpen.Click()
					[+] if (glWaitForExists(this.dlgOpenFileWarning,2) == true)
						[+] // if (this.dlgOpenFileWarning.btnOK1.Exists())
							[ ] // this.dlgOpenFileWarning.btnOK1.Click()
						[ ] // if (this.dlgOpenFileWarning.btnOK2.Exists())
						[ ] // this.dlgOpenFileWarning.btnOK.Click()
						[ ] this.dlgOpenFileWarning.Close()
						[ ] RaiseError(-255,"Exception in OpenFile")
		[ ] 
		[+] winclass			glwcDlgSaveFile			:			DialogBox
			[+] multitag "*Save*"
				[ ] "*名前を付けて保存*"
				[ ] "*另存为*"
				[ ] "*Speichern unter*"
				[ ] "*다른 이름으로 저장*"
			[+] // mswvista multitag "*Save*"
				[ ] // "*名前を付けて保存*"
				[ ] // "*另存为*"
				[ ] // "*Speichern unter*"
				[ ] // "*다른 이름으로 저장*"
			[+] // msw2003 multitag "*Save*"
				[ ] // "*名前を付けて保存*"
				[ ] // "*另存为*"
				[ ] // "*Speichern unter*"
				[ ] // "*다른 이름으로 저장*"
			[+] //-------------------------------------------------------- Menu  --------------------------------------------------------//
				[+] property cboFileName
					[+] window get()
						[+] if (this.CustomWin("[DUIViewWndClassName]#1").CustomWin("[DirectUIHWND]#1").CustomWin("[FloatNotifySink]#1").ComboBox("#1").Exists())
							[ ] return this.CustomWin("[DUIViewWndClassName]#1").CustomWin("[DirectUIHWND]#1").CustomWin("[FloatNotifySink]#1").ComboBox("#1")
						[+] if (this.ComboBox("#1").Exists())
							[ ] return this.ComboBox("#1")
				[+] property popFileType
					[+] window get()
						[+] if (this.CustomWin("[DUIViewWndClassName]#1").CustomWin("[DirectUIHWND]#1").CustomWin("[FloatNotifySink]#2").PopupList("#1").Exists())
							[ ] return this.CustomWin("[DUIViewWndClassName]#1").CustomWin("[DirectUIHWND]#1").CustomWin("[FloatNotifySink]#2").PopupList("#1")
						[+] if (this.PopupList("#2").Exists())
							[ ] return this.PopupList("#2")
						[+] if (this.PopupList("#1").Exists())
							[ ] return this.PopupList("#1")
				[+] PushButton btnSave
					[+] multitag "Save"
						[ ] "保存(S)"
						[ ] "Speichern"
						[ ] "저장(S)"
					[+] // mswvista multitag "Save"
						[ ] // "保存(S)"
						[ ] // "Speichern"
						[ ] // "저장(S)"
					[+] // msw2003 multitag "Save"
						[ ] // "保存(S)"
						[ ] // "Speichern"
						[ ] // "저장(S)"
				[ ] 
				[+] // AnyWin cboFileName_
						[ ] // tag "#1"
						[+] // void SetText(string s)
							[ ] // window w
							[+] // if (this.GetParent().ComboBox("#1").Exists())
								[ ] // w = this.GetParent().ComboBox("#1")
							[+] // if (this.GetParent().PushButton("~/#1").Exists())
								[ ] // w = this.GetParent().PushButton("~/#1")
							[ ] // w.SetText(s)
				[+] // ComboBox cboFileName1
					[ ] // tag "#1"
					[+] // // mswxp multitag "File name:"
						[ ] // // "ファイル名(N):"
						[ ] // // "文件名(N):"
						[ ] // // "Dateiname:"
						[ ] // // "파일 이름(N):"
					[+] // // mswvista multitag "File name:[1]|File name:"
						[ ] // // "ファイル名(N):[1]|ファイル名(N):"
						[ ] // // "文件名(N):[1]|文件名(N):"
						[ ] // // "Dateiname:[1]|Dateiname:"
						[ ] // // "파일 이름(N):[1]|파일 이름(N):"
					[+] // // msw2003 multitag "File name:"
						[ ] // // "ファイル名(N):"
						[ ] // // "文件名(N):"
						[ ] // // "Dateiname:"
						[ ] // // "파일 이름(N):"
				[+] // ComboBox cboFileName2
					[ ] // tag "~/#1"
					[+] // // mswxp multitag "File name:"
						[ ] // // "ファイル名(N):"
						[ ] // // "文件名(N):"
						[ ] // // "Dateiname:"
						[ ] // // "파일 이름(N):"
					[ ] // // mswvista multitag "[DUIViewWndClassName]#1/[DirectUIHWND]#1/[FloatNotifySink]#1/#1"
					[+] // // msw2003 multitag "File name:"
						[ ] // // "ファイル名(N):"
						[ ] // // "文件名(N):"
						[ ] // // "Dateiname:"
						[ ] // // "파일 이름(N):"
				[+] // PopupList popFileType1
					[ ] // tag "#1"
					[+] // // mswxp multitag "Save as type:"
						[ ] // // "ファイルの種類(T):"
						[ ] // // "保存类型(T):"
						[ ] // // "Dateityp:"
						[ ] // // "파일 형식(T):"
					[+] // // mswvista multitag "Save as type:"
						[ ] // // "ファイルの種類(T):"
						[ ] // // "保存类型(T):"
						[ ] // // "Dateityp:"
						[ ] // // "파일 형식(T):"
					[+] // // msw2003 multitag "Save as type:"
						[ ] // // "ファイルの種類(T):"
						[ ] // // "保存类型(T):"
						[ ] // // "Dateityp:"
						[ ] // // "파일 형식(T):"
				[+] // PopupList popFileType2
					[ ] // tag "~/#1"
					[+] // // mswxp multitag "Save as type:"
						[ ] // // "ファイルの種類(T):"
						[ ] // // "保存类型(T):"
						[ ] // // "Dateityp:"
						[ ] // // "파일 형식(T):"
					[ ] // // mswvista multitag "[DUIViewWndClassName]#1/[DirectUIHWND]#1/[FloatNotifySink]#2/#1"
					[+] // // msw2003 multitag "Save as type:"
						[ ] // // "ファイルの種類(T):"
						[ ] // // "保存类型(T):"
						[ ] // // "Dateityp:"
						[ ] // // "파일 형식(T):"
			[+] //-------------------------------------------------------- Dialog  -------------------------------------------------------//
				[+] DialogBox dlgSaveFileWarning
					[ ] tag "$MessageBox"
					[+] property btnYes
						[+] window get()
							[+] if (this.PushButton("#1").Exists() && this.PushButton("#2").Exists())
								[ ] return this.PushButton("#1")
							[+] if (this.CustomWin("[DirectUIHWND]#1").CustomWin("[CtrlNotifySink]#1").PushButton("#1").Exists() && this.CustomWin("[DirectUIHWND]#1").CustomWin("[CtrlNotifySink]#2").PushButton("#1").Exists())
								[ ] return this.CustomWin("[DirectUIHWND]#1").CustomWin("[CtrlNotifySink]#1").PushButton("#1")
							[ ] return null
					[+] property btnOK
						[+] window get()
							[+] if (this.PushButton("#1").Exists() && !this.PushButton("#2").Exists())
								[ ] return this.PushButton("#1")
							[+] if (this.CustomWin("[DirectUIHWND]#1").CustomWin("[CtrlNotifySink]#1").PushButton("#1").Exists() && !this.CustomWin("[DirectUIHWND]#1").CustomWin("[CtrlNotifySink]#2").PushButton("#1").Exists())
								[ ] return this.CustomWin("[DirectUIHWND]#1").CustomWin("[CtrlNotifySink]#1").PushButton("#1")
							[ ] return null
					[ ] 
					[ ] 
					[ ] 
					[+] // PushButton btnYes
						[+] // mswxp multitag "Yes"
							[ ] // "はい(Y)"
							[ ] // "是(Y)"
							[ ] // "Ja"
							[ ] // "예(Y)"
						[+] // mswvista multitag "[DirectUIHWND]#1/[CtrlNotifySink]#1/Yes"
							[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/はい(Y)"
							[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/是(Y)"
							[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/Ja"
							[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/예(Y)"
						[+] // msw2003 multitag "Yes"
							[ ] // "はい(Y)"
							[ ] // "是(Y)"
							[ ] // "Ja"
							[ ] // "예(Y)"
					[+] // PushButton btnOK
						[+] // mswxp multitag "OK"
							[ ] // "确定"
							[ ] // "확인"
						[+] // mswvista multitag "[DirectUIHWND]#1/[CtrlNotifySink]#1/OK"
							[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/确定"
							[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/확인"
						[+] // msw2003 multitag "OK"
							[ ] // "确定"
							[ ] // "확인"
			[+] //------------------------------------------------------- Method -------------------------------------------------------//
				[+] void SaveFile(string sFile,string sType optional)
					[ ] this.cboFileName.CaptureBitMap("{SYS_GetEnv("TEMP")}\1.bmp")
					[+] if (sType != null)
						[ ] this.popFileType.Select(sType)
						[+] // if (this.popFileType.Exists())
							[ ] // this.popFileType.Select(sType)
						[+] // else if (this.popFileType2.Exists())
							[ ] // this.popFileType2.Select(sType)
						[+] // else
							[ ] // RaiseError(-255,"Exception in SaveFile")
					[ ] sleep(1)
					[ ] this.cboFileName.SetText(sFile)
					[ ] sleep(1)
					[ ] this.btnSave.SetFocus()
					[ ] this.btnSave.Click()
					[+] if (glWaitForExists(this.dlgSaveFileWarning,2) == true)
						[+] if (this.dlgSaveFileWarning.btnYes != null)
							[ ] this.dlgSaveFileWarning.btnYes.Click()
							[+] if (this.dlgSaveFileWarning.btnOK != null)
								[ ] RaiseError(-255,"Exception in SaveFile: can not write?")
							[+] if (this.Exists(3))
								[ ] RaiseError(-255,"Exception in SaveFile: permission?")
							[ ] return
						[+] if (this.dlgSaveFileWarning.btnOK != null)
							[ ] RaiseError(-255,"Exception in SaveFile: can not write?")
		[ ] 
		[+] winclass			glwcTvwFolder				:			TreeView
			[+] boolean SelectFolder(string sPath, string sDelim optional) // start with   "DRIVER:", and end with sDelim, sample: "C:\WINDOWS\"
				[+] if (sDelim == null)
					[ ] sDelim = "\"
				[+] if (right(sPath,1) != sDelim)
					[ ] sPath = sPath + sDelim
				[ ] 
				[ ] list of string lsTarg = glCastStrToList(sPath, sDelim)
				[+] if (right(lsTarg[1],1) != ":")
					[ ] gllog.Error("Path error!")
				[ ] 
				[ ] // no Desktop Folder or the first target item exists
				[ ] list of string lsContents = this.GetContents()
				[ ] string sStart = null
				[+] for each sStart in lsContents
					[+] if (StrPos(upper(lsTarg[1]),upper(sStart)) != 0)
						[ ] this.Select(sStart)
						[ ] sStart = this.GetSelText()
						[ ] break
					[+] else
						[ ] sStart = null
				[ ] // Desktop Folder Exists, expand at most 2 levels to search lsTarg[1]
				[+] if (sStart == null)
					[ ] int iCount1 = ListCount(this.GetContents())
					[ ] int iCount2
					[+] if (iCount1 == 1)
						[ ] this.Expand("#1") // Expand the "Desktop Folder"
						[ ] iCount1 = ListCount(this.GetContents())
					[ ] int i = 2 // loop from the second item
					[+] while (i <= ListCount(this.GetContents()))
						[ ] this.Select("#{i}")
						[+] do
							[ ] this.Expand("#{i}")
						[+] except
							[ ] i++
							[ ] continue
						[ ] iCount2 = ListCount(this.GetContents())
						[ ] int j
						[+] for (j = i + 1; j <= i + iCount2 - iCount1; j ++)
							[ ] this.Select("#{j}")
							[ ] sStart = this.GetSelText()
							[+] if (StrPos(upper(lsTarg[1]),upper(sStart)) != 0)
								[ ] break
							[+] else
								[+] do
									[ ] this.Collapse("#{j}")
								[+] except
									[ ] 
								[ ] sStart = null
						[+] if (sStart != null)
							[ ] break
						[+] else
							[+] do
								[ ] this.Collapse("#{i}")
							[+] except
								[ ] 
						[ ] i++
				[+] if (sStart == null)
					[ ] gllog.Error("Path error!")
				[ ] 
				[ ] // building new selectable path in treeview
				[ ] int k = 2
				[+] while (k <= ListCount(lsTarg))
					[ ] sStart += "/{lsTarg[k]}"
					[ ] k++
				[ ] 
				[ ] return glTreeViewSelector(this,sStart,"/")
		[ ] 
		[ ] 
	[ ] 
	[+] // message box and buttons
		[+] winclass			glwcBtnYes				:			PushButton
			[+] multitag "Yes*"
				[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/Yes"
				[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/はい(Y)"
				[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/是(Y)"
				[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/Ja"
				[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/예(Y)"
				[ ] "はい*"
				[ ] "是*"
				[ ] "Ja*"
				[ ] "예*"
			[+] // mswvista multitag "Yes*"
				[ ] // "はい*"
				[ ] // "是*"
				[ ] // "Ja*"
				[ ] // "예*"
			[+] // msw2003 multitag "Yes*"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/Yes"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/はい(Y)"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/是(Y)"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/Ja"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/예(Y)"
				[ ] // "はい*"
				[ ] // "是*"
				[ ] // "Ja*"
				[ ] // "예*"
		[ ] 
		[+] winclass			glwcBtnNo					:			PushButton
			[+] multitag "No*"
				[ ] "いいえ*"
				[ ] "否*"
				[ ] "Nein*"
				[ ] "아니요*"
			[+] // mswvista multitag "No*"
				[ ] // "いいえ*"
				[ ] // "否*"
				[ ] // "Nein*"
				[ ] // "아니요*"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/No"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/いいえ(N)"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/否(N)"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/Nein"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/아니오(N)"
			[+] // msw2003 multitag "No*"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/No"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/いいえ(N)"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/否(N)"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/Nein"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/아니오(N)"
				[ ] // "いいえ*"
				[ ] // "否*"
				[ ] // "Nein*"
				[ ] // "아니요*"
		[ ] 
		[+] winclass			glwcBtnOK				:			PushButton
			[+] multitag "OK*"
				[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/OK"
				[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/OK"
				[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/确定"
				[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/확인"
				[ ] "确定*"
				[ ] "확인*"
			[+] // mswvista multitag "OK*"
				[ ] // "确定*"
				[ ] // "확인*"
			[+] // msw2003 multitag "OK*"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/OK"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/OK"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/确定"
				[ ] // // "[DirectUIHWND]#1/[CtrlNotifySink]#1/확인"
				[ ] // "确定*"
				[ ] // "확인*"
		[ ] 
		[+] winclass			glwcBtnCancel			:			PushButton
			[+] multitag "Cancel*"
				[ ] "キャンセル*"
				[ ] "取消*"
				[ ] "Abbrechen*"
				[ ] "취소*"
			[+] // mswvista multitag "Cancel*"
				[ ] // "キャンセル*"
				[ ] // "取消*"
				[ ] // "Abbrechen*"
				[ ] // "취소*"
			[+] // msw2003 multitag "Cancel*"
				[ ] // "キャンセル*"
				[ ] // "取消*"
				[ ] // "Abbrechen*"
				[ ] // "취소*"
		[ ] 
		[+] winclass			glwcBtnApply				:			PushButton
			[+] multitag "Apply*"
				[ ] "適用*"
				[ ] "应用*"
				[ ] "Übernehmen*"
				[ ] "적용*"
			[+] // mswvista multitag "Apply*"
				[ ] // "適用*"
				[ ] // "应用*"
				[ ] // "Übernehmen*"
				[ ] // "적용*"
			[+] // msw2003 multitag "Apply*"
				[ ] // "適用*"
				[ ] // "应用*"
				[ ] // "Übernehmen*"
				[ ] // "적용*"
		[ ] 
		[+] winclass			glwcBtnHelp				:			PushButton
			[+]  multitag "Help*"
				[ ] "ヘルプ*"
				[ ] "帮助*"
				[ ] "Hilfe*"
				[ ] "도움말*"
			[+] // mswvista multitag "Help*"
				[ ] // "ヘルプ*"
				[ ] // "帮助*"
				[ ] // "Hilfe*"
				[ ] // "도움말*"
			[+] // msw2003 multitag "Help*"
				[ ] // "ヘルプ*"
				[ ] // "帮助*"
				[ ] // "Hilfe*"
				[ ] // "도움말*"
		[ ] 
		[+] winclass			glwcMessageBox			:			DialogBox
			[ ] glwcBtnYes btnYes
			[ ] glwcBtnNo btnNo
			[ ] glwcBtnOK btnOK
			[ ] glwcBtnCancel btnCancel
			[ ] glwcBtnApply btnApply
			[ ] glwcBtnHelp btnHelp
			[+] list of string getStaticTexts()
				[ ] int i
				[ ] list of string lsContents, lsResults
				[ ] this.SetActive()
				[ ] lsContents = this.GetContents()
				[+] for(i=1;i<ListCount(lsContents)+1;i++)
					[+] if( StrPos("[StaticText]", lsContents[i])!=0 )
						[ ] ListAppend( lsResults, this.StaticText(lsContents[i]).GetTag() )
				[ ] return lsResults
	[ ] 
	[+] // command dialog
		[+] winclass			glwcCMDWindow			:			DialogBox
			[+] //--------------------------------------------------------- GUI - --------------------------------------------------------//
				[+] DialogBox dlgContextMenu
					[ ] tag "#1"
			[+] //------------------------------------------------------- Method -------------------------------------------------------//
				[+] boolean OpenContextMenu()
					[+] if (this.dlgContextMenu.Exists() == false)
						[ ] this.TypeKeys("<Alt-Space>")
						[+] if (glWaitForExists(this.dlgContextMenu) == false)
							[ ] return false
						[+] else
							[ ] return true
					[+] else
						[ ] return true
				[+] void PickContextMenu(string str)
					[+] if (this.OpenContextMenu() == true)
						[+] switch str
							[+] case "Restore"
								[ ] this.TypeKeys("<Enter>")
							[+] case "Move"
								[ ] this.TypeKeys("<down><Enter>")
							[+] case "Size"
								[ ] this.TypeKeys("<down 2><Enter>")
							[+] case "Minimize"
								[ ] this.TypeKeys("<down 3><Enter>")
							[+] case "Maximize"
								[ ] this.TypeKeys("<down 4><Enter>")
							[+] case "Close"
								[ ] this.TypeKeys("<down 5><Enter>")
							[+] case "Mark"
								[ ] this.TypeKeys("<down 6><right><Enter>")
							[+] case "Copy"
								[ ] this.TypeKeys("<down 6><right><down><Enter>")
							[+] case "Paste"
								[ ] this.TypeKeys("<down 6><right><down 2><Enter>")
							[+] case "Select All"
								[ ] this.TypeKeys("<down 6><right><down 3><Enter>")
							[+] case "Scoll"
								[ ] this.TypeKeys("<down 6><right><down 4><Enter>")
							[+] case "Find"
								[ ] this.TypeKeys("<down 6><right><down 5><Enter>")
							[+] case "Default"
								[ ] this.TypeKeys("<down 7><Enter>")
							[+] case "Properties"
								[ ] this.TypeKeys("<down 8><Enter>")
				[+] list of string GetCMDContents()
					[ ] this.PickContextMenu("Select All")
					[ ] this.PickContextMenu("Copy")
					[ ] return Clipboard.GetText()
				[+] boolean WaitForFinish(int iTimeout optional, int iHop optional)
					[+] if (iTimeout == null)
						[ ] iTimeout = 60
					[+] if (iHop == null)
						[ ] iHop = 10
					[ ] int i = 0
					[ ] int iOldLineNum
					[ ] int iNewLineNum
					[+] while (i < iTimeout)
						[ ] iOldLineNum = ListCount(this.GetCMDContents())
						[ ] sleep(iHop)
						[ ] iNewLineNum = ListCount(this.GetCMDContents())
						[+] if (iOldLineNum == iNewLineNum)
							[ ] return true
						[+] else
							[ ] i += iHop
					[ ] return false
				[+] void ExecuteCommand(string str)
					[ ] this.TypeKeys("{str}<Enter>")
				[+] void TurnToDirectory(string sPath)
					[ ] this.ExecuteCommand("cd /d {sPath}")
	[ ] 
	[ ] 
[ ] 
[-] //--------------------------------------------------------------------------------- common window ------------------------------------------------------------------------------------------//
	[+] // StartMenu
		[+] private			window			DialogBox			dlgMenuContent
			[ ] tag "~"
			[+] CustomWin Menu  
				[ ] tag "[MenuSite]#1"
				[+] ToolBar bar
					[ ] tag "#1"
					[+] PushButton btnPrograms
						[+] multitag "Programs"
							[ ] "プログラム(P)"
							[ ] "程序(P)"
							[ ] "Programme"
							[ ] "프로그램(P)"
						[+] // mswvista multitag "Programs"
							[ ] // "プログラム(P)"
							[ ] // "程序(P)"
							[ ] // "Programme"
							[ ] // "프로그램(P)"
						[+] // msw2003 multitag "Programs"
							[ ] // "プログラム(P)"
							[ ] // "程序(P)"
							[ ] // "Programme"
							[ ] // "프로그램(P)"
					[+] PushButton btnRun
						[+] multitag "Run"
							[ ] "ファイル名を指定して実行(R)"
							[ ] "运行(R)"
							[ ] "Ausführen"
							[ ] "실행(R)"
						[+] // mswvista multitag "Run"
							[ ] // "ファイル名を指定して実行(R)"
							[ ] // "运行(R)"
							[ ] // "Ausführen"
							[ ] // "실행(R)"
						[+] // msw2003 multitag "Run"
							[ ] // "ファイル名を指定して実行(R)"
							[ ] // "运行(R)"
							[ ] // "Ausführen"
							[ ] // "실행(R)"
		[ ] 
		[+] private			window			DialogBox			dlgNewStartMenu
			[ ] tag "Start menu"
			[+] ListView lstRecentPrograms
				[ ] tag "[DesktopProgramsMFU]#1/#1"
			[+] TreeView trvAllPrograms
				[ ] tag "[Desktop NSCHost]#1/[NamespaceTreeControl]All Programs/#1"
			[+] PushButton btnAllprograms
				[ ] tag "[Desktop More Programs Pane]#1/[PushButton]All Programs"
			[+] TextField txtSearchBox
				[ ] tag "[Desktop OpenBox Host]#1/[Search Box]#1/[SearchEditBoxWrapperClass]#1/[DirectUIHWND]#1"
		[ ] 
		[+] private			winclass			dlgCommandNotFound			:			DialogBox    // command not found "c:\not_exists"
			[+] property btnOK
				[+] window get()
					[+] if (this.CustomWin("[DirectUIHWND]#1").CustomWin("[CtrlNotifySink]#1").PushButton("#1").Exists())
						[ ] return this.CustomWin("[DirectUIHWND]#1").CustomWin("[CtrlNotifySink]#1").PushButton("#1")
					[+] if (this.PushButton("#1").Exists())
						[ ] return this.PushButton("#1")
				[ ] 
			[+] // PushButton btnOK
				[+] // mswxp multitag "OK"
					[ ] // "确定"
					[ ] // "확인"
				[+] // mswvista multitag "[DirectUIHWND]#1/[CtrlNotifySink]#1/OK"
					[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/确定"
					[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/확인"
				[+] // msw2003 multitag "OK"
					[ ] // "确定"
					[ ] // "확인"
		[ ] 
		[+] window			DialogBox			gldlgRun
			[+] multitag "Run"
				[ ] "ファイル名を指定して実行"
				[ ] "运行"
				[ ] "Ausführen"
				[ ] "실행"
			[+] ComboBox cboOpen
				[ ] tag "#1"
				[+] // mswxp multitag "Open:"
					[ ] // "名前(O):"
					[ ] // "打开(O):"
					[ ] // "Öffnen:"
					[ ] // "열기(O):"
				[+] // mswvista multitag "Type the name of a program, folder, document, or Internet resource, and Windows will open it for you." // !!!!!
					[ ] // "名前(O):"
					[ ] // "打开(O):" // ok
					[ ] // "Geben Sie den Namen eines Programms, Ordners, Dokuments oder einer Internetressource an."//"Öffnen:"
					[ ] // "열기(O):"
				[+] // msw2003 multitag "Open:"
					[ ] // "名前(O):"
					[ ] // "打开(O):"
					[ ] // "Öffnen:"
					[ ] // "열기(O):"
			[+] PushButton btnOK
				[ ] tag "#1"
				[+] // mswxp multitag "OK"
					[ ] // "确定"
					[ ] // "확인"
				[+] // mswvista multitag "OK"
					[ ] // "确定"
					[ ] // "확인"
				[+] // msw2003 multitag "OK"
					[ ] // "确定"
					[ ] // "확인"
			[+] DialogBox	dlgLocationNotFound      // location not found "c:\not exists\anything"
				[ ] tag "$MessageBox"
				[+] // mswxp multitag "Run"
					[ ] // "ファイル名を指定して実行"
					[ ] // "运行"
					[ ] // "Ausführen"
					[ ] // "실행"
				[ ] // mswvista multitag "$MessageBox"
				[+] PushButton btnOK
					[ ] tag "#1"
					[+] // mswxp multitag "OK"
						[ ] // "确定"
						[ ] // "확인"
					[+] // mswvista multitag "[DirectUIHWND]#1/[CtrlNotifySink]#1/OK"
						[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/确定"
						[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/확인"
					[+] // msw2003 multitag "OK"
						[ ] // "确定"
						[ ] // "확인"
	[ ] 
	[+] // TaskManager
		[+] window			MainWin			glwTaskManager
			[+] multitag "[DialogBox]Windows Task Manager"
				[ ] "[DialogBox]Windows タスク マネージャ"
				[ ] "[DialogBox]Windows 任务管理器"
				[ ] "[DialogBox]Windows Task-Manager"
				[ ] "[DialogBox]Windows 작업 관리자"
			[+] // mswvista multitag "[DialogBox]Windows Task Manager"
				[ ] // "[DialogBox]Windows タスク マネージャ"
				[ ] // "[DialogBox]Windows 任务管理器"
				[ ] // "[DialogBox]Windows Task-Manager"
				[ ] // "[DialogBox]Windows 작업 관리자"
			[+] // msw2003 multitag "[DialogBox]Windows Task Manager"
				[ ] // "[DialogBox]Windows タスク マネージャ"
				[ ] // "[DialogBox]Windows 任务管理器"
				[ ] // "[DialogBox]Windows Task-Manager"
				[ ] // "[DialogBox]Windows 작업 관리자"
			[+] //-------------------------------------------------------- Const ---------------------------------------------------------//
				[ ] const		sDir = "{glsWINDIR}\system32"
				[ ] const		sCmdLine = "{glsWINDIR}\system32\taskmgr.exe"
			[+] //-------------------------------------------------------- Menu  --------------------------------------------------------//
				[+] Menu mnuFile
					[+] multitag "File"
						[ ] "ファイル(F)"
						[ ] "文件(F)"
						[ ] "Datei"
						[ ] "파일(F)"
					[+] // mswvista multitag "File"
						[ ] // "ファイル(F)"
						[ ] // "文件(F)"
						[ ] // "Datei"
						[ ] // "파일(F)"
					[+] // msw2003 multitag "File"
						[ ] // "ファイル(F)"
						[ ] // "文件(F)"
						[ ] // "Datei"
						[ ] // "파일(F)"
					[+] MenuItem miExitTaskManager
						[+] mswxp multitag "Exit Task Manager"
							[ ] "タスク マネージャの終了(X)"
							[ ] "退出任务管理器(X)"
							[ ] "Beenden"
							[ ] "작업 관리자 끝내기(X)"
						[+] mswvista multitag "Exit Task Manager"
							[ ] "タスク マネージャの終了(X)"
							[ ] "退出任务管理器(X)"
							[ ] "Beenden"
							[ ] "작업 관리자 끝내기(X)"
						[+] msw2003 multitag "Exit Task Manager"
							[ ] "タスク マネージャの終了(X)"
							[ ] "退出任务管理器(X)"
							[ ] "Beenden"
							[ ] "작업 관리자 끝내기(X)"
				[+] Menu mnuView
					[+] multitag "View"
						[ ] "表示(V)"
						[ ] "查看(V)"
						[ ] "Ansicht"
						[ ] "보기(V)"
					[+] // mswvista multitag "View"
						[ ] // "表示(V)"
						[ ] // "查看(V)"
						[ ] // "Ansicht"
						[ ] // "보기(V)"
					[+] // msw2003 multitag "View"
						[ ] // "表示(V)"
						[ ] // "查看(V)"
						[ ] // "Ansicht"
						[ ] // "보기(V)"
					[+] MenuItem miRefreshNow
						[+] multitag "Refresh Now"
							[ ] "最新の情報に更新(R)"
							[ ] "立即刷新(R)"
							[ ] "Aktualisieren"
							[ ] "지금 새로 고침(R)"
						[+] // mswvista multitag "Refresh Now"
							[ ] // "最新の情報に更新(R)"
							[ ] // "立即刷新(R)"
							[ ] // "Aktualisieren"
							[ ] // "지금 새로 고침(R)"
						[+] // msw2003 multitag "Refresh Now"
							[ ] // "最新の情報に更新(R)"
							[ ] // "立即刷新(R)"
							[ ] // "Aktualisieren"
							[ ] // "지금 새로 고침(R)"
					[+] Menu mnuUpdateSpeed
						[+] multitag "Update Speed"
							[ ] "更新の頻度(U)"
							[ ] "更新速度(U)"
							[ ] "Aktualisierungsgeschwindigkeit"
							[ ] "업데이트 속도(U)"
						[+] // mswvista multitag "Update Speed"
							[ ] // "更新の頻度(U)"
							[ ] // "更新速度(U)"
							[ ] // "Aktualisierungsgeschwindigkeit"
							[ ] // "업데이트 속도(U)"
						[+] // msw2003 multitag "Update Speed"
							[ ] // "更新の頻度(U)"
							[ ] // "更新速度(U)"
							[ ] // "Aktualisierungsgeschwindigkeit"
							[ ] // "업데이트 속도(U)"
						[+] MenuItem miPaused
							[+] multitag "Paused"
								[ ] "一時停止(P)"
								[ ] "暂停(P)"
								[ ] "Angehalten"
								[ ] "일시 중지됨(P)"
							[+] // mswvista multitag "Paused"
								[ ] // "一時停止(P)"
								[ ] // "暂停(P)"
								[ ] // "Angehalten"
								[ ] // "일시 중지됨(P)"
							[+] // msw2003 multitag "Paused"
								[ ] // "一時停止(P)"
								[ ] // "暂停(P)"
								[ ] // "Angehalten"
								[ ] // "일시 중지됨(P)"
			[+] //-------------------------------------------------------- Dialog  -------------------------------------------------------//
				[+] PageList		plTab
					[ ] tag "#1"
				[+] DialogBox		dlgPrcs
					[ ] tag "#1"		
					[+] ListView	lstPrcs
						[ ] tag "#1"
					[+] PushButton btnEndProcess
						[+] mswxp multitag "End Process"
							[ ] "プロセスの終了(E)"
							[ ] "结束进程(E)"
							[ ] "Prozess beenden"
							[ ] "프로세스 끝내기(E)"
						[+] // mswvista multitag "End Process"
							[ ] // "プロセスの終了(E)"
							[ ] // "结束进程(E)"
							[ ] // "Prozess beenden"
							[ ] // "프로세스 끝내기(E)"
						[+] // msw2003 multitag "End Process"
							[ ] // "プロセスの終了(E)"
							[ ] // "结束进程(E)"
							[ ] // "Prozess beenden"
							[ ] // "프로세스 끝내기(E)"
				[+] DialogBox 	dlgWarning
					[+] multitag "Task Manager Warning"
						[ ] "タスク マネージャの警告"
						[ ] "任务管理器警告"
						[ ] "Warnung vom Task-Manager"
						[ ] "작업 관리자 경고"
						[ ] //mswvista multitag 
						[ ] "Windows Task Manager"
						[ ] "Windows タスク マネージャ"
						[ ] "Windows 任务管理器"
						[ ] "Windows Task-Manager"
						[ ] "Windows 작업 관리자"
					[+] // msw2003 multitag "Task Manager Warning"
						[ ] // "タスク マネージャの警告"
						[ ] // "任务管理器警告"
						[ ] // "Warnung vom Task-Manager"
						[ ] // "작업 관리자 경고"
					[+] property btnYes
						[+] window get()
							[+] if (this.CustomWin("[DirectUIHWND]#1").CustomWin("[CtrlNotifySink]#1").PushButton("#1").Exists())
								[ ] return this.CustomWin("[DirectUIHWND]#1").CustomWin("[CtrlNotifySink]#1").PushButton("#1")
							[+] if (this.PushButton("#1").Exists())
								[ ] return this.PushButton("#1")
					[+] // PushButton	btnYes
						[+] // mswxp multitag "Yes"
							[ ] // "はい(Y)"
							[ ] // "是(Y)"
							[ ] // "Ja"
							[ ] // "예(Y)"
						[+] // mswvista multitag "[DirectUIHWND]#1/[CtrlNotifySink]#1/End process"
							[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/プロセスの終了"
							[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/结束进程"
							[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/Prozess beenden"
							[ ] // "[DirectUIHWND]#1/[CtrlNotifySink]#1/프로세스 끝내기"
						[+] // msw2003 multitag "Yes"
							[ ] // "はい(Y)"
							[ ] // "是(Y)"
							[ ] // "Ja"
							[ ] // "예(Y)"
				[+] DialogBox 	dlgUnTerminate
					[+] multitag "Unable to Terminate Process"
						[ ] "无法中止进程"
						[ ] "Abbrechen des Prozesses nicht möglich"
						[ ] "プロセスを終了できません"
						[ ] "프로세스를 종료할 수 없습니다."
					[+] // mswvista multitag "Unable to Terminate Process"
						[ ] // "无法中止进程"
						[ ] // "Abbrechen des Prozesses nicht möglich"
						[ ] // "プロセスを終了できません"
						[ ] // "프로세스를 종료할 수 없습니다."
					[+] // msw2003 multitag "Unable to Terminate Process"
						[ ] // "无法中止进程"
						[ ] // "Abbrechen des Prozesses nicht möglich"
						[ ] // "プロセスを終了できません"
						[ ] // "프로세스를 종료할 수 없습니다."
					[+] PushButton btnOK
						[+] multitag "OK"
							[ ] "确定"
							[ ] "확인"
						[+] // mswvista multitag "OK"
							[ ] // "确定"
							[ ] // "확인"
						[+] // msw2003 multitag "OK"
							[ ] // "确定"
							[ ] // "확인"
			[+] //-------------------------------------------------------- Method  ------------------------------------------------------//
				[+] void RefreshList()
					[ ] this.SetActive()
					[ ] this.mnuView. miRefreshNow.Pick()
					[ ] this.SetActive()
				[+] void EndFromProcess( list of string lsKeys)
					[ ] integer i, j, iNum
					[ ] list of string lsContents
					[ ] this.SetActive()
					[ ] this.Maximize()
					[ ] plTab.Select( "#2" )           // select process/ tab
					[ ] this.mnuView.mnuUpdateSpeed.miPaused.Pick()
					[+] for(i=1;i<ListCount(lsKeys)+1;i++)
						[ ] RefreshList()
						[ ] lsContents = dlgPrcs.lstPrcs.GetContents()
						[+] for(j=1;j<ListCount(lsContents)+1;j++)
							[+] if( StrPos( lsKeys[i], GetField( lsContents[j], ";", 1))!=0 )
								[ ] dlgPrcs.lstPrcs.Select( GetField( lsContents[j], ";", 1) )
								[ ] dlgPrcs.btnEndProcess.Click()
								[+] if( glWaitForExists(dlgWarning,3))
									[ ] dlgWarning.SetActive()
									[ ] dlgWarning.btnYes.Click()
									[+] if (dlgUnTerminate.Exists(2))
										[ ] dlgUnTerminate.btnOK.Click()
									[+] // if (sOSType== "xp")
										[+] // if(glWaitForExists(dlgUnTerminate,2))
											[ ] // dlgUnTerminate.SetActive()
											[ ] // dlgUnTerminate.btnOK.Click()
									[+] // if (sOSType== "vista")
										[+] // if (glWaitForExists(gl_wMicrosoftWindows,5))
											[ ] // gl_wMicrosoftWindows.SetActive()
											[+] // if (glWaitForExists(gl_wMicrosoftWindows.btnCloseProgram))
												[ ] // gl_wMicrosoftWindows.btnCloseProgram.click()
								[+] if( glWaitForExists(glwcMessageBox("{lsKeys[i]}*"),3))
									[ ] glwcMessageBox("{lsKeys[i]}*").SetActive()
									[ ] glwcMessageBox("{lsKeys[i]}*").btnOK.Click()
									[+] if (dlgUnTerminate.Exists(2))
										[ ] dlgUnTerminate.btnOK.Click()
									[+] // if (sOSType== "xp")
										[+] // if(glWaitForExists(dlgUnTerminate,2))
											[ ] // dlgUnTerminate.SetActive()
											[ ] // dlgUnTerminate.btnOK.Click()
									[+] // if (sOSType== "vista")
										[+] // if (glWaitForExists(gl_wMicrosoftWindows,5))
											[ ] // gl_wMicrosoftWindows.SetActive()
											[+] // if (glWaitForExists(gl_wMicrosoftWindows.btnCloseProgram))
												[ ] // gl_wMicrosoftWindows.btnCloseProgram.click()
								[ ] RefreshList()
					[ ] this.SetActive()
				[+] boolean ProcessExists(string sPcs)
					[ ] integer i, j
					[ ] list of string lsContents
					[ ] this.SetActive()
					[ ] plTab.Select( "#2" )           // select process  tab
					[ ] RefreshList()
					[ ] lsContents = dlgPrcs.lstPrcs.GetContents()
					[+] for(j=1;j<ListCount(lsContents)+1;j++)
						[+] if( StrPos(sPcs, GetField( lsContents[j], ";", 1))!=0 )
							[ ] return true
					[ ] return false
		[ ] 
		[+] window			DialogBox		gldlgMicrosoftWindows
			[ ] mswvista tag "Microsoft Windows"
			[+] PushButton btnCloseProgram
				[+] mswvista multitag "[DirectUIHWND]#1/[CtrlNotifySink]#2/#1"
					[ ] "[DirectUIHWND]#1/[CtrlNotifySink]#2/[Button]#1"
	[ ] 
	[+] // notepad
		[+] window			MainWin		glwNotepad
			[ ] tag "*Notepad*|${glsWINDIR}\sys*\notepad.exe"
			[ ] locator "/MainWin[@caption='*Notepad*']"
			[+] //-------------------------------------------------------- Const ---------------------------------------------------------//
				[ ] const 		sCmdLine = "{glsWINDIR}\system32\notepad.exe"
				[ ] const		sDir = "{glsWINDIR}\system32"
			[+] //-------------------------------------------------------- Menu  --------------------------------------------------------//
				[+] Menu mnuFile
					[ ] tag "#1"
					[+] MenuItem miNew
						[ ] tag "#1"
					[+] MenuItem miOpen
						[ ] tag "#2"
					[+] MenuItem miSave
						[ ] tag "#3"
					[+] MenuItem miSaveAs
						[ ] tag "#4"
					[+] MenuItem miExit
						[ ] tag "#7"
				[+] Menu mnuEdit
					[ ] tag "#2"
					[+] MenuItem miUndo
						[ ] tag "#1"
					[+] MenuItem miCut
						[ ] tag "#2"
					[+] MenuItem miCopy
						[ ] tag "#3"
					[+] MenuItem miPaste
						[ ] tag "#4"
					[+] MenuItem miDelete
						[ ] tag "#5"
					[+] MenuItem miFind
						[ ] tag "#6"
					[+] MenuItem miFindNext
						[ ] tag "#7"
					[+] MenuItem miReplace
						[ ] tag "#8"
					[+] MenuItem miGoTo
						[ ] tag "#9"
					[+] MenuItem miSelectAll
						[ ] tag "#10"
					[+] MenuItem miTimeDate
						[ ] tag "#11"
				[+] Menu mnuFormat
					[ ] tag "#3"
					[+] MenuItem miWordWrap
						[ ] tag "#1"
					[+] MenuItem miFont
						[ ] tag "#2"
				[+] TextField txtContends
					[ ] tag "#1"
				[+] MenuItem muiSelectAll
					[ ] locator "//MenuItem[@caption='Select All']"
			[+] //-------------------------------------------------------- Dialog  -------------------------------------------------------//
				[ ] glwcDlgOpenFile dlgOpenFile
				[ ] glwcDlgSaveFile dlgSaveFile
				[+] DialogBox dlgReplace
					[ ] tag "#1"
					[+] TextField txtFindWhat
						[ ] tag "#1"
						[+] SetText(string str)
							[ ] this.Click()
							[ ] this.TypeKeys(str)
					[+] TextField txtReplaceWith
						[ ] tag "#2"
						[+] SetText(string str)
							[ ] this.Click()
							[ ] this.TypeKeys(str)
					[+] PushButton btnFindNext
						[ ] tag "#1"
					[+] PushButton btnReplace
						[ ] tag "#2"
					[+] PushButton btnReplaceAll
						[ ] tag "#3"
					[+] PushButton btnCancel
						[ ] tag "#4"
					[+] CheckBox chkMatchCase
						[ ] tag "#1"
				[+] DialogBox dlgNotepad
					[ ] tag "#1"
					[+] PushButton btnYes
						[ ] mswxp tag "#1"
						[ ] mswvista tag "[DirectUIHWND]#1/[CtrlNotifySink]#1/#1"
						[ ] msw2003 tag "#1"
					[+] PushButton btnNo
						[ ] mswxp tag "#2"
						[ ] mswvista tag "[DirectUIHWND]#1/[CtrlNotifySink]#2/#1"
						[ ] msw2003 tag "#2"
					[+] PushButton btnCancel
						[ ] mswxp tag "#3"
						[ ] mswvista tag "[DirectUIHWND]#1/[CtrlNotifySink]#3/#1"
						[ ] msw2003 tag "#3"
			[+] //-------------------------------------------------------- Method  ------------------------------------------------------//
				[+] OpenFile(string sPath)
					[+] if (this.dlgOpenFile.Exists() == false)
						[ ] this.SetActive()
						[ ] this.mnuFile.miOpen.Pick()
					[+] if (glWaitForExists(this.dlgOpenFile) == false)
						[ ] RaiseError(-255,"Exception in OpenFile")
					[ ] this.dlgOpenFile.SetActive()
					[ ] this.dlgOpenFile.OpenFile(sPath)
				[+] SaveFile(string sPath)
					[+] if (this.dlgOpenFile.Exists() == false)
						[ ] this.SetActive()
						[ ] this.mnuFile.miSaveAs.Pick()
						[ ] sleep(2)
					[+] if (glWaitForExists(this.dlgSaveFile) == false)
						[ ] RaiseError(-255,"Exception in SaveFile")
					[ ] this.dlgSaveFile.SetActive()
					[ ] this.dlgSaveFile.SaveFile(sPath)
		[ ] 
		[+] window			DialogBox		gldlgLicenseManager
			[ ] tag "Aspen Technology License Manager - Reminder"
			[ ] locator "/Dialog[@caption='Aspen Technology License Manager - Reminder']"
			[+] PushButton		btnSnooze
				[ ] locator "//PushButton[@caption='Snooze']"
	[ ] 
	[-] //Aspen Energy Analyzer
		[-] window			MainWin		glwAEA
			[ ] tag "*Aspen Energy Analyzer*|${sProgramFilePath}\AspenTech\Aspen Energy Analyzer{sVersion}\concepts.exe"
			[ ] locator "/MainWin[@caption='*Aspen Energy Analyzer {sVersion} - aspenONE*']"
			[-] //-------------------------------------------------------- Const ---------------------------------------------------------//
				[ ] const 		sCmdLine = "{sProgramFilePath}\AspenTech\Aspen Energy Analyzer{sVersion}\concepts.exe"
				[ ] const		sDir = "{sProgramFilePath}\AspenTech\Aspen Energy Analyzer{sVersion}"
			[+] //-------------------------------------------------------- Control  --------------------------------------------------------//
				[+] WPFTreeView trvPartTree
					[ ] locator "//TreeView"
				[+] TextField	txtName
					[ ] locator "//TextField[@caption='Name']"
				[+] MainWin		mwMain
					[ ] locator "//MainWin[@caption='HI Project:*']"
				[+] DialogBox	dlgAspenEnergyAnalyzer
					[ ] locator "//DialogBox[@caption='Aspen Energy Analyzer']"
					[+] PushButton	btnYes
						[ ] locator "//PushButton[@caption='Yes']"
					[+] PushButton	btnNo
						[ ] locator "//PushButton[@caption='No']"
					[ ] 
				[+] Control		ctrlToolBar
					[ ] locator "//Control[@windowClassName='HCustomControl'][2]"
			[+] //-------------------------------------------------------- Method  ------------------------------------------------------//
				[ ] 
	[ ] 
	[-] //Aspen Flare System Analyzer
		[-] window			MainWin		glwFlarenet
			[ ] tag "*Aspen Flare System Analyzer*|${sProgramFilePath}\AspenTech\Aspen Flare System Analyzer {sVersion}\AspenFlareSystemAnalyzer.exe"
			[ ] locator "/WPFWindow[@caption='*Aspen Flare System Analyzer {sVersion} - aspenONE']"
			[-] //-------------------------------------------------------- Const ---------------------------------------------------------//
				[ ] const 		sCmdLine = "{sProgramFilePath}\AspenTech\Aspen Flare System Analyzer {sVersion}\AspenFlareSystemAnalyzer.exe"
				[ ] const		sDir = "{sProgramFilePath}\AspenTech\Aspen Flare System Analyzer {sVersion}"
			[+] //-------------------------------------------------------- Control  --------------------------------------------------------//
				[ ] //Menu
				[+] Menu mnuFile
					[ ] locator "//WPFMenuItem[@caption='File']"
					[ ] 
				[ ] //Dialog
				[+] DialogBox dlgSaveConfirm
					[ ] locator "//DialogBox[@caption='Aspen Flare System Analyzer']"
					[+] PushButton	btnNo
						[ ] locator "//PushButton[@caption='No']"
				[ ] 
				[ ] 
			[+] //-------------------------------------------------------- Method  ------------------------------------------------------//
				[ ] 
		[+] window 			DialogBox	gldImportAspenPlusSources
			[ ] locator "/WPFWindow[@caption='Import Aspen Plus Sources']"
			[+] WPFButton		btnBrowse
				[ ] locator "//WPFButton[@automationId='UltraButtonBrowse']"
			[+] DialogBox		dlgAspenPlusModelFile
				[ ] locator "//DialogBox[@caption='Aspen Plus Model File']"
				[+] PushButton	btnOpen
					[ ] locator "//PushButton[@caption='Open']"
				[+] ComboBox	cboFileName
					[ ] locator "//ComboBox[@caption='File name:']"
			[+] WPFButton		btnOpen
				[ ] locator "//WPFButton[@automationId='UltraButtonOpen']"
			[+] WPFButton		btnOK
				[ ] locator "//WPFButton[@automationId='UltraButtonOK']"
	[ ] 
	[+] //CompareEDR
		[+] window			MainWin		glwCompareEDR
			[ ] tag "CompareEDR|${sAspenPlus_sProjectDir}\data\datain\CQ00417644\EDRCompareTool\CompareEDRFiles.exe"
			[ ] locator "/FormsWindow[@caption='CompareEDR']"
			[+] //-------------------------------------------------------- Const ---------------------------------------------------------//
				[ ] const 		sCmdLine = "{sAspenPlus_sProjectDir}\data\datain\CQ00417644\EDRCompareTool\CompareEDRFiles.exe"
				[ ] const		sDir = "{sAspenPlus_sProjectDir}\data\datain\CQ00417644\EDRCompareTool"
			[+] //-------------------------------------------------------- Control  --------------------------------------------------------//
				[+] TextField	txtBaseFile
					[ ] locator "//TextField[@automationId='txtBaseFile']"
				[+] TextField	txtCurrentFile
					[ ] locator "//TextField[@automationId='txtCurrentFile']"
				[+] TextField	txtDiffFileLocation
					[ ] locator "//TextField[@automationId='txtLogLoc']"
				[+] PushButton	btnBaseFileBrowse
					[ ] locator "//PushButton[@automationId='button4']"
				[+] PushButton	btnCurrentFileBrowse
					[ ] locator "//PushButton[@automationId='button3']"
				[+] PushButton	btnDiffFileBrowse
					[ ] locator "//PushButton[@automationId='button8']"
				[+] PushButton	btnCompare
					[ ] locator "//PushButton[@automationId='button5']"
				[+] PushButton	btnViewDiff
					[ ] locator "//PushButton[@caption='View Differences']"
				[+] StaticText	txtFindDifference
					[ ] locator "//StaticText[@caption='Comparsion finished with difference!']"
			[+] //-------------------------------------------------------- Dialog  -------------------------------------------------------//
				[+] DialogBox	dlgCompareFinish
					[ ] locator "//DialogBox"
					[+] PushButton	btnOK
						[ ] locator "//PushButton[@caption='OK']"
			[+] //-------------------------------------------------------- Method  ------------------------------------------------------//
				[+] void CompareEDRFiles(string sLeft,string sRight,string sOutput)
					[+] if(!this.btnCompare.Exists(3))
						[ ] this.SetActive()
						[ ] this.TypeKeys("<Right>")
						[ ] sleep(1)
					[ ] this.txtBaseFile.Click()
					[ ] this.txtBaseFile.SetText(sLeft)
					[ ] sleep(1)
					[ ] this.txtCurrentFile.Click()
					[ ] this.txtCurrentFile.SetText(sRight)
					[ ] sleep(1)
					[ ] this.txtDiffFileLocation.Click()
					[ ] this.txtDiffFileLocation.SetText(sOutput)
					[ ] sleep(1)
					[ ] this.btnCompare.Click()
					[+] if(this.dlgCompareFinish.Exists(2000))
						[ ] this.dlgCompareFinish.SetActive()
						[ ] this.dlgCompareFinish.btnOK.Click()
						[ ] sleep(1)
					[+] else
						[ ] Log.Fail("'Compare Finish' dialog does not pop up.")
					[+] if(this.txtFindDifference.Exists(5))
						[ ] Log.Fail("Comparison with difference. Please check manually.")
					[+] else
						[ ] Log.Pass("The file is the same as the baseline.")
				[ ] 
	[ ] 
	[-] //Aspen Exchanger Design & Rating
		[-] window			MainWin		glwEDR
			[ ] tag "*Aspen Exchanger Design & Rating*|${sProgramFilePath}\AspenTech\Aspen Exchanger Design and Rating *\XEQ\AspenEDR.exe"
			[ ] locator "/WPFWindow[@caption='*Aspen Exchanger Design & Rating * - aspenONE']"
			[-] //-------------------------------------------------------- Const ---------------------------------------------------------//
				[ ] const 		sCmdLine = "{sProgramFilePath}\AspenTech\Aspen Exchanger Design and Rating {sVersionEDR}\XEQ\AspenEDR.exe"
				[ ] const		sDir = "{sProgramFilePath}\AspenTech\Aspen Exchanger Design and Rating {sVersionEDR}\XEQ"
			[+] //-------------------------------------------------------- Control  --------------------------------------------------------//
				[+] WPFButtonBase	btnRun
					[ ] locator "//WPFButtonBase[@caption='Run']"
				[+] WPFUserControl	ctrlDgDesc
					[ ] locator "//WPFUserControl[@automationId='messageList']"
				[+] WPFTabItem	tbiWarningsAndMessages
					[ ] locator "//WPFTabItem[@caption='Warnings & Messages*']"
				[+] WPFRadioButton	rdbRatingChecking
					[ ] locator "//WPFRadioButton[@automationId='RbtnShellTubeRating']"
				[+] WPFRadioButton	rdbAll
					[ ] locator "//WPFRadioButton[@automationId='radioButtonAll']"
			[+] //-------------------------------------------------------- Dialog  -------------------------------------------------------//
				[+] DialogBox	dlgSaveAs
					[ ] locator "//DialogBox[@caption='Save As']"
					[+] ComboBox	cboFileName
						[ ] locator "//ComboBox"
					[+] PushButton	btnSave
						[ ] locator "//PushButton[@caption='Save']"
				[+] DialogBox	dlgSaveConfirm
					[ ] locator "//DialogBox[@caption='Aspen Exchanger Design & Rating']"
					[+] PushButton	btnYes
						[ ] locator "//PushButton[@caption='Yes']"
					[+] PushButton	btnNo
						[ ] locator "//PushButton[@caption='No']"
					[+] PushButton	btnCancel
						[ ] locator "//PushButton[@caption='Cancel']"
				[+] DialogBox	dlgOpen
					[ ] locator "//DialogBox[@caption='Open']"
					[+] ComboBox	cboFileName
						[ ] locator "//ComboBox[@caption='File name:']"
					[+] PushButton	btnOpen
						[ ] locator "//PushButton[@caption='Open']"
			[+] //-------------------------------------------------------- Method  ------------------------------------------------------//
				[+] void SaveFile(string sPath)
					[+] if(!this.dlgSaveAs.Exists())
						[ ] this.SetActive()
						[ ] this.TypeKeys("<Alt-F>S2",1)
					[ ] this.dlgSaveAs.SetActive()
					[ ] this.dlgSaveAs.cboFileName.Click()
					[ ] this.dlgSaveAs.cboFileName.SetText("{sPath}")
					[ ] sleep(1)
					[ ] this.dlgSaveAs.btnSave.Click()
					[ ] sleep(5)
				[+] CloseDocument(boolean bNeedSave optional,string sPath optional)
					[+] if(bNeedSave==null)
						[ ] bNeedSave=false
					[ ] this.TypeKeys("<Alt-F>C",1)
					[ ] sleep(1)
					[+] if(this.dlgSaveConfirm.Exists(20))
						[ ] this.dlgSaveConfirm.SetActive()
						[+] if(bNeedSave)
							[ ] this.dlgSaveConfirm.btnYes.Click()
							[ ] SaveFile(sPath)
						[+] else
							[ ] this.dlgSaveConfirm.btnNo.Click()
				[+] OpenFile(string sPath)
					[+] if(!this.dlgOpen.Exists(5))
						[ ] this.TypeKeys("<Alt-F>O",2)
					[ ] this.dlgOpen.SetActive()
					[ ] this.dlgOpen.cboFileName.Click()
					[ ] this.dlgOpen.cboFileName.SetText(sPath)
					[ ] sleep(1)
					[ ] this.dlgOpen.btnOpen.Click()
					[ ] sleep(10)
				[ ] 
		[+] window 			DialogBox	dlgExchangerList
			[ ] locator "/WPFWindow[@caption='Exchangers in *']"
			[+] WPFCheckBox	chkReviewOrChange
				[ ] locator "//WPFCheckBox[@automationId='chkDetails']"
			[+] wcAPDataGrid	dgGrid
				[ ] locator "//WPFControl[@automationId='TempAndPressureGrid']"
			[+] WPFCheckBox	chkAdvanced
				[ ] locator "//WPFCheckBox[@automationId='AdvancedChkBox']"
			[+] WPFButton		btnSizeExchanger
				[ ] locator "//WPFButton[@automationId='ImportButton']"
			[+] WPFListBox		lstContents
				[ ] locator "//WPFListBox[@automationId='ExchangerList']"
		[+] window 			DialogBox	dlgImportPSFData
			[ ] locator "/WPFWindow[@caption='Import PSF Data']"
			[+] WPFCheckBox	chkSeperate
				[ ] locator "//WPFCheckBox[@automationId='cbSepPP']"
			[+] WPFButton		btnOK
				[ ] locator "//WPFButton[@automationId='cmdOk']"
		[+] window 			DialogBox	dlgSelectpressures
			[ ] locator "/WPFWindow[@caption='Select Pressures']"
			[+] WPFCheckBox	chkPropSel1
				[ ] locator "//WPFCheckBox[@automationId='chkPropSel1']"
			[+] WPFCheckBox	chkPropSel2
				[ ] locator "//WPFCheckBox[@automationId='chkPropSel2']"
			[+] WPFCheckBox	chkPropSel3
				[ ] locator "//WPFCheckBox[@automationId='chkPropSel3']"
			[+] WPFButton		btnOK
				[ ] locator "//WPFButton[@automationId='cmdOk']"
		[+] window 			DialogBox	dlgChangeMode
			[ ] locator "/WPFWindow[@caption='Change Mode']"
			[+] WPFButton		btnUseCurrent
				[ ] locator "//WPFButton[@caption='Use Current']"
			[+] WPFButton		btnNewRating
				[ ] locator "//WPFButton[@automationId='NewButton']"
	[ ] 
[ ] 
[ ] 
[+] //-------------------------------------------------------------------------------------- l10n BETA -----------------------------------------------------------------------------------------------//
	[ ] // cache
	[+] type Node is record
		[ ] string sKey
		[ ] string sValue
		[ ] Cache rCache
	[+] type Cache is record
		[ ] list of Node lrNodes
	[+] anytype ShootCache(inout Cache cache, anytype key, anytype value null optional, boolean overwrite null optional )
		[ ] list of string lsKeys
		[ ] string sValue
		[ ] 
		[ ] anytype a
		[+] if (typeof(key) == list)
			[+] if (typeof(key) == list of string)
				[ ] lsKeys = key
			[+] else
				[+] for each a in key
					[+] do
						[ ] ListAppend(lsKeys,[string]a)
					[+] except
						[ ] RaiseError(-1,"Unexcepted Arguments!")
		[+] else
			[+] do
				[ ] ListAppend(lsKeys,[string]a)
			[+] except
				[ ] RaiseError(-1,"Unexcepted Arguments!")
		[ ] 
		[+] do 
			[ ] sValue = value
		[+] except
			[+] do
				[ ] sValue = [string]value
			[+] except
				[ ] RaiseError(-1,"Unexcepted Arguments!")
		[ ] 
		[ ] int i = ListCount(cache.lrNodes)
		[ ] int j
		[+] for (j = 1; j <= i; j++)
			[+] if (cache.lrNodes[j].sKey == lsKeys[1])
				[+] if  (ListCount(lsKeys) == 1)
					[+] if (sValue == null)
						[ ] return cache.lrNodes[j].sValue
					[+] else
						[+] if (cache.lrNodes[j].sValue == null || overwrite == true)
							[ ] cache.lrNodes[j].sValue = sValue
							[ ] return true
						[+] else
							[ ] return false
				[+] else
					[ ] ListDelete(lsKeys,1)
					[ ] return ShootCache(cache.lrNodes[j].rCache,lsKeys,sValue,overwrite)
		[+] if (sValue == null)
			[ ] return null
		[+] else
			[ ] Cache c
			[+] if (ListCount(cache.lrNodes) == 0)
				[ ] ListAppend(cache.lrNodes,{lsKeys[1],null,c})
			[+] else
				[ ] ListInsert(cache.lrNodes,1,{lsKeys[1],null,c})
			[ ] return ShootCache(cache,lsKeys,sValue,overwrite)
	[ ] 
	[ ] // excel
	[+] void QueryExcel(string sFile null, string sSql, inout HANDLE hConnection, inout HANDLE hResultSet)
		[ ] hConnection = DB_Connect ("dsn={"Silk DDA Excel"};DBQ={sFile}")
		[ ] hResultSet = DB_ExecuteSQL(hConnection,sSql)
	[+] void CloseDBHandles(inout HANDLE hConnection null, inout HANDLE hResultSet null)
		[+] if (hResultSet != null)
			[ ] DB_FinishSql(hResultSet)
		[+] if (hConnection != null)
			[ ] DB_Disconnect (hConnection)
	[+] string CastTrimStrToNullOrNumberToStr(anytype s null)
		[+] if (s == null)
			[ ] return null
		[+] if (TypeOf(s) == STRING)
			[ ] return (trim(s) == ""?null:trim(s))
		[+] else if (TypeOf(s) ==NUMBER )
			[ ] s = str(s)
			[ ] return (trim(s) == ""?null:trim(s))
		[+] else
			[ ] RaiseError(-255,"Exception in CastTrimStrToNullOrNumberToStr")
	[+] // string TagExcel(boolean bUseCache, string sFile, string sTab, string sLanguageType, string sKey)
		[ ] // string tagl10n
		[ ] // handle hConnection
		[ ] // handle hResultSet
		[+] // if (bUseCache)
			[ ] // tagl10n = ShootCache(l10nCache,{sFile,sTab,sLanguageType,sKey})
			[+] // if (tagl10n != null)
				[ ] // return tagl10n
		[ ] // QueryExcel(sFile,"select [{sTab}$].{sLanguageType} from [{sTab}$] where [{sTab}$].Tag='{sKey}'",hConnection,hResultSet)
		[+] // while (DB_FetchNext(hResultSet,tagl10n))
			[ ] // break
		[ ] // CloseDBHandles(hConnection,hResultSet)
		[+] // if (!isset(tagl10n))
			[ ] // tagl10n = sKey
		[+] // else
			[ ] // tagl10n = CastTrimStrToNullOrNumberToStr(tagl10n)
			[+] // if (tagl10n == null)
				[ ] // tagl10n = sKey
		[+] // if (bUseCache && !ShootCache(l10nCache,{sFile,sTab,sLanguageType,sKey},tagl10n,false))
			[ ] // RaiseError(-1,"write cache error!")
		[ ] // return tagl10n
	[ ] 
	[ ] // xml
	[+] type XMLProperty is record
		[ ] string propertyName
		[ ] string propertyValue
	[+] type XMLNode is record
		[ ] string nodeName
		[ ] list of XMLProperty nodeProperties
		[ ] string nodeValue // xml raw limitation, nodeValue and xmlChildren can not be non-null at the same time
		[ ] list of XMLNode xmlChildren // xml raw limitation, nodeValue and xmlChildren can not be non-null at the same time
	[+] type XML is record // extend xml to support multi top level elements
		[ ] list of XMLNode XMLNodes
	[+] string NodeProperty(in XMLNode node, in string sPropertyName)
		[ ] XMLProperty properti
		[+] for each properti in node.nodeProperties
			[+] if (lower(trim(properti.propertyName)) == lower(trim(sPropertyName))) // ignore case
				[ ] return properti.propertyValue
		[ ] return null
	[+] string NodeValue(in XMLNode node)
		[+] if (isset(node.nodeValue) && node.nodeValue != null)
			[ ] return node.nodeValue
		[+] else
			[ ] return null
	[+] list of XMLNode XMLParser(in list of XMLNode nodesIn, in list of string namesIn) // search namesIn in a list of XMLNode(XML.XMLNodes)
		[ ] list of string namesOut
		[ ] list of XMLNode nodesOut
		[ ] 
		[ ] namesOut = namesIn
		[ ] ListDelete(namesOut,1)
		[ ] 
		[ ] int i = 1
		[ ] int j = ListCount(nodesIn)
		[+] for (i = 1; i <= j; i++)
			[+] if (Lower(nodesIn[i].nodeName) == LowEr(namesIn[1])) // ignore case
				[+] if (ListCount(namesOut) == 0)
					[ ] ListAppend(nodesOut,nodesIn[i])
				[+] else
					[+] if (nodesIn[i].xmlChildren == null)
						[ ] return null
					[+] else
						[ ] list of XMLNode nodesBack = XMLParser(nodesIn[i].xmlChildren,namesOut)
						[+] if (nodesBack != null)
							[ ] ListMerge(nodesOut,nodesBack) // deep-first search
		[+] if (ListCount(nodesOut) == 0)
			[ ] return null
		[+] else
			[ ] return nodesOut
	[+] int StringParser(string str, inout list of XMLNode nodes)
		[ ] int fpos = 0 //  processed file position
		[ ] str = trim(str)
		[ ] int len = len(str)
		[+] if (len == 0)
			[ ] return 0
		[ ] // str not start with "<" : exception
		[+] if (SubStr(str,1,1) != "<")
			[ ] RaiseError(-1,"xml data error!") // error of start without start tag "<"
		[ ] 
		[ ] // str start with closing mark : exception, return
		[+] if (SubStr(str,1,2) == "</") // roll up
			[ ] return 0
		[ ] fpos = 1
		[ ] 
		[ ] 
		[ ] // str start with start mark : in order of 
		[ ] // read nodeName
		[ ] // read nodeProperties
		[ ] // read node value
		[ ] // drill down with nodes under current node
		[ ] // identify closing mark of nodeName
		[ ] // drill down with nodes in the current level
		[ ] 
		[ ] XMLNode node // node in action
		[ ] 
		[ ] // read nodeName
		[ ] string nodeName
		[ ] int nodeNameStart
		[ ] int nodeNameEnd
		[+] for (nodeNameStart=fpos+1; nodeNameStart<=len; nodeNameStart++) // find nodeName start
			[+] if (trim(SubStr(str,nodeNameStart,1)) == "")
				[ ] continue
			[+] else if (SubStr(str,nodeNameStart,1) == ">")
				[ ] RaiseError(-1,"xml data eryror!") // error of kind of "< >"
			[+] else
				[ ] break
		[+] for (nodeNameEnd=nodeNameStart+1; nodeNameEnd<= len; nodeNameEnd++) // find nodeNameEnd
			[+] if (trim(SubStr(str,nodeNameEnd,1)) == "")  // actually, should not exists " "
				[ ] nodeNameEnd = nodeNameEnd-1
				[ ] break
			[+] else if (SubStr(str,nodeNameEnd,1) == ">")
				[+] if (SubStr(str,nodeNameEnd-1,1) == "/")
					[ ] nodeNameEnd = nodeNameEnd -2
					[ ] break
				[+] else
					[ ] nodeNameEnd = nodeNameEnd -1
					[ ] break
			[+] else
				[ ] continue
		[+] if (nodeNameEnd > len)
			[ ] RaiseError(-1,"xml data error!") // error of no ending tag, kind of "<elem"
		[ ] nodeName = SubStr(str,nodeNameStart,nodeNameEnd-nodeNameStart+1)
		[+] if (StrPos("/",nodeName) != 0)
			[ ] RaiseError(-1,"xml data error!") // error of kind of "/ >", should be "/>" and symbol (/) should not exists in nodeName
		[+] else if (StrPos("'",nodeName) != 0)
			[ ] RaiseError(-1,"xml data error!") // symbol (') should not exists in nodeName
		[+] else if (StrPos("""",nodeName) != 0)
			[ ] RaiseError(-1,"xml data error!") // symbol (") should not exists in nodeName
		[+] else
			[ ] // anything else?
		[ ] node.nodeName = nodeName
		[ ] fpos = nodeNameEnd
		[ ] // print(node.nodeName)
		[ ] // print(fpos)
		[ ] 
		[ ] // read nodeProperties
		[ ] // loop
		[ ] // read nodePropertiesName
		[ ] // read nodePropertiesValue
		[ ] // end loop
		[ ] XMLProperty nodeProperties // XMLProperty in action
		[+] while (true)
			[ ] int nodePropertiesStart
			[ ] int nodePropertiesEnd
			[+] for (nodePropertiesStart=fpos+1;nodePropertiesStart<=len;nodePropertiesStart++) // find nodeProperties start
				[+] if (trim(SubStr(str,nodePropertiesStart,1)) == "")
					[ ] continue
				[+] else if (SubStr(str,nodePropertiesStart,1) == ">")
					[ ] nodePropertiesEnd = -1 // have value sign, so drill down with nodes under current node
					[ ] break
				[+] else if (SubStr(str,nodePropertiesStart,2) == "/>")
					[ ] nodePropertiesEnd = -2 // direct close, drill down with nodes in the current level
					[ ] nodePropertiesStart = nodePropertiesStart + 1
					[ ] break
				[+] else
					[+] if (nodePropertiesStart == fpos+1)
						[ ] RaiseError(-1,"xml data error!") // error of white space requried between property, simulate xml behavior in IE8
					[ ] break
			[+] if (!IsSet(nodePropertiesEnd) || nodePropertiesEnd > 0) // nodeProperties exists
				[ ] // read nodePropertiesName
				[+] for (nodePropertiesEnd = nodePropertiesStart+1; nodePropertiesEnd <= len; nodePropertiesEnd++)
					[+] if (trim(SubStr(str,nodePropertiesEnd,1)) == "")
						[ ] nodePropertiesEnd = nodePropertiesEnd - 1
						[ ] break
					[+] else if (SubStr(str,nodePropertiesEnd,1) == "=")
						[ ] nodePropertiesEnd = nodePropertiesEnd - 1
						[ ] break
					[+] else
						[ ] continue
				[+] if (nodePropertiesEnd > len)
					[ ] RaiseError(-1,"xml data error!") // error of property name not finished !!!!!
				[ ] nodeProperties.propertyName = trim(SubStr(str,nodePropertiesStart,nodePropertiesEnd-nodePropertiesStart+1))
				[ ] fpos = nodePropertiesEnd
				[ ] // print(nodeProperties.propertyName)
				[ ] // print(fpos)
				[ ] // read delim between nodePropertiesName and nodePropertiesValue
				[+] for (nodePropertiesStart = fpos+1; nodePropertiesStart <= len; nodePropertiesStart++)
					[+] if (trim(SubStr(str,nodePropertiesStart,1)) == "") // actually, should not exists " "
						[ ] continue
					[+] else if (SubStr(str,nodePropertiesStart,1) == "=")
						[ ] break
					[+] else
						[ ] RaiseError(-1,"xml data error!") // error of property delim "=" not exists !!!!!!
				[ ] fpos = nodePropertiesStart
				[ ] // print(fpos)
				[ ] // read nodePropertiesValue
				[ ] string valueTag
				[+] for (nodePropertiesStart = fpos+1; nodePropertiesStart <= len; nodePropertiesStart++) // search value start " or '
					[+] if (trim(SubStr(str,nodePropertiesStart,1)) == "")
						[ ] continue
					[+] else if (SubStr(str,nodePropertiesStart,1) == """")
						[ ] valueTag = """"
						[ ] break
					[+] else if (SubStr(str,nodePropertiesStart,1) == "'")
						[ ] valueTag = "'"
						[ ] break
					[+] else
						[ ] RaiseError(-1,"xml data error!") // error of property value start tag (" or ') not exists
				[ ] fpos = nodePropertiesStart
				[ ] // print(fpos)
				[ ] // print(valueTag)
				[+] for (nodePropertiesEnd = fpos+1; nodePropertiesEnd <= len; nodePropertiesEnd++) // search value end " or '
					[+] if (SubStr(str,nodePropertiesEnd,1) == valueTag)
						[ ] break
				[+] if (nodePropertiesEnd > len)
					[ ] RaiseError(-1,"xml data error!") // error of property value end tag (" or ') not exists
				[ ] nodeProperties.propertyValue = SubStr(str,nodePropertiesStart+1,nodePropertiesEnd-nodePropertiesStart-1) // actual value, no trim
				[ ] ListAppend(node.nodeProperties,nodeProperties)
				[ ] fpos = nodePropertiesEnd
				[ ] // print(fpos)
				[ ] // print(nodeProperties.propertyValue)
			[+] else // nodeProperties not exists
				[ ] fpos = nodePropertiesStart
				[ ] break
		[ ] // print(fpos)
		[ ] 
		[ ] // read node value
		[+] if (nodePropertiesEnd != -2 )  // have value sign, so drill down with nodes under current node
			[ ] string nodeValue
			[ ] int nodeValueStart = fpos+1
			[ ] int nodeValueEnd
			[+] for (nodeValueEnd = nodeValueStart; nodeValueEnd <= len; nodeValueEnd++)
				[+] if (SubStr(str,nodeValueEnd,1) == "<")
					[ ] nodeValueEnd = nodeValueEnd - 1
					[ ] break
			[ ] nodeValue = trim(SubStr(str,nodeValueStart,nodeValueEnd-nodeValueStart + 1))
			[+] if (nodeValue != "")
				[ ] node.nodeValue = nodeValue
			[ ] fpos = nodeValueEnd
			[ ] int i = StringParser(SubStr(str,fpos+1),node.xmlChildren)
			[ ] fpos = fpos + i
			[ ] // identify closing mark of nodeName
			[+] for (nodeNameStart = fpos+1; nodeNameStart <= len; nodeNameStart++)
				[+] if (trim(SubStr(str,nodeNameStart,1)) == "")
					[ ] continue
				[+] else if (SubStr(str,nodeNameStart,2) == "</")
					[ ] nodeNameStart = nodeNameStart + 1
					[ ] break
				[+] else
					[ ] RaiseError(-1, "xml data error!") // error of value should at front of child nodes, disobey the xml standard !!!!!!
			[ ] fpos = nodeNameStart
			[ ] // todo: add support of value behind XMLChildren
			[+] for (nodeNameStart=fpos+1; nodeNameStart<= len; nodeNameStart++) // find nodeNameStart
				[+] if (trim(SubStr(str,nodeNameStart,1)) == "")
					[ ] RaiseError(-1,"xml data error!") // error of kind of "</ elem", should be "</elem"
				[+] else
					[ ] break
			[+] for (nodeNameEnd=nodeNameStart+1; nodeNameEnd<= len; nodeNameEnd++) // find nodeNameEnd
				[+] if (trim(SubStr(str,nodeNameEnd,1)) == "")
					[ ] continue
				[+] else if (SubStr(str,nodeNameEnd,1) == ">")
					[ ] nodeNameEnd = nodeNameEnd -1
					[ ] break
				[+] else
					[ ] continue
			[+] if (nodeNameEnd > len)
				[ ] RaiseError(-1,"xml data error!") // error of no ending tag ">", kind of "</elem"
			[+] if (node.nodeName == trim(SubStr(str,nodeNameStart,nodeNameEnd-nodeNameStart+1)))
				[ ] fpos = nodeNameEnd + 1
			[+] else
				[ ] RaiseError(-1, "xml data error!") // error of no closing mark for current element !!!!!!
		[+] else // direct close, drill down with nodes in the current level
			[ ] fpos = fpos + StringParser(SubStr(str,fpos+1),nodes) + len(SubStr(str,fpos+1)) - len(ltrim(SubStr(str,fpos+1)))
		[ ] 
		[ ] ListAppend(nodes,node)
		[ ] // drill down the remaining string with nodes in the same level
		[ ] fpos = fpos + StringParser(SubStr(str,fpos+1),nodes) + len(SubStr(str,fpos+1)) - len(ltrim(SubStr(str,fpos+1)))
		[ ] 
		[ ] // print(fpos)
		[ ] // print(node)
		[ ] 
		[ ] return fpos
	[+] FileParser(string file, inout XML xml) // convert an xml file to XML record
		[ ] // convert into a single line string
		[ ] string sFileContent = ""
		[ ] list of string lsFileContents
		[ ] SYS_ListRead(lsFileContents,file)
		[ ] int i = 1
		[ ] int j = ListCount(lsFileContents)
		[+] for (i = 1; i <= j; i++)
			[ ] sFileContent += " " + lsFileContents[i]
		[ ] sFileContent = trim(sFileContent)
		[ ] 
		[ ] // read string into type XML
		[+] if (StringParser(sFileContent,xml.XMLNodes) != len(sFileContent))
			[ ] RaiseError(-1,"xml data error")
	[+] // string TagXML(boolean bUseCache, in XML rXML, string sLanguageType, window wTarget)
		[ ] // list of string lsKeys  // keys in xml
		[ ] // window w = wTarget
		[ ] // listappend(lsKeys,WindowName(w))
		[ ] // w = WindowParent(w)
		[+] // while(w != null)
			[ ] // ListInsert(lsKeys,1,WindowName(w))
			[ ] // w = WindowParent(w)
		[ ] // 
		[ ] // list of string lsCachedKeys = lsKeys // keys in cache
		[ ] // listappend(lsCachedKeys,sLanguageType)
		[ ] // 
		[ ] // string tagxml = null
		[+] // if (bUseCache)
			[ ] // tagxml = ShootCache(l10nCache,lsCachedKeys)
			[+] // if (tagxml != null)
				[ ] // return tagxml
		[ ] // 
		[ ] // list of XMLNode nodes = XMLParser(rXML.XMLNodes,lsKeys)
		[+] // if (nodes == null) // not found
			[ ] // RaiseError(-1,"xml data error!")
		[+] // if (ListCount(nodes) > 1) // should not be duplicated for Silktest frame raw limitation
			[ ] // RaiseError(-1,"xml data error!")
		[ ] // 
		[ ] // tagxml = NodeProperty(nodes[1],sLanguageType)
		[+] // if (tagxml == null)
			[ ] // tagxml = NodeProperty(nodes[1],"English") // default tag
			[+] // if (tagxml == null)
				[ ] // RaiseError(-1,"xml data error!")
		[ ] // 
		[+] // if (bUseCache && !ShootCache(l10nCache,lsCachedKeys,tagxml,false))
			[ ] // RaiseError(-1,"write cache error!")
		[ ] // return tagxml
[ ] 
[+] // // retired
	[+] // // Exception
		[+] // void glThrowException()
			[ ] // RaiseError(-1,"Unexcepted Exceptions Occur!")
		[ ] // 
		[+] // void glThrowTimeoutException()
			[ ] // RaiseError(-2,"Unexcepted Timeout Exceptions Occur!")
		[ ] // 
		[+] // void glThrowIOException()
			[ ] // RaiseError(-3,"Unexcepted IO Exceptions Occur!")
		[ ] // 
		[+] // void glThrowInvalidArgumentException()
			[ ] // RaiseError(-4,"Invailed Function Argument!")
	[ ] 
	[+] // void glHideFileExt (Boolean bHide)
		[+] // //----------------Choose to hide or show files extension-----------//
			[ ] // // Function: glHideFileExt
			[ ] // // Arguments: 
			[ ] // // Return Value: none
			[ ] // // Note:  
			[ ] // // Create Date: Jan 21st, 2008
			[ ] // // Author: Ruoyu Zuo
			[ ] // //------------------------------------------------------//
		[ ] // STRING sValue
		[ ] // INTEGER iKey = HKEY_CURRENT_USER
		[ ] // STRING strPath = "Software\Microsoft\Windows\CurrentVersion\Explorer\Advanced"
		[ ] // STRING strItem = "HideFileExt"
		[+] // if (bHide)
			[ ] // sValue = "REG_DWORD: 0x00000001"
		[+] // else
			[ ] // sValue = "REG_DWORD: 0x00000000"
		[ ] // SYS_SetRegistryValue(iKey, strPath, strItem, sValue)
	[ ] // 
	[+] // string glGetDateTime()
		[+] // //------------------------- Return system time with expected format ------------------//
			[ ] // //
			[ ] // // Author:	Webber Ling
			[ ] // // Date:	Jan-18-2007
			[ ] // //
			[ ] // // Pre:		none
			[ ] // // Post:	none
			[ ] // //
			[ ] // // Input:	none
			[ ] // // Output:	system time with expected format
			[ ] // // E.g. system format is:		2006-12-14 12.48.35.063000
			[ ] // //		modified format:		2006-12-14_12_48
			[ ] // //
			[ ] // //----------------------------------------------------------------------------------//
			[ ] // 
			[ ] // 
			[ ] // 
		[ ] // string sDT, sDate, sTime, stmp
		[ ] // DATETIME dt = GetDateTime()
		[ ] // sDT 	= [string]dt
		[ ] // sDate	= GetField( sDT, " ", 1 )
		[ ] // sTime	= GetField( sDT, " ", 2 )
		[ ] // sTime	= GetField( sTime, ".", 1 ) + "-" + GetField( sTime, ".", 2 )
		[ ] // return sDate + "_" + sTime
	[ ] // 
	[+] // void glSelFldr(WINDOW wBrowForFldr, STRING sDirToSelect)
		[ ] // LIST of STRING lsDir = {}
		[ ] // INT iField = 1
		[ ] // STRING sField = GetField(sDirToSelect,":",1)
		[ ] // STRING tsDir
		[ ] // 
		[+] // if (glsLanguage == "Korean")
			[ ] // tsDir = "/바탕 화면/내 컴퓨터/로컬 디스크 ({sField}:)"
		[+] // else
			[ ] // tsDir = "/Desktop/My Computer/Local Disk ({sField}:)"
		[ ] // 
		[ ] // ListAppend(lsDir, tsDir)
		[+] // while true
			[ ] // sField = GetField(sDirToSelect,"\",++iField)
			[+] // if	(sField == "")
				[ ] // break
			[ ] // tsDir = tsDir + "/" + sField
			[ ] // ListAppend(lsDir,tsDir)
		[ ] // 
		[ ] // INT iListCount = ListCount(lsDir)
		[ ] // INT i
		[+] // for i = 1 to (iListCount-1)
			[ ] // wBrowForFldr.tvwFldr.Expand(lsDir[i])
		[ ] // wBrowForFldr.tvwFldr.Select(lsDir[iListCount])
		[ ] // wBrowForFldr.pshOK.Click ()
[ ] 
[+] // // ready to retire
	[ ] // 
	[ ] // string glsPCName = getPCName() // ready to retire
	[+] // private STRING getPCName()
		[ ] // // logwarning("the const glsPCName is marked as ""ready to retire"", please use glsCOMPUTERNAME instead")
		[ ] // return glsCOMPUTERNAME
	[ ] // 
	[ ] // string glsWinDrive	= getWinDrive()  // ready to retire
	[+] // private STRING getWinDrive()
		[ ] // // logwarning("the const glsWinDrive is marked as ""ready to retire"", please use glsSYSTEMDRIVE instead")
		[ ] // return glsSYSTEMDRIVE
	[ ] // 
	[ ] // string glsWinDir = getWinDir()  // ready to retire
	[+] // private STRING getWinDir()
		[ ] // // logwarning("the const glsWinDir is marked as ""ready to retire"", please use glsWINDIR instead (case sensetive)")
		[ ] // return glsWINDIR
	[ ] // 
	[ ] // string glsProgramDir = getProgramDir()  // ready to retire
	[+] // private STRING getProgramDir()
		[ ] // // logwarning("the const glsProgramDir is marked as ""ready to retire"", please use glsProgramFiles instead")
		[ ] // return glsProgramFiles
	[ ] // 
	[ ] // string glsComFilesDir	= getComFilesDir()  // ready to retire
	[+] // private STRING getComFilesDir()
		[ ] // // logwarning("the const glsComFilesDir is marked as ""ready to retire"", please use glsCommonProgramFiles instead")
		[ ] // return glsCommonProgramFiles
	[ ] // 
	[ ] // string glsDocSettingDir = getDocSettingDir() // ready to retire
	[+] // private STRING getDocSettingDir()
		[+] // do
			[+] // if (glsLanguage == "Germany")
				[+] // if (glsOS == "vista")
					[ ] // return "{glsWinDrive}\ProgramData"
				[+] // else if (glsOS == "7")
					[ ] // return "{glsWinDrive}\User"
				[+] // else if (glsOS == "xp" || glsOS == "2003")
					[ ] // return "{glsWinDrive}\Dokumente und Einstellungen"
				[+] // else
					[ ] // return null
			[+] // else
				[+] // if (glsOS == "vista" || glsOS == "xp" || glsOS == "2003")
					[ ] // return "{glsWinDrive}\Documents and Settings"
				[+] // else if (glsOS == "7")
					[ ] // return "{glsWinDrive}\User"
				[+] // else
					[ ] // return null
		[+] // except
			[ ] // return null
	[ ] // 
	[+] // string glsOfficeVer	= getsOfficeVer()  // ready to retire
		[ ] // // all available values: 11(office 2003 on windows xp and windows 2003),12(office 2007 and windows vista)
		[ ] // // check whether the value is null to ensure no exception occur
	[+] // private STRING getsOfficeVer()
		[+] // if (glsOS == "xp" || glsOS == "2003")
			[ ] // return "11"
		[+] // if (glsOS == "vista" || glsOS == "7")
			[ ] // return "12"
		[ ] // return null
	[ ] // 
	[+] // // Excel macro security level
		[+] // void glSetExcelMacroLevel(string sLevel) // sLevel can be:Low, Medium,High,Very High, for excel 2003 and 2007
			[+] // if (glReg_CheckKey(HKEY_CURRENT_USER, "Software\Microsoft\Office\{glsOfficeVer}.0\Excel", "Security") != true)
				[ ] // Reg_CreateKey(HKEY_CURRENT_USER, "Software\Microsoft\Office\{glsOfficeVer}.0\Excel\Security")
			[+] // if (glReg_CheckValue(HKEY_CURRENT_USER, "Software\Microsoft\Office\{glsOfficeVer}.0\Excel\Security", "Level") != true)
				[ ] // Reg_CreateValue(HKEY_CURRENT_USER, "Software\Microsoft\Office\{glsOfficeVer}.0\Excel\Security", "Level","REG_DWORD: 0x00000003")
			[+] // switch(sLevel)
				[+] // case "Low"
					[ ] // SYS_SetRegistryValue (HKEY_CURRENT_USER, "Software\Microsoft\Office\{glsOfficeVer}.0\Excel\Security", "Level", "REG_DWORD: 0x00000001")
				[+] // case "Medium"
					[ ] // SYS_SetRegistryValue (HKEY_CURRENT_USER, "Software\Microsoft\Office\{glsOfficeVer}.0\Excel\Security", "Level", "REG_DWORD: 0x00000002")
				[+] // case "High"
					[ ] // SYS_SetRegistryValue (HKEY_CURRENT_USER, "Software\Microsoft\Office\{glsOfficeVer}.0\Excel\Security", "Level", "REG_DWORD: 0x00000003")
				[+] // case "Very High"
					[ ] // SYS_SetRegistryValue (HKEY_CURRENT_USER, "Software\Microsoft\Office\{glsOfficeVer}.0\Excel\Security", "Level", "REG_DWORD: 0x00000004")
		[ ] // 
		[+] // string glGetExcelMacroLevel()
			[+] // if (glReg_CheckKey(HKEY_CURRENT_USER,"Software\Microsoft\Office\{glsOfficeVer}.0\Excel", "Security") ==true)
				[+] // if (glReg_CheckValue(HKEY_CURRENT_USER,"Software\Microsoft\Office\{glsOfficeVer}.0\Excel\Security", "Level") ==true)
					[+] // string sCode =  SYS_GetRegistryValue(HKEY_CURRENT_USER, "Software\Microsoft\Office\{glsOfficeVer}.0\Excel\Security","Level")
						[+] // switch(sCode)
							[+] // case "REG_DWORD: 0x00000001"
								[ ] // return "Low"
							[+] // case "REG_DWORD: 0x00000002"
								[ ] // return "Medium"
							[+] // case "REG_DWORD: 0x00000003"
								[ ] // return"High"
							[+] // case "REG_DWORD: 0x00000004"
								[ ] // return "Very High"
			[ ] // return "High"
	[ ] // 
[ ] 
[+] // testcase testGL() appstate none
	[ ] // // const
	[ ] // string s
	[+] // list of string lsContants = {...}
		[ ] // "glsALLUSERSPROFILE"
		[ ] // "glsAPPDATA"
		[ ] // "glsCommonProgramFiles"
		[ ] // "glsCOMPUTERNAME"
		[ ] // "glsHOMEDRIVE"
		[ ] // "glsHOMEPATH"
		[ ] // "glsSYSTEMDRIVE"
		[ ] // "glsSYSTEMROOT"
		[ ] // "glsWINDIR"
		[ ] // "glsProgramFiles"
		[ ] // "glsUSERNAME"
		[ ] // "glsLanguage"
		[ ] // "glsOS"
		[ ] // "glsDriveName"
	[+] // for each s in lsContants
		[ ] // print ("{s}:                           {@s}")
	[ ] // 
	[ ] // // start menu
	[ ] // print ( glInvokeFromStartMenu("AspenTech/Scheduling V7.2/Aspen Olefins Scheduler"))//("Accessories/Notepad") )
	[ ] // glwNotepad.Close()
	[ ] // print ( glInvokeFromRun("cmd2") )
	[ ] // print ( glInvokeFromRun("C:\windows 2\1.exe") )
	[ ] // print ( glInvokeFromRun("X:") )
	[ ] // print ( glInvokeFromRun("c:\windows\system32\notepad.exe") )
	[ ] // 
	[ ] // // open save file
	[ ] // glwNotepad.OpenFile("c:\windows\system32\drivers\etc\hosts")
	[ ] // glwNotepad.OpenFile("c:\windows\system32\drivers\etc\hosts22")
	[ ] //   // should exception here
	[ ] // glwNotepad.SaveFile("c:\hosts22.txt")
	[ ] // glwNotepad.SaveFile("c:\hosts22.txt")
	[ ] // glwNotepad.SaveFile("c:hosts22.txt")
	[ ] // glwNotepad.SaveFile("C:\Users\lzp\Desktop\host2.txt")
	[ ] // glwNotepad.SaveFile("C:\Users\lzp\Desktop\host2.txt")
	[ ] //    //read only this file and do this again
	[ ] // glwNotepad.SaveFile("c:\hosts22.txt")
	[ ] // 
	[ ] // // taskmanager
	[ ] // print (glProcessExists("agent.exe"))
	[ ] // print (glProcessExists("agent.2222exe"))
	[ ] // 
	[ ] // glRemoveShareConnection("shluoc-exp")
[ ] 
