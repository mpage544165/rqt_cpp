
#include "rqt_cpp/my_plugin.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>

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
  }

}  // namespace rqt_example_cpp
PLUGINLIB_DECLARE_CLASS(rqt_cpp, MyPlugin, rqt_cpp::MyPlugin, rqt_gui_cpp::Plugin)


