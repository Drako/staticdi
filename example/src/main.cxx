#include "ConsoleUserInterface.hxx"
#include "StdRandomNumberGenerator.hxx"
#include "GuessTheNumber.hxx"

#include <iostream>

#include <sdi/container.hxx>

using game_container = sdi::container<
    sdi::known_types<
        ConsoleUserInterface,
        StdRandomNumberGenerator,
        GuessTheNumber
    >
>;
using app_container = sdi::container<
    sdi::known_types<
        std::reference_wrapper<std::ostream>,
        std::reference_wrapper<std::istream>
    >,
    sdi::installed_containers<
        game_container
    >
>;

int main()
{
  auto& game = app_container::use_threadsafe([](app_container& c) -> GuessTheNumber& {
    return c
        .emplace<std::reference_wrapper<std::ostream>>(std::cout)
        .emplace<std::reference_wrapper<std::istream>>(std::cin)
        .resolve<GuessTheNumber>();
  });
  game.run();
}
