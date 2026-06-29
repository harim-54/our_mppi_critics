#ifndef OUR_MPPI_CRITICS__SLOPE_CRITIC_HPP_
#define OUR_MPPI_CRITICS__SLOPE_CRITIC_HPP_

#include <string>
#include "nav2_mppi_controller/critic_function.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "rclcpp/rclcpp.hpp"

namespace our_mppi_critics
{

class SlopeCritic : public mppi::critics::CriticFunction
{
public:
  SlopeCritic() = default;
  void initialize() override;
  void score(mppi::CriticData & data) override;

private:
  unsigned int power_{1u};
  float weight_{5.0f};
  float max_slope_deg_{30.0f};
  float critical_slope_deg_{25.0f};
  float pitch_{0.0f};
  rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr imu_sub_;
};

}  // namespace our_mppi_critics

#endif  // OUR_MPPI_CRITICS__SLOPE_CRITIC_HPP_