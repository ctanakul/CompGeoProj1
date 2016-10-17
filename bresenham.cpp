#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h> //for abs

#include <fstream> //for read textfile
#include <string> //for read textfile
#include <sstream> // for read textfile

using namespace cv;
using namespace std;

//1.--------------------------------------Clear, point input, test Mat, print mat-------------------------------------------

//test how to color mat
void color_mat_test(Mat &mat){
  for (int i = 0; i < 250; ++i){
    for (int j = 0; j < 350; ++j){
      mat.at<Vec3b>(i,j) = Vec3b(255,255,0);
    }      
  }
  return; 
}


//color the whole picture
void color_whole_pict(Mat &mat, int r, int g, int b){
  for (int i = 0; i < mat.rows; ++i){
    for (int j = 0; j < mat.cols; ++j){
      mat.at<Vec3b>(i,j) = Vec3b(b,g,r);
    }      
  }
  return; 
}

//input 2 points for Bresenham test
void put_2points_in_mat(int mat[][2]){
  // mat[0][0] = 5; //mat is a pointer
  // mat[0][1] = 4;
  // mat[1][0] = 400;
  // mat[1][1] = 10;

  // //45 deg positive point
  // mat[0][0] = 30; //mat is a pointer
  // mat[0][1] = 30;
  // mat[1][0] = 500;
  // mat[1][1] = 500;

  // //45 deg positive point (reversed)
  // mat[0][0] = 400; //mat is a pointer
  // mat[0][1] = 400;
  // mat[1][0] = 3;
  // mat[1][1] = 3;

  // //45 deg negative point
  // mat[0][0] = 30; //mat is a pointer
  // mat[0][1] = 330;
  // mat[1][0] = 330;
  // mat[1][1] = 30;

  // // 45 deg negative point (reversed)
  // mat[0][0] = 300; //mat is a pointer
  // mat[0][1] = 30;
  // mat[1][0] = 0;
  // mat[1][1] = 330;

  // //Horizontal point
  // mat[0][0] = 300; //mat is a pointer
  // mat[0][1] = 30;
  // mat[1][0] = 75;
  // mat[1][1] = 30;

  // //Vertical point
  // mat[0][0] = 75; //mat is a pointer
  // mat[0][1] = 490;
  // mat[1][0] = 75;
  // mat[1][1] = 30;

  // //Positive shallow point 
  // mat[0][0] = 490; //mat is a pointer
  // mat[0][1] = 20;
  // mat[1][0] = 3;
  // mat[1][1] = 5;

  // //Positive steep point 
  // mat[0][0] = 7; //mat is a pointer
  // mat[0][1] = 498;
  // mat[1][0] = 3;
  // mat[1][1] = 5;

  // //Negative steep point 
  // mat[0][0] = 7; //mat is a pointer
  // mat[0][1] = 20;
  // mat[1][0] = 3;
  // mat[1][1] = 490;

  // //Negative shallow point 
  // mat[0][0] = 7; //mat is a pointer
  // mat[0][1] = 500;
  // mat[1][0] = 500;
  // mat[1][1] = 400;

  return;
}


// print array with the column of 2
int print_array_2(int mat[][2]){
  int block_number = sizeof(mat);
  int count = 0;
  while (count < block_number){
    cout << mat[count][0] << "," << mat[count][1] << endl; 
    count++;
  }
}


//2.---------------------------------------Bresenham line drawing---------------------------------------------------------------------------------------



//2.1------------------Vertical line operation---------------------------------------


// sort and switch 2 points to have a startpoint in the first row and endpoint in the other row with respect to x
void sort_start_point_end_point(int two_points[][2]){
  int startpoint_x,startpoint_y,endpoint_x,endpoint_y;
  if(two_points[0][0] < two_points[1][0]){
    return;
  }
  else{
    startpoint_x = two_points[1][0];  //assign x of startpoint
    startpoint_y = two_points[1][1];	
    endpoint_x = two_points[0][0];//assign x of endpoint
    endpoint_y = two_points[0][1];
  }
  two_points[0][0] = startpoint_x;
  two_points[0][1] = startpoint_y;
  two_points[1][0] = endpoint_x;
  two_points[1][1] = endpoint_y;  
}


//return True if 2 points are vertically aligned
bool check_vert(int two_points[][2]){
  if(two_points[0][0] == two_points[1][0]){return true;}
  return false;
}


// Vertical line drawing
void line_draw_vert(Mat &mat, int two_points[][2]){
  sort_start_point_end_point(two_points);
  for(int y = two_points[0][1]; y <= two_points[1][1]; ++y){
    mat.at<Vec3b>(y,two_points[0][0]) = Vec3b(0,0,0);
  }
  return;
}


//2.2------------------Horizontal line operation------------------------------------


//return True if 2 points are horizontally aligned
bool check_horiz(int two_points[][2]){
  if(two_points[0][1] == two_points[1][1]){return true;}
  return false;
}


// Horizontal line drawing
void line_draw_horiz(Mat &mat, int two_points[][2]){
  sort_start_point_end_point(two_points);
  for(int x = two_points[0][0]; x <= two_points[1][0]; ++x){
    mat.at<Vec3b>(two_points[0][1],x) = Vec3b(0,0,0);
  }
  return;
}



//2.3----------------45 degree aligned line operation------------------------------


//return True if 2 points are 45 degree aligned
bool check_equal_delta_xy(int two_points[][2]){
  int deltax = two_points[0][0]-two_points[1][0];
  int deltay = two_points[0][1]-two_points[1][1];
  if(abs(deltax) == abs(deltay)){return true;}
  return false;
}


//return True is 2 points are aligned with positive slope
bool check_positive_slope(int two_points[][2]){
  float deltax = two_points[0][0]-two_points[1][0];
  float deltay = two_points[0][1]-two_points[1][1];
  if ((deltay/deltax) > 0){return true;}
  return false;
}


//draw positive slope line
void line_draw_45deg_positive_slope(Mat &mat, int two_points[][2]){
  sort_start_point_end_point(two_points);
  int y = two_points[0][1];
  for(int x = two_points[0][0]; x <= two_points[1][0]; ++x){
    mat.at<Vec3b>(y,x) = Vec3b(0,0,0);
    y += 1;
  }
}


//draw negative slope line
void line_draw_45deg_negative_slope(Mat &mat, int two_points[][2]){
  sort_start_point_end_point(two_points);
  int y = two_points[0][1];
  for(int x = two_points[0][0]; x <= two_points[1][0]; ++x){
    mat.at<Vec3b>(y,x) = Vec3b(0,0,0);
    y -= 1;
  }
}


//45 degree line points checking and drawing
void line_draw_equal_delta_xy(Mat &mat, int two_points[][2]){
  if (check_positive_slope(two_points)){
    line_draw_45deg_positive_slope(mat,two_points);
  }
  else {line_draw_45deg_negative_slope(mat,two_points);}
}



//2.4--------------ordinary line operation (slope and non-45 deg) ------------------------------



// check if deltax i smore than delta y
bool check_deltax_more_than_deltay(int two_points[][2]){
  float deltax = two_points[0][0]-two_points[1][0];
  float deltay = two_points[0][1]-two_points[1][1];
  if (deltax > deltay){return true;}
  return false;
}


// draw non-45-deg slope line
void line_draw_ordinary(Mat &mat, int two_points[][2]){

  sort_start_point_end_point(two_points);

  float deltax = two_points[0][0]-two_points[1][0];
  float deltay = two_points[0][1]-two_points[1][1];
  float error = -1.0;
  float delta_low;
  float delta_high;
  float deltaerr;
  int error_increm_start_value; 
  int error_increm_end_value; 
  int always_increm_start_value; 
  int always_increm_end_value;

  if(abs(deltax) > abs(deltay)){
    delta_low = deltay;
    delta_high = deltax;
    error_increm_start_value = two_points[0][1];// y
    error_increm_end_value = two_points[1][1];
    always_increm_start_value = two_points[0][0];// x
    always_increm_end_value = two_points[1][0];
  }
  else{
    delta_low = deltax;
    delta_high = deltay;
    error_increm_start_value = two_points[0][0]; // x
    error_increm_end_value = two_points[1][0];
    always_increm_start_value = two_points[0][1]; // y
    always_increm_end_value = two_points[1][1];
  }

  deltaerr = abs(delta_low/delta_high);

  int count_error; 

  if(check_positive_slope(two_points)){
      count_error = error_increm_start_value;
      for (int count = always_increm_start_value; count < always_increm_end_value; ++count){
	if(delta_low == deltay){	
	  mat.at<Vec3b>(count_error,count) = Vec3b(0,0,0);
	}
	else{
	  mat.at<Vec3b>(count,count_error) = Vec3b(0,0,0);
	}
	error = error + deltaerr;
	if(error >= 0.0){
	  ++count_error;
	  error = error - 1.0;
	}
      }
    }
   else {
     count_error = error_increm_start_value;
     // if shallow and negative slope
     if(delta_low == deltay){
       for (int count = always_increm_start_value; count < always_increm_end_value; ++count){	
	 mat.at<Vec3b>(count_error,count) = Vec3b(0,0,0);
	 error = error + deltaerr;
	 if(error >= 0.0){
	   --count_error;
	   error = error - 1.0;
	 }      	
       }
     }
// if steep and negative slope
     else{
       for (int count = always_increm_start_value; count > always_increm_end_value; --count){
	 mat.at<Vec3b>(count,count_error) = Vec3b(0,0,0);
	 error = error + deltaerr;
	 if(error >= 0.0){
	   ++count_error;
	   error = error - 1.0;	  
	 }
       }      
     }
   }
}






//2.5-----------------draw line between 2 points according to Bresenham---------------------
void line_draw_brasenham(Mat &mat,int two_points[][2]){

  // check if points are horizontally or vertically aligned, and draw line.
  if (check_vert(two_points)){
    line_draw_vert(mat,two_points);
    return;
  }
  if (check_horiz(two_points)){
    line_draw_horiz(mat,two_points);
    return;
  }

  // check if points are 45 degree aligned and draw line.
  if (check_equal_delta_xy(two_points)){
    line_draw_equal_delta_xy(mat,two_points);
    return;
  }
  line_draw_ordinary(mat,two_points);
  return; 
}


//3-------------------------------------points input from file operation----------------------------------------------------------

//3.1input points from text in 'P' case
void input_point_from_text(int input[][2],string filename, int size){
  
  string item;     
  int count = 0, index_apos, index_last_brack;
  ifstream inFile;
  inFile.open(filename.c_str());

  if (inFile.fail()){
    cerr << "Error Opening File" << endl;
    exit(1);
  }

  for(int i = 0; i <= size; i++){
    //prevent the lastline multiple copies
    inFile >> item;   
    if(item.substr(0,1) == "("){
      index_apos = item.find(",");
      index_last_brack = item.find(")");
      stringstream convert1(item.substr(1,index_apos));
      convert1 >> input[i-1][0];
      stringstream convert2(item.substr(index_apos + 1,index_last_brack));
      convert2 >> input[i-1][1];
    }
  }
}



//4-------------------------------------draw polygon from points----------------------------------------------------------

//4.1draw polygon from points
void draw_polygon_line (Mat &image, int mat_points[][2], int mat_size){

  int two_dot_array[2][2];
  int j;
  for (int i = 0; i < mat_size; i++){
    if(i == mat_size - 1){j = 0;}
    else{j = i + 1;}
    
    //put 2 points into 2_dot_array
    two_dot_array[0][0] = mat_points[i][0];
    two_dot_array[0][1] = mat_points[i][1];
    two_dot_array[1][0] = mat_points[j][0];
    two_dot_array[1][1] = mat_points[j][1];
    
    // cout << "i : " << i << " j : " << j << endl;
    // cout << "twodot_x0 : " << two_dot_array[0][0] << endl;
    // cout << "twodot_y0 : " << two_dot_array[0][1] << endl;
    // cout << "twodot_x1 : " << two_dot_array[1][0] << endl;
    // cout << "twodot_y1 : " << two_dot_array[1][1] << endl;
    // cout << "sizeof = " << sizeof(two_dot_array)/(2*sizeof(two_dot_array[0][0])) << endl;

    // draw a line between 2 points
    line_draw_brasenham(image,two_dot_array);    
  }

}

//5--------------------------------------color the polygon---------------------------------------------------------------


//5.1 --------------return rightmost and leftmost x and y coordinate of a polygon line-------
///5.1.1 Build structure containing limitpoints
struct Limitpoints{
  int least_x;
  int least_y;
  int most_x;
  int most_y;
};

///5.1.2 Function for return Limitpoints
Limitpoints get_limitpoints_polygon(int points[][2], int size_point_array){

  cout << "size = " << size_point_array << endl;
  int size = size_point_array;
  Limitpoints limits;

  //find leftmost_x
  for (int x = 0; x < size; x++){
    cout << "point = " << points[x][0] << endl;
    cout << "x++ = " << x << endl;
    if ((points[x][0] < limits.least_x) || (x == 0)){
      cout << "Inside point = " << points[x][0] << endl;
      cout << "x++ = " << x << endl;
      limits.least_x = points[x][0];
    }  
  }
  //find rightmost_x
  for (int x = 0; x < size; x++){
    if ((points[x][0] > limits.most_x) || (x == 0)){
      limits.most_x = points[x][0];
    }  
  }
  //find topmost_y
  for (int y = 0; y < size; y++){
    if ((points[y][1] < limits.least_y) || (y == 0)){
      limits.least_y = points[y][1];
    }  
  }
  //find bottommost_y
  for (int y = 0; y < size; y++){
    if ((points[y][1] > limits.most_y) || (y == 0)){
      limits.most_y = points[y][1];
    }  
  }
  return limits; 
}


//5.2 color polygon in limits
void color_polygon_in_limits(Mat &polygon_unfilled, Limitpoints limits){
  //make the horizontal sweepline(y-axis)
  int fill = 0;
  cout << "test   " << polygon_unfilled.at<Vec3b>(limits.least_y,limits.least_x - 1) << endl;
  cout << "test   " << polygon_unfilled.at<Vec3b>(345,100) << endl;
  cout << "test   " << polygon_unfilled.at<Vec3b>(740,350) << endl;
  cout << "test   " << polygon_unfilled.at<Vec3b>(344,99) << endl;
  cout << "test   " << polygon_unfilled.at<Vec3b>(739,349) << endl;
  cout << "test   " << polygon_unfilled.at<Vec3b>(738,348) << endl;
  cout << "test   " << polygon_unfilled.at<Vec3b>(741,351) << endl;



  for(int y = limits.least_y; y < limits.most_y ; y++){
    //make the vertical sweepline for each step of horizontal sweepline(x-axis with each x-axis)
    for(int x = limits.least_x; x < limits.most_x ; x++){
      //if the pixel before is black and now is white, fill = 1, and fill that pixel
      if((polygon_unfilled.at<Vec3b>(y, x - 1) == Vec3b(0,0,0)) && (fill == 0)){
  	fill = 1;
      }
      else if((polygon_unfilled.at<Vec3b>(y,x) == Vec3b(0,0,0)) && (fill == 1)){
	break;
      }
      if(fill == 1){
  	polygon_unfilled.at<Vec3b>(y, x) = Vec3b(0,0,200);
      }      
    }
    fill = 0;
  }
}



//5.----------------Color the polygon process---------------------------------
void color_polygon(Mat &polygon_line, int points[][2], int size_points_array){
  //return leftmost and rightmost x and y
  Limitpoints limits = get_limitpoints_polygon(points,size_points_array);
  color_polygon_in_limits(polygon_line,limits);
}








////////--------------------------------------------------------------------------Main-----------------------------------------------------------------------//////////


int main(){
  Mat image(1000, 1000, CV_8UC3); //B,G,R
  color_whole_pict(image,255,255,255); //color whole pict to be white
  
  //input from file
  ifstream inFile;
  inFile.open("Input1.txt");
  //Check for error
  if (inFile.fail()){
    cerr << "Error Opening File" << endl;
    exit(1);
  }
  //count items
  string item;
  int count = 0;
  while (!inFile.eof()){
    inFile >> item;
    count++;
  }
  //create a list of points
  int input[count - 2][2];
  const int size_input = sizeof(input)/(2*sizeof(input[0][0]));
  //get input points
  input_point_from_text(input,"Input1.txt", size_input);


  //draw polygon by connecting points
  draw_polygon_line(image,input, size_input);
  
  //color the polygon
  color_polygon(image,input,size_input);


  namedWindow("figure", WINDOW_AUTOSIZE);
  imshow("figure",image);
  waitKey(0);
  return 0;
}




// *input : is a pointer keeping address
// *(*input) : give a value that is pointed to
// input : pointer
// input[0] : input[0][0]

// P
// (1,3)
// (4,5)
// (50,67)
