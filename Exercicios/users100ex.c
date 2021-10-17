#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct categories{
	char * public_repos;
	char * id;
	char * followers;
	char * follower_list;
	char * type;
	char * following_list;
	char * public_gists;
	char * created_at;
	char * following;
	char * login;
} catg;


void printNew(catg * values){

	for(int i=0;;i++){
		printf("%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", values[i].public_repos, 
												  values[i].id, 
												  values[i].followers, 
												  values[i].follower_list, 
												  values[i].type, 
												  values[i].following_list, 
												  values[i].public_gists, 
												  values[i].created_at, 
												  values[i].following, 
												  values[i].login);
	}
}

int main(){

	// file pointer
	FILE * fp;

	// open file
	fp = fopen("users100", "r");

	char singleLine[1024]; // buff of char arrays of lines
	int row_count = 0;
	int collum_count = 0;

	if(!fp){
		printf("Error\n");
		return 0;
	}

	catg * values; // array of structs

	int i = 0;
	while(fgets(singleLine, 1024, fp)){
		collum_count = 0;
		row_count++;
		if (row_count == 1) continue; // row of categories
		char *collum = strtok(singleLine, ";");
		while(collum){
			if(collum_count == 0) strcpy(values[i].public_repos, collum);
			if(collum_count == 1) strcpy(values[i].id, collum);
			if(collum_count == 2) strcpy(values[i].followers, collum);
			if(collum_count == 3) strcpy(values[i].follower_list, collum);
			if(collum_count == 4) strcpy(values[i].type, collum);
			if(collum_count == 5) strcpy(values[i].following_list, collum);
			if(collum_count == 6) strcpy(values[i].public_gists, collum);
			if(collum_count == 7) strcpy(values[i].created_at, collum);
			if(collum_count == 8) strcpy(values[i].following, collum);
			if(collum_count == 9) strcpy(values[i].login, collum);
				
		collum = strtok(NULL, ";"); // update collum value
		collum_count++;
		}
		i++;
	}

	fclose(fp);

	// print into the new file (temp)

	printNew(values);


	return 0;
}