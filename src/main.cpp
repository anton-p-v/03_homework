#include <cstddef>
#include <iostream>
#include <memory>
#include <map>

#include "factorial/factorial.h"


template<typename T, size_t N>
class Allocator {
 public:
  using value_type = T;

  ~Allocator() noexcept {
    std::free(pool_ptr);
  }

  T* allocate(size_t n) {
    size_t current_index = pool_index + n;

    if (current_index <= N) {
      if (pool_ptr == nullptr) {
        if (auto current_ptr = std::malloc(N * sizeof(T))) {
          pool_ptr = static_cast<T*>(current_ptr);
          pool_index = current_index;

          return pool_ptr;
        }
      } else {
        auto current_ptr = pool_ptr + pool_index;

        pool_index = current_index;

        return current_ptr;
      }
    }

    throw std::bad_alloc();
  }

  void deallocate(T* p, std::size_t n) noexcept {
  }

  template<typename Node>
  struct rebind {
    using other = Allocator<Node, N>;
  };

  using propagate_on_container_copy_assignment = std::true_type;
  using propagate_on_container_move_assignment = std::true_type;
  using propagate_on_container_swap = std::true_type;

private:
  T* pool_ptr = nullptr;
  size_t pool_index = 0;
};

template<typename T1, size_t N1, typename T2, size_t N2>
bool operator==(const Allocator<T1, N1>& lhs, const Allocator<T2, N2>& rhs) {
  return lhs.pool_ptr == rhs.pool_ptr;
}
 
template<typename T1, size_t N1, typename T2, size_t N2>
bool operator!=(const Allocator<T1, N1>& lhs, const Allocator<T2, N2>& rhs) {
  return lhs.pool_ptr != rhs.pool_ptr;
}

template<typename T, typename Allocator = std::allocator<T>>
class Container {
 public:
  void push_back(const T& data) {
    Node* node = allocator_.allocate(1);

    node->next = nullptr;
    node->data = data;

    if (current_ == nullptr) {
      current_ = begin_ = node;
    } else {
      current_->next = node;
      current_ = node;
    }
  }

 private:
  struct Node {
    Node* next = nullptr;
    T data;
  };

  Node* begin_ = nullptr;
  Node* current_ = nullptr;

  typename Allocator::template rebind<Node>::other allocator_;

 public:
  class ContainerIt {
   public:
    ContainerIt(Node* node): position_(node) {}

    ContainerIt operator++() {
      if (position_ == nullptr) {
        return nullptr;
      }

      position_ = position_->next;

      return position_;
    }

    bool operator!=(const ContainerIt& rhs) {
      return position_ != rhs.position_;
    }

    T& operator*() const {
      return position_->data;
    }
   private: 
    Node* position_;
  };

  ContainerIt begin() {
    return begin_;
  }

  ContainerIt end() {
    return nullptr;
  }
};

int main(int argc, char const *argv[]) {
  std::map<
    int,
    int> map1;
  std::map<
    int,
    int,
    std::less<int>,
    Allocator<std::pair<const int, int>, 10>> map2;

  for (int i = 0; i < 10; ++i) {
    map1[i] = factorial(i);
  }
  for (int i = 0; i < 10; ++i) {
    map2[i] = factorial(i);
  }

  std::cout << "std::map<int, int>\n";
  for (const auto& [key, value] : map1) {
    std::cout << key << ' ' << value << '\n';
  }
  std::cout << '\n';
  std::cout << "std::map<int, int, std::less<int>, Allocator<std::pair<const int, int>, 10>>\n";
  for (const auto& [key, value] : map2) {
    std::cout << key << ' ' << value << '\n';
  }

  Container<int> container1;
  Container<int, Allocator<int, 10>> container2;

  for (int i = 0; i < 10; ++i) {
    container1.push_back(i);
  }
  for (int i = 0; i < 10; ++i) {
    container2.push_back(i);
  }

  std::cout << '\n';
  std::cout << "Container<int>\n";
  for (const auto& value : container1) {
    std::cout << value << '\n';
  }
  std::cout << '\n';
  std::cout << "Container<int, Allocator<int, 10>>\n";
  for (const auto& value : container2) {
    std::cout << value << '\n';
  }

  return 0;
}
