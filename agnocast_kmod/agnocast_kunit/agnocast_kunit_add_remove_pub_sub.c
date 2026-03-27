#include "agnocast_kunit_add_remove_pub_sub.h"

#include "../agnocast.h"
#include "../agnocast_memory_allocator.h"

#include <kunit/test.h>

static const char * TOPIC_NAME = "/kunit_test_topic";
static const char * NODE_NAME = "/kunit_test_node";
static const bool QOS_IS_TRANSIENT_LOCAL = false;
static const bool QOS_IS_RELIABLE = true;
static const bool IS_TAKE_SUB = false;
static const bool IGNORE_LOCAL_PUBLICATIONS = false;
static const bool IS_BRIDGE = false;

static void setup_process(struct kunit * test, const pid_t pid)
{
  union ioctl_add_process_args add_process_args;
  int ret = agnocast_ioctl_add_process(pid, current->nsproxy->ipc_ns, false, &add_process_args);
  KUNIT_ASSERT_EQ(test, ret, 0);
}

void test_case_add_publisher_subscriber_too_many(struct kunit * test)
{
  const uint32_t qos_depth = 1;
  const pid_t publisher_subscriber_pid = 1000;
  setup_process(test, publisher_subscriber_pid);
  for (uint32_t i = 0; i < MAX_PUBLISHER_NUM; i++) {
    union ioctl_add_publisher_args add_publisher_args;
    agnocast_ioctl_add_publisher(
      TOPIC_NAME, current->nsproxy->ipc_ns, NODE_NAME, publisher_subscriber_pid, qos_depth,
      QOS_IS_TRANSIENT_LOCAL, IS_BRIDGE, &add_publisher_args);
  }
  for (uint32_t i = 0; i < MAX_SUBSCRIBER_NUM; i++) {
    union ioctl_add_subscriber_args add_subscriber_args;
    agnocast_ioctl_add_subscriber(
      TOPIC_NAME, current->nsproxy->ipc_ns, NODE_NAME, publisher_subscriber_pid, qos_depth,
      QOS_IS_TRANSIENT_LOCAL, QOS_IS_RELIABLE, IS_TAKE_SUB, IGNORE_LOCAL_PUBLICATIONS, IS_BRIDGE,
      &add_subscriber_args);
  }

  union ioctl_get_publisher_num_args get_publisher_num_args;
  int ret1 =
    agnocast_ioctl_get_publisher_num(TOPIC_NAME, current->nsproxy->ipc_ns, &get_publisher_num_args);
  KUNIT_EXPECT_EQ(test, ret1, 0);
  KUNIT_EXPECT_EQ(test, get_publisher_num_args.ret_publisher_num, MAX_PUBLISHER_NUM);

  union ioctl_get_subscriber_num_args get_subscriber_num_args;
  int ret2 = agnocast_ioctl_get_subscriber_num(
    TOPIC_NAME, current->nsproxy->ipc_ns, current->tgid, &get_subscriber_num_args);
  KUNIT_EXPECT_EQ(test, ret2, 0);
  KUNIT_EXPECT_EQ(
    test, get_subscriber_num_args.ret_other_process_subscriber_num, MAX_SUBSCRIBER_NUM);
}

void test_case_add_remove_publisher_subscriber(struct kunit * test)
{
  const uint32_t qos_depth = 1;
  const pid_t publisher_subscriber_pid = 1000;
  static topic_local_id_t pub_ids[MAX_PUBLISHER_NUM];
  static topic_local_id_t sub_ids[MAX_SUBSCRIBER_NUM];
  setup_process(test, publisher_subscriber_pid);
  for (uint32_t i = 0; i < MAX_PUBLISHER_NUM; i++) {
    union ioctl_add_publisher_args add_publisher_args;
    agnocast_ioctl_add_publisher(
      TOPIC_NAME, current->nsproxy->ipc_ns, NODE_NAME, publisher_subscriber_pid, qos_depth,
      QOS_IS_TRANSIENT_LOCAL, IS_BRIDGE, &add_publisher_args);
    pub_ids[i] = add_publisher_args.ret_id;
  }
  for (uint32_t i = 0; i < MAX_SUBSCRIBER_NUM; i++) {
    union ioctl_add_subscriber_args add_subscriber_args;
    agnocast_ioctl_add_subscriber(
      TOPIC_NAME, current->nsproxy->ipc_ns, NODE_NAME, publisher_subscriber_pid, qos_depth,
      QOS_IS_TRANSIENT_LOCAL, QOS_IS_RELIABLE, IS_TAKE_SUB, IGNORE_LOCAL_PUBLICATIONS, IS_BRIDGE,
      &add_subscriber_args);
    sub_ids[i] = add_subscriber_args.ret_id;
  }

  union ioctl_get_publisher_num_args get_publisher_num_args1;
  int ret1 = agnocast_ioctl_get_publisher_num(
    TOPIC_NAME, current->nsproxy->ipc_ns, &get_publisher_num_args1);
  KUNIT_EXPECT_EQ(test, ret1, 0);
  KUNIT_EXPECT_EQ(test, get_publisher_num_args1.ret_publisher_num, MAX_PUBLISHER_NUM);

  union ioctl_get_subscriber_num_args get_subscriber_num_args1;
  int ret2 = agnocast_ioctl_get_subscriber_num(
    TOPIC_NAME, current->nsproxy->ipc_ns, current->tgid, &get_subscriber_num_args1);
  KUNIT_EXPECT_EQ(test, ret2, 0);
  KUNIT_EXPECT_EQ(
    test, get_subscriber_num_args1.ret_other_process_subscriber_num, MAX_SUBSCRIBER_NUM);

  for (uint32_t i = 0; i < MAX_PUBLISHER_NUM; i++) {
    agnocast_ioctl_remove_publisher(TOPIC_NAME, current->nsproxy->ipc_ns, pub_ids[i]);
  }
  for (uint32_t i = 0; i < MAX_SUBSCRIBER_NUM; i++) {
    agnocast_ioctl_remove_subscriber(TOPIC_NAME, current->nsproxy->ipc_ns, sub_ids[i]);
  }
  union ioctl_get_publisher_num_args get_publisher_num_args2;
  int ret3 = agnocast_ioctl_get_publisher_num(
    TOPIC_NAME, current->nsproxy->ipc_ns, &get_publisher_num_args2);
  KUNIT_EXPECT_EQ(test, ret3, 0);
  KUNIT_EXPECT_EQ(test, get_publisher_num_args2.ret_publisher_num, 0);

  union ioctl_get_subscriber_num_args get_subscriber_num_args2;
  int ret4 = agnocast_ioctl_get_subscriber_num(
    TOPIC_NAME, current->nsproxy->ipc_ns, current->tgid, &get_subscriber_num_args2);
  KUNIT_EXPECT_EQ(test, ret4, 0);
  KUNIT_EXPECT_EQ(test, get_subscriber_num_args2.ret_other_process_subscriber_num, 0);

  for (uint32_t i = 0; i < MAX_PUBLISHER_NUM; i++) {
    union ioctl_add_publisher_args add_publisher_args;
    agnocast_ioctl_add_publisher(
      TOPIC_NAME, current->nsproxy->ipc_ns, NODE_NAME, publisher_subscriber_pid, qos_depth,
      QOS_IS_TRANSIENT_LOCAL, IS_BRIDGE, &add_publisher_args);
  }
  for (uint32_t i = 0; i < MAX_SUBSCRIBER_NUM; i++) {
    union ioctl_add_subscriber_args add_subscriber_args;
    agnocast_ioctl_add_subscriber(
      TOPIC_NAME, current->nsproxy->ipc_ns, NODE_NAME, publisher_subscriber_pid, qos_depth,
      QOS_IS_TRANSIENT_LOCAL, QOS_IS_RELIABLE, IS_TAKE_SUB, IGNORE_LOCAL_PUBLICATIONS, IS_BRIDGE,
      &add_subscriber_args);
  }

  union ioctl_get_publisher_num_args get_publisher_num_args3;
  int ret5 = agnocast_ioctl_get_publisher_num(
    TOPIC_NAME, current->nsproxy->ipc_ns, &get_publisher_num_args3);
  KUNIT_EXPECT_EQ(test, ret5, 0);
  KUNIT_EXPECT_EQ(test, get_publisher_num_args3.ret_publisher_num, MAX_PUBLISHER_NUM);

  union ioctl_get_subscriber_num_args get_subscriber_num_args3;
  int ret6 = agnocast_ioctl_get_subscriber_num(
    TOPIC_NAME, current->nsproxy->ipc_ns, current->tgid, &get_subscriber_num_args3);
  KUNIT_EXPECT_EQ(test, ret6, 0);
  KUNIT_EXPECT_EQ(
    test, get_subscriber_num_args3.ret_other_process_subscriber_num, MAX_SUBSCRIBER_NUM);
}
