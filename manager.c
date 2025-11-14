#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* get_dynamic_string();
int add_contact(char *filename);
void view_contact(char *filename);
void search_contact(char *filename);
void delete_contact(char *filename);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
	printf("Usage: ./manager [csv contact file]\n");
	return 1;
    }
    
    char ch;

    while(1)
    {
	printf("\n---------------");
	printf("\nContact Manager\n");
	printf("---------------\n");
	printf("1.Add Contact\n");
	printf("2.View Contacts\n");
	printf("3.Search Contact\n");
	printf("4.Delete Contact\n");
	printf("5.Exit\n");
	printf("Enter choice:");
	scanf(" %c",&ch);

	switch(ch)
	{
	    case '1': {
			  int r = add_contact(argv[1]);
		          if(r==2) return 2;
			  break;
		      }
	    case '2': view_contact(argv[1]);break;
	    case '3': search_contact(argv[1]);break;
	    case '4': delete_contact(argv[1]);break;
	    case '5': return 0;
	    default : printf("\n**Wrong Choice**\n\n");
	}

    }
    return 0;

}

int add_contact(char *filename)
{
    FILE *contact_file= fopen(filename,"a");
    if (contact_file == NULL)
    {
	printf("\n**Error opening file**\n\n");
	return 2;
    }
    printf("\nEnter Name:");
    char *name = get_dynamic_string();
    
    printf("Enter Number:");
    char *number = get_dynamic_string();

    fputs(name,contact_file);
    fputc(',',contact_file);
    fputs(number,contact_file);
    fputc('\n',contact_file);
    
    fclose(contact_file);
    free(name);
    free(number);
    return 0;
}


char* get_dynamic_string()
{
    int capacity = 16;
    int lenght = 0;
    char *buffer=malloc(capacity);

    char ch;
    while((ch = getchar()) == '\n');

    buffer[lenght++] = ch;

    while((ch = getchar()) != '\n')
    {
	buffer[lenght++] = ch;

	if(lenght >= capacity)
	{
	    capacity *= 2;
	    buffer = realloc(buffer,capacity);
	}
    }
    buffer[lenght]='\0';
    return buffer;
}


void view_contact(char* filename)
{
    FILE *contact_file = fopen(filename,"r");
    printf("\n-------------\n");
    printf("Contact List");
    printf("\n-------------\n");
    char ch;
    while((ch = fgetc(contact_file)) != EOF)
    {
	printf("%c",ch);
    }
    printf("-------------\n");
    fclose(contact_file);

}

void search_contact(char *filename)
{
    FILE *contact_file = fopen(filename,"r");

    printf("\nEnter Name:");
    char *input = get_dynamic_string();

    char ch;
    int capacity_name = 16;
    int capacity_num = 16;
    char *name = malloc(capacity_name);
    char *number = malloc(capacity_num);
    int reading_name = 1;
    int i = 0;
    int j = 0;
	
    while((ch = fgetc(contact_file)) != EOF)
    {
	if (ch == '\n')
	{
	    number[j] = '\0';
	    if (strcmp(name,input) == 0)
	    {
		printf("Number: %s\n",number);
		free(name);
		free(number);
		free(input);
		fclose(contact_file);
		return;
	    }
	    i = 0;
	    j = 0;
	    reading_name = 1;
	    continue;
	}

	if (ch == ',')
	{
	    name[i] = '\0';
	    reading_name = 0;
	    continue;
	}
	if(reading_name)
	{
	    name[i++] = ch;
	}
	else
	{
	    number[j++] = ch;
	}
	if(i >= capacity_name)
	{
	    capacity_name *= 2;
	    name = realloc(name,capacity_name);
	}
	if(j >= capacity_num)
	{
	    capacity_num *=2;
	    number = realloc(number,capacity_num);
	}
    }
    printf("Not found.\n");
    free(name);
    free(number);
    free(input);
    fclose(contact_file);
    return;
}


void delete_contact(char *filename)
{
    FILE *contact_file = fopen(filename,"r");
    FILE *new_file = fopen("temp.txt","w");

    printf("\nEnter Name:");
    char *input = get_dynamic_string();

    char ch;
    int capacity_name = 16;
    int capacity_num = 16;
    char *name = malloc(capacity_name);
    char *number = malloc(capacity_num);
    int reading_name = 1;
    int i = 0;
    int j = 0;
    int found = 0;
	
    while((ch = fgetc(contact_file)) != EOF)
    {
	if (ch == '\n')
	{
	    number[j] = '\0';
	    if (strcmp(name,input) == 0)
	    {
		printf("\nContact Deleted \"%s\"",name);
		found = 1;
	    }
	    else
	    {
		fputs(name,new_file);
		fputc(',',new_file);
		fputs(number,new_file);
		fputc('\n',new_file);
	    }
	    i = 0;
	    j = 0;
	    reading_name = 1;
	    continue;
	}

	if (ch == ',')
	{
	    name[i] = '\0';
	    reading_name = 0;
	    continue;
	}
	if(reading_name)
	{
	    name[i++] = ch;
	}
	else
	{
	    number[j++] = ch;
	}
	if(i >= capacity_name)
	{
	    capacity_name *= 2;
	    name = realloc(name,capacity_name);
	}
	if(j >= capacity_num)
	{
	    capacity_num *=2;
	    number = realloc(number,capacity_num);
	}
    }
    if(!found)
    {
    	printf("Not found.\n");
    }
    free(name);
    free(number);
    free(input);
    fclose(contact_file);
    fclose(new_file);
    remove(filename);
    rename("temp.txt",filename);
    return;
}

