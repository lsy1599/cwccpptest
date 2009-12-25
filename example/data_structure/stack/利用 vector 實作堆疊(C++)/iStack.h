#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;

class iStack
{
public:
  iStack(int capacity):_stack(capacity), _top(0) {}

  bool pop(int &value);
  bool push(int &value);
  bool peek(int &value);

  bool full();
  bool empty();
  void display();
  
  int size(); 			// 目前堆疊大小

private:
  int _top;
  vector<int> _stack;
};

