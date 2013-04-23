/*
 * gen_rand_array.c
 */


int randomize_in_place(int* Array, int lenth)
{
   int temp = 0;
   int i = 0;
   int random_index = 0;
   srand((int)time(0));
   for (i=0; i<lenth; i++){
      //Swap a[i] and a[random(i,n)]
      temp = Array[i];
      random_index = i + (int)(rand() % (lenth - i));
      Array[i] = Array[random_index];
      Array[random_index] = temp;
   }
   return 1;
}

