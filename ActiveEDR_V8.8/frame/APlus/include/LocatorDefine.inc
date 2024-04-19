[ ] 
[ ] String WPFRepeatButton_ZoomIn_Locator = "//WPFRepeatButton[@automationId='PART_ZoomInButton']"
[ ] String WPFRepeatButton_ZoomOut_Locator = "//WPFRepeatButton[@automationId='PART_ZoomOutButton']"
[+] //wcContextMenuManager Variables
	[ ]  String ContextMenuLocator = "//WPFContextMenu"
[ ] 
[+] //wcDefineSubStreamDataGrid Variables
	[ ]  String WPFContentControl_ClmHeaderArea_Locator="//WPFContentControl[@className='HeaderLabelArea']"
	[ ]  String WPFContentControl_AllOfClmHeader_Locator="//WPFContentControl[(@name='LabelContent' and @caption='*')]"
	[ ]  String WPFComboBox_cbLastComboBoxCell_Locator="//WPFComboBox[@automationId='PART_FocusSite']"
[ ] 
[+] //wcListBoxItemsExchange Variables
	[ ]  String WPFListBox_lbxSrc_Locator="//WPFListBox[@automationId='Part_OptionsBox']"
	[ ]  String WPFListBox_lbxDest_Locator="//WPFListBox[@automationId='Part_SelectionBox']"
	[ ]  String WPFButton_AddtoDest_Locator="WPFButton[@automationId='Move Right']"
	[ ]  String WPFButton_AddAlltoDest_Locator="WPFButton[@automationId='PART_AddAll']"
	[ ]  String WPFButton_RmFromDest_Locator="WPFButton[@automationId='Move Left']"
	[ ]  String WPFButton_RmAllFromDest_Locator="WPFButton[@automationId='PART_RemoveAll']"
	[ ] 
[ ] 
[+] //wcPSDMeshSetting Variables
	[ ]  String WPFComboBox_cbCombobox_Locator="//WPFComboBox[@automationId='PART_FocusSite']"
	[ ]  String WPFTextBox_tbTextBox_Locator="//WPFTextBox[@automationId='PART_TextBox']"
	[ ]  String WPFButton_btnCreatePSDMesh_Locator="//WPFButton[@caption='Create PSD Mesh']"
	[ ]  String wcDefineSubStreamDataGrid_dgParticleSizeDistributionMesh_Locator="//WPFControl[@automationId='PART_DataGrid']"
	[ ]  String WPFToggleButton_MeshType_Locator="//WPFControl[@automationId='PART_editControl'][2]/WPFToggleButton[@automationId='PART_DropDownButton']"
	[ ]  String WPFToggleButton_SizeUnits_Locator="//WPFControl[@automationId='PART_editControl'][6]/WPFToggleButton[@automationId='PART_DropDownButton']"
	[ ]  String WPFControl_IntervalNo_Locator="//WPFControl[@automationId='PART_editControl'][3]"
	[ ]  String WPFControl_LowerLimit_Locator="//WPFControl[@automationId='PART_editControl'][4]"
	[ ]  String WPFControl_UpperLimit_Locator="//WPFControl[@automationId='PART_editControl'][5]"
	[ ] 
[+] //wcSimulationSetupSolids Variables
	[ ]  String WPFContentControl_SolidCharacterization_Header_Locator="//WPFLabel[@caption='Solid Characterization']/../.."
	[ ] 
	[ ]  String WPFContentControl_PSDMesh_Header_Locator="//WPFLabel[@caption='PSD Mesh']/../.."
	[ ]  String wcAPDataGrid_PSDMesh_dgPsdMesh_Locator="//WPFControl[@automationId='PART_DataGrid']"
	[ ]  String WPFButton_PSDMesh_btnNew_Locator="//WPFButton[@caption='New...']"
	[ ]  String WPFButton_PSDMesh_btnEdit_Locator="//WPFButton[@caption='Edit']"
	[ ]  String WPFButton_PSDMesh_btnDelete_Locator="//WPFButton[@caption='Delete']"
	[ ]  String WPFButton_PSDMesh_btnCopy_Locator="//WPFButton[@caption='Copy']"
	[ ]  String WPFButton_PSDMesh_btnRename_Locator="//WPFButton[@caption='Rename']"
	[ ]  String WPFButton_PSDMesh_btnPaste_Locator="//WPFButton[@caption='Paste']"
	[ ] 
	[ ]  String WPFContentControl_Substreams_Locator="//WPFLabel[@caption='Substreams']/../.."
	[ ]  String wcDefineSubStreamDataGrid_dgDefineSubStream_Locator="//WPFControl[@automationId='PART_DataGrid']"
	[ ]   
	[ ]  String WPFContentControl_ScrollViewCtl_Locator="//WPFContentControl[@automationId='MMTabPage_1']"
[ ] 
[ ] 
[+] //wcSimulationSetupSolids_SA Variables
	[ ]  String WPFContentControl_Mesh_Header_Locator="//WPFLabel[@caption='Mesh']/../.."
	[ ]  String WPFContentControl_Information_Header_Locator="//WPFLabel[@caption='Information']/../.."
	[ ] 
[ ] 
[+] //wcSimulationStreamsWETCOAL_Input Variables
	[ ]  String WPFContentControl_Mixed_Header_Locator="//WPFLabel[@caption='Mixed']/../.."
	[ ]  String WPFContentControl_CISolid_Header_Locator="//WPFLabel[@caption='CI Solid']/../.."
	[ ] 
	[ ]  String WPFContentControl_NCSolid_Header_Locator="//WPFLabel[@caption='NC Solid']/../.."
	[ ]  String WPFComboBox_NCSolid_cbCombobox_Locator="//WPFComboBox[@automationId='PART_FocusSite']"
	[ ]  String WPFToggleButton_NCSolid_btnParticleSizeDistribution_Locator="//WPFToggleButton[@caption='Particle Size Distribution']"
	[ ]  String WPFButton_NCSolid_EditPSDMesh_Locator="//WPFButton[@caption='Edit PSD Mesh']"
	[ ]  String WPFToggleButton_NCSolid_PSDMeshID_Locator="//WPFControl[@automationId='PART_editControl'][12]/WPFToggleButton[@automationId='PART_DropDownButton']"
	[ ]  String wcAPDataGrid_NCSolid_dgDataGrid_Locator="//WPFControl[@automationId='PART_DataGrid'][2]"
	[ ]  String WPFRadioButton_NCSolid_rbtnADistFunction_Locator="//WPFRadioButton[@automationId='MMOptionButton_2']"
	[ ]  String WPFRadioButton_NCSolid_rbtnUserspecifiedValues_Locator="//WPFRadioButton[@automationId='MMOptionButton_1']"
	[ ]  String WPFToggleButton_NCSolid_DistFunctionType_Locator="//WPFControl[@automationId='PART_editControl'][14]/WPFToggleButton[@automationId='PART_DropDownButton']"
	[ ]  String WPFControl_NCSolid_DispersionParam_Locator="//WPFControl[@automationId='PART_editControl'][15]"
	[ ]  String WPFControl_NCSolid_MaximumDiameter_Locator="//WPFControl[@automationId='PART_editControl'][16]"
	[ ]  String WPFToggleButton_NCSolid_DiameterUnits_Locator="//WPFControl[@automationId='PART_editControl'][17]/WPFToggleButton[@automationId='PART_DropDownButton']"
	[ ]  String WPFTextBox_NCSolid_tbTextBox_Locator="//WPFTextBox[@automationId='PART_TextBox']"
	[ ]  String WPFButton_NCSolid_btnCalculate_Locator="//WPFButton[@caption='Calculate']"
	[ ]  String WPFToggleButton_NCSolid_DistFunctionTypeLabel_Locator="//WPFLabel[@caption='Type of distribution function:']/../.."
	[ ]  String WPFToggleButton_NCSolid_D63Label_Locator="//WPFLabel[@caption='D63']/../.."
	[ ]  String WPFContentControl_FlashOptions_Header_Locator="//WPFLabel[@caption='Flash Options']/../.."
	[ ]  String WPFContentControl_EOOptions_Header_Locator="//WPFLabel[@caption='EO Options']/../.."
	[ ]  String WPFContentControl_Costing_Header_Locator="//WPFLabel[@caption='Costing']/../.."
	[ ] //String WPFContentControl_Information_Header_Locator="//WPFLabel[@caption='Information']/../.."
	[ ] 
[ ] 
