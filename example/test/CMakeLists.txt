add_executable(GuessTheNumberTests
    main.cxx
    GuessTheNumberTest.cxx
    ConsoleUserInterfaceTest.cxx
    MockRandomNumberGenerator.hxx
    MockUserInterface.hxx
    )
target_link_libraries(GuessTheNumberTests PRIVATE
    GuessTheNumberImpl
    Catch2::Catch2
    trompeloeil
    )
target_compile_definitions(GuessTheNumberTests PRIVATE BUILD_TEST=1)

add_test(NAME GuessTheNumberTests COMMAND GuessTheNumberTests)
