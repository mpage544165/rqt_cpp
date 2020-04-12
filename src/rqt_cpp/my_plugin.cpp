
#include "rqt_cpp/my_plugin.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>


namespace rqt_cpp
{

  MyPlugin::MyPlugin()
    : rqt_gui_cpp::Plugin()
    , widget_(0)
  {
  // Constructor is called first before initPlugin function, needless to say.

  // give QObjects reasonable names
    setObjectName("MyPlugin");

    
  }

  void MyPlugin::initPlugin(qt_gui_cpp::PluginContext& context)
  {
    // access standalone command line arguments
    QStringList argv = context.argv();
    // create QWidget
    widget_ = new QWidget();
    // extend the widget with all attributes and children from UI file
    ui_.setupUi(widget_);
    // add widget to the user interface
    context.addWidget(widget_);

    image_transport::ImageTransport it(getNodeHandle());
    imSub = it.subscribe("/cvImage", 1, &MyPlugin::imageCallback, this);
    //imSub = it.subscribe("/ardrone/front/image_raw", 1, &MyPlugin::imageCallback, this);

    // ros::NodeHandle nh;
    // //rospy.Subscriber('/ground_truth/state', Odometry, self.print_ROSdata)
    // ros::Subscriber odomSub = nh.subscribe("/ground_truth/state", 1, &MyPlugin::odomCallback, this);
    // ROS_INFO("End of init.");

  }

  void MyPlugin::shutdownPlugin()
  {
    // unregister all publishers here
    imSub.shutdown();
  }

  void MyPlugin::saveSettings(qt_gui_cpp::Settings& plugin_settings,
      qt_gui_cpp::Settings& instance_settings) const
  {
    // instance_settings.setValue(k, v)
  }

  void MyPlugin::restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
      const qt_gui_cpp::Settings& instance_settings)
  {
    // v = instance_settings.value(k)
  }

  /*bool hasConfiguration() const
  {
    return true;
  }

  void triggerConfiguration()
  {
    // Usually used to open a dialog to offer the user a set of configuration
  }*/

  void MyPlugin::imageCallback(const sensor_msgs::Image::ConstPtr& msg){
    cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::RGB8);
    QImage image(cv_ptr->image.data, cv_ptr->image.cols, cv_ptr->image.rows, cv_ptr->image.step[0], QImage::Format_RGB888);
    ui_.label->setPixmap(QPixmap::fromImage(image));

    ROS_INFO("End of imageCallback.");
  }

    
  // //odomCallback
  // void MyPlugin::odomCallback(const nav_msgs::Odometry::ConstPtr& msg) {
  // 	ROS_INFO("Begin odomCallback");

  //   // Camera position in map frame
  //   double tx = msg->pose.pose.position.x;
  //   double ty = msg->pose.pose.position.y;
  //   double tz = msg->pose.pose.position.z;

  //   // Orientation quaternion
  //   // tf2::Quaternion q(
  //   //     msg->pose.pose.orientation.x,
  //   //     msg->pose.pose.orientation.y,
  //   //     msg->pose.pose.orientation.z,
  //   //     msg->pose.pose.orientation.w);

  //   // 3x3 Rotation matrix from quaternion
  //   // tf2::Matrix3x3 m(q);

  //   // Roll Pitch and Yaw from rotation matrix
  //   // double roll, pitch, yaw;
  //   // m.getRPY(roll, pitch, yaw);

  //   // Output the measure
  //   ROS_INFO("Received odom in '%s' frame : X: %.2f Y: %.2f Z: %.2f",
  //            msg->header.frame_id.c_str(),
  //            tx, ty, tz);


  // }

}  // namespace rqt_cpp

PLUGINLIB_DECLARE_CLASS(rqt_cpp, MyPlugin, rqt_cpp::MyPlugin, rqt_gui_cpp::Plugin)


