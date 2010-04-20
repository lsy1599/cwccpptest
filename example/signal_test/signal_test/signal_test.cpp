// signal_test.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include <boost/signals.hpp>
class Button {
    typedef boost::signal<void (int x, int y)> onClick;

public:
    void doOnClick(const onClick::slot_type& slot);

private:
    onClick m_onClick;
};


int _tmain(int argc, _TCHAR* argv[])
{
	
	return 0;
}

