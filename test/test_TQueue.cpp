#include "TQueue.h"
#include <gtest.h>

TEST(TQueue, can_create_queue_with_positive_length)
{
	ASSERT_NO_THROW(TQueue<int> q(5));
}

TEST(TQueue, cant_create_too_large_queue)
{
	ASSERT_ANY_THROW(TQueue<int> q(MAX_QUEUE_SIZE + 1));
}

TEST(TQueue, throws_when_create_queue_with_negative_length)
{
	ASSERT_ANY_THROW(TQueue<int> q(-5));
}

TEST(TQueue, can_create_copied_queue)
{
	TQueue<int> s1(10);
	ASSERT_NO_THROW(TQueue<int> q2(s1));
}

TEST(TQueue, copied_queue_is_equal_to_source_one)
{
	TQueue<int> q1(10);
	q1.Push(2);
	q1.Push(5);
	q1.Push(11);
	TQueue<int> q2(q1);
	EXPECT_EQ(true, q1 == q2);
}

TEST(TQueue, copied_queue_has_its_own_memory)
{
	TQueue<int> q1(10);
	for (int i = 0; i < 3; i++)
		q1.Push(i);
	TQueue<int> q2(q1);
	q2.Pop();
	q2.Push(123);
	EXPECT_EQ(true, q1 != q2);
}

TEST(TQueue, can_push_and_top_element)
{
	TQueue<int> q(5);
	q.Push(5);
	q.Push(6);
	EXPECT_EQ(5, q.Top());
}

TEST(TQueue, can_pop_element)
{
	TQueue<int> q(5);
	q.Push(5);
	q.Push(6);
	q.Pop();
	EXPECT_EQ(6, q.Top());
}

TEST(TQueue, can_top_pop_element)
{
	TQueue<int> q(5);
	q.Push(5);
	q.Push(6);
	EXPECT_EQ(5, q.TopPop());
	EXPECT_EQ(6, q.TopPop());
}

TEST(TQueue, knows_if_empty)
{
	TQueue<int> q(5);
	EXPECT_EQ(true, q.IsEmpty());
	q.Push(11);
	EXPECT_EQ(false, q.IsEmpty());
	q.Pop();
	EXPECT_EQ(true, q.IsEmpty());
}

TEST(TQueue, knows_if_full)
{
	TQueue<int> q(5);
	EXPECT_EQ(false, q.IsFull());
	q.Push(0);
	EXPECT_EQ(false, q.IsFull());
	for (int i = 1; i < 5; i++)
		q.Push(i * 2);
	EXPECT_EQ(true, q.IsFull());
}

TEST(TQueue, throws_when_push_when_full)
{
	TQueue<int> q(5);
	for (int i = 0; i < 5; i++)
		q.Push(i * 2);
	ASSERT_ANY_THROW(q.Push(0));
}

TEST(TQueue, throws_when_pop_when_empty)
{
	TQueue<int> q(5);
	q.Push(0);
	q.Pop();
	ASSERT_ANY_THROW(q.Pop());
}

TEST(TQueue, can_assign_queue_to_itself)
{
	TQueue<int> q(5);
	ASSERT_NO_THROW(q = q);
}

TEST(TQueue, can_assign_queue_of_equal_size)
{
	TQueue<int> q1(5), q2(5);
	q1.Push(15);
	q1.Push(16);
	q2 = q1;
	q2.Pop();
	q2.Pop();
	q2.Push(16);
	q2.Push(15);
	EXPECT_NE(15, q2.TopPop());
	EXPECT_NE(16, q2.Top());
}

TEST(TQueue, can_assign_queue_of_different_size)
{
	TQueue<int> q1(2), q2(1);
	q1.Push(100);
	q1.Push(200);
	q2.Push(0);
	q2 = q1;
	EXPECT_EQ(100, q2.TopPop());
	EXPECT_EQ(200, q2.TopPop());
}

TEST(TQueue, compare_equal_queues_return_true)
{
	TQueue<int> q1(5), q2(5);
	q1.Push(5);
	q1.Push(6);
	q1.Push(7);

	q2.Push(5);
	q2.Push(6);
	q2.Push(7);
	EXPECT_EQ(true, q1 == q2);
}

TEST(TQueue, compare_queue_with_itself_return_true)
{
	TQueue<int> q(5);
	q.Push(0);
	EXPECT_EQ(true, q == q);
}

TEST(TQueue, queues_with_different_size_are_not_equal)
{
	TQueue<int> q1(5), q2(5);
	q1.Push(5);
	q1.Push(6);
	q2.Push(5);
	EXPECT_EQ(true, q1 != q2);
}

TEST(TQueue, same_queues_but_with_different_memory_size_are_equal)
{
	TQueue<int> q1(5), q2(10);
	q1.Push(5);
	q1.Push(6);
	q2.Push(5);
	q2.Push(6);
	EXPECT_EQ(true, q1 == q2);
}

TEST(TQueue, test_queue_cercular_buffer)
{
	TQueue<int> q(4);
	q.Push(12);
	q.Push(13);
	q.Push(14);
	q.Push(15);
	EXPECT_EQ(true, q.IsFull());
	q.Pop();
	EXPECT_EQ(false, q.IsFull());
	ASSERT_NO_THROW(q.Push(16));
	q.Pop();
	ASSERT_NO_THROW(q.Push(17));
	EXPECT_EQ(14, q.TopPop());
	EXPECT_EQ(15, q.TopPop());
	EXPECT_EQ(16, q.TopPop());
	EXPECT_EQ(17, q.TopPop());
	EXPECT_EQ(true, q.IsEmpty());
}