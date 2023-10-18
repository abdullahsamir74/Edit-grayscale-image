/*
FCAI – OOP Programming – 2023 - Assignment 1
Course Instructors:Dr. Mohammad El-Ramly
Program Name:Gray Scale Image Processor
Last Modification Date: 10/6/2023
Author1 and ID and Group: Abdullah Samir Mohamed 20220200  abdullahsamir2274@gmail.com
Author2 and ID and Group: Mohamed Ahmed Mohamed  20210596  mohamed.5580.558@gmail.com
Author3 and ID and Group: ibrahim rabea ibrahim  20221001  ibra7imsalman30@gmail.com
*/
#include<bits/stdc++.h>
#include "bmplib.cpp"
using namespace std;
unsigned char image[SIZE][SIZE];                       // To store the image that I will work on.
unsigned char standard[SIZE][SIZE];                    // we made it to avoide a wrong value when we do any operation to image like flip and others
int flag=-1;                                           // I made it to stop program if user enter invlid input especially in Shuffle FN()
unsigned char skewedH1[SIZE][SIZE];
unsigned char skewedH2[SIZE][SIZE];



void loadImage()                                       // loading the image that I will make changes to it.
{
    cout<<"Please enter file name of the image to process:";
    char imageName[50];cin>>imageName;
    strcat(imageName, ".bmp");
    readGSBMP(imageName,image);         // store original image in the place that I will edit it there
    for(int k=0;k<SIZE;k++)
    {
        for(int l=0;l<SIZE;l++)
        {
            standard[k][l]=image[k][l];         // Taking the values of image before editing it to avoide wrong value while swapping in operations
        }
    }
}


void Black_White()           // Filter (1)
{
    for (int i=0;i<SIZE;i++)
    {
        for (int j=0;j<SIZE;j++)
        {
            image[i][j]>127?image[i][j]=255:image[i][j]=0;
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void Invert_Image()            // Filter (2)
{
    for(int i=0;i<SIZE;i++)
    {
        for (int j=0;j<SIZE;j++)
        {
            image[i][j]=255-image[i][j];
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void Merge_Image()             // Filter (3)
{
    unsigned char image2[SIZE][SIZE];
    unsigned char image3[SIZE][SIZE];
    cout<<"Please enter name of image file to merge with: ";
    char secondImg[50];cin>>secondImg;
    strcat(secondImg, ".bmp");
    readGSBMP(secondImg,image2);
    for (int i=0;i<SIZE;i++)
    {
        for (int j=0;j<SIZE;j++)
        {
           image3[i][j]=(image[i][j]+image2[i][j])/2;
           image[i][j]=image3[i][j];         // to store it in image not image 3 and avoid change it in save FN() when writing it(writeGSBMP)
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void Flip_Image()                 // Filter (4)
{
    cout<<"Flip 1-> horizontally or 2-> vertically ? ";
    int choise;cin>>choise;
    if(choise==2)
    {
      for(int i=0;i<SIZE;i++)
      {
        for(int j=0;j<SIZE;j++)
        {
            image[i][j]=standard[abs(i-255)][j];     // like swapping with its opposite one
        }
      }
    }
    else if(choise==1)
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                image[i][j]=standard[i][abs(j-255)];    // same thing like above but the difference is only the side
            }
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void Rotate_Image()                     // Filter (5)
{
    cout<<"Rotate (90), (180) or (270) degrees? ";
    int userCh;cin>>userCh;
    if(userCh==90)
    {
        for(int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                image[i][j]=standard[abs(255-j)][i];       // swap each row and column then swape each new row with the opposite one
            }
        }
    }
   if(userCh==180)
    {
        for(int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                image[i][j]=standard[abs(255-i)][abs(255-j)];      // swape each row & column with the opposite one
            }
        }
    }
    else if(userCh==270)
    {
        for(int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
              image[i][j]=standard[abs(255-j)][abs(255-i)];      //180
              image[i][j]=standard[j][abs(255-i)];              // 90 :(180 +90 =270):   make both above algorithms will lead to 270 degrees
            }
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void Darken_and_Lighten()             // Filter (6)
{
    cout<<"Do you want to 1-> darken or 2-> lighten? ";
    int s;cin>>s;
    if(s==1)
    {
        for(int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                image[i][j]-=(image[i][j]/2);            // darken by 50 %
            }
        }
    }
    else if(s==2)
    {
        for(int i=0;i<SIZE;i++)
        {
            for (int j=0;j<SIZE;j++)
            {
                image[i][j]+=((255-image[i][j])/2);             // By Trying to avoid out of range
            }
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void Detect_Image_Edges()                       // Filter (7)
{
    for (int i=0; i<SIZE-1; i++){
        for (int j=0; j<SIZE-1; j++){
            if((abs(image[i][j]-image[i][j+1])>=40)||(abs(image[i][j]-image[i+1][j])>=40)){
                image[i][j]=0;
            }else {
                image[i][j] = 255;
            }
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void Enlarge_Image()                           // Filter (8)
{
    unsigned char imgcopy[SIZE][SIZE];                        // carries quarter values in Filter (8)
    cout<<"Which quarter to enlarge 1, 2, 3 or 4? ";
    int quarter;cin>>quarter;                             // user choise
    if(quarter==1)
    {
        for(int i=0;i<128;i++)
        {
            for(int j=0;j<128;j++)
            {
                imgcopy[i][j]=standard[i][j];         // we dont need any changing in indexes because it starts from zero
            }
        }
        for(int k=0;k<SIZE;k++)
        {
            for(int l=0;l<SIZE;l++)
            {
                image[k][l]=imgcopy[k/2][l/2];             // every pixel in imgcopy will cover two pixels in image
            }
        }
    }
    else if(quarter==2)
    {
        int jindex=0;
        for(int i=0;i<128;i++)
        {
            for(int j=128;j<SIZE;j++)
            {
                jindex=abs(128-j);                   // avoid misleading index in imgcopy because it should start from zero not 128
                imgcopy[i][jindex]=standard[i][j];
            }
            for(int k=0;k<SIZE;k++)           // They have the same logic and formula but the difference is changing the indexes that you edit
            {
                for(int l=0;l<SIZE;l++)
                {
                    image[k][l]=imgcopy[k/2][l/2];
                }
            }
        }
    }
    else if(quarter==3)
    {
        int index=0;
        for(int i=128;i<SIZE;i++)
        {
            index=abs(128-i);                          // avoid misleading index in imgcopy
            for(int j=0;j<128;j++)
            {
                imgcopy[index][j]=standard[i][j];
            }
        }
        for(int k=0;k<SIZE;k++)
        {
            for(int l=0;l<SIZE;l++)
            {
                image[k][l]=imgcopy[k/2][l/2];        // all of them have the same idea
            }
        }
    }
    else if(quarter==4)
    {
        for(int i=128;i<SIZE;i++)
        {
            for(int j=128;j<SIZE;j++)
            {
                imgcopy[abs(128-i)][abs(128-j)]=standard[i][j];   // avoid misleading index in imgcopy
            }
        }
        for(int k=0;k<SIZE;k++)
        {
            for(int l=0;l<SIZE;l++)
            {
                image[k][l]=imgcopy[k/2][l/2];
            }
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void Shrink_Image()                           // Filter (9)
{

    int shrinkFactor;
    cout << "Shrink to (1/2), (1/3), or (1/4) Enter 1-> (1/2), 2-> (1/3), 3-> (1/4)? ";
    cin >> shrinkFactor;
    if (shrinkFactor==1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i / 2][j / 2] = standard[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++) {
            for (int j = SIZE / 2; j < SIZE; j++) {
                image[i][j] = 255;
            }
        }
        for (int i = SIZE / 2; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] = 255;
            }
        }
    }else if (shrinkFactor==2){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i/3][j/3]=image[i][j];
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j =SIZE/3 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
        for (int i = SIZE/3; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
    }else if(shrinkFactor==3){
        for (int i = 0; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i /4][j/4]=image[i][j];
            }
        }
        for (int i = SIZE/4; i < SIZE; i++){
            for (int j =0 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
        for (int i = 0; i < SIZE; i++){
            for (int j =SIZE/4 ; j <SIZE; j++){
                image[i][j]=255;
            }
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void Mirror_Image()                        //  Filter (10)
{
    cout<<"Mirror (1) left, (2) right, (3) upper, (4) down side? ";
    int op;cin>>op;                                      // user choise
    if(op==1)                                           // left side
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int j=128;j<SIZE;j++)
            {
                image[i][j]=image[i][255-j];
            }
        }
    }
    else if(op==2)                                      // right side
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int j=0;j<128;j++)
            {
                image[i][j]=image[i][255-j];
            }
        }
    }
    //  in cases (1) & (2) the difference will be in columns and rows will not be changed
    else if(op==3)                                      // upper side
    {
        for(int i=128;i<SIZE;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                image[i][j]=image[255-i][j];
            }
        }
    }
    else if(op==4)
    {
        for(int i=0;i<128;i++)
        {
            for(int j=0;j<SIZE;j++)
            {
                image[i][j]=image[255-i][j];
            }
        }
    }
    //  in cases (3) & (4) the difference will be in rows and columns will not be changed
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void Shuffle_Image()                  // Filter (11)
{
    unsigned char quar1[150][150];
    unsigned char quar2[150][150];
    unsigned char quar3[150][150];
    unsigned char quar4[150][150];
    for(int i=0;i<128;i++)
    {
        for(int j=0;j<128;j++)
        {
            quar1[i][j]=standard[i][j];
        }
    }
    for(int i=0;i<128;i++)
    {
        for(int j=128;j<SIZE;j++)
        {
            quar2[i][abs(128-j)]=standard[i][j];
        }
    }
    for(int i=128;i<SIZE;i++)
    {
        for(int j=0;j<128;j++)
        {
            quar3[abs(128-i)][j]=standard[i][j];
        }
    }
    for(int i=128;i<SIZE;i++)
    {
        for(int j=128;j<SIZE;j++)
        {
            quar4[abs(128-i)][abs(128-j)]=standard[i][j];
        }
    }
    //////////////////////////////////////////////////  All of the above is just to make each quarter ready for swapping
    cout<<"Enter New order of quarters: ";
    int n1,n2,n3,n4;cin>>n1>>n2>>n3>>n4;
    if(n1<0||n2<0||n3<0||n4<0||n1>4||n2>4||n3>4||n4>4||n1==n2||n1==n3||n1==n4||n2==n3||n2==n4||n3==n4)     // Invalid inputs 
    {
        cout<<"Your input is rejected☹️  Please try again\n";
        flag=0;                            // To end program after calling this function in main()
        return;                           // To close the function when user enter uncorrect order
    }
    if(n1==2)
    {
        for(int i=0;i<128;i++)        //
        {                               //Standard for first quarter
            for(int j=0;j<128;j++)   //
            {
                image[i][j]=quar2[i][j];
            }
        }
    }
    else if(n1==3)
    {
        for(int i=0;i<128;i++)
        {
            for(int j=0;j<128;j++)
            {
                image[i][j]=quar3[i][j];
            }
        }
    }
    else if(n1==4)
    {
        for(int i=0;i<128;i++)
        {
            for(int j=0;j<128;j++)
            {
                image[i][j]=quar4[i][j];
            }
        }
    }
    /////////////////////// All of the above is just what is the first input
    if(n2==1)
    {
        for(int i=0;i<128;i++)           //
        {                                    // Standard for second quarter
            for(int j=128;j<SIZE;j++)    //
            {
                image[i][j]=quar1[i][abs(128-j)];
            }
        }
    }
    else if(n2==3)
    {
        for(int i=0;i<SIZE;i++)
        {
            for(int j=128;j<SIZE;j++)
            {
                image[i][j]=quar3[i][abs(128-j)];
            }
        }
    }
    else if(n2==4)
    {
        for(int i=0;i<128;i++)
        {
            for(int j=128;j<SIZE;j++)
            {
                image[i][j]=quar4[i][abs(128-j)];
            }
        }
    }
    /////////////// All of the above is just what is the second input
    if(n3==1)
    {
        for(int i=128;i<SIZE;i++)              //
        {                                           // Standard for third quarter
            for(int j=0;j<128;j++)              //
            {
                image[i][j]=quar1[abs(128-i)][j];
            }
        }
    }
    else if(n3==2)
    {
        for(int i=128;i<SIZE;i++)
        {
            for(int j=0;j<128;j++)
            {
                image[i][j]=quar2[abs(128-i)][j];
            }
        }
    }
    else if(n3==4)
    {
        for(int i=128;i<SIZE;i++)
        {
            for(int j=0;j<128;j++)
            {
                image[i][j]=quar4[abs(128-i)][j];
            }
        }
    }
    ///////// All of the above is just what is the third input
    if(n4==1)
    {
        for(int i=128;i<SIZE;i++)                //
        {                                             // Standard for last quarter
            for(int j=128;j<SIZE;j++)              //
            {
                image[i][j]=quar1[abs(128-i)][abs(128-j)];
            }
        }
    }
    else if(n4==2)
    {
        for(int i=128;i<SIZE;i++)
        {
            for(int j=128;j<SIZE;j++)
            {
                image[i][j]=quar2[abs(128-i)][abs(128-j)];
            }
        }
    }
    else if(n4==3)
    {
        for(int i=128;i<SIZE;i++)
        {
            for(int j=128;j<SIZE;j++)
            {
                image[i][j]=quar3[abs(128-i)][abs(128-j)];
            }
        }
    }
    // All of the above is just what is the last input
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void Blur_Image()            // Filter (12)
{
    int sum1=0, sum2=0, sum3=0, sum4=0;
    int Sum1=0, Sum2=0, Sum3=0,Sum4=0;
    int SUM1=0, SUM2=0, SUM3=0,SUM4=0;
    int SUm1=0, SUm2=0, SUm3=0,SUm4=0;
    for(int i=0; i < SIZE;i++){
        for(int j=0; j<SIZE; j++){

            sum1=image[i][j]+image[i+1][j]+image[i+2][j];
            sum2=image[i][j+1]+image[i][j+2];
            sum3=image[i+1][j+1]+image[i+1][j+2];
            sum4=image[i+2][j+2]+image[i+2][j+1];
            image[i][j]=(sum1+sum2+sum3+sum4)/9;

        }
    }
    for(int i=0; i < SIZE;i++){
        for(int j=0; j<SIZE; j++){

            Sum1=image[i][j]+image[i+1][j]+image[i+2][j];
            Sum2=image[i][j+1]+image[i][j+2];
            Sum3=image[i+1][j+1]+image[i+1][j+2];
            Sum4=image[i+2][j+2]+image[i+2][j+1];
            image[i][j]=(Sum1+Sum2+Sum3+Sum4)/9;

        }
    }
    for(int i=0; i < SIZE;i++){
        for(int j=0; j<SIZE; j++){

            SUM1=image[i][j]+image[i+1][j]+image[i+2][j];
            SUM2=image[i][j+1]+image[i][j+2];
            SUM3=image[i+1][j+1]+image[i+1][j+2];
            SUM4=image[i+2][j+2]+image[i+2][j+1];
            image[i][j]=(SUM1+SUM2+SUM3+SUM4)/9;

        }
    }
    for(int i=0; i < SIZE;i++){
        for(int j=0; j<SIZE; j++){

            SUm1=image[i][j]+image[i+1][j]+image[i+2][j];
            SUm2=image[i][j+1]+image[i][j+2];
            SUm3=image[i+1][j+1]+image[i+1][j+2];
            SUm4=image[i+2][j+2]+image[i+2][j+1];
            image[i][j]=(SUm1+SUm2+SUm3+SUm4)/9;

        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void crop()                      // Filter (13)
{
    cout<<"Please enter x y hight width: ";
    int x,y,hight,width;cin>>x>>y>>hight>>width;
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)                          // all row and columns another what he wants will be white to be like a cropped image
        {
           if(j>(x+width)||j<x)
           {
             image[i][j]=255;
           }
           if(i>(x+hight)||i<x)
           {
             image[i][j]=255;
           }
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            standard[i][j]=image[i][j];         //   this code is to make standard[][] up to date to apply another filter without any error and wrong old values stored in it 
        }
    }
}
void skewH(){               // Filter  (14)
    double L , theta , SSF, step, move, x;
    cout << "Please enter degree to skew right: ";
    cin >> theta;
    L = 256*tan((theta*M_PI)/180);
    x = 256/(1+((tan((theta*M_PI)/180))));
    SSF = 256/x;
    step = 256 - x;
    move = step/256;
    for(int i = 0; i < SIZE ; i++){
        for(int j = 0; j < SIZE ; j++){
            skewedH1[i][j] = 255;
            skewedH2[i][j] = 255;
        }
    }
    for(int i = 0; i < SIZE ; i++){
        for(int j = 0; j < SIZE/SSF ; j++){
            skewedH1[i][j] = image[i][j+(int)SSF];
        }
    }
    for(int i = 0; i < SIZE ; i++){
        for(int j = 0; j < SIZE ; j++){
            skewedH2[i][j + (int)step] = skewedH1[i][j];
        }
        step = step - move;
    }
    for(int i = 0; i < SIZE ; i++){
        for(int j = 0; j < SIZE ; j++){
            image[i][j] = skewedH2[i][j];
        }
    }
}
void menu();
void doSomething()
{
    int userChoise;cin>>userChoise;
    switch (userChoise)
    {
        case 0:
        {
            flag=0;
            break;
        }
        case 16:
        {
            flag=1;
            break;
        }
        case 1:
        {
            Black_White();
            menu();
            break;
        }
        case 2:
        {
            Invert_Image();
            menu();
            break;
        }
        case 3:
        {
            Merge_Image();
            menu();
            break;
        }
        case 4:
        {
            Flip_Image();
            menu();
            break;
        }
        case 5:
        {
            Rotate_Image();
            menu();
            break;
        }
        case 6:
        {
            Darken_and_Lighten();
            menu();
            break;
        }
        case 7:
        {
            Detect_Image_Edges();
            menu();
            break;
        }
        case 8:
        {
           Enlarge_Image();
           menu();
            break;
        }
        case 9:
        {
            Shrink_Image();
            menu();
            break;
        }
        case 10:
        {
            Mirror_Image();
            menu();
            break;
        }
        case 11:
        {
            Shuffle_Image();
            if(flag!=0)                    //  if user input invalid sequence will close programe
            {
                menu();
            }
            break;
        }
        case 12:
        {
            Blur_Image();
            menu();
            break;
        }
        case 13:
        {
            crop();
            menu();
            break;
        }
        case 14:
        {
            skewH();
            menu();
            break;
        }
    }
}
///////////////////////////
void menu()                              // Display available options to a user
{
    cout<<"Please select a filter to apply or 0 to exit:\n";
    cout<<"1-Black &White Filter\n2-Invert Filter\n3-Merge Filter\n4-Flip Image\n5-Rotate Image\n6-Darken and Lighten Image\n7-Detect Image Edges\n8-Enlarge Image\n9-Shrink Image\n";
    cout<<"10-Mirror 1/2 Image\n11-Shuffle Image\n12-Blur Image\n13-Crop Image\n14-Skew Image Right\n15-Skew Image UP\n16-Save the Image to a file\n0-exit\n";
    doSomething();
}
void saveImage()            // save changes
{
    char imageName[50];
   cout << "Enter the target image file name: ";
   cin >> imageName;
   strcat (imageName, ".bmp");
   writeGSBMP(imageName, image);
}
int main()
{
    loadImage();
    menu();
    if(flag==0) return 0;      // To stop program if there any wrong in condition or user input
    saveImage();
}