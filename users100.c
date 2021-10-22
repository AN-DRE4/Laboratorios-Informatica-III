#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

void removeChar(char *str, char garbage) {
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != garbage) dst++;
    }
    *dst = '\0';
}

// public_repos ;   id   ; followers ; follower_list ;    type    ; following_list ; public_gists ;       created_at    ; following ; login
// 0            ;23128004;      0    ;      []       ;Organization;     []         ;       0      ;  2016-10-28 20:08:16;     0     ; comandosfor

int checkusers(catg values[]){

	int r, i;

	for(i=0;;i++){
		scanf("%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", values[i].public_repos, 
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

	// public_repos
	int check_pr = 1;
	if (isdigit(values[i].public_repos) && (values[i].public_repos >= 0)) check_pr; else (check_pr = 0);

	// id
	int check_id = 1;
	if (isdigit(values[i].id) && (values[i].id >= 0)) check_id; else (check_id = 0);

	// followers
	int check_fer = 1;
	if (isdigit(values[i].followers) && (values[i].followers >= 0)) check_fer; else (check_fer = 0);

	// follower_list
	int check_ferl = 1;
	if ( (strlen(values[i].follower_list) ) == (strlen(values[i].followers) + 2 ) ){
		if (values[1].follower_list == "[" && (values[strlen(values[i].follower_list)].follower_list == "]") ) check_ferl;
		else (check_ferl = 0);
	} else check_ferl = 0;

	// type
	int check_t = 1;
	if ((values[i].type == "Organization") || (values[i].type == "User") || (values[i].type == "Bot") ) check_t; else (check_t = 0);

	// following_list
	int check_fingl = 1;
	if ( (strlen(values[i].following_list) ) == (strlen(values[i].following) + 2 ) ){
		if (values[1].following_list == "[" && (values[strlen(values[i].following_list)].following_list == "]") ) check_fingl;
		else (check_fingl = 0);
	} else (check_fingl = 0);

	// public_gists
	int check_pg = 1;
	if (isdigit(values[i].public_gists) && (values[i].public_gists >= 0)) check_pg; else (check_pg = 0);

	// created_at
	int check_ca = 1;

	// char data
	char * year = strcat(strcat(values[0].created_at, values[1].created_at), strcat(values[2].created_at ,values[3].created_at) );
	char * month = strcat(values[5].created_at, values[6].created_at);
	char * day = strcat(values[8].created_at, values[9].created_at);
	char * hour = strcat(values[11].created_at, values[12].created_at);
	char * minutes = strcat(values[14].created_at, values[15].created_at);
	char * seconds = strcat(values[17].created_at, values[18].created_at);

	// char data to int data
	int yeari = atoi(year);
	int monthi = atoi(month);
	int dayi = atoi(day);
	int houri = atoi(hour);
	int minutesi = atoi(minutes);
	int secondsi = atoi(seconds);

	int passmin = 1; // data above min data
	int miny = 2005; // min year
	int minm = 04; // min month
	int mind = 07; // min day

	if (yeari < miny)
		passmin = 0;
	else if (yeari == miny){
		if (monthi < minm)
			passmin = 0;
		else if (monthi == minm){
			if (dayi > mind)
				passmin;
			else
				passmin = 0;
		} else
			passmin;
	} else
		passmin;

	int passmax = 1; // data below max data
	int maxy = 2021; // max year
	int maxm = 10; // max month
	int maxd = 16; // max day

	if (yeari > maxy)
		passmax = 0;
	else if (yeari == maxy){
		if (monthi > maxm)
			passmax = 0;
		else if (monthi == maxm){
			if (dayi > maxd)
				passmax;
			else
				passmax = 0;
		} else
			passmax;
	} else
		passmax;

	switch(strlen(values[i].created_at)){

		// values[i].created_at is char when i = 4;7;10;13;16; normal case
		case 19:

			// check min and max data
			if (passmax == passmin == 1) check_ca;
			else check_ca = 0;

			// checks in particular cases that "atoi" transform string of not digits into a perfect data
			if (isdigit(year)) check_ca; else check_ca = 0;
			if (isdigit(month)) check_ca; else check_ca = 0;
			if (isdigit(day)) check_ca; else check_ca = 0;
			if (isdigit(hour)) check_ca; else check_ca = 0;
			if (isdigit(minutes)) check_ca; else check_ca = 0;
			if (isdigit(seconds)) check_ca; else check_ca = 0;

			// check chars data
			if ( ( (values[4].created_at == "-") || (values[4].created_at == "/") ) && ( (values[7].created_at == "-") || (values[7].created_at == "/") ) ) check_ca;
			else check_ca = 1;
			
			// check char hours to minutes
			if ( (values[13].created_at == ":") || (values[13].created_at == "h") ) check_ca;
			else check_ca = 1;

			// check if char when (i = 10) is a space
			if (values[10].created_at == " ") check_ca;
			else check_ca = 1;

			// check char minutes to seconds
			if ( (values[16].created_at == ":") || (values[16].created_at == "m") ) check_ca;
			else check_ca = 1;

			// correct print for data
			if (values[4].created_at == "/") values[4].created_at = "-";
			if (values[7].created_at == "/") values[7].created_at = "-";

			// correct print for time
			if (values[13].created_at == "h") values[13].created_at = ":";
			if (values[16].created_at == "m") values[16].created_at = ":";

			break;
		
		// values[i].created_at is char when i = 4;7;10;13;16;20; case of seconds have the letter s
		case 20:

			// check min and max data
			if (passmax == passmin == 1) check_ca;
			else check_ca = 0;

			// checks in particular cases that "atoi" transform string of not digits into a perfect data
			if (isdigit(year)) check_ca; else check_ca = 0;
			if (isdigit(month)) check_ca; else check_ca = 0;
			if (isdigit(day)) check_ca; else check_ca = 0;
			if (isdigit(hour)) check_ca; else check_ca = 0;
			if (isdigit(minutes)) check_ca; else check_ca = 0;
			if (isdigit(seconds)) check_ca; else check_ca = 0;

			// part from case 19 (init)

			// check chars data
			if ( ( (values[4].created_at == "-") || (values[4].created_at == "/") ) && ( (values[7].created_at == "-") || (values[7].created_at == "/") ) ) check_ca;
			else check_ca = 1;
			
			// check char hours to minutes
			if ( (values[13].created_at == ":") || (values[13].created_at == "h") ) check_ca;
			else check_ca = 1;

			// check if char when (i = 10) is a space
			if (values[10].created_at == " ") check_ca;
			else check_ca = 1;

			// check char minutes to seconds
			if ( (values[16].created_at == ":") || (values[16].created_at == "m") ) check_ca;
			else check_ca = 1;

			// correct print for data
			if (values[4].created_at == "/") values[4].created_at = "-";
			if (values[7].created_at == "/") values[7].created_at = "-";

			// correct print for time
			if (values[13].created_at == "h") values[13].created_at = ":";
			if (values[16].created_at == "m") values[16].created_at = ":";

			// part from case 19 (end)

			// if (i = 20) && values[20].created_at exists and is "s" then it deletes s from the array
			if (values[20].created_at == "s") removeChar(values[i].created_at, 20);
			else check_ca = 1;

			break;
	}

	// following
	int check_fing = 1;
	if (isdigit(values[i].following) && (values[i].following >= 0)) check_fing; else (check_fing = 0);

	// login
	int check_l = 1;
	if (values[i].login != NULL) check_l; else (check_l = 0);

	// checks all members in the struct (arrays in the struct), if there "check's" are equal to 0 (zero)
	if (check_pr == check_id == check_fer == check_ferl == check_t == check_fingl == check_pg == check_ca == check_fing == check_l == 1) return r;
	else {
		r = 0; 
		return r;
	}
}

// public_repos ;   id   ; followers ; follower_list ;    type    ; following_list ; public_gists ;       created_at    ; following ; login
// 0            ;23128004;      0    ;      []       ;Organization;     []         ;       0      ; 2016-10-28 20:08:16 ;     0     ; comandosfor
//																									2016/10/28 20h08m16s


int main(){

	// file pointer
	FILE * fp;

	// open file
	fp = fopen("users100.csv", "r");

	char singleLine[1024]; // buffer of arrays of lines
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
		char * tmp = strdup(singleLine);
        char * token;

        while((token = strsep(&tmp, ";"))) {
			while(token){
				if(collum_count == 0) strcpy(values[i].public_repos, token);
				if(collum_count == 1) strcpy(values[i].id, token);
				if(collum_count == 2) strcpy(values[i].followers, token);
				if(collum_count == 3) strcpy(values[i].follower_list, token);
				if(collum_count == 4) strcpy(values[i].type, token);
				if(collum_count == 5) strcpy(values[i].following_list, token);
				if(collum_count == 6) strcpy(values[i].public_gists, token);
				if(collum_count == 7) strcpy(values[i].created_at, token);
				if(collum_count == 8) strcpy(values[i].following, token);
				if(collum_count == 9) strcpy(values[i].login, token);
			}
		collum_count++;
		}
		i++;

		}

	fclose(fp);

	// print into the new file (temp)

	FILE * nfp;

	nfp = fopen("newusers100.csv", "w");1

	fprintf(nfp,"public_repos;id;followers;follower_list;type;following_list;public_gists;created_at;following;login\n");
	if(checkusers(values) == 1){		
		for(int i=0;;i++){
			fprintf(nfp, "%s;%s;%s;%s;%s;%s;%s;%s;%s;%s\n", values[i].public_repos, 
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

	fclose(nfp);

	return 0;
}
