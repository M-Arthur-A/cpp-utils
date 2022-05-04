#pragma once
#include <cstddef>
#include <vector>

template <typename Iterator>
class IteratorRange {
public:
  IteratorRange(Iterator begin, Iterator end)
    : first(begin)
    , last(end)
    , size_(distance(first, last))
  {}

  Iterator begin() const { return first; }

  Iterator end() const { return last; }

  std::size_t size() const { return size_; }

private:
  Iterator first, last;
  std::size_t size_;
};

template <typename Iterator>
class Paginator {
private:
  std::vector<IteratorRange<Iterator>> pages;

public:
  Paginator(Iterator begin, Iterator end, std::size_t page_size) {
    for (std::size_t left = distance(begin, end); left > 0; ) {
      std::size_t current_page_size = std::min(page_size, left);
      Iterator current_page_end = next(begin, current_page_size);
      pages.push_back({begin, current_page_end});

      left -= current_page_size;
      begin = current_page_end;
    }
  }

  auto begin() const { return pages.begin(); }

  auto end() const { return pages.end(); }

  std::size_t size() const { return pages.size(); }
};

template <typename C>
auto Paginate(C& c, std::size_t page_size)
{
	return Paginator(c.begin(), c.end(), page_size);
}

template <typename C>
auto Paginate(C&& c, std::size_t page_size) {
	return Paginator(c.begin(), c.end(), page_size);
}
