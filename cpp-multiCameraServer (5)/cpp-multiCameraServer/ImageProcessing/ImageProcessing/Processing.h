#pragma once

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>

class Processing
{
public:
	Processing() {}
	cv::Mat ProcessImg(cv::Mat img);

	double m_percent;
protected:
	// Image variables
	cv::Mat m_hsv;
	cv::Mat m_kernel;
	cv::Mat m_range;
	cv::Mat m_dilate;
	cv::Mat m_contourImg;

	// Setting Variables
		//HSV
	int m_highHue = 97;
	int m_lowHue = 64;
	int m_highSat = 255;
	int m_lowSat = 208;
	int m_highVal = 255;
	int m_lowVal = 134;
		//Kernel
	int m_kernelSize = 11;

	double m_centroidX = -1;
	double m_centroidY = -1;
	cv::Point m_fullCenter;

	std::vector<std::vector<cv::Point>> m_contours;
	std::vector<cv::Vec4i> m_hierarchy;
};

