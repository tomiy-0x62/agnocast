#include "agnocast_kunit_get_node_names.h"

#include "../agnocast.h"

#include <kunit/test.h>

static const char * TOPIC_NAME = "/kunit_test_topic";
static const char * NODE_NAME = "/kunit_test_node";
static const pid_t PID = 1000;
static const uint32_t QOS_DEPTH = 1;
static const bool IS_BRIDGE = false;

static void setup_process(struct kunit * test, const pid_t pid)
{
  union ioctl_add_process_args add_process_args;
  int ret = agnocast_ioctl_add_process(pid, current->nsproxy->ipc_ns, false, &add_process_args);
  KUNIT_ASSERT_EQ(test, ret, 0);
}

void test_case_get_node_names(struct kunit * test)
{
  union ioctl_add_publisher_args add_pub_args;
  struct ioctl_get_node_names_args get_node_names_args = {};
  int ret;

  setup_process(test, PID);

  ret = agnocast_ioctl_add_publisher(
    TOPIC_NAME, current->nsproxy->ipc_ns, NODE_NAME, PID, QOS_DEPTH, false, IS_BRIDGE,
    &add_pub_args);
  KUNIT_ASSERT_EQ(test, ret, 0);

  // copy_to_user inside ioctl_get_node_names returns -EFAULT in KUnit (kernel thread)
  // context, but reaching it confirms that the node name was found.
  char buffer[512];
  get_node_names_args.buffer = buffer;
  get_node_names_args.count = 0;
  ret = agnocast_ioctl_get_node_names(&get_node_names_args);
  KUNIT_EXPECT_TRUE(test, ret == -EFAULT || (ret == 0 && get_node_names_args.count == 1));
}
