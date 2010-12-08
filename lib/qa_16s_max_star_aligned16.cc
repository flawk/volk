#include <volk/volk.h>
#include <qa_16s_max_star_aligned16.h>
#include <volk/volk_16s_max_star_aligned16.h>
#include <cstdlib>
#include <time.h>
//test for ssse3

#ifndef LV_HAVE_SSSE3

void qa_16s_max_star_aligned16::t1() {
  printf("ssse3 not available... no test performed\n");
}

#else



void qa_16s_max_star_aligned16::t1() {
  
  volk_environment_init();
  clock_t start, end;
  double total;
  const int vlen = 6400;
  const int ITERS = 100000;
  short input0[vlen] __attribute__ ((aligned (16)));
  short output0[1] __attribute__ ((aligned (16)));

  short output1[1] __attribute__ ((aligned (16)));

  for(int i = 0; i < vlen; ++i) {
    short plus0 = ((short) (rand() - (RAND_MAX/2))) >> 2;

    short minus0 = ((short) (rand() - (RAND_MAX/2))) >> 2;
    
    input0[i] = plus0 - minus0;
    
  }
  printf("16s_max_star_aligned\n");

  start = clock();
  for(int count = 0; count < ITERS; ++count) {
    volk_16s_max_star_aligned16_manual(output0, input0, vlen << 1, "generic");
  }
  end = clock();
  total = (double)(end-start)/(double)CLOCKS_PER_SEC;
  printf("generic_time: %f\n", total);
  start = clock();
  for(int count = 0; count < ITERS; ++count) {
    volk_16s_max_star_aligned16_manual(output1, input0, vlen << 1, "ssse3");
  }
  end = clock();
  total = (double)(end-start)/(double)CLOCKS_PER_SEC;
  printf("ssse3_time: %f\n", total);
  for(int i = 0; i < 1; ++i) {
    //printf("inputs: %d, %d\n", input0[i*2], input0[i*2 + 1]);
    //printf("generic... %d, ssse3... %d\n", output0[i], output1[i]);
  }
  
  for(int i = 0; i < 1; ++i) {
    
    CPPUNIT_ASSERT_EQUAL(output0[i], output1[i]);
  }
}

#endif