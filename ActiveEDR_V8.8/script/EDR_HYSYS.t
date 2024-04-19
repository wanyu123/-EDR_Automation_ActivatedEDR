[ ] 
[ ] use "../frame/HYSYS/Frame.inc"
[ ] 
[+] testcase CQ00510213() appstate CleanState		
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 17, 2013
	[-] // Variables defination
		[ ] sCaseName="{sAspenHysysSamples}\Water Distribution Network.hsc"
	[-] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
	[-] // Case script
		[ ] Print("4.2.1 Activating EDR activation with no heat exchanger in HYSYS file ")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS; open the Water Distribution Network.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sCaseName,10)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
			[ ] AH.SetActive()
			[+] if(AH.Find("//WPFTextBlock[@caption='Simulation Case: Case']").Exists())
				[ ] print("sss")
				[ ] AH.Find("//WPFTextBlock[@caption='Simulation Case: Case']").Click(2)
				[ ] sleep(1)
				[ ] AH.muiAutoHide.Click()
				[ ] sleep(2)
		[-] Print("Step 2: Hover the mouse onto the exchanger icon, the tooltip will pop up.")
			[+] if(!AH.ctrlDashboard.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnExpandCollapseDashboard.Click()
				[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] AH.ctrlEDRDashboard.DoubleClick()//wanyu
			[-] if(AH.tbiExchangerSummary.Exists())
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[-] if(AH.ctrlEDRDashboard.ctrlOK.TextCapture()=="0" && AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" && AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
					[ ] Log.Pass("All the simple model number and the rigorous model number is displayed as 0.")
				[-] else
					[ ] Log.Fail("Not all the simple model number and the rigorous model number is displayed as 0.")
				[-] if(!AH.btnExchanger.IsEnabled)
					[ ] Log.Pass("The Exchanger icon is inactive.")
				[-] else
					[ ] Log.Fail("The Exchanger icon is active.")
				[-] if(AH.btnExchanger.ToolTip==sAHToolTip)
					[ ] Log.Pass("Tooltip displays as expected.")
				[-] else
					[ ] Log.Fail("Tooltip does not display as expected.")
			[-] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] 
	[ ] 
[+] testcase CQ00510214() appstate CleanState	
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 17, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510214"
		[ ] sCaseName="{sAspenHysysSamples}\Natural Gas Dehydration with TEG.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i, iSimple=0
		[ ] string sBitmapDir
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
	[-] // Case script
		[ ] Print("4.2.2 Activating EDR activation with only simple heat exchanger in HYSYS file")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the Natural Gas Dehydration with TEG.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sCaseName,10)
			[-] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
			[ ] AH.SetActive()
		[-] Print("Step 2: Check the dashboard is displayed as below.")
			[+] if(AH.ctrlEDRDashboard.ctrlOK.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("The number of the rigorous models(OK and At Risk) is shown as 0.")
			[+] else
				[ ] Log.Fail("The number of the rigorous models(OK and At Risk) is not shown as 0.")
			[ ] AH.btnExpandCollapseDashboard.Click() //Line added by Yael Gonzalez on 11/22/2021
			[-] if(AH.btnExchanger.IsEnabled)
				[ ] Log.Pass("The Exchanger icon is active.")
			[-] else
				[ ] Log.Fail("The Exchanger icon is inactive.")
		[+] Print("Step 3: Click the exchanger icon")
			[ ] AH.ClickExchanger()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[+] if(AH.chkShowModelStatus.IsEnabled && AH.chkShowLegend.IsEnabled && !AH.chkShowRiskStatus.IsEnabled)
				[ ] Log.Pass("The Show model status and Show legend are active, and the Show risk status is inactive.")
			[+] else
				[ ] Log.Fail("The Show model status or Show legend are inactive, or the Show risk status is active.")
		[+] Print("Step 4: Click the Activated EDR dashboard, the following Exchanger Summary Table will be opened.")
			[-] if(!AH.ctrlDashboard.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnExpandCollapseDashboard.Click()
				[ ] sleep(3)
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[+] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[+] for(i=1;i<=ListCount(AH.dgGeneralTable.FindAll("/WPFDataGridRow"));i++)
					[+] if(AH.IsSimpleModel(i))
						[ ] iSimple++
				[+] if(iSimple==Val(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()))
					[ ] Log.Pass("The number shown for the simple models(Unknown) is same as the HYSYS contains.")
				[+] else
					[ ] Log.Fail("The number shown for the simple models(Unknown) is not same as the HYSYS contains")
				[ ] inum=Val(AH.ctrlEDRDashboard.ctrlOK.TextCapture())+Val(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture())+Val( AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture())
				[+] if(inum==ListCount(AH.dgGeneralTable.FindAll("/WPFDataGridRow")))
					[ ] Log.Pass("The models displayed in Activated Summary table have the same number.")
				[+] else
					[ ] Log.Fail("The models displayed in Activated Summary table do not have the same number.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] 
	[ ] 
[+] testcase CQ00510216() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510216"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[ ] sCaseName="Multi-HXs.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,iSimple=0,iRigorous=0,i
		[ ] string sBitmapDir
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.3.1 Basic function for Activating EDR panel")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached Multi-HXs.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the EDR activation button, the following Model Status panel and Operational Risk panel will be opened.")
			[+] if(!AH.ctrlDashboard.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnExpandCollapseDashboard.Click()
				[ ] sleep(3)
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[-] // for(i=1;i<=ListCount(AH.dgGeneralTable.FindAll("/WPFDataGridRow"));i++)
					[-] // if(AH.IsSimpleModel(i))
						[ ] // iSimple++
						[ ] // print("{i}--------------------------------")
					[-] // else
						[ ] // iRigorous++
				[+] // if(iSimple==Val(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()))
					[ ] // Log.Pass("The number shown for the simple models(Unknown) is same as the HYSYS contains.")
				[+] // else
					[ ] // Log.Fail("The number shown for the simple models(Unknown) is not same as the HYSYS contains")
				[-] // if(Val(AH.ctrlEDRDashboard.ctrlOK.TextCapture())+Val( AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture())==iRigorous)
					[ ] // Log.Pass("The number shown for the rigorous models(OK & At Risk) is same as the HYSYS contains.")
				[+] // else
					[ ] // Log.Fail("The number shown for the rigorous models(OK & At Risk) is not same as the HYSYS contains.")
				[+] // if(AH.btnExchanger.IsEnabled)
					[ ] // Log.Pass("The Exchanger icon is active.")
				[+] // else
					[ ] // Log.Fail("The Exchanger icon is inactive.")
				[ ] //Step 3
				[ ] AH.SetActive()
				[ ] AH.ClickExchanger()
				[+] if(AH.chkShowModelStatus.IsEnabled && AH.chkShowLegend.IsEnabled && AH.chkShowRiskStatus.IsEnabled)
					[ ] Log.Pass("All the buttons are active.")
				[-] else
					[ ] Log.Fail("Not all the buttons are active..")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Click the exchanger icon.")
		[-] Print("Step 4: Click the Collapse button beside the close button. The Activated EDR dashboard will show the smaller icon.")
			[ ] AH.SetActive()
			[ ] AH.btnExpandCollapseDashboard.Click()
			[ ] sleep(2)
			[+] if(!AH.ctrlDashboard.Exists())
				[ ] Log.Pass("The Activated EDR dashboard shows the smaller icon.")
			[+] else
				[ ] Log.Fail("The Activated EDR dashboard does not show the smaller icon.")
		[+] Print("Step 5: Click the Collapse button again, the Activated EDR dashboard will displayed as step 2")
			[ ] AH.SetActive()
			[ ] AH.btnExpandCollapseDashboard.Click()
			[ ] sleep(2)
			[+] if(AH.ctrlDashboard.Exists())
				[ ] Log.Pass("The Activated EDR dashboard shows as step 2..")
			[+] else
				[ ] Log.Fail("The Activated EDR dashboard does not show tas step 2.")
		[ ] Print("Step 6: Click the active dashboard, the Activated Summary Table will pop up.")
		[ ] 
	[ ] 
[+] testcase CQ00510225() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510225"
		[ ] sDatain="{sDatain}\Multi HXs"
		[ ] sCaseName="Multi-HXs.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
		[ ] RECT r
		[ ] list of string lsDataInFlyover, lsDataActual
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.3.3 Activating EDR activation – Show model status")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached Multi-HXs.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,150)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] sleep(1)
			[ ] AH.btnGoToParent.Click()
			[ ] sleep(10)
			[-] if(wSubFlowsheet.Exists(5))
				[ ] wSubFlowsheet.SetActive()
				[ ] wSubFlowsheet.Close()
				[ ] sleep(1)
			[-] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] sleep(1)
			[ ] AH.btnGoToParent.Click()
			[ ] sleep(10)
			[+] if(wSubFlowsheet.Exists(5))
				[ ] wSubFlowsheet.SetActive()
				[ ] wSubFlowsheet.Close()
				[ ] sleep(1)
		[-] Print("Step 2: Click the Exchanger icon on the Activated EDR dashboard and select “Show legend” option, the following picture will displayed and a check mark is displayed in front of the option.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(2)
			[ ] AH.chkShowLegend.Check()
			[ ] sleep(2)
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Legend.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for confirming legend picture displays and a check mark is displayed in front of the option.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Check.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for confirming legend picture displays and a check mark is displayed in front of the option.")
		[-] Print("Step 3: Select the “Show legend” again, both the legend and check mark are removed.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowLegend.Uncheck()
			[ ] sleep(2)
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\NoLegend.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for confirming both legend picture and check mark disappear.")
		[-] Print("Step 4: Click the  “Show model status” option.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowModelStatus.Check()
			[ ] sleep(2)
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Circles.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. {chr(10)}"
    +"For rigorous ones, it's blue, for simple ones, it's grey. {chr(10)}"
    +"Make sure the number of the simple models and rigorous models are displayed right on the Model Status panel.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Check4.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for confirming a check mark is displayed in front of the 'Show model status' model.")
		[-] Print("Step 5: Move the mouse hover over E-100, the following flyover should be displayed.")	
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.trvFlowSheet.Select("/Case (Main)")
				[ ] sleep(1)
				[ ] wObjectNavigator.lstUnitOperations.Select("E-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2-10 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgHeatExchanger.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgHeatExchanger.GetDatainFlyover("Heat Exchanger")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetHeatResults("E-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Tube Side Delta T' value is correct.")
				[+] else
					[ ] Log.Fail("'Tube Side Delta T' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Shell Side Delta T' value is correct.")
				[+] else
					[ ] Log.Fail("'Shell Side Delta T' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(Abs(Val(lsDataInFlyover[6])-Val(lsDataActual[6]))/Val(lsDataActual[6])<0.01 && lsDataInFlyover[7]==lsDataActual[7])
					[ ] Log.Pass("'Tube Side Pressure Drop' value is correct.")
				[+] else
					[ ] Log.Fail("'Tube Side Pressure Drop' value is incorrect. Expected: {lsDataActual[6]}{lsDataInFlyover[7]}, In Flyover it's {lsDataInFlyover[6]}{lsDataActual[7]}.")
				[+] if(Abs(Val(lsDataInFlyover[8])-Val(lsDataActual[8]))/Val(lsDataActual[8])<0.01 && lsDataInFlyover[9]==lsDataActual[9])
					[ ] Log.Pass("'Shell Side Pressure Drop' value is correct.")
				[+] else
					[ ] Log.Fail("'Shell Side Pressure Drop' value is incorrect. Expected: {lsDataActual[8]}{lsDataInFlyover[9]}, In Flyover it's {lsDataInFlyover[8]}{lsDataActual[9]}.")
				[+] if(Abs(Val(lsDataInFlyover[10])-Val(lsDataActual[10]))/Val(lsDataActual[10])<0.01 && lsDataInFlyover[11]==lsDataActual[11])
					[ ] Log.Pass("'Duty' value is correct.")
				[+] else
					[ ] Log.Fail("'Duty' value is incorrect. Expected: {lsDataActual[10]}{lsDataInFlyover[11]}, In Flyover it's {lsDataInFlyover[10]}{lsDataActual[11]}.")
			[ ] AH.CloseTab("Heat Exchanger: E-100*")
			[ ] sleep(2)
		[+] Print("Step 6: Move the mouse hover over LNG-100, the following flyover should be displayed.") 
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.trvFlowSheet.Select("/Case (Main)")
				[ ] sleep(1)
				[ ] wObjectNavigator.lstUnitOperations.Select("LNG-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
				[ ] sleep(5)
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgLNG.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgLNG.GetDatainFlyover("LNG")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetLNGResults("LNG-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'LMTD' value is correct.")
				[+] else
					[ ] Log.Fail("'LMTD' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'UA' value is correct.")
				[+] else
					[ ] Log.Fail("'UA' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(Abs(Val(lsDataInFlyover[6])-Val(lsDataActual[6]))/Val(lsDataActual[6])<0.01 && lsDataInFlyover[7]==lsDataActual[7])
					[ ] Log.Pass("'Exchanger Cold Duty' value is correct.")
				[+] else
					[ ] Log.Fail("'Exchanger Cold Duty' value is incorrect. Expected: {lsDataActual[6]}{lsDataInFlyover[7]}, In Flyover it's {lsDataInFlyover[6]}{lsDataActual[7]}.")
				[ ] 
			[ ] AH.CloseTab("LNG: LNG-100*")
			[ ] sleep(2)
		[+] Print("Step 7: Move the mouse hover AC-100, the following flyover should be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.trvFlowSheet.Select("/Case (Main)")
				[ ] sleep(1)
				[ ] wObjectNavigator.lstUnitOperations.Select("AC-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgAirCooler.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgAirCooler.GetDatainFlyover("AC to be Converted")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetACToBeConvertResults("AC-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Process Stream Delta P' value is correct.")
				[+] else
					[ ] Log.Fail("'Process Stream Delta P' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Molar Flow' value is correct.")
				[+] else
					[ ] Log.Fail("'Molar Flow' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
			[ ] AH.CloseTab("Air cooler: AC-100*")
			[ ] sleep(2)
		[+] Print("Step 8: Move the mouse hover FH-100, the following flyover should be displayed.")		
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.trvFlowSheet.Select("/Case (Main)")
				[ ] sleep(1)
				[ ] wObjectNavigator.lstUnitOperations.Select("FH-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgFiredHeater.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgFiredHeater.GetDatainFlyover("FH to be Conveted")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetFHToBeConvertedResults("FH-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Process Stream Delta T' value is correct.")
				[+] else
					[ ] Log.Fail("'Process Stream Delta T' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Pressure Drop' value is correct.")
				[+] else
					[ ] Log.Fail("'Pressure Drop' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(Abs(Val(lsDataInFlyover[6])-Val(lsDataActual[6]))/Val(lsDataActual[6])<0.01 && lsDataInFlyover[7]==lsDataActual[7])
					[ ] Log.Pass("'Duty' value is correct.")
				[+] else
					[ ] Log.Fail("'Duty' value is incorrect. Expected: {lsDataActual[6]}{lsDataInFlyover[7]}, In Flyover it's {lsDataInFlyover[6]}{lsDataActual[7]}.")
				[ ] 
			[ ] AH.CloseTab("Fired Heater: FH-100*")
			[ ] sleep(2)
		[-] Print("Step 9: Move the mouse hover E-101, the following flyover should be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.trvFlowSheet.Select("/Case (Main)")
				[ ] sleep(1)
				[ ] wObjectNavigator.lstUnitOperations.Select("E-101")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-20 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[-] if(wflyover2.dlgShellTube.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgShellTube.GetDatainFlyover("Shell&Tube")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetShellTubeResults("E-101")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(MatchStr("*{lsDataInFlyover[1]}*",lsDataActual[1]))
					[ ] Log.Pass("'Rigorous Model' value is correct.")
				[+] else
					[ ] Log.Fail("'Rigorous Model' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Surface Area' value is correct.")
				[+] else
					[ ] Log.Fail("'Surface Area' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Total Heat Load' value is correct.")
				[+] else
					[ ] Log.Fail("'Total Heat Load' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(lsDataInFlyover[6]==lsDataActual[6])
					[ ] Log.Pass("'TEMA Type' value is correct.")
				[+] else
					[ ] Log.Fail("'TEMA Type' value is incorrect. Expected: {lsDataActual[6]}, In Flyover it's {lsDataInFlyover[6]}.")
				[+] if(Val(lsDataInFlyover[7])==Val(lsDataActual[7]))
					[ ] Log.Pass("'Shells in Series' value is correct.")
				[+] else
					[ ] Log.Fail("'Shells in Series' value is incorrect. Expected: {lsDataActual[7]}, In Flyover it's {lsDataInFlyover[7]}.")
				[+] if(Val(lsDataInFlyover[8])==Val(lsDataActual[8]))
					[ ] Log.Pass("'Shells in Parallel' value is correct.")
				[+] else
					[ ] Log.Fail("'Shells in Parallel' value is incorrect. Expected: {lsDataActual[8]}, In Flyover it's {lsDataInFlyover[8]}.")
			[ ] AH.CloseTab("Heat Exchanger: E-101*")
			[ ] sleep(2)
		[+] Print("Step 10: Move the mouse hover LNG-101, the following flyover should be displayed.") 
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.trvFlowSheet.Select("/Case (Main)")
				[ ] sleep(1)
				[ ] wObjectNavigator.lstUnitOperations.Select("LNG-101")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgPlateFin.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgPlateFin.GetDatainFlyover("PlateFin")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetPlateFinResults("LNG-101")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(MatchStr("*{lsDataInFlyover[1]}*",lsDataActual[1]))
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Total Heat Load' value is correct.")
				[+] else
					[ ] Log.Fail("'Total Heat Load' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(lsDataInFlyover[4]==lsDataActual[4])
					[ ] Log.Pass("'Streams' value is correct.")
				[+] else
					[ ] Log.Fail("'Streams' value is incorrect. Expected: {lsDataActual[4]}, In Flyover it's {lsDataInFlyover[4]}.")
				[+] if(Val(lsDataInFlyover[5])==Val(lsDataActual[5]))
					[ ] Log.Pass("'Exchangers in Parallel' value is correct.")
				[+] else
					[ ] Log.Fail("'Exchangers in Parallel' value is incorrect. Expected: {lsDataActual[5]}, In Flyover it's {lsDataInFlyover[5]}.")
			[ ] AH.CloseTab("LNG: LNG-101*")
			[ ] sleep(2)
		[+] Print("Step 11: Move the mouse hover AC-100-2, the following flyover should be displayed.") 
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.trvFlowSheet.Select("/Case (Main)")
				[ ] sleep(1)
				[ ] wObjectNavigator.lstUnitOperations.Select("AC-100-2")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgAirCooled.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgAirCooled.GetDatainFlyover("Air Cooled")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetACResults("AC-100-2")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(MatchStr("*Simple*",lsDataInFlyover[1])==MatchStr("*Simple*",lsDataActual[1]))
					[ ] Log.Pass("'Rigorous Model' value is correct.")
				[+] else
					[ ] Log.Fail("'Rigorous Model' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Surface Area' value is correct.")
				[+] else
					[ ] Log.Fail("'Surface Area' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Total Heat Load' value is correct.")
				[+] else
					[ ] Log.Fail("'Total Heat Load' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(lsDataInFlyover[6]==lsDataActual[6])
					[ ] Log.Pass("'Fan Configuration' value is correct.")
				[+] else
					[ ] Log.Fail("'Fan Configuration' value is incorrect. Expected: {lsDataActual[6]}, In Flyover it's {lsDataInFlyover[6]}.")
				[+] if(Val(lsDataInFlyover[7])==Val(lsDataActual[7]))
					[ ] Log.Pass("'Bays per Unit' value is correct.")
				[+] else
					[ ] Log.Fail("'Bays per Unit' value is incorrect. Expected: {lsDataActual[7]}, In Flyover it's {lsDataInFlyover[7]}.")
				[+] if(Val(lsDataInFlyover[8])==Val(lsDataActual[8]))
					[ ] Log.Pass("'Bundles per Bay' value is correct.")
				[+] else
					[ ] Log.Fail("'Bundles per Bay' value is incorrect. Expected: {lsDataActual[8]}, In Flyover it's {lsDataInFlyover[8]}.")
				[+] if(Val(lsDataInFlyover[9])==Val(lsDataActual[9]))
					[ ] Log.Pass("'Fans per Bay' value is correct.")
				[+] else
					[ ] Log.Fail("'Fans per Bay' value is incorrect. Expected: {lsDataActual[9]}, In Flyover it's {lsDataInFlyover[9]}.")
			[ ] AH.CloseTab("Air cooler: AC-100-2*")
			[ ] sleep(2)
		[+] Print("Step 12: Move the mouse hover FH-101, the following flyover should be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.trvFlowSheet.Select("/Case (Main)")
				[ ] sleep(1)
				[ ] wObjectNavigator.lstUnitOperations.Select("FH-101")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgFiredHeater.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgFiredHeater.GetDatainFlyover("Fired Heater")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetFiredHeater("FH-101")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(MatchStr("*{lsDataInFlyover[1]}*",lsDataActual[1]))
					[ ] Log.Pass("'Rigorous Model' value is correct.")
				[+] else
					[ ] Log.Fail("'Rigorous Model' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Total Heat Load' value is correct.")
				[+] else
					[ ] Log.Fail("'Total Heat Load' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01)
					[ ] Log.Pass("'Overall Efficiency' value is correct.")
				[+] else
					[ ] Log.Fail("'Overall Efficiency' value is incorrect. Expected: {lsDataActual[4]}, In Flyover it's {lsDataInFlyover[4]}.")
				[+] if(lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Streams' value is correct.")
				[+] else
					[ ] Log.Fail("'Streams' value is incorrect. Expected: {lsDataActual[5]}, In Flyover it's {lsDataInFlyover[5]}.")
				[+] if(lsDataInFlyover[6]==lsDataActual[6])
					[ ] Log.Pass("'Firebox in Unit' value is correct.")
				[+] else
					[ ] Log.Fail("'Firebox in Unit' value is incorrect. Expected: {lsDataActual[6]}, In Flyover it's {lsDataInFlyover[6]}.")
				[+] if(lsDataInFlyover[7]==lsDataActual[7])
					[ ] Log.Pass("'Convection Banks' value is correct.")
				[+] else
					[ ] Log.Fail("'Convection Banks' value is incorrect. Expected: {lsDataActual[7]}, In Flyover it's {lsDataInFlyover[7]}.")
			[ ] AH.CloseTab("Fired Heater: FH-101*")
			[ ] sleep(2)
		[-] Print("Step 13: Click the Exchanger icon on the Activated EDR dashboard and select 'Show model status'")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowModelStatus.Uncheck()
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\NoCircles.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for confirming the highlighted circles are disappeard. ")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\NoCheck.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for confirming the check mark is disappeard in front of the 'Show model status'.")
			[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510226() appstate CleanState	
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510226"
		[ ] sDatain="{sDatain}\Multi HXs"
		[ ] sCaseName="Multi-HXs.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i,j
		[ ] string sBitmapDir
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
		[+] list of string lsPopHeaders2={...}
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] ""
			[ ] ""
			[ ] ""
			[ ] ""
			[ ] "Combustion"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] ""
		[ ] list of string lsDataInFlyover, lsDataActual
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.3.4 Activating EDR activation – Operational Risk Panel")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached Multi-HXs.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] sleep(1)
			[ ] AH.btnGoToParent.Click()
			[ ] sleep(10)
			[+] if(wSubFlowsheet.Exists(5))
				[ ] wSubFlowsheet.SetActive()
				[ ] wSubFlowsheet.Close()
				[ ] sleep(1)
			[+] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] sleep(1)
			[ ] AH.btnGoToParent.Click()
			[ ] sleep(10)
			[+] if(wSubFlowsheet.Exists(5))
				[ ] wSubFlowsheet.SetActive()
				[ ] wSubFlowsheet.Close()
				[ ] sleep(1)
		[-] Print("Step 2: Click the Exchanger icon on the Activated EDR dashboard and select 'Show risk status' option, the following picture will display and a check mark is displayed in front of the option.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowRiskStatus.Check()
			[ ] sleep(2)
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Risk.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. {chr(10)}"
    +"All the exchangers will be encircled in colors according their risk status. {chr(10)}"
    +"Simple models will be encircled in grey; models of OK risk status will be circled in green, warning risk in yellow and serious risk in red. {chr(10)}"
    +"Make sure the numbers of each risk status are displayed right on the Operational Risk panel.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Check.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for confirming the check mark is displayed in front of the 'Show risk status'.")
		[-] Print("Step 3: Move the mouse hover over E-100, the following flyover should be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("E-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2-10 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgHeatExchanger.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgHeatExchanger.GetDatainFlyover("Heat Exchanger")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetHeatResults("E-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Tube Side Delta T' value is correct.")
				[+] else
					[ ] Log.Fail("'Tube Side Delta T' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Shell Side Delta T' value is correct.")
				[+] else
					[ ] Log.Fail("'Shell Side Delta T' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(Abs(Val(lsDataInFlyover[6])-Val(lsDataActual[6]))/Val(lsDataActual[6])<0.01 && lsDataInFlyover[7]==lsDataActual[7])
					[ ] Log.Pass("'Tube Side Pressure Drop' value is correct.")
				[+] else
					[ ] Log.Fail("'Tube Side Pressure Drop' value is incorrect. Expected: {lsDataActual[6]}{lsDataInFlyover[7]}, In Flyover it's {lsDataInFlyover[6]}{lsDataActual[7]}.")
				[+] if(Abs(Val(lsDataInFlyover[8])-Val(lsDataActual[8]))/Val(lsDataActual[8])<0.01 && lsDataInFlyover[9]==lsDataActual[9])
					[ ] Log.Pass("'Shell Side Pressure Drop' value is correct.")
				[+] else
					[ ] Log.Fail("'Shell Side Pressure Drop' value is incorrect. Expected: {lsDataActual[8]}{lsDataInFlyover[9]}, In Flyover it's {lsDataInFlyover[8]}{lsDataActual[9]}.")
				[+] if(Abs(Val(lsDataInFlyover[10])-Val(lsDataActual[10]))/Val(lsDataActual[10])<0.01 && lsDataInFlyover[11]==lsDataActual[11])
					[ ] Log.Pass("'Duty' value is correct.")
				[+] else
					[ ] Log.Fail("'Duty' value is incorrect. Expected: {lsDataActual[10]}{lsDataInFlyover[11]}, In Flyover it's {lsDataInFlyover[10]}{lsDataActual[11]}.")
		[-] Print("Step 4: Move the mouse hover over LNG-100, the following flyover should be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("LNG-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgLNG.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgLNG.GetDatainFlyover("LNG")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetLNGResults("LNG-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'LMTD' value is correct.")
				[+] else
					[ ] Log.Fail("'LMTD' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'UA' value is correct.")
				[+] else
					[ ] Log.Fail("'UA' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(Abs(Val(lsDataInFlyover[6])-Val(lsDataActual[6]))/Val(lsDataActual[6])<0.01 && lsDataInFlyover[7]==lsDataActual[7])
					[ ] Log.Pass("'Exchanger Cold Duty' value is correct.")
				[+] else
					[ ] Log.Fail("'Exchanger Cold Duty' value is incorrect. Expected: {lsDataActual[6]}{lsDataInFlyover[7]}, In Flyover it's {lsDataInFlyover[6]}{lsDataActual[7]}.")
				[ ] 
		[-] Print("Step 5: Move the mouse hover over AC-100, the following flyover should be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("AC-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgAirCooler.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgAirCooler.GetDatainFlyover("AC to be Converted")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetACToBeConvertResults("AC-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Process Stream Delta P' value is correct.")
				[+] else
					[ ] Log.Fail("'Process Stream Delta P' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Molar Flow' value is correct.")
				[+] else
					[ ] Log.Fail("'Molar Flow' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
		[-] Print("Step 6: Move the mouse hover over FH-100, the following flyover should be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("FH-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[-] if(wflyover2.dlgFiredHeater.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgFiredHeater.GetDatainFlyover("FH to be Conveted")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[-] else
				[ ] lsDataActual=AH.GetFHToBeConvertedResults("FH-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Process Stream Delta T' value is correct.")
				[+] else
					[ ] Log.Fail("'Process Stream Delta T' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Pressure Drop' value is correct.")
				[+] else
					[ ] Log.Fail("'Pressure Drop' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(Abs(Val(lsDataInFlyover[6])-Val(lsDataActual[6]))/Val(lsDataActual[6])<0.01 && lsDataInFlyover[7]==lsDataActual[7])
					[ ] Log.Pass("'Duty' value is correct.")
				[+] else
					[ ] Log.Fail("'Duty' value is incorrect. Expected: {lsDataActual[6]}{lsDataInFlyover[7]}, In Flyover it's {lsDataInFlyover[6]}{lsDataActual[7]}.")
				[ ] 
		[-] Print("Step 7: Move the mouse hover over E-101, the following flyover should be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("E-101")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2-20 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgShellTube.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\SortingLogic7.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Pressure; 2)Temperature; 3)Vibration; 4)Erosion rhoV2; 5)Heat Transfer; 6)Pressure Drop; 7)Flow; 8) Other.")
					[ ] //Step 9
					[+] for j=135 to 150
						[ ] wflyover2.dlgShellTube.Click(1,j,10)
						[+] if(wOperationWarnings.Exists(3))
							[ ] Log.Pass("The operation warning box for E-101 pops up.")
							[ ] wOperationWarnings.SetActive()
							[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
							[+] else
								[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
								[ ] ListPrint(lsPopHeaders)
								[ ] Log.Fail("Actual: ")
								[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
							[ ] wOperationWarnings.btnClose.Click()
						[ ] break
					[+] if(j>160)
						[ ] Log.Fail("The operation warning box for LNG-100 does not  pop up as expected.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 8: Click the highlighted traffic button, the operation warning box for E-101 should pop up.")
		[-] Print("Step 9: Move the mouse hover over LNG-101, the following flyover should be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("LNG-101")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgPlateFin.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\SortingLogic9.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Pressure; 2)Temperature; 3)Vibration; 4)Erosion rhoV2; 5)Heat Transfer; 6)Pressure Drop; 7)Flow; 8) Other.")
					[ ] //Step 11
					[+] for j=135 to 150
						[ ] wflyover2.dlgPlateFin.Click(1,j,10)
						[+] if(wOperationWarnings.Exists())
							[ ] Log.Pass("The operation warning box for LNG-101 pops up.")
							[ ] wOperationWarnings.SetActive()
							[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
							[+] else
								[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
								[ ] ListPrint(lsPopHeaders)
								[ ] Log.Fail("Actual: ")
								[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
							[ ] wOperationWarnings.SetActive()
							[ ] wOperationWarnings.btnClose.Click()
						[ ] break
					[+] if(j>160)
						[ ] Log.Fail("The operation warning box for LNG-100 does not  pop up as expected.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 10: Click the highlighted traffic button, the operation warning box for LNG-101 should pop up.")
		[-] Print("Step 11: Move the mouse hover over AC-100-2, the following flyover should be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("AC-100-2")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgAirCooled.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\SortingLogic11.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Pressure; 2)Temperature; 3)Vibration; 4)Erosion rhoV2; 5)Heat Transfer; 6)Pressure Drop; 7)Flow; 8) Other.")
					[ ] //Step 12
					[+] for j=150 to 700
						[ ] wflyover2.dlgAirCooled.Click(1,j,10)
						[+] if(wOperationWarnings.Exists())
							[ ] Log.Pass("The operation warning box for AC-101 pops up.")
							[ ] wOperationWarnings.SetActive()
							[ ] sBitmapDir=Desktop.CaptureBitmap("{sDataout}\Warnings12.bmp")
							[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the warnings.")
							[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
							[+] else
								[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
								[ ] ListPrint(lsPopHeaders)
								[ ] Log.Fail("Actual: ")
								[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
							[ ] wOperationWarnings.SetActive()
							[ ] wOperationWarnings.btnClose.Click()
						[ ] break
					[+] if(j>160)
						[ ] Log.Fail("The operation warning box for LNG-100 does not  pop up as expected.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 12: Click the highlighted traffic button, the operation warning box for AC-100-2 should pop up.")
		[+] Print("Step 13: Move the mouse hover over FH-101, the following flyover should be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("FH-101")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[-] if(wflyover2.dlgFiredHeater.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\SortingLogic13.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Pressure; 2)Temperature; 3)Vibration; 4)Erosion rhoV2; 5)Heat Transfer; 6)Pressure Drop; 7)Flow; 8) Other.")
					[ ] //Step 14
					[-] for j=150 to 700
						[ ] wflyover2.dlgFiredHeater.Click(1,j,10)
						[-] if(wOperationWarnings.Exists())
							[ ] Log.Pass("The operation warning box for FH-101 pops up.")
							[ ] wOperationWarnings.SetActive()
							[ ] sBitmapDir=Desktop.CaptureBitmap("{sDataout}\Warnings14.bmp")
							[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the warnings.")
							[+] if(lsPopHeaders2==GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
							[+] else
								[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
								[ ] ListPrint(lsPopHeaders2)
								[ ] Log.Fail("Actual: ")
								[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
							[ ] wOperationWarnings.SetActive()
							[ ] wOperationWarnings.btnClose.Click()
						[ ] break
					[+] if(j>160)
						[ ] Log.Fail("The operation warning box for LNG-100 does not  pop up as expected.")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 14: Click the highlighted traffic button, the operation warning box for FH-101 should pop up.")
		[ ] 
	[ ] 
[+] testcase CQ00510236() appstate CleanState
	[-] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510236"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[ ] sCaseName="Shell&Tube Simple_V12.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
		[ ] RECT r
	[-] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.1.1 Convert Simple model to Shell&Tube model – Auto Size ")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached Shell&Tube Simple.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the EDR activation button and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[+] if(wConverttoRigorousExchanger.Exists(15))
					[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] //Step 4
					[ ] wConverttoRigorousExchanger.Close()
					[ ] sleep(1)
				[+] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
				[+] if(AH.IsSimpleModel(1))
					[ ] Log.Pass("The simple model is not converted to rigorous model.")
				[+] else
					[ ] Log.Fail("The simple model is converted to rigorous model.")
				[ ] //Step 5
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wConverttoRigorousExchanger.Exists(15))
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] wConverttoRigorousExchanger.btnConvert.Click()
					[ ] sleep(200)
					[-] if(AH.dlgAH.Exists(100))
						[ ] 
						[ ] AH.dlgAH.SetActive()
						[ ] AH.dlgAH.btnYes.Click()
						[ ] sleep(2)
				[-] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
				[ ] //Step 6
				[+] if(AH.IsSimpleModel(1))
					[ ] Log.Fail("The simple model is not converted to rigorous model.")
				[+] else
					[ ] Log.Pass("The simple model is converted to rigorous model.")
				[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1" && AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
					[ ] Log.Pass("The Exchanger Summary table is updated.")
				[-] else
					[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[-] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select the Shell&Tube simple model E-100, click the 'Convert to Rigorous' button on the activated summary table, the Covert to Rigorous Exchanger form will pop up.")
		[ ] Print("Step 4: Click Close button.")
		[ ] Print("Step 5: Click the Convert to Rigorous button again and click Convert with the default setting.")
		[ ] Print("Step 6: The simple model is converted to rigorous model successfully.")
		[ ] 
	[ ] 
[+] testcase CQ00510240() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510240"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[-] list of string lsCaseName={...}
			[ ] "Shell&Tube Simple_V12.hsc"
			[ ] "CS_Floating_Head_US.EDT"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[-] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.1.2 Convert Simple model to Shell&Tube model – Auto Size using Template")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached Shell&Tube Simple.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+lsCaseName[1],50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wConverttoRigorousExchanger.Exists(15))
					[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] //Step 3
					[ ] wConverttoRigorousExchanger.rdbAutoSizeUsingTemplate.Check()
					[ ] sleep(1)
					[-] if(wConverttoRigorousExchanger.txtTemplate.IsEnabled)
						[ ] Log.Pass("The Select a Template File for sizing text box is active.")
					[-] else
						[ ] Log.Fail("The Select a Template File for sizing text box is inactive.")
					[ ] wConverttoRigorousExchanger.btnTemplateBrowse.Click()
					[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
						[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.Click()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.SetText("{sDataout}\{lsCaseName[2]}")
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[ ] sleep(1)
					[+] else
						[ ] Log.Fail("Open window does not pop up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] wConverttoRigorousExchanger.btnConvert.Click()
					[ ] sleep(20) 
					[+] if(AH.dlgAH.Exists(100))
						[ ] 
						[ ] AH.dlgAH.SetActive()
						[ ] AH.dlgAH.btnYes.Click()
						[ ] sleep(2)
				[-] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
				[ ] //Step 6
				[-] if(AH.IsSimpleModel(1))
					[ ] Log.Fail("The simple model is not converted to rigorous model.")
				[-] else
					[ ] Log.Pass("The simple model is converted to rigorous model.")
				[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1" && AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
					[ ] Log.Pass("The Exchanger Summary table is updated.")
				[-] else
					[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select the Shell&Tube simple model E-100, click the 'Convert to Rigorous' button on the activated summary table, the Covert form will pop up.")
		[ ] Print("Step 4: Select Auto Size using Template in the Size Exchanger area..")
		[ ] Print("Step 5: Browse to the attached templated file CS_Floating_Head_US.EDT and click Convert button.")
		[ ] Print("Step 6: The simple model is converted to rigorous model successfully.")
		[ ] 
	[ ] 
[+] testcase CQ00510242() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510242"
		[ ] sDatain="{sDatain}\CQ00510242"
		[ ] sCaseName="Shell&Tube Simple_V12.HSC"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[-] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.1.3 Convert Simple model to Shell&Tube model – Size Interactively")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached Shell&Tube Simple.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wConverttoRigorousExchanger.Exists(15))
					[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] //Step 4
					[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Check()
					[ ] sleep(1)
					[ ] //Step 5
					[ ] wConverttoRigorousExchanger.btnConvert.Click()
					[-] if(wEDRSizingConsole.Exists(100))
						[ ] wEDRSizingConsole.SetActive()
						[ ] //Step 6
						[ ] wEDRSizingConsole.btnSize.Click()
						[ ] sleep(300)
						[ ] wEDRSizingConsole.btnCancel.Click()
						[-] if(wEDRSizingConsole.dlgCancel.Exists(20))
							[ ] wEDRSizingConsole.dlgCancel.SetActive()
							[ ] wEDRSizingConsole.dlgCancel.btnYes.Click()
							[ ] sleep(2)
					[-] else
						[ ] Log.Fail("EDR Sizing Console window does not pop up.")
				[-] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
			[-] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select the Shell&Tube simple model E-100, click the 'Convert to Rigorous' button on the activated summary table, the Covert to Rigorous Exchanger form will pop up.")
		[ ] Print("Step 4: Select Size Interactively in the Size Exchanger area.")
		[ ] Print("Step 5: Click Convert button, the EDR Sizing Console dialog will pop up.")
		[+] Print("Step 6: Click Size button and then click Cancel button")
			[+] if(AH.IsSimpleModel(1))
				[ ] Log.Pass("The simple model is not converted to rigorous model.")
			[+] else
				[ ] Log.Fail("The simple model is converted to rigorous model.")
		[-] Print("Step 7: Repeat 3-6 and click Accept Design on the EDR Sizing Console dialog.")
			[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
			[-] if(wConverttoRigorousExchanger.Exists(15))
				[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
				[ ] wConverttoRigorousExchanger.SetActive()
				[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Check()
				[ ] sleep(1)
				[ ] wConverttoRigorousExchanger.btnConvert.Click()
				[-] if(wEDRSizingConsole.Exists(100))
					[ ] wEDRSizingConsole.SetActive()
					[ ] wEDRSizingConsole.btnSize.Click()
					[ ] sleep(300)
					[ ] wEDRSizingConsole.btnAcceptDesign.Click()
					[+] if(AH.dlgAH.Exists(100))
						[ ] 
						[ ] AH.dlgAH.SetActive()
						[ ] AH.dlgAH.btnYes.Click()
						[ ] sleep(2)
				[+] else
					[ ] Log.Fail("EDR Sizing Console window does not pop up.")
			[+] else
				[ ] Log.Fail("Convert to Rigorous window does not pop up.")
			[+] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The simple model is not converted to rigorous model.")
			[+] else
				[ ] Log.Pass("The simple model is converted to rigorous model.")
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1" && AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[-] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[ ] 
		[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510244() appstate CleanState
	[-] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510244"
		[ ] sDatain="{sDatain}\CQ00510240"
		[-] list of string lsCaseName={...}
			[ ] "Shell&Tube Simple_V12.hsc"
			[ ] "CS_Floating_Head_US.EDT"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[-] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.1.4 Convert Simple model to Shell&Tube model – Size Interactively with Template")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached Shell&Tube Simple.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+lsCaseName[1],50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[+] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[+] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[+] if(wConverttoRigorousExchanger.Exists(15))
					[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] //Step 4
					[ ] wConverttoRigorousExchanger.rdbSizeInteractivelyUsingTemplate.Check()
					[ ] sleep(1)
					[+] if(wConverttoRigorousExchanger.txtTemplate.IsEnabled)
						[ ] Log.Pass("The Select a Template File for sizing text box is active.")
					[+] else
						[ ] Log.Fail("The Select a Template File for sizing text box is inactive.")
					[ ] //Step 5
					[ ] wConverttoRigorousExchanger.btnTemplateBrowse.Click()
					[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
						[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.Click()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.SetText("{sDataout}\{lsCaseName[2]}")
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[ ] sleep(1)
					[+] else
						[ ] Log.Fail("Open window does not pop up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] wConverttoRigorousExchanger.btnConvert.Click()
					[+] if(wEDRSizingConsole.Exists(100))
						[ ] wEDRSizingConsole.SetActive()
						[ ] wEDRSizingConsole.btnSize.Click()
						[ ] sleep(100)
						[ ] wEDRSizingConsole.btnAcceptDesign.Click()
						[+] if(AH.dlgAH.Exists(100))
							[ ] 
							[ ] AH.dlgAH.SetActive()
							[ ] AH.dlgAH.btnYes.Click()
							[ ] sleep(2)
					[+] else
						[ ] Log.Fail("EDR Sizing Console window does not pop up.")
				[+] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select the Shell&Tube simple model E-100, click the 'Convert to Rigorous' button on the activated summary table, the Covert to Rigorous Exchanger form will pop up.")
		[ ] Print("Step 4: Select Size Interactively using Template in the Size Exchanger area.")
		[ ] Print("Step 5: Browse to the attached templated file CS_Floating_Head_US.EDT and click Convert button.")
		[-] Print("Step 6: Click Size Exchanger and Accept Design")
			[-] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The simple model is not converted to rigorous model.")
			[-] else
				[ ] Log.Pass("The simple model is converted to rigorous model.")
			[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[-] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[-] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[-] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510245() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510245"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[-] list of string lsCaseName={...}
			[ ] "HYSYS_Tasc.hsc"
			[ ] "QTASC1.EDR"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
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
		[ ] Print("4.4.1.5 Convert Simple model to Shell&Tube model – Import EDR File")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached Shell&Tube Simple.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+lsCaseName[1],50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[+] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[+] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[+] if(wConverttoRigorousExchanger.Exists(15))
					[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] //Step 4
					[ ] wConverttoRigorousExchanger.rdbSpecifyExchangerGeometry.Check()
					[ ] sleep(1)
					[ ] //Step 5
					[ ] wConverttoRigorousExchanger.rdbImportEDRFile.Check()
					[ ] sleep(1)
					[+] if(wConverttoRigorousExchanger.txtImport.IsEnabled)
						[ ] Log.Pass("The Import EDR File text box is active.")
					[+] else
						[ ] Log.Fail("The Import EDR File text box is inactive.")
					[ ] wConverttoRigorousExchanger.btnImportBrowse.Click()
					[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
						[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.Click()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.SetText("{sDataout}\{lsCaseName[2]}")
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[ ] sleep(1)
					[+] else
						[ ] Log.Fail("Open window does not pop up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] wConverttoRigorousExchanger.btnConvert.Click()
					[ ] sleep(2)
				[+] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select the Shell&Tube simple model E-100, click the 'Convert to Rigorous' button on the activated summary table, the Covert to Rigorous Exchanger form will pop up.")
		[ ] Print("Step 4: Select Specify Exchanger Geometry option for Select Conversion Method.")
		[ ] Print("Step 5: Select Import EDR File in the Specify Exchanger Geometry area.")
		[-] Print("Step 6: Browse to the attached import file QTASC1.EDR and click Convert button.")
			[-] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The simple model is not converted to rigorous model.")
			[-] else
				[ ] Log.Pass("The simple model is converted to rigorous model.")
			[-] if (AH.ExpandTheDashboardButton.Exists() == true)
				[ ] AH.ExpandTheDashboardButton.Select()  //chen
				[ ] sleep(0.5)
			[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[ ] 
		[ ] 
	[ ] 
[ ] 
[+] testcase CQ00510248() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510248"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[ ] sCaseName="ACOL Simple.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
		[ ] RECT r
	[-] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.2.1 Convert Simple model to AirCooled model – Auto Size")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached ACOL Simple.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wConverttoRigorousExchanger.Exists(15))
					[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] //Step 4
					[ ] wConverttoRigorousExchanger.Close()
					[ ] sleep(1)
				[-] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
				[-] if(AH.IsSimpleModel(1))
					[ ] Log.Pass("The simple model is not converted to rigorous model.")
				[-] else
					[ ] Log.Fail("The simple model is converted to rigorous model.")
				[ ] //Step 5
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wConverttoRigorousExchanger.Exists(15))
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] wConverttoRigorousExchanger.btnConvert.Click()
					[ ] sleep(100)
					[-] if(AH.dlgAH.Exists(400))
						[ ] 
						[ ] AH.dlgAH.SetActive()
						[ ] AH.dlgAH.btnYes.Click()
						[ ] sleep(2)
				[+] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
				[ ] //Step 6
				[-] if(AH.IsSimpleModel(1))
					[ ] Log.Fail("The simple model is not converted to rigorous model.")
				[-] else
					[ ] Log.Pass("The simple model is converted to rigorous model.")
				[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1" && AH.ctrlEDRDashboard.ctrlOK.TextCapture()=="0")
					[ ] Log.Pass("The simple model and rigorous number in the EDR dashboard are updated..")
				[-] else
					[ ] Log.Fail("The simple model and rigorous number in the EDR dashboard are not updated..")
				[-] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
					[ ] Log.Pass("The Exchanger Summary table is updated.")
				[-] else
					[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[-] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select the AirCooled simple model AC-100, click the 'Convert to Rigorous' button on the activated summary table, the Covert form will pop up.")
		[ ] Print("Step 4: Click Close button")
		[ ] Print("Step 5: Click the Convert to Rigorous button again and click Convert with the default setting..")
		[ ] Print("Step 6: Click the simple button again and click Convert.")
		[ ] 
	[ ] 
[+] testcase CQ00510249() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510249"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[+] list of string lsCaseName={...}
			[ ] "ACOL Simple.hsc"
			[ ] "CS_Air_Cooled_SI.EDT"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.2.2 Convert Simple model to AirCooled model – Auto Size using Template")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached ACOL Simple.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+lsCaseName[1],50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wConverttoRigorousExchanger.Exists(15))
					[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] //Step 3
					[ ] wConverttoRigorousExchanger.rdbAutoSizeUsingTemplate.Check()
					[ ] sleep(1)
					[-] if(wConverttoRigorousExchanger.txtTemplate.IsEnabled)
						[ ] Log.Pass("The Select a Template File for sizing text box is active.")
					[-] else
						[ ] Log.Fail("The Select a Template File for sizing text box is inactive.")
					[ ] wConverttoRigorousExchanger.btnTemplateBrowse.Click()
					[-] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
						[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.Click()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.SetText("{sDataout}\{lsCaseName[2]}")
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[ ] sleep(1)
					[+] else
						[ ] Log.Fail("Open window does not pop up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] wConverttoRigorousExchanger.btnConvert.Click()
					[ ] sleep(300)
					[+] if(wAspenHysys.Exists(100))
						[ ] wAspenHysys.SetActive()
						[ ] wAspenHysys.btnOK.Click()
						[ ] 
				[+] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
				[ ] //Step 6
				[-] if(AH.IsSimpleModel(1))
					[ ] Log.Fail("The simple model is not converted to rigorous model.")
				[+] else
					[ ] Log.Pass("The simple model is converted to rigorous model.")
				[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1" && AH.ctrlEDRDashboard.ctrlOK.TextCapture()=="0")
					[ ] Log.Pass("The simple model and rigorous number in the EDR dashboard are updated..")
				[+] else
					[ ] Log.Fail("The simple model and rigorous number in the EDR dashboard are not updated..")
				[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
					[ ] Log.Pass("The Exchanger Summary table is updated.")
				[+] else
					[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select the AirCooled simple model AC-100, click the 'Convert to Rigorous' button on the activated summary table, the Covert form will pop up.")
		[ ] Print("Step 4: Select Auto Size using Template in the Select Sizing Method and click convert.")
		[ ] Print("Step 5: Browse to the attached CS_Air_Cooled_SI.EDT template file and click Convert button.")
		[ ] 
	[ ] 
[+] testcase CQ00510252() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510252"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[ ] sCaseName="ACOL Simple.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.2.3 Convert Simple model to AirCooled model – Size Interactively")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached ACOL Simple.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Activated EDR dashboard and and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wConverttoRigorousExchanger.Exists(15))
					[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] //Step 4
					[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Check()
					[ ] sleep(1)
					[ ] //Step 5
					[ ] wConverttoRigorousExchanger.btnConvert.Click()
					[ ] //sleep(150)
					[-] if(wEDRSizingConsole.Exists(100))
						[ ] wEDRSizingConsole.SetActive()
						[ ] //Step 6
						[ ] wEDRSizingConsole.btnSize.Click()
						[ ] sleep(500)
						[ ] wEDRSizingConsole.btnCancel.Click()
						[+] if(wEDRSizingConsole.dlgCancel.Exists(20))
							[ ] wEDRSizingConsole.dlgCancel.SetActive()
							[ ] wEDRSizingConsole.dlgCancel.btnYes.Click()
							[ ] sleep(2)
					[+] else
						[ ] Log.Fail("EDR Sizing Console window does not pop up.")
				[+] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select the AirCooled simple model AC-100, click the 'Convert to Rigorous' button on the activated summary table, the Covert form will pop up.")
		[ ] Print("Step 4: Select Size Interactively in the Size Exchanger area.")
		[ ] Print("Step 5: Click Convert button, the EDR Sizing Console dialog will pop up.")
		[+] Print("Step 6: Click Size Exchanger button and then click Cancel button.")
			[+] if(AH.IsSimpleModel(1))
				[ ] Log.Pass("The simple model is not converted to rigorous model.")
			[+] else
				[ ] Log.Fail("The simple model is converted to rigorous model.")
		[-] Print("Step 7: Close the case and repeat 1-6 and click Accept Design on the EDR Sizing Console dialog.")
			[ ] AH.SetActive()
			[ ] AH.CloseCase()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[ ] ExpandNaviPane()
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wConverttoRigorousExchanger.Exists(15))
					[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] wConverttoRigorousExchanger.rdbSizeInteractively.Check()
					[ ] sleep(1)
					[ ] wConverttoRigorousExchanger.btnConvert.Click()
					[ ] sleep(100)
					[-] if(wEDRSizingConsole.Exists(100))
						[ ] wEDRSizingConsole.SetActive()
						[ ] wEDRSizingConsole.btnSize.Click()
						[ ] sleep(500)
						[ ] wEDRSizingConsole.btnAcceptDesign.Click()
						[+] if(wAspenHysys.Exists(100))
							[ ] wAspenHysys.SetActive()
							[ ] wAspenHysys.btnOK.Click()
							[ ] sleep(2)
					[+] else
						[ ] Log.Fail("EDR Sizing Console window does not pop up.")
				[+] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[+] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The simple model is not converted to rigorous model.")
			[+] else
				[ ] Log.Pass("The simple model is converted to rigorous model.")
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1" && AH.ctrlEDRDashboard.ctrlOK.TextCapture()=="0")
				[ ] Log.Pass("The simple model and rigorous number in the EDR dashboard are updated..")
			[+] else
				[ ] Log.Fail("The simple model and rigorous number in the EDR dashboard are not updated..")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510254() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510254"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[+] list of string lsCaseName={...}
			[ ] "ACOL Simple.hsc"
			[ ] "CS_Air_Cooled_SI.EDT"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.2.4 Convert Simple model to EDR rigorous model – Size Interactively with Template")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached ACOL Simple.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+lsCaseName[1],50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wConverttoRigorousExchanger.Exists(15))
					[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] //Step 4
					[ ] wConverttoRigorousExchanger.rdbSizeInteractivelyUsingTemplate.Check()
					[ ] sleep(1)
					[+] if(wConverttoRigorousExchanger.txtTemplate.IsEnabled)
						[ ] Log.Pass("The Select a Template File for sizing text box is active.")
					[+] else
						[ ] Log.Fail("The Select a Template File for sizing text box is inactive.")
					[ ] //Step 5
					[ ] wConverttoRigorousExchanger.btnTemplateBrowse.Click()
					[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
						[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.Click()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.SetText("{sDataout}\{lsCaseName[2]}")
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[ ] sleep(1)
					[+] else
						[ ] Log.Fail("Open window does not pop up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] wConverttoRigorousExchanger.btnConvert.Click()
					[-] if(wEDRSizingConsole.Exists(100))
						[ ] wEDRSizingConsole.SetActive()
						[ ] //Step 6
						[ ] wEDRSizingConsole.btnSize.Click()
						[ ] sleep(500)
						[ ] wEDRSizingConsole.btnAcceptDesign.Click()
						[+] if(wAspenHysys.Exists(100))
							[ ] wAspenHysys.SetActive()
							[ ] wAspenHysys.btnOK.Click()
							[ ] sleep(5)
					[+] else
						[ ] Log.Fail("EDR Sizing Console window does not pop up.")
				[+] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select the AirCooled simple model AC-100, click the 'Convert to Rigorous' button on the activated summary table, the Covert form will pop up.")
		[ ] Print("Step 4: Select Size Interactively using Template in the Select Sizing Method.")
		[ ] Print("Step 5: Browse to the attached CS_Air_Cooled_SI.EDT template file and click Convert button.")
		[-] Print("Step 6: Click Size Exchanger button and then click Accept Design button.")
			[-] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The simple model is not converted to rigorous model.")
			[+] else
				[ ] Log.Pass("The simple model is converted to rigorous model.")
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
		[ ] 
	[ ] 
[+] testcase CQ00510255() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510255"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[-] list of string lsCaseName={...}
			[ ] "HYSYS_Acol_V12.hsc"
			[ ] "QACOL9.EDR"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
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
		[ ] Print("4.4.2.5 Convert Simple model to AirCooled model – Import EDR File")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached HYSYS_Acol.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+lsCaseName[1],50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[+] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[+] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[+] if(wConverttoRigorousExchanger.Exists(15))
					[ ] Log.Pass("The Convert to Rigorous Exchanger form pops up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] //Step 4
					[ ] wConverttoRigorousExchanger.rdbSpecifyExchangerGeometry.Check()
					[ ] sleep(1)
					[ ] //Step 5
					[ ] wConverttoRigorousExchanger.rdbImportEDRFile.Check()
					[ ] sleep(1)
					[+] if(wConverttoRigorousExchanger.txtImport.IsEnabled)
						[ ] Log.Pass("The Import EDR File text box is active.")
					[+] else
						[ ] Log.Fail("The Import EDR File text box is inactive.")
					[ ] wConverttoRigorousExchanger.btnImportBrowse.Click()
					[+] if(wConverttoRigorousExchanger.dlgOpen.Exists(10))
						[ ] wConverttoRigorousExchanger.dlgOpen.SetActive()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.Click()
						[ ] wConverttoRigorousExchanger.dlgOpen.cboFileName.SetText("{sDataout}\{lsCaseName[2]}")
						[ ] sleep(1)
						[ ] wConverttoRigorousExchanger.dlgOpen.btnOpen.Click()
						[ ] sleep(1)
					[+] else
						[ ] Log.Fail("Open window does not pop up.")
					[ ] wConverttoRigorousExchanger.SetActive()
					[ ] wConverttoRigorousExchanger.btnConvert.Click()
					[ ] sleep(2)
				[+] else
					[ ] Log.Fail("Convert to Rigorous window does not pop up.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select the AirCooled simple model AC-100, click the 'Convert to Rigorous' button on the activated summary table, the Covert form will pop up.")
		[ ] Print("Step 4: Select Specify Exchanger Geometry option for Select Conversion Method.")
		[-] Print("Step 5: Browse to the attached import file QACOL9.EDR and click Convert button.")
			[+] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The simple model is not converted to rigorous model.")
			[+] else
				[ ] Log.Pass("The simple model is converted to rigorous model.")
			[-] if (AH.ExpandTheDashboardButton.Exists() == true)
				[ ] AH.ExpandTheDashboardButton.Select()  //chen
				[ ] sleep(0.5)
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
		[ ] 
	[ ] 
[+] testcase CQ00510258() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510258"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[-] list of string lsCaseName={...}
			[ ] "HYSYS_PlateFin_V12.hsc"
			[ ] "PFsimple crossflow.EDR"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[-] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.3.1 Convert Simple model to PlateFin model")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached HYSYS_PlateFin.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+lsCaseName[1],50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wEDRConvert.Exists(10))
					[ ] Log.Pass("Convert window is displayed on top of the form")
					[ ] //Step 4
					[ ] wEDRConvert.SetActive()
					[ ] wEDRConvert.Close()
				[-] else
					[ ] Log.Fail("Convert window does not pop up.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select the PlateFin simple model LNG-100; click the 'Convert to Rigorous' button on the Activated Summary table.")
		[ ] Print("Step 4: Click Close button.")
		[-] Print("Step 5: Repeat step 3 and click Convert.")
			[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
			[-] if(wEDRConvert.Exists(10))
				[ ] wEDRConvert.SetActive()
				[ ] wEDRConvert.btnConvert.Click()
				[-] if(wLNG.Exists(20))
					[ ] wLNG.SetActive()
					[ ] wLNG.lbParameters.Click()
					[+] if(MatchStr("Simple*",wLNG.tpgDesign.dgRatingMethod.Find("//WPFDataGridCell[2]").TextCapture()))
						[ ] Log.Pass("The HYSYS LNG exchanger form opens with the Design tab-Parameters ply.")
					[+] else
						[ ] Log.Fail("The HYSYS LNG exchanger form opens with the Design tab-Parameters ply.")
					[ ] //Step 6
					[ ] wLNG.tpgDesign.dgRatingMethod.Find("//WPFDataGridCell[2]").Click()
					[ ] Desktop.TypeKeys("<Backspace>",1)
					[ ] wLNG.cboComboBox.Select("EDR - PlateFin")
					[ ] sleep(2)
					[ ] //Step 7
					[ ] wLNG.SetTab("EDR PlateFin")
					[ ] sleep(1)
					[ ] wLNG.tpgEDRPlateFin.btnImport.Click()
					[+] if(wLNG.wImportGeometryFromFile.Exists(10))
						[ ] wLNG.wImportGeometryFromFile.SetActive()
						[ ] wLNG.wImportGeometryFromFile.txtFileName.Click()
						[ ] wLNG.wImportGeometryFromFile.txtFileName.TypeKeys(sDataout+"\"+lsCaseName[2])
						[ ] sleep(1)
						[ ] wLNG.wImportGeometryFromFile.btnOpen.Click()
						[ ] sleep(1)
					[+] else
						[ ] Log.Fail("Import window does not pop up.")
					[ ] wLNG.SetActive()
					[ ] wLNG.tpgEDRPlateFin.dgEDR.Find("/WPFDataGridRow[1]//WPFDataGridCell[2]").Click()
					[ ] Desktop.TypeKeys("<Backspace>",1)
					[ ] Desktop.TypeKeys("<Down><Enter>",1)
					[ ] wLNG.tpgEDRPlateFin.dgEDR.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
					[ ] Desktop.TypeKeys("<Backspace>",1)
					[ ] Desktop.TypeKeys("<Down 2><Enter>",8)
					[ ] wLNG.SetActive()
					[ ] wLNG.Close()
				[+] else
					[ ] Log.Fail("The HYSYS LNG exchanger form does not open.")
			[-] else
				[ ] Log.Fail("Convert window does not pop up.")
		[ ] Print("Step 6: Select 'EDR-PlateFin' from the Rating Method dropdown box.")
		[ ] Print("Step 7. Go to EDR PlateFin tab and then click the Import button to import the attached PFsimple crossflow.EDR Platefin model.")
		[-] Print("Step 8. Map the streams in HYSYS to the correct LNG Pass Name. In this case, HInlet-HOutlet for Stream 1 and CInlet-COutlet for Stream 2.")
			[+] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The simple model is not converted to rigorous model.")
			[+] else
				[ ] Log.Pass("The simple model is converted to rigorous model.")
			[-] if (AH.ExpandTheDashboardButton.Exists() == true)
				[ ] AH.ExpandTheDashboardButton.Select()  //chen
				[ ] sleep(0.5)
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlOK.TextCapture()=="1")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510260() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510260"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[+] list of string lsCaseName={...}
			[ ] "HYSYS_FH Simple.hsc"
			[ ] "QFiredHeater1.EDR"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.4.4.1 Convert Simple model to FiredHeater model")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached HYSYS_FH.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+lsCaseName[1],50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wEDRConvert.Exists(10))
					[ ] Log.Pass("Convert window is displayed on top of the form")
					[ ] //Step 4
					[ ] wEDRConvert.SetActive()
					[ ] wEDRConvert.Close()
				[-] else
					[ ] Log.Fail("Convert window does not pop up.")
			[-] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select a FiredHeater simple model; click the 'Convert to Rigorous' button on the Activated Summary table.")
		[ ] Print("Step 4: Click Close button.")
		[-] Print("Step 5: Repeat step 3 and click Convert.")
			[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
			[-] if(wEDRConvert.Exists(10))
				[ ] wEDRConvert.SetActive()
				[ ] wEDRConvert.btnConvert.Click()
				[+] if(wFiredHeater.Exists(10))
					[ ] wFiredHeater.SetActive()
					[+] if(MatchStr("Simple*",wFiredHeater.cboSteadyStateModel.TextCapture()))
						[ ] Log.Pass("The HYSYS FiredHeater form opens with the Design tab-Parameters ply.")
					[+] else
						[ ] Log.Fail("The HYSYS FiredHeater form opens with the Design tab-Parameters ply.")
					[ ] wFiredHeater.cboSteadyStateModel.Select("EDR - FiredHeater")
					[ ] sleep(2)
					[ ] //Step 6
					[ ] wFiredHeater.SetTab("EDR FiredHeater")
					[ ] sleep(1)
					[ ] wFiredHeater.btnImport.Click()
					[-] if(wFiredHeater.wImportGeometryFromFile.Exists(20))
						[ ] wFiredHeater.wImportGeometryFromFile.SetActive()
						[ ] wFiredHeater.wImportGeometryFromFile.txtFileName.Click()
						[ ] wFiredHeater.wImportGeometryFromFile.txtFileName.TypeKeys(sDataout+"\"+lsCaseName[2])
						[ ] sleep(1)
						[ ] wFiredHeater.wImportGeometryFromFile.btnOpen.Click()
						[ ] sleep(10)
					[-] else
						[ ] Log.Fail("Import window does not pop up.")
					[ ] wFiredHeater.SetActive()
					[ ] wFiredHeater.Close()
				[-] else
					[ ] Log.Fail("The HYSYS FiredHeater form opens.")
			[+] else
				[ ] Log.Fail("Convert window does not pop up.")
		[+] Print("Step 6: Go to EDR FiredHeter tab and then click the Import button to import the attached QFiredHeater1.EDR FiredHeater file.Go to Worksheet tab-Conditions ply, delete the Air Mass Flow value if the consistency error pop up and change the Solver to Active.")
			[+] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The simple model is not converted to rigorous model.")
			[+] else
				[ ] Log.Pass("The simple model is converted to rigorous model.")
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[ ] 
			[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510262() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510262"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[ ] sCaseName="Tasc_rig.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[+] // Case script
		[ ] Print("4.5.1.1 Convert Shell&Tube model to Simple model – First Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached Tasc_rig.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[+] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[+] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[+] if(wRevertTo.Exists(10))
					[ ] Log.Pass("Pop-up message displays on top of the form as expected.")
					[ ] wRevertTo.SetActive()
					[ ] wRevertTo.Close()
				[+] else
					[ ] Log.Fail("Pop-up message does not display on top of the form as expected.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select a Shell&Tube model, e.g. E-100; click the Revert to Simple button on the Activated Summary table.")
		[ ] Print("Step 4: Click Close")
		[+] Print("Step 5: Repeat step 3 and click Revert button with the default selection option.")
			[ ] AH.SetActive()
			[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
			[+] if(wRevertTo.Exists(10))
				[ ] Log.Pass("Pop-up message displays on top of the form as expected.")
				[ ] wRevertTo.SetActive()
				[ ] wRevertTo.btnRevert.Click()
				[+] if(wHeatExchanger.Exists(10))
					[ ] wHeatExchanger.SetActive()
					[+] if(wHeatExchanger.tpgDesign.cboHeatExchangerModel.Exists(5))
						[ ] Log.Pass("The HYSYS Shell&Tube form opens automatically with the Design tab-Parameters ply.")
						[+] if(wHeatExchanger.tpgDesign.cboHeatExchangerModel.TextCapture()=="Simple End Point")
							[ ] Log.Pass("The Heat Exchanger Model is changed to Simple End Point.")
						[+] else
							[ ] Log.Fail("The Heat Exchanger Model is not changed to Simple End Point.")
					[+] else
						[ ] Log.Fail("The HYSYS Shell&Tube form does not open automatically with the Design tab-Parameters ply.")
					[ ] wHeatExchanger.Close()
				[+] else
					[ ] Log.Fail("The HYSYS Shell&Tube form does not open with the Design tab-Parameters ply.")
			[+] else
				[ ] Log.Fail("Pop-up message does not display on top of the form as expected.")
			[+] if(!AH.IsSimpleModel(1))
				[ ] Log.Fail("The simple model is not reverted to simple model.")
			[+] else
				[ ] Log.Pass("The simple model is reverted to simple model.")
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[ ] 
		[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510263() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510263"
		[ ] sDatain="{sDatain}\CQ00510262"
		[ ] sCaseName="Tasc_rig.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[+] // Case script
		[ ] Print("4.5.1.2 Convert Shell&Tube model to Simple model – Second Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached Tasc_rig.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Activated EDR dashboard  and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wRevertTo.Exists(10))
					[ ] Log.Pass("Pop-up message displays on top of the form as expected.")
					[ ] wRevertTo.SetActive()
					[ ] wRevertTo.rdbWithOriginalSpecs.Check()
					[ ] sleep(1)
					[ ] wRevertTo.btnRevert.Click()
					[-] if(AH.dlgAH.Exists(100))
						[ ] 
					[-] else
						[ ] Log.Fail("Confirm dialog does not pop up.")
					[-] if(wHeatExchanger.Exists(10))
						[ ] wHeatExchanger.SetActive()
						[ ] wHeatExchanger.Close()
				[-] else
					[ ] Log.Fail("Pop-up message does not display on top of the form as expected.")
			[-] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select a Shell&Tube model, e.g. E-100; click the Revert to Simple button on the Activated Summary table.")
		[ ] Print("Step 4: Select End Point with Original Specs option and Click Revert.")
		[+] Print("Step 5: Click No.")
			[ ] AH.dlgAH.SetActive()
			[ ] AH.dlgAH.btnNo.Click()
			[ ] sleep(2)
			[ ] 
			[-] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The simple model is reverted to simple model.")
			[-] else
				[ ] Log.Pass("The simple model is not reverted to simple model.")
		[+] Print("Step 6: Repeat step 2-4, click Yes on the pop up dialog.")
			[ ] AH.SetActive()
			[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
			[-] if(wRevertTo.Exists(10))
				[ ] Log.Pass("Pop-up message displays on top of the form as expected.")
				[ ] wRevertTo.SetActive()
				[ ] wRevertTo.rdbWithOriginalSpecs.Check()
				[ ] sleep(1)
				[ ] wRevertTo.btnRevert.Click()
				[-] if(AH.dlgAH.Exists(10))
					[ ] AH.dlgAH.SetActive()
					[ ] AH.dlgAH.btnYes.Click()
				[-] else
					[ ] Log.Fail("Confirm dialog does not pop up.")
				[-] if(wHeatExchanger.Exists(10))
					[ ] wHeatExchanger.SetActive()
					[-] if(wHeatExchanger.tpgDesign.cboHeatExchangerModel.Exists(5))
						[ ] Log.Pass("The HYSYS Shell&Tube form opens automatically with the Design tab-Parameters ply.")
						[-] if(wHeatExchanger.tpgDesign.cboHeatExchangerModel.TextCapture()=="Simple End Point")
							[ ] Log.Pass("The Heat Exchanger Model is changed to Simple End Point.")
						[-] else
							[ ] Log.Fail("The Heat Exchanger Model is not changed to Simple End Point.")
					[-] else
						[ ] Log.Fail("The HYSYS Shell&Tube form does not open automatically with the Design tab-Parameters ply.")
					[ ] wHeatExchanger.Close()
				[+] else
					[ ] Log.Fail("The HYSYS Shell&Tube form does not open with the Design tab-Parameters ply.")
			[+] else
				[ ] Log.Fail("Pop-up message does not display on top of the form as expected.")
			[+] if(!AH.IsSimpleModel(1))
				[ ] Log.Fail("The simple model is not reverted to simple model.")
			[-] else
				[ ] Log.Pass("The simple model is reverted to simple model.")
				[ ] sleep(1)
			[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="2" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[-] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[-] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[ ] 
		[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510264() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510264"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[ ] sCaseName="Rigorous AirCooler.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[+] // Case script
		[ ] Print("4.5.2.1 Convert AirCooled model to Simple model – First Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached Rigorous Aircooler.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[+] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[+] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[+] if(wRevertTo.Exists(10))
					[ ] Log.Pass("Pop-up message displays on top of the form as expected.")
					[ ] wRevertTo.SetActive()
					[ ] wRevertTo.Close()
				[+] else
					[ ] Log.Fail("Pop-up message does not display on top of the form as expected.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select an AirCooled model; click the Revert to Simple button on the Activated Summary table.")
		[+] Print("Step 4: Click Close.")
			[+] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The rigorous model is reverted to simple model.")
			[+] else
				[ ] Log.Pass("The rigorous model is not reverted to simple model.")
		[+] Print("Step 5: Repeat step 3, click Revert with the default select option.")
			[ ] AH.SetActive()
			[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
			[+] if(wRevertTo.Exists(10))
				[ ] Log.Pass("Pop-up message displays on top of the form as expected.")
				[ ] wRevertTo.SetActive()
				[ ] wRevertTo.btnRevert.Click()
				[+] if(wAirCoolerEDR.Exists(10))
					[ ] wAirCoolerEDR.SetActive()
					[+] if(wAirCoolerEDR.tpgDesign.cboAirCoolerModel.Exists(5))
						[ ] Log.Pass("The HYSYS AirCooled form opens automatically with the Design tab-Parameters ply.")
						[+] if(wAirCoolerEDR.tpgDesign.cboAirCoolerModel.TextCapture()=="Air Cooler Simple Design")
							[ ] Log.Pass("The Heat Exchanger Model is changed to Air Cooler Simple Design.")
						[+] else
							[ ] Log.Fail("The Heat Exchanger Model is not changed to Air Cooler Simple Design.")
						[ ] wAirCoolerEDR.Close()
				[+] else
					[ ] Log.Fail("The HYSYS AirCooled form does not open.")
			[+] else
				[ ] Log.Fail("Pop-up message does not display on top of the form as expected.")
			[+] if(!AH.IsSimpleModel(1))
				[ ] Log.Fail("The rigorous model is not reverted to simple model.")
			[+] else
				[ ] Log.Pass("The rigorous model is reverted to simple model.")
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[ ] 
		[ ] 
	[ ] 
[ ] 
[+] testcase CQ00510265() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510265"
		[ ] sDatain="{sDatain}\CQ00510264"
		[ ] sCaseName="Rigorous AirCooler.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[+] // Case script
		[ ] Print("4.5.2.2 Convert AirCooled model to Simple model – Second Alternative Flow")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached Rigorous Aircooler.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[+] Print("Step 2: Click the  Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[+] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[+] if(wRevertTo.Exists(10))
					[ ] Log.Pass("Pop-up message displays on top of the form as expected.")
					[ ] wRevertTo.SetActive()
					[ ] wRevertTo.rdbWithOriginalSpecs.Check()
					[ ] sleep(1)
					[ ] wRevertTo.btnRevert.Click()
					[+] if(wAirCoolerEDR.Exists(10))
						[ ] wAirCoolerEDR.SetActive()
						[+] if(wAirCoolerEDR.tpgDesign.cboAirCoolerModel.Exists(5))
							[ ] Log.Pass("The HYSYS AirCooled form opens automatically with the Design tab-Parameters ply.")
							[+] if(wAirCoolerEDR.tpgDesign.cboAirCoolerModel.TextCapture()=="Air Cooler Simple Design")
								[ ] Log.Pass("The Heat Exchanger Model is changed to Air Cooler Simple Design.")
							[+] else
								[ ] Log.Fail("The Heat Exchanger Model is not changed to Air Cooler Simple Design.")
							[ ] wAirCoolerEDR.Close()
					[+] else
						[ ] Log.Fail("The HYSYS AirCooled form does not open.")
				[+] else
					[ ] Log.Fail("Pop-up message does not display on top of the form as expected.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Select an AirCooled model; click the Revert to Simple button on the Activated Summary table.")
		[+] Print("Step 4: Click Revert with the Simple Design with Original Specs option.")
			[+] if(!AH.IsSimpleModel(1))
				[ ] Log.Fail("The rigorous model is not reverted to simple model.")
			[+] else
				[ ] Log.Pass("The rigorous model is reverted to simple model.")
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
		[ ] 
	[ ] 
[+] testcase CQ00510266() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510266"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[ ] sCaseName="PLATEFIN1 RIG.HSC"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.5.3.1 Convert Platefin model to LNG Simple model")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached PlateFin1 RIG.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[+] Print("Step 2: Click the  Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[+] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] AH.SetActive()
				[ ] AH.Find("//WPFTabItem[@caption='Exchanger Summary Table*']").Click(2)
				[ ] sleep(1)
				[ ] AH.muiCloseOtherTabs.Click()
				[ ] sleep(2)
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[+] if(wRevert.Exists(10))
					[ ] wRevert.SetActive()
					[ ] wRevert.Close()
					[ ] sleep(1)
				[+] else
					[ ] Log.Fail("No pop-up message displayed.")
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[+] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The rigorous model is reverted to simple model.")
			[+] else
				[ ] Log.Pass("The rigorous model is not reverted to simple model.")
		[ ] Print("Step 3: Select the PlateFin rigorous model LNG-100; click the PlateFin button on the Exchanger Summary table.")
		[ ] Print("Step 4: Click Close.")
		[-] Print("Step 5: Repeat step 3, click Revert.")
			[ ] AH.SetActive()
			[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
			[-] if(wRevert.Exists(10))
				[ ] wRevert.SetActive()
				[ ] wRevert.btnRevert.Click()
				[-] if(wLNG.Exists(10))
					[ ] wLNG.SetActive()
					[ ] wLNG.lbParameters.Click()
					[ ] sleep(2)
					[-] if(wLNG.tpgDesign.dgRatingMethod.Exists(3))
						[ ] Log.Pass("The HYSYS LNG form opens with the Design tab-Parameters ply.")
						[ ] //Step 6
						[ ] wLNG.tpgDesign.dgRatingMethod.Find("//WPFDataGridCell[2]").Click()
						[ ] Desktop.TypeKeys("<Backspace>",1)
						[ ] wLNG.cboComboBox.Select("Simple End Point")
						[ ] //Step 7
						[+] if(wLNG.dlgAH.Exists(100))
							[ ] 
							[ ] wLNG.dlgAH.SetActive()
							[ ] wLNG.dlgAH.btnNo.Click()
							[ ] sleep(2)
						[+] else
							[ ] Log.Fail("Warning dialog does not pop up.")
						[-] if(wLNG.tpgDesign.dgRatingMethod.Find("//WPFDataGridCell[2]").TextCapture()=="EDR	-	PlateFin")
							[ ] Log.Pass("The rigorous model is not converted to simple model.")
						[+] else
							[ ] Log.Fail("The rigorous model is converted to simple model.")
						[ ] //Step 8
						[ ] wLNG.SetActive()
						[ ] wLNG.tpgDesign.dgRatingMethod.Find("//WPFDataGridCell[2]").Click()
						[ ] Desktop.TypeKeys("<Backspace>",1)
						[ ] wLNG.cboComboBox.Select("Simple End Point")
						[+] if(wLNG.dlgAH.Exists(10))
							[ ] wLNG.dlgAH.SetActive()
							[ ] wLNG.dlgAH.btnYes.Click()
							[ ] sleep(1)
						[+] else
							[ ] Log.Fail("Warning dialog does not pop up.")
						[ ] wLNG.Close()
				[+] else
					[ ] Log.Fail("The HYSYS LNG form does not open.")
			[+] else
				[ ] Log.Fail("No pop-up message displayed.")
		[ ] Print("Step 6: Choose one of the simple models as Rating Method from the selection box.")
		[ ] Print("Step 7: Click No for the pop up warning dialog.")
		[-] Print("Step 8: Repeat step 5-6 and click Yes for the pop up warning dialog.")
			[-] if(!AH.IsSimpleModel(1))
				[ ] Log.Fail("The rigorous model is not reverted to simple model.")
			[-] else
				[ ] Log.Pass("The rigorous model is reverted to simple model.")
			[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[-] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[-] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[-] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
		[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510268() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510268"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[ ] sCaseName="firedheater1 rig.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
	[-] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.5.4.1 Convert FiredHeater model to Simple model")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached firedheater1 rig.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Activated EDR dashboard and open the activated summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] AH.SetActive()
				[ ] AH.Find("//WPFTabItem[@caption='Exchanger Summary Table*']").Click(2)
				[ ] sleep(1)
				[ ] AH.muiCloseOtherTabs.Click()
				[ ] sleep(2)
				[ ] //Step 3
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wRevert.Exists(10))
					[ ] wRevert.SetActive()
					[ ] wRevert.Close()
					[ ] sleep(1)
				[-] else
					[ ] Log.Fail("No pop-up message displayed.")
			[-] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
			[-] if(AH.IsSimpleModel(1))
				[ ] Log.Fail("The rigorous model is reverted to simple model.")
			[+] else
				[ ] Log.Pass("The rigorous model is not reverted to simple model.")
		[ ] Print("Step 3: Select the FiredHeater rigorous model FH-100; click the Revert to Simple button on the Exchanger Summary table.")
		[ ] Print("Step 4: Click Close.")
		[-] Print("Step 5: Repeat step 3, click Revert.")
			[ ] AH.SetActive()
			[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
			[-] if(wRevert.Exists(10))
				[ ] wRevert.SetActive()
				[ ] wRevert.btnRevert.Click()
				[-] if(wFiredHeater.Exists(10))
					[ ] wFiredHeater.SetActive()
					[-] if(wFiredHeater.cboSteadyStateModel.TextCapture()=="EDR	-	FiredHeater")
						[ ] Log.Pass("The HYSYS FiredHeater form opens with the Design tab-Parameters ply.")
					[-] else
						[ ] Log.Fail("The HYSYS FiredHeater form does not open with the Design tab-Parameters ply.")
					[ ] wFiredHeater.cboSteadyStateModel.Select("Simple fired heater")
					[ ] sleep(8)
					[-] if(wFiredHeater.cboSteadyStateModel.TextCapture()=="Simple fired heater")
						[ ] Log.Pass("The model is reverted successfully.")
					[-] else
						[ ] Log.Fail("The model is not reverted successfully.")
					[ ] wFiredHeater.SetActive()
					[ ] wFiredHeater.Close()
				[+] else
					[ ] Log.Fail("The HYSYS FiredHeater form opens.")
			[+] else
				[ ] Log.Fail("No pop-up message displayed.")
		[-] Print("Step 6: Choose the Simple fire heater models as Steady State model from the model selection box.")
			[+] if(!AH.IsSimpleModel(1))
				[ ] Log.Fail("The rigorous model is not reverted to simple model.")
			[+] else
				[ ] Log.Pass("The rigorous model is reverted to simple model.")
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
		[ ] 
	[ ] 
[+] testcase CQ00510270() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510270"
		[ ] sDatain="{sDatain}\CQ00510270"
		[ ] sCaseName="Shell&Tube Simple.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
		[ ] RECT r
		[ ] list of string lsDataInFlyover, lsDataActual
		[-] list of string lsPopHeaders={...}  
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] "Vibration"
			[ ] //""  //Teenie updated
			[ ] "Erosion: RhoV2"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] //""//xiaoqing
			[ ] "Other"
	[-] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.6.1 Shell&Tube smoke test for Activated EDR in HYSYS")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached Shell&Tube Simple.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[-] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[-] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Exchanger icon on the Activated EDR dashboard and select the Show model status option.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowModelStatus.Check()
			[ ] sleep(2)
		[-] Print("Step 3: Go to flowsheet, move the mouse hover over the Shell&Tube simple model E-100, which highlighted in grey circle.The following window will be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step3.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. It's grey.")
			[ ] AH.SetActive()
			[ ] AH.tabiFlowsheetModify.Select()
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(5))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("E-100")
				[ ] sleep(2)  //Teenie updated
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-10 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgHeatExchanger.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgHeatExchanger.GetDatainFlyover("Heat Exchanger")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[-] else
				[ ] lsDataActual=AH.GetHeatResults("E-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Tube Side Delta T' value is correct.")
				[+] else
					[ ] Log.Fail("'Tube Side Delta T' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Shell Side Delta T' value is correct.")
				[+] else
					[ ] Log.Fail("'Shell Side Delta T' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(Abs(Val(lsDataInFlyover[6])-Val(lsDataActual[6]))/Val(lsDataActual[6])<0.01 && lsDataInFlyover[7]==lsDataActual[7])
					[ ] Log.Pass("'Tube Side Pressure Drop' value is correct.")
				[+] else
					[ ] Log.Fail("'Tube Side Pressure Drop' value is incorrect. Expected: {lsDataActual[6]}{lsDataInFlyover[7]}, In Flyover it's {lsDataInFlyover[6]}{lsDataActual[7]}.")
				[+] if(Abs(Val(lsDataInFlyover[8])-Val(lsDataActual[8]))/Val(lsDataActual[8])<0.01 && lsDataInFlyover[9]==lsDataActual[9])
					[ ] Log.Pass("'Shell Side Pressure Drop' value is correct.")
				[+] else
					[ ] Log.Fail("'Shell Side Pressure Drop' value is incorrect. Expected: {lsDataActual[8]}{lsDataInFlyover[9]}, In Flyover it's {lsDataInFlyover[8]}{lsDataActual[9]}.")
				[+] if(Abs(Val(lsDataInFlyover[10])-Val(lsDataActual[10]))/Val(lsDataActual[10])<0.01 && lsDataInFlyover[11]==lsDataActual[11])
					[ ] Log.Pass("'Duty' value is correct.")
				[+] else
					[ ] Log.Fail("'Duty' value is incorrect. Expected: {lsDataActual[10]}{lsDataInFlyover[11]}, In Flyover it's {lsDataInFlyover[10]}{lsDataActual[11]}.")
			[ ] AH.SetActive()
			[ ] AH.CloseTab("Heat Exchanger: E-100*")
			[ ] sleep(1)
		[-] Print("Step 4: Click Size Rigorous button.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("E-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-10 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos-20+r.xSize/2,i)
				[-] if(wflyover2.dlgHeatExchanger.Exists())
					[ ] wflyover2.btnSizeRigorous.Click()
					[-] if(wSizingToCreateRigorousExchanger.Exists(15))
						[ ] Log.Pass("Sizing To Create Rigorous Exchanger window does pops up.")
						[ ] wSizingToCreateRigorousExchanger.SetActive()
						[ ] //Step 5
						[ ] wSizingToCreateRigorousExchanger.rdbAutoSize.Check()
						[ ] sleep(1)
						[ ] wSizingToCreateRigorousExchanger.btnConvert.Click()
						[-] if(xWindow.dlgAH.Exists(100))
							[ ] 
							[ ] xWindow.dlgAH.SetActive()
							[ ] xWindow.dlgAH.btnYes.Click()
							[ ] sleep(2)
					[-] else
						[ ] Log.Fail("Sizing To Create Rigorous Exchanger window does not pop up.")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 5: Select Auto Size and click Convert. Click Yes to accept the change.")
		[-] Print("Step 6: Move the mouse hover over the converted Shell&Tube rigorous model. The model now is highlighted in blue circle. The following window will be displayed.")
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\BlueCircle.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the circle's color, it's should be blue.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(2)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("E-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[-] if(wflyover2.dlgShellTube.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgShellTube.GetDatainFlyover("Shell&Tube")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[-] else
				[ ] lsDataActual=AH.GetShellTubeResults("E-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(MatchStr("*{lsDataInFlyover[1]}*",lsDataActual[1]))
					[ ] Log.Pass("'Rigorous Model' value is correct.")
				[+] else
					[ ] Log.Fail("'Rigorous Model' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Surface Area' value is correct.")
				[+] else
					[ ] Log.Fail("'Surface Area' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Total Heat Load' value is correct.")
				[+] else
					[ ] Log.Fail("'Total Heat Load' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(lsDataInFlyover[6]==lsDataActual[6])
					[ ] Log.Pass("'TEMA Type' value is correct.")
				[+] else
					[ ] Log.Fail("'TEMA Type' value is incorrect. Expected: {lsDataActual[6]}, In Flyover it's {lsDataInFlyover[6]}.")
				[+] if(Val(lsDataInFlyover[7])==Val(lsDataActual[7]))
					[ ] Log.Pass("'Shells in Series' value is correct.")
				[+] else
					[ ] Log.Fail("'Shells in Series' value is incorrect. Expected: {lsDataActual[7]}, In Flyover it's {lsDataInFlyover[7]}.")
				[+] if(Val(lsDataInFlyover[8])==Val(lsDataActual[8]))
					[ ] Log.Pass("'Shells in Parallel' value is correct.")
				[+] else
					[ ] Log.Fail("'Shells in Parallel' value is incorrect. Expected: {lsDataActual[8]}, In Flyover it's {lsDataInFlyover[8]}.")
		[-] Print("Step 7: Change the display circle option to Show risk status option. ")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowRiskStatus.Check()
			[ ] sleep(2)
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step7.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. It's yellow.")
		[-] Print("Step 8: Move the mouse hover over the Shell&Tube rigorous model. The following flyover will be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(3)
			[ ] AH.Minimize()
			[ ] sleep(1)
			[ ] AH.Maximize()
			[ ] sleep(1)
			[ ] AH.SetActive()
			[ ] AH.ActiveTab("View")
			[ ] sleep(2)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("E-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[-] if(wflyover2.dlgShellTube.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\SortingLogic.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Pressure; 2)Temperature; 3)Vibration; 4)Erosion rhoV2; 5)Heat Transfer; 6)Pressure Drop; 7)Flow; 8) Other.")
					[ ] //Step 9
					[ ] wflyover2.dlgShellTube.Click(1,140,10)
					[-] if(wOperationWarnings.Exists())
						[ ] Log.Pass("The operation warning box for E-100 pops up.")
						[ ] wOperationWarnings.SetActive()
						[ ] wOperationWarnings.click()
						[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
						[ ] 
						[-] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
							[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
						[-] else
							[ ] wOperationWarnings.SetActive()
							[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
							[+] else
								[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
								[ ] ListPrint(lsPopHeaders)
								[ ] Log.Fail("Actual: ")
								[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
						[ ] wOperationWarnings.SetActive()
						[ ] wOperationWarnings.btnClose.Click()
					[-] else
						[ ] Log.Fail("The operation warning box for FH-101 does not  pop up as expected.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 9: Click the highlighted traffic button, the operation warning box for E-100 should pop up.")
		[-] Print("Step 10: Change the display circle option to Show model status option.")
			[ ] AH.SetActive()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowModelStatus.Check()
			[ ] sleep(2)
		[-] Print("Step 11: Move the mouse hover over the E-100 and click the Revert to End Point button on flyover.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("E-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgShellTube.Exists())
					[ ] wflyover2.btnRevert.Click()
					[+] if(wRevert.Exists(10))
						[ ] Log.Pass("Pop-up message is displayed on top of the form.")
						[ ] //Step 12
						[ ] wRevert.SetActive()
						[ ] wRevert.Close()
						[ ] sleep(1)
					[+] else
						[ ] Log.Fail("Pop-up message is not displayed on top of the form.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[-] Print("Step 12: Click Close.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Heat Exchanger: E-100")
			[ ] sleep(1)
			[ ] AH.SetTab("Design")
			[ ] sleep(2)
			[-] if(AH.cboHeatExchangerModel.TextCapture()=="Rigorous Shell&Tube")
				[ ] Log.Pass("The Heat Exchanger Model is changed to Simple End Point.")
			[-] else
				[ ] Log.Fail("The Heat Exchanger Model is not changed to Simple End Point.")
		[-] Print("Step 13: Click the Activated EDR dashboard and open the exchanger summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] //Step 14
				[ ] AH.SetActive()
				[ ] //AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()  //Old
				[ ] AH.dgGeneralTable.Find("//WPFDataGridCell[3]").Click()  //Teenie updated
				[-] if(wRevert.Exists(10))
					[ ] //Step 15
					[ ] wRevert.SetActive()
					[ ] wRevert.btnRevert.Click()
					[ ] sleep(8)
				[-] else
					[ ] Log.Fail("No pop-up message displayed.")
			[-] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 14: Select E-100 and click Revert to Simple button.")
		[-] Print("Step 15: Click Revert with the default option.")
			[-] do
				[ ] AH.SetTab("Heat Exchanger: E-100")
				[-] if AH.dlgAH.exists(30)
					[ ] AH.dlgAH.btnOK.Click()
					[ ] 
				[ ] sleep(1)
				[-] if(AH.cboHeatExchangerModel.Exists(5))
					[ ] Log.Pass("The HYSYS Shell&Tube form opens automatically with the Design tab-Parameters ply.")
					[+] if(AH.cboHeatExchangerModel.TextCapture()=="Simple End Point")
						[ ] Log.Pass("The Heat Exchanger Model is changed to Simple End Point.")
					[-] else
						[ ] Log.Fail("The Heat Exchanger Model is not changed to Simple End Point.")
				[-] else
					[ ] Log.Fail("The HYSYS Shell&Tube form does not open automatically with the Design tab-Parameters ply.")
			[+] except
				[ ] Log.Fail("The HYSYS Shell&Tube form does not open.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.SetActive()
			[ ] AH.SetTab("Heat Exchanger: E-100")
			[ ] sleep(1)
			[ ] AH.SetTab("Design")
			[ ] sleep(2)
			[-] if(AH.cboHeatExchangerModel.TextCapture()=="Simple End Point")
				[ ] Log.Pass("The Heat Exchanger Model is reverted to simple successfully.")
			[-] else
				[ ] Log.Fail("The Heat Exchanger Model is not reverted to simple.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Exchanger Summary Table")
			[ ] sleep(2)  //Teenie added
			[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[-] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[ ] sleep(2)  //Teenie added
			[ ] //if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")  //Old
			[-] if(AH.dgGeneralTable.Find("//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")  //Teenie updated
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[-] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510272() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510272"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[+] list of string lsCaseName={...}
			[ ] "ACOL Simple.hsc"
			[ ] "CS_Air_Cooled_SI.EDT"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
		[ ] RECT r
		[ ] list of string lsDataInFlyover, lsDataActual
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
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.6.2 Air Cooled smoke test for Activated EDR in HYSYS")
		[ ] Print("------------------------------------------------------------------------")
		[+] Print("Step 1: Launch HYSYS, open the attached ACOL simple.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+lsCaseName[1],50)
			[+] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Exchanger icon on the Activated EDR dashboard and select the Show model status option.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(3)
			[ ] AH.chkShowModelStatus.Check()
			[ ] sleep(2)
		[+] Print("Step 3: Go to flow sheet, move the mouse hover over the AirCooled simple model AC-100, which highlighted in grey circle. The following window will be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step3.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. It's grey.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("AC-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgAirCooler.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgAirCooler.GetDatainFlyover("AC to be Converted")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetACToBeConvertResults("AC-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Process Stream Delta P' value is correct.")
				[+] else
					[ ] Log.Fail("'Process Stream Delta P' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Molar Flow' value is correct.")
				[+] else
					[ ] Log.Fail("'Molar Flow' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
			[ ] AH.CloseTab("Air cooler: AC-100*")
			[ ] sleep(1)
		[-] Print("Step 4: Click Size Rigorous button.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("AC-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[-] if(wflyover2.dlgAirCooler.Exists())
					[ ] wflyover2.btnSizeRigorous.Click()
					[ ] sleep(1)
					[-] if(wSizingToCreateRigorousExchanger.Exists(15))
						[ ] Log.Pass("Sizing To Create Rigorous Exchanger window does pops up.")
						[ ] wSizingToCreateRigorousExchanger.SetActive()
						[ ] //Step 5
						[ ] wSizingToCreateRigorousExchanger.rdbSizeInteractivelyUsingTemplate.Check()
						[ ] sleep(2)
						[+] if(wSizingToCreateRigorousExchanger.txtBrowse.IsEnabled)
							[ ] Log.Pass("The Select a Template File for sizing textbox is active.")
						[+] else
							[ ] Log.Fail("The Select a Template File for sizing textbox is inactive.")
						[ ] //Step 6
						[ ] wSizingToCreateRigorousExchanger.btnBrowse.Click()
						[+] if(wSizingToCreateRigorousExchanger.dlgOpen.Exists(10))
							[ ] wSizingToCreateRigorousExchanger.dlgOpen.SetActive()
							[ ] wSizingToCreateRigorousExchanger.dlgOpen.cboFileName.Click()
							[ ] wSizingToCreateRigorousExchanger.dlgOpen.cboFileName.SetText(sDataout+"\"+lsCaseName[2])
							[ ] sleep(1)
							[ ] wSizingToCreateRigorousExchanger.dlgOpen.btnOpen.Click()
							[ ] sleep(1)
						[+] else
							[ ] Log.Fail("Open dialog does not pop up.")
						[ ] wSizingToCreateRigorousExchanger.SetActive()
						[ ] wSizingToCreateRigorousExchanger.btnConvert.Click()
						[ ] sleep(100)
						[-] if(wEDRSizingConsole.Exists(500))
							[ ] Log.Pass("The EDR Sizing Console dialog pops up.")
							[ ] //Step 7
							[ ] wEDRSizingConsole.SetActive()
							[ ] wEDRSizingConsole.btnSize.Click()  
							[ ] sleep(500)
							[ ] wEDRSizingConsole.SetActive()
							[ ] sleep(2)
							[ ] wEDRSizingConsole.btnAcceptDesign.Click()
							[ ] sleep(3)
						[+] else
							[ ] Log.Fail("The EDR Sizing Console - size Shell&Tube window does not pop up.")
					[+] else
						[ ] Log.Fail("Sizing To Create Rigorous Exchanger window does not pop up.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 5: Select Size Interactively using Template as the Select Sizing Method")
		[ ] Print("Step 6: Browse to the attached CS_Air_Cooled_SI.EDT template file and click Convert button.")
		[ ] Print("Step 7: Click Size button and then click Accept Design button.")
		[-] Print("Step 8: Move the mouse hover over the converted Air Cooler rigorous model.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step8.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. It's blue.")
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("AC-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgAirCooled.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgAirCooled.GetDatainFlyover("Air Cooled")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetACResults("AC-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(MatchStr("*Simple*",lsDataInFlyover[1])==MatchStr("*Simple*",lsDataActual[1]))
					[ ] Log.Pass("'Rigorous Model' value is correct.")
				[+] else
					[ ] Log.Fail("'Rigorous Model' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Surface Area' value is correct.")
				[+] else
					[ ] Log.Fail("'Surface Area' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Total Heat Load' value is correct.")
				[+] else
					[ ] Log.Fail("'Total Heat Load' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(lsDataInFlyover[6]==lsDataActual[6])
					[ ] Log.Pass("'Fan Configuration' value is correct.")
				[+] else
					[ ] Log.Fail("'Fan Configuration' value is incorrect. Expected: {lsDataActual[6]}, In Flyover it's {lsDataInFlyover[6]}.")
				[+] if(Val(lsDataInFlyover[7])==Val(lsDataActual[7]))
					[ ] Log.Pass("'Bays per Unit' value is correct.")
				[+] else
					[ ] Log.Fail("'Bays per Unit' value is incorrect. Expected: {lsDataActual[7]}, In Flyover it's {lsDataInFlyover[7]}.")
				[+] if(Val(lsDataInFlyover[8])==Val(lsDataActual[8]))
					[ ] Log.Pass("'Bundles per Bay' value is correct.")
				[+] else
					[ ] Log.Fail("'Bundles per Bay' value is incorrect. Expected: {lsDataActual[8]}, In Flyover it's {lsDataInFlyover[8]}.")
				[+] if(Val(lsDataInFlyover[9])==Val(lsDataActual[9]))
					[ ] Log.Pass("'Fans per Bay' value is correct.")
				[+] else
					[ ] Log.Fail("'Fans per Bay' value is incorrect. Expected: {lsDataActual[9]}, In Flyover it's {lsDataInFlyover[9]}.")
		[-] Print("Step 9: Change the display circle option to Show risk status option.")
			[ ] AH.SetActive()
			[ ] AH.ClickExchanger()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] sleep(3)
			[ ] AH.chkShowRiskStatus.Check()
			[ ] sleep(2)
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step9.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. It's yellow.")
		[+] Print("Step 10: Move the mouse hover over the Air Cooler rigorous model. The following flyover will be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(3)
			[ ] AH.Minimize()
			[ ] sleep(1)
			[ ] AH.Maximize()
			[ ] sleep(1)
			[ ] AH.SetActive()
			[ ] AH.ActiveTab("View")
			[ ] sleep(2)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("AC-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-20 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[-] if(wflyover2.dlgAirCooled.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\SortingLogic.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Pressure; 2)Temperature; 3)Vibration; 4)Erosion rhoV2; 5)Heat Transfer; 6)Pressure Drop; 7)Flow; 8) Other.")
					[ ] //Step 11
					[ ] wflyover2.dlgAirCooled.Click(1,140,10)
					[-] if(wOperationWarnings.Exists(5))
						[ ] Log.Pass("The operation warning box for E-100 pops up.")
						[ ] wOperationWarnings.SetActive()
						[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
							[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
						[+] else
							[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
							[ ] ListPrint(lsPopHeaders)
							[ ] Log.Fail("Actual: ")
							[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
						[ ] wOperationWarnings.SetActive()
						[ ] wOperationWarnings.btnClose.Click()
					[+] else
						[ ] Log.Fail("The operation warning box for FH-101 does not  pop up as expected.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 11: Click the highlighted traffic button, the operation warning box for E-100 should pop up.")
		[-] Print("Step 12: Change the display circle option to Show risk status option.")
			[ ] AH.SetActive()
			[ ] AH.ClickExchanger()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] sleep(2)
			[ ] AH.chkShowModelStatus.Check()
			[ ] sleep(2)
		[+] Print("Step 13: Click Revert.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(3)
			[ ] AH.Minimize()
			[ ] sleep(1)
			[ ] AH.Maximize()
			[ ] sleep(1)
			[ ] AH.SetActive()
			[ ] AH.ActiveTab("View")
			[ ] sleep(2)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("AC-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2-20,i)
				[+] if(wflyover2.dlgAirCooled.Exists())
					[ ] wflyover2.btnRevert.Click()
					[+] if(wRevert.Exists(20))
						[ ] Log.Pass("Pop-up message is displayed on top of the form.")
						[ ] //Step 13
						[ ] wRevert.SetActive()
						[ ] wRevert.btnRevert.Click()
						[ ] sleep(8)
						[ ] AH.SetActive()
						[ ] AH.SetTab("Air cooler: AC-100")
						[ ] sleep(1)
						[ ] AH.SetTab("Design")
						[ ] sleep(2)
						[+] if(AH.cboAirCoolerModel.TextCapture()=="Air Cooler Simple Design")
							[ ] Log.Pass("The model is reverted to simple successfully.")
						[+] else
							[ ] Log.Fail("The model is not reverted to simple.")
					[+] else
						[ ] Log.Fail("Pop-up message is not displayed on top of the form.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
		[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510273() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510273"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[-] list of string lsCaseName={...}
			[ ] "HYSYS_PlateFin_V12.hsc"
			[ ] "PFsimple crossflow.EDR"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i,j
		[ ] string sBitmapDir
		[ ] RECT r
		[ ] list of string lsDataInFlyover, lsDataActual
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
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.6.3 PlateFin smoke test for Activated EDR in HYSYS")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached HYSYS_PlateFin.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+lsCaseName[1],50)
			[-] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[-] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Exchanger icon on the Activated EDR dashboard and select the Show model status option.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] // AH.ClickExchanger()
			[ ] // sleep(1)
			[ ] // AH.chkShowModelStatus.Check()
			[ ] int n = 0
			[-]  while(AH.chkShowModelStatus.exists() == false)
				[ ]  AH.btnActivateEDR.Click(1,10,10)
				[ ]  sleep(2)
				[ ]  n++
				[+] if (n > 3)
					[ ]  break
			[ ] sleep(1)
			[ ] AH.chkShowModelStatus.Check()
			[ ] sleep(2)
		[-] Print("Step 3: Go to flowsheet, move the mouse hover over the LNG simple model LNG-100, which highlighted in grey circle. The following window will be displayed. ")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step3.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. It's grey.")
			[ ] AH.SetActive()
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("LNG-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgLNG.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgLNG.GetDatainFlyover("LNG")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] lsDataActual=AH.GetLNGResults("LNG-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'LMTD' value is correct.")
				[+] else
					[ ] Log.Fail("'LMTD' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'UA' value is correct.")
				[+] else
					[ ] Log.Fail("'UA' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(Abs(Val(lsDataInFlyover[6])-Val(lsDataActual[6]))/Val(lsDataActual[6])<0.01 && lsDataInFlyover[7]==lsDataActual[7])
					[ ] Log.Pass("'Exchanger Cold Duty' value is correct.")
				[+] else
					[ ] Log.Fail("'Exchanger Cold Duty' value is incorrect. Expected: {lsDataActual[6]}{lsDataInFlyover[7]}, In Flyover it's {lsDataInFlyover[6]}{lsDataActual[7]}.")
				[ ] 
			[ ] AH.CloseTab("LNG: LNG-100*")
			[ ] sleep(1)
		[-] Print("Step 4: Click Convert to Rigorous button.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("LNG-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[-] if(wflyover2.dlgLNG.Exists())
					[ ] wflyover2.btnConverttoRigorous.Click()
					[ ] sleep(1)
					[-] if(wEDRConvert.Exists(5))
						[ ] Log.Pass("The Convert dialog pops up.")
						[ ] //Step 5
						[ ] wEDRConvert.SetActive()
						[ ] wEDRConvert.btnConvert.Click()
						[-] if(wLNG.Exists(10))
							[ ] wLNG.SetActive()
							[-] if(wLNG.dgDataGridSimple.GetCellValue(1,1)=="Rating Method")
								[ ] Log.Pass("The HYSYS LNG exchanger form opens automatically with the Design tab - parameter ply.")
							[ ] //Step 6
							[ ] wLNG.lbParameters.click()
							[ ] wLNG.tpgDesign.dgRatingMethod.Find("//WPFDataGridCell[2]").Click()
							[ ] Desktop.TypeKeys("<Backspace>",1)
							[ ] wLNG.cboComboBox.Select("EDR - PlateFin")
							[ ] sleep(2)
							[ ] //Step 7
							[ ] wLNG.SetTab("EDR PlateFin")
							[ ] sleep(1)
							[ ] wLNG.tpgEDRPlateFin.btnImport.Click()
							[-] if(wLNG.dlgImportPlateFin.Exists(300))
								[ ] wLNG.dlgImportPlateFin.SetActive()
								[ ] wLNG.dlgImportPlateFin.cboFileName.Click()
								[ ] wLNG.dlgImportPlateFin.cboFileName.SetText(sDataout+"\"+lsCaseName[2])
								[ ] sleep(1)
								[ ] wLNG.dlgImportPlateFin.btnOpen.Click()
								[ ] sleep(2)
							[-] else
								[ ] Log.Fail("Import window does not pop up.")
							[ ] wLNG.SetActive()
							[ ] wLNG.tpgEDRPlateFin.dgEDR.Find("/WPFDataGridRow[1]//WPFDataGridCell[2]").Click()
							[ ] wLNG.tpgEDRPlateFin.dgEDR.Find("/WPFDataGridRow[1]//WPFDataGridCell[2]//WPFToggleButton[@automationId='PART_DropDown']").Click()
							[ ] wLNG.tpgEDRPlateFin.dgEDR.Find("/WPFDataGridRow[1]//WPFDataGridCell[2]//WPFComboBox[1]").Select("HInlet-HOutlet")
							[ ] sleep(5)
							[ ] wLNG.tpgEDRPlateFin.dgEDR.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
							[ ] sleep(5)
							[ ] wLNG.tpgEDRPlateFin.dgEDR.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]").Click()
							[ ] sleep(5)
							[ ] wLNG.tpgEDRPlateFin.dgEDR.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]//WPFToggleButton[@automationId='PART_DropDown']").Click()
							[ ] wLNG.tpgEDRPlateFin.dgEDR.Find("/WPFDataGridRow[1]//WPFDataGridCell[3]//WPFComboBox[1]").Select("CInlet-COutlet")
							[ ] sleep(5)
							[ ] wLNG.verifyStatus("OK")
							[ ] wLNG.SetActive()
							[ ] wLNG.Close()
							[ ] 
						[-] else
							[ ] Log.Fail("The HYSYS LNG exchanger form does not open.")
					[-] else
						[ ] Log.Fail("The Convert dialog does not pop up.")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 5: Click Convert.")
		[ ] Print("Step 6: Select “EDR - PlateFin” from the Rating Method dropdown box.")
		[ ] Print("Step 7: Go to EDR PlateFin tab and then click the Import button to import the attached PFsimple crossflow.EDR Platefin model.")
		[+] Print("Step 8: Map the streams in HYSYS to the correct LNG Pass Name. In this case, HInlet-HOutlet for Stream 1 and CInlet-COutlet for Stream 2.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if (AH.ExpandTheDashboardButton.Exists() == true)
				[ ] AH.ExpandTheDashboardButton.Select()  //chen
				[ ] sleep(0.5)
			[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlOK.TextCapture()=="1")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[+] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[+] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
		[+] Print("Step 9: Move the mouse hover over the converted LNG rigorous model. The model now is highlighted in blue circle. The following window will be displayed.")
			[ ] AH.SetActive()
			[+] if(wExchangerSummaryTable.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnShoworHideSummary.Click()
				[ ] sleep(3)
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(3)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step9.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. It's blue.")
			[ ] AH.Minimize()
			[ ] sleep(1)
			[ ] AH.Maximize()
			[ ] sleep(1)
			[ ] AH.SetActive()
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("LNG-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2-20 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgPlateFin.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgPlateFin.GetDatainFlyover("PlateFin")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[+] else
				[ ] //Step 10
				[ ] lsDataActual=AH.GetPlateFinResults("LNG-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(MatchStr("*{lsDataInFlyover[1]}*",lsDataActual[1]))
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))<0.1 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Total Heat Load' value is correct.")
				[+] else
					[ ] Log.Fail("'Total Heat Load' value is incorrect. Expected: {lsDataActual[2]}{lsDataActual[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataInFlyover[3]}.")
				[+] if(lsDataInFlyover[4]==lsDataActual[4])
					[ ] Log.Pass("'Streams' value is correct.")
				[+] else
					[ ] Log.Fail("'Streams' value is incorrect. Expected: {lsDataActual[4]}, In Flyover it's {lsDataInFlyover[4]}.")
				[+] if(Val(lsDataInFlyover[5])==Val(lsDataActual[5]))
					[ ] Log.Pass("'Exchangers in Parallel' value is correct.")
				[+] else
					[ ] Log.Fail("'Exchangers in Parallel' value is incorrect. Expected: {lsDataActual[5]}, In Flyover it's {lsDataInFlyover[5]}.")
			[ ] AH.CloseTab("LNG: LNG-100*")
			[ ] sleep(1)
		[ ] Print("Step 10: Make sure the variables values are same as the HYSYS results")
		[-] Print("Step 11: Move the mouse hover over the PlateFin rigorous model. The following flyover will be displayed.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowRiskStatus.Check()
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step7.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. It's green.")
		[-] Print("Step 12: Click the highlighted traffic button, the operation warning box for LNG-100 should pop up.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(3)
			[ ] AH.SetActive()
			[ ] AH.ActiveTab("View")
			[ ] sleep(2)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("LNG-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] AH.Minimize()
			[ ] sleep(1)
			[ ] AH.Maximize()
			[ ] sleep(1)
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-20 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[-] if(wflyover2.dlgPlateFin.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\SortingLogic.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Pressure; 2)Temperature; 3)Vibration; 4)Erosion rhoV2; 5)Heat Transfer; 6)Pressure Drop; 7)Flow; 8) Other.")
					[ ] //Step 13
					[-] for j=135 to 150
						[ ] wflyover2.dlgPlateFin.Click(1,j,12)
						[-] if(wOperationWarnings.Exists())
							[ ] Log.Pass("The operation warning box for E-100 pops up.")
							[ ] wOperationWarnings.SetActive()
							[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
							[+] else
								[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
								[ ] ListPrint(lsPopHeaders)
								[ ] Log.Fail("Actual: ")
								[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
							[ ] wOperationWarnings.SetActive()
							[ ] wOperationWarnings.btnClose.Click()
						[ ] break
					[+] if(j>160)
						[ ] Log.Fail("The operation warning box for LNG-100 does not  pop up as expected.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 13: Click the hightlighted traffic button, the operation warning box for LNG-100 should pop up.")
		[-] Print("Step 14: Click the Activated EDR dashboard and open the Exchanger Summary table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] //Step 15
				[ ] AH.SetActive()
				[ ] AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").Click()
				[-] if(wRevert.Exists(10))
					[ ] //Step 16
					[ ] wRevert.SetActive()
					[ ] wRevert.btnRevert.Click()
					[-] if(wLNG.Exists(10))
						[ ] wLNG.SetActive()
						[ ] wLNG.lbParameters.Click()
						[ ] sleep(4)
						[ ] wLNG.tpgDesign.dgRatingMethod.Find("//WPFDataGridCell[2]").Click()
						[ ] Desktop.TypeKeys("<Backspace>",1)
						[ ] 
						[-] if(wLNG.cboComboBox.Exists())
							[ ] wLNG.cboComboBox.Select("Simple End Point")
							[-] if(wLNG.dlgAH.Exists(100))
								[ ] 
								[ ] wLNG.dlgAH.SetActive()
								[ ] wLNG.dlgAH.btnYes.Click()
								[ ] sleep(2)
						[ ] wLNG.SetActive()
						[ ] wLNG.Close()
					[-] else
						[ ] Log.Fail("The HYSYS LNG exchanger form does not open.")
					[ ] 
				[-] else
					[ ] Log.Fail("No pop-up message displayed.")
			[-] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 15: Click Revert to Simple button on the summary table.")
		[ ] Print("Step 16: Click Convert.")
		[-] Print("Step 17: Choose one of the simple models as Rating Method from the selection box.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Exchanger Summary Table")
			[+] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[+] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[-] if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[-] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
			[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510275() appstate CleanState	
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510275"
		[ ] sDatain="{sDatain}\{sTestCaseID}"
		[+] list of string lsCaseName={...}
			[ ] "HYSYS_FH Simple.hsc"
			[ ] "QFiredHeater1.EDR"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i
		[ ] string sBitmapDir
		[ ] RECT r
		[ ] list of string lsDataInFlyover, lsDataActual
		[-] list of string lsPopHeaders={...}
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] ""
			[ ] ""
			[ ] ""
			[ ] ""
			[ ] "Combustion"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] ""
	[-] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[+] for(i=1;i<=ListCount(lsCaseName);i++)
			[ ] File.Copy(sDatain+"\"+lsCaseName[i],sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.6.4 FiredHeater smoke test for Activated EDR in HYSYS")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached HYSYS_FH Simple.hsc example file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+lsCaseName[1],50)
			[+] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
		[-] Print("Step 2: Click the Exchanger icon on the Activated EDR dashboard and select the Show model status option.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowModelStatus.Check()
			[ ] sleep(2)
		[-] Print("Step 3: Go to the flow sheet, move the mouse hover over the Fired Heater simple model FH-100, which highlighted in grey circle. The following window will be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step3.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. It's grey.")
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("FH-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-20 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgFiredHeater.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgFiredHeater.GetDatainFlyover("FH to be Conveted")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[-] else
				[ ] lsDataActual=AH.GetFHToBeConvertedResults("FH-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(lsDataInFlyover[1]==lsDataActual[1])
					[ ] Log.Pass("'Modle Type' value is correct.")
				[+] else
					[ ] Log.Fail("'Model Type' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Process Stream Delta T' value is correct.")
				[+] else
					[ ] Log.Fail("'Process Stream Delta T' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))<0.01 && lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Pressure Drop' value is correct.")
				[+] else
					[ ] Log.Fail("'Pressure Drop' value is incorrect. Expected: {lsDataActual[4]}{lsDataInFlyover[5]}, In Flyover it's {lsDataInFlyover[4]}{lsDataActual[5]}.")
				[+] if(Abs(Val(lsDataInFlyover[6])-Val(lsDataActual[6]))/Val(lsDataActual[6])<0.01 && lsDataInFlyover[7]==lsDataActual[7])
					[ ] Log.Pass("'Duty' value is correct.")
				[+] else
					[ ] Log.Fail("'Duty' value is incorrect. Expected: {lsDataActual[6]}{lsDataInFlyover[7]}, In Flyover it's {lsDataInFlyover[6]}{lsDataActual[7]}.")
			[ ] AH.CloseTab("Fired Heater: FH-100*")
			[ ] sleep(1)
		[-] Print("Step 4: Click Convert to Rigorous button from the Exchanger Summary table.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("FH-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-20 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[-] if(wflyover2.dlgFiredHeater.Exists())
					[ ] wflyover2.btnConverttoRigorous.Click()
					[ ] sleep(1)
					[-] if(wEDRConvert.Exists(3))
						[ ] Log.Pass("The Convert dialog pops up.")
						[ ] //Step 5
						[ ] wEDRConvert.btnConvert.Click()
						[ ] sleep(1)
						[-] if(wFiredHeater.Exists(10))
							[ ] wFiredHeater.SetActive()
							[-] if(wFiredHeater.cboSteadyStateModel.Exists())
								[ ] Log.Pass("The HYSYS FiredHeater form opens automatically with the Design tab - Parameter ply.")
							[-] else
								[ ] Log.Fail("The HYSYS FiredHeater form does not open automatically with the Design tab - Parameter ply.")
							[ ] //Step 6
							[ ] wFiredHeater.cboSteadyStateModel.Select("EDR - FiredHeater")
							[ ] sleep(1)
							[ ] glWaitForMouseIdle(10)
							[ ] //Step 7
							[ ] wFiredHeater.SetTab("Worksheet")
							[ ] sleep(1)
							[ ] wFiredHeater.lbPlyPicker.Select("Conditions")
							[ ] sleep(1)
							[ ] wFiredHeater.SetActive()
							[ ] wFiredHeater.dgDataGridSimple.ClickCell(6,3,1)
							[ ] sleep(1)
							[ ] Desktop.TypeKeys("<Delete>",3)
							[ ] //Step 8
							[ ] wFiredHeater.SetTab("EDR FiredHeater")
							[ ] sleep(1)
							[ ] wFiredHeater.btnImport.Click()
							[ ] sleep(1)
							[-] if(wFiredHeater.wImportGeometryFromFile.Exists(20))
								[ ] wFiredHeater.wImportGeometryFromFile.SetActive()
								[ ] wFiredHeater.wImportGeometryFromFile.txtFileName.Click()
								[ ] wFiredHeater.wImportGeometryFromFile.txtFileName.TypeKeys(sDataout+"\"+lsCaseName[2])
								[ ] sleep(1)
								[ ] wFiredHeater.wImportGeometryFromFile.btnOpen.Click()
								[ ] sleep(15)
							[-] else
								[ ] Log.Fail("Import window does not pop up.")
							[ ] wFiredHeater.verifyStatus("EDR and HYSYS stream temperatures disagree by > 1 C")
							[ ] wFiredHeater.SetActive()
							[ ] wFiredHeater.Close()
						[-] else
							[ ] Log.Fail("The HYSYS LNG exchanger form does not open.")
					[-] else
						[ ] Log.Fail("The Convert dialog does not pop up.")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 5: Click Convert.")
		[ ] Print("Step 6: Select “EDR – FiredHeater” from the Steady State model dropdown box.")
		[ ] Print("Step 7: Go to Worksheet tab, delete the Mass Flow for Air stream")
		[-] Print("Step 8: Go to EDR FiredHeter tab and then click the Import button to import the attached QFiredHeater1.EDR FiredHeater file.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="0" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="1")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[-] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[ ] //if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")  //Old
			[-] if(AH.dgGeneralTable.Find("//WPFDataGridCell[3]").TextCapture()=="Revert to Simple")  //Teenie updated
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[-] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
		[-] Print("Step 9: Move the mouse hover over the converted Fired Heater rigorous model. The model now is highlighted in blue circle. The following window will be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step9.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. It's blue.")
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("FH-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-20 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgFiredHeater.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] lsDataInFlyover=wflyover2.dlgFiredHeater.GetDatainFlyover("Fired Heater")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[-] else
				[ ] lsDataActual=AH.GetFiredHeater("FH-100")
				[ ] // ListPrint(lsDataInFlyover)
				[ ] // print("*************")
				[ ] // ListPrint(lsDataActual)
				[+] if(MatchStr("*{lsDataInFlyover[1]}*",lsDataActual[1]))
					[ ] Log.Pass("'Rigorous Model' value is correct.")
				[+] else
					[ ] Log.Fail("'Rigorous Model' value is incorrect. Expected: {lsDataActual[1]}, In Flyover it's {lsDataInFlyover[1]}.")
				[+] if(Abs(Val(lsDataInFlyover[2])-Val(lsDataActual[2]))/Val(lsDataActual[2])<0.01 && lsDataInFlyover[3]==lsDataActual[3])
					[ ] Log.Pass("'Total Heat Load' value is correct.")
				[+] else
					[ ] Log.Fail("'Total Heat Load' value is incorrect. Expected: {lsDataActual[2]}{lsDataInFlyover[3]}, In Flyover it's {lsDataInFlyover[2]}{lsDataActual[3]}.")
				[+] if(Abs(Val(lsDataInFlyover[4])-Val(lsDataActual[4]))/Val(lsDataActual[4])<0.01)
					[ ] Log.Pass("'Overall Efficiency' value is correct.")
				[+] else
					[ ] Log.Fail("'Overall Efficiency' value is incorrect. Expected: {lsDataActual[4]}, In Flyover it's {lsDataInFlyover[4]}.")
				[+] if(lsDataInFlyover[5]==lsDataActual[5])
					[ ] Log.Pass("'Streams' value is correct.")
				[+] else
					[ ] Log.Fail("'Streams' value is incorrect. Expected: {lsDataActual[5]}, In Flyover it's {lsDataInFlyover[5]}.")
				[+] if(lsDataInFlyover[6]==lsDataActual[6])
					[ ] Log.Pass("'Firebox in Unit' value is correct.")
				[+] else
					[ ] Log.Fail("'Firebox in Unit' value is incorrect. Expected: {lsDataActual[6]}, In Flyover it's {lsDataInFlyover[6]}.")
				[+] if(lsDataInFlyover[7]==lsDataActual[7])
					[ ] Log.Pass("'Convection Banks' value is correct.")
				[+] else
					[ ] Log.Fail("'Convection Banks' value is incorrect. Expected: {lsDataActual[7]}, In Flyover it's {lsDataInFlyover[7]}.")
			[ ] AH.CloseTab("Fired Heater: FH-100*")
			[ ] sleep(1)
		[-] Print("Step 10: Change the display circle option to Show risk status option.")
			[ ] AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] sleep(2)  //Teenie added
			[ ] AH.ClickExchanger()
			[ ] sleep(1)  
			[ ] AH.chkShowRiskStatus.Check()
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step7.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. It's yellow.")
		[-] Print("Step 11: Move the mouse hover over the Fired Heater rigorous model. The following window will be displayed.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("FH-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-20 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgFiredHeater.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\SortingLogic.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the sorting logic: {chr(10)}"
    +"1. Sort first by status, 1) red warnings; 2) yellow warnings; 3) green {chr(10)}"
    +"2. Sort by order for the equivalent status, 1)Pressure; 2)Temperature; 3)Vibration; 4)Erosion rhoV2; 5)Heat Transfer; 6)Pressure Drop; 7)Flow; 8) Other.")
					[ ] //Step 12
					[ ] wflyover2.dlgFiredHeater.Click(1,150,10)
					[+] if(wOperationWarnings.Exists())
						[ ] Log.Pass("The operation warning box for E-100 pops up.")
						[ ] wOperationWarnings.SetActive()
						[+] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
							[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
						[+] else
							[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
							[ ] ListPrint(lsPopHeaders)
							[ ] Log.Fail("Actual: ")
							[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
						[ ] wOperationWarnings.SetActive()
						[ ] wOperationWarnings.btnClose.Click()
					[+] else
						[ ] Log.Fail("The operation warning box for FH-101 does not  pop up as expected.")
					[ ] break
			[-] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 12: Click the highlighted traffic button, the operation warning box for LNG-100 should pop up.")
		[-] Print("Step 13: Change the display circle option to Show model status option.")
			[ ] AH.SetActive()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] sleep(2)  //Teenie added
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowModelStatus.Check()
			[ ] sleep(2)
		[-] Print("Step 14: Move the mouse hover over the FH-100 and click the Revert button on the flyover.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active*")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[-] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("FH-100")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[-] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2-20 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgFiredHeater.Exists())
					[ ] wflyover2.btnRevert.Click()
					[+] if(wRevert.Exists(20))
						[ ] Log.Pass("Pop-up message is displayed on top of the form.")
						[ ] //Step 16
						[ ] wRevert.SetActive()
						[ ] wRevert.btnRevert.Click()
						[+] if(wFiredHeater.Exists(10))
							[ ] wFiredHeater.SetActive()
							[ ] wFiredHeater.cboSteadyStateModel.Select("Simple fired heater")
							[ ] sleep(8)
							[+] if(wFiredHeater.cboSteadyStateModel.TextCapture()=="Simple fired heater")
								[ ] Log.Pass("The model is reverted successfully.")
							[+] else
								[ ] Log.Fail("The model is not reverted successfully.")
							[ ] wFiredHeater.SetActive()
							[ ] wFiredHeater.Close()
						[+] else
							[ ] Log.Fail("The HYSYS FiredHeater form opens.")
					[+] else
						[ ] Log.Fail("Pop-up message is not displayed on top of the form.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] Print("Step 15: Click Convert.")
		[-] Print("Step 16: Choose the Simple fired heater as Model Selection from the selection box.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Exchanger Summary Table")
			[ ] sleep(2)  //Teenie added
			[-] if(AH.ctrlEDRDashboard.ctrlUnKnown.TextCapture()=="1" &&  AH.ctrlEDRDashboard.ctrlAtRisk.TextCapture()=="0")
				[ ] Log.Pass("The Simple model and rigorous model number in the EDR dashboard are updated.")
			[-] else
				[ ] Log.Fail("The Simple model and rigorous model number in the EDR dashboard are not updated.")
			[ ] sleep(2)  //Teenie added
			[ ] //if(AH.dgGeneralTable.Find("/WPFDataGridRow//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")  //Old
			[-] if(AH.dgGeneralTable.Find("//WPFDataGridCell[3]").TextCapture()=="Convert to Rigorous")  //Teenie updated
				[ ] Log.Pass("The Exchanger Summary table is updated.")
			[-] else
				[ ] Log.Fail("The Exchanger Summary table is not updated.")
		[ ] 
		[ ] 
	[ ] 
[+] testcase CQ00510280() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[+] // Variables defination
		[ ] sTestCaseID="CQ00510280"
		[ ] sDatain="{sDatain}\Multi HXs"
		[ ] sCaseName="Multi-HXs.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer inum,i,j
		[ ] string sBitmapDir,sTemp,sTemp2
		[ ] RECT r
		[ ] list of string lsSub
		[ ] list of string lsUnitOps
		[ ] boolean bFlag=true
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.3.5 Flyovers for SubFlowsheets")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached Multi-HXs.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] sleep(1)
			[ ] AH.btnGoToParent.Click()
			[ ] sleep(10)
			[+] if(wSubFlowsheet.Exists(5))
				[ ] wSubFlowsheet.SetActive()
				[ ] wSubFlowsheet.Close()
				[ ] sleep(1)
			[-] if(wPalette.Exists(15))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] sleep(1)
			[ ] AH.btnGoToParent.Click()
			[ ] sleep(10)
			[+] if(wSubFlowsheet.Exists(5))
				[ ] wSubFlowsheet.SetActive()
				[ ] wSubFlowsheet.Close()
				[ ] sleep(1)
		[-] Print("Step 2: Click the Exchanger icon on the Activated EDR dashboard and select “Show model status”.")
			[ ] AH.SetActive()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowModelStatus.Check()
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnFlowSheet.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.trvFlowSheet.Select("/Case (Main)")
				[ ] sleep(1)
				[ ] wObjectNavigator.lstUnitOperations.Select("Flow-1")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Circles.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for confirming object Flow-1 is highlighted in blue.")
		[-] Print("Step 3: Hover over the highlighted circle for Flow-1, the Flyover is displayed.")
			[ ] AH.SetActive()
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.trvFlowSheet.Select("/Case (Main)")
				[ ] sleep(1)
				[ ] wObjectNavigator.lstUnitOperations.Select("Flow-1")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[-] for i=r.yPos+r.ySize/2-120 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[-] if(wflyover2.dlgSubFlowsheet.Exists())
					[ ] Log.Pass("Flyover displays.")
					[+] if wflyover2.txtDisplayTextBlockOkNum.Exists(5)
						[ ] // sTemp=wflyover2.Find("//WPFControl[@automationId='horizontalDisplayText'][2]/WPFTextBlock[@caption='*']").TextCapture()
						[ ] // sTemp2=wflyover2.Find("//WPFControl[@automationId='horizontalDisplayText'][3]/WPFTextBlock[@caption='*']").TextCapture()
						[ ] 
						[ ] sTemp=wflyover2.txtDisplayTextBlockOkNum.TextCapture()
						[ ] sTemp2=wflyover2.txtDisplayTextBlockRiskNum.TextCapture()
						[ ] 
					[-] else
						[ ] // sTemp=wflyover2.Find("//WPFControl[@automationId='horizontalDisplayText'][2]/WPFTextBox[@automationId='*']").TextCapture()
						[ ] // sTemp2=wflyover2.Find("//WPFControl[@automationId='horizontalDisplayText'][3]/WPFTextBox[@automationId='*']").TextCapture()
						[ ] sTemp=wflyover2.txtDisplayTextBoxOkNum.TextCapture()
						[ ] sTemp2=wflyover2.txtDisplayTextBoxRiskNum.TextCapture()
						[ ] 
					[+] if(sTemp!="0" || sTemp2!="0")
						[ ] Log.Pass("The sub-flowsheet contains rigoroous model.")
					[+] else
						[ ] Log.Fail("The sub-flowsheet does not contain rigoroous model.")
					[ ] wflyover2.btnShowSummary.Click()
					[ ] sleep(1)
					[+] do
						[ ] AH.SetTab("Subflowsheet FLOW-1 Exchanger Summary Table")
						[ ] lsSub=GetAllDataInOneColumn(AH.dgGeneralTable,1)
						[ ] lsUnitOps=GetAllDataInOneColumn(AH.dgGeneralTable,2)
					[+] except
						[ ] ExceptClear()
						[ ] Log.Fail("Summary table does not display.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
			[ ] //Validation of Step 4
			[+] if(ListCount(lsSub)!=0)
				[+] for(j=1;j<=ListCount(lsSub);j++)
					[+] if(lsUnitOps[j]=="FLOW-1 (TPL1)")
						[ ] sTemp="/UnitOps/FLOW-1/UnitOps/{SubStr(lsSub[j],1,StrPos("@",lsSub[j])-2)}"
					[+] else
						[ ] sTemp="/UnitOps/FLOW-1/UnitOps/{SubStr(lsUnitOps[j],1,StrPos("(",lsUnitOps[j])-2)}/UnitOps/{SubStr(lsSub[j],1,StrPos("@",lsSub[j])-2)}"
					[ ] inum=StrPos("/",sTemp,true)
					[ ] AH.trvPartTree.trviUnitOps.Collapse()
					[ ] sleep(1)
					[+] do
						[ ] AH.trvPartTree.Expand("{SubStr(sTemp,1,inum)}")
						[ ] AH.trvPartTree.Click("{sTemp}")
					[+] except
						[ ] ExceptClear()
						[ ] Log.Fail("In line {j}, the heat exchanger in 2nd level sub-flowhseet does not display with @ in the front of the sub-flowsheet name in 2nd column.")
						[ ] bFlag=false
				[+] if(bFlag)
					[ ] Log.Pass("The heat exchanger in 2nd level sub-flowhseet does not display with @ in the front of the sub-flowsheet name in 2nd column.")
		[ ] Print("Step 4: Click the Show Summary button, the following flyover dialog will be displayed.")
		[+] Print("Step 5: Click the exchanger name link, e.g. E-101-2@TPL3.")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Subflowsheet FLOW-1 Exchanger Summary Table")
			[ ] sleep(1)
			[ ] AH.dgGeneralTable.Find("/WPFDataGridRow[6]//WPFDataGridCell[1]").Click()
			[+] if(wHeatExchanger.Exists(10))
				[ ] wHeatExchanger.SetActive()
				[+] if(wHeatExchanger.tpgRigorousShell.btnImport.Exists(3))
					[ ] Log.Pass("The Heat Exchanger: E-101-2@TPL3 dialog will pop up and the Rigorous Shell&Tube tab is displayed.")
				[+] else
					[ ] Log.Fail("The Heat Exchanger: E-101-2@TPL3 dialog will pop up and the Rigorous Shell&Tube tab is not displayed.")
				[ ] wHeatExchanger.Close()
			[+] else
				[ ] Log.Fail("The HYSYS Shell&Tube form does not open with the Design tab-Parameters ply.")
		[+] Print("Step 6: Click the close button, the subflowsheet exchanger summary table can be closed successfully. ")
			[ ] AH.CloseTab("Subflowsheet FLOW-1 Exchanger Summary Table")
		[+] Print("Step 7: Double click the Flow-1, click Sub-Flowsheet Environment button to enter the subflowsheet")
			[ ] AH.SetActive()
			[ ] AH.SetTab("Flowsheet Case (Main) - Solver Active")
			[ ] sleep(2)
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.trvFlowSheet.Select("/Case (Main)")
				[ ] sleep(1)
				[ ] wObjectNavigator.lstUnitOperations.Select("Flow-1")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] // AH.SetActive()
			[ ] // r=AH.areaForMainFlowsheet.GetRect()
			[ ] // //AH.areaForMainFlowsheet.MoveMouse(r.xPos+r.xSize/2,r.yPos+r.ySize/2+100)
			[ ] // AH.areaForMainFlowsheet.DoubleClick(1,r.xPos+r.xSize/2-220,r.yPos+r.yPos/2-120)
			[ ] AH.SetActive()
			[ ] RECT r2=AH.areaForMainFlowsheet.GetRect()
			[ ] AH.areaForMainFlowsheet.DoubleClick(1,r2.xPos+r2.xSize/2-220,r2.yPos+r2.yPos/2-120)
			[ ] 
			[+] if(wSubFlowsheetFLOW1.Exists(20))
				[ ] wSubFlowsheetFLOW1.SetActive()
				[ ] wSubFlowsheetFLOW1.btnSubFlowsheetEnvironment.Click()
				[ ] sleep(10)
				[+] if(wSubFlowsheet.Exists(5))
					[ ] wSubFlowsheet.SetActive()
					[ ] wSubFlowsheet.Close()
					[ ] sleep(1)
				[+] if(wPalette.Exists(5))
					[ ] wPalette.SetActive()
					[ ] wPalette.Close()
					[ ] sleep(1)
				[ ] AH.SetActive()
				[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step7.bmp")
				[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for confirming rigorous HeatXs are highlighted in blue, simple HeatXs are hightlighted in grey.")
			[+] else
				[ ] Log.Fail("Sub Flowsheet window does not pop up.")
		[-] Print("Step 8: Click the Exchanger icon on the Activated EDR dashboard and select “Show risk status”.")
			[ ] // AH.SetActive()
			[ ] //AH.btnExchanger.Image.Click()
			[ ] // AH.btnExchanger.DoubleClick()
			[ ] AH.ClickExchanger()
			[ ] sleep(1)
			[ ] AH.chkShowRiskStatus.Check()
			[ ] sleep(2)
			[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Step8.bmp")
			[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for circles' color around the models. In the case, RIG and FH-101-2 are highlighted in yellow.")
		[+] Print("Step 9: Hover over the highlight for SIM, the following flyover is displayed")
			[ ] AH.SetActive()
			[ ] AH.ActiveTab("View")
			[ ] AH.btnFlowSheet.Click()
			[ ] sleep(1)
			[ ] AH.ActiveTab("View")
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("SIM")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2-10 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgSubFlowsheet.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\SIM.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the flyover of SIM.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[+] print("Step 10: Hover over the highlight for RIG, the following flyover is displayed")
			[ ] AH.SetActive()
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("RIG")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2-10 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgSubFlowsheet.Exists())
					[ ] Log.Pass("Flyover displays.")
					[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\RIG.bmp")
					[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' to verify the flyover of RIG.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[+] print("Step 11: Click Show Summary, the Sub-flowsheet summary table is displayed.")
			[ ] AH.SetActive()
			[ ] AH.ActiveTab("View")
			[ ] sleep(1)
			[ ] AH.btnZoomToFIt.Click()
			[ ] sleep(2)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] AH.btnFindObject.Click()
			[+] if(wObjectNavigator.Exists(2))
				[ ] wObjectNavigator.SetActive()
				[ ] wObjectNavigator.lstUnitOperations.Select("RIG")
				[ ] sleep(1)
				[ ] wObjectNavigator.btnLocate.Click()
			[+] else
				[ ] Log.Fail("'Object Navigator' window does not pop up.")
			[ ] r=AH.areaForMainFlowsheet.GetRect()
			[+] for i=r.yPos+r.ySize/2-10 to r.yPos+r.ySize/2+500
				[ ] AH.MoveMouse(r.xPos+r.xSize/2,i)
				[+] if(wflyover2.dlgSubFlowsheet.Exists())
					[ ] wflyover2.btnShowSummary.Click()
					[ ] sleep(1)
					[+] do
						[ ] AH.SetTab("Subflowsheet RIG @TPL1 Exchanger Summary Table")
						[ ] Log.Pass("The sub flowsheet summary table displays.")
						[ ] //Step 12
						[ ] AH.SetActive()
						[ ] AH.dgGeneralTable.Find("/WPFDataGridRow[2]//WPFDataGridCell[4]").Click()
						[+] if(wOperationWarnings.Exists(10))
							[ ] Log.Pass("The Operation Warning form displays.")
							[ ] wOperationWarnings.Close()
						[+] else
							[ ] Log.Fail("The Operation Warning form does not display.")
					[+] except
						[ ] ExceptClear()
						[ ] Log.Fail("The sub flowsheet summary table does not display.")
					[ ] break
			[+] if(i>r.yPos+r.ySize/2+500)
				[ ] Log.Fail("Flyover does not display.")
		[ ] print("Step 12: Click the traffic light button for the exchanger, e.g. AC-100-2@TPL3, the Operation Warning form will be displayed.")
	[ ] 
[+] testcase CQ00510223() appstate CleanState
	[+] // ========================Log===========================
		[ ] // Author:	Susan Shi
		[ ] // Date: 	Dev 18, 2013
	[-] // Variables defination
		[ ] sTestCaseID="CQ00510223"
		[ ] sDatain="{sDatain}\Multi HXs"
		[ ] sCaseName="Multi-HXs.hsc"
		[ ] sDataout="{sDataout}\{sTestCaseID}"
		[ ] integer i, iSimple=0,irow,k,j
		[-] list of string lsPopHeaders={...}
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] "Vibration"
			[ ] "Erosion: RhoV2"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] "Other"
		[-] list of string lsPopHeadersFH={...}
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] ""
			[ ] ""
			[ ] ""
			[ ] ""
			[ ] "Combustion"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] ""
		[+] list of string lsHeadersExp={...}
			[ ] "Exchanger Name"
			[ ] "Subflowsheet"
			[ ] "Model Status"
			[ ] "Summary"
			[ ] "Pressure"
			[ ] "Temperature"
			[ ] "Vibration"
			[ ] "Erosion: RhoV2"
			[ ] "Heat Transfer"
			[ ] "Pressure Drop"
			[ ] "Flow"
			[ ] "Combustion"
			[ ] "Other"
		[-] list of string lsModelType={...}
			[ ] "AC-100-2"
			[ ] "E-101"
			[ ] //"FH-"
			[ ] "LNG-101"
		[ ] list of window lw
		[ ] List of FILEINFO lFiles
		[ ] string sTemp1,sTemp2
		[ ] string sBitmapDir,sModel,sPath
		[ ] RECT r
		[ ] list of window lwAllRows
		[ ] list of string lsModels, lsHierarchy,lsPath,lsHeadersAct,lsSort,lsSub
	[+] // Case initicalize
		[ ] Print("Entry Condition: EDR is installed on the machine.")
		[ ] Dir.Delete(sDataout)
		[ ] Dir.New(sDataout)
		[ ] File.Copy(sDatain+"\"+sCaseName,sDataout)
		[ ] sleep(2)
	[-] // Case script
		[ ] Print("4.3.2 EDR activated summary table workflow ")
		[ ] Print("------------------------------------------------------------------------")
		[-] Print("Step 1: Launch HYSYS, open the attached Multi-HXs.hsc file.")
			[ ] AH.Launch()
			[ ] AH.SetActive()
			[ ] AH.Open(sDataout+"\"+sCaseName,50)
			[+] if(AH.btnUnpin.Exists())
				[ ] AH.SetActive()
				[ ] AH.btnUnpin.Click()
				[ ] sleep(2)
			[ ] ExpandNaviPane()
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] sleep(1)
			[ ] AH.btnGoToParent.Click()
			[ ] sleep(10)
			[+] if(wSubFlowsheet.Exists(5))
				[ ] wSubFlowsheet.SetActive()
				[ ] wSubFlowsheet.Close()
				[ ] sleep(1)
			[+] if(wPalette.Exists(5))
				[ ] wPalette.SetActive()
				[ ] wPalette.Close()
				[ ] sleep(1)
			[ ] AH.ActiveTab("Flowsheet/Modify")
			[ ] sleep(1)
			[ ] AH.btnGoToParent.Click()
			[ ] sleep(10)
			[+] if(wSubFlowsheet.Exists(5))
				[ ] wSubFlowsheet.SetActive()
				[ ] wSubFlowsheet.Close()
				[ ] sleep(1)
		[-] // Print("Step 2: Click the Activated EDR dashboard to open the Exchanger Summary Table.")
			[ ] // AH.SetActive()
			[ ] // sleep(1)
			[ ] // AH.ctrlEDRDashboard.Click()
			[ ] // sleep(2)
			[ ] // AH.ctrlEDRDashboard.Click()
			[ ] // sleep(2)
			[-] // if(AH.tbiExchangerSummary.Exists(30))
				[ ] // Log.Pass("Exchanger Summary Table appears.")
				[ ] // AH.SetActive()
				[ ] // lsHeadersAct=GetHeaders(AH.dgGeneralTable)
				[+] // for(i=1;i<=ListCount(lsHeadersExp);i++)
					[+] // if(lsHeadersAct[i+1]!=lsHeadersExp[i])
						[ ] // Log.Fail("Table headers are not the same as expected.")
						[ ] // break
				[+] // if(i>ListCount(lsHeadersExp))
					[ ] // Log.Pass("Table headers are as expected.")
				[ ] // //Col 1
				[ ] // Print("Col1-------------------------------")
				[ ] // lsModels=GetAllDataInOneColumn(AH.dgGeneralTable,1)
				[ ] // AH.SetActive()
				[ ] // AH.Find("//WPFTabItem[@caption='Exchanger Summary Table*']").Click(2)
				[ ] // sleep(1)
				[ ] // AH.muiCloseOtherTabs.Click()
				[ ] // sleep(2)
				[+] // for(i=1;i<=ListCount(lsModels);i++)
					[ ] // AH.SetActive()
					[ ] // sTemp1=AH.dgGeneralTable.Find("/WPFDataGridRow[{i}]//WPFDataGridCell[1]").TextCapture()
					[ ] // sTemp2=AH.dgGeneralTable.Find("/WPFDataGridRow[{i}]//WPFDataGridCell[3]").TextCapture()
					[ ] // AH.dgGeneralTable.Find("/WPFDataGridRow[{i}]//WPFDataGridCell[1]").Click()
					[+] // if(AH.IsSimpleModel(i))
						[ ] // //Col 3
						[ ] // Print("Col3---------------{i}----------------")
						[+] // if(sTemp2=="Convert to Rigorous")
							[ ] // Log.Pass("'Convert to Rigorous' is displayed for simple models.")
						[+] // else
							[ ] // Log.Fail("'Convert to Rigorous' is not displayed for simple models.")
					[+] // else
						[ ] // //Col 3
						[+] // if(sTemp2=="Revert to Simple")
							[ ] // Log.Pass("'Revert to Simple' is displayed for rigorous models.")
						[+] // else
							[ ] // Log.Fail("'Revert to Simple' is not displayed for rigorous models.")
				[ ] // //Col 2
				[ ] // lsHierarchy=GetAllDataInOneColumn(AH.dgGeneralTable,2)
				[+] // for(j=1;j<=ListCount(lsModels);j++)
					[+] // if(StrPos("@",lsModels[j])!=0)
						[ ] // lsModels[j]=SubStr(lsModels[j],1,StrPos("@",lsModels[j])-2)
					[+] // if(lsHierarchy[j]=="")
						[ ] // sPath="/UnitOps/"
					[+] // else if(lsHierarchy[j]=="FLOW-1 (TPL1)")
						[ ] // sPath="/UnitOps/FLOW-1/UnitOps/"
					[+] // else
						[ ] // sPath="/UnitOps/FLOW-1/UnitOps/{SubStr(lsHierarchy[j],1,StrPos("(",lsHierarchy[j])-2)}/UnitOps/"
					[ ] // lsSub=AH.GetModelsInABlock(sPath)
					[+] // if(ListFind(lsSub,lsModels[j])==0)
						[ ] // Log.Fail("Not find {lsModels[j]}")
						[ ] // break
					[ ] // sleep(1)
				[+] // if(j>ListCount(lsHierarchy))
					[ ] // Log.Pass("The heat exchangers in 1st level sub-flowsheet are displayed in the exactly sub-flowsheet name in 2nd column.")
				[+] // else
					[ ] // Log.Fail("The heat exchangers in 1st level sub-flowsheet are not displayed in the exactly sub-flowsheet name in 2nd column as expected.")
				[ ] // //Col 4
				[ ] // Print("Col4-------------------------------")
				[ ] // sBitmapDir=AH.CaptureBitmap("{sDataout}\Col4.bmp")
				[ ] // Log.Warning("Please check the screenshot '{sBitmapDir}' manually to make sure the number of each risk status and simple models are same as that in EDR dashboard..")
				[ ] // //Step 3 &4
				[-] // for(j=1;j<=3;j++)
					[ ] // AH.SetActive()
					[+] // for(k=ListCount(lsModels);k>=1;k--)
						[ ] // ListDelete(lsModels,k)
					[ ] // lsModels=GetAllDataInOneColumn(AH.dgGeneralTable,j)
					[ ] // AH.dgGeneralTable.Find("/WPFDataGridColumnHeader[{j+1}]").Click()
					[ ] // lsSort=GetAllDataInOneColumn(AH.dgGeneralTable,j)
					[ ] // ListSort(lsModels)
					[+] // if(lsModels==lsSort)
						[ ] // Log.Pass("Contents are sorted by ascending.")
					[-] // else
						[ ] // Log.Fail("Contents are not sorted by ascending.")
					[ ] // sleep(1)
					[ ] // AH.SetActive()
					[ ] // AH.dgGeneralTable.Find("/WPFDataGridColumnHeader[{j+1}]").Click()
					[ ] // lsSort=GetAllDataInOneColumn(AH.dgGeneralTable,j)
					[+] // if(ReverseList(lsModels)==lsSort)
						[ ] // Log.Pass("Contents are sorted by descending.")
					[+] // else
						[ ] // Log.Fail("Contents are not sorted by descending.")
					[ ] // sleep(1)
				[ ] // //Step 5
				[ ] // AH.SetActive()
				[ ] // AH.btnFilterHierarchy.Click()
				[+] // if(AH.lstGeneral.Exists(10))
					[ ] // AH.chkSelectAll.Uncheck()
					[ ] // sleep(1)
					[ ] // AH.chkRIG.Check()
					[ ] // sleep(1)
					[ ] // AH.btnPopupOK.Click()
					[ ] // sleep(1)
					[ ] // //Verification
					[ ] // lsModels=GetAllDataInOneColumn(AH.dgGeneralTable,1)
					[ ] // sPath="/UnitOps/FLOW-1/UnitOps/RIG/UnitOps/"
					[ ] // lsSub=AH.GetModelsInABlock(sPath)
					[+] // for(j=1;j<=ListCount(lsModels);j++)
						[+] // if(ListFind(lsSub,SubStr(lsModels[j],1,StrPos("@",lsModels[j])-2))==0)
							[ ] // Log.Fail("{SubStr(lsModels[j],1,StrPos("@",lsModels[j])-2)} is not under {sPath}, filter function wrong.")
							[ ] // break
						[ ] // sleep(1)
					[+] // if(j>ListCount(lsHierarchy))
						[ ] // Log.Pass("Filter funcation right for the 2nd column..")
				[+] // else
					[ ] // Log.Fail("Filter pop-up does not display.")
				[ ] // AH.SetActive()
				[ ] // AH.btnFilterHierarchy.Click()
				[+] // if(AH.lstGeneral.Exists(10))
					[ ] // AH.chkSelectAll.Check()
					[ ] // sleep(1)
					[ ] // AH.btnPopupOK.Click()
					[ ] // sleep(1)
				[+] // else
					[ ] // Log.Fail("Filter pop-up does not display.")
				[ ] // //Step 6
				[ ] // AH.SetActive()
				[ ] // AH.btnFilterStatus.Click()
				[-] // if(AH.lstGeneral.Exists(10))
					[ ] // AH.chkSelectAll.Uncheck()
					[ ] // sleep(1)
					[ ] // AH.chkConvertToRigorous.Check()
					[ ] // sleep(1)
					[ ] // AH.btnPopupOK.Click()
					[ ] // sleep(1)
					[ ] // //Verification
					[ ] // irow=ListCount(AH.dgGeneralTable.FindAll("/WPFDataGridRow"))
					[-] // for(j=1;j<=irow;j++)
						[ ] // sTemp1=AH.dgGeneralTable.Find("/WPFDataGridRow[{j}]//WPFDataGridCell[3]").TextCapture()
						[-] // if(sTemp1!="Convert to Rigorous")
							[ ] // Log.Fail("Filter function for Status column works wrong.")
							[ ] // break
					[-] // if(j>irow)
						[ ] // Log.Pass("Filter function for Status column works correctly.")
				[+] // else
					[ ] // Log.Fail("Filter pop-up does not display.")
				[ ] // AH.SetActive()
				[ ] // AH.btnFilterStatus.Click()
				[+] // if(AH.lstGeneral.Exists(10))
					[ ] // AH.chkSelectAll.Check()
					[ ] // sleep(1)
					[ ] // AH.btnPopupOK.Click()
					[ ] // sleep(1)
				[+] // else
					[ ] // Log.Fail("Filter pop-up does not display.")
				[ ] // //Step 7
				[ ] // lsModels=GetAllDataInOneColumn(AH.dgGeneralTable,1)
				[+] // for(j=1;j<=ListCount(lsModels);j++)
					[+] // if(lsModels[j]=="E-101")
						[ ] // AH.SetActive()
						[ ] // AH.dgGeneralTable.Find("//WPFTextBlock[@automationId='hyperlink'][{j}]/WPFTextBlock[@caption='E-101']").Click()
						[ ] // sleep(2)
						[+] // if(wHeatExchanger.Exists(10))
							[ ] // Log.Pass("The Heat Exchanger: E-101 dialog pops up.")
							[+] // if(wHeatExchanger.tpgRigorousShell.btnImport.Exists(3))
								[ ] // Log.Pass("The rigorous tab is displayed.")
							[+] // else
								[ ] // Log.Fail("The rigorous tab is not displayed.")
							[ ] // wHeatExchanger.Close()
						[+] // else
							[ ] // Log.Fail("The Heat Exchanger: E-101 dialog does not pop up.")
						[ ] // break
				[+] // if(j>ListCount(lsModels))
					[ ] // Log.Fail("Could not find model E-101.")
				[ ] // //Step 8
				[+] // for(j=1;j<=ListCount(lsModels);j++)
					[+] // if(lsModels[j]=="AC-100-2")
						[ ] // AH.SetActive()
						[ ] // AH.dgGeneralTable.Find("//WPFDataGridRow[8]").Find("//WPFDataGridCell[4]").Click()
						[+] // if(wOperationWarnings.Exists(15))
							[ ] // Log.Pass("The operation warning box pops up for AC-100-2.")
							[ ] // wOperationWarnings.SetActive()
							[+] // if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] // Log.Pass("The detail risk status for the variables are shown in the table.")
							[+] // else
								[ ] // Log.Fail("The detail risk status for the variables are not shown in the table as expected.")
								[ ] // Print("Expect:----------------------------------------")
								[ ] // ListPrint(lsPopHeaders)
								[ ] // Print("Actual:----------------------------------------")
								[ ] // ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
							[ ] // wOperationWarnings.SetActive()
							[ ] // wOperationWarnings.btnClose.Click()
						[+] // else
							[ ] // Log.Fail("The operation warning box for AC-100-2 does not  pop up as expected.")
						[ ] // break
				[+] // if(j>ListCount(lsModels))
					[ ] // Log.Fail("Could not find model AC-100-2.")
				[ ] // //Step 9&10&11
				[-] // for(i=1;i<=ListCount(lsModelType);i++)
					[-] // for(j=1;j<=ListCount(lsModels);j++)
						[-] // if(MatchStr("{lsModelType[i]}*",lsModels[j]))
							[ ] // AH.SetActive()
							[ ] // AH.dgGeneralTable.Find("//WPFDataGridRow[{i}]").Find("//WPFDataGridCell[4]").Click()
							[-] // if(wOperationWarnings.Exists(10))
								[ ] // Log.Pass("The operation warning box pops up for {lsModelType[i]} model type.")
								[ ] // wOperationWarnings.SetActive()
								[+] // if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
									[ ] // Log.Pass("The detail risk status for the variables are shown in the table.")
								[+] // else
									[ ] // Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
									[ ] // ListPrint(lsPopHeaders)
									[ ] // Log.Fail("Actual: ")
									[ ] // ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] // wOperationWarnings.SetActive()
								[ ] // wOperationWarnings.btnClose.Click()
							[-] // else
								[ ] // Log.Fail("The operation warning box for {lsModelType[i]} model type does not  pop up as expected.")
							[ ] // sleep(2)
							[ ] // break
			[+] // else
				[ ] // Log.Fail("Exchanger Summary Table does not appear.")
		[-] Print("Step 2: Click the Activated EDR dashboard to open the Exchanger Summary Table.")
			[ ] AH.SetActive()
			[ ] sleep(1)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[ ] AH.ctrlEDRDashboard.Click()
			[ ] sleep(2)
			[-] if(AH.tbiExchangerSummary.Exists(30))
				[ ] Log.Pass("Exchanger Summary Table appears.")
				[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Cols.bmp")
				[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually to make sure contents showing in each column are correct.")
				[ ] //Step 3 &4
				[+] for(j=1;j<=3;j++)
					[ ] AH.SetActive()
					[+] for(k=ListCount(lsModels);k>=1;k--)
						[ ] ListDelete(lsModels,k)
					[ ] lsModels=GetAllDataInOneColumn(AH.dgGeneralTable,j)
					[ ] AH.dgGeneralTable.Find("/WPFDataGridColumnHeader[{j+1}]").Click()
					[ ] lsSort=GetAllDataInOneColumn(AH.dgGeneralTable,j)
					[ ] ListSort(lsModels)
					[ ] print(lsModels)
					[+] if(lsModels==lsSort)
						[ ] Log.Pass("Contents are sorted by ascending.")
					[-] else
						[ ] Log.Fail("Contents are not sorted by ascending.")
					[ ] sleep(1)
					[ ] AH.SetActive()
					[ ] AH.dgGeneralTable.Find("/WPFDataGridColumnHeader[{j+1}]").Click()
					[ ] lsSort=GetAllDataInOneColumn(AH.dgGeneralTable,j)
					[ ] print(ReverseList(lsModels))
					[-] if(ReverseList(lsModels)==lsSort)
						[ ] Log.Pass("Contents are sorted by descending.")
					[-] else
						[ ] Log.Fail("Contents are not sorted by descending.")
					[ ] sleep(1)
				[ ] //Summary column Sorting
				[ ] AH.SetActive()
				[ ] AH.dgGeneralTable.Find("/WPFDataGridColumnHeader[5]").Click()
				[ ] sleep(1)
				[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Summary_Asc.bmp")
				[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for confirming contents are sorted by ascending.")
				[ ] AH.SetActive()
				[ ] AH.dgGeneralTable.Find("/WPFDataGridColumnHeader[5]").Click()
				[ ] sleep(1)
				[ ] sBitmapDir=AH.CaptureBitmap("{sDataout}\Summary_Des.bmp")
				[ ] Log.Warning("Please check the screenshot '{sBitmapDir}' manually for confirming contents are sorted by descending.")
				[ ] //Step 5
				[ ] AH.SetActive()
				[ ] AH.btnFilterHierarchy.Click()
				[+] if(AH.lstGeneral.Exists(10))
					[ ] AH.chkSelectAll.Uncheck()
					[ ] sleep(1)
					[ ] AH.chkRIG.Check()
					[ ] sleep(1)
					[ ] AH.btnPopupOK.Click()
					[ ] sleep(1)
					[ ] //Verification
					[ ] lsModels=GetAllDataInOneColumn(AH.dgGeneralTable,1)
					[ ] sPath="/UnitOps/FLOW-1/UnitOps/RIG/UnitOps/"
					[ ] lsSub=AH.GetModelsInABlock(sPath)
					[-] for(j=1;j<=ListCount(lsModels);j++)
						[-] if(ListFind(lsSub,SubStr(lsModels[j],1,StrPos("@",lsModels[j])-2))==0)
							[ ] Log.Fail("{SubStr(lsModels[j],1,StrPos("@",lsModels[j])-2)} is not under {sPath}, filter function wrong.")
							[ ] break
						[ ] sleep(1)
					[+] if(j>ListCount(lsHierarchy))
						[ ] Log.Pass("Filter funcation right for the 2nd column..")
				[+] else
					[ ] Log.Fail("Filter pop-up does not display.")
				[ ] AH.SetActive()
				[ ] AH.btnFilterHierarchy.Click()
				[-] if(AH.lstGeneral.Exists(10))
					[ ] AH.chkSelectAll.Check()
					[ ] sleep(1)
					[ ] AH.btnPopupOK.Click()
					[ ] sleep(3)
				[+] else
					[ ] Log.Fail("Filter pop-up does not display.")
				[ ] //Step 6
				[ ] AH.SetActive()
				[ ] AH.btnFilterStatus.Click()
				[-] if(AH.lstGeneral.Exists(10))
					[ ] AH.chkSelectAll.Uncheck()
					[ ] sleep(1)
					[ ] AH.chkConvertToRigorous.Check()
					[ ] sleep(1)
					[ ] AH.btnPopupOK.Click()
					[ ] sleep(1)
					[ ] //Verification
					[ ] irow=ListCount(AH.dgGeneralTable.FindAll("/WPFDataGridRow"))
					[-] for(j=1;j<=irow;j++)
						[ ] sTemp1=AH.dgGeneralTable.Find("/WPFDataGridRow[{j}]//WPFDataGridCell[3]").TextCapture()
						[-] if(sTemp1!="Convert to Rigorous")
							[ ] Log.Fail("Filter function for Status column works wrong.")
							[ ] break
					[+] if(j>irow)
						[ ] Log.Pass("Filter function for Status column works correctly.")
				[-] else
					[ ] Log.Fail("Filter pop-up does not display.")
				[ ] AH.SetActive()
				[ ] AH.btnFilterStatus.Click()
				[+] if(AH.lstGeneral.Exists(10))
					[ ] AH.chkSelectAll.Check()
					[ ] sleep(1)
					[ ] AH.btnPopupOK.Click()
					[ ] sleep(1)
				[+] else
					[ ] Log.Fail("Filter pop-up does not display.")
				[ ] //Step 7
				[ ] lsModels=GetAllDataInOneColumn(AH.dgGeneralTable,1)
				[-] for(j=1;j<=ListCount(lsModels);j++)
					[+] if(lsModels[j]=="E-101")
						[ ] AH.SetActive()
						[ ] AH.dgGeneralTable.Find("//WPFTextBlock[@automationId='hyperlink'][{j}]/WPFTextBlock[@caption='E-101']").Click()
						[ ] sleep(2)
						[+] if(wHeatExchanger.Exists(10))
							[ ] Log.Pass("The Heat Exchanger: E-101 dialog pops up.")
							[+] if(wHeatExchanger.tpgRigorousShell.btnImport.Exists(3))
								[ ] Log.Pass("The rigorous tab is displayed.")
							[+] else
								[ ] Log.Fail("The rigorous tab is not displayed.")
							[ ] wHeatExchanger.Close()
						[+] else
							[ ] Log.Fail("The Heat Exchanger: E-101 dialog does not pop up.")
						[ ] break
				[+] if(j>ListCount(lsModels))
					[ ] Log.Fail("Could not find model E-101.")
				[ ] //Step 8&9&10&11
				[-] for(i=1;i<=ListCount(lsModelType);i++)
					[-] for(j=1;j<=ListCount(lsModels);j++)
						[-] if(MatchStr("{lsModelType[i]}*",lsModels[j]) )
							[ ] AH.SetActive()
							[ ] AH.dgGeneralTable.Find("//WPFDataGridRow[{j}]").Find("//WPFDataGridCell[4]").Click()
							[-] if(wOperationWarnings.Exists(10))
								[ ] Log.Pass("The operation warning box pops up for {lsModelType[i]} model type.")
								[ ] wOperationWarnings.SetActive()
								[-] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
									[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
								[+] else
									[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
									[ ] ListPrint(lsPopHeaders)
									[ ] Log.Fail("Actual: ")
									[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] wOperationWarnings.SetActive()
								[ ] wOperationWarnings.btnClose.Click()
							[-] else
								[ ] Log.Fail("The operation warning box for {lsModelType[i]} model type does not  pop up as expected.")
							[ ] sleep(2)
							[ ] break
						[-] // else if(MatchStr("{lsModelType[i]}*",lsModels[j]) && i==3)
							[ ] // AH.SetActive()
							[ ] // AH.dgGeneralTable.Find("//WPFDataGridRow[{j}]").Find("//WPFDataGridCell[4]").Click()
							[-] // if(wOperationWarnings.Exists(10))
								[ ] // Log.Pass("The operation warning box pops up for {lsModelType[i]} model type.")
								[ ] // wOperationWarnings.SetActive()
								[+] // if(lsPopHeadersFH==GetAllDataInOneColumn(wOperationWarnings,1))
									[ ] // Log.Pass("The detail risk status for the variables are shown in the table.")
								[+] // else
									[ ] // Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
									[ ] // ListPrint(lsPopHeaders)
									[ ] // Log.Fail("Actual: ")
									[ ] // ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] // wOperationWarnings.SetActive()
								[ ] // wOperationWarnings.btnClose.Click()
							[-] // else
								[ ] // Log.Fail("The operation warning box for {lsModelType[i]} model type does not  pop up as expected.")
							[ ] // sleep(2)
							[ ] // break
						[ ] 
			[+] else
				[ ] Log.Fail("Exchanger Summary Table does not appear.")
		[ ] Print("Step 3: Click the headline of the Exchanger Name column, the Exchanger Name in the summary table will be sorted by ascending. Click the headline again; the Exchanger Name in the summary table will be sorted by descending.")
		[ ] Print("Step 4: Repeat Step 3 for the other columns, ‘Subflowsheet’, ‘Model Status’ and ‘Summary’ column.")
		[ ] Print("Step 5: Click the arrow button in the Subflowsheet column; select one of the filter options. E.g. RIG(TPL3).")
		[ ] Print("Step 6: Repeat Step 5 for Model Status and Operation Risk Status column.")
		[ ] Print("Step 7: Click the link for E-101 in Exchanger Name column, the Heat Exchanger: E-101 dialog will pop up and the Rigorous tab is displayed for E-101 will pop up")
		[ ] Print("Step 8: Click the traffic light button of AC-100-2 in Summary column, the Operation Warnings form for AC-100-2 will pop up.")
		[ ] Print("Step 9: Click Close button, the Operation Warnings form will be closed")
		[ ] Print("Step 10: Repeat step 8-9 for the Shell&Tube, FiredHeater and PlateFin models")
		[ ] Print("Step 11: Click Close button, the Exchanger Summary Table is closed")
		[ ] 
	[ ] 
[ ] 
[ ] 
[ ] 
[+] testcase debug() appstate none
	[ ] int irow,j,i
	[ ] string sTemp1
	[ ] list of string lsModels
	[-] list of string lsModelType={...}
		[ ] "AC-100-2"
		[ ] "E-101"
		[ ] //"FH-"
		[ ] "LNG-101"
	[-] list of string lsPopHeaders={...}
		[ ] "Pressure"
		[ ] "Temperature"
		[ ] "Vibration"
		[ ] "Erosion: RhoV2"
		[ ] "Heat Transfer"
		[ ] "Pressure Drop"
		[ ] "Flow"
		[ ] "Other"
	[-] list of string lsPopHeadersFH={...}
		[ ] "Pressure"
		[ ] "Temperature"
		[ ] ""
		[ ] ""
		[ ] ""
		[ ] ""
		[ ] "Combustion"
		[ ] "Heat Transfer"
		[ ] "Pressure Drop"
		[ ] "Flow"
		[ ] ""
	[ ] 
	[-] 
		[-] AH.SetActive()
				[ ] lsModels=GetAllDataInOneColumn(AH.dgGeneralTable,1)
				[-] for(j=1;j<=ListCount(lsModels);j++)
					[-] if(lsModels[j]=="E-101")
						[ ] AH.SetActive()
						[ ] AH.dgGeneralTable.Find("//WPFTextBlock[@automationId='hyperlink'][{j}]/WPFTextBlock[@caption='E-101']").Click()
						[ ] sleep(2)
						[-] if(wHeatExchanger.Exists(10))
							[ ] Log.Pass("The Heat Exchanger: E-101 dialog pops up.")
							[-] if(wHeatExchanger.tpgRigorousShell.btnImport.Exists(3))
								[ ] Log.Pass("The rigorous tab is displayed.")
							[+] else
								[ ] Log.Fail("The rigorous tab is not displayed.")
							[ ] wHeatExchanger.Close()
						[+] else
							[ ] Log.Fail("The Heat Exchanger: E-101 dialog does not pop up.")
						[ ] break
				[+] if(j>ListCount(lsModels))
					[ ] Log.Fail("Could not find model E-101.")
				[ ] //Step 8&9&10&11
				[-] for(i=1;i<=ListCount(lsModelType);i++)
					[-] for(j=1;j<=ListCount(lsModels);j++)
						[-] if(MatchStr("{lsModelType[i]}*",lsModels[j]) && i!=3)
							[ ] AH.SetActive()
							[ ] AH.dgGeneralTable.Find("//WPFDataGridRow[{j}]").Find("//WPFDataGridCell[4]").Click()
							[-] if(wOperationWarnings.Exists(10))
								[ ] Log.Pass("The operation warning box pops up for {lsModelType[i]} model type.")
								[ ] wOperationWarnings.SetActive()
								[-] if(lsPopHeaders==GetAllDataInOneColumn(wOperationWarnings,1))
									[ ] Log.Pass("The detail risk status for the variables are shown in the table.")
								[+] else
									[ ] Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
									[ ] ListPrint(lsPopHeaders)
									[ ] Log.Fail("Actual: ")
									[ ] ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] wOperationWarnings.SetActive()
								[ ] wOperationWarnings.btnClose.Click()
							[-] else
								[ ] Log.Fail("The operation warning box for {lsModelType[i]} model type does not  pop up as expected.")
							[ ] sleep(2)
							[ ] break
						[-] // else if(MatchStr("{lsModelType[i]}*",lsModels[j]) && i==3)
							[ ] // AH.SetActive()
							[ ] // AH.dgGeneralTable.Find("//WPFDataGridRow[{j}]").Find("//WPFDataGridCell[4]").Click()
							[-] // if(wOperationWarnings.Exists(10))
								[ ] // Log.Pass("The operation warning box pops up for {lsModelType[i]} model type.")
								[ ] // wOperationWarnings.SetActive()
								[-] // if(lsPopHeadersFH==GetAllDataInOneColumn(wOperationWarnings,1))
									[ ] // Log.Pass("The detail risk status for the variables are shown in the table.")
								[-] // else
									[ ] // Log.Fail("The detail risk status for the variables are not shown in the table as expected.Expect:")
									[ ] // ListPrint(lsPopHeaders)
									[ ] // Log.Fail("Actual: ")
									[ ] // ListPrint(GetAllDataInOneColumn(wOperationWarnings,1))
								[ ] // wOperationWarnings.SetActive()
								[ ] // wOperationWarnings.btnClose.Click()
							[-] // else
								[ ] // Log.Fail("The operation warning box for {lsModelType[i]} model type does not  pop up as expected.")
							[ ] // sleep(2)
							[ ] // break
	[ ] 
