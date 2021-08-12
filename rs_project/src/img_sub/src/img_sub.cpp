#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"
#include "image_transport/image_transport.h"
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int16_t depth_value = 0;
//const sensor_msgs::CameraInfoConstPtr &info_msg
void ImageCallback(const sensor_msgs::Image::ConstPtr &img){
    cv_bridge::CvImagePtr cv_ptr;

    try {
      cv_ptr = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::BGR8);
    } catch (cv_bridge::Exception &e) {
      ROS_ERROR("Error to convert!");
      return;
    }

    Mat rs_img = cv_ptr->image.clone();
    Mat img_houghC;
    //rs_img.copyTo(img_houghC);

    cvtColor(rs_img,img_houghC,CV_RGB2GRAY);

    //이미지 블러 처리
    //medianBlur(img_houghC,img_houghC,5);

    //vector 데이터 3개 저장 - x,y,r
    vector<Vec3f> circles;
    //parmeter - dp=1(이미지 해상도), min_dist(선택된 원들의 최소 중심거리), threshold,
    HoughCircles(img_houghC, circles, HOUGH_GRADIENT, 1, 30, 150, 20, 0, 50);

    for (size_t i = 0; i < circles.size(); i++)
        {
            Vec3i c = circles[i];
            Point center(c[0], c[1]);
            int radius = c[2];

            circle(img_houghC, center, radius, Scalar(0, 255, 0), 2);
            circle(img_houghC, center, 2, Scalar(0, 0, 255), 3);
        }


    cv::imshow("Image show2", img_houghC);
    cv::waitKey(1);

}
//void callback(const sensor_msgs::CameraInfoConstPtr &info_msg){
void callback(const sensor_msgs::Image::ConstPtr &img){
    //rs2_intrinsics info;
    //info.
    //rs2::pointcloud pc;
    //cout<< info.wid<<endl;
    cv_bridge::CvImagePtr cv_ptr;

    try {
      cv_ptr = cv_bridge::toCvCopy(img, sensor_msgs::image_encodings::TYPE_16UC1);
    } catch (cv_bridge::Exception &e) {
      ROS_ERROR("Error to convert!");
      return;
    }

    Mat rs_img = cv_ptr->image.clone();
    depth_value = rs_img.at<unsigned int>(240,120);
    cv::imshow("Image show1", rs_img);
    cv::waitKey(1);
    cout<< depth_value<<endl;
}

//camera/color/image_raw 토픽이름 따올거
int main(int argc, char **argv)
{
    ros::init(argc, argv, "img_sub");
    ros::NodeHandle nh;
    //realsense 부분ｒ（
    ros::Subscriber rs = nh.subscribe("/camera/color/image_raw", 1, ImageCallback);
    //ros::Subscriber rs = nh.subscribe("/camera/color/camera_info", 1, callback);
    //ros::Subscriber rs2 = nh.subscribe("/camera/aligned_depth_to_color/image_raw", 1, callback);
    cout<< "gp"<<endl;

    //ROS_INFO("%f %f", width, height);

    ros::spin();

    return 0;
}
