To run the program

    $ ./Brasenham

-----------------------------------------

If there's segmentation fault eroor shown
It's because the stack reaches the limit set.

    $ ulimit -s 32000

to set  the limit of stack 

-------------------------------------------

You might need to setup CMake first...

------------------------------------------
To edit the code, go to brasenham.cpp

You can change input files in Main() and filename

Input1.txt ------ Draw and color a polygon from counter-clockwise point sequence
Input-2.txt ----- Draw two polygons and color each of them according to the RGB color given
It has 2 operations according to what we type in two_polygons_operation(filename, "u"); in Main()
If the second input string is "u", they will be union and clor both of them red.
If the second input string is "i", they will be color to show which is front and rear according to x-coordinate
