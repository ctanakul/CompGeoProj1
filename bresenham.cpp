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
  int block_number = sizeof(mat)/(2*sizeof(mat[0][0]));;
  int count = 0;
  while (count < block_number){
    cout << mat[count][0] << "," << mat[count][1] << endl; 
    count++;
  }
}

//get assignment type from the head of the txt file
string get_first_line(string filename){
  //input from file
  ifstream inFile;
  inFile.open(filename.c_str());
  //Check for error
  if (inFile.fail()){
    cerr << "Error Opening File" << endl;
    exit(1);
  }
  //get herd file
  string first_line;
  inFile >> first_line;
  return first_line;
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



//4-------------------------------------draw polygon from points(1 polygon)----------------------------------------------------------

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

//5--------------------------------------color the polygon(1 polygon)---------------------------------------------------------------


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
      if(fill == 1 and y != limits.least_y){
  	polygon_unfilled.at<Vec3b>(y, x) = Vec3b(0,0,200);
      }      
    }
    fill = 0;
  }
}



//5.3----------------Color the polygon process---------------------------------
void color_polygon(Mat &polygon_line, int points[][2], int size_points_array){
  //return leftmost and rightmost x and y
  Limitpoints limits = get_limitpoints_polygon(points,size_points_array);
  color_polygon_in_limits(polygon_line,limits);
}


//6---------------------------------------------------------polygons operation(union and intersection)-----------------------------------------------------

struct BGR_color{
  int b;
  int g;
  int r;
};

struct Polygons_info{
  int number_points_polygon1;
  int number_points_polygon2;
  BGR_color bgr_polygon1;
  BGR_color bgr_polygon2;
};


//6.1 ------------count points of each of 2 polygons to further build an array----------
Polygons_info count_points_2polygon(string filename){

  //input from file
  ifstream inFile;
  inFile.open(filename.c_str());
  //Check for error
  if (inFile.fail()){
    cerr << "count_points_2polygon :: Error Opening File" << endl;
    exit(1);
  }
        
  //count items
  string item;
  int polygon, end_string;
  int count_bgr;//r = 1, g = 2, b = 3, end = 4
  Polygons_info polygons_info;
  polygons_info.number_points_polygon1 = 0;
  polygons_info.number_points_polygon2 = 0;

  while (!inFile.eof()){
    inFile >> item;
    // cout << "item = " << item << endl;
    if (item == "P1"){
      polygon = 1;
      count_bgr = 1 ;
    }
    else if (item == "P2"){
      polygon = 2;
      count_bgr = 1;
    }
    //get info of polygon 1
    if (item != "P1" && polygon == 1){
      if(count_bgr == 1){
	end_string = item.find(",");
	stringstream convertR1(item.substr(1,end_string));
	convertR1 >> polygons_info.bgr_polygon1.r; 
	count_bgr = 2;
      }
      else if (count_bgr == 2){
	end_string = item.find(",");
	stringstream convertG1(item.substr(1,end_string));
	convertG1 >> polygons_info.bgr_polygon1.g; 
	count_bgr = 3;	
      }
      else if (count_bgr == 3){
	end_string = item.find(")");
	stringstream convertB1(item.substr(0,end_string));
	convertB1 >> polygons_info.bgr_polygon1.b; 
	count_bgr = 4;
      }
      else if (count_bgr == 4){
	polygons_info.number_points_polygon1++;
      }
    }

    //get info of polygon 2
    else if (item != "P2" && polygon == 2){
      if(count_bgr == 1){
	end_string = item.find(",");
	stringstream convertR2(item.substr(1,end_string));
	convertR2 >> polygons_info.bgr_polygon2.r; 
	count_bgr = 2;
      }
      else if (count_bgr == 2){
	end_string = item.find(",");
	stringstream convertG2(item.substr(1,end_string));
	convertG2 >> polygons_info.bgr_polygon2.g; 
	count_bgr = 3;	
      }
      else if (count_bgr == 3){
	end_string = item.find(")");
	stringstream convertB2(item.substr(0,end_string));
	convertB2 >> polygons_info.bgr_polygon2.b; 
	count_bgr = 4;
      }
      else if (count_bgr == 4){
	polygons_info.number_points_polygon2++;
      }
    }
  }
  return polygons_info; // for test
}
 
//6.2 ------------input points into arrays of 2 polygons------------------------------------

void input_point_from_text_2polygons(int input_1[][2],int size_input1,int input_2[][2], int size_input2,string filename){

  //input from file
  ifstream inFile;
  inFile.open(filename.c_str());
  //Check for error
  if (inFile.fail()){
    cerr << "input_point_from_text_2polygons :: Error Opening File" << endl;
    exit(1);
  }

  int index_apos, index_last_brack;
  string item;

  // input points into first array
  for(int i1 = -5; i1 < size_input1; i1++){
    //prevent the lastline multiple copies
    inFile >> item; 
    if(i1 >= 0) {
      if(item.substr(0,1) == "("){
	index_apos = item.find(",");
	index_last_brack = item.find(")");
	stringstream convert1(item.substr(1,index_apos));
	convert1 >> input_1[i1][0];
	stringstream convert2(item.substr(index_apos + 1,index_last_brack));
	convert2 >> input_1[i1][1];	
      }
      // cout << "i1  :  " << input_1[i1][0] << " , " << input_1[i1][1] << endl;
      // cout << "i1 is " << i1 << endl;
    }
  }

  
  // input points into second array
  for(int i2 = -4; i2 < size_input2; i2++){
    //prevent the lastline multiple copies
    inFile >> item;     
    // cout << "item is " << item << endl;
    if(i2 >= 0) {
      if(item.substr(0,1) == "("){
	index_apos = item.find(",");
	index_last_brack = item.find(")");
	stringstream convert1(item.substr(1,index_apos));
	convert1 >> input_2[i2][0];
	stringstream convert2(item.substr(index_apos + 1,index_last_brack));
	convert2 >> input_2[i2][1];
      }
      // cout << "i2  :  " << input_2[i2][0] << " , " << input_2[i2][1] << endl;
      // cout << "i2 is " << i2 << endl;
    }      
  }
}


//6.3------------------



//6.3-----------------------color a polygon (scan-line) from image to image--------
void color_scan_line_im_to_im(Mat &image, Mat &back_image, int mat_point[][2],int size_input, int B, int G, int R){
  //return leftmost and rightmost x and y
  Limitpoints limits = get_limitpoints_polygon(mat_point, size_input);
  int fill = 0;

  for(int y = limits.least_y; y < limits.most_y ; y++){
    //make the vertical sweepline for each step of horizontal sweepline(x-axis with each x-axis)
    for(int x = limits.least_x; x < limits.most_x ; x++){
      //if the pixel before is black and now is white, fill = 1, and fill that pixel
      if((back_image.at<Vec3b>(y, x - 1) == Vec3b(0,0,0)) && (fill == 0)){
  	fill = 1;
      }
      else if((back_image.at<Vec3b>(y,x) == Vec3b(0,0,0)) && (fill == 1)){
	break;
      }
      if(fill == 1 and y != limits.least_y){
        image.at<Vec3b>(y, x) = Vec3b(B,G,R);
      }      
    }
    fill = 0;
  }
}


void color_union_scan_line_im_to_im(Mat &image, Mat &back_image, int mat_point[][2],int size_input, int B, int G, int R){
  //return leftmost and rightmost x and y
  Limitpoints limits = get_limitpoints_polygon(mat_point, size_input);
  int fill = 0;

  for(int y = limits.least_y; y < limits.most_y ; y++){
    //make the vertical sweepline for each step of horizontal sweepline(x-axis with each x-axis)
    for(int x = limits.least_x; x < limits.most_x ; x++){
      //if the pixel before is black and now is white, fill = 1, and fill that pixel
      if((back_image.at<Vec3b>(y, x - 1) == Vec3b(0,0,0)) && (fill == 0)){
  	fill = 1;
      }
      else if((back_image.at<Vec3b>(y,x) == Vec3b(0,0,0)) && (fill == 1)){
	break;
      }
      if(fill == 1 and y != limits.least_y){
        image.at<Vec3b>(y, x) = Vec3b(B,G,R);
	if(back_image.at<Vec3b>(y,x + 1) != Vec3b(255,255,255)){
	  image.at<Vec3b>(y, x + 1) = Vec3b(B,G,R);
	}
	if(back_image.at<Vec3b>(y-1,x) == Vec3b(0,0,0) || back_image.at<Vec3b>(y -2,x) != Vec3b(255,255,255)){
	  image.at<Vec3b>(y-1,x) = Vec3b(B,G,R);
	}      
	if(back_image.at<Vec3b>(y+1,x) == Vec3b(0,0,0) || back_image.at<Vec3b>(y +2,x) != Vec3b(255,255,255)){
	  image.at<Vec3b>(y+1,x) = Vec3b(B,G,R);
	}      
      }
    }
    fill = 0;
  }
}


//6.4-----------------------draw and color a polygon--------------------------------
void draw_color_polygon_from_im_to_im(Mat &image,Mat &back_image, int mat_point[][2], int mat_size, int B, int G, int R, string operation_type){

  //draw polygons in both image
  draw_polygon_line(image, mat_point, mat_size);
  draw_polygon_line(back_image, mat_point, mat_size);

  //color the real image according to the polygon image
  if(operation_type == "i"){
  color_scan_line_im_to_im(image, back_image, mat_point, mat_size, B, G, R);
  }
  else if(operation_type == "u"){
    color_union_scan_line_im_to_im(image, back_image, mat_point, mat_size, 0, 0, 255);
  }
}
  
//6.----------------Union and intersect operation-------------------------------------------

void two_polygons_operation(string filename, string operation_type){

    Mat image(1000, 1000, CV_8UC3);//the final image of 2 polygons
    Mat polygon_1(1000, 1000, CV_8UC3);//first polygon accd to least_y
    Mat polygon_2(1000, 1000, CV_8UC3);//second polygon according to y then x
    color_whole_pict(image,255,255,255);
    color_whole_pict(polygon_1,255,255,255);
    color_whole_pict(polygon_2,255,255,255);

    //seperate points into two polygons
    //count number of points of each polygon
    Polygons_info polygons_info = count_points_2polygon(filename);
    // cout << "number_points_polygon1 = "<< polygons_info.number_points_polygon1 << endl;
    // cout << "number_points_polygon2 = "<< polygons_info.number_points_polygon2 << endl;
    // cout << "polygons_info.bgr_polygon1.r = "<< polygons_info.bgr_polygon1.r << endl;
    // cout << "polygons_info.bgr_polygon1.g = "<< polygons_info.bgr_polygon1.g << endl;
    // cout << "polygons_info.bgr_polygon1.b = "<< polygons_info.bgr_polygon1.b << endl;
    // cout << "polygons_info.bgr_polygon2.r = "<< polygons_info.bgr_polygon2.r << endl;
    // cout << "polygons_info.bgr_polygon2.g = "<< polygons_info.bgr_polygon2.g << endl;
    // cout << "polygons_info.bgr_polygon2.b = "<< polygons_info.bgr_polygon2.b << endl;

    // create arrays of both polygon points
    int input_1[polygons_info.number_points_polygon1][2];
    int input_2[polygons_info.number_points_polygon2][2];
    
    //get input arrays size
    const int size_input1 = sizeof(input_1)/(2*sizeof(input_1[0][0]));
    const int size_input2 = sizeof(input_2)/(2*sizeof(input_2[0][0]));
    cout << "size in 1 = " << size_input1 << endl;
    cout << "size in 2 = " << size_input2 << endl;

    //input points to array
    input_point_from_text_2polygons(input_1, size_input1, input_2, size_input2, filename);

    //Determine front and rear polygons according to least x of both
    Limitpoints limits1 = get_limitpoints_polygon(input_1, size_input1);
    Limitpoints limits2 = get_limitpoints_polygon(input_2, size_input2);
    int front;
    if (limits1.least_x < limits2.least_x){front = 1;}
    else {front = 2;}
    
    //color with scan line according to each own image with the sequence of rear then front

    if(front == 1 && operation_type == "i"){
      draw_color_polygon_from_im_to_im(image, polygon_2, input_2, size_input2, polygons_info.bgr_polygon1.b, polygons_info.bgr_polygon2.g, polygons_info.bgr_polygon2.r, "i");
      draw_color_polygon_from_im_to_im(image, polygon_1, input_1, size_input1, polygons_info.bgr_polygon1.b, polygons_info.bgr_polygon1.g, polygons_info.bgr_polygon1.r, "i");
    }
    else if(front == 2 && operation_type == "i"){
      draw_color_polygon_from_im_to_im(image, polygon_1, input_1, size_input1, polygons_info.bgr_polygon1.b, polygons_info.bgr_polygon1.g, polygons_info.bgr_polygon1.r, "i");
      draw_color_polygon_from_im_to_im(image, polygon_2, input_2, size_input2, polygons_info.bgr_polygon1.b, polygons_info.bgr_polygon2.g, polygons_info.bgr_polygon2.r, "i");
    }

    if(front == 1 && operation_type == "u"){
      draw_color_polygon_from_im_to_im(image, polygon_2, input_2, size_input2, 0, 0, 255, "u");
      draw_color_polygon_from_im_to_im(image, polygon_1, input_1, size_input1, 0, 0, 255, "u");
    }
    else if(front == 2 && operation_type == "u"){
      draw_color_polygon_from_im_to_im(image, polygon_1, input_1, size_input1, 0, 0, 255, "u");
      draw_color_polygon_from_im_to_im(image, polygon_2, input_2, size_input2, 0, 0, 255, "u");
    }

    //imshow
    namedWindow("figure", WINDOW_AUTOSIZE);
    imshow("figure",image);
}



////////--------------------------------------------------------------------------Main-----------------------------------------------------------------------//////////


int main(){

  string filename = "Input-2.txt";

  //return the head of the file, "T" or "P"
  string first_line = get_first_line(filename);
  
  //Determine the process from T and P 
  if(first_line == "P"){
    
    Mat image(1000, 1000, CV_8UC3); //B,G,R
    color_whole_pict(image,255,255,255); //color whole pict to be white
    
    //input from file
    ifstream inFile;
    inFile.open(filename.c_str());
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
    input_point_from_text(input,filename, size_input);
    
    
    //draw polygon by connecting points
    draw_polygon_line(image,input, size_input);
    
    //color the polygon
    color_polygon(image,input,size_input);

    namedWindow("figure", WINDOW_AUTOSIZE);
    imshow("figure",image);


  }//Closed bracket for P function
  else if(first_line == "T"){

    two_polygons_operation(filename, "u");
  }
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
