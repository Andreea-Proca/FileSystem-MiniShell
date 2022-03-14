#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LINE_SIZE 300

struct Dir;
struct File;

typedef struct Dir{
	char *name;   // numele directorului
	struct Dir* parent;  // pointer catre parintele directorului(null pentru radacina)
	struct File* head_children_files;  // pointer catre primul element de tip File din interiorul directorului
	struct Dir* head_children_dirs; // pointer catre primul element de tip Dir din interiorul directorului
	struct Dir* next; // pointer catre urmatorul element din lista in care se afla directorul
}Dir; // structura de tip director
 
typedef struct File {
	char *name;  // numele fisierului
	struct Dir* parent; // pointer catre directorul pe
	struct File* next; // pointer catre urmatorul element din lista de fisiere
}File; // structura de tip fisier


void touch (Dir* parent, char* name) {
	int ok = 0;
	struct File *aux;
	aux = parent->head_children_files;
	if(parent->head_children_files != NULL){
		while( aux != NULL){
			if(strcmp(aux->name, name) == 0){
				printf("File already exists\n");
				ok = 1;
				break;
			}
			aux = aux->next;
		}
	}
	if( ok == 0 ){
		struct File *fisier =  malloc(sizeof(struct File));
		fisier->name = malloc((strlen(name)+1)*sizeof(char));
		strcpy(fisier->name, name);
		fisier->parent = parent;
		fisier->next = NULL;

		struct File *aux1;
		aux1 = parent->head_children_files;
		if(parent->head_children_files != NULL){
			while( aux1->next != NULL)
				aux1 = aux1->next;
			aux1->next = fisier;
		}else{
			parent->head_children_files = fisier;
		}
	}
}

void mkdir (Dir* parent, char* name) {

	struct File *aux;
	aux = parent->head_children_files;
	int ok = 0;
	if(parent->head_children_files != NULL){
		while( aux->next != NULL){
			if(strcmp(aux->name, name) == 0){
				printf("File already exists\n");
				ok = 1;
				break;
			}
			aux = aux->next;
		}
	}

	struct Dir *aux1;
	aux1 = parent->head_children_dirs;
	if(parent->head_children_dirs != NULL){
		while( aux1 != NULL){
			if(strcmp(aux1->name, name) == 0){
				printf("Directory already exists\n");
				ok = 1;
				break;
			}
			aux1 = aux1->next;
		}
	}

	if( ok == 0){
	struct Dir *directory =  malloc(sizeof(struct Dir));
	directory->name = malloc((strlen(name)+1)*sizeof(char));  
	strcpy(directory->name, name);
	directory->parent = parent;  
	directory->next = NULL; 
	directory->head_children_files = NULL;
	directory->head_children_dirs = NULL;

	struct Dir *aux2;
	aux2 = parent->head_children_dirs;

		if(parent->head_children_dirs != NULL){
			while( aux2->next != NULL)
				aux2 = aux2->next;
			aux2->next = directory;
		}else{
			parent->head_children_dirs = directory;
		}
	}
}

void ls (Dir* parent) {

	struct Dir *aux1;
	aux1 = parent->head_children_dirs;
	while( aux1 != NULL){
		printf( "%s\n", aux1->name);
		aux1 = aux1->next ;
	}
	struct File *aux2;
	aux2 = parent->head_children_files;
	while( aux2 != NULL){
		printf( "%s\n", aux2->name);
		aux2 = aux2->next ;
	}
}

void rm (Dir* parent, char* name) {
	int ok = 0;
	struct File *aux;
	aux = parent->head_children_files;
	if(parent->head_children_files != NULL){
		if(strcmp(aux->name, name) == 0){
			parent->head_children_files = aux->next;
			free(aux->name);
			free(aux);
			ok = 1;
		}else{
			while( aux->next != NULL){
				if(strcmp(aux->next->name, name) == 0){
					struct File *helper = aux->next;
					aux->next = aux->next->next;
					free(helper->name);
					free(helper);
					ok = 1;
					break;
				}
				aux = aux->next;
			}
		}
	}
	if(ok == 0)
		printf("Could not find the file\n");
}


void rmdir (Dir* parent, char* name) {
	int ok = 0;
	struct Dir *target;
	target = parent->head_children_dirs;
	struct Dir *prev = target;
	if(parent->head_children_dirs != NULL){
		while( target != NULL){
			if(strcmp(target->name, name) == 0){
				ok = 1;
				break;
			}
			prev = target;
			target = target->next;
		}
	}
	if(ok == 0){
		printf("Could not find the dir\n");
		return;
	}
	//del dir
	if(target != NULL){
		struct Dir *aux1;
			aux1 = target->head_children_dirs;
				while( aux1 != NULL){
						struct Dir *helper = aux1->next;
						rmdir(target, aux1->name);
						aux1 = helper;
						target->head_children_dirs = helper;
				}
		//del fisieer
		struct File *aux2;
		aux2 = target->head_children_files;
		while( aux2 != NULL){
			struct File *aux = aux2;
			aux2 = aux2->next;
			rm(target, aux->name);
		}
		if(parent->head_children_dirs == target){
			parent->head_children_dirs = target->next;
		}else{
			if(parent->head_children_dirs->next == NULL){
				parent->head_children_dirs = NULL;
			}else{
				prev->next = target->next;
			}
		}
		free(target->name);
		free(target);
	}
}



void cd(Dir** target, char *name) {
	if( strcmp(name, "..") == 0 ){
		if((*target)->parent != NULL){
			*target = (*target)->parent;
		}
	}else
	{
		int ok = 0;
		struct Dir *aux1;
		aux1 = (*target)->head_children_dirs;
		if((*target)->head_children_dirs != NULL){
			while( aux1 != NULL){
				if(strcmp(aux1->name, name) == 0){
					*target = aux1;
					ok = 1;
					break;
				}
				aux1 = aux1->next;
			}
		}
		if(ok == 0)
			printf("No directories found!\n");
	}
}

char *pwd (Dir* target) {
		
	char *s = malloc(100*sizeof(char));
	char *sir = malloc(100*sizeof(char));
	strcpy(sir,target->name);
	struct Dir *aux;
	aux = target;
	while( aux->parent != NULL){
		strcpy(s,aux->parent->name);
		strcat(s,"/");
		strcat(s, sir);
		strcpy(sir, s);
		aux = aux->parent;
	}
	strcpy(s,"/");
	strcat(s, sir);
	strcpy(sir, s);
	free(s);
	return sir;
}

void stop (Dir* target) {

	//free mem
	if(target != NULL){

		struct Dir *aux1;
			aux1 = target->head_children_dirs;
				while( aux1 != NULL){
						struct Dir *helper = aux1->next;
						rmdir(target, aux1->name);
					aux1 = helper;
				}

		//del fisieer
		struct File *aux2;
		aux2 = target->head_children_files;
		while( aux2 != NULL){
			struct File *aux = aux2;
			aux2 = aux2->next;
			rm(target, aux->name);
		}
		free(target->name);
		free(target);
	}
	exit(1);
}

void print_sp( int n) {
	for(int i=0; i<n; i++)
		printf("%s","    ");
}

void tree (Dir* target, int level) {
	
	if(target != NULL ){
		if(level != -1){
			print_sp(level);
			printf("%s\n", target->name);
		}
		struct Dir *aux1;
		aux1 = target->head_children_dirs;
		while( aux1 != NULL){
			tree(aux1, level+1);
			aux1 = aux1->next;
		}
		struct File *aux2;
		aux2 = target->head_children_files;
		while( aux2 != NULL){
			print_sp(level+1);
			printf("%s\n", aux2->name);
			aux2 = aux2->next;
		}
	}
}

void mv(Dir* parent, char *oldname, char *newname) {
	int oldfile = 0;
	int olddir = 0;
	int newfile = 0;
	int newdir = 0;

	//este file?
	struct File *aux;
	aux = parent->head_children_files;
	struct File *save;
	struct File *prev;
	struct File *prev_save;
	if(parent->head_children_files != NULL){
		while( aux != NULL){
			if(strcmp(aux->name, oldname) == 0){
				oldfile = 1;
				save = aux;
				prev_save = prev;
			}
			if(strcmp(aux->name, newname) == 0){
				printf("File/Director already exists\n");
				newfile = 1;
			}
			prev = aux;
			aux = aux->next;
		}
	}
	//este dir?
	struct Dir *aux1;
	aux1 = parent->head_children_dirs;
	struct Dir *save1 = aux1;
	struct Dir *prev1 = aux1;
	struct Dir *prev_save1 = aux1;
	if(parent->head_children_dirs != NULL){
		while( aux1 != NULL){
			if(strcmp(aux1->name, oldname) == 0){
				olddir = 1;
				save1 = aux1;
				prev_save1 = prev1;
			}
			if(strcmp(aux1->name, newname) == 0){
				printf("File/Director already exists\n");
				newdir = 1;
			}
			prev1 = aux1;
			aux1 = aux1->next;
		}
	}

	if( olddir == 0 && oldfile == 0)
		printf("File/Director not found\n");

	if( olddir == 1 && newdir == 0 && newfile == 0){
			strcpy(save1->name, newname);
			if(parent->head_children_dirs == save1){
				if(save1->next != NULL){
				parent->head_children_dirs = save1->next;
				prev1->next = save1;
				save1->next = NULL;
				}
			}else{
				prev_save1->next = save1->next;
				prev1->next = save1;
				save1->next = NULL;
			}

		}

		if( oldfile == 1 && newfile == 0 && newdir == 0){
			strcpy(save->name, newname);
			if(parent->head_children_files == save){
				if(save->next != NULL){
				parent->head_children_files = save->next;
				prev->next = save;
				save->next = NULL;
				}
			}else{
				prev_save->next = save->next;
				prev->next = save;
				save->next = NULL;
			}
		}
}

int main () {

	struct Dir *home = calloc(1,sizeof(struct Dir));
	home->name = malloc((sizeof("home")+1)*sizeof(char));  
	strcpy(home->name, "home");
	home->parent = NULL;  
	home->head_children_files = NULL;
	home->head_children_dirs = NULL;
	home->next = NULL; 

	struct Dir *curr = home;

	char *buffer;
	size_t bufsize = MAX_INPUT_LINE_SIZE;
	size_t characters;
	buffer = (char *)malloc(bufsize * sizeof(char));
	do
	{	
		if( buffer == NULL)
		{
			perror("Unable to allocate buffer");
			exit(1);
		}

		characters = getline(&buffer,&bufsize,stdin);

		char *s1, *s2, *s3;
		if( strstr(buffer, " ")){
			s1 = strtok (buffer," ");
			if( strstr(buffer + strlen(s1) + 1, " ")){
				s2 = strtok (buffer + strlen(s1) + 1," ");
				s3 = strtok (buffer + strlen(s1) + 1 + + strlen(s2) + 1,"\n");
				}else{
					s2 = strtok (buffer + strlen(s1) + 1,"\n");
				}
		}else{
			s1 = strtok (buffer,"\n");
		}

		if(strcmp(s1, "touch") == 0){
			touch( curr, s2);
		}
		if(strcmp(s1, "mkdir") == 0){
			mkdir( curr, s2);
		}
		if(strcmp(s1, "ls") == 0){
			ls(curr);
		}
		if(strcmp(s1, "rm") == 0){
			rm(curr,s2);
		}
		if(strcmp(s1, "rmdir") == 0){
			rmdir(curr,s2);
		}
		if(strcmp(s1, "cd") == 0){
			cd(&curr, s2);
		}
		if(strcmp(s1, "tree") == 0){
			tree(curr, -1);
		}
		if(strcmp(s1, "pwd") == 0){
			char *sir = pwd(curr);
			printf("%s\n", sir);
			free(sir);
		}
		if(strcmp(s1, "mv") == 0){
			mv(curr, s2, s3);
		}

	} while (strcmp(buffer, "stop") != 0);

	if(strcmp(buffer, "stop") == 0){
		free(buffer);
		stop(home);
	}

	return 0;
}
