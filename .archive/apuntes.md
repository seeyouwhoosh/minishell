## Funciones externas permitidas
```c
#include <stdio.h>
int printf(const char *restrict format, ...);
/* @ Cuando ocurre un error, imprime "el coso: el mensaje del error asignado", el mensaje 
varía según el ERRNO */
void perror(const char *s);

#include <stdlib.h>
void *malloc(size_t size);
void free(void *ptr);
void exit(int status);

/* @ Para conseguir el contenido del environment, principalmente creo que PATH y supongo
que todo lo demás si hay que imitar el comportamiento de hecho */
char *getenv(const char *name);

#include <fcntl.h>
int open(const char *pathname, int flags, mode_t mode);

#include <unistd.h>

/* @ Mira si los permisos de un archivo son correctos
@ int mode: Bitwise-inclusive OR of the access permissions to be checked (R_OK, W_OK, X_OK)
or the existence test (F_OK)
@ return: 0 si no hay ningún problema, -1 otherwise, que hay específicos, según definidos */
int access(const char *pathname, int mode);
ssize_t write(int fildes, const void *buf, size_t nbyte);
ssize_t read(int fildes, void *buf, size_t nbyte);
int close(int fildes);

/* @ El absolute path al current working directory, pero solo para el proceso, es decir, no
altera realmente la localización de la termina actual */
char *getcwd(char *buf, size_t size);

/* @ Es como un "cd", funciona para ".." */
int chdir(const char *path);

/* @ Se crea una copia del proceso activo. PID adopta un valor (el identificador del proceso
hijo), hace lo que tiene que hacer como si fuera un programa aparte (puedes hacer exit)
compartiendo variables del proceso que se ha copiado antes. Por lo que entiendo, cuando
termina el proceso, regresa al proceso padre con el PID, no se mantienen las variables
cambiadas. Relevante para hacer exec de algún tipo */
pid_t fork(void);
int execve(const char *path, char *const _Nullable argv[], char *const _Nullable envp[]);
int dup(int fildes);
int dup2(int fildes, int fildes2);
int pipe(int fildes[2]);

/* @ find the pathname of a terminal associated with the file descriptor */
char *ttyname(int fildes);

/* @ En qué slot está la terminal actual, pero creo que hoy en día está prácticamente
deprecated */
int ttyslot(void);

/* @ Básicamente eliminar lo que sea que tenga ese nombre, si hay algún proceso con el archivo
abierto, espera a que acabe antes de eliminarlo */
int unlink(const char *path);

#include <dirent.h>

/* @ Similar al open() para los files */
DIR *opendir(const char *dirname);

/* @ Similar al read() de los files, excepto que te devuelve un puntero a struct que contiene
el nombre de la carpeta en el elemento char *d_name */
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);

#include <sys/wait.h>
pid_t wait(int *stat_loc);
pid_t waitpid(pid_t pid, int *stat_loc, int options);
pid_t wait3(int *_Nullable wstatus, int options, struct rusage *_Nullable rusage);
pid_t wait4(pid_t pid, int *_Nullable wstatus, int options, struct rusage *_Nullable rusage);

#include <signal.h>
/* @ Cuando se ejecuta la señal, se delega a la handler */
sighandler_t signal(int signum, sighandler_t handler);

/* @ Examina y cambia la acción asociada a la señal
@ sigaction act: define cómo actúa la señal, puede ser NULL, en tal caso, no cambia nada. Mirar
struct abajo.
@ sigaction oact: aquí es donde se almacena la información de la señal antes de cambiar, puede
ser NULL, en tal caso no se almacena nada */
int sigaction(int sig, const struct sigaction *restrict act, struct sigaction *restrict oact);
int sigemptyset(sigset_t *set);
int sigaddset(sigset_t *set, int signo);

/* @ Send a signal to a process */
int kill(pid_t pid, int sig);

#include <sys/stat.h>
/* Get file information */
int stat(const char *restrict path, struct stat *restrict statbuf);
int fstat(int fd, struct stat *statbuf);
int lstat(const char *restrict path, struct stat *restrict statbuf);

#include <string.h>
char *strerror(int errnum)

#include <sys/iotcl.h>
int ioctl(int fd, unsigned long op, ...);

#include <readline/readline.h>
/* @ Esto es como la función input() de python */
char *readline(const char *prompt);

/* @ Permite acceder a comandos anteriores usando las flechas*/
void add_history(const char *line);
void rl_clear_history();

/* @ Indica al sistema que estás en una nueva línea, like, cuando has insertado un comando y pones
enter. No entiendo muy bien esto, pero podrían surgir problemas si no se pone*/
int rl_on_new_line();

/* @ Reemplazar la línea actual con lo que sea que tenga text; el clear_undo es para indicar si hay
que limpiar el historial */
void rl_replace_line(const char *text, int clear_undo);

/* @ Vuelve a mostrar el prompt */
void rl_redisplay();

#include <term.h>
int tgetent(char *bp, const char *name);
int tgetflag(const char *id);
int tgetnum(const char *id);
char *tgetstr(const char *id, char **area);
char *tgoto(const char *cap, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));


#include <termios.h>
int tcsetattr(int fildes, int optional_actions, const struct termios *termios_p);
int tcgetattr(int fildes, struct termios *termios_p);
```

## Guidelines generales

### Detalles detallados (https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)

### Notas de lo que no hace falta gestionar
* "The readline() function can cause memory leaks. You don’t have to fix them."

### Características en general
- [ ] Runnear comandos con rutas absolutas, relativas y sin ruta
- [ ] Todos los comandos se ven con el comando `history`
- [ ] Manejar `"..."` (no expande los caracteres especiales excepto el dólar) y `'...'` (no expande nada, todo es literal);
	* Metacharacters are: pipe (|), ampersand (&), semicolon (;), less-than sign (<), greater-than sign (>), left parenthesis ((), right parenthesis ()), dollar sign ($), backquote (`), backslash (\), right quote ('), double quotation marks (")
- [ ] `Not interpret unclosed quotes or special characters which are not required by the subject such as \ (backslash) or ; (semicolon).` Esto me parece muy sospechoso
- [ ] Variables de entorno $ALGO
- [ ] Handle $? which should expand to the exit status of the most recently executed foreground pipeline.


### Hacer las built-in functions
- [ ] echo with option -n
- [ ] cd with only a relative or absolute path
- [ ] pwd with no options
- [ ] unset with no options
- [ ] export with no options
- [ ] env with no options or arguments
- [ ] exit with no options
Los demás comandos se pueden gestionar con el `execve`

### Gestionar los shortcuts (Ctrl-C, Ctrl-D...)
LINK: https://www.infor.uva.es/~fdiaz/so/doc/SO_PR04_20061115.pdf 
- [ ] ctrl-C displays a new prompt on a new line. `SIGINT`
- [ ] ctrl-D exits the shell. EOF
- [ ] ctrl-\ does nothing. `SIGQUIT`

#### Ejemplo para el Ctrl + C
```c
#include  <stdio.h>
#include  <unistd.h>
#include  <signal.h>
#include  <stdlib.h>

void  INThandler(int sig)
{
	char	c;

	signal(sig, SIG_IGN); // ignora las demás signals cuando procesa este
	printf("OUCH, did you hit Ctrl-C?\n"
			"Do you really want to quit? [y/n] ");
	c = getchar();
	if (c == 'y' || c == 'Y')
		exit(0);
	else
		signal(SIGINT, INThandler); // vuelve a su estado original
}

int  main(void)
{
	signal(SIGINT, INThandler);
	while (1)
		pause();
	return 0;
}
```

#### struct sigaction
```c
struct sigaction {
	void       (*sa_handler)(int); // similar al handler de la función signal
	sigset_t   sa_mask; // define el set de signals que se usa. sa_mask must be set by using one or more of the signal set manipulation functions: sigemptyset(), sigfillset(), sigaddset(), or sigdelset()
	int        sa_flags; // cambia el comportamiento de las señales. Ejemplo: SA_SIGINFO Tells the system to use the signal action specified by sa_sigaction instead of sa_handler.
	void       (*sa_sigaction)(int, siginfo_t *, void *); // 
};
```
Para más información porque es denso y pesado, y quiero llorar: https://www.ibm.com/docs/en/zos/2.5.0?topic=functions-sigaction-examine-change-signal-action

### Gestionar redirecciones
Todas las permitaciones tipo
```sh
< file cmd arg1 arg2
cmd < file arg1 arg2
cmd arg1 < file arg2
cmd arg1 arg2 < file
```
son legales.
- [ ] `<` should redirect input.
- [ ] `>` should redirect output.
- [ ] `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. 
    * However, it doesn’t have to update the history!
- [ ] `>>` should redirect output in append mode.
- [ ] Pipes

#### Respecto a redirigir el standard error
`>& file`, `&> file` ó `2> file`.
Una forma de redirigir el standard error al mismo sitio que el standard output es `> file 2> &1`

------------------------------------------------
## Extras
* && and || with parenthesis for priorities.
* Wildcards * should work for the current working directory.

## Further links
* https://www.ibm.com/docs/en/aix/7.1.0?topic=concepts-shells-terminology 
* https://brennan.io/2015/01/16/write-a-shell-in-c/