
#include <vector>
#include <string>
using namespace std;

#include "ModelEvaluation.h"
#include "file.h"
#include "image.h"

ModelEvaluation::ModelEvaluation(Classifier& clf, Size& patch_size, float thresh)
:clf_(clf), patch_size_(patch_size),thresh_(thresh)
{
	load_all_neg_img_ = false;
	sample_patch_num_ = 10;
	max_test_num_ = 100000;
	display_ = 10000;
}


bool ModelEvaluation::Positive(float score)
{
	if ( score >thresh_ )
	{
		return true;
	}
	else
	{
		return false;
	}
}

float ModelEvaluation::calcMr(const string& pos_patch_dir)
{
	vector<string> file_name_vec;
	if (!GetFileName(file_name_vec, pos_patch_dir, "bmp")
		|| file_name_vec.size()<=0)
	{
		return 0.0f;
	}
	
	int err_num = 0;
	int sum_num = 0;
	for (unsigned int i=0; i<file_name_vec.size(); i++)
	{
		string img_name = pos_patch_dir + "/" + file_name_vec[i];
		Mat img = imread(img_name,-1);
		if (!img.data)
		{
			continue;
		}
		sum_num++;
		
		vector<float> score_vec = clf_.Predict(img);
		/*
		for(int k=0; k<score_vec.size(); k++)
		{
			cout << "label " << k << "\t" << score_vec[k] << endl;
		}
		 //*/
		if (!Positive(score_vec[1]))
		{
			err_num++;
		}
		if(sum_num%display_==0)
		{
			cout << "test patch " << sum_num << "\t\t" << (float)err_num/sum_num << endl; 
		}
	}
	return (float)err_num/sum_num;
}


float ModelEvaluation::calcFpr(const string& img_dir)
{
	cv::RNG rng(cv::getTickCount());
	int test_num = 0;
	int fp_num = 0;
	if (load_all_neg_img_)
	{
		vector<Mat> img_vec;
		loadImage(img_dir, img_vec, "jpg");

		while (test_num<max_test_num_)
		{
			int img_index = rng.uniform(0, img_vec.size());
			Mat patch;
			genRandPatch(img_vec[img_index], patch, patch_size_);
			vector<float> score_vec = clf_.Predict(patch);
			if (Positive(score_vec[1]))
			{
				fp_num++;
			}
			test_num++;
			if ((test_num+1)%display_ == 0)
			{
				cout << "test patch " << test_num << "\t\t" << (float)fp_num/test_num << endl; 
			}
		}
	}
	else
	{
	    	vector<string> file_name_vec;
		if (!GetFileName(file_name_vec, img_dir, "jpg")
			|| file_name_vec.size()<=0)
		{
			return 0.0;
		}
		
		while (test_num<max_test_num_)
		{
			int img_index = rng.uniform(0, file_name_vec.size());
			string img_name = img_dir + "/" + file_name_vec[img_index];
			Mat img = imread(img_name, -1);
			if (!img.data)
			{
				continue;
			}
			vector<Mat> patch_vec;
			genRandPatch(img, patch_vec, patch_size_, sample_patch_num_);
			for (unsigned int i=0; i<sample_patch_num_; i++)
			{
				vector<float> score_vec = clf_.Predict(patch_vec[i]);
				/*
				for(int k=0; k<score_vec.size(); k++)
				{
					cout << "label " << k << "\t" << score_vec[k] << endl;
				}
				 */
				if (Positive(score_vec[1]))
				{
					//cout << "fp score: " << score_vec[1] << endl;  
					fp_num++;
				}
			}
			test_num += sample_patch_num_;
			if (test_num%display_==0)
			{
				cout << "test patch " << test_num << "\t\t" << (float)fp_num/test_num << endl; 
			}
		}
	}
	float fpr = (float)fp_num/test_num;
	return fpr;
}


