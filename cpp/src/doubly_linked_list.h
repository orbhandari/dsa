#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <cassert>
#include <expected>
#include <memory>
#include <optional>
#include <ostream>

namespace V1 {

enum class Error {
    invalid_state,
    invalid_input,
    node_not_found,
};

template <typename T>
class DoublyLinkedList {
  private:
    struct Node;

  public:
    DoublyLinkedList() = default;
    DoublyLinkedList(T value);
    DoublyLinkedList(DoublyLinkedList&&) = default;
    DoublyLinkedList(const DoublyLinkedList&) = default;
    DoublyLinkedList& operator=(DoublyLinkedList&&) = default;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = default;
    ~DoublyLinkedList() = default;

    void append(T value);
    auto insertAfter(std::shared_ptr<Node> node, T value) -> std::expected<void, Error>;
    auto insertBefore(std::shared_ptr<Node> node, T value) -> std::expected<void, Error>;
    void remove(std::shared_ptr<Node> node);
    auto find(T value) const -> std::optional<std::shared_ptr<Node>>;
    auto getHead() const -> std::shared_ptr<Node>;
    auto getTail() const -> std::shared_ptr<Node>;
    int getSize() const {
        return m_size;
    };
    bool isEmpty() const {
        return m_size == 0;
    };

    friend std::ostream& operator<<(std::ostream& out, const DoublyLinkedList& list) {
        auto iterator{list.getHead()};
        while (iterator) {
            out << iterator->value << " ";
            iterator = iterator->next;
        }
        return out;
    }

  private:
    struct Node {
        T value{};
        std::shared_ptr<Node> next{};
        std::shared_ptr<Node> prev{};
    };

    std::shared_ptr<Node> m_head{};
    std::shared_ptr<Node> m_tail{};
    int m_size{0};
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(T value)
    : m_head{std::make_shared<Node>(value)}, m_tail{m_head}, m_size{1} {};

template <typename T>
auto DoublyLinkedList<T>::getHead() const -> std::shared_ptr<Node> {
    return m_head;
}

template <typename T>
auto DoublyLinkedList<T>::getTail() const -> std::shared_ptr<Node> {
    return m_tail;
}

template <typename T>
void DoublyLinkedList<T>::append(T value) {

    if (isEmpty()) {
        m_head = std::make_shared<Node>(value);
        m_tail = m_head;
        ++m_size;
    } else {
        assert(m_tail != nullptr);
        insertAfter(getTail(), value);
    }
};

template <typename T>
auto DoublyLinkedList<T>::insertAfter(std::shared_ptr<Node> node, T value)
    -> std::expected<void, Error> {
    assert(node && "Node cannot be null.");
    if (!node) {
        return std::unexpected(Error::invalid_input);
    }

    auto iterator{getHead()};
    while (iterator) {
        if (iterator == node) {
            auto nextNode{iterator->next};
            auto newNode{std::make_shared<Node>(value, nextNode, iterator)};
            if (iterator == getTail())
                m_tail = newNode;
            else
                nextNode->prev = newNode;
            iterator->next = newNode;
            ++m_size;
            return {};
        }

        iterator = iterator->next;
    }

    return std::unexpected(Error::node_not_found);
}

template <typename T>
auto DoublyLinkedList<T>::insertBefore(std::shared_ptr<Node> node, T value)
    -> std::expected<void, Error> {
    assert(node && "Node cannot be null.");
    if (!node) {
        return std::unexpected(Error::invalid_input);
    }
    auto head{getHead()};
    if (node == head) {
        auto newNode{std::make_shared<Node>(value, head)};
        head->prev = newNode;
        m_head = newNode;
        ++m_size;
        return {};
    }

    auto iterator{head};
    while (iterator) {
        if (iterator == node) {
            auto prevNode{iterator->prev};
            auto newNode{std::make_shared<Node>(value, iterator, prevNode)};
            prevNode->next = newNode;
            iterator->prev = newNode;
            ++m_size;
            return {};
        }

        iterator = iterator->next;
    }

    return std::unexpected(Error::node_not_found);
}

template <typename T>
auto DoublyLinkedList<T>::find(T value) const -> std::optional<std::shared_ptr<Node>> {
    auto iterator{getHead()};
    while (iterator) {
        if (iterator->value == value) {
            return iterator;
        }

        iterator = iterator->next;
    }

    return std::nullopt;
};

template <typename T>
void DoublyLinkedList<T>::remove(std::shared_ptr<Node> node) {

    auto iterator{getHead()};
    while (iterator) {
        if (iterator == node) {

            auto prevNode{iterator->prev};
            auto nextNode{iterator->next};

            if (prevNode) {
                prevNode->next = nextNode;
            } else {
                m_head = nextNode;
            }

            if (nextNode) {
                nextNode->prev = prevNode;
            } else {
                m_tail = prevNode;
            }

            --m_size;
        }

        iterator = iterator->next;
    }
};
} // namespace V1

#endif
