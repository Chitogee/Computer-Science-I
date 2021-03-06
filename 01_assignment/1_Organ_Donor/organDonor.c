/*
 * Name: James Choi
 * Date: August 28, 2013
 * Course: Computer-Science I (10:30AM-11:20AM)
 * Submission: Assignment #1 (Organ Donor)
 * Description: This program reads in a file containing information about patients
 *              on a waiting list for organ transplant, as well as a list of
 *              donated organs. It matches donated organ with compatible
 *              users on the waiting list; writing the result to the output
 *
 **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 20
#define BLOODTYPESIZE 4


////////////////////////////////////////////////////////////////////
//////////////////////// Data Structures ///////////////////////////
///////////////////////////////////////////////////////////////////
// Date
typedef struct {
	int month;
	int day;
	int year;
} dateT;

// Time
typedef struct {
	int hour;
	int minute;
} timeT;

// Patient on waiting list
typedef struct {
	char * name;
	char * organname;
	char bloodtype[BLOODTYPESIZE];
	dateT dateAdded ;
	timeT timeAdded;
	int received;
} organT;

// Donated Organ
typedef struct {
    char * organ ;
    char * bloodType ;
}Donor ;

////////////////////////////////////////////////////////////////////
///////////////////// Function prototypes  ////////////////////////
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// Function: allocate
// Argument: numLines (Number to allocate)
// Return:   A dynamically allocated array of people on the waiting list
// Description: Allocate patient list
///////////////////////////////////////////////////////////////////
organT ** allocate(int numLines);
///////////////////////////////////////////////////////////////////
// Function: printPatient
// Argument: patient (single patient *)
// Return:   void
// Description: Debug purpose
///////////////////////////////////////////////////////////////////
void printPatient(organT ** patient);
///////////////////////////////////////////////////////////////////
// Function: readPatients
// Argument: infile (A file pointer instance)
// Return:   organT ** containing a populated patient list
// Description: Reads in infile, allocates and returns a populate list
///////////////////////////////////////////////////////////////////
organT ** readPatients();
///////////////////////////////////////////////////////////////////
// Function:  readDonorList
// Argument:  infile
// Return:    Donor ** which is an array of organ/bloodtype data struct
// Description: Reads infile, allocates and populates Donor **
///////////////////////////////////////////////////////////////////
Donor ** readDonorList();
///////////////////////////////////////////////////////////////////
// Function: findPair,
// Argument: outfile, donorList, patient
// Return:   void
// Description:  Given the file to output to, a list of donors and patients
//               For every organ donated, will match with patient on waiting
//               list.
///////////////////////////////////////////////////////////////////
void findPair( Donor ** donorList , organT ** patient);
///////////////////////////////////////////////////////////////////
// Function:  orgPatientByOrgan
// Argument:  patient
// Return:    void
// Description:  Given an array of patients, for each patient and organ they
//               requested, it will find another patient in the list who
//               requested the same organ, and will swap places if individual
//               further down in the list precedes the current
///////////////////////////////////////////////////////////////////
void orgPatientByOrgan(organT ** patient);

int main(){
	organT ** patient = readPatients();
    Donor ** donorList = readDonorList();

    orgPatientByOrgan(patient);
    printPatient(patient);
    findPair(donorList,patient);
    free(donorList);
    free(patient);
}

////////////////////////////////////////////////////////////////////
///////////////////// Function Definitions ////////////////////////
///////////////////////////////////////////////////////////////////
void orgPatientByOrgan(organT ** patient){
    int i = 0 ;
    int listLength = 0 ;
    int compareLimit = 100 ;
    int listSize = 0 ;
    int matchesFound = 0 ;
    // First count the number of patients requesting organ
    while ( patient[i] != NULL ){
        listSize++ ;
        i++ ;
    }
    // Go through the list of patients and find the req. organ, then look ahead
    // and find somebody else requesting the same thing.
    // Sort by dateAdded, if
    // the dates are the same then sort by time.
    int j = 0 ;
    for ( i = 0 ; i < listSize ; i++ ){
        for (j = i ; j < listSize ; j++ ){
            // If two people want the same organ
            if(strncmp(patient[i]->organname,patient[j]->organname,compareLimit)==0){
                // compare year
                if ( patient[i]->dateAdded.year > patient[j]->dateAdded.year ){
                    organT * fPatient = patient[j] ;
                    patient[j] = patient[i] ;
                    patient[i] = fPatient ;
                }
                // compare month
                else if ( patient[i]->dateAdded.month > patient[j]->dateAdded.month &&  patient[i]->dateAdded.year == patient[j]->dateAdded.year ){
                    organT * fPatient = patient[j] ;
                    patient[j] = patient[i] ;
                    patient[i] = fPatient ;
                }
                // compare date
                else if ( patient[i]->dateAdded.day > patient[j]->dateAdded.day && patient[i]->dateAdded.month == patient[j]->dateAdded.month &&
                          patient[i]->dateAdded.year == patient[j]->dateAdded.year ){
                    organT * fPatient = patient[j] ;
                    patient[j] = patient[i] ;
                    patient[i] = fPatient ;
                }
                // compare time if dates are the same
                else if ( patient[i]->dateAdded.day == patient[j]->dateAdded.day && patient[i]->dateAdded.month == patient[j]->dateAdded.month &&
                          patient[i]->dateAdded.year == patient[j]->dateAdded.year ){
                    if ( patient[i]->timeAdded.hour > patient[j]->timeAdded.hour){
                        organT * fPatient = patient[j] ;
                        patient[j] = patient[i] ;
                        patient[i] = fPatient ;
                    }
                    else if ( patient[i]->timeAdded.hour ==  patient[j]->timeAdded.hour && patient[i]->timeAdded.minute > patient[j]->timeAdded.minute){
                        organT * fPatient = patient[j] ;
                        patient[j] = patient[i] ;
                        patient[i] = fPatient ;
                    }
                    else{
                        continue ;
                    }
                }
                else{
                    continue ;
                }
            }
        }

    }
}
void findPair(Donor ** donorList , organT ** patient){
    int i = 0 ;
    int j = 0 ;
    int compareLimit = 100 ;
    int result = 0 ;
    while ( donorList[i] != NULL ){
        while ( patient[j] != NULL ){
            if ( strncmp( donorList[i]->organ,patient[j]->organname,compareLimit)==0 && strncmp( donorList[i]->bloodType ,patient[j]->bloodtype,compareLimit)==0 && patient[j]->received != 1 ){
                patient[j]->received = 1 ;
                printf("%s %s\n",patient[j]->name,donorList[i]->organ);
                j = 0 ;
                break ;
            }
            j++ ;
        }
        if ( patient[j] == NULL ){
            //fprintf(outfile,"No match found\n");
            printf("%s","No Match Found\n");
            j = 0 ;
        }
        i++ ;
    }
}

organT ** allocate(int numLines){
	organT ** patient = (organT ** )malloc(sizeof(organT *)*(numLines+1));
	int i = 0 ;
	for ( i = 0 ; i < numLines ; i++ ){
		patient[i]  = (organT * )malloc(sizeof(organT ));
		patient[i]->name= (char *)malloc(sizeof(char)*SIZE);
		patient[i]->organname = (char *)malloc(sizeof(char)*SIZE);
		patient[i]->dateAdded.month = 0;
		patient[i]->dateAdded.day= 0;
		patient[i]->dateAdded.year= 0;
		patient[i]->timeAdded.hour = 0;
		patient[i]->timeAdded.minute = 0;
		patient[i]->received = 0 ;
	}
	patient[i] = NULL ;
	return patient ;
}
void printPatient(organT ** patient){
    int i = 0 ;
	while ( patient[i] != NULL ){
		//printf("\nName: %s\n",patient[i]->name);
		//printf("Organ: %s\n",patient[i]->organname);
		//printf("BloodType: %s\n",patient[i]->bloodtype);
		//printf("Added: %d/%d/%d\n",patient[i]->dateAdded.month,patient[i]->dateAdded.day,patient[i]->dateAdded.year);
        i++ ;
	}
}
organT ** readPatients(){
	int numLines ;
	// Get the first line
	//fscanf(infile,"%d",&numLines);
    scanf("%d",&numLines);
	// Allocate a pointer of pointers and all the points contained within lol
	organT ** patient = allocate(numLines);

	int i = 0 ;
	// scan an print
	while ( i < numLines ){
        // Make a throwaway variable to hold the characters "/" and ":"
        char ch ;
		// Scan that shit
        dateT dateAdded  ;
        timeT timeAdded  ;
		scanf("%s %s %s %d%c%d%c%d %d%c%d",(patient[i]->name),(patient[i]->organname),(patient[i]->bloodtype),
                                                   //  Month            /        Day            /      year
                                                   (&dateAdded.month),(&ch),(&dateAdded.day),(&ch),(&dateAdded.year),
                                                   //    Hour           :      Minute
                                                   (&timeAdded.hour),(&ch),(&timeAdded.minute));
        patient[i]->dateAdded = dateAdded ;
        patient[i]->timeAdded= timeAdded;
		i++ ;
	}

	return patient ;
}
Donor ** readDonorList(){
    int numLines =0;
    int i = 0 ;
    scanf("%d",&numLines);
    Donor ** donorList = (Donor **)malloc(sizeof(Donor*)*(numLines+1));
    while (i < numLines){
        donorList[i] = (Donor *)malloc(sizeof(Donor));
        donorList[i]->organ = (char *)malloc(sizeof(char)*(SIZE+1));
        donorList[i]->bloodType = (char *)malloc(sizeof(char)*(SIZE+1));
        scanf("%s %s",donorList[i]->organ,donorList[i]->bloodType);
        //printf("\nOrgan: %s \nBloodType: %s\n",donorList[i]->organ,donorList[i]->bloodType);
        i++ ;
    }
    donorList[numLines] = NULL;
    return donorList;
}

