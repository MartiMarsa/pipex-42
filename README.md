# pipex-42
This project will let you discover in detail a UNIX mechanism that you already know by using it in your program.

PSEUDOCODE


	./pipex infile "ls -l" "wc -l" outfile

	usaremos una estructura que contenga los datos 
	typedef struct s_pipex
	{
		pid_t	pid1; ->> fork(): primera bifurcacion del proceso
		pid_t	pid2; ->> fork(): segunda bifurcacion del proceso
		int		tube[2]; ->> pipe(tube[2]): nos devuelve 2 fd, tube[0] para read y tube [1] para write
		int		infile; ->> el primer argumento, usamos la funcion open (OREADONLY) para obtener el fd 
		int		outfile; ->> el utlimo argumento, usamos 
		char	*paths; ->> las rutas que alberga la variable entorno PATH
		char	**cmd_paths; ->> arreglo de punteros a cadenas que contienen las rutas de los binarios {"", "/usr/bin", "/bin", NULL}
		char	**cmd_args; ->> arreglo de punteros a cadenas que contienen el argumento de la linea de comandos {"ls", "-l", NULL}
		char	*cmd; ->> variable que almacena la ruta completa al ejecutable del programa que se va a ejecutar. "/usr/bin/ls" o NULL si no existe
	}t_pipex;

	main ---> int	main(int argc, char *argv[], char *envp[])

	t_data	*data;

	if (argc != 5) { (error manejable)
		ERROR_MESSAGE 1 -> // implementar funcion que maneja errores y salida de programa. 
	}
	1- obtener infile -> OPEN argv[1] READONLY -> CONTROL ERROR; { (error critico)
		ERROR_MESSAGE 2 -> // 
	}
	2- obtener outfile -> OPEN argv[4] TRUNCAR / CREAR / READ&WRITE -> CONTROL ERROR;{ (error critico)
		ERROR_MESSAGE 2	
	}
	3- abrir pipe -> CONTROL ERROR;{ (error critico)
		ERROR_MESSAGE 3	
	}
	4- aislar las rutas de los binarios de la variable de entorno PATH;    -->>      data->paths = get_paths(envp) // implementar funcion
	5- crear un array de punderos a cadenas con las rutas de los binarios;    -->>    data->cmd_paths = ft_split(data->paths, ":")
	6- bifurcar proceso con fork() -> CONTROL DE ERROR -> ejecutar proceso hijo;
		
		Proceso que se va a encargar de escribir al pipe;
		- Cerrar fd properly
		- duplicar fd
		- encontrar el comando en los directorios de "PATH" -> CONTROL DE ERROR (si no existe el comando salida abrupta)
		- execve (ruta comando, comando, entorno)

	7- bifurcar proceso con fork() -> CONTROL DE ERROR -> ejecutar proceso hijo;

		Proceso que se va a encargar de leer en el pipe y escribir en el archivo de salida
		- Cerrar fd properly
		- duplicar fd
		- encontrar el comando en los directorios de "PATH" -> CONTROL DE ERROR (si no existe el comando salida abrupta)
		- execve (ruta comando, comando, entorno)

	8- Proceso padre monitorea procesos hijos y freezea lo mallokiado;
	9-RETURN :);


	pipex()

	MENSAJES DE ERROR:
	1- CANTIDAD DE ARGUMENTOS; 
	2- ERROR AL ABRIR EL ARCHIVO -> ARCHIVO NO EXIXTE, PERMISOS INSUFICIENTES, RUTA EQUIVOCADA, LIMITE DE ARCHIVOS ABIERTOS POR PROCESO, DOS O MAS PROCESOS INTENTAN ABRIR EL MISMO ARCHIVO (CONDICIONES DE CARRERA ERROENAS);
	3- ERROR AL CREAR PIPE -> Límite de tuberías alcanzado, Fallo en la asignación de recursos, Permisos insuficientes, Fallo interno del sistema;
	4- ERROR AL DUPLICAR PROCESO "FORK()" -> Exceso de procesos, Fallo en la asignación de recursos, Límite de procesos hijo alcanzado, Fallo interno del sistema;
	5- ERRORES DE QUE OCURREN EN PROCESOS HIJOS.............

