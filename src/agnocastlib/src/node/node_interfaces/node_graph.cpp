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
  throw std::runtime_error("NodeGraph::get_topic_names_and_types is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

std::map<std::string, std::vector<std::string>> NodeGraph::get_service_names_and_types() const
{
  throw std::runtime_error("NodeGraph::get_service_names_and_types is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

std::map<std::string, std::vector<std::string>> NodeGraph::get_service_names_and_types_by_node(
  const std::string & node_name, const std::string & namespace_) const
{
  (void)node_name;
  (void)namespace_;
  throw std::runtime_error(
    "NodeGraph::get_service_names_and_types_by_node is not supported in agnocast. "
    // "Use agnocast::???? instead."
  );
};

std::map<std::string, std::vector<std::string>> NodeGraph::get_client_names_and_types_by_node(
  const std::string & node_name, const std::string & namespace_) const
{
  (void)node_name;
  (void)namespace_;
  throw std::runtime_error(
    "NodeGraph::get_client_names_and_types_by_node is not supported in agnocast. "
    // "Use agnocast::???? instead."
  );
};

std::map<std::string, std::vector<std::string>> NodeGraph::get_publisher_names_and_types_by_node(
  const std::string & node_name, const std::string & namespace_, bool no_demangle) const
{
  (void)node_name;
  (void)namespace_;
  (void)no_demangle;
  throw std::runtime_error(
    "NodeGraph::get_publisher_names_and_types_by_node is not supported in agnocast. "
    // "Use agnocast::???? instead."
  );
};

std::map<std::string, std::vector<std::string>> NodeGraph::get_subscriber_names_and_types_by_node(
  const std::string & node_name, const std::string & namespace_, bool no_demangle) const
{
  (void)node_name;
  (void)namespace_;
  (void)no_demangle;
  throw std::runtime_error(
    "NodeGraph::get_subscriber_names_and_types_by_node is not supported in agnocast. "
    // "Use agnocast::???? instead."
  );
};

std::vector<std::string> NodeGraph::get_node_names() const
{
  throw std::runtime_error("NodeGraph::get_node_names is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

std::vector<std::tuple<std::string, std::string, std::string>>
NodeGraph::get_node_names_with_enclaves() const
{
  throw std::runtime_error("NodeGraph::get_node_names_with_enclaves is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

std::vector<std::pair<std::string, std::string>> NodeGraph::get_node_names_and_namespaces() const
{
  throw std::runtime_error("NodeGraph::get_node_names_and_namespaces is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

size_t NodeGraph::count_publishers(const std::string & topic_name) const
{
  (void)topic_name;
  throw std::runtime_error("NodeGraph::count_publishers is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

size_t NodeGraph::count_subscribers(const std::string & topic_name) const
{
  (void)topic_name;
  throw std::runtime_error("NodeGraph::count_subscribers is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

const rcl_guard_condition_t * NodeGraph::get_graph_guard_condition() const
{
  throw std::runtime_error("NodeGraph::get_graph_guard_condition is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

void NodeGraph::notify_graph_change()
{
  throw std::runtime_error("NodeGraph::notify_graph_change is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

void NodeGraph::notify_shutdown()
{
  throw std::runtime_error("NodeGraph::notify_shutdown is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

rclcpp::Event::SharedPtr NodeGraph::get_graph_event()
{
  throw std::runtime_error("NodeGraph::notify_shutdown is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

void NodeGraph::wait_for_graph_change(
  rclcpp::Event::SharedPtr event, std::chrono::nanoseconds timeout)
{
  (void)event;
  (void)timeout;
  throw std::runtime_error("NodeGraph::wait_for_graph_change is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

size_t NodeGraph::count_graph_users() const
{
  throw std::runtime_error("NodeGraph::count_graph_users is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

std::vector<rclcpp::TopicEndpointInfo> NodeGraph::get_publishers_info_by_topic(
  const std::string & topic_name, bool no_mangle) const
{
  (void)topic_name;
  (void)no_mangle;
  throw std::runtime_error("NodeGraph::get_publishers_info_by_topic is not supported in agnocast. "
                           // "Use agnocast::???? instead."
  );
};

std::vector<rclcpp::TopicEndpointInfo> NodeGraph::get_subscriptions_info_by_topic(
  const std::string & topic_name, bool no_mangle) const
{
  (void)topic_name;
  (void)no_mangle;
  throw std::runtime_error(
    "NodeGraph::get_subscriptions_info_by_topic is not supported in agnocast. "
    // "Use agnocast::???? instead."
  );
};

}  // namespace agnocast::node_interfaces
