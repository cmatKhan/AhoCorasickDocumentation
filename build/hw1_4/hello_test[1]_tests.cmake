add_test( HelloTest.BasicAssertions /home/oguzkhan/class/bioseq/assignments/hw1/homework-1-problem-4-cmatKhan/build/hw1_4/hello_test [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties( HelloTest.BasicAssertions PROPERTIES WORKING_DIRECTORY /home/oguzkhan/class/bioseq/assignments/hw1/homework-1-problem-4-cmatKhan/build/hw1_4)
set( hello_test_TESTS HelloTest.BasicAssertions)
