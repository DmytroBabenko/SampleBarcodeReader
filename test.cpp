#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <cmath>
#include <iostream>

// find a cos angle between vectors
static double   angle(cv::Point pt1, cv::Point pt2, cv::Point pt0) {
    double  dx1 = pt1.x - pt0.x;
    double  dy1 = pt1.y - pt0.y;
    double  dx2 = pt2.x - pt0.x;
    double  dy2 = pt2.y - pt0.y;
    return (dx1 * dx2) / sqrt((dx1 * dx1 + dy1 * dy1) * (dx2 * dx2 + dy2 * dy2) + 1e-10);
}


/**
 * Helper function to display text in the center of a contour
*/
void setLabel(cv::Mat& im, const std::string label, std::vector<cv::Point>& contour)
{
    int fontface = cv::FONT_HERSHEY_TRIPLEX;
    double scale = 0.4;
    int thickness = 1;
    int baseline = 0;

    cv::Size text = cv::getTextSize(label, fontface, scale, thickness, &baseline);
    cv::Rect r = cv::boundingRect(contour);

    cv::Point pt(r.x + ((r.width - text.width) / 2), r.y + ((r.height + text.height) / 2));
    cv::rectangle(im, pt + cv::Point(0, baseline), pt + cv::Point(text.width, -text.height), CV_RGB(255,255,255), CV_FILLED);
    cv::putText(im, label, pt, fontface, scale, CV_RGB(0,0,0), thickness, 8);
}

int     main(int argc, char *argv[]) {
    cv::VideoCapture    capture(0);
    // cv::Mat src = cv::imread("assets/s-l300.jpg");
    cv::Mat         src;

    while(cv::waitKey(30) != 'q')
    {
        capture >> src;
        if (true) {
            
            if (src.empty()) {
                std::cout << "No image loaded" << std::endl;
                return -1;
            }

            //convert to grayscale
            cv::Mat gray;
            cv::cvtColor(src, gray, CV_BGR2GRAY);

            //use Canny instead of thresold to catch squares with gradient shading
            cv::Mat bw;
            cv::Canny(gray, bw, 50, 5);
            cv::imshow("bw", bw);

            //find contours
            std::vector<std::vector<cv::Point> > contours;
            cv::findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

            std::vector<cv::Point>  approx;
            cv::Mat dst = src.clone();

            for (int i = 0; i < contours.size(); i++) {
                //approximate contour with accuracy proportional to the contour perimeter
                cv::approxPolyDP(cv::Mat(contours[i]), approx, cv::arcLength(cv::Mat(contours[i]), true) * 0.02, true);

                //skip small or non-convex objects
                if (std::fabs(cv::contourArea(contours[i])) < 100 || !cv::isContourConvex(approx))
                    continue;

                if (approx.size() == 3) {
                    setLabel(dst, "TRI", contours[i]);    // Triangles
                }
                else if (approx.size() >=4 && approx.size() <=6) {
                    // Number of vertices of polygonal curve
                    int vtc = approx.size();
                    
                    // Get the cosines of all corners
                    std::vector<double> cos;
                    for (int j = 2; j < vtc+1; j++)
                        cos.push_back(angle(approx[j%vtc], approx[j-2], approx[j-1]));

                    // Sort ascending the cosine values
                    std::sort(cos.begin(), cos.end());

                    // Get the lowest and the highest cosine
                    double mincos = cos.front();
                    double maxcos = cos.back();

                    // Use the degrees obtained above and the number of vertices
                    // to determine the shape of the contour
                    if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
                        setLabel(dst, "RECT", contours[i]);
                    else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27)
                        setLabel(dst, "PENTA", contours[i]);
                    else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45)
                        setLabel(dst, "HEXA", contours[i]);
                }
                else
                {
                    // Detect and label circles
                    double area = cv::contourArea(contours[i]);
                    cv::Rect r = cv::boundingRect(contours[i]);
                    int radius = r.width / 2;

                    if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
                        std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)
                        setLabel(dst, "CIR", contours[i]);
                }
            }
            cv::imshow("src", src);
            cv::imshow("dst", dst);
        }
        else {
            break;
        }
    }
    // cv::waitKey(0);
    return 0;
}
