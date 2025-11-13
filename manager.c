#include <stdio.h>
#include <stdlib.h>

char* get_dynamic_string();
int add_contact(char *filename);
void view_contact(char *filename);

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
	printf("3.Exit\n");
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
	    case '3': return 0;
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
