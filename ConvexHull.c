// Created by Ethan Foss (B00764435) on 2018-03-09.
// This program finds the convex hull of a given set of points

#include <stdio.h>
void convexHull(int x[], int y[], int size);
int main(){

    int z;
    int size;
    //Scans the input file for the number of points
    scanf("%d", &size);

    //Creates two arrays of the specified size to store the x
    // and y values respectively
    int xVals[size];
    int yVals[size];

    //Stores all of the x and y values from the input file into
    //the arrays
    for(z=0; z<size; z=z+1){
        //If both scanned values return successfully (Both return 1)
        if(scanf("%d %d", &xVals[z], &yVals[z]) == 2){
        //If at least one of the values is not scanned successfully
        } else {
            //Print out an error statement, exit the program
            printf("Error: Non-numerical input detected.\n");
            return 0;
        }
    }

    //If there are at least 3 points
    if(size>=3){
        //Calls the convex hull calculation method with both arrays
        //as well as the size as parameters
        convexHull(xVals, yVals, size);
        return 1;
    //If there are fewer than 3 points
    } else {
        //Print out an error statement and exit the program
        printf("Error: A polygon requires at least 3 points.\n");
        return 0;
    }

}

void convexHull(int x[], int y[], int size){

    int passedT = 0;
    int convexPointCount = 1;
    int numChecked = 0;
    int kInc = 0;
    int jInc = 0;
    int jX = x[jInc];
    int jY = y[jInc];
    int kX = x[kInc];
    int kY = y[kInc];

    int i = 0;
    int z;
    int tX;
    int tY;
    int C[100][2];

    //Fills the final array with 0s for all x values and y values
    for(z=0; z<100; z=z+1){
        C[z][0] = 0;
        C[z][1] = 0;
    }

    //Moves through the entire list of points, finding the point
    //with the maximum y value
    for(z=0; z<size; z=z+1){
        if(z==0){
            tX = x[0];
            tY = y[0];
        } else if(y[z]>tY){
            tY = y[z];
            tX = x[z];
        }
    }
    //Set the maximum y value as the first value in the set
    //of convex hull points
    C[0][0] = tX;
    C[0][1] = tY;

    //While the k point does not equal the maximum y
    //point and the loop has not passed the maximum y
    //point more times than there are points. (This protects the
    //program against the edge case where all points are
    //involved in the convex hull)
    while((kX != tX || kY != tY) || passedT != size){
        //If the k point is equal to the maximum
        //y point
        if(kX == tX && kY == tY){
            //If the k point has NOT reached the end of 
            //the set of points, move it to the next point
            if(kInc<size-1) {
                kInc = kInc + 1;
                kX = x[kInc];
                kY = y[kInc];
            //If the k point HAS reached the end of 
            //the set of points, move it to the first point
            } else if(kInc == size-1){
                kInc = 0;
                kX = x[kInc];
                kY = y[kInc];
            }
            //Increment passedT to mark that the maximum y 
            //point has been passed
            passedT ++;
        }
        //While the referenced j point has not reached 
        //the end of the list of points
        while(jInc<size) {
            //If the j point is not equal to the current point at C[i]
            //and the j point is not equal to the k point 
            if ((jX != C[i][0] || jY != C[i][1]) && (jX != kX || jY != kY)) {
                //If the k point set is counterclockwise from the j point set
                if ((((kX - C[i][0]) * (jY - C[i][1])) - ((jX - C[i][0]) * (kY - C[i][1]))) < 0) {
                    //Mark that another point has passed the test
                    numChecked = numChecked+1;
                //If the above computation results in 0, the k and j points must lie on the same line
                } else if((((kX - C[i][0]) * (jY - C[i][1])) - ((jX - C[i][0]) * (kY - C[i][1]))) == 0){
                	//If the j point is farther away than the k point
                	if(((jX*jX)+(jY*jY)) > ((kX*kX)+(kY*kY))){
                		//Mark that another point has passed the test
                		numChecked = numChecked+1;
                	}
                }
                //If all of the necessary points have been checked
                //and the k point is confirmed to be counterclockwise
                //from all other points
                if(numChecked == size-2){
                    //Mark that there has been another convex hull point found
                    convexPointCount = convexPointCount+1;
                    //Increment i
                    i = i + 1;
                    //Add the k point to the array of convex hull points
                    C[i][0] = kX;
                    C[i][1] = kY;
                    //If the k point has NOT reached the end of 
                    //the set of points, move it to the next point
                    if(kInc<size-1) {
                        kInc = kInc + 1;
                        kX = x[kInc];
                        kY = y[kInc];
                    //If the k point HAS reached the end of 
                    //the set of points, move it to the first point
                    } else if(kInc == size-1){
                        kInc = 0;
                        kX = x[kInc];
                        kY = y[kInc];
                    }
                }
            }
            //Move to the next j point 
            jInc = jInc + 1;
            jX = x[jInc];
            jY = y[jInc];
        }
        //Reset numchecked to 0
        numChecked = 0;
        //Reset to the first j point
        jInc = 0;
        jX = x[jInc];
        jY = y[jInc];
        //If the k point has NOT reached the end of 
        //the set of points, move it to the next point
        if(kInc<size-1) {
            kInc = kInc + 1;
            kX = x[kInc];
            kY = y[kInc];
        //If the k point HAS reached the end of 
        //the set of points, move it to the first point
        } else if(kInc == size-1){
            kInc = 0;
            kX = x[kInc];
            kY = y[kInc];
        }
    }

    //Print out the number of points in the convex hull
    printf("%d\n", convexPointCount);

    //As the loop iterates, print out the x and y 
    //values of each convex hull point            
    for(z=0; z<convexPointCount; z=z+1){
        printf("%d %d\n", C[z][0], C[z][1]);
    }
}
