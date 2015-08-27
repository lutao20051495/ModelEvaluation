
#ifndef CLASSIFIER
#define CLASSIFIER

#include <caffe/caffe.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
using namespace  cv;
using namespace caffe;

typedef std::pair<string, float> Prediction;

class Classifier {
public:
	Classifier(){};
	Classifier(const string& proto_file_path,
		    const string& model_file_path,
		    const string& mean_file_path,
		    const string& label_file_path);

	vector<Prediction> Classify(const cv::Mat& img, int N = 5);
	
	vector<float> Predict(const Mat& img);

 private:
	void SetMean(const string& mean_file);

	void WrapInputLayer(std::vector<Mat>* input_channels);

	void Preprocess(const cv::Mat& img,
					std::vector<cv::Mat>* input_channels);

 private:
	shared_ptr<Net<float> > net_;
	Size input_geometry_;
	int num_channels_;
	Mat mean_;
	vector<string> labels_;
};

#endif