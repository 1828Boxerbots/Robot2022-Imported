//// ImageProcessing.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include "Processing.h"

//
//int highHue = 97;
//int lowHue = 64;
//int highSat = 255;
//int lowSat = 208;
//int highVal = 255;
//int lowVal = 134;
//
//int brightness = 0;
//int contrast = 100;
//double realCon = 1.0;
//
//int kernelSize = 11;
//
//void DisplayImage(std::string windowName, cv::Mat image)
//{
//    cv::imshow(windowName, image);
//}
//
//cv::Mat ProcessImg(cv::Mat img)
//{
//    int height = img.cols;
//    int width = img.rows;
//
//    /*cv::line(img, cv::Point(0, 0), cv::Point(height, width), cv::Scalar(255, 0, 0), 3);
//    cv::line(img, cv::Point(0, width), cv::Point(height, 0), cv::Scalar(255, 0, 0), 3);
//
//    cv::line(img, cv::Point(0, width / 2), cv::Point(height, width/2), cv::Scalar(0, 0, 255), 3);
//    cv::line(img, cv::Point(height / 2, 0), cv::Point(height / 2, width), cv::Scalar(0, 0, 255), 3);*/
//
//    // HSV
//    cv::Mat hsv;
//    cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);
//    //DisplayImage("HSV", hsv);
//
//    // KERNEL
//    cv::Mat kernel;
//    kernel = cv::Mat::ones(cv::Size(kernelSize, kernelSize), cv::MORPH_DILATE);
//
//    // IN_RANGE
//    cv::Scalar lowValue = cv::Scalar(lowHue, lowSat, lowVal);
//    cv::Scalar highValue = cv::Scalar(highHue, highSat, highVal);
//    cv::Mat range;
//    cv::inRange(hsv, lowValue, highValue, range);
//
//    // ERODE / DIALATE
//    //cv::Mat rode;
//    //cv::erode(range, rode, kernel);
//    ////DisplayImage("Erode", rode);
//    //cv::Mat dila;
//    //cv::dilate(range, dila, kernel);
//    ////DisplayImage("Dilate", dila);
//    //cv::Mat open;
//    //cv::morphologyEx(range, open, cv::MORPH_OPEN, kernel);
//    ////DisplayImage("Open", open);
//    //cv::Mat close;
//    //cv::morphologyEx(range, close, cv::MORPH_CLOSE, kernel);
//    ////DisplayImage("Close", close);
//
//    //Contours
//    std::vector<std::vector<cv::Point>> contours;
//    std::vector<cv::Vec4i> hierarchy;
//    //cv::threshold(range, range, 180, 255, cv::THRESH_BINARY);
//    cv::Mat cannyImg;
//    //cv::Canny(range, cannyImg, 0, 0);
//
//    cv::Mat rode, dil;
//    //cv::erode(range, rode, kernel);
//    cv::dilate(range, dil, kernel);
//
//    DisplayImage("Thresh", dil);
//
//    cv::findContours(dil, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
//
//    //std::vector<cv::Point2f> centroid(contours.size());
//    double centroidX = -1;
//    double centroidY = -1;
//    double highestArea = -1;
//    int count = -1;
//    cv::Mat contoursIMG = cv::Mat::zeros(range.rows, range.cols, CV_8UC3);
//
//    //for (int i = 0; i < contours.size(); i++)
//    //{
//    //    double area = cv::contourArea(contours[i]);
//
//    //    if (area > highestArea)
//    //    {
//    //        highestArea = area;
//    //        count = i;
//    //    }
//    //}
//
//    //if (count > 0)
//    //{
//    //    cv::Rect boundRect = cv::boundingRect(contours[count]);
//    //    centroidX = boundRect.x + (double)(boundRect.width / 2);
//    //    centroidY = boundRect.y + (double)(boundRect.height / 2);
//
//    //    cv::line(contoursIMG, cv::Point(centroidX, centroidY - boundRect.height / 2), cv::Point(centroidX, centroidY + boundRect.height / 2), cv::Scalar(255, 0, 0));
//    //    cv::line(contoursIMG, cv::Point(centroidX - boundRect.width / 2, centroidY), cv::Point(centroidX + boundRect.height / 2, centroidY), cv::Scalar(255, 0, 0));
//
//    //    //square
//    //    cv::Scalar color(0, 255, 0);
//    //    cv::Point topLeft(centroidX - (boundRect.width / 2), centroidY + boundRect.height / 2);
//    //    cv::Point topRight(centroidX + (boundRect.width / 2), centroidY + (boundRect.height / 2));
//    //    cv::Point bottomLeft(centroidX - (boundRect.width / 2), centroidY - (boundRect.height / 2));
//    //    cv::Point bottomRight(centroidX + (boundRect.width / 2), centroidY - (boundRect.height / 2));
//    //    cv::line(contoursIMG, topLeft, topRight, color, 3);
//    //    cv::line(contoursIMG, topLeft, bottomLeft, color, 3);
//    //    cv::line(contoursIMG, bottomLeft, bottomRight, color, 3);
//    //    cv::line(contoursIMG, bottomRight, topRight, color, 3);
//
//    //    cv::drawContours(contoursIMG, contours, count, cv::Scalar(255, 0, 0), 2);
//    //}
//    //else
//    //{
//    //    contoursIMG = range;
//    //}
//
//    for (int i = 0; i < contours.size(); i++)
//    {
//        cv::Rect boundRect = cv::boundingRect(contours[i]);
//
//        centroidX = boundRect.x + (double)(boundRect.width / 2);
//        centroidY = boundRect.y + (double)(boundRect.height / 2);
//
//        //cross
//        cv::line(contoursIMG, cv::Point(centroidX, centroidY - boundRect.height / 2), cv::Point(centroidX, centroidY + boundRect.height / 2), cv::Scalar(255, 0, 0));
//        cv::line(contoursIMG, cv::Point(centroidX - boundRect.width / 2, centroidY), cv::Point(centroidX + boundRect.height / 2, centroidY), cv::Scalar(255, 0, 0));
//
//        //square
//        cv::Scalar color(0, 255, 0);
//        cv::Point topLeft(centroidX - (boundRect.width / 2), centroidY + boundRect.height / 2);
//        cv::Point topRight(centroidX + (boundRect.width / 2), centroidY + (boundRect.height / 2));
//        cv::Point bottomLeft(centroidX - (boundRect.width / 2), centroidY - (boundRect.height / 2));
//        cv::Point bottomRight(centroidX + (boundRect.width / 2), centroidY - (boundRect.height / 2));
//        cv::line(contoursIMG, topLeft, topRight, color, 3);
//        cv::line(contoursIMG, topLeft, bottomLeft, color, 3);
//        cv::line(contoursIMG, bottomLeft, bottomRight, color, 3);
//        cv::line(contoursIMG, bottomRight, topRight, color, 3);
//
//        //if(!isnan(centroidX) || !isnan(centroidY))
//        cv::drawContours(contoursIMG, contours, i, cv::Scalar(255, 0, 0), 2);
//    }
//    cv::Moments moms = cv::moments(dil, true);
//    if (moms.m00 != 0)
//    {
//        cv::Point center = cv::Point2f(moms.m10 / moms.m00, moms.m01 / moms.m00);
//
//        cv::line(contoursIMG, cv::Point(center.x, 0), cv::Point(center.x, contoursIMG.cols), cv::Scalar(0, 0, 255));
//        cv::line(contoursIMG, cv::Point(0, center.y), cv::Point(contoursIMG.cols, center.y), cv::Scalar(0, 0, 255));
//    }
//    return contoursIMG;
//}
//
//cv::Mat ChangeBrightnessContrast(cv::Mat img)
//{
//    cv::Mat newImg = cv::Mat::zeros(img.size(), img.type());
//    realCon = double(contrast) / 100.0;
//    std::cout << realCon << "\n";
//    for (int y = 0; y < img.rows; y++) 
//    {
//        for (int x = 0; x < img.cols; x++) 
//        {
//            for (int c = 0; c < img.channels(); c++) 
//            {
//                newImg.at<cv::Vec3b>(y, x)[c] =
//                    cv::saturate_cast<uchar>(realCon * img.at<cv::Vec3b>(y, x)[c] + brightness);
//            }
//        }
//    }
//
//    return newImg;
//}
//
int main()
{
    Processing processing;
    cv::VideoCapture cam(0);
    cv::Mat img;
    while (true)
    {
        cam.read(img);
        cv::imshow("window", img);
    }
}
//
//// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
//// Debug program: F5 or Debug > Start Debugging menu
//
//// Tips for Getting Started: 
////   1. Use the Solution Explorer window to add/manage files
////   2. Use the Team Explorer window to connect to source control
////   3. Use the Output window to see build output and other messages
////   4. Use the Error List window to view errors
////   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
////   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
