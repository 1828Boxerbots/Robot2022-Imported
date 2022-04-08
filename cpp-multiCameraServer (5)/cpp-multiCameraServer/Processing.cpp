#include "Processing.h"

cv::Mat Processing::ProcessImg(cv::Mat img)
{
	// Convert to HSV
	cv::cvtColor(img, m_hsv, cv::COLOR_BGR2HSV);
	// Create kernel
	m_kernel = cv::Mat::ones(cv::Size(m_kernelSize, m_kernelSize), cv::MORPH_DILATE);
	// InRange
	cv::Scalar lowValue(m_lowHue, m_lowSat, m_lowVal);
	cv::Scalar highValue(m_highHue, m_highSat, m_highVal);
	cv::inRange(m_hsv, lowValue, highValue, m_range);
	// Dilate
	cv::dilate(m_range, m_dilate, m_kernel);
	// contours
	cv::findContours(m_dilate, m_contours, m_hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
	m_contourImg = cv::Mat::zeros(m_range.rows, m_range.cols, CV_8UC3);
	// loop through all contours
	for (int i = 0; i < m_contours.size(); i++)
	{
		cv::Rect boundRect = cv::boundingRect(m_contours[i]);
		m_centroidX = boundRect.x + (double)(boundRect.width / 2);
		m_centroidX = boundRect.y + (double)(boundRect.height / 2);
		//sqaure around contours
		cv::Scalar color(0, 255, 0);
		cv::Point topLeft(m_centroidX - (boundRect.width / 2), m_centroidY + boundRect.height / 2);
		cv::Point topRight(m_centroidX + (boundRect.width / 2), m_centroidY + (boundRect.height / 2));
		cv::Point bottomLeft(m_centroidX - (boundRect.width / 2), m_centroidY - (boundRect.height / 2));
		cv::Point bottomRight(m_centroidX + (boundRect.width / 2), m_centroidY - (boundRect.height / 2));
		cv::line(m_contourImg, topLeft, topRight, color, 3);
		cv::line(m_contourImg, topLeft, bottomLeft, color, 3);
		cv::line(m_contourImg, bottomLeft, bottomRight, color, 3);
		cv::line(m_contourImg, bottomRight, topRight, color, 3);
		// draw contours
		cv::drawContours(m_contourImg, m_contours, i, cv::Scalar(255, 0, 0));
	}
	// Center of all images
	cv::Moments moms = cv::moments(m_dilate, true);
	if (moms.m00 != 0)
	{
		m_fullCenter = cv::Point2f(moms.m10 / moms.m00, moms.m01 / moms.m00);
		cv::line(m_contourImg, cv::Point(m_fullCenter.x, 0), cv::Point(m_fullCenter.x, m_contourImg.cols), cv::Scalar(0, 0, 255));
		cv::line(m_contourImg, cv::Point(0, m_fullCenter.y), cv::Point(m_contourImg.cols, m_fullCenter.y), cv::Scalar(0, 0, 255));
	}
	return m_contourImg;
}