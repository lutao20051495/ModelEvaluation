
#include <string>
using namespace std;

#include "Classifier.h"

class ModelEvaluation
{
public:
	Classifier&	clf_;
	float thresh_;
	int display_;
	int max_test_num_;
	bool load_all_neg_img_;
	int sample_patch_num_;
	Size patch_size_;
public:
	ModelEvaluation(Classifier& clf, Size& patch_size, float thresh);
	float calcFpr(const string& neg_img_dir);
	float calcMr(const string& pos_patch_dir);
	
	bool Positive(float score);
};
