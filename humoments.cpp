#include "humoments.h"

HuMoments::HuMoments(int *array, int width, int height)
{
    // array must be binary(0 or 1(not 255))
    this->width = width; this->height = height;
    object = new int[width*height];
    for(int i=0;i<width*height;i++)
        object[i] = array[i];
}

HuMoments::~HuMoments()
{
    delete[] object;
}

float HuMoments::calcMoment(int p, int q)
{
    // calc (p+q)th moment of object
    float sum=0;
    for(int x=0; x<width; x++)
    {
        for(int y=0; y<height; y++)
        {
            sum += object[x+y*width]*pow(x,p)*pow(y,q);
        }
    }
    return sum;
}

void HuMoments::calcOrgins()
{
    // calc orgins
    orginOfX = calcMoment(1,0)/calcMoment(0,0);
    orginOfY = calcMoment(0,1)/calcMoment(0,0);
}

float HuMoments::calcCentralMoment(int p, int q)
{
    // calculate central moment
    float sum=0;
    for(int x=0; x<width; x++)
    {
        for(int y=0; y<height; y++)
        {
            sum += object[x+y*width]*pow((x-orginOfX),p)*pow((y-orginOfY),q);
        }
    }
    return sum;
}

float HuMoments::calcNormalizedMoment(int p, int q)
{
    // calculate normalized moments
    float temp = ((p+q)/2)+1;
    return calcCentralMoment(p,q)/pow(calcMoment(0,0),temp);
}

void HuMoments::calcInvariantMoments()
{
    // calculate 7 invariant moments
    invariantMoments[0] = calcNormalizedMoment(2,0) + calcNormalizedMoment(0,2);
    invariantMoments[1] = pow((calcNormalizedMoment(2,0) - calcNormalizedMoment(0,2)),2) + 4 * (pow(calcNormalizedMoment(1,1),2));
    invariantMoments[2] = pow((calcNormalizedMoment(3,0) - 3 * calcNormalizedMoment(1,2)),2) +
            pow((3*calcNormalizedMoment(2,1) - calcNormalizedMoment(0,3)),2);
    invariantMoments[3] = pow((calcNormalizedMoment(3,0) + calcNormalizedMoment(1,2)),2) +
            pow((calcNormalizedMoment(2,1) + calcNormalizedMoment(0,3)),2);
    invariantMoments[4] = (calcNormalizedMoment(3,0) - 3 * calcNormalizedMoment(1,2)) *
            (calcNormalizedMoment(3,0)+calcNormalizedMoment(1,2)) *
            (pow(calcNormalizedMoment(3,0) + calcNormalizedMoment(1,2),2) - 3 * pow(calcNormalizedMoment(2,1)+calcNormalizedMoment(0,3),2)) +
            (3 * calcNormalizedMoment(2,1) - calcNormalizedMoment(0,3)) * (calcNormalizedMoment(2,1)+calcNormalizedMoment(0,3)) *
            (pow(3 * (calcNormalizedMoment(3,0) + calcNormalizedMoment(1,2)),2) - pow(calcNormalizedMoment(2,1) + calcNormalizedMoment(0,3),2));
    invariantMoments[5] = (calcNormalizedMoment(2,0)-calcNormalizedMoment(0,2)) * (pow(calcNormalizedMoment(3,0) + calcNormalizedMoment(1,2),2) -
            pow(calcNormalizedMoment(2,1) + calcNormalizedMoment(0,3),2)) + (4 * calcNormalizedMoment(1,1) * (calcNormalizedMoment(3,0) + calcNormalizedMoment(1,2)) *
                                                                             calcNormalizedMoment(2,1) + calcNormalizedMoment(0,3));
    invariantMoments[6] = (3 * calcNormalizedMoment(2,1) - calcNormalizedMoment(0,3)) * (calcNormalizedMoment(3,0) + calcNormalizedMoment(1,2)) * (pow(calcNormalizedMoment(3,0)+calcNormalizedMoment(1,2),2) -
            3 * pow(calcNormalizedMoment(2,1) + calcNormalizedMoment(0,3),2)) - (calcNormalizedMoment(3,0) - 3 * calcNormalizedMoment(1,2)) * (calcNormalizedMoment(2,1) + calcNormalizedMoment(0,3)) *
            (3 * pow(calcNormalizedMoment(3,0) + calcNormalizedMoment(1,2),2) - pow(calcNormalizedMoment(2,1) + calcNormalizedMoment(0,3),2));
}

float *HuMoments::getInvariantMoments()
{
    // return 7 invariant moments with array
    return invariantMoments;
}
