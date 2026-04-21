- CISC: 
	- Hace varias tareas secuenciales en una instrucción, pero siempre sobre un par de datos. 
	- Instrucciones complejas que hacen más trabajo por línea, pero son más difíciles de implementar y consumen más. Ideal para densidad de código y compatibilidad.
	- La unidad de control suele ser microcodificada. Esto significa que tiene una memoria ROM interna (el microcódigo) donde cada instrucción compleja se traduce a una secuencia de micro-operaciones. Esa ROM ocupa espacio en el chip (más "bytes" o transistores). Por ejemplo, el Intel 8086 tenía microcódigo.
- RISC: 
	- Hace una misma tarea sobre muchos pares de datos al mismo tiempo, usando una sola sola instrucción. 
	- Instrucciones simples y rápidas, pero necesitas más líneas de código. Solo LOAD/STORE tocan memoria. Ideal para eficiencia y bajo consumo.
	- La unidad de control es cableada (hardware dedicado). No hay ROM de microcódigo; cada instrucción simple se decodifica directamente con puertas lógicas. Ocupa menos espacio y es más rápida.
	- 1

