#include <gtest/gtest.h>

#include <vm_stack.h>

TEST(chuck, vm_stack)
{
    vm_stack stack {nullptr};
    EXPECT_EQ(stack.size(), 0);

    vm_num_t num {1};
    stack.push(num);

    EXPECT_EQ(stack.size(), sizeof(vm_num_t));

    vm_num_t num1 = stack.pop_num();

    EXPECT_EQ(num1, num);
    EXPECT_EQ(stack.size(), 0);
}
