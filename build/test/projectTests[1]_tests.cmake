add_test([=[HelloTest.BasicAssertions]=]  C:/Users/HoffR/software-engineering-project-daisy/build/test/projectTests.exe [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY C:/Users/HoffR/software-engineering-project-daisy/build/test SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  projectTests_TESTS HelloTest.BasicAssertions)
