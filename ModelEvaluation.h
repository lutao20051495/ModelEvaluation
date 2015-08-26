
#include <string>
using namespace std;

#include "Classifier.h"

class ModelEvaluation
{
public:
	Classifier	clf_;
	bool load_all_img;
	vector<float> thresh_vec_;
	int display_;
	int max_test_num_;
	bool load_all_neg_img_;
	int sample_patch_num_;
	Size patch_size_;
public:
	ModelEvaluation(){};
	float calcFpr(string& neg_img_dir);
	float calcMr(string& pos_patch_dir);
	
	bool isCorrect(vector<float>& score_vec, int label, float thresh);
	bool isCorrect(float score, int label, float thresh);
};
