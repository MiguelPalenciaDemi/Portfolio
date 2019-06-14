--Made by Miguel Palencia de Miguel miguelpalenciademi@gmail.com






--State
last_state = 1
--Arrays temporales
staticArray_values= #(true,false,false,false,false,false,false,false,false,false,false,false)
skeletalArray = #(true,false,false,false,false,false,false,false,false,true,true,true)
animArray = #(false,false,false,false,false,false,false,true,true,false,true,true)

function hasTag  obj = 
(
	if (findString obj.name "SM_"==1) or (findString obj.name "SK_"==1) or (findString obj.name "AN_"==1) then 
	(		
		return true
	)
		
	return false


)

function returnType obj = 
(
	case of
	(
		(findString obj.name "SM_"==1):return 1
		
		(findString obj.name "SK_"==1):return 2

		(findString obj.name "SA_"==1): return 3

		default: return 0

	)
)


try(destroyDialog FBXExport) catch()

rollout FBXExport "Export FBX" width:415 height:616
(
	button 'bt1' "Create Assets" pos:[17,53] width:365 height:42 align:#left
	label 'lbl1' "FBX Export" pos:[152,21] width:160 height:32 align:#left
	radiobuttons 'rdo1' "Asset Type" pos:[45,122] width:301 height:30 labels:#("Static Mesh", "Skeletal Mesh", "Animation") columns:3 align:#left
	GroupBox 'grp2' "Export Settings" pos:[35,185] width:344 height:267 align:#left
	checkbox 'chk1' "Smoothing Groups" pos:[40,208] width:112 height:16 align:#left
	checkbox 'chk2' "Split per-vertex Normals" pos:[40,228] width:112 height:16 align:#left
	checkbox 'chk3' "Tangents and binormals" pos:[40,248] width:112 height:16 align:#left
	checkbox 'chk4' "Turbosmooth" pos:[40,268] width:112 height:16 align:#left
	checkbox 'chk5' "Preserve Instances" pos:[40,208] width:112 height:16 align:#left
	checkbox 'chk6' "Selection Sets" pos:[40,288] width:112 height:16 align:#left
	checkbox 'chk7' "Convert Deforming Dummies to bones" pos:[40,308] width:112 height:16 align:#left
	checkbox 'chk8' "Animation" pos:[40,328] width:112 height:16 align:#left
	checkbox 'chk9' "Bake Animation" pos:[40,348] width:112 height:16 align:#left
	checkbox 'chk10' "Deformations" pos:[40,368] width:112 height:16 align:#left
	checkbox 'chk11' "Skins" pos:[40,388] width:112 height:16 align:#left
	checkbox 'chk12' "Morphs" pos:[40,408] width:112 height:16 align:#left
	GroupBox 'grp5' "Export Folder" pos:[36,465] width:342 height:64 align:#left
	edittext 'path' "" pos:[47,496] width:270 height:18 align:#left
	button 'btn5' "..." pos:[326,495] width:31 height:18 align:#left
	button 'btn6' "Export" pos:[36,549] width:168 height:31 align:#left
	button 'btn7' "Save Export Settings" pos:[214,549] width:168 height:31 align:#left
	
	function checkCheckBox = 
	(

		case of 
			(
				(last_state == 1): 
				(
					chk1.checked = staticArray_values[1]
					chk2.checked = staticArray_values[2]
					chk3.checked = staticArray_values[3]
					chk4.checked = staticArray_values[4]
					chk5.checked = staticArray_values[5]
					chk6.checked = staticArray_values[6]
					chk7.checked = staticArray_values[7]
					chk8.checked = staticArray_values[8]
					chk9.checked = staticArray_values[9]
					chk10.checked = staticArray_values[10]
					chk11.checked = staticArray_values[11]
					chk12.checked = staticArray_values[12] 
				)
				(last_state == 2): 
				(
					chk1.checked = skeletalArray[1]
					chk2.checked = skeletalArray[2]
					chk3.checked = skeletalArray[3]
					chk4.checked = skeletalArray[4]
					chk5.checked = skeletalArray[5]
					chk6.checked = skeletalArray[6]
					chk7.checked = skeletalArray[7]
					chk8.checked = skeletalArray[8]
					chk9.checked = skeletalArray[9]
					chk10.checked = skeletalArray[10]
					chk11.checked = skeletalArray[11]
					chk12.checked = skeletalArray[12] 
				)
				(last_state == 3): 
				(
					chk1.checked = animArray[1]
					chk2.checked = animArray[2]
					chk3.checked = animArray[3]
					chk4.checked = animArray[4]
					chk5.checked = animArray[5]
					chk6.checked = animArray[6]
					chk7.checked = animArray[7]
					chk8.checked = animArray[8]
					chk9.checked = animArray[9]
					chk10.checked = animArray[10]
					chk11.checked = animArray[11]
					chk12.checked = animArray[12] 
				)
			)

	)





	function saveCheckBox = 
	(

		case of 
			(
				(last_state == 1): 
				(
					staticArray_values[1] = chk1.checked
					staticArray_values[2] = chk2.checked
					staticArray_values[3] = chk3.checked
					staticArray_values[4] = chk4.checked
					staticArray_values[5] = chk5.checked
					staticArray_values[6] = chk6.checked
					staticArray_values[7] = chk7.checked
					staticArray_values[8] = chk8.checked
					staticArray_values[9] = chk9.checked
					staticArray_values[10] = chk10.checked
					staticArray_values[11] = chk11.checked
					staticArray_values[12] = chk12.checked 
				)
				(last_state == 2): 
				(
					skeletalArray[1] = chk1.checked
					skeletalArray[2] = chk2.checked
					skeletalArray[3] = chk3.checked
					skeletalArray[4] = chk4.checked
					skeletalArray[5] = chk5.checked
					skeletalArray[6] = chk6.checked
					skeletalArray[7] = chk7.checked
					skeletalArray[8] = chk8.checked
					skeletalArray[9] = chk9.checked
					skeletalArray[10] = chk10.checked
					skeletalArray[11] = chk11.checked
					skeletalArray[12] = chk12.checked 
				)
				(last_state == 3): 
				(
					animArray[1] = chk1.checked
					animArray[2] = chk2.checked
					animArray[3] = chk3.checked
					animArray[4] = chk4.checked
					animArray[5] = chk5.checked
					animArray[6] = chk6.checked
					animArray[7] = chk7.checked
					animArray[8] = chk8.checked
					animArray[9] = chk9.checked
					animArray[10] = chk10.checked
					animArray[11] = chk11.checked
					animArray[12] = chk12.checked 
				)
			)
	)
	
	function setGeo obj arrGeo putGeo = 
	(
		if (putGeo == true) then
		(
			for chd in arrGeo do 
			(
				chd.parent = undefined
			)
		)
		else 
		(
			for chd in arrGeo do 
			(
				chd.parent = obj.children[1]
			)
		)
	
		

	)

	function getGeo arrGeo obj = 
	(
		
		for index = 1 to obj.children[1].count do 
		(			
			append arrGeo obj.children[1].children[index]
			
		)
		

	)

	function getJoints arrJoints arrChd = 
	(
		
		for index = 1 to obj.children[2].count do 
		(			
			append arrJoints obj.children[2].children[index]
			
		)
		

	)

	function getRigs arrRigs arrChd = 
	(
		
		for index = 1 to obj.children[3].count do 
		(			
			append arrRigs obj.children[3].children[index]
			
		)
		

	)

	function setJoints obj arrJoints putJoints = 
	(
		if (putJoints == true) then
		(
			for chd in arrJoints  do 
			(
				chd.parent = undefined
			)
		)
		else 
		(
			for chd in arrJoints  do 
			(
				chd.parent = obj.children[2]
			)
		)
	
		

	)

	function setRigs obj arrRigs putRigs = 
	(
		if (putRigs == true) then
		(
			for chd in arrRigs  do 
			(
				chd.parent = undefined
			)
		)
		else 
		(
			for chd in arrRigs  do 
			(
				chd.parent = obj.children[3]
			)
		)
	
		

	)

	function SetParameterFBX obj  = 
	(		
		case of
		(
			(returnType obj == 1):
			(
				FBXExporterSetParam  "SmoothingGroups" staticArray_values[1]
				FBXExporterSetParam  "NormalsPerPoly" staticArray_values[2]
				FBXExporterSetParam  "TangentSpaceExport" staticArray_values[3]
				FBXExporterSetParam  "SmoothMeshExport" staticArray_values[4]
				FBXExporterSetParam  "Preserveinstances" staticArray_values[5]
				FBXExporterSetParam  "SelectionSetExport" staticArray_values[6]
				FBXExporterSetParam  "SelectionSetExport" staticArray_values[7]
				FBXExporterSetParam  "Animation" staticArray_values[8]
				FBXExporterSetParam  "BakeAnimation" staticArray_values[9]

				--Deformations
				if( staticArray_values[10]) then 
				(
					FBXExporterSetParam  "Skin" true
					FBXExporterSetParam  "Shape" true
				)else 
				(
					FBXExporterSetParam  "Skin" staticArray_values[11]
					FBXExporterSetParam  "Shape" staticArray_values[12]
				)

			)

			(returnType obj == 2):
			(
				FBXExporterSetParam  "SmoothingGroups" skeletalArray[1]
				FBXExporterSetParam  "NormalsPerPoly" skeletalArray[2]
				FBXExporterSetParam  "TangentSpaceExport" skeletalArray[3]
				FBXExporterSetParam  "SmoothMeshExport" skeletalArray[4]
				FBXExporterSetParam  "Preserveinstances" skeletalArray[5]
				FBXExporterSetParam  "SelectionSetExport" skeletalArray[6]
				FBXExporterSetParam  "SelectionSetExport" skeletalArray[7]
				FBXExporterSetParam  "Animation" skeletalArray[8]
				FBXExporterSetParam  "BakeAnimation" skeletalArray[9]

				--Deformations
				if( skeletalArray[10]) then 
				(
					FBXExporterSetParam  "Skin" true
					FBXExporterSetParam  "Shape" true
				)else 
				(
					FBXExporterSetParam  "Skin" skeletalArray[11]
					FBXExporterSetParam  "Shape" skeletalArray[12]
				)

			)

			(returnType obj == 3):
			(
				FBXExporterSetParam  "SmoothingGroups" animArray[1]
				FBXExporterSetParam  "NormalsPerPoly" animArray[2]
				FBXExporterSetParam  "TangentSpaceExport" animArray[3]
				FBXExporterSetParam  "SmoothMeshExport" animArray[4]
				FBXExporterSetParam  "Preserveinstances" animArray[5]
				FBXExporterSetParam  "SelectionSetExport" animArray[6]
				FBXExporterSetParam  "SelectionSetExport" animArray[7]
				FBXExporterSetParam  "Animation" animArray[8]
				FBXExporterSetParam  "BakeAnimation" animArray[9]

				--Deformations
				if( animArray[10]) then 
				(
					FBXExporterSetParam  "Skin" true
					FBXExporterSetParam  "Shape" true
				)else 
				(
					FBXExporterSetParam  "Skin" animArray[11]
					FBXExporterSetParam  "Shape" animArray[12]
				)

			)


		)
		
		
		
	

	)

	on FBXExport open do
	(
		rdo1.state = last_state
		checkCheckBox()
		btn6.enabled = false
	)
	on bt1 pressed do
	(
		tag = "SM_"
		case of
		(
			(rdo1.state == 1): tag="SM_"
			(rdo1.state == 2): tag="SK_"
			(rdo1.state == 3): tag="AN_"
			
		)
		
		differentObjects = selection as array

		--Define variables
			parentPoint
			joints
			rig
			geo


		
		if(differentObjects.count>0) then 
		(

			
			create = false
			
			
			for obj in differentObjects do
			(
				if obj.parent == undefined then
				(
					if create == false do 
					(
						parentPoint = Point name: (tag+obj.name) pos:[0,0,0]
						joints = Point name: "joints" pos:[0,0,0]
						rig = Point name: "rig" pos:[0,0,0]
						geo = Point name: "geo" pos:[0,0,0]
						joints.parent = parentPoint
						rig.parent = parentPoint
						geo.parent = parentPoint
						create = true
					)	

					
					obj.parent = parentPoint	
				) 			
				
			)
		)
		else 
		(
			parentPoint = Point name: (tag+"newObject") pos:[0,0,0]
			joints = Point name: "joints" pos:[0,0,0]
			rig = Point name: "rig" pos:[0,0,0]
			geo = Point name: "geo" pos:[0,0,0]
	
			joints.parent = parentPoint
			rig.parent = parentPoint
			geo.parent = parentPoint
			
		)
		
		
	
	)
	on rdo1 changed stat do
	(
		tag = "SM_"
		case of
		(
			(rdo1.state == 1): tag="SM_"
			(rdo1.state == 2): tag="SK_"
			(rdo1.state == 3): tag="AN_"
			
		)
		differentObjects = getCurrentSelection()
		for obj in differentObjects do 
		(
			
			print obj as string
			classof obj
			if (obj.parent == undefined and (hasTag obj) and classof obj == Point ) then 
			(				
				_name = substring obj.name 4 (obj.name.count-3)
				obj.name = (tag+_name)
				nameFile = obj.name
			)
		
		)
		
		
		saveCheckBox()
		last_state = rdo1.state
	
		checkCheckBox()
	
	
	)
	on path entered text do
	(
		if(path.text != "") then
		(
			if(doesFileExist path.text) then
			(
				btn6.enabled = true
			)
			else 
			(
				btn6.enabled = false
			)
			
		)
			
		else
		(
			btn6.enabled = false
		)
			
		
	)
	on btn5 pressed do
	(
		txt = getSavePath caption:"Choose root" initialDir: "C/:"
		if (txt != undefined and txt != "" ) then
		(
			path.text = txt
			btn6.enabled = true
		) else
		(
			if(doesFileExist path.text) then
			(
				btn6.enabled = true
			)else
			(btn6.enabled = false)
		)
			
		
		
	)

	function getAllChildren parentObj arraySelected = 
	(
		for child in parentObj.children do
		(
 			append arraySelected child
			 if(child.children.count>0)then 
			 (
				 getAllChildren child arraySelected
			 )
		)
                       

	)

	function setAllChildrenHerarchy parentObj arraySelected _exported = 
	(
		if (_exported == false)then
		(
			for child in parentObj.children do
			(
				child.parent = undefined
			)
		)
		else 
		(
			for child in arraySelected do
			(
				if(child.parent == undefined) then
					child.parent = parentObj
			)
		)
		
                       

	)

	on btn6 pressed do
	(
		differentObjects = selection as array
		
		if(differentObjects.count>0) then 
		(
			for obj in differentObjects do
			(
				if obj.parent == undefined and hasTag obj then
				(
					parentGeo
					parentJoint
					parentRig
					
					for chd in obj.children do 
					(
						case of
						(
							(chd.name == "geo"): parentGeo = chd
							(chd.name == "joints"): parentJoint = chd
							(chd.name == "rig"): parentRig = chd
						)
					)

					arrayGeo = #()

					getAllChildren parentGeo arrayGeo
					setAllChildrenHerarchy parentGeo arrayGeo false

					
					arrayJoints= #()
					getAllChildren parentJoint arrayJoints
					setAllChildrenHerarchy parentJoint arrayJoints false					
					
					arrayRigs= #()	
					getAllChildren parentRig arrayRigs
					setAllChildrenHerarchy parentRig arrayRigs false			
					

					
					
					
					SetParameterFBX obj 
					exportPath = path.text+"/"+ obj.name
					
					
					case of
					(
						(returnType obj == 1 ): select arrayGeo 
						(returnType obj == 2 ): 
						(
							select arrayGeo 
							selectMore arrayJoints 
						
						)
						(returnType obj == 3 ):
						(
							select arrayGeo 
							selectMore arrayJoints 
							selectMore arrayRigs 
						
						)
					)					
					
					exportFile exportPath #noPrompt selectedOnly:true 
					setAllChildrenHerarchy parentGeo arrayGeo true
					setAllChildrenHerarchy parentJoint arrayJoints true
					setAllChildrenHerarchy parentRig arrayRigs true
					

				)
				
			)
		)


		
	)


	

)
 createdialog FBXExport

