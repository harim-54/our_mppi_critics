#include "our_mppi_critics/slope_critic.hpp"
#include <cmath>
#include "xtensor/xarray.hpp"
#include "xtensor/xmath.hpp"

namespace our_mppi_critics
{

void SlopeCritic::initialize()
{
  auto node = parent_.lock();

  node->declare_parameter(name_ + ".cost_power", 1);
  node->declare_parameter(name_ + ".cost_weight", 5.0f);
  node->declare_parameter(name_ + ".max_slope_deg", 30.0f);
  node->declare_parameter(name_ + ".critical_slope_deg", 25.0f);

  power_              = node->get_parameter(name_ + ".cost_power").as_int();
  weight_             = node->get_parameter(name_ + ".cost_weight").as_double();
  max_slope_deg_      = node->get_parameter(name_ + ".max_slope_deg").as_double();
  critical_slope_deg_ = node->get_parameter(name_ + ".critical_slope_deg").as_double();

  // IMU 토픽 구독
  imu_sub_ = node->create_subscription<sensor_msgs::msg::Imu>(
    "/imu", rclcpp::SensorDataQoS(),
    [this](const sensor_msgs::msg::Imu::SharedPtr msg) {
      // quaternion → pitch 변환
      const auto & q = msg->orientation;
      pitch_ = std::asin(2.0f * (q.w * q.y - q.z * q.x));
    });

  RCLCPP_INFO(logger_, "SlopeCritic instantiated with %d power and %f weight", power_, weight_);
}

void SlopeCritic::score(mppi::CriticData & data)
{
  if (!enabled_) {return;}

  const float pitch_deg = std::abs(pitch_) * 180.0f / M_PI;

  if (pitch_deg < 1.0f) {return;}

  const size_t batch_size = data.trajectories.x.shape(0);
  xt::xtensor<float, 1> cost = xt::zeros<float>({batch_size});

  if (pitch_deg >= max_slope_deg_) {
    cost = xt::ones<float>({batch_size}) * 1000.0f;
  } else if (pitch_deg >= critical_slope_deg_) {
    float ratio = (pitch_deg - critical_slope_deg_) /
      (max_slope_deg_ - critical_slope_deg_);
    cost = xt::ones<float>({batch_size}) * ratio * 100.0f;
  } else {
    float ratio = pitch_deg / critical_slope_deg_;
    cost = xt::ones<float>({batch_size}) * ratio * 10.0f;
  }

  if (power_ > 1u) {
    data.costs += xt::pow(cost * weight_, static_cast<float>(power_));
  } else {
    data.costs += cost * weight_;
  }
}

}  // namespace our_mppi_critics

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(
  our_mppi_critics::SlopeCritic,
  mppi::critics::CriticFunction)