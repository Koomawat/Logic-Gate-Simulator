#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char **argv)
{
	FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
		printf("error");
        return 0;
    }
	else
	{	
		char input[50];
        int read = fscanf( f, "%s ", &input);

		int inputs;
		read = fscanf( f, "%d ", &inputs);
		
		char input2[50];
		
		char inps[inputs][50];
		
		int inpCount = 0;
		
		memset(inps, '\0', sizeof(inps[0][0]) * inputs * 50);
		
		while(read != EOF)
		{
     		read = fscanf( f, "%s ", &input2);		
			strcpy(inps[inpCount],input2);		
			
			inpCount++;
			
			if (strcmp(input2,"OUTPUTVAR") == 0)
			{
				break;
			}			
		}
	
		int outp;
		read = fscanf( f, "%d ", &outp);
		
		int cn2 = 0;
		
		char outps[outp][50];
		
		memset(outps, '\0', sizeof(outps[0][0]) * outp * 50);
		
		while(read != EOF)
		{
     		read = fscanf( f, "%s ", &input2);
			strcpy(outps[cn2],input2);
		
			cn2++;
		
			if(strcmp(input2,"NOT") == 0
			|| strcmp(input2,"AND") == 0
			|| strcmp(input2,"OR") == 0
			|| strcmp(input2,"NAND") == 0
			|| strcmp(input2,"NOR") == 0
			|| strcmp(input2,"XOR") == 0)
			{
				break;
			}			
		}
	
		int power = pow(2,inputs);
		int results[power][outp+inputs];
		memset(results, 0, sizeof(results[0][0]) * (outp+inputs) * power);
	
		int x = 2;
		int count = 1;
		for(int a = 0; a < (outp+inputs); a++)
		{		
			int q = x/2;
			for(int i = q; i< power; i+=x)
			{
				for (int j = 0; j < q; j++)
				{
					results[i+j][inputs-count] = 1;
				}		
			}
			count++;
			x = x * 2;
		}
		
		int commands = 0;
		while(read != EOF)
		{	
			if(strcmp(input2,"NOT") == 0
			|| strcmp(input2,"AND") == 0
			|| strcmp(input2,"OR") == 0
			|| strcmp(input2,"NAND") == 0
			|| strcmp(input2,"NOR") == 0
			|| strcmp(input2,"XOR") == 0)
			{
			 	commands++;
			}
			read = fscanf( f, "%s ", &input2);
		}
		rewind(f);
		
		read = fscanf( f, "%s ", &input2);
		
		int temps[power][commands-outp];
		memset(temps, 0, sizeof(temps[0][0]) * (commands-outp) * power);
		
		int count2 = 0;
		
		char inps2[commands-outp][50];
		memset(inps2, '\0', sizeof(inps2[0][0]) * (commands-outp) * 50);

		while(read != EOF)
		{
			if(strcmp(input2,"NOT") == 0)
			{
				char inp1[50];
				read = fscanf( f, "%s ", &inp1);				
				char inp2[50];
				read = fscanf( f, "%s ", &inp2);
				
				int bool1;
				int tempi;
				for(int i = 0; i < outp; i++)
				{
					if(strcmp(outps[i],inp2) == 0)
					{
						bool1 = 1;
						tempi = i;
					}
				}
				if(bool1 != 1)
				{
					strcpy(inps2[count2],inp2);
					int tempj = 0;
					for(int i = 0; i < commands-outp+1; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							for(int j = 0; j < power; j++)
							{
								temps[j][count2] = !(results[j][tempj]);
							}		
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;
							for(int j = 0; j < power; j++)
							{
								temps[j][count2] = !(temps[j][tempj]);
							}	
						}
					}
					count2++;
				}
				else if(bool1 == 1)
				{
					int tempj = 0;
					for(int i = 0; i < commands-outp+1; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							for(int j = 0; j < power; j++)
							{
								if((results[j][tempj]) == 0)
								{
									results[j][tempi+inputs] = 1;
								}
								else
								{
									results[j][tempi+inputs] = 0;
								}
							}
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;
							for(int j = 0; j < power; j++)
							{
								if((temps[j][tempj]) == 0)
								{
									results[j][tempi+inputs] = 1;
								}
								else
								{
									results[j][tempi+inputs] = 0;
								}
							}						
						}
					}
				}				
			}
			else if(strcmp(input2,"AND") == 0)
			{
				char inp1[50];
				read = fscanf( f, "%s ", &inp1);
				char inp2[50];
				read = fscanf( f, "%s ", &inp2);
				char inp3[50];
				read = fscanf( f, "%s ", &inp3);

				int bool1;
				int tempi;
				for(int i = 0; i < outp; i++)
				{
					if(strcmp(outps[i],inp3) == 0)
					{
						bool1 = 1;
						tempi = i;
					}
				}

				if(bool1 != 1)
				{
					strcpy(inps2[count2],inp3);
					int tempj,tempk,code1,code2,code3,code4 = 0;
					for(int i = 0; i < commands-outp+1; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							code1 = 1;
							break;
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;		
							code2 = 1;		
							break;			
						}
					}
					for(int i = 0; i < commands-outp+1; i++)
					{
						if(strcmp(inps[i],inp2) == 0)
						{
							tempk = i;
							code3 = 1;
							break;	
						}
						else if(strcmp(inps2[i],inp2) == 0)
						{
							tempk = i;
							code4 = 1;	
							break;							
						}
					}

					if(code1 == 1 && code3 == 1)
					{
						//working with IN IN temp
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 && results[i][tempk] == 1)
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code1 == 1 && code4 == 1)
					{
						//working with IN temp temp
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 && temps[i][tempk] == 1)
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code2 == 1 && code3 == 1)
					{
						//working with temp IN temp
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 && results[i][tempk] == 1)
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code2 == 1 && code4 == 1)
					{
						//working with temp temp temp
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 && temps[i][tempk] == 1)
							{
								temps[i][count2] = 1;
							}
						}
					}
					count2++;
				}
				else if(bool1 == 1)
				{
					int tempj,tempk,code1,code2,code3,code4 = 0;
					for(int i = 0; i < commands+inputs; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							code1 = 1;
							break;
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;		
							code2 = 1;		
							break;			
						}
					}
					for(int i = 0; i < commands+inputs; i++)
					{
						if(strcmp(inps[i],inp2) == 0)
						{
							tempk = i;
							code3 = 1;
							break;	
						}
						else if(strcmp(inps2[i],inp2) == 0)
						{
							tempk = i;
							code4 = 1;	
							break;							
						}
					}

					if(code1 == 1 && code3 == 1)
					{
						//working with IN IN OUT
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 && results[i][tempk] == 1)
							{
								results[i][tempi+inputs] = 1;
							}
						}

					}
					else if(code1 == 1 && code4 == 1)
					{
						//working with IN temp OUT
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 &&  temps[i][tempk] == 1)
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
					else if(code2 == 1 && code3 == 1)
					{
						//working with temp IN OUT
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 && results[i][tempk] == 1)
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
					else if(code2 == 1 && code4 == 1)
					{
						//working with temp temp OUT
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 && temps[i][tempk] == 1)
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
				}
			}
			else if(strcmp(input2,"OR") == 0)
			{
				char inp1[50];
				read = fscanf( f, "%s ", &inp1);
				char inp2[50];
				read = fscanf( f, "%s ", &inp2);
				char inp3[50];
				read = fscanf( f, "%s ", &inp3);

				int bool1;
				int tempi;
				for(int i = 0; i < outp; i++)
				{
					//printf("%s\n",outps[i]);
					//printf("%s\n",inp2);
					if(strcmp(outps[i],inp3) == 0)
					{
						bool1 = 1;
						tempi = i;
					}
				}

				if(bool1 != 1)
				{
					strcpy(inps2[count2],inp3);
					int tempj,tempk,code1,code2,code3,code4 = 0;
					for(int i = 0; i < commands-outp+1; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							code1 = 1;
							break;
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;		
							code2 = 1;		
							break;			
						}
					}
					for(int i = 0; i < commands-outp+1; i++){
						if(strcmp(inps[i],inp2) == 0)
						{
							tempk = i;
							code3 = 1;
							break;	
						}
						else if(strcmp(inps2[i],inp2) == 0)
						{
							tempk = i;
							code4 = 1;	
							break;							
						}
					}

					if(code1 == 1 && code3 == 1)
					{
						//working with IN IN temp
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 || results[i][tempk] == 1)
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code1 == 1 && code4 == 1)
					{
						//working with IN temp temp
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 || temps[i][tempk] == 1)
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code2 == 1 && code3 == 1)
					{
						//working with temp IN temp
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 || results[i][tempk] == 1)
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code2 == 1 && code4 == 1)
					{
						//working with temp temp temp
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 || temps[i][tempk] == 1)
							{
								temps[i][count2] = 1;
							}
						}
					}
					count2++;
				}
				else if(bool1 == 1)
				{
					int tempj,tempk,code1,code2,code3,code4 = 0;
					for(int i = 0; i < commands+inputs; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							code1 = 1;
							break;
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;		
							code2 = 1;		
							break;			
						}
					}
					for(int i = 0; i < commands+inputs; i++)
					{
						if(strcmp(inps[i],inp2) == 0)
						{
							tempk = i;
							code3 = 1;
							break;	
						}
						else if(strcmp(inps2[i],inp2) == 0)
						{
							tempk = i;
							code4 = 1;	
							break;							
						}
					}

					if(code1 == 1 && code3 == 1)
					{
						//working with IN IN OUT
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 || results[i][tempk] == 1)
							{
								results[i][tempi+inputs] = 1;
							}
						}

					}
					else if(code1 == 1 && code4 == 1)
					{
						//working with IN temp OUT
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 || temps[i][tempk] == 1)
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
					else if(code2 == 1 && code3 == 1)
					{
						//working with temp IN OUT
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 || results[i][tempk] == 1)
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
					else if(code2 == 1 && code4 == 1)
					{
						//working with temp temp OUT
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 || temps[i][tempk] == 1)
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
				}
			}
			else if(strcmp(input2,"NAND") == 0)
			{
				char inp1[50];
				read = fscanf( f, "%s ", &inp1);
				char inp2[50];
				read = fscanf( f, "%s ", &inp2);
				char inp3[50];
				read = fscanf( f, "%s ", &inp3);

				int bool1;
				int tempi;
				for(int i = 0; i < outp; i++)
				{
					//printf("%s\n",outps[i]);
					//printf("%s\n",inp2);
					if(strcmp(outps[i],inp3) == 0)
					{
						bool1 = 1;
						tempi = i;
					}
				}

				if(bool1 != 1)
				{
					strcpy(inps2[count2],inp3);
					int tempj,tempk,code1,code2,code3,code4 = 0;
					for(int i = 0; i < commands-outp+1; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							code1 = 1;
							break;
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;		
							code2 = 1;		
							break;			
						}
					}
					for(int i = 0; i < commands-outp+1; i++)
					{
						if(strcmp(inps[i],inp2) == 0)
						{
							tempk = i;
							code3 = 1;
							break;	
						}
						else if(strcmp(inps2[i],inp2) == 0)
						{
							tempk = i;
							code4 = 1;	
							break;							
						}
					}

					if(code1 == 1 && code3 == 1)
					{
						//working with IN IN temp
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 && results[i][tempk] == 1)
							{
								
							}
							else
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code1 == 1 && code4 == 1)
					{
						//working with IN temp temp
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 && temps[i][tempk] == 1)
							{
								
							}
							else
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code2 == 1 && code3 == 1)
					{
						//working with temp IN temp
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 && results[i][tempk] == 1)
							{
								
							}
							else
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code2 == 1 && code4 == 1)
					{
						//working with temp temp temp
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 && temps[i][tempk] == 1)
							{
								
							}
							else
							{
								temps[i][count2] = 1;
							}
						}
					}
					count2++;
				}
				else if(bool1 == 1)
				{
					int tempj,tempk,code1,code2,code3,code4 = 0;
					for(int i = 0; i < commands+inputs; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							code1 = 1;
							break;
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;		
							code2 = 1;		
							break;			
						}
					}
					for(int i = 0; i < commands+inputs; i++)
					{
						if(strcmp(inps[i],inp2) == 0)
						{
							tempk = i;
							code3 = 1;
							break;	
						}
						else if(strcmp(inps2[i],inp2) == 0)
						{
							tempk = i;
							code4 = 1;	
							break;							
						}
					}

					if(code1 == 1 && code3 == 1)
					{
						//working with IN IN OUT
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 && results[i][tempk] == 1)
							{
								
							}
							else
							{
								results[i][tempi+inputs] = 1;
							}
						}

					}
					else if(code1 == 1 && code4 == 1)
					{
						//working with IN temp OUT
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 1 && temps[i][tempk] == 1)
							{
								
							}
							else
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
					else if(code2 == 1 && code3 == 1)
					{
						//working with temp IN OUT
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 && results[i][tempk] == 1)
							{
								
							}
							else
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
					else if(code2 == 1 && code4 == 1)
					{
						//working with temp temp OUT
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 1 && temps[i][tempk] == 1)
							{
								
							}
							else
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
				}
			}
			else if(strcmp(input2,"NOR") == 0)
			{
				char inp1[50];
				read = fscanf( f, "%s ", &inp1);
				char inp2[50];
				read = fscanf( f, "%s ", &inp2);
				char inp3[50];
				read = fscanf( f, "%s ", &inp3);

				int bool1;
				int tempi;
				for(int i = 0; i < outp; i++)
				{
					//printf("%s\n",outps[i]);
					//printf("%s\n",inp2);
					if(strcmp(outps[i],inp3) == 0)
					{
						bool1 = 1;
						tempi = i;
					}
				}

				if(bool1 != 1)
				{
					strcpy(inps2[count2],inp3);
					int tempj,tempk,code1,code2,code3,code4 = 0;
					for(int i = 0; i < commands-outp+1; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							code1 = 1;
							break;
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;		
							code2 = 1;		
							break;			
						}
					}
					for(int i = 0; i < commands-outp+1; i++)
					{
						if(strcmp(inps[i],inp2) == 0)
						{
							tempk = i;
							code3 = 1;
							break;	
						}
						else if(strcmp(inps2[i],inp2) == 0)
						{
							tempk = i;
							code4 = 1;	
							break;							
						}
					}

					if(code1 == 1 && code3 == 1)
					{
						//working with IN IN temp
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 0 && results[i][tempk] == 0)
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code1 == 1 && code4 == 1)
					{
						//working with IN temp temp
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 0 && temps[i][tempk] == 0)
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code2 == 1 && code3 == 1)
					{
						//working with temp IN temp
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 0 && results[i][tempk] == 0)
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code2 == 1 && code4 == 1)
					{
						//working with temp temp temp
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 0 && temps[i][tempk] == 0)
							{
								temps[i][count2] = 1;
							}
						}
					}
					count2++;
				}
				else if(bool1 == 1)
				{
					int tempj,tempk,code1,code2,code3,code4 = 0;
					for(int i = 0; i < commands+inputs; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							code1 = 1;
							break;
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;		
							code2 = 1;		
							break;			
						}
					}
					for(int i = 0; i < commands+inputs; i++)
					{
						if(strcmp(inps[i],inp2) == 0)
						{
							tempk = i;
							code3 = 1;
							break;	
						}
						else if(strcmp(inps2[i],inp2) == 0)
						{
							tempk = i;
							code4 = 1;	
							break;							
						}
					}

					if(code1 == 1 && code3 == 1)
					{
						//working with IN IN OUT
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 0 && results[i][tempk] == 0)
							{
								results[i][tempi+inputs] = 1;
							}
						}

					}
					else if(code1 == 1 && code4 == 1)
					{
						//working with IN temp OUT
						for(int i = 0; i < power; i++)
						{
							if(results[i][tempj] == 0 &&  temps[i][tempk] == 0)
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
					else if(code2 == 1 && code3 == 1)
					{
						//working with temp IN OUT
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 0 && results[i][tempk] == 0)
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
					else if(code2 == 1 && code4 == 1)
					{
						//working with temp temp OUT
						for(int i = 0; i < power; i++)
						{
							if(temps[i][tempj] == 0 && temps[i][tempk] == 0)
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
				}
			}
			else if(strcmp(input2,"XOR") == 0)
			{
				char inp1[50];
				read = fscanf( f, "%s ", &inp1);
				char inp2[50];
				read = fscanf( f, "%s ", &inp2);
				char inp3[50];
				read = fscanf( f, "%s ", &inp3);

				int bool1;
				int tempi;
				for(int i = 0; i < outp; i++)
				{
					//printf("%s\n",outps[i]);
					//printf("%s\n",inp2);
					if(strcmp(outps[i],inp3) == 0)
					{
						bool1 = 1;
						tempi = i;
					}
				}

				if(bool1 != 1)
				{
					strcpy(inps2[count2],inp3);
					int tempj,tempk,code1,code2,code3,code4 = 0;
					for(int i = 0; i < commands-outp+1; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							code1 = 1;
							break;
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;		
							code2 = 1;		
							break;			
						}
					}
					for(int i = 0; i < commands-outp+1; i++)
					{
						if(strcmp(inps[i],inp2) == 0)
						{
							tempk = i;
							code3 = 1;
							break;	
						}
						else if(strcmp(inps2[i],inp2) == 0)
						{
							tempk = i;
							code4 = 1;	
							break;							
						}
					}

					if(code1 == 1 && code3 == 1)
					{
						//working with IN IN temp
						for(int i = 0; i < power; i++)
						{
							if((results[i][tempj] == 1 && results[i][tempk] == 0) || results[i][tempj] == 0 && results[i][tempk] == 1)
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code1 == 1 && code4 == 1)
					{
						//working with IN temp temp
						for(int i = 0; i < power; i++)
						{
							if((results[i][tempj] == 1 && temps[i][tempk] == 0) || (results[i][tempj] == 0 && temps[i][tempk] == 1))
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code2 == 1 && code3 == 1)
					{
						//working with temp IN temp
						for(int i = 0; i < power; i++)
						{
							if((temps[i][tempj] == 1 && results[i][tempk] == 0) || (temps[i][tempj] == 0 && results[i][tempk] == 1))
							{
								temps[i][count2] = 1;
							}
						}
					}
					else if(code2 == 1 && code4 == 1)
					{
						//working with temp temp temp
						for(int i = 0; i < power; i++)
						{
							if((temps[i][tempj] == 1 && temps[i][tempk] == 0) || (temps[i][tempj] == 0 && temps[i][tempk] == 1))
							{
								temps[i][count2] = 1;
							}
						}
					}
					count2++;
				}
				else if(bool1 == 1)
				{
					int tempj,tempk,code1,code2,code3,code4 = 0;
					for(int i = 0; i < commands+inputs; i++)
					{
						if(strcmp(inps[i],inp1) == 0)
						{
							tempj = i;
							code1 = 1;
							break;
						}
						else if(strcmp(inps2[i],inp1) == 0)
						{
							tempj = i;		
							code2 = 1;		
							break;			
						}
					}
					for(int i = 0; i < commands+inputs; i++)
					{
						if(strcmp(inps[i],inp2) == 0)
						{
							tempk = i;
							code3 = 1;
							break;	
						}
						else if(strcmp(inps2[i],inp2) == 0)
						{
							tempk = i;
							code4 = 1;	
							break;							
						}
					}

					if(code1 == 1 && code3 == 1)
					{
						//working with IN IN OUT
						for(int i = 0; i < power; i++)
						{
							if((results[i][tempj] == 1 && results[i][tempk] == 0) || (results[i][tempj] == 0 && results[i][tempk] == 1))
							{
								results[i][tempi+inputs] = 1;
							}
						}

					}
					else if(code1 == 1 && code4 == 1)
					{
						//working with IN temp OUT
						for(int i = 0; i < power; i++)
						{
							if((results[i][tempj] == 1 &&  temps[i][tempk] == 0) || (results[i][tempj] == 0 &&  temps[i][tempk] == 1))
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
					else if(code2 == 1 && code3 == 1)
					{
						//working with temp IN OUT
						for(int i = 0; i < power; i++)
						{
							if((temps[i][tempj] == 1 && results[i][tempk] == 0) || (temps[i][tempj] == 0 && results[i][tempk] == 1))
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
					else if(code2 == 1 && code4 == 1)
					{
						//working with temp temp OUT
						for(int i = 0; i < power; i++)
						{
							if((temps[i][tempj] == 1 && temps[i][tempk] == 0) || (temps[i][tempj] == 0 && temps[i][tempk] == 1))
							{
								results[i][tempi+inputs] = 1;
							}
						}
					}
				}
			}
			read = fscanf( f, "%s ", &input2);
		}
		for(int i = 0; i < power; i++)
		{
			for(int j = 0; j < (outp+inputs); j++)
			{
				printf("%d ", results[i][j]);
			}
			printf("\n");
		}
		fclose(f); 
	}
}