/*

This file is licensed under the X11 license:

Copyright (C) 2013 Andreas Ehliar

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL ANDREAS EHLIAR BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of Andreas Ehliar shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from Andreas Ehliar.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char **argv)
{
	int i;
	char **tmp;
	int j;

	for(i=0; i < 1000; i++){
		tmp[i] = malloc(1024*1024);
		if(!tmp[i]){
			printf("Cannot allocate memory\n");
			//exit(0); //do not stop the program, but keep the memory allocated
			break;
		}

		// Ensure the pages are actually allocated!
		for(j=0; j < 1024*1024; j+=1024){
			tmp[i][j] = 1;
		}
		printf("Allocated memory (%d MiB)\n",i);
	}
	int n;
	while(1){
		for(n = 0; n < i; n++){ //keep writing to the memory, so different pages are swapped out
			printf("writing at MiB %d\n", n);
			for(j=0; j < 1024*1024; j+=1024){
				tmp[n][j] = n%2;
			}
		}
	}
	return 0;
}
