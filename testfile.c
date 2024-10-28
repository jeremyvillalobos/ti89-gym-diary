// C Source File
// Created 8/13/2003; 12:04:39 PM
// Author: Jeremy F Villalobos
#define USE_TI89              // Compile for TI-89
#define USE_TI92PLUS          // Compile for TI-92 Plus
#define USE_V200              // Compile for V200

// #define OPTIMIZE_ROM_CALLS // Use ROM Call Optimization

#define MIN_AMS 100           // Compile for AMS 1.00 or higher

#define SAVE_SCREEN           // Save/Restore LCD Contents

#include <tigcclib.h>         // Include All Header Files

// Main Function

struct vari{
	int vari;
	int index;
};
struct ProgData{
	int CurrentIndex;
	
};
void read(FILE*, struct vari*);
void write(FILE*, struct vari*);
void checkAll(FILE*, struct vari*);
void edit(FILE*, struct vari*);
void delete(FILE*, struct vari*);
void _main(void)
{
	FILE *cfPtr;
	FILE Backup;
	struct vari vari1 = {0};
	struct vari vari2 = {0};
	char key = 0;
		clrscr();
	
	if( ( cfPtr = fopen( "apple2", "a+" ) ) == NULL)
			printf( "File could not be opened.\n");
	else 
	{
		Backup = *cfPtr;
		while( (key = ngetchx()) != 'p')
			{
			switch(key)
				{
				case '0':	
					write(cfPtr, &vari1);
					break;
				case '1':
					edit(cfPtr, &vari1);
					break;
				case '2':
					read(cfPtr,&vari2);
					break;
				case '3':
					checkAll(cfPtr,&vari2);
					break;
				case '4':
					delete(cfPtr,&vari1);
					break;
				default:
					printf("not valid entry");
					break;
				printf("\nvari 1 %d.  vari 2 %d", vari1.vari, vari2.vari);
				}
				rewind(cfPtr);
			}
		ngetchx();
	
	}
	fclose(cfPtr);
}

void delete(FILE *cfPtr, struct vari* vari1)
{
	FILE *FPtr;
	int index = 0;
	struct ProgData PData ={0};
	if( ( FPtr = fopen( "Prog", "a+") ) == NULL)
		printf( "File could not be opened.\n");
	else
	{
		printf("\ndelete index:  ");
		index = ngetchx();
		//fread(PData, sizeof(struct ProgData), 1, FPtr);
			while(!(fseek(cfPtr, (index - 47) * sizeof(struct vari), SEEK_SET)))
			{
				fseek(cfPtr, (index-47) *sizeof(struct vari), SEEK_SET);
				if(fread(vari1, sizeof(struct vari), 1 ,cfPtr))
					printf("\n%d  ", vari1->vari);
				if(!fseek(cfPtr, (index - 48) * sizeof(struct vari),SEEK_SET))
				{
					//vari1->vari=0;
					fwrite(vari1, sizeof(struct vari), 1 ,cfPtr);
					printf("success");
				}
				else
				{
					printf("a la puta...");
					rewind(cfPtr);//*cfPtr = Backup;
				}
				index++;
			}
			//set deleted record to 0
			vari1->vari = 0;
			rewind(cfPtr);
			fseek(cfPtr, (index - 49) * sizeof(struct vari), SEEK_SET);
			fwrite(vari1, sizeof(struct vari),1, cfPtr);
			//setdeleted record to 0
			fseek(FPtr, 0, SEEK_SET);
			fread(&PData, sizeof(struct ProgData), 1 , FPtr);
			PData.CurrentIndex--;
			printf("\nCI %d  ", PData.CurrentIndex);
			fseek(FPtr, 0, SEEK_SET);
			fwrite(&PData, sizeof(struct ProgData), 1 ,FPtr);
	}
	fclose(FPtr);
}
void checkAll(FILE *cfPtr, struct vari* vari1){
	int index = 0;
	
	printf( "\n");
	while(!(fseek(cfPtr,index++ *sizeof(struct vari), SEEK_SET)))
	{
		fread(vari1, sizeof( struct vari), 1 , cfPtr);
		printf("%d   ", vari1->vari);
		if(!(index % 4))
		{
			printf("\n");
		}
	}

}
void edit(FILE *cfPtr, struct vari* vari1){
	FILE Backup;
	char key= 0;
	int fail = 0;
	
		printf("\ngive index number:  ");
		key = ngetchx();
		printf("\ngive new value:  ");
		vari1->vari = ngetchx();
			
		fail = fseek(cfPtr, (key - 48) * sizeof(struct vari), SEEK_SET);
		if(fail) 
		{
			printf("\nseek fail!");
			*cfPtr = Backup;
		}else
			{
				fwrite(vari1, sizeof(struct vari), 1, cfPtr);
			}
}
void write(FILE *cfPtr, struct vari* vari1)
{
	struct ProgData PData ={0};
	FILE *FPtr;
	if( ( FPtr = fopen( "Prog", "a+") ) == NULL)
		printf( "File could not be opened.\n");		//try opening file...
	else
	{
		vari1->vari = ngetchx();									//get input
		//write new record
		rewind(FPtr);//fseek(FPtr, 0,SEEK_SET);
		fread(&PData,sizeof(struct ProgData),1, FPtr);
		printf("\nCIndex: %d   ", PData.CurrentIndex);
		//write new record
		//save information on progdata
		fseek(cfPtr, (PData.CurrentIndex)* sizeof(struct vari), SEEK_SET);
		fwrite(vari1, sizeof( struct vari), 1, cfPtr);
		PData.CurrentIndex++;
		fseek(FPtr,0,SEEK_SET);
		fwrite(&PData, sizeof(struct ProgData), 1, FPtr);
		printf("\nvari 1 %d.  CI %d   ", vari1->vari, PData.CurrentIndex);
		
	}
	fclose(FPtr);
}
void read(FILE *cfPtr, struct vari* vari2)
{
	FILE Backup;
	int fail;
	char key = 0;
	printf("\nindex to be read:  ");
	key = ngetchx();
	Backup = *cfPtr;
	fail = fseek(cfPtr, (key - 48) * sizeof(struct vari), SEEK_SET);
		if(fail) 
		{
			printf("\nseek fail!");
			*cfPtr = Backup;
		}else
			{
			fread(vari2, sizeof( struct vari), 1 , cfPtr);
			printf("\nvari2  %d    %d", vari2->vari, vari2->index);
			}
}
