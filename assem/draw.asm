start  	CLR
	LOAD r2,$2
	LDSPR r2
	LOAD r0,$B
	LOAD r1,$A
drw	DRAW r0,r1,5
end 	JUMP drw
	
