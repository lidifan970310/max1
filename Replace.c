#include <stdio.h>
#include <stdlib.h> 

 // declaration of all three functions
void FindRecord(char*, char*, char[]);
void Replace(char*, char*, char[]);
void SaveRecord(char*, char*, char[]);
int main(void){
 // creat three strings to store name,newname and record
  char name[1000], newname[1000], record[1000];
 // initialization of record
  for(int i = 0; i < 999; i++) record[i] = '\0';
 // get name by user input and store into string name
  printf("Please enter the name you want to replace: ");
  fgets(name,999,stdin);
 // get newname by user input and store into string newname
  printf("Please enter the replacement name: ");
  fgets(newname,999,stdin);
 // call findRecord to find the contact infomation and store into string record
  FindRecord("phonebook.csv",name,record);
 // call Replace to replace the name by newname
  Replace(name, newname, record);
 // call SaveRecord to updated record back into the CSV file
  SaveRecord("phonebook.csv",name,record);
  return 0;
}

void FindRecord(char *filename, char *name, char record[]){
 // read the file line by line
  char tmp[1000];
  int i, j, counter;
  FILE *file = fopen(filename, "rt");
  fgets(tmp,999,file);
  while(!feof(file)){
  	// find the one whose name is the same as input string name
  	i = 0, counter = 0;
  	while(tmp[i] != ','){
  		if(tmp[i] == name[i]) counter++; 
  		i++;
	  }
	// fill the record string when name matches, then break the loop
   if(counter == i){
   	j = 0;
   	while(tmp[j]){
   		record[j] = tmp[j];
   		j++;
	   }
	   record[j+1] = '\0';
   	break;
   }
   fgets(tmp,999,file);
 }
 // if no one's name matches, print a error message and exit
  if(counter != i){
  	printf("Invalid input, please try again!\n");
  	exit(1);
  }
  //close the file
  fclose(file); 
}

void Replace(char *name, char *newname, char record[]){
	// set a pointer named replaced to store replaced sentence
	char* replaced = (char*)calloc(1000, sizeof(char));
	// set another pointer to fill the replaced sentence in the string
	char* filler = replaced;
	// fill the newname first
	while(*newname){
		*filler = *newname;
		filler++;
		newname++;
	}
	// delete the carriage return
	filler--;
	// set a pointer to find the first comma of the original sentence
	// then copy everything after the comma(including the comma)
	char *comma = record;
	while(*comma != ',') comma++;
	while(*comma){
		*filler = *comma;
		filler++;
		comma++;
	}
	// wipe everything out in the original string
	char* cleaner = record;
	for(int i = 0; i < 999; i++){
		*cleaner = '\0';
		cleaner++;
	}
	// fill the replaced sentence in record
	char* filler2 = replaced;
    while(*filler2){
    	*record = *filler2;
    	filler2++;
    	record++;
	}
	// free
	free(replaced);
}
void SaveRecord(char *filename, char *name, char record[]){
 // set a string named temp to scan the file line by line
  char temp[1000];
 // set a pointer named replacedText to store processed csv file
  char* replacedText = (char*)calloc(1000, sizeof(char));
 // set a pointer to write the new csv file
  char* textWriter = replacedText;
 // set a pointer to compare names
  char* nameComparison = name;
 // read the original file and find the line need to be replaced
 // if need not, write the sentence in temp
  int i, counter, j;
  FILE *fileReader = fopen(filename, "rt");
  fgets(temp,999,fileReader);
  while(!feof(fileReader)){
  	i = 0, counter = 0;
        nameComparison = name;
    while(temp[i] != ','){
    	if(temp[i] == *nameComparison){
    		counter++;
    		nameComparison++;
		}
    	i++;
	}
	if(counter == i){
		while(*record){
			*textWriter = *record;
			textWriter++;
			record++;
		}
	}
	else{
		j = 0;
		while(temp[j]){
			*textWriter = temp[j];
			textWriter++;
			j++;
		}
	}
	fgets(temp,999,fileReader);
  }
  // overwrite the original file by the processed file
  FILE *fileWriter = fopen(filename, "wt");
  fprintf(fileWriter, "%s", replacedText);
  // close and free
  fclose(fileReader);
  fclose(fileWriter);
  free(replacedText);
}
