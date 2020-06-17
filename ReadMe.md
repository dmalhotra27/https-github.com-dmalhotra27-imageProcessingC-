Exercise
---------
Analyzing the number of colored ares in an image in C++.

Exercise: Input a grey-scale image, count number of colored areas in that image. Output should be contents of array with corresponding count 
of each gray shade retrieved.

Algorithm:
-----------
1. Parse command line arguments & retrieve imput file name along with dimensions -- width & height.
2. Read image data into Mat array (for normal image files e.g. jpg/jpeg/png) or buffer in case of binary file
3. Resize image for normal image files
4. Create an object for Image class & initialize with dimensions above & image data
5. Count areas algorithm is based on computing neighbour pixels for each pixel having same shade value, constituting a single area
6. Recursively invoke neighbouring pixels logic for neighbours determined in step 5. 
7. Mark the pixels already considered during step 5 & 6 as 'true' to avoid infinite loop and to correctly determine contours/areas.
8. Output array based on different regions determined above (step 5).

NOTE:: Make sure stack size is enlarged considering big image sizes & to avoid stack overflow exception.

Compilation Steps:
-------------------
g++ main.cpp Image.cpp -o count-areas

Run instructions:
------------------
Once the program has been complied, run the following command to start the program:

./count-areas <input-filename> --shape <width>,<height>