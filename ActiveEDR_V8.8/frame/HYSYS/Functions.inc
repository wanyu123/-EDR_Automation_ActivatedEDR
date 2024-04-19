[ ] 
[ ] use "Frame.inc"
[ ] use "24hRunningByNobody.inc"
[ ] use "4Test.inc"
[ ] 
[+] //File Handle
	[+] void CopyFile(string sSource, string sDestination)
		[ ] //If sSource is a file, it will only copy the file to sDestination
		[ ] //If sSource is a directory, it will copy the whole folder sSource to sDestination
		[ ] string sCmd
		[+] if(SYS_DirExists(sSource))
			[ ] sCmd = "XCOPY {chr(34)}{sSource}{chr(34)} {chr(34)}{sDestination}{chr(34)} /E /Y /F /I /R"
		[+] else if(SYS_FileExists(sSource))
			[ ] sCmd = "XCOPY {chr(34)}{sSource}{chr(34)} {chr(34)}{sDestination}{chr(34)} /Y /R"
		[+] else
			[ ] Log.Fail("The path {sSource} is not valid, please check it.")
			[ ] exit
			[ ] 
		[ ] print(sCmd)
		[ ] list of string lsOutput
		[ ] SYS_Execute(sCmd, lsOutput)
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
			[ ] SYS_MakeDir ("{chr(34)}{sOutputFolder}{chr(34)}")
		[+] except
			[ ] SYS_Execute("mkdir {chr(34)}{sOutputFolder}{chr(34)}")
			[ ] // print("====================================================================")
			[ ] // print(" The folder ""{sFolder}"" is already existing")
			[ ] // print("====================================================================")
	[+] void DeleteFolder(String sFolder, String sDir NULL optional)
		[+] //---------------------Log---------------------//
			[ ] // Info			:	Remove a folder with the name of sFolder under sDir.
			[ ] //					If sDir is NULL, the path is the sFolder.
			[ ] // Author		:	Eric Lu
			[ ] // Date			:	December 06, 2011	
		[ ] 
		[ ] String sOutputFolder
		[ ] 
		[+] if ( sDir != NULL )
			[ ] sOutputFolder = "{sDir}{sFolder}"
		[+] else
			[ ] sOutputFolder = "{sFolder}"
		[+] do
			[ ] SYS_Execute("rmdir {chr(34)}{sOutputFolder}{chr(34)} /s /q")
		[+] except
			[ ] Log.Fail("Remove folder {sOutputFolder} failed.")
	[+] boolean glVerifyFileContainDataValues(string sFilePath, list of string lstExpectResults)
		[ ] //Description:
		[ ] //Use to verify if expect results are existing in a text file, you can generate your own text file according to your requirement.
		[ ] //glVerifyResultContainDataValues("C:\temp.txt", lstExpectResults)
		[ ] //sFilePath is a txt file which contains all of runtime data, we can click Select All button on Datagrid and copy all of the values to a txt file.
		[ ] //lstExpectResults is the list which contains all of the expected results.
		[ ] 
		[ ] 
		[ ] integer i=1, j=1,iCount=0
		[ ] handle hFile
		[ ] string sLine
		[ ] hFile = FileOpen (sFilePath, FM_READ)
		[+] while (FileReadLine (hFile, sLine))
			[ ] sLine = trim(sLine)
			[+] if(j<=ListCount(lstExpectResults))
				[+] if(MatchStr("{lstExpectResults[j]}*",sLine))
					[ ] Log.Message("Find {lstExpectResults[j]}")
					[ ] j++
					[ ] iCount++
		[+] if(iCount>=ListCount(lstExpectResults))
			[ ] Log.Pass("Get all of the values in results.")
			[ ] FileClose(hFile)
			[ ] return true
		[+] else
			[ ] Log.Warning("Didn't get all of the results in {sFilePath}.")
			[ ] FileClose(hFile)
			[ ] return false
	[+] boolean glVerifyItemInList(list of string lstStr, string sItem)
		[ ] //Description:
		[ ] //Use to verify if expect item is existing in a list
		[ ] //glVerifyItemInListFile(lst, "abc")
		[ ] //sFilePath is a txt file which contains all of runtime data, we can click Select All button on Datagrid and copy all of the values to a txt file.
		[ ] //sItem is the string of item you want to check if exists in the list.
		[ ] int i
		[ ] i=ListFind(lstStr,sItem)
		[+] if(i>=1)
			[ ] return true
		[+] else
			[ ] Log.Warning("Didn't find the item in list.")
			[ ] return false
	[+] list of string ReadFileToList(string sFileName, boolean bIgnoreBlankLine optional)
		[ ] list of string lstReturn
		[ ] handle hFile
		[ ] string sLine
		[ ] hFile = FileOpen (sFileName, FM_READ)
		[+] while (FileReadLine (hFile, sLine))
			[+] if(bIgnoreBlankLine!=null &&bIgnoreBlankLine==true)
				[+] if(sLine=="")
					[ ] continue
			[ ] ListAppend(lstReturn,sLine)
		[ ] return lstReturn
	[+] void WriteListToFile(string sFileName, list of anytype lstText, FILEMODE fm optional)
		[+] // Description
			[ ] //Write a list contents to text file
			[ ] //sFileName: the file name with path.
			[ ] //lstText: the list which will be written to sFileName.
			[ ] // Author:	Eric Lu
			[ ] // Created Date: 	July 31, 2012
		[ ] integer i
		[+] if(fm==null)
			[ ] fm=FM_WRITE
		[ ] handle hFile = FileOpen(sFileName,fm)
		[+] for(i=1;i<=ListCount(lstText);i++)
			[ ] FileWriteLine(hFile,lstText[i])
		[ ] FileClose(hFile)
		[ ] 
	[+] void WriteStrToFile(string sFileName, string sText)
		[+] // Description
			[ ] //Write a string contents to text file
			[ ] //sFileName: the file name with path.
			[ ] //sText: the string which will be written to sFileName.
			[ ] // Author:	Eric Lu
			[ ] // Created Date: 	January 24, 2013
		[ ] handle hFile = FileOpen(sFileName,FM_WRITE)
		[ ] FileWriteLine(hFile,sText)
		[ ] FileClose(hFile)
		[ ] 
	[+] string glGetFileVersion(string sFileName)
		[+] // Description
			[ ] //Get the version of the file
			[ ] //sFileName: the file name with path.
			[ ] // Author:	Eric Lu
			[ ] // Created Date: 	February 21, 2013
		[+] if(!SYS_FileExists(sFileName))
			[ ] Log.Error("The file {sFileName} is not exists, please check the path is correct.")
			[ ] return "Get File Version Failed"
		[ ] string sFileNameDoubleSlash=StrTran(sFileName,"\","\\")
		[ ] //print(sFileNameDoubleSlash)
		[ ] SYS_Execute("wmic datafile where {chr(34)}Name= '{sFileNameDoubleSlash}' {chr(34)} get Version",lstString)
		[+] if(lstString!=null && listcount(lstString)>1)
			[ ] 
			[ ] return trim(lstString[2])
		[+] else
			[ ] Log.Error(lstString)
[-] //Cursor Related
	[+] // void glWaitForMouseIdle(integer iTimeOut optional, integer waitTimes optional)
		[ ] // //Default wait of 2.5 Seconds unless mouse is active
		[ ] // //waitTimes is the number of sucessive 0.5 second loops with the mouse idle before this function will exit. Min exit time = waitTimes * 0.5 seconds
		[+] // if( iTimeOut == NULL )
			[ ] // iTimeOut = 30
		[ ] // real rTime=0
		[ ] // integer counter = 0
		[ ] // integer Exit = 5
		[+] // if( waitTimes != NULL)
			[+] // if( waitTimes <=  0)
				[ ] // Log.warning("The wait times should be a positive integer, but you used a 0 or negative one, we will use the default value 5")
			[+] // else
				[ ] // Exit = waitTimes
		[ ] // 
		[+] // while( rTime < iTimeOut && counter < Exit)
			[ ] // rTime = rTime+0.5
			[ ] // sleep(0.5)
			[ ] // 
			[+] // if( Cursor.GetType()=="WAIT" || Cursor.GetType()=="DELAY" )
				[ ] // counter = 0
			[+] // else
				[ ] // counter++
			[ ] // 
			[ ] // 
		[+] // if(rTime > iTimeOut)
			[ ] // Log.Error("ERROR: TIMEOUT REACHED BUT YOUR COMPUTER IS STILL THINKING REALLY HARD")
		[ ] // 
	[-] boolean glWaitForMouseIdle(integer iTimeOut optional, integer waitTimes optional, window WaitFor optional)
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
		[-] while( rTime < iTimeOut && counter < Exit)
			[ ] rTime = rTime+0.5
			[ ] sleep(0.5)
			[ ] 
			[+] if( Cursor.GetType()=="WAIT" || Cursor.GetType()=="DELAY" )
				[ ] counter = 0
			[+] else
				[ ] counter++
			[ ] 
			[+] if( WaitFor != NULL && WaitFor.Exists())
				[ ] return true
			[ ] 
		[+] if(rTime > iTimeOut)
			[ ] Log.Error("ERROR: TIMEOUT REACHED BUT YOUR COMPUTER IS STILL THINKING REALLY HARD")
		[ ] 
		[ ] return false
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
[+] //Common Object manipulation
	[+] string Aspen_GetComboxSelectedText(window ComboxObj)
		[ ] string sSelectedText
		[ ] sSelectedText=ComboxObj.GetProperty("SelectedItemText")
		[ ] return sSelectedText
	[+] void glSelectItemInComboBox(window wParentWindow, string sAttribute, string sValue, string sItemName, int iIndex optional)
			[ ] //Description:
			[ ] //SelectItemInComboBox(AP,"automationId","PART_editControl","11",3)
			[ ] // use to select combox item in A+ user interface.
			[ ] //sAttribute:  such as caption, automationid , classtype...
			[ ] //sValue : the actual value of caption, automationid , classtype...
			[ ] //sItemName: the  item to be selected.
			[ ] //index :the index for sValue; e.g.  "2"  in the @className='AesXamComboEdit'][2]"
			[ ] // Author		:	Eric Lu
			[ ] // Date			:	June 04, 2012	
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
	[+] void glSetEditControlText(window wParentWindow, string sAttribute, string sAttributeValue, string sText, int iIndex optional)
			[ ] //Description:
			[ ] //glSetEditControlText(AP,"automationId","PART_editControl","11",3)
			[ ] // use to select combox item in A+ user interface.
			[ ] //sAttribute:  such as caption, automationid , classtype...
			[ ] //sValue : the actual value of caption, automationid , classtype...
			[ ] //sText: the  text to be set.
			[ ] //index :the index for sValue; e.g.  "2"  in the @className='PART_editControl'][2]"
			[ ] // Author		:	Eric Lu
			[ ] // Date			:	July 24, 2012	
			[ ] 
			[ ] wParentWindow.SetActive()
			[ ] window editControl
			[+] if(iIndex == null)
				[ ] editControl = wParentWindow.Find("//WPFControl[@{sAttribute}='{sAttributeValue}']")
			[+] else
				[ ] editControl = wParentWindow.Find("//WPFControl[@{sAttribute}='{sAttributeValue}'][{iIndex}]")
			[ ] editControl.Click()
			[ ] sleep(0.5)
			[ ] editControl.TypeKeys("<Ctrl-a>")
			[ ] sleep(0.5)
			[ ] editControl.TypeKeys(sText)
			[ ] sleep(0.5)
			[ ] editControl.TypeKeys("<Enter>")
	[+] boolean glVerifyDataGridColumnHeaders(window wDataGrid,LIST OF ANYTYPE lstHeaderInfo)
		[ ] //Description:
		[ ] //Use to verify if the Column Header of a DataGrid is correct, the precondition is that there is at least one WPFTextBlock in each header.
		[ ] //glVerifyDataGridColumnHeaders(AH.dgDataGrid, lstHeaderInfo)
		[ ] //lstHeaderInfo is a list, each item in this list cotains the captions of the WPFTextBlock which belongs to the Header
		[ ] // Author		:	Eric Lu
		[ ] // Date			:	July 31, 2012	
		[ ] 
		[ ] list of window lstColumnHeaders = wDataGrid.FindAll("//WPFDataGridColumnHeader")
		[ ] int i
		[ ] //We always need to ignore the first WPFDataGridColumnHeader, it is the whole header.
		[+] if(ListCount(lstHeaderInfo)!= (ListCount(lstColumnHeaders)-1))
			[ ] Log.Fail("The number of  Column Header is not correct")
			[ ] return false
		[+] else
			[+] for(i=1;i<=(ListCount(lstColumnHeaders)-1);i++)
				[ ] list of WINDOW lstTextBlocks = lstColumnHeaders[i+1].FindAll("//WPFTextBlock")
				[+] if(ListCount(lstTextBlocks)!=ListCount(lstHeaderInfo[i]))
					[ ] Log.Fail("The Contents number for Column Header {i} is not correct.")
					[ ] return false
				[+] else
					[ ] int j
					[+] for(j=1;j<=ListCount(lstTextBlocks);j++)
						[+] if(lstTextBlocks[j].GetCaption()!=lstHeaderInfo[i][j])
							[ ] Log.Fail("Expect {lstHeaderInfo[i][j]} but get {lstTextBlocks[j].GetCaption()}.")
							[ ] return false
			[+] if(i>ListCount(lstHeaderInfo))
				[ ] return true
			[+] else
				[ ] return false
	[+] boolean glVerifyDataGridRowHeaders(window wDataGrid,LIST OF ANYTYPE lstHeaderInfo)
		[ ] //Description:
		[ ] //Use to verify if the Row Header of a DataGrid is correct the precondition is that there is at least one WPFLabel in each header.
		[ ] //If there is no WPFLabel in the Row Header, we need to use glDataGridMultiSelect() to get the first row's contents.
		[ ] //glVerifyDataGridRowHeaders(AH.dgDataGrid, lstHeaderInfo)
		[ ] //lstHeaderInfo is a list, each item in this list cotains the captions of the WPFLabel which belongs to the Header
		[ ] // Author		:	Eric Lu
		[ ] // Date			:	July 31, 2012	
		[ ] 
		[ ] list of window lstDatagridRows = wDataGrid.FindAll("//WPFDataGridRow")
		[ ] int i
		[+] if(ListCount(lstHeaderInfo)!= ListCount(lstDatagridRows))
			[ ] Log.Warning("The number of  Row Header is not correct")
			[ ] return false
		[+] else
			[+] for(i=1;i<=ListCount(lstDatagridRows);i++)
				[ ] list of WINDOW lstLabels = lstDatagridRows[i].FindAll("//WPFLabel")
				[+] if(ListCount(lstLabels)!=ListCount(lstHeaderInfo[i]))
					[ ] Log.Warning("The Contents number for Row Header {i} is not correct.")
					[ ] return false
				[+] else
					[ ] int j
					[+] for(j=1;j<=ListCount(lstLabels);j++)
						[+] if(lstLabels[j].GetCaption()!=lstHeaderInfo[i][j])
							[ ] Log.Fail("Expect {lstHeaderInfo[i][j]} but get {lstLabels[j].GetCaption()}.")
							[ ] return false
			[+] if(i>ListCount(lstHeaderInfo))
				[ ] return true
			[+] else
				[ ] return false
	[+] boolean glVerifyDataGridEnterMotion(window wParentWindowForDataGrid, window wDataGrid,int iRow, int iColumn, string sEnterMotion, string sAfterEnter optional)
		[ ] //Description:
		[ ] //Use to verify the DataGrid Enter motion.
		[ ] //wParentWindowForDataGrid: the parent window of the wDataGrid.
		[ ] //wDataGrid: the datagrid we want to verfity.
		[ ] //iRow: the row number for the cell.
		[ ] //iColumn: the column number for the cell.
		[ ] //sEnterMotion: the type of enter motion we want to verify, it can only be "none","below" or "right".
		[ ] // Author		:	Eric Lu
		[ ] // Date			:	July 24, 2012	
		[ ] 
		[ ] string sEnterMotionType
		[+] if(sVersion>="V8.3")
			[ ] wParentWindowForDataGrid=Desktop
		[+] if(Lower(sEnterMotion)=="none")
				[ ] wDataGrid.SetFocus()
				[ ] wDataGrid.TypeKeys("<Ctrl-Home>")
				[+] if(iColumn>1)
					[ ] wParentWindowForDataGrid.TypeKeys("<Right {iColumn-1}>")
				[+] if(iRow>1)
					[ ] wParentWindowForDataGrid.TypeKeys("<Down {iRow-1}>")
				[ ] Clipboard.SetText()
				[+] do
					[ ] wDataGrid.CurrentCell.TypeKeys("<Ctrl-C>")
				[+] except
					[ ] ExceptClear()
					[ ] wParentWindowForDataGrid.TypeKeys("<Ctrl-C>")
				[ ] lstString = Clipboard.GetText()
				[ ] sValue=lstString[1]
				[+] if(sValue=="" || MatchStr("*empty*",sValue))
					[ ] Log.Fail("The cell({iRow},{iColumn}) is not valid or can't copy value from it, the value is empty.")
					[ ] return false
				[ ] sleep(1)
				[ ] wParentWindowForDataGrid.TypeKeys("<Enter>")
				[ ] Clipboard.SetText()
				[ ] 
				[+] do
					[ ] wDataGrid.CurrentCell.TypeKeys("<Ctrl-C>")
				[+] except
					[ ] ExceptClear()
					[ ] wParentWindowForDataGrid.TypeKeys("<Ctrl-C>")
				[ ] lstString = Clipboard.GetText()
				[+] if(sValue==lstString[1])
					[ ] Log.Pass("Verify Enter motion is none pass.")
					[ ] return true
				[+] else
					[ ] Log.Fail("Verify Enter motion is none failed, expect focus stay in cell {sValue} but goes to {lstString[1]}.")
					[ ] return false
		[+] else if(Lower(sEnterMotion)=="below")
				[ ] sEnterMotionType = "Below"
		[+] else if(Lower(sEnterMotion)=="right")
			[ ] sEnterMotionType = "Right"
		[+] else if(Lower(sEnterMotion)=="left")
				[ ] sEnterMotionType = "Left"
		[+] else
			[ ] Log.Fail("Enter motion {sEnterMotion} is not supported.")
			[ ] return false
		[+] if(sAfterEnter==null)
			[ ] Log.Fail("For Enter motion Below, parameter  'sAfterEnter' can't be null.")
			[ ] return false
		[ ] wDataGrid.SetFocus()
		[ ] wDataGrid.TypeKeys("<Ctrl-Home>")
		[+] if(iColumn>1)
			[ ] wParentWindowForDataGrid.TypeKeys("<Right {iColumn-1}>")
		[+] if(iRow>1)
			[ ] wParentWindowForDataGrid.TypeKeys("<Down {iRow-1}>")
		[ ] Clipboard.SetText()
		[+] do
			[ ] wDataGrid.CurrentCell.TypeKeys("<Ctrl-C>")
		[+] except
			[ ] ExceptClear()
			[ ] wParentWindowForDataGrid.TypeKeys("<Ctrl-C>")
		[ ] lstString = Clipboard.GetText()
		[ ] sValue=lstString[1]
		[+] if(sValue=="" || MatchStr("*empty*",sValue))
			[ ] Log.Fail("The cell({iRow},{iColumn}) is not valid or can't copy value from it, the value is empty.")
			[ ] return false
		[ ] sleep(1)
		[ ] wParentWindowForDataGrid.TypeKeys("<Enter>")
		[ ] sleep(1)
		[ ] Clipboard.SetText()
		[+] do
			[ ] wDataGrid.CurrentCell.TypeKeys("<Ctrl-C>")
		[+] except
			[ ] ExceptClear()
			[ ] wParentWindowForDataGrid.TypeKeys("<Ctrl-C>")
		[ ] lstString = Clipboard.GetText()
		[+] if(lstString[1]=="" || MatchStr("*empty*",sValue))
			[ ] Log.Fail("The cell({iRow},{iColumn}) is not valid or can't copy value from it, the value is empty.")
			[ ] return false
		[+] else if(sAfterEnter==lstString[1])
			[ ] Log.Pass("Verify Enter motion is {sEnterMotionType} pass.")
			[ ] return true
		[+] else
			[ ] Log.Fail("Verify Enter motion is {sEnterMotionType} failed, expect focus in cell {sValue} but goes to {lstString[1]}.")
			[ ] return false
	[ ] //Modified by Juan at 5/10/2013 since previous function not work since V8.3
	[+] list of string glDataGridMultiSelect(window wParentWindowForDataGrid, window wDataGrid, int iSelectedRowCount, int iSelecttedColumnCount, int iStartRow optional, int iStartColumn)
		[+] //Description
			[ ] //Select iSelectedRowCount rows and iSelecttedColumnCount from start point row number iStartRow and column number iStartColumn.
			[ ] //The iStartRow iStartColumn need have value at the same time, or neither or them has value, if they are none, select from left top corner.
			[ ] //wDataGrid: it is the table we want to select.
			[ ] //iSelectedRowCount: row count we want to select.
			[ ] //iSelecttedColumnCount: column count we want to select
			[ ] //iStartRow: the start row number.
			[ ] //iStartColumn: the start column number.
			[ ] // Author		:	Eric Lu
			[ ] // Date			:	July 31, 2012	
		[ ] 
		[ ] //For V8.3 DataGrid issue
		[+] if(sVersion>="V8.3")
			[ ] wParentWindowForDataGrid = Desktop
		[ ] 
		[ ] wDataGrid.SetFocus()
		[ ] wDataGrid.Click()
		[ ] wDataGrid.TypeKeys("<Ctrl-Home>")
		[+] if(iStartColumn!=null)
			[+] if(iStartRow>1)
				[ ] wParentWindowForDataGrid.TypeKeys("<Down {iStartRow-1}>")
				[ ] sleep(0.5)
			[+] if(iStartColumn>1)
				[ ] wParentWindowForDataGrid.TypeKeys("<Right {iStartColumn-1}>")
				[ ] sleep(0.5)
		[ ] wParentWindowForDataGrid.PressKeys("<Shift>")
		[+] if(iSelecttedColumnCount>1)
			[+] wParentWindowForDataGrid.TypeKeys("<Right {iSelecttedColumnCount-1}>")
				[ ] sleep(0.5)
		[+] if(iSelectedRowCount>1)
			[+] wParentWindowForDataGrid.TypeKeys("<Down {iSelectedRowCount-1}>")
				[ ] sleep(0.5)
		[ ] wParentWindowForDataGrid.ReleaseKeys("<Shift>")
		[ ] Clipboard.SetText()
		[ ] wParentWindowForDataGrid.TypeKeys("<Ctrl-C>")
		[+] do
			[ ] print(ListCount(Clipboard.GetText()))
		[+] except
			[ ] Exceptclear()
			[ ] wDataGrid.Click(MB_RIGHT)
			[ ] wContextMenu.Exists(5)
			[ ] wContextMenu.TextClick("Copy")
			[ ] sleep(0.5)
		[+] if(ListCount(Clipboard.GetText())<=1)
			[ ] AH.TypeKeys("<Ctrl-C>")
		[+] if(ListCount(Clipboard.GetText())<=1)
			[ ] wDataGrid.TypeKeys("<Ctrl-C>")
		[+] if(ListCount(Clipboard.GetText())<=1)
			[ ] Desktop.TypeKeys("<Ctrl-C>")
		[ ] list of string lstString = Clipboard.GetText()
		[ ] return lstString
	[+] boolean glVerifyAllCheckBoxStatusInDataGrid(window wDataGrid, list of anytype lstExpectCHKStatus)
		[+] //Description
			[ ] //Verify all of the checkbox status is correct in DataGrid.
			[ ] //wDataGrid: the DataGrid we want to check.
			[ ] //lstExpectCHKStatus: the list which saved the status, each item in list is a row's checkbox status.
			[ ] // Author		:	Eric Lu
			[ ] // Date			:	July 31, 2012	
		[ ] 
		[ ] list of WINDOW lstDatagridRows = wDataGrid.FindAll("//WPFDataGridRow")
		[+] if(ListCount(lstDatagridRows)!=ListCount(lstExpectCHKStatus))
			[ ] Log.Warning("The count of rows are not same as the length of expect list.")
			[ ] return false
		[+] else
			[ ] int i
			[+] for(i=1;i<ListCount(lstDatagridRows);i++)
				[ ] list of window wCheckBoxes=lstDatagridRows[i].FindAll("//WPFCheckBox")
				[+] if(ListCount(wCheckBoxes)!=ListCount(lstExpectCHKStatus[i]))
					[ ] Log.Warning("The count of check box in row {i} is not same as the length of expect list.")
					[ ] return false
				[+] else
					[ ] int j
					[+] for(j=1;j<ListCount(lstExpectCHKStatus[i]);j++)
						[+] if(Lower(lstExpectCHKStatus[i][j])=="true")
							[+] if(!wCheckBoxes[j].IsChecked)
								[ ] Log.Fail("The checkbox {j} in Row {i} is not checked but expect checked..")
								[ ] return false
						[ ] else
						[+] if(Lower(lstExpectCHKStatus[i][j])=="false")
							[+] if(wCheckBoxes[j].IsChecked)
								[ ] Log.Fail("The checkbox{j} in Row {i} is checked but expect not checked.")
								[ ] return false
		[ ] return true
	[+] // string glGoToCell(int row, int column, window wParent, window datagrid,string str optional)
		[+] // //Description
			[ ] // // glGoToCellInEOVar ( row, column, wParent, datagrid, str) - move focus to the specific row and column in datagrid, if str is not null, will set the cell value as str or will get the cell value.
			[ ] // //  Usage:
			[ ] // //  - glGoToCellInEOVar(3,4,AH,datagrid,"BLK.SPEC3O_PRES") or AH.GoToCell(3,4,AH,datagrid,"Constant")
			[ ] // // Author		:	Eric Lu
			[ ] // // Create Date			:	July 31, 2012	
			[ ] // // Modified by Eric Lu on March 1, 2013
		[ ] // datagrid.SetFocus()
		[ ] // sleep(0.5)
		[+] // do
			[ ] // window wCell=datagrid.Find("//WPFDataGridCell[1]")
			[ ] // wCell.SetFocus()
			[ ] // sleep(1)
			[ ] // wCell.Click()
			[ ] // sleep(1)
		[+] // except
			[ ] // ExceptClear()
		[ ] // //datagrid.Click()
		[ ] // sleep(0.5)
		[ ] // list of string lststrValue
		[ ] // //wParent.TypeKeys("<Ctrl-Home>")
		[ ] // datagrid.TypeKeys("<Ctrl-Home>")
		[+] // if(row>1)
			[ ] // wParent.TypeKeys("<Down {row-1}>")
		[ ] // sleep(1)
		[+] // if(column>1)
			[ ] // wParent.TypeKeys("<Right {column-1}>")
		[ ] // sleep(1)
		[+] //  if (str != null)
			[+] // list of STRING lststr = {...}
				[ ] // str
			[ ] // Clipboard.SetText(lststr)
			[ ] // wParent.TypeKeys("<Ctrl-V>")
			[ ] // Clipboard.SetText()
			[ ] // sleep(0.5)
			[ ] // //datagrid.TypeKeys("<Ctrl-C>")
			[ ] // wParent.TypeKeys("<Ctrl-C>")
			[ ] // lststrValue = Clipboard.GetText()
			[ ] // wParent.TypeKeys("<Enter>")
			[ ] // return lststrValue[1]
		[+] // else
			[ ] // Clipboard.SetText()
			[ ] // datagrid.TypeKeys("<Ctrl-C>")
			[ ] // lststrValue = Clipboard.GetText()
			[ ] // return lststrValue[1]
			[ ] // 
	[ ] //Modified by Juan at 5/10/2013 since previous function not work since V8.3
	[+] string glGoToCell(int row, int column, window wParent, window datagrid,string str optional)
		[+] //Description
			[ ] // glGoToCellInEOVar ( row, column, wParent, datagrid, str) - move focus to the specific row and column in datagrid, if str is not null, will set the cell value as str or will get the cell value.
			[ ] //  Usage:
			[ ] //  - glGoToCellInEOVar(3,4,AH,datagrid,"BLK.SPEC3O_PRES") or AH.GoToCell(3,4,AH,datagrid,"Constant")
			[ ] // Author		:	Eric Lu
			[ ] // Create Date			:	July 31, 2012	
			[ ] // Modified by Eric Lu on March 1, 2013
		[+] if(sVersion>="V8.3")
			[ ] wParent = Desktop
		[ ] 
		[ ] datagrid.SetFocus()
		[ ] sleep(0.5)
		[+] do
			[ ] window wCell=datagrid.Find("//WPFDataGridCell[1]")
			[ ] wCell.ScrollIntoView()                                                         //wCell.SetFocus()
			[ ] sleep(1)
			[ ] wCell.Click()
			[ ] sleep(1)
		[+] except
			[ ] ExceptClear()
		[ ] //datagrid.Click()
		[ ] sleep(0.5)
		[+] list of string lststrValue={...}
			[ ] ""
		[ ] datagrid.TypeKeys("<Ctrl-Home>")
		[+] if(row>1)
			[+] do
				[ ] datagrid.CurrentCell.TypeKeys("<Down {row-1}>")                                //wParent.TypeKeys("<Down {row-1}>")
			[+] except
				[ ] ExceptClear()
				[ ] wParent.TypeKeys("<Down {row-1}>")  
		[ ] sleep(1)
		[+] if(column>1)
			[+] do
				[ ] datagrid.CurrentCell.TypeKeys("<Right {column-1}>")                            //wParent.TypeKeys("<Right {column-1}>")
			[+] except
				[ ] ExceptClear()
				[ ] wParent.TypeKeys("<Right {column-1}>")  
		[ ] sleep(1)
		[+] if (str != null)
			[+] list of STRING lststr = {...}
				[ ] str
			[ ] Clipboard.SetText(lststr)
			[+] do
				[ ] datagrid.CurrentCell.TypeKeys("<Ctrl-V>")                                      //wParent.TypeKeys("<Ctrl-V>")
			[+] except
				[ ] ExceptClear()
				[ ] wParent.TypeKeys("<Ctrl-V>")
			[ ] Clipboard.SetText()
			[ ] sleep(0.5)
			[+] do
				[ ] datagrid.CurrentCell.TypeKeys("<Ctrl-C>")                                      //wParent.TypeKeys("<Ctrl-C>")
			[+] except
				[ ] ExceptClear()
				[ ] wParent.TypeKeys("<Ctrl-C>")
			[ ] lststrValue = Clipboard.GetText()
			[+] do
				[+] if(lststrValue[1]=="")
					[ ] datagrid.TypeKeys("<Ctrl-C>")
					[ ] lststrValue = Clipboard.GetText()
			[+] except
				[ ] datagrid.TypeKeys("<Ctrl-C>")
				[ ] lststrValue = Clipboard.GetText()
			[ ] 
			[+] do
				[ ] datagrid.CurrentCell.TypeKeys("<Enter>")                                       //wParent.TypeKeys("<Enter>")
			[+] except
				[ ] ExceptClear()
				[ ] wParent.TypeKeys("<Enter>")
			[ ] return lststrValue[1]
		[+] else
			[ ] Clipboard.SetText()
			[+] do
				[+] if(datagrid.CurrentCell.TextCapture()=="")
					[ ] datagrid.CurrentCell.TypeKeys("<Ctrl-C>")                                      //datagrid.TypeKeys("<Ctrl-C>")
				[+] else
					[ ] return datagrid.CurrentCell.GetProperty("Text")
			[+] except
				[ ] ExceptClear()
				[ ] datagrid.TypeKeys("<Ctrl-C>")
			[ ] lststrValue = Clipboard.GetText()
			[+] do
				[+] if(lststrValue[1]=="")
					[ ] wParent.TypeKeys("<Ctrl-C>")
					[ ] lststrValue = Clipboard.GetText()
			[+] except
				[ ] datagrid.TypeKeys("<Ctrl-C>")
				[ ] lststrValue = Clipboard.GetText()
			[ ] int i=ListCount(lststrValue)
			[+] if(i>0)
				[ ] return lststrValue[i]
			[+] else
				[ ] return ""
	[+] // string glGoToCellInInverted(int row, int column, window wParent, window datagrid,string str optional)
		[+] // //Description
			[ ] // // GoToCellInEOVar ( row, column, datagrid, str) - move focus to the specific row and column inverted in datagrid, if str is not null, will set the cell value as str.
			[ ] // //  Usage:
			[ ] // //  - glGoToCellInEOVar(3,4,wParent,datagrid,"BLK.SPEC3O_PRES") or AH.GoToCell(3,4,wParent,datagrid,"Constant")
			[ ] // // Author		:	Eric Lu
			[ ] // // Date			:	July 31, 2012	
		[ ] // datagrid.SetFocus()
		[ ] // list of string lststrValue
		[ ] // wParent.TypeKeys("<Ctrl-End>")
		[ ] // wParent.TypeKeys("<Up {row-1}>")
		[ ] // sleep(1)
		[ ] // wParent.TypeKeys("<Left {column-1}>")
		[ ] // sleep(1)
		[+] //  if (str != null)
			[+] // list of STRING lststr = {...}
				[ ] // str
			[ ] // Clipboard.SetText(lststr)
			[ ] // wParent.TypeKeys("<Ctrl-V>")
			[ ] // Clipboard.SetText()
			[ ] // datagrid.TypeKeys("<Ctrl-C>")
			[ ] // lststrValue = Clipboard.GetText()
			[+] // // if(str == lststrValue[1])
				[ ] // // Log.Pass("Value modifies to {str} Pass.")
			[+] // // else
				[ ] // // Log.Warning("Value modifies to {str} Fail, actually to {lststrValue[1]}.")
			[ ] // datagrid.TypeKeys("<Enter>")
			[ ] // return lststrValue[1]
		[+] // else
			[ ] // Clipboard.SetText()
			[ ] // datagrid.TypeKeys("<Ctrl-C>")
			[ ] // lststrValue = Clipboard.GetText()
			[ ] // return lststrValue[1]
			[ ] // 
		[ ] // 
	[ ] //Modified by Juan at 5/10/2013 since previous function not work since V8.3
	[+] string glGoToCellInInverted(int row, int column, window wParent, window datagrid,string str optional)
		[+] //Description
			[ ] // GoToCellInEOVar ( row, column, datagrid, str) - move focus to the specific row and column inverted in datagrid, if str is not null, will set the cell value as str.
			[ ] //  Usage:
			[ ] //  - glGoToCellInEOVar(3,4,wParent,datagrid,"BLK.SPEC3O_PRES") or AH.GoToCell(3,4,wParent,datagrid,"Constant")
			[ ] // Author		:	Eric Lu
			[ ] // Date			:	July 31, 2012	
		[+] if(sVersion>="V8.3")
			[ ] wParent = Desktop
		[ ] 
		[ ] datagrid.SetFocus()
		[ ] list of string lststrValue
		[ ] datagrid.TypeKeys("<Ctrl-End>")                                               //wParent.TypeKeys("<Ctrl-End>")
		[+] if(row>1)
			[+] do
				[ ] datagrid.CurrentCell.TypeKeys("<Up {row-1}>")                                //wParent.TypeKeys("<Up {row-1}>")
			[+] except
				[ ] ExceptClear()
				[ ] wParent.TypeKeys("<Up {row-1}>")  
		[ ] sleep(1)
		[+] if(column>1)
			[+] do
				[ ] datagrid.CurrentCell.TypeKeys("<Left {column-1}>")                            //wParent.TypeKeys("<Left {column-1}>")
			[+] except
				[ ] ExceptClear()
				[ ] wParent.TypeKeys("Left {column-1}>")  
		[ ] sleep(1)
		[+]  if (str != null)
			[+] list of STRING lststr = {...}
				[ ] str
			[ ] Clipboard.SetText(lststr)
			[+] do
				[ ] datagrid.CurrentCell.TypeKeys("<Ctrl-V>")                                      //wParent.TypeKeys("<Ctrl-V>")
			[+] except
				[ ] ExceptClear()
				[ ] wParent.TypeKeys("<Ctrl-V>")
			[ ] Clipboard.SetText()
			[ ] sleep(0.5)
			[+] do
				[ ] datagrid.CurrentCell.TypeKeys("<Ctrl-C>")                                      //wParent.TypeKeys("<Ctrl-C>")
			[+] except
				[ ] ExceptClear()
				[ ] wParent.TypeKeys("<Ctrl-C>")
			[ ] lststrValue = Clipboard.GetText()
			[+] // if(str == lststrValue[1])
				[ ] // Log.Pass("Value modifies to {str} Pass.")
			[+] // else
				[ ] // Log.Warning("Value modifies to {str} Fail, actually to {lststrValue[1]}.")
			[ ] datagrid.CurrentCell.TypeKeys("<Enter>")                      //datagrid.TypeKeys("<Enter>")
			[ ] return lststrValue[1]
		[+] else
			[ ] Clipboard.SetText()
			[+] do
				[ ] datagrid.CurrentCell.TypeKeys("<Ctrl-C>")                     //datagrid.TypeKeys("<Ctrl-C>")
			[+] except
				[ ] ExceptClear()
				[ ] datagrid.TypeKeys("<Ctrl-C>")
			[ ] lststrValue = Clipboard.GetText()
			[ ] return lststrValue[1]
			[ ] 
		[ ] 
	[ ] 
	[+] boolean glFindItemsInList(list of STRING lstItemsTobeFind, list of STRING lstToTraversal)
		[ ] string str
		[+] for each str in lstItemsTobeFind
			[+] if(listfind(lstToTraversal, str)<=0)
				[ ] Log.Message("Item {str} not be found in list.")
				[ ] return false
		[ ] return true
	[+] boolean glFindStringInList(string sTobeFind, list of STRING lstToTraversal, boolean bDebug optional)
		[ ] string str
		[+] if(bDebug!=null && bDebug==true)
			[ ] listprint(lstToTraversal)
		[+] for each str in lstToTraversal
			[+] if(MatchStr("*{sTobeFind}*", str))
				[ ] return true
		[ ] return false
	[+] boolean glWaitObjectExist(window wObject, int iTimeOut optional)
		[+] //Description
			[ ] //  Usage:
			[ ] // glWaitObjectExist ( AH,10) - Expect the AH shows in 10 seconds, if not, print an timeout error..
			[ ] // Author		:	Eric Lu
			[ ] // Date			:	January 18, 2013	
		[+] if(iTimeOut==null)
			[ ] iTimeOut=15
		[ ] int i=0
		[+] while(i<iTimeOut)
			[+] if(wObject.Exists())
				[ ] Log.Message("Found {wObject}")
				[ ] return true
			[+] else
				[ ] sleep(1)
				[ ] i+=1
		[ ] Log.Error("The object {wObject} is not be shown in {iTimeOut} seconds.")
		[ ] return false
	[+] boolean glWaitObjectEnable(window wObject, int iTimeOut optional)
		[+] //Description
			[ ] //  Usage:
			[ ] // glWaitObjectEnable( AH,10) - Expect the AH is enabled  in 15 seconds, if not, print an timeout error..
			[ ] // Author		:	Eric Lu
			[ ] // Date			:	November 24, 2013	
		[+] if(iTimeOut==null)
			[ ] iTimeOut=15
		[ ] int i=0
		[+] while(i<iTimeOut)
			[+] if(wObject.IsEnabled)
				[ ] Log.Message("Found {wObject}")
				[ ] return true
			[+] else
				[ ] sleep(1)
				[ ] i+=1
		[ ] Log.Warning("The object {wObject} is not enabled in {iTimeOut} seconds.")
		[ ] return false
	[ ] 
[+] //Use Adiff.exe compare tool to compare two text files. if files out of tolerance, an error message will print and followed with detailed diffs.
	[-] boolean CompareFileByAdiff (string sBaseFile, string sActualFile, float fReltol optional, float fAbstol optional, string sIgnorePatternFile optional)
		[ ] //sBaseFile: the first file to compared, usually baseline file
		[ ] //sActualFile: the second file to compared, usually the actually result file
		[ ] //fReltol: the relative tolerance. default value is global const cfRelTol
		[ ] //fAbstol: the absolute tolerance. default value is global const cfAbsTol
		[ ] //sIgnorePatternFile: the ignore pattern file, please input adiff.exe --help in command line to see more details.
		[ ] 
		[ ] string sIgnorePatthenFileArg=""
		[+] if (fReltol == NULL)
			[ ] fReltol = cfRelTol
		[+] if (fAbstol == NULL)
			[ ] fAbstol = cfAbsTol
		[+] if (sIgnorePatternFile != NULL)
			[ ] sIgnorePatthenFileArg = '--ignore-patterns-file="{sIgnorePatternFile}"'
		[+] if (!SYS_FileExists (sBaseFile))
			[ ] LogError ("File: {sBaseFile} not Exists")
			[ ] return False
		[+] if (!SYS_FileExists (sActualFile))
			[ ] LogError ("File: {sActualFile} not Exists")
			[ ] return False
		[ ] list of string lsCMDLine
		[ ] //Use Classic Agent to SYS_Execute some command, this is a walkaroud of Open Agent. Open Agent can't correct SYS_Execute
		[ ] //scripts created by Classic agent.
		[ ] disconnectall()
		[ ] connect(null, CLASSIC_AGENT)
		[ ] print("abstol is {fAbstol}")
		[ ] print("fReltol is {fReltol}")
		[ ] 
		[ ] SYS_Execute ('"{csAdiffCmdLine}" --spiff -b -i -B --abstol={fAbstol} --reltol={fReltol} --ignore-aplus-history {sIgnorePatthenFileArg} "{sBaseFile}" "{sActualFile}"', lsCMDLine)
		[ ] 
		[+] if (lsCMDLine == {})
			[ ] return True
		[+] else
			[ ] Log.Message("xxx--Difference found:")
			[ ] print("============================diff begins===========================================")
			[ ] ListPrint (lsCMDLine)
			[ ] print("============================diff ends=============================================")
			[ ] return False
[+] //System Environment
	[+] String glGetSystemType()
		[+] // Author : Eric Lu  August 03,2012
			[ ] // if return x64, it means the operation system is based on  64bit, if return x86 the operation system is based on 32bit. 
		[ ] String sSystemDriver=SYS_GetEnv ("SYSTEMDRIVE")
		[ ] String sSystemType
		[+] if(SYS_DIREXISTS("{sSystemDriver}\Program Files (x86)"))
			[ ] sSystemType="x64"
		[+] else
			[ ] sSystemType="x86"
		[ ] return sSystemType
[+] boolean StringListCompare(list of string lstBase, list of string lstResult, boolean bInOrder optional,boolean pntWarning optional)
	[ ] //Description
	[ ] // both two lists are 1 dimensional string.
	[ ] // if bInOrder is null or true, it  will need the two list are the same and the items are in the same order.
	[ ] // if bInOrder is false, will ignore the order, just check two list have the same item.
	[ ] // if pntWarning is false, will not produce warning
	[ ] // Author		:	Eric Lu
	[ ] // Date			:	July 31, 2012	
	[ ] 
	[ ] 
	[+] if(ListCount(lstBase)!=ListCount(lstResult))
		[+] if(pntWarning == null || pntWarning == true)
			[ ] Log.Warning("The length of {lstBase} and {lstResult} are different")
		[ ] return false
	[+] else
		[+] if(bInOrder==null || bInOrder==true)
			[ ] int i
			[+] for(i=1;i<=ListCount(lstBase);i++)
				[+] if(lstBase[i]!=lstResult[i])
					[ ] Log.Warning("Expect '{lstBase[i]}' but get '{lstResult[i]}' for item {i} in list.")
					[ ] return false
			[+] if(i>ListCount(lstBase))
				[ ] return true
			[+] else
				[ ] return false
		[+] else
			[ ] string sItem
			[+] for each sItem in lstBase
				[+] if(ListFind(lstResult,sItem)==0)
					[ ] Log.Fail("Item {sItem} not found in the list.")
					[ ] return false
			[ ] return true
[+] int glGetSignificantFigureNumber(string sValue)
	[ ] int iRight=0
	[ ] int iLeft=0
	[ ] //sValue = "6.45e-10"
	[ ] list of string lstStr = glCastStrToList(sValue, ".")
	[ ] int iCount=Len(lstStr[2])
	[ ] string sTemp
	[+] if(val(lstStr[1])==0)
		[+] while(Lower(Left(lstStr[2],1))!="e" && iRight<iCount)
			[ ] sTemp = Right(lstStr[2],len(lstStr[2])-1)
			[ ] lstStr[2]=sTemp
			[ ] iRight+=1
		[ ] return iRight
	[+] else
		[ ] iLeft = Len(lstStr[1])
		[+] while(Lower(Left(lstStr[2],1))!="e" && iRight<iCount)
			[ ] sTemp = Right(lstStr[2],len(lstStr[2])-1)
			[ ] lstStr[2]=sTemp
			[ ] iRight+=1
		[ ] return (iRight+iLeft)
	[ ] 
[+] void CaptureCurrentBitMap(string sPath)
	[ ] Agent.SetOption (OPT_BITMAP_MATCH_COUNT, 0)
	[ ] Agent.SetOption (OPT_BITMAP_MATCH_INTERVAL, 0)
	[ ] Agent.SetOption (OPT_BITMAP_MATCH_TIMEOUT, 0)
	[+] do
		[ ] Desktop.CaptureBitmap(sPath)
		[ ] Log.Message("You can reference the screenshot {sPath}.")
	[+] except
		[ ] ExceptClear()
		[ ] Log.Warning("Failed to capture the screenshot.")
[+] glCommitAspenHysysDialog(int iSeconds)
	[ ] //Description
	[ ] // Handle the "Aspen Hysys" pop up dialog box by clicking the button Yes or OK if it pops up in iSeconds.
	[ ] // Author		:	Eric Lu
	[ ] // Date			:	Jan 10, 2013	
	[+] if (iSeconds == null)
		[ ] iSeconds = 5
	[ ] int i=0
	[+] while (i <= iSeconds)
		[+] if wAspenHysysdlg.Exists()
			[ ] wAspenHysysdlg.SetActive()
			[ ] wAspenHysysdlg.btnYes.Click()
			[ ] glWaitForMouseIdle(10)
		[+] if dlgAspenHysys.Exists()
			[ ] dlgAspenHysys.SetActive()
			[ ] dlgAspenHysys.btnYes.Click()
			[ ] glWaitForMouseIdle(10)
		[ ] sleep(1)
		[ ] i ++
[+] glRejectAspenHysysDialog(int iSeconds)
	[ ] //Description
	[ ] // Handle the "Aspen Hysys" pop up dialog box by clicking the button No or OK if it pops up in iSeconds.
	[ ] // Author		:	Eric Lu
	[ ] // Date			:	Jan 10, 2013	
	[+] if (iSeconds == null)
		[ ] iSeconds = 5
	[ ] int i=0
	[+] while (i <= iSeconds)
		[+] if wAspenHysysdlg.Exists()
			[ ] wAspenHysysdlg.SetActive()
			[+] if(wAspenHysysdlg.btnOK.Exists())
				[ ] wAspenHysysdlg.btnOK.Click()
			[+] if(wAspenHysysdlg.btnNo.Exists())
				[ ] wAspenHysysdlg.btnNo.Click()
			[ ] glWaitForMouseIdle(10)
		[+] if dlgAspenHysys.Exists()
			[ ] dlgAspenHysys.SetActive()
			[+] if(dlgAspenHysys.btnOK.Exists())
				[ ] dlgAspenHysys.btnOK.Click()
			[+] if(dlgAspenHysys.btnNo.Exists())
				[ ] dlgAspenHysys.btnNo.Click()
			[ ] glWaitForMouseIdle(10)
		[ ] i ++
[+] SetTimeOut(real rTimeOut, boolean bContinueOrNot optional)
	[ ] //Description
	[ ] //Set a timeout if the action will hang there, and you can decide the case exit or continue to execute the next step by setting the bContinueOrNot.
	[ ] //Known issue	: This method can't work together before SYS_Execute(), so if your case has SYS_Execute, please put this method after that.
	[ ] // rTimeOut	: 	the timeout value, the unit is second.
	[ ] // bContinueOrNot	:	if it is true, the case will just print an error and continue executing the next step, default is false.
	[ ] // Author		:	Eric Lu
	[ ] // Date			:	January 10, 2013	
	[ ] 
	[+] spawn
		[ ] hTimer=TimerCreate ()
		[ ] TimerStart(hTimer)
		[+] while(TimerValue(hTimer)<rTimeOut)
			[ ] 
		[ ] TimerDestroy(hTimer)
		[+] critical
			[+] if(bContinueOrNot==null || bContinueOrNot==false)
				[ ] Log.Fail("The  action didn't finished in {rTimeOut} seconds..")
				[ ] exit
			[+] else
				[ ] Log.Fail("The  action didn't finished in {rTimeOut} seconds..")
[+] void SetUnitForCase(string sUnit)
	[ ] //Description
	[ ] // Set the unit when we want to check the value, to avoid the problem that it shows different in different machine.
	[ ] // sUnit: the caption of the unit shows in Options->Unit Of Measure->Available Units Sets
	[ ] // Author		:	Eric Lu
	[ ] // Date			:	Jan 23, 2013	
	[ ] 
	[ ] AH.InvokeOptionsFromFile()
	[ ] wOptions.SetActive()
	[+] if !wOptions.lstiUnitsOfMeasure.Exists()
		[ ] wOptions.lpgUnitOfMeasure.click()
	[ ] wOptions.lstiUnitsOfMeasure.Click()
	[ ] sleep(1)
	[ ] wOptions.lpgUnitOfMeasure.lstAvailableUnitsSet.SetFocus()
	[ ] sleep(1)
	[ ] wOptions.lpgUnitOfMeasure.lstAvailableUnitsSet.Select(sUnit)
	[ ] sleep(3)
	[ ] wOptions.btnOK.Click()
	[ ] glWaitForMouseIdle(5)
[+] int copyDirectory( string inPath, string outPath, boolean copyInnerDir )
	[ ] //Copies contents of a directory to another directory, if that directory
	[ ] 
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
[+] boolean checkTolerance( number base, number toCheck, real  tolerance)
	[+] if( base == 0 && toCheck == 0)
		[ ] Log.Pass( "Base: {base}  , Checking: {toCheck},   Error: 0%     Error Limit: {tolerance * 100.0}% ")
		[ ] return True
	[+] else if( base == 0 && toCheck != 0)
		[ ] Log.Pass( "Base: {base}  , Checking: {toCheck},   Error: inf     Error Limit: {tolerance * 100.0}% ")
		[ ] return false
	[+] else if(      abs( (base - toCheck)/(1.0*base)) > tolerance )
		[ ] PRINT( "FAIL:  Base: {base}  , Checking: {toCheck},   Difference: {abs( (base - toCheck)/(1.0*base))*100.0}%     Tolerance Limit: {tolerance * 100.0}% ")
		[ ] return False
	[+] else
		[ ] Log.Pass( "Base: {base}  , Checking: {toCheck},   Difference: {abs( (base - toCheck)/(1.0*base))*100.0}%     Tolerance Limit: {tolerance * 100.0}% ")
		[ ] return true
[ ] 
[ ] 
[ ] real relTol = 0.01
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
[+] list of STRING SplitString(string sList, string sDelim)
	[ ] int i = 1
	[ ] list of STRING lsWords
	[ ] 
	[+] while(GetField(sList,sDelim, i) != "")
		[ ] ListAppend(lsWords,GetField(sList,sDelim,i))
		[ ] i++
	[ ] return lsWords
[ ] 
[+] // Need to make this function sometime...
		[+] // boolean setValueByHeader(window dataGrid, string value,  string rowHeader optional, string columnHeader optional )
			[ ] // // Header Format is       "HEADER_Name	INSTANCE #	SHIFT_AMOUNT #"
			[ ] // //Search to see if second row is blank
[ ] 
[ ] 
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
[+] Step(STRING sLog)
	[ ] prINT("==={sLog}")
[ ] 
[-] killPrograms()
	[ ] SYS_Execute("taskkill /f /t /im aspenhysys.exe")
	[ ] SYS_Execute("taskkill /f /t /im apmain.exe")
	[ ] SYS_Execute("taskkill /f /t /im concepts.exe")
	[ ] SYS_Execute("taskkill /f /t /im PVTProPkg.Exe")
	[ ] SYS_Execute("taskkill /f /t /im WerFault.exe")
	[ ] SYS_Execute("taskkill /f /t /im regsvr32.exe")
	[ ] SYS_Execute("taskkill /f /t /im regsvr32.exe")
	[ ] SYS_Execute("taskkill /f /t /im bjacwin.exe")
	[ ] SYS_Execute("taskkill /f /t /im ConceptualDesignBuilder.exe")
	[ ] SYS_Execute("taskkill /f /t /im AspenFlareSystemAnalyzer.exe")
	[ ] SYS_Execute("taskkill /f /t /im P2Converter.exe")
	[ ] 
[+] void checkForCrash()
	[+] if( dlgAspenHysysHasStoppedWorking.exists() || wAspenHysysHasStoppedWorking.Exists() )
		[ ] Log.Error("ERROR: Aspen Hysys has stopped Working")
		[ ] return
	[ ] Log.Pass("No Crash Indicated")
[+] void RunAsAdmin(string sExeFilePath)
	[ ] // This function is used for setting the exe run as administrator
	[ ] // sExeFilePath is the full path of the exe file you want to set
	[ ] // Known issue: once you used this method set the exe run as administrator successfully, you need use Administrator to logon the machine, or silk cannot invoke the exe.
	[ ] handle hFile
	[ ] handle hFileNew
	[ ] string sLine
	[ ] string sFile="{sTools}\raw.bat"
	[ ] string sFileNew="{sTools}\RunHysysAsAdmin.bat"
	[ ] string cmd
	[ ] 
	[ ] hFile = FileOpen (sFile, FM_READ )
	[ ] hFileNew=FileOpen (sFileNew, FM_WRITE )
	[+] while (FileReadLine (hFile, sLine))
			[+] if(MatchStr("*AspenHysysPath*",sLine))
				[ ] sLine=StrTran (sLine, "AspenHysysPath", sExeFilePath )
				[ ] FileWriteLine(hFileNew,sLine)
			[+] else
				[ ] FileWriteLine(hFileNew,sLine)
	[ ] FileClose(hFile)
	[ ] FileClose(hFileNew)
	[ ] SYS_Execute(sFileNew)
[+] void RemoveRunAsAdmin(string sExeFilePath)
	[ ] // This function is used for removing the run as administrator set by RunAsAdmin()
	[ ] // sExeFilePath is the full path of the exe file you want to set
	[ ] handle hFile
	[ ] handle hFileNew
	[ ] string sLine
	[ ] string sFile="{sTools}\raw2.bat"
	[ ] string sFileNew="{sTools}\RemoveRunHysysAsAdmin.bat"
	[ ] string cmd
	[ ] 
	[ ] hFile = FileOpen (sFile, FM_READ )
	[ ] hFileNew=FileOpen (sFileNew, FM_WRITE )
	[+] while (FileReadLine (hFile, sLine))
			[+] if(MatchStr("*AspenHysysPath*",sLine))
				[ ] sLine=StrTran (sLine, "AspenHysysPath", sExeFilePath )
				[ ] FileWriteLine(hFileNew,sLine)
			[+] else
				[ ] FileWriteLine(hFileNew,sLine)
	[ ] FileClose(hFile)
	[ ] FileClose(hFileNew)
	[ ] SYS_Execute(sFileNew)
[ ] 
[ ] //Append by Susan
[+] void ExpandNaviPane()
	[ ] RECT rectNavPane
	[ ] rectNavPane=AH.Find("//WPFContentControl[@name='PART_SelectedGroupContent']").GetRect()
	[+] if(rectNavPane.xSize<=34)
		[ ]  AH.Find("//WPFToggleButton[@automationId='MinimizeButton']").Click()
[ ] //Append done
[ ] 
[ ] //Performance Test
[+] list of string PerformanceMonitor(string sCounter,string sProcess,int iSamples optional)
	[ ] //This function can measure the memory and CPU usage
	[ ] list of STRING lsTable,lsOutput
	[ ] string sTable,sTemp,sCommand
	[+] if iSamples==null
		[ ] iSamples=1
	[ ] 
	[+] switch(sCounter)
		[+] case "CPU"
			[ ] sCommand="typeperf {chr(34)}\Process({sProcess})\% Processor Time{chr(34)} -sc {iSamples}"
		[+] case "Memory"
			[ ] sCommand="typeperf {chr(34)}\Process({sProcess})\Working Set{chr(34)} -sc {iSamples}"
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
[+] SwitchAPED()
	[ ] SYS_EXECUTE("{chr(34)}{sProgramFilePath}\AspenTech\AprSystem {sVersion}\PropertiesDatabase\Bin\setaped.exe{chr(34)}",NULL, EM_CONTINUE_RUNNING)
	[ ] wAspenPropertiesDatabaseSelectionApplication.Exists(30)
	[ ] sleep(0.8)
	[ ] wAspenPropertiesDatabaseSelectionApplication.rdAspenPropertiesEnterpriseDatabase.Click()
	[ ] sleep(1)
	[ ] wAspenPropertiesDatabaseSelectionApplication.btnOK.Click()
	[ ] sleep(1)
[+] SwitchLegacyDatabank()
	[ ] SYS_EXECUTE("{chr(34)}{sProgramFilePath}\AspenTech\AprSystem {sVersion}\PropertiesDatabase\Bin\setaped.exe{chr(34)}",NULL, EM_CONTINUE_RUNNING)
	[ ] wAspenPropertiesDatabaseSelectionApplication.Exists(30)
	[ ] sleep(0.8)
	[ ] wAspenPropertiesDatabaseSelectionApplication.rdLegacyPropertiesDatabanks.Click()
	[ ] sleep(1)
	[ ] wAspenPropertiesDatabaseSelectionApplication.btnOK.Click()
	[ ] sleep(1)
[ ] 
[ ] 
[ ] 
[ ] int iFailSc=0
[+] void glFail(string sErrorInfo optional,string sOutputFolder optional,string sFileName optional,int iMode optional)
	[ ] //Created by Weiwei Wu
	[ ] 
	[ ] //Feature Description:
	[ ] //This function is just an enhancement of Log.Fail. It will make a snapshot automatically and then display a Fail message.
	[ ] //Hope this can make debug a little bit easier.
	[ ] 
	[ ] string sPath
	[ ] 
	[ ] Agent.SetOption (OPT_BITMAP_MATCH_COUNT, 0)
	[ ] Agent.SetOption (OPT_BITMAP_MATCH_INTERVAL, 0)
	[ ] Agent.SetOption (OPT_BITMAP_MATCH_TIMEOUT, 0)
	[ ] 
	[ ] iFailSc++
	[+] if sFileName==null
		[ ] sFileName=str(iFailSc)
	[+] if sOutputFolder==null
		[ ] sOutputFolder=sDataout
	[+] if sErrorInfo==null
		[ ] sErrorInfo="Problem Detected. This step failed. "
	[ ] sPath=sOutputFolder+"\"+sFileName+".bmp"
	[+] do
		[ ] Desktop.CaptureBitmap(sPath)
		[ ] sErrorInfo=sErrorInfo+". You can reference the screenshot {sPath}."
	[+] except
		[ ] 
	[+] if iMode==2
		[ ] Log.Warning("{sErrorInfo}")
	[+] else
		[ ] Log.Fail("{sErrorInfo}")
	[ ] 
[+] void glInitializeWin(window wWin,real rTimeOut optional)
	[ ] //Created by Weiwei Wu
	[ ] //Feature Description
	[ ] //This function will wait till a window exist and then maximize it. It would be good if everyone can maximize a window before
	[ ] //we actually do sth on it because when I debug, I encounter a lot of issue such as "xxx cannot be click because it is
	[ ] //out of screen" Hope this could be a fix.
	[ ] 
	[ ] //The other thing is that when the rTimeOut is set to zero, it will open the window you want for you.
	[ ] //Curently, it support following window:
	[ ] //wPalette
	[ ] //Definition
	[ ] int i
	[ ] boolean bWin
	[ ] HTIMER hTime=TimerCreate("Timer")
	[ ] TimerStart(hTime)
	[ ] RECT rectDesktop,rectWin
	[ ] boolean bOpenWindow=true
	[ ] list of window lwWindowMaximize={...}
	[ ] 
	[+] if rTimeOut==null
		[ ] rTimeOut=30
	[ ] 
	[ ] //standard way to open window
	[+] if rTimeOut==0
		[+] switch wWin
			[+] case wPalette
				[ ] AH.SetActive()
				[ ] AH.Maximize()
				[ ] 
				[ ] i=0
				[+] while i<=900
					[+] if AH.GetMode()!="Simulation"
						[ ] i++
						[ ] AH.SetMode("Simulation")
						[ ] sleep(5)
					[+] else
						[ ] break
				[+] if i>900
					[ ] glFail("Fail to switch to simulation mode within 900s")
					[ ] return
				[ ] 
				[ ] //use F4 to open to window
				[ ] i=0
				[+] for (i=0;i<=10;i++)
					[ ] AH.SetActive()
					[ ] sleep(1)
					[ ] AH.TypeKeys("<F4>")
					[+] if wPalette.Exists(10)
						[ ] sleep(1)
						[ ] return
				[ ] 
				[ ] //if f4 failed, then use clicking methods
				[ ] sleep(0.5)
				[ ] AH.SetTab("View")
				[+] if AH.btnModelPalette.Exists(10)
					[+] if AH.btnModelPalette.GetProperty("IsEnabled")
						[ ] sleep(1)
						[ ] AH.btnModelPalette.Click()
						[ ] return
				[ ] 
				[ ] //if both of the methods failed, then we have nothing to do
				[ ] glFail("The model and streams palette is not active or cannot be launched")
				[ ] return
				[ ] 
				[ ] 
				[ ] 
			[+] default
				[ ] glFail("Unable to Find and Open Window {wWin}, please check to verify the window is correct")
				[ ] return
	[+] else
		[ ] bOpenWindow=false
	[ ] 
	[ ] //After open window, it will use default timeout
	[+] if bOpenWindow==true
		[ ] rTimeOut=30
	[ ] 
	[ ] //Wait for the window to open, then maximize it
	[+] while rTimeOut>=TimerValue(hTime)
		[+] if wWin.Exists()
			[ ] sleep(1)
			[ ] break
		[+] if wAspenHysys.Exists()
			[ ] sleep(0.8)
			[+] do
				[ ] wAspenHysys.Close()
			[ ] except
	[+] if TimerValue(hTime)>rTimeOut
		[ ] Log.Warning("Windows {wWin} failed to show up within {rTimeOut} s. Trying to launch it for you")
		[ ] glInitializeWin(wWin,0)
	[+] else
		[ ] i=0
		[+] while TimerValue(hTime)<=rTimeOut
			[ ] bWin=false
			[+] do
				[ ] bWin=wWin.GetProperty("IsEnabled")
			[ ] except
			[+] if bWin==false
				[+] do
					[ ] bWin=wWin.GetProperty("Enabled")
				[ ] except
			[+] if bWin==true
				[ ] break
			[+] else
				[ ] sleep(0.9)
				[ ] i++
		[+] if TimerValue(hTime)>rTimeOut
			[ ] glFail("Fail to enabled the window within {rTimeOut} s",null,null,2)
			[ ] return
		[ ] sleep(1)
		[ ] wWin.SetActive()
		[ ] sleep(0.5)
		[+] // if we cannot maximize the window, then we try to move the window to the center of the screen
			[+] if ListFind(lwWindowMaximize,wWin)!=0
				[+] do
					[ ] wWin.Maximize()
				[+] except
					[ ] Log.Message("Fail to maximize the window {wWin.GetCaptire()}. Just Move it to the center of the screen")
					[ ] Agent.SetOption(OPT_SYNC_TIMEOUT,0)
					[ ] rectDesktop=Desktop.GetRect()
					[ ] rectWin=wWin.GetRect()
					[ ] wWin.Move((rectDesktop.xSize-rectWin.xSize)/2,(rectDesktop.ySize-rectWin.ySize)/2)
			[+] else
				[ ] rectDesktop=Desktop.GetRect()
				[+] if rectDesktop.xSize==1920&&rectDesktop.ySize==1080
					[ ] wWin.Move(200,200)
					[ ] wWin.Size(1000,700)
				[+] else if rectDesktop.xSize==1600&&rectDesktop.ySize==900
					[ ] wWin.Move(120,120)
					[ ] wWin.Size(1000,640)
	[ ] wWin.SetActive()
	[ ] sleep(1)
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
			[ ] i=StrPos(".",sStringToSplit)
			[ ] continue
		[+] else
			[ ] ListAppend(y,SubStr(sStringToSplit,1,(i-1)))
		[ ] sStringToSplit=SubStr(sStringToSplit,(i+1))
		[ ] i=StrPos(".",sStringToSplit)
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
[-] list of string GetAllDataInOneColumn(window wTable, integer icol)
	[ ] list of string lsAllModels
	[ ] integer i, inum, icell
	[ ] inum=ListCount(wTable.FindAll("//WPFDataGridRow"))
	[ ] // icell=ListCount(wTable.FindAll("//WPFDataGridCell"))
	[ ] icell=ListCount(wTable.FindAll("//WPFDataGridRow[1]//WPFDataGridCell"))
	[-] for(i=0;i<inum;i++)
		[ ] // ListAppend(lsAllModels,wTable.Find("//WPFDataGridCell[{i*(icell/inum)+icol}]").sCaption)
		[ ] ListAppend(lsAllModels,wTable.Find("//WPFDataGridCell[{i*(icell)+icol}]").sCaption)
		[ ] sleep(1)
	[ ] ListPrint(lsAllModels)
	[ ] return lsAllModels
[+] string GetFieldContent(integer iFieldOrder, window w optional)
	[+] if(w==null)
		[ ] return AH.Find("//WPFControl[@automationId='PART_editControl'][{iFieldOrder}]/WPFTextBlock").sCaption
	[+] else
		[ ] return w.Find("//WPFControl[@automationId='PART_editControl'][{iFieldOrder}]/WPFTextBlock").sCaption
[+] void SaveToNotepad(string sFileName)
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
[ ] 
[+] void VerifyCaptialCostFlyoverValues(string sTooltip, boolean bIsPopup optional)
	[ ] //sTooltip is the data in Tooltip
	[ ] string sECost,sICost,sECUnit,sICUnit,sTemp
	[+] if(bIsPopup==null)
		[ ] bIsPopup=false
	[+] if(!bIsPopup)
		[ ] AH.SetActive()
		[ ] sleep(1)
		[ ] sECost=AH.Find("//WPFControl[@className='XamTextEditor'][8]").TextCapture()
		[ ] sICost=AH.Find("//WPFControl[@className='XamTextEditor'][9]").TextCapture()
		[ ] sTemp=AH.Find("//WPFContentControl[66]").TextCapture()
		[ ] sECUnit=SubStr(sTemp,StrPos("[",sTemp)+1,StrPos("]",sTemp)-StrPos("[",sTemp)-1)
		[ ] sTemp=AH.Find("//WPFContentControl[68]").TextCapture()
		[ ] sICUnit=SubStr(sTemp,StrPos("[",sTemp)+1,StrPos("]",sTemp)-StrPos("[",sTemp)-1)
		[ ] sleep(1)
		[+] if(MatchStr("*{sECost}*",sTooltip) && MatchStr("*{sICost}*",sTooltip) && MatchStr("*{sECUnit}*",sTooltip) && MatchStr("*{sICUnit}*",sTooltip))
			[ ] Log.Pass("The value of 'Total equipment cost' and 'total installed cost' on the dashboard and the tooltip match.")
		[+] else
			[ ] Log.Fail("The value of 'Total equipment cost' and 'total installed cost' on the dashboard and the tooltip do not match.")
	[+] else
		[ ] wEconomicEquipmentDataSummary.SetActive()
		[ ] sleep(3)
		[ ] sECost=wEconomicEquipmentDataSummary.txtEquipmentCost.TextCapture()
		[ ] sleep(1)
		[ ] sICost=wEconomicEquipmentDataSummary.txtInstalledCost.TextCapture()
		[ ] sleep(1)
		[ ] sTemp=wEconomicEquipmentDataSummary.Find("//WPFContentControl[45]").TextCapture()
		[ ] sECUnit=SubStr(sTemp,StrPos("[",sTemp)+1,StrPos("]",sTemp)-StrPos("[",sTemp)-1)
		[ ] sleep(1)
		[ ] sTemp=wEconomicEquipmentDataSummary.Find("//WPFContentControl[47]").TextCapture()
		[ ] sICUnit=SubStr(sTemp,StrPos("[",sTemp)+1,StrPos("]",sTemp)-StrPos("[",sTemp)-1)
		[ ] sleep(2)
		[+] if(MatchStr("*{sECost}*",sTooltip) && MatchStr("*{sICost}*",sTooltip) && MatchStr("*{sECUnit}*",sTooltip) && MatchStr("*{sICUnit}*",sTooltip))
			[ ] Log.Pass("The value of 'Total equipment cost' and 'total installed cost' on the dashboard and the tooltip match.")
		[+] else
			[ ] Log.Fail("The value of 'Total equipment cost' and 'total installed cost' on the dashboard and the tooltip do not match.")
		[ ] 
	[ ] 
[+] void VerifyCaptialCost(boolean bIsPopup optional)
	[ ] //sTooltip is the data in Tooltip
	[ ] string sVal,sUnit,sTemp
	[+] if(bIsPopup==null)
		[ ] bIsPopup=false
	[+] if(!bIsPopup)
		[ ] AH.SetActive()
		[ ] sleep(1)
		[ ] sVal=AH.Find("//WPFControl[@className='XamTextEditor'][1]").TextCapture()
		[ ] sTemp=AH.Find("//WPFContentControl[52]").TextCapture()
		[ ] sUnit=SubStr(sTemp,StrPos("[",sTemp)+1,StrPos("]",sTemp)-StrPos("[",sTemp)-1)
		[+] if(sVal==AH.grpCaptialCost.txtCaptialCostValue.sCaption && sUnit==AH.grpCaptialCost.txtCaptialCostUnit.sCaption)
			[ ] Log.Pass("'Captial Cost' value in the form is the same as in the panel.")
		[+] else
			[ ] Log.Fail("'Captial Cost' value in the form is not the same as in the panel.")
	[+] else
		[ ] wEconomicEquipmentDataSummary.SetActive()
		[ ] sleep(1)
		[ ] sVal=wEconomicEquipmentDataSummary.txtTotalCaptialCost.TextCapture()
		[ ] sTemp=wEconomicEquipmentDataSummary.Find("//WPFContentControl[31]").TextCapture()
		[ ] sUnit=SubStr(sTemp,StrPos("[",sTemp)+1,StrPos("]",sTemp)-StrPos("[",sTemp)-1)
		[ ] sleep(1)
		[ ] wEconomicEquipmentDataSummary.Minimize()
		[ ] sleep(1)
		[+] if(sVal==AH.grpCaptialCost.txtCaptialCostValue.sCaption && sUnit==AH.grpCaptialCost.txtCaptialCostUnit.sCaption)
			[ ] Log.Pass("'Captial Cost' value in the form is the same as in the panel.")
		[+] else
			[ ] Log.Fail("'Captial Cost' value in the form is not the same as in the panel.")
	[ ] 
[+] void VerifyUtilityCost(boolean bIsPopup optional)
	[ ] //sTooltip is the data in Tooltip
	[ ] string sVal,sUnit,sTemp
	[+] if(bIsPopup==null)
		[ ] bIsPopup=false
	[+] if(!bIsPopup)
		[ ] AH.SetActive()
		[ ] sleep(1)
		[ ] sVal=AH.Find("//WPFControl[@className='XamTextEditor'][5]").TextCapture()
		[ ] sTemp=AH.Find("//WPFContentControl[60]").TextCapture()
		[ ] sUnit=SubStr(sTemp,StrPos("[",sTemp)+1,StrPos("]",sTemp)-StrPos("[",sTemp)-1)
		[+] if(sVal==AH.grpUtilityCost.txtUtilityCosttValue.sCaption && sUnit==AH.grpUtilityCost.txtUtilityCostUnit.sCaption)
			[ ] Log.Pass("'Utility Cost' value in the form is the same as in the panel.")
		[+] else
			[ ] Log.Fail("'Utility Cost' value in the form is not the same as in the panel.")
	[+] else
		[ ] wEconomicEquipmentDataSummary.SetActive()
		[ ] sleep(1)
		[ ] sVal=wEconomicEquipmentDataSummary.txtUtilityCost.TextCapture()
		[ ] sTemp=wEconomicEquipmentDataSummary.Find("//WPFContentControl[39]").TextCapture()
		[ ] sUnit=SubStr(sTemp,StrPos("[",sTemp)+1,StrPos("]",sTemp)-StrPos("[",sTemp)-1)
		[ ] sleep(1)
		[ ] wEconomicEquipmentDataSummary.Minimize()
		[ ] sleep(1)
		[+] if(sVal==AH.grpUtilityCost.txtUtilityCosttValue.sCaption && sUnit==AH.grpUtilityCost.txtUtilityCostUnit.sCaption)
			[ ] Log.Pass("'Utility Cost' value in the form is the same as in the panel.")
		[+] else
			[ ] Log.Fail("'Utility Cost' value in the form is not the same as in the panel.")
		[ ] 
	[ ] 
[+] void VerifyNoLicenseUsage()			//SLM_Econ_IPE 
	[ ] list of string lsTemp
	[ ] integer i
	[ ] string sComputerName=SYS_GetEnv("computername")
	[ ] glwSLMLicenseProfiler.Invoke()
	[ ] glwSLMLicenseProfiler.SetActive()
	[+] do
		[ ] glwSLMLicenseProfiler.cboLicenseServer.Select("shslmtest")
	[+] except
		[ ] ExceptClear()
		[ ] glwSLMLicenseProfiler.cboLicenseServer.Select("shdevfile01")
	[ ] glwSLMLicenseProfiler.cboLicenseServer.Click()
	[ ] 
	[ ] sleep(3)
	[ ] glwSLMLicenseProfiler.btnLoadInformation.Click()
	[ ] sleep(1)
	[ ] glWaitForMouseIdle(50)
	[ ] glwSLMLicenseProfiler.btnViewLicenses.Click()
	[ ] sleep(1)
	[ ] glWaitForMouseIdle(200)
	[ ] glwSLMLicenseProfiler.dgGrid.sclVertical.ScrollByLine(25)
	[ ] glwSLMLicenseProfiler.dgGrid.Find("/DataGridRow[8]").Click()
	[ ] sleep(1)
	[ ] glwSLMLicenseProfiler.btnViewLicenseUsage.Click()
	[ ] sleep(1)
	[+] if(wLicenseUsageDetails.Exists(5))
		[ ] wLicenseUsageDetails.SetActive()
		[+] if(wLicenseUsageDetails.txtContents.GetContents()[1]=="No users found.")
			[ ] Log.Pass("No usage of SLM_Econ_IPE.")
		[+] else
			[ ] lsTemp=wLicenseUsageDetails.txtContents.GetContents()
			[+] for(i=1;i<=ListCount(lsTemp);i++)
				[+] if(MatchStr("*Computer name:	{sComputerName}*",lsTemp[i]))
					[ ] break
			[+] if(i>ListCount(lsTemp))
				[ ] Log.Pass("No usage of SLM_Econ_IPE.")
			[+] else
				[ ] Log.Fail("There's usage of SLM_Econ_IPE.")
		[ ] wLicenseUsageDetails.btnClose.Click()
		[ ] sleep(1)
	[+] else
		[ ] Log.Fail("'License Usage Details' window does not pop up.")
	[+] glwSLMLicenseProfiler.Close()
		[ ] 
	[ ] sleep(1)
	[ ] 
[ ] 
[ ] 
[ ] //==============Appended Done===========
[ ] 
[ ] 
[ ] 
