[ ] use "../frame/APMainFrame.inc"
[ ] 
[ ] 
[-] //Aspen Plus Main window
	[ ] //Open Agent
	[-] window wcAspenPlus APlus
		[ ] locator "/WPFWindow[@caption='* - Aspen Plus*- aspenONE*']"
		[ ] 
		[+] //-----------------------------Blocks-------------------------------//
			[+] void SetBlockTemp(STRING BlockName, STRING Temp)
				[ ] this.SetActive()
				[ ] this.trviBlocks.Expand()
				[ ] this.trvPartTree.Click(BlockName)
				[ ] this.grpFlashSpecifications.Temperature.Click()
				[ ] this.grpFlashSpecifications.Temperature.txtTemperature.setText("{Temp}")
				[ ] window w = this.Find("//WPFControl[@automationId='PART_editControl'][3]")
				[ ] w.TypeKeys("{Temp}<enter>",0.2)
				[ ] sleep(1)
				[ ] 
			[+] void CheckBlockTemp(STRING BlockName, STRING Temp, BOOLEAN bOriginal optional)
				[ ] //bOriginal  true  means the result have not been overwritten
				[ ] //bOriginal  false  means the result have  been overwritten
				[ ] STRING BlockNameCon ="trvi{BlockName}"
				[ ] STRING sTemp=""
				[+] if(bOriginal==null)
					[ ] bOriginal =  TRUE
				[ ] this.SetActive()
				[ ] this.trviBlocks .Expand()
				[ ] this.trvPartTree.Click(BlockName)
				[ ] this.@BlockNameCon.Expand()
				[ ] this.trvBlockResults.Select()
				[ ] this.trvPartTree.Click("Results")
				[ ] this.grpResultSummary.Temperature.click()
				[ ] sTemp=this.grpResultSummary.Temperature.txtTemperature.Text
				[ ] print(sTemp)
				[+] if(sTemp==Temp)
					[+] if bOriginal
						[ ] Log.Pass("Results have not been overwritten (i.e. temp in {BlockName} is still {Temp}F")
					[+] else 
						[ ] Log.Pass("Results have been overwritten (i.e. temp in {BlockName} is {Temp}F now")
				[+] else
					[ ] Log.Fail("Check Block temp failed!!!")
				[ ] this.@BlockNameCon.Collapse()
			[+] void VerifyBlockResults(BOOLEAN bExists optional)
				[ ] //bExists true means Block Results  shoud be displayed
				[ ] this.SetActive()
				[+] if this.grpResultSummary.Temperature.IsEnabled&&this.grpResultSummary.Pressure.IsEnabled
					[+] // if((AP.BlockTemperatureValue.Text!="")&&(AP.OutletPressureValue.Text!=""))
						[ ] Log.Pass("Partial Results are displayed!")
				[+] else
					[+] if((bExists!=null)&&bExists)
						[ ] Log.Fail("Block Results are empty!!")
					[+] else
						[ ] Log.Pass("Block Results are empty!!")
			[+] void RenameBS(STRING Name, STRING NewName)
				[+] //Desc&History
					[ ] //*********************************************************************
					[ ] //	Function Name:		RenameBS
					[ ] //	Description:			Rename Block or Streams
					[ ] //	Argument:				STRING Name: Block Name with definition like 'trviB1' in * inc file
					[ ]                                                                            //Stream Name with definition like 'trviS1' in *inc file
					[ ] 
					[ ] //    Example:                       RenameBS("B1","BLK1")
					[ ]                                              //RenameBS("S1","Stream1")
					[ ] 
					[ ] //	Tester:					Amy.Wang(Amy.Wang@aspentech.com)
					[ ] //	Date:					April  16, 2012
					[+] //	History:	
						[ ] //					None	
					[ ] //***********************************************************************
				[ ] 
				[ ] // STRING NameCon ="trvi{Name}"
				[ ] 
				[ ] this.SetActive()
				[+] if(MatchStr("*S*",Name))
					[ ] this.trviStreams.Expand()
				[+] if(MatchStr("*B*",Name))
					[ ] this.trviBlocks.Expand()
				[+] do
					[ ] this.Find("//WPFTreeViewItem[@caption='{Name}']").Click(2)
					[ ] sleep(1)
				[+] except
					[+] if E_WINDOW_NOT_FOUND == exceptnum()
						[ ] this.Find("//WPFTreeViewItem[@caption='{Substr(Name,2)}']").Click(2)
					[+] else
						[ ] reraise
				[ ] // this.@NameCon.Click(2)
				[ ] this.miRename.Click()
				[ ]  wRename.SetActive()
				[ ]  wRename.TbText.SetText(NewName)
				[ ]  wRename.BtnOK.Click()
			[+] void DeleteBS(STRING Name)
				[+] //Desc&History
					[ ] //*********************************************************************
					[ ] //	Function Name:		RenameBS
					[ ] //	Description:			Rename Block or Streams
					[ ] //	Argument:				STRING Name: Block Name with definition like 'trviB1' in * inc file
					[ ]                                                                            //Stream Name with definition like 'trviS1' in *inc file
					[ ] 
					[ ] //    Example:                       DeleteBS("B1")
					[ ]                                              //DeleteBS("S1")
					[ ] 
					[ ] //	Tester:					Amy.Wang(Amy.Wang@aspentech.com)
					[ ] //	Date:					Jan  18, 2012
					[+] //	History:	
						[ ] //					None	
					[ ] //***********************************************************************
				[ ] 
				[ ] STRING NameCon ="trvi{Name}"
				[ ] 
				[ ] this.SetActive()
				[+] if(MatchStr("*S*",NameCon))
					[ ] this.trviStreams.Expand()
				[+] if(MatchStr("*B*",NameCon))
					[ ] this.trviBlocks.Expand()
				[ ] this.@NameCon.Click(2)
				[ ] this.miDelete.Click()
				[ ]  dlgAspenPlusOKOrCancel.SetActive()
				[ ]  dlgAspenPlusOKOrCancel.BtnOK.Click()
			[ ] 
		[+] //----------------------------Streams---------------------------//
			[+] void AddStreams(STRING StreamName,STRING SteamType)
				[ ] this.SetActive()
				[ ] this.trviStreams.Click()
				[ ] this.btnNew.Click()
				[ ] wCreateNewId.SetActive()
				[ ] wCreateNewId.TxbText.SetText(StreamName)
				[ ] wCreateNewId.cboType.Select(SteamType)
				[ ] wCreateNewId.btnOK.Click()
				[ ] sleep(2)
		[+] //-----------------Interactively Load Results---------------------//
			[+] void InteractivelyLoadResults(BOOLEAN bStatus)
				[+] //Desc&History
					[ ] //*********************************************************************
					[ ] //	Description:			Switch Interactively Load Results  status  by File -> Options -> Simulation
					[ ] //	Argument:				BOOLEAN bStatus: TRUE, Switch Interactively Load Results  status on
					[ ]                                                                                  //False , Switch Interactively Load Results  status off
					[ ] 
					[ ] //    Example:                       InteractivelyLoadResults(TRUE)                                  
					[ ] //	Tester:					Amy.Wang(Amy.Wang@aspentech.com)
					[ ] //	Date:					April  16, 2012
					[+] //	History:	
						[ ] //					None	
					[ ] //***********************************************************************
					[ ] 
				[ ] 
				[ ] sleep(5)
				[ ] this.SetActive()
				[ ] //File -> Options -> Simulation
				[ ] this.mnuFile.Click()
				[ ] this.miOptions.Click()
				[ ] // sleep(1)
				[ ] // AspenPlusClassicWin.DialogBox("#1").SetActive()
				[ ] // RECT rc = AspenPlusClassicWin.DialogBox("#1").GetRect()
				[ ] // Agent.SetOption (OPT_VERIFY_EXPOSED, false)
				[ ] // AspenPlusClassicWin.  DialogBox("#1").Click(1,rc.xSize  - 70, rc.ySize - 15)
				[ ] // Agent.SetOption (OPT_VERIFY_EXPOSED, TRUE)
				[ ] wSimulationRunOptions.SetActive()
				[+] if(wSimulationRunOptions.ChkInteractiveLoad.State)
					[+] if(!bStatus)
						[ ] wSimulationRunOptions.ChkInteractiveLoad.Uncheck()
						[ ] wSimulationRunOptions.Btn_OK.Click()
						[ ] return
				[ ] wSimulationRunOptions.ChkInteractiveLoad.Check()
				[ ] wSimulationRunOptions.Btn_OK.Click()
			[+] void CheckInteractivelyLoadState(BOOLEAN bStatus)
				[+] //Desc&History
					[ ] //*********************************************************************
					[ ] //	Description:			Check Interactively Load Results  status  by File -> Options -> Simulation
					[ ] //	Argument:				BOOLEAN bStatus: TRUE, Check Interactively Load Results  status is on
					[ ]                                                                                  //False , Check Interactively Load Results  status is  off
					[ ] 
					[ ] //    Example:                       CheckInteractivelyLoadState(TRUE)                                  
					[ ] //	Tester:					Amy.Wang(Amy.Wang@aspentech.com)
					[ ] //	Date:					April  16, 2012
					[+] //	History:	
						[ ] //					None	
					[ ] //***********************************************************************
					[ ] 
					[ ] 
				[ ] 
				[ ] this.SetActive()
				[ ] //File -> Options -> Simulation
				[ ] // this.mnuFile.Click()
				[ ] // sleep(1)
				[ ] // AspenPlusClassicWin.DialogBox("#1").SetActive()
				[ ] // RECT rc = AspenPlusClassicWin.DialogBox("#1").GetRect()
				[ ] // Agent.SetOption (OPT_VERIFY_EXPOSED, false)
				[ ] // AspenPlusClassicWin.  DialogBox("#1").Click(1,rc.xSize  - 70, rc.ySize - 15)
				[ ] // Agent.SetOption (OPT_VERIFY_EXPOSED, true)
				[ ] this.mnuFile.Click()
				[ ] this.miOptions.Click()
				[ ] wSimulationRunOptions.SetActive()
				[ ] //bStatus=SimulationRunOptions.ChkInteractiveLoad.IsChecked()
				[+] if(wSimulationRunOptions.ChkInteractiveLoad.IsChecked)
					[+] if(bStatus)
						[ ] Log.Pass(" Load Results mode is on")
					[+] else 
						[ ] Log.Fail("Check InteractivelyLoad State fail!!!")
				[+] else
					[+] if(!bStatus)
						[ ] Log.Pass(" Load Results mode is off")
					[+] else 
						[ ] Log.Fail("Check InteractivelyLoad State fail!!!")
					[ ] 
				[ ] wSimulationRunOptions.Btn_OK.Click()
			[+] void EnableGolbalData(BOOLEAN bEnabled)
				[ ] this.SetActive()
				[ ] this.SetTab("Main Flowsheet")
				[ ] this.SetTab("Modify")
				[ ] this.miDisplayOptions.Click(1,21,56)
				[+] if(this.miGlobalData.IsChecked)
					[+] if(!bEnabled)
						[ ] this.miGlobalData.Click()
						[ ] return
					[+] else
						[ ] return
				[+] else
					[+] if(bEnabled)
						[ ] this.miGlobalData.Click()
						[ ] return
					[+] else
						[ ] return
					[ ] 
			[+] void LoadResult()
				[ ] this.SetActive()
				[ ] this.SetTab("Home")
				[ ] this.grpRun.btnRunSettings.Click()
				[ ]  wRunSettings.SetActive()
				[ ]  wRunSettings.TbOptions.Click()
				[ ]  wRunSettings.BtnLoad.Click()
				[ ] sleep(2)
				[ ]  wRunSettings.BtnOk.Click()
			[+] void InteractivelyLoadResultsByFile(STRING sDir,BOOLEAN bStatus)
				[ ] 
				[+] //Desc&History
					[ ] //*********************************************************************
					[ ] //	Description:			Switch Interactively Load Results  status  by edit 'partial 1' in * bkp file
					[ ] 
					[ ] //	Argument:				BOOLEAN bStatus: TRUE, Check Interactively Load Results  status  on
					[ ]                                                                                  //False , Check Interactively Load Results  status   off
					[ ] //                                                      STRING sDir:  The path of *bkp file        
					[ ] //    Example:                       InteractivelyLoadResultsByFile(TRUE)                                  
					[ ] //	Tester:					Amy.Wang(Amy.Wang@aspentech.com)
					[ ] //	Date:					April  16, 2012
					[+] //	History:	
						[ ] //					None	
					[ ] //***********************************************************************
				[ ] 
				[ ] LIST OF STRING IsContents = {}
				[ ] INT i=0
				[ ] IsContents=File.Read(sDir)
				[+] for(i=1;i<=listcount(IsContents);i++)
					[+] if(MatchStr("*partial *",IsContents[i]))
						[+] if bStatus
							[ ] IsContents[i]="partial 1"
						[+] else
							[ ] IsContents[i]="partial 0"
					[ ] 
				[ ] File.Delete(sDir)
				[ ] File.New(sDir,IsContents)
			[+] void CheckInteractivelyLoadState2(BOOLEAN bStatus)
					[ ] //bStatus TRUE means Load Results mode is on
					[ ] //bStatus FALSE means Load Results mode is off
					[ ] this.SetActive()
					[ ] sleep(2)
					[ ] //File -> Options -> Simulation
					[ ] //Run settings-> options
					[ ]  this.SetTab("Home")
					[ ] this.grpRun.btnRunSettings.Click()
					[ ]  wRunSettings.SetActive()
					[ ]  wRunSettings.TbOptions.Click()
					[+] if( wRunSettings.ChkInteractivelyLoad.IsChecked)
						[+] if(bStatus)
							[ ] Log.Pass(" Load Results mode is on")
						[+] else 
							[ ] Log.Fail("Check InteractivelyLoad State fail!!!")
					[+] else
						[+] if(!bStatus)
							[ ] Log.Pass(" Load Results mode is off")
						[+] else 
							[ ] Log.Fail("Check InteractivelyLoad State fail!!!")
						[ ] 
				[ ]  wRunSettings.BtnOk.Click()
			[ ] 
			[ ] 
			[ ] 
		[+] //--------------------- Check Result Files----------------------//
			[+] void GenerateHistoryFile()
				[ ] 
				[ ] INT i=0
				[ ] BOOLEAN bFlag = false
				[ ] 
				[ ] this.SetActive()
				[ ] this.SetTab("Home")
				[ ] 
				[ ] this.grpSummary.btnHistory.Click()
				[ ] glwNotepad.SetActive()
				[ ] Clipboard.SetText({})
				[ ] glwNotepad.TypeKeys("<Ctrl-a>")
				[ ] glwNotepad.TypeKeys("<Ctrl-c>")
				[ ] LIST of STRING HistoryContents = Clipboard.GetText()
				[+] for(i=1;i<=listcount(HistoryContents);i++)
					[+] if MatchStr("*Report file generated*",HistoryContents[i])
						[ ] Log.Pass("History file is generated successfully")
						[ ] bFlag=true
				[+] if(bFlag == false)
					[ ] Log.Fail("Please check the history file!!!")
				[ ] glwNotepad.Close()
			[+] void ViewReport(STRING sCategory, STRING sItemName, STRING sDir)
				[ ] this.SetActive()
				[ ] this.SetTab("Home")
				[ ] this.grpSummary.btnReport.Click()
				[+] if(dlgAspenPlus.Exists(5))
					[ ] dlgAspenPlus.SetActive()
					[ ] Log.Message(dlgAspenPlus.TxtBlock.Text)
					[ ] dlgAspenPlus.BtnYes.Click()
					[ ] return
				[+] if !wReport.Exists(2)
					[ ] this.TypeKeys("<Ctrl-Alt-R>",0.2)
				[ ] wReport.SetActive()
				[ ] wReport.Select(sCategory,sItemName)
				[ ] wReport.Apply.Click()
				[ ] sleep(2)
				[ ] glwNotepad.SaveFile(sDir)
				[ ] glwNotepad.mnuFile.miExit.Pick()
				[ ] wReport.Cancel.Click()
			[+] AddNewTabView(string newTabViewName)
				[ ] //Simulation-->Result Summary--> Streams(Custom)-->Add new Tab
				[ ] // AddNewTabView ( string )  - Add a new view  name it as newTabViewName 
				[ ] //  Arguments:
				[ ] //  1.  newTabViewName  - string, name of the tab view you want to add
				[ ] //  Usage: AP.AddNewTabView("sheet1")
				[ ] glWaitForMouseIdle(30)
				[ ] this.hccSimulation.Click()
				[ ] this.RunAP(3)
				[ ] this.TypeKeys("<Ctrl-F8>")
				[ ] sleep(2)
				[ ] this.trviResultsSummary.Click()
				[ ] sleep(2)
				[ ] this.trviResultsSummary.Expand()
				[ ] sleep(2)
				[ ] this.trviCustomStream.Click()
				[ ] sleep(5)
				[ ] this.tabiDefault.Click(2)
				[+] if(contextMenuBox.Exists(5))
					[ ] contextMenuBox.TypeKeys("<Down>")
					[ ] sleep(1)
					[ ] contextMenuBox.TypeKeys("<Enter>")
				[+] else
					[ ] Log.Error("The expected context menu didn't pop up")
					[ ] 
				[+] if(wInputName.Exists(10))
					[ ] wInputName.SetActive()
					[ ] wInputName.TextboxName.SetText(newTabViewName)
					[ ] wInputName.btnOK.Click()
				[+] else
					[ ] Log.Error("Didn't find the expected Input Name window.")
					[ ] 
			[+] CountIteration(string sFile, integer iMax )
				[ ] HFILE hFile
				[ ] STRING sLine
				[ ] 
				[ ] string sIteration = "Iteration"
				[ ] string sNext 
				[ ] integer iLine = 0
				[ ] integer iIterationCount = 0
				[ ] integer nNum
				[ ] // =======================================================
				[ ] 
				[ ] hFile = FileOpen (sFile, FM_READ)
				[+] while (FileReadLine (hFile, sLine))
					[ ] sLine = left(trim(sLine),Len(sIteration))
					[ ] 
					[+] if sLine == sIteration
						[+] while(FileReadLine (hFile, sLine))
							[ ] sNext = left(trim(sLine),2)
							[ ] iLine = iLine+2
							[+] if MatchStr("Successful solution*",sLine)
								[ ] break
							[ ] nNum = Val (sNext)
							[+] if nNum == iIterationCount
								[ ] iIterationCount++
							[ ] 
						[ ] iIterationCount-- 
					[ ] iLine++
				[ ] 
				[ ] FileClose (hFile)
				[ ] 
				[ ] 
				[+] if iIterationCount > iMax
					[ ] Log.Error("Number of iterations - {iIterationCount} exceed {iMax}")
				[+] if iIterationCount < iMax
					[ ] Log.Error("Number of iterations - {iIterationCount} less then {iMax}")
				[ ] 
				[+] if iIterationCount == iMax
					[ ] Log.Pass("Number of iterations  is - {iIterationCount}")
				[ ] 
			[+] CountIterationInclude0(string sFile, integer iMax )
				[ ] HFILE hFile
				[ ] STRING sLine
				[ ] 
				[ ] string sIteration = "Iteration"
				[ ] string sNext 
				[ ] integer iLine = 0
				[ ] integer iIterationCount = 0
				[ ] integer nNum
				[ ] integer i=0
				[ ] boolean bIteration0 = false
				[ ] // =======================================================
				[ ] 
				[ ] hFile = FileOpen (sFile, FM_READ)
				[+] while (FileReadLine (hFile, sLine))
					[ ] sLine = left(trim(sLine),Len(sIteration))
					[ ] 
					[+] if sLine == sIteration
						[+] while(FileReadLine (hFile, sLine))
							[ ] sNext = left(trim(sLine),2)
							[ ] iLine = iLine+2
							[ ] nNum = Val (sNext)
							[+] if nNum == iIterationCount
								[+] if(iIterationCount==1)&&( i==2)
									[ ] bIteration0 = TRUE
								[ ] iIterationCount++
							[ ] i++
						[ ] iIterationCount-- 
					[ ] iLine++
				[ ] 
				[ ] FileClose (hFile)
				[ ] 
				[+] if bIteration0
					[ ] iIterationCount++
				[ ] 
				[+] if iIterationCount > iMax
					[ ] Log.Error("Number of iterations - {iIterationCount} exceed {iMax}")
				[+] if iIterationCount < iMax
					[ ] Log.Error("Number of iterations - {iIterationCount} less then {iMax}")
				[ ] 
				[+] if iIterationCount == iMax
					[ ] Log.Pass("Number of iterations  is - {iIterationCount}")
				[ ] 
			[+] VerifyControlPanelCommand(string sCommand, list of string lstExpectResults)
				[ ] this.SetActive()
				[+] if(!this.togbtnExpander.IsChecked)
					[ ] this.togbtnExpander.Click()
				[ ] this.txtCommandLine.TypeKeys(sCommand)
				[ ] sleep(0.5)
				[ ] this.txtCommandLine.TypeKeys("<Enter>")
				[ ] 
				[ ] // list of string lstText = this.rtxtMessageView.GetText()
				[ ] integer i=1, j=1,iCount=0
				[ ] // handle hFile = FileOpen("C:\temp.txt",FM_WRITE)
				[+] // for(i=1;i<=ListCount(lstText);i++)
					[ ] // FileWriteLine(hFile,lstText[i])
				[ ] // FileClose(hFile)
				[ ] string sLine
				[ ] // hFile = FileOpen ("C:\temp.txt", FM_READ)
				[ ] list of string lstText  = this.getCPContent(true, true)
				[ ] // while (FileReadLine (hFile, sLine))
				[+] for each sLine in lstText
					[ ] sLine = trim(sLine)
					[+] if(j<=ListCount(lstExpectResults))
						[+] if(MatchStr(lstExpectResults[j],sLine))
							[ ] Log.Message("Find {lstExpectResults[j]}")
							[ ] j++
							[ ] iCount++
				[+] if(iCount>=ListCount(lstExpectResults))
					[ ] Log.Pass("Get all of the command results in Control panel successfully.")
				[+] else
					[ ] Log.Error("Didn't get all of the command results in Control panel.")
					[ ] 
				[ ] // FileClose(hFile)
			[+] ClearMessageinControlPanel()
				[ ] //Clear message in Control Panel
				[ ] this.SetActive()
				[ ] this.OpenControlPanel()
				[ ] this.grpControlPanel.btnClearMessages.Click()
				[ ] 
			[+] void CheckDataGridResults(list of string lsExpected)
				[ ] this.SetActive()
				[ ] Clipboard.SetText({})
				[ ] this.btnSelectAll.Click()
				[ ] this.TypeKeys("<Ctrl-c>")
				[ ] list of string lsResults = Clipboard.GetText()
				[ ] ListPrint(lsResults)
				[ ] Str.MatchList(lsResults,lsExpected)
			[ ] 
		[+] //--------------------------------------Print Methods-----------------//
			[+] void SavePrintFile(string sFileName)
				[+] //---------------------Log---------------------//
					[ ] // Info			:	Print the current table, chart, or PFS as electric XPS(*.xps) materia.
					[ ] //					sFileName is the full path of the file name
					[ ] // Author		:	Eric Lu
					[ ] // Date			:	December 07, 2011	
				[ ] 
				[ ] this.mnuFile.Click()
				[ ] sleep(1)
				[ ] this.miPrint.Click()
				[ ] sleep(1)
				[ ] dlgPrint.SetActive()
				[ ] sleep(1)
				[+] if(dlgPrint.lstv.Exists())
					[ ] dlgPrint.lstv.Select("*XPS*")
					[ ] dlgPrint.btnPrint.Click()
				[+] else
					[ ] dlgPrint.cboName.Click()
					[ ] dlgPrint.cboName.Select("*XPS*")
					[ ] dlgPrint.btnOK.Click()
				[ ] glWaitForMouseIdle(15)
				[ ] dlgSavePrintFile.SetActive()
				[ ] dlgSavePrintFile.cboSetName.SetText("{sFileName}")
				[ ] dlgSavePrintFile.btnSave.SetFocus()
				[ ] dlgSavePrintFile.btnSave.Click()
				[+] if(dlgConfirmSaveAs.Exists(5))
					[ ] dlgConfirmSaveAs.SetActive()
					[ ] dlgConfirmSaveAs.btnYes.Click()
		[+] //-----------------------Search Variables----------------------------//
			[+] void SearchVariablesOpen_Define()
				[ ] this.SetActive()
				[ ] this.SetTab("Define")
				[ ] this.grpReference.Exists(5)
				[ ] this.grpReference.btnBrowse.Click()
				[+] if( !wSearchVariables.Exists(20) )
					[ ] LogError("***The 'Search Variables' window does not exist.***")
				[ ] 
			[ ] 
			[ ] 
			[ ] 
			[+] void SearchVariablesOpen_Vary()
				[ ] this.SetActive()
				[ ] this.SetTab("Vary")			//Navigates to the "Vary" tab
				[ ] this.btnSearcher.Click()									//Opens the "Search Variables" window
				[ ] 
				[+] if wSearchVariables.Exists(20)==false				//verifies that the "Search Variables" window opens (Step 2a)
					[ ] LogError("***The 'Search Variables' window does not exist.***")
				[ ] 
				[ ] 
			[+] void SearchVariablesOpen_From()
				[ ] this.SetActive()
				[ ] this.SetTab("From")
				[ ] 
				[ ] this.imgSearch.Click()
				[ ] 
				[+] if wSearchVariables.Exists(20)==false				//verifies that the "Search Variables" window opens (Step 2a)
					[ ] LogError("***The 'Search Variables' window does not exist.***")
				[ ] 
				[ ] 
			[+] void SearchVariablesOpen_To()
				[ ] this.SetActive()
				[ ] this.SetTab("To")
				[ ] 
				[ ] this.Find("//WPFLabel[@caption='Variable:']/../../../WPFControl[@automationId='MMFindButton_2']/WPFContentControl/WPFButton").Click()
				[ ] 
				[+] if wSearchVariables.Exists(20)==false				//verifies that the "Search Variables" window opens (Step 2a)
					[ ] LogError("***The 'Search Variables' window does not exist.***")
				[ ] 
				[ ] 
			[+] void SearchVariablesEnter(string sInput, string sSelect)
				[ ] wSearchVariables.TxtSearchCriteria.SetText(sInput)										//enters a value, and searches for it. (Step 2b)
				[ ] wSearchVariables.SetActive()
				[ ] wSearchVariables.BtnSearch.Click()
				[+] 
					[+] do
						[ ] wSearchVariables.Lv.Select("{sSelect} *")
						[ ] string sResult=wSearchVariables.Lv.Find("//WPFListViewItem/WPFTextBlock[@caption='{sSelect}']").GetCaption()	
					[+] except
						[ ] Log.Error("ERROR: Unable to find {sSelect}")
						[ ] return
					[ ] 
				[+] if sResult != sSelect
					[ ] LogError("***The search term could not be found.***")
				[+] else
					[ ] Print("***Search term {sSelect} was found in 'Results' field.***")
				[ ] 
			[+] void SearchVariablesSelect_Define(string sSelect)
					[ ] exceptClear()
					[ ] wSearchVariables.Lv.Select("{sSelect} *")
					[ ] wSearchVariables.Button_1.Click()
				[ ] sleep(0.5)
				[ ] 
				[+] do
					[ ] APlus.grpReference.find("//WPFTextBlock[@caption='{sSelect}']")
					[ ] Log.Pass("{sSelect} Was Selected ")
				[+] except
					[ ] exceptClear()
					[ ] Log.Error("ERROR: {sSelect} was not placed in the variable box")
				[ ] 
				[ ] 
			[+] void SearchVariablesSelect_Vary_Alt(string sSelect)
				[ ] wSearchVariables.Lv.Find("//WPFListViewItem[@caption='{sSelect}*']/WPFTextBlock").DoubleClick()				//clicks on the specified value, presses select. (Step 2c)
				[ ] 
				[ ] 
				[ ] //wSearchVariables.Button_1.Click()															//closes "Search Variables" window
				[ ] 
				[ ] string sVariable=this.Find("//WPFLabel[@caption='Variable:']/../../../WPFControl[@automationId='MMComboEdit_3']/WPFContentControl").GetCaption()													//gets the value in the "Variable" field
				[+] if sVariable != sSelect																			//tests that the value matches what is expected
					[ ] LogError("***The search term could not be found.***")
				[+] else
					[ ] Print("***Search term {sSelect} was found in 'Variable' field.***")
				[ ]                
			[+] void SearchVariablesSelect_Vary(string sSelect)
				[ ] wSearchVariables.Lv.Find("//WPFListViewItem[@caption='{sSelect}*']/WPFTextBlock").DoubleClick()				//clicks on the specified value, presses select. (Step 2c)
				[ ] 
				[ ] 
				[ ] //wSearchVariables.Button_1.Click()															//closes "Search Variables" window
				[ ] 
				[ ] string sVariable=this.Find("//WPFGroupBox[@caption='Manipulated variable']//WPFControl[@automationId='PART_editControl'][4]/WPFTextBlock").GetCaption()													//gets the value in the "Variable" field
				[+] if sVariable != sSelect																			//tests that the value matches what is expected
					[ ] LogError("***The search term could not be found.***")
				[+] else
					[ ] Print("***Search term {sSelect} was found in 'Variable' field.***")
				[ ]                
			[+] void SearchVariablesSelect_From(string sSelect)
				[ ] wSearchVariables.Lv.Find("//WPFListViewItem[@caption='{sSelect}*']/WPFTextBlock").Click()												//clicks on the specified value, presses select. (Step 2c)
				[ ] 
				[ ] 
				[ ] wSearchVariables.Button_1.Click()															//closes "Search Variables" window
				[ ] 
				[ ] string sVariable=this.Find("//WPFLabel[@caption='Variable:']/../../../WPFControl[@automationId='MMComboEdit_8']/WPFContentControl").GetCaption()												//gets the value in the "Variable" field
				[+] if sVariable != sSelect																			//tests that the value matches what is expected
					[ ] LogError("***The search term could not be found.***")
				[+] else
					[ ] Print("***Search term {sSelect} was found in 'Variable' field.***")
				[ ] 
			[+] void SearchVariablesSelect_To(string sSelect)
				[ ] wSearchVariables.Lv.Find("//WPFListViewItem[@caption='{sSelect}*']/WPFTextBlock").Click()						//clicks on the specified value, presses select. (Step 2c)
				[ ] 
				[ ] 
				[ ] wSearchVariables.Button_1.Click()															//closes "Search Variables" window
				[ ] 
				[ ] string sVariable=this.Find("//WPFLabel[@caption='Variable:']/../../../WPFControl[@automationId='MMComboEdit_4']/WPFContentControl").GetCaption()												//gets the value in the "Variable" field
				[+] if sVariable != sSelect																			//tests that the value matches what is expected
					[ ] LogError("***The search term could not be found.***")
				[+] else
					[ ] Print("***Search term {sSelect} was found in 'Variable' field.***")
				[ ] 
				[ ] 
			[ ] 
		[+] //----------------------EO Configuration---------------------------//
			[+] EOInPutConfigureValuesForVariables(string sVariableName, string sValue, string sLowerBound, string sUpperBound,int iRow, string physicalType optional, string units optional)
				[ ] this.Find("//WPFDataGridRow[@className='GridControlDataGridRow'][{iRow}]").Find("//WPFDataGridCell[1]").Click()
				[ ] this.Find("//WPFButton[@automationId='PART_browse']").click()
				[ ] EOVariables.SetActive()
				[ ] EOVariables.ButtonQuery.Click()
				[ ] wEnterQuery.SetActive()
				[ ] sleep(10)
				[+] if(wEnterQuery.btnClear.IsEnabled)
					[ ] wEnterQuery.btnClear.Click()
				[ ] wEnterQuery.txtValue.TypeKeys("{sVariableName}")
				[ ] wEnterQuery.btnAddCondition.Click()
				[ ] wEnterQuery.btnOK.Click()
				[ ] EOVariables.SetActive()
				[ ] EOVariables.Find("//WPFContentControl[@caption='{sVariableName}']").Click()
				[ ] EOVariables.ButtonSelect.Click()
				[ ] this.Find("//WPFDataGridRow[@className='GridControlDataGridRow'][{iRow}]").Find("//WPFDataGridCell[@className='GridControlCell'][3]").TypeKeys(sValue)
				[ ] this.Find("//WPFDataGridRow[@className='GridControlDataGridRow'][{iRow}]").Find("//WPFDataGridCell[@className='GridControlCell'][6]").TypeKeys(sLowerBound)
				[ ] this.Find("//WPFDataGridRow[@className='GridControlDataGridRow'][{iRow}]").Find("//WPFDataGridCell[@className='GridControlCell'][7]").TypeKeys(sUpperBound)
				[ ] sleep(5)
				[+] if( physicalType != NULL)
					[ ] this.Find("//WPFDataGridRow[@className='GridControlDataGridRow'][{iRow}]").Find("//WPFDataGridCell[@className='GridControlCell'][4]").TypeKeys(physicalType+"<Tab>")
				[ ] sleep(5)
				[+] if( units != NULL)
					[ ] this.Find("//WPFDataGridRow[@className='GridControlDataGridRow'][{iRow}]").Find("//WPFDataGridCell[@className='GridControlCell'][5]").TypeKeys(units+"<Tab>")
			[+] AddVariableByBrowse(string sVariableName, int iRow optional)
				[ ] this.SetProperty("Height",450)
				[ ] this.SetProperty("Width",600)
				[ ] 
				[ ] this.SetActive()
				[+] if(iRow == null)
					[ ] this.btnBrowseVariables.Click()
					[ ] sleep(0.5)
				[+] else
					[ ] this.Find("//WPFButton[@automationId='PART_browse'][{iRow}]").click()
					[ ] sleep(0.5)
				[ ] EOVariables.SetActive()
				[ ] EOVariables.ButtonQuery.Click()
				[ ] sleep(0.5)
				[ ] wEnterQuery.SetActive()
				[+] if(wEnterQuery.btnClear.IsEnabled)
					[ ] wEnterQuery.btnClear.Click()
				[ ] sleep(0.5)
				[ ] wEnterQuery.txtValue.TypeKeys("{sVariableName}")
				[ ] wEnterQuery.btnAddCondition.Click()
				[ ] sleep(0.5)
				[ ] wEnterQuery.btnOK.Click()
				[ ] sleep(0.5)
				[ ] EOVariables.SetActive()
				[ ] EOVariables.Find("//WPFContentControl[@caption='{sVariableName}']").Click()
				[ ] sleep(0.5)
				[ ] EOVariables.ButtonSelect.Click()
				[ ] 
			[+] AddConnectForEOConfigration(int iRowToAdd, string sName, string sDestination,string sSource, boolean IsCheckedForPortConnection, boolean IsCheckedForEnabled)
				[ ] //window dataRecorder = AP.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]")
				[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFControl[@className='AesXamValueEdit'][1]").Click()
				[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFControl[@className='AesXamValueEdit'][1]").TypeKeys(sName)
				[ ] sleep(0.5)
				[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFControl[@className='AesXamValueEdit'][1]").TypeKeys("<Enter>")
				[ ] 
				[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFControl[@className='AesXamValueEdit'][2]").Click()
				[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFControl[@className='AesXamValueEdit'][2]").TypeKeys(sDestination)
				[ ] sleep(0.5)
				[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFControl[@className='AesXamValueEdit'][2]").TypeKeys("<Enter>")
				[ ] 
				[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFControl[@className='AesXamValueEdit'][3]").Click()
				[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFControl[@className='AesXamValueEdit'][3]").TypeKeys(sSource)
				[ ] sleep(0.5)
				[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFControl[@className='AesXamValueEdit'][3]").TypeKeys("<Enter>")
				[ ] 
				[+] if(IsCheckedForPortConnection)
					[+] if(!this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFCheckBox[1]").IsChecked)
						[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFCheckBox[1]").Click()
				[+] else
					[+] if(this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFCheckBox[1]").IsChecked)
						[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFCheckBox[1]").Click()
					[ ] 
				[+] if(IsCheckedForEnabled)
					[+] if(!this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFCheckBox[2]").IsChecked)
						[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFCheckBox[2]").Click()
				[+] else
					[+] if(this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFCheckBox[2]").IsChecked)
						[ ] this.Find("//WPFControl[@className='DataRecordPresenter'][{iRowToAdd}]").Find("//WPFCheckBox[2]").Click()
					[ ] 
			[+] QueryEOVars(list of string sVars)
				[ ] //Query specific EO Variables
				[ ] int i=1
				[ ] this.SetActive()
				[+] if !this.tabiDefault.Exists(3)
					[ ] sleep(2)
				[ ] this.tabiDefault.Click(2)
				[ ] sleep(0.5)
				[ ] this.miEnterQuery.Click()
				[ ] wEnterQuery.Exists(2)
				[ ] wEnterQuery.SetActive()
				[+] if wEnterQuery.btnClear.IsEnabled
					[ ] wEnterQuery.btnClear.Click()
				[+] for(i=1;i<listcount(sVars);i++)
					[ ] wEnterQuery.txtValue.SetText(sVars[i])
					[ ] wEnterQuery.rdMatchVariablesInObjectiveFunction.Select()
					[ ] wEnterQuery.rdChooseCondition.Select()
					[ ] wEnterQuery.btnAddCondition.Click()
					[ ] wEnterQuery.btnOr.Click()
				[ ] wEnterQuery.txtValue.SetText(sVars[i])
				[ ] wEnterQuery.rdMatchVariablesInObjectiveFunction.Select()
				[ ] wEnterQuery.rdChooseCondition.Select()
				[ ] wEnterQuery.btnAddCondition.Click()
				[ ] wEnterQuery.btnOK.Click()
				[ ] 
			[ ] 
		[-] //----------------------PFS object manipulation---------------------------//
			[+] void FindAndSelectObjectForInput(string strBlockName, string strStreamName optional)
				[ ] // FindAndSelectObjectForInput ( strBlockName, strStreamName optional )  - Invoke input page for Block[/Stream]
				[ ] //   Arguments
				[ ] //   1.  strBlockName , string, name of Block
				[ ] //   2.  strStreamName, string, name of Stream, optional argument.
				[ ] //   Usage:  AP.FindAndSelectObjectForInput('B1')
				[ ] 
				[+] if (this.tbMainFlowsheet.Exists())
					[ ] Log.Message("The tab page 'Main Flowsheet exist.'")
					[ ] this.tbMainFlowsheet.Click()
					[ ] sleep(3)
				[+] else
					[ ] Log.Message("Switch to Simulation page.'")
					[ ] this.hccSimulation.Click()
					[ ] glWaitForMouseIdle(15)
					[ ] this.tbMainFlowsheet.Click()
				[ ] RECT rect = this.areaForMainFlowsheet.GetRect()
				[ ] this.areaForMainFlowsheet.Click(1, (rect.xPos+rect.xSize)/20, (rect.yPos+rect.ySize)/20)
				[ ] this.areaForMainFlowsheet.TypeKeys("<Application>")
				[ ] // Invoke context menu to select "Find Object"
				[+] if(contextMenuBox.Exists(5))
					[ ] Log.Message("Invoke Find Object dialog.'")
					[ ] contextMenuBox.TypeKeys("<Up>")
					[ ] sleep(1)
					[ ] contextMenuBox.TypeKeys("<Enter>")
				[+] else
					[ ] Log.Error("The context menu not be shown.")
					[ ] 
				[+] if(wFindObject.Exists(3))
					[ ] wFindObject.SetActive()
					[+] if((strBlockName !="")&&(Lower(strBlockName)!="default"))
						[ ] Log.Message("Find Blocks {strBlockName}.'")
						[ ] wFindObject.lstBlocks.TypeKeys(strBlockName)
					[+] if(strStreamName != null)
						[ ] wFindObject.lstStreams.TypeKeys(strStreamName)
						[ ] Log.Message("Find Stream {strStreamName}.'")
					[ ] wFindObject.btnFind.Click()
					[ ] sleep(3)
					[ ] wFindObject.btnClose.Click()
					[ ] sleep(3)
				[+] else
					[ ] Log.Error("The Find Object dialog not be shown.")
					[ ] 
				[+] // Invoke context menu to select "Input"
					[ ] // this.tbMainFlowsheet.Click()
				[ ] this.areaForMainFlowsheet.TypeKeys("<Application>")
				[+] if(contextMenuBox2.Exists(5))
					[ ] Log.Message("Invoke Input page.'")
					[ ] 
					[ ] contextMenuBox2.TypeKeys("<Down>")
					[ ] sleep(1)
					[ ] contextMenuBox2.TypeKeys("<Enter>")
				[ ] // this.Find("//WPFContextMenu").TypeKeys("<Down><Enter>",0.5)
				[ ] 
			[+] void FindAndSelectObjectInCurrentFlowsheet(string strHierarchy, string strBlockName, string strStreamName optional)
				[ ] // FindAndSelectObject ( strBlockName, strStreamName optional )  - set focus on PFS for Block[/Stream]
				[ ] //   Arguments
				[ ] //   1.  strBlockName , string, name of Block
				[ ] //   2.  strStreamName, string, name of Stream, optional argument.
				[ ] //   Usage:  AP.FindAndSelectObject('B1')
				[ ] RECT rect = this.areaForMainFlowsheet.GetRect()
				[ ] this.areaForMainFlowsheet.Click(1, (rect.xPos+rect.xSize)/20, (rect.yPos+rect.ySize)/20)
				[ ] this.areaForMainFlowsheet.TypeKeys("<Application>")
				[ ] // Invoke context menu to select "Find Object"
				[ ] 
				[+] if(contextMenuBox2.Exists(5))
					[ ] Log.Message("Invoke Find Object dialog.'")
					[ ] contextMenuBox2.TypeKeys("f")
				[+] else
					[ ] Log.Error("The context menu not be shown.")
					[ ] 
				[+] if(wFindObject.Exists(3))
					[+] if((strHierarchy =="")||("default"==Lower(strHierarchy)))
						[+] if((strBlockName =="")||(Lower(strBlockName)=="default"))
							[+] if(strStreamName != null)
								[ ] wFindObject.lstStreams.TypeKeys(strStreamName)
								[ ] Log.Message("Find Stream {strStreamName}.'")
								[ ] wFindObject.btnFind.Click()
								[ ] sleep(3)
								[ ] wFindObject.btnClose.Click()
								[ ] sleep(3)
						[+] else
							[ ] Log.Message("Find Block {strBlockName}.'")
							[ ] wFindObject.SetActive()
							[ ] wFindObject.lstBlocks.TypeKeys(strBlockName)
							[+] if(strStreamName != null)
								[ ] Log.Message("Find Stream {strStreamName}.'")
								[ ] wFindObject.lstStreams.TypeKeys(strStreamName)
							[ ] wFindObject.btnFind.Click()
							[ ] sleep(3)
							[ ] wFindObject.btnClose.Click()
							[ ] sleep(3)
							[ ] 
					[+] else
						[ ] Log.Message("Find Hierachy {strHierarchy}")
						[ ] wFindObject.trvHierarchy.Find("//WPFTreeViewItem[@caption='{strHierarchy}']").Click()
						[ ] Log.Message("Find Blocks {strBlockName}.'")
						[ ] wFindObject.SetActive()
						[ ] wFindObject.lstBlocks.TypeKeys(strBlockName)
						[+] if(strStreamName != null)
							[ ] wFindObject.lstStreams.TypeKeys(strStreamName)
							[ ] Log.Message("Find Stream {strStreamName}.'")
						[ ] wFindObject.btnFind.Click()
						[ ] sleep(3)
						[ ] wFindObject.btnClose.Click()
						[ ] sleep(3)
						[ ] 
				[+] else
					[ ] Log.Error("The Find Object dialog not be shown.")
					[ ] 
				[ ] sleep(5)
				[ ] // APlus.mainFlowSheetArea.SetFocus()
			[+] void FindAndSelectObject(string strHierarchy, string strBlockName, string strStreamName optional)
				[ ] // FindAndSelectObject ( strBlockName, strStreamName optional )  - set focus on PFS for Block[/Stream]
				[ ] //   Arguments
				[ ] //   1.  strBlockName , string, name of Block
				[ ] //   2.  strStreamName, string, name of Stream, optional argument.
				[ ] //   Usage:  AP.FindAndSelectObject('B1')
				[ ] 
				[+] if (this.tbMainFlowsheet.Exists())
					[ ] Log.Message("The tab page 'Main Flowsheet exist.'")
					[ ] this.tbMainFlowsheet.Click()
					[ ] sleep(3)
				[+] else
					[ ] Log.Message("Switch to Simulation page.'")
					[ ] this.hccSimulation.Click()
					[ ] glWaitForMouseIdle(15)
					[ ] this.tbMainFlowsheet.Click()
				[ ] RECT rect = this.areaForMainFlowsheet.GetRect()
				[ ] this.areaForMainFlowsheet.Click(1, (rect.xPos+rect.xSize)/20, (rect.yPos+rect.ySize)/20)
				[ ] this.areaForMainFlowsheet.TypeKeys("<Application>")
				[ ] // Invoke context menu to select "Find Object"
				[+] if(contextMenuBox.Exists(5))
					[ ] Log.Message("Invoke Find Object dialog.'")
					[ ] APlus.find("//WPFMenuItem[@caption='*Find Object*']").Click()
				[+] else
					[ ] Log.Error("The context menu not be shown.")
					[ ] 
				[+] if(wFindObject.Exists(3))
					[+] if((strHierarchy =="")||("default"==Lower(strHierarchy)))
						[+] if((strBlockName =="")||(Lower(strBlockName)=="default"))
							[+] if(strStreamName != null)
								[ ] wFindObject.lstStreams.TypeKeys(strStreamName)
								[ ] Log.Message("Find Stream {strStreamName}.'")
								[ ] wFindObject.btnFind.Click()
								[ ] sleep(3)
								[ ] wFindObject.btnClose.Click()
								[ ] sleep(3)
						[+] else
							[ ] Log.Message("Find Block {strBlockName}.'")
							[ ] wFindObject.SetActive()
							[ ] wFindObject.lstBlocks.TypeKeys(strBlockName)
							[+] if(strStreamName != null)
								[ ] Log.Message("Find Stream {strStreamName}.'")
								[ ] wFindObject.lstStreams.TypeKeys(strStreamName)
							[ ] wFindObject.btnFind.Click()
							[ ] sleep(3)
							[ ] wFindObject.btnClose.Click()
							[ ] sleep(3)
							[ ] 
					[+] else
						[ ] Log.Message("Find Hierachy {strHierarchy}")
						[ ] wFindObject.trvHierarchy.Find("//WPFTreeViewItem[@caption='{strHierarchy}']").Click()
						[ ] Log.Message("Find Blocks {strBlockName}.'")
						[ ] wFindObject.SetActive()
						[ ] wFindObject.lstBlocks.TypeKeys(strBlockName)
						[+] if(strStreamName != null)
							[ ] wFindObject.lstStreams.TypeKeys(strStreamName)
							[ ] Log.Message("Find Stream {strStreamName}.'")
						[ ] wFindObject.btnFind.Click()
						[ ] sleep(3)
						[ ] wFindObject.btnClose.Click()
						[ ] sleep(3)
						[ ] 
				[+] else
					[ ] Log.Error("The Find Object dialog not be shown.")
					[ ] 
			[ ] 
			[-] void FindAndSelectObject1(string strHierarchy, string strBlockName, string strStreamName optional)
				[ ] // FindAndSelectObject ( strBlockName, strStreamName optional )  - set focus on PFS for Block[/Stream]
				[ ] //   Arguments
				[ ] //   1.  strBlockName , string, name of Block
				[ ] //   2.  strStreamName, string, name of Stream, optional argument.
				[ ] //   Usage:  AP.FindAndSelectObject('B1')
				[ ] 
				[+] if (this.tbMainFlowsheet.Exists())
					[ ] Log.Message("The tab page 'Main Flowsheet exist.'")
					[ ] this.tbMainFlowsheet.Click()
					[ ] sleep(3)
				[+] else
					[ ] Log.Message("Switch to Simulation page.'")
					[ ] this.hccSimulation.Click()
					[ ] glWaitForMouseIdle(15)
					[ ] this.tbMainFlowsheet.Click()
				[ ] RECT rect = this.areaForMainFlowsheet.GetRect()
				[ ] this.areaForMainFlowsheet.Click(1, (rect.xPos+rect.xSize)/20, (rect.yPos+rect.ySize)/20)
				[ ] this.areaForMainFlowsheet.TypeKeys("<Application>")
				[ ] // Invoke context menu to select "Find Object"
				[-] if(contextMenuBox.Exists(5))
					[ ] Log.Message("Invoke Find Object dialog.'")
					[ ] APlus.find("//WPFMenuItem[@caption='*Find Object*']").Click()
				[-] else
					[ ] Log.Error("The context menu not be shown.")
					[ ] 
				[-] if(wFindObject.Exists(3))
					[+] if((strHierarchy =="")||("default"==Lower(strHierarchy)))
						[+] if((strBlockName =="")||(Lower(strBlockName)=="default"))
							[+] if(strStreamName != null)
								[ ] wFindObject.lstStreams.TypeKeys(strStreamName)
								[ ] Log.Message("Find Stream {strStreamName}.'")
								[ ] wFindObject.btnFind.Click()
								[ ] sleep(3)
								[ ] wFindObject.btnClose.Click()
								[ ] sleep(3)
						[+] else
							[ ] Log.Message("Find Block {strBlockName}.'")
							[ ] wFindObject.SetActive()
							[ ] wFindObject.tbSearch.SetText(strBlockName)
							[ ] // wFindObject.lstBlocks.TypeKeys(strBlockName)
							[+] if(strStreamName != null)
								[ ] Log.Message("Find Stream {strStreamName}.'")
								[ ] wFindObject.lstStreams.TypeKeys(strStreamName)
							[ ] wFindObject.Find("//WPFTextBlock[@caption='*{strBlockName}']").Click()
							[ ] 
					[+] else
						[ ] Log.Message("Find Hierachy {strHierarchy}")
						[ ] wFindObject.trvHierarchy.Find("//WPFTreeViewItem[@caption='{strHierarchy}']").Click()
						[ ] Log.Message("Find Blocks {strBlockName}.'")
						[ ] wFindObject.SetActive()
						[ ] wFindObject.lstBlocks.TypeKeys(strBlockName)
						[+] if(strStreamName != null)
							[ ] wFindObject.lstStreams.TypeKeys(strStreamName)
							[ ] Log.Message("Find Stream {strStreamName}.'")
						[ ] wFindObject.btnFind.Click()
						[ ] sleep(3)
						[ ] wFindObject.btnClose.Click()
						[ ] sleep(3)
						[ ] 
				[-] else
					[ ] Log.Error("The Find Object dialog not be shown.")
					[ ] 
			[ ] 
			[ ] 
			[ ] 
			[-] void FindObject(string sBlock, string sStream optional)
				[ ] this.SetActive()
				[ ] this.tbView.Select()
				[ ] this.btnFindObject.Click()
				[ ] wFindObject.Exists(3)
				[-] wFindObject.SetActive()
					[-] if((sBlock !="")&&(Lower(sBlock)!="default"))
						[ ] Log.Message("Find Blocks {sBlock}.'")
						[ ] wFindObject.tbSearch.SetText(sBlock)
						[ ] wFindObject.Find("//WPFTextBlock[@caption='{sBlock}']").Click()
						[ ] 
					[+] if(sStream != null)
						[ ] 
						[ ] wFindObject.tbSearch.SetText(sBlock)
						[ ] wFindObject.Find("//WPFTextBlock[@caption='{sStream}']").Click()
						[ ] 
						[ ] Log.Message("Find Stream {sStream}.'")
				[ ] 
				[ ] 
			[-] void ExpandObjectInPFS(string strHierarchy, string strBlockName, string strStreamName optional)
					[ ] //Find the Object first
					[+] if(strStreamName!=null)
						[ ] FindAndSelectObjectInCurrentFlowsheet(strHierarchy,strBlockName,strStreamName)
					[+] else
						[ ] FindAndSelectObjectInCurrentFlowsheet(strHierarchy,strBlockName)
					[ ] //Expand Block
					[ ] this.areaForMainFlowsheet.TypeKeys("<Application>")
					[+] if(contextMenuBox2.Exists(5))
						[ ] contextMenuBox2.TypeKeys("<Down>")
						[ ] sleep(1)
						[ ] contextMenuBox2.TypeKeys("<Enter>")
					[+] else
						[ ] Log.Error("The context menu didn't be shown.")
					[ ] sleep(2)
		[+] //----------------------Others---------------------------//
			[+] void PureComponentRunAnalysis(string strPureComponentName,string strProperty,string strPhase,string strComponentName,string strScreenshotName)
				[ ] this.SetTab("{strPureComponentName}*Input")
				[ ] glWaitForMouseIdle(5)
				[ ] //Select property in ComboBox
				[ ] this.SelectItemInComboBox("automationId","PART_editControl","{strProperty}",2)
				[+] if(("v" == lower(strPhase)) || ("vapour" == lower(strPhase)) )
					[+] if(!this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][1]").IsChecked)
						[ ] this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][1]").Click()
					[ ] //Uncheck Liquid
					[+] if(this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][2]").IsChecked)
						[ ] this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][2]").Click()
					[ ] //Uncheck Solid
					[+] if(this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][3]").IsChecked)
						[ ] this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][3]").Click()
				[+] if(("l" == lower(strPhase)) || ("liquid" == lower(strPhase)) )
					[ ] //Uncheck Vapour
					[+] if(this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][1]").IsChecked)
						[ ] this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][1]").Click()
					[ ] //Check Liquid
					[+] if(!this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][2]").IsChecked)
						[ ] this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][2]").Click()
					[ ] //Uncheck Solid
					[+] if(this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][3]").IsChecked)
						[ ] this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][3]").Click()
				[+] if(("s" == lower(strPhase)) || ("solid" == lower(strPhase)) )
					[ ] //Uncheck Vapour
					[+] if(this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][1]").IsChecked)
						[ ] this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][1]").Click()
					[ ] //Check Liquid
					[+] if(this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][2]").IsChecked)
						[ ] this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][2]").Click()
					[ ] //Check Solid
					[+] if(!this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][3]").IsChecked)
						[ ] this.Find("//WPFCheckBox[@automationId='PART_CheckBox'][3]").Click()
				[+] if(this.btnMoveAllLeft.IsEnabled)
					[ ] this.btnMoveAllLeft.Click()
				[ ] this.Find("//WPFListBoxItem[@caption='{strComponentName}']").Click()
				[ ] this.btnMoveRight.Click()
				[ ] this.btnRunAnalysis.Click()
				[ ] sleep(2)
				[ ] glWaitForMouseIdle(20)
				[ ] Desktop.CaptureBitmap(strScreenshotName)
				[ ] Log.Warning("Please compare the screenshot {strScreenshotName} with baseline.")
			[+] void BinarayInputRunAnalysis(string strAnalysisType,string strCompositionBasis,list of string lstTemOrPre,string strNoOfPoints,string strValidPhase,string strScreenshotName, string strBaseMethod optional)
				[ ] // this.trvPartTree.Expand("/Analysis")
				[ ] // this.trvPartTree.Click("/Analysis/BINRY-1")
				[ ] // sleep(1)
				[ ] // this.SetTab("Binary Analysis")
				[ ] sleep(1)
				[ ] 
				[ ] // Select Analysis type
				[ ] this.SelectItemInComboBox("automationId","PART_editControl","{strAnalysisType}",1)
				[ ] 
				[ ] // Select Composition Basis
				[ ] this.SelectItemInComboBox("automationId","PART_editControl","{strCompositionBasis}",4)
				[ ] 
				[ ] // set temperature or pressure value
				[+] if(Lower(strAnalysisType) != "gibbs energy of mixing")
					[ ] this.Find("//WPFControl[@automationId='PART_DataGrid'][2]//WPFTextBlock[1]").Click()
					[ ] sleep(0.5)
					[ ] this.Find("//WPFControl[@automationId='PART_DataGrid'][2]//WPFTextBlock[1]").typekeys("{lstTemOrPre[1]}")
					[ ] sleep(0.5)
					[ ] this.TypeKeys("<Enter>")
					[ ] int i
					[+] if(ListCount(lstTemOrPre)>=2)
						[+] for(i =2;i<= ListCount(lstTemOrPre);i++)
							[ ] this.TypeKeys(lstTemOrPre[i])
							[ ] sleep(0.5)
							[ ] this.TypeKeys("<Enter>")
				[+] else
					[ ] this.Find("//WPFControl[@automationId='PART_editControl'][11]").Click()
					[ ] sleep(0.5)
					[ ] this.TypeKeys("{lstTemOrPre[1]}")
					[ ] this.Find("//WPFControl[@automationId='PART_DataGrid'][2]//WPFTextBlock[1]").Click()
					[ ] sleep(0.5)
					[ ] this.Find("//WPFControl[@automationId='PART_DataGrid'][2]//WPFTextBlock[1]").typekeys("{lstTemOrPre[2]}")
					[ ] sleep(0.5)
					[ ] this.TypeKeys("<Enter>")
					[ ] 
					[+] if(ListCount(lstTemOrPre)>=3)
						[+] for(i =3;i<= ListCount(lstTemOrPre);i++)
							[ ] this.TypeKeys(lstTemOrPre[i])
							[ ] sleep(0.5)
							[ ] this.TypeKeys("<Enter>")
					[ ] 
					[ ] //set No. of Points
					[ ] this.Find("//WPFControl[@automationId='PART_editControl'][8]").DoubleClick()
					[ ] sleep(0.5)
					[ ] sleep(0.5)
					[ ] this.TypeKeys("<Backspace 4><Delete 3>")
					[ ] sleep(0.5)
					[ ] sleep(0.5)
					[ ] this.TypeKeys("{strNoOfPoints}")
					[ ] 
					[ ] this.btnRunAnalysis.Click()
					[ ] sleep(2)
					[ ] glWaitForMouseIdle(20)
					[ ] 
					[ ] Desktop.CaptureBitmap(strScreenshotName)
					[ ] Log.Warning("Please compare the screenshot {strScreenshotName} with baseline.")
					[ ] return
					[ ] 
				[ ] //set No. of Points
				[ ] // APlus.grpCompositions.tbNoOfPoints.inputText("{strNoOfPoints}")
				[ ] this.Find("//WPFControl[@automationId='PART_editControl'][8]").DoubleClick()
				[ ] sleep(0.5)
				[ ] sleep(0.5)
				[ ] this.TypeKeys("<Backspace 4><Delete 3>")
				[ ] sleep(0.5)
				[ ] sleep(0.5)
				[ ] this.TypeKeys("{strNoOfPoints}")
				[ ] 
				[ ] //Select valid phase
				[+] if(strValidPhase!="" || lower(strValidPhase) != "default")
					[ ] this.SelectItemInComboBox("automationId","PART_editControl","{strValidPhase}",10)
				[ ] 
				[ ] this.btnRunAnalysis.Click()
				[ ] sleep(2)
				[ ] glWaitForMouseIdle(20)
				[ ] 
				[ ] Desktop.CaptureBitmap(strScreenshotName)
				[ ] Log.Warning("Please compare the screenshot {strScreenshotName} with baseline.")
				[ ] 
				[ ] this.SetActive()
				[ ] this.SetTab("Home")
				[+] if(this.btnBinary.Exists())
					[ ] this.btnBinary.Click()
					[ ] sleep(3)
					[ ] glWaitForMouseIdle(10)
				[ ] 
				[+] // do
					[ ] // this.SetTab("BINRY*Input")
				[+] // except
					[ ] // Log.Error("The Binary Input didn't appear.")
				[ ] 
			[ ] 
			[+] void CloseOtherTabs()
				[ ] string sPage= ""
				[ ] string sMode=""
				[ ] list of string lsTemp
				[ ] list of string lsActualPages
				[ ] 
				[ ] this.SetActive()
				[ ] this.mnuFilesMenu.Click()
				[ ] list of STRING lsPages = APlus.mnuFilesMenu.mniFilesMenuItem.GetContents()
				[+] for each sPage in lsPages
					[ ] lsTemp= Str.Split(sPage,"]")
					[ ] ListAppend(lsActualPages,lsTemp[2])
				[ ] sMode = this.GetMode()
				[+] switch(sMode)
					[+] case "Simulation"
						[ ] //Verify StartPage and Flowsheet tab existed.
						[ ] Verify(APlus.tbMainFlowsheet.Exists(2), True)
						[ ] Verify(APlus.tbStartPage.Exists(2), True)
						[ ] 
					[+] case "Properties"
						[ ] //Verify StartPage  existed.
						[ ] Verify(APlus.tbStartPage.Exists(2), True)
						[ ] 
						[ ] 
					[+] default
						[ ] 
				[ ] 
				[ ] Print(lsPages)
				[ ] Print(lsActualPages)
				[ ] 
				[ ] 
		[+] //---------------------------Model Libraries------------------------------//
			[+] void CreateModelLbrary(string sDisplayName, string sFilePath)
				[ ] this.SetActive()
				[ ] this.SetMode("Simulation")
				[ ] sleep(5)
				[ ] 
				[ ] this.tbCustomize.Click()
				[ ] this.grpManageLibraries.btnModelLibraries.Click()
				[ ] sleep(0.5)
				[ ] 
				[ ] wManageLibraries.SetActive()
				[ ] wManageLibraries.btnNew.Click()
				[ ] wNewUserModelLibrary.SetActive()
				[ ] wNewUserModelLibrary.txtDisplayName.SetText("{sDisplayName}")
				[ ] wNewUserModelLibrary.txtFilePath.SetText("{sFilePath}")
				[ ] wNewUserModelLibrary.btnCreate.Click()
			[+] void CreateNewCategory(string sCategory)
				[ ] wModelLibraryEditor.SetActive()
				[ ] wModelLibraryEditor.wccCategoryPanel.Click(2)
				[ ] sleep(1)
				[ ] wModelLibraryEditor.miCreateNewCategory.Select()
				[ ] 
				[ ] wNewUserCategory.SetActive()
				[ ] wNewUserCategory.txtNewName.SetText("{sCategory}")
				[ ] wNewUserCategory.btnOK.Click()
				[ ] 
			[+] void PlaceModelToFlowsheet(string sCategory,string sBlock)
				[ ] //First select Category,then put the Blocks to PFS
				[ ] //APlus.PlaceModelToFlowsheet("User Model","User2")
				[ ] this.SetActive()
				[+] if !this.grpModelPalette.Exists()
					[ ] this.TypeKeys("<F10>")
				[ ] 
				[ ] this.grpModelPalette.Find( "//WPFTabItem[@caption='{sCategory}']").click()
				[ ] sleep(0.5)
				[ ] this.grpModelPalette.Find("//WPFButton[@caption='{sBlock}']").click()
				[ ] this.areaForMainFlowsheet.Click(1,400,400)
				[ ] this.grpModelPalette.grpLibraryControl.btnCancelInsertMode.Click()
		[+] //--------------------------Change AspenPlus Working folder-----------//
			[+] void ChangeWokingFolder(string sFloder)
				[ ] this.SetActive()
				[ ] //File -> Options -> Simulation
				[ ] this.TypeKeys("<Alt>F")
				[ ] AspenPlusClassicWin.DialogBox("#1").SetActive()
				[ ] Agent.SetOption (OPT_VERIFY_EXPOSED, false)
				[ ] AspenPlusClassicWin.  DialogBox("#1").Click(1,390,540)
				[ ] Agent.SetOption (OPT_VERIFY_EXPOSED, TRUE)
				[ ] wSimulationRunOptions.SetActive()
				[ ] wSimulationRunOptions.Files.Select()
				[ ] // wSimulationRunOptions.grpLocations.txtWorkFolder.SetText("{sFloder}")
				[ ] wSimulationRunOptions.grpLocations.txtWorkFolder.TypeKeys("<Shift-End><Backspace>")
				[ ] wSimulationRunOptions.grpLocations.txtWorkFolder.TypeKeys("{sFloder}<Enter>")
				[ ] 
				[ ] // wSimulationRunOptions.TypeKeys("<Enter>")
				[ ] sleep(2)
				[ ] // // if wSimulationRunOptions.Btn_Apply.IsEnabled
				[ ] // wSimulationRunOptions.Btn_Apply.Click()
				[ ] wSimulationRunOptions.SetActive()
				[ ] wSimulationRunOptions.Btn_OK.DoubleClick()
				[ ] 
		[+] //------------------------------NIST-TDE ------------------------------------//
			[+] void Retrieve_BinaryMixture(string sComponent1, string sComponent2)
				[ ] this.btnNIST.Click()
				[ ] wNistThermoDataEngine.SetActive()
				[ ] wNistThermoDataEngine.rdlBinaryMixture.Select()
				[ ] wNistThermoDataEngine.cbo1stComponentSToEvaluate.Select(sComponent1)
				[ ] wNistThermoDataEngine.cbo2ndComponentSToEvaluate.Select(sComponent2)
				[ ] wNistThermoDataEngine.btnRetrieveData.Click()
				[ ] sleep(1)
				[+] while !wNistThermoDataEngine.btnRetrieveData.IsEnabled
					[ ] sleep(1)
				[ ] Print("Retrieve data successfully")
				[ ] wNistThermoDataEngine.Close()
			[+] void SaveBinaryDataset(string sDataset,BOOLEAN bOverWritten optional)
				[ ] this.SetTab("TDE Binary Results")
				[ ] this.tbExperimental.Click()
				[ ] this.find("//WPFTreeViewItem[@caption='{sDataset}']").setfocus()
				[ ] this.find("//WPFTreeViewItem[@caption='{sDataset}']").click()
				[ ] sleep(1)
				[ ] this.btnSaveBinaryData.Click()
				[+] if wBinaryExperimentalDataToBeSaved.Exists(3)
					[ ] wBinaryExperimentalDataToBeSaved.SetActive()
					[ ] wBinaryExperimentalDataToBeSaved.btnOK.Click()
				[+] if bOverWritten!= null
					[+] if bOverWritten
						[ ] dlgAspenPlus.SetActive()
						[ ] dlgAspenPlus.BtnYes.Click()
					[+] else
						[ ] dlgAspenPlus.SetActive()
						[ ] dlgAspenPlus.BtnNo.Click()
				[+] if wNistTdeConfirmSaving.Exists(3)
					[ ] wNistTdeConfirmSaving.SetActive()
					[ ] wNistTdeConfirmSaving.BtnOK.Click()
			[+] void RunConsistencyTest()
				[ ] this.SetActive()
				[ ] this.tbConsistencyTest.Click()
				[ ] this.btnRunConsistencyTest.Click()
				[ ] wNISTTDEConsistencyTest.Exists(60)
				[ ] wNISTTDEConsistencyTest.SetActive()
				[ ] wNISTTDEConsistencyTest.btnOK.Click()
				[ ] sleep(8)
				[ ] wNISTTDEConsistencyTest.Exists(60)
				[ ] wNISTTDEConsistencyTest.SetActive()
				[ ] wNISTTDEConsistencyTest.btnOK.Click()
				[ ] sleep(20)
		[ ] 
		[ ] 
	[ ] 
	[ ] 
[-] appstate CleanState() basedon none
	[ ] Case.RunBy24h(gbRunBy24hRunning)
	[ ] checkForProgramError()
	[ ] KillPrograms()
	[ ] Sys_Execute("powershell.exe set-executionpolicy unrestricted -force")
[ ] 
[+] appstate BaseState() basedon DefaultBaseState
	[ ] //Agent.SetOption (OPT_HANG_APP_TIME_OUT, 10001) 
	[+] // spawn
		[+] // if(Basic.CheckTime(1800))
			[ ] // 
			[ ] // Basic.CleanUp()
			[ ] // exit
		[ ] // 
	[+] // spawn
		[+] // while(!Case.bRunComplete)
			[ ] // //print(bRunComplete)
			[+] // if(!Basic.CheckTime(600,60))
				[ ] // continue
			[+] // else
				[ ] // //Basic.ResartAgent()
				[+] // // if(dlgCrash.btnCloseProgram.Exists())
					[ ] // // dlgCrash.SetActive()
					[ ] // // dlgCrash.btnCloseProgram.Click()
					[ ] // // Log.Fail("Our application has crashed!")
				[ ] // Basic.CleanUp()
				[ ] // Log.Fail("Exist this test case by run time out!")
				[ ] // exit
		[ ] // 
	[+] // if(gbRunByServer)
		[ ] // 
	[+] // else
		[+] // if(Case.iRunCount>giMaxRunLoop)
			[ ] // exit
		[+] // else
			[ ] // ++Case.iRunCount
	[ ] Case.RunBy24h(gbRunBy24hRunning)
	[ ] 
	[ ] Agent.SetOption (OPT_WINDOW_TIMEOUT, 60)
	[ ] Agent.SetOption (OPT_WINDOW_RETRY, 5) //1
	[ ] Agent.SetOption(OPT_HANG_APP_TIME_OUT,10000)
	[ ] CleanUp()
	[ ] 
[ ] 
[ ] 
[ ] 
[ ] 
