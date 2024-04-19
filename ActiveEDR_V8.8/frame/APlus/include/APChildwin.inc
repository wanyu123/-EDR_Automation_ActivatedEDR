	[ ] // use "../frame/APMainFrame.inc"
	[ ] use "APMainWin.inc"
	[ ] 
	[ ] 
	[+] //Startup / Initialization Windows
		[+] window DialogBox wAspenTechnologyProductRegistration
			[ ] locator "/DialogBox[@caption='Aspen Technology Product Registration']"
			[+] PushButton btnCancel
				[ ] locator "//PushButton[@caption='Cancel']"
			[+] PushButton btnDoNotRegister
				[ ] locator "//PushButton[@caption='Do Not Register']"
			[ ] 
		[+] window FormsWindow wAspenPropertiesDatabaseConfiguration
			[ ] locator "/FormsWindow[@caption='Aspen Properties Database Configuration']"
			[ ] 
			[ ] // The working directory of the application when it is invoked
			[ ] const sDir = "%ProgramFiles%\AspenTech\AprSystem V8.8\PropertiesDatabase\Bin"
			[ ] 
			[ ] // The command line used to invoke the application
			[ ] const sCmdLine = "%ProgramFiles%\AspenTech\AprSystem V8.8\PropertiesDatabase\Bin\dbRestore.exe"
			[ ] 
			[+] TextField txtStatus
				[ ] locator "//TextField[@automationId='textBox1']"
		[+] window DialogBox wAspenTechnologyLicenseManagerReminder
			[ ] locator "/DialogBox[@caption='Aspen Technology License Manager - Reminder']"
			[+] PushButton btnSnooze
				[ ] locator "//PushButton[@caption='Snooze']"
	[ ] 
	[+] //Error Windows
		[+] window DialogBox wRuntimeError
			[ ] locator "//DialogBox[@caption='Microsoft Visual C++ Runtime Library']"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@caption='OK']"
			[+] StaticText txtWarning
				[ ] locator "//StaticText[2]"
		[+] window DialogBox wAspenPlusError
			[ ] locator "//DialogBox[@caption='Aspen Plus']"
			[+] StaticText txtMessage
				[ ] locator "//StaticText[2]"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@caption='OK']"
			[ ] 
		[+] window DialogBox wAspenPropertiesError
			[ ] locator "//DialogBox[@caption='Aspen Properties']"
			[+] StaticText txtMessage
				[ ] locator "//StaticText[2]"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@caption='OK']"
			[ ] 
		[+] window MainWin wAspenPlusErrorMainWin
			[ ] locator "/MainWin[@caption='Aspen Plus']"
			[+] StaticText txtMessage
				[ ] locator "//StaticText[2]"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@caption='OK']"
			[ ] 
		[+] window MainWin wAspenPropertiesErrorMainWin
			[ ] locator "/MainWin[@caption='Aspen Properties']"
			[+] StaticText txtMessage
				[ ] locator "//StaticText[2]"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@caption='OK']"
			[ ] 
		[+] window MainWin wAspenPlusHasStoppedWorking
			[ ] locator "/DialogBox[@caption='AspenPlus']"
			[+] PushButton btnCloseProgram
				[ ] locator "//PushButton[@caption='Close program']"
		[+] window MainWin wAspenPropertiesHasStoppedWorking
			[ ] locator "/DialogBox[@caption='AspenProperties']"
			[+] PushButton btnCloseProgram
				[ ] locator "//PushButton[@caption='Close program']"
		[+] window FormsWindow wMicrosoftNETFramework
			[ ] locator "/FormsWindow[@caption='Microsoft .NET Framework']"
			[+] PushButton btnContinue
				[ ] locator "//PushButton[@caption='Continue']"
		[ ] 
	[ ] 
	[+] //Classic Agent
		[+] window glwcMessageBox	AspenPlusClassicWin
			[+] multitag"*Aspen Plus*aspenONE"
				[ ] "*Aspen Plus {sVersion}*"
				[ ] "* - Aspen Properties V* - aspenONE"
			[+] glwcDlgOpenFile	dlgOpenFile
				[ ] tag"Open"
			[+] glwcDlgSaveFile   dlgSaveAsFile
				[ ] tag "Save As"
			[+] glwcDlgSaveFile   dlgExport
				[ ] tag "*Export*|*Save As*"
			[+] glwcMessageBox dlgPrintPreview
				[ ] tag "Print Preview"
				[+] PushButton btnPrint
					[+] multitag "Print"
						[ ] "$20001"
				[+] void SavePrintFile(string sFileName)
					[+] //---------------------Log---------------------//
						[ ] // Info			:	Print the current table, chart, or PFS as electric XPS(*.xps) materia.
						[ ] //					sFileName is the full path of the file name
						[ ] // Author		:	Eric Lu
						[ ] // Date			:	December 07, 2011	
					[ ] 
					[ ] this.btnPrint.Click()
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
					[ ] 
			[ ] 
			[ ] 
	[ ] 
	[+] //Reinitialize
		[+] window MainWin wReinitialize
			[ ] locator "/WPFWindow[@caption='Reinitialize']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='Button_1']"
				[ ] 
	[ ] 
	[+] //Other Aspen Plus main window
		[+] window wcAspenPlus APR
			[ ] locator "/WPFWindow[@caption='*Aspen Properties*- aspenONE']"
			[ ] 
			[ ] // The working directory of the application when it is invoked
			[ ] const sDir = "%USERPROFILE%\Desktop"
			[ ] 
			[ ] // The command line used to invoke the application
			[ ] const sCmdLine = "{sProgramFilePath}\AspenTech\Aspen Properties {sVersion}\GUI\Xeq\AspenProperties.exe"
			[+] WPFToggleButton mnuFile
				[ ] locator "//*[@className='ApplicationMenuPresenter']"
			[+] WPFMenuItem       miNew
				[ ] locator "//WPFMenuItem[@caption='New']"
			[ ] 
			[ ] 
			[+] DialogBox ImportIKCAPEFile
				[ ] locator "Import IK-CAPE file"
				[+] TextField FileName
					[ ] locator "File name:"
	[ ] 
	[+] //Open File related windows
		[ ] 
		[+] window WPFWindow wUpwardCompatibility
			[ ] locator "/WPFWindow[@caption='Upward Compatibility']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
			[+] WPFRadioButton RdlKeepExistingDatabanks
				[ ] locator "//WPFRadioButton[@automationId='radioMantain' or @automationId='radioMaitain']"
			[+] WPFRadioButton RdlUpgradeToNewDatabanks
				[ ] locator "//WPFRadioButton[@automationId='radioFollow']"
			[ ] 
		[ ] 
		[+] window WPFWindow wUpgradeDatabanks
			[ ] locator "/WPFWindow[@caption='Upgrade databanks']"
			[+] WPFCheckBox chkUpgrade
				[ ] locator "//WPFCheckBox[@automationId='chkUpgrade']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
		[ ] 
		[+] window WPFWindow wDatabankUpgradeWarning
			[ ] locator "/WPFWindow[@caption='Databank upgrade warning']"
			[+] WPFTextBlock TextBlock
				[ ] locator "//WPFTextBlock[@caption='We did not upgrade your simulation to use the new PURE26 databank because the version of the backup file and databanks selected prevented us from doing so automatically.  To use this new databank, please select it on the Components | Specifications form.']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
		[ ] 
		[+] window WPFWindow dlgDontAskThisQuestionAgain
			[ ] locator "/WPFWindow[@caption='Aspen Plus' or @caption='Aspen Properties']"
			[+] WPFCheckBox  cboDontAskThisQuestionAgain
				[ ] locator "//WPFCheckBox[@caption='Don*t*.']"
			[+] WPFButton BtnOK
				[ ] locator "//WPFButton[@automationId='Button1']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='Button2']"
		[ ] 
		[+] window WPFWindow wParameterValuesForSelectComponentIDEdit // this is the parameter value dialog for Select the parameter and edit the value
			[ ] locator "/WPFWindow[@caption='Parameter Values']"
			[+] WPFDataGrid drgNameGrid
				[ ] locator "@automationId='NameGrid'"
				[+] FillComponentID(int nRow, int nColumn optional, string sComponentID optional)
					[+] if nColumn == null
						[ ] nColumn = 3
					[+] if null == sComponentID
						[ ] sComponentID = str(nRow)
					[ ] this.Find("//WPFDataGridRow[{nRow}]//WPFDataGridCell[{nColumn}]").DoubleClick()
					[ ] wEnterParameterValue.Exists(10)
					[ ] wEnterParameterValue.SetActive()
					[ ] wEnterParameterValue.txtEditBox.SetText(sComponentID)
					[ ] wEnterParameterValue.BtnOK.Click()
				[+] FillAllComponentID(list of string lsComponentIDs optional)
					[ ] int nCount = ListCount(this.FindAll("//WPFDataGridRow"))
					[+] if lsComponentIDs!= null && ListCount(lsComponentIDs) != nCount
						[ ] LogError("the Component ID list count  is not equal the Row count, please manual check!")
					[ ] int i = 1 
					[+] for ( i = 1; i <= nCount ; ++i)
						[+] if null == lsComponentIDs
							[ ] this.FillComponentID(i)
						[+] else
							[ ] this.FillComponentID(i, null, lsComponentIDs[i])
						[ ] 
				[ ] 
			[+] WPFButton SelectAll
				[ ] locator "@automationId='SelectAll'"
			[+] WPFButton btnEditValue
				[ ] locator "@automationId='Button_1'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='Button_2'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Button_3'"
			[+] WPFButton btnHelp
				[ ] locator "@automationId='Button_4'"
		[ ] 
		[+] window WPFWindow wEnterParameterValue
			[ ] locator "/WPFWindow[@caption='Enter Parameter Value']"
			[+] WPFLabel PromptLabel
				[ ] locator "@automationId='promptLabel'"
			[+] WPFTextBox txtEditBox
				[ ] locator "@automationId='editBox'"
			[+] WPFButton BtnOK
				[ ] locator "@automationId='btnOK'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btnCancel'"
		[ ] 
		[+] window WPFWindow dlgAspenPlusBackup
			[ ] locator "/WPFWindow[@caption='Aspen Plus']"
			[+] WPFTextBlock TxtBlock
				[ ] locator "@automationId='TxtBlock'"
			[+] WPFButton BtnYes
				[ ] locator "@automationId='btn0'"
			[+] WPFButton BtnNo
				[ ] locator "@automationId='btn1'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btn2'"
		[ ] 
		[+] window WPFWindow wErrorsReadingaBackupFile
			[ ] locator "/WPFWindow[@caption='Errors reading a backup file']"
			[+] WPFTextBox TxtFileContent
				[ ] locator "@automationId='txtFileContent'"
		[ ] 
		[+] window DialogBox dlgOpen
			[ ] locator "Open"
			[+] TextField txtFileName
				[ ] locator "File name:"
			[+] ComboBox cboFileNameExtention
				[ ] locator "//ComboBox[@caption='Files of type:']"
			[+] PushButton btnOpen
				[ ] locator "Open"
			[+] PushButton btnCancel
				[ ] locator "Cancel"
		[+] window WPFWindow wAspenPlusSaveLoseDataWarning
			[ ] locator "/WPFWindow[@caption='Aspen Plus']"
			[+] WPFTextBlock BkpTxtForPlus
				[ ] locator "//WPFTextBlock[@automationId='bkpTxtForPlus']"
			[+] WPFCheckBox DoNotShowThisMessageAgain
				[ ] locator "//WPFCheckBox[@caption='Do not show this message again']"
			[+] WPFButton btnOK //Yes 
				[ ] locator "//WPFButton[@automationId='btnOk' or @automationId='Button1' or @automationId='btn1' ]"
			[+] WPFButton btnNo
				[ ] locator "//WPFButton[@automationId='btnNo' or @automationId='Button2']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
		[+] window WPFWindow	 wUpgradedatabanks
			[ ] locator "/WPFWindow[@caption='Upgrade databanks']"
			[+] WPFButton	btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
		[+] window WPFWindow wAspenPlusReplaceExistingFile
			[ ] locator "/WPFWindow[@caption='Aspen Plus']"
			[+] WPFButton BtnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='btn1']"
	[ ] 
	[+] //Import&Export window
		[+] window DialogBox dlgImportWin
			[ ] locator "DialogBox[@caption='Import' or @caption='Open']"
			[ ] 
			[ ] // Different build maybe use different locators for txtFileName.
			[+] property  txtFileName
				[+] window get()
					[+] do
						[+] if (this.Find( "//TextField[@caption='File name:']").Exists())
							[ ] return this.Find( "//TextField[@caption='File name:']")
					[+] except
						[ ] 
					[+] do
						[+] if (this.Find( "//TextField[1]").Exists())
							[ ] return this.Find( "//TextField[1]")
					[+] except
						[ ] 
			[+] WPFTreeView trv1
				[ ] locator "//WPFTreeView[@automationId='tree1']"
			[+] PushButton btnOpen
				[ ] locator "//PushButton[@caption='Open']"
			[+] PushButton btnCancel
				[ ] locator "//PushButton[@caption='Cancel']"
				[ ] 
			[+] // ComboBox cboFileOfType
				[ ] // locator "//ComboBox[@caption='Files of type:']"
			[+] ComboBox cboFileOfType
				[ ] locator "//ComboBox[@caption='File name:'][2]"
			[+] PushButton btnSelectHierarchy
				[ ] locator "//PushButton[@caption='*Select Hierarchy*']"
			[ ] 
			[+] void Import(string sFileName, string sImportFrom)
				[ ] // Import ( string, string )  - Exports a file
				[ ] //   Arguments
				[ ] //   1.  fileName , string, name of export file - extension determines type of file to export
				[ ] //   Usage:  dlgImport.Export('c:\\temp\\pfdtut.inp', "default")
				[ ] 
				[ ] string sExtenison = Lower(glGetReverseField(sFileName, ".", 1))
				[+] string sBaseFileName = SubStr(sFileName,1, len(sFileName) - len(sExtenison)-1)
					[ ] this.SetActive()
					[ ] this.txtFileName.TypeKeys(sBaseFileName)
					[ ] this.cboFileOfType.SetFocus()
					[ ] this.cboFileOfType.Select("*{sExtenison}*")
					[ ] // this coordination (320,425)is the center of Import into Hierachy ComboBox
					[ ] // this.Click(1,320,425)
					[ ] this.btnSelectHierarchy.Click()
					[ ] sleep(2)
					[ ] wSelectHierarchy.SetActive()
					[ ] wSelectHierarchy.trv1.Select(sImportFrom)
					[ ] wSelectHierarchy.btnOK.Click()
					[ ] this.btnOpen.SetFocus()
					[ ] this.btnOpen.Click()
					[ ] this.WaitForDisappearance(10)
				[ ] 
		[+] window WPFWindow dlgImportConfirm
			[ ] locator "/WPFWindow[@caption='Aspen Plus']"
			[+] WPFImage HeaderImage
				[ ] locator "//WPFImage[@automationId='HeaderImage']"
			[+] WPFTextBlock TxtBlock
				[ ] locator "//WPFTextBlock[@automationId='TxtBlock']"
			[+] WPFButton BtnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='btn1']"
		[+] window WPFWindow dlgImportExportWarning
			[ ] locator "/WPFWindow[@caption='Aspen Plus']"
			[+] WPFImage HeaderImage
				[ ] locator "@automationId='HeaderImage'"
			[+] WPFTextBlock TxtBlock
				[ ] locator "@automationId='TxtBlock'"
			[+] WPFButton BtnYes
				[ ] locator "@automationId='btn0'"
			[+] WPFButton BtnNo
				[ ] locator "@automationId='btn1'"
			[+] WPFButton BtnCancel
				[ ] locator  "@automationId='btn2'"
		[+] window WPFWindow wSelectFileToBeExported
			[ ] locator "/WPFWindow[@caption='Step 1: Select File to be Exported']"
			[+] WPFContentControl WizardContent
				[ ] locator "//WPFContentControl[@name='WizardContent']"
			[+] WPFRadioButton rdlXVector
				[ ] locator "//WPFRadioButton[@caption='Aspen Plus X-Vector File(binary)']"
			[+] WPFRadioButton rdlVariablesFileAscii
				[ ] locator "//WPFRadioButton[@caption='Aspen Plus Variables File(ASCII)']"
			[+] WPFButton btnBrowse
				[ ] locator "//WPFButton[@automationId='theButton' or @caption='Browse...']"
			[+] WPFTextBox TheTextBox
				[ ] locator "//WPFTextBox[@automationId='theTextBox']"
			[+] WPFButton BtnPrev
				[ ] locator "//WPFButton[@automationId='btnPrev']"
			[+] WPFButton BtnNext
				[ ] locator "//WPFButton[@automationId='btnNext']"
			[+] WPFButton BtnFinish
				[ ] locator "//WPFButton[@automationId='btnFinish']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
			[+] DialogBox dlgExport
				[ ] locator "//DialogBox[@caption='Export']"
				[+] PushButton btnSave
					[ ] locator "//PushButton[@caption='Save']"
				[+] PushButton btnCancel
					[ ] locator "//PushButton[@caption='Cancel']"
				[+] TextField txtName
					[ ] locator "//TextField"
				[+] void ExportFile(string sFullName)
					[ ] this.txtName.SetFocus()
					[ ] this.txtName.TypeKeys(sFullName)
					[ ] this.btnSave.SetFocus()
					[ ] this.btnSave.Click()
		[+] window WPFWindow wSelectVariableAttributesToExport
			[ ] locator "/WPFWindow[@caption='Step 2: Select Variable Attributes to Export']"
			[+] WPFUserControl Name
				[ ] locator "//WPFUserControl[@caption='Name']"
			[+] WPFCheckBox chkName
				[ ] locator "//WPFCheckBox[@automationId='Name']"
			[+] WPFCheckBox chkUnits
				[ ] locator "//WPFCheckBox[@automationId='Units']"
			[+] WPFCheckBox chkValue
				[ ] locator "//WPFCheckBox[@automationId='Value']"
			[+] WPFCheckBox chkPhysicalType
				[ ] locator "//WPFCheckBox[@automationId='PhysicalType']"
			[+] WPFCheckBox chkLowerBound
				[ ] locator "//WPFCheckBox[@automationId='LowerBound']"
			[+] WPFCheckBox chkSpecType
				[ ] locator "//WPFCheckBox[@automationId='SpecType']"
			[+] WPFCheckBox chkUpperBound
				[ ] locator "//WPFCheckBox[@automationId='UpperBound']"
			[+] WPFCheckBox chkSimpleSpec
				[ ] locator "//WPFCheckBox[@automationId='SimpleSpec']"
			[+] WPFCheckBox chkResolvedLb
				[ ] locator "//WPFCheckBox[@automationId='Resolved_LB']"
			[+] WPFCheckBox chkStepBound
				[ ] locator "//WPFCheckBox[@automationId='StepBound']"
			[+] WPFCheckBox chkResolvedUb
				[ ] locator "//WPFCheckBox[@automationId='Resolved_UB']"
			[+] WPFCheckBox chkStepBoundWeight
				[ ] locator "//WPFCheckBox[@automationId='StepBoundWeight']"
			[+] WPFCheckBox chkInitialValue
				[ ] locator "//WPFCheckBox[@automationId='InitialValue']"
			[+] WPFCheckBox chkActiveBound
				[ ] locator "//WPFCheckBox[@automationId='ActiveBound']"
			[+] WPFCheckBox chkChange
				[ ] locator "//WPFCheckBox[@automationId='Change']"
			[+] WPFCheckBox chkShadowPrice
				[ ] locator "//WPFCheckBox[@automationId='ShadowPrice']"
			[+] WPFCheckBox chkScale
				[ ] locator "//WPFCheckBox[@automationId='Scale']"
			[+] WPFButton BtnPrev
				[ ] locator "//WPFButton[@automationId='btnPrev']"
			[+] WPFButton BtnNext
				[ ] locator "//WPFButton[@automationId='btnNext']"
			[+] WPFButton BtnFinish
				[ ] locator "//WPFButton[@automationId='btnFinish']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
			[+] void CheckAllCheckBox()
				[ ] LIST OF WINDOW  chkBoxes = wSelectVariableAttributesToExport.FindAll(".//WPFCheckBox")
				[ ] int i
				[+] for(i=1;i<=ListCount(chkBoxes);i++)
					[+] if(chkBoxes[i].IsEnabled)
						[+] if(!chkBoxes[i].IsChecked)
							[ ] chkBoxes[i].Click()
							[+] if(dlgAspenPlus.Exists(3))
								[ ] dlgAspenPlus.SetActive()
								[ ] dlgAspenPlus.BtnYes.Click()
							[ ] 
			[+] void CheckAllCheckBoxesFaster()
				[ ] LIST OF WINDOW  chkBoxes = wSelectVariableAttributesToExport.FindAll(".//WPFCheckBox")
				[ ] int i
				[+] for(i=1;i<=ListCount(chkBoxes);i++)
					[+] if(chkBoxes[i].IsEnabled)
						[+] if(!chkBoxes[i].IsChecked)
							[ ] chkBoxes[i].Click()
							[+] if(dlgAspenPlus.Exists(1))
								[ ] dlgAspenPlus.SetActive()
								[ ] dlgAspenPlus.BtnYes.Click()
							[ ] 
			[ ] 
		[+] window WPFWindow wResolveIdConflicts
			[ ] locator "/WPFWindow[@caption='Resolve ID Conflicts']"
			[+] WPFButton btnReplace
				[ ] locator "//WPFButton[@automationId='Replace']"
			[+] WPFButton btnMerge
				[ ] locator "//WPFButton[@automationId='Merge']"
			[+] WPFButton btnEditID
				[ ] locator "//WPFButton[@automationId='EditID']"
			[+] WPFButton btnAddPrefix
				[ ] locator "//WPFButton[@automationId='AddPrefix']"
			[+] WPFButton btnAddSuffix
				[ ] locator "//WPFButton[@automationId='AddSuffix']"
			[+] WPFButton btnIgnore
				[ ] locator "//WPFButton[@automationId='Ignore']"
			[+] WPFButton btnUndo
				[ ] locator "//WPFButton[@automationId='Undo']"
			[+] WPFButton btnOk
				[ ] locator "//WPFButton[@automationId='Ok']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='Cancel']"
			[+] WPFButton btnHelp
				[ ] locator "//WPFButton[@automationId='Help']"
			[+] WPFListView lstConflictIDList
				[ ] locator "//WPFListView[@automationId='ConflictIDList']"
				[+] WPFListViewItem lsviBlocksB1
					[ ] locator "//WPFListViewItem[@caption='Blocks B1*']"
				[ ] 
		[+] window WPFWindow wObjectName
			[ ] locator "/WPFWindow[@caption='Object Name']"
			[+] WPFTextBox txtObjectName
				[ ] locator "@automationId='editBox'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='btnOK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='btnCancel'"
		[+] window WPFWindow wImportOption
			[ ] locator "/WPFWindow[@caption='Import Option']"
			[+] WPFCheckBox chkClearTheContents
				[ ] locator "@automationId='CheckBox_1'"
			[+] WPFCheckBox chkReplaceConflicts
				[ ] locator "@automationId='CheckBox_2'"
			[+] WPFButton BtnContinue
				[ ] locator "@automationId='BtnContinue'"
			[+] WPFButton BtnAbort
				[ ] locator "@automationId='BtnAbort'"
			[+] WPFButton BtnHelp
				[ ] locator "@automationId='BtnHelp'"
		[+] window DialogBox dlgExportAPR
			[ ] locator "//DialogBox[@caption='Export']"
			[+] TextField txtFileName
				[ ] locator "//TextField"
			[+] ComboBox cboSaveAsFileType
				[ ] locator "//ComboBox[2]"
			[+] PushButton btnSave
				[ ] locator "//PushButton[@caption='Save']"
			[+] PushButton btnCancel
				[ ] locator "//PushButton[@caption='Cancel']"
			[ ] 
		[ ] 
		[+] window DialogBox dlgExport
			[ ] locator "//DialogBox[@caption='Export' or @caption='Save*as']"
			[+] TextField txtFileName
				[ ] locator "//TextField[1]"
			[+] ComboBox cboSaveAsType
				[ ] locator "//ComboBox[2]"
			[+] StaticText staticExportFrom
				[ ] locator "//StaticText[@caption='Export from hierarchy:']"
			[+] WPFComboBox cboExportFrom
				[ ] locator "//WPFComboBox[@automationId='Combox1']"
			[+] PushButton btnSelectHierarchy
				[ ] locator "//PushButton[@caption='*Select Hierarchy*']"
			[+] WPFTreeView trv1
				[ ] locator "//WPFTreeView[@automationId='tree1']"
			[+] PushButton btnSave
				[ ] locator "//PushButton[@caption='Save']"
			[+] PushButton btnCancel
				[ ] locator "//PushButton[@caption='Cancel']"
			[+] void Export(string sFileName, string sExportFrom)
				[ ] // Export ( string, string )  - Exports a file
				[ ] //   Arguments
				[ ] //   1.  fileName , string, name of export file - extension determines type of file to export
				[ ] //   Usage:  dlgExport.Export('c:\\temp\\pfdtut.inp', "default")
				[ ] string sExtenison = Lower(glGetReverseField(sFileName, ".", 1))
				[ ] string sBaseFileName = SubStr(sFileName,1, len(sFileName) - len(sExtenison)-1)
				[+] if((sExportFrom == "")||(sExportFrom == "default"))
					[ ] AspenPlusClassicWin.dlgExport.SaveFile(sBaseFileName,"*.{Lower(sExtenison)}*")
				[+] else
					[ ] this.SetActive()
					[ ] this.txtFileName.TypeKeys(sBaseFileName)
					[ ] this.cboSaveAsType.SetFocus()
					[ ] this.cboSaveAsType.Select("*{sExtenison}*")
					[ ] // this coordination (320,425)is the center of Export from Hierachy ComboBox
					[ ] this.btnSelectHierarchy.Click()
					[ ] sleep(2)
					[ ] wSelectHierarchy.SetActive()
					[ ] wSelectHierarchy.trv1.Select(sExportFrom)
					[ ] wSelectHierarchy.btnOK.Click()
					[ ] this.btnSave.SetFocus()
					[ ] this.btnSave.Click()
					[ ] 
					[ ] this.WaitForDisappearance(10)
				[ ] 
				[ ] glWaitForMouseIdle(60)
				[+] Log.Pass("Save file {sBaseFileName} as {upper(sExtenison)} successfully!!!")
					[ ] 
				[+] if(dlgAspenPlusOKOrCancel.Exists(3))
					[ ] dlgAspenPlusOKOrCancel.SetActive()
					[ ] dlgAspenPlusOKOrCancel.BtnOK.Click()
				[ ] 
			[ ] 
		[+] window FormsWindow wSelectHierarchy
			[ ] locator "/FormsWindow[@caption='Select Hierarchy']"
			[+] TreeView trv1
				[ ] locator "//TreeView[@automationId='treeView1']"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@automationId='btnOK']"
			[ ] 
		[+] window WPFWindow wSelectFileToBeImported
			[ ] locator "/WPFWindow[@caption='Step 1: Select File to be Imported']"
			[+] WPFContentControl WizardContent
				[ ] locator "@name='WizardContent'"
			[+] WPFRadioButton rdlAspenPlusXVectorFileBinary
				[ ] locator "Aspen Plus X-Vector File(binary)"
			[+] WPFRadioButton rdlAspenPlusVariablesFileASCII
				[ ] locator "Aspen Plus Variables File(ASCII)"
			[+] WPFTextBox TheTextBox
				[ ] locator "@automationId='theTextBox'"
			[+] WPFButton btnBrowse
				[ ] locator "@automationId='theButton'"
			[+] WPFButton BtnPrev
				[ ] locator "@automationId='btnPrev'"
			[+] WPFButton BtnNext
				[ ] locator "@automationId='btnNext'"
			[+] WPFButton BtnFinish
				[ ] locator "@automationId='btnFinish'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btnCancel'"
			[+] DialogBox dlgOpen
				[ ] locator "Open"
				[+] ComboBox cboFileName
					[ ] locator "[@caption='File name:'][1]"
				[+] TextField txtFileName
					[ ] locator "File name:"
				[+] StaticText FilesOfType
					[ ] locator "Files of type:"
				[+] ComboBox cboFileNameExtention
					[ ] locator "[@caption='File name:'][2]"
				[+] PushButton btnOpen
					[ ] locator "Open"
				[+] PushButton btnCancel
					[ ] locator "Cancel"
				[+] ToolBar ToolBar
					[ ] locator "[1]"
				[+] PushToolItem PushToolItem
					[ ] locator "[1]"
				[+] PushToolItem PushToolItem2
					[ ] locator "[2]"
				[+] PushToolItem RecentPages
					[ ] locator "Recent Pages"
				[+] Control AddressBandRoot
					[ ] locator "@windowClassName='Address Band Root'"
				[+] ProgressBar ProgressBar
					[ ] locator "//ProgressBar"
				[+] Control SearchBox
					[ ] locator "@windowClassName='Search Box'"
				[+] Control SearchEditBoxWrapperClass
					[ ] locator "@windowClassName='SearchEditBoxWrapperClass'"
		[ ] 
		[+] window WPFWindow wSelectScopeToImportVariable
			[ ] locator "/WPFWindow[@caption='Step 2: Select Scope to Import Variables From']"
			[+] WPFTreeView TreeView
				[ ] locator "//WPFTreeView"
			[+] WPFTreeViewItem CAspenPlus_SmokeTestDataDataou
				[ ] locator "C:\AspenPlus_SmokeTest\data\dataout\CQ00247879\analyzer.var"
			[+] WPFImage Image
				[ ] locator "//WPFImage"
			[+] WPFCheckBox chkSynchronizeSMResultsWithImport
				[ ] locator "Synchronize SM results with imported values"
			[+] WPFButton BtnPrev
				[ ] locator "@automationId='btnPrev'"
			[+] WPFButton BtnNext
				[ ] locator "@automationId='btnNext'"
			[+] WPFButton BtnFinish
				[ ] locator "@automationId='btnFinish'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btnCancel'"
		[+] window WPFWindow wSelectVariableAttributesToImport
			[ ] locator "/WPFWindow[@caption='Step 3: Select Variable Attributes to Import']"
			[+] WPFUserControl Name
				[ ] locator "Name"
			[+] WPFCheckBox chkName
				[ ] locator "@automationId='Name'"
			[+] WPFCheckBox chkUnits
				[ ] locator "@automationId='Units'"
			[+] WPFCheckBox chkValue
				[ ] locator "@automationId='Value'"
			[+] WPFCheckBox chkPhysicalType
				[ ] locator "@automationId='PhysicalType'"
			[+] WPFCheckBox chkLowerBound
				[ ] locator "@automationId='LowerBound'"
			[+] WPFCheckBox chkSpecType
				[ ] locator "@automationId='SpecType'"
			[+] WPFCheckBox chkUpperBound
				[ ] locator "@automationId='UpperBound'"
			[+] WPFCheckBox chkSimpleSpec
				[ ] locator "@automationId='SimpleSpec'"
			[+] WPFCheckBox chkResolved_LB
				[ ] locator "@automationId='Resolved_LB'"
			[+] WPFCheckBox chkStepBound
				[ ] locator "@automationId='StepBound'"
			[+] WPFCheckBox chkResolved_UB
				[ ] locator "@automationId='Resolved_UB'"
			[+] WPFCheckBox chkStepBoundWeight
				[ ] locator "@automationId='StepBoundWeight'"
			[+] WPFCheckBox chkInitialValue
				[ ] locator "@automationId='InitialValue'"
			[+] WPFCheckBox chkActiveBound
				[ ] locator "@automationId='ActiveBound'"
			[+] WPFCheckBox chkChange
				[ ] locator "@automationId='Change'"
			[+] WPFCheckBox chkShadowPrice
				[ ] locator "@automationId='ShadowPrice'"
			[+] WPFCheckBox chkScale
				[ ] locator "@automationId='Scale'"
			[+] WPFButton BtnPrev
				[ ] locator "@automationId='btnPrev'"
			[+] WPFButton BtnNext
				[ ] locator "@automationId='btnNext'"
			[+] WPFButton BtnFinish
				[ ] locator "@automationId='btnFinish'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btnCancel'"
			[+] void CheckAllCheckBox()
				[ ] LIST OF WINDOW  chkBoxes = this.FindAll(".//WPFCheckBox")
				[ ] int i
				[+] for(i=1;i<=ListCount(chkBoxes);i++)
					[+] if(chkBoxes[i].IsEnabled)
						[+] if(!chkBoxes[i].IsChecked)
							[ ] chkBoxes[i].Click()
							[+] if(dlgAspenPlusOKOrCancel.Exists(3))
								[ ] dlgAspenPlusOKOrCancel.SetActive()
								[ ] dlgAspenPlusOKOrCancel.BtnOK.Click()
							[ ] 
			[+] void CheckAllCheckBoxesFaster()
				[ ] LIST OF WINDOW  chkBoxes = this.FindAll(".//WPFCheckBox")
				[ ] int i
				[+] for(i=1;i<=ListCount(chkBoxes);i++)
					[+] if(chkBoxes[i].IsEnabled)
						[+] if(!chkBoxes[i].IsChecked)
							[ ] chkBoxes[i].Click()
							[+] if(dlgAspenPlusOKOrCancel.Exists(1))
								[ ] dlgAspenPlusOKOrCancel.SetActive()
								[ ] dlgAspenPlusOKOrCancel.BtnOK.Click()
							[ ] 
			[ ] 
			[ ] 
		[ ] 
		[ ] 
		[+] window WPFWindow wSelectAdditionalRecordsToExport
			[ ] locator "/WPFWindow[@caption='Step 2: Select Additional Records to Export']"
			[+] WPFButton btnBack
				[ ] locator "//WPFButton[@automationId='BtnBack']"
			[+] WPFButton btnFinish
				[ ] locator "//WPFButton[@automationId='Button_1']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='Button_2']"
		[+] window WPFWindow wSelectAdditionalObjectsToExport
			[+] locator "/WPFWindow[@caption='Select additional objects to export:']"
				[+] WPFCheckBox chkHideDisabledNodes
					[ ] locator "//WPFCheckBox[@automationId='checkHideDisabled']"
				[+] WPFButton btnOK
					[ ] locator "//WPFButton[@automationId='Button_1']"
				[+] WPFButton btnCancel
					[ ] locator "//WPFButton[@automationId='Button_2']"
		[+] window DialogBox dlgImportIKCapeFile
			[ ] locator "//DialogBox[@caption='Import IK-CAPE file']"
			[+] TextField txtFileName
				[ ] locator "//TextField[@caption='File name:']"
			[+] PushButton btnOpen
				[ ] locator "//PushButton[@caption='Open']"
		[ ] 
		[+] window WPFWindow wPrefix
			[ ] locator "/WPFWindow[@caption='Prefix']"
			[+] WPFTextBox txbEnterPrefix
				[ ] locator "@automationId='editBox'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='btnOK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='btnCancel'"
		[ ] 
		[ ] 
	[ ] 
	[+] //Run A+ cases windows
		[+] window WPFWindow wNewUtility
			[ ] locator "/WPFWindow[@caption='New Utility']"
			[+] WPFTextBox txtNewUtility
				[ ] locator "//WPFTextBox[@automationId='txtNewUtility']"
			[+] WPFComboBox cboCopyForm
				[ ] locator "//WPFComboBox[@automationId='cboCopyForm']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
		[+] window WPFWindow wReinit
			[ ] locator "/WPFWindow[@caption='Reinit' or @caption='Reinitialize']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
			[+] WPFButton btnHelp
				[ ] locator "//WPFButton[@automationId='Help']"
			[+] WPFTextBlock TextBlock
				[ ] locator "//WPFTextBlock[@caption='Reinitialize calculations. Use when you do not want the next execution of the selected item to start with the previous results.']"
			[+] WPFTextBlock TextBlock2
				[ ] locator "//WPFTextBlock[@caption='Choose what you want to reinitialize:']"
			[+] WPFComboBox ComboBox
				[ ] locator "//WPFComboBox"
			[+] WPFComboBoxItem cboSimulation
				[ ] locator "//WPFComboBoxItem[@caption='Simulation']"
			[+] WPFComboBoxItem cboBlock
				[ ] locator "//WPFComboBoxItem[@caption='Block']"
			[+] WPFComboBoxItem cboConvergence
				[ ] locator "//WPFComboBoxItem[@caption='Convergence']"
			[+] WPFComboBoxItem cboStreams
				[ ] locator "//WPFComboBoxItem[@caption='Streams']"
			[+] WPFTreeView TreeView
				[ ] locator "@automationId='TreeView_1'"
			[+] WPFTreeViewItem trviSelectAll
				[ ] locator "*Select all*"
			[+] WPFCheckBox chkSelectAll
				[ ] locator "*Select all*"
			[+] WPFTreeViewItem trviALL
				[ ] locator "ALL"
			[+] WPFCheckBox chkALL
				[ ] locator "ALL"
			[+] WPFTreeViewItem trviB1
				[ ] locator "B1"
			[+] WPFCheckBox chkB1
				[ ] locator "B1"
			[+] WPFTreeViewItem trviB2
				[ ] locator "B2"
			[+] WPFCheckBox chkB2
				[ ] locator "B2"
			[+] WPFTreeViewItem trviB3
				[ ] locator "B3"
			[+] WPFCheckBox chkB3
				[ ] locator "B3"
			[+] WPFTreeViewItem trviB4
				[ ] locator "B4"
			[+] WPFCheckBox chkB4
				[ ] locator "B4"
			[+] WPFTreeViewItem trviB5
				[ ] locator "B5"
			[+] WPFCheckBox chkB5
				[ ] locator "B5"
			[+] WPFTreeViewItem trviB6
				[ ] locator "B6"
			[+] WPFCheckBox chkB6
				[ ] locator "B6"
		[+] window WPFWindow wInitializeForEO
			[ ] locator "/WPFWindow[@caption='Initialize or Reinitialize Equation Oriented Simulation']"
			[+] WPFRadioButton rdlReinitializeAndRunTheSequentia
				[ ] locator "Reinitialize and run the sequential modular simulation, and synchronize to the equation oriented simulation"
			[+] WPFRadioButton rdlRebuildEquationOrientedSimulat
				[ ] locator "Rebuild equation oriented simulation and reinitialize with current EO results"
			[+] WPFRadioButton rdlRestorePreviousSolutionFromBef
				[ ] locator "Restore previous solution (from before last EO solve)"
			[+] WPFRadioButton rdlReinitializeEquationOrientedSi
				[ ] locator "@caption='Reinitialize equation oriented simulation with changes in configuration Flowsheet/Hierarchy level EO-Input and EO-Options may not be reused during initialization'"
			[+] WPFRadioButton rdlUpdateEquationOrientedSimulati
				[ ] locator "Update equation oriented simulation from external file"
			[+] WPFButton BtnOK
				[ ] locator "@automationId='btnOK'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btnCancel'"
			[+] WPFButton BtnHelp
				[ ] locator "@automationId='btnHelp'"
		[+] window WPFWindow wReinitConfirm
			[ ] locator "/WPFWindow[@caption='Aspen Plus']"
			[+] WPFImage HeaderImage
				[ ] locator "//WPFImage[@automationId='HeaderImage']"
			[+] WPFTextBlock TxtBlock
				[ ] locator "//WPFTextBlock[@automationId='TxtBlock']"
			[+] WPFButton BtnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='btn1']"
		[+] window WPFWindow wEconomicAnalysis
			[ ] locator "/WPFWindow[@className='EconomicAnalysisDialog' or @caption='Economic Analysis']"
			[+] WPFTextBlock TextBlock
				[ ] locator "//WPFTextBlock[@caption='Your simulation has converged.  To evaluate the capital and operating costs of this process, click the """"""""Activate"""""""" button below.']"
			[+] WPFButton btnLearnMore
				[ ] locator "//WPFButton[@automationId='Button_1']"
			[+] WPFButton btnActivate
				[ ] locator "//WPFButton[@automationId='Button_2']"
			[+] WPFButton btnClose
				[ ] locator "//WPFButton[@automationId='Button_3']"
			[+] WPFCheckBox CheckBox
				[ ] locator "/WPFCheckBox[@automationId='CheckBox_1']"
		[+] window WPFWindow wRequiredInputComplete
			[ ] locator "//WPFWindow[@caption='Required Input Complete']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btn0' or @Caption= '_OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btn1' or @Caption= '_Cancel']"
		[+] window WPFWindow wCompletionStatus
			[ ] locator "/WPFWindow[@caption='Completion Status']"
			[+] WPFRichTextBox txbMessageView
				[ ] locator "@automationId='messageView'"
		[+] window WPFWindow wSimulationComplete
			[ ] locator "/WPFWindow[@caption='Simulation Complete']"
			[+] WPFRadioButton rdDisplayRunStatus
				[ ] locator "@automationId='Rd0'"
			[+] WPFRadioButton rdEnterEOInput
				[ ] locator "@automationId='Rd1'"
			[+] WPFRadioButton rdSyncEOModels
				[ ] locator "@automationId='Rd2'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='OK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Cancel'"
		[+] window WPFWindow wSimulationErrors
			[ ] locator "/WPFWindow[@caption='Simulation Errors']"
			[+] WPFRadioButton rdlDisplayEOVariables
				[ ] locator "@automationId='Rd0'"
			[+] WPFRadioButton rdlDisplayRunStatusResults
				[ ] locator "@automationId='Rd1'"
			[+] WPFRadioButton rdlEnterEOInput
				[ ] locator "@automationId='Rd2'"
			[+] WPFRadioButton rdlSolveEOModels
				[ ] locator "@automationId='Rd3'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='OK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Cancel'"
		[+] window WPFWindow wRequiredPropertyEstimationInputComplete
			[ ] locator "/WPFWindow[@caption='Required Property Estimation Input Complete']"
			[+] WPFTextBlock TxtBlock
				[ ] locator "@automationId='TxtBlock'"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='Cancel']"
		[+] window WPFWindow wPropertyEstimationWarnings
			[ ] locator "/WPFWindow[@caption='Property Estimation Warnings']"
			[+] WPFTextBlock TxtBlock
				[ ] locator "@automationId='TxtBlock'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='btn0'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='btn1'"
		[+] window WPFWindow wSimulationWarnings
			[ ] locator "/WPFWindow[@caption='Simulation Warnings']"
			[+] WPFControl AesGroupBox
				[ ] locator "@automationId='AesGroupBox'"
			[+] WPFContentControl AesControlBorder
				[ ] locator "@className='AesControlBorder'"
			[+] WPFRadioButton rdlDisplayRunStatus
				[ ] locator "@automationId='Rd0'"
			[+] WPFRadioButton rdlEnterEOInput
				[ ] locator "@automationId='Rd1'"
			[+] WPFRadioButton rdlSyncEOModels
				[ ] locator "@automationId='Rd2'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='OK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Cancel'"
		[+] window WPFWindow wFlowsheetIncomplete
			[ ] locator "/WPFWindow[@caption='Flowsheet Incomplete']"
			[+] WPFTextBox txtArea
				[ ] locator "@automationId='txtFileContent'"
		[+] window WPFWindow wRequiredEOConfigurationInputComplete
			[ ] locator "/WPFWindow[@caption='*EO Configuration Input Complete']"
			[+] WPFRadioButton rdGoToNext
				[ ] locator "@automationId='Rd0'"
			[+] WPFRadioButton rdDefineMeasurements
				[ ] locator "@automationId='Rd1'"
			[+] WPFRadioButton rdDefineSignificantComponents
				[ ] locator "@automationId='Rd2'"
			[+] WPFRadioButton rdDefineObjective
				[ ] locator "@automationId='Rd3'"
			[+] WPFRadioButton rdDefineSpecGroups
				[ ] locator "@automationId='Rd4'"
			[+] WPFRadioButton rdDefineUserConnections
				[ ] locator "@automationId='Rd5'"
			[+] WPFRadioButton rdDefineHierarchies
				[ ] locator "@automationId='Rd6'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='OK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Cancel'"
		[+] window WPFWindow wInitializeOrReinitialize
			[ ] locator "/WPFWindow[@caption='Initialize or Reinitialize Equation Oriented Simulation']"
			[+] WPFRadioButton rdlReinitializeAndRunTheSequentia
				[ ] locator "Reinitialize and run the sequential modular simulation, and synchronize to the equation oriented simulation"
			[+] WPFRadioButton rdlRebuildEquationOrientedSimulat
				[ ] locator "Rebuild equation oriented simulation and reinitialize with current EO results"
			[+] WPFRadioButton rdlRestorePreviousSolutionFromBef
				[ ] locator "Restore previous solution (from before last EO solve)"
			[+] WPFRadioButton rdlReinitializeEquationOrientedSi
				[ ] locator "@caption='Reinitialize equation oriented simulation with changes in configuration Flowsheet/Hierarchy level EO-Input and EO-Options may not be reused during initialization'"
			[+] WPFRadioButton rdlUpdateEquationOrientedSimulati
				[ ] locator "Update equation oriented simulation from external file"
			[+] WPFButton BtnOK
				[ ] locator "@automationId='btnOK'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btnCancel'"
			[+] WPFButton BtnHelp
				[ ] locator "@automationId='btnHelp'"
		[+] window WPFWindow wUpdateParameters
			[ ] locator "/WPFWindow[@caption='Update Parameters']"
			[+] WPFButton btnYes
				[ ] locator "//WPFButton[1]"
			[+] WPFButton btnNo
				[ ] locator "//WPFButton[2]"
				[ ] 
		[+] window WPFWindow wPropertiesAnalysisSetupComplete
			[ ] locator "/WPFWindow[@caption='Properties Analysis/Setup Complete']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[1]"
		[+] window WPFWindow wSimulationErrorsNew
			[ ] locator "/WPFWindow[@caption='Simulation Errors']"
			[+] WPFRadioButton rdlDisplayRunStatusResults
				[ ] locator "@automationId='Rd0'"
			[+] WPFRadioButton rdlDisplayEOVariables
				[ ] locator "@automationId='Rd1'"
			[+] WPFRadioButton rdlEnterEOInput
				[ ] locator "@automationId='Rd2'"
			[+] WPFRadioButton rdlSolveEOModels
				[ ] locator "@automationId='Rd3'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='OK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Cancel'"
		[+] window WPFWindow wReadyToExecuteBlock
			[ ] locator "/WPFWindow[@caption='Ready to execute block*']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[1]"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[2]"
		[+] window WPFWindow wReExecute
			[ ] locator "/WPFWindow[@caption='Re-execute']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[1]"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[2]"
		[+] window WPFWindow wRequiredPropertyAnalysisInputComplete
			[ ] locator "/WPFWindow[@caption='Required Property Analysis Input Complete']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btn1']"
		[+] window MainWin wSelectCompilerForAspenPlus
			[ ] tag "[DialogBox]*{sProgramFilePath}\AspenTech\AprSystem {sVersion}\Engine\Xeq\ApSetComp.exe*"
			[ ] const sCmdLine ="{sProgramFilePath}\AspenTech\AprSystem {sVersion}\Engine\Xeq\ApSetComp.exe  -select"
			[+] //--------------------------------------------------------- GUI - --------------------------------------------------------//
				[+] DialogBox dlgContextMenu
					[ ] tag "#1"
			[+] //------------------------------------------------------- Method -------------------------------------------------------//
				[+] void Invoke()
					[+] if !this.Exists(2)
						[ ] derived::Invoke()
					[ ] this.SetActive()
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
					[ ] Clipboard.SetText()
					[ ] this.PickContextMenu("Select All")
					[ ] this.PickContextMenu("Copy")
					[ ] sleep(0.5)
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
					[ ] this.ExecuteCommand('cd /d "{sPath}"')
				[+] void Exit()
					[ ] this.ExecuteCommand("Exit")
				[+] boolean FindStr(string sPattern)
					[ ] int i
					[ ] boolean bRev = false
					[ ] list of string lsResults = this.GetCMDContents()
					[+] for (i = 1; i <= listcount(lsResults); ++i)
						[+] if MatchStr(sPattern,lsResults[i])
							[ ] bRev = True
							[ ] break
					[ ] 
					[ ] return bRev
				[+] boolean checkForErrors(int passCount)
					[ ] string sPattern1 = "*TERMINAL ERRORS      0        0         0*"
					[ ] string sPattern2 = "*SEVERE ERRORS      0        0         0*"
					[ ] string sPattern3 = "*ERRORS      0        0         0*"
					[ ] string sPattern4 = "*NO ERRORS OR WARNINGS GENERATED*"
					[ ] int i
					[ ] integer countPass1 = 0
					[ ] integer countPass2 = 0
					[ ] integer countPass3 = 0
					[ ] integer countPass4 = 0
					[ ] list of string lsResults = this.GetCMDContents()
					[+] for (i = 1; i <= listcount(lsResults); i++)
						[+] if MatchStr(sPattern1,lsResults[i])
							[ ] countPass1++
						[+] else if(MatchStr(sPattern2,lsResults[i]) )
							[ ] countPass2++
						[+] else if(MatchStr(sPattern3,lsResults[i]) )
							[ ] countPass3++
						[+] else if(MatchStr(sPattern4,lsResults[i]) )
							[ ] countPass4++
						[+] else
							[ ] 
							[ ] 
						[ ] print(lsResults[i])
					[ ] PRINT("sPattern1: {countPass1}     sPattern2: {countPass2}       sPattern3: {countPass3}      sPattern4: {countPass4}  ")
					[ ] integer countPassTotal =   countPass4*3 + countPass1 + countPass2 + countPass3
					[ ] integer countExpected = passCount * 3  // 3 Rows of no errors for each test. "NO ERRORS OR WARNINGS GENERATED" counts as 3 rows of no errors since it will not print error table
					[+] if(  (countPassTotal ) < countExpected)
						[ ] Log.Error("One of the test cases has an error, Check command_output.txt count is {countPassTotal} ")
						[ ] // OUTPUT COMMAND LINE
						[ ] handle hFile = FileOpen("{sDataout}\command_output.txt", FM_WRITE)
						[ ] string sLine
						[+] for each sLine in lsResults
							[ ] FileWriteLine( hFile, sLine)
							[ ] 
						[ ] FileClose(hFile)
					[+] else  if(  (countPassTotal ) ==  countExpected)
						[ ] Log.Pass("*********EXPECTED NUMBER OF PASSED TESTS HAS BEEN FOUND******************")
						[ ] return TRUE
					[+] if(  countPassTotal <= countExpected )
						[ ] Log.ERROR("NOT COUNTING PASSES CORRECTLY, FIX COUNTING METHOD")
					[ ] return FALSE
				[+] boolean waitUntilFinished(string directory)
					[ ] //directory should be in a similar format
					[ ] //                  C:\Temp
					[ ] int timeout = 180
					[ ] int i = 0
					[ ] list of STRING contents = this.GetCMDContents()
					[+] while( contents[listcount(contents)] !=  "{directory}>"  && i < timeout)
						[ ] i+=5
						[ ] sleep(2)
						[ ] contents = this.GetCMDContents()
					[ ] 
					[+] if( i <= timeout)
						[ ] return TRUE
					[+] else
						[ ] return FALSE
					[ ] 
				[ ] 
				[ ] 
		[ ] 
	[ ] 
	[+] //Print windows
		[+] window DialogBox dlgPrint
			[ ] locator "//DialogBox[@caption='Print']"
			[+] ComboBox cboName
				[ ] locator "//ComboBox[@caption='Name:']"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@caption='OK']"
			[+] PushButton btnPrint
				[ ] locator "//PushButton[@caption='Print']"
				[ ] 
			[+] ListViewEx lstv
				[ ] locator "//ListViewEx[1]"
				[ ] 
		[+] window DialogBox dlgSavePrintFile
			[ ] locator "//*[@caption='Save Print Output As' or @caption='Save the file as']"
			[+] ComboBox cboSetName
				[ ] locator "//ComboBox[1]"
			[+] PushButton btnSave
				[ ] locator "//PushButton[@caption='Save']"
		[+] window DialogBox dlgConfirmSaveAs
			[ ] locator "//DialogBox[@caption='Confirm Save As']"
			[+] PushButton btnYes
				[ ] locator "//PushButton[@caption='Yes']"
			[+] PushButton btnNo
				[ ] locator "//PushButton[@caption='No']"
				[ ] 
	[ ] 
	[+] //Control Panel windows
		[+] window WPFWindow wControlPanel
			[ ] locator "//WPFHeaderedContentControl[@automationId='ControlPanelScreenFactory']"
			[+] WPFContentControl PaneToolWindow
				[ ] locator "//WPFContentControl[@className='PaneToolWindow']"
			[+] WPFFrameworkElement Zce2de05b4d6e4096a1cb79c0c1fb0
				[ ] locator "//WPFFrameworkElement[@automationId='Zce2de05b4d6e4096a1cb79c0c1fb0cec']"
			[+] WPFHeaderedContentControl ControlPanelScreenFactory
				[ ] locator "//WPFHeaderedContentControl[@automationId='ControlPanelScreenFactory']"
			[+] WPFContentControl ControlPanelView
				[ ] locator "//WPFContentControl[@automationId='controlPanelView']"
			[+] WPFExpander ExpOptions
				[ ] locator "//WPFExpander[@automationId='expOptions']"
			[+] WPFToggleButton tbToggleEOControl
				[ ] locator "//WPFToggleButton[@automationId='HeaderSite']"
			[+] WPFToggleButton HeaderSite
				[ ] locator "//WPFToggleButton[@automationId='HeaderSite']"
			[+] WPFContentControl ResizableBd
				[ ] locator "//WPFContentControl[@name='resizableBd']"
			[+] WPFThumb PartRightThumb
				[ ] locator "//WPFThumb[@automationId='Part_RightThumb']"
			[+] WPFExpander ExpSequence
				[ ] locator "//WPFExpander[@automationId='expSequence']"
			[+] WPFToggleButton ToggleButton
				[ ] locator "//WPFToggleButton[2]"
			[+] WPFTextBlock ExpandedHeader
				[ ] locator "//WPFTextBlock[@automationId='ExpandedHeader']"
			[+] WPFTreeView SequenceView
				[ ] locator "//WPFTreeView[@automationId='sequenceView']"
			[+] WPFTreeViewItem trviCalculationSequence
				[ ] locator "//WPFTreeViewItem[@caption='Calculation Sequence']"
			[+] WPFImage HeaderImage
				[ ] locator "//WPFImage[@automationId='HeaderImage'][1]"
			[+] WPFTextBlock CalculationSequenceTextBlock
				[ ] locator "//WPFTextBlock[@caption='Calculation Sequence']"
			[+] WPFTreeViewItem Cv
				[ ] locator "//WPFTreeViewItem[@caption='CV']"
			[+] WPFImage HeaderImage2
				[ ] locator "//WPFImage[@automationId='HeaderImage'][2]"
			[+] WPFTextBlock CvTextBlock
				[ ] locator "//WPFTextBlock[@caption='CV']"
			[+] WPFTreeViewItem B2
				[ ] locator "//WPFTreeViewItem[@caption='B2']"
			[+] WPFImage HeaderImage3
				[ ] locator "//WPFImage[@automationId='HeaderImage'][3]"
			[+] WPFTextBlock B2TextBlock
				[ ] locator "//WPFTextBlock[@caption='B2']"
			[+] PushButton btnCancel
				[ ] locator "//PushButton[@caption='Cancel']"
			[+] CheckBox chkDisplayAsIcon
				[ ] locator "//CheckBox[@caption='Display As Icon']"
			[+] WPFTreeViewItem B3
				[ ] locator "//WPFTreeViewItem[@caption='B3']"
			[+] WPFImage HeaderImage4
				[ ] locator "//WPFImage[@automationId='HeaderImage'][4]"
			[+] WPFTextBlock B3TextBlock
				[ ] locator "//WPFTextBlock[@caption='B3']"
			[+] WPFMenuItem miReinitialize
				[ ] locator "//WPFMenuItem[@caption='_Reinitialize']"
			[+] WPFTreeViewItem B4
				[ ] locator "//WPFTreeViewItem[@caption='B4']"
			[+] WPFImage HeaderImage5
				[ ] locator "//WPFImage[@automationId='HeaderImage'][5]"
			[+] WPFTextBlock B4TextBlock
				[ ] locator "//WPFTextBlock[@caption='B4']"
			[+] WPFTreeViewItem B5
				[ ] locator "//WPFTreeViewItem[@caption='B5']"
			[+] WPFImage HeaderImage6
				[ ] locator "//WPFImage[@automationId='HeaderImage'][6]"
			[+] WPFTextBlock B5TextBlock
				[ ] locator "//WPFTextBlock[@caption='B5']"
			[+] WPFTreeViewItem OLVER01
				[ ] locator "//WPFTreeViewItem[@caption='$OLVER01']"
			[+] WPFImage HeaderImage7
				[ ] locator "//WPFImage[@automationId='HeaderImage'][7]"
			[+] WPFTextBlock OLVER01TextBlock
				[ ] locator "//WPFTextBlock[@caption='$OLVER01']"
			[+] WPFTreeViewItem B1
				[ ] locator "//WPFTreeViewItem[@caption='B1']"
			[+] WPFImage HeaderImage8
				[ ] locator "//WPFImage[@automationId='HeaderImage'][8]"
			[+] WPFTextBlock B1TextBlock
				[ ] locator "//WPFTextBlock[@caption='B1']"
			[+] WPFTreeViewItem B6
				[ ] locator "//WPFTreeViewItem[@caption='B6']"
			[+] WPFImage HeaderImage9
				[ ] locator "//WPFImage[@automationId='HeaderImage'][9]"
			[+] WPFTextBlock B6TextBlock
				[ ] locator "//WPFTextBlock[@caption='B6']"
			[+] WPFRichTextBox MessageView
				[ ] locator "//WPFRichTextBox[@automationId='messageView']"
			[+] WPFLabel LabelSMStatus
				[ ] locator "@automationId='labelSMStatus'"
			[+] WPFLabel LabelEOStatus
				[ ] locator "@automationId='labelEOStatus'"
			[+] WPFCheckBox chkInvokePresolveScript
				[ ] locator "@automationId='CheckBox_1'"
			[+] WPFCheckBox chkInvokePostsolveScript
				[ ] locator "@automationId='CheckBox_2'"
			[+] WPFTextBox txtCommandLine
				[ ] locator "@automationId='tbCommandLine'"
			[+] WPFButton BtnClose
				[ ] locator "@automationId='btnClose'"
			[+] WPFButton BtnNoCreep
				[ ] locator "@automationId='btnNoCreep'"
			[+] WPFButton BtnAbort
				[ ] locator "@automationId='btnAbort'"
			[+] WPFToggleButton tbHideSequence
				[ ] locator "Hide sequence"
			[ ] 
		[+] window WPFWindow wCopySpecial
			[ ] locator "/WPFWindow[@caption='Copy Special']"
			[+] WPFTreeView trvTreeView
				[ ] locator "//WPFTreeView[@automationId='theTreeView']"
				[+] WPFTreeViewItem tviFlowsheet
					[ ] locator "//WPFTreeViewItem[@caption='Flowsheet']"
					[+] WPFCheckBox chkFlowsheet
						[ ] locator "//WPFCheckBox[@caption='Flowsheet']"
				[+] WPFTreeViewItem tviFlowsheetingOptions
					[ ] locator "//WPFTreeViewItem[@caption='Flowsheeting Options']"
					[+] WPFCheckBox chkFlowsheetingOptions
						[ ] locator "//WPFCheckBox[@caption='Flowsheeting Options']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='Button_1']"
	[ ] 
	[+] //Simulation Run options windows
		[+] window WPFWindow wSimulationRunOptions
			[ ] locator "/WPFWindow[@caption='Simulation Run Options' or @caption='File Type And Location Options' or @caption='Upward Compatibility Options' or @caption='Flowsheet Display Options']"
			[ ] 
			[+] WPFListBox LstOption
				[ ] locator "@automationId='lstOption'"
			[+] WPFListBoxItem Simulation
				[ ] locator "Simulation"
			[+] WPFListBoxItem PropertiesBasis
				[ ] locator "Properties Basis"
			[+] WPFListBoxItem Files
				[ ] locator "Files"
			[+] WPFListBoxItem Flowsheet
				[ ] locator "Flowsheet"
			[+] WPFListBoxItem Plots
				[ ] locator "Plots"
			[+] WPFListBoxItem UpwardCompatibility
				[ ] locator "Upward Compatibility"
			[+] WPFListBoxItem Advanced
				[ ] locator "Advanced"
			[+] WPFListBoxItem Startup
				[ ] locator "Startup"
			[+] WPFButton Btn_Help
				[ ] locator "@automationId='btn_Help'"
			[+] WPFButton Btn_Apply
				[ ] locator "@automationId='btn_Apply'"
			[+] WPFButton Btn_Cancel
				[ ] locator "@automationId='btn_Cancel'"
			[+] WPFButton Btn_OK
				[ ] locator "@automationId='btn_OK'"
			[+] WPFCheckBox ChkInteractiveLoad
				[ ] locator "@automationId='chkInteractiveLoad'"
			[ ] //Files tab
			[+] WPFHeaderedContentControl grpLocations
				[ ] locator "//WPFHeaderedContentControl[@caption='Locations']"
				[+] WPFTextBox txtWorkFolder
					[ ] locator "//WPFTextBox[@automationId='txtDefaultWorking']"
			[ ] 
			[ ] //UpwardCompatibility
			[+] WPFCheckBox tbiUpwardCompatibility
				[+] WPFCheckBox chkShowUpwardCompatibilityDialog
					[ ] locator "//WPFCheckBox[@automationId='chkShowUpwardCompat']"
			[ ] 
			[ ] //Flowsheet Display Options
			[ ] //Automatically assign block name with prefix:
			[+] WPFCheckBox chkAutoAssignBlockName
				[ ] locator "//WPFCheckBox[@automationId='chkAssignBlockName']"
		[+] window WPFWindow  wRunSettings
			[ ] locator "/WPFWindow[@caption='Run Settings']"
			[+] WPFTabControl TcRunSettings
				[ ] locator "//WPFTabControl[@automationId='tc_RunSettings']"
			[+] WPFGroupBox GbUserPropertyDatabanks
				[ ] locator "//WPFGroupBox[@automationId='gb_UserPropertyDatabanks']"
			[+] WPFLabel LbPp1a
				[ ] locator "//WPFLabel[@automationId='lb_pp1a']"
			[+] WPFTextBox TxtPp1a
				[ ] locator "//WPFTextBox[@automationId='txt_pp1a']"
			[+] WPFLabel LbPp1b
				[ ] locator "//WPFLabel[@automationId='lb_pp1b']"
			[+] WPFTextBox TxtPp1b
				[ ] locator "//WPFTextBox[@automationId='txt_pp1b']"
			[+] WPFLabel LbPp2a
				[ ] locator "//WPFLabel[@automationId='lb_pp2a']"
			[+] WPFTextBox TxtPp2a
				[ ] locator "//WPFTextBox[@automationId='txt_pp2a']"
			[+] WPFLabel LbPp2b
				[ ] locator "//WPFLabel[@automationId='lb_pp2b']"
			[+] WPFTextBox TxtPp2b
				[ ] locator "//WPFTextBox[@automationId='txt_pp2b']"
			[+] WPFLabel LbPp2c
				[ ] locator "//WPFLabel[@automationId='lb_pp2c']"
			[+] WPFTextBox TxtPp2c
				[ ] locator "//WPFTextBox[@automationId='txt_pp2c']"
			[+] WPFGroupBox GbUserLibraries
				[ ] locator "//WPFGroupBox[@automationId='gb_UserLibraries']"
			[+] WPFLabel LbInsert
				[ ] locator "//WPFLabel[@automationId='lb_Insert']"
			[+] WPFTextBox TxtInsert
				[ ] locator "//WPFTextBox[@automationId='txt_Insert']"
			[+] WPFLabel LbStream
				[ ] locator "//WPFLabel[@automationId='lb_Stream']"
			[+] WPFTextBox TxtStream
				[ ] locator "//WPFTextBox[@automationId='txt_Stream']"
			[+] WPFGroupBox GbMiscellaneousFiles
				[ ] locator "//WPFGroupBox[@automationId='gb_Miscellaneous_Files']"
			[+] WPFLabel LbLinkerOptions
				[ ] locator "//WPFLabel[@automationId='lb_LinkerOptions']"
			[+] WPFTextBox TxtLinkerOptions
				[ ] locator "//WPFTextBox[@automationId='txt_LinkerOptions']"
			[+] WPFLabel LbRunDefinitions
				[ ] locator "//WPFLabel[@automationId='lb_RunDefinitions']"
			[+] WPFTextBox TxtRunDefinition
				[ ] locator "//WPFTextBox[@automationId='txt_RunDefinition']"
			[+] WPFTabItem TbOptions
				[ ] locator "//WPFTabItem[@automationId='tb_Options']"
			[+] WPFTabItem TbBatchRun
				[ ] locator "//WPFTabItem[@automationId='tb_BatchRun']"
			[+] WPFTabItem TbEngineFiles
				[ ] locator "//WPFTabItem[@automationId='tb_EngineFiles']"
			[+] WPFButton BtnOk
				[ ] locator "//WPFButton[@automationId='btn_OK']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='btn_Cancel']"
			[+] WPFButton BtnApply
				[ ] locator "//WPFButton[@automationId='btn_Apply']"
			[+] WPFButton BtnHelp
				[ ] locator "//WPFButton[@automationId='btn_Help']"
			[+] WPFGroupBox GbInteractiveRuns
				[ ] locator "//WPFGroupBox[@automationId='gb_InteractiveRuns']"
			[+] WPFCheckBox chkAutoRunMode
				[ ] locator "//WPFCheckBox[@automationId='chkAutoRun']"
			[+] WPFCheckBox ChkExpressRun
				[ ] locator "//WPFCheckBox[@automationId='chk_ExpressRun']"
			[+] WPFCheckBox ChkInteractivelyLoad
				[ ] locator "//WPFCheckBox[@automationId='chk_InteractivelyLoad']"
			[+] WPFCheckBox ChkAnimateFlowsheet
				[ ] locator "//WPFCheckBox[@automationId='chk_AnimateFlowsheet']"
			[+] WPFGroupBox GbInputOptions
				[ ] locator "//WPFGroupBox[@automationId='gb_InputOptions']"
			[+] WPFCheckBox ChkAllowRun
				[ ] locator "//WPFCheckBox[@automationId='chk_AllowRun']"
			[+] WPFCheckBox ChkEditKeyword
				[ ] locator "//WPFCheckBox[@automationId='chk_EditKeyword']"
			[+] WPFGroupBox GbCurrentSimulation
				[ ] locator "//WPFGroupBox[@automationId='gb_CurrentSimulation']"
			[+] WPFLabel LblLoadResults
				[ ] locator "//WPFLabel[@automationId='lbl_LoadResults']"
			[+] WPFButton BtnLoad
				[ ] locator "//WPFButton[@automationId='btn_Load']"
			[+] WPFLabel LblRestartSimulation
				[ ] locator "//WPFLabel[@automationId='lbl_RestartSimulation']"
			[+] WPFButton BtnRestart
				[ ] locator "//WPFButton[@automationId='btn_Restart']"
			[+] WPFGroupBox grpSubmit
				[ ] locator "//WPFGroupBox[@automationId='GroupBox_1']"
				[+] WPFTextBox txbRunId
					[ ] locator "//WPFTextBox[@automationId='TextBox_1']"
				[+] WPFTextBox txbLocation
					[ ] locator "//WPFTextBox[@automationId='txtPath']"
				[+] WPFTextBox txbCommandLine
					[ ] locator "//WPFTextBox[@automationId='TextBox_2']"
				[+] WPFCheckBox chkDeleteTempFiles
					[ ] locator "//WPFCheckBox[@automationId='chk_DeleteFiles']"
				[+] WPFButton btnSubmit
					[ ] locator "//WPFButton[@automationId='btnSubmit']"
				[+] WPFButton btnBrowse
					[ ] locator "//WPFButton[@automationId='btnBrowse']"
			[+] WPFGroupBox grpJobStatusAndLoadResults
				[ ] locator "//WPFGroupBox[@automationId='GroupBox_2']"
				[+] WPFListView lsvBatchRuns
					[ ] locator "//WPFListView[@automationId='lsbIDs']"
				[+] WPFButton btnLoad
					[ ] locator "//WPFButton[@automationId='btnLoad']"
					[ ] 
					[ ] 
					[ ] 
		[ ] 
		[ ] 
	[ ] 
	[+] //Blocks and Streams window
		[+] window WPFWindow  wRename
			[ ] locator "/WPFWindow[@caption='Rename']"
			[+] WPFTextBlock TextBlkPrompt
				[ ] locator "@automationId='textBlkPrompt'"
			[+] WPFTextBox TbText
				[ ] locator "@automationId='tbText'"
			[+] WPFButton BtnOK
				[ ] locator "@automationId='btnOK'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btnCancel'"
		[+] window WPFWindow wCopyStreamResultsToInputSpec //Window name changed to CopyResultsToIputSpecifications
			[ ] locator "/WPFWindow[@caption='Copy results to input specifications']"
			[+] WPFCheckBox ChkFeed
				[ ] locator "@automationId='chkFeed'"
			[+] WPFCheckBox ChkTear
				[ ] locator "@automationId='chkTear'"
			[+] WPFCheckBox ChkAllOtherInput
				[ ] locator "@automationId='chkInput'"
			[+] WPFCheckBox ChkAllOtherNotRecommend
				[ ] locator "@automationId='chkOther'"
			[+] WPFRadioButton rdlUseInput
				[ ] locator "@automationId='Input_Radio'"
			[+] WPFRadioButton rdlReconcileSelectedVar
				[ ] locator "@automationId='Select_Radio'"
			[+] WPFGroupBox grpSelectStreamsToReconcile
				[ ] locator "@automationId='gbxSSTR'"
				[+] WPFCheckBox chkFeedStreams
					[ ] locator "@automationId='chkFeed'"
				[+] WPFCheckBox chkTearStreams
					[ ] locator "@automationId='chkTear'"
				[+] WPFCheckBox chkAllOtherStreamsWithInputSpecifications
					[ ] locator "@automationId='chkInput'"
				[+] WPFCheckBox chkAllOtherStreamsNotRecommended
					[ ] locator "@automationId='chkOther'"
			[+] WPFGroupBox grpSelectVariablesToReconcile
				[ ] locator "@automationId='gbxSVTR'"
				[+] WPFRadioButton rdUseInputSpecificationsToSelectVariablesToReconcile
					[ ] locator "@automationId='Input_Radio'"
				[+] WPFRadioButton rdReconcileSelectedvariables
					[ ] locator "@automationId='Select_Radio'"
			[+] WPFGroupBox grpStateVariables
				[ ] locator "@automationId='gbxSV'"
				[+] WPFRadioButton rdTemperaturePressure
					[ ] locator "@automationId='TP_Radio'"
				[+] WPFRadioButton rdTemperatureVaporFraction
					[ ] locator "@automationId='TV_Radio'"
				[+] WPFRadioButton rdPressureVaporFraction
					[ ] locator "@automationId='PV_Radio'"
			[+] WPFGroupBox grpTypeOfVariables
				[ ] locator "@automationId='gbxTV'"
				[+] WPFRadioButton rdComponentFlows
					[ ] locator "@automationId='CF_Radio'"
				[+] WPFRadioButton rdComponentFractionsTotalFlow
					[ ] locator "@automationId='TF_Radio'"
			[+] WPFGroupBox grpBasisForMIXEDSubstream
				[ ] locator "@automationId='gbxBFMS'"
				[+] WPFRadioButton rdMole
					[ ] locator "@automationId='MIMole_Radio'"
				[+] WPFRadioButton rdMass
					[ ] locator "@automationId='MIMass_Radio'"
				[+] WPFRadioButton rdStandardVolume
					[ ] locator "@automationId='MISTDVOL_Radio'"
			[+] WPFGroupBox grpBasisForCISOLIDSubstream
				[ ] locator "@automationId='gbxBFCS'"
				[+] WPFRadioButton rdMole
					[ ] locator "@automationId='CIMole_Radio'"
				[+] WPFRadioButton rdMass
					[ ] locator "@automationId='CIMass_Radio'"
			[+] WPFButton BtnOK
				[ ] locator "@automationId='btnOK'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btnCancel'"
		[+] window WPFWindow wReconcileBlocksWithErrorsOrWarnings
			[ ] locator "/WPFWindow[@caption='Reconcile blocks with errors or warnings?']"
			[+] WPFButton BtnYes
				[ ] locator "@automationId='btn0'"
			[+] WPFButton BtnYesToAll
				[ ] locator "@automationId='btn1'"
			[+] WPFButton BtnNo
				[ ] locator "@automationId='btn2'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btn3'"
		[+] window WPFWindow wAdditionalOptions
			[ ] locator "/WPFWindow[@caption='Additional Options']"
			[+] WPFButton btnClose
				[ ] locator "Close"
		[+] window WPFWindow wStreamClass
			[ ] locator "/WPFWindow[@caption='Stream Class']"
			[+] WPFComboBox cboStreamClassList
				[ ] locator "@automationId='cbxStreamClassList'"
			[+] WPFButton BtnOK
				[ ] locator "@automationId='btnOK'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btnCancel'"
		[+] window WPFWindow wStreamPointProperties
			[ ] locator "/WPFWindow[@caption='Stream Point Properties']"
			[+] WPFCheckBox chkMole
				[ ] locator "[@automationId='PART_CheckBox'][1]"
			[+] WPFCheckBox chkMass
				[ ] locator "[@automationId='PART_CheckBox'][2]"
			[+] WPFCheckBox chkVolume
				[ ] locator "[@automationId='PART_CheckBox'][3]"
			[+] WPFCheckBox chkThermodynamicProperties
				[ ] locator "[@automationId='PART_CheckBox'][4]"
			[+] WPFCheckBox chkTransportProperties
				[ ] locator "[@automationId='PART_CheckBox'][5]"
			[+] WPFButton btnGo
				[ ] locator "Go"
			[+] WPFButton btnCancel
				[ ] locator "Cancel"
		[+] window WPFWindow wStreamPointAnalysisResults
			[ ] locator "/WPFWindow[@caption='Stream Point Analysis Results']"
		[+] window WPFWindow wStreamComponentFlow
			[ ] locator "/WPFWindow[@caption='Stream Component Flow']"
			[+] WPFButton btnGo
				[ ] locator "//WPFButton[@caption='Go']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
				[ ] 
		[+] window WPFWindow wStreamComponentFlowAnalysisResults
			[ ] locator "/WPFWindow[@caption='Stream Component Flow Analysis Results']"
		[+] window WPFWindow wStreamComposition
			[ ] locator "/WPFWindow[@caption='Stream Composition']"
			[+] WPFButton btnGo
				[ ] locator "//WPFButton[@caption='Go']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
				[ ] 
		[+] window WPFWindow wStreamCompositionAnalysisResults
			[ ] locator "/WPFWindow[@caption='Stream Composition Analysis Results']"
		[+] window WPFWindow wStreamPetroleumProperties
			[ ] locator "/WPFWindow[@caption='Stream Petroleum Properties']"
			[+] WPFButton btnGo
				[ ] locator "//WPFButton[@caption='Go']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
				[ ] 
		[+] window WPFWindow wStreamPetroleumAnalysisResults
			[ ] locator "/WPFWindow[@caption='Stream - Petroleum Analysis Results']"
		[+] window WPFWindow wAddBlock
			[ ] locator "//WPFWindow[@caption='Add Block']"
			[ ] 
			[+] WPFTextBox txbName
				[ ] locator "//WPFTextBox[@automationId='tbText']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
				[ ] 
		[+] window WPFWindow wConfirmDelete
			[ ] locator "/WPFWindow[@caption='Confirm Delete']"
			[+] WPFImage HeaderImage
				[ ] locator "@automationId='HeaderImage'"
			[+] WPFTextBlock txbWarning
				[ ] locator "@automationId='TxtBlock'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='btn0'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='btn1'"
		[ ] 
		[ ] 
	[ ] 
	[+] //Components
		[+] window WPFWindow wElectrolyteWizard
			[ ] locator "/WPFWindow[@caption='Electrolyte Wizard']"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='buttonCancel'"
			[+] WPFButton btnBack
				[ ] locator "//WPFButton[@caption='*Back']"
			[+] WPFButton btnNext
				[ ] locator "//WPFButton[@caption='Next*']"
			[+] WPFButton btnFinish
				[ ] locator "//WPFButton[@caption='Finish']"
				[ ] 
			[+] WPFButton btnMove
				[ ] locator "@automationId='btnMove'"
			[+] WPFButton btnMoveAll
				[ ] locator "@automationId='btnMoveAll'"
			[+] WPFButton btnRemove
				[ ] locator "@automationId='btnRemove'"
			[+] WPFButton btnClearAll
				[ ] locator "@automationId='btnClearAll'"
			[+] WPFGroupBox grpSelectChemDatabank
				[ ] locator "//WPFGroupBox[@automationId='grpDBank']"
				[+] WPFComboBox cboChemistryDataSource
					[ ] locator "//WPFComboBox[@automationId='cboDBSelect']"
				[+] WPFComboBox cboReferenceState
					[ ] locator "//WPFComboBox[@automationId='cboRefStateSelect']"
				[ ] 
			[+] WPFGroupBox grpSelectBaseComponents
				[ ] locator "//WPFGroupBox[@caption='Select base components']"
				[+] WPFButton btnMoveRight
					[ ] locator "//WPFButton[1]"
				[+] WPFButton btnMoveAllRight
					[ ] locator "//WPFButton[2]"
				[+] WPFButton btnMoveLeft
					[ ] locator "//WPFButton[3]"
				[+] WPFButton btnMoveAllLeft
					[ ] locator "//WPFButton[4]"
				[+] WPFListBox lsbAvailableComponents
					[ ] locator "//WPFListBox[1]"
				[+] WPFListBox lsbSelectedComponents
					[ ] locator "//WPFListBox[2]"
			[+] WPFGroupBox grpHydrogenIonType
				[ ] locator "//WPFGroupBox[@caption='Hydrogen ion type']"
				[+] WPFRadioButton rdHydronium
					[ ] locator "//WPFRadioButton[1]"
				[+] WPFRadioButton rdHydrogen
					[ ] locator "//WPFRadioButton[2]"
			[ ] 
			[ ] 
			[ ] 
			[ ] 
		[+] window WPFWindow wDechemaDethermOnTheWeb
			[ ] locator "/WPFWindow[@caption='DECHEMA Detherm on the Web']"
			[+] WPFGroupBox grpAvailableComponents
				[ ] locator "//WPFGroupBox[@caption='Available components']"
			[+] WPFListView LstAvailableComps
				[ ] locator "//WPFListView[@automationId='lstAvailableComps']"
			[+] WPFButton BtnMove
				[ ] locator "//WPFButton[@automationId='btnMove']"
			[+] WPFButton BtnMoveAll
				[ ] locator "//WPFButton[@automationId='btnMoveAll']"
			[+] WPFButton BtnRemove
				[ ] locator "//WPFButton[@automationId='btnRemove']"
			[+] WPFButton BtnRemoveAll
				[ ] locator "//WPFButton[@automationId='btnRemoveAll']"
			[+] WPFListView LstSelectedComps
				[ ] locator "//WPFListView[@automationId='lstSelectedComps']"
			[+] WPFGroupBox PropertyToSearch
				[ ] locator "//WPFGroupBox[@caption='Property to search']"
			[+] WPFComboBox CboDethermProp
				[ ] locator "//WPFComboBox[@automationId='cboDethermProp']"
			[+] WPFButton BtnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
		[+] window WPFWindow wUserDefinedComponentWizard
			[ ] locator "/WPFWindow[@caption='User-Defined Component Wizard']"
			[+] WPFTextBox txtCompID
				[ ] locator "//WPFTextBox[@automationId='txtCompID']"
			[+] WPFComboBox cboType
				[ ] locator "//WPFComboBox[@automationId='cboType']"
			[+] WPFTextBox txtAlias
				[ ] locator "//WPFTextBox[@automationId='tbFormula']"
			[ ] 
			[+] WPFButton btnDrawStru
				[ ] locator "//WPFButton[@automationId='btnDrawStru']"
			[+] WPFGroupBox grpPropertyData
				[ ] locator "//WPFGroupBox[@automationId='grpConvProp']"
				[+] WPFTextBox txtMolecularWeight
					[ ] locator "//WPFTextBox[@automationId='txtMolecularWeight']"
				[+] WPFTextBox txtNormalBoilingPoint
					[ ] locator "//WPFTextBox[@automationId='txtNbp']"
				[+] WPFComboBox cboUnbp
					[ ] locator "//WPFComboBox[@automationId='cboUnbp']"
			[ ] 
			[+] WPFGroupBox grpBasicData
				[ ] locator "//WPFGroupBox[@automationId='GroupBox_1']"
				[+] WPFButton btn2
					[ ] locator "//WPFButton[@automationId='btnVP']"
			[+] WPFButton btnEvaluateNow
				[ ] locator "//WPFButton[@automationId='btnTDE']"
			[+] WPFButton btnNext
				[ ] locator "//WPFButton[@automationId='Button_2']"
			[+] void EvaluateNow()
				[ ] this.SetActive()
				[ ] this.btnEvaluateNow.Click()
				[ ] sleep(2)
				[ ] wNISTTDEPurePropertyEvaluation.SetActive()
				[ ] wNISTTDEPurePropertyEvaluation.btnOK.Click()
				[ ] sleep(10)
				[ ] glWaitForMouseIdle(300)
				[ ] sleep(10)
				[ ] wSaveUserInputPropertiesData.SetActive()
				[ ] wSaveUserInputPropertiesData.btnOK.Click()
		[ ] 
		[+] window WPFWindow wAliasExists
			[ ] locator "/WPFWindow[@caption='Alias Exists']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btn1']"
		[+] window WPFWindow wMoleculeEditor
			[ ] locator "/WPFWindow[@caption='*Molecule Editor']"
			[ ] 
			[+] WPFUserControl grpToolBox
				[ ] locator "//WPFUserControl[@automationId='Toolbox']"
				[+] WPFUserControl tlBenzene
					[ ] locator "//WPFUserControl[@caption='Benzene']"
			[+] WPFUserControl ucDrawingCanvas
				[ ] locator "//WPFUserControl[@automationId='UserControl_1']"
			[+] WPFButton btnOpen
				[ ] locator "//WPFButton[@automationId='Button_1']"
			[+] wcOpenDialogBox dlgOpen
				[ ] locator "//DialogBox[@caption='Open']"
			[+] void ImportMolFile(string sFile)
				[ ] this.SetActive()
				[ ] this.btnOpen.Click()
				[ ] this.dlgOpen.OpenFile(sFile)
			[ ] 
		[+] window WPFWindow wNISTTDEPurePropertyEvaluation
			[ ] locator "/WPFWindow[@caption='NIST/TDE pure property evaluation']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btn1']"
		[ ] 
		[+] window WPFWindow wSaveUserInputPropertiesData
			[ ] locator "/WPFWindow[@caption='Save User-Input Properties Data']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
		[+] window WPFWindow wEnterID
			[ ] locator "/WPFWindow[@caption='Enter ID']"
			[+] WPFTextBox txtRecordID
				[ ] locator "//WPFTextBox[@automationId='editBox']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
		[+] window WPFWindow wVaporPressureData
			[ ] locator "/WPFWindow[@caption='Vapor Pressure Data*']"
			[+] WPFTabItem tbData
				[ ] locator "//WPFTabItem[@automationId='MMTabItem_2']"
			[+] wcAPWPFComboBox cboTemp
				[ ] locator "//WPFControl[@automationId='PART_editControl'][1]"
			[+] wcAPWPFComboBox cboPL
				[ ] locator "//WPFControl[@automationId='PART_editControl'][2]"
			[+] wcAPDataGrid dgExperimentalData
				[ ] locator "//WPFControl[@automationId='PART_DataGrid']"
			[+] wcAPWPFComboBox cboUsage2
				[ ] locator "//WPFControl[@className='AesXamComboEdit'][2]"
			[ ] 
		[+] window WPFWindow wStagewizard
			[ ] locator "/WPFWindow[@caption='Stage wizard']"
			[+] wcAPWPFTextBox txtNewTotalNumberofStages
				[ ] locator "//WPFControl[@automationId='PART_editControl'][2]"
			[+] wcAPWPFComboBox cboAddStages
				[ ] locator "//WPFControl[@className='AesXamComboEdit']"
			[+] wcAPWPFTextBox txtStage
				[ ] locator "//WPFControl[@automationId='PART_editControl'][4]"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
		[+] window WPFWindow dlgStagewizard
			[ ] locator "/WPFWindow[@caption='Stage Wizard'][2]"
			[+] WPFTextBlock txbStageNotAllowedToDelete
				[ ] locator "//WPFTextBlock[@caption='You are trying to delete a stage with a product, which is not allowed in the stage wizard.']"
			[+] WPFTextBlock txbNoEnoughStagesToDelete
				[ ] locator "//WPFTextBlock[@caption='There are not enough stages to be deleted.  Please change the specification on the Stage wizard form.']"
			[+] WPFTextBlock txbFeedStageDeleteError
				[ ] locator "//WPFTextBlock[@caption='You are trying to delete a feed stage, which is not allowed in the stage wizard.']"
				[ ] 
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
	[ ] 
	[+] //Variables Definition
		[+] window WPFContentControl  wVariableDefinition
			[ ] locator "//WPFContentControl[@caption='Edit selected variable'][1]"
			[+] WPFGroupBox grpCategory
				[ ] locator "//WPFGroupBox[@caption='Category']"
				[+] WPFRadioButton rdAll
					[ ] locator "//WPFRadioButton[1]"
				[+] WPFRadioButton rdBlocks
					[ ] locator "//WPFRadioButton[4]"
				[+] WPFRadioButton rdStreams
					[ ] locator "//WPFRadioButton[6]"
				[+] WPFRadioButton rdModelUtility
					[ ] locator "//WPFRadioButton[8]"
				[+] WPFRadioButton rdPhysicalPropertyParameters
					[ ] locator "//WPFRadioButton[10]"
				[+] WPFRadioButton rdReactions
					[ ] locator "//WPFRadioButton[12]"
			[+] WPFGroupBox grpReference
				[ ] locator "//WPFGroupBox[@caption=' Reference ']"
				[ ] 
				[+] wcAPWPFComboBox cboType
					[ ] locator "//WPFControl[@automationId='PART_editControl'][1]"
				[+] wcAPWPFComboBox cboStream
					[ ] locator "//WPFControl[@automationId='PART_editControl'][2]"
				[+] wcAPWPFComboBox cboSubstream
					[ ] locator "//WPFControl[@automationId='PART_editControl'][3]"
				[+] wcAPWPFComboBox cboVariable
					[ ] locator "//WPFControl[@automationId='PART_editControl'][4]"
			[+] WPFGroupBox grpEOInput
				[ ] locator "//WPFGroupBox[@caption='EO input']"
				[+] wcAPWPFTextBox txbOpenVariable
					[ ] locator "//WPFControl[@automationId='PART_editControl'][1]"
				[+] wcAPWPFTextBox txbDescription
					[ ] locator "//WPFControl[@automationId='PART_editControl'][2]"
				[+] WPFButton btnBrowseVariable
					[ ] locator "//WPFButton[@automationId='PART_browse']"
				[ ] 
				[ ] 
			[ ] 
			[ ] 
			[ ] 
			[+] WPFComboBox cboType
				[ ] locator "//WPFComboBox[@automationId='PART_FocusSite']"
				[ ] 
			[+] wcAPWPFComboBox cboSteam
				[ ] locator "//WPFGroupBox[@caption=' Reference ']//WPFControl[@automationId='cboRowsvw_0']"
				[ ] 
			[+] wcAPWPFComboBox cboSubStream
				[ ] locator "//WPFGroupBox[@caption=' Reference ']//WPFControl[@automationId='cboRowsvw_1']"
				[ ] 
			[+] wcAPWPFComboBox cboComponent
				[ ] locator "//WPFGroupBox[@caption=' Reference ']//WPFControl[@automationId='cboRowsvw_2']"
				[ ] 
			[ ] 
			[+] WPFImage imgImage
				[ ] locator "[2]"
			[ ] 
			[+] WPFTextBlock txbVariable
				[ ] locator "WPFLabel[@caption='Variable:']/../../../WPFControl[@automationId='MMComboEdit_3']/WPFContentControl"
				[ ] 
			[ ] 
			[+] WPFButton btnClose
				[ ] locator "//WPFButton[@caption='Close']"
				[ ] 
			[+] void SelectCategory(string sCategoryName)
				[ ] this.Find("//WPFRadioButton[(@automationId='PART_RadioButton' and @caption='{sCategoryName}')]").Click()
			[+] void SelectReferenceType(string sTypeName)
				[ ] glSelectItemInComboBox(wVariableDefinition,"automationId", "PART_editControl",sTypeName,2)
			[+] void SelectReferenceBlockType(string sTypeName)
				[ ] glSelectItemInComboBox(wVariableDefinition,"automationId", "PART_editControl",sTypeName,3)
			[+] void SelectReferenceVariableType(string sVariableType)
				[ ] glSelectItemInComboBox(wVariableDefinition,"automationId", "PART_editControl",sVariableType,4)
			[+] void SelectReferenceVariableTypeDynamic(string sVariableType, int iSpecify)
				[ ] //Unlike "SelectReferenceVariableType" this function allows the user to specify the combobox
				[ ] glSelectItemInComboBox(wVariableDefinition,"automationId", "PART_editControl",sVariableType, iSpecify)
			[ ] 
			[ ] 
		[+] window WPFWindow wSearchVariables
			[ ] locator "/WPFWindow[@caption='Search Variables']"
			[+] WPFButton Button_1
				[ ] locator "@automationId='Button_1'"
			[+] WPFButton Button_2
				[ ] locator "@automationId='Button_2'"
			[+] WPFButton Button_3
				[ ] locator "@automationId='Button_3'"
			[+] WPFGroupBox GroupBox_1
				[ ] locator "@automationId='GroupBox_1'"
			[+] WPFTextBox TxtSearchCriteria
				[ ] locator "@automationId='txtSearchCriteria'"
			[+] WPFButton BtnSearch
				[ ] locator "@automationId='btnSearch'"
			[+] WPFGroupBox GroupBox_2
				[ ] locator "@automationId='GroupBox_2'"
			[+] WPFListView Lv
				[ ] locator "@automationId='lv'"
				[+] WPFListViewItem lsvPopulated
					[ ] locator "@caption='*'"
			[+] WPFColumnHeader VariableName
				[ ] locator "Variable Name"
			[+] WPFColumnHeader Description
				[ ] locator "Description"
			[+] WPFColumnHeader VariableSearchInformation
				[ ] locator "Variable Search Information"
			[ ] 
		[+] window WPFWindow wCreateNewVariable
			[ ] locator "/WPFWindow[@caption='Create new variable']"
			[ ] 
			[+] WPFTextBox txbName
				[ ] locator "//WPFTextBox[@automationId='tbText']"
				[ ] 
			[ ] 
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
				[ ] 
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
				[ ] 
			[ ] 
			[ ] 
		[+] window WPFWindow wColumnChooser
			[ ] locator "/WPFWindow[@caption='Column Chooser']"
			[+] WPFCheckBox chkSelectUnselectAll
				[ ] locator "Select(unselect) all"
			[+] WPFScrollViewer Index
				[ ] locator "Index"
			[+] WPFItemsControl ItemsControl
				[ ] locator "//WPFItemsControl"
			[+] WPFCheckBox IndexCheckBox
				[ ] locator "Index"
			[+] WPFCheckBox chkVariable
				[ ] locator "Variable"
			[+] WPFCheckBox chkValue
				[ ] locator "Value"
			[+] WPFCheckBox chkUnits
				[ ] locator "Units"
			[+] WPFCheckBox chkBaseUnits
				[ ] locator "Base Units"
			[+] WPFCheckBox PhysicalType
				[ ] locator "Physical Type"
			[+] WPFCheckBox ConnectionType
				[ ] locator "Connection Type"
			[+] WPFCheckBox chkSpecification
				[ ] locator "Specification"
			[+] WPFCheckBox LowerBound
				[ ] locator "Lower Bound"
			[+] WPFCheckBox UpperBound
				[ ] locator "Upper Bound"
			[+] WPFCheckBox StepBound
				[ ] locator "Step Bound"
			[+] WPFCheckBox InitialValue
				[ ] locator "Initial Value"
			[+] WPFCheckBox Change
				[ ] locator "Change"
			[+] WPFCheckBox InternalScale
				[ ] locator "Internal Scale"
			[+] WPFCheckBox SolverScale
				[ ] locator "Solver Scale"
			[+] WPFCheckBox SoftBoundWeight
				[ ] locator "Soft bound weight"
			[+] WPFCheckBox BoundType
				[ ] locator "Bound type"
			[+] WPFCheckBox ActiveBound
				[ ] locator "Active bound"
			[+] WPFCheckBox ShadowPrice
				[ ] locator "Shadow Price"
			[+] WPFCheckBox Marked
				[ ] locator "Marked"
			[+] WPFButton btnOK
				[ ] locator "@automationId='buttonOK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='buttonCancel'"
			[+] void SelectColumns(list of string lsColumns optional)
				[ ] this.SetActive()
				[+] if lsColumns == null
					[ ] lsColumns = {"Select(unselect) all"}
				[ ] wColumnChooser.SetActive()
				[ ] wColumnChooser.chkSelectUnselectAll.Check() //we have to SelectAll to make it possible to unselect all.
				[ ] wColumnChooser.chkSelectUnselectAll.Uncheck()//Unselect all
				[ ] string sColumn
				[+] for each sColumn in lsColumns
					[ ] window wColumn = wColumnChooser.Find("//WPFCheckBox[@caption='{sColumn}']")
					[ ] wColumn.Check()
				[ ] wColumnChooser.btnOK.Click()
				[ ] wColumnChooser.WaitForDisappearance(30)
			[ ] 
		[+] window WPFWindow wFieldChooser
			[ ] locator "/WPFWindow[@caption='Field Chooser']"
			[+] WPFContentControl FieldChooser
				[ ] locator "Field Chooser"
			[+] WPFControl FieldChooserControl
				[ ] locator "@className='FieldChooser'"
			[+] WPFListBox lstFieldsListBox
				[ ] locator "@automationId='PART_FieldsListBox'"
			[+] WPFListBoxItem lsiTemperature
				[ ] locator "Temperature Temperature"
			[+] WPFControl CheckBox
				[ ] locator "@automationId='checkBox'"
			[+] WPFCheckBox PART_FocusSite
				[ ] locator "@automationId='PART_FocusSite'"
			[+] void SelectColumns(list of string lsColumns optional)
				[ ] this.SetActive()
				[ ] list of window lw = wFieldChooser.FindAll("//WPFListBox/WPFListBoxItem")
				[ ] window wTemp
				[ ] int i
				[ ] 
				[ ] 
				[+] for i = 1 to listcount(lw)
					[+] do
						[ ] wFieldChooser.lstFieldsListBox.ScrollIntoView(i)
						[ ] wTemp = wFieldChooser.FindAll("//WPFListBox/WPFListBoxItem[{i}]//WPFCheckBox")[1]
						[+] if wTemp.IsChecked
							[ ] print(wFieldChooser.Find("//WPFListBox/WPFListBoxItem[{i}]").sCaption)
							[ ] wTemp.unCheck()
							[ ] 
					[+] except
						[+] // if exceptnum() == E_WINDOW_NOT_FOUND
							[ ] // exceptclear()
						[+] // else
							[ ] exceptlog()
				[+] if lsColumns == null
					[+] for i = 1 to listcount(lw)
						[ ] wTemp = wFieldChooser.FindAll("//WPFListBox/WPFListBoxItem[{i}]//WPFCheckBox")[1]
						[ ] wTemp.Check()
					[ ] this.Close()
					[ ] this.WaitForDisappearance(30)
					[ ] return
				[ ] string sColumn
				[+] for each sColumn in lsColumns
					[ ] window w = this.FindAll("//WPFListBoxItem[@caption='{sColumn+"*"}']")[1]
					[ ] w.Find("//WPFCheckBox").Check()
				[ ] this.Close()
				[ ] this.WaitForDisappearance(30)	
	[ ] 
	[+] //Model Library
		[+] window WPFWindow wManageLibraries
			[ ] locator "/WPFWindow[@caption='Manage Libraries']"
			[+] WPFDataGrid grdAvailableLibraries
				[ ] locator "//WPFDataGrid[@automationId='theDataGrid']"
			[+] WPFButton btnNew
				[ ] locator "//WPFButton[@automationId='buttonNew']"
			[+] WPFButton btnImport
				[ ] locator "//WPFButton[@automationId='buttonImport']"
			[+] WPFButton btnEdit
				[ ] locator "//WPFButton[@caption='Edit...']"
			[+] LibraryImport(string sFileName)
				[ ] wManageLibrariesClassic.dlgOpenUserModelLibrary.SetActive()
				[ ] wManageLibrariesClassic.dlgOpenUserModelLibrary.OpenFile(sFileName)
				[ ] 
			[+] LibraryDelete(string sLibraryName)
				[ ] list of window lwRows = this.grdAvailableLibraries.Items//FindAll("//WPFDataGridRow")
				[ ] int i, j
				[+] for(i=1; i <= listcount(lwRows); ++i)
					[ ] list of window lwCells = lwRows[i].Cells//lwRows[i].FindAll("//WPFDataGridCell")
					[+] // for(j=1; j <= listcount(lwCells); ++j) //for debug popurse
						[ ] // print(lwCells[j].sCaption)
						[ ] // print(lwCells[j].Name)
					[ ] 
					[+] if sLibraryName == lwCells[2].sCaption
						[ ] lwCells[2].Click()
						[ ] // lwRows[i].Select()
						[ ] sleep(5)
						[ ] this.TypeKeys("<Delete>")
			[+] boolean LibraryExists(string sLibraryName)
				[ ] list of window lwRows = this.grdAvailableLibraries.Items
				[ ] int i, j
				[+] for(i = 1; i <= listcount(lwRows); ++i)
					[ ] list of window lwCells = lwRows[i].Cells
					[+] // for(j=1; j <= listcount(lwCells); ++j) //for debug popurse
						[ ] // print(lwCells[j].sCaption)
						[ ] // print(lwCells[j].Name)
					[ ] 
					[+] if sLibraryName == lwCells[2].sCaption
						[ ] return true
				[ ] return false
			[+] LibraryCheck(string sLibraryName)
				[ ] list of window lwRows = this.grdAvailableLibraries.Items
				[ ] int i, j
				[+] for(i = 1; i <= listcount(lwRows); ++i)
					[ ] list of window lwCells = lwRows[i].Cells
					[+] // for(j=1; j <= listcount(lwCells); ++j) //for debug popurse
						[ ] // print(lwCells[j].sCaption)
						[ ] // print(lwCells[j].Name)
					[ ] 
					[+] if sLibraryName == lwCells[2].sCaption
						[ ] lwCells[2].Click()
						[ ] window chkInUse = lwCells[1].Find("//WPFCheckBox[@automationId='checkBoxIsInUse']")
						[ ] chkInUse.Check()
				[ ] 
			[ ] 
		[+] window WPFWindow wNewUserModelLibrary
			[ ] locator "/WPFWindow[@caption='New User Model Library']"
			[+] WPFTextBox txtDisplayName
				[ ] locator "//WPFTextBox[@automationId='theLibraryName']"
			[+] WPFTextBox txtFilePath
				[ ] locator "//WPFTextBox[@automationId='theFilePath']"
			[+] WPFButton btnCreate
				[ ] locator "//WPFButton[@automationId='buttonOK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='buttonCancel']"
		[+] window WPFWindow  wModelLibraryEditor
			[ ] locator "/WPFWindow[@caption='*Model Library Editor']"
			[+] WPFContentControl wccCategoryPanel
				[ ] locator "//WPFContentControl[@className='PaneToolWindow']"
			[+] WPFContentControl Model1
				[ ] locator "//WPFContentControl[@name='PART_OptionButton']"
			[+] WPFMenuItem miEditUserConfig
				[ ] locator "//WPFMenuItem[@caption='Edi_t User Configuration']"
			[+] WPFMenuItem miCreateNewCategory
				[ ] locator "//WPFMenuItem[@caption='_Create New Category']"
			[ ] 
		[+] window WPFWindow  wNewUserCategory
			[ ] locator "/WPFWindow[@caption='AspenPlus User Model Library']"
			[+] WPFTextBox txtNewName
				[ ] locator "//WPFTextBox[@automationId='textBoxNewName']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='buttonOK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='buttonCancel']"
		[+] window glwcMessageBox wManageLibrariesClassic
			[ ] tag "Manage Libraries"
			[ ] parent AspenPlusClassicWin
			[+] glwcDlgOpenFile dlgOpenUserModelLibrary
				[ ] tag "Open User Model Library"
			[ ] 
		[+] window WPFWindow wCustomModelTypeCreationWizard
			[ ] locator "/WPFWindow[@caption='Custom Model Type Creation Wizard']"
			[+] WPFGroupBox grpModelTypeCreationOptions
				[ ] locator "//WPFGroupBox[@automationId='GroupBox_1']"
				[+] WPFRadioButton rdAdd
					[ ] locator "//WPFRadioButton[@automationId='radionButtonAdd']"
				[+] WPFRadioButton rdAppend
					[ ] locator "//WPFRadioButton[@automationId='radionButtonAppend']"
			[+] WPFGroupBox grpAvailableLibraries
				[ ] locator "//WPFGroupBox[@automationId='GroupBox_1']"
				[+] WPFListBox lbLibraries
					[ ] locator "//WPFListBox[@automationId='theListBox']"
			[+] WPFGroupBox grpAvailableCategories
				[ ] locator "//WPFGroupBox[@automationId='GroupBox_1']"
				[+] WPFListBox lbCategories
					[ ] locator "//WPFListBox[@automationId='theListBox']"
				[ ] 
			[+] WPFGroupBox grpIconsCopyMode
				[ ] locator "//WPFGroupBox[@automationId='GroupBox_2']"
				[+] WPFRadioButton rdCopyDefault
					[ ] locator "//WPFRadioButton[@automationId='RadioButton_1']"
				[+] WPFRadioButton rdCopyCurrent
					[ ] locator "//WPFRadioButton[@automationId='RadioButton_2']"
				[+] WPFRadioButton rdCopyAll
					[ ] locator "/WPFRadioButton[@automationId='RadioButton_3']"
			[+] WPFTextBox txtModelTypeName
				[ ] locator "//WPFTextBox[@automationId='textBoxModelTypeName']"
			[+] WPFButton btnBack
				[ ] locator "//WPFButton[@automationId='Button_1']"
			[+] WPFButton btnNext
				[ ] locator "//WPFButton[@automationId='Button_2']"
			[+] WPFButton btnFinish
				[ ] locator "//WPFButton[@automationId='Button_3']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='buttonCancel']"
			[ ] 
		[+] window WPFWindow wUserModelConfigurationEditor
			[ ] locator "/WPFWindow[@caption='*User Model Configuration Editor']"
			[+] WPFDataGrid dgConfigGrid
				[ ] locator "//WPFDataGrid[@automationId='ConfigGrid']"
				[+] WPFDataGridCell firstCell
					[ ] locator "//WPFDataGridCell[2]"
				[+] void CreateVariables(int row,string sVar)
					[ ] //Create Variables for specified row.
					[ ] this.Find("//WPFDataGridRow[{row}]//WPFDataGridCell[2]").click()
					[ ] this.Find("//WPFTextBox").setText("{sVar}")
					[ ] this.TypeKeys("<Enter>")
				[+] void SpecifyInputOuput(int row,string sInputOutput)
					[ ] //Create Variables for specified row.
					[ ] sleep(1)
					[ ] int index = row*3
					[ ] print(index)
					[ ] this.Find("//WPFDataGridRow[{row}]//WPFDataGridCell[6]").doubleclick()
					[ ] this.Find("//WPFComboBox[{index}]").Select("{sInputOutput}")
				[ ] 
			[+] WPFButton btnImport
				[ ] locator "//WPFButton[@automationId='btnImport']"
			[+] WPFButton btnExport
				[ ] locator "//WPFButton[@automationId='btnExport']"
			[+] WPFButton btnSave
				[ ] locator "//WPFButton[@automationId='btnApply']"
			[+] WPFButton btnClose
				[ ] locator "//WPFButton[@automationId='btnCancel']"
			[+] wcOpenDialogBox dlgExportFortranFile
				[ ] locator "//DialogBox[@caption='Export Fortran File']"
				[+] PushButton btnSave
					[ ] locator "//PushButton[@caption='Save']"
				[+] ComboBox FileNameComboBox
					[ ] locator "//ComboBox[1]"
				[+] void Export(STRING sFile)
					[ ] this.SetActive()
					[ ] this.FileNameComboBox.SetText(sFile)
					[ ] this.btnSave.Click()
				[ ] 
		[+] window WPFWindow wPaletteCategories
			[ ] locator "/WPFWindow[@caption='Palette Categories']"
			[+] WPFDataGrid dgAvailableCategories
				[ ] locator "//WPFDataGrid[@automationId='theDataGrid']"
			[+] WPFButton btnPriorityUp
				[ ] locator "//WPFButton[@automationId='buttonUp']"
			[+] WPFButton btnPriorityDown
				[ ] locator "//WPFButton[@automationId='buttonDown']"
			[+] void MoveCategoriesToTop(string sCategory)
				[ ] this.SetActive()
				[ ] this.Find("//WPFDataGridRow[@caption='{sCategory}']").setFocus()
				[ ] this.Find("//WPFDataGridRow[@caption='{sCategory}']").Click()
				[ ] 
				[+] while this.btnPriorityUp.IsEnabled
					[ ] this.btnPriorityUp.Click()
					[ ] sleep(0.5)
					[+] if(!this.btnPriorityUp.IsEnabled)
						[ ] break
				[ ] 
			[ ] 
			[ ] 
	[ ] 
	[+] //Save File
		[+] window DialogBox dlgSaveAs
			[ ] locator "//DialogBox[@caption='Save As']"
			[+] ComboBox cboSaveAsFileName
				[ ] locator "//ComboBox[1]"
			[+] TextField txtFileName
				[ ] locator "//TextField"
			[+] ComboBox cboSaveAsType
				[ ] locator "//ComboBox[2]"
			[+] ComboBox cboEncoding
				[ ] locator "//ComboBox[@caption='Encoding:']"
			[+] PushButton btnSave
				[ ] locator "//PushButton[@caption='Save']"
			[+] PushButton btnCancel
				[ ] locator "//PushButton[@caption='Cancel']"
	[ ] 
	[+] //Exit Aspen Plus windows
		[+] window WPFWindow  wAspenPlusSaveWarning
			[ ] locator "/WPFWindow[@caption='Aspen Plus']"
			[+] WPFTextBlock BkpTxtForPlus
				[ ] locator "//WPFTextBlock[@automationId='bkpTxtForPlus']"
			[+] WPFCheckBox DoNotShowThisMessageAgain
				[ ] locator "//WPFCheckBox[@caption='Do not show this message again']"
			[+] WPFButton btnOK //Yes 
				[ ] locator "//WPFButton[@automationId='btnOk' or @automationId='Button1' or @automationId='btn1' ]"
			[+] WPFButton btnNo
				[ ] locator "//WPFButton[@automationId='btnNo' or @automationId='Button2' or @automationId='btn1']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
	[ ] 
	[+] //Common windows
		[+] window WPFWindow wDataRegressionErrors
			[ ] locator "/WPFWindow[@caption='Data Regression Errors']"
		[+] window WPFWindow wWarning
			[ ] locator "/WPFWindow[@caption='Warning']"
			[+] WPFButton btnYes
				[ ] locator "//WPFButton[@caption='*Yes' or @automationId='btn0']"
			[+] WPFButton btnNo
				[ ] locator "//WPFButton[@caption='*No']"
				[ ] 
			[ ] 
		[+] window WPFWindow wAspenProperties
			[ ] locator "/WPFWindow[@caption='Aspen Properties']"
			[+] WPFImage HeaderImage
				[ ] locator "@automationId='HeaderImage'"
			[+] WPFTextBlock TxtBlock
				[ ] locator "//WPFTextBlock[1]"
			[+] WPFButton BtnYes
				[ ] locator "//WPFButton[@caption='*Yes']"
			[+] WPFButton BtnNo
				[ ] locator "//WPFButton[@caption='*No']"
			[+] WPFButton BtnCancel
				[ ] locator  "//WPFButton[@caption='*Cancel]"
			[+] WPFButton BtnOK
				[ ] locator "//WPFButton[@caption='*OK']"
			[+] WPFButton BtnCancelfor2buttonwin
				[ ] locator "@automationId='btn1'"
			[+] WPFLabel txtWriteAccess
				[ ] locator "//WPFLabel[@caption='You do not have write access*']"
				[ ] 
			[+] WPFCheckBox chkDontAsk
				[ ] locator "//WPFCheckBox[@caption='Don*t ask*']"
			[+] WPFTextBox txbEnterID
				[ ] locator "//WPFTextBox[@automationId='tbText']"
			[ ] 
			[ ] 
		[+] window WPFWindow  wConfirm
			[ ] locator "/WPFWindow[@caption='Confirm']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btn1']"
			[ ] 
		[ ] 
		[+] window DialogBox dlgAspenPlus1
			[ ] locator "//DialogBox[@caption='Aspen Plus']"
			[+] property btnYes
				[+] window Get()
					[+] if this.btnYs.Exists()
						[ ] return this.btnYs
					[+] if this.btnOK.Exists()
						[ ] return this.btnOK
			[+] PushButton btnYs
				[ ] locator "//PushButton[@caption='Yes']"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@caption='OK']"
			[+] PushButton btnNo
				[ ] locator "//PushButton[@caption='No']"
			[+] PushButton btnCancel
				[ ] locator "//PushButton[@caption='Cancel']"
		[ ] 
		[ ] 
		[+] window WPFWindow dlgAspenPlus
			[ ] locator "/WPFWindow[@caption='Aspen Plus']"
			[+] WPFLabel txtWriteAccess
				[ ] locator "//WPFLabel[@caption='You do not have write access*']"
				[ ] 
			[+] WPFCheckBox chkDontAsk
				[ ] locator "//WPFCheckBox[@automationId='CheckBox_1']"
			[+] WPFImage HeaderImage
				[ ] locator "@automationId='HeaderImage'"
			[+] WPFTextBlock TxtBlock
				[ ] locator "@automationId='TxtBlock'"
			[+] WPFButton BtnYes
				[ ] locator "@automationId='btn0'"
			[+] WPFButton BtnNo
				[ ] locator "@automationId='btn1' or @automationId='btnNo'"
			[+] WPFButton BtnCancel
				[ ] locator  "@automationId='btn2 or @automationId='Button2'"
			[+] WPFButton BtnOK
				[ ] locator  "//WPFButton[@caption='*OK' or @automationId='Button1']"
			[ ] 
		[+] window WPFWindow wCreateNewId
			[ ] locator "/WPFWindow[@caption='Create New ID']"
			[+] WPFTextBlock txtBlkPrompt
				[ ] locator "//WPFTextBlock[@automationId='textBlkPrompt']"
			[+] WPFTextBox TxbText
				[ ] locator "//WPFTextBox[@automationId='tbText']"
			[+] WPFComboBox cboType
				[ ] locator "//WPFComboBox[@automationId='cbRecord']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
		[+] window WPFWindow wNew
			[ ] locator "/WPFWindow[@caption='New']"
			[+] WPFListBox lstCategories
				[ ] locator "//WPFListBox[@automationId='listBoxCategories']"
			[+] WPFListBoxItem lsiBlankAndRecent
				[ ] locator "//WPFListBoxItem[@caption='Blank and Recent']"
			[+] WPFListBoxItem lsiMyTemplates
				[ ] locator "//WPFListBoxItem[@caption='My Templates...']"
			[+] WPFListBoxItem lsiInstalledTemplates
				[ ] locator "//WPFListBoxItem[@caption='Installed Templates']"
			[+] WPFListBoxItem lsiAirSeparation
				[ ] locator "//WPFListBoxItem[@caption='Air Separation']"
			[+] WPFListBoxItem lsiChemicalProcesses
				[ ] locator "//WPFListBoxItem[@caption='Chemical Processes']"
			[+] WPFListBoxItem lsiElectrolytes
				[ ] locator "//WPFListBoxItem[@caption='Electrolytes']"
			[+] WPFListBoxItem lsiGasProcessing
				[ ] locator "//WPFListBoxItem[@caption='Gas Processing']"
			[+] WPFListBoxItem lsiMetallurgy
				[ ] locator "//WPFListBoxItem[@caption='Metallurgy']"
			[+] WPFListBoxItem lsiPharmaceutical
				[ ] locator "//WPFListBoxItem[@caption='Pharmaceutical']"
			[+] WPFListBoxItem lsiPolymers
				[ ] locator "//WPFListBoxItem[@caption='Polymers']"
			[+] WPFListBoxItem lsiRefinery
				[ ] locator "//WPFListBoxItem[@caption='Refinery']"
			[+] WPFListBoxItem lsiSolids
				[ ] locator "//WPFListBoxItem[@caption='Solids']"
			[+] WPFTextBlock txtBlankAndRecent
				[ ] locator "//WPFTextBlock[@caption='Blank and Recent']"
			[+] WPFListBox lstBlankAndRecent
				[ ] // locator "//WPFListBox[2]"
				[ ] locator "//WPFListBox[@automationId='ListBox_1']"
				[+] WPFListBoxItem lsiBlankSimulation
					[ ] locator "//WPFListBoxItem[@caption='Blank Simulation']"
				[+] WPFListBoxItem lsiBlankCase
					[ ] locator "//WPFListBoxItem[@caption='Blank Case']"
					[ ] 
				[ ] 
			[+] WPFListBox lstRecentlySelectedTemplates
				[ ] locator "//WPFListBox[3]"
			[+] WPFGroupBox Preview
				[ ] locator "//WPFGroupBox[@caption='Preview']"
			[+] WPFScrollViewer ScrollViewer
				[ ] locator "//WPFScrollViewer"
			[+] WPFButton BtnCreate
				[ ] locator "//WPFButton[@automationId='btnCreate']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
		[+] window WPFWindow  wOverrideConsistencyCheck
			[ ] locator "/WPFWindow[@caption='Override Consistency Check?']"
			[+] WPFButton btnYes
				[ ] locator "//WPFButton[@automationId='btn0']"
				[ ] 
			[+] WPFButton btnNo
				[ ] locator "//WPFButton[@automationId='btn1']"
				[ ] 
			[ ] 
			[ ] 
		[+] window FormsWindow  wReconcileSectionIDs
			[ ] locator "/FormsWindow[@caption='Reconcile Section IDs']"
			[+] PushButton CmdGenerate
				[ ] locator "//PushButton[@automationId='cmdGenerate']"
			[+] PushButton CmdHelp
				[ ] locator "@automationId='cmdHelp'"
			[+] Group FraOption
				[ ] locator "@automationId='fraOption'"
			[+] RadioList OptIgnore
				[ ] locator "@automationId='optIgnore'"
			[+] RadioList OptOverride
				[ ] locator "@automationId='optOverride'"
			[+] PageList MstTheTab
				[ ] locator "@automationId='mstTheTab'"
			[+] Group _mstTheTab_TabPage0
				[ ] locator "@automationId='_mstTheTab_TabPage0'"
			[+] Group FraSecID
				[ ] locator "@automationId='fraSecID'"
			[+] TextField TxtSectionID
				[ ] locator "//TextField[@automationId='txtEdit']"
			[+] Control MhfSecID
				[ ] locator "//Control[@automationId='mhfSecID']"
			[+] PushButton btnCancel
				[ ] locator "//PushButton[@automationId='cmdCancel']"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@automationId='cmdOK']"
		[+] window WPFWindow wGenerateEstimatesFromAvailable
			[ ] locator "/WPFWindow[@caption='Generate estimates from available results']"
			[+] WPFContentControl MMTabPage_1
				[ ] locator "@automationId='MMTabPage_1'"
			[+] WPFControl MMGroupBox_1
				[ ] locator "@automationId='MMGroupBox_1'"
			[+] WPFContentControl GenerateEstimatesFor
				[ ] locator "[@caption='Generate estimates for'][2]"
			[+] WPFGroupBox GenerateEstimatesForGroupBox
				[ ] locator "Generate estimates for"
			[+] WPFControl MMCheckBox_1
				[ ] locator "@automationId='MMCheckBox_1'"
			[+] WPFContentControl Temperature
				[ ] locator "[@caption='Temperature'][1]"
			[+] WPFCheckBox chkTemperature
				[ ] locator "[@automationId='PART_CheckBox'][1]"
			[+] WPFLabel TemperatureLabel
				[ ] locator "Temperature"
			[+] WPFControl MMCheckBox_2
				[ ] locator "@automationId='MMCheckBox_2'"
			[+] WPFContentControl LiquidAndVaporMoleFlows
				[ ] locator "[@caption='Liquid and vapor mole flows'][1]"
			[+] WPFCheckBox chkLiquidAndVaporMoleFlows
				[ ] locator "[@automationId='PART_CheckBox'][2]"
			[+] WPFLabel LiquidAndVaporMoleFlowsLabel
				[ ] locator "Liquid and vapor mole flows"
			[+] WPFControl MMCheckBox_3
				[ ] locator "@automationId='MMCheckBox_3'"
			[+] WPFContentControl LiquidAndVaporComponentMoleFra
				[ ] locator "[@caption='Liquid and vapor component mole fractions'][1]"
			[+] WPFCheckBox chkLiquidAndVaporComponentMoleFra
				[ ] locator "[@automationId='PART_CheckBox'][3]"
			[+] WPFLabel LiquidAndVaporComponentMoleFraLabel
				[ ] locator "Liquid and vapor component mole fractions"
			[+] WPFControl MMOptionGroup_1
				[ ] locator "@automationId='MMOptionGroup_1'"
			[+] WPFContentControl GenerateEstimatesForStages
				[ ] locator "[@caption='Generate estimates for stages'][1]"
			[+] WPFControl AesGroupBox
				[ ] locator "@className='AesGroupBox'"
			[+] WPFContentControl GenerateEstimatesForStages2
				[ ] locator "[@caption='Generate estimates for stages'][2]"
			[+] WPFGroupBox GenerateEstimatesForStagesGroupBox
				[ ] locator "Generate estimates for stages"
			[+] WPFRadioButton MMOptionButton_1
				[ ] locator "@automationId='MMOptionButton_1'"
			[+] WPFRadioButton PART_RadioButton
				[ ] locator "(@automationId='PART_RadioButton' and @caption='Currently specified stages')"
			[+] WPFRadioButton MMOptionButton_2
				[ ] locator "@automationId='MMOptionButton_2'"
			[+] WPFRadioButton rbAllStagesforOthers
				[ ] locator "//WPFRadioButton[(@automationId='PART_RadioButton' and @caption='All stages for*')]"
				[ ] // locator "(@automationId='PART_RadioButton' and @caption='All stages for temperatures and flows;     Feed and product locations for compositions')"
			[+] WPFRadioButton MMOptionButton_3
				[ ] locator "@automationId='MMOptionButton_3'"
			[+] WPFRadioButton rbAllStages
				[ ] locator "(@automationId='PART_RadioButton' and @caption='All stages')"
			[+] WPFControl MMGroupBox_2
				[ ] locator "@automationId='MMGroupBox_2'"
			[+] WPFContentControl PrecisionOfEstimates
				[ ] locator "[@caption='Precision of estimates'][1]"
			[+] WPFGroupBox PrecisionOfEstimatesGroupBox
				[ ] locator "Precision of estimates"
			[+] WPFControl MMCheckBox_4
				[ ] locator "@automationId='MMCheckBox_4'"
			[+] WPFContentControl KeepAllAvailableDigits 
				[ ] locator "[@caption='Keep all available digits'][1]"
			[+] WPFCheckBox chkKeepAllAvailableDigits
				[ ] locator "//WPFGroupBox[@caption='Precision of estimates']//WPFCheckBox[@automationId='PART_CheckBox']"
			[+] WPFLabel KeepAllAvailableDigitsLabel
				[ ] locator "Keep all available digits"
			[+] WPFControl MMCmdButton_1
				[ ] locator "@automationId='MMCmdButton_1'"
			[+] WPFContentControl Generate
				[ ] locator "[@caption='Generate'][1]"
			[+] WPFButton btnGenerate
				[ ] locator "Generate"
			[+] WPFControl MMCmdButton_2
				[ ] locator "@automationId='MMCmdButton_2'"
			[+] WPFContentControl Cancel
				[ ] locator "[@caption='Cancel'][1]"
			[+] WPFButton CancelButton
				[ ] locator "Cancel"
		[+] window WPFWindow wAccessingData
			[ ] locator "/WPFWindow[@caption='Accessing Data ...']"
		[+] window WPFWindow wFindObject
			[ ] locator "/WPFWindow[@caption='Find Object']"
			[+] WPFTreeView trvHierarchy
				[ ] locator "//WPFTreeView[@automationId='HierarchyTreeView']"
			[+] WPFTreeViewItem Plant
				[ ] locator "//WPFTreeViewItem[@caption='Plant']"
			[+] WPFListBox lstBlocks
				[ ] locator "//WPFListBox[@automationId='BlocksListBox']"
			[+] WPFListBox lstStreams
				[ ] locator "//WPFListBox[@automationId='StreamsListBox']"
			[+] WPFCheckBox chkSubHierarchies
				[ ] locator "//WPFCheckBox[@automationId='SubHierarchiesCheckBox']"
			[+] WPFCheckBox chkCenterView
				[ ] locator "//WPFCheckBox[@automationId='CenterViewCheckBox']"
			[+] WPFCheckBox chkZoomView
				[ ] locator "//WPFCheckBox[@automationId='ZoomViewCheckBox']"
			[+] WPFComboBox cboBlockFilter
				[ ] locator "//WPFComboBox[@automationId='BlockFilterComboBox']"
			[+] WPFComboBox cboStreamFilter
				[ ] locator "//WPFComboBox[@automationId='StreamFilterComboBox']"
			[+] WPFButton btnApplyFilters
				[ ] locator "//WPFButton[@automationId='ApplyFiltersButton']"
			[+] WPFButton btnFind
				[ ] locator "//WPFButton[@automationId='FindButton']"
			[+] WPFButton btnClose
				[ ] locator "//WPFButton[@automationId='CloseButton']"
			[ ] 
			[+] WPFTextBox tbSearch
				[ ] locator "//WPFTextBox[@automationId='SearchTextBoxItem']"
			[ ] 
		[+] window WPFWindow wMoveSelectionTo
			[ ] locator "/WPFWindow[@caption='Move Selection To']"
			[+] WPFButton btnOK
				[ ] locator "@automationId='button1'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='button2'"
			[+] WPFRadioButton RdCreateNewHierachy
				[ ] locator "@automationId='Rd1'"
			[+] WPFTextBox txtNewHierachy
				[ ] locator "@automationId='text1'"
			[+] WPFRadioButton RdMoveToHierachy
				[ ] locator "@automationId='Rd2'"
			[+] WPFRadioButton RdExtractHierachyContentsAndDelete
				[ ] locator "@automationId='Rd3'"
			[+] WPFComboBox cboMoveToHierach
				[ ] locator "@automationId='Combox1'"
				[+] void Select(string sItemName)
					[ ] this.Open()
					[ ] sleep(0.5)
					[ ] //this.Find("//WPFTreeViewItem[@caption='{sItemName}']").Click()
					[ ] this.Find("//WPFTreeView[@automationId='tree1']").Select(sItemName)
			[+] WPFComboBoxItem ComboBoxItem_1
				[ ] locator "@automationId='ComboBoxItem_1'"
			[+] WPFCheckBox chkShowAdvancedSelection
				[ ] locator "@automationId='check1'"
		[+] window WPFWindow wAdvancedMoveSelection
			[ ] locator "/WPFWindow[@caption='Advanced Move Selection']"
			[+] WPFTreeView trvTheTreeView
				[ ] locator "@automationId='theTreeView'"
			[+] WPFTreeViewItem Plant
				[ ] locator "Plant"
			[+] WPFCheckBox PlantCheckBox
				[ ] locator "Plant"
			[+] WPFTreeViewItem Setup
				[ ] locator "Setup"
			[+] WPFCheckBox SetupCheckBox
				[ ] locator "Setup"
			[+] WPFTreeViewItem Properties
				[ ] locator "Properties"
			[+] WPFCheckBox PropertiesCheckBox
				[ ] locator "Properties"
			[+] WPFTreeViewItem Flowsheet
				[ ] locator "Flowsheet"
			[+] WPFCheckBox FlowsheetCheckBox
				[ ] locator "Flowsheet"
			[+] WPFTreeViewItem Section
				[ ] locator "Section"
			[+] WPFCheckBox SectionCheckBox
				[ ] locator "Section"
			[+] WPFTreeViewItem GLOBAL
				[ ] locator "GLOBAL"
			[+] WPFCheckBox GLOBALCheckBox
				[ ] locator "GLOBAL"
			[+] WPFTreeViewItem DefStreams
				[ ] locator "Def-Streams"
			[+] WPFCheckBox DefStreamsCheckBox
				[ ] locator "Def-Streams"
			[+] WPFTreeViewItem CustomForms
				[ ] locator "Custom Forms"
			[+] WPFCheckBox CustomFormsCheckBox
				[ ] locator "Custom Forms"
			[+] WPFTreeViewItem Streams
				[ ] locator "Streams"
			[+] WPFCheckBox StreamsCheckBox
				[ ] locator "Streams"
			[+] WPFTreeViewItem Blocks
				[ ] locator "Blocks"
			[+] WPFCheckBox BlocksCheckBox
				[ ] locator "Blocks"
			[+] WPFTreeViewItem CDUPetroFrac
				[ ] locator "CDU (PetroFrac)"
			[+] WPFCheckBox CDUPetroFracCheckBox
				[ ] locator "CDU (PetroFrac)"
			[+] WPFTreeViewItem PREFLASHPetroFrac
				[ ] locator "PREFLASH (PetroFrac)"
			[+] WPFCheckBox PREFLASHPetroFracCheckBox
				[ ] locator "PREFLASH (PetroFrac)"
			[+] WPFTreeViewItem VDUPetroFrac
				[ ] locator "VDU (PetroFrac)"
			[+] WPFCheckBox VDUPetroFracCheckBox
				[ ] locator "VDU (PetroFrac)"
			[+] WPFTreeViewItem Convergence
				[ ] locator "Convergence"
			[+] WPFCheckBox ConvergenceCheckBox
				[ ] locator "Convergence"
			[+] WPFTreeViewItem Costing
				[ ] locator "Costing"
			[+] WPFCheckBox CostingCheckBox
				[ ] locator "Costing"
			[+] WPFTreeViewItem FlowsheetingOptions
				[ ] locator "Flowsheeting Options"
			[+] WPFCheckBox FlowsheetingOptionsCheckBox
				[ ] locator "Flowsheeting Options"
			[+] WPFTreeViewItem ModelAnalysisTools
				[ ] locator "Model Analysis Tools"
			[+] WPFCheckBox ModelAnalysisToolsCheckBox
				[ ] locator "Model Analysis Tools"
			[+] WPFTreeViewItem EOConfiguration
				[ ] locator "EO Configuration"
			[+] WPFCheckBox EOConfigurationCheckBox
				[ ] locator "EO Configuration"
			[+] WPFCheckBox CheckHideDisabled
				[ ] locator "@automationId='checkHideDisabled'"
			[+] WPFCheckBox chkSpecGroups
				[ ] locator "//WPFCheckBox[@caption='Spec Groups']"
			[+] WPFButton btnOK
				[ ] locator "@automationId='Button_1'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Button_2'"
		[+] window WPFWindow 	wDefineSpecGroups
			[ ] locator "//WPFWindow[@caption='Define Spec Groups']"
			[+] wcAPWPFTextBox txtDescription
				[ ] locator "//WPFControl[@automationId='Part_editControl'][2]"
			[+] WPFCheckBox chkEnable
				[ ] locator "//WPFCheckBox[@automationId='PART_CheckBox']"
				[ ] 
			[+] WPFButton btnBrowseVariables
				[ ] locator "//WPFButton[@automationId='PART_browse'][1]"
			[+] WPFButton btnClose
				[ ] locator "//WPFButton[@caption='Close']"
			[+] WPFItemsControl dgEOVars
				[ ] locator "//WPFItemsControl[@className='RecordListControl']"
			[ ] 
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
				[ ] // EOVariables.Find("//WPFListViewItem[@caption='{sVariableName}']").Click()
				[ ] EOVariables.Find("//WPFContentControl[@caption='{sVariableName}']").Click()
				[ ] sleep(0.5)
				[ ] EOVariables.ButtonSelect.Click()
				[ ] 
		[+] window WPFWindow EOVariables
			[ ] locator "/WPFWindow[@caption='EO Variables']"
			[+] WPFButton ButtonCancel
				[ ] locator "@automationId='buttonCancel'"
			[+] WPFButton ButtonQuery
				[ ] locator "@automationId='buttonQuery'"
			[+] WPFButton ButtonSelect
				[ ] locator "@automationId='buttonSelect'"
			[+] WPFContentControl wccVariableLabel
				[ ] locator "//WPFContentControl[@caption='Variable'][3]"
			[ ] //WPFContextMenu cmu ContextMenu
			[+] WPFMenuItem  miShowFilterRecord
				[ ] locator "//WPFMenuItem[@caption='Sho_w Filter Record']"
			[+] WPFControl  VariableInput
				[ ] locator "//WPFControl[@className='XamComboEditor'][1]"
			[+] WPFComboBox VariableInputField
				[ ] locator "//WPFComboBox[@automationId='PART_FocusSite']"
			[+] WPFToggleButton btnDropDown
				[ ] locator "//WPFToggleButton[@automationId='PART_DropDownButton']"
			[+] WPFTreeView	trvLookIn
				[ ] locator "//WPFTreeView[@automationId='TreeView_1']"
			[+] WPFToggleButton	btnUnitFilter
				[ ] locator "//WPFToggleButton[@automationId='FilterButton'][3]"
			[+] WPFToggleButton	btnPhysicalTypeFilter
				[ ] locator "//WPFToggleButton[@automationId='FilterButton'][4]"
			[+] WPFComboBox	cboFilter
				[ ] locator "//WPFComboBox[@automationId='PART_FocusSite']"
			[+] WPFContentControl	ColVariables
				[ ] locator "//WPFContentControl[@caption='Variable'][3]"
			[+] wcAPDataGrid dgVars
				[ ]  locator "//WPFControl[@automationId='PART_XamDataGrid']"
			[+] WPFButton	btnQuery
				[ ] locator "//WPFButton[@automationId='buttonQuery']"
			[ ] 
		[+] window WPFWindow wEnterQuery
			[ ] locator "/WPFWindow[@caption='Enter Query...']"
			[+] WPFTextBox txtMainTextBox
				[ ] locator "//WPFTextBox[@automationId='textBoxQuery']"
			[+] WPFTextBox txtValue
				[ ] locator "//WPFTextBox[@automationId='textBoxRightText']"
			[+] WPFButton btnAddCondition
				[ ] locator "//WPFButton[@automationId='buttonAddCondition']"
			[+] WPFButton btnClear
				[ ] locator "//WPFButton[@automationId='buttonClear']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='buttonOK']"
				[ ] 
			[+] WPFButton btnOr
				[ ] locator "//WPFButton[@automationId='buttonConditionOr']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='buttonCancel']"
			[+] WPFTextBox txtObjectiveFunction
				[ ] locator "//WPFTextBox[@automationId='TextBox_1']"
			[+] WPFRadioButton rdChooseCondition
				[ ] locator "//WPFRadioButton[@automationId='RadioButton_1']"
			[+] WPFRadioButton rdMatchVariablesWithModifiedAttribute
				[ ] locator "//WPFRadioButton[@automationId='RadioButton_2']"
			[+] WPFRadioButton rdMatchVariablesInObjectiveFunction
				[ ] locator "//WPFRadioButton[@automationId='RadioButton_3']"
			[+] WPFComboBox cboConditionValue
				[ ] locator "//WPFComboBox[@automationId='comboBoxOperatorRightItem']"
			[+] WPFComboBox cboConditionType
				[ ] locator "//WPFComboBox[@automationId='comboBoxVariable']"
				[ ] 
				[ ] 
			[+] WPFMenuItem       miExportAPR
				[ ] locator "//WPFMenuItem[@caption='Export'][2]"
			[+] WPFButton btnAnd
				[ ] locator "//WPFButton[@automationId='buttonConditionAnd']"
				[ ] 
			[ ] 
		[+] window WPFWindow dlgAspenPlusOKOrCancel
			[ ] locator "/WPFWindow[@caption='Aspen Plus']"
			[+] WPFImage HeaderImage
				[ ] locator "//WPFImage[@automationId='HeaderImage']"
			[+] WPFTextBlock TxtBlock
				[ ] locator "//WPFTextBlock[@automationId='TxtBlock']"
			[+] WPFButton BtnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='btn1']"
		[+] window WPFWindow dlgAspenPlusYesOrNo
			[ ] locator "/WPFWindow[@caption='Aspen Plus' or @caption='Aspen Properties']"
			[+] WPFButton btnYes
				[ ] locator "//WPFButton[@automationId='btnYes' or @automationId='btn0']"
			[+] WPFButton btnNo
				[ ] locator "//WPFButton[@automationId='btnNo' or @automationId='btn1']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel' or @automationId='btn02' or @automationId='btn2']"
		[+] window WPFWindow wAspenPlus
			[ ] locator "/WPFWindow[@caption='Aspen Plus']"
			[+] WPFImage HeaderImage
				[ ] locator "@automationId='HeaderImage'"
			[+] WPFTextBlock TxtBlock
				[ ] locator "@automationId='TxtBlock' or @automationId='TextBlock_1'"
			[+] WPFTextBox txbEnterID
				[ ] locator "//WPFTextBox[@automationId='tbText']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='*OK*']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='*Cancel*']"
			[+] WPFButton btnYes
				[ ] locator "//WPFButton[@caption='*Yes*']"
			[+] WPFButton btnNo
				[ ] locator "//WPFButton[@caption='*No*']"
			[ ] 
			[ ] 
		[+] window WPFWindow wParameterValues
			[ ] locator "/WPFWindow[@caption='Parameter Values']"
			[+] WPFTextBlock ValueOfParameterWILSONAlreadyE
				[ ] locator "Value of parameter WILSON already exists for components ETOAC ETHANOL on the Parameters form. You can choose to replace it with the regressed results from DRS.{chr(10)}{chr(10)}Choose the ""Yes to all"" option to replace existing parameters with the regressed value(s) in all subsequent cases{chr(10)}"
			[+] WPFButton BtnYes
				[ ] locator "@automationId='btn0'"
			[+] WPFButton BtnNo
				[ ] locator "@automationId='btn1'"
			[+] WPFButton BtnYesToAll
				[ ] locator "@automationId='btn2'"
			[+] WPFButton BtnNoToAll
				[ ] locator "@automationId='btn3'"
		[+] window WPFWindow wAssistantPropertyMethodSelection
			[ ] locator "/WPFWindow[@caption='Assistant - Property method selection']"
			[+] WPFButton btnAbout
				[ ] locator "About…"
			[+] WPFButton btnReport
				[ ] locator "Report…"
			[+] WPFButton btnBack
				[ ] locator "[3]"
			[+] WPFButton btnNext 
				[ ] locator "Property method selection{chr(13)}{chr(10)}Getting started"
				[ ] //locator "[4]" 
			[+] WPFButton btnClose
				[ ] locator "Close"
			[+] DomLink btnSpecifyComponentType
				[ ] locator "//BrowserWindow//A[1]"
			[+] DomLink btnSpecifyProcessType
				[ ] locator "//BrowserWindow//A[@textContents='Specify process type']"
			[+] DomLink btnSpecial
				[ ] locator "//BrowserWindow//A[3]"
			[+] DomLink btnElectrolyteSystem
				[ ] locator "//BrowserWindow//A[@textContents='Electrolyte system']"
			[+] DomLink btnElectrolytePropertyMethods
				[ ] locator "//BrowserWindow//A[@href='assist:/ELEC/HELEC']"
			[+] DomLink btnOilAndGas
				[ ] locator "//BrowserWindow//A[@textContents='Oil and gas']"
		[ ] 
		[+] window WPFWindow wStopPointsManager
			[ ] locator "/WPFWindow[@caption='Stop Points Manager']"
			[+] WPFLabel ChooseTypeOfBlock
				[ ] locator "//WPFLabel[@caption='Choose type of block:']"
			[+] WPFComboBox cboChooseTypeOfBlock
				[ ] locator "//WPFComboBox"
			[+] WPFComboBoxItem cboiBlock
				[ ] locator "//WPFComboBoxItem[@caption='Block']"
			[+] WPFComboBoxItem cboiConvergence
				[ ] locator "//WPFComboBoxItem[@caption='Convergence']"
			[+] WPFComboBoxItem cboiSensitivity
				[ ] locator "//WPFComboBoxItem[@caption='Sensitivity']"
			[+] WPFComboBoxItem cboiTransfer
				[ ] locator "//WPFComboBoxItem[@caption='Transfer']"
			[+] WPFComboBoxItem cboiCalculator
				[ ] locator "//WPFComboBoxItem[@caption='Calculator']"
			[+] WPFComboBoxItem cboiUtilities
				[ ] locator "//WPFComboBoxItem[@caption='Utilities']"
			[+] WPFComboBoxItem cboiBalance
				[ ] locator "//WPFComboBoxItem[@caption='Balance']"
			[+] WPFComboBoxItem cboiPressureRelief
				[ ] locator "//WPFComboBoxItem[@caption='Pressure Relief']"
			[+] WPFComboBoxItem cboiRegression
				[ ] locator "//WPFComboBoxItem[@caption='Regression']"
			[+] WPFComboBoxItem cboiMeasurement
				[ ] locator "//WPFComboBoxItem[@caption='Measurement']"
			[+] WPFGroupBox BlockIDs
				[ ] locator "//WPFGroupBox[@caption='Block IDs']"
			[+] WPFTreeView TreeView
				[ ] locator "//WPFTreeView"
			[+] WPFTreeViewItem B1
				[ ] locator "//WPFTreeViewItem[@caption='B1']"
			[+] WPFImage Image
				[ ] locator "//WPFImage[1]"
			[+] WPFTextBlock B1TextBlock
				[ ] locator "//WPFTextBlock[@caption='B1']"
			[+] WPFTreeViewItem B2
				[ ] locator "//WPFTreeViewItem[@caption='B2']"
			[+] WPFImage Image2
				[ ] locator "//WPFImage[2]"
			[+] WPFTextBlock B2TextBlock
				[ ] locator "//WPFTextBlock[@caption='B2']"
			[+] WPFTreeViewItem B3
				[ ] locator "//WPFTreeViewItem[@caption='B3']"
			[+] WPFImage Image3
				[ ] locator "//WPFImage[3]"
			[+] WPFTextBlock B3TextBlock
				[ ] locator "//WPFTextBlock[@caption='B3']"
			[+] WPFTreeViewItem B4
				[ ] locator "//WPFTreeViewItem[@caption='B4']"
			[+] WPFImage Image4
				[ ] locator "//WPFImage[4]"
			[+] WPFTextBlock B4TextBlock
				[ ] locator "//WPFTextBlock[@caption='B4']"
			[+] WPFTreeViewItem B5
				[ ] locator "//WPFTreeViewItem[@caption='B5']"
			[+] WPFImage Image5
				[ ] locator "//WPFImage[5]"
			[+] WPFTextBlock B5TextBlock
				[ ] locator "//WPFTextBlock[@caption='B5']"
			[+] WPFTreeViewItem B6
				[ ] locator "//WPFTreeViewItem[@caption='B6']"
			[+] WPFImage Image6
				[ ] locator "//WPFImage[6]"
			[+] WPFTextBlock B6TextBlock
				[ ] locator "//WPFTextBlock[@caption='B6']"
			[+] WPFButton btnStopBefore
				[ ] locator "//WPFButton[@caption='Stop before']"
			[+] WPFButton btnStopAfter
				[ ] locator "//WPFButton[@caption='Stop after']"
			[+] WPFGroupBox StopPoints
				[ ] locator "//WPFGroupBox[@caption='Stop Points']"
			[+] WPFListBox LvPointList
				[ ] locator "//WPFListBox[@automationId='lvPointList']"
			[+] WPFButton btnRemove
				[ ] locator "//WPFButton[@caption='Remove']"
			[+] WPFButton btnClear
				[ ] locator "//WPFButton[@caption='Clear']"
			[+] WPFButton btnOk
				[ ] locator "//WPFButton[@caption='OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
			[+] WPFButton btnHelp
				[ ] locator "//WPFButton[@automationId='Help']"
		[ ] window wcSelectCompilerforAspen wSelectCompilerforAspen
		[+] window WPFHeaderedContentControl wTdeEvaluateResult
			[ ] locator "//WPFHeaderedContentControl[@automationId='TdeEvaluateResultScreenFactory']"
			[+] WPFContentControl PaneToolWindow
				[ ] locator "//WPFContentControl[@className='PaneToolWindow']"
			[+] WPFHeaderedContentControl TdeEvaluateResultScreenFactory
				[ ] locator "//WPFHeaderedContentControl[@automationId='TdeEvaluateResultScreenFactory']"
			[+] WPFContentControl TDEResultPageView
				[ ] locator "//WPFContentControl[@automationId='TDEResultPageView']"
			[+] WPFGroupBox GBPurePropList
				[ ] locator "//WPFGroupBox[@automationId='GBPurePropList']"
			[+] WPFListBox lstPurePropList
				[ ] locator "WPFListBox[@automationId='PurePropList']"
				[+] WPFListBoxItem lstiAll
					[ ] locator "//WPFListBoxItem[@caption='All']"
				[+] WPFListBoxItem lstiHeatCapacity_IdealGas
					[ ] locator "//WPFListBoxItem[@caption='Heat capacity (Ideal gas )']"
				[+] WPFListBoxItem lstiHeatCapacity_LiquidVSGas
					[ ] locator "//WPFListBoxItem[@caption='Heat capacity (Liquid vs. Gas )']"
			[+] WPFGridSplitter GridSplitter
				[ ] locator "//WPFGridSplitter"
			[+] WPFControl MMTabStrip
				[ ] locator "//WPFControl[@className='MMTabStrip']"
			[+] WPFTabControl PartTabControl
				[ ] locator "//WPFTabControl[@automationId='PART_TabControl']"
			[+] WPFControl ctlPartDataGrid
				[ ] locator "//WPFControl[@automationId='PART_DataGrid']"
			[+] WPFTabItem tiExperimentalData
				[ ] locator "//WPFTabItem[@automationId='PureTabData']"
			[+] WPFTabItem tiEvaluatedResults
				[ ] locator "//WPFTabItem[@automationId='PureTabResult']"
			[+] WPFTabItem tiParameters
				[ ] locator "//WPFTabItem[@automationId='PureTabPara']"
			[+] WPFButton BtnReevaluate
				[ ] locator "//WPFButton[@automationId='btnRevPure']"
			[+] WPFButton BtnSave
				[ ] locator "//WPFButton[@automationId='btnSavePure']"
			[+] WPFButton BtnHelp
				[ ] locator "//WPFButton[@automationId='btnHelp']"
			[+] list of string GetData()
				[ ] APlus.SetActive()
				[ ] Clipboard.SetText()
				[ ] wTdeEvaluateResult.ctlPartDataGrid.Click(1,5,5)
				[ ] sleep(1)
				[ ] wTdeEvaluateResult.ctlPartDataGrid.Click(1,5,5)
				[ ] APlus.btnCopyProp.Click()
				[ ] sleep(5)
				[ ] return (Clipboard.GetText())
			[+] VerifyDataEmpty()
				[+] if listcount(this.GetData()) <= 1
					[ ] RaiseError(-255,"Data is not populated in DataGrid, it is empty!!!")
			[ ] 
			[ ] 
		[+] window WPFWindow wTdeReEvaluate
			[ ] locator "/WPFWindow[@caption='TDE Re-evaluate']"
			[+] WPFGroupBox TemperatureRangeK
				[ ] locator "//WPFGroupBox[@caption='Temperature range (K)']"
			[+] WPFLabel Lower
				[ ] locator "//WPFLabel[@caption='Lower:']"
			[+] WPFTextBox TextboxTLower
				[ ] locator "//WPFTextBox[@automationId='textboxTLower']"
			[+] WPFLabel Upper
				[ ] locator "//WPFLabel[@caption='Upper:']"
			[+] WPFTextBox TextboxTUpper
				[ ] locator "//WPFTextBox[@automationId='textboxTUpper']"
			[+] WPFRadioButton Rd1
				[ ] locator "//WPFRadioButton[@automationId='rd1']"
			[+] WPFControl SpinboxPoint
				[ ] locator "//WPFControl[@automationId='spinboxPoint']"
			[+] WPFContentControl ContentControl100
				[ ] locator "//WPFContentControl[@caption='100']"
			[+] WPFControl PartEditControl
				[ ] locator "//WPFControl[@automationId='PART_editControl']"
			[+] WPFTextBlock TextBlock
				[ ] locator "//WPFTextBlock[@automationId='TextBlock']"
			[+] WPFRepeatButton PartSpinUp
				[ ] locator "//WPFRepeatButton[@automationId='PART_spinUp']"
			[+] WPFRepeatButton PartSpinDown
				[ ] locator "//WPFRepeatButton[@automationId='PART_spinDown']"
			[+] WPFRadioButton Rd2
				[ ] locator "//WPFRadioButton[@automationId='rd2']"
			[+] WPFTextBox TextboxIncrements
				[ ] locator "//WPFTextBox[@automationId='textboxIncrements']"
			[+] WPFButton BtnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
			[+] WPFButton Cancel
				[ ] locator "//WPFButton[@caption='Cancel']"
		[ ] 
		[+] window DialogBox APrSystemHelp
			[ ] locator "/MainWin[@caption='APrSystem Help']"
			[+] DomElement body
				[ ] locator "//BrowserWindow//BODY"
			[+] boolean verifyContents(list of string lstExpected)
				[ ] this.body.Click()
				[ ] this.body.TypeKeys("<ctrl-a>")
				[ ] this.body.TypeKeys("<ctrl-c>")
				[ ] list of STRING lstContents = Clipboard.GetText()
				[ ] integer i=1, j = 1
				[ ] string sLine
				[ ] int helpLength = listCount(lstContents)
				[ ] int expectedCount = listCount(lstExpected)
				[ ] 
				[+] while( i <= helpLength && j <= expectedCount )
						[+] if(MatchStr("*{lstExpected[j]}*",lstContents[i]))
							[ ] Log.Message("Found {lstExpected[j]}")
							[ ] j++
							[+] if( j > expectedCount )
								[ ] break
						[+] else
							[ ] i++
				[+] if(j <= expectedCount)
					[ ] Log.Error("ERROR: Failed to Find the Following Strings In the Help Window:")
					[+] while( j <= expectedCount )
						[ ] Print(lstExpected[j])
						[ ] j++
					[ ] return FALSE
				[+] else
					[ ] Log.Pass("Found all expected Strings")
					[ ] return TRUE
					[ ] 
		[+] window DialogBox wAPrSystemHelp
			[ ] tag "/MainWin[@caption='APrSystem Help']"
			[ ] locator "/FormsWindow[@caption='Aspen Plus V*Help']"
			[+] ToolBar ToolBar1
				[ ] tag "$1006"
				[+] PushButton Hide
					[+] multitag "Hide"
						[ ] "$201"
				[+] PushButton Back
					[+] multitag "Back"
						[ ] "$204"
				[+] PushButton Forward
					[+] multitag "Forward"
						[ ] "$209"
				[+] PushButton Home
					[+] multitag "Home"
						[ ] "$205"
				[+] PushButton Print
					[+] multitag "Print"
						[ ] "$207"
				[+] PushButton Options
					[+] multitag "Options"
						[ ] "$208"
			[+] CustomWin ctlContents
				[ ] tag "[HH Child]$0[2]"
				[+] CustomWin ShellEmbedding1
					[ ] tag "[Shell Embedding]$0"
					[+] CustomWin ShellDocObjectView1
						[ ] tag "[Shell DocObject View]$0"
						[+] CustomWin InternetExplorer_Server1
							[ ] tag "[Internet Explorer_Server]$0"
			[+] CustomWin HHSizeBar1
				[ ] tag "[HH SizeBar]$0"
			[+] CustomWin HHChild1
				[ ] tag "[HH Child]$0[1]"
				[+] PageList PageList1
					[ ] tag "$1007"
					[+] TreeView TreeView1
						[ ] tag "$0"
			[+] string GetTopic()
				[ ] this.SetActive()
				[ ] window w = wAPrSystemHelp.FindAll("//Control[@className='CefSharp.WinForms.*WebBrowser']")[1]
				[ ] RECT rc = w.GetRect()
				[ ] w.Click(1, rc.xSize*2/3,rc.ySize/2)
				[ ] wAPrSystemHelp.TypeKeys("<Ctrl-a 3>", 1)
				[ ] wAPrSystemHelp.TypeKeys("<Ctrl-c 3>", 1)
				[ ] sleep(5)
				[ ] return Clipboard.GetText()[1]
				[ ] 
		[ ] 
		[ ] 
		[+] window DialogBox contextMenuBox
			[ ] locator "//WPFContextMenu"
			[+] multitag ""
				[ ] "[DialogBox]#1"
		[+] window glwcMessageBox contextMenuBox2
			[+] multitag ""
				[ ] // "#2|#1"
		[ ] 
		[+] window DialogBox dlgFileDownload
			[ ] locator "//DialogBox[@caption='File Download']"
			[+] PushButton btnSave
				[ ] locator "//PushButton[@caption='Save']"
		[+] window MainWin wDownloadComplete
			[ ] locator "/MainWin[@caption='Download complete']"
			[+] PushButton btnClose
				[ ] locator "//PushButton[@caption='Close']"
			[+] PushButton btnOpenFolder
				[ ] locator "//PushButton[@caption='Open Folder']"
			[+] PushButton btnOpen
				[ ] locator "//PushButton[@caption='Open']"
				[ ] 
				[ ] 
		[ ] 
		[+] window MainWin wReveal
			[ ] locator "//WPFWindow[@caption='Reveal']"
			[+] WPFListView	lsvObjects
				[ ] locator "//WPFListView[@automationId='lbItems']"
			[+] WPFButtonBase btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
			[ ] 
		[+] window WPFWindow wDataRegressionRunSelection
			[ ] locator "/WPFWindow[@caption='Data Regression Run Selection']"
			[+] WPFGroupBox SelectRegressionCasesToRunAndTheirOrder
				[ ] locator "Select regression case(s) to run and their order"
			[+] WPFGroupBox DontRun
				[ ] locator "Don't run"
			[+] WPFListBox LstAvailableComp
				[ ] locator "@automationId='lstAvailableComp'"
			[+] WPFButton BtnMove
				[ ] locator "@automationId='btnMove'"
			[+] WPFButton BtnMoveAll
				[ ] locator "@automationId='btnMoveAll'"
			[+] WPFButton btnRemove
				[ ] locator "//WPFButton[@automationId='btnRemove']"
			[+] WPFButton btnRemoveAll
				[ ] locator "//WPFButton[@automationId='btnClearAll']"
			[ ] 
			[+] WPFButton BtnRemove
				[ ] locator "@automationId='btnRemove'"
			[+] WPFButton BtnClearAll
				[ ] locator "@automationId='btnClearAll'"
			[+] WPFGroupBox Run
				[ ] locator "Run"
			[+] WPFListBox LstSelectedComp
				[ ] locator "@automationId='lstSelectedComp'"
			[+] WPFListBoxItem R1
				[ ] locator "R-1"
			[+] WPFListBoxItem R2
				[ ] locator "R-2"
			[+] WPFListBoxItem R3
				[ ] locator "R-3"
			[+] WPFButton BtnUp
				[ ] locator "@automationId='btnUp'"
			[+] WPFImage Image
				[ ] locator "[1]"
			[+] WPFButton BtnDown
				[ ] locator "@automationId='btnDown'"
			[+] WPFImage Image2
				[ ] locator "[2]"
			[+] WPFButton BtnOK
				[ ] locator "@automationId='btnOK'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btnCancel'"
		[+] window WPFWindow wDataRegressionCasesIncomplete
			[ ] locator "/WPFWindow[@caption='Data Regression Cases Incomplete']"
			[+] WPFLabel Label1
				[ ] locator "@automationId='label1'"
			[+] WPFControl AesGroupBox
				[ ] locator "@automationId='AesGroupBox'"
			[+] WPFContentControl AesControlBorder
				[ ] locator "@className='AesControlBorder'"
			[+] WPFRadioButton rdEnterMore
				[ ] locator "@automationId='Rd0'"
			[+] WPFRadioButton rdSpecifyCases
				[ ] locator "@automationId='Rd1'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='OK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Cancel'"
			[+] WPFLabel LblTitle
				[ ] locator "@automationId='LblTitle'"
		[+] window DialogBox wPasteError
			[ ] locator "//DialogBox[@caption='Paste Error']"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@caption='OK']"
		[ ] 
		[+] window WPFWindow wNewUtilty
			[ ] locator "/WPFWindow [@caption='New Utility']"
			[+] WPFTextBox tbUtilityName
				[ ] locator "//WPFTextBox[@automationId='txtNewUtility']"
			[+] WPFComboBox cboCopyFrom
				[ ] locator "//WPFComboBox[@automationId='cboCopyForm']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
		[ ] 
		[+] window WPFWindow wRequiresWater
			[ ] locator "/WPFWindow[@caption='Aspen Plus']"
			[+] WPFTextBlock tbText
				[ ] locator "//WPFTextBlock[@automationId='TextBlock_1']"
			[+] WPFButton btnYes
				[ ] locator "//WPFButton[@automationId='btn0']"
			[+] WPFButton btnNo
				[ ] locator "//WPFButton[@automationId='btn1']"
	[ ] 
	[+] //NIST TDE
		[+] window WPFWindow wNistThermoDataEngine
			[ ] locator "/WPFWindow[@caption='NIST ThermoData Engine']"
			[+] WPFGroupBox PropertyDataType
				[ ] locator "//WPFGroupBox[@caption='Property data type']"
			[+] WPFRadioButton rdlPure
				[ ] locator "//WPFRadioButton[@caption='Pure']"
			[+] WPFRadioButton rdlBinaryMixture
				[ ] locator "//WPFRadioButton[@caption='Binary mixture']"
			[+] WPFGroupBox ComponentSToEvaluate
				[ ] locator "//WPFGroupBox[@caption='Component(s) to evaluate']"
			[+] WPFComboBox cbo1stComponentSToEvaluate
				[ ] locator "//WPFComboBox[1]"
				[+] WPFComboBoxItem H2
					[ ] locator "//WPFComboBoxItem[@caption='H2']"
				[+] WPFComboBoxItem N2
					[ ] locator "//WPFComboBoxItem[@caption='N2']"
				[+] WPFComboBoxItem C1
					[ ] locator "//WPFComboBoxItem[@caption='C1']"
				[+] WPFComboBoxItem BZ
					[ ] locator "//WPFComboBoxItem[@caption='BZ']"
				[+] WPFComboBoxItem Ch
					[ ] locator "//WPFComboBoxItem[@caption='CH']"
			[+] WPFComboBox cbo2ndComponentSToEvaluate
				[ ] locator "//WPFComboBox[2]"
				[+] WPFComboBoxItem ComboBoxItem
					[ ] locator "//WPFComboBoxItem[6]"
				[+] WPFComboBoxItem ComboBoxItem7
					[ ] locator "//WPFComboBoxItem[7]"
				[+] WPFComboBoxItem ComboBoxItem8
					[ ] locator "//WPFComboBoxItem[8]"
				[+] WPFComboBoxItem ComboBoxItem9
					[ ] locator "//WPFComboBoxItem[9]"
				[+] WPFComboBoxItem ComboBoxItem10
					[ ] locator "//WPFComboBoxItem[10]"
			[+] WPFButton btnEnterAdditionalData
				[ ] locator "//WPFButton[@caption='Enter additional data ...']"
			[+] WPFButton btnEvaluateNow
				[ ] locator "//WPFButton[@caption='Evaluate now']"
			[+] WPFButton btnRetrieveData
				[ ] locator "//WPFButton[@automationId='Button_2']"
			[+] WPFButton BtnHelp
				[ ] locator "//WPFButton[@automationId='BtnHelp']"
			[+] WPFStatusBar stsbStatusBar
				[ ] locator "//WPFStatusBar"
			[+] WPFStatusBarItem stsbiStatus
				[ ] locator "//WPFStatusBarItem"
			[+] WPFTextBlock LinkTip
				[ ] locator "//WPFTextBlock[@automationId='LinkTip']"
			[+] WPFHyperlink Hyperlink
				[ ] locator "//WPFHyperlink"
			[ ] //Method
			[+] VOID DataEvaluation(String sComp)
				[ ] this.SetActive()
				[ ] this.rdlPure.Select()
				[ ] this.cbo1stComponentSToEvaluate.Select(sComp)
				[ ] this.btnEvaluateNow.Click()
				[+] while ! this.btnEvaluateNow.IsEnabled
					[ ] sleep(1)
				[ ] Print("Evaluation sComp Finished")
			[+] VOID EvaluateAndSavePara(String sComp)
				[ ] //4. The results should be displayed in the result dialog box.
				[ ] wAspenProp.SetActive()
				[ ] wAspenProp.grpDataSource.btnNIST.Click()
				[ ] this.SetActive()
				[ ] this.rdlPure.Select()
				[ ] this.cbo1stComponentSToEvaluate.Select(sComp)
				[ ] this.btnEvaluateNow.Click()
				[+] while ! this.btnEvaluateNow.IsEnabled
					[ ] sleep(1)
				[ ] Print("Evaluation sComp Finished")
				[ ] this.Close()
				[ ] //5.Save all the properties to forms.
				[ ] wAspenProp.tbTDEPureResults.Click()
				[ ] wAspenProp.btnSavePara.Click()
				[ ] wParametersToBeSaved.SetActive()
				[ ] wParametersToBeSaved.btnOK.Click()
				[ ] wNistTdeConfirmSaving.SetActive()
				[ ] wNistTdeConfirmSaving.BtnOK.Click()
				[ ] wAspenProp.Closetab("Pure Components")
				[ ] 
		[+] window WPFWindow wBinaryExperimentalDataToBeSaved
			[ ] locator "/WPFWindow[@caption='Binary experimental data to be saved']"
			[+] WPFItemsControl wicDatasets
				[ ] locator "//WPFItemsControl[@className='RecordListControl']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='Button_1']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='Button_2']"
		[+] window WPFWindow wNistTdeConfirmSaving
			[ ] locator "/WPFWindow[@caption='NIST/TDE confirm saving']"
			[+] WPFImage HeaderImage
				[ ] locator "//WPFImage[@automationId='HeaderImage']"
			[+] WPFTextBlock TxtBlock
				[ ] locator "//WPFTextBlock[@automationId='TxtBlock']"
			[+] WPFButton BtnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='btn1']"
		[+] window WPFWindow wPureExperimentalDataToBeSaved
			[ ] locator "/WPFWindow[@caption='Pure experimental data to be saved']"
			[+] WPFCheckBox BtnSaveAcceptedDataOnly
				[ ] locator "//WPFCheckBox[@automationId='btncheck']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
			[+] WPFButton btnHelp
				[ ] locator "//WPFButton[@automationId='Help']"
		[+] window WPFWindow wSpecifyDataEvaluationRegressionCase
			[ ] locator "/WPFWindow[@caption='Specify Data Evaluation/Regression Case']"
			[+] WPFGroupBox grpCalculationType
				[ ] locator "//WPFGroupBox[@automationId='GroupBox_1']"
				[+] WPFRadioButton rdEvaluation
					[ ] locator "//WPFRadioButton[@automationId='RadioButton_1']"
				[+] WPFRadioButton rdRegression
					[ ] locator "//WPFRadioButton[@automationId='RadioButton_2']"
			[+] wcAPWPFTextBox txtCaseID
				[ ] locator "//WPFControl[@automationId='PART_editControl']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='Button_1']"
		[+] window WPFWindow wNISTTDEConsistencyTest
			[ ] locator "/WPFWindow[@caption='NIST/TDE consistency test']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btn0']"
		[+] window WPFWindow wSurfaceTension
			[ ] locator "/WPFWindow[@caption='Surface tension (Liquid vs. Gas )*']"
		[+] window WPFWindow wParametersToBeSaved
			[ ] locator "/WPFWindow[@caption='Parameters to be saved']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
			[+] WPFButton btnHelp
				[ ] locator "//WPFButton[@automationId='Help']"
		[+] window WPFWindow wVaporPressureCrystalGas
			[ ] locator "/WPFWindow[@caption='Vapor pressure (Crystal 1 vs. Gas )*']"
	[ ] 
	[+] //Summary Report
		[+] window WPFWindow wReport
			[ ] locator "/WPFWindow[@caption='Report']"
			[+] WPFButton btnOK
				[ ] locator "OK"
			[+] WPFButton Cancel
				[ ] locator "Cancel"
			[+] WPFButton Apply
				[ ] locator "Apply"
			[+] WPFComboBox ComboBox
				[ ] locator "//WPFComboBox[@automationId='ComboBox_1']"
			[+] WPFComboBoxItem ConnectingStreams
				[ ] locator "//WPFComboBoxItem[@caption='Connecting Streams']"
			[+] WPFTreeView TreeView
				[ ] locator "@automationId='treeView'"
			[+] WPFTreeViewItem trviSelectAll
				[ ] locator "*Select all *"
			[+] WPFCheckBox chkSelectAll
				[ ] locator "*Select all*"
			[+] void Select(string sCategory, string sItemName)
				[ ] this.ComboBox.Select("{sCategory}")
				[ ] this.trviSelectAll.Expand()
				[ ] //this.Find("//WPFCheckBox[@caption='*{sItemName}*']").click()
				[ ] this.Find("//WPFCheckBox[@caption='{sItemName}*']").Check()
				[ ] 
			[+] void DeSelect(string sCategory, string sItemName)
				[ ] this.ComboBox.Select("{sCategory}")
				[ ] this.trviSelectAll.Expand()
				[ ] this.Find("//WPFCheckBox[@caption='*{sItemName}*']").UnCheck()
				[ ] 
			[ ] 
		[+] window WPFWindow wInputName
			[ ] locator "/WPFWindow[@caption='Input Name']"
			[+] WPFLabel lablEnterTheSheetName
				[ ] locator "//WPFLabel[@caption='Enter the sheet name:']"
			[+] WPFTextBox TextboxName
				[ ] locator "//WPFTextBox[@automationId='textboxName']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='buttonOK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='buttonCancel']"
		[+] window WPFWindow wStreamSummaryEditViewWizard
			[ ] locator "/WPFWindow[@caption='Stream Summary Edit View Wizard']"
			[+] WPFLabel lablCustomStreamSummaryViewFile
				[ ] locator "//WPFLabel[@caption='Custom stream summary view file:']"
			[+] WPFCheckBox chkStream1
				[ ] locator "//WPFCheckBox[@automationId='PART_FocusSite'][1]"
			[+] WPFCheckBox chkStream2
				[ ] locator "//WPFCheckBox[@automationId='PART_FocusSite'][2]"
			[+] WPFCheckBox chkStream3
				[ ] locator "//WPFCheckBox[@automationId='PART_FocusSite'][3]"
			[+] WPFCheckBox chkStream4
				[ ] locator "//WPFCheckBox[@automationId='PART_FocusSite'][4]"
			[+] WPFButton btnLeft
				[ ] locator "//WPFButton[@automationId='buttonLeft']"
			[+] WPFButton btnSave
				[ ] locator "//WPFButton[@automationId='buttonSave']"
			[+] WPFButton btnOpen
				[ ] locator "//WPFButton[@automationId='buttonOpen']"
			[+] WPFButton btnBack
				[ ] locator "//WPFButton[@automationId='buttonBack']"
			[+] WPFButton btnNext
				[ ] locator "//WPFButton[@automationId='buttonNext']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='buttonOK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='buttonCancel']"
			[+] WPFButton btnHelp
				[ ] locator "//WPFButton[@automationId='buttonHelp']"
			[+] WPFButton btnUp
				[ ] locator "//WPFButton[@automationId='buttonUp']"
			[+] WPFButton btnDown
				[ ] locator "//WPFButton[@automationId='buttonDown']"
			[+] WPFListBox ListBoxDestination
				[ ] locator "//WPFListBox[@automationId='listBoxDestination']"
			[+] WPFListBox lbSelectedProperties
				[ ] locator "//WPFListBox[@automationId='listBoxRight']"
			[+] WPFTabItem PropertySelection
				[ ] locator "//WPFTabItem[@caption='Property Selection']"
			[+] WPFTabItem DisplayOptions
				[ ] locator "//WPFTabItem[@caption='Display Options']"
			[+] WPFTabItem CalculationOptions
				[ ] locator "//WPFTabItem[@caption='Calculation Options']"
			[+] WPFTabItem LabelOptions
				[ ] locator "//WPFTabItem[@caption='Label Options']"
			[+] WPFTabItem StreamSelection
				[ ] locator "//WPFTabItem[@caption='Stream Selection']"
			[+] DialogBox dlgSaveAs
				[ ] locator "//DialogBox[@caption='Save As']"
				[+] PushButton pshSave
					[ ] locator "//PushButton[@caption='Save']"
				[+] TextField txtFileName
					[ ] locator "//TextField"
				[+] DialogBox dlgSaveAsReplace
					[ ] locator "//DialogBox[@caption='Save As']"
					[+] PushButton pshYes
						[ ] locator "//PushButton[@caption='Yes']"
			[+] DialogBox dlgOpen
				[ ] locator "//DialogBox[@caption='Open']"
				[+] PushButton pshOpen
					[ ] locator "//PushButton[@caption='Open']"
				[+] TextField txtFileName
					[ ] locator "//TextField"
				[ ] 
	[ ] 
	[+] //Aspen Properties 
		[+] window WPFWindow wDataRegressionInputComplete
			[ ] locator "/WPFWindow[@caption='*Data Regression Input Complete']"
			[+] WPFTextBlock txtBlock
				[ ] locator "@automationId='TxtBlock'"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='*OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='*Cancel']'"
		[+] window WPFWindow wPropertyEstimationInputComplete
			[ ] locator "/WPFWindow[@caption='Property Estimation Input Complete']"
			[+] WPFTextBlock TxtBlock
				[ ] locator "@automationId='TxtBlock'"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='Cancel']"
		[+] window WPFWindow wPropertiesInputComplete
			[ ] locator "/WPFWindow[@caption='*Properties Input Complete' ]"
			[+] WPFLabel Label1
				[ ] locator "@automationId='label1'"
			[+] WPFControl AesGroupBox
				[ ] locator "@automationId='AesGroupBox'"
			[+] WPFContentControl AesControlBorder
				[ ] locator "@className='AesControlBorder'"
			[+] WPFRadioButton rdRunPropertyAnalysis
				[ ] locator "@automationId='Rd0'"
			[+] WPFRadioButton rdModifyRequired
				[ ] locator "@automationId='Rd1'"
			[+] WPFRadioButton rdEnterProperty
				[ ] locator "@automationId='Rd2'"
			[+] WPFRadioButton rdEnterExperimental
				[ ] locator "@automationId='Rd3'"
			[+] WPFRadioButton rdGotToSimulation
				[ ] locator "//WPFRadioButton[@automationId='Rd4' or @caption='Go to Simulation environment']"
			[+] WPFButton btnOK
				[ ] locator "@automationId='OK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Cancel'"
			[+] WPFLabel lblTitle
				[ ] locator "@automationId='LblTitle'"
			[ ] 
		[+] window WPFWindow wRequiredPropertiesInputComplete
			[ ] locator "/WPFWindow[@caption='*Properties Input Complete' ]"
			[+] WPFLabel Label1
				[ ] locator "@automationId='label1'"
			[+] WPFControl AesGroupBox
				[ ] locator "@automationId='AesGroupBox'"
			[+] WPFContentControl AesControlBorder
				[ ] locator "@className='AesControlBorder'"
			[+] WPFRadioButton rdRunPropertyAnalysis
				[ ] locator "@automationId='Rd0'"
			[+] WPFRadioButton rdModifyRequired
				[ ] locator "@automationId='Rd1'"
			[+] WPFRadioButton rdEnterProperty
				[ ] locator "@automationId='Rd2'"
			[+] WPFRadioButton rdEnterExperimental
				[ ] locator "@automationId='Rd3'"
			[+] WPFRadioButton rdGotToSimulation
				[ ] locator "//WPFRadioButton[@automationId='Rd4' or @caption='Go to Simulation environment']"
			[+] WPFButton btnOK
				[ ] locator "@automationId='OK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Cancel'"
			[+] WPFLabel lblTitle
				[ ] locator "@automationId='LblTitle'"
			[ ] 
		[+] window WPFWindow wAdjustedVariableRangeListOptions
			[ ] locator "/WPFWindow[@caption='Adjusted Variable Range/List Options']"
			[+] WPFControl txbList1
				[ ] locator "//WPFControl[@className=MMVariableEdit][1]"
			[+] WPFButton btnNext
				[ ] locator "//WPFButton[@automationId='PART_BUTTON'][1]"
			[+] WPFButton btnClose
				[ ] locator "//WPFButton[@caption='Close']"
		[+] window WPFWindow wFindCompounds
			[ ] locator "/WPFWindow[@caption='Find Compounds']"
			[+] WPFRadioButton rdBeginWith
				[ ] locator "@automationId='radioBeginWith'"
			[+] WPFRadioButton rdContains
				[ ] locator "@automationId='radioContains'"
			[+] WPFRadioButton rdEquals
				[ ] locator "@automationId='radioEquals'"
			[+] WPFTextBox txbName
				[ ] locator "@automationId='txtContainValue'"
			[+] WPFTextBlock TextBlock_4
				[ ] locator "@automationId='TextBlock_4'"
			[+] WPFComboBox cboCompoundClass
				[ ] locator "@automationId='cboCompoundClass'"
			[+] WPFTextBox txbMWFrom
				[ ] locator "@automationId='txtMWFrom'"
			[+] WPFTextBox txbMWTo
				[ ] locator "@automationId='txtMWTo'"
			[+] WPFTextBox txbBPFrom
				[ ] locator "@automationId='txtBPFrom'"
			[+] WPFTextBox txbBPTo
				[ ] locator "@automationId='txtBPTo'"
			[+] WPFComboBox cboBpUnit
				[ ] locator "@automationId='cboBpUnit'"
			[+] WPFButton btnFind
				[ ] locator "@automationId='btnFind'"
			[+] WPFButton btnNewSearch
				[ ] locator "@automationId='btnNewSearch'"
			[+] WPFButton btnHelp
				[ ] locator "@automationId='btnHelp'"
			[+] WPFListView lsvCompounds
				[ ] locator "@automationId='lstComps'"
			[+] WPFButton btnAddSelectedComponents
				[ ] locator "@automationId='btnAdd'"
			[+] WPFTabItem tabiDatabanks
				[ ] locator "@automationId='tabDatabanks'"
			[+] WPFTabItem tabiCompounds
				[ ] locator "@automationId='tabCompounds'"
			[+] WPFButton btnClose
				[ ] locator "@automationId='btnClose'"
			[+] WPFStatusBarItem stbStatus
				[ ] locator "WPFStatusBarItem[@automationId='StatusBarItem_1']"
			[ ] 
		[+] window WPFWindow wChemistryIDExists
			[ ] locator "/WPFWindow[@caption='Chemistry ID Exists']"
			[+] WPFButton btnYes
				[ ] locator "//WPFButton[1]"
			[+] WPFButton btnNo
				[ ] locator "//WPFButton[2]"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[3]"
			[ ] 
		[+] window WPFPopup wHenryComponentListIDExists
			[ ] locator "/WPFWindow[@caption='Henry-Component List ID Exists']"
		[+] window WPFWindow wDethermOnTheWeb
			[ ] locator "/WPFWindow[@caption='Detherm on the Web']"
			[+] WPFTextBox TxtUrl
				[ ] locator "//WPFTextBox[@automationId='txtUrl']"
			[+] BrowserWindow WBrowser
				[ ] locator "//BrowserWindow[@automationId='wBrowser']"
				[ ] // Lines 7
				[+] DomCheckBox chkLines7
					[ ] locator "INPUT[@value='3']"
				[+] DomButton btnViewCart
					[ ] locator "INPUT[@name='action[ViewCart]']"
			[+] DomButton btnOrder
				[ ] locator "//INPUT[@accessKey='o']"
			[+] DomButton btnReset
				[ ] locator "//INPUT[@id='resetb']"
			[ ] 
			[+] DomButton btnLogin
				[ ] locator "//INPUT[@id='login']"
			[+] DomButton btnConfirm
				[ ] locator "//INPUT[@name='action']"
			[+] DomButton btnDownload
				[ ] locator "//INPUT[@name='action']"
			[+] DomButton btnPurchase
				[ ] locator "//BrowserWindow[@automationId='wBrowser']//INPUT[@value='PURCHASE']"
			[ ] 
			[+] DomTextField txtUserName
				[ ] locator "//INPUT[@name='username']"
			[+] DomTextField txtPassword
				[ ] locator "//INPUT[@name='password']"
				[ ] 
			[+] WPFButton BtnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
			[+] WPFButton BtnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
			[+] BrowserWindow WBrowser1
				[ ] locator "@automationId='wBrowser'"
				[+] DomCheckBox X2
					[ ] locator "INPUT[@value='2']"
				[+] DomElement X229357
					[ ] locator "TD[@title='229357']"
				[+] DomButton ActionNext
					[ ] locator "INPUT[@name='action[Next]']"
				[+] DomTextField Text1
					[ ] locator "INPUT[@id='text1']"
				[+] DomTextField Text2
					[ ] locator "INPUT[@id='text2']"
				[+] DomButton Submit2
					[ ] locator "INPUT[@id='submit2']"
				[+] DomButton ActionViewCart
					[ ] locator "INPUT[@name='action[ViewCart]']"
				[+] DomButton O
					[ ] locator "INPUT[@accessKey='o']"
				[+] DomTextField Username
					[ ] locator "INPUT[@name='username']"
				[+] DomTextField Password
					[ ] locator "INPUT[@name='password']"
				[+] DomButton Login
					[ ] locator "INPUT[@id='login']"
				[+] DomButton Action
					[ ] locator "INPUT[@name='action']"
			[+] DialogBox AutoComplete
				[ ] locator "AutoComplete"
				[+] PushButton No
					[ ] locator "No"
			[+] WPFButton BtnOK1
				[ ] locator "@automationId='btnOK'"
		[+] window DialogBox wCOTAPPM
			[ ] locator "//DialogBox[@caption='COTAPPM']"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@caption='OK']"
			[+] PushButton btnYes
				[ ] locator "//PushButton[@caption='Yes']"
			[+] PushButton btnNo
				[ ] locator "//PushButton[@caption='No']"
			[ ] 
		[+] window WPFWindow wPropTPlot
			[ ] locator "/WPFWindow[@caption='*Prop. vs T - Plot*']"
		[+] window wcAspenProperties wAspenProp
			[ ] locator "/WPFWindow[@caption='*Aspen Properties*']"
			[+] void AddComponent(list of string sComponents)
				[ ] // Such as:
				[ ] //wAspenProp.AddComponent({"ETHANOL","WATER"})
				[ ] //
				[ ] String sComp
				[ ] int i =0
				[ ] this.SetActive()
				[ ] this.tbComSpecifications.Click()
				[+] for each sComp in sComponents
					[ ] this.dgComponents.SetCellData(0,i,sComp)
					[ ] i++
					[ ] sleep(0.5)
			[+] void SelectComponents(list of string lsCom)
				[ ] String sComp
				[ ] this.SetActive()
				[ ] this.tbComSpecifications.Click()
				[ ] this.btnFind.Click()
				[+] for each sComp in lsCom
					[ ] wFindCompounds.SetActive()
					[ ] wFindCompounds.rdEquals.Select()
					[ ] wFindCompounds.txbName.SetText(sComp)
					[ ] wFindCompounds.btnFind.Click()
					[+] while !wFindCompounds.btnFind.IsEnabled
						[ ] sleep(1)
					[+] do
						[ ] wFindCompounds.lsvCompounds.Find("//WPFListViewItem[1]").Click()
						[ ] // wFindCompounds.Find("//WPFTextBlock[@caption='{sComp}']").SetFocus()
					[+] except
						[ ] Log.Error("Can not find component {sComp}")
						[ ] break
					[ ] wFindCompounds.btnAddSelectedComponents.Click()
					[+] if wAspenProperties.Exists(3)
						[ ] wAspenProperties.Find("//WPFButton[@automationId='btn1']").click()//Add new comp
					[ ] sleep(0.5)
				[ ] wFindCompounds.btnClose.Click()
			[+] void PureComponentRunAnalysis(string strPureComponentName,string strProperty,string strPhase,string strComponentName,string strScreenshotName)
				[ ] this.SetTab("{strPureComponentName}*Input")
				[ ] glWaitForMouseIdle(5)
				[ ] //Select property in ComboBox
				[ ] this.grpProperty.cboProperty.Select(strProperty)
				[+] if(("v" == lower(strPhase)) || ("vapour" == lower(strPhase)) )
					[+] if this.grpProperty.chkVapor.IsEnabled
						[ ] this.grpProperty.chkVapor.Check()
					[ ] //Uncheck Liquid
					[+] if this.grpProperty.chkLiquid.IsEnabled
						[ ] this.grpProperty.chkLiquid.Uncheck()
					[ ] //Uncheck Solid
					[+] if this.grpProperty.chkSolid.IsEnabled
						[ ] this.grpProperty.chkSolid.Uncheck()
				[+] if(("l" == lower(strPhase)) || ("liquid" == lower(strPhase)) )
					[ ] //Uncheck Vapour
					[+] if this.grpProperty.chkVapor.IsEnabled
						[ ] this.grpProperty.chkVapor.Uncheck()
					[ ] //Check Liquid
					[+] if this.grpProperty.chkLiquid.IsEnabled
						[ ] this.grpProperty.chkLiquid.Check()
					[ ] //Uncheck Solid
					[+] if this.grpProperty.chkSolid.IsEnabled
						[ ] this.grpProperty.chkSolid.Uncheck()
					[ ] 
				[+] if(("s" == lower(strPhase)) || ("solid" == lower(strPhase)) )
					[ ] //Uncheck Vapour
					[+] if this.grpProperty.chkVapor.IsEnabled
						[ ] this.grpProperty.chkVapor.Uncheck()
					[ ] //UnCheck Liquid
					[+] if this.grpProperty.chkLiquid.IsEnabled
						[ ] this.grpProperty.chkLiquid.Uncheck()
					[ ] //Check Solid
					[+] if this.grpProperty.chkSolid.IsEnabled
						[ ] this.grpProperty.chkSolid.Check()
				[+] if(this.grpComponents.btnMoveAllLeft.IsEnabled)
					[ ] this.grpComponents.btnMoveAllLeft.Click()
				[ ] this.Find("//WPFListBoxItem[@caption='{strComponentName}']").Click()
				[ ] this.grpComponents.btnMoveRight.Click()
				[ ] this.btnRunAnalysis.Click()
				[ ] sleep(2)
				[ ] glWaitForMouseIdle(20)
				[ ] Desktop.CaptureBitmap(strScreenshotName)
				[ ] Log.Warning("Please compare the screenshot {strScreenshotName} with baseline.")
			[+] void BinarayInputRunAnalysis(string strAnalysisType,string strCompositionBasis,list of string lstTemOrPre,string strNoOfPoints,string strValidPhase,string strScreenshotName, string strBaseMethod optional)
				[ ] sleep(1)
				[ ] 
				[ ] // Select Analysis type
				[ ] this.cboAnalysisType.Select(strAnalysisType)
				[ ] // Select Composition Basis
				[ ] this.grpCompositions.cboCompositionBasis.Select(strCompositionBasis)
				[ ] 
				[ ] // set temperature or pressure value
				[+] if(Lower(strAnalysisType) != "gibbs energy of mixing")
					[ ] this.grpPressureOrTempList.dgPressureorTempList.SetFocus()
					[ ] sleep(0.5)
					[+] int i
						[+] for(i =1;i<= ListCount(lstTemOrPre);i++)
							[ ] int column= i-1
							[ ] this.grpPressureOrTempList.dgPressureorTempList.SetCellData(column,0,lstTemOrPre[i])
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
				[ ] this.grpCompositions.tbNoOfPoints.InputText(strNoOfPoints)
				[ ] 
				[ ] //Select valid phase
				[+] if(strValidPhase!="" || lower(strValidPhase) != "default")
					[ ] this.grpValidPhases.cboPhases.Select(strValidPhase)
				[ ] 
				[ ] this.btnRunAnalysis.Click()
				[ ] sleep(4)
				[ ] glWaitForMouseIdle(20)
				[ ] 
				[ ] Desktop.CaptureBitmap(strScreenshotName)
				[ ] Log.Warning("Please compare the screenshot {strScreenshotName} with baseline.")
				[ ] 
				[ ] this.SetActive()
				[ ] this.SetTab("Home")
				[+] if(this.grpAnalysis.btnBinary.Exists())
					[ ] this.grpAnalysis.btnBinary.Click()
					[ ] glWaitForMouseIdle(5)
				[ ] 
				[+] do
					[ ] this.SetTab("BINRY*Input")
				[+] except
					[ ] Log.Error("The Binary Input didn't appear.")
				[ ] 
			[+] void CheckDataGridResults(list of string lsExpected, string sDescription)
				[ ] this.SetActive()
				[ ] Clipboard.SetText({})
				[ ] this.btnSelectAll.Click()
				[ ] this.TypeKeys("<Ctrl-c 3>", 0.5)
				[ ] list of string lsResults = Clipboard.GetText()
				[+] if Str.MatchList(lsResults,lsExpected)
					[ ] Log.Pass("Compare passed for  {sDescription}")
				[+] else
					[ ] Log.Error("Compare failed for {sDescription}")
					[ ] ListPrint(lsResults)
			[ ] 
		[+] window WPFWindow wNewAspenPropertiesCase
			[ ] locator "/WPFWindow[@caption='New']"
			[+] WPFListBox lbCaseType
				[ ] locator "//WPFListBox[@automationId='listBoxCategories']"
				[+] WPFListBoxItem lbiBlankRecent
					[ ] locator "//WPFListBoxItem[@caption='Blank and Recent']"
				[+] WPFListBoxItem lbiUser
					[ ] locator "//WPFListBoxItem[@caption='User']"
			[+] WPFButton btnCreate
				[ ] locator "//WPFButton[@automationId='btnCreate']"
		[+] window WPFWindow wUpwardCompatibilityInAspenProp
			[ ] locator "/WPFWindow[@caption='Upward Compatibility']"
			[+] WPFRadioButton rdMaintain
				[ ] locator "//WPFRadioButton[@automationId='radioMaitain']"
			[+] WPFRadioButton rdFollowNewFeatures
				[ ] locator "//WPFRadioButton[@automationId='radioFollow']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
			[ ] 
		[+] window MainWin wAspenCOMThermoCAPEOPENInformationmessage
			[ ] locator "/MainWin[@caption='Aspen COMThermo CAPE-OPEN * Information message']"
			[+] PushButton btnOK
				[ ] locator "OK"
		[+] window MainWin wAspenPropertiesDatabaseSelectionApplication
			[ ] locator "/Window[@caption='Database Selector - Aspen Properties V*']"
			[+] PushButton btnOK
				[ ] locator "OK"
			[+] PushButton btnCancel
				[ ] locator "Cancel"
			[+] RadioList rdAspenPropertiesEnterpriseDatabase
				[ ] locator "Aspen Properties Enterprise Database"
			[+] RadioList rdLegacyPropertiesDatabanks
				[ ] locator "Legacy Properties Databanks"
			[ ] 
		[+] window WPFWindow wOptionsCodes
			[ ] locator "/WPFWindow[@caption='Option Codes']"
			[+] wcAPWPFTextBox txbCode1
				[ ] locator "//WPFControl[@automationId='PART_editControl'][2]"
			[+] wcAPWPFTextBox txbCode2
				[ ] locator "//WPFControl[@automationId='PART_editControl'][3]"
			[+] wcAPWPFTextBox txbCode3
				[ ] locator "//WPFControl[@automationId='PART_editControl'][4]"
			[+] wcAPWPFTextBox txbCode4
				[ ] locator "//WPFControl[@automationId='PART_editControl'][5]"
			[+] wcAPWPFTextBox txbCode5
				[ ] locator "//WPFControl[@automationId='PART_editControl'][6]"
			[+] WPFButton btnClose
				[ ] locator "//WPFButton[@caption='*Close']"
		[+] window WPFWindow wWaterRequired
			[ ] locator "/WPFWindow[@caption='Water Required*']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='*OK']"
		[+] window WPFWindow wNewPureComponentParameters
			[ ] locator "/WPFWindow[@caption='New Pure Component Parameters']"
			[+] WPFRadioButton rdScalar
				[ ] locator "//WPFRadioButton[2]"
			[+] WPFRadioButton rdTDependent
				[ ] locator "//WPFRadioButton[2]"
			[+] WPFRadioButton rdNonconventional
				[ ] locator "//WPFRadioButton[3]"
			[+] WPFTreeView trvParameter
				[ ] locator "//WPFTreeView[@automationId='treeParameter']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
		[+] window glwcMessageBox	AspenPropertisClassicWin
			[ ] tag"*Aspen Properties*"
			[+] glwcDlgOpenFile	dlgOpenFile
				[ ] tag"Open"
			[ ] glwcDlgSaveFile   dlgSaveAsFile
			[+] glwcDlgSaveFile   dlgExport
				[ ] tag "Export"
		[ ] window wcAPCongurationTester wAPCongurationTester
		[+] window WPFWindow wNonDataBankComponents
			[ ] locator "/WPFWindow[@caption='Non-Databank Components']"
			[+] WPFLabel Label1
				[ ] locator "@automationId='label1'"
			[+] WPFControl AesGroupBox
				[ ] locator "@automationId='AesGroupBox'"
			[+] WPFContentControl AesControlBorder
				[ ] locator "@className='AesControlBorder'"
			[+] WPFRadioButton btnGoToNext
				[ ] locator "@automationId='Rd0'"
			[+] WPFRadioButton btnEnterProperty
				[ ] locator "@automationId='Rd1'"
			[+] WPFRadioButton btnEnterExperimental
				[ ] locator "@automationId='Rd2'"
			[+] WPFRadioButton btnEnterMolecular
				[ ] locator "@automationId='Rd3'"
			[+] WPFRadioButton btnTurnOnProperty
				[ ] locator "@automationId='Rd4'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='OK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Cancel'"
			[+] WPFLabel LblTitle
				[ ] locator "@automationId='LblTitle'"
		[+] window WPFWindow wRequiredPropertiesInputComplet
			[ ] locator "/WPFWindow[@caption='*Properties Input Complete']"
			[+] WPFRadioButton rdRunPropertyAnalysis
				[ ] locator "@automationId='Rd0'"
			[+] WPFRadioButton rdGoToSimulationEnv
				[ ] locator "@automationId='Rd1'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='OK'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Cancel'"
		[+] window WPFWindow wCleanPropertyParameters
			[ ] locator "/WPFWindow[@caption='Clean Property Parameters']"
			[+] WPFGroupBox GroupBox_1
				[ ] locator "@automationId='GroupBox_1'"
			[+] WPFRadioButton rdlCleanResults
				[ ] locator "@automationId='radioCleanResults'"
			[+] WPFCheckBox chkRegressed
				[ ] locator "@automationId='chkRegressed'"
			[+] WPFCheckBox chkEstimated
				[ ] locator "@automationId='chkEstimated'"
			[+] WPFCheckBox chkRetrieved
				[ ] locator "@automationId='chkRetrieved'"
			[+] WPFRadioButton rdlPurgeIncomplete
				[ ] locator "@automationId='radioPurgeIncomplete'"
			[+] WPFRadioButton rdlioClearAll
				[ ] locator "@automationId='radioClearAll'"
			[+] WPFButton BtnOK
				[ ] locator "@automationId='btnOK'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btnCancel'"
			[+] WPFButton BtnHelp
				[ ] locator "@automationId='btnHelp'"
		[+] window WPFWindow wRequiredDataRegressionInputComplete
			[ ] locator "/WPFWindow[@caption='Required Data Regression Input Complete']"
			[+] WPFTextBlock txtBlock
				[ ] locator "@automationId='TxtBlock'"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='*OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='*Cancel']'"
		[ ] 
		[+] window WPFWindow wAvailablePropertyPackages
			[ ] locator "/WPFWindow[@caption='Available Property Packages']"
			[+] WPFLabel Name
				[ ] locator "//WPFLabel[@caption='Name']"
			[+] WPFTextBox txtName
				[ ] locator "//WPFTextBox[1]"
			[+] WPFLabel Description
				[ ] locator "//WPFLabel[@caption='Description']"
			[+] WPFTextBox txtDescription
				[ ] locator "//WPFTextBox[2]"
			[+] WPFLabel About
				[ ] locator "//WPFLabel[@caption='About']"
			[+] WPFTextBox txtAbout
				[ ] locator "//WPFTextBox[3]"
			[+] WPFLabel Vendor
				[ ] locator "//WPFLabel[@caption='Vendor']"
			[+] WPFTextBox txtVendor
				[ ] locator "//WPFTextBox[4]"
			[+] WPFLabel CapeOpenVersion
				[ ] locator "//WPFLabel[@caption='CAPE-OPEN version']"
			[+] WPFTextBox txtCapeOpenVersion
				[ ] locator "//WPFTextBox[5]"
			[+] WPFLabel ComponentVersion
				[ ] locator "//WPFLabel[@caption='Component version']"
			[+] WPFTextBox txtComponentVersion
				[ ] locator "//WPFTextBox[6]"
			[+] WPFLabel ComponentHelp
				[ ] locator "//WPFLabel[@caption='Component help']"
			[+] WPFButton btnHelp
				[ ] locator "//WPFButton[@caption='Help']"
			[+] WPFButton btnBtnDetail
				[ ] locator "//WPFButton[@automationId='btnDetail']"
			[+] WPFLabel PropertyPackages
				[ ] locator "//WPFLabel[@caption='Property Packages']"
			[+] WPFTreeView Tree
				[ ] locator "//WPFTreeView[@automationId='tree']"
			[+] WPFTreeViewItem trviAspenProperties
				[ ] locator "//WPFTreeViewItem[@caption='Aspen Properties']"
			[+] WPFTreeViewItem trviDefault
				[ ] locator "//WPFTreeViewItem[@caption='Default']"
			[+] WPFTreeViewItem trviHcgas
				[ ] locator "//WPFTreeViewItem[@caption='Hcgas']"
			[+] WPFTreeViewItem trviPfdtut
				[ ] locator "//WPFTreeViewItem[@caption='pfdtut']"
			[+] WPFTreeViewItem trviSimple
				[ ] locator "//WPFTreeViewItem[@caption='Simple']"
			[+] WPFTreeViewItem trviStandalonePropertyPackages
				[ ] locator "//WPFTreeViewItem[@caption='Standalone Property Packages']"
			[+] WPFButton btnOk
				[ ] locator "//WPFButton[@caption='OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
		[+] window WPFWindow wCapeOpenPackages
				[ ] locator "//WPFHeaderedContentControl[@automationId='_AnonymousScreen1']"
			[+] WPFContentControl PaneToolWindow
				[ ] locator "//WPFContentControl[@className='PaneToolWindow']"
			[+] WPFFrameworkElement Zc76f5374201a470999014bd62efc3
				[ ] locator "//WPFFrameworkElement[@automationId='Zc76f5374201a470999014bd62efc31a9']"
			[+] WPFHeaderedContentControl AnonymousScreen1
				[ ] locator "//WPFHeaderedContentControl[@automationId='_AnonymousScreen1']"
			[+] WPFContentControl ApwnFormContentHost
				[ ] locator "//WPFContentControl[@className='ApwnFormContentHost']"
			[+] WPFContentControl MMCOPackageList1D
				[ ] locator "//WPFContentControl[@className='MMCOPackage_List1D']"
			[+] WPFContentControl GrdChild
				[ ] locator "//WPFContentControl[@name='grdChild']"
			[+] WPFContentControl Name
				[ ] locator "//WPFContentControl[@caption='Name'][4]"
			[+] WPFControl PartDataGrid
				[ ] locator "//WPFControl[@automationId='PART_DataGrid']"
			[+] WPFItemsControl RecordListControl
				[ ] locator "//WPFItemsControl[@className='RecordListControl']"
			[+] WPFControl DataRecordPresenter
				[ ] locator "//WPFControl[@className='DataRecordPresenter']"
			[+] WPFButton btnSelectAll
				[ ] locator "//WPFButton[@automationId='SelectAll']"
			[+] WPFButton btnNew
				[ ] locator "//WPFButton[@caption='New...']"
			[+] WPFButton btnEdit
				[ ] locator "//WPFButton[@caption='Edit']"
			[+] WPFButton btnDelete
				[ ] locator "//WPFButton[@caption='Delete']"
			[+] WPFButton btnRename
				[ ] locator "//WPFButton[@caption='Rename']"
			[+] WPFButton btnImport
				[ ] locator "//WPFButton[@caption='Import']"
		[+] window MainWin wCapeOpenPropertyPackageManagerClassic
			[+] multitag "AspenTech CAPE-OPEN Property Package Manager"
				[ ] "$C:\Program Files*\AspenTech\APrSystem*\Engine\xeq\Cotappm.exe"
			[ ] glwcDlgSaveFile   dlgSaveAsFile
			[+]  DialogBox dlgCOTAPPM
				[ ] tag "COTAPPM"
				[+] PushButton btnYes
					[+] multitag "Yes"
						[ ] "$6"
				[+] PushButton btnNo
					[+] multitag "No"
						[ ] "$7"
				[+] PushButton btnOK
					[+] multitag "OK"
						[ ] "$2"
		[+] window MainWin wCapeOpenPropertyPackageManager
			[ ] locator "/MainWin[@caption='AspenTech CAPE-OPEN Property Package Manager']"
			[+] void Invoke()
				[+] if APR.Exists()
					[ ] APR.SetActive()
					[ ] APR.TypeKeys("<Alt>FEC",0.5)
					[+] if !this.Exists(10)
						[ ] APR.SetActive()
						[ ] APR.TypeKeys("<Alt>FTC",0.5)
				[+]  else
					[ ] APlus.SetActive()
					[ ] APlus.TypeKeys("<Alt>FTC",0.5)
					[+] if !this.Exists(10)
						[ ] APlus.SetActive()
						[ ] APlus.TypeKeys("<Alt>FTC",0.5)
			[+] Menu mnuFile
				[ ] locator "//Menu[@caption='File']"
			[+] MenuItem miSaveAndRegister
				[ ] locator "//MenuItem[@caption='Save and register']"
			[+] MenuItem miMenuItem
				[ ] locator "//MenuItem[2]"
			[+] MenuItem miRecentFile
				[ ] locator "//MenuItem[@caption='Recent File']"
			[+] MenuItem miExit
				[ ] locator "//MenuItem[@caption='Exit']"
			[+] Menu mnuTools
				[ ] locator "//Menu[@caption='Tools']"
			[+] MenuItem miUnregisterPropertyPackages
				[ ] locator "//MenuItem[@caption='Unregister Property Packages']"
			[+] Menu mnuView
				[ ] locator "//Menu[@caption='View']"
			[+] MenuItem miToolbar
				[ ] locator "//MenuItem[@caption='Toolbar']"
			[+] Menu mnuHelp
				[ ] locator "//Menu[@caption='Help']"
			[+] MenuItem miAboutCotappm
				[ ] locator "//MenuItem[@caption='About COTAPPM']"
			[+] TextField txtName
				[ ] locator "//TextField[1]"
			[+] TextField Description
				[ ] locator "//TextField[@caption='Description']"
			[+] TextField Vendor
				[ ] locator "//TextField[@caption='Vendor']"
			[+] TextField CoVersion
				[ ] locator "//TextField[@caption='CO Version']"
			[+] TextField CompVersion
				[ ] locator "//TextField[@caption='Comp. Version']"
			[+] PushButton btnSaveAndRegister
				[ ] locator "//PushButton[@caption='Save and Register']"
			[+] ToolBar ToolBar
				[ ] locator "//ToolBar"
			[+] PushToolItem ptiSave
				[ ] locator "//PushToolItem[1]"
			[+] PushToolItem ptiUnRegister
				[ ] locator "//PushToolItem[2]"
			[+] PushButton pshSaveandRegister
				[ ] locator "//PushButton[@caption='Save and Register']"
			[+] DialogBox dlgSaveAs
				[ ] locator "//DialogBox[@caption='Save As']"
				[+] PushButton pshSave
					[ ] locator "//PushButton[@caption='Save']"
				[+] TextField txtFileName
					[ ] locator "//TextField"
			[+] DialogBox dlgCOTAPPM
				[ ] locator "//DialogBox[@caption='COTAPPM']"
				[+] PushButton pshYes
					[ ] locator "//PushButton[@caption='Yes']"
				[+] PushButton pshOK
					[ ] locator "//PushButton[@caption='OK']"
				[ ] 
			[+] SaveandRegister(string sFileName optional)
				[+] if !wCapeOpenPropertyPackageManager.Exists(2)
					[ ] sleep(2)
					[ ] this.Invoke()
					[ ] sleep(2)
				[ ] wCapeOpenPropertyPackageManager.pshSaveandRegister.Exists(40)
				[ ] sleep(3)
				[ ] wCapeOpenPropertyPackageManager.pshSaveandRegister.Click()
				[+] if this.dlgSaveAs.Exists(30)
					[ ] sleep(2)
					[ ] 
				[+] if sFileName!=null
					[ ] wCapeOpenPropertyPackageManager.dlgSaveAs.txtFileName.SetFocus()
					[ ] sleep(2)
					[ ] //wCapeOpenPropertyPackageManager.dlgSaveAs.txtFileName.TypeKeys("<Ctrl-A><Delete>")
					[ ] wCapeOpenPropertyPackageManager.dlgSaveAs.txtFileName.SetText("{sFileName}")
					[ ] sleep(2)
				[ ] this.dlgSaveAs.pshSave.Click()
				[+] if dlgCOTAPPM.pshYes.Exists(3)
					[ ] sleep(3)
					[ ] dlgCOTAPPM.pshYes.Click()
				[+] if dlgCOTAPPM.pshOK.Exists(3)
					[ ] sleep(3)
					[ ] dlgCOTAPPM.pshOK.Click()
		[+] window glwcMessageBox AspenPropertiesHelp
			[ ] tag "Aspen Properties Help"
			[+] ToolBar ToolBar1
				[ ] tag "$1006"
				[+] PushButton Hide
					[+] multitag "Hide"
						[ ] "$201"
				[+] PushButton Back
					[+] multitag "Back"
						[ ] "$204"
				[+] PushButton Forward
					[+] multitag "Forward"
						[ ] "$209"
				[+] PushButton Home
					[+] multitag "Home"
						[ ] "$205"
				[+] PushButton Print
					[+] multitag "Print"
						[ ] "$207"
				[+] PushButton Options
					[+] multitag "Options"
						[ ] "$208"
			[+] CustomWin ctlContents
				[ ] tag "[HH Child]$0[2]"
				[+] CustomWin ShellEmbedding1
					[ ] tag "[Shell Embedding]$0"
					[+] CustomWin ShellDocObjectView1
						[ ] tag "[Shell DocObject View]$0"
						[+] CustomWin InternetExplorer_Server1
							[ ] tag "[Internet Explorer_Server]$0"
			[+] CustomWin HHSizeBar1
				[ ] tag "[HH SizeBar]$0"
			[+] CustomWin HHChild1
				[ ] tag "[HH Child]$0[1]"
				[+] PageList PageList1
					[ ] tag "$1007"
					[+] glwcTvwFolder TreeView1
						[ ] tag "$0"
			[+] string GetTopic()
				[ ] this.SetActive()
				[ ] Clipboard.SetText()
				[ ] wAPrSystemHelp.ctlContents.Click(1,10,10)
				[ ] wAPrSystemHelp.TypeKeys("<Ctrl-a 3>", 1)
				[ ] wAPrSystemHelp.TypeKeys("<Ctrl-c 3>", 1)
				[ ] sleep(5)
				[ ] return Clipboard.GetText()[1]
				[ ] 
			[ ] 
		[+] window WPFWindow wGenerateBinaryVLEorLLEData
			[ ] locator "/WPFWindow[@caption='Generate Binary VLE or LLE Data']"
			[+] wcAPWPFComboBox cboPropertyMethod
				[ ] locator "//WPFControl[@automationId='PART_editControl'][4]"
			[+] WPFButton btnGenerate
				[ ] locator "//WPFButton[1]"
			[+] WPFButton btnNext
				[ ] locator "//WPFButton[2]"
			[+] WPFButton btnClose
				[ ] locator "//WPFButton[3]"
			[ ] 
		[+] window WPFWindow wChangedDataType
			[ ] locator "/WPFWindow[@caption='Changed Data Type']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='*OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='*Cancel']"
				[ ] 
		[+] window WPFWindow wDeviations
			[ ] locator "/WPFWindow[@caption='Deviations']"
			[+] wcAPWPFTextBox txbAverageDeviation
				[ ] locator "//WPFControl[@automationId='PART_editControl'][1]"
			[+] wcAPWPFTextBox txbMaximumDeviation
				[ ] locator "//WPFControl[@automationId='PART_editControl'][2]"
			[+] wcAPWPFTextBox txbRootMeanSquareError
				[ ] locator "//WPFControl[@automationId='PART_editControl'][3]"
			[+] wcAPWPFTextBox txbRootMeanSquareErrorPercent
				[ ] locator "//WPFControl[@automationId='PART_editControl'][4]"
			[+] wcAPWPFTextBox txbAverageAbsolute
				[ ] locator "//WPFControl[@automationId='PART_editControl'][5]"
			[+] wcAPWPFTextBox txbAverageAbsolutePercent
				[ ] locator "//WPFControl[@automationId='PART_editControl'][6]"
			[+] WPFButton btnClose
				[ ] locator "//WPFButton[@caption='Close']"
				[ ] // 
		[+] window WPFWindow wBinaryVLE
			[ ] locator "/WPFWindow[@caption='Binary VLE*']"
		[+] window WPFWindow wEditLegend
			[ ] locator "/WPFWindow[@caption='Edit Legend']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOk']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
			[ ] 
			[+] VerifyLegend(list of string lsExpected)
				[ ] // VerifyLegend({"Experiment data (Accepted)","Experiment data (Rejected)","Evaluated Results"})
				[ ] string sTemp
				[+] for each sTemp in lsExpected
					[+] do
						[ ] this.Find("//WPFDataGridRow[@caption='{sTemp}']")
					[+] except
						[ ] LogError("{sTemp} is expected in Legend Text")
	[ ] 
	[+] //Aspen Simulation Engine
		[+] window wcSimualtionEngineWindow wSimualtionEngineWindow
			[ ] 
			[ ] 
			[ ] 
		[ ] window wcSimualtionEngineWindow wSimulationEngineWindow  //MEH!
		[ ] 
	[ ] 
	[+] //Aspen Properties Calculation Engine
		[ ] window wcCalculationEngineWindow wCalculationEngineWindow
	[ ] 
	[+] //Command line prompt (cmd.exe dilalog)
		[+] window wcSimualtionEngineWindow wCmd
			[ ] tag "[DialogBox]*cmd.exe*"
			[ ] const sCmdLine = '{glsWINDIR}\system32\cmd.exe'
		[ ] 
	[ ] 
	[+] //Regional Settings
		[+] window glwcMessageBox wRegionAndLanguage
			[ ] tag "Region and Language|Region"
			[+] glwcMessageBox tabiFormats
				[+] multitag "Formats"
					[ ] "$0"
				[+] PopupList popFormat
					[+] multitag "Format:"
						[ ] "$1021"
				[+] PopupList popShortDate
					[+] multitag "Short date:"
						[ ] "$1028"
				[+] PopupList popLongDate
					[+] multitag "Long date:"
						[ ] "$1029"
				[+] PopupList popShortTime
					[+] multitag "Short time:"
						[ ] "$1030"
				[+] PopupList popLongTime
					[+] multitag "Long time:"
						[ ] "$1031"
				[+] PopupList popFirstDayOfWeek
					[+] multitag "First day of week:"
						[ ] "$1032"
				[+] PushButton btnAdditionalSettings
					[+] multitag "Additional settings"
						[ ] "$1024"
			[+] PushButton OK
				[+] multitag "OK"
					[ ] "$1"
			[+] PushButton Cancel
				[+] multitag "Cancel"
					[ ] "$2"
			[+] PushButton Apply
				[+] multitag "Apply"
					[ ] "$12321"
			[+] PageList PageList1
				[ ] tag "$12320"
			[ ] 
			[ ] 
		[+] window glwcMessageBox wCustomizeFormat
			[ ] tag "Customize Format"
			[ ] parent wRegionAndLanguage
			[+] glwcMessageBox tabiNumbers
				[+] multitag "Numbers"
					[ ] "$0"
				[+] TextField txtPositive
					[+] multitag "Positive:"
						[ ] "$1005"
				[+] TextField txtNegative
					[+] multitag "Negative:"
						[ ] "$1006"
				[+] ComboBox cboExample
					[+] multitag "Example"
						[ ] "$1070"
				[+] PopupList popNoOfDigitsAfterDecimal
					[+] multitag "No. of digits after decimal:"
						[ ] "$1072"
				[+] ComboBox cboDigitGroupingSymbol
					[+] multitag "Digit grouping symbol:"
						[ ] "$1073"
				[+] PopupList popDigitGrouping
					[+] multitag "Digit grouping:"
						[ ] "$1074"
				[+] ComboBox cboNegativeSignSymbol
					[+] multitag "Negative sign symbol:"
						[ ] "$1076"
				[+] PopupList popNegativeNumberFormat
					[+] multitag "Negative number format:"
						[ ] "$1078"
				[+] PopupList popDisplayLeadingZeros
					[+] multitag "Display leading zeros:"
						[ ] "$1080"
				[+] ComboBox cboListSeparator
					[+] multitag "List separator:"
						[ ] "$1079"
				[+] PopupList popMeasurementSystem
					[+] multitag "Measurement system:"
						[ ] "$1081"
				[+] PopupList popStandardDigits
					[+] multitag "Standard digits:"
						[ ] "$1083"
				[+] PopupList popUseNativeDigits
					[+] multitag "Use native digits:"
						[ ] "$1085"
				[+] PushButton btnReset
					[+] multitag "Reset"
						[ ] "$1046"
			[+] PushButton btnOK
				[+] multitag "OK"
					[ ] "$1"
			[+] PushButton btnCancel
				[+] multitag "Cancel"
					[ ] "$2"
			[+] PushButton btnApply
				[+] multitag "Apply"
					[ ] "$12321"
			[+] PageList PageList1
				[ ] tag "$12320"
			[ ] 
			[ ] 
			[ ] 
	[ ] 
	[+] //Analysis
		[+] window WPFWindow wDistillationSynthesis
			[ ] locator "//*[@caption='Distillation Synthesis']"
			[+] WPFTreeViewItem trviTenaryPlot
				[ ] locator "//WPFTreeViewItem[@caption='Ternary Plot']"
			[+] WPFButton btnLearnMore
				[ ] locator "//WPFButton[@automationId='BtnLm']"
			[+] WPFButton btnFindAzeotropes
				[ ] locator "//WPFButton[@automationId='BtnFa']"
			[+] WPFButton btnUseDistillationSynthesis
				[ ] locator "//WPFButton[@automationId='BtnUds']"
			[+] WPFButton btnContinueToAspenPlusResidueCurves
				[ ] locator "//WPFButton[@automationId='BtnCta']"
				[ ] 
		[+] //Curves
			[+] window WPFWindow wCustomCurve
				[ ] locator "/WPFWindow[@caption='Custom']"
				[+] WPFUserControl lsCurveList
					[ ] locator "@automationId='CurveList'"
					[+] WPFContentControl SelectAll
						[ ] locator "[@caption='Select all'][1]"
					[+] WPFCheckBox chkSelectAll
						[ ] locator "@automationId='PART_CheckBox'"
					[+] WPFLabel SelectAllLabel
						[ ] locator "Select all"
				[+] WPFButton btnOK
					[ ] locator "OK"
				[+] WPFButton btnCancel
					[ ] locator "Cancel"
				[+] WPFComboBox	cboXAxis
					[ ] locator "//WPFComboBox[@automationId='ComboBoxXAxis']"
			[+] window WPFWindow wParametric
				[ ] locator "/WPFWindow[@caption='Parametric']"
				[+] WPFComboBox cboXAxis
					[ ] locator "@automationId='ComboBoxXAxis'"
				[+] WPFComboBox cboParaVar
					[ ] locator "@automationId='ComboBoxParaVar'"
				[+] WPFListBox lbCurvesList
					[ ] locator "@automationId='CurvesList'"
					[+] WPFCheckBox chkSelectAll
						[ ] locator "@automationId='PART_CheckBox'"
				[+] WPFButton btnOK
					[ ] locator "OK"
				[+] WPFButton btnCancel
					[ ] locator "Cancel"
			[ ] 
		[ ] 
	[ ] 
	[+] //Notepad
		[+] window MainWin wNotepad
			[+] multitag "*.txt*Notepad*"
				[ ] "*Notepad"
				[ ] "$C:\Windows\system32\notepad.exe"
			[ ] const sCmdLine = "C:\Windows\system32\notepad.exe"
			[+] Menu mnuFile
				[ ] tag "File"
				[+] MenuItem miNew
					[+] multitag "New"
						[ ] "$1"
				[+] MenuItem miOpen
					[+] multitag "Open"
						[ ] "$2"
				[+] MenuItem miSave
					[+] multitag "Save"
						[ ] "$3"
				[+] MenuItem miSaveAs
					[+] multitag "Save As"
						[ ] "$4"
				[+] MenuItem miPageSetup
					[+] multitag "Page Setup"
						[ ] "$5"
				[+] MenuItem miPrint
					[+] multitag "Print"
						[ ] "$6"
				[+] MenuItem miExit
					[+] multitag "Exit"
						[ ] "$7"
			[+] Menu mnuEdit
				[ ] tag "Edit"
				[+] MenuItem miUndo
					[+] multitag "Undo"
						[ ] "$16"
				[+] MenuItem miCut
					[+] multitag "Cut"
						[ ] "$768"
				[+] MenuItem miCopy
					[+] multitag "Copy"
						[ ] "$769"
				[+] MenuItem miPaste
					[+] multitag "Paste"
						[ ] "$770"
				[+] MenuItem miDelete
					[+] multitag "Delete"
						[ ] "$771"
				[+] MenuItem miFind
					[+] multitag "Find"
						[ ] "$21"
				[+] MenuItem miFindNext
					[+] multitag "Find Next"
						[ ] "$22"
				[+] MenuItem miReplace
					[+] multitag "Replace"
						[ ] "$23"
				[+] MenuItem miGoTo
					[+] multitag "Go To"
						[ ] "$24"
				[+] MenuItem miSelectAll
					[+] multitag "Select All"
						[ ] "$25"
				[+] MenuItem miTimeDate
					[+] multitag "Time?Date"
						[ ] "$26"
			[+] Menu mnuFormat
				[ ] tag "Format"
				[+] MenuItem miWordWrap
					[+] multitag "Word Wrap"
						[ ] "$32"
				[+] MenuItem miFont
					[+] multitag "Font"
						[ ] "$33"
			[+] Menu mnuView
				[ ] tag "View"
				[+] MenuItem miStatusBar
					[+] multitag "Status Bar"
						[ ] "$27"
			[+] Menu mnuHelp
				[ ] tag "Help"
				[+] MenuItem miViewHelp
					[+] multitag "View Help"
						[ ] "$64"
				[+] MenuItem miAboutNotepad
					[+] multitag "About Notepad"
						[ ] "$65"
			[+] TextField TextField1
				[ ] tag "$15"
			[+] TextField TextField2
				[ ] locator "//TextField"
			[ ] 
	[ ] 
	[+] //Help
		[+] window MainWin wAPHelp
			[ ] locator "/MainWin[@caption='APrSystem Help']"
			[+] DomElement txtAnalysisPureComp
				[ ] locator "//H3[@textContents='Analysis Pure Component Input Pure*']"
			[+] PageList TabControl
				[ ] locator "//PageList"
			[+] TreeView Tree
				[ ] locator "//TreeView"
	[ ] 
	[+] // Other windows invoked from PFS area
		[+] window WPFWindow wBubbleAndDewPointCurve
			[ ] locator "/WPFWindow[@caption='Bubble and Dew Point Curve']"
			[+] WPFButton btnGo
				[ ] locator "//WPFButton[@caption='Go']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
				[ ] 
		[+] window WPFWindow wBubbleAndDewPointCurveResults
			[ ] locator "/WPFWindow[@caption='*Bubble and Dew Point Curve Results']"
		[+] window WPFWindow wBubbleAndDewPointCurvePlot
			[ ] locator "/WPFWindow[@caption='*Bubble and Dew Point Curve - Plot']"
		[+] window WPFWindow wPVCurve
			[ ] locator "/WPFWindow[@caption='Pressure vs. Vapor Fraction Curve']"
			[+] WPFButton btnGo
				[ ] locator "//WPFButton[@caption='Go']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
				[ ] 
		[+] window WPFWindow wPVCurvePlot
			[ ] locator "/WPFWindow[@caption='*Pressure vs. Vapor Fraction Curve - Plot']"
		[+] window WPFWindow wPVCurveResults
			[ ] locator "/WPFWindow[@caption='*Pressure vs. Vapor Fraction Curve Results']"
		[+] window WPFWindow wTVCurve
			[ ] locator "/WPFWindow[@caption='Temperature vs. Vapor Fraction Curve']"
			[+] WPFButton btnGo
				[ ] locator "//WPFButton[@caption='Go']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
				[ ] 
		[+] window WPFWindow wTVCurvePlot
			[ ] locator "/WPFWindow[@caption='*Temperature vs. Vapor Fraction Curve - Plot']"
		[+] window WPFWindow wTVCurveResults
			[ ] locator "/WPFWindow[@caption='*Temperature vs. Vapor Fraction Curve Results']"
		[+] window WPFWindow wDistillationCurve
			[ ] locator "/WPFWindow[@caption='Distillation Curve']"
			[+] WPFButton btnGo
				[ ] locator "//WPFButton[@caption='Go']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
				[ ] 
		[+] window WPFWindow wDistCurve
			[ ] locator "/WPFWindow[@caption='Dist-Curve']"
			[+] WPFListBox lstCurvesList
				[ ] locator "//WPFListBox[@automationId='CurvesList']"
				[+] WPFCheckBox chkSelectAll
					[ ] locator "//WPFCheckBox[@automationId='PART_CheckBox']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='OK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@caption='Cancel']"
				[ ] 
		[+] window WPFWindow wDistillationCurvePlot
			[ ] locator "/WPFWindow[@caption='*Distillation Curve - Plot']"
		[+] window WPFWindow wDistillationCurveResults
			[ ] locator "/WPFWindow[@caption='*Distillation Curve Results']"
	[ ] 
	[+] // Find
		[+] window MainWin wFind
			[ ] locator "//DialogBox[@caption='Find']"
			[+] TextField txtFind
				[ ] locator "//TextField[@caption='Find what:']"
				[ ] //locator "//DialogBox[@caption='Find']//TextField[@caption='Find what:']"
				[ ] 
				[ ] 
			[+] WPFButtonBase btnNext
				[ ] locator "PushButton[@caption='Find Next']"
			[+] WPFButtonBase btnCancel
				[ ] locator "//PushButton[@caption='Cancel']"
	[ ] 
	[+] //PROII to Aspen Plus converter
		[+] window wcPROIIConverter wPROIIConverter
			[+] void Convert(int iTimeOut optional)
				[ ] //Convert the file to Aspen plus
				[ ] //   Arguments
				[ ] //   1.  iTimeOut , int, default 120 seconds.  time out for convert process.
				[ ] this.SetActive()
				[ ] this.ToolBarTray.ToolBar.BtnRun.Click()
				[ ] sleep(5)
				[ ] HANDLE hTimer
				[ ] hTimer = TimerCreate ()
				[ ] TimerStart (hTimer)
				[+] if iTimeOut == null
					[ ] iTimeOut = 120
				[ ] this.SetActive()
				[+] while(wWaiting.Exists() && (TimerValue(hTimer) < iTimeOut))
					[ ] int i = 0
					[ ] 
					[+] while (wColumnSizingAndRatingDetected.Exists(15))
						[ ] wColumnSizingAndRatingDetected.SetActive()
						[ ] wColumnSizingAndRatingDetected.BtnNo.Click()
						[ ] i++
					[+] if i > 1
						[ ] Log.Error("Column Sizing And Rating Detected dialog pops up {i} times")
				[ ] 
				[ ] TimerStop (hTimer)
				[ ] string sTime = TimerStr(hTimer)
				[ ] print("Approximate convert TIme: {sTime} seconds")
				[ ] real rTime = TimerValue (hTimer)
				[ ] TimerDestroy(hTimer)
				[+] if( rTime> iTimeOut)
					[ ] RaiseError(-1, "Process was not able to convert within max timeout of {iTimeOut} seconds")
				[ ] wPROII_AP.Exists(30)
				[ ] wPROII_AP.SetActive()
				[ ] wPROII_AP.Maximize()
		[+] window WPFWindow wWaiting
			[ ] locator "/WPFWindow[@caption='Waiting']"
			[+] WPFTextBlock Exporting
				[ ] locator "Exporting ..."
			[+] WPFProgressBar PgsWaitting
				[ ] locator "@automationId='pgsWaitting'"
		[+] window wcAspenPlus wPROII_AP
			[ ] locator "/WPFWindow[@caption='*Aspen Plus {sVersion}*']"
			[+] Export (string sFileName)
				[ ] // Export ( string )  - Exports a file
				[ ] //   Arguments
				[ ] //   1.  fileName , string, name of export file - extension determines type of file to export
				[ ] //   Usage:  this.Export('c:\\temp\\pfdtut.inp')
				[+] if sys_FileExists(sFileName)
					[ ] Sys_Execute('del /f /q "{sFileName}"')
				[ ] string sExtenison = glGetReverseField(sFileName, ".", 1)
				[ ] string sBaseFileName = SubStr(sFileName,1, len(sFileName) - len(sExtenison)-1)
				[+] if sys_DirExists(sBaseFileName)
					[ ] sys_execute('rd /s /q "{sBaseFileName}"')
				[ ] this.SetActive()
				[+] if (this.GetMode() == "Properties") && ("rep" == Lower(sExtenison) || "inp" == Lower(sExtenison)|| "xml" == Lower(sExtenison))
					[+] switch (lower(sExtenison))
						[+] case "rep"
							[ ] this.TypeKeys("<Ctrl-Alt-R>")
						[+] case "inp"
							[ ] this.TypeKeys("<Ctrl-Alt-I>")
						[+] case "xml"
							[ ] this.TypeKeys("<Ctrl-Alt-X>")
					[ ] glwNotepad.Exists(20)
					[ ] glwNotepad.SetActive()
					[ ] glwNotepad.SaveFile(sFileName)
					[ ] glwNotepad.SetActive()
					[ ] glwNotepad.mnuFile.miExit.Pick()
					[+] if glwNotepad.Exists(5)
						[ ] glwNotepad.Exit()
					[+] if File.Exists(sFileName + '.txt')
						[ ] disconnectall()
						[ ] connect(null, CLASSIC_AGENT)
						[ ] Sys_Movefile(sFileName,strtran(sFileName, ".txt", ""))
					[+] if File.Exists(sFileName)
						[ ] Log.Pass("Save file {sBaseFileName} as {upper(sExtenison)} successfully!!!")
				[+] else
					[ ] this.mnuFile.Click()
					[ ] this.miExport.Exists(5)
					[ ] this.miExport.Click()
					[ ] this.miFile.Exists(5)
					[ ] this.miFile.Click()
					[ ] dlgExport.Exists(20)
					[ ] sleep(1)
					[ ] dlgExport.exists(10)
					[ ] dlgExport.SetActive()
					[ ] dlgExport.cboSaveAsType.Select("*.{Lower(sExtenison)}*")
					[ ] dlgExport.txtFileName.SetText(sBaseFileName)
					[+] dlgExport.btnSave.Click()
						[ ] 
					[+] if( dlgConfirmSaveAs.Exists(2) )
						[ ] dlgConfirmSaveAs.btnYes.Click()
						[ ] 
					[ ] glWaitForMouseIdle(60)
					[ ] int i = 0
					[+] while( dlgExport.Exists() && i < 60)
						[ ] sleep(0.5)
						[ ] i++
					[ ] 
					[ ] this.SetActive()
				[ ] 
		[+] window WPFWindow wColumnSizingAndRatingDetected
			[ ] locator "/WPFWindow[@caption='Column Sizing and Rating Detected']"
			[+] WPFImage HeaderImage
				[ ] locator "@automationId='HeaderImage'"
			[+] WPFTextBlock TxtBlock
				[ ] locator "@automationId='TxtBlock'"
			[+] WPFButton BtnYes
				[ ] locator "@automationId='btn0'"
			[+] WPFButton BtnNo
				[ ] locator "@automationId='btn1'"
		[+] window WPFWindow wUpwardsCompatibilityTrayRating
			[ ] locator "/WPFWindow[@caption='Upwards Compatibility: Tray Rating']"
			[+] WPFTextBlock txtTextBlock_1
				[ ] locator "@automationId='TextBlock_1'"
			[+] WPFCheckBox ChkDontshow
				[ ] locator "@automationId='chkDontshow'"
			[+] WPFButton BtnYes
				[ ] locator "@automationId='btn0'"
			[+] WPFButton BtnNo
				[ ] locator "@automationId='btn1'"
		[ ] 
	[ ] 
	[+] //TQ Curves
		[+] window WPFWindow wTQCurves
			[ ] locator "/WPFWindow[@caption='TQ Curves']"
			[+] WPFCheckBox chkSelectAll
				[ ] locator "@automationId='PART_CheckBox'"
			[+] WPFCheckBox chkINLET
				[ ] locator "INLET"
			[+] WPFCheckBox chkOUTLET
				[ ] locator "OUTLET"
			[+] WPFButton btnOK
				[ ] locator "OK"
			[+] WPFButton btnCancel
				[ ] locator "Cancel"
	[ ] 
	[+] window WPFWindow wZoom
		[ ] locator "/WPFWindow[@caption='Zoom']"
		[+] WPFRadioButton rdCustom
			[ ] locator "//WPFRadioButton[6]"
		[+] wcAPWPFTextBox txbZoom
			[ ] locator "//WPFControl[@automationId='_zoomTextBox']"
		[+] WPFButton btnOK
			[ ] locator "//WPFButton[1]"
		[+] WPFButton btnCancel
			[ ] locator "//WPFButton[2]"
			[ ] 
	[ ] 
	[+] //WinZip
		[+] window wcWinZip wWinZip
			[ ] locator "/MainWin[@caption='WinZip Pro*']"
			[ ] 
	[ ] 
	[+] //Internet Explorer
		[+] window BrowserApplication wInternetExplorer
			[ ] locator "/BrowserApplication"
			[+] DomElement body
				[ ] locator "//BrowserWindow//BODY"
			[ ] 
			[+] DialogBox dlgMessage
				[ ] locator "//DialogBox"
				[+] PushButton btnCancel
					[ ] locator "//PushButton[@caption='Cancel']"
				[+] PushButton btnOK
					[ ] locator "//PushButton[@caption='OK']"
			[ ] 
			[+] AnyWin tpgCQ
				[ ] locator "//BrowserWindow"
				[ ] string currentID = NULL
				[+] DomTextField txbSearchID
					[ ] locator "//INPUT[@id='cqFindRecordString']"
				[+] DomButton btnSearch
					[ ] locator "//BUTTON[@id='cqFindRecordButton']"
				[+] DomTextField txbTestCount
					[ ] locator "//DIV[@id='cq_widget_CqFormEdit*'][7]/TABLE[@cellPadding='0']//INPUT[@aria-valuenow='*']"
				[+] DomElement txtOpenId
					[ ] locator "//TD[@textContents='TestCase:{currentID}']"
				[+] DomElement btnModify
					[ ] locator "//SPAN[@textContents='Modify']"
				[+] DomButton btnSave
					[ ] locator "//SPAN[@textContents='Save'][1]"
				[+] DomElement btnResults
					[ ] locator "//SPAN[@textContents='Results']"
				[+] DomElement btnNew
					[ ] locator "//SPAN[@textContents='New']"
				[+] DomElement lbNewRecord
					[ ] locator "//SPAN[@textContents='New Record']"
				[+] DomElement btnSaveResults
					[ ] locator "//SPAN[@textContents='Save'][2]"
				[+] DomTextField txbVersion
					[ ] locator "//TABLE[@id='widget_cq_widget_CqF*'][1]//INPUT[@id='cq_widget_CqFilterin*']"
				[+] DomTextField txbBuild
					[ ] locator "//INPUT[@maxLength='50'][1]"
				[+] DomTextField txbOS
					[ ] locator "//TABLE[@id='widget_cq_widget_CqF*'][2]//INPUT[@id='cq_widget_CqFilterin*']"
				[+] DomTextField txbPassCount
					[ ] locator "//INPUT[@id='cq_widget_CqNumberTe*'][1]"
				[+] DomElement errorWindow
					[ ] locator "//DIV[@id='cq_widget_CqMessageD*']"
				[+] DomElement btnClose 
					[ ] locator "//SPAN[@textContents='Close']"
				[+] DomElement btnCloseNode
					[ ] locator "//SPAN[@dojoAttachPoint='closeButtonNode']"
	[+] //Other
		[+] window WPFWindow wResolveIDConflicts
			[ ] locator "/WPFWindow[@caption='Resolve ID Conflicts']"
			[+] WPFButton btnMerge
				[ ] locator "//WPFButton[@automationId='Merge']"
			[+] WPFButton btnEditID
				[ ] locator "//WPFButton[@automationId='EditID']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='Ok']"
			[+] WPFListView lsvConflictIDList
				[ ] locator "//WPFListView[@automationId='ConflictIDList']"
		[+] window WPFWindow wAdvancedOptions
			[ ] locator "/WPFWindow[@caption='Advanced Options']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btn_OK']"
			[+] WPFButton btnRestoreMessages
				[ ] locator "//WPFButton[@automationId='btnBringBackMessages']"
			[+] WPFButton btnRestoreReminders
				[ ] locator "//WPFButton[@automationId='btnBringBackReminders']"
				[ ] 
		[+] window WPFWindow wReboilerWizard
			[ ] locator "/WPFWindow[@caption='Reboiler Wizard']"
			[+] WPFTextBox txbReboilerType
				[ ] locator "@automationId='textBox1'"
			[+] WPFTextBox txbPseudoStreamID
				[ ] locator "@automationId='textBox2'"
			[+] WPFComboBox cboBlockID
				[ ] locator "@automationId='CmbBlockID'"
			[+] WPFComboBox cboType
				[ ] locator "@automationId='ComboBox_1'"
			[+] WPFComboBox cboMode
				[ ] locator "@automationId='ComboBox_2'"
			[+] WPFComboBox cboCirculationType
				[ ] locator "@automationId='ComboBox_3'"
			[+] WPFButton btnBrowse
				[ ] locator "@automationId='Button_1'"
			[+] WPFTextBox txbFilePath
				[ ] locator "@automationId='TextBox_1'"
			[+] WPFComboBox cboFlashBlockID
				[ ] locator "@automationId='CmbFlashBlockID'"
			[+] WPFTextBox txbFirstCalculationBlockID
				[ ] locator "@automationId='TextBox_2'"
			[+] WPFTextBox  txbSecondCalculationBlockID
				[ ] locator "@automationId='TextBox_3'"
			[+] WPFTextBox  txbDampingFactor
				[ ] locator "@automationId='TextBox_4'"
			[+] WPFCheckBox chkMoveToHierachyBlock
				[ ] locator "@automationId='CheckBox_1'"
			[+] WPFComboBox cboHierachyBlock
				[ ] locator "@automationId='CmbMoveToHierarchy'"
			[+] WPFCheckBox chkMaintainLinkToTheseBlocks
				[ ] locator "@automationId='CheckBox_2'"
			[+] WPFButton btnOK
				[ ] locator "@automationId='Button_2'"
			[+] WPFButton btnCancel
				[ ] locator "@automationId='Button_3'"
			[+] WPFButton btnHelp
				[ ] locator "@automationId='Button_4'"
		[+] window WPFWindow wRateConstantParameters
			[ ] locator "/WPFWindow[@caption='Rate Constant Parameters']"
			[+] WPFButton btnClose
				[ ] locator "Close"
			[+] WPFButton btnGetRateConstants
				[ ] locator "Get Rate Constants"
		[ ] 
	[ ] 
	[+] //Economics
		[+] window WPFWindow wMapOptions
			[ ] locator "/WPFWindow[@caption='Map Options']"
			[+] WPFGroupBox grpSource
				[ ] locator "//WPFGroupBox[@automationId='grpSource']"
				[+] WPFRadioButton rdMapSelected
					[ ] locator "//WPFRadioButton[1]"
				[+] WPFRadioButton rdMapAll
					[ ] locator "//WPFRadioButton[2]"
			[+] WPFGroupBox grpBasis
				[ ] locator "//WPFGroupBox[@automationId='grpBasis']"
				[+] WPFRadioButton rdLastMapping
					[ ] locator "//WPFRadioButton[1]"
				[+] WPFRadioButton rdDefault
					[ ] locator "//WPFRadioButton[2]"
			[+] WPFGroupBox grpEvaluateOptions
				[ ] locator "//WPFGroupBox[@automationId='grpEvaluate']"
				[+] WPFCheckBox chkSizeEquipment
					[ ] locator "//WPFCheckBox[1]"
				[+] WPFCheckBox chkCustomSizing
					[ ] locator "//WPFCheckBox[2]"
				[+] WPFCheckBox chkEvaluateCost
					[ ] locator "//WPFCheckBox[3]"
					[ ] 
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[1]"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[2]"
		[+] window WPFWindow wMapPreview
			[ ] locator "/WPFWindow[@caption='MapPreview']"
			[+] WPFListBox lsbUnitOperations
				[ ] locator "//WPFListBox[@automationId='lbUnitOp']"
			[+] WPFComboBox cboConfiguration
				[ ] locator "//WPFComboBox[@automationId='cbConfig']"
			[+] WPFListView lsvMapping
				[ ] locator "//WPFListView[@automationId='lstMapping']"
			[+] WPFButton btnAdd
				[ ] locator "//WPFButton[1]"
			[+] WPFButton btnDelete
				[ ] locator "//WPFButton[2]"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[3]"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[4]"
		[+] window WPFWindow wEquipmentSelection
			[ ] locator "/WPFWindow[@caption='Equipment Selection']"
			[+] WPFListBox lsbType
				[ ] locator "//WPFListBox[@automationId='lbType']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOk']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnOk']"
			[ ] 
	[ ] 
	[+] //Energy Analysis 
		[+] window WPFWindow wEnergyAnalysisOptions
			[ ] locator "/WPFWindow[@caption='Energy Analysis Options']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@automationId='btnOK']"
			[+] WPFButton btnCancel
				[ ] locator "//WPFButton[@automationId='btnCancel']"
			[+] WPFToggleButton btnCustomize
				[ ] locator "//WPFToggleButton[@caption='Customize']"
			[+] WPFToggleButton btnFlowsheetSelection
				[ ] locator "//WPFToggleButton[@caption='Flowsheet Selection']"
			[+] WPFTextBox txbApproachTemperature
				[ ] locator "//WPFTextBox[@className='MMTextBox']"
			[+] WPFComboBox cboProcessType
				[ ] locator "//WPFComboBox[@automationId='ProcessTypeCombox']"
	[ ] 
	[+] //Excel Windows for integrated testing
		[ ] window wcMicrosoftExcel Excel
		[+] window MainWin wGoTo
			[ ] locator "//MainWin[@caption='Go To']"
			[ ] parent Excel
			[+] Control txbCell
				[ ] locator "//Control[1]"
			[ ] 
		[+] window MainWin wExcelSaveWarning
			[ ] locator "/MainWin[@caption='Microsoft Excel*']//MainWin[@caption='Microsoft Excel']"
			[ ] 
		[ ] 
		[ ] 
	[ ] 
	[+] //Summary Grid
		[+] window FormsWindow wAspenSummaryGridMain
			[ ] locator "/FormsWindow[@caption='Aspen Summary Grid']"
			[+] WPFRadioButton rdAllTablesInOne
				[ ] locator "//WPFRadioButton[@automationId='radTablesOnSameWs']"
			[+] WPFCheckBox chkExportVariableLink
				[ ] locator "//WPFUserControl[@automationId='elementHost1']//WPFCheckBox[@caption='Export variable link*']"
			[+] WPFButton btnExport
				[ ] locator "//WPFUserControl[@automationId='elementHost1']//WPFButton[@caption='Export tables to Excel']"
			[+] WPFButton btnClose
				[ ] locator "//WPFUserControl[@automationId='elementHost1']//WPFButton[@automationId='btnClose']"
			[ ] 
		[+] window FormsWindow wAspenSummaryGridStatus// Because there are 2 windows open at once with the same name
			[ ] locator "/FormsWindow[@caption='Aspen Summary Grid'][2]"
			[+] WPFTextBlock txbStatus
				[ ] locator "//WPFUserControl[@automationId='elementHost1']//WPFTextBlock[1]"
			[+] WPFCheckBox chkOpenInExcel
				[ ] locator "//WPFCheckBox[@automationId='chkOpenExportedExcelFile']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='OK']"
		[+] window DialogBox wAspenSummaryGridSave
			[ ] locator "//DialogBox[@caption='Aspen Summary Grid']"
			[+] TextField txbFileName
				[ ] locator "//TextField"
			[+] ComboBox cboFileType
				[ ] locator "//ComboBox[2]"
			[+] PushButton btnSave
				[ ] locator "//PushButton[@caption='Save']"
			[+] PushButton btnCancel
				[ ] locator "//PushButton[@caption='Cancel']"
		[+] window FormsWindow wAspenSimulationWorkbookLink
			[ ] locator "/FormsWindow[@caption='Aspen Simulation Workbook']"
			[+] PushButton btnYes
				[ ] locator "//PushButton[@automationId='cmdYes']"
			[+] PushButton btnNo
				[ ] locator "//PushButton[@automationId='cmdNo']"
			[+] PushButton btnCancel
				[ ] locator "//PushButton[@automationId='cmdCancel']"
			[ ] 
		[+] window DialogBox wAspenSimulationWorkbookConnect
			[ ] locator "/DialogBox[@caption='Aspen Simulation Workbook']"
			[+] PushButton btnYes
				[ ] locator "//PushButton[@caption='Yes']"
			[+] PushButton btnNo
				[ ] locator "//PushButton[@caption='No']"
				[ ] 
		[+] window MainWin wAspenSimulationWorkbookWarning
			[ ] locator "/MainWin[@caption='Aspen Simulation Workbook']"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@caption='OK']"
		[+] window FormsWindow wAspenSimulationWorkbookStatus
			[ ] locator "/FormsWindow[@caption='Aspen Simulation Workbook']"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@automationId='cmdOk']"
			[+] StaticText txtInfo
				[ ] locator "//StaticText[@automationId='lblMsgBody']"
			[+] WPFControl txbStatus
				[ ] locator "//Control[@automationId='lblMsgTitle']"
		[+] window DialogBox wAspenSimulationWorkbookError
			[ ] locator "/DialogBox[@caption='Aspen Simulation Workbook']"
			[+] StaticText txtError
				[ ] locator "//StaticText[2]"
			[+] PushButton btnOK
				[ ] locator "//PushButton[@caption='OK']"
	[ ] 
	[+] //Energy Analysis
		[+] window WPFWindow wRetrofitProgress
			[ ] locator "/WPFWindow[@className='ProcessBarWindow']"
			[+] WPFButton btnOK
				[ ] locator "//WPFButton[@caption='OK']"
			[+] WPFTextBlock txbStatus
				[ ] locator "//WPFTextBlock[2]"
		[ ] 
	[ ] 
	[+] //Microsoft Word
		[+] window MainWin wMicrosoftWord
			[ ] locator "/MainWin[@caption='*Word']"
			[ ] const sCmdLine ="{sProgramFilePath}\Microsoft Office\Office15\WINWORD.EXE" //office 2010
			[ ] 
			[+] void Invoke()
				[+] if !this.Exists(2)
					[ ] derived::Invoke()
					[ ] sleep(5)
				[ ] this.SetActive()
			[ ] 
	[+] 
		[+] window MainWin wAspenCustomModeler
			[ ] locator "/MainWin[@caption='*Aspen Custom Modeler* aspenONE']"
			[ ] const sExampleFolder="{sProgramFilePath}\AspenTech\Aspen Custom Modeler {sVersion}\Examples"
			[ ] const sCmdLine ="{sProgramFilePath}\AspenTech\AMSystem {sVersion}\Bin\AspenModeler.exe" //Version TBD
			[+] //menu
				[+] Menu mnuTools
					[ ] locator "//Menu[@caption='Tools']"
					[+] MenuItem miConfigureProperties
						[ ] locator "//MenuItem[@caption='Configure Properties']"
				[+] Menu mnuFile
					[ ] locator "//Menu[@caption='File']"
					[+] MenuItem miOpen
						[ ] locator "//MenuItem[@caption='Open']"
			[+] //window
				[+] MainWin mainExploringSimulation
					[ ] locator "//MainWin[@caption='Exploring - Simulation']"
					[+] TreeView trvAllItems
						[ ] locator "//TreeView[@caption=' All Items']"
					[+] ListViewEx lsvContentsofFlowsheet
						[ ] locator "//ListViewEx[@caption=' Contents of Flowsheet']"
			[+] //StatusBar
				[+] StatusBar stbReady
					[ ] locator "//StatusBar[@caption='Ready']"
			[ ] 
			[+] //DialogBox
				[+] DialogBox dlgPropertiesConfiguration
					[ ] locator "//DialogBox[@caption='Physical Properties Configuration']"
					[ ] 
					[+] RadioList rdUseAspenProperties
						[ ] locator "//RadioList[@caption='Use Aspen property system']"
					[+] PushButton btnImportAspenPropertiesFile
						[ ] locator "//PushButton[@caption='Import Aspen Properties file']"
					[+] PushButton btnEditUsingAspenProperties
						[ ] locator "//PushButton[@caption='Edit using Aspen Properties']"
					[+] PushButton btnUsePropertiesDefinitionFile
						[ ] locator "//PushButton[@caption='Use Properties definition file']"
					[+] RadioList rdUseCustomProperties
						[ ] locator "//RadioList[@caption='Use custom properties']"
					[ ] 
					[+] PushButton btnOK
						[ ] locator "//PushButton[@caption='OK']"
				[+] DialogBox dlgOpen
					[ ] locator "//DialogBox[@caption='Open']"
					[+] TextField txtFileName
						[ ] locator "//TextField[@caption='File name:']"
				[+] DialogBox dlgAspenModeler
					[ ] locator "//DialogBox[@caption='AspenModeler']"
					[+] PushButton pshYes
						[ ] locator "//PushButton[@caption='Yes']"
					[+] PushButton pshNo
						[ ] locator "//PushButton[@caption='No']"
					[ ] 
				[+] DialogBox dlgScripting
					[ ] locator "//DialogBox[@caption='Scripting']"
					[+] StaticText stcScriptCompleted
						[ ] locator "//StaticText[@caption='Script completed.']"
				[+] DialogBox dlgExport
					[ ] locator "//DialogBox[@caption='Export']"
					[+] TextField txtFileName
						[ ] locator "//TextField"
				[+] DialogBox dlgRuncomplete
					[ ] locator "//DialogBox[@caption='Run complete']"
				[+] DialogBox dlgConfirmSaveAs
					[ ] locator "//DialogBox[@caption='Confirm Save As']"
					[+] PushButton pshYes
						[ ] locator "//PushButton[@caption='Yes']"
				[+] DialogBox dlgInstallexportedmodel
					[ ] locator "//DialogBox[@caption='Install exported model']"
					[+] PushButton pshYes
						[ ] locator "//PushButton[@caption='Yes']"
					[+] PushButton pshNo
						[ ] locator "//PushButton[@caption='No']"
			[ ] 
			[+] //Groups of Toolbar
				[+] ToolBar grpRunToolbar
					[ ] locator "//ToolBar[@caption='Run Toolbar']"
					[+] ComboBox cboStateSelection
						[ ] locator "//ComboBox"
					[+] PushToolItem pshRun
						[ ] locator "//PushToolItem[1]"
			[ ] 
			[+] //Method
				[+] OpenFile(string sLocation,boolean bDiscardFile optional)
					[+] if !SYS_FileExists(sLocation)
						[ ] Log.Fail("Cannot find file in {sLocation}. Check again before running")
						[ ] goto End
					[ ] wAspenCustomModeler.SetActive()
					[ ] sleep(1)
					[ ] wAspenCustomModeler.TypeKeys("<Ctrl-O>")
					[ ] sleep(1)
					[+] if this.dlgOpen.Exists(15)
						[+] while FindTextField("//DialogBox[@caption='Open']//TextField[@caption='File name:']").GetText()!="{sLocation}"
							[ ] wAspenCustomModeler.dlgOpen.txtFileName.SetFocus()
							[ ] wAspenCustomModeler.dlgOpen.txtFileName.TypeKeys("<Ctrl-A><Delete>")
							[ ] wAspenCustomModeler.dlgOpen.txtFileName.TypeKeys("{sLocation}")
							[ ] sleep(1)
						[ ] wAspenCustomModeler.dlgOpen.txtFileName.TypeKeys("<Enter>")
						[+] if wAspenCustomModeler.dlgAspenModeler.Exists(5)
							[+] if bDiscardFile==true
								[ ] wAspenCustomModeler.dlgAspenModeler.pshYes.Click()
							[+] else
								[ ] wAspenCustomModeler.dlgAspenModeler.pshNo.Click()
						[+] if wAspenCustomModeler.stbReady.Exists(30)
							[ ] Log.Pass("Open file {sLocation} successfully")
						[+] else
							[ ] Log.Fail("Fail to open file {sLocation}")
					[+] else
						[ ] Log.Fail("Fail to start Open window. ==Setting.ini==wAspenCustomModeler.open==CHK1")
					[+] End:
						[ ] 
				[+] void Invoke()
					[+] if !this.Exists(2)
						[ ] derived::Invoke()
					[+] if this.mnuTools.Exists(15)
						[ ] Log.Pass("Aspen Custom Modeler open successfully!")
					[+] else
						[ ] Log.Fail("Aspen Custom Modeler fail to open. ERR:=Setting.ini=wAspenCustomModeler for further reference")
					[ ] this.SetActive()
					[ ] this.Maximize()
					[ ] sleep(2)
	[ ] 
	[+] //WlmAdmin
		[+] window MainWin wWAdmin
			[ ] locator "/MainWin[@caption='*WlmAdmin*']"
			[ ] const sCmdLine = "%ProgramFiles%\Common Files\AspenTech Shared\SLM Administration Tools\WlmAdmin.exe"
			[ ] 
			[ ] 
			[+] //TreeView
				[+] TreeView trvTree
					[ ] locator "//TreeView"
			[ ] 
			[+] //Status Bar
				[+] StatusBar stbReady
					[ ] locator "//StatusBar[@caption='Ready']"
			[ ] 
			[ ] 
			[+] //Menu
				[+] Menu mnuView
					[ ] locator "//Menu[@caption='View']"
					[+] MenuItem miRefreshall
						[ ] locator "//MenuItem[@caption='Refresh all']"
						[ ] 
				[+] Menu mnuEdit
					[ ] locator "//Menu[@caption='Edit']"
					[+] MenuItem miDefinedServerList
						[ ] locator "//MenuItem[@caption='Defined Server List']"
			[+] //DialogBox
				[+] DialogBox dlgDefinedServerList
					[ ] locator "//DialogBox[@caption='Defined Server List']"
					[+] TextField txtServer
						[ ] locator "//TextField[@caption='Server:']"
					[+] PushButton pshAdd
						[ ] locator "//PushButton[@caption='Add']"
					[+] PushButton pshOK
						[ ] locator "//PushButton[@caption='OK']"
			[ ] 
			[+] //MainGrid
				[+] ListView	lstDetailedInfo
					[ ] locator "//ListView[@caption='No']"
					[ ] 
			[+] //ScrollBar
				[+] ScrollBar	scrVertical
					[ ] locator "//VerticalScrollBar"
			[ ] 
			[+] //Method
				[+] Invoke()
					[+] if !this.Exists(2)
						[ ] derived::Invoke()
					[+] if this.stbReady.Exists(15)
						[ ] Log.Pass("WlmAdmin open successfully!")
					[+] else
						[ ] Log.Fail("WlmAdmin fail to open.")
					[ ] this.Maximize()
					[ ] this.SetActive()
					[ ] sleep(1)
				[+] RefreshAll()
					[ ] wWAdmin.SetActive()
					[+] if wWAdmin.stbReady.Exists(30)
						[ ] sleep(0.8)
						[ ] wWAdmin.mnuView.Pick()
						[+] if wWAdmin.mnuView.miRefreshall.Exists(15)
							[ ] sleep(1)
							[ ] wWAdmin.mnuView.miRefreshall.Click()
						[+] else
							[ ] Log.Fail("Menuitem RefreshAll fails to show up within 15s =APChildrenwin.inc=wWadmin.Refreshall.CHK1")
						[+] if wWAdmin.stbReady.Exists(30)
							[ ] Log.Pass("Refresh Successfully")
							[ ] sleep(0.5)
						[+] else
							[ ] Log.Fail("Refresh failed within 30s =APChildrenwin.inc=wWadmin.Refreshall.CHK2")
					[+] else
						[ ] Log.Fail("ERR: The status is not ready within 30s. =APChildrenwin.inc=wWadmin.Refreshall.CHK3")
						[ ] 
					[ ] sleep(2)
				[+] AddServer(string sServer)
					[ ] wWAdmin.mnuEdit.Pick()
					[+] if wWAdmin.mnuEdit.miDefinedServerList.Exists(5)
						[ ] sleep(0.8)
						[ ] wWAdmin.mnuEdit.miDefinedServerList.Pick()
						[ ] sleep(0.8)
					[+] else
						[ ] Log.Fail("ERR1: Fail to show miDefinedServerList within 5s=APChildrenwin=wWAdmin=AddServer=")
						[ ] goto End
					[+] if wWAdmin.dlgDefinedServerList.Exists(5)
						[ ] sleep(0.8)
						[ ] wWAdmin.dlgDefinedServerList.txtServer.SetFocus()
						[ ] wWAdmin.dlgDefinedServerList.txtServer.TypeKeys("<Ctrl-A><Delete>")
						[ ] wWAdmin.dlgDefinedServerList.txtServer.TypeKeys("{sServer}")
						[ ] wWAdmin.dlgDefinedServerList.pshAdd.Click()
						[ ] sleep(0.8)
						[ ] wWAdmin.dlgDefinedServerList.pshOK.Click()
						[+] if wWAdmin.stbReady.Exists(180)
							[ ] sleep(1)
							[+] print("Add Server Successfully")
								[+] //double-check
									[+] if wWAdmin.stbReady.Exists(180)
										[ ] sleep(1)
										[ ] print("Add Server Successfully")
						[+] else
							[ ] print("Add Server failed.")
						[ ] 
						[ ] 
					[+] else
						[ ] Log.Fail("ERR1: dlgDefinedServerList fail to show up  within 5s=APChildrenwin=wWAdmin=AddServer=")
					[ ] 
					[ ] 
					[ ] 
					[ ] 
					[ ] 
					[ ] 
					[ ] End:
				[+] CheckUser(string sServer,string sProduct,int iNumberUsers optional)
					[ ] string sUserName=SYS_GetEnv ("USERNAME")
					[ ] string sCompName=SYS_GetEnv("computername")
					[ ] string sDir="/Defined Servers/"+sServer+"/"+sProduct+" /"+sUserName
					[ ] list of STRING lsItem
					[ ] integer i,j=1
					[ ] int iNumberItemMatch=0
					[ ] this.trvTree.Expand("Defined Servers")
					[ ] sleep(0.5)
					[+] //Slowly Expand sServer
						[ ] this.trvTree.Expand("Defined Servers/{sServer}")
						[+] if this.stbReady.Exists(300)
							[ ] sleep(3)
						[+] else
							[ ] Log.Fail("Querying takes more than 300s")
							[ ] goto End
						[ ] sleep(3)
					[+] //Slowly Expand Products
						[ ] this.trvTree.Expand("Defined Servers/{sServer}/{sProduct} ")
						[ ] RECT r=this.trvTree.GetItemRect("Defined Servers/{sServer}/{sProduct} ")
						[ ] 
						[+] if this.stbReady.Exists(300)
							[ ] sleep(3)
						[+] else
							[ ] Log.Fail("Querying takes more than 300s")
							[ ] goto End
					[ ] sleep(3)
					[ ] lsItem=wWAdmin.trvTree.GetContents()
					[+] // //test
						[ ] // ListPrint(lsItem)
						[ ] // print("=============================================================")
					[ ] sleep(0.6)
					[ ] 
					[ ] //Appended 
					[ ] 
					[ ] print(r.xPos)
					[ ] print(r.yPos)
					[+] for(i=1;i<=ListCount(lsItem);i++)
						[+] if(MatchStr("*Defined Servers/{sServer}/{sProduct}*",lsItem[i]))
							[+] if lsItem[i]==sDir
								[ ] this.SetActive()
								[ ] this.trvTree.Click(1,r.xPos+10,r.yPos+10+18*(j-1))
								[ ] sleep(2)
								[ ] string sItem3=wWAdmin.lstDetailedInfo.GetItemText(3)
								[+] if(MatchStr("*{sCompName}",Upper(sItem3)))
									[ ] iNumberItemMatch++
								[ ] 
							[ ] j++
							[+] if(!MatchStr("*Defined Servers/{sServer}/{sProduct}*",lsItem[i+1]))
								[ ] break
					[ ] //Append done
					[+] if iNumberUsers!=null
						[+] if iNumberUsers==iNumberItemMatch
							[ ] Log.Pass("There are {iNumberUsers} usernames <{sUserName}> found in <{sProduct}>")
						[+] else
							[ ] Log.Fail("There are {iNumberItemMatch} usernames <{sUserName}> found in <{sProduct}, but the target value is {iNumberUsers}")
					[+] else
						[+] if iNumberItemMatch!=0
							[ ] Log.Pass("User {sUserName} found in {sProduct}")
						[+] else
							[ ] Log.Fail("Fail tol find user {sUserName} found in {sProduct}")
					[ ] End:
	[ ] 
	[+] //Aspen process Economic Analyzer
		[+] window MainWin APEA
			[ ] locator "/MainWin[@caption='*Aspen Process Economic Analyzer*']"
			[ ] const sDir = "C:\windows\system32"
			[ ] const sCmdLine = "%ProgramFiles%\AspenTech\Economic Evaluation V8.4\Program\Sys\ICARUSKB.EXE -IA""IPE"""
			[+] StatusBar stbStatusBar
				[ ] locator "//StatusBar"
			[ ] //menu
			[+] Menu mnuFile
				[ ] locator "//Menu[@caption='File']"
				[+] MenuItem miExit
					[ ] locator "//MenuItem[@caption='Exit']"
			[ ] //window
			[+] DialogBox wAspenICARUSProducts
				[ ] locator "//DialogBox[@caption='Aspen ICARUS Products']"
				[+] PushButton pshYes
					[ ] locator "//PushButton[@caption='Yes']"
				[+] PushButton pshNo
					[ ] locator "//PushButton[@caption='No']"
			[+] DialogBox wLoadSimulatorData
				[ ] locator "//DialogBox[@caption='Load Simulator Data?']"
				[+] PushButton pshYes
					[ ] locator "//PushButton[@caption='Yes']"
			[+] DialogBox wUtilityResource
				[ ] locator "//DialogBox[@caption='Utility Resource(s)']"
				[+] PushButton pshOK
					[ ] locator "//PushButton[@caption='OK']"
			[+] DialogBox wCreateNewProject
				[ ] locator "//DialogBox[@caption='Create New Project']"
				[+] PushButton pshOK
					[ ] locator "//PushButton[@caption='OK']"
			[+] DialogBox wProjectProperties
				[ ] locator "//DialogBox[@caption='Project Properties']"
				[+] PushButton pshOK
					[ ] locator "//PushButton[@caption='OK']"
			[+] DialogBox wInputUnitsofMeasureSpecifications
				[ ] locator "//DialogBox[@caption='Input Units of Measure Specifications']"
				[+] PushButton pshClose
					[ ] locator "//PushButton[@caption='Close']"
			[+] DialogBox wGeneralProjectData
				[ ] locator "//DialogBox[@caption='General Project Data']"
				[+] PushButton pshOK
					[ ] locator "//PushButton[@caption='OK']"
		[ ] 
	[ ] 
	[+] //Aspen Plus Dynamics
		[+] window MainWin AspenPlusDynamics
			[ ] locator "/MainWin[@caption='*Aspen Plus Dynamics*']"
			[ ] const sDir = "C:\ProgramData\AspenTech\Aspen Plus Dynamics {sVersion}"
			[ ] const sCmdLine = "{sAspenPlus_DynamicsDir}\AspenModeler.exe /AD"
			[+] Menu mnuFile
				[ ] locator "//Menu[@caption='File']"
	[ ] 
	[ ] //Aspen Plus Solids window
	[+] window WPFWindow wNewItem
		[ ] locator "/WPFWindow[@caption='New Item']"
		[+] WPFButton btnOK
			[ ] locator "//WPFButton[@automationId='btnOK']"
		[+] WPFButton btnCancel
			[ ] locator "//WPFButton[@automationId='btnCancel']"
	[ ] 
	[ ] //Aspen Properties Database Manager
	[+] window FormsWindow wAspenPropertiesDatabaseManager
		[ ] locator "/FormsWindow[@caption='*Database Manager']"
		[+] PushButton btnOK
			[ ] locator "//PushButton[@caption='*OK*']"
		[+] PushButton btnCancel
			[ ] locator "//PushButton[@caption='*Cancel*']"
			[ ] 
		[ ] 
	[+] window wcAPDM APDM
		[ ] locator "/MainWin[@caption='APDBMGRV{sV}*']"
	[+] window wcAPDCT APDCT
		[ ] locator "/FormsWindow[@caption='Aspen Properties Database Configuration Tester {sVersion}' or @caption='Database Tester*']"
	[+] window FormsWindow wFindCompoundsFrom
		[ ] locator "/FormsWindow[@caption='Find Compounds from*']"
		[+] TextField txtCompoundName
			[ ] locator "//TextField[@automationId='textBoxNameOrAlias']"
		[+] ListViewEx lstResults
			[ ] locator "//ListViewEx[@automationId='listViewResults']"
		[+] PushButton btnFindNow
			[ ] locator "//PushButton[@automationId='buttonFindNow']"
		[+] RadioList rdContains
			[ ] locator "//RadioList[@automationId='radioButtonContains']"
		[+] RadioList rdEquals
			[ ] locator "//RadioList[@automationId='radioButtonEquals']"
		[+] RadioList rdBeginsWith
			[ ] locator "//RadioList[@automationId='radioButtonBeginsWith']"
		[+] PushButton btnClose
			[ ] locator "//PushButton[@automationId='buttonCancel']"
		[+] PushButton btnNewSearch
			[ ] locator "//PushButton[@automationId='buttonNewSearch']"
		[+] Group grpCompoundsFound
			[ ] locator "//Group[@automationId='groupBoxResults']"
	[ ] 
	[+] //PSV
		[+] window WPFWindow wStreamSelection
			[ ] locator "/WPFWindow[@caption='Stream Selection']"
			[+] WPFTreeView trvHierarchies
				[ ] locator "@automationId='TreeView_Hierarchies'"
			[+] WPFListBox lbStreams
				[ ] locator "@automationId='LstBox_Streams'"
			[+] WPFButton btnSetStream
				[ ] locator "@automationId='BtnSetStream'"
		[+] window WPFWindow wStepwiseFlashData
			[ ] locator "/WPFWindow[@caption='Stepwise Flash Data']"
			[+] WPFControl txtFlashNumberEditor
				[ ] locator "//WPFControl[@automationId='flashNumberEditor']"
			[+] wcPSVEditBox txtMaxIterationTemperatureTextBlock
				[ ] locator "@automationId='UserControl_1'"
			[+] WPFTextBlock txtTempDifferenceTextBlock
				[ ] locator "//WPFControl[@automationId='displayBox'][2]/WPFFrameworkElement[@automationId='TextBlock']"
			[+] WPFButton BtnOK
				[ ] locator "@automationId='btOK'"
			[+] WPFButton BtnCancel
				[ ] locator "@automationId='btCancel'"
	[ ] 
	[ ] 
	[ ] //==============Added By Zhangya===========
	[ ] //Solid PSD mesh Dialog
	[+] window WPFWindow dlgPSDmesh
		[ ] locator "/WPFWindow[@caption='PSD mesh']"
		[ ] wcPSDMeshSetting pgPSDMeshSetting
		[+] CloseDialog()
			[+] do
				[ ] Desktop.Find("//WPFControl[@automationId='MMCmdButton_2']").Click()
			[+] except
				[ ] this.btnClose.Click()
		[+] WPFButton btnClose
			[ ] locator "//WPFButton[@caption='Close']"
		[+] WPFControl	cboType
			[ ] locator "//WPFControl[@automationId='MMComboEdit_1']"
		[+] WPFControl	nstIntervals
			[ ] locator "//WPFControl[@automationId='MMSpinBox_1']"
		[+] WPFControl	txtLowerLimit
			[ ] locator "//WPFControl[@automationId='MMValueEdit_2']"
		[+] WPFControl	txtUpperLimit
			[ ] locator "//WPFControl[@automationId='MMValueEdit_3']"
		[+] WPFControl	lstSizeUnit
			[ ] locator "//WPFControl[@automationId='MMVariableEdit_1']"
		[+] WPFButton	btnCreatePSDMesh
			[ ] locator "//WPFButton[@caption='Create PSD Mesh']"
	[ ] //Dialog Window
	[+] window MessageBoxClass MessageBox
		[ ] tag "~ActiveApp/[DialogBox]$MessageBox|[DialogBox]Aspen Plus|[DialogBox]Create New ID|[DialogBox]New Item|[DialogBox]PSD mesh|[DialogBox]WET-COAL Inlet PSD Curve"
		[+] PushButton OK
			[ ] locator "//WPFButton[@caption='OK']"
		[+] PushButton Cancel
			[ ] locator "//WPFButton[@caption='Cancle']"
		[+] PushButton Yes
			[ ] locator "//WPFButton[@caption='Yes' or @caption='_Yes']"
		[+] PushButton No
			[ ] locator "//WPFButton[@caption='No' or @caption='_No']"
		[ ] 
		[+] WPFTextBlock  Message
			[ ] locator "//WPFTextBlock[@automationId='TextBlock_1']"
			[ ] 
	[ ] 
	[ ] //==============Added By Susan Shi===========
	[+] window WPFWindow wExchangerSummaryTable
		[ ] locator "/WPFWindow[@caption='Exchanger Summary Table']"
		[+] WPFDataGrid	dgTable
			[ ] locator "//WPFDataGrid[@automationId='datagrid']"
		[+] WPFToggleButton	btnContainerFilter
			[ ] locator "//WPFToggleButton[@automationId='filterContainer']"
		[+] WPFToggleButton	btnStatusFilter
			[ ] locator "//WPFToggleButton[@automationId='filterStatus']"
		[+] WPFToggleButton	btnRiskFilter
			[ ] locator "//WPFToggleButton[@automationId='filterRisk']"
		[+] WPFTextBlock	txtWarning
			[ ] locator "//WPFTextBlock[@caption='* Warning']"
		[+] WPFTextBlock	txtWarningMessage
			[ ] locator "//WPFTextBlock[@caption='To activate operational risks convert*']"
		[+] WPFUserControl	dlgFilter
			[ ] locator "//WPFUserControl[@caption='(Select All)']"
		[+] WPFButton	btnOK
			[ ] locator "//WPFButton[@caption='OK']"
		[+] WPFButton	btnCancel
			[ ] locator "//WPFButton[@caption='Cancel']"
		[+] WPFButton	btnConvert
			[ ] locator "//WPFButton[@automationId='btnSimple']"
		[+] WPFCheckBox	chkSelectAll
			[ ] locator "//WPFCheckBox[@caption='(Select All)']"
		[ ] //Methods
		[+] boolean CheckShowMode(integer irow)
			[+] do
				[ ] this.dgTable.Find("//WPFDataGridRow[{irow}]").Find("//WPFDataGridCell[1]").Find("//WPFTextBlock[@automationId='hyperlink']")
				[ ] return true
			[+] except
				[ ] ExceptClear()
				[ ] return false
		[+] string GetModelName(integer irow)
			[ ] string slast=this.dgTable.Find("//WPFDataGridRow[{irow}]").Find("//WPFDataGridCell[1]").sCaption
			[ ] slast=SubStr(slast,1,(Len(slast)-1)/2)  //Because the name will show twice with a blank space
			[ ] string sdir=this.dgTable.Find("//WPFDataGridRow[{irow}]").Find("//WPFDataGridCell[2]").sCaption
			[+] if(sdir!=" ")
				[ ] return sdir+"."+slast
			[+] else
				[ ] return slast
		[+] string GetModelStatus(integer irow)
			[ ] return this.dgTable.Find("//WPFDataGridRow[{irow}]").Find("//WPFDataGridCell[3]").sCaption
		[+] void Filter(string sFilterWhat, list of string lscondition optional)
			[ ] string sFilterItem,sPath=""
			[ ] boolean bFlag=false
			[ ] integer iCount,i
			[ ] list of string lsModels
			[+] if(lscondition==null)
				[ ] bFlag=true
				[ ] ListAppend(lscondition,"(Select All)")
			[ ] this.SetActive()
			[+] switch (sFilterWhat)
				[+] case "Hierarchy"
					[ ] this.btnContainerFilter.Click()
				[+] case "Status"
					[ ] this.btnStatusFilter.Click()
				[+] case "Risk"
					[ ] this.btnRiskFilter.Click()
			[ ] sleep(1)
			[+] if(wExchangerSummaryTable.dlgFilter.Exists(3))
				[ ] BUTTONSTATE bs = wExchangerSummaryTable.chkSelectAll.GetProperty("State")
				[+] if(bs == BS_CHECKED)
					[ ] this.chkSelectAll.Click()
				[ ] sleep(1)
				[+] for each sFilterItem in lscondition
					[ ] this.Find("//WPFCheckBox[@caption='{sFilterItem}']").Select()
					[ ] sleep(1)
				[ ] wExchangerSummaryTable.btnOK.Click()
				[ ] sleep(1)
			[+] else
				[ ] Log.Fail("Filter pop-up does not display.")
			[ ] //Check the result of filitering
			[+] if(bFlag)
				[+] if(APlus.GetAllModels()==GetAllDataInOneColumn(wExchangerSummaryTable.dgTable,1))
					[ ] Log.Pass("Records dispaly correctly after filitering.")
				[+] else
					[ ] Log.Fail("Records display incorrectly after filitering.")
			[+] else
				[+] switch (sFilterWhat)
					[+] case "Hierarchy"
						[+] for each sFilterItem in lscondition
							[+] if(sFilterItem=="(Blanks)")
								[ ] sPath="/Blocks"
							[+] else
								[ ] list of string lsModel=SplitStringToList(sFilterItem)
								[ ] iCount=ListCount(lsModel)
								[+] for(i=1;i<iCount;i++)
									[ ] sPath=sPath+"/Blocks/"+lsModel[i]
								[ ] sPath=sPath+"/Blocks"
							[ ] ListAppend(lsModels, APlus.GetModelsInABlock(sPath))
						[+] if(lsModels==GetAllDataInOneColumn(this.dgTable,1))
							[ ] Log.Pass("Records dispaly correctly after filitering.")
						[+] else
							[ ] Log.Fail("Records display incorrectly after filitering.")
					[+] case "Status"
						[ ] iCount=ListCount(wExchangerSummaryTable.FindAll("//WPFDataGridRow"))
						[+] if(iCount==APlus.GetModelCountByStatus(lscondition))
							[+] for(i=1;i<=iCount;i++)
								[+] if(ListFind(lscondition,this.GetModelStatus(i))==0)
									[ ] bFlag=true
							[+] if(bFlag)
								[ ] Log.Fail("Records display incorrectly after filitering.")
							[+] else
								[ ] Log.Pass("Records dispaly correctly after filitering.")
						[+] else
							[ ] Log.Fail("Records display incorrectly after filitering.")
					[+] case "Risk"
						[ ] // will wirte further
		[+] void ClickHyperlinkToOpenForm(string sModel)
			[ ] this.SetActive()
			[ ] this.Find("//WPFTextBlock[@automationId='hyperlink']/WPFTextBlock[@caption='{sModel}']").Click()
			[ ] sleep(1)
			[ ] glWaitForMouseIdle(20)
			[ ] APlus.btnShoworHideSummary.Click()
			[ ] sleep(1)
			[+] if((APlus.Find("//WPFTextBlock[@caption='{sModel}*']")).Exists())
				[ ] Log.Pass("The Aspen Plus form for the selected exchanger opens automatically with the Specifications ply.")
			[+] else
				[ ] Log.Fail("The Aspen Plus form for the selected exchanger does not open automatically with the Specifications ply.")
	[+] window WPFWindow dlgConvertExchanger
		[ ] locator "/WPFWindow[@caption='Convert Exchanger']"
		[+] WPFButton	btnConvert
			[ ] locator "//WPFButton[@automationId='OK']"
		[+] WPFButton btnCancel
			[ ] locator "//WPFButton[@automationId='Cancel']"
	[+] window WPFWindow wConverttoRigorousExchanger
		[ ] locator "/WPFWindow[@caption='Convert to Rigorous Exchanger']"
		[+] WPFRadioButton	rdbShellandTube
			[ ] locator "//WPFRadioButton[@automationId='RigShellTube']"
		[+] WPFRadioButton	rdbAirCooled
			[ ] locator "//WPFRadioButton[@automationId='RigAircool']"
		[+] WPFRadioButton	rdbPlate
			[ ] locator "//WPFRadioButton[@automationId='RigPlate']"
		[+] WPFRadioButton	rdbSizeInteractively
			[ ] locator "//WPFRadioButton[@automationId='Interactive']"
		[+] WPFRadioButton	rdbSizeInteractivelyusingTemplate
			[ ] locator "//WPFRadioButton[@automationId='Template']"
		[+] WPFRadioButton	rdbImportEDRFile
			[ ] locator "//WPFRadioButton[@automationId='Import']"
		[+] WPFTextBox	txtSelectTemplate
			[ ] locator "//WPFTextBox[@automationId='TemplateFilePath']"
		[+] WPFTextBox	txtSelectEDRFile
			[ ] locator "//WPFTextBox[@automationId='ImportFilePath']"
		[+] WPFButton	btnTemplateBrowse
			[ ] locator "//WPFButton[@automationId='TemplateBrowse']"
		[+] WPFButton	btnImportBrowse
			[ ] locator "//WPFButton[@automationId='ImportBrowse']"
		[+] WPFButton	btnConvert
			[ ] locator "//WPFButton[@automationId='OK']"
			[ ] 
			[+] void Click()
				[ ] Agent.SetOption(OPT_VERIFY_ACTIVE, FALSE)
				[ ] Agent.SetOption(OPT_VERIFY_ENABLED, FALSE)
				[ ] Agent.SetOption(OPT_VERIFY_APPREADY, FALSE)
				[ ] Agent.SetOption(OPT_VERIFY_APPREADY, FALSE)
				[ ] Agent.SetOption(OPT_SYNC_TIMEOUT, 0.1)
				[ ] 
				[+] if ! this.IsEnabled
					[ ] sleep(60)
				[ ] wConverttoRigorousExchanger.TextClick("Convert")
				[ ] Agent.SetOption(OPT_SYNC_TIMEOUT, 5)
				[ ] Agent.SetOption(OPT_VERIFY_ACTIVE, TRUE)
				[ ] Agent.SetOption(OPT_VERIFY_ENABLED, TRUE)
				[ ] Agent.SetOption(OPT_VERIFY_APPREADY, TRUE)
			[ ] 
		[+] WPFButton btnCancel
			[ ] locator "//WPFButton[@automationId='Cancel']"
		[+] DialogBox	dlgOpen
			[ ] locator "//Dialog[@caption='Open']"
			[+] TextField	txtFileName
				[ ] locator "//TextField[@caption='File name:']"
			[+] PushButton	btnOpen
				[ ] locator "//PushButton[@caption='Open']"
			[+] PushButton	btnCancel
				[ ] locator "//PushButton[@caption='Cancel']"
		[+] WPFRadioButton	rdbSpecifyExchangerGeometry
			[ ] locator "//WPFRadioButton[@caption='Specify Exchanger Geometry']"
		[ ] 
		[ ] //Method
		[+] void OpenFile(string sFilePath)
			[ ] this.dlgOpen.SetActive()
			[ ] this.dlgOpen.txtFileName.SetFocus()
			[ ] this.dlgOpen.txtFileName.TypeKeys("{sFilePath}")
			[ ] sleep(1)
			[ ] this.dlgOpen.btnOpen.Click()
	[-] window WPFWindow	wOperationWarnings
		[ ] locator "/WPFWindow[@caption='*Operation Warnings']"
		[+] WPFDataGrid	dgTable
			[ ] locator "//WPFDataGrid[@automationId='datagrid']"
	[+] window WPFWindow wAllOperationRisks
		[ ] locator "//WPFUserControl[@caption='*All Operation Risks*']"
		[+] WPFDataGrid	dgTable
			[ ] locator "//WPFDataGrid[@automationId='datagrid']"
		[+] WPFButton	btnClose
			[ ] locator "//WPFButton[@caption='r']"
	[-] window WPFWindow	wflyover
		[ ] locator "/WPFWindow[2]"
		[+] WPFUserControl	dlgPlate
			[ ] locator "//WPFUserControl[@caption='Plate: *']"
			[+] WPFTextBlock	txtSurfaceArea
				[ ] locator "//WPFTextBlock[5]"
			[+] WPFTextBlock	txtTotalHeatLoad
				[ ] locator "//WPFTextBlock[8]"
			[-] WPFTextBlock	txtExchangersinParallel
				[ ] locator "//WPFTextBlock[14]"//xiaoqing
		[+] WPFUserControl	dlgHeatX
			[ ] locator "//WPFUserControl[@caption='HeatX: *']"
			[+] WPFTextBlock	txtHotSideDeltaT
				[ ] locator "//WPFTextBlock[5]"
			[+] WPFTextBlock	txtColdSideDeltaT
				[ ] locator "//WPFTextBlock[8]"
			[+] WPFTextBlock	txtDuty
				[ ] locator "//WPFTextBlock[11]"
			[+] WPFTextBlock	txtArea
				[ ] locator "//WPFTextBlock[14]"
		[-] WPFUserControl	dlgShellandTube
			[ ] //locator "//WPFUserControl[1]"
			[ ] locator "//WPFUserControl[@caption='Shell&Tube: *' or @automationId='UserControl_1']"
			[-] WPFTextBlock	txtSurfaceArea
				[ ] locator "//WPFTextBlock[5]"
			[-] WPFTextBlock	txtTotalHeadLoad
				[ ] locator "//WPFTextBlock[8]"
			[-] WPFTextBlock	txtTEMAType
				[ ] locator "//WPFTextBlock[11]"
			[+] WPFTextBlock	txtShellsinSeries
				[ ] locator "//WPFTextBlock[14]"
			[+] WPFTextBlock	txtShellsinParallel
				[ ] locator "//WPFTextBlock[17]"
		[-] WPFUserControl	dlgAirCooled
			[ ] //locator "//WPFUserControl[@automationId='UserControl_1']"
			[ ] locator "//WPFUserControl[@caption='AirCooled: *']"
			[+] WPFTextBlock	txtSurfaceArea
				[ ] locator "//WPFTextBlock[5]"
			[-] WPFTextBlock	txtSurfaceArea1
				[ ] locator "//WPFTextBlock[@automationId='TextBlock_5']"
			[ ] 
			[+] WPFTextBlock	txtTotalHeadLoad
				[ ] locator "//WPFTextBlock[8]"
			[+] WPFTextBlock	txtFanConfiguration
				[ ] locator "//WPFTextBlock[11]"
			[+] WPFTextBlock	txtBaysperUnit
				[ ] locator "//WPFTextBlock[14]"
			[+] WPFTextBlock	txtBundlesperBay
				[ ] locator "//WPFTextBlock[17]"
			[+] WPFTextBlock	txtFansperBay
				[ ] locator "//WPFTextBlock[20]"
		[+] WPFUserControl	dlgHierarchyBlock
			[ ] locator "//WPFUserControl[@caption='Hierarchy Block: *']"
		[+] WPFButton	btnConvert
			[ ] locator "//WPFButton[@caption='Convert']"
		[+] WPFButton	btnViewTable
			[ ] locator "//WPFButton[@caption='View Table']"
		[+] WPFButton	btnBack
			[ ] locator "//WPFButton[@automationId='btnBack']"
		[+] WPFDataGrid	dgTable
			[ ] locator "//WPFDataGrid[@automationId='datagrid']"
		[+] WPFTextBlock	txtWarnings
			[ ] locator "//WPFTextBlock[3]"
		[+] WPFButton	btnSizeRigorous
			[ ] locator "//WPFButton[@caption='Size Rigorous']"
		[+] WPFButton	btnSpecifyRigorous
			[ ] locator "//WPFButton[@caption='Specify Rigorous']"
		[+] WPFButton	btnShowSummary
			[ ] locator "//WPFButton[@automationId='btnShowSummary']"
		[ ] 
		[ ] 
	[+] window wcSize wSizeShellandTube
		[ ] locator "/WPFWindow[@caption='Size Shell&Tube']"
	[+] window wcSize	wSizeAirCooled
		[ ] locator "/WPFWindow[@caption='Size AirCooled']"
	[+] window FormsWindow wAPlusHelp
		[ ] locator "/FormsWindow[@caption='Aspen Plus V*Help']"
	[+] window WPFWindow wTernaryPlot
		[ ] locator "/WPFWindow[@caption='Ternary Plot']"
		[+] WPFControl	txtRefluxRatio
			[ ] locator "//WPFControl[@automationId='PART_editControl'][6]"
		[+] WPFButton	btnReset
			[ ] locator "//WPFButton[@caption='Reset']"
		[+] WPFButton	btnRecalculate
			[ ] locator "//WPFButton[@caption='Recalculate']"
		[+] WPFButton	btnShowOrHide
			[ ] locator "//WPFButton[@caption='Show/Hide']"
		[+] WPFButton	btnCancel
			[ ] locator "//WPFButton[@caption='Cancel']"
		[+] WPFButton	btnClose
			[ ] locator "//WPFButton[@caption='Close']"
		[+] WPFLabel	txtStageInfo
			[ ] locator "//WPFLabel[16]"
	[+] window WPFWindow wShowHide
		[ ] locator "/WPFWindow[@caption='Show/Hide']"
		[+] WPFButton	btnOK
			[ ] locator "//WPFButton[@automationId='btnOK']"
		[+] WPFButton	btnCancel
			[ ] locator "//WPFButton[@automationId='btnCancel']"
		[ ] 
	[+] window WPFWindow	wConvertTo
		[ ] locator "/WPFWindow[@caption='Convert To ...']"
		[+] WPFButton	btnOK
			[ ] locator "//WPFButton[@automationId='OkButton']"
		[+] WPFButton	btnCancel
			[ ] locator "//WPFButton[@automationId='CancelButton']"
	[+] window FormsWindow	wGenerateEstimates
		[ ] locator "/FormsWindow[@caption='Generate estimates']"
		[+] CheckBox	chkTemperature
			[ ] locator "//CheckBox[@automationId='checkBox1']"
		[+] CheckBox	chkCompositions
			[ ] locator "//CheckBox[@automationId='checkBox2']"
		[+] PushButton	btnOK
			[ ] locator "//PushButton[@automationId='button1']"
	[+] window WPFWindow wTableFormat
		[ ] locator "/WPFWindow[@caption='Table Format']"
		[ ] 
	[+] window WPFWindow wDeleteExistingAreaSpec
		[ ] locator "/WPFWindow[@caption='Delete existing area spec']"
		[+] WPFButton	btnOK
			[ ] locator "//WPFButton[@automationId='btn0']"
		[+] WPFButton	btnCancel
			[ ] locator "//WPFButton[@automationId='btn1']"
		[ ] 
	[+] window WPFWindow wSizeShellTube
		[ ] locator "/WPFWindow[@caption='Aspen Plus - Size Shell&Tube']"
		[+] WPFButton	btnOK
			[ ] locator "//WPFButton[@automationId='btn0']"
	[+] window WPFWindow wNewSpecGroup
		[ ] locator "/WPFWindow[@caption='New Spec group']"
		[+] WPFTextBox		txtGroupName
			[ ] locator "//WPFTextBox[@automationId='tbText']"
		[+] WPFButton		btnOK
			[ ] locator "//WPFButton[@automationId='btnOK']"
		[ ] 
	[+] window WPFWindow wCopyFromEORun
		[ ] locator "/WPFWindow[@caption='Copy from EO Run']"
		[+] WPFButton	btnCopy
			[ ] locator "//WPFButton[@caption='Copy']"
		[+] WPFButton	btnCancel
			[ ] locator "//WPFButton[@caption='Cancel']"
		[+] WPFCheckBox	chbValue
			[ ] locator "//WPFCheckBox[@automationId='PART_CheckBox'][2]"
		[+] WPFCheckBox	chbUnits
			[ ] locator "//WPFCheckBox[@automationId='PART_CheckBox'][6]"
		[+] WPFCheckBox	chbLowerBound
			[ ] locator "//WPFCheckBox[@automationId='PART_CheckBox'][8]"
		[+] WPFCheckBox	chbUpperBound
			[ ] locator "//WPFCheckBox[@automationId='PART_CheckBox'][10]"
		[ ] 
	[+] window WPFWindow wResultsCruve
		[ ] locator "/WPFWindow[@caption='Results Curve']"
		[+] WPFButton	btnOK
			[ ] locator "//WPFButton[@caption='OK']"
		[+] WPFButton	btnCancel
			[ ] locator "//WPFButton[@caption='Cancel']"
		[+] WPFButton	btnClearSelections
			[ ] locator "//WPFButton[@caption='Clear Selections']"
		[+] WPFComboBox	cboXAxis
			[ ] locator "//WPFComboBox[@automationId='ComboBoxXAxis']"
		[+] WPFCheckBox	chkParametricVariable
			[ ] locator "//WPFCheckBox[@automationId='chkParaVar']"
		[+] WPFListBox	lstCurvesList
			[ ] locator "//WPFListBox[@automationId='CurvesList']"
		[+] WPFCheckBox	chkSelectAll
			[ ] locator "//WPFCheckBox[@automationId='PART_CheckBox']"
	[+] window WPFWindow wPSD
		[ ] locator "/WPFWindow[@caption='PSD']"
		[+] WPFButton	btnOK
			[ ] locator "//WPFButton[@caption='OK']"
		[+] WPFButton	btnCancel
			[ ] locator "//WPFButton[@caption='Cancel']"
		[+] WPFListBox	lstSubStreams
			[ ] locator "//WPFListBox[@automationId='CurvesList']"
		[+] WPFListBox	lstStreams
			[ ] locator "//WPFListBox[@automationId='CurvesList'][2]"
		[ ] 
	[+] window WPFWindow wExportDone
		[ ] locator "/WPFWindow[3]"
		[+] WPFButton	btnOK
			[ ] locator "//WPFButton[@automationId='btn0']"
		[ ] 
	[+] window WPFWindow wNewReactionSet
		[ ] locator "/WPFWindow[@caption='New Reaction Set']"
		[+] WPFTextBox		txtName
			[ ] locator "//WPFTextBox[@automationId='tbText']"
		[+] WPFButton	btnOK
			[ ] locator "//WPFButton[@automationId='btnOK']"
		[+] WPFButton 	btnCancel
			[ ] locator "//WPFButton[@automationId='btnCancel']"
	[+] window WPFWindow wEnterType
		[ ] locator "/WPFWindow[@caption='Enter Type']"
		[+] WPFComboBox	cboType
			[ ] locator "//WPFComboBox[@automationId='cboType2']"
		[+] WPFButton	btnOK
			[ ] locator "//WPFButton[@automationId='btnOK']"
	[+] window WPFWindow wEditReaction
		[ ] locator "/WPFWindow[@caption='Edit Reaction']"
		[+] wcAPDataGrid dgReactants
			[ ] locator "//WPFControl[@automationId='PART_DataGrid']"
		[+] wcAPDataGrid dgProducts
			[ ] locator "//WPFControl[@automationId='PART_DataGrid'][2]"
		[+] WPFButton	btnNext
			[ ] locator "//WPFButton[@automationId='PART_BUTTON']"
		[+] WPFButton	btnClose
			[ ] locator "//WPFButton[@caption='Close']"
		[+] WPFComboBox	cboComponent
			[ ] locator "//WPFComboBox[@automationId='PART_FocusSite']"
	[+] window WPFWindow wSolids
		[ ] locator "/WPFWindow[@caption='Solids']"
		[+] WPFRadioButton	rdbReactingPhaseAndSolidPhase
			[ ] locator "//WPFRadioButton[@automationId='MMOptionButton_2']"
		[+] WPFRadioButton	rdbReactingPhaseOnly
			[ ] locator "//WPFRadioButton[@automationId='MMOptionButton_1']"
		[+] WPFRadioButton	rdbSoildPhaseOnly
			[ ] locator "//WPFRadioButton[@automationId='MMOptionButton_3']"
		[+] WPFRadioButton	rdbSoildAndFluidPhase
			[ ] locator "//WPFRadioButton[@automationId='MMOptionButton_4']"
		[+] WPFRadioButton	rdbAllSolidSubstreams
			[ ] locator "//WPFRadioButton[@automationId='MMOptionButton_5']"
		[+] WPFRadioButton	rdbSubstreamOfTheSolidComponent
			[ ] locator "//WPFRadioButton[@automationId='MMOptionButton_6']"
		[+] WPFButton	btnClose
			[ ] locator "//WPFButton[@automationId='PART_BUTTON']"
	[+] window WPFWindow wCompositionProfiles
		[ ] locator "/WPFWindow[@caption='Composition profiles']"
		[+] WPFListBox	lstComponentsToPlot
			[ ] locator "//WPFListBox[@automationId='CurvesList']"
		[+] WPFButton	btnOK
			[ ] locator "//WPFButton[@caption='OK']"
	[+] window WPFWindow wSearchPhyicalProperties
		[ ] locator "/WPFWindow[@caption='Search Physical Properties']"
		[+] WPFTextBox		txtSearchContent
			[ ] locator "//WPFTextBox[@automationId='txtProperty']"
		[+] WPFButton	btnSearch
			[ ] locator "//WPFButton[@automationId='btnSearch']"
		[+] WPFListView		lsvPropertiesAvailable
			[ ] locator "//WPFListView[@automationId='lstProperty']"
		[+] WPFListView		lsvPropetriesSelected
			[ ] locator "//WPFListView[@automationId='lstAcceptedProperty']"
		[+] WPFButton		btnOK
			[ ] locator "//WPFButton[@automationId='btnOK']"
	[+] window WPFWindow wHelp
		[ ] locator "/FormsWindow[@caption='Aspen Plus V* Help']"
	[+] window WPFWindow wEnergyAnalysis
		[ ] locator "/WPFWindow[@caption='Energy Analysis']"
		[+] WPFButton	btnYes
			[ ] locator "//WPFButton[@automationId='Button_1']"
		[+] WPFButton	btnNo
			[ ] locator "//WPFButton[@automationId='Button_2']"
		[ ] 
	[+] window WPFWindow wAspenCompoundFile
		[ ] locator "/FormsWindow[@caption='Aspen Compound File']"
		[+] ListViewEx	lveEmbeddedFiles
			[ ] locator "//ListViewEx[@automationId='fileListView']"
	[+] window WPFWindow wDistillationsythesis
		[ ] locator "/WPFWindow[@caption='Distillation Synthesis']"
		[+] WPFButton	btnLearn
			[ ] locator "//WPFButton[@automationId='BtnLm']"
		[+] WPFButton 	btnContinue
			[ ] locator "//WPFButton[@automationId='BtnCta']"
		[+] WPFButton	btnUse
			[ ] locator "//WPFButton[@automationId='BtnUds']"
		[+] WPFButton	btnFind
			[ ] locator "//WPFButton[@automationId='BtnFa']"
		[+] WPFCheckBox	chkNotShow
			[ ] locator "//WPFCheckBox[@automationId='ChkDns']"
	[+] window WPFWindow wDefineVariables
		[ ] locator "/WPFWindow[@caption='Define Variables']"
		[+] wcAPDataGrid dgGrid
			[ ]  locator "//WPFControl[@automationId='PART_DataGrid']"
		[+] WPFButton	btnClose
			[ ] locator "//WPFButton[@automationId='PART_BUTTON']"
	[+] window WPFWindow wEDRSizingConsole
		[ ] locator "/WPFWindow[@caption='EDR Sizing Console*']"
		[+] WPFButton	btnSize
			[ ] locator "//WPFButton[@caption='Size']"
		[+] WPFButton	btnCancel
			[ ] locator "//WPFButton[@caption='Cancel']"
		[+] WPFButton	btnSave
			[ ] locator "//WPFButton[@caption='Save']"
		[+] WPFButton	btnAcceptDesign
			[ ] locator "//WPFButton[@caption='Accept Design']"
			[ ] 
			[+] void Click()
				[ ] 
				[ ] Agent.SetOption(OPT_VERIFY_ACTIVE, FALSE)
				[ ] Agent.SetOption(OPT_VERIFY_ENABLED, FALSE)
				[ ] Agent.SetOption(OPT_VERIFY_APPREADY, FALSE)
				[ ] Agent.SetOption(OPT_VERIFY_APPREADY, FALSE)
				[ ] Agent.SetOption(OPT_SYNC_TIMEOUT, 0.1)
				[+] if !this.IsEnabled
					[ ] sleep(60)
				[+] if !this.IsEnabled
					[ ] wEDRSizingConsole.btnSize.click()
					[ ] sleep(60)
					[ ] wEDRSizingConsole.TextClick("Accept Design")
				[+] else
					[ ] wEDRSizingConsole.TextClick("Accept Design")
					[ ] 
				[ ] Agent.SetOption(OPT_SYNC_TIMEOUT, 5)
				[ ] Agent.SetOption(OPT_VERIFY_ACTIVE, TRUE)
				[ ] Agent.SetOption(OPT_VERIFY_ENABLED, TRUE)
				[ ] Agent.SetOption(OPT_VERIFY_APPREADY, TRUE)
				[ ] 
				[ ] 
				[ ] 
			[ ] 
			[ ] 
		[+] DialogBox	dlgCancel
			[ ] locator "//DialogBox[@caption='Cancel']"
			[+] PushButton	btnNo
				[ ] locator "//PushButton[@caption='No']"
			[+] PushButton	btnYes
				[ ] locator "//PushButton[@caption='Yes']"
		[+] DialogBox	dlgSaveExchangerDesign
			[ ] locator "//DialogBox[@caption='Save Exchanger Design']"
			[+] ComboBox	cboFileName
				[ ] locator "//ComboBox"
			[+] PushButton	btnSave
				[ ] locator "//PushButton[@caption='Save']"
	[+] window FormsWindow	wTemperoryInput
		[ ] locator "/FormsWindow[@caption='Temporary Input']"
	[+] window WPFWindow	wRevertShortcutExchangerModel
		[ ] locator "/WPFWindow[@caption='Revert to Shortcut Exchanger Model']"
		[+] WPFRadioButton	rdbShortcutWithEDR
			[ ] locator "//WPFRadioButton[@automationId='RadioButton_0_1']"
		[+] WPFRadioButton	rdbShortcut
			[ ] locator "//WPFRadioButton[@automationId='RadioButton__0_2']"
		[+] WPFButton		btnRevert
			[ ] locator "//WPFButton[@automationId='Button_1']"
	[+] window WPFWindow	wSizingToCreateRigorousExchanger
		[ ] locator "/WPFWindow[@caption='Sizing to Create  Rigorous Exchanger']"
		[+] WPFRadioButton	rdbShellTube
			[ ] locator "//WPFRadioButton[@automationId='RigShellTube']"
		[+] WPFRadioButton	rdbKettleReboiler
			[ ] locator "//WPFRadioButton[@automationId='RigKettleReboiler']"
		[+] WPFRadioButton	rdbThermosyphon
			[ ] locator "//WPFRadioButton[@automationId='RigThermosyphon']"
		[+] WPFRadioButton	rdbAirCooled
			[ ] locator "//WPFRadioButton[@automationId='RigAircool']"
		[+] WPFRadioButton	rdbSizeInteractively
			[ ] locator "//WPFRadioButton[@automationId='Interactive']"
		[+] WPFRadioButton	rdbSizeInteractivelyUsingTemplate
			[ ] locator "//WPFRadioButton[@automationId='Template']"
		[+] WPFButton		btnConvert
			[ ] locator "//WPFButton[@automationId='OK']"
	[+] window WPFWindow	wSpecifyRigorousExchanger
		[ ] locator "/WPFWindow[@caption='Specify  Rigorous Exchanger']"
		[+] WPFRadioButton	rdbShellTube
			[ ] locator "//WPFRadioButton[@automationId='RigShellTube']"
		[+] WPFRadioButton	rdbKettleReboiler
			[ ] locator "//WPFRadioButton[@automationId='RigKettleReboiler']"
		[+] WPFRadioButton	rdbThermosyphon
			[ ] locator "//WPFRadioButton[@automationId='RigThermosyphon']"
		[+] WPFRadioButton	rdbAirCooled
			[ ] locator "//WPFRadioButton[@automationId='RigAircool']"
		[+] WPFRadioButton	rdbPlate
			[ ] locator "//WPFRadioButton[@automationId='RigPlate']"
		[+] WPFRadioButton	rdbInputKeyGeometry
			[ ] locator "//WPFRadioButton[@automationId='InputKeyGeometry']"
		[+] WPFRadioButton	rdbImportEDRFile
			[ ] locator "//WPFRadioButton[@automationId='Import']"
		[+] WPFTextBox		txtFilePath
			[ ] locator "//WPFTextBox[@automationId='ImportFilePath']"
		[+] WPFButton			btnBrowse
			[ ] locator "//WPFButton[@automationId='ImportBrowse']"
		[+] WPFButton			btnConvert
			[ ] locator "//WPFButton[@automationId='OK']"
			[+] void Click()
				[ ] Agent.SetOption(OPT_VERIFY_ACTIVE, FALSE)
				[ ] Agent.SetOption(OPT_VERIFY_ENABLED, FALSE)
				[ ] Agent.SetOption(OPT_VERIFY_APPREADY, FALSE)
				[ ] Agent.SetOption(OPT_VERIFY_APPREADY, FALSE)
				[ ] Agent.SetOption(OPT_SYNC_TIMEOUT, 0.1)
				[ ] 
				[+] if ! this.IsEnabled
					[ ] sleep(60)
				[ ] wSpecifyRigorousExchanger.TextClick("Convert")
				[ ] Agent.SetOption(OPT_SYNC_TIMEOUT, 5)
				[ ] Agent.SetOption(OPT_VERIFY_ACTIVE, TRUE)
				[ ] Agent.SetOption(OPT_VERIFY_ENABLED, TRUE)
				[ ] Agent.SetOption(OPT_VERIFY_APPREADY, TRUE)
	[ ] //Add
[ ] 
