#include <iostream>


int main(int argc, char const *argv[]) {
  try {
    std::cout << "Hello world!" << std::endl;

    return 0;
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;

    return 1;
  }
}
