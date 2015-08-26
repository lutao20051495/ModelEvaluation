
#include <vector>
#include <string>
using namespace std;

#include "ModelEvaluation.h"
#include "file.h"


bool ModelEvaluation::isCorrect(vector<float>& score_vec, int label, float thresh)
{
	if (score_vec[label]>thresh)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool ModelEvaluation::isCorrect(float score, int label, float thresh)
{
	if ( (label&&(score>thresh))
		|| (!label&&((1-score)>=thresh)) )
	    {
		    return true;
	    }
	    else
	    {
		    return false;
	    }
}

float ModelEvaluation::calcMr(string& pos_patch_dir)
{
	vector<string> file_name_vec;
	GetFileName(file_name_vec, pos_patch_dir, "bmp");
	
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
		if (!isCorrect(score_vec, 1, thresh_vec_[1]))
		{
			err_num++;
		}
	}
	return (float)err_num/sum_num;
}


