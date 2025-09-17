#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>

int data = 15;
int bss = 0;
char *str = "Bonjourmonde";

void function_memory(void){};

int main(void) {
	int stack = 17;
	char *heap = malloc(64);
	void *mem_map = mmap(NULL,1024,PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS,-1,0);

	printf("Données globales initialisées: %p\n",&data);
	printf("Données globales initialisées à 0: %p\n",&bss);
	printf("Chaine de caractères: %p\n",str);
	printf("Données allouées dynamiquement: %p\n",heap);
	printf("Données à portées limitées: %p\n",&stack);
	printf("Mémoire code: %p\n",&function_memory);
	printf("Librairie partagée: %p\n",(void *)printf);
	printf("Mémoire allouée par mmap: %p\n",mem_map);
	printf("\n");

	int pid, status;
	pid = fork();
	if (pid == 0){ //child process
		pid_t ppid = getppid();
		char *pid_str[20];
		snprintf(pid_str, sizeof(pid_str), "%d", ppid);
		char *arg[] = {"pmap", "-X",pid_str,NULL};
		execvp("pmap",arg);
	}
	if (pid != 0){ //parent process
		wait(&status);
	}

	return 0;
}