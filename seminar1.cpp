#include <iostream>
#include <assert.h>
#include <string>
#include <sstream>

template<typename T>
class Queue {
    struct Node {
        Node(const T& value): value(value), next(nullptr) {
        }

        T value;
        Node* next;
    };
public:
    Queue(): head(nullptr), tail(head)  {
    }

    ~Queue() {
        while (!is_empty()) {
            pop();
        }
    }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    bool is_empty() const { return (head == nullptr && head == tail); };

    void push(const T& value) {
        Node* node = new Node(value);
        if (is_empty()) {
            head = node;
            tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    }

    T pop() {
        Node* tmp_node = head;
        T value = tmp_node->value;

        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete tmp_node;
        return value;
    }


private:
    Node* head;
    Node* tail;
};

void testQueue() {
    {
        Queue<int> q;
        assert(q.is_empty());
    }

    {
        Queue<int> q;
        q.push(1);
        assert(!q.is_empty());

        int v = q.pop();

        assert(v == 1);
        assert(q.is_empty());
    }
    {
        Queue<int> q;
        for (int i = 0; i < 100; i++) {
            q.push(i);
        }
        assert(!q.is_empty());
        for (int i = 0; i < 100; i++) {
            assert(q.pop() == i);
        }
        assert(q.is_empty());
    }
    {
        Queue<std::string> q;
        q.push("1");
        q.push("2");
        assert(!q.is_empty());
        assert(q.pop() == "1");
        assert(q.pop() == "2");
    }
    std::cout << "Tests Queue OK" << std::endl;
}

int run(std::istream& input, std::ostream& output) {
    Queue<int> q;
    int commands_count = 0;
    input >> commands_count;

    for (int i = 0; i < commands_count; i++) {
        int command = 0;
        int expected = 0;
        input >> command >> expected;
        switch (command)
        {
        case 2: //pop
            {
                int value = q.is_empty() ? -1 : q.pop();
                if (value != expected) {
                    output << "NO" << std::endl;
                    return 0;
                }
            }
            break;
        case 3: //push
            q.push(expected);
            break;
        default:
            output << "NO" << std::endl;
            return 0;
        }
    }
    output << "YES" << std::endl;
    return 0;
}

void testLogic() {
    {
        std::stringstream input;
        std::stringstream output;
        input << "3" << std::endl;
        input << "3 44\n";
        input << "3 50\n";
        input << "2 44\n";
        run(input, output);
        std::cout << output.str() << std::endl;
        std::string s = output.str();
        for (char c : s) {
            std::cout << std::hex << (int)c << std::endl;
        }
        assert(output.str() == "YES\n");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "2\n";
        input << "2 -1\n";
        input << "3 10\n";

        run(input, output);
        assert(output.str() == "YES\n");
    }
    {
        std::stringstream input;
        std::stringstream output;
        input << "2\n";
        input << "3 44\n";
        input << "2 66\n";

        run(input, output);
        assert(output.str() == "NO\n");
    }
    std::cout << "Tests Logic OK" << std::endl;
}

void run_tests() {
    testQueue();
    testLogic();
}
int main() {
    //run_tests();
    return run(std::cin, std::cout);
}
