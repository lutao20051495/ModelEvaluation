
#include <vector>
using namespace std;

#include "ModelEvaluation.h"
#include "file.h"

double ModelEvaluation::calcMr(string& pos_patch_dir)
{
	vector<string> file_name_vec;
	GetFileName(file_name_vec, pos_patch_dir, "bmp");
	
}