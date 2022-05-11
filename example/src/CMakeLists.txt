add_library(GuessTheNumberImpl STATIC
    GuessTheNumber.hxx GuessTheNumber.cxx
    CheckResult.hxx
    RandomNumberGenerator.hxx
    StdRandomNumberGenerator.hxx StdRandomNumberGenerator.cxx
    UserInterface.hxx
    ConsoleUserInterface.hxx ConsoleUserInterface.cxx
    )
target_include_directories(GuessTheNumberImpl INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(GuessTheNumberImpl PUBLIC staticdi)

add_executable(GuessTheNumber main.cxx)
target_link_libraries(GuessTheNumber PRIVATE
    GuessTheNumberImpl
    )
