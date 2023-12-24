# sort: Ordena ascendentemente un arreglo de enteros sin signo usando un
# algoritmo ridiculamente ineficiente.

# La funcion sort esta programada en assembler RiscV. El codigo equivalente
# en C esta comentado, mostrando la ubicacion de las variables en los
# registros.  La funcion recorre el arreglo revisando que los elementos
# consecutivos esten ordenados.  Si encuentra 2 elementos consecutivos
# desordenados, los intercambia y reinicia el recorrido del arreglo
# desde el comienzo.  El arreglo esta ordenado cuando se recorre
# completamente sin encontrar elementos consecutivos desordenados.

    .file "sort-rv.s"
    .text
    .globl sort         # Se necesita para que la etiqueta sea conocida en
                        # test-sort.c
    .type sort, @function # typedef unsigned int uint;
sort:                   # void sort(uint nums[], int n) { // registros a0, a1
    addi    sp,sp,-64   #   // Apila registro de activacion
    sw      ra, 60(sp)  #   // resguarda direccion de retorno
    sw      a0,56(sp)   #   uint *p= nums; // p esta en sp+56
    addi    a1,a1,-1    #   uint *ult= &nums[n-1]; // ult esta en sp+52
    slli    a1,a1,2     #   // tamanno del arreglo
    add     a1,a0,a1
    sw      a1,52(sp)
    sw      a0,48(sp)   #   // nums esta en direccion sp+48
    mv      t0,a0       #   // p esta en registro t0
                        #   while (p<ult) {
    j       .while_cond #     // la condicion del while se evalua al final
.while_begin:           #     // del ciclo para mayor eficiencia

    sw      t0,56(sp)   # resguardar p en memoria

    # Hasta aca no puede modificar nada

    #################################################
    ### Comienza el codigo que Ud. debe modificar ###
    #################################################
    # a0 = nums (uint *p = nums, p esta en sp+56); t0 = p; 
    # a1 = &nums[n-1] (uint *ult = &nums[n-1], ult esta en sp+52) 

    # no puede alterar los registros s0-s11, si lo hace debe resguardarlos
    # en 0(sp), 4(sp), ... o 44(sp)
    # El valor de p esta temporalmente en el registro t0 (p = &nums)
    # No puede hacer mas trabajo que la comparacion (no puede usar ret)
    lw      a0,0(t0)    #     cargamos las ¿direcciones? de las palabras
    lw      a1,4(t0)    #     en a0 y en a1
    

# contamos las palabras del primer string y guardamos el resultado en t2
	lbu a4,0(a0)        # a4 = a[i], i-ésimo carácter de la primera palabra
	beq	a4,zero,.L9		# a[i] != '\0' -> .L9
	addi	a5,a0,1		# i = 0
	li	a3,1			# espacio = 1, valor inicial
    li	a0,0			# a0 = words de la palabra a
	li	a2,32			# a2 = ' '
	li	a7,1			# espacio = 1, valor variable
	li	a6,0			# espacio = 0, valor fijo
	j	.L8				# -> .L8
.L10:
	mv	a3,a7			# espacio = 1
.L7:
	addi	a5,a5,1		# i++
	lbu	a4,-1(a5)		# se avanza al siguiente a[i]
	beq	a4,zero,.L12	# a[i] != '\0', aquí está la condición del while -> .L9
.L8:
	beq	a4,a2,.L10		# a[i] == ' ' -> .L10
	beq	a3,zero,.L7		# espacio == 0 -> .L7
	addi	a0,a0,1		# words++
	mv	a3,a6			# espacio = 0
	j	.L7				# -> .L7
.L12:
    mv t2,a0
    j .L33
.L9:	
    li	a0,0
	mv t2,a0
.L33:

# contamos las palabras del segundo string y guardamos el resultado en t3
	lbu a4,0(a1)        # a4 = b[i], i-ésimo carácter de la segunda palabra
	beq	a4,zero,.L92		# a[i] != '\0' -> .L9
	addi	a5,a0,1		# i = 0
	li	a3,1			# espacio = 1, valor inicial
    li	a0,0			# a0 = words de la palabra a
	li	a2,32			# a2 = ' '
	li	a7,1			# espacio = 1, valor variable
	li	a6,0			# espacio = 0, valor fijo
	j	.L82			# -> .L82
.L102:
	mv	a3,a7			# espacio = 1
.L72:
	addi	a5,a5,1		# i++
	lbu	a4,-1(a5)		# se avanza al siguiente a[i]
	beq	a4,zero,.L92	# a[i] != '\0', aquí está la condición del while -> .L92
.L82:
	beq	a4,a2,.L102		# a[i] == ' ' -> .L102
	beq	a3,zero,.L72		# espacio == 0 -> .L72
	addi	a0,a0,1		# words++
	mv	a3,a6			# espacio = 0
	j	.L72				# -> .L72
.L122:
    mv t3,a0
    j .L34
.L92:		
    li	a0,0
	mv t3,a0
.L34:
                              # valor retornado queda en registro a0
                              # p ya no esta en el registro t0
    sub t1,t3,t2             
    mv      t1,a0            # Dejar resultado de la comparacion en t1

    # En el registro t1 debe quedar la conclusion de la comparacion:
    # si t1<=0 p[0] y p[1] estan en orden y no se intercambiaran.

    #################################################
    ### Fin del codigo que Ud. debe modificar     ###
    #################################################

    # Desde aca no puede modificar nada
    # Si t1>0 se intercambian p[0] y p[1] y se asigna p= noms para revisar
    # nuevamente que los elementos esten ordenados desde el comienzo del arreglo

.decision:              #     if (0>=rc) {
    lw      t0,56(sp)   #       // p esta en registro t0
    blt     zero,t1,.else
    addi    t0,t0,4     #       p++; // avanzar en arreglo de enteros
    j       .while_cond #     }

.else:                  #     else { // intercambar p[0] y p[1], y reiniciar
    lw      a0,0(t0)    #       int aux= p[0]; // a0
    lw      a1,4(t0)    #       int aux2= p[1];
    sw      a0,4(t0)    #       p[0]= aux2;
    sw      a1,0(t0)    #       p[1]= aux;
    lw      t0,48(sp)   #       p= noms;
                        #     }

.while_cond:            #     // se evalua la condicion del while
    lw      t1,52(sp)   #     // ult esta en t1
    bltu    t0,t1,.while_begin #  // Condicion del while es p<ult
			#   }
    lw      ra,60(sp)   #   // Se restaura direccion de retorno
    addi    sp,sp,64    #   // Desapila registro de activacion
    ret			# }
