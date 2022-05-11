#include <sdi.hxx>

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <iostream>
#include <sstream>
#include <string>

struct io_device {
  virtual ~io_device() noexcept = default;

  virtual void println(std::string const& message) = 0;
};

class outstream_device final : public io_device {
  std::ostream& out;

public:
  using dependencies = sdi::dependencies<std::ostream>;

  explicit outstream_device(std::ostream& out)
      :out{out}
  {
  }

  void println(std::string const& message) override
  {
    out << message << std::endl;
  }
};

class greeter final {
  io_device& io;

public:
  using dependencies = sdi::dependencies<io_device>;

  explicit greeter(io_device& io)
      :io{io}
  {
  }

  void greet(std::string const& whom = "World")
  {
    io.println("Hello, " + whom + "!");
  }
};

TEST_CASE("Can resolve object", "[container]")
{
  sdi::container<sdi::known_types<outstream_device, greeter, std::ostringstream>> c;

  auto& g = c.resolve<greeter>();
  g.greet();

  auto const& out = c.resolve<std::ostringstream>();
  CHECK(out.str() == "Hello, World!\n");
}

TEST_CASE("Can emplace global objects via reference wrapper", "[container]")
{
  sdi::container<sdi::known_types<outstream_device, greeter, std::reference_wrapper<std::ostream>>> c;
  c.emplace<std::reference_wrapper<std::ostream>>(std::cout);

  auto& g = c.resolve<greeter>();
  g.greet();
}
