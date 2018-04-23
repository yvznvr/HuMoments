# HuMoments
7 Invariant Moments for Object Recognizing

If you want more information about Hu Moments, you can use following link<br/>
http://www.wseas.us/e-library/conferences/2013/CambridgeUK/AISE/AISE-15.pdf


 Example<br/>
 arr is an one dimensional array of object and arr must be binary image(0 and 1(not 255))<br/>
 width and height is integer<br/>
 
 ```c
 HuMoments obj1(arr,width,height);
 obj1.calcOrgins();
 obj1.calcInvariantMoments();
 float *moments = obj1.getInvariantMoments();
 std::cout << moments[0] << endl << moments[1] << endl << moments[2] << endl << moments[3] << endl << moments[4] << endl << moments[5] << endl << moments[6] << endl;
 ```
