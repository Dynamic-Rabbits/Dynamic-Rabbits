/**
 *  @file ub_env_var_test_app2.c
 *  @brief 
 *  @author John F.X. Galea
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){

	if (argc == 2){

		setenv("HELLO_TEST", "THIS IS THE TEST!", 1);
		setenv("HELLO_THERE", "WOOT!", 1);

		if (strcmp("okay", argv[1]) == 0){
			printf("The path variable is %s\n", getenv("HELLO_TEST"));
			printf("The other path variable is %s\n", getenv("HELLO_THERE"));

		}else{
			printf("Incorrect arg!");
		}
	}
}



