
#include <string>
using namespace std;

class ModelEvaluation
{
public:
	//Classifier	clf_;
	bool load_all_img;
public:
	ModelEvaluation(){};
	double calcFpr(string& neg_img_dir);
	double calcMr(string& pos_patch_dir);
};
