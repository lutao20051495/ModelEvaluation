#include <opencv2/opencv.hpp>
using namespace cv;

void loadImage(const string& dir, vector<Mat>& img_vec, const string& type);

void genRandPatch(Mat& img, Mat& patch, Size& patch_size);

void genRandPatch(Mat& img, vector<Mat>& patch_vec, Size& patch_size, int patch_num);
