#include "agnocast/node/node_interfaces/node_graph.hpp"

namespace agnocast::node_interfaces
{

NodeGraph::NodeGraph(NodeBase::SharedPtr node_base) : node_base_(std::move(node_base))
{
}

std::map<std::string, std::vector<std::string>> NodeGraph::get_topic_names_and_types(
  bool no_demangle) const
{
  (void)no_demangle;
  throw std::runtime_error("NodeGraph::get_topic_names_and_types is not supported in agnocast. ");
};

std::map<std::string, std::vector<std::string>> NodeGraph::get_service_names_and_types() const
{
  throw std::runtime_error("NodeGraph::get_service_names_and_types is not supported in agnocast. ");
};

std::map<std::string, std::vector<std::string>> NodeGraph::get_service_names_and_types_by_node(
  const std::string & node_name, const std::string & namespace_) const
{
  (void)node_name;
  (void)namespace_;
  throw std::runtime_error(
    "NodeGraph::get_service_names_and_types_by_node is not supported in agnocast. ");
};

std::map<std::string, std::vector<std::string>> NodeGraph::get_client_names_and_types_by_node(
  const std::string & node_name, const std::string & namespace_) const
{
  (void)node_name;
  (void)namespace_;
  throw std::runtime_error(
    "NodeGraph::get_client_names_and_types_by_node is not supported in agnocast. ");
};

std::map<std::string, std::vector<std::string>> NodeGraph::get_publisher_names_and_types_by_node(
  const std::string & node_name, const std::string & namespace_, bool no_demangle) const
{
  (void)node_name;
  (void)namespace_;
  (void)no_demangle;
  throw std::runtime_error(
    "NodeGraph::get_publisher_names_and_types_by_node is not supported in agnocast. ");
};

std::map<std::string, std::vector<std::string>> NodeGraph::get_subscriber_names_and_types_by_node(
  const std::string & node_name, const std::string & namespace_, bool no_demangle) const
{
  (void)node_name;
  (void)namespace_;
  (void)no_demangle;
  throw std::runtime_error(
    "NodeGraph::get_subscriber_names_and_types_by_node is not supported in agnocast. ");
};

std::vector<std::string> NodeGraph::get_node_names() const
{
  struct ioctl_get_node_names_args get_node_names_args = {};
  char buffer[1024];
  get_node_names_args.buffer = buffer;
  get_node_names_args.count = 0;
  if (ioctl(agnocast::agnocast_fd, AGNOCAST_GET_NODE_NAMES_CMD, &get_node_names_args) < 0) {
    RCLCPP_ERROR(logger, "AGNOCAST_GET_NODE_NAMES_CMD failed: %s", strerror(errno));
    close(agnocast::agnocast_fd);
    exit(EXIT_FAILURE);
  }

  std::vector<std::string> node_names;
  char * current_ptr = buffer;

  for (int i = 0; i < get_node_names_args.count; ++i) {
    std::string s(current_ptr);
    node_names.push_back(s);
    current_ptr += s.length() + 1;
  }

  return node_names;
};

std::vector<std::tuple<std::string, std::string, std::string>>
NodeGraph::get_node_names_with_enclaves() const
{
  throw std::runtime_error(
    "NodeGraph::get_node_names_with_enclaves is not supported in agnocast. ");
};

std::vector<std::pair<std::string, std::string>> NodeGraph::get_node_names_and_namespaces() const
{
  throw std::runtime_error(
    "NodeGraph::get_node_names_and_namespaces is not supported in agnocast. ");
};

size_t NodeGraph::count_publishers(const std::string & topic_name) const
{
  union ioctl_get_publisher_num_args args = {};
  args.topic_name = {topic_name.c_str(), topic_name.size()};
  if (ioctl(agnocast::agnocast_fd, AGNOCAST_GET_PUBLISHER_NUM_CMD, &args) < 0) {
    RCLCPP_ERROR(logger, "AGNOCAST_GET_PUBLISHER_NUM_CMD failed: %s", strerror(errno));
    close(agnocast::agnocast_fd);
    exit(EXIT_FAILURE);
  }
  uint32_t count = args.ret_publisher_num;
  // If an R2A bridge exists, exclude the agnocast publisher created by the bridge
  if (args.ret_r2a_bridge_exist && count > 0) {
    count--;
  }

  uint32_t ros2_count = args.ret_ros2_publisher_num;
  // If an R2A bridge exists, exclude the agnocast publisher created by the bridge
  if (args.ret_a2r_bridge_exist && ros2_count > 0) {
    ros2_count--;
  }

  return count + ros2_count;
};

size_t NodeGraph::count_subscribers(const std::string & topic_name) const
{
  union ioctl_get_subscriber_num_args args = {};
  args.topic_name = {topic_name.c_str(), topic_name.size()};
  if (ioctl(agnocast::agnocast_fd, AGNOCAST_GET_SUBSCRIBER_NUM_CMD, &args) < 0) {
    RCLCPP_ERROR(logger, "AGNOCAST_GET_SUBSCRIBER_NUM_CMD failed: %s", strerror(errno));
    close(agnocast::agnocast_fd);
    exit(EXIT_FAILURE);
  }
  uint32_t inter_count = args.ret_other_process_subscriber_num;
  // If an R2A bridge exists, exclude the agnocast subscriber created by the bridge
  if (args.ret_r2a_bridge_exist && inter_count > 0) {
    inter_count--;
  }

  uint32_t ros2_count = args.ret_ros2_subscriber_num;
  // If an R2A bridge exists, exclude the agnocast subscriber created by the bridge
  if (args.ret_a2r_bridge_exist && ros2_count > 0) {
    ros2_count--;
  }

  return inter_count + ros2_count;
};

const rcl_guard_condition_t * NodeGraph::get_graph_guard_condition() const
{
  throw std::runtime_error("NodeGraph::get_graph_guard_condition is not supported in agnocast. ");
};

void NodeGraph::notify_graph_change()
{
  throw std::runtime_error("NodeGraph::notify_graph_change is not supported in agnocast. ");
};

void NodeGraph::notify_shutdown()
{
  throw std::runtime_error("NodeGraph::notify_shutdown is not supported in agnocast. ");
};

rclcpp::Event::SharedPtr NodeGraph::get_graph_event()
{
  throw std::runtime_error("NodeGraph::notify_shutdown is not supported in agnocast. ");
};

void NodeGraph::wait_for_graph_change(
  rclcpp::Event::SharedPtr event, std::chrono::nanoseconds timeout)
{
  (void)event;
  (void)timeout;
  throw std::runtime_error("NodeGraph::wait_for_graph_change is not supported in agnocast. ");
};

size_t NodeGraph::count_graph_users() const
{
  throw std::runtime_error("NodeGraph::count_graph_users is not supported in agnocast. ");
};

std::vector<rclcpp::TopicEndpointInfo> NodeGraph::get_publishers_info_by_topic(
  const std::string & topic_name, bool no_mangle) const
{
  (void)topic_name;
  (void)no_mangle;
  throw std::runtime_error(
    "NodeGraph::get_publishers_info_by_topic is not supported in agnocast. ");
};

std::vector<rclcpp::TopicEndpointInfo> NodeGraph::get_subscriptions_info_by_topic(
  const std::string & topic_name, bool no_mangle) const
{
  (void)topic_name;
  (void)no_mangle;
  throw std::runtime_error(
    "NodeGraph::get_subscriptions_info_by_topic is not supported in agnocast. ");
};

}  // namespace agnocast::node_interfaces
