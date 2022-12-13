#include <stdio.h>
#include <stdlib.h>


//Avriel Lyon
//10/26/2021
//P4 Merge Sort Scholar Program

//function declaration 
int * createLibrary(int * bookArray, int numBooks);
void mergeSort(int * bookArray, int low, int high);
void mergeFunction(int * bookArray, int low, int mid, int high);
int calculateBooks(int * bookArray, int numBooks, long long maxPages);

int main() {
  int numCases;
  int numBooks;
  int i;

  //set to long long as it could pass the 
  //int capacity in a max case situation
  long long maxPages;

  //get the number of cases to handle
  scanf("%d", & numCases);

  for (i = 0; i < numCases; i++) {
    scanf("%d", & numBooks);
    scanf("%lld", & maxPages);

    //create the bookArray and calloc space for it
    int * bookArray = (int * ) calloc(numBooks, sizeof(int));

    //set the values within the array
    bookArray = createLibrary(bookArray, numBooks);

    //sort the array
    mergeSort(bookArray, 0, numBooks - 1);

    //print out the number of books you can read
    //without going over the max pages you can read
    printf("%d\n", calculateBooks(bookArray, numBooks, maxPages));

    //free bookArray to avoid memory errors
    free(bookArray);
  }

  return 0;
}

int * createLibrary(int * bookArray, int numBooks) {
  int i;
  int numPages;

  //loop through the number of books and read in the number of pages per book
  //set these values to the bookArray
  for (i = 0; i < numBooks; i++) {
    scanf("%d", & numPages);
    bookArray[i] = numPages;
  }

  //return the bookArray
  return bookArray;
}

int calculateBooks(int * bookArray, int numBooks, long long maxPages) {

  //number of books read
  int booksRead = 0;
  //total pagesRead, data type of long long since it'll exceed the int capacity
  long long pagesRead = 0;

  int i;

  //for the length of the list, loop through it
  for (i = 0; i < numBooks; i++) {
    //if pagesRead already surpasses maxPages
    if (maxPages < pagesRead) {
      break;
    }

    //check if we can still add to pagesRead without going over the max
    if (maxPages < pagesRead + bookArray[i]) {
      break;
    }

    //add to pagesRead the amount of pages at that spot in the array
    pagesRead += bookArray[i];

    //incremement booksRead as we were able to add that book
    booksRead++;
  }

  //return the amount of booksRead
  return booksRead;
}

void mergeSort(int * bookArray, int low, int high) {

  if (low < high) {
    //set the mid to be the average between low and high
    int mid = (low + high) / 2;

    //call merge sort for the left of the array
    mergeSort(bookArray, low, mid);

    //call merge sort for the right of the array
    mergeSort(bookArray, mid + 1, high);

    //merge the arrays
    mergeFunction(bookArray, low, mid + 1, high);

  }

}

void mergeFunction(int * bookArray, int low, int mid, int high) {
  //find the length of the array
  int arrayLength = (high - low) + 1;

  //three values to increment
  int index1 = low; //starts at the begining of the array
  int index2 = mid; //starts at the middle of the array
  int mainIndex = 0; //starts at index 0

  int i;

  //creating a temporary array to store the sorted values
  int * tempArray = (int * ) calloc(arrayLength, sizeof(int));

  while ((index1 < mid) || (index2 <= high)) {

    if (index2 > high || (index1 < mid && bookArray[index1] < bookArray[index2])) {
      //placing the values in their sorted position
      tempArray[mainIndex] = bookArray[index1];

      //increment from the start of the array to the mid point
      index1++;
      mainIndex++;
    } else {
      //placing the values in their sorted position
      tempArray[mainIndex] = bookArray[index2];

      //increment from the middle of the array to the end of the array
      index2++;
      mainIndex++;
    }
  }

  //put the values from the tempArray back into the bookArray
  for (i = low; i <= high; i++) {
    bookArray[i] = tempArray[i - low];
  }

  //free the temporary array to avoid memory errors
  free(tempArray);
}
