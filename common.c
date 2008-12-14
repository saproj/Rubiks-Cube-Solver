#include <stdio.h>

#include "common.h"
#include "cube.h"

/*
 * See more comments in common.h
 */

/*
 * See common.h for more info
 */
int whichpos(const char *cubie)
{
    /* Takes a 6 character cubie string and returns which cubie it is,
     * one through twenty.  cubie is NOT null terminated (this func only
     * touches the first 6 chars)
     * */
    int ns[4] = {-1,-1,-1,-1};
    int i, j=0;
    for (i=0; i<6; i++) {
        if (cubie[i] == 'n')
            ns[j++] = i;
    }
    /* Just a big if statement will suffice: */
    if (ns[0]==0 && ns[1]==1 && ns[2]==5 && ns[3]==-1)
        return 0;
    else if (ns[0]==0 && ns[1]==1 && ns[2]==2 && ns[3]==5)
        return 1;
    else if (ns[0]==0 && ns[1]==1 && ns[2]==2 && ns[3]==-1)
        return 2;
    else if (ns[0]==0 && ns[1]==1 && ns[2]==4 && ns[3]==5)
        return 3;
    else if (ns[0]==0 && ns[1]==1 && ns[2]==2 && ns[3]==4)
        return 4;
    else if (ns[0]==0 && ns[1]==4 && ns[2]==5 && ns[3]==-1)
        return 5;
    else if (ns[0]==0 && ns[1]==2 && ns[2]==4 && ns[3]==5)
        return 6;
    else if (ns[0]==0 && ns[1]==2 && ns[2]==4 && ns[3]==-1)
        return 7;
    else if (ns[0]==0 && ns[1]==1 && ns[2]==3 && ns[3]==5)
        return 8;
    else if (ns[0]==0 && ns[1]==1 && ns[2]==2 && ns[3]==3)
        return 9;
    else if (ns[0]==0 && ns[1]==3 && ns[2]==4 && ns[3]==5)
        return 10;
    else if (ns[0]==0 && ns[1]==2 && ns[2]==3 && ns[3]==4)
        return 11;
    else if (ns[0]==1 && ns[1]==3 && ns[2]==5 && ns[3]==-1)
        return 12;
    else if (ns[0]==1 && ns[1]==2 && ns[2]==3 && ns[3]==5)
        return 13;
    else if (ns[0]==1 && ns[1]==2 && ns[2]==3 && ns[3]==-1)
        return 14;
    else if (ns[0]==1 && ns[1]==3 && ns[2]==4 && ns[3]==5)
        return 15;
    else if (ns[0]==1 && ns[1]==2 && ns[2]==3 && ns[3]==4)
        return 16;
    else if (ns[0]==3 && ns[1]==4 && ns[2]==5 && ns[3]==-1)
        return 17;
    else if (ns[0]==2 && ns[1]==3 && ns[2]==4 && ns[3]==5)
        return 18;
    else if (ns[0]==2 && ns[1]==3 && ns[2]==4 && ns[3]==-1)
        return 19;
    
    return -1;
}

/* This is also expensive, should not be called in main loop */
int whichrot(const char *cubie)
{
    char cols[2]; /* used for edge cubies */
    char tmp;
    int i, j;
    int pos = whichpos(cubie);
    if (pos == 0 || pos == 2 || pos == 5 || pos == 7 || 
            pos == 12 || pos == 14 || pos == 17 || pos == 19) {
        /* Corner cubie */
        if (cubie[FRONT] == 'w' || cubie[FRONT] == 'y' ||
                cubie[BACK] == 'w' || cubie[BACK] == 'y') {
            return 0;
        } else if (cubie[LEFT] == 'w' || cubie[LEFT] == 'y' ||
                cubie[RIGHT] == 'w' || cubie[RIGHT] == 'y') {
            return 1;
        } else if (cubie[TOP] == 'w' || cubie[TOP] == 'y' ||
                cubie[DOWN] == 'w' || cubie[DOWN] == 'y') {
            return 2;
        } else {
            fprintf(stderr, "Caution: whichrot error __LINE__\n");
            return -1;
        }
            
    } else {
        /* Edge cubie */
        j=0;
        for (i=0; i<6; ++i){
            if (cubie[i] != 'n') {
                cols[j++] = cubie[i];
            }
        }
        /*
         * Put white or yellow in the first col.
         * If there's no white or yellow, put blue or green first
         */
        if (cols[1] == 'w' || cols[1] == 'y') {
            tmp = cols[1];
            cols[1] = cols[0];
            cols[0] = tmp;
        } else if ((cols[0] != 'w' && cols[0] != 'y') && 
                (cols[1] == 'b' || cols[1] == 'g')) {
            tmp = cols[1];
            cols[1] = cols[0];
            cols[0] = tmp;
        } else {
            fprintf(stderr, "Something has gone horribly wrong in whichrot __LINE__\n");
            return -1;
        }

        /* 
         * white/yellow case 
         * if white/yellow is on the front or back, or if the other color is
         * on the top or bottom, we know it's oriented 0
         * otherwise, 1
         *
         * For the last four edge cubies (the four that don't have white or
         * yellow on them) we check to see if green/blue is on the front or
         * back, or if the other color is on the top or bottom.  Then it's
         * 0.
         *
         * Therefore, thanks to the re-ordering done above, it's the same
         * check:
         */
        if (cubie[TOP] == cols[1] || cubie[DOWN] == cols[1] ||
                cubie[FRONT] == cols[0] || cubie[BACK] == cols[0]) {
            return 0;
        } else {
            return 1;
        }
    }
}
