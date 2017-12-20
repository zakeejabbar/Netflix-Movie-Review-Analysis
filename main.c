/*main.c*/

//
// Netflix movie analysis: top-10 by rating and # of reviews.
//
// <<Zakee Jabbar (zjabba2)>>
// Windows with Visual Studio
// U. of Illinois, Chicago
// CS251, Spring 2017
// Project #01
//

// ignore stdlib warnings if working in Visual Studio:
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// MOVIE structure: storing the necessary parts for the project
typedef struct MOVIE
{
  int movieID;
  char movieName[255];
  int numReviews;
  double ratingSum;
  double ratingAvg;

} MOVIE;

//
// getFileName: inputs a filename from the keyboard, make sure the file can be
// opened, and returns the filename if so.  If the file cannot be opened, an
// error message is output and the program is exited.
//
char *getFileName()
{
  char filename[512];
  int  fnsize = sizeof(filename) / sizeof(filename[0]);

  // input filename from the keyboard:
  fgets(filename, fnsize, stdin);
  filename[strcspn(filename, "\r\n")] = '\0';  // strip EOL char(s):

  // make sure filename exists and can be opened:
  FILE *infile = fopen(filename, "r");
  if (infile == NULL)
  {
    printf("**Error: unable to open '%s'\n\n", filename);
    exit(-1);
  }

  fclose(infile);

  // duplicate and return filename:
  char *s = (char *)malloc((strlen(filename) + 1) * sizeof(char));
  strcpy(s, filename);

  return s;
}



int main()
{
    int i = 0;
    int j = 0;
    char str[255];
    char str2[255];
    char *token;
    char *token2;
    char *token3;

    // get filenames from the user/stdin:
    char *MoviesFileName = getFileName();
    char *ReviewsFileName = getFileName();

    // opens the movies and reviews file:
    FILE *movieFile = fopen(MoviesFileName, "r");
    FILE *reviewFile = fopen(ReviewsFileName, "r");


    // reads the first line in each file and stores the integer N and R:
    int movEntries = atoi(fgets(str,255,movieFile));
    int revEntries = atoi(fgets(str2,255,reviewFile));
    printf("Movies: %d\n", movEntries);
    printf("Reviews %d\n", revEntries);


    // sets the size and allocates memory for the struct based on number of movies
    MOVIE *movies = (MOVIE *)malloc(sizeof(MOVIE) * movEntries);

// reads the movies file and stores info in the array of structs
for(i = 0; i < movEntries;i++)
  {
    fgets(str,255,movieFile);

    token = strtok(str, ",");
    int m = atoi(token);
    movies[m-1].movieID = atoi(token);

    token2 = strtok(NULL, ",");
    strcpy(movies[m-1].movieName,token2);

    token3 = strtok(NULL, ",");

  }

// read the reviews file and stores info in the array of structs
for(i = 0; i < revEntries;i++)
  {
    fgets(str,255,reviewFile);

    token = strtok(str, ",");
    token2 = strtok(NULL, ",");
    token3 = strtok(NULL, ",");

    movies[atoi(token)-1].ratingSum += atoi(token3);
    movies[atoi(token)-1].numReviews++;

  }

// sets the value of the rating to 0 if 0 reviews, or calculates the rating
for(i = 0; i < movEntries; i++)
{

    if(movies[i].numReviews == 0)
    {

        movies[i].ratingAvg = 0;
    }
    else
    {
        movies[i].ratingAvg = movies[i].ratingSum/movies[i].numReviews;
    }
}

// sorts the array of structs by rating
for(i = 0; i < movEntries - 1; i++)
{
    int biggest = i;

    for (j = i+1; j < movEntries; j++)
    {
        if(movies[j].ratingAvg > movies[biggest].ratingAvg)
        {

            biggest = j;
        }
        else if(movies[j].ratingAvg == movies[biggest].ratingAvg)
        {
            if(strcmp(movies[j].movieName, movies[biggest].movieName) < 0)
            {
                biggest = j;
            }
        }
    }

    MOVIE T = movies[i];
    movies[i] = movies[biggest];
    movies[biggest] = T;
}


printf("**Top-10 by Rating**\n");


// prints the list of top 10 by rating
for(i = 0; i < 10; i++)
{
    printf("%d: %f,'%s'\n",i+1, movies[i].ratingAvg, movies[i].movieName);
}

// sorts the array of structs by number of reviews
for(i = 0; i < movEntries - 1; i++)
{
    int biggest = i;
    for (j = i+1; j < movEntries; j++)
    {
        if(movies[j].numReviews > movies[biggest].numReviews)
        {

            biggest = j;
        }
        else if(movies[j].numReviews == movies[biggest].numReviews)
        {
            if(strcmp(movies[j].movieName, movies[biggest].movieName) < 0)
            {
                biggest = j;
            }
        }
    }

    MOVIE T = movies[i];
    movies[i] = movies[biggest];
    movies[biggest] = T;
}

printf("**Top-10 by Num Reviews**\n");

// prints the list of top 10 by number of reviews
for(i = 0; i < 10; i++)
{
    printf("%d: %d,'%s'\n",i+1, movies[i].numReviews, movies[i].movieName);
}



  return 0;
}
