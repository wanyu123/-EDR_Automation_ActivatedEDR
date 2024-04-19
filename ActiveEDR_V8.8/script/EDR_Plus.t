[ ] // use "../frame/frame/Frame.inc"
[ ] use "../frame/APlus/include/APMainWin.inc"
[ ] 
[ ] //EDR cases
[+] testcase CQ00510118() appstate CleanState		
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 17, 2013
	[+] // Variables defination
		[ ] sCaseName="{sAspenPlusFavorites}\testprob.bkp"
		[ ] string sTemp
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
	[+] // Case script
		[ ] Print("4.2.1 Activating EDR activation with no heat exchanger in Aspen Plus file.")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1. Launch Aspen Plus; open the testprob.bkp from Aspen Plus example file and the EDR dashboard is displayed as below.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.Open(sCaseName,0)
			[+] if(APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" && APlus.ctrlEDRDashboard.ctrlOK.TextCapture()=="0" && APlus.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("EDR dashboard is displayed as expected.")
			[+] else
				[ ] Log.Fail("EDR dashboard is not displayed as expected.")
		[+] Print("Step 2. Click the Activated EDR icon on the dashboard and the Exchanger Summary Table will appear but the list is empty .")
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[+] if(ListCount(APlus.dgGeneralTable.FindAll("/WPFDataGridRow"))==0)
					[ ] Log.Pass("The list is empty.")
				[+] else
					[ ] Log.Fail("The list is not empty.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[+] // if(!APlus.ctrlEDRDashboard.btnActivateEDR.IsEnabled)
				[ ] // Log.Pass("The Exchanger Summary Table will NOT appear.")
			[+] // else
				[ ] // Log.Fail("The Exchanger Summary Table sappears.")
		[+] Print("Step 3. Put the cursor over the inactive drop-down button and the tooltip appears.")
			[ ] sTemp=APlus.ctrlEDRDashboard.btnActivateEDR.ToolTip
			[+] if(sTemp==sAPlusToolTip)
				[ ] Log.Pass("Tooltip displays as expected.")
			[+] else
				[ ] Log.Fail("Tooltip does not display as expected.")
		[+] Print("Step 4: Put the cursor over the Unknown area and the tooltip appears.")
			[ ] sTemp=APlus.ctrlEDRDashboard.ctrlUnKnown.ToolTip
			[ ] print(sTemp)
			[+] if(sTemp=="Number of heat exchangers that are not yet rated/designed, have missing information or errors.")
				[ ] Log.Pass("Tooltip of Unknown displays as expected.")
			[+] else
				[ ] Log.Fail("Tooltip of Unknown does not display as expected.")
		[+] Print("Step 5: Put the cursor over the OK area and the tooltip appears")
			[ ] sTemp=APlus.ctrlEDRDashboard.ctrlOK.ToolTip
			[+] if(sTemp=="Number of heat exchangers that are already rated/designed and have NO operational risk.")
				[ ] Log.Pass("Tooltip of OK displays as expected.")
			[+] else
				[ ] Log.Fail("Tooltip of OK does not display as expected.")
		[+] Print("Step 6: Put the cursor over the At Risk area and the tooltip appears")
			[ ] sTemp=APlus.ctrlEDRDashboard.ctrlAtRisk.ToolTip
			[+] if(sTemp=="Number of heat exchangers that are already rated/designed and have at least one operational risk.")
				[ ] Log.Pass("Tooltip of AtRisk displays as expected.")
			[+] else
				[ ] Log.Fail("Tooltip of AtRisk does not display as expected.")
		[+] Print("Step 7: Collapse the dashboard to reduced form")
			[ ] APlus.SetActive()
			[ ] APlus.btnExpandOrCollapse.Click()
			[ ] sleep(1)
		[+] Print("Step 8: Put the cursor over the areas and the tooltips appear")
			[ ] sTemp=APlus.ctrlEDRDashboard.btnActivateEDR.ToolTip
			[+] if(sTemp==sAPlusToolTip)
				[ ] Log.Pass("Tooltip displays as expected.")
			[+] else
				[ ] Log.Fail("Tooltip does not display as expected.")
			[ ] sTemp=APlus.ctrlEDRDashboard.ctrlUnKnown.ToolTip
			[ ] print(sTemp)
			[+] if(sTemp=="Number of heat exchangers that are not yet rated/designed, have missing information or errors.")
				[ ] Log.Pass("Tooltip of Unknown displays as expected.")
			[+] else
				[ ] Log.Fail("Tooltip of Unknown does not display as expected.")
			[ ] sTemp=APlus.ctrlEDRDashboard.ctrlOK.ToolTip
			[+] if(sTemp=="Number of heat exchangers that are already rated/designed and have NO operational risk.")
				[ ] Log.Pass("Tooltip of OK displays as expected.")
			[+] else
				[ ] Log.Fail("Tooltip of OK does not display as expected.")
			[ ] sTemp=APlus.ctrlEDRDashboard.ctrlAtRisk.ToolTip
			[+] if(sTemp=="Number of heat exchangers that are already rated/designed and have at least one operational risk.")
				[ ] Log.Pass("Tooltip of AtRisk displays as expected.")
			[+] else
				[ ] Log.Fail("Tooltip of AtRisk does not display as expected.")
		[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510120() appstate CleanState	
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 17, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510120"
		[ ] sCaseName="{sAspenPlusExamples}\Power\Coal Gasification\igcc.bkp"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer i, iSimple=0
		[ ] string sBitmapDir
		[ ] list of string lsModels
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
	[+] // Case script
		[ ] Print("4.2.2 Activating EDR activation with only simple heat exchanger in Aspen plus file.")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus,open the igcc.bkp from the example file.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.Open(sCaseName,0)
		[+] Print("Step 2: Click the Activated EDR icon, the following Exchanger Summary Table will appear.")
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //a
				[ ] lsModels=APlus.GetModelsInSummaryTable()
				[+] for(i=1;i<=ListCount(lsModels);i++)
					[+] if(APlus.GetModelType(lsModels[i]))
						[ ] iSimple++
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(iSimple==Val(APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture()))
					[ ] Log.Pass("The number shown in dashboard for the simple models is the same as that Aspen Plus contains.")
				[+] else
					[ ] Log.Fail("The number shown in dashboard for the simple models is not the same as that Aspen Plus contains. On dashboard, it's {APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture()}, Actual: it's{iSimple}.")
				[+] if(ListCount(lsModels)==Val(APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture())+Val(APlus.ctrlEDRDashboard.ctrlOK.TextCapture())+Val(APlus.ctrlEDRDashboard.ctrlAtRisk.TextCapture()))
					[ ] Log.Pass("The models displayed in Exchanger Summary table have the same number.")
				[+] else
					[ ] Log.Fail("The models displayed in Exchanger Summary table do not have the same number.")
				[ ] //b
				[+] if(Val(APlus.ctrlEDRDashboard.ctrlOK.TextCapture())+Val(APlus.ctrlEDRDashboard.ctrlAtRisk.TextCapture())==0)
					[ ] Log.Pass("The number of the rigorous models is shown as 0 (OK and At Risk).")
				[+] else
					[ ] Log.Fail("The number of the rigorous models is not shown as 0 (OK and At Risk).")
				[ ] //c
				[+] if(APlus.IsOperationalRiskBlank())
					[ ] Log.Pass("The Operational Risk is blank in Exchanger Summary Table.")
				[+] else
					[ ] Log.Fail("The Operational Risk is not blank in Exchanger Summary Table.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("a.	Make sure the number shown in dashboard for the simple models and is the same as that Aspen Plus contain. Make sure the models displayed in Exchanger Summary table have the same number.")
		[ ] Print("b.	Make sure the number of the rigorous models is shown as 0 (OK and At Risk). ")
		[ ] Print("c.	Make sure the Operational Risk is blank in Exchanger Summary Table.")
		[+] Print("Step 3: Close the Exchanger Summary Table.")
			[ ] APlus.SetActive()
			[ ] APlus.closeTab("Exchanger Summary Table")
	[ ] 
[+] testcase CQ00510122() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510122"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\Multi HXs"
		[ ] sCaseName="multi_HXs.bkp"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer i, iSimple=0, iRigorous=0
		[ ] string sBitmapDir
		[ ] list of string lsModels
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] SYS_Execute("xcopy {sDatain} {sDataout} /e")
		[ ] sleep(2)
	[+] // Case script
		[ ] Print("4.3.1 Basic function for Activating EDR panel.")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus; Open the attached multi_HXs.bkp example file.")
			[ ] APlus.LaunchFaster(false,false)
			[ ] APlus.SetActive()
			[ ] //APlus.Open(sDataout+"\"+sCaseName,1)
			[ ] APlus.Open(sDatain+"\"+sCaseName,0)
		[+] Print("Step 2: Click the EDR activation button, the following Exchanger Summary Table window (non - modal) will be opened with Model Status and operational risks displayed.")
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //a
				[ ] lsModels=APlus.GetModelsInSummaryTable()
				[+] for(i=1;i<=ListCount(lsModels);i++)
					[+] if(APlus.GetModelType(lsModels[i]))
						[ ] iSimple++
						[ ] //b
						[ ] APlus.ctrlEDRDashboard.Click()
						[ ] sleep(3)
						[ ] string sText =APlus.dgGeneralTable.Find("/WPFDataGridRow[{i}]//WPFDataGridCell[3]").GetProperty("Text")
						[+] if(Matchstr( "*Convert to Rigorous*",sText))
							[ ] Log.Pass("In line {i}, model Status for Simple models is displayed as Convert to Rigorous.")
						[+] else
							[ ] Log.Fail("In line {i}, model Status for Simple models is not displayed as Convert to Rigorous.")
						[ ] //c_ could not recognize the circle's color
					[+] else
						[ ] iRigorous++
						[ ] //b
						[ ] APlus.ctrlEDRDashboard.Click()
						[ ] sleep(3)
						[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[{i}]//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
							[ ] Log.Pass("In line {i}, model Status for Rigorous models is displayed as Revert to Simple.")
						[+] else
							[ ] Log.Fail("In line {i}, model Status for Rigorous models is not displayed as Revert to Simple.")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[ ] print(iSimple)
				[ ] print(iRigorous)
				[+] if(iSimple==Val(APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture()))
					[ ] Log.Pass("The number shown in dashboard for the simple models is the same as that Aspen Plus contains.")
				[+] else
					[ ] Log.Fail("The number shown in dashboard for the simple models is not the same as that Aspen Plus contains. On dashboard, it's {APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture()}, Actual: it's{iSimple}.")
				[+] if(iRigorous==Val(APlus.ctrlEDRDashboard.ctrlOK.TextCapture())+Val(APlus.ctrlEDRDashboard.ctrlAtRisk.TextCapture()))
					[ ] Log.Pass("OK/At Risk are rigorous in dashboard.")
				[+] else
					[ ] Log.Fail("OK/At Risk are not rigorous in dashboard.")
				[ ] //Step 3
				[ ] APlus.SetActive()
				[ ] APlus.btnExpandOrCollapse.Click()
				[+] if(!APlus.ctrlEDRDashboard.txtCaption.Exists(5))
					[ ] Log.Pass("The dashboard is minimized.")
				[+] else
					[ ] Log.Fail("The dashboard is not minimized.")
				[ ] APlus.SetActive()
				[ ] APlus.btnExpandOrCollapse.Click()
				[+] if(APlus.ctrlEDRDashboard.txtCaption.Exists(5))
					[ ] Log.Pass("The dashboard appears.")
				[+] else
					[ ] Log.Fail("The dashboard does not appear.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Make sure that Unknown is Simple, OK/At Risk are rigorous in dashboard.")
		[ ] Print("Make sure that in Exchanger Summary Table, Model Status for Simple models is displayed as Convert to Rigorous and Revert to Simple for Rigorous models.")
		[ ] Print("Make sure the color for Operational Risk is Green – OK; Yellow – Warning; Red – Risk;")
		[ ] Print("Step 3: Click the up arrow and the dashboards will be minimized. Click the down arrow and the dashboards will appear.")
		[+] // Print("Step 4: When the width of Aspen Plus window is small, click the right arrow and EDR dashboard will be fully displayed; click the left arrow and EE dashboard will be fully displayed.")
			[ ] // APlus.SetActive()
			[ ] // APlus.Restore()
			[ ] // sleep(3)
			[ ] // APlus.btnRightScroll.Click()
			[+] // if(APlus.ctrlEDRDashboard.ctrlAtRisk.Exists(5))
				[ ] // Log.Pass("Click the right arrow and EDR dashboard is fully displayed.")
			[+] // else
				[ ] // Log.Fail("Click the right arrow and EDR dashboard is not fully displayed.")
			[ ] // APlus.btnLeftScroll.Click()
			[+] // if(APlus.ctrlEEDashboard.txtCaption.Exists(5))
				[ ] // Log.Pass("Click the left arrow and EE dashboard is fully displayed.")
			[+] // else
				[ ] // Log.Fail("Click the left arrow and EE dashboard is not fully displayed.")
		[ ] 
	[ ] 
[+] testcase CQ00510169() appstate CleanState
	[-] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510169"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\SimpleToRigorous"
		[+] list of string lsCaseName={...}
			[ ] "Shortcut.bkp"
			[ ] "Detailed.bkp"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer inum,i
		[ ] string sBitmapDir
	[-] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[-] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
			[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.1.1 Convert Simple/Detailed model to Shell&Tube model – Size Interactively")
		[ ] Print("------------------------------------------------------------------------")
		[-] for(i=1;i<=ListCount(lsCaseName);i++)
			[+] Print("Step 1: Launch Aspen Plus, open the attached {lsCaseName[i]} example file.")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.OpenFaster("{sDataout}\{lsCaseName[i]}",0)
			[+] Print("Step 2: Reset and run the file.")
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
			[-] Print("Step 3: Click the EDR dashboard and open the Exchanger Summary Table.")
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[-] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 4
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[-] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] //Step 5
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size Shell&Tube window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] //Step 6
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnCancel.Click()
							[+] if(wEDRSizingConsole.dlgCancel.Exists(15))
								[ ] wEDRSizingConsole.dlgCancel.SetActive()
								[ ] wEDRSizingConsole.dlgCancel.btnNo.Click()
								[ ] sleep(1)
							[+] else
								[ ] Log.Fail("Cancel confirm window does not pop up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnCancel.Click()
							[+] if(wEDRSizingConsole.dlgCancel.Exists(15))
								[ ] wEDRSizingConsole.dlgCancel.SetActive()
								[ ] wEDRSizingConsole.dlgCancel.btnYes.Click()
								[ ] sleep(2)
							[+] else
								[ ] Log.Fail("Cancel confirm window does not pop up.")
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
					[ ] APlus.SetTab("B1 (HeatX)")
					[ ] sleep(1)
					[+] if(APlus.rdbShortcut.IsChecked || APlus.rdbDetailed.IsChecked)
						[ ] Log.Pass("The simple model is not converted to the rigorous model.")
					[+] else
						[ ] Log.Fail("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] Print("Step 4: Click the “Convert to Rigorous” button for B1, and the “Covert to Rigorous Exchanger” window will pop up.")
			[ ] Print("Step 5: Select Shell&Tube as Exchanger Type and Size Interactively as Sizing Method. Click the “Convert” button.")
			[ ] Print("Step 6: Click Size button and then the Cancel button. And a dialog will appear.")
			[+] Print("Step 7: Repeat steps 4-5. Click Size and then click Save button on the Size Shell&Tube dialog.")
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size Shell&Tube window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSave.Click()
							[+] if(wEDRSizingConsole.dlgSaveExchangerDesign.Exists(15))
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.SetActive()
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.cboFileName.Click()
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.cboFileName.SetText("{sDataout}\{i}.edr")
								[ ] sleep(1)
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.btnSave.Click()
								[ ] sleep(10)
							[+] else
								[ ] Log.Fail("Save Exchanger Design window does not pop up.")
							[ ] 
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[ ] 
							[ ] // wEDRSizingConsole.Find("//WPFButton[@caption='Accept Design']").Click(1,5,5)
							[ ] 
							[ ] // Agent.SetOption(OPT_VERIFY_ACTIVE, FALSE)
							[ ] // Agent.SetOption(OPT_VERIFY_ENABLED, FALSE)
							[ ] // Agent.SetOption(OPT_VERIFY_APPREADY, FALSE)
							[ ] // Agent.SetOption(OPT_VERIFY_APPREADY, FALSE)
							[ ] // Agent.SetOption(OPT_SYNC_TIMEOUT, 0.1)
							[+] // do
								[ ] // 
								[ ] // wEDRSizingConsole.TextClick("Accept Design")
								[ ] // 
							[+] // except
								[ ] // 
							[ ] // Agent.SetOption(OPT_SYNC_TIMEOUT, 5)
							[ ] // Agent.SetOption(OPT_VERIFY_ACTIVE, TRUE)
							[ ] // Agent.SetOption(OPT_VERIFY_ENABLED, TRUE)
							[ ] // Agent.SetOption(OPT_VERIFY_APPREADY, TRUE)
							[ ] 
							[ ] 
							[ ] 
							[ ] 
							[ ] // glWaitForExists(wWarning, 10)
							[+] // if wWarning.Exists(50)
								[ ] // 
								[ ] // wWarning.SetActive()
								[ ] // wWarning.TextClick("OK")
								[ ] // 
							[ ] 
							[+] if(wWarning.Exists(100))
								[ ] wWarning.SetActive()
								[ ] wWarning.btnYes.Click()
								[ ] 
							[ ] sleep(5)
							[ ] //Verification
							[ ] 
							[ ] 
							[ ] glwEDR.Invoke()
							[ ] glwEDR.SetActive()
							[ ] 
							[ ] glwEDR.OpenFile("{sDataout}\{i}.edr")
							[+] do
								[ ] sleep(5)
								[ ] glwEDR.SetActive()
								[ ] 
								[ ] glwEDR.Maximize()
								[ ] Log.Pass("No error occurs when opening the saved EDR file.")
							[+] except
								[ ] ExceptClear()
								[ ] Log.Fail("Error occurs when opening the saved EDR file.")
							[ ] glwEDR.Exit()
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[+] Print("Step 8: Click Accept Design button.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("B1 (HeatX)")
				[ ] sleep(1)
				[+] if(APlus.rdbShellTube.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] Print("Step 9: Repeat above steps with the attached Detailed.bkp file.")
				[ ] APlus.SetActive()
				[ ] APlus.CloseDocument()
				[ ] APlus.Exit()
		[ ] 
	[ ] 
[+] testcase CQ00510171() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 3, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510171"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\SimpleToRigorous"
		[+] list of string lsCaseName={...}
			[ ] "Shortcut.bkp"
			[ ] "Detailed.bkp"
		[ ] string sTemplateFile="CS_Floating_Head_US.EDT"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer inum,i
		[ ] string sBitmapDir,sTemp1,sTemp2,sTemp3
		[ ] RECT r
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
			[ ] sleep(2)
		[ ] File.Copy(sDatain+"\EDT\"+sTemplateFile,sDataout)
	[+] // Case script
		[ ] Print("4.4.1.2. Convert Simple model to Shell&Tube model -- Size Interactively using Template")
		[ ] Print("------------------------------------------------------------------------")
		[ ] APlus.Launch()
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[+] Print("Step 1: Launch Aspen Plus, open the attached ShutCut.bkp example file.")
				[ ] APlus.SetActive()
				[ ] APlus.OpenFaster("{sDataout}\{lsCaseName[i]}",0)
			[+] Print("Step 2: Reset and run the file.")
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
			[+] Print("Step 3: Click the EDR dashboard and open the Exchanger Summary Table.")
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 4
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] //Step 5
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractivelyusingTemplate.Select()
						[ ] sleep(1)
						[ ] //Step 6
						[ ] wConverttoRigorousExchanger.btnTemplateBrowse.Click()
						[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
							[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.Click()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.SetText("{sDataout}\{sTemplateFile}")
							[ ] sleep(1)
							[ ] wConverttoRigorousExchanger.dlgOpen.btnCancel.Click()
						[+] else
							[ ] Log.Fail("Open window does not pop up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.Close()
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/B1")
				[ ] sleep(2)
				[+] if(APlus.rdbShortcut.IsChecked || APlus.rdbDetailed.IsChecked)
					[ ] Log.Pass("The simple model is not converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model has been converted to the rigorous model.")
			[ ] Print("Step 4: Click the “Convert to Rigorous” button for B1, and the “Covert to Rigorous Exchanger” window will pop up.")
			[ ] Print("Step 5: Select Shell&Tube as the model type and Size Interactively using Template as Sizing Method.")
			[ ] Print("Step 6: Browse to the attached template file CS_Floating_Head_US.EDT")
			[ ] Print("Step 7: Click Cancel button.")
			[+] Print("Step 8: Repeat step 6 then click Close button")
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractivelyusingTemplate.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnTemplateBrowse.Click()
						[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
							[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.Click()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.SetText("{sDataout}\{sTemplateFile}")
							[ ] sleep(1)
							[ ] wConverttoRigorousExchanger.dlgOpen.Close()
						[+] else
							[ ] Log.Fail("Open window does not pop up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.Close()
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/B1")
				[ ] sleep(2)
				[+] if(APlus.rdbShortcut.IsChecked || APlus.rdbDetailed.IsChecked)
					[ ] Log.Pass("The simple model is not converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model has been converted to the rigorous model.")
			[+] Print("Step 9: Repeat step 6 and click Convert button")
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractivelyusingTemplate.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnTemplateBrowse.Click()
						[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
							[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.Click()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.SetText("{sDataout}\{sTemplateFile}")
							[ ] sleep(1)
							[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
							[ ] sleep(3)
							[+] if !wConverttoRigorousExchanger.btnConvert.IsEnabled
								[ ] sleep(10)
						[+] else
							[ ] Log.Fail("Open window does not pop up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] 
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size Shell&Tube window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[ ] //Step 10
							[ ] 
							[+] if(wWarning.Exists(100))
								[ ] wWarning.SetActive()
								[ ] wWarning.btnYes.Click()
								[ ] 
							[ ] 
							[ ] sleep(5)
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/B1")
				[ ] sleep(2)
			[+] Print("Step 10: Click Size button and then Accept Design button.")
				[+] if(APlus.rdbShellTube.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] Print("Step 11: Click the Exchanger Name B1 and EDR Browser will be opened.")
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] APlus.dgGeneralTable.Find("//WPFTextBlock[@automationId='hyperlink']/WPFTextBlock[@caption='B1']").Click()
					[ ] sleep(7)
					[+] do 
						[ ] APlus.SetActive()
						[ ] APlus.SetTab("B1 (HeatX) - EDR Browser")
						[ ] Log.Pass("The exchanger name B1 and EDR browser openes.")
						[ ] sTemp1=SubStr(APlus.tpgEDRBrowser.cboTEMAType1.TextCapture(),1,1)
						[ ] sTemp2=SubStr(APlus.tpgEDRBrowser.cboTEMAType2.TextCapture(),1,1)
						[ ] sTemp3=SubStr(APlus.tpgEDRBrowser.cboTEMAType3.TextCapture(),1,1)
						[+] if(sTemp1=="A" && sTemp2=="E" && sTemp3=="S")
							[ ] Log.Pass("TEMA type is AES.")
						[+] else
							[ ] Log.Fail("TEMA type is not AES, it's {sTemp1}{sTemp2}{sTemp3}.")
						[+] if(APlus.tpgEDRBrowser.cboTubePatten.TextCapture()=="90	-	Square")
							[ ] Log.Pass("Tube pattern is 90-Square.")
						[+] else
							[ ] Log.Fail("Tube pattern is not 90-Square.")
					[+] except
						[ ] ExceptClear()
						[ ] Log.Fail("The exchanger name B1 and EDR browser does not opene.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.CloseDocument()
		[ ] 
	[ ] 
[+] testcase CQ00510173() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 3, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510173"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\SimpleToRigorous"
		[+] list of string lsCaseName={...}
			[ ] "Shortcut.bkp"
			[ ] "Detailed.bkp"
		[ ] string sTemplateFile="HTFS-ST.EDR"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer inum,i
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
			[ ] sleep(2)
		[ ] File.Copy(sDatain+"\EDR\"+sTemplateFile,sDataout)
	[+] // Case script
		[ ] Print("4.4.1.3. Convert Simple model to Shell&Tube model -- Import EDR File")
		[ ] Print("------------------------------------------------------------------------")
		[ ] APlus.Launch()
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[+] Print("Step 1: Launch Aspen Plus, open the attached ShutCut.bkp example file.")
				[ ] APlus.SetActive()
				[ ] APlus.OpenFaster("{sDataout}\{lsCaseName[i]}",0)
			[+] Print("Step 2: Reset and run the file.")
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
			[+] Print("Step 3: Click the EDR dashboard and open the Exchanger Summary Table.")
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 4
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] //Step 5
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSpecifyExchangerGeometry.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbImportEDRFile.Select()
						[ ] sleep(1)
						[ ] //Step 6
						[ ] wConverttoRigorousExchanger.btnImportBrowse.Click()
						[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
							[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.Click()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.SetText("{sDataout}\{sTemplateFile}")
							[ ] sleep(1)
							[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[+] else
							[ ] Log.Fail("Open window does not pop up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wWarning.Exists(100))
							[ ] wWarning.SetActive()
							[ ] wWarning.btnYes.Click()
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] Print("Step 4: Click the “Convert to Rigorous” button for B1, and the “Covert to Rigorous Exchanger” window will pop up.")
			[ ] Print("Step 5: Select Shell&Tube as the Model Type and Import EDR File as Sizing Method.")
			[ ] Print("Step 6: Browse to the attached template file HTFS-ST.EDR and click Convert button.")
			[+] Print("Step 7: The simple model is converted to rigorous model successfully.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/B1")
				[ ] sleep(2)
				[+] if(APlus.rdbShellTube.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] Print("Step 8: Repeat above steps with the attached Detailed.bkp file")
				[ ] APlus.SetActive()
				[ ] APlus.CloseDocument()
			[ ] 
	[ ] 
[+] testcase CQ00510175() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 7, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510175"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\SimpleToAirCooled"
		[+] list of string lsCaseName={...}
			[ ] "Shortcut AC.bkp"
			[ ] "Detailed AC.bkp"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer inum,i
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
			[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.1.1. Convert Simple model to AirCooled model -- Size Interactively")
		[ ] Print("------------------------------------------------------------------------")
		[-] for(i=1;i<=ListCount(lsCaseName);i++)
			[+] Print("Step 1: Launch Aspen Plus, open the attached {lsCaseName[i]} example file.")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.OpenFaster("{sDataout}\{lsCaseName[i]}",0)
			[+] Print("Step 2: Reset and run the case.")
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
			[+] Print("Step 3: Click the EDR dashboard and open the Exchanger Summary Table.")
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 4
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] //Step 5
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbAirCooled.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size AirCooled window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] //Step 6
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnCancel.Click()
							[+] if(wEDRSizingConsole.dlgCancel.Exists(15))
								[ ] wEDRSizingConsole.dlgCancel.SetActive()
								[ ] wEDRSizingConsole.dlgCancel.btnNo.Click()
								[ ] sleep(1)
							[+] else
								[ ] Log.Fail("Cancel confirm window does not pop up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnCancel.Click()
							[+] if(wEDRSizingConsole.dlgCancel.Exists(15))
								[ ] wEDRSizingConsole.dlgCancel.SetActive()
								[ ] wEDRSizingConsole.dlgCancel.btnYes.Click()
								[ ] sleep(2)
							[+] else
								[ ] Log.Fail("Cancel confirm window does not pop up.")
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
					[ ] APlus.SetTab("HTFS-AC (HeatX)")
					[ ] sleep(1)
					[+] if(APlus.rdbShortcut.IsChecked || APlus.rdbDetailed.IsChecked)
						[ ] Log.Pass("The simple model is not converted to the rigorous model.")
					[+] else
						[ ] Log.Fail("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] Print("Step 4: Click the “Convert to Rigorous” button for B1, and the “Covert to Rigorous Exchanger” window will pop up.")
			[ ] Print("Step 5: Select AirCooled as Exchanger Type and Size Interactively as Sizing Method. Click the “Convert” button")
			[ ] Print("Step 6: Click Size button and then the Cancel button. And a dialog will appear.")
			[-] Print("Step 7: Repeat steps 4-5. Click Size and then click Save button on the Size Shell&Tube dialog.")
				[ ] APlus.ctrlEDRDashboard.Click()
				[-] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[-] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbAirCooled.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[-] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size AirCooled window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSave.Click()
							[+] if(wEDRSizingConsole.dlgSaveExchangerDesign.Exists(15))
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.SetActive()
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.cboFileName.Click()
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.cboFileName.SetText("{sDataout}\{i}.edr")
								[ ] sleep(1)
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.btnSave.Click()
								[ ] sleep(1)
							[+] else
								[ ] Log.Fail("Save Exchanger Design window does not pop up.")
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[+] if(wWarning.Exists(100))
								[ ] wWarning.SetActive()
								[ ] wWarning.btnYes.Click()
							[ ] sleep(5)
							[ ] //Verification
							[ ] glwEDR.Invoke()
							[ ] glwEDR.OpenFile("{sDataout}\{i}.edr")
							[+] do
								[ ] glwEDR.Maximize()
								[ ] Log.Pass("No error occurs when opening the saved EDR file.")
							[+] except
								[ ] ExceptClear()
								[ ] Log.Fail("Error occurs when opening the saved EDR file.")
							[ ] glwEDR.Exit()
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[+] Print("Step 8: Click Accept Design button.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("HTFS-AC (HeatX)")
				[ ] sleep(1)
				[+] if(APlus.rdbAirCooled.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] Print("Step 9. Run the case and verify there is no error.")
				[ ] APlus.SetActive()
				[ ] APlus.Run()
				[ ] APlus.Verify_AP_Status("Results Available")
			[+] Print("Step 10. Repeat above steps with the attached Detailed AC.bkp file.")
				[ ] APlus.SetActive()
				[ ] APlus.CloseDocument()
				[ ] APlus.Exit()
			[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510176() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 3, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510176"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\SimpleToAirCooled"
		[+] list of string lsCaseName={...}
			[ ] "Shortcut AC.bkp"
			[ ] "Detailed AC.bkp"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] 
		[ ] string sTemplateFile="CS_Air_Cooled_SI.EDT"
		[ ] integer i
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
		[ ] File.Copy(sDatain+"\EDT\"+sTemplateFile,sDataout)
		[ ] sleep(2)
	[+] // Case script
		[ ] Print("4.4.1.2. Convert Simple model to EDR rigorous model -- Size Interactively using Template")
		[ ] Print("------------------------------------------------------------------------")
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[+] Print("Step 1: Launch Aspen Plus, open the attached ShutCut.bkp example file. ")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.OpenFaster("{sDataout}\{lsCaseName[i]}",0)
			[+] Print("Step 2: Reset and run the file.")
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
			[+] Print("Step 3: Click the EDR dashboard and open the Exchanger Summary Table.")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 4
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] //Step 5
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbAirCooled.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractivelyusingTemplate.Select()
						[ ] sleep(1)
						[ ] //Step 6
						[ ] wConverttoRigorousExchanger.btnTemplateBrowse.Click()
						[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
							[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.Click()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.SetText("{sDataout}\{sTemplateFile}")
							[ ] sleep(1)
							[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[+] else
							[ ] Log.Fail("Open window does not pop up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size AirCooled window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnCancel.Click()
							[+] if(wEDRSizingConsole.dlgCancel.Exists(15))
								[ ] wEDRSizingConsole.dlgCancel.SetActive()
								[ ] wEDRSizingConsole.dlgCancel.btnNo.Click()
								[ ] sleep(1)
							[+] else
								[ ] Log.Fail("Cancel confirm window does not pop up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnCancel.Click()
							[+] if(wEDRSizingConsole.dlgCancel.Exists(15))
								[ ] wEDRSizingConsole.dlgCancel.SetActive()
								[ ] wEDRSizingConsole.dlgCancel.btnYes.Click()
								[ ] sleep(2)
							[+] else
								[ ] Log.Fail("Cancel confirm window does not pop up.")
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/HTFS-AC")
				[ ] sleep(2)
				[+] if(APlus.rdbShortcut.IsChecked || APlus.rdbDetailed.IsChecked)
					[ ] Log.Pass("The simple model is not converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model has been converted to the rigorous model.")
			[ ] Print("Step 4: Click the “Convert to Rigorous” button for B1, and the “Covert to Rigorous Exchanger” window will pop up.")
			[ ] Print("Step 5: Select AirCooled as Exchanger Type and Size Interactively Using Template as Sizing Method. The Convert button is inactive.")
			[ ] Print("Step 6: Browse to the attached template file CS_Air_Cooled_SI.EDT and click Convert button.")
			[ ] Print("Step 7: Click Size button and then the Cancel button. And a dialog will appear.")
			[+] Print("Step 8: Repeat steps 4-5. Click Size and then click Save button on the Size Shell&Tube dialog.")
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbAirCooled.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractivelyusingTemplate.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnTemplateBrowse.Click()
						[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
							[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.Click()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.SetText("{sDataout}\{sTemplateFile}")
							[ ] sleep(1)
							[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[+] else
							[ ] Log.Fail("Open window does not pop up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size AirCooled window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()  
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSave.Click()
							[+] if(wEDRSizingConsole.dlgSaveExchangerDesign.Exists(15))
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.SetActive()
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.cboFileName.Click()
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.cboFileName.SetText("{sDataout}\{i}.edr")
								[ ] sleep(1)
								[ ] wEDRSizingConsole.dlgSaveExchangerDesign.btnSave.Click()
								[ ] sleep(1)
							[+] else
								[ ] Log.Fail("Save Exchanger Design window does not pop up.")
							[ ] //Step 9
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[+] if(wWarning.Exists(100))
								[ ] wWarning.SetActive()
								[ ] wWarning.btnYes.Click()
							[ ] sleep(5)
							[ ] //Verification
							[ ] glwEDR.Invoke()
							[ ] glwEDR.OpenFile("{sDataout}\{i}.edr")
							[+] do
								[ ] glwEDR.Maximize()
								[ ] Log.Pass("No error occurs when opening the saved EDR file.")
							[+] except
								[ ] ExceptClear()
								[ ] Log.Fail("Error occurs when opening the saved EDR file.")
							[ ] glwEDR.Exit()
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/HTFS-AC")
				[ ] sleep(2)
				[+] if(APlus.rdbAirCooled.IsChecked)
					[ ] Log.Pass("The simple model is not converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model has been converted to the rigorous model.")
			[ ] Print("Step 9: Click Accept Design button.")
			[+] Print("Step 10: Run the case and verify there is no error.")
				[ ] APlus.SetActive()
				[ ] APlus.Run()
				[ ] APlus.Verify_AP_Status("Results Available")
			[+] Print("Step 11. Repeat above steps with the attached Detailed AC.bkp file.")
				[ ] APlus.SetActive()
				[ ] APlus.CloseDocument()
				[ ] APlus.Exit()
		[ ] 
	[ ] 
[+] testcase CQ00510177() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 3, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510177"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\SimpleToAirCooled"
		[+] list of string lsCaseName={...}
			[ ] "Shortcut AC.bkp"
			[ ] "Detailed AC.bkp"
		[ ] string sTemplateFile="HTFS-AC.EDR"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer inum,i
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
			[ ] sleep(2)
		[ ] File.Copy(sDatain+"\EDR\"+sTemplateFile,sDataout)
		[ ] sleep(1)
	[+] // Case script
		[ ] Print("4.4.2.3. Convert Simple model to AirCooled model -- Import EDR File")
		[ ] Print("------------------------------------------------------------------------")
		[ ] APlus.Launch()
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[+] Print("Step 1: Launch Aspen Plus, open the attached ShutCut AC.bkp example file. ")
				[ ] APlus.SetActive()
				[ ] APlus.OpenFaster("{sDataout}\{lsCaseName[i]}",0)
			[+] Print("Step 2: Reset and run the file.")
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
			[+] Print("Step 3: Click the EDR dashboard and open the Exchanger Summary Table.")
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 4
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] //Step 5
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbAirCooled.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSpecifyExchangerGeometry.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbImportEDRFile.Select()
						[ ] sleep(1)
						[ ] //Step 6
						[ ] wConverttoRigorousExchanger.btnImportBrowse.Click()
						[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
							[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.Click()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.SetText("{sDataout}\{sTemplateFile}")
							[ ] sleep(1)
							[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[+] else
							[ ] Log.Fail("Open window does not pop up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wWarning.Exists(100))
							[ ] wWarning.SetActive()
							[ ] wWarning.btnYes.Click()
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] Print("Step 4: Click the “Convert to Rigorous” button for B1, and the “Covert to Rigorous Exchanger” window will pop up.")
			[ ] Print("Step 5: Select Air Cooled as Exchanger Type and select Import EDR File as Sizing Method.")
			[ ] Print("Step 6: Browse to the attached EDR file HTFS-AC.EDR and click Convert button.")
			[+] Print("Step 7: The simple model is converted to rigorous model successfully.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/HTFS-AC")
				[ ] sleep(2)
				[+] if(APlus.rdbAirCooled.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] Print("Step 8: Run the case and verify there is no error.")
				[ ] APlus.SetActive()
				[ ] APlus.Run()
				[ ] APlus.Verify_AP_Status("Results Available")
			[+] Print("Step 9. Repeat above steps with the attached Detailed AC.bkp file.")
				[ ] APlus.SetActive()
				[ ] APlus.CloseDocument()
		[ ] 
	[ ] 
[+] testcase CQ00510178() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 3, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510178"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\SimpleToRigorous"
		[+] list of string lsCaseName={...}
			[ ] "Shortcut.bkp"
			[ ] "Detailed.bkp"
		[ ] string sTemplateFile="HTFS-PL.EDR"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer inum,i
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
			[ ] sleep(2)
		[ ] File.Copy(sDatain+"\EDR\"+sTemplateFile,sDataout)
		[ ] sleep(1)
	[+] // Case script
		[ ] Print("4.4.3.1 Convert Simple model to Plate model -- Import EDR File")
		[ ] Print("------------------------------------------------------------------------")
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[+] Print("Step 1: Launch Aspen Plus, open the attached ShutCut.bkp example file.")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.OpenFaster("{sDataout}\{lsCaseName[i]}",0)
			[+] Print("Step 2: Reset and run the file.")
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
			[+] Print("Step 3: Click the EDR dashboard and open the Exchanger Summary Table.")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 4
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] //Step 5
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbPlate.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSpecifyExchangerGeometry.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbImportEDRFile.Select()
						[ ] sleep(1)
						[ ] //Step 6
						[ ] wConverttoRigorousExchanger.btnImportBrowse.Click()
						[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
							[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.Click()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.SetText("{sDataout}\{sTemplateFile}")
							[ ] sleep(1)
							[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[+] else
							[ ] Log.Fail("Open window does not pop up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.Close()
						[+] if(wWarning.Exists(100))
							[ ] wWarning.SetActive()
							[ ] wWarning.btnYes.Click()
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] Print("Step 4: Click the “Convert to Rigorous” button for B1, and the “Covert to Rigorous Exchanger” window will pop up.")
			[ ] Print("Step 5: Select Plate as Exchanger Type and select Import EDR File as Sizing Method.")
			[+] Print("Step 6: Browse to the attached EDR file HTFS-PL.EDR and close the ‘Convert to Rigorous Exchanger’ dialog.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/B1")
				[ ] sleep(2)
				[+] if(APlus.rdbShortcut.IsChecked || APlus.rdbDetailed.IsChecked)
					[ ] Log.Pass("The simple model is not converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model has been converted to the rigorous model.")
			[+] Print("Step 7: Repeat steps 4-6 and click Convert button.")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbPlate.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSpecifyExchangerGeometry.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbImportEDRFile.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnImportBrowse.Click()
						[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
							[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.Click()
							[ ] wConverttoRigorousExchanger.dlgOpen.txtFileName.SetText("{sDataout}\{sTemplateFile}")
							[ ] sleep(1)
							[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[+] else
							[ ] Log.Fail("Open window does not pop up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wWarning.Exists(100))
							[ ] wWarning.SetActive()
							[ ] wWarning.btnYes.Click()
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[+] Print("Step 8: The simple model is converted to rigorous model successfully.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/B1")
				[ ] sleep(2)
				[+] if(APlus.rdbPlate.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] Print("Step 9. Run the case and verify there is no error.")
				[ ] APlus.SetActive()
				[ ] APlus.Run()
				[ ] APlus.Verify_AP_Status("Results Available")
			[+] Print("Step 10. Repeat above steps with the attached Detailed.bkp file")
				[ ] APlus.SetActive()
				[ ] APlus.CloseDocument()
				[ ] APlus.Exit()
			[ ] 
		[ ] 
	[ ] 
[ ] 
[+] testcase CQ00510180() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 3, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510180"
		[ ] sCaseName=sAspenPlusExamples+"\EDR\EDR-ShellTube.apwz"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] 
		[ ] integer i
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
	[+] // Case script
		[ ] Print("4.5.1.1 Convert Shell&Tube model to Simple model -- First Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[-] for(i=1;i<=2;i++)
			[-] Print("Step 1: Launch Aspen Plus; open the EDR-ShellTube.apwz from Aspen Plus example file.")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.OpenFaster(sCaseName)
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
			[-] Print("Step 2: Click the EDR dashboard to open Exchanger Summary Table.")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[ ] APlus.ctrlEDRDashboard.DoubleClick()//added
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 3
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wRevertShortcutExchangerModel.Exists(20))
						[ ] wRevertShortcutExchangerModel.SetActive()
						[ ] wRevertShortcutExchangerModel.Close()
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/EDR-ST")
				[ ] sleep(2)
				[+] if(APlus.rdbShellTube.IsChecked)
					[ ] Log.Pass("The exchanger model remains as rigorous.")
				[+] else
					[ ] Log.Fail("The exchanger model does not remain as rigorous.")
			[-] Print("Step 3: Click the Revert to Simple button in Model Status column for EDR-ST.")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[ ] APlus.ctrlEDRDashboard.DoubleClick()//added
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wRevertShortcutExchangerModel.Exists(20))
						[ ] wRevertShortcutExchangerModel.SetActive()
						[ ] //wRevertShortcutExchangerModel.rdbShortcutWithEDR.Select()
						[ ] wRevertShortcutExchangerModel.Find("//WPFRadioButton[{i}]").Select()
						[ ] sleep(1)
						[ ] wRevertShortcutExchangerModel.btnRevert.Click()
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/EDR-ST")
				[ ] sleep(2)
				[+] if(APlus.rdbShortcut.IsChecked)
					[ ] Log.Pass("The exchanger model changes to Shortcut.")
					[ ] APlus.SetTab("Specifications")
					[+] if(i==1)
						[+] if(APlus.txtThird.TextCapture()!=null || APlus.txtThird.TextCapture()!="")
							[ ] Log.Pass("Constant UA value displays.")
						[+] else
							[ ] Log.Fail("Constant UA value does not display.")
						[ ] APlus.SetActive()
						[ ] APlus.SetTab("Pressure Drop")
						[ ] sleep(1)
						[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="")
							[ ] Log.Pass("Outlet Pressure value displays.")
						[+] else
							[ ] Log.Fail("Outlet Pressure value does not display.")
					[+] else
						[+] if(APlus.txtThird.TextCapture()==null || APlus.txtThird.TextCapture()=="")
							[ ] Log.Pass("Constant UA value does not display.")
						[+] else
							[ ] Log.Fail("Constant UA value displays.")
						[ ] APlus.SetActive()
						[ ] APlus.SetTab("Pressure Drop")
						[ ] sleep(1)
						[+] if(APlus.txtFirst.TextCapture()==null || APlus.txtFirst.TextCapture()=="0")
							[ ] Log.Pass("Outlet Pressure value does not display.")
						[+] else
							[ ] Log.Fail("Outlet Pressure value displays.")
				[+] else
					[ ] Log.Fail("The exchanger model does not change to Shortcut.")
			[+] Print("Step 4: After revert, verify that the EDR dashboard and Exchanger Summary Table are updated.")
					[ ] APlus.SetActive()
					[ ] APlus.ctrlEDRDashboard.Click()
					[ ] APlus.ctrlEDRDashboard.DoubleClick()//added
					[+] if(wHelp.Exists(50))
						[ ] wHelp.Close()
						[ ] sleep(2)
					[+] if(APlus.tbiExchangerSummary.Exists())
						[-] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
							[ ] Log.Pass("The EDR dashboard and Exchanger Summary table are updated.")
						[+] else
							[ ] Log.Fail("The EDR dashboard and Exchanger Summary table are not updated.")
					[+] else
						[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] 
			[ ] APlus.SetActive()
			[ ] APlus.CloseDocument()
			[ ] APlus.Exit()
	[ ] 
[+] testcase CQ00510181() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 3, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510181"
		[ ] sCaseName=sAspenPlusExamples+"\EDR\EDR-ShellTube.apwz"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] 
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
	[+] // Case script
		[ ] Print("4.5.1.2 Convert Shell&Tube model to Simple model -- Second Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: 1.	Launch Aspen Plus; open and run the EDR-ShellTube.apwz from Aspen Plus example file.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.OpenFaster(sCaseName)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.tbHome.Click()
			[ ] APlus.grpRun.btnRun.Click()
			[ ] sleep(3)
			[ ] glWaitForMouseIdle(100)
			[+] if(wSimulationWarnings.Exists(3))
				[ ] wSimulationWarnings.SetActive()
				[ ] wSimulationWarnings.btnCancel.Click()
				[ ] sleep(5)
		[-] Print("Step 2: 2.	Go to Block EDR-ST, Setup form, Specifications tab.")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/EDR-ST")
			[ ] sleep(2)
		[-] Print("Step 3: 3.	Click Reconcile button.")
			[ ] APlus.btnReconcileEDR.Click()
			[ ] sleep(2)
			[+] if(APlus.rdbShortcut.IsChecked)
				[ ] Log.Pass("The exchanger model changes to Shortcut.")
				[ ] APlus.SetTab("Specifications")
				[+] if(APlus.txtThird.TextCapture()!=null || APlus.txtThird.TextCapture()!="")
					[ ] Log.Pass("Constant UA value in 'Specifications' tab displays.")
				[+] else
					[ ] Log.Fail("Constant UA value in 'Specifications' tab does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("Pressure Drop")
				[ ] sleep(1)
				[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="")
					[ ] Log.Pass("Outlet Pressure value displays.")
				[+] else
					[ ] Log.Fail("Outlet Pressure value does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("U Methods")
				[ ] sleep(1)
				[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="")
					[ ] Log.Pass("Constant UA value in 'U Methods' tab displays.")
				[+] else
					[ ] Log.Fail("Constant UA value in 'U Methods' tab does not display.")
			[+] else
				[ ] Log.Fail("The exchanger model does not change to Shortcut.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[ ] APlus.ctrlEDRDashboard.DoubleClick()//added
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
					[ ] Log.Pass("The EDR dashboard and Exchanger Summary table are updated.")
				[+] else
					[ ] Log.Fail("The EDR dashboard and Exchanger Summary table are not updated.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] 
	[ ] 
[+] testcase CQ00510182() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 3, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510182"
		[ ] sCaseName=sAspenPlusExamples+"\EDR\EDR-ShellTube.apwz"
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] 
		[ ] Dir.Delete(sDataout)
	[-] // Case script
		[ ] Print("4.5.1.3 Convert Shell&Tube model to Simple model -- Third Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus; open and run the EDR-ShellTube.apwz from Aspen Plus example file.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.OpenFaster(sCaseName)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.tbHome.Click()
			[ ] APlus.grpRun.btnRun.Click()
			[ ] sleep(3)
			[ ] glWaitForMouseIdle(100)
			[+] if(wSimulationWarnings.Exists(3))
				[ ] wSimulationWarnings.SetActive()
				[ ] wSimulationWarnings.btnCancel.Click()
				[ ] sleep(5)
		[-] Print("Step 2: Go to Block EDR-ST, Setup form, Specifications tab.")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/EDR-ST")
			[ ] sleep(2)
		[-] Print("Step 3: Select the Model fidelity from Shell & Tube to Shortcut.")
			[ ] APlus.SetActive()
			[ ] APlus.rdbShortcut.Check()
			[ ] sleep(2)
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[ ] APlus.ctrlEDRDashboard.DoubleClick()//added
			[-] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[-] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
					[ ] Log.Pass("The EDR dashboard and Exchanger Summary table are updated.")
				[+] else
					[ ] Log.Fail("The EDR dashboard and Exchanger Summary table are not updated.")
			[-] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] 
			[ ] 
	[ ] 
[+] testcase CQ00510184() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 3, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510184"
		[ ] sCaseName=sAspenPlusExamples+"\EDR\EDR-ACOL.apwz"
		[ ] integer i
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] 
		[ ] Dir.Delete(sDataout)
	[+] // Case script
		[ ] Print("4.5.2.1 Convert AirCooled model to Simple model -- First Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[+] for(i=1;i<=2;i++)
			[+] Print("Step 1: Launch Aspen Plus; open the EDR-ACOL.apwz from Aspen Plus example file.")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.OpenFaster(sCaseName)
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
			[+] Print("Step 2: Click the EDR dashboard to open Exchanger Summary Table.")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 3
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wRevertShortcutExchangerModel.Exists(20))
						[ ] wRevertShortcutExchangerModel.SetActive()
						[ ] wRevertShortcutExchangerModel.Close()
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/EDR-AC")
				[ ] sleep(2)
				[+] if(APlus.rdbAirCooled.IsChecked)
					[ ] Log.Pass("The exchanger model remains as rigorous.")
				[+] else
					[ ] Log.Fail("The exchanger model does not remain as rigorous.")
			[+] Print("Step 3: Click the Revert to Simple button in Model Status column for EDR-AC.")
					[ ] APlus.SetActive()
					[ ] APlus.ctrlEDRDashboard.Click()
					[+] if(wHelp.Exists(50))
						[ ] wHelp.Close()
						[ ] sleep(2)
					[+] if(APlus.tbiExchangerSummary.Exists())
						[ ] Log.Pass("Exchanger Summary Table appears.")
						[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
						[+] if(wRevertShortcutExchangerModel.Exists(20))
							[ ] wRevertShortcutExchangerModel.SetActive()
							[ ] //wRevertShortcutExchangerModel.rdbShortcutWithEDR.Select()
							[ ] wRevertShortcutExchangerModel.Find("//WPFRadioButton[{i}]").Select()
							[ ] sleep(1)
							[ ] wRevertShortcutExchangerModel.btnRevert.Click()
					[+] else
						[ ] Log.Fail("Exchanger Summary Table does not appear.")
					[ ] APlus.SetActive()
					[ ] APlus.trvPartTree.Expand("/Blocks/")
					[ ] APlus.trvPartTree.Select("/Blocks/EDR-AC")
					[ ] sleep(2)
					[+] if(APlus.rdbShortcut.IsChecked)
						[ ] Log.Pass("The exchanger model changes to Shortcut.")
						[ ] APlus.SetTab("Specifications")
						[+] if(i==1)
							[+] if(APlus.txtThird.TextCapture()!=null || APlus.txtThird.TextCapture()!="")
								[ ] Log.Pass("Constant UA value displays.")
							[+] else
								[ ] Log.Fail("Constant UA value does not display.")
							[ ] APlus.SetActive()
							[ ] APlus.SetTab("Pressure Drop")
							[ ] sleep(1)
							[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="")
								[ ] Log.Pass("Outlet Pressure value displays.")
							[+] else
								[ ] Log.Fail("Outlet Pressure value does not display.")
						[+] else
							[+] if(APlus.txtThird.TextCapture()==null || APlus.txtThird.TextCapture()=="")
								[ ] Log.Pass("Constant UA value does not display.")
							[+] else
								[ ] Log.Fail("Constant UA value displays.")
							[ ] APlus.SetActive()
							[ ] APlus.SetTab("Pressure Drop")
							[ ] sleep(1)
							[+] if(APlus.txtFirst.TextCapture()==null || APlus.txtFirst.TextCapture()=="0")
								[ ] Log.Pass("Outlet Pressure value does not display.")
							[+] else
								[ ] Log.Fail("Outlet Pressure value displays.")
					[+] else
						[ ] Log.Fail("The exchanger model does not change to Shortcut.")
			[+] Print("Step 4: After revert, verify that the EDR dashboard and Exchanger Summary Table are updated.")
					[ ] APlus.SetActive()
					[ ] APlus.ctrlEDRDashboard.Click()
					[+] if(wHelp.Exists(50))
						[ ] wHelp.Close()
						[ ] sleep(2)
					[+] if(APlus.tbiExchangerSummary.Exists())
						[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
							[ ] Log.Pass("The EDR dashboard and Exchanger Summary table are updated.")
						[+] else
							[ ] Log.Fail("The EDR dashboard and Exchanger Summary table are not updated.")
					[+] else
						[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] APlus.SetActive()
			[ ] APlus.CloseDocument()
			[ ] APlus.Exit()
			[ ] 
	[ ] 
[+] testcase CQ00510185() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 10, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510185"
		[ ] sCaseName=sAspenPlusExamples+"\EDR\EDR-ACOL.apwz"
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] 
		[ ] Dir.Delete(sDataout)
	[+] // Case script
		[ ] Print("4.5.2.2 Convert AirCooled model to Simple model -- Second Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus; open and run the EDR-ACOL.apwz from Aspen Plus example file.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.OpenFaster(sCaseName)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
		[+] Print("Step 2: Go to Block EDR-AC, Setup form, Specifications tab.")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/EDR-AC")
			[ ] sleep(2)
		[+] Print("Step 3: Click Reconcile button.")
			[ ] APlus.btnReconcileEDR.Click()
			[ ] sleep(2)
			[+] if(APlus.rdbShortcut.IsChecked)
				[ ] Log.Pass("The exchanger model changes to Shortcut.")
				[ ] APlus.SetTab("Specifications")
				[+] if(APlus.txtThird.TextCapture()!=null || APlus.txtThird.TextCapture()!="")
					[ ] Log.Pass("Constant UA value in 'Specifications' tab displays.")
				[+] else
					[ ] Log.Fail("Constant UA value in 'Specifications' tab does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("Pressure Drop")
				[ ] sleep(1)
				[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="")
					[ ] Log.Pass("Outlet Pressure value displays.")
				[+] else
					[ ] Log.Fail("Outlet Pressure value does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("U Methods")
				[ ] sleep(1)
				[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="")
					[ ] Log.Pass("Constant UA value in 'U Methods' tab displays.")
				[+] else
					[ ] Log.Fail("Constant UA value in 'U Methods' tab does not display.")
			[+] else
				[ ] Log.Fail("The exchanger model does not change to Shortcut.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
					[ ] Log.Pass("The EDR dashboard and Exchanger Summary table are updated.")
				[+] else
					[ ] Log.Fail("The EDR dashboard and Exchanger Summary table are not updated.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] 
	[ ] 
[+] testcase CQ00510186() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 3, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510186"
		[ ] sCaseName=sAspenPlusExamples+"\EDR\EDR-ACOL.apwz"
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] 
		[ ] Dir.Delete(sDataout)
	[+] // Case script
		[ ] Print("4.5.2.3 Convert AirCooled model to Simple model -- Third Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus; open and run the EDR-ACOL.apwz from Aspen Plus example file.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.OpenFaster(sCaseName)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
		[+] Print("Step 2: Go to Block EDR-AC, Setup form, Specifications tab.")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/EDR-AC")
			[ ] sleep(2)
		[+] Print("Step 3: Select the Model fidelity from Air Cooled to Shortcut.")
			[ ] APlus.SetActive()
			[ ] APlus.rdbShortcut.Check()
			[ ] sleep(2)
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
					[ ] Log.Pass("The EDR dashboard and Exchanger Summary table are updated.")
				[+] else
					[ ] Log.Fail("The EDR dashboard and Exchanger Summary table are not updated.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] 
	[ ] 
[+] testcase CQ00510187() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 15, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510187"
		[ ] sCaseName=sAspenPlusExamples+"\EDR\EDR-PLATE.apwz"
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] 
		[ ] Dir.Delete(sDataout)
	[+] // Case script
		[ ] Print("4.5.3.1 Convert Plate model to Simple model -- First Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus; Open the HTFS-PLATE.apwz from Aspen Plus example file.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.OpenFaster(sCaseName)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
		[+] Print("Step 2: Click the EDR dashboard to open the Exchanger Summary Table.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3-a
				[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
				[+] if(wRevertShortcutExchangerModel.Exists(20))
					[ ] wRevertShortcutExchangerModel.SetActive()
					[ ] wRevertShortcutExchangerModel.Close()
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/B1")
			[ ] sleep(2)
			[+] if(APlus.rdbPlate.IsChecked)
				[ ] Log.Pass("The exchanger model remains as rigorous.")
			[+] else
				[ ] Log.Fail("The exchanger model does not remain as rigorous.")
		[+] Print("Step 3: Click the Revert to Simple button in Model Status column for B1.")
			[ ] //b
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
				[+] if(wRevertShortcutExchangerModel.Exists(20))
					[ ] wRevertShortcutExchangerModel.SetActive()
					[ ] wRevertShortcutExchangerModel.rdbShortcutWithEDR.Select()
					[ ] sleep(1)
					[ ] wRevertShortcutExchangerModel.btnRevert.Click()
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/B1")
			[ ] sleep(2)
			[+] if(APlus.rdbShortcut.IsChecked)
				[ ] Log.Pass("The exchanger model changes to Shortcut.")
				[ ] APlus.SetTab("Specifications")
				[+] if(APlus.txtThird.TextCapture()!=null || APlus.txtThird.TextCapture()!="")
					[ ] Log.Pass("Constant UA value displays.")
				[+] else
					[ ] Log.Fail("Constant UA value does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("Pressure Drop")
				[ ] sleep(1)
				[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="")
					[ ] Log.Pass("Outlet Pressure value displays.")
				[+] else
					[ ] Log.Fail("Outlet Pressure value does not display.")
			[+] else
				[ ] Log.Fail("The exchanger model does not change to Shortcut.")
			[ ] APlus.SetActive()
			[ ] APlus.CloseDocument()
			[ ] APlus.Exit()
		[+] Print("Step 4: After revert, verify that the EDR dashboard and Exchanger Summary Table are updated.")
			[ ] //c
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.OpenFaster(sCaseName)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
				[+] if(wRevertShortcutExchangerModel.Exists(20))
					[ ] wRevertShortcutExchangerModel.SetActive()
					[ ] wRevertShortcutExchangerModel.rdbShortcut.Check()
					[ ] sleep(1)
					[ ] wRevertShortcutExchangerModel.btnRevert.Click()
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/B1")
			[ ] sleep(2)
			[+] if(APlus.rdbShortcut.IsChecked)
				[ ] Log.Pass("The exchanger model changes to Shortcut.")
				[ ] APlus.SetTab("Specifications")
				[+] if(APlus.txtThird.TextCapture()==null || APlus.txtThird.TextCapture()=="")
					[ ] Log.Pass("Constant UA value does not display.")
				[+] else
					[ ] Log.Fail("Constant UA value  displays.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("Pressure Drop")
				[ ] sleep(1)
				[+] if(APlus.txtFirst.TextCapture()==null || APlus.txtFirst.TextCapture()=="" || APlus.txtFirst.TextCapture()=="0" )
					[ ] Log.Pass("Outlet Pressure value does not display.")
				[+] else
					[ ] Log.Fail("Outlet Pressure value  displays.")
			[+] else
				[ ] Log.Fail("The exchanger model does not change to Shortcut.")
			[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510188() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 15, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510188"
		[ ] sCaseName=sAspenPlusExamples+"\EDR\EDR-PLATE.apwz"
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] 
		[ ] Dir.Delete(sDataout)
	[+] // Case script
		[ ] Print("4.5.3.2 Convert Plate model to Simple model -- Second Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus; Open the HTFS-PLATE.apwz from Aspen Plus example file.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.OpenFaster(sCaseName)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
		[+] Print("Step 2: Go to Block B1, Setup form, Specifications tab.")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/B1")
			[ ] sleep(2)
		[+] Print("Step 3: Click Reconcile button.")
			[ ] APlus.btnReconcileEDR.Click()
			[ ] sleep(2)
			[+] if(APlus.rdbShortcut.IsChecked)
				[ ] Log.Pass("The exchanger model changes to Shortcut.")
				[ ] APlus.SetTab("Specifications")
				[+] if(APlus.txtThird.TextCapture()!=null || APlus.txtThird.TextCapture()!="")
					[ ] Log.Pass("Constant UA value in 'Specifications' tab displays.")
				[+] else
					[ ] Log.Fail("Constant UA value in 'Specifications' tab does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("Pressure Drop")
				[ ] sleep(1)
				[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="")
					[ ] Log.Pass("Outlet Pressure value displays.")
				[+] else
					[ ] Log.Fail("Outlet Pressure value does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("U Methods")
				[ ] sleep(1)
				[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="" || APlus.txtFirst.TextCapture()!="0" )
					[ ] Log.Pass("Constant UA value in 'U Methods' tab displays.")
				[+] else
					[ ] Log.Fail("Constant UA value in 'U Methods' tab does not display.")
			[+] else
				[ ] Log.Fail("The exchanger model does not change to Shortcut.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
					[ ] Log.Pass("The EDR dashboard and Exchanger Summary table are updated.")
				[+] else
					[ ] Log.Fail("The EDR dashboard and Exchanger Summary table are not updated.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] 
			[ ] 
		[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510190() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Jan 3, 2014
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510190"
		[ ] sCaseName=sAspenPlusExamples+"\EDR\EDR-PLATE.apwz"
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] 
		[ ] Dir.Delete(sDataout)
	[+] // Case script
		[ ] Print("4.5.3.2 Convert Plate model to Simple model -- Third Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus; Open the HTFS-PLATE.apwz from Aspen Plus example file.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.OpenFaster(sCaseName)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
		[+] Print("Step 2: Go to Block B1, Setup form, Specifications tab.")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/B1")
			[ ] sleep(2)
		[+] Print("Step 3: Select the Model fidelity from Plate to Shortcut.")
			[ ] APlus.SetActive()
			[ ] APlus.rdbShortcut.Check()
			[ ] sleep(2)
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
					[ ] Log.Pass("The EDR dashboard and Exchanger Summary table are updated.")
				[+] else
					[ ] Log.Fail("The EDR dashboard and Exchanger Summary table are not updated.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] 
	[ ] 
[+] testcase CQ00510191() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510191"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\Multi HXs"
		[ ] sCaseName="multi_HXs.bkp"
		[ ] 
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer inum,i,j
		[ ] string sBitmapDir
		[ ] RECT r,rfly
		[ ] List of FILEINFO lFiles
		[+] list of string lsPopHeaders={...}
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] "Vibration"
			[ ] "Erosion: RhoV2"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] "Other"
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] lFiles=SYS_GetDirContents(sDatain)
		[+] for i=1 to ListCount(lFiles)
			[ ] File.Copy(sDatain+"\"+lFiles[i].sName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.3.4. Activating EDR activation -- Operational Risk Panel")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch Aspen Plus, open the attached multi_HXs.bkp example file. Reset and run the case.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.Open(sDataout+"\"+sCaseName,0)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.tbHome.Click()
			[ ] APlus.grpRun.btnRun.Click()
			[ ] sleep(3)
			[ ] glWaitForMouseIdle(150)
			[+] if(wSimulationWarnings.Exists(230))
				[ ] wSimulationWarnings.SetActive()
				[ ] wSimulationWarnings.btnCancel.Click()
				[ ] sleep(5)
		[-] Print("Step 2: Click on the drop-down button of EDR dashboard and select Show risk status and there are circles highlighted for the exchangers in the flowsheet.")
			[ ] APlus.SetActive()
			[ ] APlus.btnActivateEDR.Click(1,10,10)
			[ ] sleep(1)
			[ ] int n = 0
			[-] while(APlus.chkShowRiskStatus.exists() == false)
				[ ] APlus.btnActivateEDR.Click(1,10,10)
				[ ] sleep(2)
				[ ] n++
				[-] if (n > 3)
					[ ] break
			[ ] APlus.chkShowRiskStatus.Check()
			[ ] sleep(2)
			[ ] APlus.SetTab("Main Flowsheet")
			[ ] sleep(1)
			[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\Circles.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. {chr(10)}"
    +"All the exchangers will be encircled in colors according their risk status. {chr(10)}"
    +"Simple models will be encircled in grey; models of OK risk status will be circled in green, warning risk in yellow and serious risk in red. {chr(10)}"
    +"Make sure the numbers of each risk status are displayed right on the Operational Risk panel.")
		[+] Print("Step 3: Move the mouse hover B1, the following flyover will be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.FindAndSelectObject1("default","B1")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHeatX.Exists())
					[ ] Log.Pass("Flyover displays.")
					[+] if(wflyover.dlgHeatX.txtHotSideDeltaT.sCaption=="5")
						[ ] Log.Pass("Value of 'Hot Side Delta T' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Hot Side Delta T' is wrong. Expect: 5. Actual: {wflyover.dlgHeatX.txtHotSideDeltaT.sCaption}")
					[+] if(wflyover.dlgHeatX.txtColdSideDeltaT.sCaption=="5.2638761")
						[ ] Log.Pass("Value of 'Cold Side Delta T' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Cold Side Delta T' is wrong. Expect: 5.2638761. Actual: {wflyover.dlgHeatX.txtColdSideDeltaT.sCaption}")
					[+] if(wflyover.dlgHeatX.txtDuty.sCaption=="600111.088")
						[ ] Log.Pass("Value of 'Duty' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Duty' is wrong. Expect: 600111.088. Actual: {wflyover.dlgHeatX.txtDuty.sCaption}")
					[+] if(wflyover.dlgHeatX.txtArea.sCaption=="1031.37583")
						[ ] Log.Pass("Value of 'Area' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Area' is wrong. Expect: 1031.37583. Actual: {wflyover.dlgHeatX.txtArea.sCaption}")
				[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[+] Print("Step 4: Move the mouse hover B2, the following flyover will be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.FindAndSelectObject1("default","B2")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHeatX.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] //if(wflyover.dlgHeatX.txtHotSideDeltaT.sCaption=="4.7667857")
					[+] if(Abs(Val(wflyover.dlgHeatX.txtHotSideDeltaT.sCaption)-4.7667857)/4.7667857<0.01)
						[ ] Log.Pass("Value of 'Hot Side Delta T' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Hot Side Delta T' is wrong. Expect: 4.7667857. Actual: {wflyover.dlgHeatX.txtHotSideDeltaT.sCaption}")
					[ ] //if(wflyover.dlgHeatX.txtColdSideDeltaT.sCaption=="5.0325026")
					[+] if(Abs(Val(wflyover.dlgHeatX.txtColdSideDeltaT.sCaption)-5.0325026)/5.0325026<0.01)
						[ ] Log.Pass("Value of 'Cold Side Delta T' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Cold Side Delta T' is wrong. Expect: 5.0325026. Actual: {wflyover.dlgHeatX.txtColdSideDeltaT.sCaption}")
					[ ] // if(wflyover.dlgHeatX.txtDuty.sCaption=="573583.721")
					[+] if(Abs(Val(wflyover.dlgHeatX.txtDuty.sCaption)-573583.721)/573583.721<0.01)
						[ ] Log.Pass("Value of 'Duty' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Duty' is wrong. Expect: 573583.721. Actual: {wflyover.dlgHeatX.txtDuty.sCaption}")
					[ ] //if(wflyover.dlgHeatX.txtArea.sCaption=="437.801104")
					[+] if(Abs(Val(wflyover.dlgHeatX.txtArea.sCaption)-437.801104)/437.801104<0.01)
						[ ] Log.Pass("Value of 'Area' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Area' is wrong. Expect: 437.801104. Actual: {wflyover.dlgHeatX.txtArea.sCaption}")
				[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[-] Print("Step 5: Move the mouse hover HTFS-ST, the following flyover should be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.FindAndSelectObject1("default","HTFS-ST")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2-20,i)
				[-] if(wflyover.dlgShellandTube.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\SortingLogic1.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Heat Transfer; 2)Other; 3)Vibration; 4)Flow; 5)Erosion rhoV2; 6)Pressure Drop")
					[ ] //Step 6
					[ ] rfly=wflyover.dlgShellandTube.GetRect()
					[-] for j= rfly.xSize/2 to rfly.xPos+rfly.xSize step 5
						[ ] wflyover.dlgShellandTube.Click(1,j,10)
						[+] if(wOperationWarnings.Exists())
							[ ] Log.Pass("The operation warning box for HTFS-ST pops up.")
							[ ] wOperationWarnings.SetActive()
							[-] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
								[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
							[+] else
								[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
								[ ] ListPrint(lsPopHeaders)
								[ ] Log.Fail("Actual: ")
								[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
							[ ] wOperationWarnings.Close()
							[ ] break
					[+] if(j>rfly.xPos+rfly.xSize)
						[ ] Log.Fail("The operation warning box for HTFS-ST does not  pop up as expected.")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 6: Click the highlighted traffic button, the operation warning box for HTFS-ST should pop up.")
		[-] Print("Step 7: Move the mouse hover HTFS-AC, the following flyover should be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.FindAndSelectObject1("default","HTFS-AC")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2-20,i)
				[-] if(wflyover.dlgAirCooled.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\SortingLogic2.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Heat Transfer; 2)Other; 3)Vibration; 4)Flow; 5)Erosion rhoV2; 6)Pressure Drop")
					[ ] //Step 8
					[ ] rfly=wflyover.dlgAirCooled.GetRect()
					[-] for j= rfly.xSize/2 to rfly.xPos+rfly.xSize step 5
							[ ] wflyover.dlgAirCooled.Click(1,j,10)
							[-] if(wOperationWarnings.Exists())
								[ ] Log.Pass("The operation warning box for HTFS-AC pops up.")
								[ ] wOperationWarnings.SetActive()
								[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
									[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
								[+] else
									[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
									[ ] ListPrint(lsPopHeaders)
									[ ] Log.Fail("Actual: ")
									[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
								[ ] wOperationWarnings.Close()
								[ ] break
					[+] if(j>rfly.xPos+rfly.xSize)
						[ ] Log.Fail("The operation warning box for HTFS-AC does not pop up as expected.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 8: Click the highlighted traffic button, the operation warning box for HTFS-AC should pop up.")
		[+] Print("Step 9: Move the mouse hover HTFS-PT, the following flyover should be displayed.")
			[ ] APlus.SetActive()
			[ ] // APlus.FindAndSelectObject1("default","HTFS-PL")
			[ ] APlus.FindObject("HTFS-PL")
			[ ] 
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover.dlgPlate.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\SortingLogic3.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Heat Transfer; 2)Other; 3)Vibration; 4)Flow; 5)Erosion rhoV2; 6)Pressure Drop")
					[ ] //Step 10
					[ ] rfly=wflyover.dlgPlate.GetRect()
					[+] for j= rfly.xSize/2 to rfly.xPos+rfly.xSize step 5
							[ ] wflyover.dlgPlate.Click(1,j,10)
							[+] if(wOperationWarnings.Exists())
								[ ] Log.Pass("The operation warning box for HTFS-PT pops up.")
								[ ] wOperationWarnings.SetActive()
								[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
									[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
								[+] else
									[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
									[ ] ListPrint(lsPopHeaders)
									[ ] Log.Fail("Actual: ")
									[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
								[ ] wOperationWarnings.Close()
								[ ] break
					[+] if(j>rfly.xPos+rfly.xSize)
						[ ] Log.Fail("The operation warning box for HTFS-PT does not pop up as expected.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 10: Click the highlighted traffic button, the operation warning box for HTFS-AC should pop up.")
		[ ] 
	[ ] 
[ ] 
[+] testcase CQ00510192() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510192"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\Multi HXs"
		[ ] sCaseName="multi_HXs.bkp"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer inum,i
		[ ] string sBitmapDir
		[ ] RECT r
		[ ] List of FILEINFO lFiles
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] lFiles=SYS_GetDirContents(sDatain)
		[+] for i=1 to ListCount(lFiles)
			[ ] File.Copy(sDatain+"\"+lFiles[i].sName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.3.2. EDR activated summary table workflow")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch Aspen Plus; open the attached multi HXs.bkp example file. Reset and run the case.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.Open(sDataout+"\"+sCaseName,0)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.tbHome.Click()
			[ ] APlus.grpRun.btnRun.Click()
			[ ] sleep(3)
			[ ] glWaitForMouseIdle(120)
			[-] if(wSimulationWarnings.Exists(230))
				[ ] wSimulationWarnings.SetActive()
				[ ] wSimulationWarnings.btnCancel.Click()
				[ ] sleep(5)
		[-] Print("Step 2: Click the drop-down button on EDR dashboard and select Show model Status and there are circles highlighted for the exchangers in the flowsheet – blue for rigorous models and grey for simple models.")
			[ ] APlus.SetActive()
			[ ] APlus.btnActivateEDR.DoubleClick(1,10,10)
			[ ] sleep(1)
			[ ] int n = 0
			[-]  while(APlus.chkShowModelStatus.exists() == false)
				[ ]  APlus.btnActivateEDR.Click(1,10,10)
				[ ]  sleep(2)
				[ ]  n++
				[+] if (n > 3)
					[ ]  break
			[ ] sleep(1)
			[ ] APlus.chkShowModelStatus.Check()
			[ ] sleep(2)
			[ ] APlus.SetTab("Main Flowsheet")
			[ ] sleep(1)
			[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\Circles.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. {chr(10)}"
    +"For rigorous ones, it's blue, for simple ones, it's grey. {chr(10)}"
    +"Make sure the number of the simple models and rigorous models are displayed right on the Model Status panel.")
		[-] Print("Step 3: Move the mouse hover B1, the following flyover will be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.FindAndSelectObject1("default","B1")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHeatX.Exists())
					[ ] Log.Pass("Flyover displays.")
					[+] if(wflyover.dlgHeatX.txtHotSideDeltaT.sCaption=="5")
						[ ] Log.Pass("Value of 'Hot Side Delta T' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Hot Side Delta T' is wrong. Expect: 5. Actual: {wflyover.dlgHeatX.txtHotSideDeltaT.sCaption}")
					[+] if(wflyover.dlgHeatX.txtColdSideDeltaT.sCaption=="5.2638761")
						[ ] Log.Pass("Value of 'Cold Side Delta T' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Cold Side Delta T' is wrong. Expect: 5.2638761. Actual: {wflyover.dlgHeatX.txtColdSideDeltaT.sCaption}")
					[+] if(wflyover.dlgHeatX.txtDuty.sCaption=="600111.088")
						[ ] Log.Pass("Value of 'Duty' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Duty' is wrong. Expect: 600111.088. Actual: {wflyover.dlgHeatX.txtDuty.sCaption}")
					[+] if(wflyover.dlgHeatX.txtArea.sCaption=="1031.37583")
						[ ] Log.Pass("Value of 'Area' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Area' is wrong. Expect: 1031.37583. Actual: {wflyover.dlgHeatX.txtArea.sCaption}")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[-] Print("Step 4: Move the mouse hover B2, the following flyover will be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.FindAndSelectObject1("default","B2")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHeatX.Exists())
					[ ] Log.Pass("Flyover displays.")
					[+] if(wflyover.dlgHeatX.txtHotSideDeltaT.sCaption=="4.7667857")
						[ ] Log.Pass("Value of 'Hot Side Delta T' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Hot Side Delta T' is wrong. Expect: 4.7667857. Actual: {wflyover.dlgHeatX.txtHotSideDeltaT.sCaption}")
					[+] if(wflyover.dlgHeatX.txtColdSideDeltaT.sCaption=="5.0325026")
						[ ] Log.Pass("Value of 'Cold Side Delta T' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Cold Side Delta T' is wrong. Expect: 5.0325026. Actual: {wflyover.dlgHeatX.txtColdSideDeltaT.sCaption}")
					[+] if(wflyover.dlgHeatX.txtDuty.sCaption=="573583.721")
						[ ] Log.Pass("Value of 'Duty' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Duty' is wrong. Expect: 573583.721. Actual: {wflyover.dlgHeatX.txtDuty.sCaption}")
					[+] if(wflyover.dlgHeatX.txtArea.sCaption=="437.801104")
						[ ] Log.Pass("Value of 'Area' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Area' is wrong. Expect: 437.801104. Actual: {wflyover.dlgHeatX.txtArea.sCaption}")
				[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[-] Print("Step 5: Move the mouse hover HTFS-ST, the following flyover will be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.FindAndSelectObject1("default","HTFS-ST")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[-] if(wflyover.dlgShellandTube.Exists())
					[ ] Log.Pass("Flyover displays.")
					[-] if(wflyover.dlgShellandTube.txtSurfaceArea.sCaption=="923.683")
						[ ] Log.Pass("Value of 'Surface Area' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Surface Are' is wrong. Expect: 923.683. Actual: {wflyover.dlgShellandTube.txtSurfaceArea.sCaption}")
					[-] if(wflyover.dlgShellandTube.txtTotalHeadLoad.sCaption=="574317")
						[ ] Log.Pass("Value of 'Total Head Load' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Total Head Load' is wrong. Expect: 574317. Actual: {wflyover.dlgShellandTube.txtTotalHeadLoad.sCaption}")
					[+] if(wflyover.dlgShellandTube.txtTEMAType.sCaption=="AEL")
						[ ] Log.Pass("Value of 'TEMA Type' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'TEMA Type' is wrong. Expect: AEL. Actual: {wflyover.dlgShellandTube.txtTEMAType.sCaption}")
					[+] if(wflyover.dlgShellandTube.txtShellsinSeries.sCaption=="2")
						[ ] Log.Pass("Value of 'Shells in Series' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Shells in Series' is wrong. Expect: 2. Actual: {wflyover.dlgShellandTube.txtShellsinSeries.sCaption}")
					[+] if(wflyover.dlgShellandTube.txtShellsinParallel.sCaption=="1")
						[ ] Log.Pass("Value of 'Shells in Series' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Shells in Series' is wrong. Expect: 1. Actual: {wflyover.dlgShellandTube.txtShellsinParallel.sCaption}")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[-] Print("Step 6: Move the mouse hover HTFS-AC, the following flyover will be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.FindAndSelectObject1("default","HTFS-AC")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgAirCooled.Exists())
					[ ] Log.Pass("Flyover displays.")
					[+] if(wflyover.dlgAirCooled.txtSurfaceArea.sCaption=="1836.35")
						[ ] Log.Pass("Value of 'Surface Area' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Surface Are' is wrong. Expect: 1836.35. Actual: {wflyover.dlgAirCooled.txtSurfaceArea.sCaption}")
					[+] if(wflyover.dlgAirCooled.txtTotalHeadLoad.sCaption=="267947")
						[ ] Log.Pass("Value of 'Total Head Load' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Total Head Load' is wrong. Expect: 267947. Actual: {wflyover.dlgAirCooled.txtTotalHeadLoad.sCaption}")
					[+] if(wflyover.dlgAirCooled.txtFanConfiguration.sCaption=="Forced")
						[ ] Log.Pass("Value of 'Fan Configuration' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Fan Configuration' is wrong. Expect: Forced. Actual: {wflyover.dlgAirCooled.txtFanConfiguration.sCaption}")
					[+] if(wflyover.dlgAirCooled.txtBaysperUnit.sCaption=="1")
						[ ] Log.Pass("Value of 'Bays per Unit' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Bays per Unit' is wrong. Expect: 1. Actual: {wflyover.dlgAirCooled.txtBaysperUnit.sCaption}")
					[+] if(wflyover.dlgAirCooled.txtBundlesperBay.sCaption=="1")
						[ ] Log.Pass("Value of 'Bundles per Bay' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Bundles per Bay' is wrong. Expect: 1. Actual: {wflyover.dlgAirCooled.txtBundlesperBay.sCaption}")
					[+] if(wflyover.dlgAirCooled.txtFansperBay.sCaption=="2")
						[ ] Log.Pass("Value of 'Fans per Bay' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Fans per Bay' is wrong. Expect: 2. Actual: {wflyover.dlgAirCooled.txtFansperBay.sCaption}")
					[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\SettingPlan.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually to verify Setting Plan.")
				[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[-] Print("Step 7: Move the mouse hover HTFS-PT, the following flyover will be displayed.")
			[ ] APlus.SetActive()
			[ ] // APlus.FindAndSelectObject1("default","HTFS-PL")
			[ ] APlus.FindObject("HTFS-PL")
			[ ] 
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgPlate.Exists())
					[ ] Log.Pass("Flyover displays.")
					[+] if(wflyover.dlgPlate.txtSurfaceArea.sCaption=="1049.87")
						[ ] Log.Pass("Value of 'Surface Area' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Surface Area' is wrong. Expect: 1049.87. Actual: {wflyover.dlgPlate.txtSurfaceArea.sCaption}")
					[+] if(wflyover.dlgPlate.txtTotalHeatLoad.sCaption=="600112")
						[ ] Log.Pass("Value of 'Total Heat Load' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Total Heat Load' is wrong. Expect: 600112. Actual: {wflyover.dlgPlate.txtTotalHeatLoad.sCaption}")
					[+] if(wflyover.dlgPlate.txtExchangersinParallel.sCaption=="1")
						[ ] Log.Pass("Value of 'Exchangers in Parallel' is correct.")
					[+] else
						[ ] Log.Fail("Value of 'Exchangers in Parallel' is wrong. Expect: 1. Actual: {wflyover.dlgPlate.txtExchangersinParallel.sCaption}")
				[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] 
	[ ] 
[+] testcase CQ00510199() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 27, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510199"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\SimpleToRigorous"
		[ ] sCaseName="Shortcut.bkp"
		[ ] 
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] string sTemplateFile=sDatain+"\EDT\CS_Air_Cooled_SI.EDT"
		[ ] integer inum,i, irow,j,iCount,k
		[ ] string sBitmapDir,sModel,sPath
		[ ] RECT r,rfly
		[+] list of string lsPopHeaders={...}
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] "Vibration"
			[ ] "Erosion: RhoV2"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] "Other"
		[ ] list of window lwAllRows
		[ ] list of string lsValues, lsResults
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.6.1 Shell&Tube smoke test for Activated EDR in Aspen Plus")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus, open the attached Shortcut.bkp and run.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.Open(sDataout+"\"+sCaseName,0)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
			[ ] sleep(30)
			[+] if(APlus.btnUnpin.Exists())
				[ ] APlus.SetActive()
				[ ] APlus.btnUnpin.Click()
				[ ] sleep(2)
		[+] Print("Step 2: Click the drop-down button in EDR dashboard and select Show model status.")
			[ ] APlus.SetActive()
			[ ] APlus.btnActivateEDR.Click(1,10,10)
			[ ] int n = 0
			[-]  while(APlus.chkShowModelStatus.exists() == false)
				[ ]  APlus.btnActivateEDR.Click(1,10,10)
				[ ]  sleep(2)
				[ ]  n++
				[+] if (n > 3)
					[ ]  break
			[ ] sleep(1)
			[ ] APlus.chkShowModelStatus.Check()
			[ ] sleep(2)
		[+] Print("Step 3: Go to flowsheet, move the mouse over block B1, which is highlighted in grey circle. The following window will be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet*")
			[ ] sleep(3)
			[ ] APlus.FindObject("B1")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[-] if(wflyover.dlgHeatX.Exists(3))
					[ ] Log.Pass("Flyover displays.")
					[ ] //Step 4 - Get the values need check
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtHotSideDeltaT.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[6]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtColdSideDeltaT.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[9]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtDuty.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[12]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtArea.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[15]").sCaption)
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] //Step 4 - check
				[ ] lsResults=APlus.GetHeatResults("B1")
				[+] if(Abs(Val(lsResults[1])-Val(lsValues[1]))<0.001 && lsValues[2]==lsResults[2])
					[ ] Log.Pass("Value of 'Hot Side Delta T' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Hot Side Delta T' is wrong. Expect: {lsValues[1]} {lsValues[2]}. Actual: {lsResults[1]} {lsResults[2]}.")
					[ ] 
				[+] if(Abs(Val(lsResults[3])-Val(lsValues[3]))<0.1 && lsValues[4]==lsResults[4])
					[ ] Log.Pass("Value of 'Cold Side Delta T' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Cold Side Delta T' is wrong. Expect: {lsValues[3]} {lsValues[4]}. Actual: {lsResults[3]} {lsResults[4]}.")
					[ ] 
				[+] if(Abs(Val(lsResults[5])-Val(lsValues[5]))<0.001 && lsValues[6]==lsResults[6])
					[ ] Log.Pass("Value of 'Duty' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Duty' is wrong. Expect: {lsValues[5]} {lsValues[6]}. Actual: {lsResults[5]} {lsResults[6]}.")
				[+] if(Abs(Val(lsResults[7])-Val(lsValues[7]))<0.001 && lsValues[8]==lsResults[8])
					[ ] Log.Pass("Value of 'Area' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Area' is wrong. Expect: {lsValues[7]} {lsValues[8]}. Actual: {lsResults[7]} {lsResults[8]}.")
		[ ] Print("Step 4: Make sure the variables values are same as the Aspen Plus results.")
		[+] Print("Step 5: Click Size Rigorous button on the flyover, select Shell&Tube as Model Type and Size Interactively.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet*")
			[ ] sleep(3)
			[ ] APlus.FindObject("B1")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[ ] APlus.CaptureBitmap("C:\Users\Administrator\Documents\test.bmp")
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+600  
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHeatX.Exists(2))
					[ ] Log.Pass("Flyover displays.")
					[ ] wflyover.btnSizeRigorous.Click()
					[ ] sleep(2)
					[+] if(wSizingToCreateRigorousExchanger.Exists(15))
						[ ] wSizingToCreateRigorousExchanger.SetActive()
						[ ] wSizingToCreateRigorousExchanger.rdbShellTube.Check()
						[ ] sleep(1)
						[ ] wSizingToCreateRigorousExchanger.rdbSizeInteractively.Check()
						[ ] sleep(1)
						[ ] wSizingToCreateRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(30)) //chen
							[ ] //Step 6
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()  
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[ ] sleep(5)
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("Sizing To Create Rigorous Exchanger window does not pop up.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[+] Print("Step 6: Click Size button and Accept Design in EDR Sizing Console.")
			[ ] //Verification
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/B1")
			[ ] sleep(2)
			[+] if(APlus.rdbShellTube.IsChecked)
				[ ] Log.Pass("The simple model has been converted to the rigorous model.")
			[+] else
				[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] if(APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" && APlus.ctrlEDRDashboard.ctrlOK.TextCapture()=="1" && APlus.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("EDR dashboard is updateded.")
			[+] else
				[ ] Log.Fail("EDR dashboard is not updateded.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
					[ ] Log.Pass("Exchanger Summary table is updateded.")
				[+] else
					[ ] Log.Fail("Exchanger Summary table is not updateded.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ]  APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet")
			[ ] sleep(2)
			[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\Step6.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually to verify the flyover has been updateded.")
		[-] Print("Step 7: Move the mouse hover over the converted Shell&Tube rigorous model. The model now is highlighted in blue circle. The following window will be displayed.")
			[-] for(i=LIstCount(lsValues);i>=1;i--)
				[ ] ListDelete(lsValues,i)
			[+] for(i=ListCount(lsResults);i>=1;i--)
				[ ] ListDelete(lsResults,i)
			[ ] sleep(2)
			[ ] APlus.CaptureBitmap("C:\Users\Administrator\Documents\test.bmp",APlus.areaForMainFlowsheet.GetRect())
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-100 to r.yPos+r.ySize/2+100
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[ ] sleep(2)
				[-] if(wflyover.dlgShellandTube.Exists(2))
					[ ] Log.Pass("Flyover displays.")
					[ ] //Step 8 - Get the values need check
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.txtSurfaceArea.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.Find("//WPFTextBlock[6]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.txtTotalHeadLoad.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.Find("//WPFTextBlock[9]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.txtTEMAType.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.txtShellsinSeries.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.txtShellsinParallel.sCaption)
					[ ] print("*******lsValues********")
					[ ] ListPrint(lsValues)
					[ ] print("******lsValues*********")
					[ ] break
				[-] else
					[ ] Log.warning("Flyover not displays.")
					[ ] 
			[-] if(i>r.yPos+r.ySize/2+600)
				[ ] Log.Fail("Flyover does not display.")
			[-] else
				[ ] //Step 8 - check
				[ ] lsResults=APlus.GetSTResults("B1")
				[ ] print("****lsResults****")
				[ ] ListPrint(lsResults)
				[ ] print("****lsResults****")
				[ ] print("****lsValues****")
				[ ] ListPrint(lsValues)
				[ ] print("****lsValues****")
				[+] if(Abs(Val(lsResults[1])-Val(lsValues[1]))<0.001 && lsValues[2]==lsResults[2])
					[ ] Log.Pass("Value of 'Surface Area' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Surface Area' is wrong. Expect: {lsValues[1]} {lsValues[2]}. Actual: {lsResults[1]} {lsResults[2]}.")
				[+] if(Abs(Val(lsResults[3])-Val(lsValues[3]))<0.001 && lsValues[4]==lsResults[4])
					[ ] Log.Pass("Value of 'Total Heat Load' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Total Heat Load' is wrong. Expect: {lsValues[3]} {lsValues[4]}. Actual: {lsResults[3]} {lsResults[4]}.")
				[+] if(lsResults[5]==lsValues[5])
					[ ] Log.Pass("Value of 'TEMA Type' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'TEMA Type' is wrong. Expect: {lsValues[5]}. Actual: {lsResults[5]}.")
				[+] if(lsResults[6]==lsValues[6])
					[ ] Log.Pass("Value of 'Shells in Series' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Shells in Series' is wrong. Expect: {lsValues[6]}. Actual: {lsResults[6]}.")
				[+] if(lsResults[7]==lsValues[7])
					[ ] Log.Pass("Value of 'Shells in Parallel' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Shells in Parallel' is wrong. Expect: {lsValues[7]}. Actual: {lsResults[7]}.")
		[ ] Print("Step 8: Make sure the variables values are same as the Aspen Plus results.")
		[-] Print("Step 9: Select Show risk status from the drop-down button of EDR dashboard.")
			[ ] APlus.SetActive()
			[ ] APlus.btnActivateEDR.Click(1,10,10)
			[ ] sleep(1)
			[ ] n = 0
			[-]  while(APlus.chkShowModelStatus.exists() == false)
				[ ]  APlus.btnActivateEDR.Click(1,10,10)
				[ ]  sleep(2)
				[ ]  n++
				[+] if (n > 3)
					[ ]  break
			[ ] sleep(1)
			[ ] APlus.chkShowRiskStatus.Check()
			[ ] sleep(2)
		[+] Print("Step 10. Click the highlighted traffic button, the operation warning box for B1 should pop up.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet*")
			[ ] sleep(1)
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgShellandTube.Exists(3))
					[ ] Log.Pass("Flyover displays.")
					[ ] //Step 9 Verification
					[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\SortingLogic1.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Heat Transfer; 2)Other; 3)Vibration; 4)Flow; 5)Erosion rhoV2; 6)Pressure Drop")
					[ ] rfly=wflyover.dlgShellandTube.GetRect()
					[+] for j= rfly.xSize/2 to rfly.xPos+rfly.xSize step 5
						[ ] wflyover.dlgShellandTube.Click(1,j,10)
						[+] if(wOperationWarnings.Exists())
							[ ] Log.Pass("The operation warning box for B1 pops up.")
							[ ] wOperationWarnings.SetActive()
							[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
								[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
							[+] else
								[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
								[ ] ListPrint(lsPopHeaders)
								[ ] Log.Fail("Actual: ")
								[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
							[ ] wOperationWarnings.Close()
							[ ] break
					[+] if(j>rfly.xPos+rfly.xSize)
						[ ] Log.Fail("The operation warning box for HTFS-PT does not pop up as expected.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[+] Print("Step 11: Click the Revert to Simple button on the Exchanger Summary Table.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
				[ ] //Step 12
				[+] if(wRevertShortcutExchangerModel.Exists(20))
					[ ] wRevertShortcutExchangerModel.SetActive()
					[ ] //Step 13
					[ ] wRevertShortcutExchangerModel.rdbShortcutWithEDR.Select()
					[ ] sleep(1)
					[ ] wRevertShortcutExchangerModel.btnRevert.Click()
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 12: The following dialog appears.")
		[ ] Print("Step 13: Select ‘Shortcut with EDR Calculated UA and Pressure Drops’ and click Revert button.")
		[+] Print("Step 14: The model is converted successfully.")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/B1")
			[ ] sleep(2)
			[+] if(APlus.rdbShortcut.IsChecked)
				[ ] Log.Pass("The exchanger model changes to Shortcut.")
				[ ] APlus.SetTab("Specifications")
				[+] if(APlus.txtThird.TextCapture()!=null || APlus.txtThird.TextCapture()!="")
					[ ] Log.Pass("Constant UA value displays.")
				[+] else
					[ ] Log.Fail("Constant UA value does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("Pressure Drop")
				[ ] sleep(1)
				[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="")
					[ ] Log.Pass("Outlet Pressure value displays.")
				[+] else
					[ ] Log.Fail("Outlet Pressure value does not display.")
			[+] else
				[ ] Log.Fail("The exchanger model does not change to Shortcut.")
			[+] if(APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" && APlus.ctrlEDRDashboard.ctrlOK.TextCapture()=="0" && APlus.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("EDR dashboard is updateded.")
			[+] else
				[ ] Log.Fail("EDR dashboard is not updateded.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
					[ ] Log.Pass("Exchanger Summary table is updateded.")
				[+] else
					[ ] Log.Fail("Exchanger Summary table is not updateded.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510201() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 27, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510201"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\SimpleToAirCooled"
		[ ] sCaseName="Detailed AC.bkp"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] string sTemplateFile=sDatain+"\EDT\CS_Air_Cooled_SI.EDT"
		[ ] integer inum,i, irow,j,iCount,k
		[ ] string sBitmapDir,sModel,sPath
		[ ] RECT r,rfly
		[ ] list of window lwAllRows
		[ ] list of string lsValues, lsResults
		[+] list of string lsPopHeaders={...}
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] "Vibration"
			[ ] "Erosion: RhoV2"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] "Other"
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.6.2 AirCooled smoke test for Activated EDR in Aspen Plus")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch Aspen Plus, open the attached Detailed AC.bkp. Reset and run the file.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.Open(sDataout+"\"+sCaseName,0)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
			[+] if(APlus.btnUnpin.Exists())
				[ ] APlus.SetActive()
				[ ] APlus.btnUnpin.Click()
				[ ] sleep(2)
		[-] Print("Step 2: Click the drop-down button in EDR dashboard and select Show model status.")
			[ ] APlus.SetActive()
			[ ] // APlus.btnActivateEDR.DoubleClick(1,10,10)
			[ ] //APlus.btnActivateEDR.Click()
			[ ] APlus.ClickExchanger()
			[ ] sleep(1)
			[ ] APlus.chkShowModelStatus.Check()
			[ ] sleep(2)
		[+] Print("Step 3: Go to flowsheet, move the mouse over block HTFS-AC, which is highlighted in grey circle. The following window will be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet*")
			[ ] sleep(3)
			[ ] //APlus.FindObject("HTFS-AC")
			[ ] APlus.FindAndSelectObject1("default","HTFS-AC")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHeatX.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] //Step 4 - Get the values need check
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtHotSideDeltaT.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[6]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtColdSideDeltaT.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[9]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtDuty.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[12]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtArea.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[15]").sCaption)
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] //Step 4 - check
				[ ] lsResults=APlus.GetHeatResults("HTFS-AC", true)
				[+] if(Abs(Val(lsResults[1])-Val(lsValues[1]))/Val(lsValues[1])<0.001 && lsValues[2]==lsResults[2])
					[ ] Log.Pass("Value of 'Hot Side Delta T' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Hot Side Delta T' is wrong. Expect: {lsValues[1]} {lsValues[2]}. Actual: {lsResults[1]} {lsResults[2]}.")
					[ ] 
				[+] if(Abs(Val(lsResults[3])-Val(lsValues[3]))/Val(lsValues[3])<0.1 && lsValues[4]==lsResults[4])
					[ ] Log.Pass("Value of 'Cold Side Delta T' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Cold Side Delta T' is wrong. Expect: {lsValues[3]} {lsValues[4]}. Actual: {lsResults[3]} {lsResults[4]}.")
					[ ] 
				[+] if(Abs(Val(lsResults[5])-Val(lsValues[5]))/Val(lsValues[5])<0.001 && lsValues[6]==lsResults[6])
					[ ] Log.Pass("Value of 'Duty' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Duty' is wrong. Expect: {lsValues[5]} {lsValues[6]}. Actual: {lsResults[5]} {lsResults[6]}.")
				[+] if(Abs(Val(lsResults[7])-Val(lsValues[7]))/Val(lsValues[7])<0.001 && lsValues[8]==lsResults[8])
					[ ] Log.Pass("Value of 'Area' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Area' is wrong. Expect: {lsValues[7]} {lsValues[8]}. Actual: {lsResults[7]} {lsResults[8]}.")
		[ ] Print("Step 4: Make sure the variables values are same as the Aspen Plus results.")
		[+] Print("Step 5: Click Size Rigorous button on the flyover, select Air Cooled as Model Type and Size Interactively, then click Convert button.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet*")
			[ ] sleep(3)
			[ ] APlus.FindAndSelectObject1("default","HTFS-AC")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHeatX.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] wflyover.btnSizeRigorous.Click()
					[ ] sleep(2)
					[+] if(wSizingToCreateRigorousExchanger.Exists(15))
						[ ] wSizingToCreateRigorousExchanger.SetActive()
						[ ] wSizingToCreateRigorousExchanger.rdbAirCooled.Check()
						[ ] sleep(1)
						[ ] wSizingToCreateRigorousExchanger.rdbSizeInteractively.Check()
						[ ] sleep(1)
						[ ] wSizingToCreateRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] //Step 6
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()  
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[+] if(wWarning.Exists(100))
								[ ] //Step 7
								[ ] wWarning.SetActive()
								[ ] wWarning.btnYes.Click()
							[ ] sleep(5)
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("Sizing To Create Rigorous Exchanger window does not pop up.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 6: Click Size button and Accept Design in EDR Sizing Console and the following dialog appears.")
		[+] Print("Step 7: Click OK to the dialog.")
			[ ] //Verification
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/HTFS-AC")
			[ ] sleep(2)
			[+] if(APlus.rdbAirCooled.IsChecked)
				[ ] Log.Pass("The simple model has been converted to the rigorous model.")
			[+] else
				[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] if(APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" && APlus.ctrlEDRDashboard.ctrlOK.TextCapture()=="0" && APlus.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1")
				[ ] Log.Pass("EDR dashboard is updateded.")
			[+] else
				[ ] Log.Fail("EDR dashboard is not updateded.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
					[ ] Log.Pass("Exchanger Summary table is updateded.")
				[+] else
					[ ] Log.Fail("Exchanger Summary table is not updateded.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ]  APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet")
			[ ] sleep(2)
			[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\Step7.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually to verify the flyover has been updateded.")
		[-] Print("Step 8: Move the mouse hover over the converted Shell&Tube rigorous model. The model now is highlighted in blue circle. The following window will be displayed.")
			[+] for(i=LIstCount(lsValues);i>=1;i--)
				[ ] ListDelete(lsValues,i)
			[+] for(i=ListCount(lsResults);i>=1;i--)
				[ ] ListDelete(lsResults,i)
			[ ] APlus.SetActive()
			[ ] // APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
			[ ] APlus.SetActive()
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[-] if(wflyover.dlgAirCooled.Exists(2))
					[ ] Log.Pass("Flyover displays.")
					[ ] //Step 8 - Get the values need check
					[ ] ListAppend(lsValues,wflyover.dlgAirCooled.txtSurfaceArea1.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgAirCooled.Find("//WPFTextBlock[6]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgAirCooled.txtTotalHeadLoad.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgAirCooled.Find("//WPFTextBlock[9]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgAirCooled.txtFanConfiguration.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgAirCooled.txtBaysperUnit.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgAirCooled.txtBundlesperBay.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgAirCooled.txtFansperBay.sCaption)
					[ ] print("--------------")
					[ ] listprint(lsValues)
					[ ] print("--------------")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[-] else
				[ ] //Step 9 - check
				[ ] lsResults=APlus.GetAirCooledResults("HTFS-AC")
				[+] if(Abs(Val(lsResults[1])-Val(lsValues[1]))/Val(lsValues[1])<0.001 && lsValues[2]==lsResults[2])
					[ ] Log.Pass("Value of 'Surface Area' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Surface Area' is wrong. Expect: {lsValues[1]} {lsValues[2]}. Actual: {lsResults[1]} {lsResults[2]}.")
				[+] if(Abs(Val(lsResults[3])-Val(lsValues[3]))/Val(lsValues[3])<0.001 && lsValues[4]==lsResults[4])
					[ ] Log.Pass("Value of 'Total Heat Load' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Total Heat Load' is wrong. Expect: {lsValues[3]} {lsValues[4]}. Actual: {lsResults[3]} {lsResults[4]}.")
				[+] if(lsResults[5]==lsValues[5])
					[ ] Log.Pass("Value of 'Fan Configuration' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Fan Configuration' is wrong. Expect: {lsValues[5]}. Actual: {lsResults[5]}.")
				[+] if(lsResults[6]==lsValues[6])
					[ ] Log.Pass("Value of 'Bays per Unit' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Bays per Unit' is wrong. Expect: {lsValues[6]}. Actual: {lsResults[6]}.")
				[+] if(lsResults[7]==lsValues[7])
					[ ] Log.Pass("Value of 'Bundles per Bay' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Bundles per Bay' is wrong. Expect: {lsValues[7]}. Actual: {lsResults[7]}.")
				[+] if(lsResults[8]==lsValues[8])
					[ ] Log.Pass("Value of 'Fans per Bay' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Fans per Bay' is wrong. Expect: {lsValues[7]}. Actual: {lsResults[7]}.")
		[ ] Print("Step 9: Make sure the variables values are same as the Aspen Plus results.")
		[-] Print("Step 10: Select Show risk status from the drop-down button of EDR dashboard.")
			[ ] APlus.SetActive()
			[ ] APlus.btnActivateEDR.DoubleClick(1,10,10)
			[ ] sleep(1)
			[ ] APlus.chkShowRiskStatus.Check()
			[ ] sleep(2)
		[+] Print("Step 11: Click the highlighted traffic button, the operation warning box for B1 should pop up.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet*")
			[ ] sleep(1)
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgAirCooled.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\SortingLogic1.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Heat Transfer; 2)Other; 3)Vibration; 4)Flow; 5)Erosion rhoV2; 6)Pressure Drop")
					[ ] //Step 11
					[ ] rfly=wflyover.dlgAirCooled.GetRect()
					[+] for j= rfly.xSize/2 to rfly.xPos+rfly.xSize step 5
						[ ] wflyover.dlgAirCooled.Click(1,j,10)
						[+] if(wOperationWarnings.Exists())
							[ ] Log.Pass("The operation warning box for B1 pops up.")
							[ ] wOperationWarnings.SetActive()
							[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
								[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
							[+] else
								[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
								[ ] ListPrint(lsPopHeaders)
								[ ] Log.Fail("Actual: ")
								[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
							[ ] wOperationWarnings.Close()
							[ ] break
					[+] if(j>rfly.xPos+rfly.xSize)
						[ ] Log.Fail("The operation warning box for HTFS-PT does not pop up as expected.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[+] Print("Step 12: Click the Revert to Simple button on the Exchanger Summary Table.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
				[ ] //Step 13
				[+] if(wRevertShortcutExchangerModel.Exists(20))
					[ ] wRevertShortcutExchangerModel.SetActive()
					[ ] //Step 14
					[ ] wRevertShortcutExchangerModel.rdbShortcutWithEDR.Select()
					[ ] sleep(1)
					[ ] wRevertShortcutExchangerModel.btnRevert.Click()
					[+] if(wDeleteExistingAreaSpec.Exists(20))
						[ ] //Step 15
						[ ] wDeleteExistingAreaSpec.SetActive()
						[ ] wDeleteExistingAreaSpec.btnOK.Click()
					[ ] sleep(3)
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 13: The following dialog appears.")
		[ ] Print("Step 14: Select ‘Shortcut with EDR Calculated UA and Pressure Drops’ and click Revert button.")
		[ ] Print("Step 15: Click OK to the following dialog.")
		[+] Print("Step 16: The model is converted successfully.")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/HTFS-AC")
			[ ] sleep(2)
			[+] if(APlus.rdbShortcut.IsChecked)
				[ ] Log.Pass("The exchanger model changes to Shortcut.")
				[ ] APlus.SetTab("Specifications")
				[+] if(APlus.txtThird.TextCapture()!=null || APlus.txtThird.TextCapture()!="")
					[ ] Log.Pass("Constant UA value displays.")
				[+] else
					[ ] Log.Fail("Constant UA value does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("Pressure Drop")
				[ ] sleep(1)
				[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="")
					[ ] Log.Pass("Outlet Pressure value displays.")
				[+] else
					[ ] Log.Fail("Outlet Pressure value does not display.")
			[+] else
				[ ] Log.Fail("The exchanger model does not change to Shortcut.")
			[+] if(APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" && APlus.ctrlEDRDashboard.ctrlOK.TextCapture()=="0" && APlus.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("EDR dashboard is updateded.")
			[+] else
				[ ] Log.Fail("EDR dashboard is not updateded.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
					[ ] Log.Pass("Exchanger Summary table is updateded.")
				[+] else
					[ ] Log.Fail("Exchanger Summary table is not updateded.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] 
	[ ] 
[+] testcase CQ00510202() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 27, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510202"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\SimpleToRigorous"
		[ ] sCaseName="Detailed.bkp"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] string sTemplateFile=sDatain+"\EDR\HTFS-PL.EDR"
		[ ] integer inum,i, irow,j,iCount,k
		[ ] string sBitmapDir,sModel,sPath
		[ ] RECT r,rfly
		[ ] list of window lwAllRows
		[ ] list of string lsValues, lsResults
		[+] list of string lsPopHeaders={...}
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] "Vibration"
			[ ] "Erosion: RhoV2"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] "Other"
		[+] list of string lsInputData={...}
			[ ] "2.9"
			[ ] "55"
			[ ] "65"
			[ ] "20"
			[ ] "87"
			[ ] "0.02"
			[ ] "0.2"
			[ ] "12"
			[ ] "33"
			[ ] "20"
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.6.3 Plate smoke test for Activated EDR in Aspen Plus")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus, open the attached Detailed.bkp example file. Reset and run the case.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.Open(sDataout+"\"+sCaseName,0)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
			[+] if(APlus.btnUnpin.Exists())
				[ ] APlus.SetActive()
				[ ] APlus.btnUnpin.Click()
				[ ] sleep(2)
		[-] Print("Step 2: Click the drop-down button in EDR dashboard and select Show model status.")
			[ ] APlus.SetActive()
			[ ] sleep(5)
			[ ] //APlus.btnActivateEDR.DoubleClick(1,10,10)
			[ ] APlus.ClickExchanger()
			[ ] APlus.chkShowModelStatus.Check()
			[ ] sleep(2)
		[+] Print("Step 3: Go to flowsheet, move the mouse over block B1, which is highlighted in grey circle. The following window will be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet")
			[ ] APlus.FindObject("B1")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHeatX.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] //Step 4 - Get the values need check
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtHotSideDeltaT.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[6]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtColdSideDeltaT.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[9]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtDuty.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[12]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtArea.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[15]").sCaption)
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] //Step 4 - check
				[ ] lsResults=APlus.GetHeatResults("B1",true)
				[+] if(Abs(Val(lsResults[1])-Val(lsValues[1]))<0.001 && lsValues[2]==lsResults[2])
					[ ] Log.Pass("Value of 'Hot Side Delta T' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Hot Side Delta T' is wrong. Expect: {lsValues[1]} {lsValues[2]}. Actual: {lsResults[1]} {lsResults[2]}.")
					[ ] 
				[+] if(Abs(Val(lsResults[3])-Val(lsValues[3]))<0.1 && lsValues[4]==lsResults[4])
					[ ] Log.Pass("Value of 'Cold Side Delta T' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Cold Side Delta T' is wrong. Expect: {lsValues[3]} {lsValues[4]}. Actual: {lsResults[3]} {lsResults[4]}.")
					[ ] 
				[+] if(Abs(Val(lsResults[5])-Val(lsValues[5]))<0.001 && lsValues[6]==lsResults[6])
					[ ] Log.Pass("Value of 'Duty' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Duty' is wrong. Expect: {lsValues[5]} {lsValues[6]}. Actual: {lsResults[5]} {lsResults[6]}.")
				[+] if(Abs(Val(lsResults[7])-Val(lsValues[7]))<0.1 && lsValues[8]==lsResults[8])
					[ ] Log.Pass("Value of 'Area' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Area' is wrong. Expect: {lsValues[7]} {lsValues[8]}. Actual: {lsResults[7]} {lsResults[8]}.")
		[ ] Print("Step 4: Make sure the variables values are same as the Aspen Plus results.")
		[+] Print("Step 5: Click Specify Rigorous button. Select Plate as Model Type and select Input Key Geometry.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet*")
			[ ] APlus.Find("//WPFTextBlock[@caption='Main Flowsheet']").Click()
			[ ] sleep(3)
			[ ] APlus.FindObject("B1")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHeatX.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] wflyover.btnSpecifyRigorous.Click()
					[+] if(wSpecifyRigorousExchanger.Exists(20))
						[ ] wSpecifyRigorousExchanger.SetActive()
						[ ] wSpecifyRigorousExchanger.rdbPlate.Check()
						[ ] sleep(1)
						[ ] wSpecifyRigorousExchanger.rdbInputKeyGeometry.Check()
						[ ] sleep(1)
						[ ] wSpecifyRigorousExchanger.btnConvert.Click()
						[ ] //Step 6
						[+] if(wWarning.Exists(20))
							[ ] wWarning.SetActive()
							[ ] wWarning.btnYes.Click()
						[ ] sleep(5)
					[+] else
						[ ] Log.Fail("'Specify Rigorous Exchanger' window does not pop up.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 6: Click OK to the following dialog.")
		[+] Print("Step 7: Change the Model Readiness to Working Offline in the ribbon.")
			[+] do 
				[ ] APlus.SetTab("B1 (HeatX) - EDR Browser")
				[ ] Log.Pass("EDR Browser displays.")
				[ ] APlus.SetActive()
				[ ] APlus.btnConnectionStatus.Click()
				[ ] sleep(2)
				[ ] APlus.SetActive()
				[ ] APlus.ctrlTabNavigation.trvParttree.Expand("/Plate/Input/")
				[ ] APlus.ctrlTabNavigation.trvParttree.Expand("/Plate/Input/Problem Definition/")
				[ ] APlus.ctrlTabNavigation.trvParttree.Select("/Plate/Input/Problem Definition/Process Data/")
				[ ] sleep(2)
				[ ] APlus.tpgEDRBrowser.txbEstimatedPressureDrop1.Click()
				[ ] APlus.TypeKeys("{lsInputData[1]}<Enter>")
				[ ] sleep(3)
				[ ] //APlus.tpgEDRBrowser.txbEstimatedPressureDrop2.Click()
				[ ] APlus.TypeKeys("{lsInputData[1]}<Enter>")
				[ ] sleep(1)
				[ ] APlus.ctrlTabNavigation.trvParttree.Expand("/Plate/Input/Exchanger Geometry/")
				[ ] APlus.ctrlTabNavigation.trvParttree.Select("/Plate/Input/Exchanger Geometry/Geometry Summary/")
				[ ] sleep(3)
				[ ] APlus.SetActive()
				[ ] APlus.tpgEDRBrowser.txbTotalNumOfChannels1.Click()
				[ ] APlus.TypeKeys("{lsInputData[2]}<Enter>")
				[ ] sleep(1)
				[ ] APlus.tpgEDRBrowser.txbTotalNumOfChannels2.Click()
				[ ] APlus.TypeKeys("{lsInputData[2]}<Enter>")
				[ ] sleep(3)
				[ ] APlus.SetActive()
				[ ] APlus.ctrlTabNavigation.trvParttree.Select("/Plate/Input/Exchanger Geometry/Plate Details/")
				[ ] sleep(2)
				[ ] APlus.tpgEDRBrowser.txbChevronAngle.Click()
				[ ] APlus.TypeKeys("{lsInputData[3]}<Enter>")
				[ ] sleep(1)
				[ ] APlus.tpgEDRBrowser.txbHorizontalPort.Click()
				[ ] APlus.TypeKeys("{lsInputData[4]}<Enter>")
				[ ] sleep(1)
				[+] for(i=5;i<=ListCount(lsInputData);i++)
					[ ] APlus.TypeKeys("{lsInputData[i]}<Enter>")
					[ ] sleep(1)
				[ ] APlus.SetActive()
				[ ] APlus.btnRunEDR.Click()
				[ ] sleep(10)
				[ ] APlus.btnRunStatus.Click()
				[ ] sleep(12)
				[ ] i=ListCount(APlus.tpgEDRBrowser.lsvStatusView.Items)
				[+] if(APlus.tpgEDRBrowser.lsvStatusView.Items[i].TextCapture()=="-- successfully completed")
					[ ] Log.Pass("No error.")
				[+] else
					[ ] Log.Fail(" {i}With error.{APlus.tpgEDRBrowser.lsvStatusView.Items[i].TextCapture()}")
			[+] except
				[ ] ExceptClear()
				[ ] Log.Fail("EDR Browser does not display.")
		[+] Print("Step 8: Set Model Readiness to Connected and run Aspen Plus.")
			[ ] APlus.SetActive()
			[ ] APlus.btnConnectionStatus.Click()
			[ ] sleep(2)
			[ ] APlus.SetActive()
			[ ] APlus.closeTab("B1 (HeatX) - EDR Browser")
			[ ] sleep(1)
			[ ] APlus.SetActive()
			[ ] APlus.Run()
			[ ] //Verification
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.ScrollToPosition(0,O_VERTICAL)
			[ ] sleep(1)
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/B1")
			[ ] sleep(2)
			[+] if(APlus.rdbPlate.IsChecked)
				[ ] Log.Pass("The simple model has been converted to the rigorous model.")
			[+] else
				[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] if(APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" && APlus.ctrlEDRDashboard.ctrlOK.TextCapture()=="1" && APlus.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("EDR dashboard is updateded.")
			[+] else
				[ ] Log.Fail("EDR dashboard is not updateded.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
					[ ] Log.Pass("Exchanger Summary table is updateded.")
				[+] else
					[ ] Log.Fail("Exchanger Summary table is not updateded.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ]  APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet")
			[ ] sleep(2)
			[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\Step6.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually to verify the flyover has been updateded.")
		[+] Print("Step 9: Move the mouse hover over the converted Plate rigorous model. The model now is highlighted in blue circle. The following window will be displayed.")
			[+] for(i=LIstCount(lsValues);i>=1;i--)
				[ ] ListDelete(lsValues,i)
			[+] for(i=ListCount(lsResults);i>=1;i--)
				[ ] ListDelete(lsResults,i)
			[ ] APlus.SetActive()
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgPlate.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] ListAppend(lsValues,wflyover.dlgPlate.txtSurfaceArea.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgPlate.Find("//WPFTextBlock[6]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgPlate.txtTotalHeatLoad.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgPlate.Find("//WPFTextBlock[9]").sCaption)//xiaoqing
					[ ] ListAppend(lsValues,wflyover.dlgPlate.txtExchangersinParallel.sCaption)
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsResults=APlus.GetPlateResults("B1")
				[+] if(Abs(Val(lsResults[1])-Val(lsValues[1]))<0.001 && lsValues[2]==lsResults[2])
					[ ] Log.Pass("Value of 'Hot Side Delta T' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Hot Side Delta T' is wrong. Expect: {lsValues[1]} {lsValues[2]}. Actual: {lsResults[1]} {lsResults[2]}.")
				[+] if(Abs(Val(lsResults[3])-Val(lsValues[3]))<0.1 && lsValues[4]==lsResults[4])
					[ ] Log.Pass("Value of 'Cold Side Delta T' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Cold Side Delta T' is wrong. Expect: {lsValues[3]} {lsValues[4]}. Actual: {lsResults[3]} {lsResults[4]}.")
					[ ] 
				[+] if(Abs(Val(lsResults[5])-Val(lsValues[5]))<0.001)
					[ ] Log.Pass("Value of 'Duty' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Duty' is wrong. Expect: {lsValues[5]}. Actual: {lsResults[5]}.")
		[ ] Print("Step 10: Make sure the variables values are same as the Aspen Plus results.")
		[-] Print("Step 11: Select Show risk status from the drop-down button of EDR dashboard.")
			[ ] APlus.SetActive()
			[ ] APlus.btnActivateEDR.DoubleClick(1,10,10)
			[ ] sleep(1)
			[ ] APlus.chkShowRiskStatus.Check()
			[ ] sleep(2)
		[+] Print("Step 12: Move the mouse hover over the Plate rigorous model. The following flyover will be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgPlate.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\SortingLogic1.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Heat Transfer; 2)Other; 3)Vibration; 4)Flow; 5)Erosion rhoV2; 6)Pressure Drop")
					[ ] rfly=wflyover.dlgPlate.GetRect()
					[+] for j= rfly.xSize/2 to rfly.xPos+rfly.xSize step 5
						[ ] wflyover.dlgPlate.Click(1,j,10)
						[ ] //Step 13
						[+] if(wOperationWarnings.Exists())
							[ ] Log.Pass("The operation warning box for B1 pops up.")
							[ ] wOperationWarnings.SetActive()
							[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
								[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
							[+] else
								[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
								[ ] ListPrint(lsPopHeaders)
								[ ] Log.Fail("Actual: ")
								[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
							[ ] sleep(3)
							[ ] wOperationWarnings.SetActive()
							[ ] wOperationWarnings.Close()
							[ ] break
					[+] if(j>rfly.xPos+rfly.xSize)
						[ ] Log.Fail("The operation warning box for HTFS-PT does not pop up as expected.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 13: Click the highlighted traffic button, the operation warning box for B1 should pop up.")
		[+] Print("Step 14: Click ‘Revert to Simple’ button in Exchanger Summary Table and the following dialog appears.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
				[+] if(wRevertShortcutExchangerModel.Exists(20))
					[ ] wRevertShortcutExchangerModel.SetActive()
					[ ] //Step 15
					[ ] wRevertShortcutExchangerModel.rdbShortcutWithEDR.Select()
					[ ] sleep(1)
					[ ] wRevertShortcutExchangerModel.btnRevert.Click()
					[+] if(wDeleteExistingAreaSpec.Exists(20))
						[ ] //Step 16
						[ ] wDeleteExistingAreaSpec.SetActive()
						[ ] wDeleteExistingAreaSpec.btnOK.Click()
					[ ] sleep(3)
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 15: Select ‘Short cut with EDR Calculated UA and Pressure Drops’ and click Revert button.")
		[ ] Print("Step 16. Click OK to the ‘Delete existing area spec’ dialog.")
		[+] Print("Step 17. The model is converted successfully. ")
			[ ] APlus.SetActive()
			[ ] APlus.trvPartTree.Expand("/Blocks/")
			[ ] APlus.trvPartTree.Select("/Blocks/B1")
			[ ] sleep(2)
			[+] if(APlus.rdbShortcut.IsChecked)
				[ ] Log.Pass("The exchanger model changes to Shortcut.")
				[ ] APlus.SetTab("Specifications")
				[+] if(APlus.txtThird.TextCapture()!=null || APlus.txtThird.TextCapture()!="")
					[ ] Log.Pass("Constant UA value displays.")
				[+] else
					[ ] Log.Fail("Constant UA value does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.SetTab("Pressure Drop")
				[ ] sleep(1)
				[+] if(APlus.txtFirst.TextCapture()!=null || APlus.txtFirst.TextCapture()!="")
					[ ] Log.Pass("Outlet Pressure value displays.")
				[+] else
					[ ] Log.Fail("Outlet Pressure value does not display.")
			[+] else
				[ ] Log.Fail("The exchanger model does not change to Shortcut.")
			[+] if(APlus.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" && APlus.ctrlEDRDashboard.ctrlOK.TextCapture()=="0" && APlus.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("EDR dashboard is updateded.")
			[+] else
				[ ] Log.Fail("EDR dashboard is not updateded.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[+] if(APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
					[ ] Log.Pass("Exchanger Summary table is updateded.")
				[+] else
					[ ] Log.Fail("Exchanger Summary table is not updateded.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510206() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 27, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510206"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\Multi HXs"
		[ ] sCaseName="multi_HXs.bkp"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer inum,i, irow,j,iCount,k
		[ ] string sBitmapDir,sModel,sPath
		[ ] RECT r
		[ ] list of window lwAllRows
		[ ] list of string lsModels, lsHierarchy,lsPath,lsSub
		[ ] List of FILEINFO lFiles
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] lFiles=SYS_GetDirContents(sDatain)
		[+] for i=1 to ListCount(lFiles)
			[ ] File.Copy(sDatain+"\"+lFiles[i].sName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.3.5. Flyovers for Sub-Flowsheets")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus; open the attached multi HXs.bkp example file. Reset and run the case.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.Open(sDataout+"\"+sCaseName,0)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
			[+] if(APlus.btnUnpin.Exists())
				[ ] APlus.SetActive()
				[ ] APlus.btnUnpin.Click()
				[ ] sleep(2)
		[-] Print("Step 2: Click the drop-down button on EDR dashboard and select Show model Status.")
			[ ] APlus.SetActive()
			[ ] APlus.btnActivateEDR.Click(1,10,10)
			[ ] int n = 0
			[-]  while(APlus.chkShowModelStatus.exists() == false)
				[ ]  APlus.btnActivateEDR.Click(1,10,10)
				[ ]  sleep(2)
				[ ]  n++
				[+] if (n > 3)
					[ ]  break
			[ ] sleep(1)
			[ ] APlus.chkShowModelStatus.Check()
			[ ] sleep(2)
		[+] Print("Step 3: Hover over the highlight circle for H1, the flyover is displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet")
			[ ] sleep(1)
			[ ] APlus.FindAndSelectObject1("default","H1")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHierarchyBlock.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] //Step 4 - get the table's contents of 1st and 2nd columns
					[ ] wflyover.btnShowSummary.Click()
					[ ] lwAllRows=APlus.dgGeneralTable.FindAll("//WPFDataGridRow")
					[ ] irow=ListCount(lwAllRows)
					[+] for(j=1;j<=irow;j++)
						[ ] sModel=APlus.dgGeneralTable.Find("//WPFDataGridRow[{j}]").Find("//WPFDataGridCell[1]").TextCapture()
						[ ] sModel = StrTran(sModel,"	","")
						[ ] 
						[ ] ListAppend(lsModels,sModel)
						[ ] ListAppend(lsHierarchy, APlus.dgGeneralTable.Find("//WPFDataGridRow[{j}]").Find("//WPFDataGridCell[2]").TextCapture())
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] //Step 4 - check result
				[ ] ListPrint(lsHierarchy)
				[ ] print("----------------------------------------")
				[ ] 
				[+] for(j=1;j<=ListCount(lsModels);j++)
					[ ] sPath=""
					[ ] lsPath=SplitStringToList(lsHierarchy[j])
					[+] for(k=1;k<=ListCount(lsPath);k++)
						[ ] sPath=sPath+"/Blocks/"+lsPath[k]
					[ ] sPath=sPath+"/Blocks/"
					[ ] APlus.trvPartTree.Select(sPath)
					[ ] lsSub=APlus.GetModelsInABlock(sPath)
					[ ] ListPrint(lsSub)
					[+] if(ListFind(lsSub,lsModels[j])==0)
						[ ] Log.Fail("Not find {lsModels[j]}")
					[ ] sleep(1)
					[ ] APlus.trvPartTree.CollapseAll()
					[ ] 
				[+] if(j>=ListCount(lsHierarchy))
					[ ] Log.Pass("The heat exchangers in 1st level sub-flowsheet are displayed in the exactly sub-flowsheet name in 2nd column.")
				[+] else
					[ ] Log.Fail("The heat exchangers in 1st level sub-flowsheet are not displayed in the exactly sub-flowsheet name in 2nd column as expected.")
		[ ] Print("Step 4: Click the Show Summary button and the following flyover dialog will be displayed")
		[+] Print("Step 5: Double click H1 to open the flowsheet-H1.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet")
			[ ] sleep(1)
			[ ] APlus.FindAndSelectObject1("default","H1")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[ ] APlus.DoubleClick(1,r.xPos+r.xSize/2,r.yPos+r.ySize/2)
			[ ] sleep(2)
			[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\Sub_H1_Color.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the color: {chr(10)}"
    +"The hierarchy contains rigorous HeatXs will be highlighted in blue and the hierarchy contains only simple HeatXs will be highlighted in grey.")
		[-] Print("Step 6: Click Show risk status in EDR dashboard.")
			[ ] APlus.SetActive()
			[ ] APlus.btnActivateEDR.Click(1,10,10)
			[ ] n = 0
			[-]  while(APlus.chkShowModelStatus.exists() == false)
				[ ]  APlus.btnActivateEDR.Click(1,10,10)
				[ ]  sleep(2)
				[ ]  n++
				[+] if (n > 3)
					[ ]  break
			[ ] APlus.chkShowRiskStatus.Check()
			[ ] sleep(2)
			[ ] APlus.SetTab("Main Flowsheet")
			[ ] sleep(1)
			[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\BgColor3.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for backgroundcolor when mouse over the object and the orange border around the Operational Risk panel.{chr(10)}"
    +"In the case, HSIM is highlighted in grey and HRIG is highlighted in yellow..")
		[+] Print("Step 7: Hover over the highlight for HSIM, the Flyover is displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.FindAndSelectObject1("default","HSIM")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHierarchyBlock.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[+] Print("Step 8: Hover over the highlight for HRIG, the Flyover is displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.FindAndSelectObject1("default","HRIG")
			[ ] 
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHierarchyBlock.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] //Step 9
					[ ] wflyover.btnShowSummary.Click()
					[ ] sleep(2)
					[+] do
						[ ] APlus.SetTab("Hierarchy Block HRIG Exchanger Summary Table")
						[ ] Log.Pass("The exchanger summary table displays.")
						[ ] //Step 10
						[ ] APlus.SetActive()
						[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[4]").Click()
						[+] if(wOperationWarnings.Exists(10))
							[ ] Log.Pass("The operation warning box pops up.")
						[+] else
							[ ] Log.Fail("The operation warning box does not pop up.")
					[+] except
						[ ] ExceptClear()
						[ ] Log.Fail("The exchanger summary table does not display.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 9: Click Show Summary, the Exchanger Summary Table will be displayed.")
		[ ] Print("Step 10: Click the traffic light for the exchanger, the Operation Warning form will be displayed.")
	[ ] 
[+] testcase CQ00545026() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 27, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00545026"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\"+sTestCaseID
		[ ] sCaseName="activated dashboard.apwz"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] string sTemp1,sTemp2
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[+] // Case script
		[ ] Print("Scenario 1: EDR-AEA-EE")
		[+] Print("------------------------------------------------------------------------")
			[+] Print("Step 1: Open and run attached activated dashboard.apwz.")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.Open(sDataout+"\"+sCaseName,0)
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
				[+] if(APlus.btnUnpin.Exists())
					[ ] APlus.SetActive()
					[ ] APlus.btnUnpin.Click()
					[ ] sleep(2)
			[-] Print("Step 2: Click Activated EDR dashboard and click “Convert to rigorous” button to convert the simple model to rigorous model (size Shell & Tube Interactively – Size – Accept Design).")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[-] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 3
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[-] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[-] if(wEDRSizingConsole.Exists(50))
							[ ] Log.Pass("The EDR Sizing Console - size Shell&Tube window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[ ] sleep(2)
						[-] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[-] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/EDR-ST")
				[ ] sleep(2)
				[+] if(APlus.rdbShellTube.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[-] Print("Step 3: Click Activated Energy Analyzer dashboard.")
				[ ] APlus.SetActive()
				[ ] APlus.grpActivatedEnergyAnalysis.btnActivatedAnalysisOnOff.Click()
				[ ] glWaitForMouseIdle(600)
				[ ] APlus.SetActive()
				[ ] sTemp1=APlus.grpActivatedEnergyAnalysis.txtActivatedEnergyAnalysisPercentChange.TextCapture()
				[ ] sTemp2=APlus.grpActivatedEnergyAnalysis.txtActivatedEnergyAnalysisMWUsed.TextCapture()
				[+] if(sTemp1!="" && sTemp1!=null && sTemp2!="" && sTemp2!=null)
					[ ] Log.Pass("Data display in EE dashboard and there 's no error.")
			[-] Print("Step 4: Click Activated Economic Evaluation dashboard.")
				[ ] APlus.SetActive()
				[ ] APlus.grpActivatedEconomicAnalysis.btnActivatedEconomicAnalysisOnOff.Click()
				[ ] sleep(15)
				[ ] APlus.SetActive()
				[ ] // APlus.Minimize()
				[ ] // sleep(1)
				[ ] // APlus.Maximize()
				[ ] // sleep(1)
				[ ] sTemp1=APlus.grpActivatedEconomicAnalysis.txtActivatedEconomicAnalysisCapitalCost.TextCapture()
				[ ] sTemp2=APlus.grpActivatedEconomicAnalysis.txtActivatedEconomicAnalysisUtilityCost.TextCapture()
				[+] if(sTemp1!="" && sTemp1!=null && sTemp2!="" && sTemp2!=null)
					[ ] Log.Pass("Data display in EE dashboard and there 's no error.")
			[+] Print("Step 5: Close the case without saving.")
				[ ] APlus.CloseDocument()
				[ ] APlus.Exit()
		[ ] Print("Scenario 2: EDR-EE-AEA")
		[+] Print("------------------------------------------------------------------------")
			[+] Print("Step 1: Open and run attached activated dashboard.apwz.")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.Open(sDataout+"\"+sCaseName,0)
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
				[+] if(APlus.btnUnpin.Exists())
					[ ] APlus.SetActive()
					[ ] APlus.btnUnpin.Click()
					[ ] sleep(2)
			[+] Print("Step 2: Click Activated EDR dashboard and click “Convert to rigorous” button to convert the simple model to rigorous model (size Shell & Tube Interactively – Size – Accept Design).")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 3
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size Shell&Tube window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[ ] sleep(2)
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/EDR-ST")
				[ ] sleep(2)
				[+] if(APlus.rdbShellTube.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] Print("Step 3: Click Activated Economic Evaluation dashboard.")
				[ ] APlus.SetActive()
				[ ] APlus.grpActivatedEconomicAnalysis.btnActivatedEconomicAnalysisOnOff.Click()
				[ ] sleep(35)
				[ ] APlus.SetActive()
				[ ] // APlus.Minimize()
				[ ] // sleep(1)
				[ ] // APlus.Maximize()
				[ ] // sleep(1)
				[ ] sTemp1=APlus.grpActivatedEconomicAnalysis.txtActivatedEconomicAnalysisCapitalCost.TextCapture()
				[ ] sTemp2=APlus.grpActivatedEconomicAnalysis.txtActivatedEconomicAnalysisUtilityCost.TextCapture()
				[+] if(sTemp1!="" && sTemp1!=null && sTemp2!="" && sTemp2!=null)
					[ ] Log.Pass("Data display in EE dashboard and there 's no error.")
			[+] Print("Step 4: Click Activated Energy Analyzer dashboard.")
				[ ] APlus.SetActive()
				[ ] APlus.grpActivatedEnergyAnalysis.btnActivatedAnalysisOnOff.Click()
				[ ] sleep(15)
				[ ] APlus.SetActive()
				[ ] sTemp1=APlus.grpActivatedEnergyAnalysis.txtActivatedEnergyAnalysisPercentChange.TextCapture()
				[ ] sTemp2=APlus.grpActivatedEnergyAnalysis.txtActivatedEnergyAnalysisMWUsed.TextCapture()
				[+] if(sTemp1!="" && sTemp1!=null && sTemp2!="" && sTemp2!=null)
					[ ] Log.Pass("Data display in EE dashboard and there 's no error.")
			[+] Print("Step 5: Close the case without saving.")
				[ ] APlus.CloseDocument()
				[ ] APlus.Exit()
		[ ] Print("Scenario 3: EE-EDR")
		[+] Print("------------------------------------------------------------------------")
			[+] Print("Step 1: Open and run attached activated dashboard.apwz.")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.Open(sDataout+"\"+sCaseName,0)
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
				[+] if(APlus.btnUnpin.Exists())
					[ ] APlus.SetActive()
					[ ] APlus.btnUnpin.Click()
					[ ] sleep(2)
			[+] Print("Step 2: Click Activated Economic Evaluation dashboard.")
				[ ] APlus.SetActive()
				[ ] APlus.grpActivatedEconomicAnalysis.btnActivatedEconomicAnalysisOnOff.Click()
				[ ] sleep(15)
				[ ] APlus.SetActive()
				[ ] // APlus.Minimize()
				[ ] // sleep(1)
				[ ] // APlus.Maximize()
				[ ] // sleep(1)
				[ ] // APlus.SetTab("Main Flowsheet")
				[ ] sTemp1=APlus.grpActivatedEconomicAnalysis.txtActivatedEconomicAnalysisCapitalCost.TextCapture()
				[ ] sTemp2=APlus.grpActivatedEconomicAnalysis.txtActivatedEconomicAnalysisUtilityCost.TextCapture()
				[+] if(sTemp1!="" && sTemp1!=null && sTemp2!="" && sTemp2!=null)
					[ ] Log.Pass("Data display in EE dashboard and there 's no error.")
			[+] Print("Step 3: Click Activated EDR dashboard and click “Convert to rigorous” button to convert the simple model to rigorous model (size Shell & Tube Interactively – Size – Accept Design).")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 3
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size Shell&Tube window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[ ] sleep(2)
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/EDR-ST")
				[ ] sleep(2)
				[+] if(APlus.rdbShellTube.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] Print("Step 4: Close the case without saving.")
				[ ] APlus.CloseDocument()
				[ ] APlus.Exit()
		[ ] Print("Scenario 4: AEA-EDR")
		[+] Print("------------------------------------------------------------------------")
			[+] Print("Step 1: Open and run attached activated dashboard.apwz.")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.Open(sDataout+"\"+sCaseName,0)
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
				[+] if(APlus.btnUnpin.Exists())
					[ ] APlus.SetActive()
					[ ] APlus.btnUnpin.Click()
					[ ] sleep(2)
			[+] Print("Step 2: Click Activated Energy Analyzer dashboard.")
				[ ] APlus.SetActive()
				[ ] APlus.grpActivatedEnergyAnalysis.btnActivatedAnalysisOnOff.Click()
				[ ] sleep(15)
				[ ] APlus.SetActive()
				[ ] sTemp1=APlus.grpActivatedEnergyAnalysis.txtActivatedEnergyAnalysisPercentChange.TextCapture()
				[ ] sTemp2=APlus.grpActivatedEnergyAnalysis.txtActivatedEnergyAnalysisMWUsed.TextCapture()
				[+] if(sTemp1!="" && sTemp1!=null && sTemp2!="" && sTemp2!=null)
					[ ] Log.Pass("Data display in EE dashboard and there 's no error.")
			[+] Print("Step 3: Click Activated EDR dashboard and click “Convert to rigorous” button to convert the simple model to rigorous model (size Shell & Tube Interactively – Size – Accept Design).")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 3
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size Shell&Tube window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[ ] sleep(2)
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/EDR-ST")
				[ ] sleep(2)
				[+] if(APlus.rdbShellTube.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] Print("Step 4: Close the case without saving.")
				[ ] APlus.CloseDocument()
				[ ] APlus.Exit()
		[ ] Print("Scenario 5: EE-AEA-EDR")
		[+] Print("------------------------------------------------------------------------")
			[+] Print("Step 1: Open and run attached activated dashboard.apwz.")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.Open(sDataout+"\"+sCaseName,0)
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
				[+] if(APlus.btnUnpin.Exists())
					[ ] APlus.SetActive()
					[ ] APlus.btnUnpin.Click()
					[ ] sleep(2)
			[+] Print("Step 2: Click Activated Economic Evaluation dashboard.")
				[ ] APlus.SetActive()
				[ ] APlus.grpActivatedEconomicAnalysis.btnActivatedEconomicAnalysisOnOff.Click()
				[ ] sleep(15)
				[ ] APlus.SetActive()
				[ ] // APlus.Minimize()
				[ ] // sleep(1)
				[ ] // APlus.Maximize()
				[ ] // sleep(1)
				[ ] // APlus.SetTab("Main Flowsheet")
				[ ] sTemp1=APlus.grpActivatedEconomicAnalysis.txtActivatedEconomicAnalysisCapitalCost.TextCapture()
				[ ] sTemp2=APlus.grpActivatedEconomicAnalysis.txtActivatedEconomicAnalysisUtilityCost.TextCapture()
				[+] if(sTemp1!="" && sTemp1!=null && sTemp2!="" && sTemp2!=null)
					[ ] Log.Pass("Data display in EE dashboard and there 's no error.")
			[+] Print("Step 3: Click Activated Energy Analyzer dashboard.")
				[ ] APlus.SetActive()
				[ ] APlus.grpActivatedEnergyAnalysis.btnActivatedAnalysisOnOff.Click()
				[ ] sleep(15)
				[ ] APlus.SetActive()
				[ ] sTemp1=APlus.grpActivatedEnergyAnalysis.txtActivatedEnergyAnalysisPercentChange.TextCapture()
				[ ] sTemp2=APlus.grpActivatedEnergyAnalysis.txtActivatedEnergyAnalysisMWUsed.TextCapture()
				[+] if(sTemp1!="" && sTemp1!=null && sTemp2!="" && sTemp2!=null)
					[ ] Log.Pass("Data display in EE dashboard and there 's no error.")
			[+] Print("Step 4: Click Activated EDR dashboard and click “Convert to rigorous” button to convert the simple model to rigorous model (size Shell & Tube Interactively – Size – Accept Design).")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 3
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size Shell&Tube window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[ ] sleep(2)
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/EDR-ST")
				[ ] sleep(2)
				[+] if(APlus.rdbShellTube.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] Print("Step 5: Close the case without saving.")
				[ ] APlus.CloseDocument()
				[ ] APlus.Exit()
		[ ] Print("Scenario 6: EA-EE-EDR")
		[+] Print("------------------------------------------------------------------------")
			[+] Print("Step 1: Open and run attached activated dashboard.apwz.")
				[ ] APlus.Launch()
				[ ] APlus.SetActive()
				[ ] APlus.Open(sDataout+"\"+sCaseName,0)
				[ ] APlus.Reinit()
				[ ] sleep(5)
				[ ] APlus.Run()
				[+] if(APlus.btnUnpin.Exists())
					[ ] APlus.SetActive()
					[ ] APlus.btnUnpin.Click()
					[ ] sleep(2)
			[+] Print("Step 2: Click Activated Energy Analyzer dashboard.")
				[ ] APlus.SetActive()
				[ ] APlus.grpActivatedEnergyAnalysis.btnActivatedAnalysisOnOff.Click()
				[ ] sleep(15)
				[ ] APlus.SetActive()
				[ ] sTemp1=APlus.grpActivatedEnergyAnalysis.txtActivatedEnergyAnalysisPercentChange.TextCapture()
				[ ] sTemp2=APlus.grpActivatedEnergyAnalysis.txtActivatedEnergyAnalysisMWUsed.TextCapture()
				[+] if(sTemp1!="" && sTemp1!=null && sTemp2!="" && sTemp2!=null)
					[ ] Log.Pass("Data display in EE dashboard and there 's no error.")
			[+] Print("Step 3: Click Activated Economic Evaluation dashboard.")
				[ ] APlus.SetActive()
				[ ] APlus.grpActivatedEconomicAnalysis.btnActivatedEconomicAnalysisOnOff.Click()
				[ ] sleep(15)
				[ ] APlus.SetActive()
				[ ] // APlus.Minimize()
				[ ] // sleep(1)
				[ ] // APlus.Maximize()
				[ ] // sleep(1)
				[ ] // APlus.SetTab("Main Flowsheet")
				[ ] sTemp1=APlus.grpActivatedEconomicAnalysis.txtActivatedEconomicAnalysisCapitalCost.TextCapture()
				[ ] sTemp2=APlus.grpActivatedEconomicAnalysis.txtActivatedEconomicAnalysisUtilityCost.TextCapture()
				[+] if(sTemp1!="" && sTemp1!=null && sTemp2!="" && sTemp2!=null)
					[ ] Log.Pass("Data display in EE dashboard and there 's no error.")
			[+] Print("Step 4: Click Activated EDR dashboard and click “Convert to rigorous” button to convert the simple model to rigorous model (size Shell & Tube Interactively – Size – Accept Design).")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[+] if(wHelp.Exists(50))
					[ ] wHelp.Close()
					[ ] sleep(2)
				[+] if(APlus.tbiExchangerSummary.Exists())
					[ ] Log.Pass("Exchanger Summary Table appears.")
					[ ] //Step 3
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[+] if(wConverttoRigorousExchanger.Exists(10))
						[ ] Log.Pass("'Covert to Rigorous Exchanger' window pops up.")
						[ ] wConverttoRigorousExchanger.SetActive()
						[ ] wConverttoRigorousExchanger.rdbShellandTube.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Select()
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.btnConvert.Click()
						[+] if(wEDRSizingConsole.Exists(20))
							[ ] Log.Pass("The EDR Sizing Console - size Shell&Tube window pops up.")
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()
							[ ] sleep(25)
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[ ] sleep(2)
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("'Covert to Rigorous Exchanger' window does not pop up.")
				[+] else
					[ ] Log.Fail("Exchanger Summary Table does not appear.")
				[ ] APlus.SetActive()
				[ ] APlus.trvPartTree.Expand("/Blocks/")
				[ ] APlus.trvPartTree.Select("/Blocks/EDR-ST")
				[ ] sleep(2)
				[+] if(APlus.rdbShellTube.IsChecked)
					[ ] Log.Pass("The simple model has been converted to the rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is not converted to the rigorous model.")
			[+] Print("Step 5: Close the case without saving.")
				[ ] APlus.CloseDocument()
				[ ] APlus.Exit()
		[ ] 
	[ ] 
[+] testcase CQ00510127() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 27, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510127"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\Multi HXs"
		[ ] sCaseName="multi_HXs.bkp"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] integer i, iSimple=0,irow,k,j
		[+] list of string lsHeadersExp={...}
			[ ] "Exchanger Name"
			[ ] "Hierarchy Block"
			[ ] "Model Status"
			[ ] "Summary"
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] "Vibration"
			[ ] "Erosion: RhoV2"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] "Other"
		[+] list of string lsPopHeaders={...}
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] "Vibration"
			[ ] "Erosion: RhoV2"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] "Other"
		[+] list of string lsModelsType={...}
			[ ] "HTFS-ST"
			[ ] "HTFS-PL"
			[ ] "HTFS-AC"
		[ ] list of window lw
		[ ] List of FILEINFO lFiles
		[ ] string sTemp1,sTemp2
		[ ] string sBitmapDir,sModel,sPath
		[ ] RECT r
		[ ] list of window lwAllRows
		[ ] list of string lsModels, lsHierarchy,lsPath,lsHeadersAct,lsSort,lsSub,lsTemp
		[ ] boolean bFlag
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] lFiles=SYS_GetDirContents(sDatain)
		[+] for i=1 to ListCount(lFiles)
			[ ] File.Copy(sDatain+"\"+lFiles[i].sName,sDataout)
		[ ] sleep(2)
	[+] // Case script
		[ ] Print("4.3.2 EDR activated summary table workflow")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus, open the attached multi HXs.bkp example file.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.Open(sDataout+"\"+sCaseName,0)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
			[+] if(APlus.btnUnpin.Exists())
				[ ] APlus.SetActive()
				[ ] APlus.btnUnpin.Click()
				[ ] sleep(2)
		[+] Print("Step 2: Click the EDR activation button and the Exchanger Summary Table appears.")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[ ] print("Col4--------------------")
			[ ] sBitmapDir=APlus.CaptureBitmap("{sDataout}\Col4.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually to make sure the number of each risk status and simple models are same as that in EDR dashboard..")
			[ ] 
			[+] if(APlus.tbiExchangerSummary.Exists())
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] APlus.SetActive()
				[ ] lsHeadersAct=GetHeaders(APlus.dgGeneralTable)
				[+] for(i=1;i<=ListCount(lsHeadersExp);i++)
					[+] if(lsHeadersAct[i+1]!=lsHeadersExp[i])
						[ ] Log.Fail("Table headers are not the same as expected.")
						[ ] break
				[+] if(i>ListCount(lsHeadersExp))
					[ ] Log.Pass("Table headers are as expected.")
				[ ] //Col 1
				[ ] print("Col1--------------------")
				[ ] lsTemp=GetAllDataInOneColumn(APlus.dgGeneralTable,1)	//get model name
				[ ] lsModels=APlus.GetModelsInSummaryTable()			//get full path
				[+] for(i=1;i<=ListCount(lsModels);i++)
					[ ] APlus.SetActive()
					[ ] sleep(1)
					[ ] APlus.Find("//WPFTabItem[@caption='Main Flowsheet Main Flowsheet']").Click(2)
					[ ] sleep(1)
					[ ] APlus.muiCloseOtherTabs.Click()
					[ ] sleep(2)
					[ ] bFlag=APlus.GetModelType(lsModels[i])		// include Col2 check
					[ ] APlus.SetActive()
					[ ] sleep(1)
					[ ] APlus.Find("//WPFTabItem[@caption='Main Flowsheet Main Flowsheet']").Click(2)
					[ ] sleep(1)
					[ ] APlus.muiCloseOtherTabs.Click()
					[ ] sleep(2)
					[ ] APlus.ctrlEDRDashboard.Click()
					[ ] sleep(2)
					[ ] 
					[ ] sTemp2=APlus.dgGeneralTable.Find("/WPFDataGridRow[{i}]//WPFDataGridCell[3]").TextCapture()
					[ ] APlus.dgGeneralTable.Find("//WPFTextBlock[@automationId='hyperlink'][{i}]/WPFTextBlock[@caption='{lsTemp[i]}']").Click()
					[ ] sleep(7)
					[+] do
						[ ] APlus.SetTab("*{lsTemp[i]}* - Setup")
						[ ] APlus.SetTab("Specifications")
						[ ] sleep(1)
						[+] if(bFlag)
							[ ] Log.Pass("For simple models, click on the exchanger name and the Setup form opens.")
						[+] else
							[ ] Log.Fail("For rigorous models, click on the exchanger name and the EDR Browser opens.")
						[ ] //Col 3
						[+] if(sTemp2=="Convert to Rigorous")
							[ ] Log.Pass("'Convert to Rigorous' is displayed for simple models.")
						[+] else
							[ ] Log.Fail("'Convert to Rigorous' is not displayed for simple models.")
					[+] except
						[ ] ExceptClear()
						[+] do
							[ ] APlus.SetTab("*{lsTemp[i]}* - EDR Browser")
							[+] if(!bFlag)
								[ ] Log.Pass("For rigorous model, click on the exchanger name and the EDR Browser opens.")
							[+] else
								[ ] Log.Fail("For simple model, click on the exchanger name and the EDR Browser opens.")
						[+] except
							[ ] //ExceptClear()
							[ ] Log.Fail("No tab page opens.")
				[ ] // //Col 2
				[ ] // print("Col2--------------------")
				[ ] // irow=ListCount(APlus.dgGeneralTable.FindAll("/WPFDataGridRow"))
				[+] // for(j=1;j<=irow;j++)
					[ ] // sModel=APlus.dgGeneralTable.Find("//WPFDataGridRow[{j}]").Find("//WPFDataGridCell[1]").TextCapture()
					[ ] // ListAppend(lsModels,sModel)
					[ ] // ListAppend(lsHierarchy, APlus.dgGeneralTable.Find("//WPFDataGridRow[{j}]").Find("//WPFDataGridCell[2]").TextCapture())
				[ ] // ListPrint(lsHierarchy)
				[ ] // print("----------------------------------------")
				[+] // for(j=1;j<=ListCount(lsModels);j++)
					[ ] // sPath=""
					[ ] // lsPath=SplitStringToList(lsHierarchy[j])
					[+] // for(k=1;k<=ListCount(lsPath);k++)
						[ ] // sPath=sPath+"/Blocks/"+lsPath[k]
					[ ] // sPath=sPath+"/Blocks/"
					[ ] // lsSub=APlus.GetModelsInABlock(sPath)
					[+] // if(ListFind(lsSub,lsModels[j])==0)
						[ ] // Log.Fail("Not find {lsModels[j]}")
					[ ] // sleep(1)
				[+] // if(j>=ListCount(lsHierarchy))
					[ ] // Log.Pass("The heat exchangers in 1st level sub-flowsheet are displayed in the exactly sub-flowsheet name in 2nd column.")
				[+] // else
					[ ] // Log.Fail("The heat exchangers in 1st level sub-flowsheet are not displayed in the exactly sub-flowsheet name in 2nd column as expected.")
				[ ] // 
				[ ] //Col 4
				[ ] //Step 3 &4
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[ ] sleep(2)
				[+] for(j=1;j<=3;j++)
					[ ] APlus.SetActive()
					[ ] lsModels=GetAllDataInOneColumn(APlus.dgGeneralTable,j)
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridColumnHeader[{j+1}]").Click()
					[ ] lsSort=GetAllDataInOneColumn(APlus.dgGeneralTable,j)
					[ ] ListSort(lsModels)
					[+] if(lsModels==lsSort)
						[ ] Log.Pass("Contents are sorted by ascending.")
					[+] else
						[ ] Log.Fail("Contents are not sorted by ascending.")
					[ ] sleep(1)
					[ ] APlus.SetActive()
					[ ] APlus.dgGeneralTable.Find("/WPFDataGridColumnHeader[{j+1}]").Click()
					[ ] lsSort=GetAllDataInOneColumn(APlus.dgGeneralTable,j)
					[+] if(ReverseList(lsModels)==lsSort)
						[ ] Log.Pass("Contents are sorted by descending.")
					[+] else
						[ ] Log.Fail("Contents are not sorted by descending.")
					[ ] sleep(1)
				[ ] //Step 5
				[ ] APlus.SetActive()
				[ ] APlus.btnFilterHierarchy.Click()
				[+] if(APlus.lstGeneral.Exists(10))
					[ ] APlus.chkSelectAll.Uncheck()
					[ ] sleep(1)
					[ ] APlus.chkH1HRIG.Check()
					[ ] sleep(1)
					[ ] APlus.btnPopupOK.Click()
					[ ] sleep(1)
					[ ] //Verification
					[ ] sPath=""
					[ ] lsPath=SplitStringToList(APlus.dgGeneralTable.Find("//WPFDataGridRow[1]").Find("//WPFDataGridCell[2]").TextCapture())
					[ ] lsModels=GetAllDataInOneColumn(APlus.dgGeneralTable,1)
					[+] for(k=1;k<=ListCount(lsPath);k++)
						[ ] sPath=sPath+"/Blocks/"+lsPath[k]
					[ ] sPath=sPath+"/Blocks/"
					[ ] lsSub=APlus.GetModelsInABlock(sPath)
					[+] for(j=1;j<=ListCount(lsModels);j++)
						[+] if(ListFind(lsSub,lsModels[j])==0)
							[ ] Log.Fail("{lsModels[j]} is not under {sPath}, filter function wrong.")
						[ ] sleep(1)
					[+] if(j>=ListCount(lsHierarchy))
						[ ] Log.Pass("Filter funcation right for the 2nd column..")
				[+] else
					[ ] Log.Fail("Filter pop-up does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.ctrlEDRDashboard.Click()
				[ ] sleep(2)
				[ ] APlus.btnFilterHierarchy.Click()
				[+] if(APlus.lstGeneral.Exists(10))
					[ ] APlus.chkSelectAll.Check()
					[ ] sleep(1)
					[ ] APlus.btnPopupOK.Click()
					[ ] sleep(1)
				[+] else
					[ ] Log.Fail("Filter pop-up does not display.")
				[ ] //Step 6
				[ ] APlus.SetActive()
				[ ] APlus.btnFilterStatus.Click()
				[+] if(APlus.lstGeneral.Exists(10))
					[ ] APlus.chkSelectAll.Uncheck()
					[ ] sleep(1)
					[ ] APlus.chkConvertToRigorous.Check()
					[ ] sleep(1)
					[ ] APlus.btnPopupOK.Click()
					[ ] sleep(1)
					[ ] //Verification
					[ ] irow=ListCount(APlus.dgGeneralTable.FindAll("/WPFDataGridRow"))
					[+] for(j=1;j<=irow;j++)
						[ ] sTemp1=APlus.dgGeneralTable.Find("/WPFDataGridRow[{j}]//WPFDataGridCell[3]").TextCapture()
						[+] if(sTemp1!="Convert to Rigorous")
							[ ] Log.Fail("Filter function for Status column works wrong.")
							[ ] break
					[+] if(j>irow)
						[ ] Log.Pass("Filter function for Status column works correctly.")
				[+] else
					[ ] Log.Fail("Filter pop-up does not display.")
				[ ] APlus.SetActive()
				[ ] APlus.btnFilterStatus.Click()
				[+] if(APlus.lstGeneral.Exists(10))
					[ ] APlus.chkSelectAll.Check()
					[ ] sleep(1)
					[ ] APlus.btnPopupOK.Click()
					[ ] sleep(1)
				[+] else
					[ ] Log.Fail("Filter pop-up does not display.")
				[ ] //Step 7
				[ ] APlus.dgGeneralTable.Find("//WPFTextBlock[@caption='HHTFS-AC']").Click()
				[ ] sleep(2)
				[+] do
					[ ] APlus.SetTab("H1.HRIG.HHTFS-AC (HeatX) - EDR Browser")
					[ ] Log.Pass("EDR browser opens.")
				[+] except
					[ ] ExceptClear()
					[ ] Log.Fail("EDR browser does not open")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Click the headline of the Exchanger Name column, the Exchanger Name in the summary table will be sorted by ascending. Click the headline again; the Exchanger Name in the summary table will be sorted by descending.")
		[ ] Print("Step 4: Repeat Step 3 for the Hierarchy Block, Model Status and Summary columns.")
		[ ] Print("Step 5: Click the down arrow button in the Hierarchy Block column; select one of the filter options. E.g. H1.HRIG")
		[ ] Print("Step 6: Repeat Step 5 for Model Status and Summary column.")
		[ ] Print("Step 7: Click the link for HTFS-AC in Exchanger Name column, the EDR Browser for HTFS-AC will pop up.")
		[+] Print("Step 8: The Operation Warnings are displayed with the following variables:")
			[ ] APlus.SetActive()
			[ ] APlus.ctrlEDRDashboard.Click()
			[+] if(wHelp.Exists(50))
				[ ] wHelp.Close()
				[ ] sleep(2)
			[+] if(APlus.tbiExchangerSummary.Exists())
				[ ] APlus.SetActive()
				[+] for(i=5;i<=ListCount(lsHeadersExp);i++)
					[+] if(lsHeadersAct[i+1]!=lsHeadersExp[i])
						[ ] Log.Fail("Table headers are not the same as expected.")
						[ ] break
				[+] if(i>ListCount(lsHeadersExp))
					[ ] Log.Pass("Table headers are as expected.")
				[ ] //Step 9 & 10 & 11
				[+] for(j=1;j<=ListCount(lsModelsType);j++)
					[+] for(i=1;i<=ListCount(lsModels);i++)
						[+] if(APlus.dgGeneralTable.Find("//WPFDataGridRow[{i}]").Find("//WPFDataGridCell[4]").TextCapture()==lsModelsType[j])
							[ ] APlus.SetActive()
							[ ] APlus.dgGeneralTable.Find("//WPFDataGridRow[{i}]").Find("//WPFDataGridCell[4]").Click()
							[+] if(wOperationWarnings.Exists(10))
								[ ] Log.Pass("The operation warning box for HTFS-ST pops up.")
								[ ] wOperationWarnings.SetActive()
								[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
									[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
								[+] else
									[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
									[ ] ListPrint(lsPopHeaders)
									[ ] Log.Fail("Actual: ")
									[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings.dgTable,1))
								[ ] //Step 10
								[ ] wOperationWarnings.Close()
							[+] else
								[ ] Log.Fail("The operation warning box for HTFS-ST does not pop up.")
							[ ] break
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 9: Click the traffic light of HTFS-ST in Column 2, the Operation Warnings form for HTFS-ST will pop up.")
		[ ] Print("Step 10: Click the “X” button, the Operation Warnigs form will be closed.")
		[ ] Print("Step 11: Repeat step 9&10 for the AirCooled and Plate models.")
		[ ] 
	[ ] 
[ ] 
[ ] 
[ ] 
[+] testcase debug() appstate none
	[-] // //APlus.GetHeatResults("B1")
			[ ] // APlus.SetActive()
			[ ] // APlus.btnActivateEDR.Click(1,10,10)
			[ ] // sleep(1)
			[ ] // APlus.chkShowModelStatus.Check()
			[ ] sleep(2)
[ ] 
[+] testcase dubug1() appstate none
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510199"
		[ ] sDatain=sAspenPlus_sProjectDir+"data\datain\SimpleToRigorous"
		[ ] sCaseName="Shortcut.bkp"
		[ ] sDataout=sAspenPlus_sProjectDir+"data\dataout\"+sTestCaseID
		[ ] string sTemplateFile=sDatain+"\EDT\CS_Air_Cooled_SI.EDT"
		[ ] integer inum,i, irow,j,iCount,k
		[ ] string sBitmapDir,sModel,sPath
		[ ] RECT r,rfly
		[+] list of string lsPopHeaders={...}
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] "Vibration"
			[ ] "Erosion: RhoV2"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] "Other"
		[ ] list of window lwAllRows
		[ ] list of string lsValues, lsResults
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.6.1 Shell&Tube smoke test for Activated EDR in Aspen Plus")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch Aspen Plus, open the attached Shortcut.bkp and run.")
			[ ] APlus.Launch()
			[ ] APlus.SetActive()
			[ ] APlus.Open(sDataout+"\"+sCaseName,0)
			[ ] APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
			[+] if(APlus.btnUnpin.Exists())
				[ ] APlus.SetActive()
				[ ] APlus.btnUnpin.Click()
				[ ] sleep(2)
		[-] Print("Step 2: Click the drop-down button in EDR dashboard and select Show model status.")
			[ ] APlus.SetActive()
			[ ] APlus.btnActivateEDR.Click(1,10,10)
			[ ] sleep(1)
			[ ] int n
			[-] while(APlus.chkShowModelStatus.exists() == false)
				[ ] APlus.btnActivateEDR.Click(1,10,10)
				[ ] sleep(2)
				[ ] n++
				[-] if (n > 3)
					[ ] break
			[ ] APlus.chkShowModelStatus.Check()
			[ ] sleep(2)
		[+] Print("Step 3: Go to flowsheet, move the mouse over block B1, which is highlighted in grey circle. The following window will be displayed.")
			[ ] APlus.SetActive()
			[ ] APlus.SetTab("Main Flowsheet*")
			[ ] sleep(3)
			[ ] APlus.FindObject("B1")
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover.dlgHeatX.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] //Step 4 - Get the values need check
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtHotSideDeltaT.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[6]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtColdSideDeltaT.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[9]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtDuty.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[12]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.txtArea.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgHeatX.Find("//WPFTextBlock[15]").sCaption)
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] //Step 4 - check
				[ ] lsResults=APlus.GetHeatResults("B1")
				[+] if(Abs(Val(lsResults[1])-Val(lsValues[1]))<0.001 && lsValues[2]==lsResults[2])
					[ ] Log.Pass("Value of 'Hot Side Delta T' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Hot Side Delta T' is wrong. Expect: {lsValues[1]} {lsValues[2]}. Actual: {lsResults[1]} {lsResults[2]}.")
					[ ] 
				[+] if(Abs(Val(lsResults[3])-Val(lsValues[3]))<0.1 && lsValues[4]==lsResults[4])
					[ ] Log.Pass("Value of 'Cold Side Delta T' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Cold Side Delta T' is wrong. Expect: {lsValues[3]} {lsValues[4]}. Actual: {lsResults[3]} {lsResults[4]}.")
					[ ] 
				[+] if(Abs(Val(lsResults[5])-Val(lsValues[5]))<0.001 && lsValues[6]==lsResults[6])
					[ ] Log.Pass("Value of 'Duty' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Duty' is wrong. Expect: {lsValues[5]} {lsValues[6]}. Actual: {lsResults[5]} {lsResults[6]}.")
				[+] if(Abs(Val(lsResults[7])-Val(lsValues[7]))<0.001 && lsValues[8]==lsResults[8])
					[ ] Log.Pass("Value of 'Area' is correct.")
				[+] else
					[ ] Log.Fail("Value of 'Area' is wrong. Expect: {lsValues[7]} {lsValues[8]}. Actual: {lsResults[7]} {lsResults[8]}.")
[ ] 
[+] testcase debug2() appstate none
				[ ] LIST OF STRING lsResults
				[ ] APlus.SetActive()
				[ ] lsResults=APlus.GetSTResults("B1")
				[ ] print("****lsResults****")
				[ ] ListPrint(lsResults)
				[ ] 
	[ ] 
	[ ] 
[+] testcase debug3() appstate none
			[ ] RECT r,rfly
			[ ] LIST OF STRING lsValues
			[ ] 
			[ ] int i,j
			[ ] APlus.SetActive()
			[ ] APlus.SetActive()
			[ ] // APlus.Reinit()
			[ ] sleep(5)
			[ ] APlus.Run()
			[ ] sleep(20)
			[ ] APlus.SetActive()
			[ ] APlus.CaptureBitmap("C:\Users\Administrator\Documents\test.bmp",APlus.areaForMainFlowsheet.GetRect())
			[ ] r=APlus.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-100 to r.yPos+r.ySize/2+600
				[ ] APlus.MoveMouse(r.xPos+r.xSize/2,i)
				[ ] sleep(2)
				[-] if(wflyover.dlgShellandTube.Exists(2))
					[ ] Log.Pass("Flyover displays.")
					[ ] //Step 8 - Get the values need check
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.txtSurfaceArea.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.Find("//WPFTextBlock[6]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.txtTotalHeadLoad.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.Find("//WPFTextBlock[9]").sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.txtTEMAType.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.txtShellsinSeries.sCaption)
					[ ] ListAppend(lsValues,wflyover.dlgShellandTube.txtShellsinParallel.sCaption)
					[ ] print("*******lsValues********")
					[ ] ListPrint(lsValues)
					[ ] print("******lsValues*********")
					[ ] break
			[ ] 
			[ ] // APlus.FindAndSelectObject1("default","HTFS-AC")
			[ ] // r=APlus.areaForMainFlowsheet.GetRect()
			[-] // for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] // APlus.MoveMouse(r.xPos+r.xSize/2-20,i)
				[-] // if(wflyover.dlgAirCooled.Exists())
					[ ] // Log.Pass("Flyover displays.")
					[ ] // //sBitmapDir=APlus.CaptureBitmap("{sDataout}\SortingLogic2.bmp")
					[ ] // //Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    // // +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    // // +"2. Sort by order for the equivalent status, 1)Heat Transfer; 2)Other; 3)Vibration; 4)Flow; 5)Erosion rhoV2; 6)Pressure Drop")
					[ ] // //Step 8
					[ ] // rfly=wflyover.dlgAirCooled.GetRect()
					[-] // for j= rfly.xSize/2 to rfly.xPos+rfly.xSize step 2
							[ ] // wflyover.dlgAirCooled.Click(1,j,10)
							[-] // if(wOperationWarnings.Exists())
								[ ] // Log.Pass("The operation warning box for HTFS-AC pops up.")
								[ ] // wOperationWarnings.SetActive()
	[ ] 
	[ ] 
	[ ] 
