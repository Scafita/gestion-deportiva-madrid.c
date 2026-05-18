#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 5000

// Definimos los Prototipos de las funciones.
void sustituir_guiones (char lista[]);
void poner_guiones(char cadena[]);
int comparar(const char lista1[], const char lista2[]);
void ImprimirCentros(struct Actividad registros[], int nregistros); 
void ImprimirDeportes(struct Actividad registros[], int nregistros);
void SistemaRecomendacion(struct Actividad registros[], int nregistros);
int SoloLetras(char cadena[]);
int DNIValido(char dni[]);

// Definimos las estructuras que se van a utilizar
struct Actividad {
    int anio; 
    int edad; 
    int mes; 
    int dia; 
    int plazas; 
    int ocupadas; 
    int libres;
    char dia_semana[20];
    char hora_inicio[10];
    char hora_fin[10];
    char actividad_base[50];
    char modalidad[50];
    char centro[100];
    char tipo_actividad[50];
};

struct FrecuenciaHora {
	char hora[15];
	int cantidad;
};

int main() {
    int opcion = 0;
    struct Actividad registros[N];
    int nregistros = 0;
    int i;
    int encontrado = 0;
    int login_valido = 0; // Variable para controlar el bucle
    
    // Creamos en forma de adorno un inicio de sesion como si de una web se tratara.
    char usuario[50];
	char contrasena[50];

    printf("========================================\n");
    printf("    ***GESTION DEPORTIVA MADRID***\n");
    printf("========================================\n\n");
    
    printf("INICIO DE SESION\n\n");
    
    // BUCLE DO WHILE de validacion de las condiciones.
    do 
	{
        printf("Nombre de usuario (Solo letras): ");
        scanf(" %[^\n]", usuario); // El %[^\n] permite leer frases con espacios
        
        printf("Contrasena (Solo letras): ");
        scanf(" %[^\n]", contrasena); // El %[^\n] permite leer frases con espacios
        

        if (SoloLetras(usuario) == 1 && SoloLetras(contrasena) == 1) // Comprobamos con la funcion SoloLetras que la contraseña y el usuario solo tienen letras
    	{
            login_valido = 1; // Todo correcto, permitimos salir del bucle
        } else 
		{
			// Avisamos del error
            printf("-----ERROR: El usuario y la contrasena solo pueden contener letras y espacios.-----\n");
            printf("-----Numeros o caracteres especiales no estan permitidos. Intentelo de nuevo.-----\n\n");
        }
        
    } while (login_valido == 0);

    printf("Bienvenido/a %s.\n", usuario);
    printf("Acceso concedido.\n\n");
    
	// Abrimos y leemos el fichero "deportesayuntamiento.txt" que se encuentra en la misma carpeta que el ejecutable de este mismo archivo.
    FILE * fentrada;
    fentrada = fopen("deportesayuntamiento.txt", "r");
    if (fentrada == NULL) {
        printf("Error abriendo el fichero. Comprueba el nombre exacto.\n");
        return 0;
    }
    
    i = 0;

    while (fscanf(fentrada, "%d %d %d %s %s %s %s %s %s %d %d %d %s", &registros[i].anio, &registros[i].mes, &registros[i].dia, registros[i].dia_semana, registros[i].hora_inicio, registros[i].hora_fin, registros[i].actividad_base, registros[i].modalidad, registros[i].centro, &registros[i].plazas, &registros[i].ocupadas, &registros[i].libres, registros[i].tipo_actividad) != EOF) 
	{
        i++;
        nregistros++;
    }
    fclose(fentrada);
	system("cls");// Util para limpiar la consola y que no aparezca todo el rato el inicio de sesion con los datos del usuario
    do {
    	 
		printf("Bienvenido/a %s.\n", usuario);
		printf("Acceso concedido.\n\n");
        printf("\n ************************************************ ");
		printf("\n *********** GESTION DEPORTIVA MADRID *********** ");
		printf("\n ************************************************ \n");
        printf("\n <<<<<<<<<<<<<<<<<<<<<<Listados>>>>>>>>>>>>>>>>>> \n");
		printf("1. \tInformacion del Listado General.\n");
		printf("2. \tInformacion del Listado de centros.\n"); 
		printf("3. \tInformacion del Listado de deportes.\n");
		
		printf("\n <<<<<<<<<<<<<<<<<<Plazas>>>>>>>>>>>>>>>>>>>>>>> \n");
        printf("4. \tInformacion Disponibilidad por centro (Plazas libres).\n");
        printf("5. \tDeteccion de Actividades 'Fantasma'.\n"); 
		printf("6. \tInformacion de centros con menor ocupacion.\n");
		
		printf("\n <<<<<<<<<<<<<<<<<Demandas>>>>>>>>>>>>>>>>>>>>> \n");
		printf("7. \tRanking **TOP 3** Centros mas demandados.\n");
		printf("8. \tHoras de mayor demanda (actividades por horario).\n");
		
		printf("\n <<<<<<<<<<<<<<<<<Documentos>>>>>>>>>>>>>>>>>>> \n");
        printf("9. \tInforme de Centro.\n");
		printf("10. \tCertificado de inscripcion.\n");

		printf("\n <<<<<<<<<<<<<<<<<Interacciones>>>>>>>>>>>>>>>> \n");
        printf("11. \tBuscador de actividades por dia.\n");
        printf("12. \tSistema de Recomendacion Inteligente.\n");
    	
    	printf("\n <<<<<<<<<<<<<<<<<Estadisticos>>>>>>>>>>>>>>>>> \n");
        printf("13. \tHistograma de Ocupacion.\n");
        
        printf("\n <<<<<<<<<<<<<<<<<Extras>>>>>>>>>>>>>>>>>>>>>>> \n");
        printf("14. \tAyuda.\n");
        
        printf("15. \tSalir del programa.\n");
        printf("Introduce una opcion: \n");
		scanf("%d", &opcion); 
        
        switch(opcion)
		{
            case 1: 
                printf("Imprimiendo listado...\n");
                for (i = 0; i < nregistros; i++)
				{
					char var_temp1[100]; //Definimos variables temporales para no modificar la lista original
					char var_temp2[100];
            		strcpy(var_temp1, registros[i].centro); // Con el comando 'strcpy' copiamos la lista de los centros a la nueva variable temporal
            		strcpy(var_temp2, registros[i].actividad_base);
            		sustituir_guiones(var_temp1); // Sustituimos los guiones en la variable temporal para la lista de centros
            		sustituir_guiones(var_temp2); // Sustituimos los guiones en la variable temporal para la lista de actividades 

                    printf("A %d/%d/%d. Centro y Actividad: %-30s - %-45s: %-03d plazas libres\n", registros[i].dia, registros[i].mes, registros[i].anio, var_temp1, var_temp2, registros[i].libres); 
                } // %-30s Se utiliza para que en la cmd todo este distribuido en columnas. Especificamente, %-30s Reserva 30 espacios y se coloca el caracter a la izquierda.
                break; 
            
            case 2:
				
				ImprimirCentros(registros, nregistros); // Hacemos llamamiento de la funcion
				
				break;
			
			case 3:
				
				
				ImprimirDeportes(registros, nregistros); // Hacemos llamamiento de la funcion de igual manera que la anterior.
				
				break;
			
			case 4:
			
			printf("Centros deportivos con plazas libres \n");
            	for (i = 0; i < nregistros; i++)
				{
					char var_temp1[100]; //Definimos variables temporales para no modificar la lista original
					char var_temp2[100];
            		strcpy(var_temp1, registros[i].centro); // Con el comando 'strcpy' copiamos la lista de los centros a la nueva variable temporal
            		strcpy(var_temp2, registros[i].actividad_base);
            		sustituir_guiones(var_temp1); // Sustituimos los guiones en la variable temporal para la lista de centros
            		sustituir_guiones(var_temp2);
                    
					if(registros[i].libres>0)
					{
                    	printf("A %d/%d/%d. Centro y Actividad: %-30s - %-45s | %-03d ocupadas | %-03d plazas libres \n", registros[i].dia, registros[i].mes, registros[i].anio, var_temp1, var_temp2, registros[i].ocupadas, registros[i].libres); 
					}
				} 
                break;	
			
			case 5: 
			
			printf("\nACTIVIDADES FANTASMA:\n\n");

    				for(i = 0; i < nregistros; i++) 
					{
					char var_temp1[100]; //Definimos variables temporales para no modificar la lista original
					char var_temp2[100];
            		strcpy(var_temp1, registros[i].centro); // Con el comando 'strcpy' copiamos la lista de los centros a la nueva variable temporal
            		strcpy(var_temp2, registros[i].actividad_base);
            		sustituir_guiones(var_temp1); // Sustituimos los guiones en la variable temporal para la lista de centros
            		sustituir_guiones(var_temp2);
        				
						if(registros[i].ocupadas == 0) 
						{
           			 	printf("%-30s | %-45s | %-02s-%-02s | %-02d plazas\n", var_temp1, var_temp2, registros[i].hora_inicio, registros[i].hora_fin, registros[i].plazas);
        				}
   					}

    			break;	
			
			case 6:
				printf("Los centros con menor ocupacion son:\n\n");
								
				for (i = 0; i < nregistros; i++)
				{
					char var_temp1[100]; //Definimos variables temporales para no modificar la lista original
					char var_temp2[100];
            		strcpy(var_temp1, registros[i].centro); // Con el comando 'strcpy' copiamos la lista de los centros a la nueva variable temporal
            		strcpy(var_temp2, registros[i].actividad_base);
            		sustituir_guiones(var_temp1); // Sustituimos los guiones en la variable temporal para la lista de centros
            		sustituir_guiones(var_temp2);
					
					if (registros[i].plazas > 0)
					{
						float porcentaje = ((float)registros[i].ocupadas / registros[i].plazas); //Para que haga el porcentaje bien con decimales ponemos float
						
						if (porcentaje < 0.15) printf("%-30s | %-45s | %-10s | %.0f%%\n", var_temp1, var_temp2, registros[i].hora_inicio, porcentaje * 100); //El doble %% es para que imprima % en pantalla
						
						encontrado = 1;
					}
					
				}
				
				if (encontrado ==0)
				{
					printf("Vaya, parece que los centros estan bastante ocupados .\n");
				
				}
				
				printf("El porcentaje de la derecha indica la ocupacion del centro correspondiente (valores como 0% indican que no hay nadie registrado aun).\n");
			
				break;
			
			
			case 7:
            {
            	int i, j, k;
			
			    char centros[200][100];
			    int total_ocupadas[200];
			    int num_centros = 0;
			
			    for(i = 0; i < nregistros; i++)
			    {
			        encontrado = 0;
			
			        for(j = 0; j < num_centros; j++)
			        {
			            if(comparar(registros[i].centro, centros[j]) == 1)
			            {
			                total_ocupadas[j] += registros[i].ocupadas;
			                encontrado = 1;
			                break;
			            }
			        }
			
			        if(encontrado == 0)
			        {
			            k = 0;
			
			            while(registros[i].centro[k] != '\0')
			            {
			                centros[num_centros][k] = registros[i].centro[k];
			                k++;
			            }
			
			            centros[num_centros][k] = '\0';
			
			            total_ocupadas[num_centros] = registros[i].ocupadas;
			
			            num_centros++;
			        }
			    }
			
			    for(i = 0; i < num_centros - 1; i++)
			    {
			        for(j = i + 1; j < num_centros; j++)
			        {
			            if(total_ocupadas[j] > total_ocupadas[i])
			            {
			                int aux_ocupadas;
			                char aux_centro[100];
			
			                aux_ocupadas = total_ocupadas[i];
			                total_ocupadas[i] = total_ocupadas[j];
			                total_ocupadas[j] = aux_ocupadas;
			
			                k = 0;
			
			                while(centros[i][k] != '\0')
			                {
			                    aux_centro[k] = centros[i][k];
			                    k++;
			                }
			
			                aux_centro[k] = '\0';
			
			                k = 0;
			
			                while(centros[j][k] != '\0')
			                {
			                    centros[i][k] = centros[j][k];
			                    k++;
			                }
			
			                centros[i][k] = '\0';
			
			                k = 0;
			
			                while(aux_centro[k] != '\0')
			                {
			                    centros[j][k] = aux_centro[k];
			                    k++;
			                }
			
			                centros[j][k] = '\0';
			            }
			        }
			    }
			
			    printf("\n===== TOP 3 CENTROS MAS DEMANDADOS =====\n\n");
			
			    for(i = 0; i < 3 && i < num_centros; i++)
			    {
			    	
			    	char var_temp1[100]; //Definimos variables temporales para no modificar la lista original
            		strcpy(var_temp1, centros[i]); // Con el comando 'strcpy' copiamos la lista de los centros a la nueva variable temporal
            		sustituir_guiones(var_temp1); // Sustituimos los guiones en la variable temporal para la lista de centros
			
			        printf("%d. %-35s | %d plazas ocupadas\n", i + 1, var_temp1, total_ocupadas[i]);
			    }
			
			    break;
            }

			case 8: 
			{
				struct FrecuenciaHora horas[N];
                int num_horas = 0;
                int j_idx;
                
                printf("Calculando las horas con mayor cantidad de actividades...\n");

                for (i = 0; i < nregistros; i++) 
                {
                    int hor_encontrada = 0;
                    
                    for (j_idx = 0; j_idx < num_horas; j_idx++) 
                    {
                        if (comparar(registros[i].hora_inicio, horas[j_idx].hora) == 1) 
                        {
                            horas[j_idx].cantidad++;
                            hor_encontrada = 1;
                            break;
                        }
                    }
                    
                    if (hor_encontrada == 0) 
                    {
                        strcpy(horas[num_horas].hora, registros[i].hora_inicio);
                        horas[num_horas].cantidad = 1;
                        num_horas++;
                    }
                }

                for (i = 0; i < num_horas - 1; i++) 
                {
                    for (j_idx = 0; j_idx < num_horas - i - 1; j_idx++) 
                    {
                        if (horas[j_idx].cantidad < horas[j_idx+1].cantidad) 
                        {
                            struct FrecuenciaHora temp = horas[j_idx];
                            horas[j_idx] = horas[j_idx+1];
                            horas[j_idx+1] = temp;
                        }
                    }
                }

                printf("\n-------------- HORAS DE MAYOR DEMANDA --------------\n");
                printf("%-15s | %-20s\n", "HORA INICIO", "NUMERO DE ACTIVIDADES");
                printf("-------------------------------------------------------\n");
                for (i = 0; i < num_horas; i++) 
                {
                    printf("%-15s | %-20d\n", horas[i].hora, horas[i].cantidad);
                }
                printf("\n");
                
                break;
			}
			
			case 9:
			{
			    FILE * fsalida;
				char nombre_fichero[100];
				char centro_buscado[100]; // En esta variable se almacenan los nombres de los deportes sin '_'
				
				
				printf("Introduce el nombre del centro para generar el informe. Ej: Francisco Fernandez Ochoa (Intenta no dejar un espacio al final): \n"); // Se puede hacer un bucle for que quite los espacios del final del nombre, ya que si estos existen, va a dar error.
				scanf(" %[^\n]", centro_buscado);
				
				poner_guiones(centro_buscado);
				
				strcpy(nombre_fichero, centro_buscado);
				
				fsalida = fopen(strcat(nombre_fichero, ".txt"), "w");
				
				if (fsalida == NULL)  // Bucle en caso de que exista algun error creando el archivo
				{
					printf("Error al crear el archivo.\n");
					break; 
				}

				fprintf(fsalida, "====================================================================\n");
				fprintf(fsalida, "                         INFORME DETALLADO: %s\n", centro_buscado);
				fprintf(fsalida, "====================================================================\n\n");
				fprintf(fsalida, "INFORMACION DE LOCALIZACION DEL CENTRO:\n");
				fprintf(fsalida, "Consulte lineas de EMT y Metro en: www.madrid.es\n\n");
				fprintf(fsalida, "ACTIVIDADES OFERTADAS:\n\n");
				fprintf(fsalida, "%-45s | %-10s | %-10s | %-6s\n", "ACTIVIDAD", "INICIO", "FIN", "PLAZAS"); // Los ponemos como variables char para poder contar los espacios y que concuerden con los datos que estarán mas abajo.
				fprintf(fsalida, "--------------------------------------------------------------------\n");
				
				encontrado = 0; 
				for (i = 0; i < nregistros; i++) 
				{
					if (comparar(registros[i].centro, centro_buscado) == 1) 
					{
						char var_temp2[100]; //Definimos variables temporales para no modificar la lista original
            			strcpy(var_temp2, registros[i].actividad_base); // Con el comando 'strcpy' copiamos la lista de los centros a la nueva variable temporal
            			sustituir_guiones(var_temp2);
						fprintf(fsalida, "%-45s | %-10s | %-10s | %-6d\n", var_temp2, registros[i].hora_inicio, registros[i].hora_fin, registros[i].plazas);
						encontrado = 1;
					}
				}
				
				fclose(fsalida);
				
				if (encontrado == 0) 
				{
					printf("No se han encontrado datos para el centro: %s\n", centro_buscado);
				} 
				else 
				{
					printf("Generando Informe...\n");
					printf("EXITO. El informe '%s' ha sido creado en la carpeta del proyecto.\n", nombre_fichero);
				}
				
				break;
			}
			
			case 10:
			{
				char nombre[100];
			    char dni[20];
			    int indice;
			    int datos_validos = 0;
			
			    FILE *fcertificado;
			
			    printf("\n*****CERTIFICADO DE INSCRIPCION****\n");
			
			    do
			    {
			        printf("Introduce tu nombre y primer apellido: ");
			        scanf(" %[^\n]", nombre);
			
			        printf("Introduce tu DNI (8 numeros y 1 letra): ");
			        scanf("%s", dni);
			
			        if(SoloLetras(nombre) == 1 && DNIValido(dni) == 1)
			        {
			            datos_validos = 1;
			        }
			        else
			        {
			            printf("\n----- ERROR EN LOS DATOS -----\n");
			
			            if(SoloLetras(nombre) == 0)
			            {
			                printf("El nombre solo puede contener letras y espacios.\n");
			            }
			
			            if(DNIValido(dni) == 0)
			            {
			                printf("El DNI debe tener 8 numeros y 1 letra.\n");
			            }
			
			            printf("Intentelo de nuevo.\n\n");
			        }
			
			    } while(datos_validos == 0);
			    for(i = 0; i < nregistros; i++)  //MEJOR QUE PEDIR EL NUMERO DE LA ACTIVIDAD, que es bastante tedioso sobre todo porque hay 5000 lineas, preguntar por el deporte en cuestion, la hora, el sitio, etc...
				{
					
					char var_temp1[100]; //Definimos variables temporales para no modificar la lista original
					char var_temp2[100];
            		strcpy(var_temp1, registros[i].centro); // Con el comando 'strcpy' copiamos la lista de los centros a la nueva variable temporal
            		strcpy(var_temp2, registros[i].actividad_base);
            		sustituir_guiones(var_temp1); // Sustituimos los guiones en la variable temporal para la lista de centros
            		sustituir_guiones(var_temp2);
					
			        printf("%d. %s - %s - %s %s\n", i, var_temp1, var_temp2, registros[i].dia_semana, registros[i].hora_inicio);
			    }
			
			    printf("Selecciona el numero de actividad: \n");  // A ESTO ES A LO QUE ME REFIERO MAS ARRIBA
			    scanf("%d", &indice);
			    printf("\n");
			
			    if(indice < 0 || indice >= nregistros) 
				{
					printf("Actividad no valida\n");
			        break;
			    }
			
			    fcertificado = fopen("certificado_inscripcion.txt", "w");
			
			    if(fcertificado == NULL) 
				{
					printf("Error creando el certificado\n");
			        break;
			    }
				
				sustituir_guiones(registros[indice].centro); // QUITAMOS LOS GUIONES
				sustituir_guiones(registros[indice].actividad_base);
			    
				fprintf(fcertificado, "========== CERTIFICADO DE INSCRIPCION ==========\n\n");
				fprintf(fcertificado, "Nombre del usuario: %s\n", nombre);
				fprintf(fcertificado, "DNI: %s\n", dni);
				fprintf(fcertificado, "Centro deportivo: %s\n", registros[indice].centro);
				fprintf(fcertificado, "Actividad: %s\n", registros[indice].actividad_base);
				fprintf(fcertificado, "Dia: %s %d/%d/%d\n", registros[indice].dia_semana, registros[indice].dia, registros[indice].mes, registros[indice].anio);
				fprintf(fcertificado, "Horario: %s - %s\n", registros[indice].hora_inicio, registros[indice].hora_fin);
				fprintf(fcertificado, "\n===============================================\n");
				
				poner_guiones(registros[indice].actividad_base); // LOS VOLVEMOS A PONER PARA NO MODIFICAR LA LISTA ORIGINAL
				poner_guiones(registros[indice].centro);
				
				fclose(fcertificado);
			
			    printf("Certificado generado correctamente.\n");
			    printf("Archivo creado en su carperta y titulado: certificado_inscripcion.txt\n");
			
			    break;
			}
			
			case 11:
			{
				char act_buscado[50];
				char dia_buscado[20];
				char respuesta[20];
				char ver_deportes;
				
				printf("\n--- BUSCADOR DE ACTIVIDADES POR DIA ---\n");

				do 
				{
					printf("Quieres ver la lista de deportes disponibles primero? (S/N):\n");
					scanf("%s", respuesta);
					ver_deportes = respuesta[0];
					
					if (ver_deportes != 'S' && ver_deportes != 'N') 
					{
						printf(">> Opcion Incorrecta. Por favor, escriba unicamente S o N.\n\n");
					}
				} while (ver_deportes != 'S' && ver_deportes != 'N');
				
				if (ver_deportes == 'S') 
				{
					ImprimirDeportes(registros, nregistros);
					printf("\n");
				}
				
				do 
				{
					printf("Introduce la actividad (Escribalo igual que en la lista, ej: gap o core): "); 
					
					fflush(stdin);
					scanf(" %[^\n]", act_buscado); // El %[^\n] permite leer frases con espacios
					poner_guiones(act_buscado);
					
				} while (SoloLetras(act_buscado) == 0); // Se ha tenido que modificar la funcion para que se pueda admitir la barra baja del fichero
				
				printf("Introduce el dia (Ej: lunes, martes, miercoles, jueves, viernes, sabado, domingo) o escriba 'TODOS':");
				fflush(stdin);
				scanf(" %s", dia_buscado);
				printf("\n");
				sustituir_guiones(act_buscado);
				printf("Buscando '%s' para dia '%s'...\n", act_buscado, dia_buscado);
				poner_guiones(act_buscado);
				printf("---------------------------------------------------------------------\n");
				printf("%-30s | %-12s | %-10s | %-8s\n", "CENTRO DEPORTIVO", "DIA", "HORARIO", "LIBRES");
				printf("---------------------------------------------------------------------\n");
                encontrado = 0; 
				for (i = 0; i < nregistros; i++)
				{
					if (comparar(registros[i].actividad_base, act_buscado) == 1)
					{
						if (comparar(registros[i].dia_semana, dia_buscado) == 1 || comparar(dia_buscado, "TODOS") == 1) // CONDICIÓN  El día debe coincidir o el usuario ha escrito "TODO" (Caracteres constantes)
						{
			
							if (registros[i].libres > 0)
							{
								sustituir_guiones(registros[i].centro);
								printf("%-30s | %-12s | %-5s-%-4s | %-8d\n", registros[i].centro, registros[i].dia_semana, registros[i].hora_inicio, registros[i].hora_fin, registros[i].libres);	
								encontrado++;
								poner_guiones(registros[i].centro);
							}
						}
					}
				}

				if (encontrado == 0)
				{
					printf("\nLo sentimos, no hay plazas libres para '%s' con esos filtros.\n", act_buscado);
					printf("(Tip: Asegurate de haber escrito las mayusculas exactamente igual que en la lista)\n");
				} else
				{
					printf("Total de clases encontradas: %d. \n", encontrado);
				}
				printf("---------------------------------------------------------------------\n\n");
				break;   
			}
			
			case 12: 
			{
			    SistemaRecomendacion(registros, nregistros);
				break;
			}
			case 13:
			{
				int num_centros = 0;
			    char centros_elegidos[10][100]; // [5] Indica la cantidad de centros que se almacenan en la variable
				char respuesta[20];
				char ver_centros;
				int j, k;

			    printf("\n--- HISTOGRAMA DE OCUPACION ---\n");
			    
			    do {
			        printf("Cuantos centros quieres comparar en el grafico (1 a 10)?: ");
			        scanf("%d", &num_centros);
					/* if (scanf("%d", &num_centros) != 1) 
					{
			            while (getchar() != '\n'); // Limpiamos si mete letras
			            num_centros = 0;
			        }*/
			        if (num_centros < 1 || num_centros > 10) printf("Eleccion incorrecta o fuera de rango. Elija del 1 al 10.");
			    } while (num_centros < 1 || num_centros > 10);
				
				do 
				{
					printf("Quieres ver la lista de centros disponibles primero? (S/N):\n");
					scanf("%s", respuesta);
					ver_centros = respuesta[0];
					
					if (ver_centros != 'S' && ver_centros != 'N') 
					{
						printf(">> Opcion Incorrecta. Por favor, escriba unicamente S o N.\n\n");
					}
				} while (ver_centros != 'S' && ver_centros != 'N');
				
				if (ver_centros == 'S') 
				{
					ImprimirCentros(registros, nregistros);
					//printf("\n");
				}
				
			    for (i = 0; i < num_centros; i++) {
			        printf("\nIntroduce el nombre del centro %d: (Copia y pega de la lista de centros) \n", i + 1);
			        scanf(" %[^\n]", centros_elegidos[i]);
			      	poner_guiones(centros_elegidos[i]);
			    }
				printf("\n\n");
				
				// Realizamos el estilo del gráfico
			    printf("Generando grafico...\n");
			    printf("%-28s | %-50s | %s\n", "CENTRO DEPORTIVO", "0%                      50%                    100%", "OCUP.");
			    printf("--------------------------------------------------------------------------------------------------\n");

			    for (i= 0; i < num_centros; i++) 
				{
			        int total_plazas = 0;
			        int total_ocupadas = 0;
			        int centro_existe = 0;

			        // Buscamos los datos de este centro en el fichero
			        for (k = 0; k < nregistros; k++) 
					{
			            if (comparar(registros[k].centro, centros_elegidos[i]) == 1) 
						{
			                total_plazas += registros[k].plazas;
			                total_ocupadas += registros[k].ocupadas;
			                centro_existe = 1;
			            }
			        }

			        if (centro_existe == 1 && total_plazas > 0)  // Realizamos una regla de tres en donde 100% de la Ocupacion equivale a 50 Caracteres o 2% de ocupacion equivale a 1 caracter.
					{
			            float porcentaje = ((float)total_ocupadas / total_plazas) * 100.0;
			            int num_caracteres = (int)(porcentaje / 2.0);
			            
			            sustituir_guiones(centros_elegidos[i]);
			            printf("%-28s | ", centros_elegidos[i]);
						poner_guiones(centros_elegidos[i]); 
						
			            for (j = 0; j < 50; j++) 
						{
			                if (j < num_caracteres) {
			                    printf("#"); // Pintamos la barra
			                } else {
			                    printf(" "); // Rellenamos el resto con espacios blancos
			                }
			            }
			            
			            printf(" | %5.2f%%\n", porcentaje);// Se cierra la barra y se muestra el porcentaje final
			        } 
					else 
					{
			            // Si el usuario se inventó el nombre
			            for (i = 0; i<num_centros; i++)
			            {
							sustituir_guiones(centros_elegidos[i]); // No me hace falta poner guiones ya que el centro no esta en la lista
						}
			            printf("%-28s | Centro no encontrado o sin plazas.\n", centros_elegidos[i]);
			        }
			    }
			    
			    printf("--------------------------------------------------------------------------------------------------\n");
			    break;
			 } 
			
			case 14: //Voy a imprimir unas opciones para que el usuario elija y luego voy a hacer otro menu de casos con los que pueda interactuar. Sin embargo solo van a ser frases informativas y orientativas.
   				int duda;
  				printf("\n==========================================================\n");
 				printf("          SISTEMA DE AYUDA Y ASISTENCIA AL USUARIO         \n");
 				printf("==========================================================\n");
  				printf("Hola, ¿en que podemos ayudarte hoy?\n");
 				printf("1. No encuentro mi centro deportivo.\n");
   				printf("2. ¿Como genero un certificado oficial?\n");
    			printf("3. ¿Que es una 'Actividad Fantasma'?\n");
    			printf("4. No entiendo como funciona el histograma.\n");
    			printf("5. Otros problemas.\n");
    			printf("Introduce tu duda (1-4): ");
   				scanf("%d", &duda);
   				
   					switch(duda) {
   						case 1:
   							printf("GUIA: Muchos centros utilizan guiones bajos, mayusculas etc.\n");
   							printf("Prueba a utilizar la funcion 4 del menu principal para copiar y pegar el centro sin problemas.\n");
   						break;
   										
   						case 2:
           					printf("GUIA: Selecciona la opcion 12. Necesitaras tener a mano tu DNI.\n");
            				printf("El programa generara un archivo llamado 'certificado_inscripcion.txt, en la misma carpeta donde tienes este programa'\n");
   						break;
   						
   						case 3:
   							printf("GUIA: Las actividades fantasma son aquellas en las que la ocupacion de la actividad es del 0%%, es decir,\n no hay nadie apuntado y por ello son como un 'fantasma'.\n");
   							printf("De esta manera, si no te gustan las actividades tan masificadas, las actividades fantasma son ideales para ti.\n");
						break;
						
						case 4:
							printf("GUIA: el histograma es un indicador grafico del aforo de personas que ocupan plazas en los distintos centros que se hayan indicado comparar.\n");
							printf("El simbolo #, indica el %% de ocupacion, por lo que los centros con mas #, son los mas ocupados.\n");
						break;
						
						case 5:
							printf("Si su problema no se encuentra en las opciones anteriores llame al 123 456 789.\n");
						break;
						
						default:
							printf("Prueba a reiniciar el programa o a llamar al soporte tecnico.\n");
				}
   			
				break;
				
			case 15:
                printf("Muchas gracias por utilizar nuestro porgrama de GESTION DEPORTIVA. Hasta la proxima.\n");
                break;
                
            default:
                printf("Opcion incorrecta.\n");
        }
    } while (opcion != 15);
    
    return 0; 
}


void sustituir_guiones (char cadena[]) // PARA NO CAMBIAR TODAS LAS CADENAS, 
{
	int i=0; 
	while(cadena[i]!='\0') 
	{
		if (cadena[i] == '_')
		{
			cadena[i] = ' '; 
		}
		i++; 
	}	
}

void poner_guiones(char cadena[]) // MISMA FUNCION QUE "sustituir_guiones" pero a la inversa
{
    int i = 0;
    while(cadena[i] != '\0') 
    {
        if (cadena[i] == ' ') 
        {
            cadena[i] = '_'; 
        }
        i++;
    }    
}

int comparar(const char lista1[], const char lista2[]) // Funcion que compara las cadenas de caracteres de la lista de 'deportesayuntamientos.txt'
{
    int k = 0;
    
    while (lista1[k] != '\0' || lista2[k] != '\0') // Comprueba caracter por caracter hasta que se encuentra un espacio. (También se incluyen las '_' que son separaciones dentro de una misma cadena)
	{
        if (lista1[k] != lista2[k]) 
		{
            return 0;  // DEVUELVE 0 SI SON DISTINTAS
        }
        k++;
    }
    
    return 1; // DEVUELVE 1 SI SON IGUALES. IMPORTANTE: saber que devuelve la funcion para poder utilizarla correctamente en el main.
}

void ImprimirCentros(struct Actividad registros[], int nregistros) // Funcion void para imprimir por pantalla los centros sin repetir.
{
    int i, j;
    printf("--- LISTADO DE CENTROS DEPORTIVOS ---\n");
    
    for (i = 0; i < nregistros; i++) 
	{
        int repetido = 0;
        
        for (j = 0; j < i; j++) 
		{
            if (comparar(registros[i].centro, registros[j].centro) == 1) // Nombramos a la funcion 'comparar'.
			{
                repetido = 1; 
                break;
            }
        }
        
        if (repetido == 0) 
		{ 
			char var_temp1[100];
            strcpy(var_temp1, registros[i].centro);
            sustituir_guiones(var_temp1);
            printf("%s\n", var_temp1);
        }
    }
}


void ImprimirDeportes(struct Actividad registros[], int nregistros) // De manera parecida a la anterior, nombramos una funcion void para imprimir la lista de deportes sin que se repitan.
{
    int i, j;
    printf("--- LISTADO DE DEPORTES/ACTIVIDADES ---\n");
    
    for (i = 0; i < nregistros; i++) 
	{
        int repetido = 0;
        
        for (j = 0; j < i; j++) 
		{
            if (comparar(registros[i].actividad_base, registros[j].actividad_base) == 1) 
			{
                repetido = 1; 
                break;
            }
        }
        
        if (repetido == 0) 
		{
            char var_temp2[100];
            strcpy(var_temp2, registros[i].actividad_base);
            sustituir_guiones(var_temp2);
            printf("%s \n", var_temp2);
        }
    }
}


void SistemaRecomendacion(struct Actividad registros[], int nregistros) 
{
    char act_buscada[50];
    char repetir;
    int i;

    int indice_ganador = -1; // Inicializamos a -1 porque en 0 nos da error. 
    float mejor_porcentaje = -1.0;  // Esto se debe a que si elegimos una actividad con 0 plazas libres y entramos en:  if (porcentaje_actual > mejor_porcentaje), nos puede devolver que el mejor deporte para el usuario seria uno con 0 plazas disponibles. Asi corregimos ese error. 

    printf("--- SISTEMA INTELIGENTE DE RECOMENDACION ---\n");
    printf("Que deporte te gustaria practicar? (ej: pilates, nado_libre): \n"); // Puede ser que el usuario, si ha elegido esta opcion, no sepa que deportes hay disponibles en este fichero, asi que le damos la opcion de mostrar deportes.
    printf("Quieres echar un vistazo a la lista de deportes? (S/N) \n");
	

	do
	{
		fflush(stdin); // Para reiniciar los caracteres de la memoria.
		scanf("%c", &repetir);
		if (repetir!='S' && repetir!='N') printf("Opcion Incorrecta. Quieres echar un vistazo a la lista de deportes? (S/N) \n");
	}while (repetir!='S' && repetir!='N');
	
	if (repetir=='S')
	{
		ImprimirDeportes(registros, nregistros);
		printf("\n\n (Recomendable: copie y pegue el deporte)\n\n");
	}
	
	printf("Que deporte te gustaria practicar? (ej: pilates, nado_libre): \n"); // Volvemos a preguntar ahora  que el usuario sabe que deportes hay disponibles
	
	fflush(stdin); // Necesario para limpiar la memoria. Si no, lo que sucede es que el programa interpreta 'gimnasia_suave_b_balance' como 'imnasia_suave_b_balance' por ejemplo. Se come la primera letra.
	scanf(" %[^\n]", act_buscada);
	printf("\n\n");
	poner_guiones(act_buscada);

    for (i = 0; i < nregistros; i++) // Buscamos en la lista la actividad buscada
	{
        if (comparar(registros[i].actividad_base, act_buscada) == 1)  // Nuevamente volvemos a utilizar la funcion 'comparar'
		{
            if (registros[i].plazas > 0 && registros[i].libres > 0)  // Util en caso de error al dividir por 0. 
			{
                float porcentaje_actual = ((float)registros[i].libres / registros[i].plazas) * 100.0; // Se necesita que sean variables float con decimales, ya que la division no siempre proporciona valores enteros.
                
                if (porcentaje_actual > mejor_porcentaje) 
				{
                    mejor_porcentaje = porcentaje_actual; 
                    indice_ganador = i;      
                }
            }
        }
    }
    
    printf("Analizando %d registros...\n\n", nregistros);
    
    if (indice_ganador == -1)  // Esto quiere decir que no se ha encontrado ninguna actividad y por lo tanto el bucle no ha actualizado el contador.
	{
        printf("Actualmente no hay plazas libres para %s en todo Madrid. Por favor, intentelo de nuevo mas tarde.\n", act_buscada);
    } else 
	{
        printf("*** NUESTRA RECOMENDACION ***\n");
        sustituir_guiones(registros[indice_ganador].centro);
        printf("Le recomendamos el centro deportivo: %s. \n", registros[indice_ganador].centro);
        poner_guiones(registros[indice_ganador].centro);
        printf("\t -Dia de la semana: %s. \n", registros[indice_ganador].dia_semana);
        printf("\t -Horario: de %s a %s. \n", registros[indice_ganador].hora_inicio, registros[indice_ganador].hora_fin);
        
        printf("Por que te recomendamos esta opcion?\n");
        printf("Pensamos que sentira mas comodo en una actividad menos masificada. Tiene %d plazas libres de un total de %d.\n", registros[indice_ganador].libres, registros[indice_ganador].plazas);
        printf("El porcentaje de plazas libres es del %.2f%%.", mejor_porcentaje);
        printf("\n\n");
    }	
}


int SoloLetras(char cadena[]) // Función que comprueba si una cadena tiene solo letras y espacios
{
    int i = 0;
    if (cadena[0] == '\0') return 0; // Si el usuario no escribe nada, da error

    while (cadena[i] != '\0') 
	{
        char c = cadena[i];
        
        
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ' || c=='_')) // Verificamos si NO es una letra mayúscula, NI minúscula, NI un espacio
		{
            return 0; // Hemos encontrado un número o símbolo -> ERROR
        }
        i++;
    }
    return 1; // Todo es correcto, solo hay letras
}

// Funcion para validar DNI
// Debe tener 8 numeros y 1 letra
int DNIValido(char dni[])
{
    int i;

    // Comprobar longitud
    for(i = 0; dni[i] != '\0'; i++);

    if(i != 9)
    {
        return 0;
    }

    // Comprobar los 8 primeros numeros
    for(i = 0; i < 8; i++)
    {
        if(dni[i] < '0' || dni[i] > '9')
        {
            return 0;
        }
    }

    // Comprobar ultima letra
    if(!((dni[8] >= 'A' && dni[8] <= 'Z') ||
         (dni[8] >= 'a' && dni[8] <= 'z')))
    {
        return 0;
    }

    return 1;
}
