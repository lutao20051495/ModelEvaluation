
#include "file.h"
#include "image.h"

void loadImage(const string& dir, vector<Mat>& img_vec, const string& type)
{
	vector<string> file_name_vec;
	GetFileName(file_name_vec, dir, type);
	
	for(unsigned int i=0; i<file_name_vec.size(); i++)
	{
		string img_name = dir + "/" + file_name_vec[i];
		Mat img = imread(img_name, -1);
		img_vec.push_back(img);
	}
}


void genRandPatch(Mat& img, Mat& patch, Size& patch_size)
{
	cv::RNG rng(cv::getTickCount());
	int x1 = rng.uniform(0, img.cols);
	int y1 = rng.uniform(0, img.rows);
	int x2 = rng.uniform(0, img.cols);
	int y2 = rng.uniform(0, img.rows);
	
	Rect roi;
	if (x1<x2)
	{
		roi.x = x1;
		roi.width = x2-x1+1;
	}
	else
	{
		roi.x = x2;
		roi.width = x1-x2+1;
	}
	
	if(y1<y2)
	{
		roi.y = y1;
		roi.height = y2-y1+1;
	}
	else
	{
		roi.y = y2;
		roi.height = y1-y2+1;
	}
	patch = img(roi).clone();
	resize(patch, patch, patch_size);
	
	return;
}


void genRandPatch(Mat& img, vector<Mat>& patch_vec, Size& patch_size, int patch_num)
{
	for(int i=0; i<patch_num; i++)
	{
		Mat patch;
		genRandPatch(img, patch, patch_size);
		patch_vec.push_back(patch);
	}
	
	return;
}