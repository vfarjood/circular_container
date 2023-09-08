//
// Created by vahid on 08/08/23.
//

#ifndef BANDYERLICODE_ERIZO_SRC_ERIZO_DATA_PACKET_CIRCULARCONTAINER_H_
#define BANDYERLICODE_ERIZO_SRC_ERIZO_DATA_PACKET_CIRCULARCONTAINER_H_

#include <array>
#include <type_traits>
#include <initializer_list>


namespace vfc {

// Forward declaration:
template<typename Tp, std::size_t _capacity, bool _const>
class circular_container_reverse_iterator;



// Iterate over elements in read/write mode //
template<typename Tp, std::size_t _capacity, bool _const>
class circular_container_iterator {

 public:

  // Standard type definitions
  using value_type        = typename Tp::value_type;
  using size_type         = typename Tp::size_type;
  using pointer           = value_type*;
  using const_pointer     = const value_type*;
  using reference         = value_type&;
  using const_reference   = const value_type&;
  using difference_type   = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;
  using self_type         = circular_container_iterator<Tp, _capacity, _const>;

  //Constructor:
  circular_container_iterator()
      : m_container(nullptr), m_index(0) {}

  circular_container_iterator(const self_type& other)
      : m_container(other.m_container), m_index(other.m_index) {}

  circular_container_iterator(self_type&& other)
      : m_container(other.m_container), m_index(other.m_index)
      {
        other.m_container = nullptr;
        other.m_index = 0;
      }

  explicit circular_container_iterator(Tp& container, size_type index)
      : m_container(&container), m_index(index) {}

  explicit circular_container_iterator(circular_container_reverse_iterator<Tp, _capacity, _const>& iter)
      : m_container(iter.data()), m_index(iter.index()) {}

  explicit circular_container_iterator(const circular_container_reverse_iterator<Tp, _capacity, _const>& iter)
      : m_container(iter.data()), m_index(iter.index()) {}

  self_type& operator=(const self_type& other) {
    if(this != &other){
      m_container = other.m_container;
      m_index = other.m_index;
    }
    return *this;
  }

  self_type& operator=(self_type&& other) {
    if(this != &other){
      m_container = other.m_container;
      m_index = other.m_index;
      other.m_container = nullptr;
      other.m_index = 0;
    }
    return *this;
  }

  ~circular_container_iterator() {
    m_container = nullptr;
    m_capacity  = 0;
    m_index     = 0;
  }

  // Operator overload:
  template<bool C = _const, typename std::enable_if<(!C), int>::type* = nullptr>
  [[nodiscard]] reference operator*() { // dereference operator
    return m_container->m_buffer[m_index];
  }
  template<bool C = _const, typename std::enable_if<(C), int>::type* = nullptr>
  [[nodiscard]] const_reference operator*() const { // dereference operator
    return m_container->m_buffer[m_index];
  }

  template<bool C = _const, typename std::enable_if<(!C), int>::type* = nullptr>
  [[nodiscard]] pointer operator->() { // Pointer to the element
    return &(m_container->m_buffer[m_index]);
  }

  template<bool C = _const, typename std::enable_if<(C), int>::type* = nullptr>
  [[nodiscard]] const_pointer operator->() const { // Pointer to the element
    return &(m_container->m_buffer[m_index]);
  }

  self_type& operator++() { // prefix increment
    ++m_index %= m_capacity;
    return *this;
  }

  self_type operator++(int) { // postfix increment
    auto temp_iterator = *this;
    ++m_index %= m_capacity;
    return temp_iterator;
  }

  self_type& operator--() { // prefix decrement
    if(m_index == 0){
      m_index = m_capacity - 1;
    } else {
      --m_index;
    }
    return *this;
  }

  self_type operator--(int) { // postfix decrement
    auto temp_iterator = *this;
    if(m_index == 0){
      m_index = m_capacity - 1;
    } else {
      --m_index;
    }
    return temp_iterator;
  }

  bool operator==(const self_type& other) {
    return m_index == other.m_index;
  }

  bool operator!=(const self_type& other) {
    return !(*this == other);
  }

  [[nodiscard]] size_type index() const noexcept {
    return m_index;
  }

  [[nodiscard]] Tp* data() const noexcept {
    return m_container;
  }

 private:
  Tp* m_container;
  size_type m_capacity = _capacity+1;
  size_type m_index;

};



 // Iterate over elements in read-only mode //
template<typename Tp, std::size_t _capacity, bool _const>
class circular_container_reverse_iterator {

 public:

  // Standard type definitions
  using value_type        = typename Tp::value_type;
  using size_type         = typename Tp::size_type;
  using pointer           = value_type*;
  using const_pointer     = const value_type*;
  using reference         = value_type&;
  using const_reference   = const value_type&;
  using difference_type   = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;
  using self_type         = circular_container_reverse_iterator<Tp, _capacity, _const>;

  //Constructor:
  circular_container_reverse_iterator()
      : m_container(nullptr), m_index(0) {}

  circular_container_reverse_iterator(const self_type& other)
      : m_container(other.m_container), m_index(other.m_index) {}

  circular_container_reverse_iterator(self_type&& other)
      : m_container(other.m_container), m_index(other.m_index)
      {
        other.m_container = nullptr;
        other.m_index = 0;
      }

  explicit circular_container_reverse_iterator(Tp& container, size_type index)
      : m_container(&container), m_index(index) {}

  explicit circular_container_reverse_iterator(circular_container_iterator<Tp, _capacity, _const>& iter)
      : m_container(iter.data()), m_index(iter.index()) {}

  explicit circular_container_reverse_iterator(const circular_container_iterator<Tp, _capacity, _const>& iter)
      : m_container(iter.data()), m_index(iter.index()) {}

  self_type& operator=(const self_type& other) {
    if(this != &other){
      m_container = other.m_container;
      m_index = other.m_index;
    }
    return *this;
  }

  self_type& operator=(self_type&& other) {
    if(this != &other){
      m_container = other.m_container;
      m_index = other.m_index;
      other.m_container = nullptr;
      other.m_index = 0;
    }
    return *this;
  }

  ~circular_container_reverse_iterator() {
    m_container = nullptr;
    m_capacity  = 0;
    m_index     = 0;
  }

  // Operator overload:
  template<bool C = _const, typename std::enable_if<(!C), int>::type* = nullptr>
  [[nodiscard]] reference operator*() { // dereference operator
    return m_container->m_buffer[m_index];
  }
  template<bool C = _const, typename std::enable_if<(C), int>::type* = nullptr>
  [[nodiscard]] const_reference operator*() const { // dereference operator
    return m_container->m_buffer[m_index];
  }

  template<bool C = _const, typename std::enable_if<(!C), int>::type* = nullptr>
  [[nodiscard]] pointer operator->() { // Pointer to the element
    return &(m_container->m_buffer[m_index]);
  }

  template<bool C = _const, typename std::enable_if<(C), int>::type* = nullptr>
  [[nodiscard]] const_pointer operator->() const { // Pointer to the element
    return &(m_container->m_buffer[m_index]);
  }

  self_type& operator++() { // prefix increment
    if(m_index == 0){
      m_index = m_capacity - 1;
    } else {
      --m_index;
    }
    return *this;
  }

  self_type operator++(int) { // postfix increment
    auto temp_iterator = *this;
    if(m_index == 0){
      m_index = m_capacity - 1;
    } else {
      --m_index;
    }
    return temp_iterator;
  }

  self_type& operator--() { // prefix decrement
    ++m_index %= m_capacity;
    return *this;
  }

  self_type operator--(int) { // postfix decrement
    auto temp_iterator = *this;
    ++m_index %= m_capacity;
    return temp_iterator;
  }

  bool operator==(const self_type& other) {
    return m_index == other.m_index;
  }

  bool operator!=(const self_type& other) {
    return !(*this == other);
  }

  [[nodiscard]] size_type index() const noexcept {
    return m_index;
  }

  [[nodiscard]] Tp* data() const noexcept {
    return m_container;
  }

 private:
  Tp* m_container;
  size_type m_capacity = _capacity+1;
  size_type m_index;

};


// Circular Container class implementation: ///
template<typename Tp, std::size_t _capacity>
class CircularContainer {
 public:

  // Standard type definitions used also in STL containers:
  using value_type              = Tp;
  using size_type               = std::size_t;
  using difference_type         = std::ptrdiff_t;
  using pointer                 = value_type*;
  using const_pointer           = const value_type*;
  using reference               = value_type&;
  using const_reference         = const value_type&;
  using iterator                = circular_container_iterator<CircularContainer<Tp, _capacity>, _capacity, false>;
  using const_iterator          = circular_container_iterator<CircularContainer<Tp, _capacity>, _capacity, true>;
  using reverse_iterator        = circular_container_reverse_iterator<CircularContainer<Tp, _capacity>, _capacity, false>;
  using const_reverse_iterator  = circular_container_reverse_iterator<CircularContainer<Tp, _capacity>, _capacity, true>;

  CircularContainer() = default;
  CircularContainer(const CircularContainer& other) = default;
  CircularContainer(CircularContainer&& other) = default;
  CircularContainer& operator=(const CircularContainer& other) = default;
  CircularContainer& operator=(CircularContainer&& other) = default;
  ~CircularContainer() = default;

  // Enable CircularContainer class to be brace initialized:
  explicit CircularContainer(std::initializer_list<value_type> values)
    {
      for(auto& item : values){
        this->insert(this->end(), item);
      }
    }

  // Modifiers
  void push_back(const value_type& item) {
    m_buffer[m_tail] = item;
    ++m_tail %= m_capacity;
    ++m_content_size;
    if(m_tail == m_head) {
      ++m_head %= m_capacity;
      m_content_size = m_capacity-1;
    }
  }
  void emplace_back(value_type&& item) {
    m_buffer[m_tail] = std::move(item);
    ++m_tail %= m_capacity;
    ++m_content_size;
    if(m_tail == m_head) {
      ++m_head %= m_capacity;
      m_content_size = m_capacity-1;
    }
  }

  void pop_front() {
    if(m_head != m_tail) {
      ++m_head %= m_capacity;
      --m_content_size;
    } else {
      clear();
    }
  }

  void insert(iterator pos, const value_type& item) {
    // inserts item before pos:
    for (auto it = end(); it != pos; --it){
      m_buffer[it.index()] = m_buffer[std::prev(it).index()];
    }
    m_buffer[pos.index()] = item;
    if(!full()) {
      ++m_tail %= m_capacity;
      ++m_content_size;
      if(m_tail == m_head) {
        ++m_head %= m_capacity;
        m_content_size = m_capacity-1;
      }
    }
  }

  void insert(iterator pos, value_type&& item) {
    // inserts item before pos:
    for (auto it = end(); it != pos; --it){
      m_buffer[it.index()] = m_buffer[std::prev(it).index()];
    }
    m_buffer[pos.index()] = std::move(item);
    if(!full()) {
      ++m_tail %= m_capacity;
      ++m_content_size;
      if(m_tail == m_head) {
        ++m_head %= m_capacity;
        m_content_size = m_capacity-1;
      }
    }
  }

  void clear() {
    m_content_size = 0;
    m_head = 0;
    m_tail = 0;
  }
  
  
  // Capacity:
  [[nodiscard]] constexpr size_type capacity() const noexcept{
    return m_capacity-1;
  }

  [[nodiscard]] constexpr bool empty() const noexcept{
    return !m_content_size;
  }
  [[nodiscard]] constexpr bool full() const noexcept{
    return m_content_size == m_capacity - 1;
  }

  [[nodiscard]] constexpr size_type size() const noexcept{
    return m_content_size;
  }
  

  // Iterators:
  iterator begin() {return iterator(*this, m_head);}

  iterator end() {return iterator(*this, m_tail);}

  const_iterator begin() const {return const_iterator(*this, m_head);}

  const_iterator end() const {return const_iterator(*this, m_tail);}

  const_iterator cbegin() {return const_iterator(*this, m_head);}

  const_iterator cend() {return const_iterator(*this, m_tail);}

  
  // reverse iterator
  reverse_iterator rbegin() {return reverse_iterator(*this, (--end()).index());}

  reverse_iterator rend() {return reverse_iterator(*this, (--begin()).index());}

  const_reverse_iterator rbegin() const {return const_reverse_iterator(*this, (--end()).index());}

  const_reverse_iterator rend() const {return onst_reverse_iterator(*this, (--begin()).index());}

  const_reverse_iterator crbegin() {return const_reverse_iterator(*this, (--end()).index());}

  const_reverse_iterator crend() {return const_reverse_iterator(*this, (--begin()).index());}

  
  // Element access:
  reference front() {
    // Undefined Behavior if container is empty!
    return *begin();
  }

  reference back() {
    // Undefined Behavior if container is empty!
    return *(--end());
  }

  const_reference front() const {
    // Undefined Behavior if container is empty!
    return *begin();
  }

  const_reference back() const {
    // Undefined Behavior if container is empty!
    return *(--end());
  }


 private:
  friend class circular_container_iterator<CircularContainer<Tp, _capacity>, _capacity, false>;
  friend class circular_container_iterator<CircularContainer<Tp, _capacity>, _capacity, true>;
  friend class circular_container_reverse_iterator<CircularContainer<Tp, _capacity>, _capacity, false>;
  friend class circular_container_reverse_iterator<CircularContainer<Tp, _capacity>, _capacity, true>;

  std::array<value_type, _capacity+1> m_buffer;
  size_type m_capacity = _capacity+1;
  size_type m_content_size = 0;
  size_type m_head = 0;
  size_type m_tail = 0;
};

// Deduction to enable CircularContainer class to be brace initialized: //
template<typename T, typename... Us>
CircularContainer(T first, Us... rest) -> CircularContainer<T, (std::is_same_v<T, Us> + ... + 1)>;

}
#endif //BANDYERLICODE_ERIZO_SRC_ERIZO_DATA_PACKET_CIRCULARCONTAINER_H_
