#include "imageData.h"
#include "functions.h"
/* Zain Paya
In this MP the goal was to implement functions in which one is able to change the pixels of a given image. Functions
 include such as inverting the color of the image, making a grayscale image, etc. the complicated aspect about this
 MP lays in the convolve image function when considering the pixels at the edge of the screen. Overall the MP isn't too bad.
	HELP!!!! I have made a proper code for the convert to gray image function however it seems that the autochecker seems
	to think its incorrect. It exactly resembles the image that you guys have provided if you create the output.png file for it.
*/

/*
 * calculateCosineFilter - calculates the cosine filter values
 * INPUTS:  int radius- integer indicating the size of array. 
 *          The filter has 2*radius+1 rows and 2*radius+1 columns
 * OUTPUTS: cosineFitler - pointer to the 1-D array of size 
 *          (2*radius+1)*(2*radius+1). Appropriate space 
 *          has already been allocated). This function must compute
 *          the appropriate values of this array as described 
 *          in the wiki writeup
 * RETURN VALUE: none
 */
void calculateCosineFilter(double *cosFilter,int radius)
{
//Your Code here
int x, y;
double C = 0.0;
double sum = 0.0;
int width = 2*radius + 1;

	for( x = -1 * radius; x <= radius; x++){			//column
		for( y = -1 * radius; y <= radius; y++){		//row
			
			
	C = cos( ( M_PI * x)/( 2 * radius ) ) + cos( ( M_PI * y)/( 2 * radius ) );
		int x_new = x + radius;					// these new variables are used to translate the x and y coordinates from 
									//-radius to 0 and from radius to width. Done so the index of cosine filter is proper.
		int y_new = y + radius;
	cosFilter[x_new * width + y_new  ] = C;
	sum = sum + C;
							}
						}
	//normalizing
	for( x = -1 * radius; x <= radius; x++){
		for( y = -1 * radius; y <= radius; y++){
			int x_new = x + radius;
			int y_new = y + radius;
		
		cosFilter[x_new * width + y_new ] = cosFilter[x_new * width + y_new]/sum;	//normalization
							}
						}			
}		

/* convolveImage - performs a convolution between a filter and image
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array) 
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         filter - pointer to the convolution filter (1-D array)
 *         radius - radius of the convolution filter
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Filter is already initialized and contains desired values.
 *       Appropriate space has been allocated for output arrays. 
 */
void convolveImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha, uint8_t *outRed,uint8_t *outGreen,
                   uint8_t *outBlue,uint8_t *outAlpha,const double *filter,
                   int radius,int width,int height)
{
//Your Code here              

    int total = height * width;              // Total number of pixels in the image
    
     int k;					//iterations
    
    for(k = 0;k < total ; k++){                   // Keep values of Alpha as it is.
     
      outAlpha[k] = inAlpha[k];
    			     }
    
    if (radius < 1){                        // If radius of filter is < 1, all values remain as it is.
    
      int x;
      for(x = 0; x < total; x++) {
         outRed[x] = inAlpha[x];
         outGreen[x] = inAlpha[x];
         outBlue[x] = inAlpha[x];
     			        }
   		   }
    else{
    

    // Initialize variables used in for loops.
    
    int i;
    int j;
    int a;
    int b;
    int c;

    
    for( i = 0; i < height ;i++){                
    
       for( j = 0; j < width; j++){
       
          double outputR = 0;                        // Initialize variables that hold the sum of (input pixel values*filter values)
          double outputG = 0;
          double outputB = 0;
          int P = i * width + j;              // Points towards current value in the image array around which the filter will be centered.
         
          int upperlimitH = i + radius;                  // Max and Min y and x coordinates of filter array currently centered around the pointer.           
          int lowerlimitH = i - radius;                 
          int upperlimitW = j + radius;
          int lowerlimitW = j - radius;
          c = 0;                               
          
          // Loop through position of all elements of the filter array.
          
          for(a = lowerlimitH; a <= upperlimitH; a++){
             for(b = lowerlimitW; b <= upperlimitW; b++){

                 if(a >= 0 && a < height && b >= 0 && b < width){       // If the position of the current element of the filter array is within the permitted boundary of the filter,
                                                              		 // calculate the product of that filter value and input array value and add it to the output variable.
  
                    outputR = outputR + inRed[a * width + b ]*( filter[c] );
                    outputG = outputG + inGreen[a * width + b ]*( filter[c] );
                    outputB = outputB + inBlue[a * width + b ]*( filter[c] );
                 } 
                 c = c + 1;                                          // Move to the next element of the filter array.
              }
           }
          
           double truncated_outR = floor(outputR);	
           double truncated_outG = floor(outputG);
           double truncated_outB = floor(outputB);
     
           if(outputR - truncated_outR > 0.5){
             int outputR = ceil(outputR);
          			 }
           else{
             int outputR = floor(outputR);
               }
           if(outputG - truncated_outG > 0.5){
            int outputG = ceil(outputG);
          			     }
           else{
             int outputG = floor( outputG );
               }
           if(outputB - truncated_outB > 0.5){
             int outputB = ceil(outputB);
          			 }
           else{
           
             int outputB = floor(outputB);
               }
             
          // If the output variable has a value between 0 and 255, store it in the respective output array, otherwise store 0 if value < 0 and 255 if value < 255.

           
          if(outputR > 255){
          
             outRed[P] = 255;
          		}
          else if(outputR < 0){
          
             outRed[P] = 0;
          		 }
          else{
          
             outRed[P] = (outputR);
              }
             

          if(outputG > 255){
          
             outGreen[P] = 255;
          	      }
          else if(outputG < 0){
          
             outGreen[P] = 0;
          		 }
          else{
          
             outGreen[P] = (outputG);
              }
        

          if(outputB > 255){
          
             outBlue[P] = 255;
         	      }
          else if(outputB < 0){
          
             outBlue[P] = 0;
          		 }
          else{
          
             outBlue[P] = (outputB);
              }

       }
     }
   }
  return;
}


/* convertToGray - convert the input image to grayscale
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         gMonoMult - pointer to array with constants to be multipiled with 
 *                     RBG channels to convert image to grayscale (3 element array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       gMonoMult contains the desired grayscale weights.
 *       Appropriate space has been allocated for output arrays. 
 */
void convertToGray(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                   uint8_t *outBlue,uint8_t *outAlpha,
                   const double *gMonoMult,int width,int height)
{
//Your Code here 
int i, j;
for(i = 0; i < height; i++){
	for( j = 0; j < width; j++){
	
	double	multR = inRed[ i * width + j ] * gMonoMult[0];	
		/*red =0, green =1, blue = 2*/
	double	multG = inGreen[ i * width + j ] * gMonoMult[1];	//input of color * gMonoMult
	double	multB = inBlue[ i * width + j ] * gMonoMult[2];
	double sum = multR + multB + multG;				// sum of input colors * gMonoMult
	int weight = floor(sum);	
	outAlpha[ i * width + j ] = inAlpha[ i * width + j ];		//Alpha in =Alpha out
	outBlue[ i * width + j ] = weight;
	outGreen[ i * width + j ] = weight;
	outRed[ i * width + j ] = weight;
		   
				    }
			    }
	return;
}

/* invertImage - inverts the colors of the image
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Appropriate space has been allocated for output arrays. 
 */
void invertImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                 uint8_t *outBlue,uint8_t *outAlpha,int width,int height)
{
//Your Code here
int i, j;
	for( i = 0; i < height; i ++){
		for( j = 0; j < width; j++){
		//invert image, 255 - respective image
outRed[ i * width + j ] = 255 - inRed[ i * width + j ];
outBlue[ i * width + j ] = 255 - inBlue[ i * width + j ];
outGreen[ i * width + j ] = 255 - inGreen[ i * width + j ];
outAlpha[i * width + j ] = inAlpha[i * width + j ];
					   }
				     }
return;
}

/* color threshold - for each pixel of input image, compares value to red, green, and blue threshold. If the values exceed all three thresholds, set the output image to the input image values. Otherwise, set them to zero. Alpha should remain unchanged.
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         width - width of the input image
 *         height - height of the input image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input image values are already loaded into the input arrays
 *       Appropriate space has been allocated for output arrays. 
 */
void colorThreshold(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                 uint8_t *inAlpha,uint8_t *outRed,uint8_t *outGreen,
                 uint8_t *outBlue,uint8_t *outAlpha,int width,int height,int redThreshold,int blueThreshold,int greenThreshold)
{
//Your Code here
int i , j;
	for( i = 0; i < height; i++){
		for( j = 0; j < width; j++){
			if(inRed[i*width+j] > redThreshold && inGreen[i*width+j] > greenThreshold && inBlue[i*width+j] > blueThreshold){	//if all pizels exceed threshold
										// output of certain color = input of certain color
				outRed[i*width+j] = inRed[i*width+j];
				outGreen[i*width+j] = inGreen[i*width+j];
				outBlue[i*width+j] = inBlue[i*width+j];
				outAlpha[i*width+j] = inAlpha[i*width+j];						    
																	 }
			else{
				//set all color outputs to 0 and Alpha to 255 to make image black
				outRed[i*width+j] = 0;
				outGreen[i*width+j] = 0;
				outBlue[i*width+j] = 0;
				outAlpha[i*width+j] = 255;
			      }

					   }
				    }
return;	
}


/* Challenge problem 2
 * Detect target image in input image. Code should see if the target image is part of the 
 * input image. Outputs the center pixel of the target in the input image. 
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array) 
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *         targetRed - pointer to the target red channel (1-D array)
 *         targetGreen - pointer to the target green channel (1-D array)
 *         targetBlue - pointer to the target blue channel (1-D array)
 *         targetAlpha - pointer to the target alpha channel (1-D array)
 *         width - width of the input image
 *         height - height of the input image
 *         targetWidth - width of the target image
 *         targetHeight - height of the target image
 * OUTPUTS: outPixelCol - column index of detected target (-1 if no target found)
 *          outPixelRow - row index of detected target (-1 if no target found)
 * RETURN VALUES: none
 * NOTE: Input and target image values are already loaded into the input arrays
 *       outPixelCol and outPixelRow are passed by reference. Set the value at these pointers
 *       to the location of the target image in the larger image (-1, -1 if not found) 
 */
void detectImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,
                   uint8_t *inAlpha,int* outPixelCol, int* outPixelRow, uint8_t *targetRed, uint8_t *targetBlue, uint8_t *targetGreen, uint8_t *targetAlpha,int width,int height,int targetWidth, int targetHeight){
	 //Your Code here
}


/* Challenge Problem 1
 * transformImage - Computes an affline transformation of the input image
 * This can be used to compute rotations, rescale, and skew the image.
 * The two-dimensional array transform defines the transform to be done.
 * The values of the output image at x', y' are assigned by finding the closest (x,y) pair in 
 * the original image by inverting the transform
 * INPUTS: inRed - pointer to the input red channel (1-D array)
 *         inGreen - pointer to the input green channel (1-D array)
 *         inBlue - pointer to the input blue channel (1-D array)
 *         inAlpha - pointer to the input alpha channel (1-D array)
 *	   transform - two-dimensional array containing transform coefficients (2-D array)
 *         width - width of the input and output image
 *         height - height of the input and output image
 * OUTPUTS: outRed - pointer to the output red channel (1-D array)
 *          outGreen - pointer to the output green channel (1-D array)
 *          outBlue - pointer to the output blue channel (1-D array)
 *          outAlpha - pointer to the output alpha channel (1-D array)
 * RETURN VALUES: none
 * NOTE: Input values are already loaded into the input arrays
 *       Appropriate space is already allocated for output image 
 */
void transformImage(uint8_t *inRed,uint8_t *inGreen,uint8_t *inBlue,uint8_t *inAlpha,
              uint8_t *outRed,uint8_t *outGreen,uint8_t *outBlue,
              uint8_t *outAlpha,const double transform[2][2],int width,int height)
{
//Your Code here

}
