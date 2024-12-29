#ifndef UTILS_H__
#define UTILS_H__
#include <stdint.h>

#define appendInt32ToArray(array, cursor, var32_t) \
			array[cursor+0]=(var32_t>>24)&0xFF;\
			array[cursor+1]=(var32_t>>16)&0xFF;\
			array[cursor+2]=(var32_t>>8)&0xFF;\
			array[cursor+3]=(var32_t)&0xFF;
			
#define appendInt64ToArray(array, cursor, var64_t) \
			array[cursor+0]=(var64_t>>(8*7))&0xFF;\
			array[cursor+1]=(var64_t>>(8*6))&0xFF;\
			array[cursor+2]=(var64_t>>(8*5))&0xFF;\
			array[cursor+3]=(var64_t>>(8*4))&0xFF;\
			array[cursor+4]=(var64_t>>(8*3))&0xFF;\
			array[cursor+5]=(var64_t>>(8*2))&0xFF;\
			array[cursor+6]=(var64_t>>(8*1))&0xFF;\
			array[cursor+7]=(var64_t)&0xFF;
			
#define ArrayToInt32(array, cursor, var32_t)\
			var32_t  = ((uint32_t)array[cursor+0])<<(8*3);\
			var32_t += ((uint32_t)array[cursor+1])<<(8*2);\
			var32_t += ((uint32_t)array[cursor+2])<<(8*1);\
			var32_t += ((uint32_t)array[cursor+3]);
			
#define ArrayToInt64(array, cursor, var64_t)\
			var64_t  = ((uint64_t)array[cursor+0])<<(8*7);\
			var64_t += ((uint64_t)array[cursor+1])<<(8*6);\
			var64_t += ((uint64_t)array[cursor+2])<<(8*5);\
			var64_t += ((uint64_t)array[cursor+3])<<(8*4);\
			var64_t += ((uint64_t)array[cursor+4])<<(8*3);\
			var64_t += ((uint64_t)array[cursor+5])<<(8*2);\
			var64_t += ((uint64_t)array[cursor+6])<<(8*1);\
			var64_t += ((uint64_t)array[cursor+7]);

#endif
