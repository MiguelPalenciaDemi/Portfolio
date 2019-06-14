--Made by Miguel Palencia de Miguel miguelpalenciademi@gmail.com
--Variables

--Seat
seat_width = 80
seat_length = 60
seat_height = 10

--Back
back_width = 0
back_length = 0
back_height = 0

--Arm
arm_width = 10
arm_length = 54
arm_height = 10


id = 0
function MakeWidth Edge_index displacement_value = (
	
	Sofa = getNodeByName (id as string)
	Sofa.SetSelection #Edge #{Edge_index}
	Sofa.SelectEdgeLoop()
	Sofa.ConvertSelection #Edge #Vertex
	vertsSelected = Sofa.selectedVerts
	for vert in vertsSelected do vert.pos.x =  displacement_value

)


function MakeLength Edge_index displacement_value = (
	
	Sofa = getNodeByName (id as string)
	Sofa.SetSelection #Edge #{Edge_index}
	Sofa.SelectEdgeLoop()
	Sofa.ConvertSelection #Edge #Vertex
	vertsSelected = Sofa.selectedVerts
	for vert in vertsSelected do vert.pos.y =  displacement_value

)

function MakeCompleteSofa = (
	
		
	sofaBox = Box  name:(id as string) lengthsegs:4 widthsegs:7 heightsegs:1 length:seat_length width:seat_width height:seat_height
	sofaBox.pivot = [sofaBox.min.x,sofaBox.min.y,0]
	sofaBox.position = [0,0,0]

	convertTo sofaBox Editable_Poly

--Set position Time

	
		--Left Arm
		_value = arm_width
		MakeWidth 151 _value 

		_value = arm_width *0.5
		MakeWidth 152 _value 


			
		--Right Arm
		_value = seat_width - arm_width
		MakeWidth 148 _value 
		_value = seat_width - (arm_width*0.5)
		MakeWidth 147 _value
	
	



	--Arm Length

		if arm_length >= seat_length then (arm_length = seat_length)
		else if arm_length > (seat_length - back_length) then
		(
			_value =  arm_length
			MakeLength 154 _value 
			print "Valor dentro de respaldo"
			_value
		)
		else if((seat_length - back_length) - arm_length>0)then
		(
			_value = (seat_length - back_length) - arm_length
			MakeLength 156 _value 
			print "Valor fuera de respaldo"
			_value
		)




	--Back Length
		_value = seat_length - (back_length*0.5)
		MakeLength 154 _value

		_value = seat_length - back_length
		MakeLength 155 _value

	--Back Width
		if back_width >= seat_width and back_width == seat_width - 2*arm_width then back_width = seat_width
		else if  seat_width != back_width and seat_width - back_width < arm_width*2  then 
		(
			rest_value = (seat_width - back_width)/2
			--Arm Left
			_value = rest_value
			MakeWidth 152 _value 

			
			--Arm Right
			_value = seat_width - rest_value
			MakeWidth 147 _value 
		)
		else if back_width < seat_width - arm_width*2 then 
		(
			rest_value = (seat_width - back_width)/2

			_value = rest_value
			MakeWidth 150 _value 	
			
			_value = seat_width - rest_value
			MakeWidth 149 _value 
		)




--Extrude Time


	--Comprobamos cual es la altura menor arm or back
	extrude_value = arm_width

	if back_height > 0 and arm_height >0 then 
	(
		--El ancho del respaldo es todo el asiento?
		if back_width >= seat_width then
		(
			--El largo del brazo no ocuapa todo el brazo?
			if seat_length - back_length - arm_length>0 then
			(
				print "1"				
				polyop.extrudeFaces sofaBox #{36..37, 41..56} extrude_value

			)
			else 
			(
				print "2"
				polyop.extrudeFaces sofaBox #{29..30, 34..37, 41..56} extrude_value


			)
		)
		else if back_width< seat_width then 
		(
			
			--Si se mete dentro del respaldo pero no llega al final
			if arm_length > (seat_length - back_length) and arm_length < seat_length then
			(
				--Si el respaldo se solapa con el brazo
				if back_width > seat_width - 2*arm_width then
				(
					print "3"
					polyop.extrudeFaces sofaBox #{29..30, 34..37, 41..49, 51..55} extrude_value
				)
				--Si el respaldo es igual al hueco entre los brazos
				else if back_width == seat_width - 2*arm_width then 
				(
					print "4"
					polyop.extrudeFaces sofaBox #{29..30, 34..37, 41..49, 52..54} extrude_value
				)
				--Si el respaldo no toca con los brazos
				else if back_width < seat_width - 2*arm_width then 
				(
					print "5"
					polyop.extrudeFaces sofaBox #{29..30, 34..37, 41..44, 46, 48..49, 53} extrude_value

				)
					
			)
			--Si el brazo no da ningun problema con el respaldo y no llega al final
			else if seat_length - back_length - arm_length>0 then
			(
				--Si el respaldo se solapa con el brazo en width
				if back_width > seat_width - 2*arm_width then
				(
					print "6"
					polyop.extrudeFaces sofaBox #{36..37, 41..42, 44..48, 51..55} extrude_value
				)
				--Si el respaldo es igual al hueco entre los brazos
				else if back_width == seat_width - 2*arm_width then 
				(
					print "7"
					polyop.extrudeFaces sofaBox #{36..37, 41..42, 45..47, 52..54} extrude_value
				)
				--Si el respaldo no toca con los brazos
				else if back_width < seat_width - 2*arm_width then 
				(
					print "8"
					polyop.extrudeFaces sofaBox #{36..37, 41..42, 46, 53} extrude_value

				)
				

			)
			--si llega hasta el final pero no entra en el respaldo
			else if seat_length - arm_length == back_length then 
			(
				--Si el respaldo se solapa con el brazo en width
				if back_width > seat_width - 2*arm_width then
				(
					print "9"
					polyop.extrudeFaces sofaBox #{29..30, 34..37, 41..42, 44..48, 51..55} extrude_value
				)
				--Si el respaldo es igual al hueco entre los brazos
				else if back_width == seat_width - 2*arm_width then 
				(
					print "10"
					polyop.extrudeFaces sofaBox #{29..30, 34..37, 41..42, 45..47, 52..54} extrude_value
				)
				--Si el respaldo no toca con los brazos
				else if back_width < seat_width - 2*arm_width then 
				(
					print "11"
					polyop.extrudeFaces sofaBox #{29..30, 34..37, 41..42, 46, 53} extrude_value
				)

			)
			
			else 
			(
				--Si el respaldo es entra entre los brazos, y estos llegan hasta el final
				if back_width < seat_width - 2*arm_width then
				(
					print "12"
					polyop.extrudeFaces sofaBox #{29..30, 34..37, 41..44, 46, 48..51, 53, 55..56} extrude_value
				)
				--Si el respaldo solapa con los brazos, y estos llegan hasta el final
				else if back_width > seat_width - 2*arm_width and arm_length<= seat_length - back_length then 
				(
					print "13"
					polyop.extrudeFaces sofaBox #{29..30, 34..37, 41..42, 44..48, 51..55} extrude_value

				)				

				else
				(print "14"
					polyop.extrudeFaces sofaBox #{29..30, 34..37, 41..56} extrude_value
				)
				
				


			)
		)

		--Extrude BackSeat again
		if(back_height>arm_height) then 
		(
			extrude_value = back_height - arm_height
			--Si el respaldo se solapa con el brazo en width

			if back_width > seat_width - 2*arm_width and back_width < seat_width then
			(		
				print back_width
				polyop.extrudeFaces sofaBox #{44..48, 51..55} extrude_value
			)
			--Si el respaldo es igual al hueco entre los brazos
			else if back_width == seat_width - 2*arm_width then 
			(		
				polyop.extrudeFaces sofaBox #{45..47, 52..54} extrude_value
			)
			--Si el respaldo no toca con los brazos
			else if back_width < seat_width - 2*arm_width then 
			(		
				polyop.extrudeFaces sofaBox #{46, 53} extrude_value
			)
			else if back_width >= seat_width then
				polyop.extrudeFaces sofaBox #{43..56} extrude_value


		)
	)



)


function MakeSofaWithoutArms = 
(

	sofaBox = Box  name:(id as string) lengthsegs:2 widthsegs:3 heightsegs:1 length:seat_length width:seat_width height:seat_height
	sofaBox.pivot = [sofaBox.min.x,sofaBox.min.y,0]
	sofaBox.position = [0,0,0]

	convertTo sofaBox Editable_Poly
	--Set position Time


		--Back Length	

			_value = seat_length - back_length
			MakeLength 44 _value

		--Back Width
		
			if seat_width > back_width then 
			(
				rest_value = (seat_width - back_width)/2
				--Arm Left
				_value = rest_value
				MakeWidth 42 _value 

				
				--Arm Right
				_value = seat_width - rest_value
				MakeWidth 41 _value 
			)
			



	--Extrude Time


		--Comprobamos cual es la altura menor arm or back
		extrude_value = back_height

	
		if(back_height>0) then 
		(			
			--Si el respaldo es m�s peque�o que el asiento			
			if seat_width > back_width then
			(		
				polyop.extrudeFaces sofaBox #{11} extrude_value
			)
			--Si el respaldo es igual que el asiento
			else  
			(		
				polyop.extrudeFaces sofaBox #{10..12} extrude_value
			)
			


		)
	

)

function MakeSofaWithoutBack = (
	
		
	sofaBox = Box  name:(id as string) lengthsegs:3 widthsegs:3 heightsegs:1 length:seat_length width:seat_width height:seat_height
	sofaBox.pivot = [sofaBox.min.x,sofaBox.min.y,0]
	sofaBox.position = [0,0,0]

	convertTo sofaBox Editable_Poly

--Set position Time


	--Left Arm
		_value = arm_width
		MakeWidth 57 _value 

		


			
	--Right Arm
		_value = seat_width - arm_width
		MakeWidth 56 _value 
		



	--Arm Length

		
		if arm_length < (2*seat_length)/3  then
		(
			print "menor a"
			_value =  (2*seat_length)/3 - arm_length
			MakeLength 60 _value 
			
		)
		else if (arm_length > (2*seat_length)/3 and arm_length < seat_length)  then
		(
			print "mayor a"
			_value = arm_length
			print _value as string
			MakeLength 59 _value 
			
		)
--Extrude Time


	--Comprobamos cual es la altura menor arm or back
	extrude_value = arm_height

	

		
		--Si el respaldo se solapa con el brazo en width

		if arm_length < (2*seat_length)/3  then
		(		
			polyop.extrudeFaces sofaBox #{13,15} extrude_value
		)
		else if arm_length >= (2*seat_length)/3 and arm_length < seat_length  then 
		(
			polyop.extrudeFaces sofaBox #{10, 12..13, 15} extrude_value
		)
		else if arm_length == seat_length then 
		(
			polyop.extrudeFaces sofaBox #{10, 12..13, 15..16, 18} extrude_value
		)

)





rollout SofaMaker "SofaMaker" width:260 height:700
(
	label 'lbl1' "Sofa Creator" pos:[98,12] width:100 height:32 align:#left
	GroupBox 'grp1' "Extras" pos:[35,48] width:186 height:44 align:#left
	checkbox 'noArms' "No Arms" pos:[45,63] width:72 height:23 align:#left
	checkbox 'noBack' "No Back" pos:[127,65] width:86 height:19 align:#left
	GroupBox 'grp2' "Seat" pos:[37,106] width:185 height:159 align:#left
	GroupBox 'grp4' "Arms" pos:[35,444] width:185 height:159 align:#left
	GroupBox 'grp5' "Back" pos:[35,275] width:185 height:159 align:#left
	button 'btn1' "Create" pos:[49,631] width:171 height:36 align:#left
	spinner 'SW' "" pos:[59,148] width:126 height:16 range:[30,100,80] align:#left
	label 'lbl3' "Width" pos:[60,131] width:38 height:11 align:#left
	label 'lbl4' "Length" pos:[60,173] width:34 height:13 align:#left
	spinner 'SL' "" pos:[59,193] width:126 height:16 range:[30,100,60] align:#left
	label 'lbl5' "Height" pos:[60,222] width:36 height:12 align:#left
	spinner 'SH' "" pos:[59,238] width:126 height:16 range:[2,50,10] align:#left
	label 'lbl6' "Width" pos:[59,298] width:37 height:12 align:#left
	spinner 'BW' "" pos:[59,316] width:126 height:16 range:[5,100,80] align:#left
	label 'lbl7' "Length" pos:[61,341] width:39 height:14 align:#left
	spinner 'BL' "" pos:[59,359] width:126 height:16 range:[5,20,15] align:#left
	label 'lbl8' "Height" pos:[61,383] width:39 height:15 align:#left
	spinner 'BH' "" pos:[59,404] width:126 height:16 range:[5,100,20] align:#left
	label 'lbl9' "Width" pos:[60,465] width:43 height:20 align:#left
	spinner 'AW' "" pos:[59,482] width:126 height:16 range:[5,20,15] align:#left
	label 'lbl10' "Length" pos:[60,510] width:49 height:17 align:#left
	spinner 'AL' "" pos:[59,531] width:126 height:16 range:[5,100,30] align:#left
	label 'lbl11' "Height" pos:[60,555] width:48 height:14 align:#left
	spinner 'AH' "" pos:[59,573] width:126 height:16 range:[5,100,10] align:#left

	on noArms changed state do
	(
		AL.enabled = not AL.enabled
		AW.enabled = not AW.enabled
		AH.enabled = not AH.enabled
	)
	on noBack changed state do
	(
		BL.enabled = not BL.enabled
		BW.enabled = not BW.enabled
		BH.enabled = not BH.enabled
	)
	on btn1 pressed  do
	(
		back_height = BH.value
		back_length = BL.value
		back_width = BW.value

		arm_height = AH.value
		arm_length = AL.value
		arm_width = AW.value

		seat_height = SH.value 
		seat_length = SL.value 
		seat_width = SW.value
		id += 1

		if noArms.checked and noBack.checked then
		(			
			sofaBox = Box  name:(id as string) lengthsegs:1 widthsegs:1 heightsegs:1 length:seat_length width:seat_width height:seat_height
			sofaBox.pivot = [sofaBox.min.x,sofaBox.min.y,0]
			sofaBox.position = [0,0,0]
			
		)
		else if noArms.checked then 
			MakeSofaWithoutArms()
		else if noBack.checked then 
			MakeSofaWithoutBack()
		else 
		(
			MakeCompleteSofa()
		)



	)
	on SW changed val do
	(
		if AW.value > SW.value*0.25 then
		(
			AW.value = SW.value
			AW.range = [5,SW.value*0.25,SW.value*0.25]
		) 
		if BW.value > SW.value then
		(
			BW.value = SW.value
			BW.range = [5,SW.value,SW.value]
		) 
	)
	on SL changed val do
	(
		if AL.value > SL.value then
		(
			AL.value = SL.value
			AL.range = [5,SL.value,SL.value]
		) 
		if BL.value > SL.value*0.33 then
		(
			BL.value = SL.value*0.33
			BL.range = [5,SL.value*0.33,SL.value*0.33]
		) 
		
	)
	on SH changed val do
		(
		
	)
	on BW changed val do
	(
		
		if BW.value > SW.value then SW.value
	
		BW.range = [5,SW.value,BW.value]
		
	
	)
	on BL changed val do
	(
		if BL.value > SL.value*0.33 then
		(
			BL.value = SL.value*0.33
			
		) 
	
		BL.range = [5,SL.value*0.33,BL.value]
	)
	on BH changed val do
	(
		if BH.value < AH.value then AH.value = BH.value
	)
	on AW changed val do
	(
		if AW.value > SW.value*0.25 then AW.value = SW.value*0.25
		AW.range = [5,SW.value*0.25,AW.value]
	)
	on AL changed val do
	(
		if AL.value > SL.value then AL.value = SL.value
		AL.range = [5,SL.value,AL.value]
	)
	on AH changed val do
	(
		if BH.value < AH.value then AH.value = BH.value
	)
)

createDialog SofaMaker