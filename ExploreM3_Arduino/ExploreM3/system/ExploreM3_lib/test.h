#ifdef __cplusplus
extern "C" {
#endif
 
#ifndef _TEST_H
#define _TEST_H

#include"stdutils.h"

class TestProg
{
	public:	
		TestProg(void);
		void LoopRun(void);
		void initializeTest();
};


extern TestProg test;


#endif

#ifdef __cplusplus
}
#endif