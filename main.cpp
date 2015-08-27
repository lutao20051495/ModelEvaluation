#include <stdio.h>
#include "ModelEvaluation.h"
#include "Classifier.h"

void evaluate( const string& proto_file_path, 
		const string& model_file_path,
		const string& mean_file_path,
		const string& label_file_path,
		const string& dir, int option);

int main(int argc, char **argv)
{
	if(argc <= 2)
	{
		return 0;
	}
	int option = atoi(argv[1]);
	switch(option)
	{
	    case 0:
	    {
		    evaluate(string(argv[2]), string(argv[3]), string(argv[4]), string(argv[5]),
					string(argv[5]), atoi(argv[3]));
		    break;
	    }
	    default:
	    {
		    cout << "error option" << endl;
	    }
	}
}

void evaluate( const string& proto_file_path, 
		const string& model_file_path,
		const string& mean_file_path,
		const string& label_file_path,
		const string& dir, int option)
{

	Classifier clf(proto_file_path, model_file_path, mean_file_path, label_file_path);
	Size patch_size(48,48);
	vector<float> thresh_vec(2);
	thresh_vec[1] = 0.5;
	thresh_vec[0] = 0.5;
		
	ModelEvaluation model_evl(clf, patch_size, thresh_vec);
	
	if(option == 0)
	{
		float mr = model_evl.calcMr(dir);
		cout << "mr:\t" << mr << endl;
	}
	else if(option == 1)
	{
		float fpr = model_evl.calcFpr(dir);
		cout << "fpr:\t" << fpr << endl;
	}
	return;
}



