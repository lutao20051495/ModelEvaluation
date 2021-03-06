
#include <caffe/caffe.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
using namespace  cv;
using namespace caffe;

class Classifier {
 public:
	Classifier(const string& model_file,
		    const string& trained_file,
		    const string& mean_file,
		    const string& label_file);
/*
	vector<Prediction> Classify(const cv::Mat& img, int N = 5);
*/
 private:
	void SetMean(const string& mean_file);
/*
	vector<float> Predict(const Mat& img);

	void WrapInputLayer(std::vector<Mat>* input_channels);

	void Preprocess(const cv::Mat& img,
					std::vector<cv::Mat>* input_channels);
*/
 private:
	shared_ptr<Net<float> > net_;
	Size input_geometry_;
	int num_channels_;
	Mat mean_;
	vector<string> labels_;
};