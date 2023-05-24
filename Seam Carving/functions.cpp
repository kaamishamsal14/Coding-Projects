#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

// TODO Write this function
int energy(const Pixel *const*image, int col, int row, int width, int height)
{
  int r_top = 0, col_l = 0, col_r = 0, r_bot = 0, total = 0, red = 0, green = 0, blue = 0;

  r_top = row - 1;
  r_bot = row + 1;
  col_r = col + 1;
  col_l = col - 1;

  if (col_l < 0) {
    col_l = width - 1;
  }
  if (col_r == width){
    col_r = 0;
  }
  if (r_top < 0) {
    r_top = height - 1;
  }
  if (r_bot == height) {
    r_bot = 0;
  }

  red = image[col_r][row].r - image[col_l][row].r;
  green = image[col_r][row].g - image[col_l][row].g;
  blue = image[col_r][row].b - image[col_l][row].b;
  total = (red*red) + (blue*blue) + (green*green);

  red = image[col][r_top].r - image[col][r_bot].r;
  green = image[col][r_top].g - image[col][r_bot].g;
  blue = image[col][r_top].b - image[col][r_bot].b;
  total += (red*red) + (blue*blue) + (green*green);

  return total;
}

// TODO Write this function
int getVerticalSeam(const Pixel *const*image, int start_col, int width, int height, int* seam)
{
  int l = 0, r = 0, c = 0, energy_l = 0, energy_r = 0, energy_c = 0;
  int energy_total = energy(image, start_col, 0, width, height);
  int col = start_col;
  seam[0] = start_col;

  for (int i = 1; i < height; i++) {
    l = col - 1;
    r = col + 1;
    c = col;

    if (l < 0){
      l = c;
    }
    if (r == width) {
      r = c;
    }
    energy_l = energy(image, l, i, width, height);
    energy_r = energy(image, r, i, width, height);
    energy_c = energy(image, c, i, width, height);

    if (energy_c <= energy_r && energy_c <= energy_l) {
      seam[i] = c;
      col = c;
      energy_total += energy_c;
    }
    if (energy_r < energy_c && energy_r <= energy_l) {
      seam[i] = r;
      col = r;
      energy_total += energy_r;
    }
    if (energy_l < energy_c && energy_l < energy_r) {
      seam[i] = l;
      col = l;
      energy_total += energy_l;
    }
  }
  return energy_total;
}

// TODO Write this function
void removeVerticalSeam(Pixel **image, int& width, int height, int *verticalSeam)
{
  for (int x = 0; x<height; x++) {

    for (int a = verticalSeam[x]; a < width - 1; a++) {
      image[a][x] = image[a + 1][x];
    }
  }
  width = width - 1;
}

// TODO Write this function for extra credit
int getHorizontalSeam(const Pixel *const*image, int start_row, int width, int height, int* seam)
{
  int energy_c = 0, energy_r = 0, energy_l = 0, c = 0, r = 0, l = 0;
  int row = start_row;
  seam[0] = start_row;
  int total_energy = energy(image, 0, start_row, width, height);
  
  for (int k = 1; k < width; k++){
    c = row;
    l = row - 1;
    r = row + 1;
    
    if (row == 0) {
      l = c;
    }
    if (row == (height-1)) {
      r = c;
    }
    energy_c = energy(image, k, c, width, height);
    energy_r = energy(image, k, r, width, height);
    energy_l = energy(image, k, l, width, height);

    if (energy_c <= energy_r && energy_c <= energy_l) {
      seam[k] = c;
      total_energy += energy_c;
      row = c;
    }
    else if (energy_r < energy_l && energy_r < energy_c) {
      seam[k] = r;
      total_energy += energy_r;
      row = r;
    }
    else if (energy_l <= energy_r && energy_l < energy_c) {
      seam[k] = l;
      total_energy += energy_l;
      row = l;
    }
  }

  return total_energy;
}

// TODO Write this function for extra credit
void removeHorizontalSeam(Pixel **image, int width, int& height, int *horizontalSeam)
{
  int i = 0;
  int k = 0;

  while (k < width) {
    for (i = horizontalSeam[k]; i < height-1; i++) {
      image[k][i] = image[k][i+1];
    }
    k++;
  }
  height --;
}

int *findMinVerticalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first col (index 0)
  int *minSeam = new int[height]{0};
  int minDist = getVerticalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[height]{0};
  int candidateDistance = -1; // invalid distance

  // start at second col (index 1) since we initialized with first col (index 0)
  for (int col = 1; col < width; ++col)
  {
    candidateDistance = getVerticalSeam(image, col, width, height, candidateSeam);

    if (candidateDistance < minDist)
    { // new min
      //  swap min & candidate
      minDist = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }
  

  // clean up 
  delete [] candidateSeam;

  return minSeam;
}

int *findMinHorizontalSeam(const Pixel *const*image, int width, int height)
{
  // initialize minSeam and minDistance to seam starting at first row (index 0)
  int *minSeam = new int[width]{0};
  int minDistance = getHorizontalSeam(image, 0, width, height, minSeam);

  int *candidateSeam = new int[width]{0};
  int candidateDistance = -1; // invalid distance

  // start at second row (index 1) since we initialized with first row (index 0)
  for (int row = 1; row < height; ++row)
  {
    candidateDistance = getHorizontalSeam(image, row, width, height, candidateSeam);

    if (candidateDistance < minDistance)
    { // new minimum
      //  swap min and candidate seams
      minDistance = candidateDistance;
      int* temp = candidateSeam;
      candidateSeam = minSeam;
      minSeam = temp;
    }
  }

    // clean up 
  delete [] candidateSeam;

  return minSeam;
}

Pixel **createImage(int width, int height)
{
  cout << "Start createImage... " << endl;

  // Create a one dimensional array on the heap of pointers to Pixels
  //    that has width elements (i.e. the number of columns)
  Pixel **image = new Pixel *[width] {}; // initializes to nullptr

  for (int col = 0; col < width; ++col)
  { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    try
    {
      image[col] = new Pixel[height];
    }
    catch (std::bad_alloc &e)
    {
      // clean up already allocated arrays
      for (int i = 0; i < col; ++i)
      {
        delete[] image[i];
      }
      delete[] image;
      // rethrow
      throw e;
    }
  }

  // initialize cells
  // cout << "Initializing cells..." << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = {0, 0, 0};
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel **image, int width)
{
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i = 0; i < width; ++i)
  {
    delete[] image[i];
  }
  delete[] image;
  image = nullptr;
  cout << "End deleteImage..." << endl;
}

bool isValidColor(int colorVal)
{
  if (colorVal < 0 || colorVal > 255)
  {
    return false;
  }
  return true;
}

Pixel ** loadImage(string filename, int &width, int &height)
{
  cout << "Start loadImage..." << endl;
  // remove
  ifstream ifs(filename);
  if (!ifs.is_open())
  {
    throw std::invalid_argument("Failed to open input file (" + filename + ")");
  }

  string type;
  ifs >> type; // should be P3
  if (toupper(type.at(0)) != 'P' || type.at(1) != '3')
  {
    throw std::domain_error("Not PPM type P3 (" + type + ")");
  }
  ifs >> width;
  // cout << "w and h: " << w << " " << h << endl;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for width");
  }
  if (width <= 0)
  {
    ostringstream oss;
    oss << "Width in file must be greater than 0 (" << width << ")";
    throw std::domain_error(oss.str());
  }

  ifs >> height;
  if (ifs.fail())
  {
    cout << "Read non-integer value for height" << endl;
  }
  if (height <= 0)
  {
    ostringstream oss;
    oss << "Height in file must be greater than 0 (" << height << ")";
    throw std::domain_error(oss.str());
  }

  int colorMax = 0;
  ifs >> colorMax;
  if (ifs.fail())
  {
    throw std::domain_error("Read non-integer value for max color value");
  }
  if (colorMax != 255)
  {
    ostringstream oss;
    oss << "Max color value must be 255 (" << colorMax << ")";
    throw std::domain_error(oss.str());
  }

  // load image throws exceptions but we will let them pass through
  Pixel **image = createImage(width, height);

  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      // cout << "Pixel(" << col << ", " << row << ")" << endl;
      ifs >> image[col][row].r;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for red");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for red (" << image[col][row].r << ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].g;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for green");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for green (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }

      ifs >> image[col][row].b;
      if (ifs.fail() && !ifs.eof())
      { // bad input that is not caused by being at the end of the file
        throw std::domain_error("Read non-integer value for blue");
      }
      if (!isValidColor(image[col][row].r))
      {
        ostringstream oss;
        oss << "Invalid color value for blue (" << image[col][row].r + ")";
        throw std::domain_error(oss.str());
      }
    }
  }
  cout << "End loadImage..." << endl;
  return image;
}

void outputImage(string filename, const Pixel *const *image, int width, int height)
{
  cout << "Start outputImage..." << endl;
  // remove code
  // declare/define and open output file stream with filename
  ofstream ofs(filename);
  // ensure file is open
  if (!ofs.is_open())
  {
    throw std::invalid_argument("Error: failed to open output file - " + filename);
  }
  ofs << "P3" << endl;
  ofs << width << " " << height << endl;
  ofs << 255 << endl;
  for (int row = 0; row < height; ++row)
  {
    for (int col = 0; col < width; ++col)
    {
      ofs << image[col][row].r << " ";
      ofs << image[col][row].g << " ";
      ofs << image[col][row].b << " ";
    }
    ofs << endl;
  }
  cout << "End outputImage..." << endl;
}