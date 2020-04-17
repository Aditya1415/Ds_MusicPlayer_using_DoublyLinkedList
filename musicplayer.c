//my ds project

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>  //we have the system function in the windows.h header file which allows us to open the file from the command prompt
#include<stdbool.h>



//music structure
//For every song there will be The song, The Artist, The Movie,and two pointers pointing towards previous and backward 

//Double Linked List is being used


typedef struct music
{
	char Song[30];
	char Artist[30];
	char Movie[30];
	char Language[30];
	struct music *Previous; //for the previous song
	struct music *Next;     //for the Next Song
	
}music;


//using doubly linked list for this

music *front=NULL;
music *rear=NULL;



bool present=false; //the boolean variable is used to check whether the specified Album or song or Artist is present or not




void display_the_song(music *s)  //to display the attributes of the song
{
	printf("The song currently palying is:\n");
	printf("Song: %s \n",s->Song);
	printf("Language: %s :\n",s->Language);
	printf("Movie: %s \n",s->Movie);
	printf("Artist: %s \n",s->Artist);
	
}



void play() //the function play is used to play the desired song by using the system function and we can move forward and backward using the doubly linked list by the characters 0 and 1
{
	music *p=front;
	do
	{
		
		char *temp;
		temp=(char *)malloc(30*sizeof(char));
		
		strcpy(temp,p->Song);
		
		strcat(temp,".mp3");
		system(temp);
		system("pause");
		int ch;
		printf("\nEnter 1 for next 0 for previous\n");
		scanf("%d",&ch);
		
		if(ch==1 && p->Next && p)
		{
			p=p->Next;
		}
		else if(ch==0 && p->Previous && p)
		{
			p=p->Previous;
		}
		else
		{
			p=p->Next;
		}
		
		
	}while(p);
	if(!p)
	{
		printf("The Music list Has been Ended");
	}
	
		
		

}



//for conversion  of ponter array into char array or i.e string //copying the content of array to string
void convert(char string[],char *array)
{
	int x;
	for(x=0;x<30;x++)
	{
		string[x]=array[x];
	}
}


//to display the  whether the song  is present or not
void browse()
{
	if(!present)
	{
		printf("\nThe song/artist/album you have searched for doesnot exists:_\nplease select another song : ");
		present=false;
	}
	
}

//using the doubly linked list
	
void push_song(char *s,char *m,char *ar,char *lang)
{
	music *temp=(music *)malloc(sizeof(music));
	temp->Previous=NULL;
	temp->Next=NULL;
	
	if(front==NULL)
	{
		convert(temp->Song,s);
		convert(temp->Artist,ar);
		convert(temp->Language,lang);
		convert(temp->Movie,m);
		front=temp;
		
	}
	else
	{
		rear=front;
		
		//to add the song at the last i.e inserting at the last
		
		while(rear->Next)
		{
			rear=rear->Next;
		}
		
		convert(temp->Song,s);
		convert(temp->Artist,ar);
		convert(temp->Language,lang);
		convert(temp->Movie,m);
		
		rear->Next=temp;
		temp->Previous=rear;
		rear=temp;
		printf("Hello");
		display_the_song(temp);
		
	}
	printf("\n------------------");
	printf("\nReading the Song\n");
	printf("\n------------------\n");
}

//pop or move function should be written



//now we will check on the functions whether the user selected album or song or artist

//if the user want to search for album

void albumfile(char *user_input,int lang)
{
		FILE *fptr;
		
		char readline[100];
		
		char delimiter[2]="-";
		
		char *str,*song,*artist,*album,*language;
		
		str=(char *)malloc(30 * sizeof(char));
		
		song=(char *)malloc(30 * sizeof(char));
		
		album=(char *)malloc(30 * sizeof(char));
		
		language=(char *)malloc(30 * sizeof(char));
		
	
		
		if(lang==1) //for telugu
		{
			fptr=fopen("F:\\FDS project\\Telugu\\Telugu.txt","r");
			
		}
		else if(lang==2) //for Hindi
		{
			fptr=fopen("F:\\FDS project\\Hindi\\hindi.txt","r");
		
		}
		else
		{
			fptr=fopen("F:\\FDS project\\English\\English.txt","r");
			
		}
		
		//checking whether the file is present or not
		
		if(fptr==NULL)
		{
			printf("\nFile not found");
			exit(1);
		}
		while((fgets(readline,150,fptr))!=NULL)
		{
			//str tok function is used to split the string based on the delimiter
			
			str=strtok(readline,delimiter);
			
			//we have written the format as Language-Song-Artist-Album
			
			language=str;
			
			str=strtok(NULL,delimiter);
			
			song=str;
			
			str=strtok(NULL,delimiter);
			
			artist=str;
			
			str=strtok(NULL,delimiter);
			
			album=str;
			
			
			if(strcmp(user_input,album) ==0)
			{
				push_song(song,album,artist,language);
				present=true;
				
			}
		}
		browse();
}


//if the user wants to search for artist
void artistfile(char *user_input,int lang)
{
		FILE *fptr;
		
		char readline[100];
		char delimiter[2]="-";
		char *str,*song,*artist,*album,*language;

		str=(char *)malloc(30 * sizeof(char));
		song=(char *)malloc(30 * sizeof(char));
		album=(char *)malloc(30 * sizeof(char));
		language=(char *)malloc(30 * sizeof(char));
		
	
		
		if(lang==1) //for telugu
		{
			fptr=fopen("F:\\FDS project\\Telugu\\telugu.txt","r");
		
		}
		else if(lang==2) //for Hindi
		{
			fptr=fopen("F:\\FDS project\\Hindi\\hindi.txt","r");
			
		}
		else //for english
		{
			fptr=fopen("F:\\FDS project\\English\\English.txt","r");
			
		}
		
		//checking whether the file is present or not
		
		if(fptr==NULL)
		{
			printf("\nFile not found");
			exit(1);
		}
		while((fgets(readline,150,fptr))!=NULL)
		{
			//str tok function is used to split the string based on the delimiter
			
			str=strtok(readline,delimiter);
			//we have written the format as Language-Song-Artist-Album-someextrastring/character
			language=str;
			
			str=strtok(NULL,delimiter);
			song=str;
			
			str=strtok(NULL,delimiter);
			artist=str;
			
			str=strtok(NULL,delimiter);
			album=str;
			
			if(strcmp(user_input,artist) ==0)
			{
				push_song(song,album,artist,language);
				present=true;
				
			}
		}
		browse();
}

//if the user wants to search for a song

void songfile(char *user_input,int lang)
{
		FILE *fptr;
		printf("songfile");
		
		char readline[100];
		char delimiter[2]="-";
		char *str,*song,*artist,*album,*language;
		
		str=(char *)malloc(30 * sizeof(char));
		song=(char *)malloc(30 * sizeof(char));
		album=(char *)malloc(30 * sizeof(char));
		language=(char *)malloc(30 * sizeof(char));
		
	
		
		if(lang==1) //for telugu
		{
			fptr=fopen("F:\\FDS project\\Telugu\\Telugu.txt","r");
		
		}
		else if(lang==2) //for Hindi
		{
			fptr=fopen("F:\\FDS project\\Hindi\\hindi.txt","r");
			
		}
		else
		{
			fptr=fopen("F:\\FDS project\\English\\English.txt","r");
			
		}
		if(fptr==NULL)
		{
			printf("\nFile not found");
			exit(1);
		}
		while((fgets(readline,150,fptr))!=NULL)
		{
			
			str=strtok(readline,delimiter);
			language=str;
			
			str=strtok(NULL,delimiter);
			song=str;
			
			str=strtok(NULL,delimiter);
			artist=str;
			
			str=strtok(NULL,delimiter);
			album=str;
			
			if(strcmp(user_input,song) ==0)
			{
				push_song(song,album,artist,language);
				present=true;
				break;
				
			}
		}
		browse();
}


int main()
{
	system("color A0");
	printf("       *********************************************\n");
	printf("       *                                           *\n");
	printf("       *                                           *\n");
	printf("       *                                           *\n");
	printf("       *                                           *\n");
	printf("       *            MUSIC PLAYER                   *\n");
	printf("       *                                           *\n");
	printf("       *                                           *\n");
	printf("       *                                           *\n");
	printf("       *                                           *\n");
	printf("       *********************************************\n");
	
	
	int language;
	int input;
	
	char *user_input;
	
	user_input=(char *)malloc(30 * sizeof(char));
	
	
	
	do
	{
		printf("Enter the Language\n");
		
		printf("\n         1---> Telugu         2--->Hindi         3--->English           \n");
		
		scanf("%d",&language);
		
		printf("\nEnter the choice\n");
		
		printf("   1-->Song    2-->Artist    3--> Album    4-->Play The songs you selected      5-->EXIT");
		
		printf("\nEnter your number here----->");
		scanf("%d",&input);
		present=false;
		switch(input)
		{
			case 1:printf("\nEnter the song You wanted in the respective Language you selected\n");
					scanf(" %[^\n]s",user_input);
					songfile(user_input,language);
					break;
			
			case 2:printf("\nEnter the Artist You wanted in the respective Language you selected\n");
					scanf(" %[^\n]s",user_input);
					artistfile(user_input,language);
					break;
			
			case 3:printf("\nEnter the Album You wanted in the respective Language you selected\n");
					scanf(" %[^\n]s",user_input);
					albumfile(user_input,language);
					break;
			
			case 4:play();
					break;
			
			case 5: exit(0);
					break;
		}
	}while(1);
	
	return 0;
}
					
		
		
		
		
	
	
	
		
		
		
	
	
	
	
	
	
	
	



	
	