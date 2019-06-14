--Made by Miguel Palencia de Miguel miguelpalenciademi@gmail.com

function MakeLength Edge_index displacement_value nameObj = 
(
		
	objMesh = getNodeByName (nameObj as string)
	objMesh.SetSelection #Edge #{Edge_index}
	objMesh.SelectEdgeLoop()
	objMesh.ConvertSelection #Edge #Vertex
	vertsSelected = objMesh.selectedVerts
	for vert in vertsSelected do vert.pos.y =  displacement_value

)

numberWalls = 0
wallList = #()
wallAssets = #()

numberWindows = 0
windowList = #()
windowAssets = #()

numberDoors = 0
doorAssets = #()
doorList = #()

numberCorner = 0
cornerAssets = #()

listAssets = #()

kindOfWallsList = #()
kindOfWindowsList = #()
kindOfDoorsList = #()

objPicked = 0


struct assetBuildt (_width, _length, _height, _parent)
struct assetWall (_width, _length, _height, _parent)
struct assetWindow (_width, _length, _height, _parent)
struct assetDoor (_width, _length, _height, _parent)
struct wallModule (_width, _height, _walls)
struct windowModule (_width, _height, _windows)
struct doorModule (_width, _height, _doors)
struct configToBuild (distanceRemain, wallsToBuild,numberOfWalls)
best_config = configToBuild distanceRemain:2000 wallsToBuild:#()
try(destroyDialog RoomBuilder) catch()
rollout RoomBuilder "RoomBuilder" width:601 height:679
(
	GroupBox 'AssetBuilder' "AssetBuilder" pos:[20,14] width:559 height:290 align:#left
	GroupBox 'Wall' "Wall" pos:[32,46] width:362 height:63 align:#left
	spinner 'wall_length' "" pos:[37,84] width:99 height:16 range:[10,1000,250] align:#left
	spinner 'wall_width' "" pos:[163,84] width:99 height:16 range:[5,1000,25] align:#left
	spinner 'wall_height' "" pos:[291,84] width:99 height:16 range:[20,1000,120] align:#left
	label 'lbl1' "Length" pos:[42,66] width:48 height:16 align:#left
	label 'lbl2' "Width" pos:[166,65] width:48 height:16 align:#left
	label 'lbl3' "Height" pos:[296,64] width:48 height:16 align:#left
	GroupBox 'grp4' "Window" pos:[34,120] width:362 height:63 align:#left
	spinner 'window_length' "" pos:[37,158] width:99 height:16 range:[0,1000,250] align:#left
	spinner 'window_height' "" pos:[290,158] width:99 height:16 range:[0,1000,25] align:#left
	spinner 'window_height_floor' "" pos:[163,157] width:99 height:16 range:[0,1000,10] align:#left
	label 'lbl4' "Length" pos:[42,140] width:48 height:16 align:#left
	label 'lbl5' "Height_Floor" pos:[166,139] width:100 height:16 align:#left
	GroupBox 'grp6' "Door" pos:[35,192] width:362 height:63 align:#left
	spinner 'door_length' "" pos:[38,230] width:99 height:16 range:[0,1000,250] align:#left
	spinner 'door_height' "" pos:[164,230] width:99 height:16 range:[0,1000,250] align:#left
	label 'lbl7' "Length" pos:[43,212] width:48 height:16 align:#left
	label 'lbl8' "Height" pos:[167,211] width:48 height:16 align:#left
	button 'btn_create' "Create" pos:[187,264] width:136 height:24 align:#left	
	
	label 'lbl16' "Height" pos:[293,139] width:48 height:16 align:#left
	button 'AddWallBtn' "+" pos:[410,66] width:29 height:27 align:#left

	button 'AddWindowBtn' "+" pos:[409,141] width:29 height:27 align:#left
	button 'AddDoorBtn' "+" pos:[409,213] width:29 height:27 align:#left
	dropdownList 'wall_dropList' "Walls" pos:[464,52] width:73 height:40 align:#left
	dropdownList 'window_dropList' "Windows" pos:[463,127] width:73 height:40 align:#left
	dropdownList 'door_dropList' "Doors" pos:[461,200] width:73 height:40 align:#left
	
	spinner 'L_Room' "Length Room" pos:[215,356] width:120 height:16 range:[0,1000,500] align:#left
	spinner 'W_Room' "Width Room" pos:[216,386] width:125 height:16 range:[0,1000,500] align:#left
	button 'Room_Btn' "Create Room" pos:[441,355] width:114 height:45 align:#left
	GroupBox 'grp5' "Room Builder" pos:[22,318] width:555 height:107 align:#left

	spinner 'room_x' "X" pos:[40,346] width:95 height:16 range:[-2e+06,200000,0] scale:1 align:#left
	spinner 'room_y' "Y" pos:[39,370] width:95 height:16 range:[-2e+06,200000,0] scale:1 align:#left
	spinner 'room_z' "Z" pos:[39,392] width:95 height:16 range:[-2e+06,200000,0] scale:1 align:#left
	groupBox 'gr20' "ChangeAsset" pos:[21,434] width:557 height:226 align:#left
	pickButton 'pickAssetBtn' "Pick Asset" pos:[46,484] width:86 height:153 align:#left
	dropDownList 'possibleWindows_dropList' "Possible Windows" pos:[164,505] width:115 height:40 align:#left
	dropDownList 'possibleDoors_dropList' "Possible Doors" pos:[329,506] width:115 height:40 align:#left
	button 'changeWindowBtn' "Change to Window" pos:[166,588] width:103 height:25 align:#left
	button 'changeDoorBtn' "Change to Door" pos:[332,589] width:97 height:25 align:#left
	button 'resetWallBtn' "Reset to Wall" pos:[467,477] width:88 height:156 align:#left
	
	
	function createWall w_width w_length w_heigth = 
	(
		wallObj = Box name:(uniqueName "SM_Wall" numDigits:3) length:w_length width:w_width height:w_heigth lengthsegments:1 widthsegments:1 heightsegments:1		
		

		wallObj.pivot = [wallObj.min.x, wallObj.min.y,wallObj.min.z]
		wallObj.position = [0,0,0]

		--convertTo wallObj Editable_Poly 

		return wallObj
	)
	

	
	function createWindow  w_length w_heigth w_width wn_length wn_heigth_floor wn_heigth= 
	(
		winObj = Box name:(uniqueName "SM_Window" numDigits:3) length:w_length width:w_width height:wn_heigth_floor lengthsegments:3 widthsegments:1 heightsegments:1

		winObj.pivot = [winObj.min.x, winObj.min.y,winObj.min.z]
		winObj.position = [0,0,0]
		
		convertTo winObj Editable_Poly

		--Seteamos la posición correcta de la ventana
		lengthToMove = (w_length - wn_length)/2
		MakeLength 13 lengthToMove winObj.name
		MakeLength 16 (w_length-lengthToMove) winObj.name

		--Seleccionamos las caras necesarias para subir en altura hasta inicio de ventana

		winObj.extrusionType = 1
		
		if(wn_heigth < w_heigth - wn_heigth_floor) then
		(
			polyop.extrudeFaces winObj #{4,6} wn_heigth
			polyop.extrudeFaces winObj #{4,6} (w_heigth-wn_heigth-wn_heigth_floor) 
			polyOp.setFaceSelection winObj #{25,27}
			winObj.bridgeSegments = 0
			winObj.bridge selLevel: #Face 
		)
		else 		
		(
			polyop.extrudeFaces winObj #{4,6}  (w_heigth - wn_heigth_floor)
		)
		
		return winObj
		
	)

	function createDoor  w_length w_heigth w_width d_length d_heigth= 
	(
		doorObj = Box name:(uniqueName "SM_Door" numDigits:3) length:w_length width:w_width height:(w_heigth - d_heigth) lengthsegments:3 widthsegments:1 heightsegments:1

		doorObj.pivot = [doorObj.min.x, doorObj.min.y,doorObj.min.z]
		doorObj.position = [0,0,0]
		convertTo doorObj Editable_Poly

		--Seteamos la posición correcta de la puerta
		lengthToMove = (w_length - d_length)/2
		MakeLength 13 lengthToMove doorObj.name
		MakeLength 16 (w_length-lengthToMove) doorObj.name

		--Seleccionamos las caras necesarias para subir en altura hasta inicio de puerta

		doorObj.extrusionType = 1
		
		polyop.extrudeFaces doorObj #{1,3} d_heigth
		doorObj.pivot = [doorObj.min.x, doorObj.min.y,doorObj.min.z]
		doorObj.position = [0,0,0]
			
		return doorObj
		
	)

	function createCorner width1 width2 heightBase = 
	(
		cornerObj = Box name:(uniqueName "SM_Corner" numDigits:3) length:width1 width:width2 height:heightBase lengthsegments:1 widthsegments:1 heightsegments:1
		append cornerAssets cornerObj
		numberCorner += 1
		return cornerObj

	)

	
	

	

	function newWall indexNumber = 
	(

		new_wall = #(indexNumber as string ,wall_width.value,wall_length.value,wall_height.value)
		append wallList new_Wall
		return new_wall
	)

	function newWindow indexNumber = 
	(

		new_window = #(indexNumber as string ,window_length.value,window_height_floor.value,window_height.value)
		append windowList new_window
		return new_window
	)

	function newDoor indexNumber = 
	(

		new_door = #(indexNumber as string ,door_length.value,door_height.value)
		append doorList new_door
		return new_door
	)

	 function newParentAsset _w _h _l = 
	 (
		 nameObj = (_w as string )+"x"+(_h as string )
		  parentPoint = Point name:nameObj position:[0, 0, 0]
		  parentObj = assetBuildt _width:_w _height:_h _parent:parentPoint _length:_l
		  append listAssets parentObj
		  return parentPoint


	 )

	 function createNode nameNode = 
	 (
		 
		  parentPoint = Point name:nameNode position:[0, 0, 0]

		  return parentPoint
	 )

	


	function getAllKindOfWalls = 
	(
		for ch in listAssets do 
		(
			module = wallModule _width: ch._width _height:ch._height _walls: #()
			for obj in ch._parent.children[1].children do 
			(
				nodeObj = assetWall _width:ch._width _height:ch._height _length:obj.length _parent: obj				
				append module._walls nodeObj
			)

			append kindOfWallsList module
				
			
		)
	)

	function getAllKindOfWindows = 
	(
		for ch in listAssets do 
		(
			module = windowModule _width: ch._width _height:ch._height _windows: #()
			for obj in ch._parent.children[2].children do 
			(
				width = (obj.max - obj.min).x
				length = (obj.max - obj.min).y
				height = (obj.max - obj.min).z
				 
				nodeObj = assetWindow _width:width _height:length _length:height _parent: obj					
				append module._windows nodeObj
			)

			append kindOfWindowsList module
				
			
		)
	)

		function getAllKindOfDoors = 
	(
		for ch in listAssets do 
		(
			module = doorModule _width: ch._width _height:ch._height _doors:#()
			for obj in ch._parent.children[3].children do 
			(
				width = (obj.max - obj.min).x
				length = (obj.max - obj.min).y
				height = (obj.max - obj.min).z
				 
				nodeObj = assetWindow _width:width _height:length _length:height _parent: obj				
				append module._doors nodeObj
			)

			append kindOfDoorsList module
				
			
		)
	)

	

	function sortWallList = 
	(
		for module in kindOfWallsList do 
		(
			for i=1 to module._walls.count do
			(
				for j=i to module._walls.count do
				(
					if module._walls[j]._length > module._walls[i]._length then
					(
						auxwall = module._walls[i]
						module._walls[i] = module._walls[j]
						module._walls[j] = auxwall

					)
				)
							
			)
		)
		

		return kindOfWallsList
			
	)

	function sortWindowList = 
	(
		for module in kindOfWindowsList do 
		(
			for i=1 to module._windows.count do
			(
				for j=i to module._windows.count do
				(
					if module._windows[j]._length > module._windows[i]._length then
					(
						auxwall = module._windows[i]
						module._windows[i] = module._windows[j]
						module._windows[j] = auxwall

					)
				)
							
			)
		)
		

		return kindOfWindowsList
			
	)

	function sortDoorList = 
	(
		for module in kindOfDoorsList do 
		(
			for i=1 to module._doors.count do
			(
				for j=i to module._doors.count do
				(
					if module._doors[j]._length > module._doors[i]._length then
					(
						auxwall = module._doors[i]
						module._doors[i] = module._doors[j]
						module._doors[j] = auxwall

					)
				)
							
			)
		)
		

		return kindOfDoorsList
			
	)

	function findCorner width1 width2 _height= 
	(
		for corner in cornerAssets do 
		(
			if( corner.length == width1 and corner.width == width2 and corner.height == _height) do 
				return corner
		)

		return undefined

	)

	function checkBestConfig wallTryList desireLength configTmp = 
	(

		arrayTmp = deepCopy wallTryList
		
		
		if(arrayTmp.count > 0) then 
		(
			if desireLength > arrayTmp[1]._length then 
			(
				desireLength -= arrayTmp[1]._length
				print "Restante:"
				print desireLength
				--configTmp = configToBuild distanceRemain:desireLength wallsToBuild:#()
				configTmp.distanceRemain = desireLength
				append configTmp.wallsToBuild arrayTmp[1]
				configTmp.numberOfWalls += 1
				--configTmp = checkBestConfig arrayTmp desireLength configTmp			

			)
			else if desireLength == arrayTmp[1]._length then 
			(
				
				desireLength -= arrayTmp[1]._length
				print "Restante Final: "
				print desireLength
				--configTmp = configToBuild distanceRemain:desireLength wallsToBuild:#()
				configTmp.distanceRemain = desireLength
				append configTmp.wallsToBuild arrayTmp[1]
				configTmp.numberOfWalls +=1
				return configTmp
				--checkBestConfig arrayTmp desireLength configTmp
				

			)
			else 
			(
				print "Este objeto ya no me vale"
				print arrayTmp[1]
				arrayTmp = deepCopy (deleteItem arrayTmp  1)		
				
				
				
			)
		)
		
		if configTmp.distanceRemain > 0 and arrayTmp.count > 0 do 
			configTmp = checkBestConfig arrayTmp desireLength configTmp

		
		return configTmp
	)

	function buildWall configurationDesired pointStart _rotate _parent= 
	(
		print "Lo estamos haciendo"
		for _wall in configurationDesired do 
		(
			
			maxOps.cloneNodes _wall._parent cloneType:#instance newNodes:&nodeInstances
			if(_rotate) then  
			(
				--rotate nodeInstances[1] (angleaxis -90.0[0,0,1])
				nodeInstances[1].rotation = (eulerangles 0 0 -90) 
				nodeInstances[1].pivot = [nodeInstances[1].min.x, nodeInstances[1].min.y,nodeInstances[1].min.z]
				nodeInstances[1].position = pointStart
				pointStart = [pointStart.x+_wall._length,pointStart.y,pointStart.z]

			)
			else
			(
				nodeInstances[1].pivot = [nodeInstances[1].min.x, nodeInstances[1].min.y,nodeInstances[1].min.z]
				nodeInstances[1].position = pointStart
				pointStart = [pointStart.x,pointStart.y+_wall._length,pointStart.z]
			)
			nodeInstances[1].parent = _parent
			
		)
		

	)

	function setCorner width1 width2 _height pointStart _parent = 
	(
		corner = findCorner width1 width2  _height
		
		if (corner != undefined) then 
		(
			maxOps.cloneNodes corner cloneType:#instance newNodes:&nodeInstances
			nodeInstances[1].pivot = [nodeInstances[1].min.x, nodeInstances[1].min.y,nodeInstances[1].min.z]
			nodeInstances[1].position = pointStart
			nodeInstances[1].parent = _parent

			print "Creada"
		)else 
		(
			corner = findCorner width2 width1 _height
			if (corner != undefined)then 
			(
				maxOps.cloneNodes corner cloneType:#instance newNodes:&nodeInstances
				rotate nodeInstances[1] (angleaxis -90.0[0,0,1])
				nodeInstances[1].pivot = [nodeInstances[1].min.x, nodeInstances[1].min.y,nodeInstances[1].min.z]
				nodeInstances[1].position = pointStart
				print "Creada"
			)

		)

		print "Esquina"

	)

	function findBestConfiguration = 
	(
		
		
		kindOfWallsList = #()
		kindOfDoorsList = #()
		kindOfWindowsList = #()
		getAllKindOfWalls()
		getAllKindOfDoors()
		getAllKindOfWindows()
		print "Muros"
		print kindOfWallsList
		print "Ventanas"
		print kindOfWindowsList
		print "Puertas"
		print kindOfDoorsList

		
		kindOfWallsList = sortWallList()
		kindOfWindowsList = sortWindowList()
		kindOfDoorsList = sortDoorList()
		
		--for obj in kindOfWallsList do
		--	print obj._length

		tempConfiguration = configToBuild distanceRemain:L_Room.value wallsToBuild:#() numberOfWalls:10
		length_config = configToBuild distanceRemain:10000 wallsToBuild:#(3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3)
		print "Distancia a tapar"
		print L_Room.value

		lengthConfigurationsArray = #()

		for wall_module in kindOfWallsList do 
		(
			
			tempConfiguration = configToBuild distanceRemain:L_Room.value wallsToBuild:#() numberOfWalls:0
			aux_length_config =  checkBestConfig wall_module._walls L_Room.value tempConfiguration
			if aux_length_config.numberOfWalls>0 do 
			(
				append lengthConfigurationsArray aux_length_config
			)
			

			

		)

		

		print "LengthConfig"
		print lengthConfigurationsArray
		


		tempConfiguration2 = configToBuild distanceRemain:W_Room.value wallsToBuild:#() numberOfWalls:0
		width_config = configToBuild distanceRemain:10000 wallsToBuild:#(3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3) numberOfWalls:0
		

		widthConfigurationsArray = #()
		
		for wall_module in kindOfWallsList do 
		(
			tempConfiguration2 = configToBuild distanceRemain:W_Room.value wallsToBuild:#() numberOfWalls:0
			aux_width_config =  checkBestConfig wall_module._walls W_Room.value tempConfiguration2
			if aux_width_config.numberOfWalls > 0 do 
			(
				append widthConfigurationsArray aux_width_config
			)
			

		)
	

		--width_config = best_config

		--COMPROBAMOS CONFIGURACIONES POR ALTURA
		bestConfigsList = #()
		print widthConfigurationsArray

		confgtmp = configToBuild distanceRemain:10000 wallsToBuild:#() numberOfWalls:1000
		for i=1 to lengthConfigurationsArray.count do 
		(
			for j = 1 to widthConfigurationsArray.count do 
			(
				
				if lengthConfigurationsArray[i].wallsToBuild[1]._height == widthConfigurationsArray[j].wallsToBuild[1]._height do 
				(					
					bestConfig = configToBuild distanceRemain:W_Room.value wallsToBuild:#() numberOfWalls:0
					bestConfig.distanceRemain = lengthConfigurationsArray[i].distanceRemain + widthConfigurationsArray[j].distanceRemain
					append bestConfig.wallsToBuild lengthConfigurationsArray[i].wallsToBuild
					append bestConfig.wallsToBuild widthConfigurationsArray[j].wallsToBuild
					bestConfig.numberOfWalls = widthConfigurationsArray[j].numberOfWalls + lengthConfigurationsArray[i].numberOfWalls
					append bestConfigsList bestConfig
				)
			)
		)


		for i=1 to bestConfigsList.count do 
		(
			if bestConfigsList[i].distanceRemain <= confgtmp.distanceRemain do 
			(
				if ((bestConfigsList[i].numberOfWalls < confgtmp.numberOfWalls) and (bestConfigsList[i].distanceRemain == confgtmp.distanceRemain)) then 
				(
					confgtmp = bestConfigsList[i]
				)

				else if (bestConfigsList[i].distanceRemain < confgtmp.distanceRemain) then 
				(
					confgtmp = bestConfigsList[i]
				)
			)
		)

		print "Mejores Configuraciones posibles"
		print bestConfigsList

		print "Configuración óptima"
		print confgtmp

		length_config = confgtmp.wallsToBuild[1]
		width_config = confgtmp.wallsToBuild[2]

		print "Width Config"
		print width_config
		pointStart = [room_x.value,room_y.value,room_z.value]

		parentObj = createNode "Room" 
		--Esquina derecha "abajo"
				
		setCorner length_config[1]._width width_config[1]._width length_config[1]._height pointStart parentObj

		--Pared "Abajo"
		pointStart.y +=  length_config[1]._width
		buildWall width_config pointStart false parentObj
		
		
		--Pared "derecha"
		pointStart.x +=  width_config[1]._width
		pointStart.y -=  length_config[1]._width		
		buildWall length_config pointStart true parentObj

		--Esquina derecha "abajo"
		pointStart.x -=  width_config[1]._width
		pointStart.y +=  W_Room.value +length_config[1]._width			
		setCorner length_config[1]._width width_config[1]._width length_config[1]._height pointStart parentObj

		--Pared "Izquierda"
		pointStart.x +=  width_config[1]._width		
		buildWall length_config pointStart true parentObj

		--Esquina izquierda "arriba"
		pointStart.x +=  L_Room.value
		--pointStart.y +=  W_Room.value +length_config[1]._width			
		setCorner length_config[1]._width width_config[1]._width length_config[1]._height pointStart parentObj 



		--Pared "Derecha"
		pointStart.y -=  W_Room.value
		--pointStart.x +=  L_Room.value		
		buildWall width_config pointStart false parentObj

		--Esquina derecha "arriba"
		pointStart.y -=  length_config[1]._width		
		setCorner length_config[1]._width width_config[1]._width length_config[1]._height pointStart  parentObj
		
	
	)

	

	
	function findAsset _w _h  = 
	(
		for obj in listAssets do 
		(
			if(obj._width == _w and obj._height == _h) then
				return obj._parent

		)

		return false
	)

	function checkNodeExist nameNode obj = 
	(
	

			for ch in obj.children do 
			(
				if ch.name == nameNode do 
				(					
					return ch
				)
					
			)		

		return createNode nameNode
	)

	function resetPickAssetModule = 
	(
		resetWallBtn.enabled = false
		changeDoorBtn.enabled = false
		changeWindowBtn. enabled = false
		window_dropList.items = #()
		door_dropList.items = #()
		objPicked = 0

		possibleDoors_dropList.items = #()
		possibleWindows_dropList.items = #()


	)

	

	
	on RoomBuilder open do
	(
		btn_create.enabled = false
	
		wall_height.enabled = false
		wall_length.enabled = false		
		wall_width.enabled = false
	
		door_height.enabled = false
		door_length.enabled = false
	
		window_height_floor.enabled = false		
		window_height.enabled = false
		window_length.enabled = false
		
		window_length.range = [5,wall_length.value-5,wall_length.value/2]
		window_height.range = [5,wall_height.value-10,wall_height.value-10]
		window_height_floor.range = [5,(wall_height.value-window_height.value),(wall_height.value-window_height.value)/2]
		window_height.range = [0,(wall_height.value-window_height_floor.value)-10,((wall_height.value-window_height_floor.value)-10)/2]
	
		door_length.range = [0,wall_length.value-5,wall_length.value/2]
		door_height.range = [0,wall_height.value-10,(wall_height.value-10)/2]
	
		room_x.value = 0
		room_y.value = 0
		room_z.value = 0

		Room_Btn.enabled = false
		resetPickAssetModule()
	
	)
	on wall_length changed val do
	(
		wallList[wall_dropList.selection][3] = wall_length.value
	
		window_length.range.y = wall_length.value-5
		if( wall_length.value-5 <= window_length.value) do 
			window_length.value = wall_length.value-5
		--window_length.range = [5,wall_length.value-5,50]
		if windowList.count > 0 do 
			windowList[window_dropList.selection][2] = window_length.value
	
		door_length.range.y = wall_length.value-5
		if( wall_length.value-5 <= door_length.value) do 
			door_length.value = wall_length.value-5
		--door_length.range = [0,wall_length.value-5,50]
		if doorList.count > 0 do 
			doorList[door_dropList.selection][2] = door_length.value
	)
	on wall_width changed val do
	(
		wallList[wall_dropList.selection][2] = wall_width.value
	)
	on wall_height changed val do
	(
	
		window_height.range = [5,wall_height.value-10,window_height.value]
		if(wall_height.value-window_height.value>=0)then
		(
			window_height_floor.range = [5,(wall_height.value-window_height.value),window_height_floor.value]
		)
		
		window_height.range = [0,(wall_height.value-window_height_floor.value)-10,window_height.value]
	
		wallList[wall_dropList.selection][4] = wall_height.value
	)
	on window_length changed val do
	(
		windowList[window_dropList.selection][2] = window_length.value
	)
	on window_height changed val do
	(
		window_height_floor.range = [5,(wall_height.value-window_height.value)-10,window_height_floor.value]
		windowList[window_dropList.selection][4] = window_height.value
	)
	on window_height_floor changed val do
	(
		windowList[window_dropList.selection][3] = window_height_floor.value
	)
	on door_length changed val do
	(
		doorList[door_dropList.selection][2] = window_height.value
	)
	on door_height changed val do
	(
		doorList[door_dropList.selection][3] = door_height.value
	)
	on btn_create pressed do
	(
	
		for i = 1 to numberWalls by 1 do
		(
			
			parentObj = findAsset wallList[i][2] wallList[i][4]
	
			
	
			objCrated = createWall wallList[i][2] wallList[i][3] wallList[i][4]
			objCrated.position = [(i*500)-500,0,0]
			nodeObj = assetWall _width:wallList[i][2] _length:wallList[i][3] _height:wallList[i][4] _parent: objCrated				
			--append kindOfWallsList nodeObj
			
			if(parentObj == false ) then 
			(
				parentObj = newParentAsset wallList[i][2] wallList[i][4] wallList[i][3]
				
			)
			
			nodeObj = checkNodeExist "Walls" parentObj
			nodeObj.parent = parentObj
			objCrated.parent = nodeObj
			
			 
			nodeObj = checkNodeExist "Windows" parentObj
			nodeObj.parent = parentObj
			for j = 1 to numberWindows by 1 do
			(
				--print windowList[j][2]
				--print wallList[i][3]
				--print "otro"
				if windowList[j][2] < wallList[i][3] then 
				(
					objCrated= createWindow  wallList[i][3] wallList[i][4] wallList[i][2] windowList[j][2] windowList[j][3] windowList[j][4] 	
					objCrated.position = [(j*500)-500,(i*500)+500,0]
					objCrated.parent = nodeObj
				)
				
			)
			nodeObj = checkNodeExist "Doors" parentObj
			nodeObj.parent = parentObj
			for z = 1 to numberDoors by 1 do
			(
				if ((doorList[z][2] < wallList[i][3])  and (doorList[z][3]< wallList[i][4] - 5) )then 
				(
					objCrated = createDoor wallList[i][3] wallList[i][4] wallList[i][2] doorList[z][2] doorList[z][3] 	
					objCrated.position = [(z*500)-500,0,(i*500)+500]
					objCrated.parent = nodeObj
				)
				
			)
	
			nodeObj = getNodeByName "Corners"
			if(nodeObj == undefined)do
			(
				nodeObj = createNode "Corners"
			)
			--nodeObj = checkNodeExist "Corners" parentObj
			--nodeObj.parent = parentObj
			if numberWalls > 1 then
			(	
				
				if i <= numberWalls then 
				(
					for c = i to numberWalls by 1 do
					(
						if (wallList[i][4] == wallList[c][4]) then
						(	
							corner = findCorner wallList[i][2] wallList[c][2] wallList[i][4]
							if(corner == undefined) do 
							(
								objCrated = createCorner wallList[i][2] wallList[c][2] wallList[i][4]
								objCrated.position = [(i*500)-500,-((c*500)+500),0]
								objCrated.parent = nodeObj
							)
							
							
						)
						
					)
					
				)
			) 
			else 
			(
				objCrated = createCorner wallList[i][2] wallList[i][2] wallList[i][4]
				objCrated.position = [0,-500 ,0]
				objCrated.parent = nodeObj
			)	
		)
	
		Room_Btn.enabled = true
		
		
	)
	on AddWallBtn pressed do
	(
		wall_height.enabled = true
		wall_length.enabled = true		
		wall_width.enabled = true
	
		btn_create.enabled = true
	
		numberWalls += 1
		newItem = newWall numberWalls
		itemsAux = wall_dropList.items
		append itemsAux newItem[1]
		wall_dropList.items = itemsAux
	)
	on AddWindowBtn pressed do
	(
		window_height_floor.enabled = true		
		window_height.enabled = true
		window_length.enabled = true
	
	
		numberWindows += 1
		newItem = newWindow numberWindows
		itemsAux = window_dropList.items
		append itemsAux newItem[1]
		window_dropList.items = itemsAux
	
	)
	on AddDoorBtn pressed do
	(
		door_height.enabled = true
		door_length.enabled = true
	
		numberDoors += 1
		newItem = newDoor numberDoors
		itemsAux = door_dropList.items
		append itemsAux newItem[1]
		door_dropList.items = itemsAux
	
	)
	on wall_dropList selected sel do
	(			
		wall_width.value = wallList[wall_dropList.selection][2]
		wall_length.value = wallList[wall_dropList.selection][3]
		wall_height.value = wallList[wall_dropList.selection][4]
	)
	on window_dropList selected sel do
	(
		window_length.value = wallList[wall_dropList.selection][2]
		window_height_floor.value = wallList[wall_dropList.selection][3]
		window_height.value = wallList[wall_dropList.selection][4]	
	)
	on door_dropList selected sel do
	(
		door_length.value = wallList[wall_dropList.selection][2]		
		door_height.value = wallList[wall_dropList.selection][3]	
	)
	on Room_Btn pressed do
	(
		findBestConfiguration()

	)

	function getPossibleWall _width _length _height  = 
	(
		posibleObjs = #()

		for i = 1 to kindOfWallsList.count do 
		(
			
			if(kindOfWallsList[i]._walls.count > 0) do 
			(
				print "uehduedhue"
				for obj in kindOfWallsList[i]._walls do 
				(
					print "uehduedhue2"
					
					if(obj._width == _width and obj._length == _length and obj._height == _height) then 
					(
						print "añadido"
						return obj._parent
					)
					else if (obj._width == _length and obj._length == _width and obj._height == _height) then 
					(
						print "añadido"
						return obj._parent
					)
				)
			)
			
		)

		return undefined
	)

	function getPossibleWindow _width _length _height  = 
	(
		posibleObjs = #()

		for i = 1 to kindOfWindowsList.count do 
		(
			if(kindOfWindowsList[i]._windows.count > 0) do 
			(
				for obj in kindOfWindowsList[i]._windows do 
				(
					dimensionObj = obj._parent.max - obj._parent.min
					if(dimensionObj.x == _width and dimensionObj.y == _length and dimensionObj.z == _height) do 
					(
						print "añadido"
						append posibleObjs obj._parent
					)
				)
			)
			
		)

		return posibleObjs
	)


	function getPossibleDoor _width _length _height  = 
	(
		posibleObjs = #()

		for i = 1 to kindOfDoorsList.count do 
		(
			if(kindOfDoorsList[i]._doors.count > 0) do 
			(
				for obj in kindOfDoorsList[i]._doors do 
				(
					dimensionObj = obj._parent.max - obj._parent.min
					if(dimensionObj.x == _width and dimensionObj.y == _length and dimensionObj.z == _height) do 
					(
						print "añadido"
						append posibleObjs obj._parent
					)
				)
			)
			
		)

		return posibleObjs
	)

	on pickAssetBtn picked obj do
	(

		objPicked = obj
		
		posibleDoors = #()
		posibleWindows = #()
		possibleDoors_dropList.items = #()
		possibleWindows_dropList.items = #()
		

		if(classof (obj) == Editable_Poly) then 
		(
			assetToChange = assetBuildt _width:100 _length:200 _height:100 
			dimensionObj = obj.max - obj.min
			assetToChange._width = dimensionObj.x
			assetToChange._length = dimensionObj.y
			assetToChange._height = dimensionObj.z
			assetToChange._parent = obj
		)else 
		(
			assetToChange = assetBuildt _width:100 _length:200 _height:100 
			assetToChange._width = obj.width
			assetToChange._length = obj.length
			assetToChange._height = obj.height
			assetToChange._parent = obj
		)
		

		posibleWindows = getPossibleWindow assetToChange._width assetToChange._length assetToChange._height 
		for window in posibleWindows do 
		(
			print "hey"
			itemsAux = possibleWindows_dropList.items
			append itemsAux window.name
			possibleWindows_dropList.items = itemsAux
			
		)

		if(possibleWindows_dropList.items.count > 0) then 
			changeWindowBtn.enabled = true
		else
			changeWindowBtn.enabled = false

		print "Posibles Windows"
		print possibleWindows_dropList.items

		posibleDoors = getPossibleDoor assetToChange._width assetToChange._length assetToChange._height 
		for door in posibleDoors do 
		(
			itemsAux = possibleDoors_dropList.items
			append itemsAux door.name
			possibleDoors_dropList.items = itemsAux
		)
		if(possibleDoors_dropList.items.count > 0) then 
			changeDoorBtn.enabled = true
		else
			changeDoorBtn.enabled = false
		print "Posibles Puertas"
		print possibleDoors_dropList.items

		resetWallBtn.enabled = true


	)
	
	on changeWindowBtn pressed  do
	(
		newObject = getNodeByName possibleWindows_dropList.items[possibleWindows_dropList.selection]
		maxOps.cloneNodes newObject cloneType:#instance newNodes:&nodeInstances
		
		nodeInstances[1].rotation = objPicked.rotation		
		nodeInstances[1].position = objPicked.position
		nodeInstances[1].pivot = [nodeInstances[1].min.x, nodeInstances[1].min.y,nodeInstances[1].min.z]
		nodeInstances[1].position = objPicked.position

		nodeInstances[1].transform = objPicked.transform

		delete objPicked
		resetPickAssetModule()

		
		
		print newObject
	)
	on changeDoorBtn pressed  do
	(
		newObject = getNodeByName possibleDoors_dropList.items[possibleDoors_dropList.selection]
		maxOps.cloneNodes newObject cloneType:#instance newNodes:&nodeInstances
		nodeInstances[1].rotation = objPicked.rotation		
		nodeInstances[1].position = objPicked.position
		nodeInstances[1].pivot = [nodeInstances[1].min.x, nodeInstances[1].min.y,nodeInstances[1].min.z]
		nodeInstances[1].position = objPicked.position
		
		

		delete objPicked
		resetPickAssetModule()
	)
	on resetWallBtn pressed  do
	(
		if(classof (objPicked) == Editable_Poly) then 
		(
			
			dimensionObj = objPicked.max - objPicked.min			
			newWallObject = getPossibleWall  dimensionObj.x dimensionObj.y dimensionObj.z
			if(newWallObject != undefined) do 
			(
				print "hola gili"
				newWallObject = getPossibleWall  dimensionObj.y dimensionObj.x dimensionObj.z
			)
		)else 
		(
			
			print "yeey"
			newWallObject = getPossibleWall  objPicked.width objPicked.length objPicked.height

		)
		
		if(newWallObject != undefined)do 
		(
			--newObject = getNodeByName possibleDoors_dropList.items[possibleDoors_dropList.selection]
			maxOps.cloneNodes newWallObject cloneType:#instance newNodes:&nodeInstances
			nodeInstances[1].rotation = objPicked.rotation		
			nodeInstances[1].position = objPicked.position
			nodeInstances[1].pivot = [nodeInstances[1].min.x, nodeInstances[1].min.y,nodeInstances[1].min.z]
			nodeInstances[1].position = objPicked.position
			delete objPicked
			objPicked = 0
		)

		resetPickAssetModule()
		
	)

	
)

createdialog RoomBuilder