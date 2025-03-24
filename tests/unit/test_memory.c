/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sscholz <sscholz@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:16:37 by sscholz           #+#    #+#             */
/*   Updated: 2025/03/19 17:16:40 by sscholz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../unity/unity.h"
#include "../../include/minishell.h"

// Setup and teardown functions (run before/after each test)
void setUp(void)
{
}

void tearDown(void) {}

void test_ft_track_strdup_basic(void)
{
	t_shell shell;
	shell.memory_list = NULL;

	char *src = "hello";
	char *dup = ft_track_strdup(&shell, src);

	TEST_ASSERT_NOT_NULL(dup);				// Check allocation succeeded
	TEST_ASSERT_EQUAL_STRING("hello", dup); // Check content matches
	TEST_ASSERT_EQUAL(5, ft_strlen(dup));	// Check length (5 chars + \0)

	ft_track_free(&shell, dup);			 // Clean up
	TEST_ASSERT_NULL(shell.memory_list); // Check memory list is empty
}

void test_ft_track_strdup_empty(void)
{
	t_shell shell;
	char *src = "";
	char *dup;

	shell.memory_list = NULL;
	dup = ft_track_strdup(&shell, src);
	TEST_ASSERT_NOT_NULL(dup);
	TEST_ASSERT_EQUAL_STRING("", dup);
	TEST_ASSERT_EQUAL_INT(0, ft_strlen(dup));
	TEST_ASSERT_EQUAL_INT(1, shell.memory_list->size); // 1 byte for \0
	ft_track_free(&shell, dup);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

void test_ft_track_strdup_null(void)
{
	t_shell shell;
	char *dup;

	shell.memory_list = NULL;
	dup = ft_track_strdup(&shell, NULL);
	TEST_ASSERT_NULL(dup);
	TEST_ASSERT_NULL(shell.memory_list); // No allocation should happen
}

void test_ft_track_strdup_long(void)
{
	t_shell shell;
	char *src = "This is a very long string to test ft_track_strdup functionality!";
	char *dup;

	shell.memory_list = NULL;
	dup = ft_track_strdup(&shell, src);
	TEST_ASSERT_NOT_NULL(dup);
	TEST_ASSERT_EQUAL_STRING(src, dup);
	TEST_ASSERT_EQUAL_INT(ft_strlen(src), ft_strlen(dup));
	TEST_ASSERT_EQUAL_INT(ft_strlen(src) + 1, shell.memory_list->size);
	ft_track_free(&shell, dup);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

void test_ft_track_strdup_memory_tracking(void)
{
	t_shell shell;
	char *src = "track me";
	char *dup;

	shell.memory_list = NULL;
	dup = ft_track_strdup(&shell, src);
	TEST_ASSERT_NOT_NULL(dup);
	TEST_ASSERT_EQUAL_PTR(dup, shell.memory_list->ptr);					// Pointer matches
	TEST_ASSERT_EQUAL_INT(ft_strlen(src) + 1, shell.memory_list->size); // Size includes \0
	TEST_ASSERT_NULL(shell.memory_list->next);							// Only one allocation
	ft_track_free(&shell, dup);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}
void test_ft_track_strdup_multiple(void)
{
	t_shell shell;
	char *src1 = "first";
	char *src2 = "second";
	char *dup1;
	char *dup2;

	shell.memory_list = NULL;
	dup1 = ft_track_strdup(&shell, src1);
	dup2 = ft_track_strdup(&shell, src2);
	TEST_ASSERT_NOT_NULL(dup1);
	TEST_ASSERT_NOT_NULL(dup2);
	TEST_ASSERT_EQUAL_STRING("first", dup1);
	TEST_ASSERT_EQUAL_STRING("second", dup2);
	TEST_ASSERT_EQUAL_PTR(dup2, shell.memory_list->ptr);	   // Most recent allocation
	TEST_ASSERT_EQUAL_PTR(dup1, shell.memory_list->next->ptr); // Previous allocation
	ft_track_free(&shell, dup1);
	TEST_ASSERT_EQUAL_PTR(dup2, shell.memory_list->ptr); // List updated
	ft_track_free(&shell, dup2);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

void test_ft_track_malloc_basic(void)
{
	t_shell shell;
	void *ptr;

	shell.memory_list = NULL;
	ptr = ft_track_malloc(&shell, 10); // Allocate 10 bytes
	TEST_ASSERT_NOT_NULL(ptr);
	TEST_ASSERT_EQUAL_PTR(ptr, shell.memory_list->ptr);
	TEST_ASSERT_EQUAL_INT(10, shell.memory_list->size);
	TEST_ASSERT_NULL(shell.memory_list->next); // Single allocation
	ft_track_free(&shell, ptr);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

// Test 2: Zero-size allocation
void test_ft_track_malloc_zero_size(void)
{
	t_shell shell;
	void *ptr;

	shell.memory_list = NULL;
	ptr = ft_track_malloc(&shell, 0); // Allocate 0 bytes
	// Assuming we allow a valid pointer (glibc behavior), adjust if you want NULL
	TEST_ASSERT_NOT_NULL(ptr); // Could be TEST_ASSERT_NULL if you change ft_track_malloc
	if (ptr)
	{
		TEST_ASSERT_EQUAL_INT(0, shell.memory_list->size);
		ft_track_free(&shell, ptr);
	}
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

// Test 3: Large allocation
void test_ft_track_malloc_large(void)
{
	t_shell shell;
	void *ptr;

	shell.memory_list = NULL;
	ptr = ft_track_malloc(&shell, 1024); // Allocate 1KB
	TEST_ASSERT_NOT_NULL(ptr);
	TEST_ASSERT_EQUAL_PTR(ptr, shell.memory_list->ptr);
	TEST_ASSERT_EQUAL_INT(1024, shell.memory_list->size);
	TEST_ASSERT_NULL(shell.memory_list->next);
	ft_track_free(&shell, ptr);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

// Test 4: Memory list integration
void test_ft_track_malloc_list_integration(void)
{
	t_shell shell;
	void *ptr;

	shell.memory_list = NULL;
	ptr = ft_track_malloc(&shell, 8);
	TEST_ASSERT_NOT_NULL(ptr);
	TEST_ASSERT_EQUAL_PTR(ptr, shell.memory_list->ptr);
	TEST_ASSERT_EQUAL_INT(8, shell.memory_list->size);
	TEST_ASSERT_NULL(shell.memory_list->next);
	TEST_ASSERT_NOT_NULL(shell.memory_list); // List exists
	ft_track_free(&shell, ptr);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

// Test 5: Multiple allocations
void test_ft_track_malloc_multiple(void)
{
	t_shell shell;
	void *ptr1;
	void *ptr2;
	void *ptr3;

	shell.memory_list = NULL;
	ptr1 = ft_track_malloc(&shell, 5);
	ptr2 = ft_track_malloc(&shell, 10);
	ptr3 = ft_track_malloc(&shell, 15);
	TEST_ASSERT_NOT_NULL(ptr1);
	TEST_ASSERT_NOT_NULL(ptr2);
	TEST_ASSERT_NOT_NULL(ptr3);
	TEST_ASSERT_EQUAL_PTR(ptr3, shell.memory_list->ptr); // Most recent
	TEST_ASSERT_EQUAL_INT(15, shell.memory_list->size);
	TEST_ASSERT_EQUAL_PTR(ptr2, shell.memory_list->next->ptr);
	TEST_ASSERT_EQUAL_INT(10, shell.memory_list->next->size);
	TEST_ASSERT_EQUAL_PTR(ptr1, shell.memory_list->next->next->ptr);
	TEST_ASSERT_EQUAL_INT(5, shell.memory_list->next->next->size);
	TEST_ASSERT_NULL(shell.memory_list->next->next->next);
	ft_track_free(&shell, ptr2); // Free middle allocation
	TEST_ASSERT_EQUAL_PTR(ptr3, shell.memory_list->ptr);
	TEST_ASSERT_EQUAL_PTR(ptr1, shell.memory_list->next->ptr);
	ft_track_free(&shell, ptr1);
	ft_track_free(&shell, ptr3);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

// Test 1: Basic free
void test_ft_track_free_basic(void)
{
	t_shell shell;
	void *ptr;

	shell.memory_list = NULL;
	ptr = ft_track_malloc(&shell, 10);
	TEST_ASSERT_NOT_NULL(ptr);
	TEST_ASSERT_NOT_NULL(shell.memory_list);
	ft_track_free(&shell, ptr);
	TEST_ASSERT_NULL(shell.memory_list);
	ft_free_all_tracked(&shell); // Should be safe even if empty
}

// Test 2: Freeing NULL
void test_ft_track_free_null(void)
{
	t_shell shell;
	void *ptr;

	shell.memory_list = NULL;
	ptr = ft_track_malloc(&shell, 5);
	TEST_ASSERT_NOT_NULL(ptr);
	ft_track_free(&shell, NULL);			 // Should do nothing
	TEST_ASSERT_NOT_NULL(shell.memory_list); // List unchanged
	TEST_ASSERT_EQUAL_PTR(ptr, shell.memory_list->ptr);
	ft_track_free(&shell, ptr);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

// Test 3: Freeing non-existent pointer
void test_ft_track_free_non_existent(void)
{
	t_shell shell;
	void *ptr1;
	void *ptr2 = (void *)0x1234; // Arbitrary non-allocated pointer

	shell.memory_list = NULL;
	ptr1 = ft_track_malloc(&shell, 8);
	TEST_ASSERT_NOT_NULL(ptr1);
	ft_track_free(&shell, ptr2); // Should do nothing
	TEST_ASSERT_NOT_NULL(shell.memory_list);
	TEST_ASSERT_EQUAL_PTR(ptr1, shell.memory_list->ptr);
	ft_track_free(&shell, ptr1);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

// Test 4: Freeing from middle of list
void test_ft_track_free_middle(void)
{
	t_shell shell;
	void *ptr1;
	void *ptr2;
	void *ptr3;

	shell.memory_list = NULL;
	ptr1 = ft_track_malloc(&shell, 5);
	ptr2 = ft_track_malloc(&shell, 10);
	ptr3 = ft_track_malloc(&shell, 15);
	TEST_ASSERT_NOT_NULL(ptr1);
	TEST_ASSERT_NOT_NULL(ptr2);
	TEST_ASSERT_NOT_NULL(ptr3);
	ft_track_free(&shell, ptr2); // Free middle allocation
	TEST_ASSERT_EQUAL_PTR(ptr3, shell.memory_list->ptr);
	TEST_ASSERT_EQUAL_PTR(ptr1, shell.memory_list->next->ptr);
	TEST_ASSERT_NULL(shell.memory_list->next->next);
	ft_track_free(&shell, ptr1);
	ft_track_free(&shell, ptr3);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

// Test 5: Freeing multiple allocations
void test_ft_track_free_multiple(void)
{
	t_shell shell;
	void *ptr1;
	void *ptr2;
	void *ptr3;

	shell.memory_list = NULL;
	ptr1 = ft_track_malloc(&shell, 5);
	ptr2 = ft_track_malloc(&shell, 10);
	ptr3 = ft_track_malloc(&shell, 15);
	TEST_ASSERT_NOT_NULL(ptr1);
	TEST_ASSERT_NOT_NULL(ptr2);
	TEST_ASSERT_NOT_NULL(ptr3);
	ft_track_free(&shell, ptr1); // Free first
	TEST_ASSERT_EQUAL_PTR(ptr3, shell.memory_list->ptr);
	TEST_ASSERT_EQUAL_PTR(ptr2, shell.memory_list->next->ptr);
	ft_track_free(&shell, ptr3); // Free head
	TEST_ASSERT_EQUAL_PTR(ptr2, shell.memory_list->ptr);
	TEST_ASSERT_NULL(shell.memory_list->next);
	ft_track_free(&shell, ptr2); // Free last
	TEST_ASSERT_NULL(shell.memory_list);
	ft_free_all_tracked(&shell);
}

// Test 6: Double free safety
void test_ft_track_free_double(void)
{
	t_shell shell;
	void *ptr;

	shell.memory_list = NULL;
	ptr = ft_track_malloc(&shell, 20);
	TEST_ASSERT_NOT_NULL(ptr);
	ft_track_free(&shell, ptr); // First free
	TEST_ASSERT_NULL(shell.memory_list);
	ft_track_free(&shell, ptr);			 // Second free - should do nothing
	TEST_ASSERT_NULL(shell.memory_list); // Still NULL, no crash
	ft_free_all_tracked(&shell);
}

// Test 1: Basic cleanup
void test_ft_free_all_tracked_basic(void)
{
	t_shell shell;
	void *ptr;

	shell.memory_list = NULL;
	ptr = ft_track_malloc(&shell, 10);
	TEST_ASSERT_NOT_NULL(ptr);
	TEST_ASSERT_NOT_NULL(shell.memory_list);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

// Test 2: Empty list
void test_ft_free_all_tracked_empty(void)
{
	t_shell shell;

	shell.memory_list = NULL;
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list); // Should stay NULL, no crash
}

// Test 3: Multiple allocations
void test_ft_free_all_tracked_multiple(void)
{
	t_shell shell;
	void *ptr1;
	void *ptr2;
	void *ptr3;

	shell.memory_list = NULL;
	ptr1 = ft_track_malloc(&shell, 5);
	ptr2 = ft_track_malloc(&shell, 10);
	ptr3 = ft_track_malloc(&shell, 15);
	TEST_ASSERT_NOT_NULL(ptr1);
	TEST_ASSERT_NOT_NULL(ptr2);
	TEST_ASSERT_NOT_NULL(ptr3);
	TEST_ASSERT_NOT_NULL(shell.memory_list);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

// Test 4: Mixed allocations
void test_ft_free_all_tracked_mixed(void)
{
	t_shell shell;
	void *ptr1;
	char *dup1;
	void *ptr2;

	shell.memory_list = NULL;
	ptr1 = ft_track_malloc(&shell, 20);
	dup1 = ft_track_strdup(&shell, "hello");
	ptr2 = ft_track_malloc(&shell, 30);
	TEST_ASSERT_NOT_NULL(ptr1);
	TEST_ASSERT_NOT_NULL(dup1);
	TEST_ASSERT_NOT_NULL(ptr2);
	TEST_ASSERT_EQUAL_STRING("hello", dup1);
	TEST_ASSERT_NOT_NULL(shell.memory_list);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
}

// Test 5: Double call
void test_ft_free_all_tracked_double(void)
{
	t_shell shell;
	void *ptr;

	shell.memory_list = NULL;
	ptr = ft_track_malloc(&shell, 25);
	TEST_ASSERT_NOT_NULL(ptr);
	ft_free_all_tracked(&shell);
	TEST_ASSERT_NULL(shell.memory_list);
	ft_free_all_tracked(&shell);		 // Second call
	TEST_ASSERT_NULL(shell.memory_list); // Still NULL, no crash
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_ft_track_strdup_basic);
	RUN_TEST(test_ft_track_strdup_empty);
	RUN_TEST(test_ft_track_strdup_null);
	RUN_TEST(test_ft_track_strdup_long);
	RUN_TEST(test_ft_track_strdup_memory_tracking);
	RUN_TEST(test_ft_track_strdup_multiple);
	write(1, "\n", 2);
	RUN_TEST(test_ft_track_malloc_basic);
	RUN_TEST(test_ft_track_malloc_zero_size);
	RUN_TEST(test_ft_track_malloc_large);
	RUN_TEST(test_ft_track_malloc_list_integration);
	RUN_TEST(test_ft_track_malloc_multiple);
	write(1, "\n", 2);
	RUN_TEST(test_ft_track_free_basic);
	RUN_TEST(test_ft_track_free_null);
	RUN_TEST(test_ft_track_free_non_existent);
	RUN_TEST(test_ft_track_free_middle);
	RUN_TEST(test_ft_track_free_multiple);
	RUN_TEST(test_ft_track_free_double);
	write(1, "\n", 2);
	RUN_TEST(test_ft_free_all_tracked_basic);
	RUN_TEST(test_ft_free_all_tracked_empty);
	RUN_TEST(test_ft_free_all_tracked_multiple);
	RUN_TEST(test_ft_free_all_tracked_mixed);
	RUN_TEST(test_ft_free_all_tracked_double);
	return UNITY_END();
}