add_executable(vm_stack_test stack.cpp)
target_link_libraries(vm_stack_test chuck binkw32 GTest::gtest_main)

add_custom_command(
    TARGET vm_stack_test
    POST_BUILD
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND /bin/sh
    ARGS run.sh $<TARGET_FILE:vm_stack_test>
)
